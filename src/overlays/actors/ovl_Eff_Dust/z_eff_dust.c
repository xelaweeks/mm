/**
 * File z_eff_dust.c
 * Overlay: ovl_Eff_Dust
 * Description: Dust effects
 */

#include "z_eff_dust.h"

#define FLAGS 0x00000030

#define THIS ((EffDust*)thisx)

void EffDust_Init(Actor* thisx, GlobalContext* globalCtx);
void EffDust_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EffDust_Update(Actor* thisx, GlobalContext* globalCtx);
void EffDust_Draw(Actor* thisx, GlobalContext* globalCtx);


void func_80918D64(EffDust* this, GlobalContext* globalCtx);
void func_80918FE4(EffDust* this, GlobalContext* globalCtx);
void func_80919230(EffDust* this, GlobalContext* globalCtx);

void func_80919768(Actor* this, GlobalContext* globalCtx);
void func_809199FC(Actor* this, GlobalContext* globalCtx);

/*
const ActorInit Eff_Dust_InitVars = {
    ACTOR_EFF_DUST,
    ACTORCAT_NPC,
    FLAGS,
    GAMEPLAY_KEEP,
    sizeof(EffDust),
    (ActorFunc)EffDust_Init,
    (ActorFunc)EffDust_Destroy,
    (ActorFunc)EffDust_Update,
    (ActorFunc)EffDust_Draw
};
*/

void func_80918B40(EffDust* this) {
    s32 i;

    for (i = 0; i < ARRAY_COUNT(this->distanceTraveled); i++) {
        this->initialPositions[i].z = 0.0f;
        this->initialPositions[i].y = 0.0f;
        this->initialPositions[i].x = 0.0f;

        this->distanceTraveled[i] = 1.0f;
    }
    this->index = 0;
}

/*
void EffDust_Init(Actor* thisx, GlobalContext* globalCtx) {
    EffDust* this = THIS;
    u32 sp18 = this->actor.params;

    func_80918B40(this);
    switch (sp18) {
    case 0:
        this->actionFunc = func_80918D64;
        this->actor.draw = func_80919768;
        this->dx = 1.0f;
        this->dy = 1.0f;
        this->dz = 1.0f;
        this->scalingFactor = 0.2f;
        break;
    case 1:
        this->actionFunc = func_80918FE4;
        this->actor.draw = func_80919768;
        this->dy = 1.0f;
        this->dx = 0.8f;
        this->dz = 0.8f;
        this->scalingFactor = 0.5f;
        break;
    case 2:
        this->actionFunc = func_80919230;
        this->actor.draw = func_809199FC;
        this->actor.room = -1;
        this->dx = 0.5f;
        this->scalingFactor = 15.0f;
        break;
    case 4:
        this->actionFunc = func_80919230;
        this->actor.draw = func_809199FC;
        this->actor.room = -1;
        this->dx = 0.5f;
        this->scalingFactor = 10.0f;
        break;
    case 5:
        this->actionFunc = func_80919230;
        this->actor.draw = func_809199FC;
        this->actor.room = -1;
        this->dx = 0.5f;
        this->scalingFactor = 20.0f;
        break;
    default:
        StartHeap_Free(this);
        break;
    }
    this->life = 10;
}
*/
#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Eff_Dust_0x80918B40/EffDust_Init.asm")

void EffDust_Destroy(Actor *thisx, GlobalContext *globalCtx) {
}

void func_80918D64(EffDust *this, GlobalContext *globalCtx) {
    s16 theta;
    s16 fi;
    s32 i;
    s32 j;
    f32* distanceTraveled = this->distanceTraveled;

    for (i = 0; i < 64; i++) {
        if ((*distanceTraveled) < 1.0f) {
            *distanceTraveled += 0.05f;
        }
        distanceTraveled++;
    }

    if (this->actor.home.rot.z != 0) {
        for (j = 0; j < 3; j++) {
            i = this->index & 0x3F;
            if (this->distanceTraveled[i] >= 1.0f) {
                // Spherical coordinate system.
                fi = randPlusMinusPoint5Scaled(0x10000);
                theta = Rand_ZeroFloat(0x1000);
                this->initialPositions[i].x = -(f32) this->actor.home.rot.z * Math_CosS(fi) * Math_CosS(theta);
                this->initialPositions[i].y = -(f32) this->actor.home.rot.z * Math_SinS(fi) * Math_CosS(theta);
                this->initialPositions[i].z = -(f32) this->actor.home.rot.z * Math_SinS(theta);
                this->distanceTraveled[i] = 0.0f;
                this->index++;
            }
        }
    }
}

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Eff_Dust_0x80918B40/func_80918FE4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Eff_Dust_0x80918B40/func_80919230.asm")

void EffDust_Update(Actor* thisx, GlobalContext* globalCtx) {
    EffDust* this = THIS;

    this->actionFunc(this, globalCtx);
}

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Eff_Dust_0x80918B40/func_80919768.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Eff_Dust_0x80918B40/func_809199FC.asm")

void EffDust_Draw(Actor *thisx, GlobalContext *globalCtx) {
    EffDust* this = THIS;

    this->drawFunc(thisx, globalCtx);
}
