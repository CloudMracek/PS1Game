#include "textures.h"

void loadTexture(u_long *tim, TIM_IMAGE *tparam) {
    GetTimInfo( tim, tparam);
	
	LoadImage(tparam->prect, tparam->paddr);
	DrawSync(0);
	
	LoadImage(tparam->crect, tparam->caddr);
	DrawSync(0);
}