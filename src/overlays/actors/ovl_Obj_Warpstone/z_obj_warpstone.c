#include "z_obj_warpstone.h"

#define FLAGS 0x00000009

#define THIS ((ObjWarpstone*)thisx)

void ObjWarpstone_Init(Actor* thisx, GlobalContext* globalCtx);
void ObjWarpstone_Destroy(Actor* thisx, GlobalContext* globalCtx);
void ObjWarpstone_Update(Actor* thisx, GlobalContext* globalCtx);
void ObjWarpstone_Draw(Actor* thisx, GlobalContext* globalCtx);
void func_80B92B10(Actor* thisx, GlobalContext* globalCtx);
void func_80B92C00(Actor* thisx, s32 arg1);
void func_80B92DC4(Actor* thisx, s32 arg1);

extern Gfx D_04023210[];
extern Gfx D_060001D0[];
extern Gfx D_06003770[];

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


// static ColliderCylinderInit sCylinderInit = {
static ColliderCylinderInit D_80B93220 = {
    { COLTYPE_METAL, AT_NONE, AC_ON | AC_HARD | AC_TYPE_PLAYER, OC1_ON | OC1_TYPE_ALL, OC2_TYPE_2, COLSHAPE_CYLINDER, },
    { ELEMTYPE_UNK2, { 0x00100000, 0x00, 0x00 }, { 0x01000202, 0x00, 0x00 }, TOUCH_NONE | TOUCH_SFX_NORMAL, BUMP_ON | BUMP_HOOKABLE, OCELEM_ON, },
    { 20, 60, 0, { 0, 0, 0 } },
};


// static InitChainEntry sInitChain[] = {
static InitChainEntry D_80B9324C[] = {
    ICHAIN_U8(targetMode, 1, ICHAIN_STOP),
};

static Gfx* D_80B93250[] = {D_060001D0, D_06003770};

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Warpstone_0x80B92B10/func_80B92B10.asm")

/*#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Warpstone_0x80B92B10/ObjWarpstone_Init.asm")*/

void ObjWarpstone_Init(Actor* thisx, GlobalContext* globalCtx) {
    ObjWarpstone* this = THIS;

    Actor_ProcessInitChain(&this->actor, D_80B9324C);
    Collider_InitAndSetCylinder(globalCtx, &this->collider, &this->actor, &D_80B93220);
    Actor_SetHeight(&this->actor, 40.0f);
    if (!IS_OWL_HIT(GET_OWL_ID(this))) {
        func_80B92B10(&this->actor, func_80B92C00);
    } else {
        func_80B92B10(&this->actor, func_80B92DC4);
        this->unk1AA = 1;
    }
}

/*#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Warpstone_0x80B92B10/ObjWarpstone_Destroy.asm")*/

void ObjWarpstone_Destroy(Actor* thisx, GlobalContext *globalCtx) {
    ObjWarpstone* this = THIS;

    Collider_DestroyCylinder(globalCtx, &this->collider);
}

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Warpstone_0x80B92B10/func_80B92C00.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Warpstone_0x80B92B10/func_80B92C48.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Warpstone_0x80B92B10/func_80B92CD0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Warpstone_0x80B92B10/func_80B92DC4.asm")

/*#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Warpstone_0x80B92B10/ObjWarpstone_Update.asm")*/

void ObjWarpstone_Update(Actor* thisx, GlobalContext* globalCtx) {
    ObjWarpstone* this = THIS;
    s32 pad;

    if (this->unk1A8 != 0) {
        if (func_800B867C(&this->actor, globalCtx) != 0) {
            this->unk1A8 = 0;
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
    } else if (func_800B84D0(&this->actor, globalCtx)) {
        this->unk1A8 = 1;
    } else if (!this->actionFunc(this, globalCtx)) {
        func_800B863C(&this->actor, globalCtx);
    }
    Collider_ResetCylinderAC(globalCtx, &this->collider.base);
    Collider_UpdateCylinder(&this->actor, &this->collider.base);
    CollisionCheck_SetOC(globalCtx, &globalCtx->colChkCtx, &this->collider.base);
    CollisionCheck_SetAC(globalCtx, &globalCtx->colChkCtx, &this->collider.base);
}

/*#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Warpstone_0x80B92B10/ObjWarpstone_Draw.asm")*/

void ObjWarpstone_Draw(Actor* thisx, GlobalContext* globalCtx2) {
    ObjWarpstone* this = THIS;
    GlobalContext* globalCtx = globalCtx2;

    func_800BDFC0(globalCtx, D_80B93250[this->unk1AA]);
    if (this->actor.home.rot.x != 0) {
	OPEN_DISPS(globalCtx->state.gfxCtx);
        func_8012C2DC(globalCtx->state.gfxCtx);
        SysMatrix_InsertTranslation(this->actor.world.pos.x, this->actor.world.pos.y + 34.0f, this->actor.world.pos.z, 0);
        SysMatrix_InsertMatrix(&globalCtx->mf_187FC, 1);
        SysMatrix_InsertTranslation(0.0f, 0.0f, 30.0f, 1);
        Matrix_Scale(this->actor.velocity.x, this->actor.velocity.x, this->actor.velocity.x, 1);
        SysMatrix_StatePush();
	gDPPipeSync(POLY_XLU_DISP++);
	gDPSetPrimColor(POLY_XLU_DISP++, 0x80, 0x80, 0xFF, 0xFF, 0xC8, this->actor.home.rot.x);
	gDPSetEnvColor(POLY_XLU_DISP++, 0x64, 0xC8, 0x00, 0xFF);
        SysMatrix_InsertZRotation_f((((globalCtx->gameplayFrames * 1500) & 0xFFFF) * M_PI) / 32768.0f, 1);
	gSPMatrix(POLY_XLU_DISP++, Matrix_NewMtx(globalCtx->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
	gSPDisplayList(POLY_XLU_DISP++, D_04023210);
        SysMatrix_StatePop();
        SysMatrix_InsertZRotation_f((~((globalCtx->gameplayFrames * 1200) & 0xFFFF) * M_PI) / 32768.0f, 1);
	gSPMatrix(POLY_XLU_DISP++, Matrix_NewMtx(globalCtx->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
	gSPDisplayList(POLY_XLU_DISP++, D_04023210);
	CLOSE_DISPS(globalCtx->state.gfxCtx);
    }
}
