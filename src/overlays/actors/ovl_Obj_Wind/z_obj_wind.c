/*
 * File: z_obj_wind.c
 * Overlay: ovl_Obj_Wind
 * Description: Updraft Current (STT) and Water Current (PFInterior)
 */

#include "z_obj_wind.h"
#include "objects/gameplay_keep/gameplay_keep.h"
#include "z64math.h"

#define FLAGS (ACTOR_FLAG_10)

#define THIS ((ObjWind*)thisx)

#define OBJ_WIND_GET_TYPE(thisx) (((thisx)->params >> 7) & 0x1F)
#define OBJ_WIND_GET_SWITCH_FLAG(thisx) ((thisx)->params & 0x7F)

void ObjWind_Init(Actor* thisx, PlayState* play);
void ObjWind_Destroy(Actor* thisx, PlayState* play);
void ObjWind_Update(Actor* thisx, PlayState* play);
void ObjWind_Draw(Actor* thisx, PlayState* play);

ActorInit Obj_Wind_InitVars = {
    ACTOR_OBJ_WIND,
    ACTORCAT_ITEMACTION,
    FLAGS,
    GAMEPLAY_KEEP,
    sizeof(ObjWind),
    (ActorFunc)ObjWind_Init,
    (ActorFunc)ObjWind_Destroy,
    (ActorFunc)ObjWind_Update,
    (ActorFunc)ObjWind_Draw,
};

static InitChainEntry sInitChain[] = {
    ICHAIN_F32(uncullZoneForward, 4000, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneScale, 4000, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneDownward, 4000, ICHAIN_STOP),
};

void ObjWind_Init(Actor* thisx, PlayState* play) {
    ObjWind* this = (ObjWind*)thisx;
    s32 pad;
    WaterBox* waterbox;
    f32 ySurface;

    Actor_ProcessInitChain(&this->actor, sInitChain);
    if (WaterBox_GetSurface1(play, &play->colCtx, this->actor.world.pos.x, this->actor.world.pos.z, &ySurface,
                             &waterbox) &&
        (this->actor.world.pos.y < ySurface)) {
        this->isUnderWater = 1;
    }
}

void ObjWind_Destroy(Actor* thisx, PlayState* play) {
}

typedef struct ObjWindStruct {
    /* 0x0 */ s16 unk_0;
    /* 0x2 */ s16 unk_2;
    /* 0x4 */ s16 unk_4;
    /* 0x6 */ s16 unk_6;
    /* 0x8 */ s16 unk_8;
} ObjWindStruct;

static ObjWindStruct D_80B2448C[] = {
    { 530, 90, 3000, 2000, 0 },   { 1120, 100, 2000, 1000, 0 }, { 620, 100, 2000, 1000, 0 },
    { 1620, 100, 2000, 1000, 0 }, { 400, 100, 2000, 1000, 0 },  { 400, 100, 2000, 1000, 0 },
    { 400, 100, 2000, 1000, 0 },  { 400, 100, 2000, 1000, 0 },  { 400, 100, 2000, 1000, 0 },
    { 400, 100, 2000, 1000, 0 },  { 400, 100, 2000, 1000, 0 },  { 400, 100, 2000, 1000, 0 },
    { 400, 100, 2000, 1000, 0 },  { 400, 100, 2000, 1000, 0 },  { 400, 100, 2000, 1000, 0 },
    { 400, 100, 2000, 1000, 0 },  { 400, 100, 2000, 1000, 0 },  { 400, 100, 2000, 1000, 0 },
    { 400, 100, 2000, 1000, 0 },  { 400, 100, 2000, 1000, 0 },  { 400, 100, 2000, 1000, 0 },
    { 400, 100, 2000, 1000, 0 },  { 400, 100, 2000, 1000, 0 },  { 400, 100, 2000, 1000, 0 },
    { 400, 100, 2000, 1000, 0 },  { 400, 100, 2000, 1000, 0 },  { 400, 100, 2000, 1000, 0 },
    { 400, 100, 2000, 1000, 0 },  { 600, 120, 3000, 2000, 0 },  { 500, 80, 3000, 2000, 0 },
    { 400, 60, 2000, 2000, 0 },   { 470, 70, 2000, 1000, 0 },
};

static s32 D_80B245CC = -1;

void ObjWind_Update(Actor* thisx, PlayState* play) {
    ObjWind* this = (ObjWind*)thisx;
    ObjWindStruct* entry = &D_80B2448C[OBJ_WIND_GET_TYPE(thisx)];
    Player* player;
    f32 cosYTimesX;
    f32 cosX;
    f32 sinYTimesX;
    Vec3f posCopy;
    Vec3f nearestPoint;
    Vec3f sp54;
    f32 dist;
    f32 distToNearestPoint;

    if (D_80B245CC != DREG(85)) {
        if ((DREG(85) >= 0) && (DREG(85) < ARRAY_COUNT(D_80B2448C))) {
            DREG(80) = D_80B2448C[DREG(85)].unk_0;
            DREG(81) = D_80B2448C[DREG(85)].unk_2;
            DREG(82) = D_80B2448C[DREG(85)].unk_4;
            DREG(83) = D_80B2448C[DREG(85)].unk_6;
            DREG(84) = D_80B2448C[DREG(85)].unk_8;
            D_80B245CC = DREG(85);
        }
    } else {
        D_80B2448C[DREG(85)].unk_0 = DREG(80);
        D_80B2448C[DREG(85)].unk_2 = DREG(81);
        D_80B2448C[DREG(85)].unk_4 = DREG(82);
        D_80B2448C[DREG(85)].unk_6 = DREG(83);
        D_80B2448C[DREG(85)].unk_8 = DREG(84);
    }
    if (OBJ_WIND_GET_SWITCH_FLAG(thisx) == 0x7F || !Flags_GetSwitch(play, OBJ_WIND_GET_SWITCH_FLAG(thisx))) {
        player = GET_PLAYER(play);
        Math_Vec3f_Copy(&posCopy, &this->actor.world.pos);
        cosX = Math_CosS(this->actor.shape.rot.x);
        dist = Math_SinS(this->actor.shape.rot.x);
        sinYTimesX = Math_SinS(this->actor.shape.rot.y) * dist;
        cosYTimesX = Math_CosS(this->actor.shape.rot.y) * dist;
        distToNearestPoint = func_80179A44(&posCopy, &player->actor.world, &nearestPoint);
        if ((distToNearestPoint >= 0.0f) && (distToNearestPoint < entry->unk_0)) {
            dist = Math_Vec3f_DistXYZAndStoreDiff(&player->actor.world.pos, &nearestPoint, &sp54);
            if (dist < entry->unk_2) {
                f32 var_fa0;
                f32 windSpeedXZ = 1.0f;
                f32 sp40;
                f32 temp_ft0;
                f32 windSpeedX;
                f32 windSpeedY;
                f32 windSpeedZ;

                var_fa0 = 1.0f - distToNearestPoint / entry->unk_0;
                sp40 = ((f32)entry->unk_4 / 100.0f) *
                       ((var_fa0 * (1.0f - dist / entry->unk_2)) + ((f32)entry->unk_8 / 100.0f));
                if (0.8f < distToNearestPoint / entry->unk_0) {
                    var_fa0 = windSpeedXZ - 1.0f;
                }
                temp_ft0 = ((f32)entry->unk_6 / 100.0f) * (dist / entry->unk_2 * var_fa0);
                if (dist != 0.0f) {
                    // FAKE:
                    if (1) {}
                    dist = 1.0f / dist;
                }
                temp_ft0 *= dist;
                windSpeedX = (sinYTimesX * sp40) + (sp54.x * temp_ft0);
                windSpeedY = (cosX * sp40) + (sp54.y * temp_ft0);
                windSpeedZ = (cosYTimesX * sp40) + (sp54.z * temp_ft0);
                player->windSpeed = sqrtf(SQ(windSpeedX) + SQ(windSpeedY) + SQ(windSpeedZ));
                player->windAngleY = Math_Atan2S_XY(windSpeedZ, windSpeedX);

                windSpeedXZ = sqrtf(SQ(windSpeedX) + SQ(windSpeedZ));
                player->windAngleX = Math_Atan2S_XY(windSpeedXZ, windSpeedY);
            }
        }
    }
    this->actor.scale.x = (f32)entry->unk_2 / 50.0f;
    this->actor.scale.z = (f32)entry->unk_2 / 50.0f;
    this->actor.scale.y = (f32)entry->unk_0 / 400.0f;
}

void ObjWind_Draw(Actor* thisx, PlayState* play) {
    ObjWind* this = (ObjWind*)thisx;

    OPEN_DISPS(play->state.gfxCtx);

    Gfx_SetupDL25_Xlu(play->state.gfxCtx);
    AnimatedMat_Draw(play, Lib_SegmentedToVirtual(&gameplay_keep_Matanimheader_07F218));
    gSPMatrix(POLY_XLU_DISP++, Matrix_NewMtx(play->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPDisplayList(POLY_XLU_DISP++, gameplay_keep_DL_07E8C0);

    CLOSE_DISPS(play->state.gfxCtx);
}
