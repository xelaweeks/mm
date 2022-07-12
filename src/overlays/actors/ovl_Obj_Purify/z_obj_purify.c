/*
 * File: z_obj_purify.c
 * Overlay: ovl_Obj_Purify
 * Description: Poisoned/Purified Water Elements
 */

#include "z_obj_purify.h"
#include "objects/object_numa_obj/object_numa_obj.h"
#include "objects/object_dekucity_obj/object_dekucity_obj.h"

#define FLAGS (ACTOR_FLAG_10 | ACTOR_FLAG_20)

#define THIS ((ObjPurify*)thisx)

void ObjPurify_Init(Actor* thisx, PlayState* play);
void ObjPurify_Destroy(Actor* thisx, PlayState* play);
void ObjPurify_Update(Actor* thisx, PlayState* play);

void func_80A84EC0(ObjPurify* this, PlayState* play);
void func_80A851C8(Actor *thisx, PlayState *play);
void func_80A85074(ObjPurify* this, PlayState* play);
void func_80A850B0(ObjPurify* this);
void func_80A850E8(ObjPurify *this, PlayState *play);
void func_80A85304(Actor *thisx, PlayState *play);
void func_80A84FB4(ObjPurify *this, PlayState *play);
void func_80A85010(ObjPurify *this, PlayState *play);
void ObjPurify_DoNothing(ObjPurify *this, PlayState *play);
void func_80A85048(ObjPurify* this);
void func_80A84FA0(ObjPurify *this);
void func_80A8515C(ObjPurify *this);
void func_80A84FEC(ObjPurify *this); 
void func_80A84EAC(ObjPurify *this);
 
const ActorInit Obj_Purify_InitVars = {
    ACTOR_OBJ_PURIFY,
    ACTORCAT_BG,
    FLAGS,
    GAMEPLAY_KEEP,
    sizeof(ObjPurify),
    (ActorFunc)ObjPurify_Init,
    (ActorFunc)ObjPurify_Destroy,
    (ActorFunc)ObjPurify_Update,
    (ActorFunc)NULL,
};

// scene info?
ObjPurifyStruct00 D_80A85480[] = {
    {
        0x164,
        { 0, 0 },
        0.1f,
        { NULL, NULL },
        { object_numa_obj_DL_0128E0, object_numa_obj_DL_012D90 },
        { object_numa_obj_Matanimheader_012CF8, object_numa_obj_Matanimheader_0131A8 },
        &object_numa_obj_Colheader_012818,
        0,
    },
    {
        0x19A,
        { 0, 0 },
        1.0f,
        { NULL, NULL },
        { object_dekucity_obj_DL_0004E0, object_dekucity_obj_DL_001030 },
        { object_dekucity_obj_Matanimheader_000E28, object_dekucity_obj_Matanimheader_001978 },
        &object_dekucity_obj_Colheader_0002AC,
        1,
    },
    {
        0x19A,
        { 0, 0 },
        1.0f,
        { object_dekucity_obj_DL_001ED8, object_dekucity_obj_DL_003998 },
        { object_dekucity_obj_DL_001D80, NULL },
        { object_dekucity_obj_Matanimheader_003820, NULL },
        NULL,
        1,
    },
    {
        0x164,
        { 0, 0 },
        0.1f,
        { NULL, NULL },
        { object_numa_obj_DL_012A60, object_numa_obj_DL_012F10 },
        { object_numa_obj_Matanimheader_012B58, object_numa_obj_Matanimheader_013008 },
        &object_numa_obj_Colheader_012818,
        0,
    },
    {
        0x164,
        { 0, 0 },
        0.1f,
        { NULL, NULL },
        { object_numa_obj_DL_012BF0, object_numa_obj_DL_0130A0 },
        { object_numa_obj_Matanimheader_012CE8, object_numa_obj_Matanimheader_013198 },
        &object_numa_obj_Colheader_012818,
        0,
    },
};

// #pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Purify/ObjPurify_SetSysMatrix.s")
// ObjPurify_SetSysMatrix
void ObjPurify_SetSysMatrix(f32 ypos) {
    Matrix_GetCurrent()->yw = ypos;
}

// #pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Purify/ObjPurify_IsPurified.s")
// ObjPurify_IsPurified
s32 ObjPurify_IsPurified(ObjPurify *this) {
    ObjPurifyStruct00 *new_var;
    new_var = &D_80A85480[this->dyna.actor.params & 0xF];
    if (!new_var->unk24) {
        // woodfall temple wood flower unraveled
        if ((gSaveContext.save.weekEventReg[12] & 1)) {
            return 1;
        }
    } 
    // woodfall temple purification cutscene watched
    else if (gSaveContext.save.weekEventReg[20] & 2) {
        return 1;
    }
    return 0;
}

// #pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Purify/ObjPurify_Init.s")
void ObjPurify_Init(Actor *thisx, PlayState *play) {
    ObjPurify *this = THIS;
    s32 pad;
    ObjPurifyStruct00 *temp_v1;
    s32 sp20;

    temp_v1 = &D_80A85480[this->dyna.actor.params & 0xF];
    sp20 = (this->dyna.actor.params >> 0xC) & 1;
    Actor_SetScale(&this->dyna.actor, temp_v1->scale);
    if (sp20 == 1) {
        DynaPolyActor_Init((DynaPolyActor *) this, 0);
    }
    this->objIndex = Object_GetIndex(&play->objectCtx, temp_v1->id);
    if (this->objIndex < 0) {
        Actor_MarkForDeath(&this->dyna.actor);
    } else if (sp20 == 0) {
        func_80A84EAC(this);
    } else if (ObjPurify_IsPurified(this) != 0) {
        Actor_MarkForDeath(&this->dyna.actor);
    } else {
        func_80A84EAC(this);
    }
}

// #pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Purify/ObjPurify_Destroy.s")
void ObjPurify_Destroy(Actor *thisx, PlayState *play) {
    ObjPurify *this = THIS;
    if (((this->dyna.actor.params >> 0xC) & 1) == 1) {
        DynaPoly_DeleteBgActor(play, &play->colCtx.dyna, this->dyna.bgId);
    }
}

// #pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Purify/func_80A84EAC.s")
void func_80A84EAC(ObjPurify *this) {
    this->actionFunc = func_80A84EC0;
}

// #pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Purify/func_80A84EC0.s")
void func_80A84EC0(ObjPurify *this, PlayState *play) {
    s16 pad;
    s32 sp28;
    s32 sp24;

    if (Object_IsLoaded(&play->objectCtx, this->objIndex) != 0) {
        sp28 = (this->dyna.actor.params >> 0xC) & 1;
        sp24 = this->dyna.actor.params & 0xF;
        this->dyna.actor.objBankIndex = this->objIndex;
        Actor_SetObjectDependency(play, &this->dyna.actor);
        if (sp28 == 1) {
            DynaPolyActor_LoadMesh(play, &this->dyna, D_80A85480[sp24].colHeader);
            func_80A84FA0(this);
        } else if (ObjPurify_IsPurified(this)) {
            func_80A8515C(this);
        } else {
            func_80A84FEC(this);
        }
    }
}

// #pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Purify/func_80A84FA0.s")
void func_80A84FA0(ObjPurify *this) {
    this->actionFunc = func_80A84FB4;
}

// #pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Purify/func_80A84FB4.s")
void func_80A84FB4(ObjPurify *this, PlayState *play) {
    if (ObjPurify_IsPurified(this)) {
        Actor_MarkForDeath(&this->dyna.actor);
    }
}

// #pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Purify/func_80A84FEC.s")
void func_80A84FEC(ObjPurify *this) {
    this->dyna.actor.draw = func_80A851C8;
    this->gfxIndex = 0;
    this->actionFunc = func_80A85010;
}

// #pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Purify/func_80A85010.s")
void func_80A85010(ObjPurify *this, PlayState *play) {
    if (ObjPurify_IsPurified(this)) {
        func_80A85048(this);
    }
}

// #pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Purify/func_80A85048.s")
void func_80A85048(ObjPurify *this) {
    this->dyna.actor.draw = func_80A851C8;
    this->gfxIndex = 0;
    this->actionFunc = func_80A85074;
    this->unk164 = 0x1E;
}

// #pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Purify/func_80A85074.s")
void func_80A85074(ObjPurify *this, PlayState *play) {
    this->unk164--;
    if (this->unk164 <= 0) {
        func_80A850B0(this);
    }
}

// #pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Purify/func_80A850B0.s")
void func_80A850B0(ObjPurify *this) {
    f32 ypos = this->dyna.actor.home.pos.y;
    this->dyna.actor.draw = func_80A85304;
    this->unk168[1] = ypos - 90.0f;
    this->actionFunc = func_80A850E8;
    this->unk168[0] = ypos;
}

// #pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Purify/func_80A850E8.s")
void func_80A850E8(ObjPurify *this, PlayState *play) {
    Math_StepToF(&this->unk168[0], this->dyna.actor.home.pos.y - 90.0f, 0.9f);
    if (Math_StepToF(&this->unk168[1], this->dyna.actor.home.pos.y, 0.9f)) {
        func_80A8515C(this);
    }
}

// #pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Purify/func_80A8515C.s")
void func_80A8515C(ObjPurify *this) {
    this->dyna.actor.flags &= ~0x10;
    this->dyna.actor.draw = func_80A851C8;
    this->gfxIndex = 1;
    this->actionFunc = ObjPurify_DoNothing;
}

// #pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Purify/ObjPurify_DoNothing.s")
void ObjPurify_DoNothing(ObjPurify *this, PlayState *play) {
}

// #pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Purify/ObjPurify_Update.s")
void ObjPurify_Update(Actor *thisx, PlayState *play) {
    ObjPurify *this = THIS;
    this->actionFunc(this, play);
}

// draw func
// #pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Purify/func_80A851C8.s")
void func_80A851C8(Actor *thisx, PlayState *play) {
    s32 pad;
    ObjPurify *this = (ObjPurify *) thisx;
    ObjPurifyStruct00 *temp_v0;
    Gfx* sp40;
    Gfx* sp3C;
    AnimatedMaterial *temp_a2;
    
    temp_v0 = &D_80A85480[this->dyna.actor.params & 0xF];
    sp40 = temp_v0->opaDList[this->gfxIndex];
    sp3C = temp_v0->xluDList[this->gfxIndex];
    temp_a2 = temp_v0->animMat[this->gfxIndex];
    
    OPEN_DISPS(play->state.gfxCtx);

    if (temp_a2 != NULL) {
        AnimatedMat_Draw(play, Lib_SegmentedToVirtual(temp_a2));
    }
    if (sp40 != 0) {
        func_8012C28C(play->state.gfxCtx);
        gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(play->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        gSPDisplayList(POLY_OPA_DISP++, sp40);
    }
    if (sp3C != 0) {
        func_8012C2DC(play->state.gfxCtx);
        gSPMatrix(POLY_XLU_DISP++, Matrix_NewMtx(play->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        gSPDisplayList(POLY_XLU_DISP++, sp3C);
    }

    CLOSE_DISPS(play->state.gfxCtx);
}

// #pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Purify/func_80A85304.s")
// also a draw func
void func_80A85304(Actor *thisx, PlayState *play) {
    s32 pad;
    ObjPurify* this = THIS;
    ObjPurifyStruct00* sp74 = &D_80A85480[this->dyna.actor.params & 0xF];
    s32 sp6C[2];
    s32 i;
    s32 tmp3;


    sp74 = &D_80A85480[this->dyna.actor.params & 0xF];
    if (this->unk168[1] < this->unk168[0]) {
        sp6C[0] = 1;
        sp6C[1] = 0;
    } else {
        sp6C[0] = 0;
        sp6C[1] = 1;
    }

    OPEN_DISPS(play->state.gfxCtx);
    func_8012C2DC(play->state.gfxCtx);
    for (i = 0; i < 2; i++) {
        tmp3 = sp6C[i];
        AnimatedMat_Draw(play, Lib_SegmentedToVirtual(sp74->animMat[tmp3]));
        ObjPurify_SetSysMatrix(this->unk168[tmp3]);
        gSPMatrix(POLY_XLU_DISP++, Matrix_NewMtx(play->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        gSPDisplayList(POLY_XLU_DISP++, sp74->xluDList[tmp3]);
    };
    CLOSE_DISPS(play->state.gfxCtx);
}