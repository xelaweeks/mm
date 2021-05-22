#include "z_en_ma4.h"

#define FLAGS 0x02000039

#define THIS ((EnMa4*)thisx)

void EnMa4_Init(Actor* thisx, GlobalContext* globalCtx);
void EnMa4_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnMa4_Update(Actor* thisx, GlobalContext* globalCtx);
void EnMa4_Draw(Actor* thisx, GlobalContext* globalCtx);



void func_80ABDCA0(EnMa4* this); // TODO: remove
void func_80ABDD2C(EnMa4* this, s32); // TODO: remove // not sure about s32
void func_80ABDD9C(EnMa4* this, GlobalContext* globalCtx); // TODO: remove
void func_80ABDE60(EnMa4* this, GlobalContext* globalCtx); // TODO: remove
//void func_80ABE1C4(EnMa4* this, GlobalContext* globalCtx);
void func_80ABE4A4(EnMa4* this);
//void func_80ABE560(EnMa4* this, GlobalContext* globalCtx);
//void func_80ABE6C8(EnMa4* this, GlobalContext* globalCtx);
//void func_80ABEB6C(EnMa4* this, GlobalContext* globalCtx);
//void func_80ABEF34(EnMa4* this, GlobalContext* globalCtx);
//void func_80ABEF8C(EnMa4* this, GlobalContext* globalCtx);
//void func_80ABF070(EnMa4* this, GlobalContext* globalCtx);
//void func_80ABF084(EnMa4* this, GlobalContext* globalCtx);
//void func_80ABF0D8(EnMa4* this, GlobalContext* globalCtx);
//void func_80ABF160(EnMa4* this, GlobalContext* globalCtx);
void func_80ABF198(EnMa4* this, GlobalContext* globalCtx);
//void func_80ABF218(EnMa4* this, GlobalContext* globalCtx);
//void func_80ABF254(EnMa4* this, GlobalContext* globalCtx);
//void func_80ABF2FC(EnMa4* this, GlobalContext* globalCtx);
//void func_80ABF354(EnMa4* this, GlobalContext* globalCtx);
//void func_80ABF494(EnMa4* this, GlobalContext* globalCtx);
//void func_80ABF4A8(EnMa4* this, GlobalContext* globalCtx);
//void func_80ABF51C(EnMa4* this, GlobalContext* globalCtx);
//void func_80ABF534(EnMa4* this, GlobalContext* globalCtx);
//void func_80ABF69C(EnMa4* this, GlobalContext* globalCtx);
//void func_80ABF6B0(EnMa4* this, GlobalContext* globalCtx);
//void func_80ABF760(EnMa4* this, GlobalContext* globalCtx);
//void func_80ABF774(EnMa4* this, GlobalContext* globalCtx);
//void func_80ABF7C8(EnMa4* this, GlobalContext* globalCtx);
//void func_80ABFCAC(EnMa4* this, GlobalContext* globalCtx);
//void func_80ABFCD4(EnMa4* this, GlobalContext* globalCtx);



/*
const ActorInit En_Ma4_InitVars = {
    ACTOR_EN_MA4,
    ACTORCAT_NPC,
    FLAGS,
    OBJECT_MA1,
    sizeof(EnMa4),
    (ActorFunc)EnMa4_Init,
    (ActorFunc)EnMa4_Destroy,
    (ActorFunc)EnMa4_Update,
    (ActorFunc)EnMa4_Draw,
};
*/

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ma4_0x80ABDCA0/func_80ABDCA0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ma4_0x80ABDCA0/func_80ABDD2C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ma4_0x80ABDCA0/func_80ABDD9C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ma4_0x80ABDCA0/func_80ABDE60.asm")

extern FlexSkeletonHeader D_06013928;

extern ColliderCylinderInit D_80AC00B0;
extern CollisionCheckInfoInit2 D_80AC00DC;

#ifdef NON_MATCHING
void EnMa4_Init(Actor* thisx, GlobalContext* globalCtx) {
    EnMa4* this = THIS;
    u32 temp_v0;

    ActorShape_Init(&this->actor.shape, 0.0f, func_800B3FC0, 18.0f);
    SkelAnime_InitSV(globalCtx, &this->skelAnime, &D_06013928, NULL, this->limbDrawTable, this->transitionDrawTable, OBJECT_MA1_LIMB_TABLE_COUNT);
    Collider_InitCylinder(globalCtx, &this->collider);
    Collider_SetCylinder(globalCtx, &this->collider, &this->actor, &D_80AC00B0);
    CollisionCheck_SetInfo2(&this->actor.colChkInfo, DamageTable_Get(0x16), &D_80AC00DC);
    func_800B78B8(globalCtx, &this->actor, 0.0f, 0.0f, 0.0f, 4);
    Actor_SetScale(&this->actor, 0.01f);
    this->actor.targetMode = 0;
    this->unk_1D8 = (u16)0;
    this->unk_334 = (u16)0;
    this->unk_33A = 1;
    this->unk_330 = (u16)0;
    this->unk_33C = (u16)0;

    if (CURRENT_DAY == (u16)1) {
        this->unk_332 = (u16)0;
    } else if ((gSaveContext.perm.weekEventReg[0x16] & 1) != 0) {
        this->unk_332 = (u16)1;
    } else {
        this->unk_332 = (u16)2;
        this->unk_33A = 0;
    }

    if (func_800EE1D8(globalCtx) != 0) {
        func_80ABDD2C(this, 0);
        this->unk_336 = (u16)1;
        func_80ABF198(this, globalCtx);
    } else {
        func_80ABDE60(this, globalCtx);
        temp_v0 = gSaveContext.perm.entranceIndex;
        if (temp_v0 == 0x6410) {
            func_80ABDD2C(this, 0);
            this->unk_336 = (u16)2;
        } else if (temp_v0 == 0x64A0) {
            func_80ABDD2C(this, 0);
            this->unk_336 = (u16)3;
        } else {
            if (this->unk_332 == 2) {
                func_80ABDD2C(this, 0xE);
                this->actor.shape.shadowScale = 0.0f;
            } else {
                func_80ABDD2C(this, 8);
            }
            this->unk_336 = (u16)0;
        }
        func_80ABE4A4(this);
    }
}
#else
#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ma4_0x80ABDCA0/EnMa4_Init.asm")
#endif

void EnMa4_Destroy(Actor* thisx, GlobalContext* globalCtx) {
    EnMa4* this = THIS;

    Collider_DestroyCylinder(globalCtx, &this->collider);
    gSaveContext.perm.weekEventReg[0x8] &= 0xFE;
}


#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ma4_0x80ABDCA0/func_80ABE1C4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ma4_0x80ABDCA0/func_80ABE4A4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ma4_0x80ABDCA0/func_80ABE560.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ma4_0x80ABDCA0/func_80ABE6C8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ma4_0x80ABDCA0/func_80ABEB6C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ma4_0x80ABDCA0/func_80ABEF34.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ma4_0x80ABDCA0/func_80ABEF8C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ma4_0x80ABDCA0/func_80ABF070.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ma4_0x80ABDCA0/func_80ABF084.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ma4_0x80ABDCA0/func_80ABF0D8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ma4_0x80ABDCA0/func_80ABF160.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ma4_0x80ABDCA0/func_80ABF198.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ma4_0x80ABDCA0/func_80ABF218.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ma4_0x80ABDCA0/func_80ABF254.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ma4_0x80ABDCA0/func_80ABF2FC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ma4_0x80ABDCA0/func_80ABF354.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ma4_0x80ABDCA0/func_80ABF494.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ma4_0x80ABDCA0/func_80ABF4A8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ma4_0x80ABDCA0/func_80ABF51C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ma4_0x80ABDCA0/func_80ABF534.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ma4_0x80ABDCA0/func_80ABF69C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ma4_0x80ABDCA0/func_80ABF6B0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ma4_0x80ABDCA0/func_80ABF760.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ma4_0x80ABDCA0/func_80ABF774.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ma4_0x80ABDCA0/func_80ABF7C8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ma4_0x80ABDCA0/func_80ABFCAC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ma4_0x80ABDCA0/func_80ABFCD4.asm")


void EnMa4_Update(Actor* thisx, GlobalContext* globalCtx) {
    EnMa4* this = THIS;
    s32 pad;

    Collider_UpdateCylinder(&this->actor, &this->collider);
    CollisionCheck_SetOC(globalCtx, &globalCtx->colCheckCtx, &this->collider.base);
    SkelAnime_FrameUpdateMatrix(&this->skelAnime);
    func_80ABDCA0(this);
    this->actionFunc(this, globalCtx);
    func_80ABDD9C(this, globalCtx);
}


// EnMa4_OverrideLimbDraw
s32 func_80ABFD9C(GlobalContext *globalCtx, s32 limbIndex, Gfx **dList, Vec3f *pos, Vec3s *rot, Actor *thisx) {
    EnMa4* this = THIS;
    Vec3s sp4;

    if (limbIndex == OBJECT_MA1_LIMB_HAIR_TOP) {
        sp4 = this->unk_1E0;
        rot->x = rot->x + sp4.y;
        rot->z = rot->z + sp4.x;
    }
    if (limbIndex == OBJECT_MA1_LIMB_HEAD) {
        sp4 = this->unk_1E6;
        rot->x = rot->x - sp4.y;
        rot->z = rot->z - sp4.x;
    }

    return 0;
}


extern Vec3f D_80AC0264;
extern Gfx D_060003B0[];

// EnMa4_PostLimbDraw
void func_80ABFE48(GlobalContext *globalCtx, s32 limbIndex, Gfx **dList, Vec3s *rot, Actor *thisx) {
    EnMa4* this = THIS;
    Vec3f sp28;

    sp28 = D_80AC0264;
    if (limbIndex == OBJECT_MA1_LIMB_HAIR_TOP) {
        SysMatrix_MultiplyVector3fByState(&sp28, &this->actor.focus.pos);
    } else if ((limbIndex == OBJECT_MA1_LIMB_ARM_RIGHT) && (this->unk_33A == 1)) {
        OPEN_DISPS(globalCtx->state.gfxCtx);
        gSPDisplayList(POLY_OPA_DISP++, D_060003B0);
        CLOSE_DISPS(globalCtx->state.gfxCtx);
    }
}


extern void* D_80AC00E8[]; // eye textures
extern void* D_80AC00FC[]; // mouth textures

extern Gfx D_06000A20[];

void EnMa4_Draw(Actor* thisx, GlobalContext* globalCtx) {
    EnMa4* this = THIS;

    OPEN_DISPS(globalCtx->state.gfxCtx);

    if (this->unk_332 == 2) {
        gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(globalCtx->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        gSPDisplayList(POLY_OPA_DISP++, D_06000A20);
    }

    func_8012C28C(globalCtx->state.gfxCtx);

    gSPSegment(POLY_OPA_DISP++, 0x08, SEGMENTED_TO_VIRTUAL(D_80AC00E8[this->unk_32E]));
    gSPSegment(POLY_OPA_DISP++, 0x09, SEGMENTED_TO_VIRTUAL(D_80AC00FC[this->unk_330]));

    SkelAnime_DrawSV(globalCtx, this->skelAnime.skeleton, this->skelAnime.limbDrawTbl, (s32) this->skelAnime.dListCount, func_80ABFD9C, func_80ABFE48, &this->actor);

    CLOSE_DISPS(globalCtx->state.gfxCtx);
}
