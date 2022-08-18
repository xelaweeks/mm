#ifndef Z_EN_STONE_HEISHI_H
#define Z_EN_STONE_HEISHI_H

#include "global.h"
#include "assets/objects/object_sdn/object_sdn.h"

struct EnStoneheishi;

typedef void (*EnStoneheishiActionFunc)(struct EnStoneheishi*, PlayState*);

typedef struct EnStoneheishi {
    /* 0x000 */ Actor actor;
    /* 0x144 */ SkelAnime skelAnime;
    /* 0x188 */ Vec3s jointTable[SOLDIER_LIMB_MAX];
    /* 0x1EE */ Vec3s morphTable[SOLDIER_LIMB_MAX];
    /* 0x254 */ EnStoneheishiActionFunc actionFunc;
    /* 0x258 */ s16 headRotY;
    /* 0x25A */ s16 headRotX;
    /* 0x25C */ s16 headRotZ;
    /* 0x25E */ s16 targetHeadPosY;
    /* 0x260 */ s16 targetHeadPosX;
    /* 0x264 */ s32 animMode;
    /* 0x268 */ s16 timer;
    /* 0x26A */ s16 unk26A;
    /* 0x26C */ f32 endFrame;
    /* 0x270 */ s16 unk270;
    /* 0x272 */ s16 textIndex;
    /* 0x274 */ s16 unk274;
    /* 0x276 */ u8 bottleStatus;
    /* 0x277 */ u8 playerGivesBluePotion;
    /* 0x278 */ ColliderCylinder collider;
} EnStoneheishi; // size = 0x2C4

typedef enum EN_STONE_HEISHI_BOTTLE {
    /* 0 */ BOTTLE_NONE,
    /* 1 */ BOTTLE_EMPTY,
    /* 2 */ BOTTLE_RED_POTION,
    /* 3 */ BOTTLE_BLUE_POTION,
} EN_STONE_HEISHI_BOTTLE;

extern const ActorInit En_Stone_heishi_InitVars;

#endif // Z_EN_STONE_HEISHI_H
