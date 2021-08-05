#include "z_obj_mure.h"

#define FLAGS 0x00000000

#define THIS ((ObjMure*)thisx)

void ObjMure_Init(Actor* thisx, GlobalContext* globalCtx);
void ObjMure_Destroy(Actor* thisx, GlobalContext* globalCtx);
void ObjMure_Update(Actor* thisx, GlobalContext* globalCtx);

void func_808D7FFC(ObjMure* this, GlobalContext* globalCtx);
void func_808D8014(ObjMure* this, GlobalContext* globalCtx);
#define ObjMure_CulledState func_808D8014
void func_808D8678(ObjMure* this, GlobalContext* globalCtx);
#define ObjMure_ActiveState func_808D8678
void func_808D7F0C(ObjMure* this, GlobalContext* globalCtx);
#define ObjMure_KillActors func_808D7F0C
void func_808D7F2C(ObjMure* this, GlobalContext* globalCtx);
#define ObjMure_CheckChildren func_808D7F2C

const ActorInit Obj_Mure_InitVars = {
    ACTOR_OBJ_MURE,
    ACTORCAT_ITEMACTION,
    FLAGS,
    GAMEPLAY_KEEP,
    sizeof(ObjMure),
    (ActorFunc)ObjMure_Init,
    (ActorFunc)ObjMure_Destroy,
    (ActorFunc)ObjMure_Update,
    (ActorFunc)NULL,
};

static f32 D_808D8780[] = { 1600.0f, 1600.0f, 1000.0f, 1000.0f, 1000.0f };
#define sZClip D_808D8780

static s32 D_808D8794[] = { 12, 9, 8, 0 };
#define sMaxChildSpawns D_808D8794

#define sSpawnActorIds D_808D87A4
static s16 D_808D87A4[] = { ACTOR_EN_KUSA, 0, ACTOR_EN_FISH, ACTOR_EN_INSECT, ACTOR_EN_BUTTE };

#define sSpawnParams D_808D87B0
static s16 D_808D87B0[] = { 0, 2, -1, 0, -1 };

// static InitChainEntry sInitChain[] = {
static InitChainEntry D_808D87BC[] = {
    ICHAIN_F32(uncullZoneForward, 1200, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneScale, 200, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneDownward, 1200, ICHAIN_STOP),
};

typedef enum {
    /* 0 */ OBJMURE_TYPE_GRASS,
    /* 1 */ OBJMURE_TYPE_UNDEFINED,
    /* 2 */ OBJMURE_TYPE_FISH,
    /* 3 */ OBJMURE_TYPE_BUGS,
    /* 4 */ OBJMURE_TYPE_BUTTERFLY
} ObjMureType;

typedef enum {
    /* 0 */ OBJMURE_CHILD_STATE_0,
    /* 1 */ OBJMURE_CHILD_STATE_1, // Dead
    /* 2 */ OBJMURE_CHILD_STATE_2
} ObjMureChildState;

s32 func_808D78D0(ObjMure* this, GlobalContext* globalCtx);
#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Mure/func_808D78D0.s")
//s32 func_808D78D0(Actor* thisx, GlobalContext* arg1) {
//    s32 result;
//    ObjMure* this = THIS;
//
//    //switch(this->unk_14E)  {
//    //    case 2:
//    //    case 3:
//    //    case 4:
//
//    if (this->type == 2 || this->type == 3 || this->type == 4) {
//        Actor_ProcessInitChain(this, D_808D87BC);
//        result = true;
//    }
//    else {
//            result = false;
//    }
//    return result;
//}

void func_808D7FFC(ObjMure* this, GlobalContext* globalCtx);

s32 func_808D7928(ObjMure* this, GlobalContext* globalCtx) {
    if (!func_808D78D0(this, globalCtx)) {
        return false;
    }
    return true;
}

void ObjMure_Init(Actor* thisx, GlobalContext* globalCtx) {
    ObjMure* this = THIS;

    this->chNum = (this->actor.params >> 0xC) & 0xF;
    this->ptn = (this->actor.params >> 8) & 7;
    this->svNum = (this->actor.params >> 5) & 3;
    this->type = this->actor.params & 0x1F;
    if (this->ptn >= 4) {
        Actor_MarkForDeath(&this->actor);
        return;
    }
    if (this->type >= 5) {
        Actor_MarkForDeath(&this->actor);
        return;
    }
    if (!func_808D7928(this, globalCtx)) {
        Actor_MarkForDeath(&this->actor);
        return;
    }
    this->actionFunc = func_808D7FFC;
}

void ObjMure_Destroy(Actor* thisx, GlobalContext* globalCtx) {
}

#define ObjMure_GetMaxChildSpawns func_808D7A14
s32 ObjMure_GetMaxChildSpawns(ObjMure* this) {
    if (this->chNum == 0) {
        return D_808D8794[this->ptn];
    }
    return this->chNum;
}

#define ObjMure_GetSpawnPos func_808D7A40
//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Mure/func_808D7A40.s")
void ObjMure_GetSpawnPos(Vec3f* outPos, Vec3f* inPos, s32 ptn, s32 idx) {
    *outPos = *inPos;
}

#define ObjMure_SpawnActors0 func_808D7A68
void ObjMure_SpawnActors0(ObjMure* this, GlobalContext* globalCtx);
#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Mure/func_808D7A68.s")
//void ObjMure_SpawnActors0(ObjMure* this, GlobalContext* globalCtx) {
//    ActorContext* ac;
//    s32 i;
//    Vec3f pos;
//    s32 pad;
//    //PosRot* world;
//    s32 maxChildren = ObjMure_GetMaxChildSpawns(this);
//
//    for (i = 0; i < maxChildren; i++) {
//        switch (this->childrenStates[i]) {
//            case OBJMURE_CHILD_STATE_1:
//                break;
//            case OBJMURE_CHILD_STATE_2:
//                ac = &globalCtx->actorCtx;
//                ObjMure_GetSpawnPos(&pos, &this->actor.world.pos, this->ptn, i);
//                this->children[i] =
//                    Actor_SpawnAsChildAndCutscene(
//                        ac,
//                        globalCtx,
//                        sSpawnActorIds[this->type],
//                        pos.x, pos.y, pos.z,
//                        this->actor.world.rot.x,
//                        this->actor.world.rot.y,
//                        this->actor.world.rot.z,
//                        sSpawnParams[this->type],
//                        this->actor.cutscene,
//                        this->actor.unk20, NULL);
//                if (this->children[i] != NULL) {
//                    //this->children[i]->flags |= 0x800;
//                    if (this->type == 0x90) {
//                        ((ObjMureChild*)this->children[i])->unk_197 = 1;
//                    }
//                    this->children[i]->room = this->actor.room;
//                }
//                break;
//            default:
//                ac = &globalCtx->actorCtx;
//                ObjMure_GetSpawnPos(&pos, &this->actor.world.pos, this->ptn, i);
//                this->children[i] = Actor_SpawnAsChildAndCutscene(
//                    ac,
//                    globalCtx, 
//                    sSpawnActorIds[this->type],
//                    pos.x, pos.y, pos.z,
//                    this->actor.world.rot.x, 
//                    this->actor.world.rot.y, 
//                    this->actor.world.rot.z,
//                    sSpawnParams[this->type],
//                    this->actor.cutscene,
//                    this->actor.unk20,
//                    NULL);
//                if (this->children[i] != NULL) {
//                    this->children[i]->room = this->actor.room;
//                }
//                break;
//        }
//    }
//}

#define ObjMure_SpawnActors1 func_808D7C64
void ObjMure_SpawnActors1(ObjMure* this, GlobalContext* globalCtx);
#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Mure/func_808D7C64.s")


#define ObjMure_SpawnActors func_808D7DC4
//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Mure/func_808D7DC4.s")
void ObjMure_SpawnActors(ObjMure* this, GlobalContext* globalCtx) {
    switch (this->svNum) {
    case 0:
        ObjMure_SpawnActors0(this, globalCtx);
        break;
    case 1:
        ObjMure_SpawnActors1(this, globalCtx);
        break;
    }
}

#define ObjMure_KillActorsImpl func_808D7E14
void ObjMure_KillActorsImpl(ObjMure* this, GlobalContext* globalCtx) {
    s32 maxChildren = ObjMure_GetMaxChildSpawns(this);
    s32 i;

    for (i = 0; i < maxChildren; i++) {
        switch (this->childrenStates[i]) {
        case OBJMURE_CHILD_STATE_1:
            this->children[i] = NULL;
            break;
        case OBJMURE_CHILD_STATE_2:
            if (this->children[i] != NULL) {
                Actor_MarkForDeath(this->children[i]);
                this->children[i] = NULL;
            }
            break;
        default:
            if (this->children[i] != NULL) {
                if (Actor_HasParent(this->children[i], globalCtx)) {
                    this->children[i] = NULL;
                }
                else {
                    Actor_MarkForDeath(this->children[i]);
                    this->children[i] = NULL;
                }
            }
            break;
        }
    }
}

void ObjMure_KillActors(ObjMure* this, GlobalContext* globalCtx) {
    ObjMure_KillActorsImpl(this, globalCtx);
}

void ObjMure_CheckChildren(ObjMure* this, GlobalContext* globalCtx) {
    s32 maxChildren = ObjMure_GetMaxChildSpawns(this);
    s32 i;

    for (i = 0; i < maxChildren; i++) {
        if (this->children[i] != NULL) {
            if (this->childrenStates[i] == OBJMURE_CHILD_STATE_0) {
                if (this->children[i]->update != NULL) {
                    if ((this->type == 0x90) && (((ObjMureChild*)this->children[i])->unk_197 != 0)){
                        this->childrenStates[i] = OBJMURE_CHILD_STATE_2;
                    }
                }
                else {
                    this->childrenStates[i] = OBJMURE_CHILD_STATE_1;
                    this->children[i] = NULL;
                }
            }
            else if (this->childrenStates[i] == OBJMURE_CHILD_STATE_2 && this->children[i]->update == NULL) {
                this->childrenStates[i] = OBJMURE_CHILD_STATE_1;
                this->children[i] = NULL;
            }
        }
    }
}

#define ObjMure_InitialAction func_808D7FFC
void ObjMure_InitialAction(ObjMure* this, GlobalContext* globalCtx) {
    this->actionFunc = ObjMure_CulledState;
}

void ObjMure_CulledState(ObjMure* this, GlobalContext* globalCtx) {
    if (fabsf(this->actor.projectedPos.z) < sZClip[this->type]) {
        this->actionFunc = ObjMure_ActiveState;
        this->actor.flags |= 0x10;
        ObjMure_SpawnActors(this, globalCtx);
    }
}

#define ObjMure_SetFollowTargets func_808D8074
void ObjMure_SetFollowTargets(ObjMure* this, f32 randMax) {
    s32 index;
    s32 maxChildren = ObjMure_GetMaxChildSpawns(this);
    s32 i;

    for (i = 0; i < maxChildren; i++) {
        if (this->children[i] != NULL) {
            this->children[i]->child = NULL;
            if (Rand_ZeroOne() <= randMax) {
                index = Rand_ZeroOne() * (maxChildren - 0.5f);
                if (i != index) {
                    this->children[i]->child = this->children[index];
                }
            }
        }
    }
}

#define ObjMure_SetChildToFollowPlayer func_808D814C
/**
 * Selects a child that will follow after the player
 * `idx1` is the index + 1 of the child that will follow the player. If `idx1` is zero, no actor will follow the player
 */
void ObjMure_SetChildToFollowPlayer(ObjMure* this, s32 idx1) {
    s32 maxChildren = ObjMure_GetMaxChildSpawns(this);
    s32 i;
    s32 i2;
    s32 j;

    for (i = 0, i2 = 0; i < maxChildren; i++) {
        if (this->children[i] != NULL) {
            if (i2 < idx1) {
                i2++;
                this->children[i]->child = this->children[i];
                for (j = 0; j < maxChildren; j++) {
                    if (i != j && this->children[j]->child == this->children[i]) {
                        this->children[j]->child = NULL;
                    }
                }
            }
            else if (this->children[i]->child == this->children[i]) {
                this->children[i]->child = NULL;
            }
        }
    }
}

void func_808D82CC(ObjMure* this, GlobalContext* globalCtx);
void func_808D84F4(ObjMure* this, GlobalContext* globalCtx);

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Mure/func_808D82CC.s")
// Fish, Bugs
void func_808D82CC(ObjMure* this, GlobalContext* globalCtx);
#define ObjMure_GroupBehavior0 func_808D82CC

//void ObjMure_GroupBehavior0(ObjMure* this, GlobalContext* globalCtx) {
//    if (this->unk_1A4 <= 0) {
//        if (this->unk_1A6) {
//            this->unk_1A6 = false;
//            ObjMure_SetFollowTargets(this, (Rand_ZeroOne() * 0.5f) + 0.1f);
//            if (this->actor.xzDistToPlayer < 60.0f) {
//                this->unk_1A4 = (s16)(Rand_ZeroOne() * 5.5f) + 4;
//            }
//            else {
//                this->unk_1A4 = (s16)(Rand_ZeroOne() * 40.5f) + 4;
//            }
//        }
//        else {
//            this->unk_1A6 = true;
//            if (this->actor.xzDistToPlayer < 60.0f) {
//                this->unk_1A4 = (s16)(Rand_ZeroOne() * 10.5f) + 4;
//                ObjMure_SetFollowTargets(this, (Rand_ZeroOne() * 0.2f) + 0.8f);
//            }
//            else {
//                this->unk_1A4 = (s16)(Rand_ZeroOne() * 10.5f) + 4;
//                ObjMure_SetFollowTargets(this, (Rand_ZeroOne() * 0.2f) + 0.6f);
//            }
//        }
//    }
//    if (this->actor.xzDistToPlayer < 120.0f) {
//        this->unk_1A8++;
//    }
//    else {
//        this->unk_1A8 = 0;
//    }
//    if (this->unk_1A8 >= 80) {
//        ObjMure_SetChildToFollowPlayer(this, 1);
//    }
//    else {
//        ObjMure_SetChildToFollowPlayer(this, 0);
//    }
//}

void func_808D84F4(ObjMure* this, GlobalContext* globalCtx);
#define ObjMure_GroupBehavior1 func_808D84F4
#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Mure/func_808D84F4.s")
// Butterflies
//void func_808D84F4(ObjMure* this, GlobalContext* globalCtx) {
//#define ObjMure_GroupBehavior1 func_808D84F4
//    s32 maxChildren;
//    s32 i;
//
//    if (this->unk_1A4 <= 0) {
//        if (this->unk_1A6) {
//            this->unk_1A6 = false;
//            ObjMure_SetFollowTargets(this, Rand_ZeroOne() * 0.2f);
//            if (this->actor.xzDistToPlayer < 60.0f) {
//                this->unk_1A4 = (s16)(Rand_ZeroOne() * 5.5f) + 4;
//            }
//            else {
//                this->unk_1A4 = (s16)(Rand_ZeroOne() * 40.5f) + 4;
//            }
//        }
//        else {
//            this->unk_1A6 = true;
//            ObjMure_SetFollowTargets(this, Rand_ZeroOne() * 0.7f);
//            this->unk_1A4 = (s16)(Rand_ZeroOne() * 10.5f) + 4;
//        }
//    }
//
//    maxChildren = ObjMure_GetMaxChildSpawns(this);
//    for (i = 0; i < maxChildren; i++) {
//        if (this->children[i] != NULL) {
//            if (this->children[i]->child != NULL && this->children[i]->child->update == NULL) {
//                this->children[i]->child = NULL;
//            }
//        }
//    }
//}

static ObjMureActionFunc D_808D87C8[] = {
    NULL, NULL, func_808D82CC, func_808D82CC, func_808D84F4,
};
#define sTypeGroupBehaviorFunc D_808D87C8

void func_808D8678(ObjMure* this, GlobalContext* globalCtx) {
    func_808D7F2C(this, globalCtx);
    if (sZClip[this->type] + 40.0f <= fabsf(this->actor.projectedPos.z)) {
        this->actionFunc = func_808D8014;
        this->actor.flags &= ~0x10;
        func_808D7F0C(this, globalCtx);
    }
    else if (sTypeGroupBehaviorFunc[this->type] != NULL) {
        sTypeGroupBehaviorFunc[this->type](this, globalCtx);
    }
}

void ObjMure_Update(Actor* thisx, GlobalContext* globalCtx) {
    ObjMure* this = THIS;

    if (this->unk_1A4 > 0) {
        this->unk_1A4--;
    }
    this->actionFunc(this, globalCtx);
}
