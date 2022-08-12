#include "display.h"

// Dual buffer vars
DB db[2];
int db_active = 0;
char *db_nextpri;
RECT screen_clip;

// Lighting
MATRIX color_mtx = {
    ONE, 0, 0, // Red
    ONE,   0, 0, // Green
    ONE, 0, 0  // Blue
};

MATRIX light_mtx = {
    /* X,  Y,  Z */
    0, 0, -2048, 0, 0, 0, 0, 0, 0};

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

char pad_buff[2][34];
PADTYPE *pad;

void pollInput() {
  pad = (PADTYPE *)&pad_buff[0][0];
  // Parse controller input

  // Divide out fractions of camera rotation
  trot.vx = cam_rot.vx >> 12;
  trot.vy = cam_rot.vy >> 12;
  trot.vz = cam_rot.vz >> 12;

  FntPrint(-1, "X=%d Y=%d Z=%d\n", cam_pos.vx >> 12, cam_pos.vy >> 12,
           cam_pos.vz >> 12);
  FntPrint(-1, "RX=%d RY=%d\n", cam_rot.vx >> 12, cam_rot.vy >> 12);

  if (pad->stat == 0) {

    // For digital pad, dual-analog and dual-shock
    if ((pad->type == 0x4) || (pad->type == 0x5) || (pad->type == 0x7)) {

      // The button status bits are inverted,
      // so 0 means pressed in this case

      // Look controls
      if (!(pad->btn & PAD_UP)) {

        // Look up
        cam_rot.vx -= ONE * 8;

      } else if (!(pad->btn & PAD_DOWN)) {

        // Look down
        cam_rot.vx += ONE * 8;
      }

      if (!(pad->btn & PAD_LEFT)) {

        // Look left
        cam_rot.vy += ONE * 8;

      } else if (!(pad->btn & PAD_RIGHT)) {

        // Look right
        cam_rot.vy -= ONE * 8;
      }

      // Movement controls
      if (!(pad->btn & PAD_TRIANGLE)) {

        // Move forward
        cam_pos.vx -= ((isin(trot.vy) * icos(trot.vx)) >> 12) << 2;
        cam_pos.vy += isin(trot.vx) << 2;
        cam_pos.vz += ((icos(trot.vy) * icos(trot.vx)) >> 12) << 2;

      } else if (!(pad->btn & PAD_CROSS)) {

        // Move backward
        cam_pos.vx += ((isin(trot.vy) * icos(trot.vx)) >> 12) << 2;
        cam_pos.vy -= isin(trot.vx) << 2;
        cam_pos.vz -= ((icos(trot.vy) * icos(trot.vx)) >> 12) << 2;
      }

      if (!(pad->btn & PAD_SQUARE)) {

        // Slide left
        cam_pos.vx -= icos(trot.vy) << 2;
        cam_pos.vz -= isin(trot.vy) << 2;

      } else if (!(pad->btn & PAD_CIRCLE)) {

        // Slide right
        cam_pos.vx += icos(trot.vy) << 2;
        cam_pos.vz += isin(trot.vy) << 2;
      }

      if (!(pad->btn & PAD_R1)) {

        // Slide up
        cam_pos.vx -= ((isin(trot.vy) * isin(trot.vx)) >> 12) << 2;
        cam_pos.vy -= icos(trot.vx) << 2;
        cam_pos.vz += ((icos(trot.vy) * isin(trot.vx)) >> 12) << 2;
      }

      if (!(pad->btn & PAD_R2)) {

        // Slide down
        cam_pos.vx += ((isin(trot.vy) * isin(trot.vx)) >> 12) << 2;
        cam_pos.vy += icos(trot.vx) << 2;
        cam_pos.vz -= ((icos(trot.vy) * isin(trot.vx)) >> 12) << 2;
      }
    }

    // For dual-analog and dual-shock (analog input)
    if ((pad->type == 0x5) || (pad->type == 0x7)) {

      // Moving forwards and backwards
      if (((pad->ls_y - 128) < -16) || ((pad->ls_y - 128) > 16)) {

        cam_pos.vx +=
            (((isin(trot.vy) * icos(trot.vx)) >> 12) * (pad->ls_y - 128)) >> 5;
        cam_pos.vy -= (isin(trot.vx) * (pad->ls_y - 128)) >> 5;
        cam_pos.vz -=
            (((icos(trot.vy) * icos(trot.vx)) >> 12) * (pad->ls_y - 128)) >> 5;
      }

      // Strafing left and right
      if (((pad->ls_x - 128) < -16) || ((pad->ls_x - 128) > 16)) {
        cam_pos.vx += (icos(trot.vy) * (pad->ls_x - 128)) >> 5;
        cam_pos.vz += (isin(trot.vy) * (pad->ls_x - 128)) >> 5;
      }

      // Look up and down
      if (((pad->rs_y - 128) < -16) || ((pad->rs_y - 128) > 16)) {
        cam_rot.vx += (pad->rs_y - 128) << 9;
      }

      // Look left and right
      if (((pad->rs_x - 128) < -16) || ((pad->rs_x - 128) > 16)) {
        cam_rot.vy -= (pad->rs_x - 128) << 9;
      }
    }
  }
}

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

  InitPAD(&pad_buff[0][0], 34, &pad_buff[1][0], 34);
  StartPAD();
  ChangeClearPAD(0);
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
  pollInput();
}

void sortObject(OBJECT *obj) {
  int i, p;
  POLY_FT4 *pol4;

  MATRIX omtx, lmtx;

  RotMatrix(&obj->rot, &omtx);
  TransMatrix(&omtx, &obj->pos);

  MulMatrix0(&light_mtx, &omtx, &lmtx);

  //gte_SetLightMatrix(&lmtx);

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

    /*if (p < 0)
      continue;
*/
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

    pol4->tpage =
        getTPage(obj->tim.mode, 0, obj->tim.prect->x, obj->tim.prect->y);
    setClut(pol4, obj->tim.crect->x, obj->tim.crect->y);
    setUV4(pol4, 127 - obj->uv_data[obj->uv_indices[i].v0].vx,
           obj->uv_data[obj->uv_indices[i].v0].vy,
           127 - obj->uv_data[obj->uv_indices[i].v1].vx,
           obj->uv_data[obj->uv_indices[i].v1].vy,
           127 - obj->uv_data[obj->uv_indices[i].v2].vx,
           obj->uv_data[obj->uv_indices[i].v2].vy,
           127 - obj->uv_data[obj->uv_indices[i].v3].vx,
           obj->uv_data[obj->uv_indices[i].v3].vy);
    setRGB0( pol4, 128, 128, 128 );
    gte_avsz4();
    gte_stotz(&p);
    addPrim(db[db_active].ot + (p >> 2), pol4);

    pol4++;
  }

  db_nextpri = (char *)pol4;
  PopMatrix();
}