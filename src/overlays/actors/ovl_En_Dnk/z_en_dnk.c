#include "z_en_dnk.h"

#define FLAGS 0x00000009

#define THIS ((EnDnk*)thisx)

void EnDnk_Init(Actor* thisx, GlobalContext* globalCtx);
void EnDnk_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnDnk_Update(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit En_Dnk_InitVars = {
    ACTOR_EN_DNK,
    ACTORTYPE_NPC,
    FLAGS,
    GAMEPLAY_KEEP,
    sizeof(EnDnk),
    (ActorFunc)EnDnk_Init,
    (ActorFunc)EnDnk_Destroy,
    (ActorFunc)EnDnk_Update,
    (ActorFunc)NULL
};
*/

GLOBAL_ASM("asm/non_matchings/ovl_En_Dnk_0x80A514F0/func_80A514F0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Dnk_0x80A514F0/func_80A515C4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Dnk_0x80A514F0/func_80A51648.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Dnk_0x80A514F0/func_80A51890.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Dnk_0x80A514F0/func_80A518DC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Dnk_0x80A514F0/EnDnk_Init.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Dnk_0x80A514F0/EnDnk_Destroy.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Dnk_0x80A514F0/EnDnk_Update.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Dnk_0x80A514F0/func_80A51A78.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Dnk_0x80A514F0/func_80A51AA4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Dnk_0x80A514F0/func_80A51CB8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Dnk_0x80A514F0/func_80A51D78.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Dnk_0x80A514F0/func_80A51DA4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Dnk_0x80A514F0/func_80A51FC0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Dnk_0x80A514F0/func_80A52018.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Dnk_0x80A514F0/func_80A52074.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Dnk_0x80A514F0/func_80A52134.asm")
