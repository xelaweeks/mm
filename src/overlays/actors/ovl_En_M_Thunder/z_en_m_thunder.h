#ifndef _Z_EN_M_THUNDER_H_
#define _Z_EN_M_THUNDER_H_

#include <global.h>

struct EnMThunder;

typedef struct EnMThunder {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x80];
} EnMThunder; // size = 0x1C4

extern const ActorInit En_M_Thunder_InitVars;

#endif
