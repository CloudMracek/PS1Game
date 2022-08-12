#include <psxgte.h>
#include "../display.h"

int floor_num_faces = 1;

SVECTOR floor_verts[] = {
  {-742,-742,0},
  {742,-742,0},
  {-742,742,0},
  {742,742,0}
};

SVECTOR floor_norms[] = {
  {0.0,-0.0,-1.0}
};

INDEX floor_vertex_indices[] = {
  {0,1,3,2}
};

INDEX floor_uv_indices[] = {
  {0,1,2,3}
};

int floor_normal_indices[] = {
2};

SVECTOR floor_uv[] = {
  {0,0},
  {127,0},
  {127,127},
  {0,127}
};

