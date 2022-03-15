/*
 * File: z_obj_yasi.c
 * Overlay: ovl_Obj_Yasi
 * Description: Palm Tree
 */

#include "z_obj_yasi.h"
#include "objects/object_obj_yasi/object_obj_yasi.h"

#define FLAGS 0x00000000

#define THIS ((ObjYasi*)thisx)

void ObjYasi_Init(Actor* thisx, GlobalContext* globalCtx);
void ObjYasi_Destroy(Actor* thisx, GlobalContext* globalCtx);
void ObjYasi_Update(Actor* thisx, GlobalContext* globalCtx);
void ObjYasi_Draw(Actor* thisx, GlobalContext* globalCtx);

// s32 D_80BB4D90[] = {0xC8580064, 0xB0FC0FA0, 0xB1000190, 0x31040320};

const ActorInit Obj_Yasi_InitVars = {
    ACTOR_OBJ_YASI,
    ACTORCAT_PROP,
    FLAGS,
    OBJECT_OBJ_YASI,
    sizeof(ObjYasi),
    (ActorFunc)ObjYasi_Init,
    (ActorFunc)ObjYasi_Destroy,
    (ActorFunc)ObjYasi_Update,
    (ActorFunc)ObjYasi_Draw,
};

static InitChainEntry sInitChain[] = {
    ICHAIN_VEC3F_DIV1000(scale, 100, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneForward, 4000, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneScale, 400, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneDownward, 800, ICHAIN_STOP),
};

void ObjYasi_Init(Actor* thisx, GlobalContext* globalCtx) {
    ObjYasi* this = THIS;
    Actor_ProcessInitChain(&this->dyna.actor, sInitChain);
    DynaPolyActor_Init(&this->dyna, 0);
    DynaPolyActor_LoadMesh(globalCtx, &this->dyna, &object_obj_yasi_Colheader_001428);

    this->dyna.actor.home.rot.y = 0;

    if ((this->dyna.actor.params & 1) != 0) {
        this->dyna.actor.scale.x = 0.2f;
        this->dyna.actor.scale.z = 0.2f;
    }
}

void ObjYasi_Destroy(Actor* thisx, GlobalContext* globalCtx) {
    ObjYasi* this = THIS;
    DynaPoly_DeleteBgActor(globalCtx, &globalCtx->colCtx.dyna, this->dyna.bgId);
}

void ObjYasi_Update(Actor* thisx, GlobalContext* globalCtx) {
    ObjYasi* this = (ObjYasi*)thisx;
    s16 temp;
    Vec3f sp1C;

    if (this->dyna.actor.home.rot.z != 0) {
        if (this->dyna.actor.params < 0) {
            if (Rand_ZeroOne() < 0.5f) {
                sp1C.x = this->dyna.actor.world.pos.x;
                sp1C.y = this->dyna.actor.world.pos.y + 280.0f;
                sp1C.z = this->dyna.actor.world.pos.z;
                Item_DropCollectible(globalCtx, &sp1C, ITEM00_NUTS_1);
            }
        }
        this->dyna.actor.home.rot.y = GET_PLAYER(globalCtx)->actor.shape.rot.y;
        this->dyna.actor.home.rot.x = 400;
        this->dyna.actor.home.rot.z = 0;
    }
    temp = (s16)(this->dyna.actor.shape.rot.x * 0.1f);
    this->dyna.actor.home.rot.x -= temp;
    this->dyna.actor.shape.rot.x = this->dyna.actor.shape.rot.x +
                                   ((s16)(this->dyna.actor.home.rot.x - ((s16)(this->dyna.actor.shape.rot.x * 0.08f))));
}

void ObjYasi_Draw(Actor* thisx, GlobalContext* globalCtx) {
    ObjYasi* this = THIS;
    Matrix_InsertTranslation(this->dyna.actor.world.pos.x, this->dyna.actor.world.pos.y, this->dyna.actor.world.pos.z,
                             0);

    if (this->dyna.actor.shape.rot.x != 0) {
        Matrix_RotateY(this->dyna.actor.home.rot.y, 1);
        Matrix_InsertXRotation_s(this->dyna.actor.shape.rot.x, 1);
        Matrix_RotateY((s16)(this->dyna.actor.shape.rot.y - this->dyna.actor.home.rot.y), 1);
    } else {
        Matrix_RotateY(this->dyna.actor.shape.rot.y, 1);
    }

    Matrix_Scale(0.1f, 0.1f, 0.1f, 1);
    Gfx_DrawDListOpa(globalCtx, object_obj_yasi_DL_000360);
}
