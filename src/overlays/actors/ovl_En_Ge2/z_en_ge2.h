#ifndef Z_EN_GE2_H
#define Z_EN_GE2_H

#include "global.h"
#include "z64snap.h"
#include "objects/object_gla/object_gla.h"

struct EnGe2;

typedef void (*EnGe2ActionFunc)(struct EnGe2*, PlayState*);

#define GERUDO_PURPLE_GET_EXIT(thisx) (((thisx)->params) & 0x1F) //!< Exit to send Player to when caught
#define GERUDO_PURPLE_GET_TYPE(thisx) (((thisx)->params & 0xE0) >> 5)
#define GERUDO_PURPLE_GET_PATH(thisx) ((((thisx)->params) & 0xFC00) >> 10)

typedef struct EnGe2 {
    /* 0x000 */ PictoActor picto;
    /* 0x148 */ ColliderCylinder collider;
    /* 0x194 */ SkelAnime skelAnime;
    /* 0x1D8 */ Vec3s jointTable[22];
    /* 0x25C */ Vec3s morphTable[22];
    /* 0x2E0 */ s16 eyeIndex;
    /* 0x2E2 */ s16 blinkTimer;
    /* 0x2E4 */ Vec3s headRot;
    /* 0x2E8 */ Vec3s unk2EA; // unused
    /* 0x2F0 */ Path *path;
    /* 0x2F4 */ s32 curPointIndex;
    /* 0x2F8 */ u16 stateFlags;
    /* 0x2FA */ s16 yawTarget; //!< used when Player detected to fix the yaw to turn to
    /* 0x2FC */ f32 verticalDetectRange; //!< vertical range to look for the player within
    /* 0x300 */ u8 timer;
    /* 0x301 */ u8 detectedStatus;
    /* 0x302 */ s16 csAction;
    /* 0x304 */ s16 unk304; // unused
    /* 0x306 */ s16 screamTimer;
    /* 0x308 */ EnGe2ActionFunc actionFunc;
} EnGe2; // size = 0x30C

extern const ActorInit En_Ge2_InitVars;

#endif // Z_EN_GE2_H
