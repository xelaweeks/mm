#ifndef _Z_EN_M_FIRE1_H_
#define _Z_EN_M_FIRE1_H_

#include <global.h>

struct EnMFire1;

typedef struct EnMFire1 {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x50];
} EnMFire1; // size = 0x194

extern const ActorInit En_M_Fire1_InitVars;

#endif
