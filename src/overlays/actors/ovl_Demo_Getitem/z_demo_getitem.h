#ifndef Z_DEMO_GETITEM_H
#define Z_DEMO_GETITEM_H

#include "global.h"

struct DemoGetitem;

typedef void (*DemoGetitemActionFunc)(struct DemoGetitem*, PlayState*);

typedef struct DemoGetitem {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x8];
    /* 0x14C */ DemoGetitemActionFunc actionFunc;
} DemoGetitem; // size = 0x150

extern const ActorInit Demo_Getitem_InitVars;

#endif // Z_DEMO_GETITEM_H
