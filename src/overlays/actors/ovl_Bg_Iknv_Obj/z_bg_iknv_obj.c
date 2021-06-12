#include "z_bg_iknv_obj.h"

#define FLAGS 0x00000010

#define THIS ((BgIknvObj*)thisx)

void BgIknvObj_Init(Actor* thisx, GlobalContext* globalCtx);
void BgIknvObj_Destroy(Actor* thisx, GlobalContext* globalCtx);
void BgIknvObj_Update(Actor* thisx, GlobalContext* globalCtx);
void BgIknvObj_Draw(Actor* thisx, GlobalContext* globalCtx);

void BgIknvObj_DoNothing(BgIknvObj* this, GlobalContext* globalCtx);
void BgIknvObj_UpdateType0(BgIknvObj* this, GlobalContext* globalCtx);
void BgIknvObj_UpdateType1(BgIknvObj* this, GlobalContext* globalCtx);
void BgIknvObj_UpdateType2(BgIknvObj* this, GlobalContext* globalCtx);

extern CollisionHeader D_060119D4;
extern CollisionHeader D_06012CA4;
extern Gfx D_06011880[];
extern Gfx D_060129C8[];
extern Gfx D_06013058[];

const ActorInit Bg_Iknv_Obj_InitVars = {
    ACTOR_BG_IKNV_OBJ,
    ACTORCAT_BG,
    FLAGS,
    OBJECT_IKNV_OBJ,
    sizeof(BgIknvObj),
    (ActorFunc)BgIknvObj_Init,
    (ActorFunc)BgIknvObj_Destroy,
    (ActorFunc)BgIknvObj_Update,
    (ActorFunc)BgIknvObj_Draw,
};

static ColliderCylinderInit sCylinderInit = {
    { 
        COLTYPE_NONE, 
        AT_NONE,
        AC_ON | AC_TYPE_ENEMY, 
        OC1_ON | OC1_TYPE_ALL, 
        OC2_TYPE_1, 
        COLSHAPE_CYLINDER, 
    },
    { 
        ELEMTYPE_UNK0, 
        { 0x00000000, 0x00, 0x00 }, 
        { 0xF7CFFFFF, 0x00, 0x00 }, 
        TOUCH_NONE | TOUCH_SFX_NORMAL, 
        BUMP_ON, 
        OCELEM_ON, 
    },
    { 40, 40, 0, { 0, 0, 0 } },
};

void BgIknvObj_Init(Actor* thisx, GlobalContext* globalCtx) {
    s32 pad;
    BgIknvObj* this = THIS;
    CollisionHeader* colHeader = NULL;

    Actor_SetScale(&this->dyna.actor, 0.1f);
    this->actionFunc = BgIknvObj_DoNothing;
    switch (IKNV_OBJ_TYPE(this)) {
        case BG_IKNV_OBJ_TYPE_UNK0: {
            this->displayListPtr = D_06013058;
            this->actionFunc = BgIknvObj_UpdateType0;
            this->dyna.actor.flags |= 0x100000;
            this->dyna.actor.flags |= 0x10;
            return;
        }
        case BG_IKNV_OBJ_TYPE_UNK1: {
            this->displayListPtr = D_06011880;
            BcCheck3_BgActorInit(&this->dyna, 0);
            BgCheck_RelocateMeshHeader(&D_060119D4, &colHeader);
            this->dyna.bgId = BgCheck_AddActorMesh(globalCtx, &globalCtx->colCtx.dyna, &this->dyna, colHeader);
            this->actionFunc = BgIknvObj_UpdateType1;
            this->dyna.actor.world.pos.y = this->dyna.actor.home.pos.y + 120.0f;
            return;
        }
        case BG_IKNV_OBJ_TYPE_UNK2: {
            this->displayListPtr = D_060129C8;
            this->actionFunc = BgIknvObj_UpdateType2;
            BcCheck3_BgActorInit(&this->dyna, 0);
            BgCheck_RelocateMeshHeader(&D_06012CA4, &colHeader);
            this->dyna.bgId = BgCheck_AddActorMesh(globalCtx, &globalCtx->colCtx.dyna, &this->dyna, colHeader);
            Collider_InitAndSetCylinder(globalCtx, &this->collider, &this->dyna.actor, &sCylinderInit);
            Collider_UpdateCylinder(&this->dyna.actor, &this->collider);
            this->dyna.actor.colChkInfo.mass = 0xFF;
            gSaveContext.weekEventReg[0x33] &= 0xEF;
            Actor_SetHeight(&this->dyna.actor, IREG(88));
            return;
        }
    }

    Actor_MarkForDeath(&this->dyna.actor);
}

void BgIknvObj_Destroy(Actor* thisx, GlobalContext* globalCtx) {
    BgIknvObj* this = THIS;

    if (IKNV_OBJ_TYPE(this) != BG_IKNV_OBJ_TYPE_UNK1) {
        if (IKNV_OBJ_TYPE(this) == BG_IKNV_OBJ_TYPE_UNK2) {
            Collider_DestroyCylinder(globalCtx, &this->collider);
            gSaveContext.weekEventReg[0x33] &= 0xEF;
        } else {
            return;
        }
    }
    BgCheck_RemoveActorMesh(globalCtx, &globalCtx->colCtx.dyna, this->dyna.bgId);
}

s32 func_80BD7CEC(BgIknvObj* this) {
    if (this->dyna.actor.cutscene == -1) {
        return 1;
    }

    if (ActorCutscene_GetCurrentIndex() == this->dyna.actor.cutscene) {
        return 1;
    }

    if (ActorCutscene_GetCanPlayNext(this->dyna.actor.cutscene)) {
        ActorCutscene_StartAndSetUnkLinkFields(this->dyna.actor.cutscene, &this->dyna.actor);
        return 1;
    }

    ActorCutscene_SetIntentToPlay(this->dyna.actor.cutscene);
    return 0;
}

void BgIknvObj_UpdateType0(BgIknvObj* this, GlobalContext* globalCtx) {
    if (gSaveContext.weekEventReg[0xE] & 4) {
        this->dyna.actor.shape.rot.z += -0x64;
        func_800B9098(&this->dyna.actor);
        func_800B9010(&this->dyna.actor, 0x21AA);
    }

    if (globalCtx->csCtx.state != 0 && gSaveContext.sceneSetupIndex == 1 && globalCtx->csCtx.unk12 == 4 &&
        globalCtx->csCtx.frames == 0x5D7) {
        func_8019F128(0x29A9);
    }
}

s32 func_80BD7E0C(BgIknvObj* this, s16 homeRotation, GlobalContext* globalCtx) {
    this->dyna.actor.shape.yOffset = 0.0f;
    CollisionCheck_SetOC(globalCtx, &globalCtx->colCheckCtx, &this->collider.base);
    if (homeRotation != this->dyna.actor.shape.rot.y) {
        Math_SmoothStepToS(&this->dyna.actor.shape.rot.y, homeRotation, 2, 100, 100);
        this->dyna.actor.world.rot.y = this->dyna.actor.shape.rot.y;
        if ((globalCtx->gameplayFrames & 1) != 0) {
            this->dyna.actor.shape.yOffset = 5.0f;
        }
        func_800B9010(&this->dyna.actor, NA_SE_EV_STONEDOOR_OPEN_S - SFX_FLAG);
        return 0;
    }
    Audio_PlayActorSound2(&this->dyna.actor, NA_SE_EV_STONEDOOR_STOP);
    return 1;
}

void func_80BD7ED8(BgIknvObj* this, GlobalContext* globalCtx) {
    if (func_80BD7E0C(this, this->dyna.actor.home.rot.y, globalCtx)) {
        this->actionFunc = BgIknvObj_UpdateType2;
        gSaveContext.weekEventReg[0x33] &= 0xEF;
    }
    CollisionCheck_SetOC(globalCtx, &globalCtx->colCheckCtx, &this->collider.base);
}

void func_80BD7F4C(BgIknvObj* this, GlobalContext* globalCtx) {
    if (gSaveContext.time >= 0xD001) {
        this->actionFunc = func_80BD7ED8;
    }
    if (this->dyna.actor.home.rot.x == 1 && (gSaveContext.weekEventReg[0x3A] & 0x80) == 0) {
        ActorCutscene_Stop(this->dyna.actor.cutscene);
        this->dyna.actor.home.rot.x = 0;
    }
    CollisionCheck_SetOC(globalCtx, &globalCtx->colCheckCtx, &this->collider.base);
}

void func_80BD7FDC(BgIknvObj* this, GlobalContext* globalCtx) {
    if (func_80BD7E0C(this, this->dyna.actor.home.rot.y + 0x4000, globalCtx)) {
        this->actionFunc = func_80BD7F4C;
        gSaveContext.weekEventReg[0x33] |= 0x10;
        this->dyna.actor.home.rot.x = 1;
    }
}

void func_80BD8040(BgIknvObj* this, GlobalContext* globalCtx) {
    if (func_80BD7CEC(this)) {
        this->actionFunc = func_80BD7FDC;
    }
    CollisionCheck_SetOC(globalCtx, &globalCtx->colCheckCtx, &this->collider.base);
}

void BgIknvObj_UpdateType2(BgIknvObj* this, GlobalContext* globalCtx) {
    if ((gSaveContext.weekEventReg[0x3A] & 0x80) != 0) {
        this->actionFunc = func_80BD8040;
        gSaveContext.weekEventReg[0x59] |= 0x80;
    }
    CollisionCheck_SetOC(globalCtx, &globalCtx->colCheckCtx, &this->collider.base);
}

void BgIknvObj_UpdateType1(BgIknvObj* this, GlobalContext* globalCtx) {
}

void BgIknvObj_DoNothing(BgIknvObj* this, GlobalContext* globalCtx) {
}

void BgIknvObj_Update(Actor* thisx, GlobalContext* globalCtx) {
    BgIknvObj* this = THIS;

    this->actionFunc(this, globalCtx);
}

void BgIknvObj_Draw(Actor* thisx, GlobalContext* globalCtx) {
    BgIknvObj* this = THIS;

    OPEN_DISPS(globalCtx->state.gfxCtx);
    gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(globalCtx->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    func_8012C28C(globalCtx->state.gfxCtx);
    gSPDisplayList(POLY_OPA_DISP++, this->displayListPtr);
    CLOSE_DISPS(globalCtx->state.gfxCtx);
}
