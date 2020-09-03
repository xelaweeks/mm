#include "z_en_pr.h"

#define FLAGS 0x00000015

#define THIS ((EnPr*)thisx)

void EnPr_Init(Actor* thisx, GlobalContext* globalCtx);
void EnPr_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnPr_Update(Actor* thisx, GlobalContext* globalCtx);
void EnPr_Draw(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit En_Pr_InitVars = {
    ACTOR_EN_PR,
    ACTORTYPE_ENEMY,
    FLAGS,
    OBJECT_PR,
    sizeof(EnPr),
    (ActorFunc)EnPr_Init,
    (ActorFunc)EnPr_Destroy,
    (ActorFunc)EnPr_Update,
    (ActorFunc)EnPr_Draw
};
*/

GLOBAL_ASM("asm/non_matchings/ovl_En_Pr_0x80A32210/EnPr_Init.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Pr_0x80A32210/EnPr_Destroy.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Pr_0x80A32210/func_80A3242C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Pr_0x80A32210/func_80A324E0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Pr_0x80A32210/func_80A325E4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Pr_0x80A32210/func_80A326F0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Pr_0x80A32210/func_80A32740.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Pr_0x80A32210/func_80A32854.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Pr_0x80A32210/func_80A3289C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Pr_0x80A32210/func_80A3295C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Pr_0x80A32210/func_80A32984.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Pr_0x80A32210/func_80A32A40.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Pr_0x80A32210/func_80A32AF8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Pr_0x80A32210/func_80A32B20.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Pr_0x80A32210/func_80A32CDC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Pr_0x80A32210/func_80A32D28.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Pr_0x80A32210/func_80A32E60.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Pr_0x80A32210/func_80A32EA4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Pr_0x80A32210/func_80A32F48.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Pr_0x80A32210/func_80A33098.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Pr_0x80A32210/EnPr_Update.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Pr_0x80A32210/func_80A3357C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Pr_0x80A32210/func_80A335B4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Pr_0x80A32210/EnPr_Draw.asm")
