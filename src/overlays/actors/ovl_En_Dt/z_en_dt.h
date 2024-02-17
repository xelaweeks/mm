#ifndef Z_EN_DT_H
#define Z_EN_DT_H

#include "global.h"
#include "objects/object_dt/object_dt.h"

struct EnDt;

typedef void (*EnDtActionFunc)(struct EnDt*, PlayState*);

typedef struct EnDt {
    /* 0x000 */ Actor actor;
    /* 0x144 */ SkelAnime skelAnime;
    /* 0x188 */ Vec3s jointTable[OBJECT_DT_LIMB_MAX];
    /* 0x1E2 */ Vec3s morphTable[OBJECT_DT_LIMB_MAX];
    /* 0x23C */ EnDtActionFunc actionFunc;
    /* 0x240 */ s32 unk240;
    /* 0x244 */ s16 timer;
    /* 0x246 */ s16 animIndex;
    /* 0x248 */ s16 disableBlinking;
    /* 0x24A */ s16 blinkTimer;
    /* 0x24C */ s16 eyeTexIndex;
    /* 0x24E */ char pad24E[0x02];
    /* 0x250 */ f32 animEndFrame;
    /* 0x254 */ s16 unk254;
    /* 0x256 */ s16 textIdIndex;
    /* 0x258 */ s16 csIds[0x0B];
    /* 0x26E */ s16 csIdIndex;
    /* 0x270 */ s16 cutsceneState;
    /* 0x272 */ char pad272[0x02];
    /* 0x274 */ Actor* npcEnMuto;
    /* 0x278 */ Actor* npcEnBaisen;
    /* 0x27C */ Actor* targetActor;
    /* 0x280 */ s32 unk280;                 // visualStateIndex?
    /* 0x284 */ Vec3s headRotValue;
    /* 0x28A */ Vec3s headRotTarget;
    /* 0x290 */ s32 unk290;
    /* 0x294 */ ColliderCylinder collider;
} EnDt;                                             /* size = 0x2E0 */

#endif // Z_EN_DT_H
