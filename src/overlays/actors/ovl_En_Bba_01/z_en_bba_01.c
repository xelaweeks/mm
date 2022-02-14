/*
 * File: z_en_bba_01.c
 * Overlay: ovl_En_Bba_01
 * Description: Unused Bomb Shop Lady NPC
 */

#include "z_en_bba_01.h"
#include "objects/object_bba/object_bba.h"

#define FLAGS 0x00000019

#define THIS ((EnBba01*)thisx)

void EnBba01_Init(Actor* thisx, GlobalContext* globalCtx);
void EnBba01_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnBba01_Update(Actor* thisx, GlobalContext* globalCtx);
void EnBba01_Draw(Actor* thisx, GlobalContext* globalCtx);

void func_809CC370(EnHy* this, GlobalContext* globalCtx);
void func_809CC3A8(EnHy* this, GlobalContext* globalCtx);
void func_809CC3CC(EnHy* this, GlobalContext* globalCtx);

typedef enum { BBA01_DMG_EFF_NONE } EnBba01DamageEffect;

const ActorInit En_Bba_01_InitVars = {
    ACTOR_EN_BBA_01,
    ACTORCAT_NPC,
    FLAGS,
    GAMEPLAY_KEEP,
    sizeof(EnBba01),
    (ActorFunc)EnBba01_Init,
    (ActorFunc)EnBba01_Destroy,
    (ActorFunc)EnBba01_Update,
    (ActorFunc)EnBba01_Draw,
};

// static ColliderCylinderInit sCylinderInit = {
static ColliderCylinderInit D_809CCC80 = {
    { COLTYPE_HIT0, AT_NONE, AC_ON | AC_TYPE_PLAYER, OC1_ON | OC1_TYPE_ALL, OC2_TYPE_1, COLSHAPE_CYLINDER, },
    { ELEMTYPE_UNK1, { 0x00000000, 0x00, 0x00 }, { 0xF7CFFFFF, 0x00, 0x00 }, TOUCH_NONE | TOUCH_SFX_NORMAL, BUMP_ON, OCELEM_ON, },
    { 18, 64, 0, { 0, 0, 0 } },
};

// sColChkInfoInit
static CollisionCheckInfoInit2 D_809CCCAC = { 0, 0, 0, 0, MASS_IMMOVABLE };

// static DamageTable sDamageTable = {
static DamageTable D_809CCCB8 = {
    /* Deku Nut       */ DMG_ENTRY(0, BBA01_DMG_EFF_NONE),
    /* Deku Stick     */ DMG_ENTRY(0, BBA01_DMG_EFF_NONE),
    /* Horse trample  */ DMG_ENTRY(0, BBA01_DMG_EFF_NONE),
    /* Explosives     */ DMG_ENTRY(0, BBA01_DMG_EFF_NONE),
    /* Zora boomerang */ DMG_ENTRY(0, BBA01_DMG_EFF_NONE),
    /* Normal arrow   */ DMG_ENTRY(0, BBA01_DMG_EFF_NONE),
    /* UNK_DMG_0x06   */ DMG_ENTRY(0, BBA01_DMG_EFF_NONE),
    /* Hookshot       */ DMG_ENTRY(0, BBA01_DMG_EFF_NONE),
    /* Goron punch    */ DMG_ENTRY(0, BBA01_DMG_EFF_NONE),
    /* Sword          */ DMG_ENTRY(0, BBA01_DMG_EFF_NONE),
    /* Goron pound    */ DMG_ENTRY(0, BBA01_DMG_EFF_NONE),
    /* Fire arrow     */ DMG_ENTRY(0, BBA01_DMG_EFF_NONE),
    /* Ice arrow      */ DMG_ENTRY(0, BBA01_DMG_EFF_NONE),
    /* Light arrow    */ DMG_ENTRY(0, BBA01_DMG_EFF_NONE),
    /* Goron spikes   */ DMG_ENTRY(0, BBA01_DMG_EFF_NONE),
    /* Deku spin      */ DMG_ENTRY(0, BBA01_DMG_EFF_NONE),
    /* Deku bubble    */ DMG_ENTRY(0, BBA01_DMG_EFF_NONE),
    /* Deku launch    */ DMG_ENTRY(0, BBA01_DMG_EFF_NONE),
    /* UNK_DMG_0x12   */ DMG_ENTRY(0, BBA01_DMG_EFF_NONE),
    /* Zora barrier   */ DMG_ENTRY(0, BBA01_DMG_EFF_NONE),
    /* Normal shield  */ DMG_ENTRY(0, BBA01_DMG_EFF_NONE),
    /* Light ray      */ DMG_ENTRY(0, BBA01_DMG_EFF_NONE),
    /* Thrown object  */ DMG_ENTRY(0, BBA01_DMG_EFF_NONE),
    /* Zora punch     */ DMG_ENTRY(0, BBA01_DMG_EFF_NONE),
    /* Spin attack    */ DMG_ENTRY(0, BBA01_DMG_EFF_NONE),
    /* Sword beam     */ DMG_ENTRY(0, BBA01_DMG_EFF_NONE),
    /* Normal Roll    */ DMG_ENTRY(0, BBA01_DMG_EFF_NONE),
    /* UNK_DMG_0x1B   */ DMG_ENTRY(0, BBA01_DMG_EFF_NONE),
    /* UNK_DMG_0x1C   */ DMG_ENTRY(0, BBA01_DMG_EFF_NONE),
    /* Unblockable    */ DMG_ENTRY(0, BBA01_DMG_EFF_NONE),
    /* UNK_DMG_0x1E   */ DMG_ENTRY(0, BBA01_DMG_EFF_NONE),
    /* Powder Keg     */ DMG_ENTRY(0, BBA01_DMG_EFF_NONE),
};

u16 D_809CCCD8[] = { 4000, 4, 1, 3, 6000, 4, 1, 6, 4000, 4, 1, 3, 6000, 4, 1, 6 };

// UpdateModel
void func_809CC060(EnBba01* this, GlobalContext* globalCtx) {
    Player* player = GET_PLAYER(globalCtx);
    Vec3f focus;

    EnHy_UpdateSkelAnime(&this->enHy, globalCtx);
    if (func_8013D5E8(this->enHy.actor.shape.rot.y, 0x36B0, this->enHy.actor.yawTowardsPlayer)) {
        focus.x = player->actor.world.pos.x;
        focus.y = player->bodyPartsPos[7].y + 3.0f;
        focus.z = player->actor.world.pos.z;
        func_8013D2E0(&focus, &this->enHy.actor.focus.pos, &this->enHy.actor.shape.rot, &this->enHy.focusTarget,
                      &this->enHy.headRot, &this->enHy.torsoRot, D_809CCCD8);
    } else {
        Math_SmoothStepToS(&this->enHy.focusTarget.x, 0, 4, 0x3E8, 1);
        Math_SmoothStepToS(&this->enHy.focusTarget.y, 0, 4, 0x3E8, 1);
        Math_SmoothStepToS(&this->enHy.headRot.x, 0, 4, 0x3E8, 1);
        Math_SmoothStepToS(&this->enHy.headRot.y, 0, 4, 0x3E8, 1);
        Math_SmoothStepToS(&this->enHy.torsoRot.x, 0, 4, 0x3E8, 1);
        Math_SmoothStepToS(&this->enHy.torsoRot.y, 0, 4, 0x3E8, 1);
    }
    SubS_FillLimbRotTables(globalCtx, this->enHy.limbRotTableY, this->enHy.limbRotTableZ,
                           ARRAY_COUNT(this->enHy.limbRotTableY));
    EnHy_UpdateCollider(&this->enHy, globalCtx);
}

// TestIsTalking
s32 func_809CC1D4(EnBba01* this, GlobalContext* globalCtx) {
    s32 isTalking = false;

    if (Actor_ProcessTalkRequest(&this->enHy.actor, &globalCtx->state)) {
        isTalking = true;
        this->enHy.textId = 0x10B9;
        this->enHy.tmpFocusTarget = this->enHy.focusTarget;
        this->enHy.tmpHeadRot = this->enHy.headRot;
        this->enHy.tmpTorsoRot = this->enHy.torsoRot;
        this->enHy.tmpActionFunc = this->enHy.actionFunc;
        this->enHy.actionFunc = func_809CC3CC;
    }
    return isTalking;
}

s32 func_809CC270(EnBba01* this, GlobalContext* globalCtx) {
    s16 x;
    s16 y;

    Actor_GetScreenPos(globalCtx, &this->enHy.actor, &x, &y);
    //! @bug: Both x and y conditionals are always true, || should be an &&
    if (!this->enHy.waitingOnInit && ((x >= 0) || (x < SCREEN_WIDTH)) && ((y >= 0) || (y < SCREEN_HEIGHT))) {
        func_800B85E0(&this->enHy.actor, globalCtx, 30.0f, EXCH_ITEM_2E);
    }
    return true;
}

//FinishInit
void func_809CC2F0(EnHy* this, GlobalContext* globalCtx) {
    if (EnHy_Init(this, globalCtx, &object_bba_Skel_005EF0, ENHY_ANIMATION_BBA_6)) {
        this->actor.flags |= ACTOR_FLAG_1;
        this->actor.draw = EnBba01_Draw;
        this->waitingOnInit = false;
        if (ENBBA01_GET_PATH(&this->actor) == ENBBA01_NO_PATH) {
            this->actionFunc = func_809CC3A8;
        } else {
            this->actionFunc = func_809CC370;
        }
    }
}

//Walk
void func_809CC370(EnHy* this, GlobalContext* globalCtx) {
    if (EnHy_MoveForwards(this, 1.0f)) {
        this->curPoint = 0;
    }
}

//FaceFoward
void func_809CC3A8(EnHy* this, GlobalContext* globalCtx) {
    this->actor.shape.rot = this->actor.world.rot;
}

//Talk
void func_809CC3CC(EnHy* this, GlobalContext* globalCtx) {
    s16 yaw;
    u8 talkstate;

    Math_SmoothStepToS(&this->actor.shape.rot.y, this->actor.yawTowardsPlayer, 4, 0xFA0, 1);
    talkstate = Message_GetState(&globalCtx->msgCtx);
    this->inMsgState3 = (talkstate == 3) ? true : false;

    switch (talkstate) {
        case 0:
            yaw = ABS_ALT(this->actor.shape.rot.y - this->actor.yawTowardsPlayer);
            if (yaw < 0x64) {
                func_801518B0(globalCtx, this->textId, NULL);
            }
            break;
        case 2:
            this->actor.textId = 0;
            this->focusTarget = this->tmpFocusTarget;
            this->headRot = this->tmpHeadRot;
            this->torsoRot = this->tmpTorsoRot;
            this->actor.shape.rot.y = this->actor.world.rot.y;
            this->actionFunc = this->tmpActionFunc;
            this->tmpActionFunc = NULL;
            break;
    }
}

void EnBba01_Init(Actor* thisx, GlobalContext* globalCtx) {
    s32 pad;
    EnBba01* this = THIS;

    this->enHy.animObjIndex = func_8013D924(OBJECT_BBA, globalCtx);
    this->enHy.headObjIndex = func_8013D924(OBJECT_BBA, globalCtx);
    this->enHy.skelUpperObjIndex = func_8013D924(OBJECT_BBA, globalCtx);
    this->enHy.skelLowerObjIndex = func_8013D924(OBJECT_BBA, globalCtx);

    if ((this->enHy.animObjIndex < 0) || (this->enHy.headObjIndex < 0) || (this->enHy.skelUpperObjIndex < 0) ||
        (this->enHy.skelLowerObjIndex < 0)) {
        Actor_MarkForDeath(&this->enHy.actor);
    }
    this->enHy.actor.draw = NULL;
    Collider_InitCylinder(globalCtx, &this->enHy.collider);
    Collider_SetCylinder(globalCtx, &this->enHy.collider, &this->enHy.actor, &D_809CCC80);
    CollisionCheck_SetInfo2(&this->enHy.actor.colChkInfo, &D_809CCCB8, &D_809CCCAC);
    this->enHy.actor.flags &= ~ACTOR_FLAG_1;
    this->enHy.path = func_8013D648(globalCtx, ENBBA01_GET_PATH(&this->enHy.actor), ENBBA01_NO_PATH);
    this->enHy.waitingOnInit = true;
    Actor_SetScale(&this->enHy.actor, 0.01f);
    this->enHy.actionFunc = func_809CC2F0;
}

void EnBba01_Destroy(Actor* thisx, GlobalContext* globalCtx) {
    EnBba01* this = THIS;

    Collider_DestroyCylinder(globalCtx, &this->enHy.collider);
}

void EnBba01_Update(Actor* thisx, GlobalContext* globalCtx) {
    EnBba01* this = THIS;

    func_809CC1D4(this, globalCtx);
    this->enHy.actionFunc(&this->enHy, globalCtx);
    Actor_UpdateBgCheckInfo(globalCtx, &this->enHy.actor, 0.0f, 0.0f, 0.0f, 4);
    func_809CC060(this, globalCtx);
    func_809CC270(this, globalCtx);
}

//OverrideLimbDraw
s32 func_809CC6F0(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3s* rot,
                             Actor* thisx) {
    EnBba01* this = THIS;
    s8 bodyPart;
    Vec3f zeroVec = { 0.0f, 0.0f, 0.0f };

    bodyPart = gEnHyBodyParts[limbIndex];
    if (bodyPart >= 0) {
        Matrix_MultiplyVector3fByState(&zeroVec, &this->enHy.bodyPartsPos[bodyPart]);
    }

    if (limbIndex == 15) {
        OPEN_DISPS(globalCtx->state.gfxCtx);
        gSPSegment(POLY_OPA_DISP++, 0x06, globalCtx->objectCtx.status[this->enHy.headObjIndex].segment);
        gSegments[6] = PHYSICAL_TO_VIRTUAL(globalCtx->objectCtx.status[this->enHy.headObjIndex].segment);
        gSegments[6] = PHYSICAL_TO_VIRTUAL(globalCtx->objectCtx.status[this->enHy.skelLowerObjIndex].segment);
        CLOSE_DISPS(globalCtx->state.gfxCtx);
    }
    if (limbIndex == 15) {
        Matrix_InsertTranslation(1500.0f, 0.0f, 0.0f, MTXMODE_APPLY);
        Matrix_InsertXRotation_s(this->enHy.headRot.y, MTXMODE_APPLY);
        Matrix_InsertZRotation_s(-this->enHy.headRot.x, MTXMODE_APPLY);
        Matrix_InsertTranslation(-1500.0f, 0.0f, 0.0f, MTXMODE_APPLY);
    }

    if (limbIndex == 8) {
        Matrix_InsertXRotation_s(-this->enHy.torsoRot.y, MTXMODE_APPLY);
        Matrix_InsertZRotation_s(-this->enHy.torsoRot.x, MTXMODE_APPLY);
    }

    if ((limbIndex == 15) && this->enHy.inMsgState3 && ((globalCtx->state.frames % 2) == 0)) {
        Matrix_InsertTranslation(40.0f, 0.0f, 0.0f, MTXMODE_APPLY);
    }

    if ((limbIndex == 8) || (limbIndex == 9) ||
        (limbIndex == 12)) {
        rot->y += (s16)(Math_SinS(this->enHy.limbRotTableY[limbIndex]) * 200.0f);
        rot->z += (s16)(Math_CosS(this->enHy.limbRotTableZ[limbIndex]) * 200.0f);
    }

    return false;
}

//PostLimbDraw
void func_809CC984(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3s* rot, Actor* thisx) {
    EnBba01* this = THIS;
    GraphicsContext* gfxCtx = globalCtx->state.gfxCtx;
    Vec3f zeroVec = { 0.0f, 0.0f, 0.0f };

    if (limbIndex == 7) {
        OPEN_DISPS(globalCtx->state.gfxCtx);
        gSPSegment(POLY_OPA_DISP++, 0x06, globalCtx->objectCtx.status[this->enHy.skelUpperObjIndex].segment);
        gSegments[0x06] = PHYSICAL_TO_VIRTUAL(globalCtx->objectCtx.status[this->enHy.skelUpperObjIndex].segment);
        CLOSE_DISPS(globalCtx->state.gfxCtx);
    }

    if (limbIndex == 15) {
        Matrix_MultiplyVector3fByState(&zeroVec, &this->enHy.actor.focus.pos);
    }
}

//TransformLimbDraw
void func_809CCA5C(GlobalContext* globalCtx, s32 limbIndex, Actor* thisx) {
}

void EnBba01_Draw(Actor* thisx, GlobalContext* globalCtx) {
    EnBba01* this = THIS;
    s32 i;
    u8* shadowTex = GRAPH_ALLOC(globalCtx->state.gfxCtx, sizeof(u8[64][64]));
    u8* shadowTexIter;

    OPEN_DISPS(globalCtx->state.gfxCtx);

    func_8012C28C(globalCtx->state.gfxCtx);
    gSPSegment(POLY_OPA_DISP++, 0x08, Gfx_EnvColor(globalCtx->state.gfxCtx, 255, 255, 255, 0));
    gSPSegment(POLY_OPA_DISP++, 0x09, Gfx_EnvColor(globalCtx->state.gfxCtx, 55, 55, 255, 0));
    gDPPipeSync(POLY_OPA_DISP++);
    SkelAnime_DrawTransformFlexOpa(globalCtx, this->enHy.skelAnime.skeleton, this->enHy.skelAnime.jointTable,
                                   this->enHy.skelAnime.dListCount, func_809CC6F0, func_809CC984,
                                   func_809CCA5C, &this->enHy.actor);
    Matrix_InsertXRotation_s(0, MTXMODE_NEW);

    for (i = 0, shadowTexIter = shadowTex; i < (s32)sizeof(u8[64][64]); i++) {
        *shadowTexIter++ = 0;
    }
    for (i = 0; i < 5; i++) {
        func_8013CD64(this->enHy.bodyPartsPos, &this->enHy.actor.world.pos, shadowTex, i / 5.0f,
                      ARRAY_COUNT(this->enHy.bodyPartsPos), gEnHyShadowSize, gEnHyBodyPartsIndex);
    }
    func_8013CF04(&this->enHy.actor, &globalCtx->state.gfxCtx, shadowTex);

    CLOSE_DISPS(globalCtx->state.gfxCtx);
}
