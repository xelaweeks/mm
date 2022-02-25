/*
 * File: z_boss_03.c
 * Overlay: ovl_Boss_03
 * Description: Gyorg
 */

#include "z_boss_03.h"
#include "overlays/actors/ovl_Door_Warp1/z_door_warp1.h"
#include "overlays/actors/ovl_En_Water_Effect/z_en_water_effect.h"

#define FLAGS (ACTOR_FLAG_1 | ACTOR_FLAG_4 | ACTOR_FLAG_10 | ACTOR_FLAG_20)

#define THIS ((Boss03*)thisx)

void Boss03_Init(Actor* thisx, GlobalContext* globalCtx);
void Boss03_Destroy(Actor* thisx, GlobalContext* globalCtx);
void Boss03_Update(Actor* thisx, GlobalContext* globalCtx);
void Boss03_Draw(Actor* thisx, GlobalContext* globalCtx);

void func_809E344C(Boss03* this, GlobalContext* globalCtx);
void func_809E34B8(Boss03* this, GlobalContext* globalCtx);
void func_809E3968(Boss03* this, GlobalContext* globalCtx);
void func_809E3D98(Boss03* this, GlobalContext* globalCtx);
void func_809E421C(Boss03* this, GlobalContext* globalCtx);
void func_809E475C(Boss03* this, GlobalContext* globalCtx);
void func_809E497C(Boss03* this, GlobalContext* globalCtx);
void func_809E4C90(Boss03* this, GlobalContext* globalCtx);
void func_809E4E80(Boss03* this, GlobalContext* globalCtx);
void func_809E5B64(Boss03* this, GlobalContext* globalCtx);
void func_809E6640(Boss03* this, GlobalContext* globalCtx);
void func_809E6BC0(Boss03* this, GlobalContext* globalCtx);

void func_809E6A38(Boss03* this, GlobalContext* globalCtx);




void func_809E8810(Actor* thisx, GlobalContext* globalCtx);
void func_809E8BEC(Actor* thisx, GlobalContext* globalCtx);

void func_809E4E2C(Boss03* this, GlobalContext* globalCtx);

void func_809E81E4(GlobalContext* globalCtx);


void func_809E38EC(Boss03* this, GlobalContext* globalCtx);

void func_809E3D34(Boss03* this, GlobalContext* globalCtx, u8 arg2);
void func_809E4180(Boss03* this, GlobalContext* globalCtx);
void func_809E4910(Boss03* this, GlobalContext* globalCtx);


/* bss */

#if 0
// maybe u8?
glabel D_809E9840
/* 000000 809E9840 */ .space 0x1

glabel D_809E9841
/* 000001 809E9841 */ .space 0x1
#endif

// glabel D_809E9842
// /* 000002 809E9842 */ .space 0x6
extern u8 D_809E9842;

#if 0
glabel D_809E9848
/* 000008 809E9848 */ .space 0x10
#endif

// glabel D_809E9858
// /* 000018 809E9858 */ .space 0x27D8
extern GyorgEffect D_809E9858[GYORG_EFFECT_COUNT];

// glabel D_809EC030
// /* 0027F0 809EC030 */ .space 0x4
extern Boss03* D_809EC030;

// glabel D_809EC034
// /* 0027F4 809EC034 */ .space 0x4
extern s32 D_809EC034; // sRandSeed0

// glabel D_809EC038
// /* 0027F8 809EC038 */ .space 0x4
extern s32 D_809EC038; // sRandSeed1

// glabel D_809EC03C
// /* 0027FC 809EC03C */ .space 0x4
extern s32 D_809EC03C; // sRandSeed2

/* bss */


extern UNK_TYPE D_06007EB0;
extern UNK_TYPE D_06007EC8;
extern AnimationHeader D_06009554;
extern AnimationHeader D_060099D0;
extern AnimationHeader D_06009C14;
extern AnimationHeader D_06009CF8;
extern AnimationHeader D_0600A6C8;


void func_809E2760(Vec3f* arg0, u16 sfxId) {
    func_8019F420(arg0, sfxId);
}

void func_809E2788(GlobalContext* globalCtx, Vec3f* pos) {
    s16 i;
    GyorgEffect* effects = globalCtx->specialEffects;

    for (i = 0; i < GYORG_EFFECT_COUNT; i++) {
        if ((effects->type == 0) || (effects->type == 1)) {
            effects->type = 4;
            effects->pos = *pos;
            effects->unk_34.x = 0.1f;
            effects->unk_34.y = 0.4f;
            effects->velocity = gZeroVec3f;
            effects->accel = gZeroVec3f;
            effects->unk_2C = 0x0096;
            effects->unk_2E = Rand_ZeroFloat(4.0f) + 5.0f;
            return;
        }

        effects++;
    }
}

void func_809E2880(GlobalContext* globalCtx, Vec3f* pos) {
    s16 i;
    GyorgEffect* effects = globalCtx->specialEffects;

    for (i = 0; i < GYORG_EFFECT_COUNT; i++) {
        if ((effects->type == 0) || (effects->type == 1)) {
            effects->type = 2;
            effects->pos = *pos;
            effects->velocity = gZeroVec3f;
            effects->accel = gZeroVec3f;
            effects->accel.y = -2.0f;
            effects->unk_34.x = 0.1f;
            effects->unk_34.y = 0.0f;
            effects->unk_34.z = Rand_ZeroFloat(2 * M_PI);
            effects->unk_02 = Rand_ZeroFloat(100.0f);
            effects->velocity.x = randPlusMinusPoint5Scaled(25.0f);
            effects->velocity.z = randPlusMinusPoint5Scaled(25.0f);
            return;
        }

        effects++;
    }
}

void func_809E299C(GlobalContext* globalCtx, Vec3f* pos, Vec3f* velocity) {
    Vec3f accel = { 0.0f, -1.0f, 0.0f };
    f32 temp_f2;
    GyorgEffect* effects = globalCtx->specialEffects;
    s16 i;

    for (i = 0; i < GYORG_EFFECT_COUNT; i++) {
        if ((effects->type == 0) || (effects->type == 1)) {
            effects->type = 3;
            effects->pos = *pos;
            effects->velocity = *velocity;
            effects->accel = accel;
            temp_f2 = Rand_ZeroFloat(0.02f) + 0.02f;
            effects->unk_34.y = temp_f2;
            effects->unk_34.x = temp_f2;
            effects->unk_34.z = Rand_ZeroFloat(2 * M_PI);
            effects->unk_02 = Rand_ZeroFloat(100.0f);
            return;
        }

        effects++;
    }
}

void func_809E2AB4(GlobalContext* globalCtx, Vec3f* pos) {
    s16 i;
    GyorgEffect* effects = globalCtx->specialEffects;

    for (i = 0; i < GYORG_EFFECT_COUNT; i++) {
        if (effects->type == 0) {
            effects->type = 1;
            effects->pos = *pos;
            effects->velocity = gZeroVec3f;
            effects->accel = gZeroVec3f;
            effects->accel.y = 0.2f;
            effects->unk_34.x = Rand_ZeroFloat(0.3f) + 0.2f;
            effects->unk_02 = 0;
            return;
        }

        effects++;
    }
}

void func_809E2B8C(s32 arg0, ColliderJntSph* collider, Vec3f* arg2) {
    ColliderJntSphElement* temp_v1;

    collider->elements[arg0].dim.worldSphere.center.x = arg2->x;
    collider->elements[arg0].dim.worldSphere.center.y = arg2->y;
    collider->elements[arg0].dim.worldSphere.center.z = arg2->z;

    temp_v1 = &collider->elements[arg0];
    temp_v1->dim.worldSphere.radius = temp_v1->dim.scale * temp_v1->dim.modelSphere.radius;
}

// Boss03_SeedRand(s32 seed0, s32 seed1, s32 seed2)
void func_809E2C1C(s32 seed0, s32 seed1, s32 seed2) {
    D_809EC034 = seed0;
    D_809EC038 = seed1;
    D_809EC03C = seed2;
}

// Boss03_RandZeroOne
f32 func_809E2C3C(void) {
    f32 rand;

    // Wichmann-Hill algorithm
    D_809EC034 = (D_809EC034 * 171) % 30269;
    D_809EC038 = (D_809EC038 * 172) % 30307;
    D_809EC03C = (D_809EC03C * 170) % 30323;

    rand = (D_809EC034 / 30269.0f) + (D_809EC038 / 30307.0f) + (D_809EC03C / 30323.0f);
    while (rand >= 1.0f) {
        rand -= 1.0f;
    }

    return fabsf(rand);
}

Actor* func_809E2D64(GlobalContext* globalCtx) {
    Actor* actor = globalCtx->actorCtx.actorLists[ACTORCAT_BG].first;

    while (actor != NULL) {
        if (actor->id == ACTOR_BG_DBLUE_MOVEBG) {
            return actor;
        }
        actor = actor->next;
    }

    return NULL;
}

const ActorInit Boss_03_InitVars = {
    ACTOR_BOSS_03,
    ACTORCAT_BOSS,
    FLAGS,
    OBJECT_BOSS03,
    sizeof(Boss03),
    (ActorFunc)Boss03_Init,
    (ActorFunc)Boss03_Destroy,
    (ActorFunc)Boss03_Update,
    (ActorFunc)Boss03_Draw,
};

static ColliderJntSphElementInit sJntSphElementsInit1[2] = {
    {
        {
            ELEMTYPE_UNK3,
            { 0xF7CFFFFF, 0x00, 0x08 },
            { 0xF7CFFFFF, 0x00, 0x00 },
            TOUCH_ON | TOUCH_SFX_NORMAL,
            BUMP_ON,
            OCELEM_ON,
        },
        { 0, { { 0, 0, 0 }, 70 }, 100 },
    },
    {
        {
            ELEMTYPE_UNK3,
            { 0xF7CFFFFF, 0x00, 0x08 },
            { 0xF7CFFFFF, 0x00, 0x00 },
            TOUCH_ON | TOUCH_SFX_NORMAL,
            BUMP_ON,
            OCELEM_ON,
        },
        { 1, { { 0, 0, 0 }, 50 }, 100 },
    },
};

static ColliderJntSphInit sJntSphInit1 = {
    {
        COLTYPE_HIT3,
        AT_ON | AT_TYPE_ENEMY,
        AC_ON | AC_TYPE_PLAYER,
        OC1_ON | OC1_TYPE_PLAYER,
        OC2_TYPE_1,
        COLSHAPE_JNTSPH,
    },
    ARRAY_COUNT(sJntSphElementsInit1),
    sJntSphElementsInit1,
};

static ColliderJntSphElementInit sJntSphElementsInit2[5] = {
    {
        {
            ELEMTYPE_UNK3,
            { 0xF7CFFFFF, 0x00, 0x08 },
            { 0xF7CFFFFF, 0x00, 0x00 },
            TOUCH_ON | TOUCH_SFX_NORMAL,
            BUMP_ON,
            OCELEM_ON,
        },
        { 2, { { 0, 0, 0 }, 20 }, 100 },
    },
    {
        {
            ELEMTYPE_UNK3,
            { 0xF7CFFFFF, 0x00, 0x08 },
            { 0xF7CFFFFF, 0x00, 0x00 },
            TOUCH_ON | TOUCH_SFX_NORMAL,
            BUMP_ON,
            OCELEM_ON,
        },
        { 5, { { 0, 0, 0 }, 20 }, 100 },
    },
    {
        {
            ELEMTYPE_UNK3,
            { 0xF7CFFFFF, 0x00, 0x08 },
            { 0xF7CFFFFF, 0x00, 0x00 },
            TOUCH_ON | TOUCH_SFX_NORMAL,
            BUMP_ON,
            OCELEM_ON,
        },
        { 6, { { 0, 0, 0 }, 70 }, 100 },
    },
    {
        {
            ELEMTYPE_UNK3,
            { 0xF7CFFFFF, 0x00, 0x08 },
            { 0xF7CFFFFF, 0x00, 0x00 },
            TOUCH_ON | TOUCH_SFX_NORMAL,
            BUMP_ON,
            OCELEM_ON,
        },
        { 7, { { 0, 0, 0 }, 70 }, 100 },
    },
    {
        {
            ELEMTYPE_UNK3,
            { 0xF7CFFFFF, 0x00, 0x08 },
            { 0xF7CFFFFF, 0x00, 0x00 },
            TOUCH_ON | TOUCH_SFX_NORMAL,
            BUMP_ON,
            OCELEM_ON,
        },
        { 8, { { 0, 0, 0 }, 30 }, 100 },
    },
};

static ColliderJntSphInit sJntSphInit2 = {
    {
        COLTYPE_METAL,
        AT_ON | AT_TYPE_ENEMY,
        AC_ON | AC_TYPE_PLAYER,
        OC1_ON | OC1_TYPE_PLAYER,
        OC2_TYPE_1,
        COLSHAPE_JNTSPH,
    },
    ARRAY_COUNT(sJntSphElementsInit2),
    sJntSphElementsInit2,
};

Vec3f D_809E8FE8 = { 1216.0f, 140.0f, -1161.0f };

UNK_TYPE D_809E8FF4[0x42] = {
    0x43828000, 0x430C0000, 0xC47A0000, 0xC3FC0000, 0x42F00000, 0xC49F8000, 0xC490A000, 0x42A00000, 0xC4510000,
    0xC47F0000, 0x42F00000, 0x43BE8000, 0xC2080000, 0x42F00000, 0x4497A000, 0x4448C000, 0x42A00000, 0x449C4000,
    0x448EE000, 0x42F00000, 0x44174000, 0x44998000, 0x430C0000, 0xC3740000, 0x44980000, 0x430C0000, 0xC4912000,
    0x43828000, 0x430C0000, 0xC47A0000, 0xC3FC0000, 0x42F00000, 0xC45E8000, 0xC490A000, 0x42A00000, 0xC4510000,
    0xC47F0000, 0x42F00000, 0x43BE8000, 0xC2080000, 0x42F00000, 0x4497A000, 0x4448C000, 0x42A00000, 0x449C4000,
    0x448EE000, 0x42F00000, 0x44174000, 0x44998000, 0x430C0000, 0xC3740000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000,
};

Color_RGBA8 D_809E90FC = { 60, 50, 20, 255 };
Color_RGBA8 D_809E9100 = { 40, 30, 30, 255 };

void func_809E2DA0(Boss03* this, GlobalContext* globalCtx) {
    if (this->unk_2AC.y < 80.0f) {
        u8 i;
        Vec3f spA0;
        Vec3f sp94;
        Vec3f sp88;

        for (i = 0; i < 5; i++) {
            sp94.x = randPlusMinusPoint5Scaled(10.0f);
            sp94.y = Rand_ZeroFloat(2.0f) + 2.0f;
            sp94.z = randPlusMinusPoint5Scaled(10.0f);
            sp88.y = -0.075f;
            sp88.z = 0.0f;
            sp88.x = 0.0f;
            spA0.y = Rand_ZeroFloat(20.0f) + 5.0f;
            spA0.z = randPlusMinusPoint5Scaled(150.0f) + this->unk_2AC.z;
            spA0.x = randPlusMinusPoint5Scaled(150.0f) + this->unk_2AC.x;
            func_800B0EB0(globalCtx, &spA0, &sp94, &sp88, &D_809E90FC, &D_809E9100, Rand_ZeroFloat(200.0f) + 400.0f, 10, Rand_ZeroFloat(10.0f) + 25.0f);
        }
    }
}

void Boss03_Init(Actor* thisx, GlobalContext* globalCtx2) {
    Boss03* this = THIS;
    s32 i;
    GlobalContext* globalCtx = globalCtx2;
    Vec3f sp70;

    if (gSaveContext.weekEventReg[55] & 0x80) {
        Actor_SpawnAsChild(&globalCtx->actorCtx, &this->actor, globalCtx, ACTOR_DOOR_WARP1, 0.0f, 440.0f, 200.0f, 0, 0,
                           0, ENDOORWARP1_FF_1);
        Actor_Spawn(&globalCtx->actorCtx, globalCtx, ACTOR_ITEM_B_HEART, 0.0f, 440.0f, 0.0f, 0, 0, 0, 0);
        Actor_MarkForDeath(&this->actor);
        return;
    }

    // TODO: make a macro / enum
    if (this->actor.params == 0x23) {
        this->actor.update = func_809E8810;
        this->actor.draw = func_809E8BEC;

        this->unk_240 = Rand_ZeroFloat(1000.0f);

        this->actor.scale.x = Rand_ZeroFloat(0.0075f) + 0.027f;
        this->actor.scale.y = 0.02f;
        this->actor.scale.z = 0.015f;

        // This bit is weird, why is it setting the first 6 elements of the joint table?
        for (i = 0; i < 6; i++) {
            this->jointTable[i].x = Math_SinS((this->unk_240 * 0x100) + i * 15000) * 3000.0f;
            this->jointTable[i].y = Math_SinS((this->unk_240 * 0x180) + i * 20000) * 2000.0f;
            this->jointTable[i].z = Math_SinS((this->unk_240 * 0x10) + i * 19000) * 4000.0f;
        }

        this->actor.flags &= ~1;
        return;
    }

    this->actor.world.pos = D_809E8FE8;

    func_809E2C1C(1, 29093, 9786);

    for (i = 0; i < 5; i++) {
        Matrix_InsertYRotation_f((func_809E2C3C() * 3.1415927f * 0.2f) + (1.2566371f * i), 0);
        Matrix_GetStateTranslationAndScaledZ((func_809E2C3C() * 800.0f) + 400.0f, &sp70);
        Actor_Spawn(&globalCtx->actorCtx, globalCtx, ACTOR_BOSS_03, sp70.x, sp70.y, sp70.z, 0,
                    func_809E2C3C() * 0x10000, 0, 0x23);
    }

    D_809EC030 = this;

    globalCtx->specialEffects = D_809E9858;

    for (i = 0; i < ARRAY_COUNT(D_809E9858); i++) {
        D_809E9858[i].type = 0;
    }

    this->actor.targetMode = 5;
    this->actor.colChkInfo.mass = MASS_HEAVY;
    this->actor.colChkInfo.health = 10;
    Collider_InitAndSetJntSph(globalCtx, &this->collider1, &this->actor, &sJntSphInit1, this->unk_34C);
    Collider_InitAndSetJntSph(globalCtx, &this->collider2, &this->actor, &sJntSphInit2, this->unk_3EC);
    SkelAnime_InitFlex(globalCtx, &this->skelAnime, &gGyorgSkel, &D_0600A6C8, this->jointTable, this->morphTable,
                       GYORG_LIMB_MAX);
    Actor_SetScale(&this->actor, 0.2f);

    if ((KREG(64) != 0) || (gSaveContext.eventInf[5] & 0x40)) {
        this->actionFunc = func_809E344C;
        D_809E9842 = 0;
        Audio_QueueSeqCmd(0x100100FF);
    } else {
        func_809E4E2C(this, globalCtx);
        D_809E9842 = 1;
    }

    this->unk_252 = -1;
    this->unk_258 = 430.0f;
}

void Boss03_Destroy(Actor* thisx, GlobalContext* globalCtx) {
    Boss03* this = THIS;
}

void func_809E344C(Boss03* this, GlobalContext* globalCtx) {
    Player* player = GET_PLAYER(globalCtx);

    if (player->actor.world.pos.y < 540.0f) {
        this->actionFunc = func_809E34B8;
        Animation_MorphToLoop(&this->skelAnime, &D_06009CF8, -15.0f);
        this->unk_274 = 0;
        this->actor.flags |= 1;
    }
}

#ifdef NON_EQUIVALENT
// float regalloc
void func_809E34B8(Boss03* this, GlobalContext* globalCtx) {
    Player* player = GET_PLAYER(globalCtx);
    // s32 pad[6];
    s32 pad0;
    s32 pad1;
    s32 pad2;
    s32 pad3;
    s32 pad4;
    s32 pad5;
    f32 temp_f12;
    f32 temp_f20;
    f32 temp_f22;
    f32 temp;
    s16 i;

    func_809E2760(&this->actor.projectedPos, 0x32AB);
    this->unk_276 = 0x0800;
    this->skelAnime.playSpeed = 1.0f;
    this->unk_27C = 1.0f;
    this->unk_278 = 10.0f;

    SkelAnime_Update(&this->skelAnime);
    Matrix_InsertTranslation(this->actor.world.pos.x, this->actor.world.pos.y, this->actor.world.pos.z, 0);
    Matrix_RotateY(this->actor.world.rot.y, 1);

    temp_f20 = this->unk_268.x - this->actor.world.pos.x;
    temp_f22 = this->unk_268.z - this->actor.world.pos.z;
    temp = this->unk_268.y - this->actor.world.pos.y;
    temp_f12 = sqrtf(SQ(temp_f20) + SQ(temp_f22));

    Math_ApproachS(&this->actor.world.rot.x, Math_FAtan2F(temp_f12, -temp), 0x000A, this->unk_274);
    Math_ApproachS(&this->unk_2A0, Math_SmoothStepToS(&this->actor.world.rot.y, Math_FAtan2F(temp_f22, temp_f20), 0x000A, this->unk_274, 0) * -0.5f, 5, 0x0100);
    Math_ApproachS(&this->unk_274, this->unk_276, 1, 0x0100);
    Math_ApproachF(&this->actor.speedXZ, this->unk_278, 1.0f, this->unk_27C);
    Math_ApproachF(&this->unk_260, __sinf(this->skelAnime.curFrame * 0.62831855f) * 10.0f * 0.01f, 0.5f, 1.0f);

    if ((this->unk_250 == 0) && (this->actor.bgCheckFlags & 8)) {
        Matrix_GetStateTranslationAndScaledZ(-500.0f, &this->unk_268);
        this->unk_268.y = Rand_ZeroFloat(100.0f) + 150.0f;
        this->unk_250 = 0x003C;
        this->unk_24C = Rand_ZeroFloat(60.0f) + 60.0f;
        this->unk_274 = 0x0100;
    }

    if (this->unk_250 == 0) {
        if ((temp_f12 < 100.0f) || (this->unk_24C == 0)) {

            for (i = 0; i < 200; i++) {
                if ((!temp_f20) && (!temp_f20)) {}
                this->unk_268.x = randPlusMinusPoint5Scaled(2500.0f);
                this->unk_268.y = Rand_ZeroFloat(100.0f) + 150.0f;
                this->unk_268.z = randPlusMinusPoint5Scaled(2500.0f);
                if (sqrtf(SQ(this->unk_268.x - this->actor.world.pos.x) + SQ(this->unk_268.z - this->actor.world.pos.z)) > 300.0f) {
                    break;
                }
            }

            this->unk_274 = 0x0100;
            this->unk_24C = Rand_ZeroFloat(60.0f) + 60.0f;
        }
    }

    Actor_MoveWithoutGravityReverse(&this->actor);
    Math_ApproachS(&this->actor.shape.rot.x, this->actor.world.rot.x, 2, this->unk_274 * 2);
    Math_ApproachS(&this->actor.shape.rot.y, this->actor.world.rot.y, 2, this->unk_274 * 2);

    if (this->unk_24E == 0) {
        if ((this->unk_258 < player->actor.world.pos.y) && (player->actor.bgCheckFlags & 1)) {
            func_809E4674(this, globalCtx);
        } else if ((player->transformation != 1) && (player->transformation != 3)) {
            if (gGameInfo->data[0x526] == 0) {
                func_809E38EC(this, globalCtx);
            } else if (this->unk_252 <= 0) {
                func_809E38EC(this, globalCtx);
            }
        }
    }
}
#else
void func_809E34B8(Boss03* this, GlobalContext* globalCtx);
#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_03/func_809E34B8.s")
#endif

void func_809E38EC(Boss03* this, GlobalContext* globalCtx) {
    this->actionFunc = func_809E3968;
    Animation_MorphToLoop(&this->skelAnime, &D_06009CF8, -10.0f);
    this->unk_24C = 0x0064;
    this->unk_276 = 0x1000;
    this->skelAnime.playSpeed = 1.5f;
    this->unk_278 = 10.0f;
    this->unk_27C = 1.0f;
}

#ifdef NON_EQUIVALENT
void func_809E3968(Boss03* this, GlobalContext* globalCtx) {
    Player* player = GET_PLAYER(globalCtx);
    f32 temp_f2;
    f32 temp3;
    f32 temp_f18;
    f32 temp;

    this->unk_2BD = 1;
    SkelAnime_Update(&this->skelAnime);

    temp_f2 = player->actor.world.pos.x - this->actor.world.pos.x;
    temp3 = ((player->actor.world.pos.y - this->actor.world.pos.y) + 50.0f);
    temp_f18 = player->actor.world.pos.z - this->actor.world.pos.z;

    Math_ApproachS(&this->actor.world.rot.x, Math_FAtan2F(sqrtf(SQ(temp_f2) + SQ(temp_f18)), -temp3), 0x000A, this->unk_274);
    temp = Math_SmoothStepToS(&this->actor.world.rot.y, Math_FAtan2F(temp_f18, temp_f2), 0x000A, this->unk_274, 0) * -0.5f;
    Math_ApproachS(&this->unk_2A0, temp, 5, 0x0100);

    Math_ApproachS(&this->unk_274, this->unk_276, 1, 0x0100);
    Math_ApproachF(&this->actor.speedXZ, this->unk_278, 1.0f, this->unk_27C);
    Math_ApproachF(&this->unk_260, __sinf(this->skelAnime.curFrame * 0.62831855f) * 10.0f * 0.01f, 0.5f, 1.0f);
    Actor_MoveWithoutGravityReverse(&this->actor);
    Math_ApproachS(&this->actor.shape.rot.x, this->actor.world.rot.x, 2, this->unk_274 * 2);
    Math_ApproachS(&this->actor.shape.rot.y, this->actor.world.rot.y, 2, this->unk_274 * 2);

    if (((player->actor.bgCheckFlags & 1) && (player->actor.shape.feetPos[0].y >= 438.0f)) || (this->unk_24C == 0)) {
        if (&this->actor == player->actor.parent) {
            player->unk_AE8 = 0x65;
            player->actor.parent = NULL;
            player->csMode = 0;
        }
        func_809E344C(this, globalCtx);
        this->unk_24E = 0x0064;
    } else {
        Vec3f sp50;
        f32 temp_f12;
        f32 phi_f2;
        f32 sp44;
        u8 sp43;

        if ((this->unk_258 - 80.0f) < player->actor.world.pos.y) {
            sp43 = 1;
            phi_f2 = 100.0f;
            sp44 = 50.0f;
        } else {
            sp43 = 0;
            phi_f2 = 200.0f;
            sp44 = 100.0f;
        }

        Matrix_InsertTranslation(this->actor.world.pos.x, this->actor.world.pos.y, this->actor.world.pos.z, 0);
        Matrix_RotateY(this->actor.world.rot.y, 1);
        Matrix_GetStateTranslationAndScaledZ(sp44, &sp50);

        temp_f12 = sqrtf(SQ(sp50.x - player->actor.world.pos.x) + SQ(sp50.z - player->actor.world.pos.z));
        if (temp_f12 < (2.0f * phi_f2)) {
            Math_ApproachS(&this->unk_2A8, 0x3200, 2, 0x1800);
            this->unk_278 = 25.0f;
            this->unk_27C = 5.0f;
            this->skelAnime.playSpeed = 2.5f;
        }

        if (temp_f12 < phi_f2) {
            func_809E3D34(this, globalCtx, sp43);
            if (sp43 != 0) {
                Actor_Spawn(&globalCtx->actorCtx, globalCtx, ACTOR_EN_WATER_EFFECT, player->actor.world.pos.x, this->unk_258, player->actor.world.pos.z, 0, 0, 0x78, ENWATEREFFECT_777);
                func_809E2760(&this->actor.projectedPos, 0x3942U);
            }
            func_809E2760(&this->actor.projectedPos, 0x3943U);
        }
    }

    func_809E2DA0(this, globalCtx);
}
#else
#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_03/func_809E3968.s")
#endif

void func_809E3D34(Boss03* this, GlobalContext* globalCtx, u8 arg2) {
    this->actionFunc = func_809E3D98;
    Animation_MorphToLoop(&this->skelAnime, &D_06009CF8, -15.0f);
    this->unk_24C = 0x64;
    this->unk_2C4 = 0.0f;
    this->unk_2B8 = 0.0f;
    this->unk_242 = arg2;
}

void func_809E3D98(Boss03* this, GlobalContext* globalCtx) {
    Player* player = GET_PLAYER(globalCtx);
    f32 temp_f2;
    f32 temp;
    f32 temp_f18;
    Actor* new_var;

    this->skelAnime.playSpeed = 2.0f;
    this->unk_27C = 2.0f;
    this->unk_276 = 0x1000;
    this->unk_2BD = 1;
    this->unk_278 = 15.0f;
    this->actor.flags &= -2;
    SkelAnime_Update(&this->skelAnime);

    temp_f2 = player->actor.world.pos.x - this->actor.world.pos.x;
    temp = player->actor.world.pos.y - this->actor.world.pos.y;
    temp_f18 = player->actor.world.pos.z - this->actor.world.pos.z;

    Math_ApproachS(&this->actor.world.rot.x, Math_FAtan2F(sqrtf(SQ(temp_f2) + SQ(temp_f18)), -temp), 0xA, this->unk_274);
    Math_ApproachS(&this->unk_2A0, (Math_SmoothStepToS(&this->actor.world.rot.y, Math_FAtan2F(temp_f18, temp_f2), 0xA, this->unk_274, 0) * -0.5f), 5, 0x100);
    Math_ApproachS(&this->unk_274, this->unk_276, 1, 0x100);
    Math_ApproachF(&this->actor.speedXZ, this->unk_278, 1.0f, this->unk_27C);
    Math_ApproachF(&this->unk_260, __sinf(this->skelAnime.curFrame * 0.62831855f) * 10.0f * 0.01f, 0.5f, 1.0f);
    Actor_MoveWithoutGravityReverse(&this->actor);
    Math_ApproachS(&this->actor.shape.rot.x, this->actor.world.rot.x, 2, this->unk_274 * 2);
    Math_ApproachS(&this->actor.shape.rot.y, this->actor.world.rot.y, 2, this->unk_274 * 2);

    if (((player->actor.bgCheckFlags & 1) && (player->actor.shape.feetPos[0].y >= 438.0f)) || (this->unk_24C == 0)) {
        if (&this->actor == player->actor.parent) {
            player->unk_AE8 = 0x65;
            player->actor.parent = NULL;
            player->csMode = 0;
            func_80165690();
        }
        func_809E344C(this, globalCtx);
    } else {
        f32 phi_f0;

        Math_ApproachF(&player->actor.world.pos.x, this->unk_2AC.x, 1.0f, this->unk_2B8);
        Math_ApproachF(&player->actor.world.pos.y, this->unk_2AC.y, 1.0f, this->unk_2B8);
        Math_ApproachF(&player->actor.world.pos.z, this->unk_2AC.z, 1.0f, this->unk_2B8);

        if (this->unk_242 != 0) {
            phi_f0 = 10.0f;
        } else {
            phi_f0 = 2.0f;
        }

        Math_ApproachF(&this->unk_2B8, 100.0f, 1.0f, phi_f0);

        if (this->unk_2B8 > 30.0f) {
            // fake match
            if (((new_var = &this->actor) != player->actor.parent) && (globalCtx->grabPlayer(globalCtx, player) != 0)) {
                player->actor.parent = &this->actor;
                Audio_PlaySfxGeneral(0x6805, &player->actor.projectedPos, 4, &D_801DB4B0, &D_801DB4B0, &D_801DB4B8);
                func_809E4180(this, globalCtx);
            }
        } else {
            Math_ApproachS(&this->unk_2A8, 0x3200, 2, 3072.0f * phi_f0);
        }

        Math_ApproachS(&player->actor.world.rot.x, 0x4000, 1, 0x400);
        Math_ApproachS(&player->actor.shape.rot.x, 0x4000, 1, 0x400);
        Math_ApproachS(&player->actor.world.rot.y, this->unk_2A2.y, 1, 0x400);
        Math_ApproachS(&player->actor.shape.rot.y, this->unk_2A2.y, 1, 0x400);
    }

    func_809E2DA0(this, globalCtx);
}

void func_809E4180(Boss03* this, GlobalContext* globalCtx) {
    s16 temp;
    Vec3f sp20;

    this->actionFunc = func_809E421C;
    temp = Math_FAtan2F(this->actor.world.pos.z, this->actor.world.pos.x);
    Matrix_RotateY(temp, 0);
    sp20.x = 0.0f;
    sp20.y = 200.0f;
    sp20.z = 700.0f;
    Matrix_MultiplyVector3fByState(&sp20, &this->unk_268);
    this->unk_276 = 0x0800;
    this->unk_242 = 0;
    this->unk_24C = 0x0064;
    this->skelAnime.playSpeed = 1.0f;
}

#ifdef NON_EQUIVALENT
// float regalloc
void func_809E421C(Boss03* this, GlobalContext* globalCtx) {
    Player* player = GET_PLAYER(globalCtx);
    Input* input = CONTROLLER1(globalCtx);
    // SkelAnime* sp2C;                                /* compiler-managed */
    f32 temp_f2;
    f32 temp;
    f32 temp_f18;
    f32 temp_f0;
    f32 temp_f12;

    this->unk_2BD = 1;
    this->unk_25C = 0xF;

    if (this->unk_24C == 0x5A) {
        func_8016566C(0x00000096U);
    }

    SkelAnime_Update(&this->skelAnime);
    Matrix_InsertTranslation(this->actor.world.pos.x, this->actor.world.pos.y, this->actor.world.pos.z, 0);
    Matrix_RotateY(this->actor.world.rot.y, 1);
    temp_f2 = this->unk_268.x - this->actor.world.pos.x;
    temp = this->unk_268.y - this->actor.world.pos.y;
    temp_f18 = this->unk_268.z - this->actor.world.pos.z;

    temp_f12 = sqrtf(SQ(temp_f2) + SQ(temp_f18));
    Math_ApproachS(&this->actor.world.rot.x, Math_FAtan2F(temp_f12, -temp), 0xA, this->unk_274);
    Math_ApproachS(&this->unk_2A0, Math_SmoothStepToS(&this->actor.world.rot.y, Math_FAtan2F(temp_f18, temp_f2), 0xA, this->unk_274, 0) * -0.5f, 5, 0x100);
    Math_ApproachS(&this->unk_274, this->unk_276, 1, 0x100);
    Math_ApproachF(&this->unk_260, __sinf(this->skelAnime.curFrame * 0.62831855f) * 10.0f * 0.01f, 0.5f, 1.0f);

    switch (this->unk_242) {
        case 0x0:
            Math_ApproachF(&this->actor.speedXZ, 10.0f, 1.0f, 1.0f);
            if (temp_f12 < 100.0f) {
                this->unk_242 = 1;
                Animation_MorphToLoop(&this->skelAnime, &D_06009C14, -15.0f);
            }
            break;

        case 0x1:
            Math_ApproachF(&this->actor.speedXZ, 0.0f, 1.0f, 0.5f);
            Math_ApproachF(&this->actor.world.pos.y, 200.0f, 0.05f, 5.0f);
            break;
    }

    Actor_MoveWithoutGravityReverse(&this->actor);
    Math_ApproachS(&this->actor.shape.rot.x, this->actor.world.rot.x, 2, this->unk_274 * 2);
    Math_ApproachS(&this->actor.shape.rot.y, this->actor.world.rot.y, 2, this->unk_274 * 2);

    if (CHECK_BTN_ALL(input->press.button, BTN_A) || CHECK_BTN_ALL(input->press.button, BTN_B)) {
        if (this->unk_24C != 0) {
            this->unk_24C--;
        }
        if (this->unk_24C != 0) {
            this->unk_24C--;
        }
    }

    if (this->unk_24C == 0) {
        if (&this->actor == player->actor.parent) {
            player->unk_AE8 = 0x65;
            player->actor.parent = NULL;
            player->csMode = 0;
            func_80165690();
            func_800B8D50(globalCtx, NULL, 10.0f, this->actor.shape.rot.y, 0.0f, 0x20);
        }

        func_809E344C(this, globalCtx);
        this->unk_24E = Rand_ZeroFloat(100.0f) + 200.0f;
        return;
    }

    player->actor.world.pos = this->unk_2AC;
    temp_f0 = Math_SinS(this->unk_240 * 0x2000);

    Math_ApproachS(&this->unk_2A8, temp_f0 * 2000.0f, 2, 0x3000);
    player->actor.shape.rot.x = 0x4000;
    player->actor.world.rot.x = player->actor.shape.rot.x;

    player->actor.world.rot.y = player->actor.shape.rot.y = this->unk_2A2.y;
    if (this->unk_24C < 5) {
        Math_ApproachS(&this->unk_2A8, 0x3200, 2, 0x1800);
        Math_ApproachF(&this->unk_2C4, 100.0f, 1.0f, 100.0f);
    } else {
        Math_ApproachF(&this->unk_2C4, -300.0f, 1.0f, 5.0f);
        if ((this->unk_240 % 8) == 0) {
            func_809E2760(&this->actor.projectedPos, 0x3960U);
        }
    }
}
#else
#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_03/func_809E421C.s")
#endif

#ifdef NON_EQUIVALENT
// Maybe equivalent?
void func_809E4674(Boss03* this, GlobalContext* globalCtx) {
    f32 temp_f0;

    this->actionFunc = func_809E475C;
    Animation_MorphToLoop(&this->skelAnime, &D_06009C14, -15.0f);
    this->unk_24C = Rand_ZeroFloat(30.0f) + 80.0f;
    this->unk_24E = 0x0032;
    this->unk_274 = 0;

    temp_f0 = sqrtf(SQXZ(this->actor.world.pos));
    if (temp_f0 > 600.0f) {
        if (Rand_ZeroOne() < 0.5f) {
            this->unk_242 = 1;
            return;
        }
        // if (((!(&this->actor)) && (!(&this->actor))) && (!(&this->actor))) {}
    }
    this->unk_242 = 0;
}
#else
#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_03/func_809E4674.s")
#endif

void func_809E475C(Boss03* this, GlobalContext* globalCtx) {
    f32 temp_f0;
    Player* player = GET_PLAYER(globalCtx);

    if (this->unk_24E != 0) {
        func_809E2760(&this->actor.projectedPos, 0x32AB);
    }

    Math_ApproachS(&this->unk_2A0, Math_SmoothStepToS(&this->actor.world.rot.y, this->actor.yawTowardsPlayer, 0x000A, this->unk_274, 0) * -0.7f, 5, 0x0200);
    Math_ApproachS(&this->unk_274, 0x0800, 1, 0x0100);
    Math_ApproachS(&this->actor.shape.rot.y, this->actor.world.rot.y, 2, 0x1000);
    Math_ApproachS(&this->actor.world.rot.x, 0, 0x000A, 0x0200);
    Math_ApproachS(&this->actor.shape.rot.x, 0, 0x000A, 0x0200);

    temp_f0 = this->unk_258 - 70.0f;
    if (temp_f0 < this->actor.world.pos.y) {
        Math_ApproachF(&this->actor.world.pos.y, temp_f0, 0.05f, 5.0f);
    }

    SkelAnime_Update(&this->skelAnime);

    if ((this->unk_258 < player->actor.world.pos.y) && (player->actor.bgCheckFlags & 1)) {
        if (this->unk_24C == 0) {
            func_809E4910(this, globalCtx);
        }
    } else if (player->actor.world.pos.y <= this->unk_258) {
        func_809E344C(this, globalCtx);
        this->unk_24E = 0x14;
    }

    Math_ApproachF(&this->actor.speedXZ, -3.0f, 1.0f, 0.5f);
    Actor_MoveWithoutGravityReverse(&this->actor);
}

void func_809E4910(Boss03* this, GlobalContext* globalCtx) {
    Player* player = GET_PLAYER(globalCtx);

    this->actionFunc = func_809E497C;
    Animation_MorphToLoop(&this->skelAnime, &D_06009CF8, -15.0f);
    this->unk_268 = player->actor.world.pos;
}

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_03/func_809E497C.s")

void func_809E4C34(Boss03* this, GlobalContext* globalCtx) {
    this->actionFunc = func_809E4C90;
    this->actor.gravity = -2.0f;
    this->actor.velocity.y = 30.0f;
    this->actor.speedXZ = 25.0f;
    func_809E2760(&this->actor.projectedPos, NA_SE_EN_KONB_JUMP_OLD);
}

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_03/func_809E4C90.s")

void func_809E4E2C(Boss03* this, GlobalContext* globalCtx) {
    this->actionFunc = func_809E4E80;
    Animation_MorphToLoop(&this->skelAnime, &D_06009CF8, -10.0f);
    this->skelAnime.playSpeed = 2.0f;
}

Vec3f D_809E9104[] = {
    { 770.0f, 200.0f, 720.0f },
    { 831.0f, 200.0f, -570.0f },
    { 0.0f, 450.0f, 0.0f },
};

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_03/func_809E4E80.s")

void func_809E5ADC(Boss03* this, GlobalContext* globalCtx) {
    this->actionFunc = func_809E5B64;
    Animation_MorphToLoop(&this->skelAnime, &D_06009554, -10.0f);
    this->unk_52C = Animation_GetLastFrame(&D_06009554);
    Audio_QueueSeqCmd(0x100100FF);
    this->unk_24C = 0;
    this->unk_242 = 0;
    this->unk_534 = 0;
    this->actor.flags &= ~1;
}

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_03/func_809E5B64.s")

void func_809E65F4(Boss03* this, GlobalContext* globalCtx) {
    this->actionFunc = func_809E6640;
    Animation_MorphToLoop(&this->skelAnime, &D_06009C14, -15.0f);
    this->unk_534 = 0;
    this->unk_530 = 0;
}

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_03/func_809E6640.s")

//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_03/func_809E69A4.s")
void func_809E69A4(Boss03* this, GlobalContext* globalCtx) {
    Player* player = GET_PLAYER(globalCtx);

    if (this->actionFunc != func_809E6A38) {
        Animation_MorphToLoop(&this->skelAnime, &D_060099D0, -15.0f);
        this->unk_250 = 0x00C8;
        this->actionFunc = func_809E6A38;
    }

    if (&this->actor == player->actor.parent) {
        player->unk_AE8 = 0x0065;
        player->actor.parent = NULL;
        player->csMode = 0;
        func_80165690();
    }

    this->unk_240 = 0;
}

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_03/func_809E6A38.s")

void func_809E6B70(Boss03* this, GlobalContext* globalCtx) {
    Animation_MorphToLoop(&this->skelAnime, &D_06009554, -10.0f);
    this->actionFunc = func_809E6BC0;
    this->unk_24C = 0x001E;
}

void func_809E6BC0(Boss03* this, GlobalContext* globalCtx) {
    this->unk_25C = 0x000F;
    SkelAnime_Update(&this->skelAnime);
    Math_ApproachS(&this->unk_2A8, ((Math_SinS(this->unk_240 * 0x2000) * 3000.0f) + 0x3000), 2, 0x3000);
    Math_ApproachF(&this->actor.world.pos.y, 200.0f, 0.05f, 10.0f);
    if (this->unk_24C == 0) {
        if ((s8)this->actor.colChkInfo.health < 6) {
            if (this->unk_253 == 0) {
                this->unk_253++;
                func_809E65F4(this, globalCtx);
                return;
            }
        }
        func_809E344C(this, globalCtx);
        this->unk_24E = 0x0064;
    }
}

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_03/func_809E6CB4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_03/Boss03_Update.s")

void func_809E7920(GlobalContext* globalCtx, s16 objectId) {
    s32 temp_v0 = Object_GetIndex(&globalCtx->objectCtx, objectId);

    OPEN_DISPS(globalCtx->state.gfxCtx);

    gSegments[6] = PHYSICAL_TO_VIRTUAL(globalCtx->objectCtx.status[temp_v0].segment);

    gSPSegment(POLY_OPA_DISP++, 0x06, globalCtx->objectCtx.status[temp_v0].segment);
    gSPSegment(POLY_XLU_DISP++, 0x06, globalCtx->objectCtx.status[temp_v0].segment);

    CLOSE_DISPS(globalCtx->state.gfxCtx);
}

// overrideLimbDraw
s32 func_809E79C4(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3s* rot, Actor* thisx) {
    Boss03* this = THIS;

    if ((limbIndex == GYORG_LIMB_UPPER_TRUNK) || (limbIndex == GYORG_LIMB_LOWER_TRUNK) ||
        (limbIndex == GYORG_LIMB_TAIL)) {
        rot->y += this->unk_2A0;
    }
    if (limbIndex == GYORG_LIMB_UPPER_RIGHT_FIN) {
        rot->y += this->unk_29E;
    }
    if (limbIndex == GYORG_LIMB_LOWER_RIGHT_FIN) {
        rot->y += (s16)(2 * this->unk_29E);
    }
    if (limbIndex == GYORG_LIMB_UPPER_LEFT_FIN) {
        rot->y -= this->unk_29C;
    }
    if (limbIndex == GYORG_LIMB_LOWER_LEFT_FIN) {
        rot->y -= (s16)(2 * this->unk_29C);
    }
    if (limbIndex == GYORG_LIMB_JAW) {
        rot->z += this->unk_2A8;
    }

    return false;
}

s8 D_809E9128[] = {
    -1, -1, 0, -1, 4, 5, 6, -1, 2, -1, -1, 3, -1, -1, 1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
};

Vec3f D_809E9148 = { 600.0f, -100.0f, 0.0f };
Vec3f D_809E9154[] = {
    { 450.0f, 0.0f, 0.0f }, { 140.0f, -60.0f, 0.0f }, { 350.0f, 0.0f, 0.0f }, { 350.0f, 0.0f, 0.0f },
    { 100.0f, 0.0f, 0.0f }, { 150.0f, 0.0f, 0.0f },   { 500.0f, 0.0f, 0.0f },
};
Vec3f D_809E91A8 = { 100000.0f, 100000.0f, 100000.0f };
Vec3f D_809E91B4 = { 300.0f, -100.0f, -200.0f };

// postLimbDraw
void func_809E7AA8(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3s* rot, Actor* thisx) {
    Boss03* this = THIS;
    s8* temp_t8;
    s8 temp_a3;
    Vec3f sp68;
    Player* player = GET_PLAYER(globalCtx);
    MtxF sp24;

    if (limbIndex == 2) {
        limbIndex = limbIndex;
        Matrix_MultiplyVector3fByState(&D_809E9148, &this->actor.focus.pos);
    }

    temp_t8 = &D_809E9128[limbIndex];
    temp_a3 = *temp_t8;
    if (temp_a3 >= 0) {
        Matrix_MultiplyVector3fByState(&D_809E9154[temp_a3], &sp68);
        if (temp_a3 < 2) {
            if ((this->actionFunc == func_809E6A38) && (this->unk_258 < player->actor.world.pos.y)) {
                func_809E2B8C(temp_a3, &this->collider1, &D_809E91A8);
            } else {
                func_809E2B8C(temp_a3, &this->collider1, &sp68);
            }
        } else {
            func_809E2B8C(temp_a3 - 2, &this->collider2, &sp68);
        }
    }

    if (limbIndex == 0xE) {
        D_809E91B4.x = this->unk_2C4 + 300.0f;
        Matrix_MultiplyVector3fByState(&D_809E91B4, &this->unk_2AC);
        Matrix_CopyCurrentState(&sp24);
        func_8018219C(&sp24, &this->unk_2A2, 0);
    }
}

void Boss03_Draw(Actor* thisx, GlobalContext* globalCtx) {
    Boss03* this = THIS;

    OPEN_DISPS(globalCtx->state.gfxCtx);

    func_8012C28C(globalCtx->state.gfxCtx);

    if (this->unk_2D5 == 0) {
        if ((this->unk_25E & 1) != 0) {
            POLY_OPA_DISP = Gfx_SetFog(POLY_OPA_DISP, 255, 0, 0, 255, 900, 1099);
        }
        Matrix_InsertYRotation_f(this->unk_260, MTXMODE_APPLY);
        Matrix_InsertTranslation(0.0f, -600.0f, 0.0f, MTXMODE_APPLY);
        SkelAnime_DrawFlexOpa(globalCtx, this->skelAnime.skeleton, this->skelAnime.jointTable,
                              this->skelAnime.dListCount, func_809E79C4, func_809E7AA8, &this->actor);
        POLY_OPA_DISP = func_801660B8(globalCtx, POLY_OPA_DISP);
    }

    this->unk_2BC = 0;
    func_809E81E4(globalCtx);

    CLOSE_DISPS(globalCtx->state.gfxCtx);
}

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_03/func_809E7D00.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_03/func_809E81E4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_03/func_809E8810.s")

Gfx* D_809E91C0[] = {
    gGyorgSeaweedTopDL,    gGyorgSeaweedPiece5DL, gGyorgSeaweedPiece4DL,
    gGyorgSeaweedPiece3DL, gGyorgSeaweedPiece2DL, gGyorgSeaweedPiece1DL,
};

void func_809E8BEC(Actor* thisx, GlobalContext* globalCtx) {
    Boss03* this = THIS;
    s16 i;
    // Why 10 when this uses the first 6 elements?
    Mtx* mtx = GRAPH_ALLOC(globalCtx->state.gfxCtx, sizeof(Mtx) * 10);

    OPEN_DISPS(globalCtx->state.gfxCtx);

    func_8012C28C(globalCtx->state.gfxCtx);

    gSPSegment(POLY_OPA_DISP++, 0x0D, mtx);

    Matrix_InsertTranslation(this->actor.world.pos.x, this->actor.world.pos.y, this->actor.world.pos.z, 0);
    Matrix_Scale(this->actor.scale.x, this->actor.scale.y, this->actor.scale.z, 1);
    Matrix_RotateY(this->actor.shape.rot.y, 1);
    Matrix_InsertZRotation_s(0x4000, 1);
    // The indices looks a bit random...
    Matrix_RotateY(this->jointTable[5].x * -5.0f * 0.1f, 1);
    Matrix_InsertXRotation_s(this->jointTable[3].y * -5.0f * 0.1f, 1);
    Matrix_InsertZRotation_s(this->jointTable[2].z * 6.0f * 0.1f, 1);

    for (i = 0; i < 6; i++) {
        Matrix_RotateY(this->jointTable[i].x + this->morphTable[i].x, 1);
        Matrix_InsertXRotation_s(this->jointTable[i].y + this->morphTable[i].y, 1);
        Matrix_InsertZRotation_s(this->jointTable[i].z + this->morphTable[i].z, 1);

        Matrix_ToMtx(mtx);

        gSPMatrix(POLY_OPA_DISP++, mtx, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);

        gSPDisplayList(POLY_OPA_DISP++, D_809E91C0[i]);

        Matrix_GetStateTranslation(&this->unk_2DC[i]);
        Matrix_InsertTranslation(4000.0f, 0.0f, 0.0f, 1);

        mtx++;
    }

    CLOSE_DISPS(globalCtx->state.gfxCtx);
}
