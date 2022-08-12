#include <psxgpu.h>
#include <psxgte.h>
#include <sys/types.h>

#include "display.h"
#include "textures.h"

OBJECT obj1;
OBJECT fountain;
OBJECT floor_obj;

extern int cube_num_faces;

extern u_long bandwidth_face[];
TIM_IMAGE tim;

extern SVECTOR cube_verts[];
extern SVECTOR cube_norms[];
extern SVECTOR cube_uv[];

extern INDEX cube_vertex_indices[];
extern int cube_normal_indices[];
extern INDEX cube_uv_indices[];

extern int floor_num_faces;

extern u_long cobble[];
TIM_IMAGE floor_tim;

extern SVECTOR floor_verts[];
extern SVECTOR floor_norms[];
extern SVECTOR floor_uv[];

extern INDEX floor_vertex_indices[];
extern int floor_normal_indices[];
extern INDEX floor_uv_indices[];

extern int fountain_num_faces;

extern u_long fountain_texture[];
TIM_IMAGE fountain_tim;

extern SVECTOR fountain_verts[];
extern SVECTOR fountain_norms[];
extern SVECTOR fountain_uv[];

extern INDEX fountain_vertex_indices[];
extern int fountain_normal_indices[];
extern INDEX fountain_uv_indices[];


int main() {

  initDisplay();

  loadTexture(bandwidth_face, &tim);
  loadTexture(cobble, &floor_tim);
  loadTexture(fountain_texture, &fountain_tim);

  VECTOR floor_pos = {0, 0, 400};
  SVECTOR floor_rot = {-1024, 0, 0};

  SVECTOR rot = {0, 0, 0};
  VECTOR pos = {0,-500,400};

  SVECTOR fountain_rot = {1024, 0, 0};
  VECTOR fountain_pos = {0,-20,400};

  obj1.pos = pos;
  obj1.rot = rot;

  obj1.faces_num = cube_num_faces;
  obj1.tim = tim;
  obj1.texture_size = 128;
  obj1.brighness = 128;

  obj1.vertex_data = cube_verts;
  obj1.normal_data = cube_norms;
  obj1.uv_data = cube_uv;

  obj1.vertex_indices = cube_vertex_indices;
  obj1.normal_indices = cube_normal_indices;
  obj1.uv_indices = cube_uv_indices;

  fountain.pos = fountain_pos;
  fountain.rot = fountain_rot;

  fountain.faces_num = fountain_num_faces;
  fountain.tim = fountain_tim;
  fountain.texture_size = 128;
  fountain.brighness = 100;

  fountain.vertex_data = fountain_verts;
  fountain.normal_data = fountain_norms;
  fountain.uv_data = fountain_uv;

  fountain.vertex_indices = fountain_vertex_indices;
  fountain.normal_indices = fountain_normal_indices;
  fountain.uv_indices = fountain_uv_indices;

  floor_obj.pos = floor_pos;
  floor_obj.rot = floor_rot;

  floor_obj.faces_num = floor_num_faces;
  floor_obj.tim = floor_tim;
  floor_obj.texture_size = 256;
  floor_obj.brighness = 128;

  floor_obj.vertex_data = floor_verts;
  floor_obj.normal_data = floor_norms;
  floor_obj.uv_data = floor_uv;

  floor_obj.vertex_indices = floor_vertex_indices;
  floor_obj.normal_indices = floor_normal_indices;
  floor_obj.uv_indices = floor_uv_indices;

  int i = 0;

  while (1) {
    begin();
    sortObject(&floor_obj);
    sortObject(&obj1);
    sortObject(&fountain);
    end();

    rot.vx = i;
    rot.vy = i;
    obj1.rot = rot;

    if (i > 4096) {
      i = 0;
    }
    i = i + 10;
  }
}