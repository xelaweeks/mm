#ifndef Z_EN_ONPUMAN_H
#define Z_EN_ONPUMAN_H

#include "global.h"

struct EnOnpuman;

typedef void (*EnOnpumanActionFunc)(struct EnOnpuman*, PlayState*);

typedef struct EnOnpuman {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x164];
    /* 0x2A8 */ EnOnpumanActionFunc actionFunc;
} EnOnpuman; // size = 0x2AC

extern const ActorInit En_Onpuman_InitVars;

#endif // Z_EN_ONPUMAN_H
