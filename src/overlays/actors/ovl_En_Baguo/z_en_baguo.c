/*
 * File z_en_baguo.c
 * Overlay: ovl_En_Baguo
 * Description: Nejiron
 */

#include "z_en_baguo.h"

#define FLAGS 0x00000005

#define THIS ((EnBaguo*)thisx)

void EnBaguo_Init(Actor* thisx, GlobalContext* globalCtx);
void EnBaguo_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnBaguo_Update(Actor* thisx, GlobalContext* globalCtx);

const ActorInit En_Baguo_InitVars = {
    ACTOR_EN_BAGUO,
    ACTORCAT_ENEMY,
    FLAGS,
    OBJECT_GMO,
    sizeof(EnBaguo),
    (ActorFunc)EnBaguo_Init,
    (ActorFunc)EnBaguo_Destroy,
    (ActorFunc)EnBaguo_Update,
    (ActorFunc)NULL,
};

// static ColliderJntSphElementInit sJntSphElementsInit[1] = {
static ColliderJntSphElementInit D_80A3C2F0[1] = {
    {
        {
            ELEMTYPE_UNK0,
            { 0xF7CFFFFF, 0x04, 0x04 },
            { 0xF7CFFFFF, 0x00, 0x00 },
            TOUCH_ON | TOUCH_SFX_NORMAL,
            BUMP_ON,
            OCELEM_ON,
        },
        { 1, { { 0, 0, 0 }, 0 }, 1 },
    },
};

// static ColliderJntSphInit sJntSphInit = {
static ColliderJntSphInit D_80A3C314 = {
    {
        COLTYPE_HARD,
        AT_ON | AT_TYPE_ENEMY,
        AC_ON | AC_TYPE_PLAYER,
        OC1_ON | OC1_TYPE_ALL,
        OC2_TYPE_1,
        COLSHAPE_JNTSPH,
    },
    1,
    D_80A3C2F0, // sJntSphElementsInit,
};

// static DamageTable sDamageTable = {
static DamageTable D_80A3C324 = {
    /* Deku Nut       */ DMG_ENTRY(0, 0xF),
    /* Deku Stick     */ DMG_ENTRY(0, 0xF),
    /* Horse trample  */ DMG_ENTRY(0, 0x0),
    /* Explosives     */ DMG_ENTRY(1, 0xE),
    /* Zora boomerang */ DMG_ENTRY(3, 0xE),
    /* Normal arrow   */ DMG_ENTRY(0, 0xF),
    /* UNK_DMG_0x06   */ DMG_ENTRY(0, 0x0),
    /* Hookshot       */ DMG_ENTRY(3, 0xE),
    /* Goron punch    */ DMG_ENTRY(2, 0xE),
    /* Sword          */ DMG_ENTRY(1, 0xE),
    /* Goron pound    */ DMG_ENTRY(1, 0xE),
    /* Fire arrow     */ DMG_ENTRY(0, 0xF),
    /* Ice arrow      */ DMG_ENTRY(0, 0xF),
    /* Light arrow    */ DMG_ENTRY(1, 0xE),
    /* Goron spikes   */ DMG_ENTRY(2, 0xE),
    /* Deku spin      */ DMG_ENTRY(0, 0xF),
    /* Deku bubble    */ DMG_ENTRY(0, 0xF),
    /* Deku launch    */ DMG_ENTRY(1, 0xE),
    /* UNK_DMG_0x12   */ DMG_ENTRY(0, 0xF),
    /* Zora barrier   */ DMG_ENTRY(0, 0x0),
    /* Normal shield  */ DMG_ENTRY(0, 0x0),
    /* Light ray      */ DMG_ENTRY(0, 0x0),
    /* Thrown object  */ DMG_ENTRY(0, 0x0),
    /* Zora punch     */ DMG_ENTRY(1, 0xE),
    /* Spin attack    */ DMG_ENTRY(1, 0xE),
    /* Sword beam     */ DMG_ENTRY(0, 0x0),
    /* Normal Roll    */ DMG_ENTRY(0, 0x0),
    /* UNK_DMG_0x1B   */ DMG_ENTRY(0, 0x0),
    /* UNK_DMG_0x1C   */ DMG_ENTRY(0, 0x0),
    /* Unblockable    */ DMG_ENTRY(0, 0x0),
    /* UNK_DMG_0x1E   */ DMG_ENTRY(0, 0x0),
    /* Powder Keg     */ DMG_ENTRY(1, 0xE),
};

s32 D_80A3C344[] = { 0x00000000, 0x00000000, 0x00000000 };

s32 D_80A3C350[] = { 0x00000000, 0x00000000, 0x00000000 };

s32 D_80A3C35C[] = { 0x060014C8, 0x060018C8, 0x06001CC8 };

extern UNK_TYPE D_060020E8;

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Baguo/EnBaguo_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Baguo/EnBaguo_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Baguo/func_80A3B220.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Baguo/func_80A3B2CC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Baguo/func_80A3B3E0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Baguo/func_80A3B5E0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Baguo/func_80A3B794.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Baguo/func_80A3B7B8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Baguo/func_80A3B8F8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Baguo/func_80A3B958.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Baguo/EnBaguo_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Baguo/func_80A3BE24.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Baguo/func_80A3BE60.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Baguo/func_80A3BF0C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Baguo/func_80A3C008.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Baguo/func_80A3C17C.s")
