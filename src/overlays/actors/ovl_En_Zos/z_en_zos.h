#ifndef _Z_EN_ZOS_H_
#define _Z_EN_ZOS_H_

#include <global.h>

struct EnZos;

typedef struct EnZos {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x180];
} EnZos; // size = 0x2C4

extern const ActorInit En_Zos_InitVars;

#endif
