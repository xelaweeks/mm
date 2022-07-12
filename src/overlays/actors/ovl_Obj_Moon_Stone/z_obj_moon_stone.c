/*
 * File: z_obj_moon_stone.c
 * Overlay: ovl_Obj_Moon_Stone
 * Description: Moon's Tear
 */

#include "z_obj_moon_stone.h"
#include "objects/object_gi_reserve00/object_gi_reserve00.h"

#define FLAGS (ACTOR_FLAG_10 | ACTOR_FLAG_100000)

#define THIS ((ObjMoonStone*)thisx)

void ObjMoonStone_Init(Actor* thisx, PlayState* play);
void ObjMoonStone_Destroy(Actor* thisx, PlayState* play);
void ObjMoonStone_Update(Actor* thisx, PlayState* play);
void ObjMoonStone_Draw(Actor* thisx, PlayState* play);

void func_80C0662C(ObjMoonStone* this);
void func_80C06640(ObjMoonStone* this, PlayState* play);
void func_80C066F8(ObjMoonStone* this);
void func_80C0670C(ObjMoonStone* this, PlayState* play);
void func_80C0673C(ObjMoonStone* this);
void func_80C06768(ObjMoonStone* this, PlayState* play);
void func_80C0685C(ObjMoonStone* this);
void func_80C06870(ObjMoonStone* this, PlayState* play);

const ActorInit Obj_Moon_Stone_InitVars = {
    ACTOR_OBJ_MOON_STONE,
    ACTORCAT_PROP,
    FLAGS,
    OBJECT_GI_RESERVE00,
    sizeof(ObjMoonStone),
    (ActorFunc)ObjMoonStone_Init,
    (ActorFunc)ObjMoonStone_Destroy,
    (ActorFunc)ObjMoonStone_Update,
    (ActorFunc)ObjMoonStone_Draw,
};

void ObjMoonStone_Init(Actor* thisx, PlayState* play) {
    ObjMoonStone* this = THIS;

    Actor_SetScale(&this->actor, 0.3f);
    this->unk194 = (this->actor.params & 0xF000) >> 0xC;
    this->actor.targetMode = 0;
    this->actor.shape.yOffset = 25.0f;
    this->actor.focus.pos.y += 10.0f;
    if (this->unk194 == 0) {
        this->actor.colChkInfo.health = 0;
        this->actor.flags |= (ACTOR_FLAG_1 | ACTOR_FLAG_8);
        func_80C0662C(this);
    } else if (!(gSaveContext.save.weekEventReg[74] & 0x40)) {
        if ((gSaveContext.save.weekEventReg[74] & 0x80)) {
            Actor_Spawn(&play->actorCtx, play, 1, this->actor.world.pos.x, this->actor.world.pos.y,
                        this->actor.world.pos.z, 0, 0, 0, -1);
        }
        this->actor.flags &= ~ACTOR_FLAG_1;
        func_80C0673C(this);
    } else {
        Actor_MarkForDeath(&this->actor);
    }
}

void ObjMoonStone_Destroy(Actor* thisx, PlayState* play) {
}

void func_80C0662C(ObjMoonStone* this) {
    this->actionFunc = func_80C06640;
}

void func_80C06640(ObjMoonStone* this, PlayState* play) {
    Player* player = GET_PLAYER(play);
    s16 sp1A = this->actor.yawTowardsPlayer - 0x8000;

    sp1A -= player->actor.shape.rot.y;
    if (Actor_ProcessTalkRequest(&this->actor, &play->state)) {
        this->actor.colChkInfo.health = 1;
        Message_StartTextbox(play, 0x5E3, &this->actor);
        func_80C066F8(this);
    } else {
        s32 phi_v0 = ABS_ALT(sp1A);
        if (phi_v0 < 0x1555) {
            func_800B8614(&this->actor, play, 80.0f);
        }
    }
}

void func_80C066F8(ObjMoonStone* this) {
    this->actionFunc = func_80C0670C;
}

void func_80C0670C(ObjMoonStone* this, PlayState* play) {
    if (Actor_TextboxIsClosing(&this->actor, play)) {
        this->actor.colChkInfo.health = 0;
        func_80C0662C(this);
    }
}

void func_80C0673C(ObjMoonStone* this) {
    if (!(gSaveContext.save.weekEventReg[74] & 0x80)) {
        this->actor.draw = NULL;
    }
    this->actionFunc = func_80C06768;
}

void func_80C06768(ObjMoonStone* this, PlayState* play) {
    if ((gSaveContext.save.weekEventReg[74] & 0x80)) {
        if (this->actor.draw == NULL) {
            this->actor.draw = ObjMoonStone_Draw;
            Actor_Spawn(&play->actorCtx, play, 1, this->actor.world.pos.x, this->actor.world.pos.y,
                        this->actor.world.pos.z, 0, 0, 0, -1);
        }
    }
    if (this->actor.draw) {
        if (Actor_HasParent(&this->actor, play)) {
            this->actor.parent = NULL;
            this->actor.draw = NULL;
            func_80C0685C(this);
        } else if (this->actor.xzDistToPlayer < 25.0f) {
            Actor_PickUp(&this->actor, play, GI_MOON_TEAR, 100.0f, 30.0f);
        }
    }
}

void func_80C0685C(ObjMoonStone* this) {
    this->actionFunc = func_80C06870;
}

void func_80C06870(ObjMoonStone* this, PlayState* play) {
    if (Message_GetState(&play->msgCtx) == 6 && Message_ShouldAdvance(play)) {
        gSaveContext.save.weekEventReg[74] |= 0x40;
        Actor_MarkForDeath(&this->actor);
    }
}

void ObjMoonStone_Update(Actor* thisx, PlayState* play) {
    ObjMoonStone* this = THIS;
    Player* player = GET_PLAYER(play);

    if (!(player->stateFlags1 & 0x10000282)) {
        this->actionFunc(this, play);
    }
}

void ObjMoonStone_Draw(Actor* thisx, PlayState* play) {
    GraphicsContext* gfxCtx = play->state.gfxCtx;

    OPEN_DISPS(play->state.gfxCtx);
    func_8012C28C(play->state.gfxCtx);
    func_8012C2DC(play->state.gfxCtx);
    AnimatedMat_Draw(play, Lib_SegmentedToVirtual(object_gi_reserve00_Matanimheader_001C60));
    gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(play->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPDisplayList(POLY_OPA_DISP++, object_gi_reserve00_DL_000D78);
    Matrix_ReplaceRotation(&play->billboardMtxF);
    gSPMatrix(POLY_XLU_DISP++, Matrix_NewMtx(play->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPDisplayList(POLY_XLU_DISP++, object_gi_reserve00_DL_000C80);
    CLOSE_DISPS(play->state.gfxCtx);
}
