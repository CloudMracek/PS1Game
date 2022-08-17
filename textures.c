#include <stdint.h>
#include <psxgpu.h>
#include "textures.h"

void loadTexture(const uint32_t *tim, TIM_IMAGE *tparam) {
    GetTimInfo(tim, tparam);
	
	LoadImage(tparam->prect, tparam->paddr);
	DrawSync(0);

	if (tparam->mode & 8) {
		LoadImage(tparam->crect, tparam->caddr);
		DrawSync(0);
	}
}
