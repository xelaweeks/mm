#ifndef _Z_EN_LOOK_NUTS_H_
#define _Z_EN_LOOK_NUTS_H_

#include <global.h>

struct EnLookNuts;

typedef struct EnLookNuts {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x14C];
} EnLookNuts; // size = 0x290

extern const ActorInit En_Look_Nuts_InitVars;

#endif
