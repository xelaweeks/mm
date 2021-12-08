#ifndef Z_OBJ_KZSAKU_H
#define Z_OBJ_KZSAKU_H

#include "global.h"

struct ObjKzsaku;

typedef void (*ObjKzsakuActionFunc)(struct ObjKzsaku*, GlobalContext*);

typedef struct ObjKzsaku {
    /* 0x0000 */ DynaPolyActor dyna;
    /* 0x015C */ ObjKzsakuActionFunc actionFunc;
    /* 0x0160 */ f32 unk_160;
    /* 0x0164 */ s32 switchFlag;
    /* 0x0168 */ s16 timer;
    /* 0x016A */ s16 unk_16A;
} ObjKzsaku; // size = 0x16C

extern const ActorInit Obj_Kzsaku_InitVars;

#endif // Z_OBJ_KZSAKU_H
