#ifndef _Z_EN_JA_H_
#define _Z_EN_JA_H_

#include <global.h>

struct EnJa;

typedef struct EnJa {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x234];
} EnJa; // size = 0x378

extern const ActorInit En_Ja_InitVars;

#endif
