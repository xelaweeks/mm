/*
 * File: z_bg_last_bwall.c
 * Overlay: ovl_Bg_Last_Bwall
 * Description: Link Moon Dungeon - Bombable, Climbable Wall
 */

#include "z_bg_last_bwall.h"

#define FLAGS 0x00000000

#define THIS ((BgLastBwall*)thisx)

void BgLastBwall_Init(Actor* thisx, PlayState* play);
void BgLastBwall_Destroy(Actor* thisx, PlayState* play);
void BgLastBwall_Update(Actor* thisx, PlayState* play);
void BgLastBwall_Draw(Actor* thisx, PlayState* play);

void BgLastBwall_InitCollider(ColliderTrisInit* init, Vec3f* pos, Vec3s* rot, ColliderTris* collider,
                              InitColliderStruct* arg4);
void func_80C187E4(BgLastBwall* this);
void func_80C184EC(BgLastBwall* this, PlayState* play);
void func_80C187F8(BgLastBwall* this, PlayState* play);
void func_80C1886C(BgLastBwall* this, PlayState* play);
void func_80C18884(BgLastBwall* this, PlayState* play);
void func_80C188C4(BgLastBwall* this, PlayState* play);
void BgLastBwall_DoNothing(BgLastBwall* this, PlayState* play);

const ActorInit Bg_Last_Bwall_InitVars = {
    ACTOR_BG_LAST_BWALL,
    ACTORCAT_BG,
    FLAGS,
    OBJECT_LAST_OBJ,
    sizeof(BgLastBwall),
    (ActorFunc)BgLastBwall_Init,
    (ActorFunc)BgLastBwall_Destroy,
    (ActorFunc)BgLastBwall_Update,
    (ActorFunc)BgLastBwall_Draw,
};

static ColliderTrisElementInit D_80C189C0[] = {
    {
        {
            ELEMTYPE_UNK0,
            { 0x00000000, 0x00, 0x00 },
            { 0x00000008, 0x00, 0x00 },
            TOUCH_NONE | TOUCH_SFX_NORMAL,
            BUMP_ON,
            OCELEM_NONE,
        },
        { { { -70.0f, 0.0f, 3.0f }, { 70.0f, 0.0f, 3.0f }, { -70.0f, 200.0f, 3.0f } } },
    },
    {
        {
            ELEMTYPE_UNK0,
            { 0x00000000, 0x00, 0x00 },
            { 0x00000008, 0x00, 0x00 },
            TOUCH_NONE | TOUCH_SFX_NORMAL,
            BUMP_ON,
            OCELEM_NONE,
        },
        { { { 70.0f, 0.0f, 3.0f }, { 70.0f, 200.0f, 3.0f }, { -70.0f, 200.0f, 3.0f } } },
    },
};

static ColliderTrisInit D_80C18A38 = {
    {
        COLTYPE_NONE,
        AT_NONE,
        AC_ON | AC_TYPE_PLAYER,
        OC1_NONE,
        OC2_NONE,
        COLSHAPE_TRIS,
    },
    ARRAY_COUNT(D_80C189C0),
    D_80C189C0, // sTrisElementsInit,
};

static ModelInfo D_80C18A48[] = { { object_last_obj_DL_0001A8, 0x0, &object_last_obj_Colheader_000288 },
                                  { object_last_obj_DL_001318, 0x0, &object_last_obj_Colheader_001450 } };

static Vec3s D_80C18A60[] = {
    { 0x118, 0x118, -0x28 },
    { 0x118, 0x118, 0x78 },
    { 0x118, 0x190, 0x78 },
    { 0x118, 0x190, -0x28 },
};

static s16 D_80C18A78[] = { 0, 1, 2, 0, 2, 3 };

static InitColliderStruct D_80C18A84 = { D_80C18A60, D_80C18A78, 2 };

static Vec3s D_80C18A90[] = {
    { -0x50, 0x190, -0x50 },
    { -0x50, 0x190, 0x50 },
    { 0x50, 0x190, 0x50 },
    { 0x50, 0x190, -0x50 },
};

static s16 D_80C18AA8[] = { 0, 3, 2, 0, 2, 1 };

static InitColliderStruct D_80C18AB4 = { D_80C18A90, D_80C18AA8, 2 };

static InitColliderStruct* D_80C18AC0[] = { &D_80C18A84, &D_80C18AB4 };

static InitChainEntry D_80C18AC8[] = {
    ICHAIN_VEC3F_DIV1000(scale, 100, ICHAIN_STOP),
};

void BgLastBwall_InitCollider(ColliderTrisInit* init, Vec3f* pos, Vec3s* rot, ColliderTris* collider,
                              InitColliderStruct* arg4) {
    s32 i;
    s32 j;
    Vec3f sp6C[3];
    Vec3f sp60;
    Vec3f sp54;

    Matrix_RotateYS(rot->y, MTXMODE_NEW);
    Matrix_RotateXS(rot->x, MTXMODE_APPLY);
    Matrix_RotateZS(rot->z, MTXMODE_APPLY);
    for (i = 0; i < init->count; i++) {
        for (j = 0; j < 3; j++) {
            Math_Vec3s_ToVec3f(&sp60, &arg4->unk0[arg4->unk4[j]]);
            Matrix_MultVec3f(&sp60, &sp54);
            Math_Vec3f_Sum(&sp54, pos, &sp6C[j]);
        }

        arg4->unk4 += 3;
        Collider_SetTrisVertices(collider, i, &sp6C[0], &sp6C[1], &sp6C[2]);
    }
}

void BgLastBwall_Init(Actor* thisx, PlayState* play) {
    u32 pad;
    BgLastBwall* this = THIS;

    Actor_ProcessInitChain(&this->dyna.actor, D_80C18AC8);
    this->unk238 = BGLASTBWALL_GET_F000(&this->dyna.actor);
    DynaPolyActor_Init(&this->dyna, 1);
    DynaPolyActor_LoadMesh(play, &this->dyna, D_80C18A48[this->unk238].colHeader);
    Collider_InitTris(play, &this->colliderTris);
    if (Flags_GetSwitch(play, BGLASTBWALL_GET_SWITCHFLAGS(&this->dyna.actor))) {
        Actor_MarkForDeath(&this->dyna.actor);
    } else if (!Collider_SetTris(play, &this->colliderTris, &this->dyna.actor, &D_80C18A38,
                                 &this->colliderTrisElement)) {
        Actor_MarkForDeath(&this->dyna.actor);
    } else {
        BgLastBwall_InitCollider(&D_80C18A38, &this->dyna.actor.world.pos, &this->dyna.actor.shape.rot,
                                 &this->colliderTris, D_80C18AC0[this->unk238]);
        SubS_FillCutscenesList(&this->dyna.actor, &this->nextCutscene, 1);
        func_80C187E4(this);
    }
}

void BgLastBwall_Destroy(Actor* thisx, PlayState* play) {
    BgLastBwall* this = THIS;
    DynaPoly_DeleteBgActor(play, &play->colCtx.dyna, this->dyna.bgId);
}

void func_80C184EC(BgLastBwall* this, PlayState* play) {
    f32 randVar;
    Vec3f spD0;
    Vec3f position;
    s32 var_v0;
    Vec3f spB4;
    s32 i;

    Matrix_RotateYS(this->dyna.actor.shape.rot.y, MTXMODE_NEW);
    Matrix_RotateXS(this->dyna.actor.shape.rot.y, MTXMODE_APPLY);
    Matrix_RotateZS(this->dyna.actor.shape.rot.y, MTXMODE_APPLY);
    for (i = 0; i < 30; i++) {
        switch (this->unk238) {
            case 0:
                spD0.x = 280.0f;
                spD0.y = Rand_Centered() * 160.0f + 320.0f;
                spD0.z = Rand_Centered() * 160.0f;
                Matrix_MultVec3f(&spD0, &position);
                Math_Vec3f_Sum(&this->dyna.actor.world.pos, &position, &position);
                break;
            case 1:
                spD0.x = Rand_Centered() * 160.0f;
                spD0.y = 400.0f;
                spD0.z = Rand_Centered() * 160.0f;
                Matrix_MultVec3f(&spD0, &position);
                Math_Vec3f_Sum(&this->dyna.actor.world.pos, &position, &position);
                break;
        }
        func_800BBFB0(play, &position, 50.0f, 2, Rand_ZeroOne() * 120.0f + 20.0f, Rand_ZeroOne() * 240.0f + 20.0f, 0);
        spB4.x = Rand_ZeroOne() * 2.5f;
        spB4.y = Rand_ZeroOne() * 2.5f + 1.0f;
        spB4.z = Rand_ZeroOne() * 2.5f;
        randVar = Rand_ZeroOne();
        if (randVar < 0.2f) {
            var_v0 = 0x60;
        } else if (randVar < 0.6f) {
            var_v0 = 0x40;
        } else {
            var_v0 = 0x20;
        }
        EffectSsKakera_Spawn(play, &position, &spB4, &position, -0x104, var_v0, 0x14, 0, 0, 0xA, 0, 0, 0x32, -1, 0x234,
                             object_last_obj_DL_000098);
    }
}

void func_80C187E4(BgLastBwall* this) {
    this->actionFunc = func_80C187F8;
}

void func_80C187F8(BgLastBwall* this, PlayState* play) {
    if (this->colliderTris.base.acFlags & 2) {
        this->colliderTris.base.acFlags &= 0xFFFD;
        Flags_SetSwitch(play, BGLASTBWALL_GET_SWITCHFLAGS(&this->dyna.actor));
        func_80C1886C(this, play);
    } else {
        CollisionCheck_SetAC(play, &play->colChkCtx, &this->colliderTris.base);
    }
}

void func_80C1886C(BgLastBwall* this, PlayState* play) {
    this->actionFunc = func_80C18884;
}

void func_80C18884(BgLastBwall* this, PlayState* play) {
    if (SubS_StartActorCutscene(&this->dyna.actor, this->nextCutscene, -1, 0)) {
        func_80C188C4(this, play);
    }
}

void func_80C188C4(BgLastBwall* this, PlayState* play) {
    func_800C62BC(play, &play->colCtx.dyna, this->dyna.bgId);
    this->dyna.actor.draw = NULL;
    func_80C184EC(this, play);
    Actor_PlaySfxAtPos(&this->dyna.actor, NA_SE_EV_WALL_BROKEN);
    this->actionFunc = BgLastBwall_DoNothing;
}

void BgLastBwall_DoNothing(BgLastBwall* this, PlayState* play) {
}

void BgLastBwall_Update(Actor* thisx, PlayState* play) {
    BgLastBwall* this = THIS;
    this->actionFunc(this, play);
}

void BgLastBwall_Draw(Actor* thisx, PlayState* play) {
    Gfx_DrawDListOpa(play, D_80C18A48[THIS->unk238].dList);
}
