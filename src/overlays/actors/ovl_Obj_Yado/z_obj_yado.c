/*
 * File: z_obj_yado.c
 * Overlay: ovl_Obj_Yado
 * Description: Stockpot Inn - 2nd Floor Window
 */

#include "z_obj_yado.h"

#define FLAGS 0x00000030

#define THIS ((ObjYado*)thisx)

void ObjYado_Init(Actor* thisx, GlobalContext* globalCtx);
void ObjYado_Destroy(Actor* thisx, GlobalContext* globalCtx);
void ObjYado_Update(Actor* thisx, GlobalContext* globalCtx);
void ObjYado_Draw(Actor* thisx, GlobalContext* globalCtx);

const ActorInit Obj_Yado_InitVars = {
    ACTOR_OBJ_YADO,
    ACTORCAT_BG,
    FLAGS,
    OBJECT_YADO_OBJ,
    sizeof(ObjYado),
    (ActorFunc)ObjYado_Init,
    (ActorFunc)ObjYado_Destroy,
    (ActorFunc)ObjYado_Update,
    (ActorFunc)ObjYado_Draw,
};

// static InitChainEntry sInitChain[] = {
static InitChainEntry D_80C16420[] = {
    ICHAIN_VEC3F_DIV1000(scale, 100, ICHAIN_STOP),
};

AnimatedMaterial* D_80C16470;

extern InitChainEntry D_80C16420[];

extern Gfx D_06000320[];
extern Gfx D_06000430[];
extern AnimatedMaterial D_060012E8;

void ObjYado_Init(Actor* thisx, GlobalContext* globalCtx) {
    ObjYado* this = THIS;

    Actor_ProcessInitChain(&this->actor, D_80C16420);
    D_80C16470 = (AnimatedMaterial *)Lib_SegmentedToVirtual(&D_060012E8);
    this->unk_144 = gSaveContext.isNight;
}

void ObjYado_Destroy(Actor* thisx, GlobalContext* globalCtx) {

}

void ObjYado_Update(Actor* thisx, GlobalContext* globalCtx) {
    ObjYado* this = THIS;

    this->unk_144 = gSaveContext.isNight;
}

void ObjYado_Draw(Actor* thisx, GlobalContext* globalCtx) {
    s32 pad;
    ObjYado* this = THIS;

    OPEN_DISPS(globalCtx->state.gfxCtx);

    if (this->unk_144 != 0) {
        gSPSegment(POLY_XLU_DISP++, 0x09, Gfx_PrimColor(globalCtx->state.gfxCtx, 128, 95, 95, 70, 155));
        gSPSegment(POLY_OPA_DISP++, 0x0A, Gfx_PrimColor(globalCtx->state.gfxCtx, 128, 0, 40, 40, 255));
    } else {
        gSPSegment(POLY_XLU_DISP++, 0x09, Gfx_PrimColor(globalCtx->state.gfxCtx, 128, 255, 255, 215, 110));
        gSPSegment(POLY_OPA_DISP++, 0x0A, Gfx_PrimColor(globalCtx->state.gfxCtx, 128, 255, 255, 215, 255));
    }

    AnimatedMat_Draw(globalCtx, D_80C16470);
    func_800BDFC0(globalCtx, D_06000430);
    func_800BE03C(globalCtx, D_06000320);

    CLOSE_DISPS(globalCtx->state.gfxCtx);
}
