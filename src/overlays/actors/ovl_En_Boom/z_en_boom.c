/*
 * File: z_en_boom.c
 * Overlay: ovl_En_Boom
 * Description: Zora boomerangs
 */

#include "z_en_boom.h"
#include "objects/gameplay_keep/gameplay_keep.h"

#define FLAGS (ACTOR_FLAG_10 | ACTOR_FLAG_20)

#define THIS ((EnBoom*)thisx)

void EnBoom_Init(Actor* thisx, GlobalContext* globalCtx);
void EnBoom_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnBoom_Update(Actor* thisx, GlobalContext* globalCtx);
void EnBoom_Draw(Actor* thisx, GlobalContext* globalCtx);

void EnBoom_SetupAction(EnBoom* this, EnBoomActionFunc actionFunc);
void func_808A2918(EnBoom* this, GlobalContext* globalCtx);

const ActorInit En_Boom_InitVars = {
    ACTOR_EN_BOOM,
    ACTORCAT_ITEMACTION,
    FLAGS,
    GAMEPLAY_KEEP,
    sizeof(EnBoom),
    (ActorFunc)EnBoom_Init,
    (ActorFunc)EnBoom_Destroy,
    (ActorFunc)EnBoom_Update,
    (ActorFunc)EnBoom_Draw,
};

static ColliderQuadInit sQuadInit = {
    {
        COLTYPE_NONE,
        AT_ON | AT_TYPE_PLAYER,
        AC_NONE,
        OC1_NONE,
        OC2_TYPE_PLAYER,
        COLSHAPE_QUAD,
    },
    {
        ELEMTYPE_UNK2,
        { 0x00000010, 0x00, 0x02 },
        { 0xF7CFFFFF, 0x00, 0x00 },
        TOUCH_ON | TOUCH_NEAREST | TOUCH_SFX_NORMAL,
        BUMP_NONE,
        OCELEM_NONE,
    },
    { { { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f } } },
};

static InitChainEntry sInitChain[] = {
    ICHAIN_S8(targetMode, 5, ICHAIN_CONTINUE),
    ICHAIN_VEC3S(shape.rot, 0, ICHAIN_STOP),
};

void EnBoom_SetupAction(EnBoom* this, EnBoomActionFunc actionFunc) {
    this->actionFunc = actionFunc;
}

void func_808A24DC(EnBoom* this, GlobalContext* globalCtx) {
    WaterBox* sp54;
    f32 sp50 = this->actor.world.pos.y;
    u16 sp4E = this->actor.bgCheckFlags & 0x20;

    if (WaterBox_GetSurface1(globalCtx, &globalCtx->colCtx, this->actor.world.pos.x, this->actor.world.pos.z, &sp50,
                             &sp54) &&
        (this->actor.world.pos.y < sp50)) {
        Vec3f sp40;

        this->actor.bgCheckFlags |= 0x20;
        sp40.x = this->actor.world.pos.x;
        sp40.y = this->actor.world.pos.y - 20.0f;
        sp40.z = this->actor.world.pos.z;
        EffectSsBubble_Spawn(globalCtx, &sp40, 20.0f, 10.0f, 20.0f, 0.13f);
    } else {
        this->actor.bgCheckFlags &= ~0x20;
    }

    if ((this->actor.bgCheckFlags & 0x40) && ((this->actor.bgCheckFlags & 0x20) != sp4E)) {
        Vec3f sp34;

        Math_Vec3f_Diff(&this->actor.world.pos, &this->actor.prevPos, &sp34);
        if (sp34.y != 0.0f) {
            f32 temp_fv0 = sqrtf(SQ(sp34.x) + SQ(sp34.z));

            if (temp_fv0 != 0.0f) {
                temp_fv0 = (((sp50 - this->actor.prevPos.y) / sp34.y) * temp_fv0) / temp_fv0;
            }

            sp34.x = this->actor.prevPos.x + (sp34.x * temp_fv0);
            sp34.y = sp50;
            sp34.z = this->actor.prevPos.z + (sp34.z * temp_fv0);
            EffectSsGSplash_Spawn(globalCtx, &sp34, NULL, NULL, 0, 300);
        }

        Actor_PlaySfxAtPos(&this->actor, NA_SE_EV_DIVE_INTO_WATER_L);

        EffectSsGRipple_Spawn(globalCtx, &sp34, 100, 500, 0);
        EffectSsGRipple_Spawn(globalCtx, &sp34, 100, 500, 4);
        EffectSsGRipple_Spawn(globalCtx, &sp34, 100, 500, 8);
    }

    this->actor.bgCheckFlags |= 0x40;
}

void EnBoom_Init(Actor* thisx, GlobalContext* globalCtx) {
    static u8 D_808A3068[4] = { 255, 255, 100, 255 };
    static u8 D_808A306C[4] = { 255, 255, 100, 64 };
    static u8 D_808A3070[4] = { 255, 255, 100, 0 };
    static u8 D_808A3074[4] = { 255, 255, 100, 0 };
    s32 pad;
    EnBoom* this = THIS;
    EffectBlureInit1 sp30;
    s32 i;

    this->actor.room = -1;
    Actor_ProcessInitChain(&this->actor, sInitChain);

    for (i = 0; i < 4; i++) {
        sp30.p1StartColor[i] = D_808A3068[i];
        sp30.p2StartColor[i] = D_808A306C[i];
        sp30.p1EndColor[i] = D_808A3070[i];
        sp30.p2EndColor[i] = D_808A3074[i];
    }

    sp30.elemDuration = 8;
    sp30.unkFlag = 0;
    sp30.calcMode = 0;

    Effect_Add(globalCtx, &this->effectIndex, 1, 0, 0, &sp30);

    Collider_InitQuad(globalCtx, &this->collider);
    Collider_SetQuad(globalCtx, &this->collider, &this->actor, &sQuadInit);
    EnBoom_SetupAction(this, func_808A2918);
}

void EnBoom_Destroy(Actor* thisx, GlobalContext* globalCtx) {
    EnBoom* this = THIS;
    Player* player = GET_PLAYER(globalCtx);
    Actor* temp;

    if (player != NULL) {
        Effect_Destroy(globalCtx, this->effectIndex);
        Collider_DestroyQuad(globalCtx, &this->collider);

        temp = this->actor.child;
        if (temp != NULL) {
            temp->parent = NULL;
            player->boomerangActor = temp;
        } else {
            temp = this->actor.parent;
            if (temp != NULL) {
                temp->child = NULL;
            } else {
                player->boomerangActor = NULL;
                player->stateFlags1 &= ~0x2000000;
            }
        }
        player->stateFlags3 |= 0x800000;
    }
}

void func_808A2918(EnBoom* this, GlobalContext* globalCtx) {
    Actor* sp7C;
    Player* player = GET_PLAYER(globalCtx);
    s32 sp74;
    s16 sp72;
    s16 sp70;
    s16 sp6E;
    s16 sp6C;
    Actor* temp;
    f32 sp64;
    f32 distXYZ;

    sp7C = this->player;

    if (sp7C != NULL) {
        sp72 = Actor_YawToPoint(&this->actor, &sp7C->focus.pos);
        sp70 = this->actor.world.rot.y - sp72;
        sp6E = Actor_PitchToPoint(&this->actor, &sp7C->focus.pos);
        sp6C = this->actor.world.rot.x - sp6E;

        sp64 = (200.0f - Math_Vec3f_DistXYZ(&this->actor.world.pos, &sp7C->focus.pos)) * 0.005f;
        if (sp64 < 0.12f) {
            sp64 = 0.12f;
        }

        if ((&player->actor != sp7C) && ((sp7C->update == NULL) || ((this->unk_1CF < 0) && (ABS_ALT(sp70) > 0x4000)))) {
            this->player = NULL;
        } else {
            if (this->unk_1CE != 0) {
                this->unk_1CE--;
                this->actor.world.rot.y += (this->actor.params == 0) ? 0x190 : -0x190;
            } else {
                if (this->unk_1CF > 0) {
                    this->unk_1CF--;
                } else {
                    this->unk_1CF = -1;
                }

                Math_ScaledStepToS(&this->actor.world.rot.y, sp72,
                                   (this->unk_1CF > 0) ? 1000 : (s16)(((sp70 < 0) ? -sp70 : sp70) * sp64));
            }

            Math_ScaledStepToS(&this->actor.world.rot.x, sp6E, ABS_ALT(sp6C) * sp64);
        }
    }

    Actor_SetSpeeds(&this->actor, 12.0f);
    Actor_MoveWithGravity(&this->actor);
    func_808A24DC(this, globalCtx);
    func_800B9010(&this->actor, NA_SE_IT_BOOMERANG_FLY - SFX_FLAG);

    if ((this->collider.base.atFlags & AT_HIT) && (((this->collider.base.at->id == ACTOR_EN_ITEM00) &&
                                                    (this->collider.base.at->params != ITEM00_HEART_CONTAINER) &&
                                                    (this->collider.base.at->params != ITEM00_HEART_PIECE)) ||
                                                   (this->collider.base.at->id == ACTOR_EN_SI))) {
        this->unk_1C8 = this->collider.base.at;
        if (this->collider.base.at->id == ACTOR_EN_SI) {
            this->collider.base.at->flags |= 0x2000;
        }
    }

    if (DECR(this->unk_1CC) != 0) {
        s32 sp5C;
        Vec3f sp50;
        s32 pad;

        sp74 = BgCheck_EntityLineTest1(&globalCtx->colCtx, &this->actor.prevPos, &this->actor.world.pos, &sp50,
                                       &this->actor.wallPoly, true, true, true, true, &sp5C);
        if (sp74 != 0) {
            if (func_800B90AC(globalCtx, &this->actor, this->actor.wallPoly, sp5C, &sp50)) {
                sp74 = 0;
            } else {
                CollisionCheck_SpawnShieldParticlesMetal(globalCtx, &sp50);
            }
        }

        if (sp74 != 0) {
            this->actor.world.rot.x = -this->actor.world.rot.x;
            this->actor.world.rot.y += 0x8000;
            this->player = &player->actor;
            this->unk_1CC = 0;
        }
    }

    if (this->unk_1CC <= 16) {
        distXYZ = Math_Vec3f_DistXYZ(&this->actor.world.pos, &player->actor.focus.pos);

        if (&player->actor != this->player) {
            if (this->player == 0) {
                this->unk_1CE = 8;
            }
            this->player = &player->actor;
        }

        if (distXYZ < 40.0f) {
            sp7C = this->unk_1C8;
            if (sp7C != NULL) {
                Math_Vec3f_Copy(&sp7C->world.pos, &player->actor.world.pos);
                if (sp7C->id == ACTOR_EN_ITEM00) {
                    sp7C->gravity = -0.9f;
                    sp7C->bgCheckFlags &= ~3;
                } else {
                    sp7C->flags &= -0x2001;
                }
            }
            Actor_MarkForDeath(&this->actor);
        }
    }

    sp7C = this->unk_1C8;
    if (sp7C != NULL) {
        if (sp7C->update == NULL) {
            this->unk_1C8 = NULL;
        } else {
            Math_Vec3f_Copy(&sp7C->world.pos, &this->actor.world.pos);
        }
    }
}

void EnBoom_Update(Actor* thisx, GlobalContext* globalCtx) {
    EnBoom* this = THIS;
    Player* player = GET_PLAYER(globalCtx);
    Actor* actor;

    if (!(player->stateFlags1 & 0x20000000)) {
        this->actionFunc(this, globalCtx);

        if (((actor = this->actor.child) != NULL) || ((actor = this->actor.parent) != NULL)) {
            this->actor.focus.pos.x = (this->actor.world.pos.x + actor->world.pos.x) * 0.5f;
            this->actor.focus.pos.y = (this->actor.world.pos.y + actor->world.pos.y) * 0.5f;
            this->actor.focus.pos.z = (this->actor.world.pos.z + actor->world.pos.z) * 0.5f;
        } else {
            Actor_SetFocus(&this->actor, 0.0f);
        }

        if (this->actor.params != 0) {
            this->unk_1CD--;
        } else {
            this->unk_1CD++;
        }
    }
}

typedef struct {
    /* 0x00 */ Gfx* unk_00;
    /* 0x04 */ Vec3f unk_04;
    /* 0x10 */ Vec3f unk_10;
} EnBoomStruct;

EnBoomStruct D_808A3078[] = {
    { gameplay_keep_DL_06FE20, { -960.0f, 0.0f, 0.0f }, { 960.0f, 0.0f, 0.0f } },
    { gameplay_keep_DL_06FF68, { -960.0f, 0.0f, 0.0f }, { 960.0f, 0.0f, 0.0f } },
};

void EnBoom_Draw(Actor* thisx, GlobalContext* globalCtx) {
    EnBoom* this = THIS;
    EnBoomStruct* sp58 = &D_808A3078[this->actor.params];
    Vec3f sp4C;
    Vec3f sp40;

    OPEN_DISPS(globalCtx->state.gfxCtx);

    Matrix_RotateY(this->actor.world.rot.y, MTXMODE_APPLY);

    Matrix_InsertZRotation_s((this->actor.params != 0) ? 0x1F40 : -0x1F40, MTXMODE_APPLY);
    Matrix_InsertXRotation_s(this->actor.world.rot.x, MTXMODE_APPLY);
    Matrix_MultiplyVector3fByState(&sp58->unk_04, &sp4C);
    Matrix_MultiplyVector3fByState(&sp58->unk_10, &sp40);

    if (func_80126440(globalCtx, &this->collider, &this->weaponInfo, &sp4C, &sp40)) {
        EffectBlure_AddVertex(Effect_GetByIndex(this->effectIndex), &sp4C, &sp40);
    }

    func_8012C28C(globalCtx->state.gfxCtx);
    Matrix_RotateY(this->unk_1CD * 0x2EE0, MTXMODE_APPLY);

    gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(globalCtx->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPDisplayList(POLY_OPA_DISP++, sp58->unk_00);

    CLOSE_DISPS(globalCtx->state.gfxCtx);
}
