#include <psxgpu.h>
#include <psxgte.h>
#include <sys/types.h>

#include "display.h"
#include "textures.h"

OBJECT obj1;

extern int cube_num_faces;

extern u_long bandwidth_face[];
TIM_IMAGE tim;

extern SVECTOR cube_verts[];
extern SVECTOR cube_norms[];
extern SVECTOR cube_uv[];

extern INDEX cube_vertex_indices[];
extern int cube_normal_indices[];
extern INDEX cube_uv_indices[];

int main() {

  initDisplay();

  GetTimInfo(bandwidth_face, &tim);

  LoadImage(tim.prect, tim.paddr);
  DrawSync(0);

  LoadImage(tim.crect, tim.caddr);
  DrawSync(0);

  VECTOR pos = {0, 0, 400};
  SVECTOR rot = {0, 0, 0};

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

  int i = 0;

  while (1) {
    begin();
    sortObject(&obj1);
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