#ifndef Z_EN_KAIZOKU_H
#define Z_EN_KAIZOKU_H

#include "global.h"
#include "z64snap.h"
#include "objects/object_kz/object_kz.h"

#define KAIZOKU_GET_EXIT_INDEX(thisx) ((thisx)->params & 0x3F)
#define KAIZOKU_GET_SWITCHFLAG(thisx) (((thisx)->params >> 6) & 0x7F)

struct EnKaizoku;

typedef void (*EnKaizokuActionFunc)(struct EnKaizoku*, PlayState*);

typedef enum EnKaizokuAnimation {
    /*  0 */ EN_KAIZOKU_ANIM_0,
    /*  1 */ EN_KAIZOKU_ANIM_1,
    /*  2 */ EN_KAIZOKU_ANIM_2,
    /*  3 */ EN_KAIZOKU_ANIM_3,
    /*  4 */ EN_KAIZOKU_ANIM_4,
    /*  5 */ EN_KAIZOKU_ANIM_5,
    /*  6 */ EN_KAIZOKU_ANIM_6,
    /*  7 */ EN_KAIZOKU_ANIM_7,
    /*  8 */ EN_KAIZOKU_ANIM_8,
    /*  9 */ EN_KAIZOKU_ANIM_9,
    /* 10 */ EN_KAIZOKU_ANIM_10,
    /* 11 */ EN_KAIZOKU_ANIM_11,
    /* 12 */ EN_KAIZOKU_ANIM_12,
    /* 13 */ EN_KAIZOKU_ANIM_13,
    /* 14 */ EN_KAIZOKU_ANIM_14,
    /* 15 */ EN_KAIZOKU_ANIM_15,
    /* 16 */ EN_KAIZOKU_ANIM_16,
    /* 17 */ EN_KAIZOKU_ANIM_17,
    /* 18 */ EN_KAIZOKU_ANIM_18,
    /* 19 */ EN_KAIZOKU_ANIM_MAX
} EnKaizokuAnimation;

typedef struct EnKaizoku {
    /* 0x000 */ PictoActor picto;
    /* 0x148 */ SkelAnime skelAnime;
    /* 0x18C */ Vec3s jointTable[KAIZOKU_LIMB_MAX];
    /* 0x21C */ Vec3s morphTable[KAIZOKU_LIMB_MAX];
    /* 0x2AC */ EnKaizokuActionFunc actionFunc;
    /* 0x2B0 */ s16 unk_2B0;
    /* 0x2B2 */ s16 unk_2B2;
    /* 0x2B4 */ s16 unk_2B4;
    /* 0x2B6 */ s16 unk_2B6;
    /* 0x2B8 */ s16 unk_2B8;
    /* 0x2BA */ s16 drawDmgEffType;
    /* 0x2BC */ s16 switchFlag;
    /* 0x2BE */ s16 unk_2BE;
    /* 0x2C0 */ f32 drawDmgEffScale;
    /* 0x2C4 */ f32 drawDmgEffFrozenSteamScale;
    /* 0x2C8 */ s16 unk_2C8;
    /* 0x2CA */ s16 unk_2CA;
    /* 0x2CC */ s16 eyeIndex;
    /* 0x2CE */ s16 blinkTimer;
    /* 0x2D0 */ s16 unk_2D0;
    /* 0x2D2 */ s16 unk_2D2;
    /* 0x2D4 */ s16 exitIndex;
    /* 0x2D6 */ s16 unk_2D6;
    /* 0x2D8 */ u8 unk_2D8;
    /* 0x2D9 */ u8 unk_2D9;
    /* 0x2DC */ f32 frameCount;
    /* 0x2E0 */ f32 unk_2E0;
    /* 0x2E4 */ EnKaizokuAnimation animIndex;
    /* 0x2E8 */ s32 bodyPartsPosIndex;
    /* 0x2EC */ s32 unk_2EC;
    /* 0x2F0 */ f32 unk_2F0;
    /* 0x2F4 */ s16 unk_2F4;
    /* 0x2F8 */ Vec3f unk_2F8;
    /* 0x304 */ Vec3f unk_304;
    /* 0x310 */ Vec3f bodyPartsPos[15];
    /* 0x3C4 */ Vec3f unk_3C4;
    /* 0x3D0 */ s32 unk_3D0;
    /* 0x3D4 */ ColliderCylinder unk_3D4;
    /* 0x420 */ ColliderQuad unk_420;
    /* 0x4A0 */ UNK_TYPE1 pad_4A0[0xD8];
    /* 0x578 */ s16 unk_578;
    /* 0x57A */ s16 unk_57A;
    /* 0x57C */ s16 unk_57C;
    /* 0x580 */ Vec3f unk_580;
    /* 0x58C */ Vec3f unk_58C;
    /* 0x598 */ s32 unk_598;
    /* 0x59C */ s16 unk_59C;
    /* 0x59E */ s16 subCamId;
    /* 0x5A0 */ s16 unk_5A0;
    /* 0x5A2 */ s16 unk_5A2;
    /* 0x5A4 */ Vec3f subCamEye;
    /* 0x5B0 */ Vec3f subCamAt;
    /* 0x5BC */ Vec3f subCamUp;
    /* 0x5C8 */ Vec3f unk_5C8;
    /* 0x5D4 */ Vec3f unk_5D4;
    /* 0x5E0 */ f32 unk_5E0;
    /* 0x5E4 */ f32 unk_5E4;
    /* 0x5E8 */ f32 unk_5E8;
    /* 0x5EC */ f32 unk_5EC;
} EnKaizoku; // size = 0x5F0

#endif // Z_EN_KAIZOKU_H
