/*
 * File: z_dm_zl.c
 * Overlay: ovl_Dm_Zl
 * Description: Child Zelda (Re-learning Song of Time cutscene)
 */

#include "z_dm_zl.h"

#define FLAGS (ACTOR_FLAG_10)

#define THIS ((DmZl*)thisx)

void DmZl_Init(Actor* thisx, GlobalContext* globalCtx);
void DmZl_Destroy(Actor* thisx, GlobalContext* globalCtx);
void DmZl_Update(Actor* thisx, GlobalContext* globalCtx);
void DmZl_Draw(Actor* thisx, GlobalContext* globalCtx);

void DmZl_DoNothing(DmZl* this, GlobalContext* globalCtx);

const ActorInit Dm_Zl_InitVars = {
    ACTOR_DM_ZL,
    ACTORCAT_ITEMACTION,
    FLAGS,
    OBJECT_ZL4,
    sizeof(DmZl),
    (ActorFunc)DmZl_Init,
    (ActorFunc)DmZl_Destroy,
    (ActorFunc)DmZl_Update,
    (ActorFunc)DmZl_Draw,
};

static AnimationInfo sAnimations[] = {
    { &gDmZl4FacingAwayHandsOverEmblemLoop, 1.0f, 0.0f, -1.0f, ANIMMODE_LOOP, -10.0f },
    { &gDmZl4TurningAround2Anim, 1.0f, 0.0f, -1.0f, ANIMMODE_ONCE, -10.0f },
    { &gDmZl4HandsOverEmblemLoopAnim, 1.0f, 0.0f, -1.0f, ANIMMODE_LOOP, -10.0f },
    { &gDmZl4GivingItemStartAnim, 1.0f, 0.0f, -1.0f, ANIMMODE_ONCE, -10.0f },
    { &gDmZl4GivingItemLoopAnim, 1.0f, 0.0f, -1.0f, ANIMMODE_LOOP, -10.0f },
    { &gDmZl4RaisingOcarinaToPlayAnim, 1.0f, 0.0f, -1.0f, ANIMMODE_ONCE, -10.0f },
    { &gDmZl4PlayingOcarinaAnim, 1.0f, 0.0f, -1.0f, ANIMMODE_LOOP, -10.0f },
};

typedef enum {
    /* 0 */ ZELDA_ANIM_FACING_AWAY,
    /* 1 */ ZELDA_ANIM_TURNING_TOWARD_PLAYER,
    /* 2 */ ZELDA_ANIM_FACING_PLAYER,
    /* 3 */ ZELDA_ANIM_GIVING_OCARINA_START,
    /* 4 */ ZELDA_ANIM_GIVING_OCARINA,
    /* 5 */ ZELDA_ANIM_PLAYING_OCARINA_START,
    /* 6 */ ZELDA_ANIM_PLAYING_OCARINA,
    /* 7 */ ZELDA_ANIM_MAX,
} DmZlAnimations;

static TexturePtr sMouthTextures[] = {
    gZl4MouthNeutralTex,
    gZl4MouthOpenSmilingTex,
    gZl4MouthFrowningTex,
    gZl4MouthOpenTex,
};

typedef enum {
    /* 0 */ ZELDA_MOUTH_NEUTRAL,
    /* 1 */ ZELDA_MOUTH_SMILING,
    /* 2 */ ZELDA_MOUTH_FROWNING,
    /* 3 */ ZELDA_MOUTH_OPEN,
} DmZlMouthTextures;

static TexturePtr sEyeTextures[] = {
    gDmZl4EyeOpenNormalTex,
    gDmZl4EyeHalfTex,
    gDmZl4EyeClosedTex,
    gDmZl4EyeWideTex,
    gDmZl4EyeHappyTex,
    gDmZl4EyeOpenLookingLeftTex,
    gDmZl4EyeOpenLookingRightTex,
};

typedef enum {
    /* 0 */ ZELDA_EYE_OPEN_NORMAL,
    /* 1 */ ZELDA_EYE_BLINKING,
    /* 2 */ ZELDA_EYE_CLOSED,
    /* 3 */ ZELDA_EYE_WIDE,
    /* 4 */ ZELDA_EYE_HAPPY,
    /* 5 */ ZELDA_EYE_OPEN_LOOKING_LEFT,
    /* 6 */ ZELDA_EYE_OPEN_LOOKING_RIGHT,
} DmZlEyeTextures;

// Unused in MM
typedef enum {
    /* 0 */ ZELDA_EYE_STATE_NORMAL,
    /* 1 */ ZELDA_EYE_STATE_CLOSED,
    /* 2 */ ZELDA_EYE_STATE_LOOKING_LEFT,
    /* 3 */ ZELDA_EYE_STATE_LOOKING_RIGHT,
    /* 4 */ ZELDA_EYE_STATE_WIDE,
    /* 5 */ ZELDA_EYE_STATE_HAPPY,
    /* 6 */ ZELDA_EYE_STATE_CLOSED2,
} DmZlEyeStates;

/**
 * This function is always called with unusedExtraOffset = 0.
 */
void DmZl_ChangeAnimation(SkelAnime* skelAnime, AnimationInfo animation[], u16 unusedExtraOffset) {
    f32 endFrame;

    animation += unusedExtraOffset;
    endFrame = (animation->frameCount < 0.0f) ? Animation_GetLastFrame(animation->animation) : animation->frameCount;

    Animation_Change(skelAnime, animation->animation, animation->playSpeed, animation->startFrame, endFrame,
                     animation->mode, animation->morphFrames);
}

void DmZl_Init(Actor* thisx, GlobalContext* globalCtx) {
    s32 pad;
    DmZl* this = THIS;

    this->animationIndex = ZELDA_ANIM_FACING_AWAY;
    this->unk_2BA = 0;
    this->actor.targetArrowOffset = 1000.0f;
    ActorShape_Init(&this->actor.shape, 0.0f, ActorShadow_DrawCircle, 24.0f);
    // these three set to NULL should mean they are dynamically allocated
    SkelAnime_InitFlex(globalCtx, &this->skelAnime, &gZl4Skeleton, NULL, NULL, NULL, 0);
    DmZl_ChangeAnimation(&this->skelAnime, &sAnimations[this->animationIndex], 0);
    Actor_SetScale(&this->actor, 0.01f);
    this->actionFunc = DmZl_DoNothing;
}

void DmZl_Destroy(Actor* thisx, GlobalContext* globalCtx) {
}

void DmZl_DoNothing(DmZl* this, GlobalContext* globalCtx) {
}

void DmZl_UpdateCutscene(DmZl* this, GlobalContext* globalCtx) {
    s32 actionIndex;

    if (Cutscene_CheckActorAction(globalCtx, 0x66)) {
        actionIndex = Cutscene_GetActorActionIndex(globalCtx, 0x66);
        if (globalCtx->csCtx.frames == globalCtx->csCtx.actorActions[actionIndex]->startFrame) {
            s16 nextAnimationIndex = ZELDA_ANIM_FACING_AWAY;

            switch (globalCtx->csCtx.actorActions[actionIndex]->action) {
                default:
                case 1:
                    break;
                case 2:
                    nextAnimationIndex = ZELDA_ANIM_TURNING_TOWARD_PLAYER;
                    break;
                case 3:
                    nextAnimationIndex = ZELDA_ANIM_GIVING_OCARINA_START;
                    break;
                case 4:
                    nextAnimationIndex = ZELDA_ANIM_PLAYING_OCARINA_START;
                    break;
            }

            if (nextAnimationIndex != this->animationIndex) {
                this->animationIndex = nextAnimationIndex;
                DmZl_ChangeAnimation(&this->skelAnime, &sAnimations[this->animationIndex], 0);
            }
        }

        Cutscene_ActorTranslateAndYaw(&this->actor, globalCtx, actionIndex);
    }

    if (Animation_OnFrame(&this->skelAnime, this->skelAnime.endFrame)) {
        actionIndex = this->animationIndex;

        if ((actionIndex == ZELDA_ANIM_TURNING_TOWARD_PLAYER) || (actionIndex == ZELDA_ANIM_GIVING_OCARINA_START) ||
            (actionIndex == ZELDA_ANIM_PLAYING_OCARINA_START)) {
            // these animations don't loop at the end, they lead into the next animation
            this->animationIndex++;
            DmZl_ChangeAnimation(&this->skelAnime, &sAnimations[this->animationIndex], 0);
        }
    }
}

/**
 * Updates the eye blinking and state, and mouth textures.
 *  (Copy-Paste from OoT, Unused in MM)
 */
void DmZl_UpdateFace(DmZl* this) {
    if (this->blinkTimer > 0) {
        this->blinkTimer--;
    } else {
        this->blinkTimer = 0;
    }

    if (this->blinkTimer < 3) {
        this->eyeTextureIndexRight = this->blinkTimer;
        this->eyeTextureIndexLeft = this->blinkTimer;
    }

    switch (this->nextEyeState) {
        case ZELDA_EYE_STATE_NORMAL:
            if (this->blinkTimer == 0) {
                this->blinkTimer = Rand_S16Offset(30, 30);
            }
            break;
        case ZELDA_EYE_STATE_CLOSED:
            if (this->blinkTimer == 0) {
                this->eyeTextureIndexLeft = this->eyeTextureIndexRight = ZELDA_EYE_CLOSED;
            }
            break;
        case ZELDA_EYE_STATE_LOOKING_LEFT:
            if (this->blinkTimer == 0) {
                this->eyeTextureIndexLeft = ZELDA_EYE_OPEN_LOOKING_LEFT;
                this->eyeTextureIndexRight = ZELDA_EYE_OPEN_LOOKING_RIGHT;
            }
            break;
        case ZELDA_EYE_STATE_LOOKING_RIGHT:
            if (this->blinkTimer == 0) {
                this->eyeTextureIndexLeft = ZELDA_EYE_OPEN_LOOKING_RIGHT;
                this->eyeTextureIndexRight = ZELDA_EYE_OPEN_LOOKING_LEFT;
            }
            break;
        case ZELDA_EYE_STATE_WIDE:
            if (this->blinkTimer == 0) {
                this->eyeTextureIndexLeft = this->eyeTextureIndexRight = ZELDA_EYE_WIDE;
            }
            break;
        case ZELDA_EYE_STATE_HAPPY:
            if (this->blinkTimer == 0) {
                this->eyeTextureIndexLeft = this->eyeTextureIndexRight = ZELDA_EYE_HAPPY;
            }
            break;
        case ZELDA_EYE_STATE_CLOSED2:
            if (this->blinkTimer >= 3) {
                this->blinkTimer = 0;
            }
            break;
    }

    switch (this->nextMouthState) {
        default:
            this->mouthTextureIndex = ZELDA_MOUTH_NEUTRAL;
            break;
        case ZELDA_MOUTH_SMILING:
            this->mouthTextureIndex = ZELDA_MOUTH_SMILING;
            break;
        case ZELDA_MOUTH_FROWNING:
            this->mouthTextureIndex = ZELDA_MOUTH_FROWNING;
            break;
        case ZELDA_MOUTH_OPEN:
            this->mouthTextureIndex = ZELDA_MOUTH_OPEN;
            break;
    }

    if (this->animationIndex == ZELDA_ANIM_PLAYING_OCARINA) {
        this->eyeTextureIndexLeft = this->eyeTextureIndexRight = ZELDA_EYE_CLOSED;
    }
}

void DmZl_Update(Actor* thisx, GlobalContext* globalCtx) {
    DmZl* this = THIS;

    DmZl_UpdateFace(this);
    SkelAnime_Update(&this->skelAnime);
    DmZl_UpdateCutscene(this, globalCtx);
    this->actionFunc(this, globalCtx);
}

s32 DmZl_OverrideLimbDraw(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3s* rot, Actor* thisx) {
    return false;
}

void DmZl_PostLimbDraw(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3s* rot, Actor* thisx) {
    DmZl* this = THIS;

    if (limbIndex == ZL4_LIMB_RIGHT_HAND) {
        if ((this->animationIndex >= ZELDA_ANIM_GIVING_OCARINA_START) &&
            (this->animationIndex <= ZELDA_ANIM_PLAYING_OCARINA)) {
            OPEN_DISPS(globalCtx->state.gfxCtx);

            gSPDisplayList(POLY_OPA_DISP++, gDmZl4OcarinaDL);

            CLOSE_DISPS(globalCtx->state.gfxCtx);
        }
    }
}

void DmZl_Draw(Actor* thisx, GlobalContext* globalCtx) {
    DmZl* this = THIS;

    OPEN_DISPS(globalCtx->state.gfxCtx);

    gSPSegment(POLY_OPA_DISP++, 0x08, Lib_SegmentedToVirtual(sEyeTextures[this->eyeTextureIndexRight]));

    gSPSegment(POLY_OPA_DISP++, 0x09, Lib_SegmentedToVirtual(sEyeTextures[this->eyeTextureIndexLeft]));

    gSPSegment(POLY_OPA_DISP++, 0x0A, Lib_SegmentedToVirtual(sMouthTextures[this->mouthTextureIndex]));

    func_8012C28C(globalCtx->state.gfxCtx);
    SkelAnime_DrawFlexOpa(globalCtx, this->skelAnime.skeleton, this->skelAnime.jointTable, this->skelAnime.dListCount,
                          DmZl_OverrideLimbDraw, DmZl_PostLimbDraw, &this->actor);

    CLOSE_DISPS(globalCtx->state.gfxCtx);
}
