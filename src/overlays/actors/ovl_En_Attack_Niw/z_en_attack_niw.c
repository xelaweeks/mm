/*
 * File: z_en_attack_niw.c
 * Overlay: ovl_En_Attack_Niw
 * Description: Attacking Cucco
 */

#include "z_en_attack_niw.h"
#include "overlays/actors/ovl_En_Niw/z_en_niw.h"

#define FLAGS (ACTOR_FLAG_10)

#define THIS ((EnAttackNiw*)thisx)

void EnAttackNiw_Init(Actor* thisx, GlobalContext* globalCtx);
void EnAttackNiw_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnAttackNiw_Update(Actor* thisx, GlobalContext* globalCtx);
void EnAttackNiw_Draw(Actor* thisx, GlobalContext* globalCtx);

void EnAttackNiw_EnterViewFromOffscreen(EnAttackNiw* this, GlobalContext* globalCtx);
void EnAttackNiw_AimAtPlayer(EnAttackNiw* this, GlobalContext* globalCtx);
void EnAttackNiw_FlyAway(EnAttackNiw* this, GlobalContext* globalCtx);

const ActorInit En_Attack_Niw_InitVars = {
    ACTOR_EN_ATTACK_NIW,
    ACTORCAT_ENEMY,
    FLAGS,
    OBJECT_NIW,
    sizeof(EnAttackNiw),
    (ActorFunc)EnAttackNiw_Init,
    (ActorFunc)EnAttackNiw_Destroy,
    (ActorFunc)EnAttackNiw_Update,
    (ActorFunc)EnAttackNiw_Draw,
};

static InitChainEntry sInitChain[] = {
    ICHAIN_U8(targetMode, 1, ICHAIN_CONTINUE),
    ICHAIN_F32_DIV1000(gravity, -2000, ICHAIN_CONTINUE),
    ICHAIN_F32(targetArrowOffset, 0, ICHAIN_STOP),
};

void EnAttackNiw_Init(Actor* thisx, GlobalContext* globalCtx) {
    EnAttackNiw* this = THIS;

    Actor_ProcessInitChain(&this->actor, sInitChain);
    ActorShape_Init(&this->actor.shape, 0.0f, ActorShadow_DrawCircle, 25.0f);
    SkelAnime_InitFlex(globalCtx, &this->skelAnime, &gNiwSkeleton, &gNiwIdleAnim, this->jointTable, this->morphTable,
                       NIW_LIMB_MAX);

    // probably copy pasted from EnNiw, which has this same code, but AttackNiw has no params
    if (this->actor.params < 0) {
        this->actor.params = 0;
    }

    Actor_SetScale(&this->actor, 0.01f);
    this->actor.gravity = 0.0f;

    this->randomTargetCenterOffset.x = randPlusMinusPoint5Scaled(100.0f);
    this->randomTargetCenterOffset.y = randPlusMinusPoint5Scaled(10.0f);
    this->randomTargetCenterOffset.z = randPlusMinusPoint5Scaled(100.0f);

    Actor_SetScale(&this->actor, 0.01f);
    this->actor.flags &= ~ACTOR_FLAG_1; // Unnecessary: this actor does not start with this flag
    this->actor.shape.rot.y = this->actor.world.rot.y = (Rand_ZeroOne() - 0.5f) * 60000.0f;
    this->actionFunc = EnAttackNiw_EnterViewFromOffscreen;
}

void EnAttackNiw_Destroy(Actor* thisx, GlobalContext* globalCtx) {
    EnAttackNiw* this = THIS;
    EnNiw* parent = (EnNiw*)this->actor.parent;

    if (this->actor.parent != NULL && this->actor.parent->update != NULL) {
        if (parent->attackNiwCount > 0) {
            parent->attackNiwCount--;
        }
    }
}

/**
 * Summary: instead of using SkelAnime animations AttackNiw modifies limbs directly to create animations
 *
 * EnNiw has its own version of this function, probably copy paste since AttackNiw only uses two animationState
 */
void EnAttackNiw_UpdateRotations(EnAttackNiw* this, GlobalContext* globalCtx, s16 animationState) {
    if (this->unkTimer24C == 0) {
        if (animationState == 0) {
            this->targetBodyRotY = 0.0f;
        } else {
            this->targetBodyRotY = -10000.0f;
        }

        this->clearRotYToggleTimer++;
        this->unkTimer24C = 3;
        if ((this->clearRotYToggleTimer % 2) == 0) {
            this->targetBodyRotY = 0.0f;
            if (animationState == 0) {
                this->unkTimer24C = Rand_ZeroFloat(30.0f);
            }
        }
    }

    if (this->unkTimer250 == 0) {
        this->unkToggle28A++;
        this->unkToggle28A &= 1;

        switch (animationState) { // only case 2 and 5 are ever called in AttackNiw
            case 0:
                this->targetLeftWingRotZ = 0.0f;
                this->targetRightWingRotZ = 0.0f;
                break;

            case 1:
                this->unkTimer250 = 3;
                this->targetLeftWingRotZ = 7000.0f;
                this->targetRightWingRotZ = 7000.0f;
                if (this->unkToggle28A == 0) {
                    this->targetLeftWingRotZ = 0.0f;
                    this->targetRightWingRotZ = 0.0f;
                }
                break;

            case 2:
                this->unkTimer250 = 2;
                this->targetLeftWingRotZ = -10000.0f;
                this->targetRightWingRotZ = -10000.0f;
                this->targetLeftWingRotY = 25000.0f;
                this->targetRightWingRotY = 25000.0f;
                this->targetLeftWingRotX = 6000.0f;
                this->targetRightWingRotX = 6000.0f;
                if (this->unkToggle28A == 0) {
                    this->targetRightWingRotY = 8000.0f;
                    this->targetLeftWingRotY = 8000.0f;
                }
                break;

            case 3:
                this->unkTimer250 = 2;
                this->targetRightWingRotY = 10000.0f;
                this->targetLeftWingRotY = 10000.0f;
                if (this->unkToggle28A == 0) {
                    this->targetRightWingRotY = 3000.0f;
                    this->targetLeftWingRotY = 3000.0f;
                }
                break;

            case 4:
                this->unusedTimer24E = 5;
                this->unkTimer24C = this->unusedTimer24E;
                break;

            case 5:
                this->unkTimer250 = 5;
                this->targetRightWingRotY = 14000.0f;
                this->targetLeftWingRotY = 14000.0f;
                if (this->unkToggle28A == 0) {
                    this->targetRightWingRotY = 10000.0f;
                    this->targetLeftWingRotY = 10000.0f;
                }
                break;
        }
    }

    if (this->targetHeadRotZ != this->headRotZ) {
        Math_ApproachF(&this->headRotZ, this->targetHeadRotZ, 0.5f, 4000.0f);
    }

    if (this->targetBodyRotY != this->upperBodyRotY) {
        Math_ApproachF(&this->upperBodyRotY, this->targetBodyRotY, 0.5f, 4000.0f);
    }

    if (this->targetLeftWingRotZ != this->leftWingRotZ) {
        Math_ApproachF(&this->leftWingRotZ, this->targetLeftWingRotZ, 0.8f, 7000.0f);
    }

    if (this->targetLeftWingRotY != this->leftWingRotY) {
        Math_ApproachF(&this->leftWingRotY, this->targetLeftWingRotY, 0.8f, 7000.0f);
    }

    if (this->targetLeftWingRotX != this->leftWingRotX) {
        Math_ApproachF(&this->leftWingRotX, this->targetLeftWingRotX, 0.8f, 7000.0f);
    }

    if (this->targetRightWingRotZ != this->rightWingRotZ) {
        Math_ApproachF(&this->rightWingRotZ, this->targetRightWingRotZ, 0.8f, 7000.0f);
    }

    if (this->targetRightWingRotY != this->rightWingRotY) {
        Math_ApproachF(&this->rightWingRotY, this->targetRightWingRotY, 0.8f, 7000.0f);
    }

    if (this->targetRightWingRotX != this->rightWingRotX) {
        Math_ApproachF(&this->rightWingRotX, this->targetRightWingRotX, 0.8f, 7000.0f);
    }
}

s32 EnAttackNiw_IsOnScreen(EnAttackNiw* this, GlobalContext* globalCtx) {
    s16 posX;
    s16 posY;

    Actor_SetFocus(&this->actor, this->targetHeight);
    Actor_GetScreenPos(globalCtx, &this->actor, &posX, &posY);

    if ((this->actor.projectedPos.z < -20.0f) || (posX < 0) || (posX > SCREEN_WIDTH) || (posY < 0) ||
        (posY > SCREEN_HEIGHT)) {
        return false;
    }
    return true;
}

void EnAttackNiw_EnterViewFromOffscreen(EnAttackNiw* this, GlobalContext* globalCtx) {
    s16 posX;
    s16 posY;
    Vec3f viewOffset;
    Vec3f flightTarget;
    s32 pad;

    this->actor.speedXZ = 10.0f;

    // randomTargetCenterOffset is set in _Init, only needs to be set once
    // but the view is moving, so now we need to re-calculate the spot in space
    viewOffset.x = this->randomTargetCenterOffset.x + globalCtx->view.at.x - globalCtx->view.eye.x;
    viewOffset.y = this->randomTargetCenterOffset.y + globalCtx->view.at.y - globalCtx->view.eye.y;
    viewOffset.z = this->randomTargetCenterOffset.z + globalCtx->view.at.z - globalCtx->view.eye.z;

    // this is the 3D spot in space where the cucco is trying to fly into (until it lands or gets close)
    flightTarget.x = globalCtx->view.at.x + viewOffset.x;
    flightTarget.y = globalCtx->view.at.y + viewOffset.y;
    flightTarget.z = globalCtx->view.at.z + viewOffset.z;

    this->targetRotY = Math_Vec3f_Yaw(&this->actor.world.pos, &flightTarget);
    this->targetRotX = Math_Vec3f_Pitch(&this->actor.world.pos, &flightTarget) * -1.0f;

    Math_SmoothStepToS(&this->actor.world.rot.y, this->targetRotY, 5, this->rotStep, 0);
    Math_SmoothStepToS(&this->actor.world.rot.x, this->targetRotX, 5, this->rotStep, 0);
    Math_ApproachF(&this->rotStep, 5000.0f, 1.0f, 100.0f);

    Actor_SetFocus(&this->actor, this->targetHeight);
    Actor_GetScreenPos(globalCtx, &this->actor, &posX, &posY);

    if (this->actor.bgCheckFlags & 8) { // touching a wall
        this->targetRotY = this->actor.yawTowardsPlayer;
        this->targetRotX = this->actor.world.rot.x - 3000.0f;
        this->hopTimer = 0;
        this->randomAngleChangeTimer = 100;
        this->rotStep = 0.0f;
        this->targetLeftWingRotX = 0.0f;
        this->targetRightWingRotX = 0.0f;
        this->unkTimer250 = this->hopTimer;
        this->unusedTimer24E = this->hopTimer;
        this->unkTimer24C = this->hopTimer;
        this->actor.gravity = -0.2f;
        this->targetHeadRotZ = 0.0f;
        this->actionFunc = EnAttackNiw_AimAtPlayer;
        this->targetXZSpeed = 5.0f;

    } else if (((this->actor.projectedPos.z > 0.0f) && (fabsf(flightTarget.x - this->actor.world.pos.x) < 50.0f) &&
                (fabsf(flightTarget.y - this->actor.world.pos.y) < 50.0f) &&
                (fabsf(flightTarget.z - this->actor.world.pos.z) < 50.0f)) ||
               (this->actor.bgCheckFlags & 1)) { // touching ground or with close distance of target
        // reset state
        this->hopTimer = 0;
        this->unkTimer250 = this->hopTimer;
        this->unusedTimer24E = this->hopTimer;
        this->unkTimer24C = this->hopTimer;
        this->rotStep = 0.0f;
        this->targetRightWingRotX = 0.0f;
        this->targetLeftWingRotX = 0.0f;

        this->targetRotY = this->actor.yawTowardsPlayer; // start turn to face player
        this->targetRotX = this->actor.world.rot.x - 2000.0f; // bank into the turn
        this->actor.gravity = -0.2f; // start gentle decent (no longer flying without gravity)
        this->targetHeadRotZ = 0.0f;
        this->actionFunc = EnAttackNiw_AimAtPlayer;
        this->targetXZSpeed = 5.0f;

    } else { // keep flying at the flightTarget for now
        this->unkTimer24C = 10;
        this->targetBodyRotY = -10000.0f;
        this->targetHeadRotZ = -3000.0f;
        EnAttackNiw_UpdateRotations(this, globalCtx, 2);
    }
}

void EnAttackNiw_AimAtPlayer(EnAttackNiw* this, GlobalContext* globalCtx) {
    if (!EnAttackNiw_IsOnScreen(this, globalCtx)) {
        Actor_MarkForDeath(&this->actor);
        return;
    }

    if (this->actor.bgCheckFlags & 1) { // touching floor
        if (this->hopTimer == 0) {
            this->hopTimer = 3;
            this->actor.velocity.y = 3.5f;
        }

        if (this->actor.gravity != -2.0f) { // first landing
            this->targetRotY = this->actor.yawTowardsPlayer;
            this->unkTimer25A = 50;
            this->randomAngleChangeTimer = 100;
            this->targetRightWingRotY = 14000.0f;
            this->targetLeftWingRotY = 14000.0f;
            this->targetRightWingRotX = 0.0f;
            this->targetLeftWingRotX = 0.0f;
            this->targetRightWingRotZ = 0.0f;
            this->targetLeftWingRotZ = 0.0f;
            this->targetRotX = 0.0f;
            this->actor.gravity = -2.0f;
        }
    }

    if (this->randomAngleChangeTimer == 50) {
        this->targetRotY = randPlusMinusPoint5Scaled(200.0f) + this->actor.yawTowardsPlayer;
    }

    Math_SmoothStepToS(&this->actor.world.rot.y, this->targetRotY, 2, this->rotStep, 0);
    Math_SmoothStepToS(&this->actor.world.rot.x, this->targetRotX, 2, this->rotStep, 0);
    Math_ApproachF(&this->rotStep, 10000.0f, 1.0f, 1000.0f);
    Math_ApproachF(&this->actor.speedXZ, this->targetXZSpeed, 0.9f, 1.0f);

    if (this->actor.gravity == -2.0f && this->unkTimer25A == 0 &&
        (this->actor.bgCheckFlags & 8 || this->randomAngleChangeTimer == 0)) {
        this->targetXZSpeed = 0.0f;
        this->actor.gravity = 0.0f;
        this->rotStep = 0.0f;
        this->targetRotX = this->actor.world.rot.x - 5000.0f;
        this->actionFunc = EnAttackNiw_FlyAway;

    } else if (this->actor.bgCheckFlags & 1) { // touching floor
        EnAttackNiw_UpdateRotations(this, globalCtx, 5);

    } else {
        EnAttackNiw_UpdateRotations(this, globalCtx, 2);
    }
}

void EnAttackNiw_FlyAway(EnAttackNiw* this, GlobalContext* globalCtx) {
    if (!EnAttackNiw_IsOnScreen(this, globalCtx)) {
        Actor_MarkForDeath(&this->actor);
        return;
    }

    Math_SmoothStepToS(&this->actor.world.rot.x, this->targetRotX, 5, this->rotStep, 0);
    Math_ApproachF(&this->rotStep, 5000.0f, 1.0f, 100.0f);
    Math_ApproachF(&this->actor.velocity.y, 5.0f, 0.3f, 1.0f);
    EnAttackNiw_UpdateRotations(this, globalCtx, 2);
}

void EnAttackNiw_Update(Actor* thisx, GlobalContext* globalCtx) {
    EnAttackNiw* this = THIS;
    s32 pad;
    EnNiw* parent;
    Player* player = GET_PLAYER(globalCtx);
    s32 pad2;
    Vec3f splashPos;

    this->unusedCounter284++;

    DECR(this->unkTimer24C);
    DECR(this->unkTimer250);
    DECR(this->hopTimer);
    DECR(this->crySfxTimer);
    DECR(this->flutterSfxTimer);
    DECR(this->randomAngleChangeTimer);
    DECR(this->unkTimer25A);

    this->actor.shape.rot = this->actor.world.rot;
    this->actor.shape.shadowScale = 15.0f;

    this->actionFunc(this, globalCtx);

    Actor_UpdateBgCheckInfo(globalCtx, &this->actor, 20.0f, 20.0f, 60.0f, 0x1D);

    if (this->actionFunc == EnAttackNiw_EnterViewFromOffscreen) {
        Actor_MoveWithoutGravity(&this->actor);
    } else {
        Actor_MoveWithGravity(&this->actor);
    }

    if (this->actor.floorHeight <= BGCHECK_Y_MIN) { // under the world
        Actor_MarkForDeath(&this->actor);

    } else if ((this->actor.bgCheckFlags & 0x20) && // on or below water
               (this->actionFunc != EnAttackNiw_FlyAway)) {
        Math_Vec3f_Copy(&splashPos, &this->actor.world.pos);
        splashPos.y += this->actor.depthInWater;
        EffectSsGSplash_Spawn(globalCtx, &splashPos, NULL, NULL, 0, 400);
        this->rotStep = 0.0f;
        this->actor.gravity = 0.0f;
        this->targetXZSpeed = 0.0f;
        this->targetRotX = this->actor.world.rot.x - 5000.0f;
        this->actionFunc = EnAttackNiw_FlyAway;

    } else {
        f32 viewOffset = 20.0f;

    label:

        if (this->actor.xyzDistToPlayerSq < SQ(viewOffset)) {
            parent = (EnNiw*)this->actor.parent;
            if ((this->actor.parent->update != NULL) && (this->actor.parent != NULL) && (parent != NULL) &&
                (parent->unkAttackNiwTimer == 0) && (player->invincibilityTimer == 0)) {
                // this updates some player values based on what we pass, need player decomp to know what this is doing
                func_800B8D50(globalCtx, &this->actor, 2.0f, this->actor.world.rot.y, 0.0f, 0x10);
                parent->unkAttackNiwTimer = 70;
            }
        }

        if (this->crySfxTimer == 0) {
            this->crySfxTimer = 30;
            Actor_PlaySfxAtPos(&this->actor, NA_SE_EV_CHICKEN_CRY_A);
        }

        if (this->flutterSfxTimer == 0) {
            this->flutterSfxTimer = 7;
            Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_CHICKEN_FLUTTER);
        }
    }
}

s32 EnAttackNiw_OverrideLimbDraw(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3s* rot,
                                 Actor* thisx) {
    EnAttackNiw* this = THIS;

    if (limbIndex == NIW_LIMB_UPPER_BODY) {
        rot->y += (s16)this->upperBodyRotY;
    }

    if (limbIndex == NIW_LIMB_HEAD) {
        rot->z += (s16)this->headRotZ;
    }

    if (limbIndex == NIW_LIMB_RIGHT_WING_ROOT) {
        rot->x += (s16)this->rightWingRotX;
        rot->y += (s16)this->rightWingRotY;
        rot->z += (s16)this->rightWingRotZ;
    }

    if (limbIndex == NIW_LIMB_LEFT_WING_ROOT) {
        rot->x += (s16)this->leftWingRotX;
        rot->y += (s16)this->leftWingRotY;
        rot->z += (s16)this->leftWingRotZ;
    }
    return false;
}

void EnAttackNiw_Draw(Actor* thisx, GlobalContext* globalCtx) {
    EnAttackNiw* this = THIS;

    func_8012C28C(globalCtx->state.gfxCtx);
    SkelAnime_DrawFlexOpa(globalCtx, this->skelAnime.skeleton, this->skelAnime.jointTable, this->skelAnime.dListCount,
                          EnAttackNiw_OverrideLimbDraw, NULL, &this->actor);
}
