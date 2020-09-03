#ifndef _Z_DM_CHAR07_H_
#define _Z_DM_CHAR07_H_

#include <global.h>

struct DmChar07;

typedef struct DmChar07 {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x178];
} DmChar07; // size = 0x2BC

extern const ActorInit Dm_Char07_InitVars;

#endif
