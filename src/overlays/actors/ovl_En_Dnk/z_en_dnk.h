#ifndef _Z_EN_DNK_H_
#define _Z_EN_DNK_H_

#include <global.h>

struct EnDnk;

typedef struct EnDnk {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x160];
} EnDnk; // size = 0x2A4

extern const ActorInit En_Dnk_InitVars;

#endif
