#include <sys/types.h>
#include <stdio.h>
#include <psxgpu.h>
#include <psxgte.h>
#include <psxpad.h>
#include <psxapi.h>
#include <psxetc.h>
#include <inline_c.h>

#include "options.h"

// ---- Structs for rendering ----
typedef struct {
    DISPENV disp;
    DRAWENV draw;
    u_long ot[OT_LEN];
    char p[PACKET_LEN];
} DB;

typedef struct {
    short v0,v1,v2,v3;
} INDEX;

typedef struct {
    VECTOR pos;
    SVECTOR rot;
    TIM_IMAGE tim;
    int faces_num;
    int texture_size;
    int brighness;
    SVECTOR *vertex_data;
    SVECTOR *normal_data;
    SVECTOR *uv_data;
    INDEX *vertex_indices;
    INDEX *uv_indices;
    int *normal_indices;
} OBJECT;

void initDisplay();

void begin();
void end();

void sortObject(OBJECT* obj);