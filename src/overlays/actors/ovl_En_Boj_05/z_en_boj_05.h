#ifndef _Z_EN_BOJ_05_H_
#define _Z_EN_BOJ_05_H_

#include <global.h>

struct EnBoj05;

typedef struct EnBoj05 {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x4D8];
} EnBoj05; // size = 0x61C

extern const ActorInit En_Boj_05_InitVars;

#endif
