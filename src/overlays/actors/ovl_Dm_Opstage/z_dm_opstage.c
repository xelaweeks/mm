/*
 * File: z_dm_opstage.c
 * Overlay: ovl_Dm_Opstage
 * Description: Lost Woods cutscene objects
 */

#include "z_dm_opstage.h"
#include "objects/object_keikoku_demo/object_keikoku_demo.h"

#define FLAGS (ACTOR_FLAG_10 | ACTOR_FLAG_20)

#define THIS ((DmOpstage*)thisx)

void DmOpstage_Init(Actor* thisx, GlobalContext* globalCtx);
void DmOpstage_Destroy(Actor* thisx, GlobalContext* globalCtx);
void DmOpstage_Update(Actor* thisx, GlobalContext* globalCtx);
void DmOpstage_Draw(Actor* thisx, GlobalContext* globalCtx);

void DmOpstage_SetupAction(DmOpstage* this, DmOpstageActionFunc actionFunc);
void func_80A9FA58(DmOpstage* this, GlobalContext* globalCtx);

const ActorInit Dm_Opstage_InitVars = {
    ACTOR_DM_OPSTAGE,
    ACTORCAT_ITEMACTION,
    FLAGS,
    OBJECT_KEIKOKU_DEMO,
    sizeof(DmOpstage),
    (ActorFunc)DmOpstage_Init,
    (ActorFunc)DmOpstage_Destroy,
    (ActorFunc)DmOpstage_Update,
    (ActorFunc)DmOpstage_Draw,
};

static InitChainEntry sInitChain[] = {
    ICHAIN_F32(uncullZoneScale, 300, ICHAIN_STOP),
};

void DmOpstage_SetupAction(DmOpstage* this, DmOpstageActionFunc actionFunc) {
    this->actionFunc = actionFunc;
}

void DmOpstage_Init(Actor* thisx, GlobalContext* globalCtx) {
    DmOpstage* this = THIS;

    Actor_ProcessInitChain(&this->dyna.actor, sInitChain);
    DmOpstage_SetupAction(this, func_80A9FA58);
    Actor_SetScale(&this->dyna.actor, 0.1f);
    if (DMOPSTAGE_GET_TYPE(&this->dyna.actor) == 0) {
        DynaPolyActor_Init(&this->dyna, 0);
        DynaPolyActor_LoadMesh(globalCtx, &this->dyna, &object_keikoku_demo_Colheader_001C98);
    }
    if (DMOPSTAGE_GET_TYPE(&this->dyna.actor) > 0) {
        this->posX = this->dyna.actor.world.pos.x;
        this->posY = this->dyna.actor.world.pos.y;
        this->posZ = this->dyna.actor.world.pos.z;
        this->dyna.actor.world.pos.x = 0.0f;
        this->dyna.actor.world.pos.y = 0.0f;
        this->dyna.actor.world.pos.z = 0.0f;
    }
}

void DmOpstage_Destroy(Actor* thisx, GlobalContext* globalCtx) {
    DmOpstage* this = THIS;

    if (DMOPSTAGE_GET_TYPE(thisx) == 0) {
        DynaPoly_DeleteBgActor(globalCtx, &globalCtx->colCtx.dyna, this->dyna.bgId);
    }
}

void func_80A9FA58(DmOpstage* this, GlobalContext* globalCtx) {
    s32 actionIndex;

    if (DMOPSTAGE_GET_TYPE(&this->dyna.actor) == 0) {
        if (Cutscene_CheckActorAction(globalCtx, 115)) {
            actionIndex = Cutscene_GetActorActionIndex(globalCtx, 115);
            if (globalCtx->csCtx.actorActions[actionIndex]->action == 2) {
                this->dyna.actor.scale.x = 0.075f;
                this->dyna.actor.scale.z = 0.3f;
            } else {
                this->dyna.actor.scale.x = 0.1f;
                this->dyna.actor.scale.z = 0.1f;
            }
            Cutscene_ActorTranslateAndYaw(&this->dyna.actor, globalCtx, actionIndex);
        }
    } else if (Cutscene_CheckActorAction(globalCtx, (DMOPSTAGE_GET_08(&this->dyna.actor) + 0x74))) {
        Cutscene_ActorTranslateAndYaw(
            &this->dyna.actor, globalCtx,
            Cutscene_GetActorActionIndex(globalCtx, (DMOPSTAGE_GET_08(&this->dyna.actor) + 0x74)));
    }
}

void DmOpstage_Update(Actor* thisx, GlobalContext* globalCtx) {
    DmOpstage* this = THIS;

    this->actionFunc(this, globalCtx);
    if ((globalCtx->sceneNum == SCENE_SPOT00) && (gSaveContext.sceneSetupIndex == 0) &&
        (globalCtx->csCtx.frames == 480)) {
        func_8019F128(NA_SE_EV_NAVY_FLY_REBIRTH);
    }
}

void DmOpstage_Draw(Actor* thisx, GlobalContext* globalCtx) {
    DmOpstage* this = THIS;

    if (DMOPSTAGE_GET_TYPE(thisx) > 0) {
        Matrix_Translate(this->dyna.actor.world.pos.x + this->posX, this->dyna.actor.world.pos.y + this->posY,
                         this->dyna.actor.world.pos.z + this->posZ, MTXMODE_NEW);
        Matrix_RotateYS(this->dyna.actor.world.rot.y, MTXMODE_APPLY);
        Matrix_Scale(0.1f, 0.1f, 0.1f, MTXMODE_APPLY);
    }
    switch (DMOPSTAGE_GET_TYPE(thisx)) {
        case 0:
            Gfx_DrawDListOpa(globalCtx, object_keikoku_demo_DL_000978);
            Gfx_DrawDListXlu(globalCtx, object_keikoku_demo_DL_000970);
            return;

        case 1:
            Gfx_DrawDListOpa(globalCtx, object_keikoku_demo_DL_002878);
            Gfx_DrawDListXlu(globalCtx, object_keikoku_demo_DL_002870);
            return;

        case 2:
            Gfx_DrawDListOpa(globalCtx, object_keikoku_demo_DL_003068);
            Gfx_DrawDListXlu(globalCtx, object_keikoku_demo_DL_003060);
            return;

        case 3:
            Gfx_DrawDListOpa(globalCtx, object_keikoku_demo_DL_003728);
            Gfx_DrawDListXlu(globalCtx, object_keikoku_demo_DL_003720);
            return;
    }
}
