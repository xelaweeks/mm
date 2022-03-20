/*
 * File: z_eff_ss_ice_smoke.c
 * Overlay: ovl_Effect_Ss_Ice_Smoke
 * Description:
 */

#include "z_eff_ss_ice_smoke.h"
#include "objects/gameplay_keep/gameplay_keep.h"

#define rAlpha regs[0]
#define rScale regs[1]
#define rScrollX regs[2]
#define rScrollY regs[3]

#define PARAMS ((EffectSsIceSmokeInitParams*)initParamsx)

u32 EffectSsIceSmoke_Init(GlobalContext* globalCtx, u32 index, EffectSs* this, void* initParamsx);
void EffectSsIceSmoke_Update(GlobalContext* globalCtx, u32 index, EffectSs* this);
void EffectSsIceSmoke_Draw(GlobalContext* globalCtx, u32 index, EffectSs* this);

const EffectSsInit Effect_Ss_Ice_Smoke_InitVars = {
    EFFECT_SS_ICE_SMOKE,
    EffectSsIceSmoke_Init,
};

u32 EffectSsIceSmoke_Init(GlobalContext* globalCtx, u32 index, EffectSs* this, void* initParamsx) {
    EffectSsIceSmokeInitParams* initParams = PARAMS;

    Math_Vec3f_Copy(&this->pos, &initParams->pos);
    Math_Vec3f_Copy(&this->velocity, &initParams->velocity);
    Math_Vec3f_Copy(&this->accel, &initParams->accel);
    this->rAlpha = 0;
    this->rScale = ABS_ALT(initParams->scale);
    if (initParams->scale < 0) {
        this->rScrollX = 1;
        this->rScrollY = 2;
    } else {
        this->rScrollX = 3;
        this->rScrollY = 15;
    }
    this->life = 50;
    this->draw = EffectSsIceSmoke_Draw;
    this->update = EffectSsIceSmoke_Update;

    return 1;
}

void EffectSsIceSmoke_Draw(GlobalContext* globalCtx, u32 index, EffectSs* this) {
    s32 pad;
    Mtx* mtx;
    f32 scale;

    OPEN_DISPS(globalCtx->state.gfxCtx);

    func_8012C2DC(globalCtx->state.gfxCtx);
    gDPSetPrimColor(POLY_XLU_DISP++, 0, 0, 195, 235, 235, this->rAlpha);
    gSPSegment(POLY_XLU_DISP++, 0x08,
               Gfx_TwoTexScroll(globalCtx->state.gfxCtx, 0, this->rScrollX * this->life, this->rScrollY * this->life,
                                0x20, 0x40, 1, 0, 0, 0x20, 0x20));
    Matrix_InsertTranslation(this->pos.x, this->pos.y, this->pos.z, MTXMODE_NEW);
    Matrix_NormalizeXYZ(&globalCtx->billboardMtxF);
    scale = this->rScale * 0.0001f;
    Matrix_Scale(scale, scale, 1.0f, MTXMODE_APPLY);
    mtx = Matrix_NewMtx(globalCtx->state.gfxCtx);
    if (mtx != NULL) {
        gSPMatrix(POLY_XLU_DISP++, mtx, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        gSPDisplayList(POLY_XLU_DISP++, gameplay_keep_DL_0510B0);
    }

    CLOSE_DISPS(globalCtx->state.gfxCtx);
}

void EffectSsIceSmoke_Update(GlobalContext* globalCtx, u32 index, EffectSs* this) {
    if (this->life < 10) {
        Math_StepToS(&this->rAlpha, 0, 10);
    } else if (this->rAlpha < 0x64) {
        this->rAlpha += 10;
    }
}
