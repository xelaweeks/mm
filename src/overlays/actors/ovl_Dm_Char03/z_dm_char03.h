#ifndef _Z_DM_CHAR03_H_
#define _Z_DM_CHAR03_H_

#include <global.h>

struct DmChar03;

typedef struct DmChar03 {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x58];
} DmChar03; // size = 0x19C

extern const ActorInit Dm_Char03_InitVars;

#endif
