#ifndef _Z_EN_BOJ_01_H_
#define _Z_EN_BOJ_01_H_

#include <global.h>

struct EnBoj01;

typedef struct EnBoj01 {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x1D0];
} EnBoj01; // size = 0x314

extern const ActorInit En_Boj_01_InitVars;

#endif
