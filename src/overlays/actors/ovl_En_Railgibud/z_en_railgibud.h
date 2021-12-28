#ifndef Z_EN_RAILGIBUD_H
#define Z_EN_RAILGIBUD_H

#include "global.h"
#include "overlays/actors/ovl_En_Rd/z_en_rd.h"

struct EnRailgibud;

typedef void (*EnRailgibudActionFunc)(struct EnRailgibud*, GlobalContext*);

#define ENRAILGIBUD_GET_7F(thisx) ((thisx)->params & 0x7F)
#define ENRAILGIBUD_GET_80(thisx) ((thisx)->params & 0x80)
#define ENRAILGIBUD_GET_FF00(thisx) (((thisx)->params & 0xFF00) >> 8)

typedef struct EnRailgibud {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ ColliderCylinder collider;
    /* 0x0190 */ SkelAnime skelAnime;
    /* 0x01D4 */ EnRailgibudActionFunc actionFunc;
    /* 0x01D8 */ Vec3f limbPos[15];
    /* 0x028C */ s32 limbIndex;
    /* 0x0290 */ UNK_TYPE1 unk290[0x4];
    /* 0x0294 */ Vec3s* unk_294;
    /* 0x0298 */ s32 unk_298;
    /* 0x029C */ s32 unk_29C;
    /* 0x02A0 */ f32 effectAlpha;
    /* 0x02A4 */ f32 effectScale;
    /* 0x02A8 */ Vec3s jointTable[REDEAD_GIBDO_LIMB_MAX];
    /* 0x0344 */ Vec3s morphTable[REDEAD_GIBDO_LIMB_MAX];
    /* 0x03E0 */ Vec3s headRotation;
    /* 0x03E6 */ Vec3s upperBodyRotation;
    /* 0x03EC */ s16 unk_3EC;
    /* 0x03EE */ s16 unk_3EE;
    /* 0x03F0 */ union {
                    s16 grabState;
                    s16 unk_3F0;
                };
    /* 0x03F2 */ union {
                    s16 playerStunWaitTimer; // Cannot stun the player if this is non-zero
                    s16 grabDamageTimer;
                    s16 headShakeTimer;
                    s16 stunTimer;
                    s16 deathTimer;
                    s16 unk_3F2;
                };
    /* 0x03F4 */ s16 grabWaitTimer; // Cannot grab the player if this is non-zero
    /* 0x03F6 */ s16 effectTimer;
    /* 0x03F8 */ s16 type;
    /* 0x03FA */ s16 isInvincible;
    /* 0x03FC */ u16 unk_3FC;
    /* 0x03FE */ u16 unk_3FE;
    /* 0x0400 */ u16 textId;
    /* 0x0402 */ s16 unk_402;
    /* 0x0404 */ u8 effectType;
    /* 0x0405 */ s8 unk_405;
} EnRailgibud; // size = 0x408

extern const ActorInit En_Railgibud_InitVars;

#endif // Z_EN_RAILGIBUD_H
