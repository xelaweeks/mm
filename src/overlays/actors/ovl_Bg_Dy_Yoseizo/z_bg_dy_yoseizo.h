#ifndef Z_BG_DY_YOSEIZO_H
#define Z_BG_DY_YOSEIZO_H

#include "global.h"

struct BgDyYoseizo;

typedef void (*BgDyYoseizoActionFunc)(struct BgDyYoseizo* this, GlobalContext* globalCtx);

typedef struct BgDyYoseizo {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ BgDyYoseizoActionFunc actionFunc;
    /* 0x0148 */ char unk_144[0x33BC];
} BgDyYoseizo; // size = 0x3504

extern const ActorInit Bg_Dy_Yoseizo_InitVars;

#endif // Z_BG_DY_YOSEIZO_H
