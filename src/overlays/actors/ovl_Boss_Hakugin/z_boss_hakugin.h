#ifndef Z_BOSS_HAKUGIN_H
#define Z_BOSS_HAKUGIN_H

#include "global.h"
#include "objects/object_boss_hakugin/object_boss_hakugin.h"
#include "overlays/effects/ovl_Effect_Ss_Fhg_Flash/z_eff_ss_fhg_flash.h"

struct BossHakugin;

#define GOHT_SHADOW_TEX_WIDTH 64
#define GOHT_SHADOW_TEX_HEIGHT 64
#define GOHT_SHADOW_TEX_SIZE ((s32)sizeof(u8[GOHT_SHADOW_TEX_HEIGHT][GOHT_SHADOW_TEX_WIDTH]))

typedef void (*BossHakuginActionFunc)(struct BossHakugin*, PlayState*);


typedef enum GohtRockType {
    /* 0 */ GOHT_ROCK_TYPE_BOULDER,
    /* 1 */ GOHT_ROCK_TYPE_STALACTITE
} GohtRockType;

typedef struct GohtRock {
    /* 0x00 */ Vec3f pos;
    /* 0x0C */ Vec3f velocity;
    /* 0x18 */ s16 timer;
    /* 0x1A */ s16 type; // See GohtRockType
    /* 0x1C */ Vec3s rot;
    /* 0x24 */ f32 scale;
} GohtRock; // size = 0x28

#define GOHT_ROCK_COUNT 180

typedef struct GohtElectricBall {
    /* 0x00 */ Vec3f pos;
    /* 0x0C */ s16 alpha;
    /* 0x0E */ Vec3s rot;
    /* 0x14 */ ColliderTris unk_14;
    /* 0x34 */ ColliderTrisElement unk_34;
} GohtElectricBall; // size = 0x90

#define GOHT_ELECTRIC_BALL_COUNT 20

typedef struct GohtMechanicalMalfunctionEffect {
    /* 0x00 */ Vec3f pos;
    /* 0x0C */ f32 scaleXY;
    /* 0x10 */ s16 life;
    /* 0x12 */ s16 unk_12;
} GohtMechanicalMalfunctionEffect; // size = 0x14

#define GOHT_MECHANICAL_MALFUNCTION_NUM_TYPES (FHGFLASH_SHOCK_GOHT_MAX - FHGFLASH_SHOCK_GOHT_2)

typedef enum GohtBodyPart {
    /*  0 */ GOHT_BODYPART_PELVIS,
    /*  1 */ GOHT_BODYPART_THORAX,
    /*  2 */ GOHT_BODYPART_HEAD,
    /*  3 */ GOHT_BODYPART_FRONT_RIGHT_UPPER_LEG,
    /*  4 */ GOHT_BODYPART_FRONT_RIGHT_LOWER_LEG,
    /*  5 */ GOHT_BODYPART_FRONT_RIGHT_HOOF,
    /*  6 */ GOHT_BODYPART_FRONT_LEFT_UPPER_LEG,
    /*  7 */ GOHT_BODYPART_FRONT_LEFT_LOWER_LEG,
    /*  8 */ GOHT_BODYPART_FRONT_LEFT_HOOF,
    /*  9 */ GOHT_BODYPART_BACK_RIGHT_THIGH,
    /* 10 */ GOHT_BODYPART_BACK_RIGHT_SHIN,
    /* 11 */ GOHT_BODYPART_BACK_RIGHT_HOOF,
    /* 12 */ GOHT_BODYPART_BACK_LEFT_THIGH,
    /* 13 */ GOHT_BODYPART_BACK_LEFT_SHIN,
    /* 14 */ GOHT_BODYPART_BACK_LEFT_HOOF,
    /* 15 */ GOHT_BODYPART_MAX
} GohtBodyPart;

typedef enum GohtColliderBodyPart {
    /*  0 */ GOHT_COLLIDER_BODYPART_HEAD,
    /*  1 */ GOHT_COLLIDER_BODYPART_THORAX,
    /*  2 */ GOHT_COLLIDER_BODYPART_PELVIS,
    /*  3 */ GOHT_COLLIDER_BODYPART_FRONT_RIGHT_UPPER_LEG,
    /*  4 */ GOHT_COLLIDER_BODYPART_FRONT_RIGHT_LOWER_LEG,
    /*  5 */ GOHT_COLLIDER_BODYPART_FRONT_RIGHT_HOOF,
    /*  6 */ GOHT_COLLIDER_BODYPART_FRONT_LEFT_UPPER_LEG,
    /*  7 */ GOHT_COLLIDER_BODYPART_FRONT_LEFT_LOWER_LEG,
    /*  8 */ GOHT_COLLIDER_BODYPART_FRONT_LEFT_HOOF,
    /*  9 */ GOHT_COLLIDER_BODYPART_BACK_RIGHT_THIGH,
    /* 10 */ GOHT_COLLIDER_BODYPART_BACK_RIGHT_SHIN,
    /* 11 */ GOHT_COLLIDER_BODYPART_BACK_RIGHT_PASTERN,
    /* 12 */ GOHT_COLLIDER_BODYPART_BACK_RIGHT_HOOF,
    /* 13 */ GOHT_COLLIDER_BODYPART_BACK_LEFT_THIGH,
    /* 14 */ GOHT_COLLIDER_BODYPART_BACK_LEFT_SHIN,
    /* 15 */ GOHT_COLLIDER_BODYPART_BACK_LEFT_PASTERN,
    /* 16 */ GOHT_COLLIDER_BODYPART_BACK_LEFT_HOOF,
    // TODO: Figure out which is which
    /* 17 */ GOHT_COLLIDER_BODYPART_HORN1,
    /* 18 */ GOHT_COLLIDER_BODYPART_HORN2,
    /* 19 */ GOHT_COLLIDER_BODYPART_MAX
} GohtColliderBodyPart;

typedef struct BossHakugin {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ SkelAnime skelAnime;
    /* 0x0188 */ BossHakuginActionFunc actionFunc;
    /* 0x018C */ u8 unk_018C;
    /* 0x018D */ u8 unk_018D;
    /* 0x018E */ u8 unk_018E;
    /* 0x018F */ u8 unk_018F;
    /* 0x0190 */ u8 blockMechanicalMalfunctionEffects; // boolean?
    /* 0x0191 */ u8 mechanicalMalfunctionBodyPartIndex; // See GohtBodyPart
    /* 0x0192 */ u8 unk_0192; // See `GohtUnk192`
    /* 0x0193 */ u8 iceAlpha;
    /* 0x0194 */ u8 unk_0194;
    /* 0x0194 */ u8 unk_0195;
    /* 0x0196 */ u8 drawDmgEffType;
    /* 0x0198 */ s16 unk_0198;
    /* 0x019A */ s16 unk_019A;
    /* 0x019C */ s16 unk_019C;
    /* 0x019E */ s16 unk_019E;
    /* 0x01A0 */ s16 unk_01A0;
    /* 0x01A2 */ s16 unk_01A2;
    /* 0x01A4 */ s16 unk_01A4;
    /* 0x01A6 */ s16 unk_01A6;
    /* 0x01A8 */ s16 unk_01A8; // Counter of some kind?
    /* 0x01AA */ s16 unk_01AA;
    /* 0x01AC */ s16 subCamId;
    /* 0x01AE */ s16 unk_01AE;
    /* 0x01B0 */ u32 unk_01B0;
    /* 0x01B4 */ s32 unk_01B4;
    /* 0x01B8 */ f32 unk_01B8;
    /* 0x01BC */ f32 unk_01BC;
    /* 0x01C0 */ f32 unk_01C0;
    /* 0x01C4 */ f32 unk_01C4;
    /* 0x01C8 */ f32 unk_01C8;
    /* 0x01CC */ f32 unk_01CC;
    /* 0x01D0 */ f32 unk_01D0;
    /* 0x01D4 */ f32 unk_01D4;
    /* 0x01D8 */ UNK_TYPE1 unk_01D8[0x4]; // probably unused float
    /* 0x01DC */ f32 drawDmgEffScale;
    /* 0x01E0 */ f32 drawDmgEffFrozenSteamScale;
    /* 0x01E4 */ f32 drawDmgEffAlpha;
    /* 0x01E8 */ Vec3s jointTable[GOHT_LIMB_MAX];
    /* 0x02AE */ Vec3s morphTable[GOHT_LIMB_MAX];
    /* 0x0374 */ Vec3s unk_0374;
    /* 0x037A */ Vec3s unk_037A;
    /* 0x0380 */ Vec3f unk_0380;
    /* 0x038C */ Vec3f subCamEye;
    /* 0x0398 */ Vec3f bodyPartsPos[GOHT_BODYPART_MAX];
    /* 0x044C */ Vec3f unk_044C;
    /* 0x0458 */ Vec3f unk_0458;
    /* 0x0464 */ Vec3f unk_0464;
    /* 0x0470 */ LightNode* lightNode;
    /* 0x0474 */ LightInfo lightInfo;
    /* 0x0484 */ ColliderJntSph bodyCollider;
    /* 0x04A4 */ ColliderJntSphElement bodyColliderElements[GOHT_COLLIDER_BODYPART_MAX];
    /* 0x0964 */ ColliderCylinder iceCollider;
    /* 0x09B0 */ Actor* unk_09B0[8];
    /* 0x09D0 */ Actor* unk_09D0[10];
    /* 0x09F8 */ GohtRock rocks[GOHT_ROCK_COUNT];
    /* 0x2618 */ GohtElectricBall electricBalls[GOHT_ELECTRIC_BALL_COUNT]; // A chain of electric balls used as an attack
    /* 0x3158 */ GohtMechanicalMalfunctionEffect mechanicalMalfunctionEffects[GOHT_MECHANICAL_MALFUNCTION_NUM_TYPES][GOHT_BODYPART_MAX]; // Black smoke and electric zaps on body parts as damage accumulates 
    /* 0x3734 */ Vec3f unk_3734[10];
    /* 0x37AC */ Vec3f unk_37AC;
    /* 0x37B8 */ ColliderSphere unk_37B8;
} BossHakugin; // size = 0x3810

#endif // Z_BOSS_HAKUGIN_H
