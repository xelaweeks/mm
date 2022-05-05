/*
 * File: z_dm_stk.c
 * Overlay: ovl_Dm_Stk
 * Description: Skull Kid (cutscene)
 */

#include "z_dm_stk.h"
#include "objects/object_stk/object_stk.h"
#include "objects/object_stk2/object_stk2.h"
#include "objects/object_stk3/object_stk3.h"

#define FLAGS (ACTOR_FLAG_10 | ACTOR_FLAG_20 | ACTOR_FLAG_2000000)

#define THIS ((DmStk*)thisx)

void DmStk_Init(Actor* thisx, GlobalContext* globalCtx);
void DmStk_Destroy(Actor* thisx, GlobalContext* globalCtx);
void DmStk_Update(Actor* thisx, GlobalContext* globalCtx);
void DmStk_Draw(Actor* thisx, GlobalContext* globalCtx);

void func_80AA16F4(DmStk* this, GlobalContext* globalCtx);
void func_80AA1704(DmStk* this, GlobalContext* globalCtx);
void func_80AA1714(DmStk* this, GlobalContext* globalCtx);
void func_80AA17F8(DmStk* this, GlobalContext* globalCtx);
void func_80AA18D8(DmStk* this, GlobalContext* globalCtx);
void func_80AA192C(DmStk* this, GlobalContext* globalCtx);
void func_80AA1998(DmStk* this, GlobalContext* globalCtx);
void func_80AA19EC(DmStk* this, GlobalContext* globalCtx);
void func_80AA1A50(DmStk* this, GlobalContext* globalCtx);
void func_80AA1AC8(DmStk* this, GlobalContext* globalCtx);
void func_80AA1B9C(DmStk* this, GlobalContext* globalCtx);
void func_80AA1C64(DmStk* this, GlobalContext* globalCtx);
void func_80AA2720(DmStk* this, GlobalContext* globalCtx);
void func_80AA27EC(DmStk* this, GlobalContext* globalCtx);

typedef enum {
    /*  0 */ SKULL_KID_ANIMATION_HEAD_ROCKING_IDLE,
    /*  1 */ SKULL_KID_ANIMATION_WALK,
    /*  2 */ SKULL_KID_ANIMATION_LOOK_AROUND,
    /*  3 */ SKULL_KID_ANIMATION_IDLE_1,
    /*  4 */ SKULL_KID_ANIMATION_IDLE_2,
    /*  5 */ SKULL_KID_ANIMATION_DAY_THREE_TELESCOPE,
    /*  6 */ SKULL_KID_ANIMATION_GLITCHY_HORSE_RIDE_START,
    /*  7 */ SKULL_KID_ANIMATION_OPENING_ARMS_CROSSED,
    /*  8 */ SKULL_KID_ANIMATION_CURSE_START,
    /*  9 */ SKULL_KID_ANIMATION_CURSE_LOOP,
    /* 10 */ SKULL_KID_ANIMATION_LAUGH_START,
    /* 11 */ SKULL_KID_ANIMATION_LAUGH_LOOP,
    /* 12 */ SKULL_KID_ANIMATION_HIDE_OCARINA_START,
    /* 13 */ SKULL_KID_ANIMATION_HIDE_OCARINA_LOOP,
    /* 14 */ SKULL_KID_ANIMATION_PICK_UP_OCARINA_AND_START_PLAYING,
    /* 15 */ SKULL_KID_ANIMATION_PLAYING_OCARINA_AND_LAUGHING,
    /* 16 */ SKULL_KID_ANIMATION_PICK_UP_OCARINA,
    /* 17 */ SKULL_KID_ANIMATION_LOOK_AT_OCARINA,
    /* 18 */ SKULL_KID_ANIMATION_KICK_OVER_LINK_1,
    /* 19 */ SKULL_KID_ANIMATION_SEARCH_LINK_1,
    /* 20 */ SKULL_KID_ANIMATION_KICK_OVER_LINK_2,
    /* 21 */ SKULL_KID_ANIMATION_SEARCH_LINK_2,
    /* 22 */ SKULL_KID_ANIMATION_HORSE_RIDE_START,
    /* 23 */ SKULL_KID_ANIMATION_HORSE_RIDE_LOOP,
    /* 24 */ SKULL_KID_ANIMATION_RAISE_MASK_START,
    /* 25 */ SKULL_KID_ANIMATION_RAISE_MASK_LOOP,
    /* 26 */ SKULL_KID_ANIMATION_LOWER_MASK,
    /* 27 */ SKULL_KID_ANIMATION_JUMP_WHILE_HIDING_OCARINA,
    /* 28 */ SKULL_KID_ANIMATION_HORSE_RIDE_AND_ROTATE,
    /* 29 */ SKULL_KID_ANIMATION_PLAY_OCARINA_WHILE_FLOATING,
    /* 30 */ SKULL_KID_ANIMATION_FLOATING_TURN_AROUND,
    /* 31 */ SKULL_KID_ANIMATION_OCARINA_JUGGLE,
    /* 32 */ SKULL_KID_ANIMATION_CALL_DOWN_MOON_START,
    /* 33 */ SKULL_KID_ANIMATION_CALL_DOWN_MOON_LOOP,
    /* 34 */ SKULL_KID_ANIMATION_SMACK_FAIRY_START,
    /* 35 */ SKULL_KID_ANIMATION_SMACK_FAIRY_LOOP,
    /* 36 */ SKULL_KID_ANIMATION_HIT_BY_BUBBLE,
    /* 37 */ SKULL_KID_ANIMATION_DROP_OCARINA,
    /* 38 */ SKULL_KID_ANIMATION_CLOCK_TOWER_ARMS_CROSSED,
    /* 39 */ SKULL_KID_ANIMATION_DEFLECT_ATTACK,
    /* 40 */ SKULL_KID_ANIMATION_TELESCOPE_LOOK_UP_START,
    /* 41 */ SKULL_KID_ANIMATION_TELESCOPE_LOOK_UP_LOOP,
    /* 42 */ SKULL_KID_ANIMATION_SURPRISE_START,
    /* 43 */ SKULL_KID_ANIMATION_SURPRISE_LOOP,
    /* 44 */ SKULL_KID_ANIMATION_LOOKING_AROUND_FOR_GIANTS_START,
    /* 45 */ SKULL_KID_ANIMATION_LOOKING_AROUND_FOR_GIANTS_LOOP,
    /* 46 */ SKULL_KID_ANIMATION_HOLD_HEAD_AND_SHAKE_START,
    /* 47 */ SKULL_KID_ANIMATION_HOLD_HEAD_AND_SHAKE_LOOP,
    /* 48 */ SKULL_KID_ANIMATION_HOLD_HEAD_AND_SCREAM_START,
    /* 49 */ SKULL_KID_ANIMATION_HOLD_HEAD_AND_SCREAM_LOOP,
    /* 50 */ SKULL_KID_ANIMATION_HUDDLE_WITH_FAIRIES,
    /* 51 */ SKULL_KID_ANIMATION_SEARCH_MASK_SALESMAN,
    /* 52 */ SKULL_KID_ANIMATION_HOLD_UP_MASK_START,
    /* 53 */ SKULL_KID_ANIMATION_HOLD_UP_MASK_LOOP,
    /* 54 */ SKULL_KID_ANIMATION_SHIVER,
    /* 55 */ SKULL_KID_ANIMATION_DRAW,
    /* 56 */ SKULL_KID_ANIMATION_DAY_THREE_TELESCOPE_LOOK_UP,
    /* 57 */ SKULL_KID_ANIMATION_SPANK,
    /* 58 */ SKULL_KID_ANIMATION_HIP_SHAKE_AND_JUMP,
    /* 59 */ SKULL_KID_ANIMATION_PLAY_FLUTE,
    /* 60 */ SKULL_KID_ANIMATION_CARTWHEEL,
    /* 61 */ SKULL_KID_ANIMATION_DANGLE_FROM_MASK_START_1,
    /* 62 */ SKULL_KID_ANIMATION_DANGLE_FROM_MASK_START_2,
    /* 63 */ SKULL_KID_ANIMATION_DANGLE_FROM_MASK_LOOP,
    /* 64 */ SKULL_KID_ANIMATION_DROPPED_FROM_MASK,
    /* 65 */ SKULL_KID_ANIMATION_LOOK_UP_AT_GIANTS,
    /* 66 */ SKULL_KID_ANIMATION_ASHAMED_START,
    /* 67 */ SKULL_KID_ANIMATION_ASHAMED_LOOP,
    /* 68 */ SKULL_KID_ANIMATION_LOOK_LEFT_START,
    /* 69 */ SKULL_KID_ANIMATION_LOOK_LEFT_LOOP,
    /* 70 */ SKULL_KID_ANIMATION_SNIFF,
    /* 71 */ SKULL_KID_ANIMATION_LAUGH_AFTER_SNIFF,
} SkullKidAnimationIndex;

typedef enum {
    /* 0 */ SKULL_KID_MASK_TYPE_NO_MASK,
    /* 1 */ SKULL_KID_MASK_TYPE_NORMAL,
    /* 2 */ SKULL_KID_MASK_TYPE_GLOWING_EYES,
    /* 3 */ SKULL_KID_MASK_TYPE_FADING_OUT,
    /* 9 */ SKULL_KID_MASK_TYPE_RAISED = 9,
} SkullKidMaskType;

typedef enum {
    /* 0 */ SKULL_KID_HAND_TYPE_HOLDING_LINK_MASK_AND_FLUTE,
    /* 1 */ SKULL_KID_HAND_TYPE_HOLDING_LINK_MASK,
    /* 2 */ SKULL_KID_HAND_TYPE_HOLDING_MAJORAS_MASK,
    /* 3 */ SKULL_KID_HAND_TYPE_HOLDING_OCARINA,
    /* 4 */ SKULL_KID_HAND_TYPE_JUGGLING_OR_DROPPING_OCARINA,
    /* 5 */ SKULL_KID_HAND_TYPE_HOLDING_MAJORAS_MASK_AND_FLUTE,
    /* 6 */ SKULL_KID_HAND_TYPE_HOLDING_FLUTE,
    /* 9 */ SKULL_KID_HAND_TYPE_DEFAULT = 9,
} SkullKidHandType;

typedef enum {
    /* 0 */ SKULL_KID_FADE_IN_STATE_NONE,
    /* 1 */ SKULL_KID_FADE_IN_STATE_START,
    /* 2 */ SKULL_KID_FADE_IN_STATE_INCREASE_FOG_N,
    /* 3 */ SKULL_KID_FADE_IN_STATE_INCREASE_ALPHA,
} SkullKidFadeInState;

typedef enum {
    /* 0 */ SKULL_KID_FADE_OUT_STATE_NONE,
    /* 1 */ SKULL_KID_FADE_OUT_STATE_FADING_OUT,
} SkullKidFadeOutState;

const ActorInit Dm_Stk_InitVars = {
    ACTOR_DM_STK,
    ACTORCAT_ITEMACTION,
    FLAGS,
    OBJECT_STK,
    sizeof(DmStk),
    (ActorFunc)DmStk_Init,
    (ActorFunc)DmStk_Destroy,
    (ActorFunc)DmStk_Update,
    (ActorFunc)DmStk_Draw,
};

static ColliderCylinderInit sCylinderInit = {
    {
        COLTYPE_HIT1,
        AT_NONE,
        AC_ON | AC_HARD | AC_TYPE_PLAYER | AC_TYPE_ENEMY,
        OC1_ON | OC1_TYPE_ALL,
        OC2_TYPE_1,
        COLSHAPE_CYLINDER,
    },
    {
        ELEMTYPE_UNK1,
        { 0x00000000, 0x00, 0x00 },
        { 0xF7CFFFFF, 0x00, 0x00 },
        TOUCH_NONE | TOUCH_SFX_NORMAL,
        BUMP_ON,
        OCELEM_ON,
    },
    { 14, 38, 0, { 0, 0, 0 } },
};

static CollisionCheckInfoInit2 sColChkInfoInit = { 1, 0, 0, 0, MASS_IMMOVABLE };

static DamageTable sDamageTable = {
    /* Deku Nut       */ DMG_ENTRY(1, 0xF),
    /* Deku Stick     */ DMG_ENTRY(1, 0xF),
    /* Horse trample  */ DMG_ENTRY(1, 0xF),
    /* Explosives     */ DMG_ENTRY(1, 0xF),
    /* Zora boomerang */ DMG_ENTRY(1, 0xF),
    /* Normal arrow   */ DMG_ENTRY(1, 0xF),
    /* UNK_DMG_0x06   */ DMG_ENTRY(1, 0xF),
    /* Hookshot       */ DMG_ENTRY(1, 0xF),
    /* Goron punch    */ DMG_ENTRY(1, 0xF),
    /* Sword          */ DMG_ENTRY(1, 0xF),
    /* Goron pound    */ DMG_ENTRY(1, 0xF),
    /* Fire arrow     */ DMG_ENTRY(1, 0xF),
    /* Ice arrow      */ DMG_ENTRY(1, 0xF),
    /* Light arrow    */ DMG_ENTRY(1, 0xF),
    /* Goron spikes   */ DMG_ENTRY(1, 0xF),
    /* Deku spin      */ DMG_ENTRY(1, 0xF),
    /* Deku bubble    */ DMG_ENTRY(1, 0xF),
    /* Deku launch    */ DMG_ENTRY(1, 0xF),
    /* UNK_DMG_0x12   */ DMG_ENTRY(1, 0xF),
    /* Zora barrier   */ DMG_ENTRY(1, 0xF),
    /* Normal shield  */ DMG_ENTRY(1, 0xF),
    /* Light ray      */ DMG_ENTRY(1, 0xF),
    /* Thrown object  */ DMG_ENTRY(1, 0xF),
    /* Zora punch     */ DMG_ENTRY(1, 0xF),
    /* Spin attack    */ DMG_ENTRY(1, 0xF),
    /* Sword beam     */ DMG_ENTRY(1, 0xF),
    /* Normal Roll    */ DMG_ENTRY(1, 0xF),
    /* UNK_DMG_0x1B   */ DMG_ENTRY(1, 0xF),
    /* UNK_DMG_0x1C   */ DMG_ENTRY(1, 0xF),
    /* Unblockable    */ DMG_ENTRY(1, 0xF),
    /* UNK_DMG_0x1E   */ DMG_ENTRY(1, 0xF),
    /* Powder Keg     */ DMG_ENTRY(1, 0xF),
};

static AnimationInfo sAnimations[] = {
    { &gSkullKidHeadRockingIdleAnim, 1.0f, 0.0f, -1.0f, ANIMMODE_LOOP, 0.0f },
    { &gSkullKidWalkAnim, 1.0f, 0.0f, -1.0f, ANIMMODE_LOOP, 0.0f },
    { &gSkullKidLookAroundAnim, 1.0f, 0.0f, -1.0f, ANIMMODE_ONCE, 0.0f },
    { &gSkullKidIdleAnim, 1.0f, 0.0f, -1.0f, ANIMMODE_LOOP, 0.0f },
    { &gSkullKidIdleAnim, 1.0f, 0.0f, -1.0f, ANIMMODE_LOOP, 0.0f },
    { &gSkullKidDayThreeTelescopeAnim, 1.0f, 0.0f, -1.0f, ANIMMODE_LOOP, 0.0f },
    { &gSkullKidGlitchyHorseRideStartAnim, 1.0f, 0.0f, -1.0f, ANIMMODE_LOOP, 0.0f },
    { &gSkullKidOpeningArmsCrossedAnim, 1.0f, 0.0f, -1.0f, ANIMMODE_LOOP, 0.0f },
    { &gSkullKidCurseStartAnim, 1.0f, 0.0f, -1.0f, ANIMMODE_ONCE, 0.0f },
    { &gSkullKidCurseLoopAnim, 1.0f, 0.0f, -1.0f, ANIMMODE_LOOP, 0.0f },
    { &gSkullKidLaughStartAnim, 1.0f, 0.0f, -1.0f, ANIMMODE_ONCE, 0.0f },
    { &gSkullKidLaughLoopAnim, 1.0f, 0.0f, -1.0f, ANIMMODE_LOOP, 0.0f },
    { &gSkullKidHideOcarinaStartAnim, 1.0f, 0.0f, -1.0f, ANIMMODE_ONCE, 0.0f },
    { &gSkullKidHideOcarinaLoopAnim, 1.0f, 0.0f, -1.0f, ANIMMODE_LOOP, 0.0f },
    { &gSkullKidPickUpOcarinaAndStartPlayingAnim, 1.0f, 0.0f, -1.0f, ANIMMODE_ONCE, 0.0f },
    { &gSkullKidPlayingOcarinaAndLaughingAnim, 1.0f, 0.0f, -1.0f, ANIMMODE_LOOP, 0.0f },
    { &gSkullKidPickUpOcarinaAnim, 1.0f, 0.0f, -1.0f, ANIMMODE_ONCE, 0.0f },
    { &gSkullKidLookAtOcarinaAnim, 1.0f, 0.0f, -1.0f, ANIMMODE_LOOP, 0.0f },
    { &gSkullKidKickOverLinkAnim, 1.0f, 0.0f, -1.0f, ANIMMODE_ONCE, 0.0f },
    { &gSkullKidSearchLinkAnim, 1.0f, 0.0f, -1.0f, ANIMMODE_LOOP, 0.0f },
    { &gSkullKidKickOverLinkAnim, 1.0f, 0.0f, -1.0f, ANIMMODE_ONCE, 0.0f },
    { &gSkullKidSearchLinkAnim, 1.0f, 0.0f, -1.0f, ANIMMODE_LOOP, 0.0f },
    { &gSkullKidHorseRideStartAnim, 1.0f, 0.0f, -1.0f, ANIMMODE_ONCE, 0.0f },
    { &gSkullKidHorseRideLoopAnim, 1.0f, 0.0f, -1.0f, ANIMMODE_LOOP, 0.0f },
    { &gSkullKidRaiseMaskStartAnim, 1.0f, 0.0f, -1.0f, ANIMMODE_ONCE, 0.0f },
    { &gSkullKidRaiseMaskLoopAnim, 1.0f, 0.0f, -1.0f, ANIMMODE_LOOP, 0.0f },
    { &gSkullKidLowerMaskAnim, 1.0f, 0.0f, -1.0f, ANIMMODE_ONCE, 0.0f },
    { &gSkullKidJumpWhileHidingOcarinaAnim, 1.0f, 0.0f, -1.0f, ANIMMODE_ONCE, 0.0f },
    { &gSkullKidHorseRideAndRotateAnim, 1.0f, 0.0f, -1.0f, ANIMMODE_ONCE, 0.0f },
    { &gSkullKidPlayOcarinaWhileFloatingAnim, 1.0f, 0.0f, -1.0f, ANIMMODE_LOOP, 0.0f },
    { &gSkullKidFloatingTurnAroundAnim, 1.0f, 0.0f, -1.0f, ANIMMODE_ONCE, 0.0f },
    { &gSkullKidOcarinaJuggleAnim, 1.0f, 0.0f, -1.0f, ANIMMODE_LOOP, 0.0f },
    { &gSkullKidCallDownMoonStartAnim, 1.0f, 0.0f, -1.0f, ANIMMODE_ONCE, 0.0f },
    { &gSkullKidCallDownMoonLoopAnim, 1.0f, 0.0f, -1.0f, ANIMMODE_LOOP, 0.0f },
    { &gSkullKidSmackFairyStartAnim, 1.0f, 0.0f, -1.0f, ANIMMODE_ONCE, 0.0f },
    { &gSkullKidSmackFairyLoopAnim, 1.0f, 0.0f, -1.0f, ANIMMODE_LOOP, 0.0f },
    { &gSkullKidHitByBubbleAnim, 1.0f, 0.0f, -1.0f, ANIMMODE_ONCE, 0.0f },
    { &gSkullKidDropOcarinaAnim, 1.0f, 0.0f, -1.0f, ANIMMODE_ONCE, 0.0f },
    { &gSkullKidClockTowerArmsCrossedAnim, 1.0f, 0.0f, -1.0f, ANIMMODE_LOOP, 0.0f },
    { &gSkullKidDeflectAttackAnim, 1.0f, 0.0f, -1.0f, ANIMMODE_ONCE, 0.0f },
    { &gSkullKidTelescopeLookUpStartAnim, 1.0f, 0.0f, -1.0f, ANIMMODE_ONCE, 0.0f },
    { &gSkullKidTelescopeLookUpLoopAnim, 1.0f, 0.0f, -1.0f, ANIMMODE_LOOP, 0.0f },
    { &gSkullKidSurpriseStartAnim, 1.0f, 0.0f, -1.0f, ANIMMODE_ONCE, 0.0f },
    { &gSkullKidSurpriseLoopAnim, 1.0f, 0.0f, -1.0f, ANIMMODE_LOOP, 0.0f },
    { &gSkullKidLookingAroundForGiantsStartAnim, 1.0f, 0.0f, -1.0f, ANIMMODE_ONCE, 0.0f },
    { &gSkullKidLookingAroundForGiantsLoopAnim, 1.0f, 0.0f, -1.0f, ANIMMODE_LOOP, 0.0f },
    { &gSkullKidHoldHeadAndShakeStartAnim, 1.0f, 0.0f, -1.0f, ANIMMODE_ONCE, 0.0f },
    { &gSkullKidHoldHeadAndShakeLoopAnim, 1.0f, 0.0f, -1.0f, ANIMMODE_LOOP, 0.0f },
    { &gSkullKidHoldHeadAndScreamStartAnim, 1.0f, 0.0f, -1.0f, ANIMMODE_ONCE, 0.0f },
    { &gSkullKidHoldHeadAndScreamLoopAnim, 1.0f, 0.0f, -1.0f, ANIMMODE_LOOP, 0.0f },
    { &gSkullKidHuddleWithFairiesAnim, 1.0f, 0.0f, -1.0f, ANIMMODE_LOOP, 0.0f },
    { &gSkullKidSearchMaskSalesmanAnim, 1.0f, 0.0f, -1.0f, ANIMMODE_LOOP, 0.0f },
    { &gSkullKidHoldUpMaskStartAnim, 1.0f, 0.0f, -1.0f, ANIMMODE_ONCE, 0.0f },
    { &gSkullKidHoldUpMaskLoopAnim, 1.0f, 0.0f, -1.0f, ANIMMODE_LOOP, 0.0f },
    { &gSkullKidShiverAnim, 1.0f, 0.0f, -1.0f, ANIMMODE_LOOP, 0.0f },
    { &gSkullKidDrawAnim, 1.0f, 0.0f, -1.0f, ANIMMODE_ONCE, 0.0f },
    { &gSkullKidDayThreeTelescopeLookUpAnim, 1.0f, 0.0f, -1.0f, ANIMMODE_ONCE, 0.0f },
    { &gSkullKidSpankAnim, 1.0f, 0.0f, -1.0f, ANIMMODE_LOOP, 0.0f },
    { &gSkullKidHipShakeAndJumpAnim, 1.0f, 0.0f, -1.0f, ANIMMODE_ONCE, 0.0f },
    { &gSkullKidPlayFluteAnim, 1.0f, 0.0f, -1.0f, ANIMMODE_LOOP, 0.0f },
    { &gSkullKidCartwheelAnim, 1.0f, 0.0f, -1.0f, ANIMMODE_ONCE, 0.0f },
    { &gSkullKidDangleFromMaskStartAnim, 1.0f, 0.0f, -1.0f, ANIMMODE_ONCE, 0.0f },
    { &gSkullKidDangleFromMaskStartAnim, 1.0f, 0.0f, -1.0f, ANIMMODE_ONCE, 0.0f },
    { &gSkullKidDangleFromMaskLoopAnim, 1.0f, 0.0f, -1.0f, ANIMMODE_LOOP, 0.0f },
    { &gSkullKidDroppedFromMaskAnim, 1.0f, 0.0f, -1.0f, ANIMMODE_ONCE, 0.0f },
    { &gSkullKidLookUpAtGiantsAnim, 1.0f, 0.0f, -1.0f, ANIMMODE_LOOP, 0.0f },
    { &gSkullKidAshamedStartAnim, 1.0f, 0.0f, -1.0f, ANIMMODE_ONCE, 0.0f },
    { &gSkullKidAshamedLoopAnim, 1.0f, 0.0f, -1.0f, ANIMMODE_LOOP, 0.0f },
    { &gSkullKidLookLeftStartAnim, 1.0f, 0.0f, -1.0f, ANIMMODE_ONCE, 0.0f },
    { &gSkullKidLookLeftLoopAnim, 1.0f, 0.0f, -1.0f, ANIMMODE_LOOP, 0.0f },
    { &gSkullKidSniffAnim, 1.0f, 0.0f, -1.0f, ANIMMODE_ONCE, 0.0f },
    { &gSkullKidLaughAfterSniffAnim, 1.0f, 0.0f, -1.0f, ANIMMODE_LOOP, 0.0f },
};

void func_80A9FDB0(DmStk* this, GlobalContext* globalCtx) {
    s32 objectIndex;

    if (((this->animationId >= SKULL_KID_ANIMATION_HEAD_ROCKING_IDLE) &&
         (this->animationId <= SKULL_KID_ANIMATION_DAY_THREE_TELESCOPE)) ||
        (this->animationId == SKULL_KID_ANIMATION_CALL_DOWN_MOON_START) ||
        (this->animationId == SKULL_KID_ANIMATION_CALL_DOWN_MOON_LOOP) ||
        (this->animationId == SKULL_KID_ANIMATION_TELESCOPE_LOOK_UP_START) ||
        (this->animationId == SKULL_KID_ANIMATION_TELESCOPE_LOOK_UP_LOOP)) {
        objectIndex = this->objectStkObjectIndex;
    } else if (this->animationId > SKULL_KID_ANIMATION_DROPPED_FROM_MASK) {
        objectIndex = this->objectStk3ObjectIndex;
    } else {
        objectIndex = this->objectStk2ObjectIndex;
    }

    if (objectIndex >= 0) {
        gSegments[6] = PHYSICAL_TO_VIRTUAL(globalCtx->objectCtx.status[objectIndex].segment);
    }
}

void func_80A9FE3C(DmStk* this, GlobalContext* globalCtx, SkelAnime* skelAnime, AnimationInfo* animation, u16 index) {
    func_80A9FDB0(this, globalCtx);

    animation += index;

    Animation_Change(skelAnime, animation->animation, animation->playSpeed, animation->startFrame,
                     (animation->frameCount < 0.0f) ? Animation_GetLastFrame(&animation->animation->common)
                                                    : animation->frameCount,
                     animation->mode, animation->morphFrames);
}

void func_80A9FED8(DmStk* this, GlobalContext* globalCtx) {
    switch (globalCtx->csCtx.frames + 20) {
        case 1195:
            Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_STALKIDS_APPEAR);
            break;

        case 1232:
        case 1241:
        case 1252:
        case 1255:
        case 1257:
            Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_STALKIDS_SHAKEHEAD);
            break;

        case 1285:
            Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_STAL03_LAUGH_BIG);
            break;

        case 1343:
            Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_STALKIDS_MASK_OFF);
            break;

        case 1410:
            Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_STALKIDS_MASK_ON);
            break;

        case 1603:
            Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_STALKIDS_WALK);
            break;

        case 1610:
            Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_STALKIDS_REVERSE);
            break;

        case 2095:
            Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_STALKIDS_SURPRISED);
            break;

        case 2190:
            Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_STALKIDS_JUMP);
            break;

        case 2212:
            Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_STALKIDS_ONGND);
            break;

        case 2214:
            Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_STAL02_LAUGH_SHORT);
            break;

        case 2250:
            Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_STAL06_SURPRISED);
            Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_STALKIDS_DOWN_K);
            break;

        case 2255:
        case 2266:
        case 2277:
        case 2288:
        case 2299:
        case 2310:
        case 2321:
        case 2332:
        case 2343:
        case 2354:
        case 2365:
        case 2376:
        case 2387:
        case 2398:
        case 2409:
        case 2420:
        case 2431:
        case 2442:
        case 2453:
        case 2464:
        case 2475:
        case 2486:
        case 2497:
        case 2508:
        case 2519:
        case 2530:
            Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_STALKIDS_RIDE);
            break;
    }
}

void func_80AA00CC(DmStk* this, GlobalContext* globalCtx) {
    if (globalCtx->csCtx.frames == 535) {
        func_8019F128(NA_SE_EV_CLOCK_TOWER_BELL);
    }
}

void func_80AA0100(DmStk* this, GlobalContext* globalCtx) {
    switch (globalCtx->csCtx.frames) {
        case 78:
        case 89:
        case 100:
        case 111:
        case 122:
        case 133:
        case 144:
        case 155:
        case 166:
        case 177:
        case 188:
        case 199:
        case 210:
        case 221:
        case 232:
        case 243:
        case 254:
            Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_STALKIDS_RIDE);
            break;

        case 173:
            Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_STAL03_LAUGH_BIG);
            break;
    }
}

void func_80AA0158(DmStk* this, GlobalContext* globalCtx) {
    switch (globalCtx->csCtx.frames) {
        case 18:
            Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_STALKIDS_GASAGOSO);
            break;

        case 90:
            Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_STALKIDS_MASK_ON);
            break;

        case 142:
            Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_EVIL_POWER);
            break;
    }
}

void func_80AA01C0(DmStk* this, GlobalContext* globalCtx) {
    switch (globalCtx->csCtx.frames) {
        case 415:
            func_801A479C(&this->actor.projectedPos, NA_SE_EN_STALKIDS_FLOAT, 100);
            break;

        case 785:
            func_8019F128(NA_SE_SY_STALKIDS_PSYCHO);
            func_8019FE74(&gSfxVolume, 0.0f, 150);
            break;

        case 560:
            Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_STAL02_LAUGH_SHORT);
            break;

        case 890:
            Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_STAL21_PSYCHO_VOICE);
            break;
    }
}

void func_80AA0264(DmStk* this, GlobalContext* globalCtx) {
    Player* player = GET_PLAYER(globalCtx);

    switch (globalCtx->csCtx.frames) {
        case 10:
            func_801A479C(&this->actor.projectedPos, NA_SE_EN_STALKIDS_FLOAT, 50);
            break;

        case 71:
            Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_STALKIDS_BODY);
            break;

        case 365:
            func_801A0654(&this->actor.projectedPos, NA_SE_EN_STALKIDS_FLOAT, 0);
            break;

        case 650:
            func_8019FE74(&gSfxVolume, 0.0f, 80);
            break;

        case 265:
            Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_STAL03_LAUGH_BIG);
            break;

        case 126:
            Actor_PlaySfxAtPos(&player->actor, NA_SE_VO_DUMMY_150);
            break;

        case 197:
            Actor_PlaySfxAtPos(&player->actor, NA_SE_VO_DUMMY_134);
            break;

        case 207:
            Actor_PlaySfxAtPos(&player->actor, NA_SE_VO_DUMMY_135);
            break;

        case 217:
            Actor_PlaySfxAtPos(&player->actor, NA_SE_VO_DUMMY_136);
            break;
    }

    if (player) {}

    if ((globalCtx->csCtx.frames >= 263) && (globalCtx->csCtx.frames < 698)) {
        Actor_PlaySfxAtPos(&player->actor, NA_SE_EN_STALKIDS_BODY_LEV - SFX_FLAG);
    }
}

void func_80AA0420(DmStk* this, GlobalContext* globalCtx) {
    static s32 D_80AA3CB8 = 0;

    switch (globalCtx->csCtx.frames) {
        case 140:
            func_801A479C(&this->actor.projectedPos, NA_SE_EN_STALKIDS_FLOAT, 80);
            break;

        case 258:
            Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_STALKIDS_TURN);
            break;

        case 524:
            Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_STALKIDS_TURN);
            Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_STAL04_ANGER);
            break;

        case 534:
            Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_PO_ROLL);
            break;

        case 678:
            Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_STALKIDS_STRETCH);
            break;
    }

    if ((this->animationId == SKULL_KID_ANIMATION_OCARINA_JUGGLE) && (globalCtx->csCtx.frames < 700)) {
        if (Animation_OnFrame(&this->skelAnime, 5.0f) || Animation_OnFrame(&this->skelAnime, 25.0f)) {
            Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_STALKIDS_OTEDAMA1);
        } else if (Animation_OnFrame(&this->skelAnime, 17.0f) || Animation_OnFrame(&this->skelAnime, 40.0f)) {
            Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_STALKIDS_OTEDAMA2);
        }
    }

    if (globalCtx->csCtx.frames >= 700) {
        if (D_80AA3CB8 < 128) {
            if ((D_80AA3CB8 & 0x1F) == 0) {
                Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_STAL20_CALL_MOON);
            } else if ((D_80AA3CB8 & 0x1F) == 16) {
                Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_STAL20_CALL_MOON2);
            }
            D_80AA3CB8++;
        }
    } else {
        D_80AA3CB8 = 0;
    }
}

void func_80AA05F0(DmStk* this, GlobalContext* globalCtx) {
    if (globalCtx->csCtx.frames == 3) {
        Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_STAL06_SURPRISED);
        Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_STALKIDS_DOWN_K);
    }
}

void func_80AA0634(DmStk* this, GlobalContext* globalCtx) {
    if ((globalCtx->csCtx.frames >= 642) && (globalCtx->csCtx.frames < 845)) {
        Actor_PlaySfxAtPos(&this->actor, NA_SE_NE_STAL23_COLD - SFX_FLAG);
    }
}

void func_80AA066C(DmStk* this, GlobalContext* globalCtx) {
    switch (globalCtx->csCtx.frames) {
        case 58:
        case 61:
        case 68:
        case 72:
        case 77:
        case 79:
            Actor_PlaySfxAtPos(&this->actor, NA_SE_PL_WALK_WATER2);
            Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_STALKIDS_WALK);
            break;

        case 186:
            Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_NUTS_UP);
            break;

        case 230:
            Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_STAL22_LAUGH_KID_L);
            break;
    }
}

void func_80AA071C(DmStk* this, GlobalContext* globalCtx) {
    switch (globalCtx->csCtx.frames) {
        case 5:
            func_801A4A28(12);
            break;

        case 660:
            Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_STALKIDS_SHAKEHEAD);
            break;
    }
}

void func_80AA076C(DmStk* this, GlobalContext* globalCtx) {
    Player* player = GET_PLAYER(globalCtx);

    switch (globalCtx->csCtx.frames) {
        case 5:
            func_801A4A28(12);
            break;

        case 45:
            Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_STALKIDS_RIDE);
            break;

        case 93:
            Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_STALKIDS_MASK_OFF);
            break;

        case 245:
            Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_STALKIDS_RIDE);
            break;

        case 269:
            Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_STAL11_LAUGH_SHY2);
            break;

        case 327:
            Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_STALKIDS_SHAKEHEAD);
            break;

        case 455:
            Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_STALKIDS_RIDE);
            break;

        case 1730:
            Audio_QueueSeqCmd(0x141400FF);
            break;

        case 1395:
            func_800B8E58(player, NA_SE_VO_DUMMY_34);
            break;

        case 1850:
            Audio_QueueSeqCmd(0x42320000);
            break;

        case 2000:
            func_801A5BD0(0x7F);
            break;
    }

    if (this->animationId == SKULL_KID_ANIMATION_HEAD_ROCKING_IDLE) {
        if (Animation_OnFrame(&this->skelAnime, 8.0f) || Animation_OnFrame(&this->skelAnime, 17.0f)) {
            Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_STALKIDS_MASK_OFF);
        }

        if (Animation_OnFrame(&this->skelAnime, 28.0f)) {
            Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_STALKIDS_RIDE);
        }
    } else if (this->animationId == SKULL_KID_ANIMATION_LAUGH_AFTER_SNIFF) {
        if (Animation_OnFrame(&this->skelAnime, 2.0f) || Animation_OnFrame(&this->skelAnime, 6.0f) ||
            Animation_OnFrame(&this->skelAnime, 12.0f) || Animation_OnFrame(&this->skelAnime, 18.0f)) {
            Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_STALKIDS_MASK_OFF);
        }
    } else if ((this->animationId == SKULL_KID_ANIMATION_SNIFF) &&
               (Animation_OnFrame(&this->skelAnime, 16.0f) || Animation_OnFrame(&this->skelAnime, 23.0f))) {
        Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_STALKIDS_NOSE);
    }
}

void func_80AA09DC(DmStk* this, GlobalContext* globalCtx) {
    static s32 D_80AA3CBC = 0;

    switch (globalCtx->csCtx.frames) {
        case 40:
            func_801A479C(&this->actor.projectedPos, NA_SE_EN_STALKIDS_FLOAT, 80);
            break;

        case 234:
            Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_STALKIDS_TURN);
            Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_STAL04_ANGER);
            break;

        case 244:
            Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_PO_ROLL);
            break;

        case 388:
            Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_STALKIDS_STRETCH);
            break;
    }

    if (globalCtx->csCtx.frames >= 408) {
        if (D_80AA3CBC < 128) {
            if ((D_80AA3CBC & 0x1F) == 0) {
                Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_STAL20_CALL_MOON);
            } else if ((D_80AA3CBC & 0x1F) == 16) {
                Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_STAL20_CALL_MOON2);
            }
            D_80AA3CBC++;
        }
    } else {
        D_80AA3CBC = 0;
    }
}

void func_80AA0B08(DmStk* this, GlobalContext* globalCtx) {
    this->unk_310.x = this->actor.projectedPos.x;
    this->unk_310.y = this->actor.projectedPos.y;
    this->unk_310.z = this->actor.projectedPos.z;

    switch (globalCtx->csCtx.frames) {
        case 64:
            Audio_PlaySfxAtPos(&this->unk_310, NA_SE_EN_STAL06_SURPRISED);
            break;

        case 327:
        case 332:
        case 335:
        case 344:
            Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_STALKIDS_MASK_OFF);
            break;

        case 367:
            Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_STALKIDS_BODY_LEV);
            break;

        case 470:
            Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_STALKIDS_HEADACHE);
            break;

        case 486:
            Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_STALKIDS_MASK_OFF);
            Audio_PlaySfxAtPos(&this->unk_310, NA_SE_EN_STAL08_CRY_BIG);
            break;

        case 496:
            Audio_PlaySfxAtPos(&this->unk_310, NA_SE_EN_STAL09_SCREAM);
            break;

        case 590:
            Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_STALKIDS_MASK_OFF);
            break;

        case 592:
            Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_STALKIDS_RIDE);
            break;

        case 594:
            Audio_PlaySfxAtPos(&this->unk_310, NA_SE_EN_STAL24_SCREAM2);
            break;
    }

    if (1) {}

    if ((globalCtx->csCtx.frames >= 62) && (globalCtx->csCtx.frames < 273)) {
        if ((Rand_ZeroOne() < 0.75f) && ((globalCtx->state.frames % 2) != 0)) {
            Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_STALKIDS_EARTHQUAKE);
        }
    }

    if ((globalCtx->csCtx.frames >= 498) && (globalCtx->csCtx.frames < 577)) {
        if ((globalCtx->state.frames % 4) == 0) {
            if ((globalCtx->state.frames & 4) != 0) {
                Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_STALKIDS_BODY_LEV);
            } else {
                Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_STALKIDS_MASK_OFF);
            }
        }
    }

    if (globalCtx->csCtx.frames >= 290) {
        func_8019F128(NA_SE_EV_KYOJIN_VOICE_SUCCESS - SFX_FLAG);
    }
}

void func_80AA0DA8(DmStk* this, GlobalContext* globalCtx) {
    switch (globalCtx->csCtx.frames) {
        case 551:
            Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_STALKIDS_PULLED);
            break;

        case 711:
            Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_STALKIDS_MASK_OFF);
            break;

        case 716:
            Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_STALKIDS_MASK_ON);
            Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_STALKIDS_ONGND);
            break;
    }
}

void func_80AA0E1C(DmStk* this, GlobalContext* globalCtx) {
    switch (globalCtx->csCtx.frames) {
        case 311:
            Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_STALKIDS_PULLED);
            break;

        case 365:
            Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_STALKIDS_MASK_OFF);
            break;

        case 372:
            Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_STALKIDS_MASK_ON);
            Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_STALKIDS_ONGND);
            break;
    }
}

void func_80AA0E90(DmStk* this, GlobalContext* globalCtx) {
    if (globalCtx->csCtx.state != 0) {
        switch (globalCtx->sceneNum) {
            case SCENE_LOST_WOODS:
                if (gSaveContext.sceneSetupIndex == 1) {
                    func_80A9FED8(this, globalCtx);
                } else if (gSaveContext.sceneSetupIndex == 0) {
                    func_80AA0100(this, globalCtx);
                } else if ((gSaveContext.sceneSetupIndex == 2) && (globalCtx->csCtx.currentCsIndex == 0)) {
                    func_80AA0158(this, globalCtx);
                }
                break;

            case SCENE_CLOCKTOWER:
                if (gSaveContext.sceneSetupIndex == 1) {
                    func_80AA00CC(this, globalCtx);
                }
                break;

            case SCENE_OPENINGDAN:
                if (gSaveContext.sceneSetupIndex == 0) {
                    if (globalCtx->csCtx.currentCsIndex == 0) {
                        func_80AA01C0(this, globalCtx);
                    } else if (globalCtx->csCtx.currentCsIndex == 1) {
                        func_80AA0264(this, globalCtx);
                    }
                }
                break;

            case SCENE_OKUJOU:
                if (gSaveContext.sceneSetupIndex == 0) {
                    if (globalCtx->csCtx.currentCsIndex == 0) {
                        func_80AA0420(this, globalCtx);
                    } else if (globalCtx->csCtx.currentCsIndex == 1) {
                        func_80AA05F0(this, globalCtx);
                    } else if (globalCtx->csCtx.currentCsIndex == 2) {
                        func_80AA09DC(this, globalCtx);
                    } else if (globalCtx->csCtx.currentCsIndex == 3) {
                        func_80AA0B08(this, globalCtx);
                    }
                } else if (gSaveContext.sceneSetupIndex == 2) {
                    if (globalCtx->csCtx.currentCsIndex == 0) {
                        func_80AA0DA8(this, globalCtx);
                    } else if (globalCtx->csCtx.currentCsIndex == 1) {
                        func_80AA0E1C(this, globalCtx);
                    }
                }
                break;

            case SCENE_00KEIKOKU:
                if (gSaveContext.sceneSetupIndex == 3) {
                    if (globalCtx->csCtx.currentCsIndex == 0) {
                        func_80AA0634(this, globalCtx);
                    } else if (globalCtx->csCtx.currentCsIndex == 2) {
                        func_80AA066C(this, globalCtx);
                    }
                } else if (gSaveContext.sceneSetupIndex == 7) {
                    if (globalCtx->csCtx.currentCsIndex == 0) {
                        func_80AA071C(this, globalCtx);
                    } else if (globalCtx->csCtx.currentCsIndex == 1) {
                        func_80AA076C(this, globalCtx);
                    }
                }
                break;
        }
    }

    if (this->animationId == SKULL_KID_ANIMATION_WALK) {
        if (Animation_OnFrame(&this->skelAnime, 2.0f) || Animation_OnFrame(&this->skelAnime, 6.0f)) {
            Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_STALKIDS_WALK);
        }
    } else if (this->animationId == SKULL_KID_ANIMATION_SEARCH_LINK_1) {
        if (Animation_OnFrame(&this->skelAnime, 0.0f) || Animation_OnFrame(&this->skelAnime, 13.0f) ||
            Animation_OnFrame(&this->skelAnime, 20.0f) || Animation_OnFrame(&this->skelAnime, 27.0f)) {
            Actor_PlaySfxAtPos(&this->actor, NA_SE_PL_CALM_HIT);
        }
    } else if (this->animationId == SKULL_KID_ANIMATION_PICK_UP_OCARINA_AND_START_PLAYING) {
        if (Animation_OnFrame(&this->skelAnime, 3.0f)) {
            Actor_PlaySfxAtPos(&this->actor, NA_SE_PL_PUT_OUT_ITEM);
        }
    } else if (this->animationId == SKULL_KID_ANIMATION_PLAYING_OCARINA_AND_LAUGHING) {
        if (Animation_OnFrame(&this->skelAnime, 14.0f)) {
            Actor_PlaySfxAtPos(&this->actor, NA_SE_EV_UNSKILLFUL_OCARINA);
        }

        if (Animation_OnFrame(&this->skelAnime, 45.0f)) {
            Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_STAL01_LAUGH);
        }
    }
}

void DmStk_Init(Actor* thisx, GlobalContext* globalCtx) {
    s32 pad;
    DmStk* this = THIS;

    this->shouldDraw = true;
    if (this->actor.params != 1) {
        this->unk_33A = 0;
        this->objectStkObjectIndex = Object_GetIndex(&globalCtx->objectCtx, OBJECT_STK);
        this->objectStk2ObjectIndex = Object_GetIndex(&globalCtx->objectCtx, OBJECT_STK2);
        this->objectStk3ObjectIndex = Object_GetIndex(&globalCtx->objectCtx, OBJECT_STK3);
        if (this->objectStkObjectIndex < 0) {
            Actor_MarkForDeath(&this->actor);
        }

        this->unk_328 = 0;
        this->unk_339 = 0;
        this->maskType = SKULL_KID_MASK_TYPE_NORMAL;
        this->animationId = SKULL_KID_ANIMATION_IDLE_1;
        this->fogR = globalCtx->lightCtx.unk7;
        this->fogG = globalCtx->lightCtx.unk8;
        this->fogB = globalCtx->lightCtx.unk9;

        if ((globalCtx->sceneNum == SCENE_LOST_WOODS) && (gSaveContext.sceneSetupIndex == 1)) {
            this->alpha = 0;
            this->fogN = 0;
            this->fogF = 1000;
            this->fogScale = 1.0f;
            this->actionFunc = func_80AA1704;
        } else if (globalCtx->sceneNum == SCENE_OKUJOU) {
            this->alpha = 255;
            this->fogN = 996;
            this->fogF = 1000;
            this->fogScale = 0.7f;
            this->unk_335 = 0;

            Collider_InitCylinder(globalCtx, &this->collider);

            if (gSaveContext.save.entranceIndex == 0x2C00) {
                if (gSaveContext.sceneSetupIndex == 0) {
                    if (gSaveContext.unk_3DD0[3] == 0) {
                        func_8010E9F0(3, 300);
                        XREG(80) = 200;
                        XREG(81) = 115;
                    }

                    if (gSaveContext.save.inventory.items[SLOT_OCARINA] == ITEM_NONE) {
                        sCylinderInit.base.colType = COLTYPE_WOOD;
                        this->actionFunc = func_80AA18D8;
                    } else {
                        sCylinderInit.base.colType = COLTYPE_WOOD;
                        this->actionFunc = func_80AA1998;
                    }

                } else if (gSaveContext.sceneSetupIndex == 3) {
                    this->animationId = SKULL_KID_ANIMATION_CLOCK_TOWER_ARMS_CROSSED;
                    if (gSaveContext.unk_3DD0[3] == 0) {
                        func_8010E9F0(3, 60);
                        XREG(80) = 200;
                        XREG(81) = 115;
                    }
                    this->actor.world.pos.y = 120.0f;
                    sCylinderInit.base.colType = COLTYPE_WOOD;
                    this->actionFunc = func_80AA27EC;
                } else {
                    this->animationId = SKULL_KID_ANIMATION_CLOCK_TOWER_ARMS_CROSSED;
                    this->actionFunc = func_80AA16F4;
                }
            } else {
                this->unk_33A = 1;
                this->animationId = SKULL_KID_ANIMATION_CLOCK_TOWER_ARMS_CROSSED;
                this->actor.world.pos.y = 120.0f;
                sCylinderInit.base.colType = COLTYPE_WOOD;
                this->actionFunc = func_80AA27EC;
            }

            Collider_SetCylinder(globalCtx, &this->collider, &this->actor, &sCylinderInit);
            CollisionCheck_SetInfo2(&this->actor.colChkInfo, &sDamageTable, &sColChkInfoInit);

        } else if ((globalCtx->sceneNum == SCENE_00KEIKOKU) && (gSaveContext.sceneSetupIndex == 0)) {
            if (!(globalCtx->actorCtx.unk5 & 2)) {
                Actor_MarkForDeath(&this->actor);
            }
            this->maskType = SKULL_KID_MASK_TYPE_GLOWING_EYES;
            this->alpha = 255;
            this->fogN = 996;
            this->fogF = 1000;
            this->fogScale = 0.7f;
            this->animationId = SKULL_KID_ANIMATION_DAY_THREE_TELESCOPE;
            this->actionFunc = func_80AA1714;
        } else {
            if ((globalCtx->sceneNum == SCENE_LOST_WOODS) && !Cutscene_IsPlaying(globalCtx)) {
                Actor_MarkForDeath(&this->actor);
            }
            this->maskType = SKULL_KID_MASK_TYPE_GLOWING_EYES;
            this->alpha = 255;
            this->fogN = 996;
            this->fogF = 1000;
            this->fogScale = 0.7f;
            this->actionFunc = func_80AA1704;
        }

        this->handType = SKULL_KID_HAND_TYPE_DEFAULT;
        this->fadeInState = SKULL_KID_FADE_IN_STATE_NONE;
        this->fadeOutState = SKULL_KID_FADE_OUT_STATE_NONE;
        this->fadeOutTimer = 0;
        this->alpha = this->alpha;
        this->actor.targetArrowOffset = 1100.0f;
        this->unk_334 = 99;
        ActorShape_Init(&this->actor.shape, 0.0f, ActorShadow_DrawCircle, 24.0f);
        SkelAnime_InitFlex(globalCtx, &this->skelAnime, &gSkullKidSkel, NULL, NULL, NULL, 0);
        func_80A9FE3C(this, globalCtx, &this->skelAnime, &sAnimations[this->animationId], 0);
    }

    Actor_SetScale(&this->actor, 0.01f);

    if ((globalCtx->sceneNum == SCENE_00KEIKOKU) && (gSaveContext.sceneSetupIndex == 3) &&
        (globalCtx->csCtx.currentCsIndex > 0)) {
        globalCtx->envCtx.unk_17 = 15;
        globalCtx->envCtx.unk_18 = 15;
    }
}

void DmStk_Destroy(Actor* thisx, GlobalContext* globalCtx) {
}

void func_80AA16F4(DmStk* this, GlobalContext* globalCtx) {
}

void func_80AA1704(DmStk* this, GlobalContext* globalCtx) {
}

void func_80AA1714(DmStk* this, GlobalContext* globalCtx) {
    Vec3f sp1C;

    if (!(gSaveContext.save.weekEventReg[74] & 0x20)) {
        func_80169474(globalCtx, &this->actor.world.pos, &sp1C);
        if (globalCtx->view.fovy < 25.0f) {
            if ((sp1C.x >= 70.0f) && (sp1C.x < 250.0f) && (sp1C.y >= 30.0f) && (sp1C.y < 210.0f)) {
                func_800FE484();
                this->actionFunc = func_80AA17F8;
            }
        }
    }
}

void func_80AA17F8(DmStk* this, GlobalContext* globalCtx) {
    s16 sp1E = this->actor.cutscene;
    s16 sp1C = ActorCutscene_GetAdditionalCutscene(sp1E);
    s16 sp18 = ActorCutscene_GetAdditionalCutscene(sp1C);
    s16 cutscene;

    if (gSaveContext.save.day < 3) {
        cutscene = sp1E;
    } else if ((gSaveContext.save.weekEventReg[8] & 0x40) ||
               ((CURRENT_DAY == 3) && (gSaveContext.save.time < CLOCK_TIME(6, 0)))) {
        cutscene = sp18;
    } else {
        cutscene = sp1C;
    }

    if (ActorCutscene_GetCanPlayNext(cutscene)) {
        ActorCutscene_Start(cutscene, &this->actor);
        func_800FE498();
        this->actionFunc = func_80AA1704;
    } else {
        ActorCutscene_SetIntentToPlay(cutscene);
    }
}

void func_80AA18D8(DmStk* this, GlobalContext* globalCtx) {
    if (ActorCutscene_GetCanPlayNext(9)) {
        ActorCutscene_Start(9, &this->actor);
        this->actionFunc = func_80AA192C;
    } else {
        ActorCutscene_SetIntentToPlay(9);
    }
}

void func_80AA192C(DmStk* this, GlobalContext* globalCtx) {
    if (globalCtx->csCtx.state == 0) {
        this->animationId = SKULL_KID_ANIMATION_CALL_DOWN_MOON_LOOP;
        this->handType = SKULL_KID_HAND_TYPE_HOLDING_OCARINA;
        func_80A9FE3C(this, globalCtx, &this->skelAnime, &sAnimations[this->animationId], 0);
        this->actionFunc = func_80AA2720;
    }
}

void func_80AA1998(DmStk* this, GlobalContext* globalCtx) {
    if (ActorCutscene_GetCanPlayNext(0xB)) {
        ActorCutscene_Start(0xB, &this->actor);
        this->actionFunc = func_80AA19EC;
    } else {
        ActorCutscene_SetIntentToPlay(0xB);
    }
}

void func_80AA19EC(DmStk* this, GlobalContext* globalCtx) {
    if (globalCtx->csCtx.state == 0) {
        this->animationId = SKULL_KID_ANIMATION_CLOCK_TOWER_ARMS_CROSSED;
        func_80A9FE3C(this, globalCtx, &this->skelAnime, &sAnimations[this->animationId], 0);
        this->actionFunc = func_80AA27EC;
    }
}

void func_80AA1A50(DmStk* this, GlobalContext* globalCtx) {
    if (ActorCutscene_GetCanPlayNext(0xA)) {
        Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_STALKIDS_DAMAGE);
        ActorCutscene_Start(0xA, &this->actor);
        this->actor.shape.rot.x = 0;
        this->actor.world.rot.x = this->actor.shape.rot.x;
        this->actor.shape.rot.y = this->actor.shape.rot.x;
        this->actor.world.rot.y = this->actor.shape.rot.x;
        this->actionFunc = func_80AA1AC8;
    } else {
        ActorCutscene_SetIntentToPlay(0xA);
    }
}

void func_80AA1AC8(DmStk* this, GlobalContext* globalCtx) {
    if ((globalCtx->csCtx.state != 0) && (globalCtx->csCtx.frames > 20)) {
        this->actionFunc = func_80AA27EC;
    }
}

void func_80AA1AF8(DmStk* this, GlobalContext* globalCtx) {
    Player* player = GET_PLAYER(globalCtx);
    f32 sin;

    this->unk_32A += 0x4B0;
    sin = Math_SinS(this->unk_32A) * 10.0f;
    Math_SmoothStepToF(&this->actor.world.pos.y, 160.0f + sin, 0.2f, 1.0f, 0.0001f);

    this->actor.world.rot.y = Actor_YawBetweenActors(&this->actor, &player->actor);
    this->actor.shape.rot.y = this->actor.world.rot.y;

    this->actor.world.rot.x = 0x1B58;
    this->actor.shape.rot.x = this->actor.world.rot.x;
}

void func_80AA1B9C(DmStk* this, GlobalContext* globalCtx) {
    Player* player = GET_PLAYER(globalCtx);

    func_80AA1AF8(this, globalCtx);
    this->unk_339++;
    if (this->unk_339 >= 3) {
        this->unk_339 = 0;
        if (!(player->stateFlags2 & 0x8000000)) {
            Message_StartTextbox(globalCtx, 0x2013, &this->actor);
        }
    }

    this->animationId = SKULL_KID_ANIMATION_DEFLECT_ATTACK;
    func_80A9FE3C(this, globalCtx, &this->skelAnime, &sAnimations[this->animationId], 0);
    Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_STALKIDS_DOWN_K);
    this->actionFunc = func_80AA1C64;
}

void func_80AA1C64(DmStk* this, GlobalContext* globalCtx) {
    func_80AA1AF8(this, globalCtx);
    if (Animation_OnFrame(&this->skelAnime, this->skelAnime.endFrame)) {
        this->animationId = SKULL_KID_ANIMATION_CLOCK_TOWER_ARMS_CROSSED;
        func_80A9FE3C(this, globalCtx, &this->skelAnime, &sAnimations[this->animationId], 0);
        this->actionFunc = func_80AA27EC;
    }

    if ((this->collider.base.acFlags & AC_HIT) && (this->actor.colChkInfo.damageEffect == 0xF)) {
        this->actionFunc = func_80AA1B9C;
    }
}

void func_80AA1D1C(DmStk* this, GlobalContext* globalCtx) {
    s32 pad;
    s32 temp_v0;

    if (Cutscene_CheckActorAction(globalCtx, 107)) {
        temp_v0 = Cutscene_GetActorActionIndex(globalCtx, 107);

        if (globalCtx->csCtx.frames == globalCtx->csCtx.actorActions[temp_v0]->startFrame) {
            if (this->unk_334 != globalCtx->csCtx.actorActions[temp_v0]->action) {
                this->unk_334 = globalCtx->csCtx.actorActions[temp_v0]->action;
                if (globalCtx->sceneNum == SCENE_CLOCKTOWER) {
                    this->handType = SKULL_KID_HAND_TYPE_HOLDING_FLUTE;
                } else {
                    this->handType = SKULL_KID_HAND_TYPE_DEFAULT;
                }

                switch (globalCtx->csCtx.actorActions[temp_v0]->action) {
                    case 0:
                    case 1:
                        this->animationId = SKULL_KID_ANIMATION_IDLE_1;
                        break;

                    case 2:
                        this->animationId = SKULL_KID_ANIMATION_WALK;
                        break;

                    case 3:
                        this->animationId = SKULL_KID_ANIMATION_KICK_OVER_LINK_2;
                        break;

                    case 4:
                        this->animationId = SKULL_KID_ANIMATION_KICK_OVER_LINK_1;
                        break;

                    case 6:
                        this->animationId = SKULL_KID_ANIMATION_PICK_UP_OCARINA;
                        this->handType = SKULL_KID_HAND_TYPE_HOLDING_OCARINA;
                        break;

                    case 7:
                        this->animationId = SKULL_KID_ANIMATION_PICK_UP_OCARINA_AND_START_PLAYING;
                        this->handType = SKULL_KID_HAND_TYPE_HOLDING_OCARINA;
                        break;

                    case 8:
                        this->animationId = SKULL_KID_ANIMATION_HEAD_ROCKING_IDLE;
                        break;

                    case 9:
                        this->animationId = SKULL_KID_ANIMATION_IDLE_1;
                        this->fadeInState = SKULL_KID_FADE_IN_STATE_START;
                        break;

                    case 12:
                        this->animationId = SKULL_KID_ANIMATION_HIDE_OCARINA_START;
                        this->handType = SKULL_KID_HAND_TYPE_HOLDING_OCARINA;
                        break;

                    case 13:
                        this->animationId = SKULL_KID_ANIMATION_JUMP_WHILE_HIDING_OCARINA;
                        this->handType = SKULL_KID_HAND_TYPE_HOLDING_OCARINA;
                        break;

                    case 14:
                        this->animationId = SKULL_KID_ANIMATION_HORSE_RIDE_START;
                        break;

                    case 15:
                        this->animationId = SKULL_KID_ANIMATION_HORSE_RIDE_LOOP;
                        break;

                    case 16:
                        this->animationId = SKULL_KID_ANIMATION_HORSE_RIDE_AND_ROTATE;
                        break;

                    case 17:
                        this->animationId = SKULL_KID_ANIMATION_OPENING_ARMS_CROSSED;
                        break;

                    case 18:
                        this->animationId = SKULL_KID_ANIMATION_CURSE_START;
                        break;

                    case 19:
                        this->animationId = SKULL_KID_ANIMATION_LAUGH_START;
                        break;

                    case 20:
                        this->animationId = SKULL_KID_ANIMATION_RAISE_MASK_START;
                        break;

                    case 21:
                        this->animationId = SKULL_KID_ANIMATION_LOWER_MASK;
                        break;

                    case 22:
                        this->animationId = SKULL_KID_ANIMATION_PLAY_OCARINA_WHILE_FLOATING;
                        if (gSaveContext.save.inventory.items[SLOT_OCARINA] == ITEM_NONE) {
                            this->handType = SKULL_KID_HAND_TYPE_HOLDING_OCARINA;
                        }
                        break;

                    case 23:
                        this->animationId = SKULL_KID_ANIMATION_FLOATING_TURN_AROUND;
                        this->handType = SKULL_KID_HAND_TYPE_JUGGLING_OR_DROPPING_OCARINA;
                        break;

                    case 24:
                        this->animationId = SKULL_KID_ANIMATION_CALL_DOWN_MOON_START;
                        if (gSaveContext.save.inventory.items[SLOT_OCARINA] == ITEM_NONE) {
                            this->handType = SKULL_KID_HAND_TYPE_HOLDING_OCARINA;
                        }
                        break;

                    case 25:
                        Actor_MarkForDeath(&this->actor);
                        break;

                    case 26:
                        this->animationId = SKULL_KID_ANIMATION_SMACK_FAIRY_START;
                        if (gSaveContext.save.inventory.items[SLOT_OCARINA] == ITEM_NONE) {
                            this->handType = SKULL_KID_HAND_TYPE_HOLDING_OCARINA;
                        }
                        break;

                    case 27:
                        this->animationId = SKULL_KID_ANIMATION_HIT_BY_BUBBLE;
                        if (gSaveContext.save.inventory.items[SLOT_OCARINA] == ITEM_NONE) {
                            this->handType = SKULL_KID_HAND_TYPE_HOLDING_OCARINA;
                        }
                        break;

                    case 28:
                        this->animationId = SKULL_KID_ANIMATION_DROP_OCARINA;
                        this->handType = SKULL_KID_HAND_TYPE_JUGGLING_OR_DROPPING_OCARINA;
                        break;

                    case 30:
                        this->animationId = SKULL_KID_ANIMATION_CLOCK_TOWER_ARMS_CROSSED;
                        break;

                    case 31:
                        this->animationId = SKULL_KID_ANIMATION_DEFLECT_ATTACK;
                        break;

                    case 32:
                        this->animationId = SKULL_KID_ANIMATION_SURPRISE_START;
                        break;

                    case 33:
                        this->animationId = SKULL_KID_ANIMATION_LOOKING_AROUND_FOR_GIANTS_START;
                        break;

                    case 34:
                        this->animationId = SKULL_KID_ANIMATION_HOLD_HEAD_AND_SHAKE_START;
                        break;

                    case 35:
                        this->animationId = SKULL_KID_ANIMATION_HOLD_HEAD_AND_SCREAM_START;
                        break;

                    case 36:
                        this->animationId = SKULL_KID_ANIMATION_HUDDLE_WITH_FAIRIES;
                        break;

                    case 37:
                        this->animationId = SKULL_KID_ANIMATION_SEARCH_MASK_SALESMAN;
                        break;

                    case 38:
                        this->animationId = SKULL_KID_ANIMATION_HOLD_UP_MASK_START;
                        break;

                    case 39:
                        this->animationId = SKULL_KID_ANIMATION_SHIVER;
                        break;

                    case 40:
                        this->animationId = SKULL_KID_ANIMATION_DRAW;
                        break;

                    case 41:
                        this->animationId = SKULL_KID_ANIMATION_TELESCOPE_LOOK_UP_START;
                        break;

                    case 42:
                        this->animationId = SKULL_KID_ANIMATION_DAY_THREE_TELESCOPE;
                        break;

                    case 43:
                        this->animationId = SKULL_KID_ANIMATION_DAY_THREE_TELESCOPE_LOOK_UP;
                        break;

                    case 44:
                        this->animationId = SKULL_KID_ANIMATION_SPANK;
                        break;

                    case 45:
                        this->animationId = SKULL_KID_ANIMATION_HIP_SHAKE_AND_JUMP;
                        this->fadeOutState = SKULL_KID_FADE_OUT_STATE_FADING_OUT;
                        break;

                    case 46:
                        this->handType = SKULL_KID_HAND_TYPE_HOLDING_FLUTE;
                        this->animationId = SKULL_KID_ANIMATION_PLAY_FLUTE;
                        break;

                    case 47:
                        this->animationId = SKULL_KID_ANIMATION_CARTWHEEL;
                        break;

                    case 48:
                        this->animationId = SKULL_KID_ANIMATION_CARTWHEEL;
                        break;

                    case 49:
                        this->animationId = SKULL_KID_ANIMATION_LOOK_UP_AT_GIANTS;
                        break;

                    case 50:
                        this->animationId = SKULL_KID_ANIMATION_ASHAMED_START;
                        break;

                    case 51:
                        this->animationId = SKULL_KID_ANIMATION_LOOK_LEFT_START;
                        break;

                    case 52:
                        this->animationId = SKULL_KID_ANIMATION_SNIFF;
                        break;

                    case 53:
                        this->animationId = SKULL_KID_ANIMATION_CARTWHEEL;
                        break;

                    case 54:
                        this->animationId = SKULL_KID_ANIMATION_DANGLE_FROM_MASK_START_1;
                        break;

                    case 55:
                        this->animationId = SKULL_KID_ANIMATION_DANGLE_FROM_MASK_START_2;
                        break;

                    case 56:
                        this->animationId = SKULL_KID_ANIMATION_DROPPED_FROM_MASK;
                        break;

                    case 57:
                        this->animationId = SKULL_KID_ANIMATION_LOOK_UP_AT_GIANTS;
                        break;

                    case 58:
                        this->animationId = SKULL_KID_ANIMATION_ASHAMED_START;
                        break;

                    case 59:
                        this->animationId = SKULL_KID_ANIMATION_LOOK_LEFT_START;
                        break;

                    case 60:
                        this->animationId = SKULL_KID_ANIMATION_SNIFF;
                        break;

                    case 5:
                    case 10:
                        break;

                    default:
                        this->animationId = SKULL_KID_ANIMATION_HEAD_ROCKING_IDLE;
                        break;
                }

                func_80A9FE3C(this, globalCtx, &this->skelAnime, &sAnimations[this->animationId], 0);
            }
        }

        Cutscene_ActorTranslateAndYaw(&this->actor, globalCtx, temp_v0);
    } else {
        this->unk_334 = 99;
    }

    if (this->fadeInState == SKULL_KID_FADE_IN_STATE_START) {
        Math_SmoothStepToF(&this->fogScale, 0.7f, 0.1f, 0.007f, 0.005f);
        if (this->fogScale < 0.71f) {
            this->fogScale = 0.7f;
            this->fogN = 800;
            this->fadeInState++;
        }
        this->fogR = globalCtx->lightCtx.unk7 * this->fogScale;
        this->fogG = globalCtx->lightCtx.unk8 * this->fogScale;
        this->fogB = globalCtx->lightCtx.unk9 * this->fogScale;

    } else if (this->fadeInState == SKULL_KID_FADE_IN_STATE_INCREASE_FOG_N) {
        if (this->fogN < 996) {
            this->fogN += 10;
        }

        if (this->fogN > 996) {
            this->fadeInState++;
            this->fogN = 996;
        }
    } else if (this->fadeInState == SKULL_KID_FADE_IN_STATE_INCREASE_ALPHA) {
        if (this->alpha < 128) {
            this->alpha += 3;
        }

        if (this->alpha < 255) {
            this->alpha += 20;
        } else {
            this->alpha = 255;
            this->fadeInState = SKULL_KID_FADE_IN_STATE_NONE;
        }
    }

    if (this->fadeOutState == SKULL_KID_FADE_OUT_STATE_FADING_OUT) {
        if (this->fadeOutTimer > 40) {
            this->maskType = SKULL_KID_MASK_TYPE_FADING_OUT;
        }

        this->fadeOutTimer++;
        if (this->fadeOutTimer >= 44) {
            this->alpha -= 35;
            if (this->alpha < 0) {
                this->alpha = 0;
                this->fadeOutState = SKULL_KID_FADE_OUT_STATE_NONE;
                gSaveContext.save.weekEventReg[12] |= 4;
                if (!(globalCtx->actorCtx.unk5 & 2)) {
                    Actor_MarkForDeath(&this->actor);
                } else {
                    this->shouldDraw = false;
                }
            }
        }
    }

    if (Animation_OnFrame(&this->skelAnime, this->skelAnime.endFrame)) {
        switch (this->animationId) {
            case SKULL_KID_ANIMATION_LOOK_AROUND:
            case SKULL_KID_ANIMATION_CURSE_START:
            case SKULL_KID_ANIMATION_LAUGH_START:
            case SKULL_KID_ANIMATION_HIDE_OCARINA_START:
            case SKULL_KID_ANIMATION_PICK_UP_OCARINA_AND_START_PLAYING:
            case SKULL_KID_ANIMATION_PICK_UP_OCARINA:
            case SKULL_KID_ANIMATION_KICK_OVER_LINK_1:
            case SKULL_KID_ANIMATION_KICK_OVER_LINK_2:
            case SKULL_KID_ANIMATION_HORSE_RIDE_START:
            case SKULL_KID_ANIMATION_RAISE_MASK_START:
            case SKULL_KID_ANIMATION_FLOATING_TURN_AROUND:
            case SKULL_KID_ANIMATION_CALL_DOWN_MOON_START:
            case SKULL_KID_ANIMATION_SMACK_FAIRY_START:
            case SKULL_KID_ANIMATION_TELESCOPE_LOOK_UP_START:
            case SKULL_KID_ANIMATION_SURPRISE_START:
            case SKULL_KID_ANIMATION_LOOKING_AROUND_FOR_GIANTS_START:
            case SKULL_KID_ANIMATION_HOLD_HEAD_AND_SHAKE_START:
            case SKULL_KID_ANIMATION_HOLD_HEAD_AND_SCREAM_START:
            case SKULL_KID_ANIMATION_HOLD_UP_MASK_START:
            case SKULL_KID_ANIMATION_DANGLE_FROM_MASK_START_2:
            case SKULL_KID_ANIMATION_ASHAMED_START:
            case SKULL_KID_ANIMATION_LOOK_LEFT_START:
            case SKULL_KID_ANIMATION_SNIFF:
                this->animationId++;
                func_80A9FE3C(this, globalCtx, &this->skelAnime, &sAnimations[this->animationId], 0);
                break;

            case SKULL_KID_ANIMATION_LOWER_MASK:
                this->animationId = SKULL_KID_ANIMATION_IDLE_1;
                this->maskType = SKULL_KID_MASK_TYPE_NORMAL;
                this->handType = SKULL_KID_HAND_TYPE_DEFAULT;
                func_80A9FE3C(this, globalCtx, &this->skelAnime, &sAnimations[this->animationId], 0);
                break;
        }
    }

    if (((this->animationId == SKULL_KID_ANIMATION_RAISE_MASK_START) && (this->skelAnime.curFrame >= 16.0f)) ||
        (this->animationId == SKULL_KID_ANIMATION_RAISE_MASK_LOOP) ||
        (this->animationId == SKULL_KID_ANIMATION_LOWER_MASK)) {
        this->maskType = SKULL_KID_MASK_TYPE_RAISED;
        this->handType = SKULL_KID_HAND_TYPE_HOLDING_MAJORAS_MASK;
    } else if (((this->animationId >= SKULL_KID_ANIMATION_HUDDLE_WITH_FAIRIES) &&
                (this->animationId <= SKULL_KID_ANIMATION_DRAW)) ||
               ((this->animationId >= SKULL_KID_ANIMATION_PLAY_FLUTE) &&
                (this->animationId <= SKULL_KID_ANIMATION_CARTWHEEL)) ||
               ((globalCtx->sceneNum == SCENE_00KEIKOKU) && (gSaveContext.sceneSetupIndex == 7))) {
        this->maskType = SKULL_KID_MASK_TYPE_NO_MASK;
        if ((this->animationId == SKULL_KID_ANIMATION_HOLD_UP_MASK_START) ||
            (this->animationId == SKULL_KID_ANIMATION_HOLD_UP_MASK_LOOP)) {
            this->handType = SKULL_KID_HAND_TYPE_HOLDING_MAJORAS_MASK_AND_FLUTE;
        }
    }

    if (this->animationId == SKULL_KID_ANIMATION_DROPPED_FROM_MASK) {
        this->maskType = SKULL_KID_MASK_TYPE_NO_MASK;
    }
}

void func_80AA26CC(DmStk* this, GlobalContext* globalCtx) {
    s32 pad;

    Collider_UpdateCylinder(&this->actor, &this->collider);
    CollisionCheck_SetAC(globalCtx, &globalCtx->colChkCtx, &this->collider.base);
    CollisionCheck_SetOC(globalCtx, &globalCtx->colChkCtx, &this->collider.base);
}

void func_80AA2720(DmStk* this, GlobalContext* globalCtx) {
    Player* player = GET_PLAYER(globalCtx);

    if (globalCtx->csCtx.state == 0) {
        func_80AA1AF8(this, globalCtx);
        this->actor.flags |= ACTOR_FLAG_1;
        this->unk_328++;
        if (this->unk_328 > 800) {
            this->unk_328 = 0;
            if (!(player->stateFlags2 & 0x8000000)) {
                Message_StartTextbox(globalCtx, 0x2014, &this->actor);
            }
        }
        if ((this->collider.base.acFlags & AC_HIT) && (this->actor.colChkInfo.damageEffect == 0xF)) {
            this->unk_335 = 1;
            this->actionFunc = func_80AA1A50;
        }
    }
}

void func_80AA27EC(DmStk* this, GlobalContext* globalCtx) {
    if (globalCtx->csCtx.state == 0) {
        func_80AA1AF8(this, globalCtx);
        this->actor.flags |= ACTOR_FLAG_1;

        if (this->animationId == SKULL_KID_ANIMATION_CALL_DOWN_MOON_LOOP) {
            this->actor.targetArrowOffset = 3100.0f;
        } else {
            this->actor.targetArrowOffset = 200.0f;
        }

        if ((this->collider.base.acFlags & AC_HIT) && (this->actor.colChkInfo.damageEffect == 0xF)) {
            this->unk_335 = 1;
            this->actionFunc = func_80AA1B9C;
        }
    }
}

void DmStk_Update(Actor* thisx, GlobalContext* globalCtx) {
    DmStk* this = THIS;

    if (this->actor.params != 1) {
        if (this->animationId == SKULL_KID_ANIMATION_CALL_DOWN_MOON_LOOP) {
            Actor_SetFocus(&this->actor, 40.0f);
        } else {
            Actor_SetFocus(&this->actor, 6.0f);
        }

        func_80A9FDB0(this, globalCtx);

        if (this->animationId != SKULL_KID_ANIMATION_DANGLE_FROM_MASK_START_1) {
            SkelAnime_Update(&this->skelAnime);
        }

        this->alpha = this->alpha;

        this->actionFunc(this, globalCtx);

        if (globalCtx->sceneNum == SCENE_OKUJOU) {
            func_80AA26CC(this, globalCtx);
        }

        func_80AA1D1C(this, globalCtx);
        func_80AA0E90(this, globalCtx);

        switch (this->unk_33A) {
            case 1:
                if (func_800B8718(&this->actor, &globalCtx->state)) {
                    this->unk_33A = 2;
                } else {
                    func_800B874C(&this->actor, globalCtx, this->actor.xzDistToPlayer,
                                  fabsf(this->actor.playerHeightRel));
                }
                break;

            case 2:
                if (ActorCutscene_GetCanPlayNext(0x10)) {
                    this->unk_33A = 3;
                    ActorCutscene_Start(0x10, &this->actor);
                    this->actionFunc = func_80AA27EC;
                } else {
                    ActorCutscene_SetIntentToPlay(0x10);
                }
                break;

            case 3:
                if (globalCtx->csCtx.state == 0) {
                    this->unk_33A = 4;
                }
                break;
        }

        if ((globalCtx->actorCtx.unk5 & 2) && (globalCtx->msgCtx.msgMode != 0) &&
            (globalCtx->msgCtx.currentTextId == 0x5E6) && !FrameAdvance_IsEnabled(&globalCtx->state) &&
            (globalCtx->sceneLoadFlag == 0) && (ActorCutscene_GetCurrentIndex() == -1) &&
            (globalCtx->csCtx.state == 0)) {
            gSaveContext.save.time = ((void)0, gSaveContext.save.time) + (u16)REG(15);
            if (REG(15) != 0) {
                gSaveContext.save.time = ((void)0, gSaveContext.save.time) + (u16)((void)0, gSaveContext.save.daySpeed);
            }
        }
    }

    if ((globalCtx->sceneNum == SCENE_00KEIKOKU) && (gSaveContext.sceneSetupIndex == 3) &&
        (globalCtx->csCtx.currentCsIndex > 0)) {
        globalCtx->envCtx.unk_17 = 15;
        globalCtx->envCtx.unk_18 = 15;
    }
}

s32 DmStk_OverrideLimbDraw(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3s* rot, Actor* thisx) {
    DmStk* this = THIS;

    if (limbIndex == SKULL_KID_LIMB_RIGHT_HAND) {
        if ((this->handType == SKULL_KID_HAND_TYPE_HOLDING_LINK_MASK_AND_FLUTE) ||
            (this->handType == SKULL_KID_HAND_TYPE_HOLDING_LINK_MASK) ||
            (this->handType == SKULL_KID_HAND_TYPE_HOLDING_OCARINA)) {
            *dList = NULL;
        }
    } else if (limbIndex == SKULL_KID_LIMB_LEFT_HAND) {
        switch (this->handType) {
            case SKULL_KID_HAND_TYPE_HOLDING_LINK_MASK:
            case SKULL_KID_HAND_TYPE_HOLDING_MAJORAS_MASK:
            case SKULL_KID_HAND_TYPE_HOLDING_OCARINA:
            case SKULL_KID_HAND_TYPE_JUGGLING_OR_DROPPING_OCARINA:
            case SKULL_KID_HAND_TYPE_HOLDING_FLUTE:
                *dList = NULL;
                break;

            case SKULL_KID_HAND_TYPE_DEFAULT:
                if (this->alpha == 255) {
                    *dList = NULL;
                }
                break;
        }
    } else if (limbIndex == SKULL_KID_LIMB_HEAD) {
        *dList = NULL;
    }

    return false;
}

void DmStk_PostLimbDraw2(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3s* rot, Actor* thisx, Gfx** gfx) {
    s32 pad;
    s32 pad2;
    DmStk* this = THIS;

    if (limbIndex == SKULL_KID_LIMB_HEAD) {
        Matrix_MultZero(&this->headPos);

        OPEN_DISPS(globalCtx->state.gfxCtx);

        gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(globalCtx->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);

        if ((this->animationId == SKULL_KID_ANIMATION_LOOK_LEFT_LOOP) ||
            (this->animationId == SKULL_KID_ANIMATION_LAUGH_LOOP) ||
            (this->animationId == SKULL_KID_ANIMATION_LAUGH_AFTER_SNIFF)) {
            gSPDisplayList(POLY_OPA_DISP++, gSkullKidHappyHeadDL);
            gSPDisplayList(POLY_OPA_DISP++, gSkullKidHappyEyesDL);
        } else {
            gSPDisplayList(POLY_OPA_DISP++, gSkullKidExpressionlessHeadDL);
            gSPDisplayList(POLY_OPA_DISP++, gSkullKidExpressionlessEyesDL);
        }

        switch (this->maskType) {
            case SKULL_KID_MASK_TYPE_NO_MASK:
                break;

            case SKULL_KID_MASK_TYPE_NORMAL:
                if ((globalCtx->sceneNum == SCENE_LOST_WOODS) && (gSaveContext.sceneSetupIndex == 1) &&
                    (globalCtx->csCtx.frames < 1400)) {
                    if (this->fogN == this->fogF) {
                        this->fogF = this->fogN;
                    }
                    POLY_OPA_DISP = Gfx_SetFog(POLY_OPA_DISP, this->fogR, this->fogG, this->fogB, this->fogA,
                                               this->fogN, this->fogF);
                    gSPDisplayList(POLY_OPA_DISP++, gSkullKidMajorasMask1DL);
                    POLY_OPA_DISP = func_801660B8(globalCtx, POLY_OPA_DISP);
                } else {
                    gSPDisplayList(POLY_OPA_DISP++, gSkullKidMajorasMask1DL);
                }
                break;

            case SKULL_KID_MASK_TYPE_GLOWING_EYES:
                gSPDisplayList(POLY_OPA_DISP++, gSkullKidMajorasMask1DL);
                gSPDisplayList(POLY_OPA_DISP++, gSkullKidMajorasMaskEyesDL);

                if (Cutscene_CheckActorAction(globalCtx, 513) &&
                    (globalCtx->csCtx.actorActions[Cutscene_GetActorActionIndex(globalCtx, 513)]->action == 2) &&
                    (this->objectStk2ObjectIndex >= 0)) {
                    Matrix_Push();
                    Matrix_Scale(2.0f, 2.0f, 2.0f, MTXMODE_APPLY);
                    gSegments[6] =
                        PHYSICAL_TO_VIRTUAL(globalCtx->objectCtx.status[this->objectStk2ObjectIndex].segment);

                    gSPSegment(POLY_OPA_DISP++, 0x06, globalCtx->objectCtx.status[this->objectStk2ObjectIndex].segment);

                    AnimatedMat_Draw(globalCtx, Lib_SegmentedToVirtual(object_stk2_Matanimheader_008658));
                    Gfx_DrawDListOpa(globalCtx, object_stk2_DL_007840);
                    gSegments[6] = PHYSICAL_TO_VIRTUAL(globalCtx->objectCtx.status[this->objectStkObjectIndex].segment);

                    gSPSegment(POLY_OPA_DISP++, 0x06, globalCtx->objectCtx.status[this->objectStkObjectIndex].segment);

                    Matrix_Pop();
                }
                break;
        }

        CLOSE_DISPS(globalCtx->state.gfxCtx);

    } else if (limbIndex == SKULL_KID_LIMB_RIGHT_HAND) {

        OPEN_DISPS(globalCtx->state.gfxCtx);

        if (this->handType != SKULL_KID_HAND_TYPE_HOLDING_MAJORAS_MASK_AND_FLUTE) {
            gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(globalCtx->state.gfxCtx),
                      G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        }

        switch (this->handType) {
            case SKULL_KID_HAND_TYPE_HOLDING_LINK_MASK_AND_FLUTE:
                gSPDisplayList(POLY_OPA_DISP++, object_stk_DL_009AC0);
                gSPDisplayList(POLY_OPA_DISP++, gSkullKidLinkMask2DL);
                break;

            case SKULL_KID_HAND_TYPE_HOLDING_LINK_MASK:
                gSPDisplayList(POLY_OPA_DISP++, object_stk_DL_009710);
                gSPDisplayList(POLY_OPA_DISP++, gSkullKidLinkMask3DL);
                break;

            case SKULL_KID_HAND_TYPE_HOLDING_OCARINA:
                gSPDisplayList(POLY_OPA_DISP++, object_stk_DL_009DA0);

                if ((globalCtx->sceneNum == SCENE_LOST_WOODS) && (gSaveContext.sceneSetupIndex == 1)) {
                    gSPDisplayList(POLY_OPA_DISP++, gSkullKidOcarinaOfTimeDL);
                }
                break;

            case SKULL_KID_HAND_TYPE_HOLDING_MAJORAS_MASK_AND_FLUTE:
                Matrix_Translate(-20.0f, -660.0f, 860.0f, MTXMODE_APPLY);
                Matrix_RotateYS(0x6142, MTXMODE_APPLY);
                Matrix_RotateXS(-0x1988, MTXMODE_APPLY);

                gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(globalCtx->state.gfxCtx),
                          G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
                gSPDisplayList(POLY_OPA_DISP++, gSkullKidMajorasMask1DL);
                break;
        }

        CLOSE_DISPS(globalCtx->state.gfxCtx);

    } else if (limbIndex == SKULL_KID_LIMB_LEFT_HAND) {

        OPEN_DISPS(globalCtx->state.gfxCtx);

        gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(globalCtx->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);

        switch (this->handType) {
            case SKULL_KID_HAND_TYPE_HOLDING_LINK_MASK_AND_FLUTE:
                break;

            case SKULL_KID_HAND_TYPE_HOLDING_LINK_MASK:
                gSPDisplayList(POLY_OPA_DISP++, object_stk_DL_0084C0);
                break;

            case SKULL_KID_HAND_TYPE_HOLDING_MAJORAS_MASK:
                gSPDisplayList(POLY_OPA_DISP++, object_stk_DL_0090C0);
                gSPDisplayList(POLY_OPA_DISP++, gSkullKidMajorasMask2DL);
                break;

            case SKULL_KID_HAND_TYPE_HOLDING_OCARINA:
                if ((globalCtx->sceneNum != SCENE_LOST_WOODS) || (gSaveContext.sceneSetupIndex != 1)) {
                    gSPDisplayList(POLY_OPA_DISP++, gSkullKidOcarinaOfTimeDL);
                }
                gSPDisplayList(POLY_OPA_DISP++, object_stk_DL_0090C0);
                break;

            case SKULL_KID_HAND_TYPE_JUGGLING_OR_DROPPING_OCARINA:
                gSPDisplayList(POLY_OPA_DISP++, object_stk_DL_0090C0);
                break;

            case SKULL_KID_HAND_TYPE_HOLDING_FLUTE:
                gSPDisplayList(POLY_OPA_DISP++, object_stk_DL_008A80);
                gSPDisplayList(POLY_OPA_DISP++, gSkullKidFluteDL);
                break;

            case SKULL_KID_HAND_TYPE_DEFAULT:
                if (this->alpha == 255) {
                    gSPDisplayList(POLY_OPA_DISP++, object_stk_DL_0087B0);
                }
                break;
        }

        CLOSE_DISPS(globalCtx->state.gfxCtx);
    }
}

void DmStk_PostLimbDraw(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3s* rot, Actor* thisx) {
    DmStk* this = THIS;

    DmStk_PostLimbDraw2(globalCtx, limbIndex, dList, rot, &this->actor, NULL);
}

void DmStk_Draw(Actor* thisx, GlobalContext* globalCtx) {
    DmStk* this = THIS;

    if (this->shouldDraw) {
        if (this->actor.params == 1) {
            Gfx_DrawDListOpa(globalCtx, gSkullKidMajorasMask1DL);
            return;
        }

        gSegments[6] = PHYSICAL_TO_VIRTUAL(globalCtx->objectCtx.status[this->objectStkObjectIndex].segment);

        OPEN_DISPS(globalCtx->state.gfxCtx);

        this->alpha = this->alpha;
        func_8012C28C(globalCtx->state.gfxCtx);

        if (this->alpha < 255) {
            func_8012C2DC(globalCtx->state.gfxCtx);
            Scene_SetRenderModeXlu(globalCtx, 1, 2);

            gDPPipeSync(POLY_XLU_DISP++);
            gDPSetEnvColor(POLY_XLU_DISP++, 0, 0, 0, this->alpha);

            POLY_XLU_DISP =
                SkelAnime_DrawFlex(globalCtx, this->skelAnime.skeleton, this->skelAnime.jointTable,
                                   this->skelAnime.dListCount, NULL, DmStk_PostLimbDraw2, &this->actor, POLY_XLU_DISP);
        } else {
            Scene_SetRenderModeXlu(globalCtx, 0, 1);

            gDPPipeSync(POLY_OPA_DISP++);
            gDPSetEnvColor(POLY_OPA_DISP++, 255, 255, 255, 255);

            SkelAnime_DrawFlexOpa(globalCtx, this->skelAnime.skeleton, this->skelAnime.jointTable,
                                  this->skelAnime.dListCount, DmStk_OverrideLimbDraw, DmStk_PostLimbDraw, &this->actor);
        }

        CLOSE_DISPS(globalCtx->state.gfxCtx);
    }
}
