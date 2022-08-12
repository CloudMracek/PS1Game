#include <psxgpu.h>
#include <psxgte.h>
#include <sys/types.h>

#include "display.h"
#include "textures.h"

OBJECT obj1;
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


int main() {

  initDisplay();

  loadTexture(bandwidth_face, &tim);
  loadTexture(cobble, &floor_tim);

  VECTOR floor_pos = {0, 0, 400};
  SVECTOR floor_rot = {-1024, 0, 0};

  SVECTOR rot = {0, 0, 0};
  VECTOR pos = {0,-200,400};

  obj1.pos = pos;
  obj1.rot = rot;

  obj1.faces_num = cube_num_faces;
  obj1.tim = tim;

  obj1.vertex_data = cube_verts;
  obj1.normal_data = cube_norms;
  obj1.uv_data = cube_uv;

  obj1.vertex_indices = cube_vertex_indices;
  obj1.normal_indices = cube_normal_indices;
  obj1.uv_indices = cube_uv_indices;

  floor_obj.pos = floor_pos;
  floor_obj.rot = floor_rot;

  floor_obj.faces_num = floor_num_faces;
  floor_obj.tim = floor_tim;

  floor_obj.vertex_data = floor_verts;
  floor_obj.normal_data = floor_norms;
  floor_obj.uv_data = floor_uv;

  floor_obj.vertex_indices = floor_vertex_indices;
  floor_obj.normal_indices = floor_normal_indices;
  floor_obj.uv_indices = floor_uv_indices;

  int i = 0;

  while (1) {
    begin();
    sortObject(&obj1);
    sortObject(&floor_obj);
    end();

    rot.vx = i;
    rot.vy = i;
    //obj1.rot = rot;

    if (i > 4096) {
      i = 0;
    }
    i = i + 10;
  }
}