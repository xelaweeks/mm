/*
 * File: z_en_tg.c
 * Overlay: ovl_En_Tg
 * Description: Target Game (Honey & Darling)
 */

#include "z_en_tg.h"

#define FLAGS (ACTOR_FLAG_1 | ACTOR_FLAG_8)

#define THIS ((EnTg*)thisx)

void EnTg_Init(Actor* thisx, GlobalContext* globalCtx);
void EnTg_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnTg_Update(Actor* thisx, GlobalContext* globalCtx);
void EnTg_Draw(Actor* thisx, GlobalContext* globalCtx);

void func_8098FA70(EnTg* this, GlobalContext* globalCtx);
void func_8098FEA8(GlobalContext *globalCtx, EnTgIdk *arg1, s32 arg2);

#if 0
const ActorInit En_Tg_InitVars = {
    ACTOR_EN_TG,
    ACTORCAT_NPC,
    FLAGS,
    OBJECT_MU,
    sizeof(EnTg),
    (ActorFunc)EnTg_Init,
    (ActorFunc)EnTg_Destroy,
    (ActorFunc)EnTg_Update,
    (ActorFunc)EnTg_Draw,
};

// static ColliderCylinderInit sCylinderInit = {
static ColliderCylinderInit D_809901C0 = {
    { COLTYPE_HIT0, AT_NONE, AC_ON | AC_TYPE_PLAYER, OC1_ON | OC1_TYPE_ALL, OC2_TYPE_1, COLSHAPE_CYLINDER, },
    { ELEMTYPE_UNK1, { 0x00000000, 0x00, 0x00 }, { 0xF7CFFFFF, 0x00, 0x00 }, TOUCH_NONE | TOUCH_SFX_NORMAL, BUMP_ON, OCELEM_ON, },
    { 18, 64, 0, { 0, 0, 0 } },
};

// sColChkInfoInit
static CollisionCheckInfoInit2 D_809901EC = { 0, 0, 0, 0, MASS_IMMOVABLE };

// static DamageTable sDamageTable = {
static DamageTable D_809901F8 = {
    /* Deku Nut       */ DMG_ENTRY(0, 0x0),
    /* Deku Stick     */ DMG_ENTRY(0, 0x0),
    /* Horse trample  */ DMG_ENTRY(0, 0x0),
    /* Explosives     */ DMG_ENTRY(0, 0x0),
    /* Zora boomerang */ DMG_ENTRY(0, 0x0),
    /* Normal arrow   */ DMG_ENTRY(0, 0x0),
    /* UNK_DMG_0x06   */ DMG_ENTRY(0, 0x0),
    /* Hookshot       */ DMG_ENTRY(0, 0x0),
    /* Goron punch    */ DMG_ENTRY(0, 0x0),
    /* Sword          */ DMG_ENTRY(0, 0x0),
    /* Goron pound    */ DMG_ENTRY(0, 0x0),
    /* Fire arrow     */ DMG_ENTRY(0, 0x0),
    /* Ice arrow      */ DMG_ENTRY(0, 0x0),
    /* Light arrow    */ DMG_ENTRY(0, 0x0),
    /* Goron spikes   */ DMG_ENTRY(0, 0x0),
    /* Deku spin      */ DMG_ENTRY(0, 0x0),
    /* Deku bubble    */ DMG_ENTRY(0, 0x0),
    /* Deku launch    */ DMG_ENTRY(0, 0x0),
    /* UNK_DMG_0x12   */ DMG_ENTRY(0, 0x0),
    /* Zora barrier   */ DMG_ENTRY(0, 0x0),
    /* Normal shield  */ DMG_ENTRY(0, 0x0),
    /* Light ray      */ DMG_ENTRY(0, 0x0),
    /* Thrown object  */ DMG_ENTRY(0, 0x0),
    /* Zora punch     */ DMG_ENTRY(0, 0x0),
    /* Spin attack    */ DMG_ENTRY(0, 0x0),
    /* Sword beam     */ DMG_ENTRY(0, 0x0),
    /* Normal Roll    */ DMG_ENTRY(0, 0x0),
    /* UNK_DMG_0x1B   */ DMG_ENTRY(0, 0x0),
    /* UNK_DMG_0x1C   */ DMG_ENTRY(0, 0x0),
    /* Unblockable    */ DMG_ENTRY(0, 0x0),
    /* UNK_DMG_0x1E   */ DMG_ENTRY(0, 0x0),
    /* Powder Keg     */ DMG_ENTRY(0, 0x0),
};

#endif

extern ColliderCylinderInit D_809901C0;
extern CollisionCheckInfoInit2 D_809901EC;
extern DamageTable D_809901F8;

extern UNK_TYPE D_0600B0E0;
extern UNK_TYPE D_80990218;
extern FlexSkeletonHeader D_0600B2B0;
extern Vec3f D_8099024C;

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Tg/func_8098F800.s")
// void func_8098F800(SkelAnime *skelAnime, s32 arg1, s16 arg2) {
//     s16 temp_v0;
//     void *temp_s0;
//     s16 phi_f0;

//     temp_s0 = arg1 + (arg2 * 0x10);
//     temp_v0 = temp_s0->unkA;
//     if ((s32) temp_v0 < 0) {
//         // s16 Animation_GetLastFrame(void* animation);
//         phi_f0 = (f32) Animation_GetLastFrame(LegacyAnimationHeader *)temp_s0->unk0);
//     } else {
//         phi_f0 = (f32) temp_v0;
//     }
//     // void Animation_Change(SkelAnime* skelAnime, AnimationHeader* animation, f32 playSpeed, f32 startFrame, f32 endFrame, u8 mode, f32 morphFrames);
//     Animation_Change(skelAnime, (AnimationHeader*) temp_s0->unk0, (f32) temp_s0->unk4, (f32) temp_s0->unk8, (f32) phi_f0, (u8) (s32) temp_s0->unkC, (f32) temp_s0->unkE);
// }

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Tg/func_8098F8A8.s")

// #pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Tg/func_8098F928.s")
void func_8098F928(EnTg* this, GlobalContext *globalCtx) {
    SkelAnime_Update(&this->skelAnime);
}

// #pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Tg/EnTg_Init.s")
void EnTg_Init(Actor *thisx, GlobalContext *globalCtx) {
    EnTg* this = THIS;

    ActorShape_Init(&this->actor.shape, 0.0f, NULL, 0.0f);
    SkelAnime_InitFlex(globalCtx, &this->skelAnime, &D_0600B2B0, NULL, this->jointTable, this->morphTable, 21);
    func_8098F800(&this->skelAnime, &D_80990218, 0);
    Collider_InitCylinder(globalCtx, &this->collider);
    Collider_SetCylinder(globalCtx, &this->collider, &this->actor, &D_809901C0);
    CollisionCheck_SetInfo2(&this->actor.colChkInfo, &D_809901F8, &D_809901EC);
    Actor_SetScale(&this->actor, 0.01f);
    this->actionFunc = func_8098FA70;
    this->actor.gravity = -4.0f;
}

// #pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Tg/EnTg_Destroy.s")
void EnTg_Destroy(Actor *thisx, GlobalContext *globalCtx) {
    EnTg* this = THIS;

    Collider_DestroyCylinder(globalCtx, &this->collider);
}

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Tg/func_8098FA70.s")
// void func_8098FA70(EnTg *this, GlobalContext *globalCtx) {
//     Vec3f sp24;
//     int phi_v1 = 0;

//     this->actor.shape.rot.y += gGameInfo->data[0x600] + 0x258;
//     this->actor.world.rot = this->actor.shape.rot;
//     this->actor.world.rot.z = this->actor.shape.rot.z;
//     if (this->unk2EC == 0) {
//         phi_v1 = 0;
//     } else {
//         this->unk2EC -= 1;
//         phi_v1 = this->unk2EC;
//     }
//     if (phi_v1 == 0) {
//         this->unk2EC = 0xC;
//         sp24.x = this->actor.world.pos.x;
//         sp24.y = this->actor.world.pos.y;
//         sp24.z = this->actor.world.pos.z;
//         func_8098FD50(&this->unk2F0, &sp24, 0xA);
//     }
// }

// #pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Tg/EnTg_Update.s")
void EnTg_Update(Actor *thisx, GlobalContext *globalCtx) {
    EnTg* this = THIS;

    this->actionFunc(this, globalCtx);
    Actor_UpdateBgCheckInfo(globalCtx, &this->actor, 0.0f, 0.0f, 0.0f, 4U);
    func_8098F928(this, globalCtx);
    func_8098FEA8(globalCtx, &this->unk2F0, 0xA);
    func_8098F8A8(this, globalCtx);
}

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Tg/func_8098FBB4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Tg/func_8098FBD0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Tg/EnTg_Draw.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Tg/func_8098FD50.s")

// #pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Tg/func_8098FEA8.s")
//    temp_s2 = Camera_GetInputDirYaw(GET_ACTIVE_CAM(globalCtx));
void func_8098FEA8(GlobalContext *globalCtx, EnTgIdk *arg1, s32 arg2) {
    Vec3f sp44;
    s16 temp_s2;
    s32 phi_v1;
    s32 i = 0;

    sp44.x = D_8099024C.x;
    sp44.y = D_8099024C.y;
    sp44.z = D_8099024C.z;
    temp_s2 = Camera_GetInputDirYaw(GET_ACTIVE_CAM(globalCtx));
    if (arg2 > 0) {
        do {
            if (arg1->unk0 == 1) {
                arg1->unk1 -= 1;
                if (arg1->unk1 == 0) {
                    phi_v1 = 0;
                } else {
                    phi_v1 = arg1->unk1 & 0xFF;
                }
                if (phi_v1 == 0) {
                    arg1->unk0 = 0U;
                }
                arg1->unk14.x = (f32) (arg1->unk14.y + arg1->unk30);
                arg1->unk14.y = (f32) (arg1->unk14.x + (2.0f * Math_SinS(arg1->unk38)));
                arg1->unk14.z = (f32) (arg1->unk14.z + (2.0f * Math_CosS(arg1->unk38)));
                Matrix_StatePush();
                Matrix_InsertTranslation(arg1->unk14.x, arg1->unk14.y, arg1->unk14.z, 0);
                Matrix_RotateY(temp_s2, 1);
                Matrix_MultiplyVector3fByState(&sp44, &arg1->unk14);
                Matrix_StatePop();
                arg1->unk38 = (s16) (arg1->unk38 + 0x1770);
            }
            arg1 += 0x3C;
            i += 1;
        } while (i != arg2);
    }
}

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Tg/func_8099000C.s")
