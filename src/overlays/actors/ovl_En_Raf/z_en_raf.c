/*
 * File: z_en_raf.c
 * Overlay: ovl_En_Raf
 * Description: Carnivorous Lilypad
 */

#include "z_en_raf.h"

#define FLAGS (ACTOR_FLAG_8000000)

#define THIS ((EnRaf*)thisx)

void EnRaf_Init(Actor* thisx, GlobalContext* globalCtx);
void EnRaf_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnRaf_Update(Actor* thisx, GlobalContext* globalCtx);
void EnRaf_Draw(Actor* thisx, GlobalContext* globalCtx);

void func_80A171D8(EnRaf* this, GlobalContext* globalCtx);
void func_80A17464(EnRaf* this, GlobalContext* globalCtx);
void func_80A175E4(EnRaf* this, GlobalContext* globalCtx);
void func_80A178A0(EnRaf* this, GlobalContext* globalCtx);
void func_80A17C6C(EnRaf* this, GlobalContext* globalCtx);
void func_80A17D54(EnRaf* this, GlobalContext* globalCtx);
void func_80A17E1C(EnRaf* this, GlobalContext* globalCtx);
void func_80A180B4(EnRaf* this, GlobalContext* globalCtx);
void func_80A1712C(EnRaf* this);
void func_80A18080(EnRaf* this);
void func_80A17414(EnRaf* this);
void func_80A17530(EnRaf* this);
void func_80A18DA0(EnRaf* this, GlobalContext* globalCtx);
void func_80A17848(EnRaf* this, GlobalContext* globalCtx);
void func_80A179C8(EnRaf* this, GlobalContext* globalCtx);
void func_80A18A90(EnRaf* this, Vec3f* arg1, Vec3f* arg2, Vec3f* arg3, f32 arg4, s16 arg5);
void func_80A18B8C(EnRaf* this, GlobalContext* globalCtx);
void func_80A17DDC(EnRaf* this);

const ActorInit En_Raf_InitVars = {
    ACTOR_EN_RAF,
    ACTORCAT_PROP,
    FLAGS,
    OBJECT_RAF,
    sizeof(EnRaf),
    (ActorFunc)EnRaf_Init,
    (ActorFunc)EnRaf_Destroy,
    (ActorFunc)EnRaf_Update,
    (ActorFunc)EnRaf_Draw,
};

// static ColliderCylinderInit sCylinderInit = {
static ColliderCylinderInit D_80A18EE0 = {
    {
        COLTYPE_NONE,
        AT_ON | AT_TYPE_ENEMY,
        AC_NONE,
        OC1_ON | OC1_TYPE_ALL,
        OC2_TYPE_1,
        COLSHAPE_CYLINDER,
    },
    {
        ELEMTYPE_UNK0,
        { 0xF7CFFFFF, 0x04, 0x10 },
        { 0xF7CFFFFF, 0x00, 0x00 },
        TOUCH_ON | TOUCH_SFX_NORMAL,
        BUMP_NONE,
        OCELEM_ON,
    },
    { 50, 10, -10, { 0, 0, 0 } },
};

static u8 D_80A18F0C[] = {
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1,
    1, 0, 1, 1, 0, 1, 1, 1, 1, 0, 1, 1, 0, 1, 0, 1, 1, 1, 1, 0, 1, 0, 1, 1, 1, 1, 1, 0, 0, 1, 0, 0,
};

static u8 D_80A18F4C[] = {
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
};

static u8 D_80A18F8C[] = {
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 0, 1, 0, 0, 1, 1, 1, 0, 1, 1, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 0, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 1, 1, 1,
    1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 0, 0, 1, 1, 1, 1, 0, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 0, 0, 1, 0, 1, 1, 1, 1, 1, 0, 0, 0,
    1, 1, 1, 1, 0, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0,
    0, 0, 0, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 0, 1,
    1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 0, 1, 1, 1, 0, 1, 1,
    1, 1, 1, 1, 1, 0, 0, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 0, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1,
    1, 1, 0, 0, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 0,
    0, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 1, 0, 0, 1, 1, 0, 0, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 0, 1, 1, 0,
    0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 1, 0, 1, 1, 1, 0, 0, 1, 0, 1, 0, 1, 0,
    1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 0, 1, 1, 1, 0, 1, 0,
    0, 1, 1, 0, 0, 0, 1, 0, 1, 1, 1, 0, 0, 0, 1, 0, 0, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 0, 1, 1,
};

static u8 D_80A1918C[] = {
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
};

// static DamageTable sDamageTable = {
static DamageTable D_80A1939C = {
    /* Deku Nut       */ DMG_ENTRY(0, 0xF),
    /* Deku Stick     */ DMG_ENTRY(0, 0xF),
    /* Horse trample  */ DMG_ENTRY(0, 0x0),
    /* Explosives     */ DMG_ENTRY(1, 0xE),
    /* Zora boomerang */ DMG_ENTRY(0, 0xF),
    /* Normal arrow   */ DMG_ENTRY(0, 0xF),
    /* UNK_DMG_0x06   */ DMG_ENTRY(0, 0x0),
    /* Hookshot       */ DMG_ENTRY(0, 0xF),
    /* Goron punch    */ DMG_ENTRY(0, 0xF),
    /* Sword          */ DMG_ENTRY(0, 0xF),
    /* Goron pound    */ DMG_ENTRY(0, 0xF),
    /* Fire arrow     */ DMG_ENTRY(0, 0xF),
    /* Ice arrow      */ DMG_ENTRY(0, 0xF),
    /* Light arrow    */ DMG_ENTRY(0, 0xF),
    /* Goron spikes   */ DMG_ENTRY(0, 0xF),
    /* Deku spin      */ DMG_ENTRY(0, 0xF),
    /* Deku bubble    */ DMG_ENTRY(0, 0xF),
    /* Deku launch    */ DMG_ENTRY(0, 0xF),
    /* UNK_DMG_0x12   */ DMG_ENTRY(0, 0xF),
    /* Zora barrier   */ DMG_ENTRY(0, 0xF),
    /* Normal shield  */ DMG_ENTRY(0, 0x0),
    /* Light ray      */ DMG_ENTRY(0, 0x0),
    /* Thrown object  */ DMG_ENTRY(0, 0xF),
    /* Zora punch     */ DMG_ENTRY(0, 0xF),
    /* Spin attack    */ DMG_ENTRY(0, 0xF),
    /* Sword beam     */ DMG_ENTRY(0, 0x0),
    /* Normal Roll    */ DMG_ENTRY(0, 0xF),
    /* UNK_DMG_0x1B   */ DMG_ENTRY(0, 0x0),
    /* UNK_DMG_0x1C   */ DMG_ENTRY(0, 0x0),
    /* Unblockable    */ DMG_ENTRY(0, 0x0),
    /* UNK_DMG_0x1E   */ DMG_ENTRY(0, 0x0),
    /* Powder Keg     */ DMG_ENTRY(0, 0xF),
};

static Vec3f D_80A193BC = { 1.0f, 1.0f, 1.0f };

static AnimationHeader* D_80A193C8[] = {
    &object_raf_Anim_000A64, &object_raf_Anim_000C7C, &object_raf_Anim_000B30,
    &object_raf_Anim_000A64, &object_raf_Anim_0003FC, &object_raf_Anim_0007A8,
};

static u8 D_80A193E0[] = {
    ANIMMODE_ONCE, ANIMMODE_ONCE, ANIMMODE_LOOP, ANIMMODE_ONCE, ANIMMODE_LOOP, ANIMMODE_ONCE,
};

static Vec3f D_80A193E8 = { 1.0f, 1.0f, 1.0f };

static Vec3f D_80A193F4 = { 0.0f, 0.0f, 0.0f };

static Vec3f D_80A19400 = { 0.0f, 0.0f, 0.0f };

static Vec3f D_80A1940C = { 1.0f, 1.0f, 1.0f };

static s16 D_80A19418[] = { 0, 4, 6 };

static Vec3f D_80A19420[] = {
    { 1.0f, 1.0f, 1.0f },
    { 1.0f, 2.0f, 1.0f },
    { 0.0f, 1.5f, 0.7f },
};

static Vec3f D_80A19444[] = {
    { 1.0f, 1.0f, 1.0f },
    { 3.0f, 2.0f, 1.5f },
    { 1.5f, 1.2f, 0.8f },
};

static s16 D_80A19468[] = { 0, 7, 9, 13, 19 };

static Vec3f D_80A19474[] = {
    { 1.0f, 1.5f, 0.7f }, { 1.0f, 2.0f, 1.5f }, { 1.0f, 2.0f, 0.5f }, { 1.0f, 2.0f, 0.5f }, { 1.0f, 1.0f, 1.0f },
};

static Vec3f D_80A194B0[] = {
    { 1.5f, 1.5f, 1.7f }, { 1.5f, 1.5f, 1.3f }, { 3.0f, 1.0f, 0.5f }, { 1.0f, 1.0f, 0.5f }, { 1.0f, 1.0f, 1.0f },
};

void func_80A16D40(u16* texture, u8* arg1, s32 arg2) {
    if ((arg2 < 0x40) && (arg1[arg2] != 0)) {
        texture[arg2] = 0;
    }
}

void func_80A16D6C(u16* texture, u8* arg1, s32 arg2) {
    if (arg1[arg2] != 0) {
        texture[arg2] = 0;
    }
}

void EnRaf_Init(Actor* thisx, GlobalContext* globalCtx) {
    EnRaf* this = THIS;
    Vec3f sp60 = D_80A193BC;
    s32 i;
    s32 j;
    CollisionHeader* colHeader = NULL;

    DynaPolyActor_Init(&this->dyna, 0);
    CollisionHeader_GetVirtual(&object_raf_Colheader_000108, &colHeader);
    this->dyna.bgId = DynaPoly_SetBgActor(globalCtx, &globalCtx->colCtx.dyna, &this->dyna.actor, colHeader);
    Collider_InitAndSetCylinder(globalCtx, &this->collider, &this->dyna.actor, &D_80A18EE0);
    this->dyna.actor.targetMode = 3;
    this->dyna.actor.colChkInfo.mass = MASS_IMMOVABLE;
    SkelAnime_InitFlex(globalCtx, &this->skelAnime, &object_raf_Skel_003428, &object_raf_Anim_000A64, this->jointTable,
                       this->morphTable, OBJECT_RAF_LIMB_MAX);
    for (i = 0; i < 12; i++) {
        Math_Vec3f_Copy(&this->unk_2C4[i], &sp60);
        Math_Vec3f_Copy(&this->unk_234[i], &sp60);
    }

    this->dyna.actor.colChkInfo.damageTable = &D_80A1939C;
    this->dyna.actor.colChkInfo.health = BREG(1) + 2;
    this->unk_3BE = EN_RAF_GET_F(&this->dyna.actor);
    this->unk_3BA = EN_RAF_GET_1F(&this->dyna.actor);
    this->unk_3C0 = EN_RAF_GET_7F(&this->dyna.actor);
    if (this->unk_3C0 == 0x7F) {
        this->unk_3C0 = -1;
    }

    if (this->unk_3BA == 0x1F) {
        this->unk_3BA = -1;
    } else {
        this->unk_3BA = 0x1E;
    }

    if (((this->unk_3C0 >= 0) || (this->unk_3BE == 1) || (gSaveContext.save.weekEventReg[12] & 1)) &&
        ((Flags_GetSwitch(globalCtx, this->unk_3C0)) || (this->unk_3BE == 1))) {
        for (j = 2; j < 11; j++) {
            Math_Vec3f_Copy(&this->unk_234[j], &gZeroVec3f);
            Math_Vec3f_Copy(&this->unk_2C4[j], &gZeroVec3f);
        }

        func_80A18080(this);
    } else {
        this->unk_3B0 = Rand_ZeroFloat(1.0f) * 20000.0f;
        Actor_SetScale(&this->dyna.actor, 0.01f);
        func_80A1712C(this);
    }
}

void EnRaf_Destroy(Actor* thisx, GlobalContext* globalCtx) {
    EnRaf* this = THIS;

    DynaPoly_DeleteBgActor(globalCtx, &globalCtx->colCtx.dyna, this->dyna.bgId);
    Collider_DestroyCylinder(globalCtx, &this->collider);
}

void func_80A17060(EnRaf* this, s32 index) {
    f32 startFrame = 0.0f;
    f32 playSpeed = 1.0f;

    this->unk_3A0 = Animation_GetLastFrame(D_80A193C8[index]);
    if (index == 0) {
        startFrame = this->unk_3A0;
    } else if (index == 1) {
        playSpeed = 2.0f;
    }

    Animation_Change(&this->skelAnime, D_80A193C8[index], playSpeed, startFrame, this->unk_3A0, D_80A193E0[index],
                     -4.0f);
}

void func_80A1712C(EnRaf* this) {
    Vec3f sp3C = D_80A193E8;
    s32 i;

    func_80A17060(this, 0);
    for (i = 2; i < 11; i++) {
        Math_Vec3f_Copy(&this->unk_2C4[i], &sp3C);
    }

    this->unk_3C2 = 3;
    this->unk_3C6 = 0;
    this->actionFunc = func_80A171D8;
}

void func_80A171D8(EnRaf* this, GlobalContext* globalCtx) {
    Player* player = GET_PLAYER(globalCtx);
    Actor* explosive;
    f32 xDiff;
    f32 yDiff;
    f32 zDiff;

    if (this->unk_3B4 == 0) {
        if ((player->transformation != PLAYER_FORM_DEKU) &&
            (this->dyna.actor.xzDistToPlayer < (BREG(48) + 80.0f) && (player->invincibilityTimer == 0) &&
             DynaPolyActor_IsInRidingMovingState(&this->dyna) && !(player->stateFlags1 & 0x8000000) &&
             globalCtx->grabPlayer(globalCtx, player))) {
            player->actor.parent = &this->dyna.actor;
            this->unk_39C = 0;

            if (player->transformation == PLAYER_FORM_GORON) {
                this->unk_39C = 2;
            } else {
                player->unk_AE8 = 50;
            }

            this->unk_3BC = player->actor.world.rot.y;
            func_80A17414(this);
            return;
        }

        if ((globalCtx->gameplayFrames % 2) == 0) {
            return;
        }

        explosive = globalCtx->actorCtx.actorLists[ACTORCAT_EXPLOSIVES].first;
        while (explosive != NULL) {
            if ((EnRaf*)explosive == this) {
                explosive = explosive->next;
                continue;
            }

            xDiff = explosive->world.pos.x - this->dyna.actor.world.pos.x;
            yDiff = explosive->world.pos.y - this->dyna.actor.world.pos.y;
            zDiff = explosive->world.pos.z - this->dyna.actor.world.pos.z;
            if ((fabsf(xDiff) < 80.0f) && (fabsf(yDiff) < 30.0f) && (fabsf(zDiff) < 80.0f) &&
                (explosive->update != NULL) && (explosive->velocity.y != 0.0f)) {
                Actor_MarkForDeath(explosive);
                this->unk_39C = 1;
                this->collider.dim.radius = 30;
                this->collider.dim.height = 90;
                this->collider.dim.yShift = -10;
                func_80A17414(this);
                return;
            }

            explosive = explosive->next;
        }
    }
}

void func_80A17414(EnRaf* this) {
    func_80A17060(this, 1);
    this->unk_3C2 = 1;
    Actor_PlaySfxAtPos(&this->dyna.actor, NA_SE_EN_SUISEN_DRINK);
    this->unk_3C6 = 1;
    this->actionFunc = func_80A17464;
}

void func_80A17464(EnRaf* this, GlobalContext* globalCtx) {
    Player* player = GET_PLAYER(globalCtx);
    f32 curFrame = this->skelAnime.curFrame;

    if ((this->unk_39C != 1) && (player->stateFlags2 & 0x80) && (&this->dyna.actor == player->actor.parent)) {
        Math_ApproachF(&player->actor.world.pos.x, this->dyna.actor.world.pos.x, 0.3f, 10.0f);
        Math_ApproachF(&player->actor.world.pos.y, this->dyna.actor.world.pos.y, 0.3f, 10.0f);
        Math_ApproachF(&player->actor.world.pos.z, this->dyna.actor.world.pos.z, 0.3f, 10.0f);
    }

    if (this->unk_3A0 <= curFrame) {
        func_80A17530(this);
    }
}

void func_80A17530(EnRaf* this) {
    s32 i;

    func_80A17060(this, 2);
    this->unk_3C4 = 0;
    for (i = 0; i < 12; i++) {
        this->unk_354[i].x = Rand_S16Offset(8, 8) << 8;
        this->unk_354[i].y = Rand_S16Offset(8, 8) << 8;
        this->unk_354[i].z = Rand_S16Offset(8, 8) << 8;
    }

    this->unk_3C2 = 2;
    this->unk_3C6 = 2;
    this->actionFunc = func_80A175E4;
}

void func_80A175E4(EnRaf* this, GlobalContext* globalCtx) {
    f32 temp;
    f32 curFrame;
    Player* player = GET_PLAYER(globalCtx);

    curFrame = this->skelAnime.curFrame;
    temp = (BREG(51) / 100.0f) + 0.2f;
    Math_ApproachF(&this->unk_3A4, temp, 0.2f, 0.03f);

    if ((player->stateFlags2 & 0x80) && (this->unk_39C != 1) && (&this->dyna.actor == player->actor.parent)) {
        Math_ApproachF(&player->actor.world.pos.x, this->dyna.actor.world.pos.x, 0.3f, 10.0f);
        Math_ApproachF(&player->actor.world.pos.y, this->dyna.actor.world.pos.y, 0.3f, 10.0f);
        Math_ApproachF(&player->actor.world.pos.z, this->dyna.actor.world.pos.z, 0.3f, 10.0f);
    }

    if (this->unk_3A0 <= curFrame) {
        if (BREG(52) == 0) {
            this->unk_3C4++;
        }

        Actor_PlaySfxAtPos(&this->dyna.actor, NA_SE_EN_SUISEN_EAT);
        switch (this->unk_39C) {
            case 0:
                globalCtx->damagePlayer(globalCtx, -2);
                func_800B8E58((Player*)this, player->ageProperties->unk_92 + NA_SE_VO_LI_DAMAGE_S);
                CollisionCheck_GreenBlood(globalCtx, NULL, &player->actor.world.pos);
                if (((BREG(53) + 5) < this->unk_3C4) || !(player->stateFlags2 & 0x80)) {
                    player->actor.freezeTimer = 10;
                    func_80A17848(this, globalCtx);
                    return;
                }
                break;

            case 1:
                Actor_ApplyDamage(&this->dyna.actor);
                if ((BREG(54) + 4) < this->unk_3C4) {
                    func_80A179C8(this, globalCtx);
                    return;
                }
                break;

            case 2:
                if ((BREG(54) + 4) < this->unk_3C4) {
                    player->actor.parent = NULL;
                    player->unk_AE8 = 1000;
                    func_80A179C8(this, globalCtx);
                }
                break;
        }
    }
}

void func_80A17848(EnRaf* this, GlobalContext* globalCtx) {
    Player* player = GET_PLAYER(globalCtx);

    func_80A17060(this, 3);
    player->actor.freezeTimer = 10;
    this->unk_3C2 = 3;
    this->unk_3C6 = 3;
    this->actionFunc = func_80A178A0;
}

void func_80A178A0(EnRaf* this, GlobalContext* globalCtx) {
    Player* player = GET_PLAYER(globalCtx);
    f32 curFrame = this->skelAnime.curFrame;

    if (Animation_OnFrame(&this->skelAnime, 10.0f)) {
        player->actor.freezeTimer = 0;
        player->actor.parent = NULL;
        Actor_PlaySfxAtPos(&this->dyna.actor, NA_SE_EN_SUISEN_THROW);
        func_800B8D50(globalCtx, &this->dyna.actor, BREG(55) + 3.0f, this->unk_3BC + 0x8000, BREG(56) + 10.0f, 0);
    } else if (curFrame < 10.0f) {
        player->actor.freezeTimer = 10;
    }

    if (this->unk_3A0 <= curFrame) {
        this->unk_3C2 = 3;
        this->unk_3C6 = 0;
        this->unk_3B4 = 0x14;
        this->actionFunc = func_80A171D8;
    }
}

void func_80A179C8(EnRaf* this, GlobalContext* globalCtx) {
    Vec3f spAC = D_80A193F4;
    Vec3f spA0 = D_80A19400;
    Vec3f sp94;
    s32 i;
    s32 pad;

    this->unk_3C6 = 4;
    Math_Vec3f_Copy(&sp94, &this->dyna.actor.world.pos);
    sp94.y += 10.0f;
    Actor_Spawn(&globalCtx->actorCtx, globalCtx, ACTOR_EN_CLEAR_TAG, sp94.x, sp94.y, sp94.z, 0, 0, 0,
                CLEAR_TAG_SMALL_EXPLOSION);
    Actor_PlaySfxAtPos(&this->dyna.actor, NA_SE_IT_BOMB_EXPLOSION);
    Actor_PlaySfxAtPos(&this->dyna.actor, NA_SE_EN_SUISEN_DEAD);
    if (this->unk_3C0 >= 0) {
        Flags_SetSwitch(globalCtx, this->unk_3C0);
    }

    this->unk_3C2 = 0;
    for (i = 0; i < BREG(57) + 30; i++) {
        spA0.x = (Rand_ZeroOne() - 0.5f) * 0.5f;
        spA0.y = -0.3f;
        spA0.z = (Rand_ZeroOne() - 0.5f) * 0.5f;
        spAC.x = Rand_ZeroOne() - 0.5f;
        spAC.y = Rand_ZeroOne() * 10.0f;
        spAC.z = Rand_ZeroOne() - 0.5f;
        func_80A18A90(this, &this->dyna.actor.world.pos, &spAC, &spA0, (Rand_ZeroFloat(1.0f) / 500.0f) + 0.002f, 90);
    }

    for (i = 2; i < 11; i++) {
        Math_Vec3f_Copy(&this->unk_2C4[i], &gZeroVec3f);
    }

    this->unk_3B4 = 5;
    if (this->unk_39C == 1) {
        func_800BC154(globalCtx, &globalCtx->actorCtx, &this->dyna.actor, 5);
        this->dyna.actor.flags |= (ACTOR_FLAG_1 | ACTOR_FLAG_4);
    }

    this->actionFunc = func_80A17C6C;
}

void func_80A17C6C(EnRaf* this, GlobalContext* globalCtx) {
    if (this->unk_3B4 == 0) {
        this->collider.dim.radius = 50;
        this->collider.dim.height = 10;
        func_800BC154(globalCtx, &globalCtx->actorCtx, &this->dyna.actor, 6);
        this->dyna.actor.flags &= ~(ACTOR_FLAG_1 | ACTOR_FLAG_4);
        func_80A18080(this);
    } else if (this->unk_39C == 1) {
        this->collider.dim.radius = 80;
        this->collider.dim.height = 50;
        CollisionCheck_SetAT(globalCtx, &globalCtx->colChkCtx, &this->collider.base);
    }
}

void func_80A17D14(EnRaf* this) {
    func_80A17060(this, 4);
    this->unk_3C4 = 0;
    this->unk_3C6 = 5;
    this->actionFunc = func_80A17D54;
}

void func_80A17D54(EnRaf* this, GlobalContext* globalCtx) {
    f32 curFrame = this->skelAnime.curFrame;

    if (this->unk_3A0 <= curFrame) {
        this->unk_3C4++;
        if ((BREG(2) + 2) < this->unk_3C4) {
            if (this->unk_3C0 >= 0) {
                Flags_SetSwitch(globalCtx, this->unk_3C0);
            }

            func_80A17DDC(this);
        }
    }
}

void func_80A17DDC(EnRaf* this) {
    func_80A17060(this, 5);
    this->unk_3C6 = 6;
    this->unk_3B6 = 0;
    this->actionFunc = func_80A17E1C;
}

void func_80A17E1C(EnRaf* this, GlobalContext* globalCtx) {
    f32 curFrame = this->skelAnime.curFrame;
    s32 i;

    if (this->unk_3A0 <= curFrame) {
        this->unk_3B6++;
        if (this->unk_3B6 < (BREG(3) + 105)) {
            for (i = 0; i < (BREG(4) + 5); i++) {
                func_80A16D6C(Lib_SegmentedToVirtual(&object_raf_Tex_002EF8), D_80A18F8C, this->unk_3C8);
                func_80A16D40(Lib_SegmentedToVirtual(&object_raf_Tex_0032F8), D_80A18F0C, this->unk_3CA);
                if (this->unk_3C8 < 0x200) {
                    this->unk_3C8++;
                }

                if (this->unk_3CA < 0x40) {
                    this->unk_3CA++;
                }
            }
        }
    }

    if (this->unk_3B6 > (BREG(5) + 50)) {
        for (i = 0; i < (BREG(6) + 5); i++) {
            func_80A16D6C(Lib_SegmentedToVirtual(&object_raf_Tex_002EF8), D_80A1918C, this->unk_3CC);
            func_80A16D40(Lib_SegmentedToVirtual(&object_raf_Tex_0032F8), D_80A18F4C, this->unk_3CE);
            if (this->unk_3CC < 0x200) {
                this->unk_3CC++;
            }

            if (this->unk_3CE < 0x40) {
                this->unk_3CE++;
            }
        }
    }

    if (this->unk_3B6 > (BREG(7) + 160)) {
        for (i = 2; i < 11; i++) {
            Math_Vec3f_Copy(&this->unk_234[i], &gZeroVec3f);
            Math_Vec3f_Copy(&this->unk_2C4[i], &gZeroVec3f);
        }

        func_80A18080(this);
    }
}

void func_80A18080(EnRaf* this) {
    if (this->unk_3C6 == 4) {
        this->unk_3B4 = 0x5A;
    } else {
        this->unk_3C6 = 7;
    }

    this->actionFunc = func_80A180B4;
}

void func_80A180B4(EnRaf* this, GlobalContext* globalCtx) {
    Vec3f sp3C = D_80A1940C;
    s32 i;

    if (this->unk_3B4 == 0) {
        this->unk_3C6 = 7;
    }

    if (this->unk_3BA >= 0) {
        if (this->unk_3BA != 0) {
            this->unk_3BA--;
        }

        if (this->unk_3BA == 0) {
            func_80A17060(this, 3);
            for (i = 2; i < 11; i++) {
                Math_Vec3f_Copy(&this->unk_2C4[i], &sp3C);
            }

            this->unk_3C2 = 3;
            this->unk_3C6 = 0;
            this->unk_3BA = EN_RAF_GET_1F(&this->dyna.actor);
            this->unk_3BA += 0x1E;
            this->actionFunc = func_80A171D8;
        }
    }
}

void EnRaf_Update(Actor* thisx, GlobalContext* globalCtx) {
    s32 pad;
    EnRaf* this = THIS;
    WaterBox* waterBox;
    f32 ySurface;
    Vec3f ripplePos;
    s32 i;

    SkelAnime_Update(&this->skelAnime);
    DECR(this->unk_3B8);
    DECR(this->unk_3B4);
    this->actionFunc(this, globalCtx);

    if ((this->unk_3C6 == 0) && (gSaveContext.save.weekEventReg[12] & 1)) {
        this->unk_3C2 = 0;
        func_80A17D14(this);
        return;
    }

    if (DynaPolyActor_IsInRidingMovingState(&this->dyna)) {
        if ((this->unk_3AC > -0.1f) && (this->unk_39E == 0)) {
            this->unk_3AC = -20.0f;
            this->unk_39E = 1;
            Actor_PlaySfxAtPos(&this->dyna.actor, NA_SE_EN_COMMON_WATER_MID);
        }
    } else {
        this->unk_39E = 0;
    }

    this->unk_3B0 += 3000.0f;
    this->unk_3A8 = 2.0f * Math_SinS(this->unk_3B0);
    if (this->unk_3BE != 2) {
        ySurface = BREG(60) + (this->dyna.actor.world.pos.y - 60.0f);
        if (WaterBox_GetSurface1(globalCtx, &globalCtx->colCtx, this->dyna.actor.world.pos.x,
                                 this->dyna.actor.world.pos.z, &ySurface, &waterBox)) {
            ySurface -= this->unk_3A8 + BREG(59);
            Math_ApproachF(&this->dyna.actor.world.pos.y, this->unk_3AC + ySurface, 0.5f, 40.0f);
            if (this->unk_3B8 == 0) {
                this->unk_3B8 = 0x1E;
                if (this->unk_3C2 == 2) {
                    this->unk_3B8 = 0xA;
                }

                Math_Vec3f_Copy(&ripplePos, &this->dyna.actor.world.pos);
                ripplePos.y = ySurface;
                EffectSsGRipple_Spawn(globalCtx, &ripplePos, 650, 3150, 0);
            }
        }
    } else {
        Math_ApproachF(&this->dyna.actor.world.pos.y, (this->dyna.actor.home.pos.y + this->unk_3AC) - this->unk_3A8,
                       0.5f, 40.0f);
    }

    Math_ApproachZeroF(&this->unk_3AC, 0.3f, 2.0f);
    if (this->unk_3C6 == 4) {
        func_80A18B8C(this, globalCtx);
    }

    for (i = 0; i < 12; i++) {
        if (this->unk_3C6 < 4) {
            Math_ApproachF(&this->unk_234[i].x, this->unk_2C4[i].x, 0.4f, 0.5f);
            Math_ApproachF(&this->unk_234[i].y, this->unk_2C4[i].y, 0.4f, 0.5f);
            Math_ApproachF(&this->unk_234[i].z, this->unk_2C4[i].z, 0.4f, 0.5f);
        } else {
            Math_ApproachF(&this->unk_234[i].x, this->unk_2C4[i].x, 1.0f, 1.0f);
            Math_ApproachF(&this->unk_234[i].y, this->unk_2C4[i].y, 1.0f, 1.0f);
            Math_ApproachF(&this->unk_234[i].z, this->unk_2C4[i].z, 1.0f, 1.0f);
        }
    }

    Collider_UpdateCylinder(&this->dyna.actor, &this->collider);
    if (this->unk_3C6 < 4) {
        CollisionCheck_SetOC(globalCtx, &globalCtx->colChkCtx, &this->collider.base);
    }
}

void func_80A1859C(GlobalContext* globalCtx2, s32 limbIndex, Actor* thisx) {
    GlobalContext* globalCtx = globalCtx2;
    EnRaf* this = THIS;
    s32 i;

    switch (this->unk_3C2) {
        case 1:
            if ((limbIndex == 3) || (limbIndex == 9) || (limbIndex == 6)) {
                for (i = 0; i < 3; i++) {
                    if ((s16)this->skelAnime.curFrame == D_80A19418[i]) {
                        Math_Vec3f_Copy(&this->unk_2C4[limbIndex], &D_80A19420[i]);
                    }
                }
            }

            if ((limbIndex == 4) || (limbIndex == 10) || (limbIndex == 7)) {
                for (i = 0; i < 3; i++) {
                    if ((s16)this->skelAnime.curFrame == D_80A19418[i]) {
                        Math_Vec3f_Copy(&this->unk_2C4[limbIndex], &D_80A19444[i]);
                    }
                }
            }
            break;

        case 2:
            if ((limbIndex == 3) || (limbIndex == 9) || (limbIndex == 6)) {
                Math_Vec3f_Copy(&this->unk_2C4[limbIndex], &D_80A19420[2]);
            } else if ((limbIndex == 4) || (limbIndex == 10) || (limbIndex == 7)) {
                Math_Vec3f_Copy(&this->unk_2C4[limbIndex], &D_80A19444[2]);
            }

            if ((limbIndex > 1) && (limbIndex < 11)) {
                Matrix_RotateY((this->unk_354[limbIndex].y * globalCtx->gameplayFrames), MTXMODE_APPLY);
                Matrix_InsertXRotation_s((this->unk_354[limbIndex].x * globalCtx->gameplayFrames), MTXMODE_APPLY);
                Matrix_InsertZRotation_s((this->unk_354[limbIndex].z * globalCtx->gameplayFrames), MTXMODE_APPLY);
                Matrix_Scale(this->unk_3A4 + 1.0f, 1.0f, 1.0f, MTXMODE_APPLY);
                Matrix_InsertZRotation_s(-(this->unk_354[limbIndex].z * globalCtx->gameplayFrames), MTXMODE_APPLY);
                Matrix_InsertXRotation_s(-(this->unk_354[limbIndex].x * globalCtx->gameplayFrames), MTXMODE_APPLY);
                Matrix_RotateY(-(this->unk_354[limbIndex].y * globalCtx->gameplayFrames), MTXMODE_APPLY);
            }
            break;

        case 3:
            if ((limbIndex == 3) || (limbIndex == 9) || (limbIndex == 6)) {
                for (i = 0; i < 5; i++) {
                    if ((s16)this->skelAnime.curFrame == D_80A19468[i]) {
                        Math_Vec3f_Copy(&this->unk_2C4[limbIndex], &D_80A19474[i]);
                    }
                }
            }

            if ((limbIndex == 4) || (limbIndex == 0xA) || (limbIndex == 7)) {
                for (i = 0; i < 4; i++) {
                    if ((s16)this->skelAnime.curFrame == D_80A19468[i]) {
                        Math_Vec3f_Copy(&this->unk_2C4[limbIndex], &D_80A194B0[i]);
                    }
                }
            }
            break;
    }

    Matrix_Scale(this->unk_234[limbIndex].x, this->unk_234[limbIndex].y, this->unk_234[limbIndex].z, MTXMODE_APPLY);
}

void EnRaf_Draw(Actor* thisx, GlobalContext* globalCtx) {
    EnRaf* this = THIS;

    func_8012C28C(globalCtx->state.gfxCtx);
    func_8012C2DC(globalCtx->state.gfxCtx);
    SkelAnime_DrawTransformFlexOpa(globalCtx, this->skelAnime.skeleton, this->skelAnime.jointTable,
                                   this->skelAnime.dListCount, NULL, NULL, func_80A1859C, &this->dyna.actor);
    if (this->unk_3C6 == 4) {
        func_80A18DA0(this, globalCtx);
    }
}

void func_80A18A90(EnRaf* this, Vec3f* arg1, Vec3f* arg2, Vec3f* arg3, f32 arg4, s16 arg5) {
    s16 i;
    EnRafParticle* particle = this->particles;

    for (i = 0; i < ARRAY_COUNT(this->particles); i++, particle++) {
        if (!particle->isVisible) {
            particle->isVisible = true;
            particle->position = *arg1;
            particle->velocity = *arg2;
            particle->acceleration = *arg3;
            particle->scale = arg4;
            particle->timer = arg5;
            particle->rotation.x = randPlusMinusPoint5Scaled(30000.0f);
            particle->rotation.y = randPlusMinusPoint5Scaled(30000.0f);
            particle->rotation.z = randPlusMinusPoint5Scaled(30000.0f);
            return;
        }
    }
}

void func_80A18B8C(EnRaf* this, GlobalContext* globalCtx) {
    s32 i;
    EnRafParticle* particle = this->particles;

    for (i = 0; i < ARRAY_COUNT(this->particles); i++, particle++) {
        if (particle->isVisible) {
            particle->position.x += particle->velocity.x;
            particle->position.y += particle->velocity.y;
            particle->position.z += particle->velocity.z;
            particle->rotation.x += 0xBB8;
            particle->rotation.y += 0xBB8;
            particle->rotation.z += 0xBB8;
            particle->velocity.x += particle->acceleration.x;
            particle->velocity.y += particle->acceleration.y;
            particle->velocity.z += particle->acceleration.z;

            if (this->unk_3BE != 2) {
                if (particle->position.y < (this->dyna.actor.world.pos.y - 10.0f)) {
                    EffectSsGSplash_Spawn(globalCtx, &particle->position, NULL, NULL, 0, particle->scale * 200000.0f);
                    SoundSource_PlaySfxAtFixedWorldPos(globalCtx, &particle->position, 50, NA_SE_EV_BOMB_DROP_WATER);
                    particle->isVisible = false;
                }
            } else if (particle->position.y < (this->dyna.actor.world.pos.y - 10.0f)) {
                Math_ApproachZeroF(&particle->scale, 0.2f, 0.001f);
                if (particle->scale <= 0.0001f) {
                    particle->timer = 0;
                }
            }

            if (particle->timer != 0) {
                particle->timer--;
            } else {
                particle->isVisible = false;
            }
        }
    }
}

void func_80A18DA0(EnRaf* this, GlobalContext* globalCtx) {
    s16 i;
    EnRafParticle* particle = this->particles;
    GraphicsContext* gfxCtx = globalCtx->state.gfxCtx;

    OPEN_DISPS(gfxCtx);

    func_8012C28C(globalCtx->state.gfxCtx);
    for (i = 0; i < ARRAY_COUNT(this->particles); i++, particle++) {
        if (particle->isVisible) {
            Matrix_InsertTranslation(particle->position.x, particle->position.y, particle->position.z, MTXMODE_NEW);
            Matrix_Scale(particle->scale, particle->scale, particle->scale, MTXMODE_APPLY);
            Matrix_InsertXRotation_s(particle->rotation.x, MTXMODE_APPLY);
            Matrix_RotateY(particle->rotation.y, MTXMODE_APPLY);
            Matrix_InsertZRotation_s(particle->rotation.z, MTXMODE_APPLY);

            gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
            gSPDisplayList(POLY_OPA_DISP++, object_raf_DL_0024E0);
        }
    }

    CLOSE_DISPS(gfxCtx);
}
