#include "global.h"

void SkelCurve_Clear(SkelAnimeCurve* skelCurve) {
    skelCurve->limbCount = 0;
    skelCurve->limbList = NULL;
    skelCurve->transUpdIdx = NULL;
    skelCurve->animCurFrame = 0.0f;
    skelCurve->animSpeed = 0.0f;
    skelCurve->animFinalFrame = 0.0f;
    skelCurve->unk0C = 0.0f;
    skelCurve->transforms = NULL;
}

s32 SkelCurve_Init(GlobalContext* globalCtx, SkelAnimeCurve* skelCurve, SkelCurveLimbList* limbListSeg,
                   TransformUpdateIndex* transUpdIdx) {
    SkelCurveLimb** limbs;
    SkelCurveLimbList* limbList = (SkelCurveLimbList*)Lib_SegmentedToVirtual(limbListSeg);

    skelCurve->limbCount = limbList->limbCount;
    skelCurve->limbList = (SkelCurveLimb**)Lib_SegmentedToVirtual(limbList->limbs);

    skelCurve->transforms = ZeldaArena_Malloc(sizeof(*skelCurve->transforms) * skelCurve->limbCount);

    do {
        skelCurve->animCurFrame = 0.0f;
    } while (0);
    return 1;
}

void SkelCurve_Destroy(GlobalContext* globalCtx, SkelAnimeCurve* skelCurve) {
    if (skelCurve->transforms != NULL) {
        ZeldaArena_Free(skelCurve->transforms);
    }
}

void SkelCurve_SetAnim(SkelAnimeCurve* skelCurve, TransformUpdateIndex* transUpdIdx, f32 arg2, f32 animFinalFrame,
                       f32 animCurFrame, f32 animSpeed) {
    skelCurve->unk0C = arg2 - skelCurve->animSpeed;
    skelCurve->animFinalFrame = animFinalFrame;
    skelCurve->animCurFrame = animCurFrame;
    skelCurve->animSpeed = animSpeed;
    skelCurve->transUpdIdx = transUpdIdx;
}

#ifdef NON_MATCHING
/* Should be functionally equivalent, also migrating rodata makes it a lot cleaner */
s32 SkelCurve_Update(GlobalContext* globalCtx, SkelAnimeCurve* skelCurve) {
    s16* transforms;
    u8* transformRefIdx;
    TransformUpdateIndex* transformIndex;
    u16* transformCopyValues;
    s32 i;
    s32 ret = 0;
    s32 k;
    TransformData* transData;
    f32 transformValue;
    s32 j;

    transformIndex = Lib_SegmentedToVirtual(skelCurve->transUpdIdx);
    transformRefIdx = Lib_SegmentedToVirtual(transformIndex->refIndex);
    transData = Lib_SegmentedToVirtual(transformIndex->transformData);
    transformCopyValues = Lib_SegmentedToVirtual(transformIndex->copyValues);
    transforms = (s16*)skelCurve->transforms;

    skelCurve->animCurFrame += skelCurve->animSpeed * (globalCtx->state.framerateDivisor * 0.5f);

    if ((skelCurve->animSpeed >= 0.0f && skelCurve->animCurFrame > skelCurve->animFinalFrame) ||
        (skelCurve->animSpeed < 0.0f && skelCurve->animCurFrame < skelCurve->animFinalFrame)) {
        skelCurve->animCurFrame = skelCurve->animFinalFrame;
        ret = 1;
    }

    for (i = 0; i < skelCurve->limbCount; i++) {
        for (j = 0; j < 3; j++) {
            for (k = 0; k < 3; k++, transformRefIdx++, transforms++) {
                if (*transformRefIdx == 0) {
                    transformValue = *transformCopyValues;
                    *transforms = transformValue;
                    transformCopyValues++;
                } else {
                    transformValue = func_800F2478(skelCurve->animCurFrame, transData, *transformRefIdx);
                    transData += *transformRefIdx;
                    if (j == 0) {
                        *transforms = transformValue * 1024.0f;
                    } else if (j == 1) {
                        *transforms = transformValue * (32768.0f / 180.0f);
                    } else {
                        *transforms = transformValue * 100.0f;
                    }
                }
            }
        }
    }

    return ret;
}
#else
#pragma GLOBAL_ASM("asm/non_matchings/code/z_fcurve_data_skelanime/SkelCurve_Update.s")
#endif

void SkelCurve_DrawLimb(GlobalContext* globalCtx, s32 limbIndex, SkelAnimeCurve* skelCurve,
                        OverrideCurveLimbDraw overrideLimbDraw, PostCurveLimbDraw postLimbDraw, s32 lod, Actor* thisx) {
    SkelCurveLimb* limb = (SkelCurveLimb*)Lib_SegmentedToVirtual(skelCurve->limbList[limbIndex]);

    OPEN_DISPS(globalCtx->state.gfxCtx);

    Matrix_StatePush();

    if (overrideLimbDraw == NULL ||
        (overrideLimbDraw != NULL && overrideLimbDraw(globalCtx, skelCurve, limbIndex, thisx))) {
        Vec3f scale;
        Vec3s rot;
        Vec3f pos;
        Gfx* dList;
        Vec3s* transform = (Vec3s*)&skelCurve->transforms[limbIndex];

        scale.x = transform->x / 1024.0f;
        scale.y = transform->y / 1024.0f;
        scale.z = transform->z / 1024.0f;
        transform++;
        rot.x = transform->x;
        rot.y = transform->y;
        rot.z = transform->z;
        transform++;
        pos.x = transform->x;
        pos.y = transform->y;
        pos.z = transform->z;

        Matrix_JointPosition(&pos, &rot);
        Matrix_Scale(scale.x, scale.y, scale.z, MTXMODE_APPLY);

        if (lod == 0) {
            s32 pad1;

            dList = limb->dList[0];
            if (dList != NULL) {
                gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(globalCtx->state.gfxCtx),
                          G_MTX_LOAD | G_MTX_NOPUSH | G_MTX_MODELVIEW);
                gSPDisplayList(POLY_OPA_DISP++, dList);
            }
        } else if (lod == 1) {
            s32 pad2;

            dList = limb->dList[0];
            if (dList != NULL) {
                gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(globalCtx->state.gfxCtx),
                          G_MTX_LOAD | G_MTX_NOPUSH | G_MTX_MODELVIEW);
                gSPDisplayList(POLY_OPA_DISP++, dList);
            }
            dList = limb->dList[1];
            if (dList != NULL) {
                gSPMatrix(POLY_XLU_DISP++, Matrix_NewMtx(globalCtx->state.gfxCtx),
                          G_MTX_LOAD | G_MTX_NOPUSH | G_MTX_MODELVIEW);
                gSPDisplayList(POLY_XLU_DISP++, dList);
            }
        }
    }

    if (postLimbDraw != NULL) {
        postLimbDraw(globalCtx, skelCurve, limbIndex, thisx);
    }

    if (limb->firstChildIdx != LIMB_DONE) {
        SkelCurve_DrawLimb(globalCtx, limb->firstChildIdx, skelCurve, overrideLimbDraw, postLimbDraw, lod, thisx);
    }

    Matrix_StatePop();

    if (limb->nextLimbIdx != LIMB_DONE) {
        SkelCurve_DrawLimb(globalCtx, limb->nextLimbIdx, skelCurve, overrideLimbDraw, postLimbDraw, lod, thisx);
    }

    CLOSE_DISPS(globalCtx->state.gfxCtx);
}

void SkelCurve_Draw(Actor* actor, GlobalContext* globalCtx, SkelAnimeCurve* skelCurve,
                    OverrideCurveLimbDraw overrideLimbDraw, PostCurveLimbDraw postLimbDraw, s32 lod, Actor* thisx) {
    if (skelCurve->transforms != NULL) {
        SkelCurve_DrawLimb(globalCtx, 0, skelCurve, overrideLimbDraw, postLimbDraw, lod, thisx);
    }
}
