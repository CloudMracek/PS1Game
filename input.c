#include <stdint.h>
#include <psxapi.h>
#include <psxpad.h>
#include "input.h"

uint8_t padBuffer[2][34];

void initInput(void) {
	InitPAD(padBuffer[0], 34, padBuffer[1], 34);
#ifdef USE_MEMORY_CARD
	InitCard(1);
#endif
	StartPAD();
#ifdef USE_MEMORY_CARD
	StartCard();
	_bu_init();
#endif
	ChangeClearPAD(0);
}
