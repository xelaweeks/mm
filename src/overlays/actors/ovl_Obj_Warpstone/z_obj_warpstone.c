#include "z_obj_warpstone.h"

#define FLAGS 0x00000009

#define THIS ((ObjWarpstone*)thisx)

void ObjWarpstone_Init(Actor* thisx, GlobalContext* globalCtx);
void ObjWarpstone_Destroy(Actor* thisx, GlobalContext* globalCtx);
void ObjWarpstone_Update(Actor* thisx, GlobalContext* globalCtx);
void ObjWarpstone_Draw(Actor* thisx, GlobalContext* globalCtx);
void ObjWarpstone_SetupAction(ObjWarpstone* this, ObjWarpstoneActionFunc actionFunc);
s32 ObjWarpstone_ClosedIdle(ObjWarpstone* this, GlobalContext* globalCtx);
s32 ObjWarpstone_BeginOpeningCutscene(ObjWarpstone* this, GlobalContext* globalCtx);
s32 ObjWarpstone_PlayOpeningCutscene(ObjWarpstone* this, GlobalContext* globalCtx);
s32 ObjWarpstone_OpenedIdle(ObjWarpstone* this, GlobalContext* globalCtx);

extern Gfx D_04023210[]; // gOwlStatueWhiteFlashDL
extern Gfx D_060001D0[]; // gOwlStatueClosedDL
extern Gfx D_06003770[]; // gOwlStatueOpenedDL

const ActorInit Obj_Warpstone_InitVars = {
    ACTOR_OBJ_WARPSTONE,
    ACTORCAT_ITEMACTION,
    FLAGS,
    OBJECT_SEK,
    sizeof(ObjWarpstone),
    (ActorFunc)ObjWarpstone_Init,
    (ActorFunc)ObjWarpstone_Destroy,
    (ActorFunc)ObjWarpstone_Update,
    (ActorFunc)ObjWarpstone_Draw,
};

static ColliderCylinderInit sCylinderInit = {
    {
        COLTYPE_METAL,
        AT_NONE,
        AC_ON | AC_HARD | AC_TYPE_PLAYER,
        OC1_ON | OC1_TYPE_ALL,
        OC2_TYPE_2,
        COLSHAPE_CYLINDER,
    },
    {
        ELEMTYPE_UNK2,
        { 0x00100000, 0x00, 0x00 },
        { 0x01000202, 0x00, 0x00 },
        TOUCH_NONE | TOUCH_SFX_NORMAL,
        BUMP_ON | BUMP_HOOKABLE,
        OCELEM_ON,
    },
    { 20, 60, 0, { 0, 0, 0 } },
};

static InitChainEntry sInitChain[] = {
    ICHAIN_U8(targetMode, 1, ICHAIN_STOP),
};

static Gfx* sOwlStatueDLs[] = { D_060001D0, D_06003770 };

void ObjWarpstone_SetupAction(ObjWarpstone* this, ObjWarpstoneActionFunc actionFunc) {
    this->actionFunc = actionFunc;
}

void ObjWarpstone_Init(Actor* thisx, GlobalContext* globalCtx) {
    ObjWarpstone* this = THIS;

    Actor_ProcessInitChain(&this->dyna.actor, sInitChain);
    Collider_InitAndSetCylinder(globalCtx, &this->collider, &this->dyna.actor, &sCylinderInit);
    Actor_SetHeight(&this->dyna.actor, 40.0f);

    if (!IS_OWL_HIT(GET_OWL_ID(this))) {
        ObjWarpstone_SetupAction(this, ObjWarpstone_ClosedIdle);
    } else {
        ObjWarpstone_SetupAction(this, ObjWarpstone_OpenedIdle);
        this->modelIndex = SEK_MODEL_OPENED;
    }
}

void ObjWarpstone_Destroy(Actor* thisx, GlobalContext* globalCtx) {
    ObjWarpstone* this = THIS;

    Collider_DestroyCylinder(globalCtx, &this->collider);
}

s32 ObjWarpstone_ClosedIdle(ObjWarpstone* this, GlobalContext* globalCtx) {
    if (this->collider.base.acFlags & AC_HIT) {
        ObjWarpstone_SetupAction(this, ObjWarpstone_BeginOpeningCutscene);
        return true;
    } else {
        /*Ye who hold the sacred sword, leave proof of our encounter.*/
        this->dyna.actor.textId = 0xC00;
        return false;
    }
}

s32 ObjWarpstone_BeginOpeningCutscene(ObjWarpstone* this, GlobalContext* globalCtx) {
    if (this->dyna.actor.cutscene < 0 || ActorCutscene_GetCanPlayNext(this->dyna.actor.cutscene)) {
        ActorCutscene_StartAndSetUnkLinkFields(this->dyna.actor.cutscene, &this->dyna.actor);
        ObjWarpstone_SetupAction(this, ObjWarpstone_PlayOpeningCutscene);
        Audio_PlayActorSound2(&this->dyna.actor, NA_SE_EV_OWL_WARP_SWITCH_ON);
    } else {
        ActorCutscene_SetIntentToPlay(this->dyna.actor.cutscene);
    }
    return true;
}

s32 ObjWarpstone_PlayOpeningCutscene(ObjWarpstone* this, GlobalContext* globalCtx) {
    if (this->timer++ >= OBJ_WARPSTONE_TIMER_DONE) {
        ActorCutscene_Stop(this->dyna.actor.cutscene);
        func_80143A10(GET_OWL_ID(this));
        ObjWarpstone_SetupAction(this, ObjWarpstone_OpenedIdle);
    } else if (this->timer < OBJ_WARPSTONE_TIMER_OPENED) {
        Math_StepToF(&this->dyna.actor.velocity.x, 0.01f, 0.001f);
        Math_StepToS(&this->dyna.actor.home.rot.x, 0xFF, 0x12);
    } else {
        Math_StepToF(&this->dyna.actor.velocity.x, 20.0f, 0.01f);
        if (this->dyna.actor.velocity.x > 0.2f) {
            this->modelIndex = SEK_MODEL_OPENED;
            Math_StepToS(&this->dyna.actor.home.rot.x, 0, 0x14);
        }
    }
    return true;
}

s32 ObjWarpstone_OpenedIdle(ObjWarpstone* this, GlobalContext* globalCtx) {
    /*You can save your progress and quit here.*/
    this->dyna.actor.textId = 0xC01;
    return false;
}

void ObjWarpstone_Update(Actor* thisx, GlobalContext* globalCtx) {
    ObjWarpstone* this = THIS;
    s32 pad;

    if (this->isTalking) {
        if (func_800B867C(&this->dyna.actor, globalCtx) != 0) {
            this->isTalking = false;
        } else if ((func_80152498(&globalCtx->msgCtx) == 4) && (func_80147624(globalCtx))) {
            if (globalCtx->msgCtx.choiceIndex != 0) {
                func_8019F208();
                globalCtx->msgCtx.unk11F22 = 0x4D;
                globalCtx->msgCtx.unk120D6 = 0;
                globalCtx->msgCtx.unk120D4 = 0;
                gSaveContext.owlSaveLocation = GET_OWL_ID(this);
            } else {
                func_801477B4(globalCtx);
            }
        }
    } else if (func_800B84D0(&this->dyna.actor, globalCtx)) {
        this->isTalking = true;
    } else if (!this->actionFunc(this, globalCtx)) {
        func_800B863C(&this->dyna.actor, globalCtx);
    }
    Collider_ResetCylinderAC(globalCtx, &this->collider.base);
    Collider_UpdateCylinder(&this->dyna.actor, &this->collider);
    CollisionCheck_SetOC(globalCtx, &globalCtx->colChkCtx, &this->collider.base);
    CollisionCheck_SetAC(globalCtx, &globalCtx->colChkCtx, &this->collider.base);
}

void ObjWarpstone_Draw(Actor* thisx, GlobalContext* globalCtx2) {
    ObjWarpstone* this = THIS;
    GlobalContext* globalCtx = globalCtx2;

    func_800BDFC0(globalCtx, sOwlStatueDLs[this->modelIndex]);
    if (this->dyna.actor.home.rot.x != 0) {
        OPEN_DISPS(globalCtx->state.gfxCtx);
        func_8012C2DC(globalCtx->state.gfxCtx);
        SysMatrix_InsertTranslation(this->dyna.actor.world.pos.x, this->dyna.actor.world.pos.y + 34.0f,
                                    this->dyna.actor.world.pos.z, MTXMODE_NEW);
        SysMatrix_InsertMatrix(&globalCtx->mf_187FC, MTXMODE_APPLY);
        SysMatrix_InsertTranslation(0.0f, 0.0f, 30.0f, MTXMODE_APPLY);
        Matrix_Scale(this->dyna.actor.velocity.x, this->dyna.actor.velocity.x, this->dyna.actor.velocity.x,
                     MTXMODE_APPLY);
        SysMatrix_StatePush();
        gDPPipeSync(POLY_XLU_DISP++);
        gDPSetPrimColor(POLY_XLU_DISP++, 128, 128, 255, 255, 200, this->dyna.actor.home.rot.x);
        gDPSetEnvColor(POLY_XLU_DISP++, 100, 200, 0, 255);
        SysMatrix_InsertZRotation_f((((globalCtx->gameplayFrames * 1500) & 0xFFFF) * M_PI) / 0x8000, MTXMODE_APPLY);
        gSPMatrix(POLY_XLU_DISP++, Matrix_NewMtx(globalCtx->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        gSPDisplayList(POLY_XLU_DISP++, D_04023210);
        SysMatrix_StatePop();
        SysMatrix_InsertZRotation_f((~((globalCtx->gameplayFrames * 1200) & 0xFFFF) * M_PI) / 0x8000, MTXMODE_APPLY);
        gSPMatrix(POLY_XLU_DISP++, Matrix_NewMtx(globalCtx->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        gSPDisplayList(POLY_XLU_DISP++, D_04023210);
        CLOSE_DISPS(globalCtx->state.gfxCtx);
    }
}
