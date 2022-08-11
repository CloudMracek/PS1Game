#include "display.h"

// Dual buffer vars
DB db[2];
int db_active = 0;
char *db_nextpri;
RECT screen_clip;

// Lighting
MATRIX color_mtx = {
    ONE, 0, 0, // Red
    0,   0, 0, // Green
    ONE, 0, 0  // Blue
};

MATRIX light_mtx = {
    /* X,  Y,  Z */
    -2048, -2048, -2048, 0, 0, 0, 0, 0, 0};

// Geometry vars
int i, p, xy_temp;
int px, py;

SVECTOR rot;
VECTOR pos;

SVECTOR verts[17][17];

VECTOR cam_pos;
VECTOR cam_rot;

VECTOR tpos;
SVECTOR trot;
MATRIX mtx, lmtx;

POLY_F4 *pol4;

void initDisplay() {
  ResetGraph(0);

  // DB 1
  SetDefDispEnv(&db[0].disp, 0, 0, SCREEN_XRES, SCREEN_YRES);
  SetDefDrawEnv(&db[0].draw, 0, SCREEN_YRES, SCREEN_XRES, SCREEN_YRES);

  setRGB0(&db[0].draw, 63, 0, 127);
  db[0].draw.isbg = 1;
  db[0].draw.dtd = 1;

  // DB 2
  SetDefDispEnv(&db[1].disp, 0, SCREEN_YRES, SCREEN_XRES, SCREEN_YRES);
  SetDefDrawEnv(&db[1].draw, 0, 0, SCREEN_XRES, SCREEN_YRES);

  setRGB0(&db[1].draw, 63, 0, 127);
  db[1].draw.isbg = 1;
  db[1].draw.dtd = 1;

  PutDrawEnv(&db[0].draw);

  ClearOTagR(db[0].ot, OT_LEN);
  ClearOTagR(db[1].ot, OT_LEN);

  db_nextpri = db[0].p;

  setRECT(&screen_clip, 0, 0, SCREEN_XRES, SCREEN_YRES);

  InitGeom();

  gte_SetGeomOffset(CENTERX, CENTERY);

  gte_SetGeomScreen(CENTERX);

  gte_SetBackColor(63, 63, 63);
  gte_SetColorMatrix(&color_mtx);

  setVector(&cam_pos, 0, ONE * -200, 0);
  setVector(&cam_rot, 0, 0, 0);

#ifdef LOAD_FONT
  FntLoad(960, 0);
  FntOpen(0, 8, 320, 216, 0, 100);
#endif
}

void display() {
  DrawSync(0);
  VSync(0);

  db_active ^= 1;
  db_nextpri = db[db_active].p;

  ClearOTagR(db[db_active].ot, OT_LEN);

  PutDrawEnv(&db[db_active].draw);
  PutDispEnv(&db[db_active].disp);

  SetDispMask(1);

  DrawOTag(db[1 - db_active].ot + (OT_LEN - 1));
}

void begin() {
  RotMatrix(&trot, &mtx);

  tpos.vx = -cam_pos.vx >> 12;
  tpos.vy = -cam_pos.vy >> 12;
  tpos.vz = -cam_pos.vz >> 12;

  ApplyMatrixLV(&mtx, &tpos, &tpos);
  TransMatrix(&mtx, &tpos);

  gte_SetRotMatrix(&mtx);
  gte_SetTransMatrix(&mtx);
}

void end() {
  FntFlush(-1);
  display();
}

void sortObject(OBJECT *obj) {
int i,p;
	POLY_F4 *pol4;
	
	// Object and light matrix for object
	MATRIX omtx,lmtx;
	
	// Set object rotation and position
	RotMatrix( &rot, &omtx );
	TransMatrix( &omtx, &pos );
	
	// Multiply light matrix to object matrix
	MulMatrix0( &light_mtx, &omtx, &lmtx );
	
	// Set result to GTE light matrix
	gte_SetLightMatrix( &lmtx );
	
	// Composite coordinate matrix transform, so object will be rotated and
	// positioned relative to camera matrix (mtx), so it'll appear as
	// world-space relative.
	CompMatrixLV( &mtx, &omtx, &omtx );
	
	// Save matrix
	PushMatrix();
	
	// Set matrices
	gte_SetRotMatrix( &omtx );
	gte_SetTransMatrix( &omtx );
	
	// Sort the cube
	pol4 = (POLY_F4*)db_nextpri;
	
	for( i=0; i<obj->faces_num; i++ ) {
		
		// Load the first 3 vertices of a quad to the GTE 
		gte_ldv3( 
			obj->vertex_data[obj->vertex_indices[i].v0], 
			obj->vertex_data[obj->vertex_indices[i].v1], 
			obj->vertex_data[obj->vertex_indices[i].v2] );
			
		// Rotation, Translation and Perspective Triple
		gte_rtpt();
		
		// Compute normal clip for backface culling
		gte_nclip();
		
		// Get result
		gte_stopz( &p );
		
		// Skip this face if backfaced
		if( p < 0 )
			continue;
		
		// Calculate average Z for depth sorting
		gte_avsz3();
		gte_stotz( &p );
		
		// Skip if clipping off
		// (the shift right operator is to scale the depth precision)
		if( ((p>>2) <= 0) || ((p>>2) >= OT_LEN) )
			continue;
		
		// Initialize a quad primitive
		setPolyF4( pol4 );
		
		// Set the projected vertices to the primitive
		gte_stsxy0( &pol4->x0 );
		gte_stsxy1( &pol4->x1 );
		gte_stsxy2( &pol4->x2 );
		
		// Compute the last vertex and set the result
		gte_ldv0( obj->vertex_data[obj->vertex_indices[i].v0]);
		gte_rtps();
		gte_stsxy( &pol4->x3 );
		
		// Load primitive color even though gte_ncs() doesn't use it.
		// This is so the GTE will output a color result with the
		// correct primitive code.
		gte_ldrgb( &pol4->r0 );
		
		// Load the face normal
		gte_ldv0( obj->normal_data[obj->normal_indices[i]] );
		
		// Normal Color Single
		gte_ncs();
		
		// Store result to the primitive
		gte_strgb( &pol4->r0 );
		
		gte_avsz4();
		gte_stotz( &p );
		
		// Sort primitive to the ordering table
		addPrim( db[db_active].ot+(p>>2), pol4 );
		
		// Advance to make another primitive
		pol4++;
		
	}
	
	// Update nextpri
	db_nextpri = (char*)pol4;
	
	// Restore matrix
	PopMatrix();
}