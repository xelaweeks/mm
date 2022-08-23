/*
 * File: z_en_wiz.c
 * Overlay: ovl_En_Wiz
 * Description: Wizzrobe
 */

#include "z_en_wiz.h"
#include "objects/gameplay_keep/gameplay_keep.h"
#include "overlays/actors/ovl_En_Wiz_Brock/z_en_wiz_brock.h"

#define FLAGS                                                                                            \
    (ACTOR_FLAG_1 | ACTOR_FLAG_4 | ACTOR_FLAG_10 | ACTOR_FLAG_20 | ACTOR_FLAG_1000 | ACTOR_FLAG_100000 | \
     ACTOR_FLAG_8000000 | ACTOR_FLAG_80000000)

#define THIS ((EnWiz*)thisx)

void EnWiz_Init(Actor* thisx, PlayState* play);
void EnWiz_Destroy(Actor* thisx, PlayState* play);
void EnWiz_Update(Actor* thisx, PlayState* play);
void EnWiz_Draw(Actor* thisx, PlayState* play);

void EnWiz_StartIntroCutscene(EnWiz* this, PlayState* play);
void EnWiz_SetupAppear(EnWiz* this, PlayState* play);
void EnWiz_Appear(EnWiz* this, PlayState* play);
void EnWiz_SetupDance(EnWiz* this);
void EnWiz_Dance(EnWiz* this, PlayState* play);
void EnWiz_SetupSecondPhaseCutscene(EnWiz* this, PlayState* play);
void EnWiz_SecondPhaseCutscene(EnWiz* this, PlayState* play);
void EnWiz_SetupWindUp(EnWiz* this);
void EnWiz_WindUp(EnWiz* this, PlayState* play);
void EnWiz_SetupAttack(EnWiz* this);
void EnWiz_Attack(EnWiz* this, PlayState* play);
void EnWiz_SetupDisappear(EnWiz* this);
void EnWiz_Disappear(EnWiz* this, PlayState* play);
void EnWiz_Damaged(EnWiz* this, PlayState* play);
void EnWiz_SetupDead(EnWiz* this);
void EnWiz_Dead(EnWiz* this, PlayState* play);

typedef enum {
    /* 1 */ EN_WIZ_ACTION_APPEAR = 1,
    /* 2 */ EN_WIZ_ACTION_RUN_BETWEEN_PLATFORMS,
    /* 3 */ EN_WIZ_ACTION_DISAPPEAR,
    /* 4 */ EN_WIZ_ACTION_DAMAGED,
    /* 5 */ EN_WIZ_ACTION_DEAD,
    /* 6 */ EN_WIZ_ACTION_BURST_INTO_FLAMES,
    /* 7 */ EN_WIZ_ACTION_RUN_IN_CIRCLES,
    /* 8 */ EN_WIZ_ACTION_ATTACK,
    /* 9 */ EN_WIZ_ACTION_DANCE,
} EnWizAction;

typedef enum {
    /* 0 */ EN_WIZ_INTRO_CS_NOT_STARTED,
    /* 1 */ EN_WIZ_INTRO_CS_CAMERA_MOVE_TO_PLATFORM,
    /* 2 */ EN_WIZ_INTRO_CS_APPEAR,
    /* 3 */ EN_WIZ_INTRO_CS_CAMERA_SPIN_TO_FACE_WIZZROBE,
    /* 4 */ EN_WIZ_INTRO_CS_WAIT_BEFORE_RUN,
    /* 5 */ EN_WIZ_INTRO_CS_RUN_IN_CIRCLES,
    /* 6 */ EN_WIZ_INTRO_CS_DISAPPEAR,
    /* 7 */ EN_WIZ_INTRO_CS_END
} EnWizIntroCutsceneState;

typedef enum {
    /* 0 */ EN_WIZ_FIGHT_STATE_FIRST_PHASE,
    /* 1 */ EN_WIZ_FIGHT_STATE_SECOND_PHASE_CUTSCENE,
    /* 2 */ EN_WIZ_FIGHT_STATE_SECOND_PHASE,
    /* 3 */ EN_WIZ_FIGHT_STATE_SECOND_PHASE_WITH_RUNNING_GHOSTS,
} EnWizFightState;

const ActorInit En_Wiz_InitVars = {
    ACTOR_EN_WIZ,
    ACTORCAT_ENEMY,
    FLAGS,
    OBJECT_WIZ,
    sizeof(EnWiz),
    (ActorFunc)EnWiz_Init,
    (ActorFunc)EnWiz_Destroy,
    (ActorFunc)EnWiz_Update,
    (ActorFunc)EnWiz_Draw,
};

static ColliderJntSphElementInit sJntSphElementsInit[10] = {
    {
        {
            ELEMTYPE_UNK0,
            { 0xF7CFFFFF, 0x00, 0x00 },
            { 0x01000202, 0x00, 0x00 },
            TOUCH_NONE | TOUCH_SFX_NORMAL,
            BUMP_NONE,
            OCELEM_NONE,
        },
        { 1, { { 0, 0, 0 }, 0 }, 1 },
    },
    {
        {
            ELEMTYPE_UNK0,
            { 0xF7CFFFFF, 0x00, 0x00 },
            { 0xF7CFFFFF, 0x00, 0x00 },
            TOUCH_NONE | TOUCH_SFX_NORMAL,
            BUMP_ON,
            OCELEM_NONE,
        },
        { 1, { { 0, 0, 0 }, 0 }, 0 },
    },
    {
        {
            ELEMTYPE_UNK0,
            { 0xF7CFFFFF, 0x00, 0x00 },
            { 0xF7CFFFFF, 0x00, 0x00 },
            TOUCH_NONE | TOUCH_SFX_NORMAL,
            BUMP_ON,
            OCELEM_NONE,
        },
        { 1, { { 0, 0, 0 }, 0 }, 0 },
    },
    {
        {
            ELEMTYPE_UNK0,
            { 0xF7CFFFFF, 0x00, 0x00 },
            { 0xF7CFFFFF, 0x00, 0x00 },
            TOUCH_NONE | TOUCH_SFX_NORMAL,
            BUMP_ON,
            OCELEM_NONE,
        },
        { 1, { { 0, 0, 0 }, 0 }, 0 },
    },
    {
        {
            ELEMTYPE_UNK0,
            { 0xF7CFFFFF, 0x00, 0x00 },
            { 0xF7CFFFFF, 0x00, 0x00 },
            TOUCH_NONE | TOUCH_SFX_NORMAL,
            BUMP_ON,
            OCELEM_NONE,
        },
        { 1, { { 0, 0, 0 }, 0 }, 0 },
    },
    {
        {
            ELEMTYPE_UNK0,
            { 0xF7CFFFFF, 0x00, 0x00 },
            { 0xF7CFFFFF, 0x00, 0x00 },
            TOUCH_NONE | TOUCH_SFX_NORMAL,
            BUMP_ON,
            OCELEM_NONE,
        },
        { 1, { { 0, 0, 0 }, 0 }, 0 },
    },
    {
        {
            ELEMTYPE_UNK0,
            { 0xF7CFFFFF, 0x00, 0x00 },
            { 0xF7CFFFFF, 0x00, 0x00 },
            TOUCH_NONE | TOUCH_SFX_NORMAL,
            BUMP_ON,
            OCELEM_NONE,
        },
        { 1, { { 0, 0, 0 }, 0 }, 0 },
    },
    {
        {
            ELEMTYPE_UNK0,
            { 0xF7CFFFFF, 0x00, 0x00 },
            { 0xF7CFFFFF, 0x00, 0x00 },
            TOUCH_NONE | TOUCH_SFX_NORMAL,
            BUMP_ON,
            OCELEM_NONE,
        },
        { 1, { { 0, 0, 0 }, 0 }, 0 },
    },
    {
        {
            ELEMTYPE_UNK0,
            { 0xF7CFFFFF, 0x00, 0x00 },
            { 0xF7CFFFFF, 0x00, 0x00 },
            TOUCH_NONE | TOUCH_SFX_NORMAL,
            BUMP_ON,
            OCELEM_NONE,
        },
        { 1, { { 0, 0, 0 }, 0 }, 0 },
    },
    {
        {
            ELEMTYPE_UNK0,
            { 0xF7CFFFFF, 0x00, 0x00 },
            { 0xF7CFFFFF, 0x00, 0x00 },
            TOUCH_NONE | TOUCH_SFX_NORMAL,
            BUMP_ON,
            OCELEM_NONE,
        },
        { 1, { { 0, 0, 0 }, 0 }, 0 },
    },
};

static ColliderJntSphInit sJntSphInit = {
    {
        COLTYPE_HIT2,
        AT_NONE,
        AC_ON | AC_TYPE_PLAYER,
        OC1_NONE,
        OC2_TYPE_1,
        COLSHAPE_JNTSPH,
    },
    ARRAY_COUNT(sJntSphElementsInit),
    sJntSphElementsInit,
};

static ColliderCylinderInit sCylinderInit = {
    {
        COLTYPE_NONE,
        AT_NONE,
        AC_ON | AC_TYPE_PLAYER,
        OC1_ON | OC1_TYPE_ALL,
        OC2_TYPE_1,
        COLSHAPE_CYLINDER,
    },
    {
        ELEMTYPE_UNK1,
        { 0xF7CFFFFF, 0x08, 0x04 },
        { 0xF7CFFFFF, 0x00, 0x00 },
        TOUCH_NONE | TOUCH_SFX_NORMAL,
        BUMP_ON,
        OCELEM_ON,
    },
    { 35, 130, 0, { 0, 0, 0 } },
};

typedef enum {
    /* 0x0 */ EN_WIZ_DMGEFF_NO_DAMAGE,    // Deals no damage
    /* 0x1 */ EN_WIZ_DMGEFF_UNK1,         // Deals no damage. Was probably originally intended for stunning.
    /* 0x2 */ EN_WIZ_DMGEFF_FIRE,         // Damages and sets Ice Wizzrobes on fire
    /* 0x3 */ EN_WIZ_DMGEFF_FREEZE,       // Damages and surrounds Fire Wizzrobes with ice
    /* 0x4 */ EN_WIZ_DMGEFF_LIGHT_ORB,    // Damages and surrounds the Wizzrobe with light orbs
    /* 0xF */ EN_WIZ_DMGEFF_DAMAGE = 0xF, // Deals regular damage
} EnWizDamageEffect;

static DamageTable sFireWizzrobeDamageTable = {
    /* Deku Nut       */ DMG_ENTRY(0, EN_WIZ_DMGEFF_UNK1),
    /* Deku Stick     */ DMG_ENTRY(1, EN_WIZ_DMGEFF_DAMAGE),
    /* Horse trample  */ DMG_ENTRY(0, EN_WIZ_DMGEFF_NO_DAMAGE),
    /* Explosives     */ DMG_ENTRY(1, EN_WIZ_DMGEFF_DAMAGE),
    /* Zora boomerang */ DMG_ENTRY(1, EN_WIZ_DMGEFF_DAMAGE),
    /* Normal arrow   */ DMG_ENTRY(1, EN_WIZ_DMGEFF_DAMAGE),
    /* UNK_DMG_D_06   */ DMG_ENTRY(0, EN_WIZ_DMGEFF_NO_DAMAGE),
    /* Hookshot       */ DMG_ENTRY(1, EN_WIZ_DMGEFF_DAMAGE),
    /* Goron punch    */ DMG_ENTRY(1, EN_WIZ_DMGEFF_DAMAGE),
    /* Sword          */ DMG_ENTRY(1, EN_WIZ_DMGEFF_DAMAGE),
    /* Goron pound    */ DMG_ENTRY(3, EN_WIZ_DMGEFF_DAMAGE),
    /* Fire arrow     */ DMG_ENTRY(1, EN_WIZ_DMGEFF_FIRE),
    /* Ice arrow      */ DMG_ENTRY(2, EN_WIZ_DMGEFF_FREEZE),
    /* Light arrow    */ DMG_ENTRY(2, EN_WIZ_DMGEFF_LIGHT_ORB),
    /* Goron spikes   */ DMG_ENTRY(0, EN_WIZ_DMGEFF_NO_DAMAGE),
    /* Deku spin      */ DMG_ENTRY(1, EN_WIZ_DMGEFF_DAMAGE),
    /* Deku bubble    */ DMG_ENTRY(1, EN_WIZ_DMGEFF_DAMAGE),
    /* Deku launch    */ DMG_ENTRY(0, EN_WIZ_DMGEFF_NO_DAMAGE),
    /* UNK_DMG_0x12   */ DMG_ENTRY(0, EN_WIZ_DMGEFF_UNK1),
    /* Zora barrier   */ DMG_ENTRY(0, EN_WIZ_DMGEFF_NO_DAMAGE),
    /* Normal shield  */ DMG_ENTRY(0, EN_WIZ_DMGEFF_NO_DAMAGE),
    /* Light ray      */ DMG_ENTRY(0, EN_WIZ_DMGEFF_NO_DAMAGE),
    /* Thrown object  */ DMG_ENTRY(1, EN_WIZ_DMGEFF_DAMAGE),
    /* Zora punch     */ DMG_ENTRY(1, EN_WIZ_DMGEFF_DAMAGE),
    /* Spin attack    */ DMG_ENTRY(1, EN_WIZ_DMGEFF_DAMAGE),
    /* Sword beam     */ DMG_ENTRY(0, EN_WIZ_DMGEFF_NO_DAMAGE),
    /* Normal Roll    */ DMG_ENTRY(0, EN_WIZ_DMGEFF_NO_DAMAGE),
    /* UNK_DMG_0x1B   */ DMG_ENTRY(0, EN_WIZ_DMGEFF_NO_DAMAGE),
    /* UNK_DMG_0x1C   */ DMG_ENTRY(0, EN_WIZ_DMGEFF_NO_DAMAGE),
    /* Unblockable    */ DMG_ENTRY(0, EN_WIZ_DMGEFF_NO_DAMAGE),
    /* UNK_DMG_0x1E   */ DMG_ENTRY(0, EN_WIZ_DMGEFF_NO_DAMAGE),
    /* Powder Keg     */ DMG_ENTRY(1, EN_WIZ_DMGEFF_DAMAGE),
};

static DamageTable sIceWizzrobeDamageTable = {
    /* Deku Nut       */ DMG_ENTRY(0, EN_WIZ_DMGEFF_UNK1),
    /* Deku Stick     */ DMG_ENTRY(1, EN_WIZ_DMGEFF_DAMAGE),
    /* Horse trample  */ DMG_ENTRY(0, EN_WIZ_DMGEFF_NO_DAMAGE),
    /* Explosives     */ DMG_ENTRY(1, EN_WIZ_DMGEFF_DAMAGE),
    /* Zora boomerang */ DMG_ENTRY(1, EN_WIZ_DMGEFF_DAMAGE),
    /* Normal arrow   */ DMG_ENTRY(1, EN_WIZ_DMGEFF_DAMAGE),
    /* UNK_DMG_D_06   */ DMG_ENTRY(0, EN_WIZ_DMGEFF_NO_DAMAGE),
    /* Hookshot       */ DMG_ENTRY(1, EN_WIZ_DMGEFF_DAMAGE),
    /* Goron punch    */ DMG_ENTRY(2, EN_WIZ_DMGEFF_DAMAGE),
    /* Sword          */ DMG_ENTRY(1, EN_WIZ_DMGEFF_DAMAGE),
    /* Goron pound    */ DMG_ENTRY(3, EN_WIZ_DMGEFF_DAMAGE),
    /* Fire arrow     */ DMG_ENTRY(2, EN_WIZ_DMGEFF_FIRE),
    /* Ice arrow      */ DMG_ENTRY(1, EN_WIZ_DMGEFF_FREEZE),
    /* Light arrow    */ DMG_ENTRY(2, EN_WIZ_DMGEFF_LIGHT_ORB),
    /* Goron spikes   */ DMG_ENTRY(0, EN_WIZ_DMGEFF_NO_DAMAGE),
    /* Deku spin      */ DMG_ENTRY(1, EN_WIZ_DMGEFF_DAMAGE),
    /* Deku bubble    */ DMG_ENTRY(1, EN_WIZ_DMGEFF_DAMAGE),
    /* Deku launch    */ DMG_ENTRY(0, EN_WIZ_DMGEFF_NO_DAMAGE),
    /* UNK_DMG_0x12   */ DMG_ENTRY(0, EN_WIZ_DMGEFF_UNK1),
    /* Zora barrier   */ DMG_ENTRY(0, EN_WIZ_DMGEFF_NO_DAMAGE),
    /* Normal shield  */ DMG_ENTRY(0, EN_WIZ_DMGEFF_NO_DAMAGE),
    /* Light ray      */ DMG_ENTRY(0, EN_WIZ_DMGEFF_NO_DAMAGE),
    /* Thrown object  */ DMG_ENTRY(1, EN_WIZ_DMGEFF_DAMAGE),
    /* Zora punch     */ DMG_ENTRY(1, EN_WIZ_DMGEFF_DAMAGE),
    /* Spin attack    */ DMG_ENTRY(1, EN_WIZ_DMGEFF_DAMAGE),
    /* Sword beam     */ DMG_ENTRY(0, EN_WIZ_DMGEFF_NO_DAMAGE),
    /* Normal Roll    */ DMG_ENTRY(0, EN_WIZ_DMGEFF_NO_DAMAGE),
    /* UNK_DMG_0x1B   */ DMG_ENTRY(0, EN_WIZ_DMGEFF_NO_DAMAGE),
    /* UNK_DMG_0x1C   */ DMG_ENTRY(0, EN_WIZ_DMGEFF_NO_DAMAGE),
    /* Unblockable    */ DMG_ENTRY(0, EN_WIZ_DMGEFF_NO_DAMAGE),
    /* UNK_DMG_0x1E   */ DMG_ENTRY(0, EN_WIZ_DMGEFF_NO_DAMAGE),
    /* Powder Keg     */ DMG_ENTRY(1, EN_WIZ_DMGEFF_DAMAGE),
};

typedef enum {
    /* 0 */ EN_WIZ_ANIM_IDLE,
    /* 1 */ EN_WIZ_ANIM_RUN,
    /* 2 */ EN_WIZ_ANIM_DANCE,
    /* 3 */ EN_WIZ_ANIM_WIND_UP,
    /* 4 */ EN_WIZ_ANIM_ATTACK,
    /* 5 */ EN_WIZ_ANIM_DAMAGE,
} EnWizAnimation;

static AnimationHeader* sAnimations[] = {
    &gWizzrobeIdleAnim,   &gWizzrobeRunAnim,    &gWizzrobeDanceAnim,
    &gWizzrobeWindUpAnim, &gWizzrobeAttackAnim, &gWizzrobeDamageAnim,
};

static u8 sAnimationModes[] = {
    ANIMMODE_LOOP, ANIMMODE_LOOP, ANIMMODE_LOOP, ANIMMODE_LOOP, ANIMMODE_LOOP, ANIMMODE_ONCE,
};

void EnWiz_Init(Actor* thisx, PlayState* play) {
    s32 pad;
    EnWiz* this = THIS;

    SkelAnime_InitFlex(play, &this->skelAnime, &gWizzrobeSkel, &gWizzrobeIdleAnim, this->jointTable, this->morphTable,
                       WIZZROBE_LIMB_MAX);
    SkelAnime_InitFlex(play, &this->ghostSkelAnime, &gWizzrobeSkel, &gWizzrobeIdleAnim, this->ghostBaseJointTable,
                       this->ghostMorphTable, WIZZROBE_LIMB_MAX);
    Actor_SetScale(&this->actor, 0.0f);
    this->platformLightAlpha = 0;
    this->alpha = 255;
    this->actor.colChkInfo.mass = MASS_IMMOVABLE;
    this->actor.targetMode = 3;
    this->unk_450 = 1.0f;
    this->actor.shape.yOffset = 700.0f;
    Collider_InitAndSetJntSph(play, &this->ghostColliders, &this->actor, &sJntSphInit, this->ghostColliderElements);
    Collider_InitAndSetCylinder(play, &this->collider, &this->actor, &sCylinderInit);
    this->staffFlameScroll = Rand_S16Offset(0, 7);
    this->switchFlag = EN_WIZ_GET_SWITCHFLAG(&this->actor);
    this->type = EN_WIZ_GET_TYPE(&this->actor);

    if (this->switchFlag == 0x7F) {
        this->switchFlag = -1;
    }

    if ((this->type == EN_WIZ_TYPE_FIRE) || (this->type == EN_WIZ_TYPE_FIRE_NO_MINI_BOSS_BGM)) {
        this->actor.colChkInfo.damageTable = &sFireWizzrobeDamageTable;
        this->actor.colChkInfo.health = 8;
        this->actor.flags &= ~ACTOR_FLAG_100000;
    } else {
        this->actor.colChkInfo.damageTable = &sIceWizzrobeDamageTable;
        this->actor.colChkInfo.health = 6;
    }

    if ((this->switchFlag >= 0) && (Flags_GetSwitch(play, this->switchFlag))) {
        Actor_MarkForDeath(&this->actor);
    } else {
        this->actor.hintId = 0x4B;
        this->currentPlatformIndex = 777;
        this->ghostColliders.elements[0].dim.modelSphere.radius = 0;
        this->ghostColliders.elements[0].dim.scale = 0.0f;
        this->ghostColliders.elements[0].dim.modelSphere.center.x = 0;
        this->ghostColliders.elements[0].dim.modelSphere.center.y = 0;
        this->ghostColliders.elements[0].dim.modelSphere.center.z = 0;
        this->actionFunc = EnWiz_StartIntroCutscene;
    }
}

void EnWiz_Destroy(Actor* thisx, PlayState* play) {
    s32 pad;
    EnWiz* this = THIS;

    Collider_DestroyCylinder(play, &this->collider);
    Collider_DestroyJntSph(play, &this->ghostColliders);
    if (this->type != EN_WIZ_TYPE_FIRE_NO_MINI_BOSS_BGM) {
        func_801A2ED8();
    }
}

void EnWiz_ChangeAnim(EnWiz* this, s32 animIndex, s32 updateGhostAnim) {
    this->endFrame = Animation_GetLastFrame(sAnimations[animIndex]);
    Animation_Change(&this->skelAnime, sAnimations[animIndex], 1.0f, 0.0f, this->endFrame, sAnimationModes[animIndex],
                     -2.0f);
    if (updateGhostAnim) {
        Animation_Change(&this->ghostSkelAnime, sAnimations[animIndex], 1.0f, 0.0f, this->endFrame,
                         sAnimationModes[animIndex], -2.0f);
    }
}

void EnWiz_HandleIntroCutscene(EnWiz* this, PlayState* play) {
    Camera* camera;
    Vec3f targetEye;
    Vec3f targetAt;

    if (this->introCutsceneState < EN_WIZ_INTRO_CS_DISAPPEAR) {
        camera = Play_GetCamera(play, this->subCamId);
        switch (this->introCutsceneState) {
            case EN_WIZ_INTRO_CS_NOT_STARTED:
                this->introCutsceneTimer = 100;
                this->introCutsceneCameraAngle = this->actor.world.rot.y;
                this->introCutsceneState++;
                break;

            case EN_WIZ_INTRO_CS_CAMERA_MOVE_TO_PLATFORM:
                Math_Vec3f_Copy(&targetEye, &this->actor.world.pos);
                Math_Vec3f_Copy(&targetAt, &this->actor.world.pos);
                targetEye.x += Math_SinS(this->introCutsceneCameraAngle) * 200.0f;
                targetEye.y += 100.0f;
                targetEye.z += Math_CosS(this->introCutsceneCameraAngle) * 200.0f;
                targetAt.y += 80.0f;
                Math_ApproachF(&camera->eye.x, targetEye.x, 0.3f, 30.0f);
                Math_ApproachF(&camera->eye.z, targetEye.z, 0.3f, 30.0f);
                Math_ApproachF(&camera->at.x, targetAt.x, 0.3f, 30.0f);
                Math_ApproachF(&camera->at.z, targetAt.z, 0.3f, 30.0f);
                camera->eye.y = targetEye.y;
                camera->at.y = targetAt.y;
                if ((fabsf(camera->eye.x - targetEye.x) < 2.0f) && (fabsf(camera->eye.y - targetEye.y) < 2.0f) &&
                    (fabsf(camera->eye.z - targetEye.z) < 2.0f) && (fabsf(camera->at.x - targetAt.x) < 2.0f) &&
                    (fabsf(camera->at.y - targetAt.y) < 2.0f) && (fabsf(camera->at.z - targetAt.z) < 2.0f)) {
                    Player* player = GET_PLAYER(play);
                    s32 i;

                    this->actor.world.rot.y = this->actor.shape.rot.y =
                        Math_Vec3f_Yaw(&this->actor.world.pos, &player->actor.world.pos);

                    for (i = 0; i < this->platformCount; i++) {
                        this->ghostRot[i].y = Math_Vec3f_Yaw(&this->ghostPos[i], &player->actor.world.pos);
                    }

                    EnWiz_ChangeAnim(this, EN_WIZ_ANIM_IDLE, true);
                    this->shouldStartTimer = false;
                    this->targetPlatformLightAlpha = 255;
                    Math_Vec3f_Copy(&this->platformLightPos, &this->actor.world.pos);
                    if (this->fightState == EN_WIZ_FIGHT_STATE_FIRST_PHASE) {
                        Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_WIZ_UNARI);
                    } else {
                        Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_WIZ_VOICE - SFX_FLAG);
                    }

                    this->introCutsceneTimer = 40;
                    this->introCutsceneState++;
                }
                break;

            case EN_WIZ_INTRO_CS_APPEAR:
                if (this->introCutsceneTimer == 0) {
                    this->introCutsceneTimer = 20;
                    this->introCutsceneState++;
                }
                break;

            case EN_WIZ_INTRO_CS_CAMERA_SPIN_TO_FACE_WIZZROBE:
                Math_Vec3f_Copy(&targetEye, &this->actor.world.pos);
                Math_Vec3f_Copy(&targetAt, &this->actor.world.pos);
                targetEye.x += Math_SinS(this->actor.world.rot.y) * 160.0f;
                targetEye.y += 70.0f;
                targetEye.z += Math_CosS(this->actor.world.rot.y) * 140.0f;
                targetAt.x += -10.0f;
                targetAt.y += 100.0f;
                Math_ApproachF(&camera->eye.x, targetEye.x, 0.3f, 30.0f);
                Math_ApproachF(&camera->eye.z, targetEye.z, 0.3f, 30.0f);
                Math_ApproachF(&camera->at.x, targetAt.x, 0.3f, 30.0f);
                Math_ApproachF(&camera->at.z, targetAt.z, 0.3f, 30.0f);
                camera->eye.y = targetEye.y;
                camera->at.y = targetAt.y;
                if (this->introCutsceneTimer == 0) {
                    this->introCutsceneTimer = 10;
                    this->introCutsceneState++;
                    this->introCutsceneCameraAngle = this->actor.world.rot.y;
                }
                break;

            case EN_WIZ_INTRO_CS_WAIT_BEFORE_RUN:
                if (this->introCutsceneTimer == 0) {
                    EnWiz_ChangeAnim(this, EN_WIZ_ANIM_RUN, false);
                    this->rotationalVelocity = 0;
                    this->introCutsceneTimer = 34;
                    this->introCutsceneState++;
                }
                break;

            case EN_WIZ_INTRO_CS_RUN_IN_CIRCLES:
                Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_WIZ_RUN - SFX_FLAG);
                if (this->introCutsceneTimer == 0) {
                    this->animLoopCounter = this->introCutsceneCameraAngle = 0;
                    this->introCutsceneState = EN_WIZ_INTRO_CS_DISAPPEAR;
                } else {
                    Math_SmoothStepToS(&this->rotationalVelocity, 0x1388, 0x64, 0x3E8, 0x3E8);
                    this->actor.world.rot.y += this->rotationalVelocity;
                }

                Math_Vec3f_Copy(&targetEye, &this->actor.world.pos);
                Math_Vec3f_Copy(&targetAt, &this->actor.world.pos);
                targetEye.x += Math_SinS(this->introCutsceneCameraAngle) * 200.0f;
                targetEye.y += 100.0f;
                targetEye.z += Math_CosS(this->introCutsceneCameraAngle) * 200.0f;
                targetAt.y += 80.0f;
                Math_ApproachF(&camera->eye.x, targetEye.x, 0.3f, 30.0f);
                Math_ApproachF(&camera->eye.z, targetEye.z, 0.3f, 30.0f);
                Math_ApproachF(&camera->at.x, targetAt.x, 0.3f, 30.0f);
                Math_ApproachF(&camera->at.z, targetAt.z, 0.3f, 30.0f);
                camera->eye.y = targetEye.y;
                camera->at.y = targetAt.y;
                break;
        }

        if (this->musicStartTimer < 11) {
            this->musicStartTimer++;
            if ((this->type != EN_WIZ_TYPE_FIRE_NO_MINI_BOSS_BGM) && (this->musicStartTimer == 11)) {
                func_801A2E54(NA_BGM_MINI_BOSS);
            }
        }
    }
}

// Also does some ghost stuff, maybe needs a better name
void EnWiz_SelectPlatform(EnWiz* this, PlayState* play) {
    Actor* prop;
    s32 i;
    s32 j;
    s16 ghostAlpha;
    s16 type;
    s16 currentPlatformIndex;

    for (i = 0; i < ARRAY_COUNT(this->platforms); i++) {
        this->platforms[i] = NULL;
    }

    prop = play->actorCtx.actorLists[ACTORCAT_PROP].first;
    i = 0;
    while (prop != NULL) {
        if (prop->id != ACTOR_EN_WIZ_BROCK) {
            prop = prop->next;
            continue;
        }

        this->platforms[i] = prop;
        i++;
        if (this->action != EN_WIZ_ACTION_BURST_INTO_FLAMES) {
            type = this->type;
            if (type == EN_WIZ_TYPE_FIRE_NO_MINI_BOSS_BGM) {
                type = EN_WIZ_TYPE_FIRE;
            }

            prop->colChkInfo.health = type + EN_WIZ_BROCK_PLATFORM_TYPE_FIRE;
            prop = prop->next;
        } else {
            prop->colChkInfo.health = EN_WIZ_BROCK_PLATFORM_TYPE_INACTIVE;
            prop = prop->next;
        }
    }

    if (this->action != EN_WIZ_ACTION_DEAD) {
        this->platformCount = i;
        if (i < 0) {
            i = 0;
        } else if (this->platformCount > 10) {
            this->platformCount = 10;
        }

        currentPlatformIndex = Rand_ZeroFloat(i);
        while ((this->currentPlatformIndex == currentPlatformIndex) || ((s16)i == currentPlatformIndex)) {
            currentPlatformIndex = Rand_ZeroFloat(i);
            if (1) {}
        }

        this->currentPlatformIndex = currentPlatformIndex;
        switch (this->fightState) {
            case EN_WIZ_FIGHT_STATE_FIRST_PHASE:
                Math_Vec3f_Copy(&this->actor.world.pos, &this->platforms[currentPlatformIndex]->world.pos);
                break;

            case EN_WIZ_FIGHT_STATE_SECOND_PHASE_CUTSCENE:
                Math_Vec3f_Copy(&this->actor.world.pos, &this->platforms[0]->world.pos);
                for (i = 0, ghostAlpha = 128; i < this->platformCount; i++, ghostAlpha -= 10) {
                    Math_Vec3f_Copy(&this->ghostPos[i], &this->actor.world.pos);
                    this->ghostAlpha[i] = ghostAlpha;
                }
                break;

            default:
                Math_Vec3f_Copy(&this->actor.world.pos, &this->platforms[currentPlatformIndex]->world.pos);
                for (i--; i >= 0; i--) {
                    if (currentPlatformIndex != i) {
                        Math_Vec3f_Copy(&this->ghostPos[i], &this->platforms[i]->world.pos);
                        this->ghostRot[i] = this->actor.world.rot;
                        this->ghostAlpha[i] = 100;
                        this->ghostNextPlatformIndex[i] = i;
                        for (j = 0; j < ARRAY_COUNT(this->jointTable); j++) {
                            this->ghostJointTables[i][j] = this->jointTable[j];
                        }
                    } else {
                        Math_Vec3f_Copy(&this->ghostPos[i], &gZeroVec3f);
                    }
                }
                break;
        }
    }
}

void EnWiz_MoveGhosts(EnWiz* this) {
    s32 i;
    s32 ghostNextPlatformIndex;
    s32 playSfx = false;

    for (i = 0; i < this->platformCount; i++) {
        if (this->ghostPos[i].x != 0.0f && this->ghostPos[i].z != 0.0f) {
            f32 diffX;
            f32 diffZ;

            ghostNextPlatformIndex = this->ghostNextPlatformIndex[i];
            diffX = this->platforms[ghostNextPlatformIndex]->world.pos.x - this->ghostPos[i].x;
            diffZ = this->platforms[ghostNextPlatformIndex]->world.pos.z - this->ghostPos[i].z;
            playSfx++;

            if (sqrtf(SQ(diffX) + SQ(diffZ)) < 30.0f) {
                this->ghostNextPlatformIndex[i]--;
                if (this->ghostNextPlatformIndex[i] < 0) {
                    this->ghostNextPlatformIndex[i] = this->platformCount - 1;
                }
            }

            ghostNextPlatformIndex = this->ghostNextPlatformIndex[i];
            Math_ApproachF(&this->ghostPos[i].x, this->platforms[ghostNextPlatformIndex]->world.pos.x, 0.3f, 30.0f);
            Math_ApproachF(&this->ghostPos[i].y, this->platforms[ghostNextPlatformIndex]->world.pos.y, 0.3f, 30.0f);
            Math_ApproachF(&this->ghostPos[i].z, this->platforms[ghostNextPlatformIndex]->world.pos.z, 0.3f, 30.0f);
            this->ghostRot[i].y =
                Math_Vec3f_Yaw(&this->ghostPos[i], &this->platforms[ghostNextPlatformIndex]->world.pos);
        }
    }

    if (playSfx) {
        Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_WIZ_RUN - SFX_FLAG);
    }
}

void EnWiz_StartIntroCutscene(EnWiz* this, PlayState* play) {
    if (ActorCutscene_GetCanPlayNext(this->actor.cutscene)) {
        ActorCutscene_StartAndSetFlag(this->actor.cutscene, &this->actor);
        this->subCamId = ActorCutscene_GetCurrentSubCamId(this->actor.cutscene);
        this->actor.flags |= ACTOR_FLAG_100000;
        EnWiz_SetupAppear(this, play);
    } else {
        ActorCutscene_SetIntentToPlay(this->actor.cutscene);
    }
}

void EnWiz_SetupAppear(EnWiz* this, PlayState* play) {
    Player* player = GET_PLAYER(play);
    s32 i;
    s16 angle;

    this->action = EN_WIZ_ACTION_APPEAR;

    if (this->timer == 0) {
        EnWiz_SelectPlatform(this, play);

        if (this->introCutsceneState != EN_WIZ_INTRO_CS_NOT_STARTED) {
            angle = Math_Vec3f_Yaw(&this->actor.world.pos, &player->actor.world.pos);
            this->actor.shape.rot.y = angle;
            this->actor.world.rot.y = angle;
            for (i = 0; i < this->platformCount; i++) {
                this->ghostRot[i].y = Math_Vec3f_Yaw(&this->ghostPos[i], &player->actor.world.pos);
            }

            EnWiz_ChangeAnim(this, EN_WIZ_ANIM_IDLE, true);
            this->shouldStartTimer = false;
            this->targetPlatformLightAlpha = 255;
            Math_Vec3f_Copy(&this->platformLightPos, &this->actor.world.pos);

            if (this->fightState == EN_WIZ_FIGHT_STATE_FIRST_PHASE) {
                Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_WIZ_UNARI);
            } else {
                Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_WIZ_VOICE - SFX_FLAG);
            }
        }

        this->actionFunc = EnWiz_Appear;
    }
}

void EnWiz_Appear(EnWiz* this, PlayState* play) {
    Vec3f sp3C = { 0.006f, 0.006f, 0.006f };
    Player* player = GET_PLAYER(play);

    EnWiz_HandleIntroCutscene(this, play);
    if (this->introCutsceneState >= EN_WIZ_INTRO_CS_APPEAR) {
        SkelAnime_Update(&this->skelAnime);
        if ((this->fightState == EN_WIZ_FIGHT_STATE_FIRST_PHASE) &&
            (this->introCutsceneState >= EN_WIZ_INTRO_CS_DISAPPEAR) &&
            ((this->actor.xzDistToPlayer < 200.0f) ||
             ((player->unk_D57 != 0) &&
              ((ABS_ALT(BINANG_SUB(this->actor.yawTowardsPlayer, this->actor.shape.rot.y)) < 0x7D0)) &&
              (ABS_ALT(BINANG_SUB(this->actor.yawTowardsPlayer, BINANG_ADD(player->actor.shape.rot.y, 0x8000))) <
               0x7D0)))) {
            EnWiz_SetupDisappear(this);
        } else {
            Math_SmoothStepToS(&this->actor.world.rot.y, this->actor.yawTowardsPlayer, 0xA, 0xBB8, 0);

            if (this->fightState == EN_WIZ_FIGHT_STATE_FIRST_PHASE) {
                Math_SmoothStepToS(&this->platformLightAlpha, this->targetPlatformLightAlpha, 10, 10, 10);
                if (!this->shouldStartTimer) {
                    this->timer = 20;
                    this->shouldStartTimer = true;
                }
            } else {
                Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_WIZ_VOICE - SFX_FLAG);
            }

            if (this->timer == 0) {
                Math_ApproachF(&this->scale, 0.015f, 0.05f, 0.01f);
                Math_SmoothStepToS(&this->alpha, 255, 1, 5, 0);
            }

            if (this->scale < 0.0138f) {
            } else {
                this->action = EN_WIZ_ACTION_RUN_IN_CIRCLES;
                this->actor.flags &= ~ACTOR_FLAG_8000000;
                this->ghostColliders.elements[0].info.bumper.dmgFlags = 0x01013A22;
                Math_Vec3f_Copy(&this->staffTargetFlameScale, &sp3C);
                this->targetPlatformLightAlpha = 0;
                if (this->introCutsceneState == EN_WIZ_INTRO_CS_DISAPPEAR) {
                    this->timer = 0;
                    this->introCutsceneTimer = 20;
                    EnWiz_SetupDisappear(this);
                } else if (this->introCutsceneState >= EN_WIZ_INTRO_CS_END) {
                    if (this->fightState == EN_WIZ_FIGHT_STATE_SECOND_PHASE_CUTSCENE) {
                        this->actionFunc = EnWiz_SetupSecondPhaseCutscene;
                    } else {
                        EnWiz_SetupDance(this);
                    }
                }
            }
        }
    }
}

void EnWiz_SetupDance(EnWiz* this) {
    EnWiz_ChangeAnim(this, EN_WIZ_ANIM_DANCE, false);
    Math_ApproachF(&this->scale, 0.015f, 0.05f, 0.001f);
    this->rotationalVelocity = 0;
    this->animLoopCounter = 0;
    this->action = EN_WIZ_ACTION_DANCE;
    if (this->fightState >= EN_WIZ_FIGHT_STATE_SECOND_PHASE) {
        Animation_Change(&this->ghostSkelAnime, &gWizzrobeRunAnim, 1.0f, 0.0f,
                         Animation_GetLastFrame(&gWizzrobeRunAnim), ANIMMODE_LOOP, 0.0f);
        this->fightState = EN_WIZ_FIGHT_STATE_SECOND_PHASE_WITH_RUNNING_GHOSTS;
    }

    Math_SmoothStepToS(&this->alpha, 255, 1, 5, 0);
    this->actionFunc = EnWiz_Dance;
}

void EnWiz_Dance(EnWiz* this, PlayState* play) {
    f32 curFrame = this->skelAnime.curFrame;
    s32 i;

    Math_SmoothStepToS(&this->alpha, 255, 1, 5, 0);
    Math_ApproachF(&this->scale, 0.015f, 0.05f, 0.001f);
    Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_WIZ_RUN - SFX_FLAG);
    this->actor.world.rot.y += this->rotationalVelocity;
    if (this->fightState >= EN_WIZ_FIGHT_STATE_SECOND_PHASE_WITH_RUNNING_GHOSTS) {
        EnWiz_MoveGhosts(this);
    } else {
        for (i = 0; i < this->platformCount; i++) {
            this->ghostRot[i].y += this->rotationalVelocity;
        }
    }

    Math_SmoothStepToS(&this->rotationalVelocity, 0x1388, 0x64, 0x3E8, 0x3E8);
    Math_SmoothStepToS(&this->platformLightAlpha, this->targetPlatformLightAlpha, 20, 50, 10);
    if (this->endFrame <= curFrame) {
        if (this->animLoopCounter < 10) {
            this->animLoopCounter++;
        }
    }

    if ((this->animLoopCounter >= 3) && (!this->hasActiveProjectile)) {
        this->targetPlatformLightAlpha = 0;
        EnWiz_SetupWindUp(this);
    }
}

void EnWiz_SetupSecondPhaseCutscene(EnWiz* this, PlayState* play) {
    s16 temp_v0 = ActorCutscene_GetAdditionalCutscene(this->actor.cutscene);

    if (!ActorCutscene_GetCanPlayNext(temp_v0)) {
        ActorCutscene_SetIntentToPlay(temp_v0);
    } else {
        ActorCutscene_StartAndSetFlag(temp_v0, &this->actor);
        this->subCamId = ActorCutscene_GetCurrentSubCamId(temp_v0);
        this->actor.flags |= ACTOR_FLAG_100000;
        EnWiz_ChangeAnim(this, EN_WIZ_ANIM_DANCE, false);
        this->action = EN_WIZ_ACTION_RUN_BETWEEN_PLATFORMS;
        this->nextPlatformIndex = 1;
        this->hasRunToEveryPlatform = false;
        Math_SmoothStepToS(&this->alpha, 255, 1, 5, 0);
        this->actionFunc = EnWiz_SecondPhaseCutscene;
    }
}

void EnWiz_SecondPhaseCutscene(EnWiz* this, PlayState* play) {
    Camera* camera;
    s32 i;

    Math_SmoothStepToS(&this->alpha, 255, 1, 5, 0);
    camera = Play_GetCamera(play, this->subCamId);
    Math_Vec3f_Copy(&camera->at, &this->actor.focus.pos);
    Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_WIZ_RUN - SFX_FLAG);
    if (this->platforms[this->nextPlatformIndex] != NULL) {
        f32 diffX = this->actor.world.pos.x - this->platforms[this->nextPlatformIndex]->world.pos.x;
        f32 diffZ = this->actor.world.pos.z - this->platforms[this->nextPlatformIndex]->world.pos.z;
        s32 pad;

        if (sqrtf(SQ(diffX) + SQ(diffZ)) < 30.0f) {
            if (!this->hasRunToEveryPlatform) {
                this->nextPlatformIndex++;
                if (this->nextPlatformIndex >= this->platformCount) {
                    this->hasRunToEveryPlatform = true;
                    this->nextPlatformIndex = 0;
                }
            } else {
                f32 diffX = this->actor.world.pos.x - this->ghostPos[this->platformCount].x;
                f32 diffZ = this->actor.world.pos.z - this->ghostPos[this->platformCount].z;
                s32 pad;
                s32 i;

                this->actor.flags |= ACTOR_FLAG_8000000;
                if (sqrtf(SQ(diffX) + SQ(diffZ)) < 20.0f) {
                    for (i = 0; i < this->platformCount; i++) {
                        Math_Vec3f_Copy(&this->ghostPos[i], &gZeroVec3f);
                    }

                    this->nextPlatformIndex = 0;
                    this->platformCount = 0;
                    this->fightState = EN_WIZ_FIGHT_STATE_SECOND_PHASE;
                    this->timer = 0;
                    ActorCutscene_Stop(ActorCutscene_GetAdditionalCutscene(this->actor.cutscene));
                    this->actor.flags &= ~ACTOR_FLAG_100000;
                    EnWiz_SetupDisappear(this);
                    return;
                }
            }
        }
    }

    Math_Vec3f_Copy(this->ghostPos, &this->actor.world.pos);
    this->ghostRot[0].y = this->actor.world.rot.y;
    Math_ApproachF(&this->actor.world.pos.x, this->platforms[this->nextPlatformIndex]->world.pos.x, 0.3f, 30.0f);
    Math_ApproachF(&this->actor.world.pos.y, this->platforms[this->nextPlatformIndex]->world.pos.y, 0.3f, 30.0f);
    Math_ApproachF(&this->actor.world.pos.z, this->platforms[this->nextPlatformIndex]->world.pos.z, 0.3f, 30.0f);
    for (i = this->platformCount; i > 0; i--) {
        Math_Vec3f_Copy(&this->ghostPos[i], &this->ghostPos[i - 1]);
        this->ghostRot[i].y = this->ghostRot[i - 1].y;
    }

    this->actor.world.rot.y =
        Math_Vec3f_Yaw(&this->actor.world.pos, &this->platforms[this->nextPlatformIndex]->world.pos);
}

void EnWiz_SetupWindUp(EnWiz* this) {
    EnWiz_ChangeAnim(this, EN_WIZ_ANIM_WIND_UP, false);
    this->animLoopCounter = 0;
    this->actionFunc = EnWiz_WindUp;
}

void EnWiz_WindUp(EnWiz* this, PlayState* play) {
    f32 curFrame = this->skelAnime.curFrame;
    s32 i;

    Math_SmoothStepToS(&this->actor.world.rot.y, this->actor.yawTowardsPlayer, 0xC8, 0x1F40, 0x1388);
    if (this->fightState >= EN_WIZ_FIGHT_STATE_SECOND_PHASE_WITH_RUNNING_GHOSTS) {
        EnWiz_MoveGhosts(this);
    } else {
        for (i = 0; i < this->platformCount; i++) {
            Math_SmoothStepToS(&this->ghostRot[i].y, this->actor.yawTowardsPlayer, 0xC8, 0x1F40, 0x1388);
        }
    }

    if (this->endFrame <= curFrame) {
        this->animLoopCounter++;
        if (this->animLoopCounter >= 2) {
            EnWiz_SetupAttack(this);
        }
    }

    Math_SmoothStepToS(&this->platformLightAlpha, this->targetPlatformLightAlpha, 10, 10, 10);
}

void EnWiz_SetupAttack(EnWiz* this) {
    EnWiz_ChangeAnim(this, EN_WIZ_ANIM_ATTACK, false);
    this->timer = 0;
    this->shouldStartTimer = false;
    this->action = EN_WIZ_ACTION_ATTACK;
    this->actionFunc = EnWiz_Attack;
}

void EnWiz_Attack(EnWiz* this, PlayState* play) {
    f32 curFrame = this->skelAnime.curFrame;

    if (this->fightState >= EN_WIZ_FIGHT_STATE_SECOND_PHASE_WITH_RUNNING_GHOSTS) {
        EnWiz_MoveGhosts(this);
    }

    if (this->timer == 0) {
        if ((Animation_OnFrame(&this->skelAnime, 6.0f)) && (!this->hasActiveProjectile)) {
            Player* player = GET_PLAYER(play);
            Vec3f sp54;
            s32 sp50 = this->type;

            Math_Vec3f_Copy(&sp54, &this->actor.world.pos);
            sp54.x += Math_SinS(this->actor.world.rot.y) * 40.0f;
            sp54.y += 60.0f;
            sp54.z += Math_CosS(this->actor.world.rot.y) * 40.0f;
            if (sp50 == 2) {
                sp50 = 0;
            }

            Actor_SpawnAsChild(&play->actorCtx, &this->actor, play, ACTOR_EN_WIZ_FIRE, sp54.x, sp54.y, sp54.z,
                               Math_Vec3f_Pitch(&sp54, &player->actor.world.pos),
                               Math_Vec3f_Yaw(&sp54, &player->actor.world.pos), 0, sp50 * 4);
            this->hasActiveProjectile = true;
            Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_WIZ_ATTACK);
            Actor_PlaySfxAtPos(&this->actor, NA_SE_PL_MAGIC_FIRE);
        }

        if ((curFrame >= 8.0f) && (!this->shouldStartTimer)) {
            this->timer = 3;
            this->shouldStartTimer = true;
        }

        if (this->endFrame <= curFrame) {
            EnWiz_SetupDisappear(this);
        }
    }
}

void EnWiz_SetupDisappear(EnWiz* this) {
    if (this->action != EN_WIZ_ACTION_DAMAGED) {
        this->rotationalVelocity = 0x2710;
        this->timer = 0;
        EnWiz_ChangeAnim(this, EN_WIZ_ANIM_IDLE, false);
        this->action = EN_WIZ_ACTION_DISAPPEAR;
    } else {
        this->rotationalVelocity = 0x2710;
        this->actor.world.rot.y += this->rotationalVelocity;
    }

    this->targetPlatformLightAlpha = 0;
    this->actor.flags |= ACTOR_FLAG_8000000;
    Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_WIZ_DISAPPEAR);
    Math_SmoothStepToS(&this->rotationalVelocity, 0x1388, 0x64, 0x3E8, 0x3E8);
    this->actor.world.rot.y += this->rotationalVelocity;
    this->actor.flags &= ~ACTOR_FLAG_1;
    this->actionFunc = EnWiz_Disappear;
}

void EnWiz_Disappear(EnWiz* this, PlayState* play) {
    s32 i;

    Math_SmoothStepToS(&this->rotationalVelocity, 0, 0xA, 0xBB8, 0x14);
    this->actor.world.rot.y += this->rotationalVelocity;
    if ((this->fightState == EN_WIZ_FIGHT_STATE_FIRST_PHASE) || (this->action == EN_WIZ_ACTION_DAMAGED)) {
        Math_ApproachZeroF(&this->scale, 0.3f, 0.01f);
        Math_SmoothStepToS(&this->platformLightAlpha, this->targetPlatformLightAlpha, 5, 50, 0);
    } else {
        Math_ApproachZeroF(&this->scale, 0.3f, 0.001f);
        Math_SmoothStepToS(&this->platformLightAlpha, this->targetPlatformLightAlpha, 10, 50, 0);
        for (i = 0; i < this->platformCount; i++) {
            this->ghostRot[i].y += this->rotationalVelocity;
        }
    }

    Math_Vec3f_Copy(&this->staffTargetFlameScale, &gZeroVec3f);
    if (this->scale < 0.001f) {
        this->scale = 0.0f;
        if ((this->introCutsceneState == EN_WIZ_INTRO_CS_DISAPPEAR) && (this->introCutsceneTimer == 0)) {
            this->introCutsceneState = EN_WIZ_INTRO_CS_END;
            ActorCutscene_Stop(this->actor.cutscene);
            this->actor.flags &= ~ACTOR_FLAG_100000;
        }

        if (this->introCutsceneState != EN_WIZ_INTRO_CS_DISAPPEAR) {
            this->alpha = 0;
            if (this->fightState == EN_WIZ_FIGHT_STATE_FIRST_PHASE) {
                this->ghostColliders.elements[0].info.bumper.dmgFlags = 0x01000202;
            }

            this->actor.flags |= ACTOR_FLAG_1;
            this->actionFunc = EnWiz_SetupAppear;
        }
    }
}

void EnWiz_SetupDamaged(EnWiz* this, PlayState* play) {
    EnWiz_ChangeAnim(this, EN_WIZ_ANIM_DAMAGE, false);
    Actor_SetColorFilter(&this->actor, 0x4000, 255, 0, 8);
    this->timer = 20;

    if ((this->fightState != EN_WIZ_FIGHT_STATE_FIRST_PHASE) && (this->actor.colChkInfo.health <= 0)) {
        Enemy_StartFinishingBlow(play, &this->actor);
        Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_WIZ_DEAD);
        this->timer = 0;
        this->actor.flags &= ~ACTOR_FLAG_1;
    } else {
        Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_WIZ_DAMAGE);
    }

    this->scale = 0.015f;
    this->platformCount = 0;
    this->targetPlatformLightAlpha = 0;
    if ((this->drawDmgEffTimer != 0) &&
        ((this->drawDmgEffType == ACTOR_DRAW_DMGEFF_FIRE) || (this->drawDmgEffType == ACTOR_DRAW_DMGEFF_LIGHT_ORBS))) {
        this->timer = 0;
    }

    this->rotationalVelocity = 0x4E20;
    if ((this->drawDmgEffTimer != 0) && (this->drawDmgEffType == ACTOR_DRAW_DMGEFF_FROZEN_SFX)) {
        this->rotationalVelocity = 0;
        this->timer = 0;
    }

    this->action = EN_WIZ_ACTION_DAMAGED;
    this->actionFunc = EnWiz_Damaged;
}

void EnWiz_Damaged(EnWiz* this, PlayState* play) {
    s32 i;

    if ((this->drawDmgEffTimer < 50) && (this->drawDmgEffType == ACTOR_DRAW_DMGEFF_FROZEN_SFX)) {
        Actor_SpawnIceEffects(play, &this->actor, this->bodyPartsPos, ARRAY_COUNT(this->bodyPartsPos), 2, 1.0f, 0.7f);
        this->drawDmgEffTimer = 0;
        this->drawDmgEffType = ACTOR_DRAW_DMGEFF_FIRE;
        this->rotationalVelocity = 0x4E20;
        this->actor.velocity.y = 30.0f;
        this->actor.gravity = -3.0f;
    }

    if ((this->drawDmgEffTimer != 0) && (this->drawDmgEffTimer < 30) &&
        ((this->drawDmgEffType == ACTOR_DRAW_DMGEFF_FIRE) || (this->drawDmgEffType == ACTOR_DRAW_DMGEFF_LIGHT_ORBS))) {
        this->actor.velocity.y = 30.0f;
        this->actor.gravity = -3.0f;
        this->drawDmgEffTimer = 0;
        this->drawDmgEffType = ACTOR_DRAW_DMGEFF_FIRE;
    } else if ((!this->isDead) && (this->fightState != EN_WIZ_FIGHT_STATE_FIRST_PHASE) &&
               (this->actor.colChkInfo.health <= 0)) {
        this->actor.velocity.y = 30.0f;
        this->actor.gravity = -3.0f;
        this->isDead = true;
    }

    this->actor.world.rot.y += this->rotationalVelocity;
    Math_SmoothStepToS(&this->rotationalVelocity, 0, 0xA, 0xBB8, 0x14);
    for (i = 0; i < this->platformCount; i++) {
        this->ghostRot[i].y += this->rotationalVelocity;
    }

    if ((this->timer == 1) ||
        ((this->actor.velocity.y < 0.0f) &&
         (this->actor.world.pos.y < (this->platforms[this->currentPlatformIndex]->world.pos.y + 11.0f)))) {
        this->timer = 0;
        this->actor.velocity.y = 0.0f;
        this->actor.gravity = 0.0f;
        this->drawDmgEffTimer = this->timer;
        this->drawDmgEffType = this->timer;

        if (this->actor.colChkInfo.health <= 0) {
            if (this->fightState == EN_WIZ_FIGHT_STATE_FIRST_PHASE) {
                this->fightState = EN_WIZ_FIGHT_STATE_SECOND_PHASE_CUTSCENE;
                if ((this->type == EN_WIZ_TYPE_FIRE) || (this->type == EN_WIZ_TYPE_FIRE_NO_MINI_BOSS_BGM)) {
                    this->actor.colChkInfo.health = 8;
                } else {
                    this->actor.colChkInfo.health = 6;
                }

                EnWiz_SetupDisappear(this);
            } else {
                EnWiz_SetupDead(this);
            }
        } else {
            EnWiz_SetupDisappear(this);
        }

        this->actor.flags |= ACTOR_FLAG_8000000;
    }

    Math_SmoothStepToS(&this->platformLightAlpha, this->targetPlatformLightAlpha, 20, 50, 10);
    Actor_MoveWithGravity(&this->actor);
    Actor_UpdateBgCheckInfo(play, &this->actor, 35.0f, 40.0f, 40.0f, 0x1F);
}

void EnWiz_SetupDead(EnWiz* this) {
    EnWiz_ChangeAnim(this, EN_WIZ_ANIM_DAMAGE, false);
    this->rotationalVelocity = 0x2710;
    this->action = EN_WIZ_ACTION_DEAD;
    this->timer = 0;
    this->actionFunc = EnWiz_Dead;
}

void EnWiz_Dead(EnWiz* this, PlayState* play) {
    s32 i;

    this->actor.world.rot.y += this->rotationalVelocity;
    Math_SmoothStepToS(&this->rotationalVelocity, 0, 0xA, 0xBB8, 0x14);
    if (this->rotationalVelocity < 0x1E) {
        Math_SmoothStepToS(&this->alpha, 0, 10, 30, 20);
        for (i = 0; i < this->platformCount; i++) {
            Math_SmoothStepToS(&this->ghostAlpha[i], 0, 10, 30, 20);
        }

        this->action = EN_WIZ_ACTION_BURST_INTO_FLAMES;
    }

    if (this->alpha < 30) {
        EnWiz_SelectPlatform(this, play);
        SoundSource_PlaySfxAtFixedWorldPos(play, &this->actor.world.pos, 50, NA_SE_EN_EXTINCT);
        Actor_MarkForDeath(&this->actor);
        if (this->switchFlag >= 0) {
            Flags_SetSwitch(play, this->switchFlag);
        }
    }
}

static Color_RGBA8 D_80A48D60 = { 250, 250, 250, 255 };

static Color_RGBA8 D_80A48D64 = { 180, 180, 180, 255 };

void EnWiz_UpdateDamage(EnWiz* this, PlayState* play) {
    s32 i;
    s32 attackDealsDamage = false;

    if (this->collider.base.acFlags & AC_HIT) {
        this->ghostColliders.base.acFlags &= ~AC_HIT;
        if (this->action < EN_WIZ_ACTION_RUN_IN_CIRCLES) {
            return;
        }

        switch (this->actor.colChkInfo.damageEffect) {
            case EN_WIZ_DMGEFF_DAMAGE:
                attackDealsDamage = true;
                break;

            case EN_WIZ_DMGEFF_FIRE:
                if (this->type == EN_WIZ_TYPE_ICE) {
                    this->drawDmgEffTimer = 40;
                    this->drawDmgEffType = ACTOR_DRAW_DMGEFF_FIRE;
                }

                attackDealsDamage = true;
                break;

            case EN_WIZ_DMGEFF_FREEZE:
                if ((this->type == EN_WIZ_TYPE_FIRE) || (this->type == EN_WIZ_TYPE_FIRE_NO_MINI_BOSS_BGM)) {
                    this->drawDmgEffTimer = 80;
                    this->drawDmgEffType = ACTOR_DRAW_DMGEFF_FROZEN_SFX;
                    this->drawDmgEffScale = 0.0f;
                    this->drawDmgEffFrozenSteamScale = 1.5f;
                }

                Actor_ApplyDamage(&this->actor);
                EnWiz_SetupDamaged(this, play);
                break;

            case EN_WIZ_DMGEFF_LIGHT_ORB:
                if (((this->drawDmgEffType != ACTOR_DRAW_DMGEFF_FROZEN_SFX) &&
                     (this->drawDmgEffType != ACTOR_DRAW_DMGEFF_FROZEN_NO_SFX)) ||
                    (this->drawDmgEffTimer == 0)) {
                    Actor_Spawn(&play->actorCtx, play, ACTOR_EN_CLEAR_TAG, this->actor.focus.pos.x,
                                this->actor.focus.pos.y, this->actor.focus.pos.z, 0, 0, 0, CLEAR_TAG_LARGE_LIGHT_RAYS);
                    this->drawDmgEffTimer = 40;
                    this->drawDmgEffType = ACTOR_DRAW_DMGEFF_LIGHT_ORBS;
                    attackDealsDamage = true;
                }
                break;
        }

        this->alpha = 255;
        if (attackDealsDamage) {
            Actor_ApplyDamage(&this->actor);
            EnWiz_SetupDamaged(this, play);
            return;
        }
    }

    if ((this->platformCount != 0) && (this->fightState != EN_WIZ_FIGHT_STATE_SECOND_PHASE_CUTSCENE)) {
        for (i = 0; i < this->platformCount; i++) {
            Vec3f accel;
            Vec3f velocity;
            Vec3f pos;
            f32 temp_fs0;
            s32 j;

            if ((iREG(50) != 0) || (this->ghostColliders.elements[i + 1].info.bumperFlags & BUMP_HIT)) {
                this->fightState = EN_WIZ_FIGHT_STATE_SECOND_PHASE;
                this->ghostColliders.base.acFlags &= ~BUMP_HIT;
                if (this->ghostPos[i].x != .0f || this->ghostPos[i].z != .0f) {
                    for (j = 0; j < 9; j++) {
                        accel.x = 0.0f;
                        accel.y = 1.0f;
                        accel.z = 0.0f;
                        velocity.x = 0.0f;
                        velocity.y = 1.0f;
                        velocity.z = 0.0f;
                        temp_fs0 = Rand_S16Offset(20, 10);
                        Math_Vec3f_Copy(&pos, &this->ghostPos[i]);
                        pos.x += (f32)Rand_S16Offset(20, 20) * ((Rand_ZeroOne() < 0.5f) ? -1 : 1);
                        pos.y += 70.0f + randPlusMinusPoint5Scaled(30.0f);
                        pos.z += (f32)Rand_S16Offset(20, 20) * ((Rand_ZeroOne() < 0.5f) ? -1 : 1);
                        func_800B0DE0(play, &pos, &velocity, &accel, &D_80A48D60, &D_80A48D64, Rand_S16Offset(350, 100),
                                      temp_fs0);
                    }

                    SoundSource_PlaySfxAtFixedWorldPos(play, &this->ghostPos[i], 50, NA_SE_EN_WIZ_LAUGH);
                    Math_Vec3f_Copy(&this->ghostPos[i], &gZeroVec3f);
                }
            }
        }
    }
}

void EnWiz_Update(Actor* thisx, PlayState* play) {
    s32 pad;
    EnWiz* this = THIS;
    s32 i;
    s32 j;

    if (this->action != EN_WIZ_ACTION_APPEAR) {
        SkelAnime_Update(&this->skelAnime);
        SkelAnime_Update(&this->ghostSkelAnime);
    }

    Actor_SetFocus(&this->actor, 60.0f);
    Actor_SetScale(&this->actor, this->scale);
    EnWiz_UpdateDamage(this, play);
    this->actionFunc(this, play);

    this->actor.shape.rot.y = this->actor.world.rot.y;

    DECR(this->timer);
    DECR(this->introCutsceneTimer);
    DECR(this->drawDmgEffTimer);

    this->collider.dim.radius = 35;
    this->collider.dim.height = 130;
    this->collider.dim.yShift = 0;
    if (this->action >= EN_WIZ_ACTION_RUN_IN_CIRCLES) {
        CollisionCheck_SetAC(play, &play->colChkCtx, &this->ghostColliders.base);
        Collider_UpdateCylinder(&this->actor, &this->collider);
        CollisionCheck_SetAC(play, &play->colChkCtx, &this->collider.base);
        CollisionCheck_SetOC(play, &play->colChkCtx, &this->collider.base);
    }

    Math_ApproachF(&this->staffFlameScale.x, this->staffTargetFlameScale.x, 0.3f, 0.002f);
    Math_ApproachF(&this->staffFlameScale.y, this->staffTargetFlameScale.y, 0.3f, 0.002f);
    Math_ApproachF(&this->staffFlameScale.z, this->staffTargetFlameScale.z, 0.3f, 0.002f);

    if (this->fightState == EN_WIZ_FIGHT_STATE_FIRST_PHASE) {
        this->platformCount = 0;
    } else if (this->fightState == EN_WIZ_FIGHT_STATE_SECOND_PHASE_WITH_RUNNING_GHOSTS) {
        for (i = 0; i < this->platformCount; i++) {
            for (j = 0; j < ARRAY_COUNT(this->ghostBaseJointTable); j++) {
                this->ghostJointTables[i][j] = this->ghostBaseJointTable[j];
            }
        }
    } else {
        for (i = 0; i < this->platformCount; i++) {
            for (j = 0; j < ARRAY_COUNT(this->jointTable); j++) {
                this->ghostJointTables[i][j] = this->jointTable[j];
            }
        }
    }
}

void EnWiz_OpaPostLimbDraw(PlayState* play, s32 limbIndex, Gfx** dList, Vec3s* rot, Actor* thisx) {
    Vec3f sp24 = { 0.0f, 0.0f, 0.0f };
    EnWiz* this = THIS;

    if (limbIndex == WIZZROBE_LIMB_STAFF) {
        sp24.x = 7300.0f;
        sp24.y = -1500.0f;
        if (this->action != EN_WIZ_ACTION_DANCE) {
            sp24.y = 0.0f;
            sp24.x = 5300.0f;
        }

        Matrix_Translate(0.0f, 0.0f, 0.0f, MTXMODE_APPLY);
        Matrix_MultVec3f(&sp24, &this->staffFlamePos);
    }

    Collider_UpdateSpheres(limbIndex, &this->ghostColliders);

    if ((limbIndex == WIZZROBE_LIMB_PELVIS) || (limbIndex == WIZZROBE_LIMB_TORSO) ||
        (limbIndex == WIZZROBE_LIMB_LEFT_UPPER_ARM) || (limbIndex == WIZZROBE_LIMB_LEFT_FOREARM) ||
        (limbIndex == WIZZROBE_LIMB_RIGHT_UPPER_ARM) || (limbIndex == WIZZROBE_LIMB_RIGHT_FOREARM) ||
        (limbIndex == WIZZROBE_LIMB_NECK) || (limbIndex == WIZZROBE_LIMB_HEAD) || (limbIndex == WIZZROBE_LIMB_JAW) ||
        (limbIndex == WIZZROBE_LIMB_LEFT_SHIN) || (limbIndex == WIZZROBE_LIMB_RIGHT_SHIN) ||
        (limbIndex == WIZZROBE_LIMB_LOINCLOTH)) {
        Matrix_MultZero(&this->bodyPartsPos[this->bodyPartsPosIndex]);
        this->bodyPartsPosIndex++;
        if (this->bodyPartsPosIndex >= ARRAY_COUNT(this->bodyPartsPos)) {
            this->bodyPartsPosIndex = 0;
        }
    }
}

void EnWiz_XluPostLimbDraw(PlayState* play, s32 limbIndex, Gfx** dList, Vec3s* rot, Actor* thisx, Gfx** gfx) {
    Vec3f sp4C = { 0.0f, 0.0f, 0.0f };
    s32 pad;
    EnWiz* this = THIS;

    if (this->action != EN_WIZ_ACTION_BURST_INTO_FLAMES) {
        if (limbIndex == WIZZROBE_LIMB_STAFF) {
            sp4C.x = 7300.0f;
            sp4C.y = -1500.0f;
            if (this->action != EN_WIZ_ACTION_DANCE) {
                sp4C.y = 0.0f;
                sp4C.x = 5300.0f;
            }

            Matrix_Translate(0.0f, 0.0f, 0.0f, MTXMODE_APPLY);
            Matrix_MultVec3f(&sp4C, &this->staffFlamePos);
        }
    } else {
        if (this->timer == 0) {
            Vec3f flamePos;

            Matrix_Translate(0.0f, 0.0f, 0.0f, MTXMODE_APPLY);
            Matrix_MultVec3f(&sp4C, &flamePos);
            flamePos.x += randPlusMinusPoint5Scaled(4.0f);
            flamePos.y += randPlusMinusPoint5Scaled(7.0f);
            flamePos.z += randPlusMinusPoint5Scaled(5.0f);
            func_800B3030(play, &flamePos, &gZeroVec3f, &gZeroVec3f, ((Rand_ZeroFloat(1.0f) * 50.0f) + 70.0f), 10, 1);
            SoundSource_PlaySfxAtFixedWorldPos(play, &flamePos, 10, NA_SE_EN_EXTINCT);
        }

        if ((limbIndex >= WIZZROBE_LIMB_RIGHT_FOOT) && (this->timer == 0)) {
            this->timer = 4;
        }
    }

    if ((limbIndex == WIZZROBE_LIMB_PELVIS) || (limbIndex == WIZZROBE_LIMB_TORSO) ||
        (limbIndex == WIZZROBE_LIMB_LEFT_UPPER_ARM) || (limbIndex == WIZZROBE_LIMB_LEFT_FOREARM) ||
        (limbIndex == WIZZROBE_LIMB_RIGHT_UPPER_ARM) || (limbIndex == WIZZROBE_LIMB_RIGHT_FOREARM) ||
        (limbIndex == WIZZROBE_LIMB_NECK) || (limbIndex == WIZZROBE_LIMB_HEAD) || (limbIndex == WIZZROBE_LIMB_JAW) ||
        (limbIndex == WIZZROBE_LIMB_LEFT_SHIN) || (limbIndex == WIZZROBE_LIMB_RIGHT_SHIN) ||
        (limbIndex == WIZZROBE_LIMB_LOINCLOTH)) {
        Matrix_MultZero(&this->bodyPartsPos[this->bodyPartsPosIndex]);
        this->bodyPartsPosIndex++;
        if (this->bodyPartsPosIndex >= ARRAY_COUNT(this->bodyPartsPos)) {
            this->bodyPartsPosIndex = 0;
        }
    }
}

void EnWiz_Draw(Actor* thisx, PlayState* play) {
    s32 pad;
    EnWiz* this = THIS;

    OPEN_DISPS(play->state.gfxCtx);

    func_8012C28C(play->state.gfxCtx);
    func_8012C2DC(play->state.gfxCtx);

    if ((this->action == EN_WIZ_ACTION_BURST_INTO_FLAMES) || (this->alpha != 255)) {
        Scene_SetRenderModeXlu(play, 1, 2);
        gDPPipeSync(POLY_XLU_DISP++);
        gDPSetEnvColor(POLY_XLU_DISP++, 0, 0, 0, this->alpha);
        POLY_XLU_DISP =
            SkelAnime_DrawFlex(play, this->skelAnime.skeleton, this->skelAnime.jointTable, this->skelAnime.dListCount,
                               NULL, EnWiz_XluPostLimbDraw, &this->actor, POLY_XLU_DISP);
    } else {
        Scene_SetRenderModeXlu(play, 0, 1);
        gDPPipeSync(POLY_OPA_DISP++);
        gDPSetEnvColor(POLY_OPA_DISP++, 255, 255, 255, this->alpha);
        SkelAnime_DrawFlexOpa(play, this->skelAnime.skeleton, this->skelAnime.jointTable, this->skelAnime.dListCount,
                              NULL, EnWiz_OpaPostLimbDraw, &this->actor);
    }

    if (this->drawDmgEffTimer != 0) {
        f32 drawDmgEffAlpha = this->drawDmgEffTimer * 0.05f;

        if ((this->drawDmgEffType == 0xB) || (this->drawDmgEffType == 0xA)) {
            this->drawDmgEffScale += 0.3f;
            if (this->drawDmgEffScale > 0.5f) {
                this->drawDmgEffScale = 0.5f;
            }

            Math_ApproachF(&this->drawDmgEffFrozenSteamScale, this->drawDmgEffScale, 0.1f, 0.04f);
        } else {
            this->drawDmgEffScale = 0.8f;
            this->drawDmgEffFrozenSteamScale = 0.8f;
        }

        Actor_DrawDamageEffects(play, &this->actor, this->bodyPartsPos, ARRAY_COUNT(this->bodyPartsPos),
                                this->drawDmgEffScale, this->drawDmgEffFrozenSteamScale, drawDmgEffAlpha,
                                this->drawDmgEffType);
    }

    if (this->platformCount > 0) {
        s32 i;
        s16 var_v0;

        Matrix_Push();

        var_v0 = this->platformCount;
        if (this->fightState == EN_WIZ_FIGHT_STATE_SECOND_PHASE_CUTSCENE) {
            var_v0 = 10;
        }

        for (i = 0; i < var_v0; i++) {
            func_8012C28C(play->state.gfxCtx);
            func_8012C2DC(play->state.gfxCtx);

            if (this->ghostPos[i].x != 0.0f && this->ghostPos[i].z != 0.0f) {
                Matrix_Translate(this->ghostPos[i].x, this->ghostPos[i].y + 10.0f, this->ghostPos[i].z, MTXMODE_NEW);
                Matrix_Scale(this->scale, this->scale, this->scale, MTXMODE_APPLY);
                Matrix_RotateYS(this->ghostRot[i].y, MTXMODE_APPLY);
                Matrix_RotateXS(this->ghostRot[i].x, MTXMODE_APPLY);
                Matrix_RotateZS(this->ghostRot[i].z, MTXMODE_APPLY);
                Scene_SetRenderModeXlu(play, 1, 2);
                gDPPipeSync(POLY_XLU_DISP++);
                gDPSetEnvColor(POLY_XLU_DISP++, 0, 0, 0, this->ghostAlpha[i]);
                POLY_XLU_DISP =
                    SkelAnime_DrawFlex(play, this->ghostSkelAnime.skeleton, this->ghostJointTables[i],
                                       this->ghostSkelAnime.dListCount, NULL, NULL, &this->actor, POLY_XLU_DISP);
                this->ghostColliders.elements[i + 1].dim.worldSphere.center.x = this->ghostPos[i].x;
                this->ghostColliders.elements[i + 1].dim.worldSphere.center.y = this->ghostPos[i].y + 50.0f;
                this->ghostColliders.elements[i + 1].dim.worldSphere.center.z = this->ghostPos[i].z;
                this->ghostColliders.elements[i + 1].dim.worldSphere.radius =
                    this->ghostColliders.elements[0].dim.modelSphere.radius;
                this->ghostColliders.elements[i + 1].dim.scale = this->ghostColliders.elements[0].dim.scale;
            }
        }

        Matrix_Pop();
    }

    func_8012C2DC(play->state.gfxCtx);
    func_8012C28C(play->state.gfxCtx);

    if (this->fightState == EN_WIZ_FIGHT_STATE_FIRST_PHASE) {
        Matrix_Push();

        AnimatedMat_Draw(play, Lib_SegmentedToVirtual(&object_wiz_Matanimheader_00211C));
        Matrix_Translate(this->platformLightPos.x, this->platformLightPos.y, this->platformLightPos.z, MTXMODE_NEW);
        Matrix_Scale(0.01f, 0.01f, 0.01f, MTXMODE_APPLY);
        gDPPipeSync(POLY_XLU_DISP++);
        gDPSetPrimColor(POLY_XLU_DISP++, 0, 0x80, 255, 255, 255, this->platformLightAlpha);

        if ((this->type == EN_WIZ_TYPE_FIRE) || (this->type == EN_WIZ_TYPE_FIRE_NO_MINI_BOSS_BGM)) {
            gDPSetEnvColor(POLY_XLU_DISP++, 255, 0, 100, 255);
        } else {
            gDPSetEnvColor(POLY_XLU_DISP++, 50, 0, 255, 255);
        }

        gSPMatrix(POLY_XLU_DISP++, Matrix_NewMtx(play->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        gSPDisplayList(POLY_XLU_DISP++, gWizzrobePlatformLightDL);

        Matrix_Pop();
    }

    // Draw the flame at the tip of the Wizzrobe's staff
    Matrix_Translate(this->staffFlamePos.x, this->staffFlamePos.y, this->staffFlamePos.z, MTXMODE_NEW);
    Matrix_Scale(this->staffFlameScale.x, this->staffFlameScale.y, this->staffFlameScale.z, MTXMODE_APPLY);
    gSPSegment(POLY_XLU_DISP++, 0x08,
               Gfx_TwoTexScroll(play->state.gfxCtx, 0, 0, 0, 32, 64, 1, 0,
                                ((this->staffFlameScroll * 10) - (play->state.frames * 20)) % 512, 32, 128));
    gDPPipeSync(POLY_XLU_DISP++);

    if ((this->type == EN_WIZ_TYPE_FIRE) || (this->type == EN_WIZ_TYPE_FIRE_NO_MINI_BOSS_BGM)) {
        gDPSetPrimColor(POLY_XLU_DISP++, 0x80, 0x80, 255, 255, 170, 255);
        gDPSetEnvColor(POLY_XLU_DISP++, 0xFF, 50, 0, 255);
    } else {
        gDPSetPrimColor(POLY_XLU_DISP++, 0x80, 0x80, 170, 255, 255, 255);
        gDPSetEnvColor(POLY_XLU_DISP++, 0, 50, 255, 255);
    }

    Matrix_Mult(&play->billboardMtxF, MTXMODE_APPLY);
    gSPMatrix(POLY_XLU_DISP++, Matrix_NewMtx(play->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPDisplayList(POLY_XLU_DISP++, gEffFire1DL);

    CLOSE_DISPS(play->state.gfxCtx);
}
