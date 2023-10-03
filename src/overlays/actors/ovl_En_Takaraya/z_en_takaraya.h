#ifndef Z_EN_TAKARAYA_H
#define Z_EN_TAKARAYA_H

#include "global.h"
#include "objects/object_bg/object_bg.h"

struct EnTakaraya;

typedef void (*EnTakarayaActionFunc)(struct EnTakaraya*, PlayState*);

#define EN_TAKARAYA_GET_SWITCH_FLAG(thisx) (u8)((thisx)->params >> 0x8)
#define TAKARAYA_GET_TREASURE_FLAG(this) (1 << (this)->actor.params)

typedef struct EnTakaraya {
    /* 0x000 */ Actor actor;
    /* 0x144 */ SkelAnime skelAnime;
    /* 0x188 */ Vec3s jointTable[OBJECT_BG_1_LIMB_MAX];
    /* 0x218 */ Vec3s morphTable[OBJECT_BG_1_LIMB_MAX];
    /* 0x2A8 */ EnTakarayaActionFunc actionFunc;
    /* 0x2AC */ u8 eyeTexIndex;
    /* 0x2AD */ u8 unk2AD;
    /* 0x2AE */ s16 timer;
    /* 0x2B0 */ s16 formSwitchFlag;
    /* 0x2B2 */ s16 switchFlag;
    /* 0x2B4 */ Vec3s headRot;
} EnTakaraya; // size = 0x2BC

#endif // Z_EN_TAKARAYA_H
