#ifndef _Z_EN_ENCOUNT2_H_
#define _Z_EN_ENCOUNT2_H_

#include <global.h>

struct EnEncount2;

typedef struct EnEncount2 {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ char unk_0144[0x292C];
} EnEncount2; // size = 0x2A70

extern const ActorInit En_Encount2_InitVars;

#endif
