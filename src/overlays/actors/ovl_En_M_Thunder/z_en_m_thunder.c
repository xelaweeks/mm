/*
 * File: z_en_m_thunder.c
 * Overlay: ovl_En_M_Thunder
 * Description: Spin attack and sword beams
 */

#include "z_en_m_thunder.h"
#include "z64rumble.h"

#define FLAGS (ACTOR_FLAG_10)

#define THIS ((EnMThunder*)thisx)

void EnMThunder_Init(Actor* thisx, PlayState* play);
void EnMThunder_Destroy(Actor* thisx, PlayState* play);
void EnMThunder_Update(Actor* thisx, PlayState* play);
void EnMThunder_Draw(Actor* thisx, PlayState* play);

void func_808B65BC(Actor* thisx, PlayState* play);

void func_808B5984(EnMThunder* this, PlayState* play);
void func_808B5F68(EnMThunder* this, PlayState* play);
void func_808B60D4(EnMThunder* this, PlayState* play);
void func_808B6310(EnMThunder* this, PlayState* play);

#if 0
const ActorInit En_M_Thunder_InitVars = {
    ACTOR_EN_M_THUNDER,
    ACTORCAT_ITEMACTION,
    FLAGS,
    GAMEPLAY_KEEP,
    sizeof(EnMThunder),
    (ActorFunc)EnMThunder_Init,
    (ActorFunc)EnMThunder_Destroy,
    (ActorFunc)EnMThunder_Update,
    (ActorFunc)EnMThunder_Draw,
};

// static ColliderCylinderInit sCylinderInit = {
static ColliderCylinderInit D_808B7120 = {
    { COLTYPE_NONE, AT_ON | AT_TYPE_PLAYER, AC_NONE, OC1_NONE, OC2_TYPE_1, COLSHAPE_CYLINDER, },
    { ELEMTYPE_UNK2, { 0x01000000, 0x00, 0x00 }, { 0xF7CFFFFF, 0x00, 0x00 }, TOUCH_ON | TOUCH_SFX_NONE, BUMP_ON, OCELEM_ON, },
    { 200, 200, 0, { 0, 0, 0 } },
};

#endif

extern ColliderCylinderInit D_808B7120;

extern u8 D_808B714C[];
// extern u8 D_808B7150[];

void func_808B53C0(EnMThunder* this, PlayState* play) {
    Player* player = GET_PLAYER(play);

    this->actor.update = func_808B65BC;
    this->unk1C2 = 0;
    this->unk1BE = 1;
    this->unk1C1 = 2;
    this->actionFunc = func_808B6310;
    this->unk1BC = 8;
    this->unk1A4 = 1.0f;
    Audio_PlaySfxGeneral(NA_SE_IT_ROLLING_CUT_LV1, &player->actor.projectedPos, 4, &D_801DB4B0, &D_801DB4B0,
                         &gSfxDefaultReverb);
    this->actor.child = NULL;
}

void EnMThunder_Init(Actor* thisx, PlayState* play) {
    s32 pad;
    EnMThunder* this = THIS;
    Player* player = GET_PLAYER(play);

    Collider_InitCylinder(play, &this->unk144);
    Collider_SetCylinder(play, &this->unk144, &this->actor, &D_808B7120);
    this->unk1BF = ENMTHUNDER_GET_UNK1BF(&this->actor);
    Lights_PointNoGlowSetInfo(&this->unk194, this->actor.world.pos.x, this->actor.world.pos.y, this->actor.world.pos.z,
                              255, 255, 255, 0);
    this->unk190 = LightContext_InsertLight(play, &play->lightCtx, &this->unk194);

    if (this->unk1BF == 0x80) {
        func_808B53C0(this, play);
        return;
    }
    this->unk144.dim.radius = 0;
    this->unk144.dim.height = 40;
    this->unk144.dim.yShift = -20;
    this->unk1BC = 8;
    this->unk1AC = 0.0f;
    this->actor.world.pos = player->bodyPartsPos[0];
    this->unk1A4 = 0.0f;
    this->unk1B4 = 0.0f;
    this->actor.shape.rot.y = player->actor.shape.rot.y + 0x8000;
    this->actor.shape.rot.x = -this->actor.world.rot.x;
    this->actor.room = -1;
    Actor_SetScale(&this->actor, 0.1f);
    this->unk1C2 = 0;

    if (player->stateFlags2 & PLAYER_STATE2_20000) {
        if (!gSaveContext.save.playerData.magicAcquired || (gSaveContext.unk_3F28 != 0) ||
            ((ENMTHUNDER_GET_MAGIC_COST(&this->actor) != 0) &&
             !func_80115DB4(play, ENMTHUNDER_GET_MAGIC_COST(&this->actor), 0))) {
            Audio_PlaySfxGeneral(NA_SE_IT_ROLLING_CUT, &player->actor.projectedPos, 4, &D_801DB4B0, &D_801DB4B0,
                                 &gSfxDefaultReverb);
            Audio_PlaySfxGeneral(NA_SE_IT_SWORD_SWING_HARD, &player->actor.projectedPos, 4, &D_801DB4B0, &D_801DB4B0,
                                 &gSfxDefaultReverb);
            Actor_MarkForDeath(&this->actor);
            return;
        }
        player->stateFlags2 &= ~PLAYER_STATE2_20000;
        this->unk1C2 = 0;
        if (gSaveContext.save.weekEventReg[23] & 2) {
            player->unk_B08[0] = 1.0f;
            this->unk144.info.toucher.damage = D_808B714C[this->unk1BF + 4];
            this->unk1BE = 0;
            if (this->unk1BF == 3) {
                this->unk1C1 = 6;
            } else if (this->unk1BF == 2) {
                this->unk1C1 = 4;
            } else {
                this->unk1C1 = 3;
            }
        } else {
            player->unk_B08[0] = 0.5f;
            this->unk144.info.toucher.damage = D_808B714C[this->unk1BF];
            this->unk1BE = 1;
            if (this->unk1BF == 3) {
                this->unk1C1 = 4;
            } else if (this->unk1BF == 2) {
                this->unk1C1 = 3;
            } else {
                this->unk1C1 = 2;
            }
        }
        if (player->meleeWeaponAnimation < 30) {
            this->unk1BE += 2;
            this->actionFunc = func_808B60D4;
            this->unk1BC = 1;
            this->unk1C1 = 12;
            this->unk144.info.toucher.dmgFlags = 0x02000000;
            this->unk144.info.toucher.damage = 3;
        } else {
            this->actionFunc = func_808B5F68;
            this->unk1BC = 8;
        }
        Audio_PlaySfxGeneral(NA_SE_IT_ROLLING_CUT_LV1, &player->actor.projectedPos, 4, &D_801DB4B0, &D_801DB4B0,
                             &gSfxDefaultReverb);
        this->unk1A4 = 1.0f;
    } else {
        this->actionFunc = func_808B5984;
    }
    this->actor.child = NULL;
}

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_M_Thunder/EnMThunder_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_M_Thunder/func_808B5890.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_M_Thunder/func_808B58CC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_M_Thunder/func_808B5984.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_M_Thunder/func_808B5EEC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_M_Thunder/func_808B5F68.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_M_Thunder/func_808B60D4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_M_Thunder/func_808B6310.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_M_Thunder/EnMThunder_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_M_Thunder/func_808B65BC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_M_Thunder/EnMThunder_Draw.s")
