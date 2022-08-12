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

POLY_FT4 *pol4;

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

  setVector(&cam_pos, 0, ONE * -100, 0);
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
  int i, p;
  POLY_FT4 *pol4;

  MATRIX omtx, lmtx;

  RotMatrix(&obj->rot, &omtx);
  TransMatrix(&omtx, &obj->pos);

  MulMatrix0(&light_mtx, &omtx, &lmtx);

  gte_SetLightMatrix(&lmtx);

  CompMatrixLV(&mtx, &omtx, &omtx);

  PushMatrix();

  gte_SetRotMatrix(&omtx);
  gte_SetTransMatrix(&omtx);

  pol4 = (POLY_FT4 *)db_nextpri;

  for (i = 0; i < obj->faces_num; i++) {

    
    gte_ldv3(&obj->vertex_data[obj->vertex_indices[i].v0],
             &obj->vertex_data[obj->vertex_indices[i].v1],
             &obj->vertex_data[obj->vertex_indices[i].v2]);

    gte_rtpt();
    gte_nclip();
    gte_stopz(&p);

    if (p < 0)
      continue;

    gte_avsz3();
    gte_stotz(&p);

    if (((p >> 2) <= 0) || ((p >> 2) >= OT_LEN))
      continue;

    setPolyFT4(pol4);

    gte_stsxy0(&pol4->x0);
    gte_stsxy1(&pol4->x1);
    gte_stsxy2(&pol4->x2);

    gte_ldv0(&obj->vertex_data[obj->vertex_indices[i].v3]);
    gte_rtps();
    gte_stsxy(&pol4->x3);

    gte_ldrgb(&pol4->r0);
    gte_ldv0(&obj->normal_data[obj->normal_indices[i]]);
    gte_ncs();
    gte_strgb(&pol4->r0);

    pol4->tpage = getTPage(obj->tim.mode, 0, obj->tim.prect->x, obj->tim.prect->y);
    setClut(pol4, obj->tim.crect->x, obj->tim.crect->y);
    setUV4(pol4, 
            128 - obj->uv_data[obj->uv_indices[i].v0].vx, obj->uv_data[obj->uv_indices[i].v0].vy,
            128 - obj->uv_data[obj->uv_indices[i].v1].vx, obj->uv_data[obj->uv_indices[i].v1].vy,
            128 - obj->uv_data[obj->uv_indices[i].v2].vx, obj->uv_data[obj->uv_indices[i].v2].vy,
            128 - obj->uv_data[obj->uv_indices[i].v3].vx, obj->uv_data[obj->uv_indices[i].v3].vy
            );

    gte_avsz4();
    gte_stotz(&p);
    addPrim(db[db_active].ot + (p >> 2), pol4);

    pol4++;
  }

  db_nextpri = (char *)pol4;
  PopMatrix();
}