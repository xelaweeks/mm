#ifndef _Z_EN_WIZ_FIRE_H_
#define _Z_EN_WIZ_FIRE_H_

#include <global.h>

struct EnWizFire;

typedef struct EnWizFire {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ char unk_0144[0x29B0];
} EnWizFire; // size = 0x2AF4

extern const ActorInit En_Wiz_Fire_InitVars;

#endif
