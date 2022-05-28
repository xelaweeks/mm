#ifndef Z64SUBS_H
#define Z64SUBS_H

#include "z64actor.h"
#include "z64scene.h"

#include "code/sub_s/sub_s.h"

extern Vec3f gOneVec3f;

#define SUBS_TIME_PATHING_ORDER 3

typedef enum {
    /* 0 */ SUBS_CUTSCENE_SET_UNK_LINK_FIELDS,
    /* 1 */ SUBS_CUTSCENE_NORMAL,
    /* 2 */ SUBS_CUTSCENE_SET_FLAG
} SubSCutsceneType;

//! @TODO: rename based on func_8013E748 and func_800B8500
typedef s32 (*func_8013E748_VerifyFunc)(struct GlobalContext*, Actor*, void*);

typedef s32 (*VerifyActor)(struct GlobalContext*, Actor*, Actor*, void*);

#define SUBS_SHADOW_TEX_WIDTH 64
#define SUBS_SHADOW_TEX_HEIGHT 64
#define SUBS_SHADOW_TEX_SIZE ((s32)sizeof(u8[SUBS_SHADOW_TEX_HEIGHT][SUBS_SHADOW_TEX_WIDTH]))

typedef struct TurnOptions {
    /* 0x0 */ u16 rotMax; // binary angles
    /* 0x2 */ u16 slowness; // larger for slower rotation, cannot be 0
    /* 0x4 */ u16 rotStepMin; // degrees
    /* 0x6 */ u16 rotStepMax; // degrees
} TurnOptions; // size = 0x8

typedef struct TurnOptionsSet {
    /* 0x00 */ TurnOptions headRotX;
    /* 0x08 */ TurnOptions headRotY;
    /* 0x10 */ TurnOptions torsoRotX;
    /* 0x18 */ TurnOptions torsoRotY;
} TurnOptionsSet; // size = 0x20

#define ACTOR_PATHING_RETURN_TO_START (1 << 0)
#define ACTOR_PATHING_SWITCH_DIRECTION (1 << 1)
#define ACTOR_PATHING_MOVE_BACKWARDS (1 << 3)
#define ACTOR_PATHING_REACHED_POINT_PERMANENT (1 << 4)
#define ACTOR_PATHING_REACHED_END_PERMANENT (1 << 5)
#define ACTOR_PATHING_REACHED_POINT_TEMPORARY (1 << 6)
#define ACTOR_PATHING_REACHED_END_TEMPORARY (1 << 7)

#define ACTOR_PATHING_REACHED_TEMPORARY \
    (ACTOR_PATHING_REACHED_POINT_TEMPORARY | ACTOR_PATHING_REACHED_END_TEMPORARY)
#define ACTOR_PATHING_REACHED_POINT \
    (ACTOR_PATHING_REACHED_POINT_PERMANENT | ACTOR_PATHING_REACHED_POINT_TEMPORARY)
#define ACTOR_PATHING_REACHED_END \
    (ACTOR_PATHING_REACHED_END_PERMANENT | ACTOR_PATHING_REACHED_END_TEMPORARY)

struct ActorPathing;
typedef void (*ActorPathingComputeFunc)(struct GlobalContext*, struct ActorPathing*);
typedef s32 (*ActorPathingUpdateFunc)(struct GlobalContext*, struct ActorPathing*);

typedef struct ActorPathing {
    /* 0x00 */ Path* setupPathList;
    /* 0x04 */ s32 pathIndex;
    /* 0x08 */ Vec3s* points;
    /* 0x0C */ s32 count;
    /* 0x10 */ s32 curPointIndex;
    /* 0x14 */ s32 begPointIndex;
    /* 0x18 */ s32 endPointIndex;
    /* 0x1C */ u8 flags;
    /* 0x1D */ u8 prevFlags;
    /* 0x20 */ Vec3f curPoint;
    /* 0x2C */ Vec3f pointOffset;
    /* 0x38 */ Vec3f prevPoint;
    /* 0x44 */ Vec3f* worldPos;
    /* 0x48 */ Actor* actor;
    /* 0x4C */ f32 distSqToCurPointXZ;
    /* 0x50 */ f32 distSqToCurPoint;
    /* 0x54 */ Vec3s rotToCurPoint;
    /* 0x5C */ ActorPathingComputeFunc computePointInfoFunc;
    /* 0x60 */ ActorPathingUpdateFunc updateActorInfoFunc; // Return true if should setNextPoint, false if the actor should move forward
    /* 0x64 */ ActorPathingUpdateFunc moveFunc; // Return true if should compute and update again
    /* 0x68 */ ActorPathingUpdateFunc setNextPointFunc; // Return true if should compute and update again
} ActorPathing; // size = 0x6C

struct EnDoor* SubS_FindDoor(struct GlobalContext* globalCtx, s32 switchFlag);

Gfx* SubS_DrawTransformFlexLimb(struct GlobalContext* globalCtx, s32 limbIndex, void** skeleton, Vec3s* jointTable, OverrideLimbDraw overrideLimbDraw, PostLimbDraw postLimbDraw, TransformLimbDraw transformLimbDraw, Actor* actor, Mtx** mtx, Gfx* gfx);
Gfx* SubS_DrawTransformFlex(struct GlobalContext* globalCtx, void** skeleton, Vec3s* jointTable, s32 dListCount, OverrideLimbDraw overrideLimbDraw, PostLimbDraw postLimbDraw, TransformLimbDraw transformLimbDraw, Actor* actor, Gfx* gfx);

s32 SubS_InCsMode(struct GlobalContext* globalCtx);

s32 SubS_UpdateLimb(s16 newRotZ, s16 newRotY, Vec3f* pos, Vec3s* rot, s32 stepRot, s32 overrideRot);

void SubS_UpdateFlags(u16* flags, u16 setBits, u16 unsetBits);

void SubS_TimePathing_FillWeightArray(f32 weightArray[], s32 numPoints, s32 len);
s32 SubS_TimePathing_ComputeProgress(f32* progress, s32 timeElapsed, s32 waypointTime, s32 totalTime, s32 pathCount, s32 numPoints, f32 weightArray[]);
void SubS_TimePathing_ComputeWeights(s32 numPoints, f32 progress, s32 waypoint, f32 weightArray[], f32 weights[]);
void SubS_TimePathing_ComputeTargetPosXZ(f32* x, f32* z, f32 progress, s32 numPoints, s32 waypoint, Vec3s points[], f32 weightArray[]);
s32 SubS_TimePathing_Update(Path* path, f32* progress, s32* timeElapsed, s32 waypointTime, s32 totalTime, s32* waypoint, f32 weightArray[], Vec3f* point, s32 timeSpeed);
void SubS_TimePathing_ComputeInitialY(struct GlobalContext* globalCtx, Path* path, s32 waypoint, Vec3f* point);

Path* SubS_GetAdditionalPath(struct GlobalContext* globalCtx, u8 pathIndex, s32 max);

Actor* SubS_FindNearestActor(Actor* actor, struct GlobalContext* globalCtx, u8 actorCategory, s16 actorId);

s32 SubS_ChangeAnimationByInfoS(SkelAnime* skelAnime, AnimationInfoS* animations, s32 index);

s32 SubS_HasReachedPoint(Actor* actor, Path* path, s32 pointIndex);

Path* SubS_GetDayDependentPath(struct GlobalContext* globalCtx, u8 pathIndex, u8 max, s32* startPointIndex);

s32 SubS_WeightPathing_ComputePoint(Path* path, s32 waypoint, Vec3f* point, f32 progress, s32 direction);
s32 SubS_WeightPathing_Move(Actor* actor, Path* path, s32* waypoint, f32* progress, s32 direction, s32 returnStart);

s32 SubS_CopyPointFromPathCheckBounds(Path* path, s32 pointIndex, Vec3f* dst);

s32 func_8013C964(Actor* actor, struct GlobalContext* globalCtx, f32 xzRange, f32 yRange, s32 itemId, s32 type);

void SubS_FillShadowTex(s32 startCol, s32 startRow, u8* tex, s32 size);
void SubS_GenShadowTex(Vec3f bodyPartsPos[], Vec3f* worldPos, u8* tex, f32 tween, u8 bodyPartsNum, u8 sizes[], s8 parentBodyParts[]);
void SubS_DrawShadowTex(Actor* actor, struct GameState* gameState, u8* tex);

s16 SubS_ComputeTurnToPointRot(s16* rot, s16 rotMax, s16 target, f32 slowness, f32 stepMin, f32 stepMax);
s32 SubS_TurnToPoint(Vec3f* point, Vec3f* focusPos, Vec3s* shapeRot, Vec3s* turnTarget, Vec3s* headRot, Vec3s* torsoRot, TurnOptionsSet* options);

s32 SubS_AngleDiffLessEqual(s16 angleA, s16 threshold, s16 angleB);

Path* SubS_GetPathByIndex(struct GlobalContext* globalCtx, s16 pathIndex, s16 max);
s32 SubS_CopyPointFromPath(Path* path, s32 pointIndex, Vec3f* dst);
s16 SubS_GetDistSqAndOrientPoints(Vec3f* vecA, Vec3f* vecB, f32* distSq);
s32 SubS_MoveActorToPoint(Actor* actor, Vec3f* point, s16 rotStep);
s16 SubS_GetDistSqAndOrientPath(Path* path, s32 pointIdx, Vec3f* pos, f32* distSq);

s8 SubS_IsObjectLoaded(s8 index, struct GlobalContext* globalCtx);
s8 SubS_GetObjectIndex(s16 id, struct GlobalContext* globalCtx);

Actor* SubS_FindActor(struct GlobalContext* globalCtx, Actor* actorListStart, u8 actorCategory, s16 actorId);

s32 SubS_FillLimbRotTables(struct GlobalContext* globalCtx, s16* limbRotTableY, s16* limbRotTableZ, s32 numLimbs);

s32 SubS_IsFloorAbove(struct GlobalContext* globalCtx, Vec3f* pos, f32 distAbove);

s32 SubS_CopyPointFromPathList(Path* paths, s32 pathIndex, s32 pointIndex, Vec3f* dst);
u8 SubS_GetPathCountFromPathList(Path* paths, s32 pathIndex);

void SubS_ActorPathing_Init(struct GlobalContext* globalCtx, Vec3f* worldPos, Actor* actor, ActorPathing* actorPath, Path* paths, s32 pathIndex, s32 begPointIndex, s32 endPointIndex, s32 curPointIndex, u8 flags);
s32 SubS_ActorPathing_Update(struct GlobalContext* globalCtx, ActorPathing* actorPath, ActorPathingComputeFunc computePointInfoFunc, ActorPathingUpdateFunc updateActorInfoFunc, ActorPathingUpdateFunc moveFunc, ActorPathingUpdateFunc setNextPointFunc);
void SubS_ActorPathing_ComputePointInfo(struct GlobalContext* globalCtx, ActorPathing* actorPath);
s32 SubS_ActorPathing_MoveWithGravity(struct GlobalContext* globalCtx, ActorPathing* actorPath);
s32 SubS_ActorPathing_MoveWithoutGravityReverse(struct GlobalContext* globalCtx, ActorPathing* actorPath);
s32 SubS_ActorPathing_SetNextPoint(struct GlobalContext* globalCtx, ActorPathing* actorPath);

void SubS_ChangeAnimationBySpeedInfo(SkelAnime* skelAnime, AnimationSpeedInfo* animations, s32 nextIndex, s32* curIndex);

s32 SubS_StartActorCutscene(Actor* actor, s16 nextCutscene, s16 curCutscene, s32 type);
s32 SubS_FillCutscenesList(Actor* actor, s16 cutscenes[], s16 numCutscenes);

void SubS_ConstructPlane(Vec3f* point, Vec3f* unitVec, Vec3s* rot, Plane* plane);
s32 SubS_LineSegVsPlane(Vec3f* point, Vec3s* rot, Vec3f* unitVec, Vec3f* linePointA, Vec3f* linePointB, Vec3f* intersect);

Actor* SubS_FindActorCustom(struct GlobalContext* globalCtx, Actor* actor, Actor* actorListStart, u8 actorCategory, s16 actorId, void* verifyData, VerifyActor verifyActor);

s32 func_8013E748(Actor* actor, struct GlobalContext* globalCtx, f32 xzRange, f32 yRange, s32 exchangeItemId, void* data, func_8013E748_VerifyFunc verifyFunc);
s32 SubS_ActorAndPlayerFaceEachOther(struct GlobalContext* globalCtx, Actor* actor, void* data);
s32 func_8013E8F8(Actor* actor, struct GlobalContext* globalCtx, f32 xzRange, f32 yRange, s32 exhangeItemId, s16 playerYawTol, s16 actorYawTol);

s32 SubS_TurnToPointStep(Vec3f* worldPos, Vec3f* focusPos, s16 shapeYRot, Vec3f* yawTarget, Vec3f* pitchTarget, s16* headZRotStep, s16* headXRotStep, s16* torsoZRotStep, s16* torsoXRotStep, u16 headZRotStepMax, u16 headXRotStepMax, u16 torsoZRotStepMax, u16 torsoXRotStepMax);

#endif
