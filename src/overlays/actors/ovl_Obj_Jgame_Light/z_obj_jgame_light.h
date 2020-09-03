#ifndef _Z_OBJ_JGAME_LIGHT_H_
#define _Z_OBJ_JGAME_LIGHT_H_

#include <global.h>

struct ObjJgameLight;

typedef struct ObjJgameLight {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x78];
} ObjJgameLight; // size = 0x1BC

extern const ActorInit Obj_Jgame_Light_InitVars;

#endif
