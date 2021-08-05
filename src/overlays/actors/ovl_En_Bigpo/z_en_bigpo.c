/*
 * File z_en_bigpo.c
 * Overlay: ovl_En_Bigpi
 * Description: Leader of the Poes, Found under Dampe's house and the well
 */

#include "z_en_bigpo.h"

#define FLAGS 0x00001215

#define THIS ((EnBigpo*)thisx)

void EnBigpo_Init(Actor* thisx, GlobalContext* globalCtx);
void EnBigpo_Destroy(Actor* thisx, GlobalContext* globalCtx);
// update functions
void EnBigpo_Update(Actor* thisx, GlobalContext* globalCtx);
void EnBigpo_UpdateFire(Actor* thisx, GlobalContext* globalCtx);

void EnBigpo_InitWellBigpo(EnBigpo* this);
void EnBigpo_HitStun(EnBigpo* this);
void EnBigpo_InitDampeMainPo(EnBigpo* this);
void EnBigpo_ChangeToFireCounting(EnBigpo* this);
void EnBigpo_InitHiddenFire(EnBigpo* this);
void EnBigpo_SetupFireRevealed(EnBigpo* this);

void EnBigpo_SetupSpawn(EnBigpo* this);
void EnBigpo_SpawnPoCutscene1(EnBigpo* this, GlobalContext* globalCtx);
void EnBigpo_SpawnPoCutscene2(EnBigpo* this, GlobalContext* globalCtx);
void EnBigpo_SpawnPoCutscene3(EnBigpo* this);
void EnBigpo_SpawnPoCutscene4(EnBigpo* this, GlobalContext* globalCtx);
void EnBigpo_SpawnPoCutscene5(EnBigpo* this);
void EnBigpo_SpawnPoCutscene6(EnBigpo* this, GlobalContext* globalCtx);
void EnBigpo_SpawnPoCutscene7(EnBigpo* this);
void EnBigpo_SpawnPoCutscene8(EnBigpo* this, GlobalContext* globalCtx);

// unk camera func
void EnBigpo_LowerCutsceneSubCamera(EnBigpo* this, GlobalContext* globalCtx);
void EnBigpo_WellWaitForProximity(EnBigpo* this, GlobalContext* globalCtx);
void EnBigpo_WaitCutsceneQueue(EnBigpo* this, GlobalContext* globalCtx);
void EnBigpo_SetupWarpOut(EnBigpo* this);
void EnBigpo_WarpingOut(EnBigpo* this, GlobalContext* globalCtx);
void EnBigpo_SetupWarpIn(EnBigpo* this, GlobalContext* globalCtx);
void EnBigpo_WarpingIn(EnBigpo* this, GlobalContext* globalCtx);
void EnBigpo_SetupIdleFlying(EnBigpo* this);
void EnBigpo_IdleFlying(EnBigpo* this, GlobalContext* globalCtx);
void EnBigpo_SetupSpinUp(EnBigpo* this);
void EnBigpo_SpinningUp(EnBigpo* this, GlobalContext* globalCtx);
void EnBigpo_SetupSpinAttack(EnBigpo* this);
void EnBigpo_SpinAttack(EnBigpo* this, GlobalContext* globalCtx);
void EnBigpo_SetupSpinDown(EnBigpo* this);
void EnBigpo_SpinningDown(EnBigpo* this, GlobalContext* globalCtx);
void EnBigpo_CheckHealth(EnBigpo* this, GlobalContext* globalCtx);
s32 EnBigpo_ApplyDamage(EnBigpo* this, GlobalContext* globalCtx);
void EnBigpo_SetupDeath(EnBigpo* this);
void EnBigpo_BurnAwayDeath(EnBigpo* this, GlobalContext* globalCtx);
void EnBigpo_SetupLanternDrop(EnBigpo* this, GlobalContext* globalCtx);
void EnBigpo_LanternFalling(EnBigpo* this, GlobalContext* globalCtx);
void EnBigpo_SpawnScoopSoul(EnBigpo* this);
void EnBigpo_ScoopSoulAppearing(EnBigpo* this, GlobalContext* globalCtx);
void EnBigpo_SetupScoopSoulIdle(EnBigpo* this);
void EnBigpo_ScoopSoulIdle(EnBigpo* this, GlobalContext* globalCtx);
void EnBigpo_SetupScoopSoulLeaving(EnBigpo* this);
void EnBigpo_ScoopSoulFadingAway(EnBigpo* this, GlobalContext* globalCtx);
void EnBigpo_Die(EnBigpo* this, GlobalContext* globalCtx);
void EnBigpo_SelectRandomFireLocations(EnBigpo* this, GlobalContext* globalCtx);
void EnBigpo_FireCounting(EnBigpo* this, GlobalContext* globalCtx);
void EnBigpo_SetupFlameCirclePositions(EnBigpo* this, GlobalContext* globalCtx);
void EnBigpo_SetupFlameCircleCutscene(EnBigpo* this);
void EnBigpo_FlameCircleCutscene(EnBigpo* this, GlobalContext* globalCtx);
void EnBigpo_UpdateColor(EnBigpo* this);
void EnBigpo_FlickerLanternLight(EnBigpo* this);
void EnBigpo_SetupRevealedFireIdle(EnBigpo* this);
void EnBigpo_RevealedFireIdle(EnBigpo* this, GlobalContext* globalCtx);
void EnBigpo_DoNothing(EnBigpo* this, GlobalContext* globalCtx);
void EnBigpo_WaitingForDampe(EnBigpo* this, GlobalContext* globalCtx);
void EnBigpo_RevealedFireGrowing(EnBigpo* this, GlobalContext* globalCtx);

// draw funcs
void EnBigpo_PostLimbDraw2(struct GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3s* rot, struct Actor* actor,
                           Gfx** gfx);
void EnBigpo_Draw1(Actor* thisx, GlobalContext* globalCtx);
void EnBigpo_DrawScoopSoul(Actor* thisx, GlobalContext* globalCtx);
void EnBigpo_DrawLantern(Actor* thisx, GlobalContext* globalCtx);
void EnBigpo_Draw4(Actor* thisx, GlobalContext* globalCtx);
void EnBigpo_DrawFire(Actor* thisx, GlobalContext* globalCtx);

extern AnimationHeader D_06001360;
extern SkeletonHeader D_06005C18;
extern AnimationHeader D_06000924;
extern AnimationHeader D_06000924;
extern AnimationHeader D_06000454;
extern Gfx D_060041A0;
extern Gfx D_06001BB0;
extern Gfx D_060058B8;
extern Gfx D_060042C8;
extern Gfx D_060043F8;

extern const ActorInit En_Bigpo_InitVars;

const ActorInit En_Bigpo_InitVars = {
    ACTOR_EN_BIGPO,
    ACTORCAT_ENEMY,
    FLAGS,
    OBJECT_BIGPO,
    sizeof(EnBigpo),
    (ActorFunc)EnBigpo_Init,
    (ActorFunc)EnBigpo_Destroy,
    (ActorFunc)EnBigpo_Update,
    (ActorFunc)NULL,
};

static ColliderCylinderInit sCylinderInit = {
    { COLTYPE_HIT3, AT_NONE | AT_TYPE_ENEMY, AC_NONE | AC_TYPE_PLAYER, OC1_NONE | OC1_TYPE_ALL, OC2_TYPE_1, COLSHAPE_CYLINDER, },
    { ELEMTYPE_UNK0, { 0xF7CFFFFF, 0x00, 0x10 }, { 0xF7CFFFFF, 0x00, 0x00 }, TOUCH_ON | TOUCH_SFX_NORMAL, BUMP_ON | BUMP_HOOKABLE, OCELEM_ON, },
    { 35, 100, 10, { 0, 0, 0 } },
};

static CollisionCheckInfoInit sColChkInfoInit = { 10, 35, 100, 50 };

// static DamageTable sDamageTable = {
static DamageTable sDamageTable = {
    /* Deku Nut       */ DMG_ENTRY(0, 0x0),
    /* Deku Stick     */ DMG_ENTRY(1, 0x0),
    /* Horse trample  */ DMG_ENTRY(0, 0x0),
    /* Explosives     */ DMG_ENTRY(1, 0x0),
    /* Zora boomerang */ DMG_ENTRY(1, 0x0),
    /* Normal arrow   */ DMG_ENTRY(1, 0x0),
    /* UNK_DMG_0x06   */ DMG_ENTRY(0, 0x0),
    /* Hookshot       */ DMG_ENTRY(0, 0xF),
    /* Goron punch    */ DMG_ENTRY(1, 0x0),
    /* Sword          */ DMG_ENTRY(1, 0x0),
    /* Goron pound    */ DMG_ENTRY(0, 0x0),
    /* Fire arrow     */ DMG_ENTRY(1, 0x0),
    /* Ice arrow      */ DMG_ENTRY(1, 0x0),
    /* Light arrow    */ DMG_ENTRY(2, 0x4),
    /* Goron spikes   */ DMG_ENTRY(1, 0x0),
    /* Deku spin      */ DMG_ENTRY(1, 0x0),
    /* Deku bubble    */ DMG_ENTRY(1, 0x0),
    /* Deku launch    */ DMG_ENTRY(2, 0x0),
    /* UNK_DMG_0x12   */ DMG_ENTRY(0, 0x0),
    /* Zora barrier   */ DMG_ENTRY(0, 0x0),
    /* Normal shield  */ DMG_ENTRY(0, 0x0),
    /* Light ray      */ DMG_ENTRY(0, 0x0),
    /* Thrown object  */ DMG_ENTRY(1, 0x0),
    /* Zora punch     */ DMG_ENTRY(1, 0x0),
    /* Spin attack    */ DMG_ENTRY(1, 0x0),
    /* Sword beam     */ DMG_ENTRY(1, 0x0),
    /* Normal Roll    */ DMG_ENTRY(0, 0x0),
    /* UNK_DMG_0x1B   */ DMG_ENTRY(0, 0x0),
    /* UNK_DMG_0x1C   */ DMG_ENTRY(0, 0x0),
    /* Unblockable    */ DMG_ENTRY(0, 0x0),
    /* UNK_DMG_0x1E   */ DMG_ENTRY(0, 0x0),
    /* Powder Keg     */ DMG_ENTRY(1, 0x0),
};

static InitChainEntry sInitChain[] = {
    ICHAIN_S8(hintId, 90, ICHAIN_CONTINUE),
    ICHAIN_F32(targetArrowOffset, 3200, ICHAIN_STOP),
};

// used in the burning death actionfunc
static Vec3f D_80B6506C = { 0.0f, 3.0f, 0.0f };

// bytes per limb, used in draw func? bit over my head
static u8 D_80B65078[] = {
    0xFF, 0x04, 0xFF, 0x00, 0xFF, 0x01, 0xFF, 0x02, 0x05, 0x03, 0x00, 0x00,
};

// used in limbdraw?
static Vec3f D_80B65084[] = {
    { 2000.0f, 4000.0f, 0.0f,},
    {-1000.0f, 1500.0f, -2000.0f,},
    {-1000.0f, 1500.0f, 2000.0f,},
}; 

void EnBigpo_Init(Actor* thisx, GlobalContext* globalCtx2) {
    GlobalContext* globalCtx = globalCtx2;
    EnBigpo* this = (EnBigpo*)thisx;
    EnBigpoFireParticle* firesPtr;
    s32 i;

    Actor_ProcessInitChain(&this->actor, sInitChain);

    // thisx req to match
    this->switchFlags = GET_BIGPO_SWITCHFLAGS(thisx);
    thisx->params &= 0xFF;
    if (thisx->params == ENBIGPO_POSSIBLEFIRE) {
        if (Flags_GetSwitch(globalCtx, this->switchFlags)) {
            Actor_MarkForDeath(&this->actor);
        } else {
            thisx->update = Actor_Noop;
            EnBigpo_InitHiddenFire(this);
        }
        return;
    }

    SkelAnime_Init(globalCtx, &this->skelAnime, &D_06005C18, &D_06000924, this->limbDrawTbl, this->transitionDrawTbl,
                   ENBIGPO_LIMBCOUNT);
    Collider_InitAndSetCylinder(globalCtx, &this->collider, &this->actor, &sCylinderInit);
    CollisionCheck_SetInfo(&thisx->colChkInfo, &sDamageTable, &sColChkInfoInit);

    for (i = 0; i < 3; i++) {
        firesPtr = &this->fires[i];
        firesPtr->light = LightContext_InsertLight(globalCtx, &globalCtx->lightCtx, &firesPtr->info);

        Lights_PointNoGlowSetInfo(&firesPtr->info, thisx->home.pos.x, thisx->home.pos.y, thisx->home.pos.z, 0xFF, 0xFF,
                                  0xFF, 0);
    }

    ActorShape_Init(&thisx->shape, 0.0f, func_800B3FC0, 45.0f);
    thisx->bgCheckFlags |= 0x400;
    this->savedHeight = thisx->home.pos.y + 100.0f;
    this->mainColor.r = 0xFF;
    this->mainColor.g = 0xFF;
    this->mainColor.b = 0xD2;
    this->mainColor.a = 0x00; // fully invisible

    if ((this->switchFlags != 0xFF) && (Flags_GetSwitch(globalCtx, this->switchFlags))) {
        Actor_MarkForDeath(&this->actor);
    }

    if (thisx->params == ENBIGPO_REGULAR) { // the well poe, starts immediately
        thisx->flags &= ~0x10; // always update OFF
        this->unkBool204 = true;
        EnBigpo_InitWellBigpo(this);
    } else if (thisx->params == ENBIGPO_SUMMONED) { // dampe type
        EnBigpo_InitDampeMainPo(this);
    }
}

void EnBigpo_Destroy(Actor* thisx, GlobalContext* globalCtx) {
    EnBigpo* this = (EnBigpo*)thisx;
    GlobalContext* gCtx2;
    s32 fireCount;

    if ((this->actor.params != ENBIGPO_POSSIBLEFIRE) && (this->actor.params != ENBIGPO_CHOSENFIRE) &&
        (this->actor.params != ENBIGPO_REVEALEDFIRE) && (this->actor.params != ENBIGPO_UNK5)) {
        // if NOT a fire type, ENBIGPO_REGULAR and ENBIGPO_SUMMONED combat types only
        if (1) {}
        gCtx2 = globalCtx;
        for (fireCount = 0; fireCount < 3; ++fireCount) {
            LightContext_RemoveLight(gCtx2, &gCtx2->lightCtx, this->fires[fireCount].light);
        }
        Collider_DestroyCylinder(gCtx2, &this->collider);
    }
}

void func_80B61914(EnBigpo* this) {
    EnBigpoFireParticle* firePtr;
    s32 i;

    for (i = 0; i < 3; i++) {
        firePtr = &this->fires[i];
        firePtr->pos.x = (Math_SinS(this->actor.shape.rot.y) * this->fireRadius) + this->actor.world.pos.x;
        firePtr->pos.z = (Math_CosS(this->actor.shape.rot.y) * this->fireRadius) + this->actor.world.pos.z;
        this->actor.shape.rot.y += 0x5555;
    }
}

void EnBigpo_UpdateSpin(EnBigpo* this) {
    s16 oldYaw = this->actor.shape.rot.y;
    this->actor.shape.rot.y += this->rotVelocity;
    if ((oldYaw < 0) && (this->actor.shape.rot.y > 0)) {
        Audio_PlayActorSound2(&this->actor, NA_SE_EN_PO_ROLL); // spinning sfx during spin attack
    }
}

// Lowers the position/eye of the camera during the Big Poe spawn cutscene
void EnBigpo_LowerCutsceneSubCamera(EnBigpo* this, GlobalContext* globalContext) {
    Camera* subCamId;
    if (this->cutsceneSubCamId != MAIN_CAM) {
        subCamId = Play_GetCamera(globalContext, this->cutsceneSubCamId);
        subCamId->eye.y -= this->actor.velocity.y;
        if (this->actor.velocity.y > 0.0f) {
            subCamId->eye.x -= 1.5f * Math_SinS(this->actor.yawTowardsPlayer);
            subCamId->eye.z -= 1.5f * Math_CosS(this->actor.yawTowardsPlayer);
        }
        func_8016970C(globalContext, this->cutsceneSubCamId, &this->actor.focus.pos, &subCamId->eye);
    }
}

void EnBigpo_InitWellBigpo(EnBigpo* this) {
    // ! @ BUG: redundant: targetable flag was already set by init, nothing else calls this
    this->actor.flags &= ~0x1; // targetable OFF
    this->actionFunc = EnBigpo_WellWaitForProximity;
    this->fireRadius = 200.0f;
}

void EnBigpo_WellWaitForProximity(EnBigpo* this, GlobalContext* globalCtx) {
    if (this->actor.xzDistToPlayer < 200.0f) {
        EnBigpo_SetupSpawn(this);
    }
}

void EnBigpo_SetupSpawn(EnBigpo* this) {
    ActorCutscene_SetIntentToPlay(this->actor.cutscene);
    this->actionFunc = EnBigpo_WaitCutsceneQueue;
}

void EnBigpo_WaitCutsceneQueue(EnBigpo* this, GlobalContext* globalCtx) {
    if (ActorCutscene_GetCanPlayNext(this->actor.cutscene)) {
        ActorCutscene_Start(this->actor.cutscene, &this->actor);
        func_800B724C(globalCtx, &this->actor, 7);
        this->cutsceneSubCamId = ActorCutscene_GetCurrentCamera(this->actor.cutscene);
        if (this->actor.params == ENBIGPO_REGULAR) { // and SUMMONED, got switched earlier
            EnBigpo_SpawnPoCutscene1(this, globalCtx);
        } else { // ENBIGPO_REVEALEDFIRE
            EnBigpo_SetupFlameCirclePositions(this, globalCtx);
        }
    } else {
        ActorCutscene_SetIntentToPlay(this->actor.cutscene);
    }
}

void EnBigpo_SpawnPoCutscene1(EnBigpo* this, GlobalContext* globalCtx) {
    s32 i;

    this->actor.draw = EnBigpo_Draw4;
    this->actor.shape.rot.y = this->actor.yawTowardsPlayer + 0x8000;
    func_80B61914(this);

    for (i = 0; i < 3; i++) {
        this->fires[i].pos.y = this->actor.world.pos.y;
    }

    this->actor.scale.x = 0.0f;
    this->actor.scale.y = 0.015f;
    this->actor.scale.z = 0.0f;

    if (this->cutsceneSubCamId != MAIN_CAM) {
        Vec3f subCamEye;
        // not F32_LERPIMP macro, introduces float reg regalloc
        subCamEye.x = ((this->actor.world.pos.x - this->fires[0].pos.x) * 1.8f) + this->actor.world.pos.x;
        subCamEye.y = this->actor.world.pos.y + 150.0f;
        subCamEye.z = ((this->actor.world.pos.z - this->fires[0].pos.z) * 1.8f) + this->actor.world.pos.z;
        func_8016970C(globalCtx, this->cutsceneSubCamId, &this->actor.focus.pos, &subCamEye);
    }
    this->actionFunc = EnBigpo_SpawnPoCutscene2;
}

// fires are growing
void EnBigpo_SpawnPoCutscene2(EnBigpo* this, GlobalContext* globalCtx) {
    if (Math_StepToF(&this->actor.scale.x, 0.01f, 0.001f) != 0) {
        EnBigpo_SpawnPoCutscene3(this);
    }
    this->actor.scale.z = this->actor.scale.x;
    this->actor.scale.y = ((0.01f - this->actor.scale.x) * 0.5f) + 0.01f;
}

// switch to fires rotation
void EnBigpo_SpawnPoCutscene3(EnBigpo* this) {
    this->rotVelocity = 0x1000;
    this->actionFunc = EnBigpo_SpawnPoCutscene4;
    this->fireRadius = 200.0f;
    this->actor.velocity.y = 0.0f;
}

// fires are circling inward toward each other
void EnBigpo_SpawnPoCutscene4(EnBigpo* this, GlobalContext* globalCtx) {
    s32 i;

    if (Math_StepToF(&this->fireRadius, 30.0f, 5.0f) != 0) {
        this->rotVelocity += 0x80;
        this->actor.velocity.y += 0.25f;
    }
    this->actor.shape.rot.y += this->rotVelocity;
    func_80B61914(this);

    if (1) {}
    for (i = 0; i < 3; i++) {
        this->fires[i].pos.y += this->actor.velocity.y;
    }

    this->actor.world.pos.y += this->actor.velocity.y;
    EnBigpo_LowerCutsceneSubCamera(this, globalCtx);
    if (this->actor.velocity.y >= 4.0f) {
        EnBigpo_SpawnPoCutscene5(this);
    }
}

// fires have touched, they start to rise, big poe starts to visibly apear
void EnBigpo_SpawnPoCutscene5(EnBigpo* this) {
    SkelAnime_ChangeAnimDefaultRepeat(&this->skelAnime, &D_06001360);
    this->actor.draw = EnBigpo_Draw1;
    Actor_SetScale(&this->actor, 0.014f);
    Audio_PlayActorSound2(&this->actor, NA_SE_EN_STALKIDS_APPEAR);
    this->actionFunc = EnBigpo_SpawnPoCutscene6;
}

// big poe becoming visible in the flames
void EnBigpo_SpawnPoCutscene6(EnBigpo* this, GlobalContext* globalCtx) {
    s32 i;
    s32 alphaPlus; // color alpha + 10

    SkelAnime_FrameUpdateMatrix(&this->skelAnime);
    this->actor.shape.rot.y += this->rotVelocity;
    alphaPlus = this->mainColor.a + 0xA; // decrease transparency
    func_80B61914(this);
    if (alphaPlus >= 0x5A) {
        this->rotVelocity -= 0x80;
        this->actor.velocity.y -= 0.25f;
        if (alphaPlus >= 0xB4) {
            Math_ScaledStepToS(&this->actor.world.rot.y, 0, 0x180);
        }
    }
    this->actor.world.pos.y += this->actor.velocity.y;

    for (i = 0; i < 3; i++) {
        this->fires[i].pos.y += this->actor.velocity.y;
    }

    EnBigpo_LowerCutsceneSubCamera(this, globalCtx);
    if (alphaPlus >= 0xFF) {
        this->mainColor.a = 0xFF; // fully visible
        EnBigpo_SpawnPoCutscene7(this);
    } else {
        this->mainColor.a = alphaPlus;
    }
}

// big poe is now fully visible
void EnBigpo_SpawnPoCutscene7(EnBigpo* this) {
    this->idleTimer = 15;
    if (this->unkBool204 == false) {
        func_801A2E54(0x38);
        this->unkBool204 = true;
    }
    this->actionFunc = EnBigpo_SpawnPoCutscene8;
}

// count 15 frames, animating, then start dampe cutscene if hes here
// also sets the main camera to align with the subCamera and switches back from the subCamera back to the main camera
void EnBigpo_SpawnPoCutscene8(EnBigpo* this, GlobalContext* globalCtx) {
    Actor* dampe;
    Camera* subCamId;

    SkelAnime_FrameUpdateMatrix(&this->skelAnime);
    this->idleTimer -= 1;
    if (this->idleTimer == 0) {
        subCamId = Play_GetCamera(globalCtx, this->cutsceneSubCamId);
        func_8016970C(globalCtx, MAIN_CAM, &subCamId->at, &subCamId->eye);
        this->cutsceneSubCamId = MAIN_CAM;
        if (this->actor.params == ENBIGPO_SUMMONED) {
            dampe = func_ActorCategoryIterateById(globalCtx, NULL, ACTORCAT_NPC, ACTOR_EN_TK);
            if (dampe != NULL) {
                // if dampe exists, switch to viewing his running away cutscene
                dampe->params = this->actor.cutscene;
            } else {
                ActorCutscene_Stop(this->actor.cutscene);
            }
        } else { // ENBIGPO_REGULAR
            ActorCutscene_Stop(this->actor.cutscene);
        }
        func_800B724C(globalCtx, &this->actor, 6);
        EnBigpo_SetupIdleFlying(this); // setup idle flying
    }
}

// spinning fade out
void EnBigpo_SetupWarpOut(EnBigpo* this) {
    this->collider.base.acFlags &= ~AC_ON;
    this->collider.base.ocFlags1 &= ~OC1_ON;
    this->rotVelocity = 0x2000;
    this->idleTimer = 32;
    this->actor.flags &= ~1; // targetable OFF
    this->actor.speedXZ = 0.0f;
    Audio_PlayActorSound2(&this->actor, NA_SE_EN_PO_DISAPPEAR);
    this->actionFunc = EnBigpo_WarpingOut;
}

// spinning fade out of reality
void EnBigpo_WarpingOut(EnBigpo* this, GlobalContext* globalCtx) {
    DECR(this->idleTimer);
    this->actor.shape.rot.y += this->rotVelocity;
    if (this->idleTimer < 0x10) {
        Math_ScaledStepToS(&this->rotVelocity, 0, 0x200);
    }
    this->mainColor.a = this->idleTimer * 7.96875f;
    if (this->idleTimer == 0) {
        this->mainColor.a = 0; // fully invisible
        EnBigpo_SetupWarpIn(this, globalCtx);
    }
}

// warp behind player
void EnBigpo_SetupWarpIn(EnBigpo* this, GlobalContext* globalCtx) {
    Player* player = PLAYER;
    f32 distance;
    s16 randomYaw;

    distance = (this->actor.xzDistToPlayer < 200.0f) ? 200.0f : this->actor.xzDistToPlayer;
    randomYaw = (Rand_Next() >> 0x14) + this->actor.yawTowardsPlayer;
    Audio_PlayActorSound2(&this->actor, NA_SE_EN_STALKIDS_APPEAR);
    SkelAnime_ChangeAnimDefaultRepeat(&this->skelAnime, &D_06001360);
    this->rotVelocity = 0x2000;
    this->actor.world.pos.x = (Math_SinS(randomYaw) * distance) + player->actor.world.pos.x;
    this->actor.world.pos.z = (Math_CosS(randomYaw) * distance) + player->actor.world.pos.z;
    this->actionFunc = EnBigpo_WarpingIn;
}

// spinning back into reality behind player
void EnBigpo_WarpingIn(EnBigpo* this, GlobalContext* globalCtx) {
    this->idleTimer += 1;
    this->actor.shape.rot.y -= this->rotVelocity;
    if (this->idleTimer >= 16) {
        // after 16th frame, start slowing rotation
        Math_ScaledStepToS(&this->rotVelocity, 0, 0x200);
    }

    this->mainColor.a = this->idleTimer * 7.96875f;
    if (this->idleTimer == 32) {
        this->mainColor.a = 0xFF; // fully visible
        if (this->unkBool204 == false) {
            func_801A2E54(0x38);
            this->unkBool204 = true;
        }
        EnBigpo_SetupIdleFlying(this);
    }
}

void EnBigpo_SetupIdleFlying(EnBigpo* this) {
    SkelAnime_ChangeAnimTransitionRepeat(&this->skelAnime, &D_06000924, -5.0f);
    // if poe missed attack, idle 4 seconds, otherwise its reappearing: attack immediately
    this->idleTimer = (this->actionFunc == EnBigpo_SpinningDown) ? 80 : 0;
    this->hoverHeightCycleTimer = 40;
    this->actor.velocity.y = 0.0f;
    this->savedHeight = this->actor.world.pos.y;
    this->actor.world.rot.y = this->actor.shape.rot.y;
    this->collider.base.acFlags |= AC_ON;
    this->collider.base.ocFlags1 |= OC1_ON;
    this->actor.flags |= 0x1; // targetable ON
    this->actionFunc = EnBigpo_IdleFlying;
}

void EnBigpo_IdleFlying(EnBigpo* this, GlobalContext* globalCtx) {
    Player* player = PLAYER;

    SkelAnime_FrameUpdateMatrix(&this->skelAnime);
    DECR(this->idleTimer);
    this->hoverHeightCycleTimer = (this->hoverHeightCycleTimer == 0) ? 0x28 : (this->hoverHeightCycleTimer - 1);
    Math_StepToF(&this->savedHeight, player->actor.world.pos.y + 100.0f, 1.5f);
    this->actor.world.pos.y = (sin_rad(this->hoverHeightCycleTimer * 0.15707964f) * 10.0f) + this->savedHeight;
    Math_StepToF(&this->actor.speedXZ, 3.0f, 0.2f);
    func_800B9010(&this->actor, NA_SE_EN_PO_FLY - SFX_FLAG);
    if (Actor_XZDistanceToPoint(&this->actor, &this->actor.home.pos) > 300.0f) {
        this->unk208 = Actor_YawToPoint(&this->actor, &this->actor.home.pos);
    }

    if ((Math_ScaledStepToS(&this->actor.shape.rot.y, this->unk208, 0x200) != 0) && (Rand_ZeroOne() < 0.075f)) {
        // casts req
        this->unk208 += (s16)((((u32)Rand_Next() >> 0x14) + 0x1000) * ((Rand_ZeroOne() < 0.5f) ? -1 : 1));
    }
    this->actor.world.rot.y = this->actor.shape.rot.y;

    if (this->idleTimer == 0) {
        // poe's break is done, time to attack
        EnBigpo_SetupSpinUp(this);
    }
}

// before it makes a bombing run, it has to spin up some speed
void EnBigpo_SetupSpinUp(EnBigpo* this) {
    this->collider.base.colType = COLTYPE_METAL;
    this->collider.base.acFlags |= AC_HARD;
    this->collider.info.bumper.dmgFlags &= ~0x8000;
    this->collider.base.atFlags |= AT_ON;
    this->rotVelocity = 0x800;
    this->actionFunc = EnBigpo_SpinningUp;
    this->actor.speedXZ = 0.0f;
}

// spinning up to max speed
void EnBigpo_SpinningUp(EnBigpo* this, GlobalContext* globalCtx) {
    SkelAnime_FrameUpdateMatrix(&this->skelAnime);
    this->rotVelocity += 0x200;
    EnBigpo_UpdateSpin(this);
    if (this->rotVelocity >= 0x3C00) {
        EnBigpo_SetupSpinAttack(this);
    }
}

void EnBigpo_SetupSpinAttack(EnBigpo* this) {
    // set flying direction at player (not spinning direction)
    this->actor.world.rot.y = this->actor.yawTowardsPlayer;
    this->actionFunc = EnBigpo_SpinAttack;
}

void EnBigpo_SpinAttack(EnBigpo* this, GlobalContext* globalCtx) {
    Player* player = PLAYER;
    s16 yawDiff;

    SkelAnime_FrameUpdateMatrix(&this->skelAnime);
    Math_StepToF(&this->actor.speedXZ, 10.0f, 1.0f);
    Math_SmoothStepToF(&this->actor.world.pos.y, player->actor.world.pos.y, 0.3f, 7.5f, 1.0f);
    EnBigpo_UpdateSpin(this);
    yawDiff = this->actor.yawTowardsPlayer - this->actor.world.rot.y;
    // because acFlags AC_HARD and COLTYPE_METAL, if we hit it means we contacted as attack
    if (((this->collider.base.atFlags & AT_HIT)) ||
        ((((yawDiff < 0) ? -yawDiff : yawDiff) >= 0x4001) && (this->actor.xzDistToPlayer > 50.0f))) {
        // hit the player OR the poe has missed and flew past player
        EnBigpo_SetupSpinDown(this);
    }
}

// after missing, spin down before idle flying
void EnBigpo_SetupSpinDown(EnBigpo* this) {
    this->collider.base.atFlags &= ~AT_ON;
    this->actionFunc = EnBigpo_SpinningDown;
}

void EnBigpo_SpinningDown(EnBigpo* this, GlobalContext* globalCtx) {
    Player* player = PLAYER;

    SkelAnime_FrameUpdateMatrix(&this->skelAnime);
    Math_SmoothStepToF(&this->actor.world.pos.y, player->actor.world.pos.y + 100.0f, 0.3f, 5.0f, 1.0f);
    Math_StepToF(&this->actor.speedXZ, 0.0f, 0.2f);
    if (Math_ScaledStepToS(&this->rotVelocity, 0, 0x200) != 0) {
        // spin down complete, re-allow hittable
        this->collider.base.colType = COLTYPE_HIT3;
        this->collider.base.acFlags &= ~AC_HARD;
        this->collider.info.bumper.dmgFlags |= 0x8000;
        EnBigpo_SetupIdleFlying(this);
    }
    EnBigpo_UpdateSpin(this);
}

// hit by player, stunned
void EnBigpo_HitStun(EnBigpo* this) {
    SkelAnime_ChangeAnimTransitionStop(&this->skelAnime, &D_06000454, -6.0f);
    func_800BCB70(&this->actor, 0x4000, 0xFF, 0, 0x10);
    this->collider.base.acFlags &= ~AC_ON;
    func_800BE504(&this->actor, &this->collider);
    this->actionFunc = EnBigpo_CheckHealth;
    this->actor.speedXZ = 5.0f;
}

// check if just damaged or dead
void EnBigpo_CheckHealth(EnBigpo* this, GlobalContext* globalCtx) {
    Math_StepToF(&this->actor.speedXZ, 0.0f, 0.5f);
    if (SkelAnime_FrameUpdateMatrix(&this->skelAnime) != 0) {
        if (this->actor.colChkInfo.health == 0) {
            EnBigpo_SetupDeath(this);
        } else {
            EnBigpo_SetupWarpOut(this);
        }
    }
}

void EnBigpo_SetupDeath(EnBigpo* this) {
    this->idleTimer = 0;
    this->actor.speedXZ = 0.0f;
    this->actor.world.rot.y = this->actor.shape.rot.y;
    this->actor.hintId = 0xFF; // clear?
    this->collider.base.ocFlags1 &= ~OC1_ON;
    this->actionFunc = EnBigpo_BurnAwayDeath;
}

// from [red damaged poe] to [burning up poe] to [shinking into the lantern]
void EnBigpo_BurnAwayDeath(EnBigpo* this, GlobalContext* globalCtx) {
    Vec3f tempVec;
    f32 unkTemp2; // dont really know what these unktemps are doing
    s16 cam;
    s16 unkTemp;
    s16 modifiedTimer;

    this->idleTimer += 1;
    if (this->idleTimer < 8) {
        cam = func_800DFCDC(ACTIVE_CAM) + 0x4800;
        if ((s32)this->idleTimer < 5) {
            unkTemp = (this->idleTimer << 0xC) - 0x4000;
            tempVec.y = (((Math_SinS(unkTemp) * 23.0f) + 40.0f) * 1.4000001f) + this->actor.world.pos.y;
            unkTemp2 = Math_CosS(unkTemp) * 32.2f;
            tempVec.x = (Math_SinS(cam) * unkTemp2) + this->actor.world.pos.x;
            tempVec.z = (Math_CosS(cam) * unkTemp2) + this->actor.world.pos.z;

        } else {
            tempVec.y = this->actor.world.pos.y + ((40.0f + (15.0f * (this->idleTimer - 5))) * 1.4000001f);
            tempVec.x = (Math_SinS(cam) * 32.2f) + this->actor.world.pos.x;
            tempVec.z = (Math_CosS(cam) * 32.2f) + this->actor.world.pos.z;
        }

        // not sure what we're turning this into, but its based on the timer
        modifiedTimer = (s32)((f32)((this->idleTimer * 10) + 80) * 1.4000001f);
        func_800B3030(globalCtx, &tempVec, &D_80B6506C, &D_801D15B0, modifiedTimer, 0, 2);
        tempVec.x = (2.0f * this->actor.world.pos.x) - tempVec.x;
        tempVec.z = (2.0f * this->actor.world.pos.z) - tempVec.z;
        func_800B3030(globalCtx, &tempVec, &D_80B6506C, &D_801D15B0, modifiedTimer, 0, 2);
        tempVec.x = this->actor.world.pos.x;
        tempVec.z = this->actor.world.pos.z;
        func_800B3030(globalCtx, &tempVec, &D_80B6506C, &D_801D15B0, modifiedTimer, 0, 2);

    } else if (this->idleTimer >= 28) {
        EnBigpo_SetupLanternDrop(this, globalCtx);

    } else if (this->idleTimer >= 19) {
        this->actor.scale.x = (((28 - this->idleTimer)) * 0.014f) * 0.1f;
        this->actor.scale.z = this->actor.scale.y = this->actor.scale.x;
        this->actor.world.pos.y += 5.0f;
    }

    if (this->idleTimer < 18) {
        func_800B9010(&this->actor, NA_SE_EN_COMMON_EXTINCT_LEV - SFX_FLAG); // burning sfx
    }
    if (this->idleTimer == 18) {
        Audio_PlayActorSound2(&this->actor, NA_SE_EN_WIZ_DISAPPEAR);
    }
}

void EnBigpo_SetupLanternDrop(EnBigpo* this, GlobalContext* globalCtx) {
    this->actor.draw = EnBigpo_DrawLantern;
    this->actor.shape.shadowDraw = NULL;
    this->actor.world.pos.x = this->drawMtxF.wx;
    this->actor.world.pos.y = this->drawMtxF.wy;
    this->actor.world.pos.z = this->drawMtxF.wz;

    Actor_SetScale(&this->actor, 0.014f);
    this->actor.gravity = -1.0f;
    this->actor.shape.yOffset = 1500.0f;
    this->actor.shape.rot.x = -0x8000;
    this->actor.velocity.y = 0.0f;
    this->actor.world.pos.y -= 15.0f;
    func_800BC154(globalCtx, &globalCtx->actorCtx, &this->actor, ACTORCAT_MISC);
    this->actor.flags &= ~0x5; // targetable OFF, enemy music OFF
    this->actor.bgCheckFlags &= ~0x400;
    this->actionFunc = EnBigpo_LanternFalling;
}

void EnBigpo_LanternFalling(EnBigpo* this, GlobalContext* globalCtx) {
    if (((this->actor.bgCheckFlags & 1)) || (this->actor.floorHeight == -32000.0f)) {
        if (this->switchFlags != 0xFF) {
            Actor_SetSwitchFlag(globalCtx, this->switchFlags);
        }

        EffectSsHahen_SpawnBurst(globalCtx, &this->actor.world.pos, 6.0f, 0, 1, 1, 0xF, OBJECT_BIGPO, 10, &D_060041A0);
        EnBigpo_SpawnScoopSoul(this);
    }
}

void EnBigpo_AdjustPoAlpha(EnBigpo* this, s32 alphaDiff) {
    s32 newAlpha;
    f32 lowerAlpha;
    f32 newXYScale;

    newAlpha = this->mainColor.a + alphaDiff;

    this->mainColor.a = (newAlpha < 0) ? (0) : ((newAlpha >= 0x100) ? 0xFF : newAlpha);

    lowerAlpha = this->mainColor.a * 0.003921569f;
    if (alphaDiff < 0) {
        newXYScale = (0.0056000003f * lowerAlpha) + 0.0014000001f;
        this->actor.scale.x = newXYScale;
        this->actor.scale.z = newXYScale;
        this->actor.scale.y = (0.007f - (0.007f * lowerAlpha)) + 0.007f;
        lowerAlpha = lowerAlpha;
    } else {
        Actor_SetScale(&this->actor, lowerAlpha * 0.007f);
        this->actor.world.pos.y = this->savedHeight + (lowerAlpha * 15.0f);
        lowerAlpha = 1.0f;
    }

    this->mainColor.r = 255.0f * lowerAlpha;
    this->mainColor.g = 200.0f * lowerAlpha;
    this->mainColor.b = 0;
}

// setup spawn soul
void EnBigpo_SpawnScoopSoul(EnBigpo* this) {
    this->actor.draw = EnBigpo_DrawScoopSoul;
    this->actor.shape.yOffset = 0.0f;
    this->actor.shape.rot.x = 0;
    this->actor.shape.rot.y = 0;
    this->actor.gravity = 0.0f;
    this->actor.velocity.y = 0.0f;
    this->mainColor.a = 0; // fully invisible
    this->actor.scale.x = 0.0f;
    this->actor.scale.y = 0.0f;
    this->savedHeight = this->actor.world.pos.y;
    Audio_PlayActorSound2(&this->actor, NA_SE_EV_METAL_BOX_BOUND); // misnamed?
    this->actionFunc = EnBigpo_ScoopSoulAppearing;
}

void EnBigpo_ScoopSoulAppearing(EnBigpo* this, GlobalContext* globalCtx) {
    this->savedHeight += 2.0f;
    EnBigpo_AdjustPoAlpha(this, 0x14); // increase visibility
    if (this->mainColor.a == 0xFF) {   // fully visible
        EnBigpo_SetupScoopSoulIdle(this);
    }
}

void EnBigpo_SetupScoopSoulIdle(EnBigpo* this) {
    this->savedHeight = this->actor.world.pos.y;
    Actor_SetHeight(&this->actor, -10.0f);
    this->idleTimer = 400;    // 20 seconds
    this->actor.flags |= 0x1; // targetable ON
    this->actionFunc = EnBigpo_ScoopSoulIdle;
}

void EnBigpo_ScoopSoulIdle(EnBigpo* this, GlobalContext* globalCtx) {
    DECR(this->idleTimer);
    if (Actor_HasParent(&this->actor, globalCtx)) {
        Actor_MarkForDeath(&this->actor);
    } else if (this->idleTimer == 0) {
        // took too long, soul is leaving
        Audio_PlayActorSound2(&this->actor, NA_SE_EN_PO_LAUGH);
        EnBigpo_SetupScoopSoulLeaving(this);
    } else {
        func_800B8A1C(&this->actor, globalCtx, 0xBA, 35.0f, 60.0f);
        this->actor.world.pos.y = (sin_rad((f32)this->idleTimer * 0.15707964f) * 5.0f) + this->savedHeight;
    }
}

void EnBigpo_SetupScoopSoulLeaving(EnBigpo* this) {
    this->actor.flags &= ~0x10001; // targetable OFF and unknown OFF
    this->actionFunc = EnBigpo_ScoopSoulFadingAway;
}

void EnBigpo_ScoopSoulFadingAway(EnBigpo* this, GlobalContext* globalCtx) {
    EnBigpo_AdjustPoAlpha(this, -0xD);
    if (this->mainColor.a == 0) { // fully invisible
        Actor_MarkForDeath(&this->actor);
    }
}

void EnBigpo_InitDampeMainPo(EnBigpo* this) {
    this->actor.flags &= ~0x1; // targetable OFF
    this->actionFunc = EnBigpo_SelectRandomFireLocations;
}

// dampe fires are in 3/N random locations, here we pick them
void EnBigpo_SelectRandomFireLocations(EnBigpo* this, GlobalContext* globalCtx) {
    Actor* enemyPtr;
    EnBigpo* randomFirePo;
    s32 fireIndex;
    s32 randomIndex;
    s32 fireCount = 0;

    // count the number of possible fires we can find (4 in vanilla)
    for (enemyPtr = FIRST_ENEMY; enemyPtr != NULL; enemyPtr = enemyPtr->next) {
        if ((enemyPtr->id == ACTOR_EN_BIGPO) && (enemyPtr->params == ENBIGPO_POSSIBLEFIRE)) {
            fireCount++;
        }
    }

    // if not enough fires exist, just starting fighting already
    if (fireCount < 3) {
        this->actor.draw = EnBigpo_Draw1;
        Actor_SetScale(&this->actor, 0.014f);
        EnBigpo_SetupWarpIn(this, globalCtx);
        Math_Vec3f_Copy(&this->actor.world.pos, &this->actor.home.pos);
        this->actor.world.pos.y += 100.0f;
        return;
    }

    // for available possiblefires, pick three to be random fires
    for (fireIndex = 0; fireIndex < 3; ++fireIndex, --fireCount) {
        enemyPtr = FIRST_ENEMY;
        randomIndex = ((s32)Rand_ZeroFloat(fireCount)) % fireCount;

        while (enemyPtr != NULL) {
            if ((enemyPtr->id == ACTOR_EN_BIGPO) && (enemyPtr->params == ENBIGPO_POSSIBLEFIRE)) {
                if (randomIndex == 0) {
                    randomFirePo = (EnBigpo*)enemyPtr;
                    randomFirePo->actor.params = ENBIGPO_CHOSENFIRE;
                    Math_Vec3f_Copy(&this->fires[fireIndex].pos, &randomFirePo->actor.world.pos);
                    randomFirePo->actor.parent = (Actor*)this;
                    randomFirePo->actor.update = EnBigpo_UpdateFire;
                    func_800BC154(globalCtx, &globalCtx->actorCtx, &randomFirePo->actor, ACTORCAT_PROP);
                    randomFirePo->unk20C = fireIndex;
                    randomFirePo->actor.flags &= ~0x1; // targetable OFF
                    // make invisible by size:0
                    Actor_SetScale(&randomFirePo->actor, 0);

                    if (this->actor.child == NULL) {
                        this->actor.child = &randomFirePo->actor;
                    } else {
                        randomFirePo->actor.child = this->actor.child;
                        this->actor.child = &randomFirePo->actor;
                    }
                    break;
                } else {
                    randomIndex--;
                }
            }
            enemyPtr = enemyPtr->next;
        }
    }

    // remove unused fires
    for (enemyPtr = FIRST_ENEMY; enemyPtr != NULL; enemyPtr = enemyPtr->next) {
        if ((enemyPtr->id == ACTOR_EN_BIGPO) && (enemyPtr->params == ENBIGPO_POSSIBLEFIRE)) {
            randomFirePo = (EnBigpo*)enemyPtr;
            randomFirePo->actionFunc = EnBigpo_Die;
            randomFirePo->actor.update = EnBigpo_UpdateFire;
        }
    }

    EnBigpo_ChangeToFireCounting(this);
}

void EnBigpo_ChangeToFireCounting(EnBigpo* this) {
    this->actionFunc = EnBigpo_FireCounting;
}

// count fires already found by dampe, once enough: spawn big poe for fight
void EnBigpo_FireCounting(EnBigpo* this, GlobalContext* globalCtx) {
    EnBigpo* firePo;
    s32 activatedFireCount = 0;

    for (firePo = (EnBigpo*)this->actor.child; firePo; firePo = (EnBigpo*)firePo->actor.child) {
        if ((firePo->actor.params == ENBIGPO_REVEALEDFIRE) && (firePo->actionFunc == EnBigpo_RevealedFireIdle)) {
            activatedFireCount++;
        }
    }

    if (activatedFireCount == 3) { // all fires found
        EnBigpo_SetupSpawn(this);
    }
}

void EnBigpo_SetupFlameCirclePositions(EnBigpo* this, GlobalContext* globalCtx) {
    EnBigpo* firePo;
    Vec3f subCamEye;

    this->idleTimer = 39;
    for (firePo = (EnBigpo*)this->actor.child; firePo; firePo = (EnBigpo*)firePo->actor.child) {
        EnBigpo_SetupFlameCircleCutscene(firePo);
    }

    // Setup sub camera: set 'eye' and 'at' and switch to subcamera
    if (this->cutsceneSubCamId != MAIN_CAM) {
        subCamEye.x = (Math_SinS(this->actor.yawTowardsPlayer) * 360.0f) + this->actor.world.pos.x;
        subCamEye.y = this->actor.world.pos.y + 150.0f;
        subCamEye.z = (Math_CosS(this->actor.yawTowardsPlayer) * 360.0f) + this->actor.world.pos.z;
        func_8016970C(globalCtx, this->cutsceneSubCamId, &this->actor.focus.pos, &subCamEye);
    }

    this->actionFunc = EnBigpo_DoNothing;
}

// nothing doing
void EnBigpo_DoNothing(EnBigpo* this, GlobalContext* globalCtx) {
}

void EnBigpo_InitHiddenFire(EnBigpo* this) {
    this->actor.draw = NULL;
    this->actionFunc = EnBigpo_WaitingForDampe;
}

// idle until dampe turns ENBIGPO_POSSIBLEFIRE into ENBIGPO_REVEALEDFIRE
void EnBigpo_WaitingForDampe(EnBigpo* this, GlobalContext* globalCtx) {
    if (this->actor.params == ENBIGPO_REVEALEDFIRE) {
        EnBigpo_SetupFireRevealed(this);
    }
}

// why make this an actionfunc though? why not just call directly?
void EnBigpo_Die(EnBigpo* this, GlobalContext* globalCtx) {
    Actor_MarkForDeath(&this->actor);
}

void EnBigpo_SetupFireRevealed(EnBigpo* this) {
    this->actor.draw = EnBigpo_DrawFire;
    this->idleTimer = 15;
    this->actionFunc = EnBigpo_RevealedFireGrowing;
}

void EnBigpo_RevealedFireGrowing(EnBigpo* this, GlobalContext* globalCtx) {
    if (Math_StepToF(&this->actor.scale.x, 0.01f, 0.0005f) != 0) {
        this->idleTimer--;
        if (this->idleTimer == 0) {
            EnBigpo_SetupRevealedFireIdle(this);
        }
    }
    this->actor.scale.z = this->actor.scale.x;
    this->actor.scale.y = ((0.01f - this->actor.scale.x) * 0.5f) + 0.01f;
}

void EnBigpo_SetupRevealedFireIdle(EnBigpo* this) {
    this->idleTimer = 10000; // 8 minutes until the fire leaves
    this->actionFunc = EnBigpo_RevealedFireIdle;
}

void EnBigpo_RevealedFireIdle(EnBigpo* this, GlobalContext* globalCtx) {
    if (this->idleTimer > 0) {
        if (this->idleTimer == 0) {
            // ! @ BUG: unreachable code
            this->actor.params = ENBIGPO_UNK5;
            return;
        }
    } else {
        if (Math_StepToF(&this->actor.scale.x, 0.0f, 0.001f) != 0) {
            this->actor.params = ENBIGPO_CHOSENFIRE;
            EnBigpo_InitHiddenFire(this);
        }
        this->actor.scale.z = this->actor.scale.x;
        this->actor.scale.y = ((0.01f - this->actor.scale.x) * 0.5f) + 0.01f;
    }
}

// this is for the flames, which are also bigpo actors
void EnBigpo_SetupFlameCircleCutscene(EnBigpo* this) {
    s16 flameHeight;

    this->idleTimer = 40;
    flameHeight = this->actor.parent->yawTowardsPlayer + this->unk20C * 0x5555;
    this->actor.home.pos.x = Math_SinS(flameHeight) * 30.0f + this->actor.parent->world.pos.x;
    this->actor.home.pos.y = this->actor.parent->world.pos.y;
    this->actor.home.pos.z = Math_CosS(flameHeight) * 30.0f + this->actor.parent->world.pos.z;
    this->actionFunc = EnBigpo_FlameCircleCutscene;
}

// every frame, swirl the flames toward big poe as summoned
void EnBigpo_FlameCircleCutscene(EnBigpo* this, GlobalContext* globalCtx) {
    Vec3f posDiff;
    f32 magnitude;

    this->idleTimer--;
    if (this->idleTimer == 0) {
        EnBigpo* parentPoh = (EnBigpo*)this->actor.parent;
        Actor_SetSwitchFlag(globalCtx, this->switchFlags);
        Math_Vec3f_Copy(&parentPoh->fires[this->unk20C].pos, &this->actor.world.pos);
        Actor_MarkForDeath(&this->actor);
        if (this->unk20C == 0) {
            parentPoh->actor.draw = EnBigpo_Draw4;
            Actor_SetScale(&parentPoh->actor, 0.01f);
            EnBigpo_SpawnPoCutscene3(parentPoh);
            parentPoh->fireRadius = 30.0f;
        }
    } else {
        Math_Vec3f_Diff(&this->actor.world.pos, &this->actor.home.pos, &posDiff);
        magnitude = Math3D_Vec3fMagnitude(&posDiff);
        if (magnitude > 0.0001f) {
            Math_Vec3f_Scale(&posDiff, 1.0f / magnitude);
        }
        magnitude = magnitude / this->idleTimer;
        this->actor.world.pos.x -= magnitude * posDiff.x;
        this->actor.world.pos.y -= magnitude * posDiff.y;
        this->actor.world.pos.z -= magnitude * posDiff.z;
    }
}

void EnBigpo_UpdateColor(EnBigpo* this) {
    s32 bplus5;
    s32 bminus5;

    if (this->actionFunc == EnBigpo_CheckHealth) {
        if ((this->actor.colorFilterTimer & 2)) {
            this->mainColor.r = 0;
            this->mainColor.g = 0;
            this->mainColor.b = 0;
        } else {
            this->mainColor.r = 0x50; // teal? what about the red health?
            this->mainColor.g = 0xFF;
            this->mainColor.b = 0xE1;
        }
    } else {
        this->mainColor.r = (this->mainColor.r + 5 >= 0x100) ? (0xFF) : (this->mainColor.r + 5);
        this->mainColor.g = (this->mainColor.g + 5 >= 0x100) ? (0xFF) : (this->mainColor.g + 5);

        // this might be a triple ternary but it matches and is easier to read spread out
        bplus5 = this->mainColor.b + 5;
        if (this->mainColor.b >= 0xD3) {
            bminus5 = this->mainColor.b - 5;
            if (bminus5 < 0xD2) {
                this->mainColor.b = 0xD2;
            } else {
                this->mainColor.b = (u8)bminus5;
            }
        } else {
            if (bplus5 >= 0xD3) {
                this->mainColor.b = 0xD2;
            } else {
                this->mainColor.b = (u8)bplus5;
            }
        }
    }
}

void EnBigpo_FlickerLanternLight(EnBigpo* this) {
    f32 rand = Rand_ZeroOne();
    this->lanternColor.r = ((s32)(rand * 30.0f)) + 0xE1;
    this->lanternColor.g = ((s32)(rand * 100.0f)) + 0x9B;
    this->lanternColor.b = ((s32)(rand * 160.0f)) + 0x5F;
    this->lanternColor.a = ((s32)(rand * 30.0f)) + 0xDC;
}

s32 EnBigpo_ApplyDamage(EnBigpo* this, GlobalContext* globalCtx) {
    if (((this->collider.base.acFlags & AC_HIT) != 0) && ((this->collider.base.acFlags & AC_HARD) == 0)) {
        this->collider.base.acFlags &= ~AC_HIT;

        if (this->actor.colChkInfo.damageEffect == 0xF) {
            return true;
        }

        if (Actor_ApplyDamage(&this->actor) == 0) {
            this->actor.flags &= ~0x1; // targetable OFF
            Audio_PlayActorSound2(&this->actor, NA_SE_EN_PO_DEAD);
            Enemy_StartFinishingBlow(globalCtx, &this->actor);
            if (this->actor.params == ENBIGPO_SUMMONED) { // dampe type
                func_801A2ED8();
            }
        } else {
            Audio_PlayActorSound2(&this->actor, NA_SE_EN_PO_DAMAGE);
        }

        // think this is the light arrow effect version fo clear tag, not black smoke
        if (this->actor.colChkInfo.damageEffect == 4) {
            this->unk21C = 4.0f;
            this->unk220 = 1.0f;
            Actor_Spawn(&globalCtx->actorCtx, globalCtx, ACTOR_EN_CLEAR_TAG, this->collider.info.bumper.hitPos.x,
                        this->collider.info.bumper.hitPos.y, this->collider.info.bumper.hitPos.z, 0, 0, 0, 0x0004);
        }
        EnBigpo_HitStun(this);
        return true;
    }
    return false;
}

void EnBigpo_Update(Actor* thisx, GlobalContext* globalCtx) {
    EnBigpo* this = (EnBigpo*)thisx;
    s32 pad;
    ColliderCylinder* thisCollider;

    if ((this->actor.flags & 0x2000) == 0x2000) {
        this->hoverHeightCycleTimer = 0;
        this->savedHeight = this->actor.world.pos.y;
    }

    if (EnBigpo_ApplyDamage(this, globalCtx) == 0) {
        if ((this->actor.isTargeted) && (this->actionFunc != EnBigpo_WarpingOut) &&
            ((this->collider.base.acFlags & AC_HARD) == 0) && (this->actor.category == ACTORCAT_ENEMY)) {
            this->unk20C += 1;
        } else {
            this->unk20C = 0;
        }
        if (this->unk20C == 0x28) {
            Audio_PlayActorSound2(&this->actor, NA_SE_EN_PO_LAUGH);
            EnBigpo_SetupWarpOut(this);
        }
    }

    this->actionFunc(this, globalCtx);
    if ((this->actionFunc != EnBigpo_SpawnPoCutscene6) && (this->actionFunc != EnBigpo_SpawnPoCutscene4)) {
        Actor_SetVelocityAndMoveYRotationAndGravity(&this->actor);
    }
    if (this->actionFunc == EnBigpo_LanternFalling) {
        Actor_UpdateBgCheckInfo(globalCtx, &this->actor, 0.0f, 27.0f, 60.0f, 4);
    }

    if (this->actor.draw == EnBigpo_DrawScoopSoul) {
        Actor_SetHeight(&this->actor, -10.0f);
    } else {
        Actor_SetHeight(&this->actor, 42.0f);
    }

    EnBigpo_UpdateColor(this);
    EnBigpo_FlickerLanternLight(this);

    this->actor.shape.shadowAlpha = this->mainColor.a;
    thisCollider = &this->collider;
    Collider_UpdateCylinder(&this->actor, thisCollider);
    if ((this->collider.base.ocFlags1 & OC1_ON)) {
        CollisionCheck_SetOC(globalCtx, &globalCtx->colChkCtx, &thisCollider->base);
    }
    if ((this->collider.base.atFlags & AT_ON)) {
        CollisionCheck_SetAT(globalCtx, &globalCtx->colChkCtx, &thisCollider->base);
    }
    if ((this->collider.base.acFlags & AC_ON)) {
        CollisionCheck_SetAC(globalCtx, &globalCtx->colChkCtx, &thisCollider->base);
    }

    if (this->unk21C > 0.0f) {
        Math_StepToF(&this->unk21C, 0.0f, 0.05f);
        if (this->mainColor.a != 0xFF) { // NOT fully visible
            if (this->mainColor.a * 0.003921569f < this->mainColor.a) {
                this->unk21C = this->mainColor.a * 0.003921569f;
            }
        }
        this->unk220 = ((this->unk21C + 1.0f) * 0.5f);
        this->unk220 = (this->unk220 > 1.0f) ? 1.0f : this->unk220;
    }
}

// alt update func: the revealed fires under dampe's house
void EnBigpo_UpdateFire(Actor* thisx, GlobalContext* globalCtx) {
    EnBigpo* this = (EnBigpo*)thisx;
    // bilboarding the fire toward player camera?
    this->actor.shape.rot.y = BINANG_ROT180(func_800DFCDC(ACTIVE_CAM));
    this->actionFunc(this, globalCtx);
}

s32 EnBigpo_OverrideLimbDraw2(struct GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3s* rot,
                              struct Actor* actor, Gfx** gfx) {
    EnBigpo* this = (EnBigpo*)actor;
    // not fully invisible
    if ((!((this->mainColor.a != 0x00) && (limbIndex != 7))) ||
        ((this->actionFunc == EnBigpo_BurnAwayDeath) && ((s32)this->idleTimer >= 2))) {
        *dList = NULL;
    }
    return 0;
}

void EnBigpo_PostLimbDraw2(struct GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3s* rot, struct Actor* actor,
                           Gfx** gfx) {
    EnBigpo* this = (EnBigpo*)actor;

    s8 limbByte;
    Vec3f* v1ptr; // todo: figure out better names
    Vec3f* v2ptr;
    Vec3f unusedVec;
    s32 i;

    OPEN_DISPS(globalCtx->state.gfxCtx);

    if ((this->actionFunc == EnBigpo_BurnAwayDeath) && (this->idleTimer >= 2) && (limbIndex == 8)) {
        gSPMatrix((*gfx)++, Matrix_NewMtx(globalCtx->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        gSPDisplayList((*gfx)++, &D_060058B8);
    }

    if (limbIndex == 7) {
        // we scale the vec3f... then do nothing with it?
        SysMatrix_GetStateTranslationAndScaledY(1400.0f, &unusedVec);
        if ((this->actionFunc == EnBigpo_BurnAwayDeath) && (this->idleTimer >= 0x13)) {
            if (actor->scale.x != 0.0f) {
                Matrix_Scale(0.014f / actor->scale.x, 0.014f / actor->scale.x, 0.014f / actor->scale.x, 1);
            }
        }
        SysMatrix_CopyCurrentState(&this->drawMtxF);
    }

    limbByte = D_80B65078[limbIndex];
    if (limbByte != -1) {
        if (limbByte < 3) {
            SysMatrix_GetStateTranslation(&this->limbPos[limbByte]);
            return;
        }
        if (limbByte == 3) {
            SysMatrix_GetStateTranslationAndScaledX(3000.0f, &this->limbPos[limbByte]);
            return;
        }
        if (limbByte == 4) {
            SysMatrix_GetStateTranslationAndScaledY(-2000.0f, &this->limbPos[limbByte]);
            return;
        }

        v2ptr = &this->limbPos[limbByte + 1];
        v1ptr = D_80B65084;
        SysMatrix_GetStateTranslationAndScaledX(-4000.0f, &this->limbPos[limbByte]);

        for (i = limbByte + 1; i < 9; i++) {
            SysMatrix_MultiplyVector3fByState(v1ptr, v2ptr);
            v2ptr++;
            v1ptr++;
        }
    }
    CLOSE_DISPS(globalCtx->state.gfxCtx);
}

// one of the two main draws
void EnBigpo_Draw1(Actor* thisx, GlobalContext* globalCtx) {
    EnBigpo* this = (EnBigpo*)thisx;
    Gfx* dispHead;

    OPEN_DISPS(globalCtx->state.gfxCtx);

    if ((this->mainColor.a == 0xFF) || (this->mainColor.a == 0)) {
        // fully visible OR fully transparent
        dispHead = POLY_OPA_DISP;
        gSPDisplayList(dispHead, &sSetupDL[6 * 0x19]);
        gSPSegment(dispHead + 1, 0x0C, &D_801AEFA0);
        gSPSegment(dispHead + 2, 0x08,
                   Gfx_EnvColor(globalCtx->state.gfxCtx, this->mainColor.r, this->mainColor.g, this->mainColor.b,
                                this->mainColor.a));
        POLY_OPA_DISP = SkelAnime_Draw2(globalCtx, this->skelAnime.skeleton, this->skelAnime.limbDrawTbl,
                                        EnBigpo_OverrideLimbDraw2, EnBigpo_PostLimbDraw2, &this->actor, dispHead + 3);

    } else {
        dispHead = POLY_XLU_DISP;
        gSPDisplayList(dispHead, &sSetupDL[6 * 0x19]);
        gSPSegment(dispHead + 1, 0x0C, &D_801AEF88);
        gSPSegment(dispHead + 2, 0x08,
                   Gfx_EnvColor(globalCtx->state.gfxCtx, this->mainColor.r, this->mainColor.g, this->mainColor.b,
                                this->mainColor.a));
        POLY_XLU_DISP = SkelAnime_Draw2(globalCtx, this->skelAnime.skeleton, this->skelAnime.limbDrawTbl,
                                        EnBigpo_OverrideLimbDraw2, EnBigpo_PostLimbDraw2, &this->actor, dispHead + 3);
    }

    func_800BE680(globalCtx, &this->actor, this->limbPos, 9, this->actor.scale.x * 71.428566f * this->unk220, 0,
                  this->unk21C, 0x14);

    SysMatrix_SetCurrentState(&this->drawMtxF);
    EnBigpo_DrawLantern(&this->actor, globalCtx);
    if (this->actionFunc == EnBigpo_SpawnPoCutscene6) {
        // call the other unk draw func
        EnBigpo_Draw4(&this->actor, globalCtx);
    }

    CLOSE_DISPS(globalCtx->state.gfxCtx);
}

void EnBigpo_DrawScoopSoul(Actor* thisx, GlobalContext* globalCtx) {
    EnBigpo* this = (EnBigpo*)thisx;
    s32 pad;

    OPEN_DISPS(globalCtx->state.gfxCtx);

    func_8012C2DC(globalCtx->state.gfxCtx);

    gSPSegment(POLY_XLU_DISP++, 0x08,
               Gfx_TwoTexScroll(globalCtx->state.gfxCtx, 0, 0, 0, 0x20, 0x40, 1, 0,
                                (globalCtx->gameplayFrames * -0xF) & 0x1FF, 0x20, 0x80));

    gDPSetPrimColor(POLY_XLU_DISP++, 0x80, 0x80, 0xFF, 0xFF, 0xAA, this->mainColor.a);

    gDPSetEnvColor(POLY_XLU_DISP++, this->mainColor.r, this->mainColor.g, this->mainColor.b, 0xFF);

    Lights_PointNoGlowSetInfo(&this->fires[0].info, this->actor.world.pos.x, this->actor.world.pos.y,
                              this->actor.world.pos.z, this->mainColor.r, this->mainColor.g, this->mainColor.b,
                              this->mainColor.a * 2);

    Matrix_RotateY(BINANG_ROT180(func_800DFCDC(ACTIVE_CAM)), MTXMODE_APPLY);

    gSPMatrix(POLY_XLU_DISP++, Matrix_NewMtx(globalCtx->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);

    gSPDisplayList(POLY_XLU_DISP++, &D_06001BB0);

    CLOSE_DISPS(globalCtx->state.gfxCtx);
}

// this matches without OPENDISPS but with it has stack issues, might be able to find an alternative match with the
// macros
void EnBigpo_DrawLantern(Actor* thisx, GlobalContext* globalCtx) {
    EnBigpo* this = (EnBigpo*)thisx;
    f32 magnitude;
    f32 magnitude2;
    Gfx* dispHead;
    Vec3f vec1;
    Vec3f vec2;
    Camera* cam = ACTIVE_CAM;

    if (cam != NULL) {
        Math_Vec3f_Diff(&cam->eye, &cam->at, &vec1);
        magnitude = Math3D_Vec3fMagnitude(&vec1);
        magnitude2 = (magnitude > 1.0f) ? (20.0f / magnitude) : (20.0f);
        Math_Vec3f_Scale(&vec1, magnitude2);
    } else {
        Math_Vec3f_Copy(&vec1, &D_801D15B0);
    }

    {
        GraphicsContext* gfx = globalCtx->state.gfxCtx;

        // fully visible OR fully transparent
        if ((this->mainColor.a == 255) || (this->mainColor.a == 0)) {
            Scene_SetRenderModeXlu(globalCtx, 0, 1);
            dispHead = gfx->polyOpa.p;
        } else {
            Scene_SetRenderModeXlu(globalCtx, 1, 2);
            dispHead = gfx->polyXlu.p;
        }

        gSPDisplayList(&dispHead[0], &sSetupDL[6 * 0x19]);

        gSPSegment(&dispHead[1], 0x0A, Gfx_EnvColor(globalCtx->state.gfxCtx, 160, 0, 255, this->mainColor.a));

        SysMatrix_GetStateTranslationAndScaledY(1400.0f, &vec2);
        Lights_PointGlowSetInfo(&this->fires[0].info, vec2.x + vec1.x, vec2.y + vec1.y, vec2.z + vec1.z,
                                this->lanternColor.r, this->lanternColor.g, this->lanternColor.b, this->lanternColor.a);

        gDPSetEnvColor(&dispHead[2], this->lanternColor.r, this->lanternColor.g, this->lanternColor.b,
                       this->mainColor.a);

        gSPMatrix(&dispHead[3], Matrix_NewMtx(globalCtx->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);

        gSPDisplayList(&dispHead[4], &D_060042C8);

        gSPDisplayList(&dispHead[5], &D_060043F8);

        // fully transparent OR fully invisible
        if ((this->mainColor.a == 255) || (this->mainColor.a == 0)) {
            gfx->polyOpa.p = &dispHead[6];
        } else {
            gfx->polyXlu.p = &dispHead[6];
        }
    }
}

// one of the main draws
// but also called by another draw function
void EnBigpo_Draw4(Actor* thisx, GlobalContext* globalCtx) {
    EnBigpo* this = (EnBigpo*)thisx;
    s32 pad[3];
    s16 fireRadius;
    MtxF* mtfxPtr;
    s32 i;

    mtfxPtr = SysMatrix_GetCurrentState();
    OPEN_DISPS(globalCtx->state.gfxCtx);

    func_8012C2DC(globalCtx->state.gfxCtx);
    Matrix_RotateY(BINANG_ROT180(func_800DFCDC(ACTIVE_CAM)), MTXMODE_NEW);
    if (this->actionFunc == EnBigpo_SpawnPoCutscene6) {
        Matrix_Scale(0.01f, 0.01f, 0.01f, 1);
        fireRadius = 0x1F4;
    } else {
        Matrix_Scale(thisx->scale.x, thisx->scale.y, thisx->scale.z, 1);
        fireRadius = (s16)(thisx->scale.x * 500.0f * 100.0f);
    }
    gSPSegment(POLY_XLU_DISP++, 0x08,
               Gfx_TwoTexScroll(globalCtx->state.gfxCtx, 0, 0, 0, 0x20, 0x40, 1, 0,
                                ((s32)globalCtx->gameplayFrames * -0x14) & 0x1FF, 0x20, 0x80));

    gDPSetPrimColor(POLY_XLU_DISP++, 0x80, 0x80, 0xAA, 0xFF, 0xFF, 0xFF - this->mainColor.a);
    gDPSetEnvColor(POLY_XLU_DISP++, 0, 0, 0xFF, 0xFF);

    for (i = 0; i < 3; i++) {
        EnBigpoFireParticle* firePtr = &this->fires[i];
        Lights_PointNoGlowSetInfo(&this->fires[i].info, this->fires[i].pos.x, this->fires[i].pos.y,
                                  this->fires[i].pos.z, 0xAA, 0xFF, 0xFF, fireRadius);
        mtfxPtr->wx = firePtr->pos.x;
        mtfxPtr->wy = firePtr->pos.y;
        mtfxPtr->wz = firePtr->pos.z;

        gSPMatrix(POLY_XLU_DISP++, Matrix_NewMtx(globalCtx->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);

        gSPDisplayList(POLY_XLU_DISP++, &D_0407D590); // flame displaylist
    }

    CLOSE_DISPS(globalCtx->state.gfxCtx);
}

// the fires dug up by dampe
void EnBigpo_DrawFire(Actor* thisx, GlobalContext* globalCtx) {
    EnBigpo* this = (EnBigpo*)thisx;
    EnBigpo* parent = (EnBigpo*)thisx->parent;
    s32 pad;

    OPEN_DISPS(globalCtx->state.gfxCtx);

    func_8012C2DC(globalCtx->state.gfxCtx);

    gSPSegment(POLY_XLU_DISP++, 0x08,
               Gfx_TwoTexScroll(globalCtx->state.gfxCtx, 0, 0, 0, 0x20, 0x40, 1, 0,
                                ((s32)globalCtx->gameplayFrames * -0x14) & 0x1FF, 0x20, 0x80));

    gDPSetPrimColor(POLY_XLU_DISP++, 0x80, 0x80, 0xAA, 0xFF, 0xFF, 0xFF);
    gDPSetEnvColor(POLY_XLU_DISP++, 0, 0, 0xFF, 0xFF);

    Lights_PointNoGlowSetInfo(&parent->fires[this->unk20C].info, thisx->world.pos.x, thisx->world.pos.y,
                              thisx->world.pos.z, 0xAA, 0xFF, 0xFF, (s32)(thisx->scale.x * 500.0f * 100.0f));

    gSPMatrix(POLY_XLU_DISP++, Matrix_NewMtx(globalCtx->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);

    gSPDisplayList(POLY_XLU_DISP++, &D_0407D590); // flame displaylist

    CLOSE_DISPS(globalCtx->state.gfxCtx);
}
