#ifndef _Z_EN_MK_H_
#define _Z_EN_MK_H_

#include <global.h>

struct EnMk;

typedef struct EnMk {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x140];
} EnMk; // size = 0x284

extern const ActorInit En_Mk_InitVars;

#endif
