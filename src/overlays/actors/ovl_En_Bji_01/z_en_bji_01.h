#ifndef _Z_EN_BJI_01_H_
#define _Z_EN_BJI_01_H_

#include <global.h>

struct EnBji01;

typedef struct EnBji01 {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x170];
} EnBji01; // size = 0x2B4

extern const ActorInit En_Bji_01_InitVars;

#endif
