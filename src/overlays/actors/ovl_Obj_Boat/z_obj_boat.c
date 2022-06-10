/*
 * File: z_obj_boat.c
 * Overlay: ovl_Obj_Boat
 * Description: Pirate Boat
 */

#include "z_obj_boat.h"
#include "objects/object_kaizoku_obj/object_kaizoku_obj.h"

#define FLAGS (ACTOR_FLAG_10)

#define THIS ((ObjBoat*)thisx)

void ObjBoat_Init(Actor* thisx, GlobalContext* globalCtx);
void ObjBoat_Destroy(Actor* thisx, GlobalContext* globalCtx);
void ObjBoat_Update(Actor* thisx, GlobalContext* globalCtx);
void ObjBoat_Draw(Actor* thisx, GlobalContext* globalCtx);

s16 func_80B9AF50(ObjBoat* this, Vec3f* arg0);
void func_80B9B428(ObjBoat* this, GlobalContext* globalCtx);
void func_80B9B124(ObjBoat* this);

const ActorInit Obj_Boat_InitVars = {
    ACTOR_OBJ_BOAT,
    ACTORCAT_BG,
    FLAGS,
    OBJECT_KAIZOKU_OBJ,
    sizeof(ObjBoat),
    (ActorFunc)ObjBoat_Init,
    (ActorFunc)ObjBoat_Destroy,
    (ActorFunc)ObjBoat_Update,
    (ActorFunc)ObjBoat_Draw,
};

static InitChainEntry sInitChain[] = {
    ICHAIN_VEC3F_DIV1000(scale, 100, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneForward, 4000, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneScale, 1000, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneDownward, 1000, ICHAIN_STOP),
};

s16 func_80B9AF50(ObjBoat* this, Vec3f* arg0) {
    s16 yaw;
    Vec3s* temp = &this->unk_164[(s32)this->posX];

    Math_Vec3s_ToVec3f(arg0, &temp[this->rotY]);
    yaw = Math_Vec3f_Yaw(&this->dyna.actor.world.pos, arg0);

    return ((this->rotY > 0) ? yaw : (yaw + 0x8000));
}

void ObjBoat_Init(Actor* thisx, GlobalContext* globalCtx) {
    s32 pad[2];
    Path* path;
    ObjBoat* this = THIS;
    Vec3f sp24;

    Actor_ProcessInitChain(&this->dyna.actor, sInitChain);
    DynaPolyActor_Init(&this->dyna, 3);
    DynaPolyActor_LoadMesh(globalCtx, &this->dyna, &object_kaizoku_obj_Colheader_009A88);
    if (OBJBOAT_GET_PARAMS(thisx) < 0) {
        this->dyna.actor.update = (void (*)(Actor*, GlobalContext*))func_80B9B428;
    } else {
        path = &globalCtx->setupPathList[OBJBOAT_GET_PATH(thisx) & 0x1F];
        this->unk_163 = path->count - 1;
        this->unk_164 = Lib_SegmentedToVirtual(path->points);
        this->rotY = 1;
        this->dyna.actor.world.pos.x = this->unk_164[this->posX].x;
        this->dyna.actor.world.pos.z = this->unk_164[this->posX].z;
        this->dyna.actor.shape.rot.y = func_80B9AF50(this, &sp24);
        this->dyna.actor.world.rot.y = this->dyna.actor.shape.rot.y;
        this->rotY = -this->rotY;
    }
}

void ObjBoat_Destroy(Actor* thisx, GlobalContext* globalCtx) {
    ObjBoat* this = THIS;

    DynaPoly_DeleteBgActor(globalCtx, &globalCtx->colCtx.dyna, this->dyna.bgId);
}

void func_80B9B124(ObjBoat* this) {
    this->unk_160 += 1000;
    this->dyna.actor.world.pos.y = Math_SinS(this->unk_160) + this->dyna.actor.home.pos.y;
    this->dyna.actor.shape.rot.x = (Math_SinS(this->unk_160) * 100.0f);
    this->dyna.actor.shape.rot.z = (Math_SinS((s16)(this->unk_160 * 2)) * 50.0f);
}

void ObjBoat_Update(Actor* thisx, GlobalContext* globalCtx) {
    s32 pad;
    ObjBoat* this = THIS;
    Player* player;
    s32 currentAction;
    f32 sp3C;
    s16 sp3A;
    Vec3f sp2C;

    player = GET_PLAYER(globalCtx);
    currentAction = DynaPolyActor_IsInRidingMovingState(&this->dyna);
    sp3C = 0.0f;
    sp3A = this->dyna.actor.shape.rot.y;
    if ((currentAction) || ((DynaPolyActor_IsInRidingFallingState(&this->dyna)))) {
        if ((this->unk_15F == 0) &&
            (OBJBOAT_GET_4000(thisx) || ((currentAction != 0) && (this->posX == this->unk_15E)))) {
            this->rotY = -this->rotY;
            if (this->rotY > 0) {
                this->unk_15E = this->unk_163;
            } else {
                this->unk_15E = 0;
            }
            this->unk_15F = 0x3C;
        }
    } else if (this->dyna.actor.speedXZ == 0.0f) {
        if (this->unk_15F != 0) {
            this->unk_15F--;
        }
    }
    if (this->posX != this->unk_15E) {
        sp3A = func_80B9AF50(this, &sp2C);
        if (Math_Vec3f_DistXZ(&this->dyna.actor.world.pos, &sp2C) < 200.0f) {
            this->posX += this->rotY;
            if (this->posX == this->unk_15E) {
                if (OBJBOAT_GET_4000(thisx)) {
                    this->posX = 0;
                } else if (this->dyna.actor.speedXZ == 0.0f) {
                    this->posX = 0;
                    this->rotY = -1;
                }
            }
        } else {
            sp3C = this->rotY * (OBJBOAT_GET_4000(thisx) ? 5.0f : 3.0f);
        }
    }
    if (player->csMode != 0x1A) {
        Math_ScaledStepToS(&this->dyna.actor.shape.rot.y, sp3A, (s16)(s32)(fabsf(this->dyna.actor.speedXZ) * 40.0f));
        this->dyna.actor.world.rot.y = this->dyna.actor.shape.rot.y;
        Math_StepToF(&this->dyna.actor.speedXZ, sp3C, 0.05f);
        Actor_MoveWithGravity(&this->dyna.actor);
        if (this->dyna.actor.speedXZ != 0.0f) {
            func_800B9010(&this->dyna.actor, NA_SE_EV_PIRATE_SHIP - SFX_FLAG);
        }
    }
    func_80B9B124(this);
}

void func_80B9B428(ObjBoat* this, GlobalContext* globalCtx2) {
    GlobalContext* globalCtx = globalCtx2;
    s32 pad;

    if (Cutscene_CheckActorAction(globalCtx, 511)) {
        CsCmdActorAction* actionIndex = globalCtx->csCtx.actorActions[Cutscene_GetActorActionIndex(globalCtx, 511)];
        if (this->unk_15F != actionIndex->action) {
            this->dyna.actor.shape.rot.x = actionIndex->urot.x;
            if (actionIndex->action != 1) {
                Path* path = &globalCtx->setupPathList[OBJBOAT_GET_PATH(&this->dyna.actor) & 0x1F];
                if (actionIndex->action == 3) {
                    path = &globalCtx->setupPathList[path->unk1];
                }
                this->unk_163 = path->count;
                this->unk_164 = Lib_SegmentedToVirtual(path->points);
                Math_Vec3s_ToVec3f(&this->dyna.actor.world.pos, this->unk_164);
                this->dyna.actor.speedXZ = actionIndex->urot.z * 0.005493164f;
                this->unk_164++;
                this->posX = 1;
            }
            this->unk_15F = actionIndex->action;
        } else {
            if (actionIndex->action != 1) {
                Vec3f vec;
                f32 step;
                Math_Vec3s_ToVec3f(&vec, this->unk_164);
                step = Math_Vec3f_StepTo(&this->dyna.actor.world.pos, &vec, this->dyna.actor.speedXZ);
                if ((this->posX < this->unk_163) && (step < this->dyna.actor.speedXZ)) {
                    this->unk_164++;
                    this->posX++;
                }
            }
            if (actionIndex->action != 3) {
                func_80B9B124(this);
                if (actionIndex->action == 2) {
                    func_800B9010(&this->dyna.actor, NA_SE_EV_PIRATE_SHIP - SFX_FLAG);
                }
            } else {
                this->dyna.actor.shape.rot.y += 0x7D0;
                this->dyna.actor.shape.rot.x += 0x3E8;
                this->dyna.actor.shape.rot.z += 0x1F4;
            }
        }
    }
}

void ObjBoat_Draw(Actor* thisx, GlobalContext* globalCtx) {
    ObjBoat* this = THIS;

    Gfx_DrawDListOpa(globalCtx, (Gfx*)&object_kaizoku_obj_DL_007630);
}
