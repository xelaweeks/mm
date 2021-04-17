#include "z_obj_ending.h"

#define FLAGS 0x00000030

#define THIS ((ObjEnding*)thisx)

void ObjEnding_Init(Actor* thisx, GlobalContext* globalCtx);
void ObjEnding_Update(Actor* thisx, GlobalContext* globalCtx);
void ObjEnding_Draw(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit Obj_Ending_InitVars = {
    ACTOR_OBJ_ENDING,
    ACTORCAT_BG,
    FLAGS,
    OBJECT_ENDING_OBJ,
    sizeof(ObjEnding),
    (ActorFunc)ObjEnding_Init,
    (ActorFunc)func_800BDFB0,
    (ActorFunc)ObjEnding_Update,
    (ActorFunc)ObjEnding_Draw
};
*/

extern InitChainEntry D_80C25CF8[];
/*
static InitChainEntry sInitChain[] = {
    ICHAIN_VEC3F_DIV1000(scale, 100, ICHAIN_STOP),
};
*/

extern unkStruct D_80C25CE0[];

void ObjEnding_Init(Actor* thisx, GlobalContext *globalCtx) {
    ObjEnding* this = THIS;
    UNK_PTR *tempPtr;

    Actor_ProcessInitChain(&this->actor, D_80C25CF8);
    this->unk144 = &D_80C25CE0[this->actor.params];
    if(false){}
    tempPtr = this->unk144->unk8;
    
    if (tempPtr != NULL) {
        this->texturePtr = Lib_SegmentedToVirtual(tempPtr);
    }
}

void ObjEnding_Update(Actor *thisx, GlobalContext *globalCtx) {
}

void ObjEnding_Draw(Actor *thisx, GlobalContext *globalCtx) {
    ObjEnding *this = THIS;
    Gfx *dl;
    UNK_TYPE4 tempunk4;

    if (this->texturePtr != NULL) {
        SceneProc_DrawAllSceneAnimatedTextures(globalCtx, this->texturePtr);
    }
    tempunk4 = this->unk144->unk0;
    if (tempunk4 != 0) {
        func_800BDFC0(globalCtx, tempunk4);
    }
    dl = this->unk144->dl;
    if (dl != NULL) {
        func_800BE03C(globalCtx, dl);
    }
}
