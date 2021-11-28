/*
 * File: z_en_hit_tag.c
 * Overlay: ovl_En_Hit_Tag
 * Description: Invisible hitbox that can spawn rupees
 */

#include "z_en_hit_tag.h"

#define FLAGS 0x00000010

#define THIS ((EnHitTag*)thisx)

void EnHitTag_Init(Actor* thisx, GlobalContext* globalCtx);
void EnHitTag_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnHitTag_Update(Actor* thisx, GlobalContext* globalCtx);

void func_80BE20E8(EnHitTag* this, GlobalContext* globalCtx);

#if 0
const ActorInit En_Hit_Tag_InitVars = {
    ACTOR_EN_HIT_TAG,
    ACTORCAT_ITEMACTION,
    FLAGS,
    GAMEPLAY_KEEP,
    sizeof(EnHitTag),
    (ActorFunc)EnHitTag_Init,
    (ActorFunc)EnHitTag_Destroy,
    (ActorFunc)EnHitTag_Update,
    (ActorFunc)NULL,
};

// static ColliderCylinderInit sCylinderInit = {
static ColliderCylinderInit D_80BE21F0 = {
    { COLTYPE_NONE, AT_NONE, AC_ON | AC_TYPE_PLAYER, OC1_ON | OC1_TYPE_PLAYER, OC2_TYPE_1, COLSHAPE_CYLINDER, },
    { ELEMTYPE_UNK0, { 0x00000000, 0x00, 0x00 }, { 0xF7CFFFFF, 0x00, 0x00 }, TOUCH_NONE | TOUCH_SFX_NORMAL, BUMP_ON, OCELEM_NONE, },
    { 16, 32, 0, { 0, 0, 0 } },
};

#endif

extern ColliderCylinderInit D_80BE21F0;

//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Hit_Tag/EnHitTag_Init.s")
void EnHitTag_Init(Actor* thisx, GlobalContext* globalCtx) {
    ColliderCylinder* pCylinder;
    EnHitTag* this = (EnHitTag* ) thisx;

    Actor_SetScale(&this->actor, 1.0f);
    this->actionFunc = func_80BE20E8;
    pCylinder = &this->cylinder;
    Collider_InitAndSetCylinder(globalCtx, &this->cylinder, &this->actor, &D_80BE21F0);
    Collider_UpdateCylinder(&this->actor, &this->cylinder);
    if (Flags_GetSwitch(globalCtx, (s32) (this->actor.params & 0xFE00) >> 9) != 0) {
        Actor_MarkForDeath(&this->actor);
    }
}

//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Hit_Tag/EnHitTag_Destroy.s")
void EnHitTag_Destroy(Actor* thisx, GlobalContext* globalCtx) {
    EnHitTag* this = (EnHitTag* ) thisx;
    Collider_DestroyCylinder(globalCtx, &this->cylinder);
}

//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Hit_Tag/func_80BE20E8.s")
void func_80BE20E8(EnHitTag* this, GlobalContext* globalCtx) {
    Vec3f dropLocation;
    s32 numCollectibles;

    if (this->cylinder.base.acFlags & AC_HIT) {
        play_sound(NA_SE_SY_GET_RUPY);
        Actor_MarkForDeath(&this->actor);
        dropLocation.x = this->actor.world.pos.x;
        dropLocation.y = this->actor.world.pos.y;
        dropLocation.z = this->actor.world.pos.z;

        for (numCollectibles = 0; numCollectibles < 3; numCollectibles++) {
            Item_DropCollectible(globalCtx, &dropLocation, 0U);
        }

        return;
    }
    CollisionCheck_SetAC(globalCtx, &globalCtx->colChkCtx, &this->cylinder.base);
}

//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Hit_Tag/EnHitTag_Update.s")
void EnHitTag_Update(Actor* thisx, GlobalContext* globalCtx) {
    EnHitTag* this = (EnHitTag* ) thisx;
    this->actionFunc(this, globalCtx);
}