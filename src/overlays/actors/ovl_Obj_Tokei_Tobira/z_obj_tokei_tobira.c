/*
 * File: z_obj_tokei_tobira.c
 * Overlay: ovl_Obj_Tokei_Tobira
 * Description: Clock Tower - Swinging Doors
 */

#include "z_obj_tokei_tobira.h"

#define FLAGS 0x00000000

#define THIS ((ObjTokeiTobira*)thisx)

void ObjTokeiTobira_Init(Actor* thisx, PlayState* play);
void ObjTokeiTobira_Destroy(Actor* thisx, PlayState* play);
void ObjTokeiTobira_Update(Actor* thisx, PlayState* play);
void ObjTokeiTobira_Draw(Actor* thisx, PlayState* play);
void ObjTokeiTobira_StartCutscene(ObjTokeiTobira* this);


ActorInit Obj_Tokei_Tobira_InitVars = {
    ACTOR_OBJ_TOKEI_TOBIRA,
    ACTORCAT_BG,
    FLAGS,
    OBJECT_TOKEI_TOBIRA,
    sizeof(ObjTokeiTobira),
    (ActorFunc)ObjTokeiTobira_Init,
    (ActorFunc)ObjTokeiTobira_Destroy,
    (ActorFunc)ObjTokeiTobira_Update,
    (ActorFunc)ObjTokeiTobira_Draw,
};

// static InitChainEntry sInitChain[] = {
static InitChainEntry D_80ABD750[] = {
    ICHAIN_F32(uncullZoneForward, 4000, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneScale, 300, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneDownward, 300, ICHAIN_CONTINUE),
    ICHAIN_VEC3F_DIV1000(scale, 100, ICHAIN_STOP),
};

Vec3f D_80ABD760 = { 0.0f, 0.0f, 80.0f };
s16 D_80ABD76C[2] = { 0xC000, 0x4000 };
s32 D_80ABD770[2] = { 0x060012B0, 0x06001590 };
f32 D_80ABD778[2] = { 1.0f, -1.0f };
Gfx *D_80ABD780[4] = { (Gfx *)0x06001108, (Gfx *)0x060013E8, NULL, NULL };


//TODO: Deal with the data

/*extern InitChainEntry D_80ABD750;
extern Vec3f D_80ABD760;
extern s16 D_80ABD76C[];
extern s32 D_80ABD770;*/

/**
 *  Object's Initialization
 */
void ObjTokeiTobira_Init(Actor* thisx, PlayState* play) {
    ObjTokeiTobira* this = THIS;
    s32 pad;
    s32 params = this->dyna.actor.params & 1;
    Vec3f objPos; // Object's position

    Actor_ProcessInitChain(&this->dyna.actor, &D_80ABD750);
    DynaPolyActor_Init(&this->dyna, DYNA_TRANSFORM_POS | DYNA_TRANSFORM_ROT_Y);
    DynaPolyActor_LoadMesh(play, &this->dyna, D_80ABD770[params]);

    if (params == 0) {
        Actor_SpawnAsChild(&play->actorCtx, &this->dyna.actor, play, 0x1A2, this->dyna.actor.world.pos.x,
                           this->dyna.actor.world.pos.y, this->dyna.actor.world.pos.z, this->dyna.actor.shape.rot.x,
                           this->dyna.actor.shape.rot.y, this->dyna.actor.shape.rot.z, 1);
    }

    Matrix_RotateYS(D_80ABD76C[params] + this->dyna.actor.shape.rot.y, MTXMODE_NEW);
    Matrix_MultVec3f(&D_80ABD760, &objPos);
    this->dyna.actor.world.pos.x += objPos.x;
    this->dyna.actor.world.pos.y += objPos.y;
    this->dyna.actor.world.pos.z += objPos.z;

    if ((params == 0) && !(CHECK_WEEKEVENTREG(WEEKEVENTREG_59_04)) && (play->sceneId == SCENE_CLOCKTOWER) &&
        (gSaveContext.sceneLayer == 0) && (this->dyna.actor.csId >= 0)) {
        this->dyna.actor.flags |= ACTOR_FLAG_10;
        this->actionFunc = ObjTokeiTobira_StartCutscene;
    }
}

void ObjTokeiTobira_Destroy(Actor* thisx, PlayState* play) {
    ObjTokeiTobira* this = THIS;

    DynaPoly_DeleteBgActor(play, &play->colCtx.dyna, this->dyna.bgId);
}

/**
 * Starts Cutscene (I think)
 * (Originally called "func * _80ABD3B0")
 */
void ObjTokeiTobira_StartCutscene(ObjTokeiTobira* this) {
    if (CutsceneManager_IsNext(this->dyna.actor.csId)) {
        CutsceneManager_StartWithPlayerCs((s16)this->dyna.actor.csId, &this->dyna.actor);
        SET_WEEKEVENTREG(WEEKEVENTREG_59_04);
        this->actionFunc = NULL;
        this->dyna.actor.flags &= ~ACTOR_FLAG_10;
    } else {
        CutsceneManager_Queue((s16)this->dyna.actor.csId);
    }
}

//extern f32 D_80ABD778[];
void ObjTokeiTobira_Update(Actor* thisx, PlayState* play) {
    s32 pad;
    ObjTokeiTobira* this = THIS;
    Player* player = GET_PLAYER(play);
    s32 pad50;
    s32 temp_param = OBJTOKEITOBIRA_GET_TYPE(&this->dyna.actor);
    f32 sp48 = D_80ABD778[temp_param];
    s32 pad44;

    if (player->actor.bgCheckFlags & BGCHECKFLAG_PLAYER_WALL_INTERACT) {
        if (DynaPoly_GetActor(&play->colCtx, player->actor.wallBgId) == &this->dyna) {
            f32 sp40;
            Vec3f sp34;

            Actor_OffsetOfPointInActorCoords(&this->dyna.actor, &sp34, &player->actor.world.pos);
            sp40 = sp34.x * sp48;

            if (sp40 > 20.0f) {
                if (sp34.z > 0.0f) {
                    this->unk160 += (sp40 - 20.0f) * sp48 * (16.0f / 3.0f);
                    this->unk168 = 1;
                    if (this->unk16C <= 0) {
                        Actor_PlaySfx(&this->dyna.actor, NA_SE_OC_WOOD_GATE_OPEN);
                        this->unk16C = 0x50;
                    }
                }

                if (sp40 > 48.0f) {
                    ObjTokeiTobira* tobira;
                    if (temp_param == 0) {
                        tobira = (ObjTokeiTobira*)this->dyna.actor.child;
                    } else {
                        tobira = (ObjTokeiTobira*)this->dyna.actor.parent;
                    }

                    if (tobira != NULL) {
                        tobira->unk168 = 1;
                    }
                }
            }
        }
    } else if (this->unk168 == 1) {
        Vec3f sp24;

        Actor_OffsetOfPointInActorCoords(&this->dyna.actor, &sp24, &player->actor.world.pos);

        if ((sp24.z > 0.0f) && (sp24.z < 30.0f)) {
            this->unk168 = 1;
            this->unk160 += sp48 * 290.0f;
        }
    }

    if (this->unk16C > 0) {
        this->unk16C -= 1;
    }

    this->unk168 = 0;
    this->unk160 *= 0.87f;
    this->unk164 += this->unk160;
    if (this->unk164 * sp48 > 14336.0f) {
        this->unk160 *= 0.1f;
        this->unk164 = 14336.0f * sp48;
    } else if (this->unk164 * sp48 < -1000.0f) {
        this->unk160 *= 0.1f;
        this->unk164 = -1000.0f * sp48;
    }

    this->dyna.actor.shape.rot.y = (s32)this->unk164 + this->dyna.actor.home.rot.y;

    if (this->actionFunc != NULL) {
        this->actionFunc(this);
    }
}

//extern Gfx* D_80ABD780[];

void ObjTokeiTobira_Draw(Actor* thisx, PlayState* play) {
    Gfx_DrawDListOpa(play, D_80ABD780[thisx->params & 1]);
}
