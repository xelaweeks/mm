/*
 * File: z_en_bom.c
 * Overlay: ovl_En_Bom
 * Description: Bomb / Powder Keg
 */

#include "z_en_bom.h"
#include "z64rumble.h"
#include "objects/gameplay_keep/gameplay_keep.h"

#define FLAGS (ACTOR_FLAG_10 | ACTOR_FLAG_20)

#define THIS ((EnBom*)thisx)

void EnBom_Init(Actor* thisx, PlayState* play);
void EnBom_Destroy(Actor* thisx, PlayState* play);
void EnBom_Update(Actor* thisx, PlayState* play);
void EnBom_Draw(Actor* thisx, PlayState* play);

void func_80871058(EnBom* this, PlayState* play);
void func_808714D4(EnBom* this, PlayState* play);
void func_80872648(PlayState* play, Vec3f* arg1);
void func_808726DC(PlayState* play, Vec3f* arg1, Vec3f* arg2, Vec3f* arg3, s32 arg4);
void func_80872BC0(PlayState* play, s32 arg1);

typedef struct {
    /* 0x00 */ Vec3f pos;
    /* 0x0C */ Vec3f velocity;
    /* 0x18 */ s16 rotY;
    /* 0x1A */ s16 rotX;
} PowderKegFuseSegment; // size = 0x1C

static PowderKegFuseSegment sPowderKegFuseSegments[16];

const ActorInit En_Bom_InitVars = {
    ACTOR_EN_BOM,
    ACTORCAT_EXPLOSIVES,
    FLAGS,
    GAMEPLAY_KEEP,
    sizeof(EnBom),
    (ActorFunc)EnBom_Init,
    (ActorFunc)EnBom_Destroy,
    (ActorFunc)EnBom_Update,
    (ActorFunc)EnBom_Draw,
};

static f32 enBomScales[] = { 0.01f, 0.03f };

static ColliderCylinderInit sCylinderInit = {
    {
        COLTYPE_HIT0,
        AT_NONE,
        AC_ON | AC_TYPE_PLAYER | AC_TYPE_OTHER,
        OC1_ON | OC1_TYPE_ALL,
        OC2_TYPE_2,
        COLSHAPE_CYLINDER,
    },
    {
        ELEMTYPE_UNK2,
        { 0x00000000, 0x00, 0x00 },
        { 0x00013828, 0x00, 0x00 },
        TOUCH_NONE | TOUCH_SFX_NORMAL,
        BUMP_ON,
        OCELEM_ON,
    },
    { 6, 11, 14, { 0, 0, 0 } },
};

static ColliderJntSphElementInit sJntSphElementsInit1[1] = {
    {
        {
            ELEMTYPE_UNK0,
            { 0x00000008, 0x00, 0x02 },
            { 0x00000000, 0x00, 0x00 },
            TOUCH_ON | TOUCH_SFX_NONE,
            BUMP_NONE,
            OCELEM_NONE,
        },
        { 0, { { 0, 0, 0 }, 0 }, 100 },
    },
};

static ColliderJntSphInit sJntSphInit1 = {
    {
        COLTYPE_HIT0,
        AT_ON | AT_TYPE_ALL,
        AC_NONE,
        OC1_NONE,
        OC2_NONE,
        COLSHAPE_JNTSPH,
    },
    ARRAY_COUNT(sJntSphElementsInit1),
    sJntSphElementsInit1,
};

static ColliderJntSphElementInit sJntSphElementsInit2[1] = {
    {
        {
            ELEMTYPE_UNK0,
            { 0x80000008, 0x00, 0x04 },
            { 0x00000000, 0x00, 0x00 },
            TOUCH_ON | TOUCH_SFX_NONE,
            BUMP_NONE,
            OCELEM_NONE,
        },
        { 0, { { 0, 0, 0 }, 0 }, 100 },
    },
};

static ColliderJntSphInit sJntSphInit2 = {
    {
        COLTYPE_HIT0,
        AT_ON | AT_TYPE_ALL,
        AC_NONE,
        OC1_NONE,
        OC2_NONE,
        COLSHAPE_JNTSPH,
    },
    ARRAY_COUNT(sJntSphElementsInit2),
    sJntSphElementsInit2,
};

static InitChainEntry sInitChain[] = {
    ICHAIN_VEC3F(scale, 0, ICHAIN_CONTINUE),
    ICHAIN_F32(targetArrowOffset, 2000, ICHAIN_CONTINUE),
    ICHAIN_F32_DIV1000(gravity, -4000, ICHAIN_STOP),
};

void EnBom_Init(Actor* thisx, PlayState* play) {
    EnBom* this = THIS;
    s32 params;

    Actor_ProcessInitChain(&this->actor, sInitChain);
    ActorShape_Init(&this->actor.shape, 700.0f, ActorShadow_DrawCircle, 16.0f);
    this->actor.colChkInfo.mass = 200;
    this->actor.colChkInfo.cylRadius = 5;
    this->actor.colChkInfo.cylHeight = 10;

    this->flashSpeedScale = 7;
    this->isPowderKeg = ENBOM_GETX_1(&this->actor);
    if (this->isPowderKeg) {
        play->actorCtx.unk5 |= 1;
        this->timer = gSaveContext.powderKegTimer;
    } else {
        this->timer = 70;
    }

    Collider_InitCylinder(play, &this->collider1);
    Collider_InitJntSph(play, &this->collider2);
    Collider_SetCylinder(play, &this->collider1, &this->actor, &sCylinderInit);

    if (!this->isPowderKeg) {
        Collider_SetJntSph(play, &this->collider2, &this->actor, &sJntSphInit1, &this->collider3);
        this->collider1.dim.radius = 6;
        this->collider1.dim.height = 11;
    } else {
        Collider_SetJntSph(play, &this->collider2, &this->actor, &sJntSphInit2, &this->collider3);
        this->collider1.dim.radius = 20;
        this->collider1.dim.height = 36;
        func_80872648(play, &this->actor.world.pos);
    }

    this->collider3.info.toucher.damage += ENBOM_GETZ_FF00(thisx);
    this->actor.shape.rot.z &= 0xFF;
    if (ENBOM_GETZ_80(&this->actor)) {
        this->actor.shape.rot.z |= 0xFF00;
    }

    this->collider2.elements[0].dim.worldSphere.center.x = this->actor.world.pos.x;
    this->collider2.elements[0].dim.worldSphere.center.y = this->actor.world.pos.y;
    this->collider2.elements[0].dim.worldSphere.center.z = this->actor.world.pos.z;

    this->actor.flags |= ACTOR_FLAG_100000;

    if (Actor_HasParent(&this->actor, play)) {
        this->actionFunc = func_808714D4;
        this->actor.room = -1;
        Actor_SetScale(&this->actor, enBomScales[this->isPowderKeg]);
    } else {
        this->actionFunc = func_80871058;
        gSaveContext.powderKegTimer = 0;
    }
}

void EnBom_Destroy(Actor* thisx, PlayState* play) {
    EnBom* this = THIS;

    Collider_DestroyJntSph(play, &this->collider2);
    Collider_DestroyCylinder(play, &this->collider1);
    if (this->isPowderKeg) {
        play->actorCtx.unk5 &= ~1;
    }
}

void func_80871058(EnBom* this, PlayState* play) {
    static Vec3f D_80872E68[] = {
        { 2.0f, -6.0f, -0.3f },
        { 1.5f, -5.0f, -0.6f },
        { 0.2f, -6.0f, -0.1f },
    };

    if (Actor_HasParent(&this->actor, play)) {
        this->actionFunc = func_808714D4;
        this->actor.room = -1;
        return;
    }

    if ((this->actor.velocity.y > 0.0f) && (this->actor.bgCheckFlags & 0x10)) {
        this->actor.velocity.y = -this->actor.velocity.y;
    }

    if ((this->actor.speedXZ != 0.0f) && (this->actor.bgCheckFlags & 8)) {
        s16 yDiff = BINANG_SUB(this->actor.wallYaw, this->actor.world.rot.y);

        if (ABS_ALT(yDiff) > 0x4000) {
            this->actor.world.rot.y =
                BINANG_SUB(this->actor.wallYaw - this->actor.world.rot.y + this->actor.wallYaw, 0x8000);
        }

        Actor_PlaySfxAtPos(&this->actor, this->isPowderKeg ? NA_SE_EV_PUT_DOWN_WOODBOX : NA_SE_EV_BOMB_BOUND);
        Actor_MoveWithGravity(&this->actor);
        this->actor.speedXZ *= 0.7f;
        this->actor.bgCheckFlags &= ~8;
    }

    if (!(this->actor.bgCheckFlags & 1)) {
        Math_StepToF(&this->actor.speedXZ, 0.0f, 0.08f);
    } else {
        Vec3f* sp58;
        u32 sp54 = func_800C99D4(&play->colCtx, this->actor.floorPoly, this->actor.floorBgId);
        Vec3f sp48;
        s16 sp46;
        f32 sp40;
        f32 sp3C;
        f32 sp38;

        sp58 = &D_80872E68[this->isPowderKeg];

        if (sp54 == 5) {
            sp58 = &D_80872E68[2];
        }

        if ((sp54 == 4) || (sp54 == 14) || (sp54 == 15)) {
            s16 sp36;

            Math_ApproachF(&this->actor.shape.yOffset, 0.0f, 0.1f, 50.0f);
            sp36 = this->actor.shape.shadowAlpha;
            Math_ApproachS(&sp36, 0, 1, 20);
            this->actor.shape.shadowAlpha = sp36;
        } else {
            Math_ApproachF(&this->actor.shape.yOffset, 700.0f, 1.0f, 700.0f);
        }

        sp40 = Math_SinS(this->actor.world.rot.y) * this->actor.speedXZ;
        sp3C = Math_CosS(this->actor.world.rot.y) * this->actor.speedXZ;
        func_800B75A0(this->actor.floorPoly, &sp48, &sp46);

        sp40 += 3.0f * sp48.x;
        sp3C += 3.0f * sp48.z;
        sp38 = sqrtf(SQ(sp40) + SQ(sp3C));

        if ((sp38 < this->actor.speedXZ) ||
            (SurfaceType_GetSlope(&play->colCtx, this->actor.floorPoly, this->actor.floorBgId) == 1)) {
            if (sp38 > 16.0f) {
                this->actor.speedXZ = 16.0f;
            } else {
                this->actor.speedXZ = sp38;
            }
            this->actor.world.rot.y = Math_FAtan2F(sp3C, sp40);
        }

        if (!Math_StepToF(&this->actor.speedXZ, 0.0f, sp58->x)) {
            s16 temp = this->actor.world.rot.y;
            s32 pad;

            if (ABS_ALT(BINANG_SUB(this->actor.world.rot.y, this->actor.shape.rot.y)) > 0x4000) {
                temp = BINANG_ROT180(temp);
            }
            Math_ScaledStepToS(&this->actor.shape.rot.y, temp, this->actor.speedXZ * 100.0f);
            this->unk_1FA += (s16)(this->actor.speedXZ * 800.0f);
        }

        if (this->actor.bgCheckFlags & 2) {
            Actor_PlaySfxAtPos(&this->actor, this->isPowderKeg ? NA_SE_EV_TRE_BOX_BOUND : NA_SE_EV_BOMB_BOUND);
            if (this->actor.velocity.y < sp58->y) {
                if ((sp54 == 4) || (sp54 == 14) || (sp54 == 15)) {
                    this->actor.velocity.y = 0.0f;
                } else {
                    this->actor.velocity.y = this->actor.velocity.y * sp58->z;
                }
                this->actor.bgCheckFlags &= ~1;
            }
        } else if (this->timer >= 4) {
            Actor_LiftActor(&this->actor, play);
        }
    }

    Actor_MoveWithGravity(&this->actor);
}

void func_808714D4(EnBom* this, PlayState* play) {
    if (Actor_HasNoParent(&this->actor, play)) {
        this->actionFunc = func_80871058;
        this->actor.room = play->roomCtx.currRoom.num;
        this->actor.flags &= ~ACTOR_FLAG_100000;
        this->actor.bgCheckFlags &= ~1;
        Math_Vec3s_ToVec3f(&this->actor.prevPos, &this->actor.home.rot);
        if (this->isPowderKeg) {
            gSaveContext.powderKegTimer = 0;
        }
        func_80871058(this, play);
    } else {
        Math_Vec3f_ToVec3s(&this->actor.home.rot, &this->actor.parent->world.pos);
        if (this->isPowderKeg) {
            gSaveContext.powderKegTimer = this->timer;
        }
    }
    Math_ScaledStepToS(&this->unk_1FA, 0, 2000);
}

void func_808715B8(EnBom* this, PlayState* play) {
    static s16 D_80872E8C[] = { 100, 200 };
    static Color_RGBA8 D_80872E90 = { 185, 140, 70, 255 };
    static Color_RGBA8 D_80872E94 = { 255, 255, 255, 255 };
    s32 i;
    s32 temp_s0;
    f32 temp_f20;
    s32 pad;
    f32 spCC;
    Vec3f spC0;
    Vec3f spB4;
    CollisionPoly* spB0;
    s32 spAC;
    Vec3f spA0;
    Vec3f sp94;
    Vec3f sp88;
    Color_RGBA8 sp84;
    Color_RGBA8 sp80;

    if (this->collider2.elements->dim.modelSphere.radius == 0) {
        this->actor.flags |= ACTOR_FLAG_20;
        Rumble_Request(this->actor.xzDistToPlayer, 255, 20, 150);
    }

    this->collider2.elements->dim.worldSphere.radius = D_80872E8C[this->isPowderKeg];
    if (this->timer == 7) {
        this->collider2.base.atFlags &= ~OC1_TYPE_1;
    }

    if (this->actor.params == ENBOM_1) {
        CollisionCheck_SetAT(play, &play->colChkCtx, &this->collider2.base);
    }

    if (play->envCtx.lightSettings.diffuseColor1[0] != 0) {
        play->envCtx.lightSettings.diffuseColor1[0] -= 25;
    }

    if (play->envCtx.lightSettings.diffuseColor1[1] != 0) {
        play->envCtx.lightSettings.diffuseColor1[1] -= 25;
    }

    if (play->envCtx.lightSettings.diffuseColor1[2] != 0) {
        play->envCtx.lightSettings.diffuseColor1[2] -= 25;
    }

    if (play->envCtx.lightSettings.ambientColor[0] != 0) {
        play->envCtx.lightSettings.ambientColor[0] -= 25;
    }

    if (play->envCtx.lightSettings.ambientColor[1] != 0) {
        play->envCtx.lightSettings.ambientColor[1] -= 25;
    }

    if (play->envCtx.lightSettings.ambientColor[2] != 0) {
        play->envCtx.lightSettings.ambientColor[2] -= 25;
    }

    if (this->timer == 0) {
        func_80123590(play, &this->actor);
        Actor_MarkForDeath(&this->actor);
    }

    if ((this->timer & 1) == 0) {
        spCC = Rand_ZeroFloat(M_PI);

        for (i = 0; i < 15; i++) {
            Matrix_RotateYF(((2.0f * (i * M_PI)) / 15.0f) + spCC, MTXMODE_NEW);
            Matrix_MultVecZ((10 - this->timer) * 300.0f * 0.1f, &spC0);
            spB4.x = this->actor.world.pos.x + spC0.x;
            spB4.y = this->actor.world.pos.y + 500.0f;
            spB4.z = this->actor.world.pos.z + spC0.z;
            if (BgCheck_EntityRaycastFloor3(&play->colCtx, &spB0, &spAC, &spB4) != BGCHECK_Y_MIN) {
                temp_s0 = func_800C99D4(&play->colCtx, spB0, spAC);
                temp_f20 = BgCheck_EntityRaycastFloor1(&play->colCtx, &spB0, &spB4);

                if ((temp_s0 == 4) || (temp_s0 == 15) || (temp_s0 == 14)) {
                    if (temp_s0 == 4) {
                        sp84 = D_80872E90;
                        sp80 = D_80872E90;
                    } else {
                        sp84 = D_80872E94;
                        sp80 = D_80872E94;
                    }
                    Matrix_MultVecZ(5.0f, &sp94);
                    sp88.x = sp88.z = 0.0f;
                    sp94.y = 2.0f;
                    sp88.y = 0.2f;

                    spA0.x = spB4.x;
                    spA0.y = temp_f20;
                    spA0.z = spB4.z;

                    temp_f20 = Rand_ZeroFloat(250.0f);
                    func_800B0F18(play, &spA0, &sp94, &sp88, &sp84, &sp80, temp_f20 + 950.0f, 10,
                                  Rand_ZeroFloat(5.0f) + 14.0f);
                }
            }
        }
    }
}

static s16 D_80872E98[] = { 3, 5 };
static s16 D_80872E9C[] = { 10, 15 };

void EnBom_Update(Actor* thisx, PlayState* play) {
    Vec3f spA4 = { 0.0f, 0.0f, 0.0f };
    Vec3f sp98 = { 0.0f, 0.1f, 0.0f };
    Vec3f sp8C = { 0.0f, 0.0f, 0.0f };
    Vec3f sp80;
    Vec3f sp74 = { 0.0f, 0.6f, 0.0f };
    Color_RGBA8 sp70 = { 255, 255, 255, 255 };
    EnBom* this = THIS;
    s32 pad;
    Player* player = GET_PLAYER(play);

    if (player->stateFlags1 & 2) {
        return;
    }

    if (Player_GetMask(play) == PLAYER_MASK_GIANT) {
        Actor_MarkForDeath(thisx);
        return;
    }

    if (this->unk_1FC != 0) {
        this->unk_1FC--;
        Math_ApproachZeroF(&thisx->speedXZ, 1.0f, 1.0f);
        Actor_MoveWithGravity(thisx);
        Actor_UpdateBgCheckInfo(play, thisx, 35.0f, 10.0f, 36.0f, 4);
        if (this->unk_1FC == 0) {
            if (this->isPowderKeg) {
                gSaveContext.powderKegTimer = 0;
            }
            Actor_MarkForDeath(thisx);
        }
    } else {
        thisx->gravity = -1.2f;
        if (this->timer != 0) {
            if (!this->isPowderKeg || (func_808715B8 == this->actionFunc) || !Play_InCsMode(play)) {
                this->timer--;
            }
        }

        if ((!this->isPowderKeg && (this->timer == 67)) || (this->isPowderKeg && (this->timer <= 2400))) {
            Actor_PlaySfxAtPos(thisx, NA_SE_PL_TAKE_OUT_SHIELD);
            Actor_SetScale(thisx, enBomScales[this->isPowderKeg]);
        }

        if ((thisx->xzDistToPlayer >= 20.0f) || (fabsf(thisx->playerHeightRel) >= 80.0f)) {
            this->unk_1F8 = 1;
        }

        this->actionFunc(this, play);

        Actor_UpdateBgCheckInfo(play, thisx, 35.0f, 10.0f, 36.0f, 0x1F);
        if (thisx->params == ENBOM_0) {
            static Vec3us D_80872ED4[] = {
                { 40, 20, 100 },
                { 300, 60, 600 },
            };
            Vec3us* sp60 = &D_80872ED4[this->isPowderKeg];

            sp74.y = 0.2f;
            Math_Vec3f_Copy(&sp80, &thisx->home.pos);
            if ((play->gameplayFrames % 2) == 0) {
                EffectSsGSpk_SpawnFuse(play, thisx, &sp80, &spA4, &sp8C);
            }
            if (this->isPowderKeg) {
                func_801A0810(&thisx->projectedPos, NA_SE_IT_BIG_BOMB_IGNIT - SFX_FLAG,
                              (this->flashSpeedScale == 7)   ? 0
                              : (this->flashSpeedScale == 3) ? 1
                                                             : 2);
            } else {
                Actor_PlaySfxAtPos(thisx, NA_SE_IT_BOMB_IGNIT - SFX_FLAG);
            }

            sp80.y += 3.0f;
            func_800B0DE0(play, &sp80, &spA4, &sp74, &sp70, &sp70, 50, 5);

            if ((this->collider1.base.acFlags & AC_HIT) ||
                ((this->collider1.base.ocFlags1 & OC1_HIT) && ((this->collider1.base.oc->category == ACTORCAT_ENEMY) ||
                                                               (this->collider1.base.oc->category == ACTORCAT_BOSS)))) {
                this->timer = 0;
                thisx->shape.rot.z = 0;
            } else if ((this->timer > 100) && (Player_IsBurningStickInRange(play, &thisx->world.pos, 30.0f, 50.0f))) {
                this->timer = 100;
            }

            sp74.y = 0.2f;
            sp80 = thisx->world.pos;
            sp80.y += 10.0f;

            if ((this->timer == sp60->x) || (this->timer == sp60->y) || (this->timer == 3)) {
                thisx->shape.rot.z = 0;
                this->flashSpeedScale >>= 1;
            }

            if ((this->timer < sp60->z) && (this->timer & (this->flashSpeedScale + 1))) {
                Math_ApproachF(&this->unk_1F4, 140.0f, 1.0f, 140.0f / this->flashSpeedScale);
            } else {
                Math_ApproachZeroF(&this->unk_1F4, 1.0f, 140.0f / this->flashSpeedScale);
            }

            if (this->timer < 3) {
                Actor_SetScale(thisx, thisx->scale.x + 0.002f);
            }

            if (this->timer == 0) {
                sp80 = thisx->world.pos;
                sp80.y += 10.0f;
                if (Actor_HasParent(thisx, play)) {
                    sp80.y += 30.0f;
                }
                Actor_Spawn(&play->actorCtx, play, ACTOR_EN_CLEAR_TAG, sp80.x, sp80.y - 10.0f, sp80.z, 0, 0, 0,
                            this->isPowderKeg);
                func_800BC848(thisx, play, D_80872E98[this->isPowderKeg], D_80872E9C[this->isPowderKeg]);
                play->envCtx.lightSettings.diffuseColor1[0] = play->envCtx.lightSettings.diffuseColor1[1] =
                    play->envCtx.lightSettings.diffuseColor1[2] = 250;
                play->envCtx.lightSettings.ambientColor[0] = play->envCtx.lightSettings.ambientColor[1] =
                    play->envCtx.lightSettings.ambientColor[2] = 250;
                Camera_AddQuake(&play->mainCamera, 2, 11, 8);
                thisx->params = ENBOM_1;
                this->timer = 10;
                thisx->flags |= (0x100000 | 0x20);
                this->actionFunc = func_808715B8;
                if (this->isPowderKeg) {
                    gSaveContext.powderKegTimer = 0;
                    Actor_PlaySfxAtPos(thisx, NA_SE_IT_BIG_BOMB_EXPLOSION);
                } else {
                    Actor_PlaySfxAtPos(thisx, NA_SE_IT_BOMB_EXPLOSION);
                }
            }
        }

        Actor_SetFocus(thisx, 20.0f);

        if (thisx->params <= ENBOM_0) {
            Collider_UpdateCylinder(thisx, &this->collider1);
            if (!Actor_HasParent(thisx, play) && (this->unk_1F8 != 0)) {
                CollisionCheck_SetOC(play, &play->colChkCtx, &this->collider1.base);
            }
            CollisionCheck_SetAC(play, &play->colChkCtx, &this->collider1.base);
        }

        if ((enBomScales[this->isPowderKeg] <= thisx->scale.x) && (thisx->params != ENBOM_1)) {
            if (thisx->depthInWater >= 20.0f) {
                Vec3f sp54;

                sp54.x = thisx->world.pos.x;
                sp54.y = thisx->world.pos.y + thisx->depthInWater;
                sp54.z = thisx->world.pos.z;
                EffectSsGRipple_Spawn(play, &sp54, 70, 500, 0);
                EffectSsGRipple_Spawn(play, &sp54, 70, 500, 10);
                sp54.y += 10.0f;
                EffectSsGSplash_Spawn(play, &sp54, NULL, NULL, 1, 500);
                Actor_Spawn(&play->actorCtx, play, ACTOR_EN_CLEAR_TAG, sp54.x, sp54.y, sp54.z, 0, 0, 1, 200);
                SoundSource_PlaySfxAtFixedWorldPos(play, &thisx->world.pos, 30, NA_SE_IT_BOMB_UNEXPLOSION);
                this->unk_1F4 = 0.0f;
                thisx->velocity.y = (KREG(83) * 0.1f) + -2.0f;
                thisx->gravity = (KREG(84) * 0.1f) + -0.5f;
                this->unk_1FC = KREG(81) + 10;
            } else if (thisx->bgCheckFlags & 0x40) {
                thisx->bgCheckFlags &= ~0x40;
                Actor_PlaySfxAtPos(thisx, NA_SE_EV_BOMB_DROP_WATER);
            }
        }
    }
}

static Vec3f D_80872EE0 = { 0.0f, 800.0f, 0.0f };
static Vec3f D_80872EEC = { -750.0f, 0.0f, 0.0f };
static Vec3f D_80872EF8 = { -800.0f, 0.0f, 0.0f };
static Vec3f D_80872F04 = { 0.0f, 0.0f, 0.0f };

#include "overlays/ovl_En_Bom/ovl_En_Bom.c"

void EnBom_Draw(Actor* thisx, PlayState* play) {
    s32 pad;
    EnBom* this = THIS;

    OPEN_DISPS(play->state.gfxCtx);

    if (this->actor.params == ENBOM_0) {
        func_8012C28C(play->state.gfxCtx);

        Collider_UpdateSpheres(0, &this->collider2);

        if (!this->isPowderKeg) {
            func_800B8050(&this->actor, play, 0);
            Matrix_MultVec3f(&D_80872EE0, &this->actor.home.pos);

            gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(play->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
            gSPDisplayList(POLY_OPA_DISP++, gameplay_keep_DL_015FA0);

            Matrix_ReplaceRotation(&play->billboardMtxF);
            Matrix_RotateXS(0x4000, MTXMODE_APPLY);

            gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(play->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
            gDPPipeSync(POLY_OPA_DISP++);
            gDPSetEnvColor(POLY_OPA_DISP++, (s8)this->unk_1F4, 0, 40, 255);
            gDPSetPrimColor(POLY_OPA_DISP++, 0, 0, (s8)this->unk_1F4, 0, 40, 255);
            gSPDisplayList(POLY_OPA_DISP++, gameplay_keep_DL_015DB0);
        } else {
            Vec3f sp58;
            Vec3f sp4C;

            if (this->unk_1FA != 0) {
                s16 sp4A = this->actor.world.rot.y - this->actor.shape.rot.y;
                f32 sp44 = (1000.0f / Math_CosS(ABS_ALT((s16)(this->unk_1FA % 10922)) - 0x1555)) + -1000.0f;

                Matrix_RotateYS(sp4A, MTXMODE_APPLY);
                Matrix_Translate(0.0f, sp44, 0.0f, MTXMODE_APPLY);
                Matrix_RotateXS(this->unk_1FA, MTXMODE_APPLY);
                Matrix_RotateYS(-sp4A, MTXMODE_APPLY);
            }

            Matrix_MultVec3f(&D_80872EEC, &this->actor.home.pos);
            Matrix_MultVec3f(&D_80872EF8, &sp58);
            Matrix_MultVec3f(&D_80872F04, &sp4C);

            gDPSetEnvColor(POLY_OPA_DISP++, 255, 255, 255, 255);
            gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(play->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
            gSPDisplayList(POLY_OPA_DISP++, gPowderKegBarrelDL);
            gSPDisplayList(POLY_OPA_DISP++, gPowderKegGoronSkullDL);

            func_808726DC(play, &this->actor.home.pos, &sp58, &sp4C, this->timer);
            func_80872BC0(play, this->timer);
        }
    }

    CLOSE_DISPS(play->state.gfxCtx);
}

void func_80872648(PlayState* play, Vec3f* arg1) {
    PowderKegFuseSegment* fuseSegmentPtr = &sPowderKegFuseSegments[0];
    s32 i;

    for (i = 0; i < ARRAY_COUNT(sPowderKegFuseSegments); i++, fuseSegmentPtr++) {
        Math_Vec3f_Copy(&fuseSegmentPtr->pos, arg1);
        Math_Vec3f_Copy(&fuseSegmentPtr->velocity, &gZeroVec3f);
        fuseSegmentPtr->rotY = 0;
        fuseSegmentPtr->rotX = 0x4000;
    }
}

void func_808726DC(PlayState* play, Vec3f* arg1, Vec3f* arg2, Vec3f* arg3, s32 arg4) {
    s32 i;
    f32 temp_f20;
    Vec3f spCC;
    Vec3f spC0;
    PowderKegFuseSegment* fuseSegmentPtr = &sPowderKegFuseSegments[0];
    PowderKegFuseSegment* fuseSegmentPtr2 = &sPowderKegFuseSegments[1];
    f32 temp_f26 = Math_Vec3f_DistXYZ(arg3, arg1);
    s32 spB0;
    f32 temp_f2;
    f32 distXZ;

    Math_Vec3f_Copy(&fuseSegmentPtr->pos, arg1);
    Math_Vec3f_Diff(arg2, arg1, &spCC);

    fuseSegmentPtr->rotY = Math_FAtan2F(spCC.z, spCC.x);
    distXZ = sqrtf(SQXZ(spCC));
    fuseSegmentPtr->rotX = Math_FAtan2F(distXZ, spCC.y);

    spB0 = (arg4 / 240) + 1;

    for (i = 0; i < spB0; i++, fuseSegmentPtr++, fuseSegmentPtr2++, arg4 -= 240) {
        f32 phi_f22;
        CollisionPoly* spA0;
        s32 sp9C;
        Vec3f sp90;

        if (arg4 >= 240) {
            phi_f22 = 8.0f;
        } else {
            phi_f22 = (arg4 % 240) * (1.0f / 240) * 8.0f;
        }

        Math_Vec3f_Sum(&fuseSegmentPtr2->pos, &fuseSegmentPtr2->velocity, &fuseSegmentPtr2->pos);
        temp_f20 = Math_Vec3f_DistXYZAndStoreDiff(arg3, &fuseSegmentPtr2->pos, &spCC);
        if (temp_f20 < temp_f26) {
            if (temp_f20 == 0.0f) {
                spCC.x = 0.0f;
                spCC.y = temp_f26;
                spCC.z = 0.0f;
            } else {
                temp_f20 = temp_f26 / temp_f20;
                spCC.x *= temp_f20;
                spCC.y *= temp_f20;
                spCC.z *= temp_f20;
            }
            Math_Vec3f_Sum(arg3, &spCC, &fuseSegmentPtr2->pos);
        }

        if (Math_Vec3f_DistXYZAndStoreDiff(&fuseSegmentPtr->pos, &fuseSegmentPtr2->pos, &spCC) == 0.0f) {
            spCC.x = 0.0f;
            spCC.y = phi_f22;
            spCC.z = 0.0f;
        }

        fuseSegmentPtr2->rotY = Math_FAtan2F(spCC.z, spCC.x);
        distXZ = sqrtf(SQXZ(spCC));
        fuseSegmentPtr2->rotX = Math_FAtan2F(distXZ, spCC.y);

        fuseSegmentPtr2->rotY =
            (s16)CLAMP(BINANG_SUB(fuseSegmentPtr2->rotY, fuseSegmentPtr->rotY), -8000, 8000) + fuseSegmentPtr->rotY;
        fuseSegmentPtr2->rotX =
            (s16)CLAMP(BINANG_SUB(fuseSegmentPtr2->rotX, fuseSegmentPtr->rotX), -8000, 8000) + fuseSegmentPtr->rotX;

        temp_f20 = Math_CosS(fuseSegmentPtr2->rotX) * phi_f22;
        spC0.x = Math_SinS(fuseSegmentPtr2->rotY) * temp_f20;
        spC0.z = Math_CosS(fuseSegmentPtr2->rotY) * temp_f20;
        spC0.y = Math_SinS(fuseSegmentPtr2->rotX) * phi_f22;

        Math_Vec3f_Sum(&fuseSegmentPtr->pos, &spC0, &fuseSegmentPtr2->pos);
        Math_Vec3f_Copy(&sp90, &fuseSegmentPtr2->pos);

        sp90.y += 50.0f;

        temp_f2 = BgCheck_EntityRaycastFloor3(&play->colCtx, &spA0, &sp9C, &sp90) - fuseSegmentPtr2->pos.y;
        if (temp_f2 >= 0.0f) {
            spC0.y += temp_f2;
            if (phi_f22 < spC0.y) {
                spC0.y = phi_f22;
                temp_f2 = 0.0f;
            } else {
                temp_f2 = sqrtf(SQ(phi_f22) - SQ(spC0.y));
            }

            if (temp_f20 == 0.0f) {
                spC0.x = temp_f2;
            } else {
                temp_f2 /= temp_f20;
                spC0.x *= temp_f2;
                spC0.z *= temp_f2;
            }

            Math_Vec3f_Sum(&fuseSegmentPtr->pos, &spC0, &fuseSegmentPtr2->pos);
            Math_Vec3f_Copy(&fuseSegmentPtr2->velocity, &gZeroVec3f);
        }

        fuseSegmentPtr2->velocity.y += -1.0f;
        if (fuseSegmentPtr2->velocity.y < -10.0f) {
            fuseSegmentPtr2->velocity.y = -10.0f;
        }
    }

    Math_Vec3f_Copy(arg1, &fuseSegmentPtr->pos);
}

void func_80872BC0(PlayState* play, s32 arg1) {
    s32 temp_s5;
    s32 i;
    PowderKegFuseSegment* fuseSegmentPtr = &sPowderKegFuseSegments[0];
    PowderKegFuseSegment* fuseSegmentPtr2;

    OPEN_DISPS(play->state.gfxCtx);

    Matrix_Translate(fuseSegmentPtr->pos.x, fuseSegmentPtr->pos.y, fuseSegmentPtr->pos.z, MTXMODE_NEW);
    Matrix_RotateZYX(fuseSegmentPtr->rotX, fuseSegmentPtr->rotY, 0, MTXMODE_APPLY);
    Matrix_Scale(0.01f, 0.01f, 0.01f, MTXMODE_APPLY);

    gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(play->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPDisplayList(POLY_OPA_DISP++, gPowderKegFuseMaterialDL);

    temp_s5 = (arg1 / 240) + 1;
    fuseSegmentPtr2 = &sPowderKegFuseSegments[1];

    for (i = 1; i < temp_s5; i++, fuseSegmentPtr2++) {
        Matrix_Translate(fuseSegmentPtr2->pos.x, fuseSegmentPtr2->pos.y, fuseSegmentPtr2->pos.z, MTXMODE_NEW);
        Matrix_RotateZYX(fuseSegmentPtr2->rotX, fuseSegmentPtr2->rotY, 0, MTXMODE_APPLY);
        Matrix_Scale(0.01f, 0.01f, 0.01f, MTXMODE_APPLY);

        gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(play->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);

        if ((i % 2) == 0) {
            gSPDisplayList(POLY_OPA_DISP++, gPowderKegFuseModel1DL);
        } else {
            gSPDisplayList(POLY_OPA_DISP++, gPowderKegFuseModel2DL);
        }
    }

    CLOSE_DISPS(play->state.gfxCtx);
}
