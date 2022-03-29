/*
 * File: z_en_syateki_okuta.c
 * Overlay: ovl_En_Syateki_Okuta
 * Description: Shooting Gallery Octorok
 */

#include "z_en_syateki_okuta.h"

#define FLAGS (ACTOR_FLAG_10 | ACTOR_FLAG_20 | ACTOR_FLAG_8000000)

#define THIS ((EnSyatekiOkuta*)thisx)

void EnSyatekiOkuta_Init(Actor* thisx, GlobalContext* globalCtx);
void EnSyatekiOkuta_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnSyatekiOkuta_Update(Actor* thisx, GlobalContext* globalCtx);
void EnSyatekiOkuta_Draw(Actor* thisx, GlobalContext* globalCtx);

void func_80A362A8(EnSyatekiOkuta* this, GlobalContext* globalCtx);
void func_80A36350(EnSyatekiOkuta* this, GlobalContext* globalCtx);
void func_80A363B4(EnSyatekiOkuta* this, GlobalContext* globalCtx);
void func_80A36488(EnSyatekiOkuta* this, GlobalContext* globalCtx);
void func_80A36504(EnSyatekiOkuta* this, GlobalContext* globalCtx);
void func_80A365EC(EnSyatekiOkuta* this, GlobalContext* globalCtx);
void func_80A36260(EnSyatekiOkuta* this);
void func_80A362F8(EnSyatekiOkuta* this);

#if 0
const ActorInit En_Syateki_Okuta_InitVars = {
    ACTOR_EN_SYATEKI_OKUTA,
    ACTORCAT_ENEMY,
    FLAGS,
    OBJECT_OKUTA,
    sizeof(EnSyatekiOkuta),
    (ActorFunc)EnSyatekiOkuta_Init,
    (ActorFunc)EnSyatekiOkuta_Destroy,
    (ActorFunc)EnSyatekiOkuta_Update,
    (ActorFunc)EnSyatekiOkuta_Draw,
};

// static ColliderCylinderInit sCylinderInit = {
static ColliderCylinderInit D_80A37570 = {
    { COLTYPE_HIT3, AT_NONE, AC_ON | AC_TYPE_PLAYER, OC1_ON | OC1_TYPE_ALL, OC2_TYPE_1, COLSHAPE_CYLINDER, },
    { ELEMTYPE_UNK1, { 0x00000000, 0x00, 0x00 }, { 0xF7CFFFFF, 0x00, 0x00 }, TOUCH_NONE | TOUCH_SFX_NORMAL, BUMP_ON, OCELEM_ON, },
    { 20, 40, -30, { 0, 0, 0 } },
};

// static InitChainEntry sInitChain[] = {
static InitChainEntry D_80A37B88[] = {
    ICHAIN_S8(hintId, 66, ICHAIN_CONTINUE),
    ICHAIN_F32(targetArrowOffset, 6500, ICHAIN_STOP),
};

#endif

extern ColliderCylinderInit D_80A37570;
extern InitChainEntry D_80A37B88[];

extern SkeletonHeader D_060033D0;
extern AnimationHeader D_0600466C;

void EnSyatekiOkuta_Init(Actor* thisx, GlobalContext* globalCtx) {
    s32 pad;
    EnSyatekiOkuta* this = THIS;
    WaterBox* waterbox;
    f32 ySurface;
    s32 bgId;

    Actor_ProcessInitChain(&this->actor, D_80A37B88);
    SkelAnime_Init(globalCtx, &this->skelAnime, &D_060033D0, &D_0600466C, this->jointTable, this->morphTable, 16);
    Collider_InitCylinder(globalCtx, &this->collider);
    Collider_SetCylinder(globalCtx, &this->collider, &this->actor, &D_80A37570);

    this->actor.floorHeight = BgCheck_EntityRaycastFloor5(&globalCtx->colCtx, &this->actor.floorPoly, &bgId,
                                                          &this->actor, &this->actor.world.pos);

    if (!(WaterBox_GetSurface1_2(globalCtx, &globalCtx->colCtx, this->actor.world.pos.x, this->actor.world.pos.z,
                                 &ySurface, &waterbox)) ||
        (ySurface <= this->actor.floorHeight)) {
        Actor_MarkForDeath(&this->actor);
    } else {
        this->actor.world.pos.y = this->actor.home.pos.y = ySurface;
    }

    this->unk_2A4 = 0;
    this->unk_2AA = 0;
    func_80A36260(this);
}

void EnSyatekiOkuta_Destroy(Actor* thisx, GlobalContext* globalCtx) {
    EnSyatekiOkuta* this = THIS;

    Collider_DestroyCylinder(globalCtx, &this->collider);
}

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Syateki_Okuta/func_80A36148.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Syateki_Okuta/func_80A361B0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Syateki_Okuta/func_80A361F4.s")

void func_80A36260(EnSyatekiOkuta* this) {
    Animation_PlayOnceSetSpeed(&this->skelAnime, &D_0600466C, 0.0f);
    this->actor.draw = NULL;
    this->actionFunc = func_80A362A8;
}

void func_80A362A8(EnSyatekiOkuta* this, GlobalContext* globalCtx) {
    Actor* actorIt = globalCtx->actorCtx.actorLists[ACTORCAT_NPC].first;

    while (actorIt != NULL) {
        if (actorIt->id == ACTOR_EN_SYATEKI_MAN) {
            this->actor.parent = actorIt;
            func_80A362F8(this);
            break;
        } else {
            actorIt = actorIt->next;
        }
    }
}

void func_80A362F8(EnSyatekiOkuta* this) {
    Animation_PlayOnceSetSpeed(&this->skelAnime, &D_0600466C, 0.0f);
    this->actor.draw = NULL;
    Actor_SetScale(&this->actor, 0.01f);
    this->actionFunc = func_80A36350;
}

void func_80A36350(EnSyatekiOkuta* this, GlobalContext* globalCtx) {
}

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Syateki_Okuta/func_80A36360.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Syateki_Okuta/func_80A363B4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Syateki_Okuta/func_80A36444.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Syateki_Okuta/func_80A36488.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Syateki_Okuta/func_80A364C0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Syateki_Okuta/func_80A36504.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Syateki_Okuta/func_80A3657C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Syateki_Okuta/func_80A365EC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Syateki_Okuta/func_80A368E0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Syateki_Okuta/func_80A36A90.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Syateki_Okuta/func_80A36AF8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Syateki_Okuta/EnSyatekiOkuta_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Syateki_Okuta/func_80A36CB0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Syateki_Okuta/func_80A370EC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Syateki_Okuta/func_80A37294.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Syateki_Okuta/EnSyatekiOkuta_Draw.s")
