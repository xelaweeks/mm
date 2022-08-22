#ifndef Z_EN_WIZ_H
#define Z_EN_WIZ_H

#include "global.h"
#include "objects/object_wiz/object_wiz.h"

struct EnWiz;

typedef void (*EnWizActionFunc)(struct EnWiz*, PlayState*);

typedef struct EnWiz {
    /* 0x000 */ Actor actor;
    /* 0x144 */ SkelAnime skelAnime;
    /* 0x188 */ Vec3s jointTable[WIZZROBE_LIMB_MAX];
    /* 0x200 */ Vec3s morphTable[WIZZROBE_LIMB_MAX];
    /* 0x278 */ SkelAnime skelAnime2;
    /* 0x2BC */ Vec3s jointTable2[WIZZROBE_LIMB_MAX];
    /* 0x334 */ Vec3s morphTable2[WIZZROBE_LIMB_MAX];
    /* 0x3AC */ EnWizActionFunc actionFunc;
    /* 0x3B0 */ s16 action;
    /* 0x3B2 */ s16 timer;
    /* 0x3B4 */ s16 introCutsceneTimer;
    /* 0x3B6 */ s16 unk_3B6; // fight state? 0 = first phase, 1 = second phase CS, 2 = beginning of second phase, 3 = first time in second phase where afterimages run
    /* 0x3B8 */ s16 staffFlameScroll;
    /* 0x3BA */ s16 hasActiveProjectile;
    /* 0x3BC */ s16 unk_3BC; // has visited every platform during second phase CS
    /* 0x3B4 */ char unk_3BE[2];
    /* 0x3C0 */ s16 rotationalVelocity;
    /* 0x3C2 */ s16 alpha;
    /* 0x3C4 */ s16 platformLightAlpha;
    /* 0x3C6 */ s16 targetPlatformLightAlpha;
    /* 0x3C8 */ s16 introCutsceneCameraAngle; // check the name on this one
    /* 0x3CA */ u8 unk_3CA; // Always false for phase 2. Mostly true for phase 1 except for 1 frame during disappearance
    /* 0x3CB */ u8 introCutsceneState;
    /* 0x3CC */ s32 musicStartTimer;
    /* 0x3D0 */ f32 endFrame;
    /* 0x3D4 */ f32 scale;
    /* 0x3D8 */ Vec3f staffFlamePos;
    /* 0x3E4 */ Vec3f staffFlameScale;
    /* 0x3F0 */ Vec3f staffTargetFlameScale;
    /* 0x3FC */ char unk_3FC[0x18];
    /* 0x414 */ Vec3f platformLightPos;
    /* 0x420 */ Actor* platforms[10];
    /* 0x448 */ Actor* freezard;
    /* 0x44C */ s16 animLoopCounter;
    /* 0x450 */ f32 unk_450; // set to 1.0f but never used
    /* 0x454 */ ColliderJntSph unk_454;
    /* 0x474 */ ColliderJntSphElement unk_474[10];
    /* 0x6F4 */ ColliderCylinder unk_6F4;
    /* 0x740 */ s32 unk_740; // platform count? only seems to kick in for second phase
    /* 0x744 */ s32 unk_744; // when running between platforms, it's the index of the "next" platform
    /* 0x748 */ s16 unk_748; // current platform
    /* 0x74A */ s16 unk_74A; // type?
    /* 0x74C */ s16 switchFlag;
    /* 0x74E */ s16 subCamId;
    /* 0x750 */ s16 isDead;
    /* 0x752 */ s16 drawDmgEffTimer;
    /* 0x754 */ s16 drawDmgEffType;
    /* 0x758 */ f32 drawDmgEffScale;
    /* 0x75C */ f32 drawDmgEffFrozenSteamScale;
    /* 0x760 */ Vec3f bodyPartsPos[12];
    /* 0x7F0 */ s16 bodyPartsPosIndex;
    /* 0x7F2 */ s16 unk_7F2[10];
    /* 0x806 */ s16 unk_806[10];
    /* 0x81C */ Vec3f unk_81C[10];
    /* 0x894 */ Vec3s unk_894[10];
    /* 0x8D0 */ Vec3s jointTable3[10][WIZZROBE_LIMB_MAX];
} EnWiz; // size = 0xD80

extern const ActorInit En_Wiz_InitVars;

#endif // Z_EN_WIZ_H
