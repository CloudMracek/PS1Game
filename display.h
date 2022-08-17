#pragma once
#include <stdint.h>
#include <psxgpu.h>
#include <psxgte.h>
#include "options.h"

// ---- Structs for rendering ----
typedef struct {
    DISPENV disp;
    DRAWENV draw;
    uint32_t *ot[OT_LEN];
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

void initDisplay(void);

void begin(void);
void end(void);

void sortObject(OBJECT *obj);
