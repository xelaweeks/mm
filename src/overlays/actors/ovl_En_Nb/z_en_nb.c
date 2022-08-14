/*
 * File: z_en_nb.c
 * Overlay: ovl_En_Nb
 * Description: Anju's Grandma
 */

#include "z_en_nb.h"
#include "objects/object_nb/object_nb.h"

#define FLAGS (ACTOR_FLAG_1 | ACTOR_FLAG_8 | ACTOR_FLAG_10 | ACTOR_FLAG_20)

#define THIS ((EnNb*)thisx)

void EnNb_Init(Actor* thisx, PlayState* play);
void EnNb_Destroy(Actor* thisx, PlayState* play);
void EnNb_Update(Actor* thisx, PlayState* play);
void EnNb_Draw(Actor* thisx, PlayState* play);

void EnNb_Wait(EnNb* this, PlayState* play);
void func_80BC0EAC(EnNb* this, PlayState* play);

void func_80BC08E0(EnNb* this, PlayState* play);
void func_80BC0978(EnNb* this, PlayState* play);

s32 func_80BC00AC(EnNb* this, PlayState* play);
s32 func_80BC01DC(EnNb* this, PlayState* play);

static u8 sScheduleScript[] = {
    /* 0x00 */ SCHEDULE_CMD_CHECK_NOT_IN_DAY_S(3, 0x21 - 0x04),
    /* 0x04 */ SCHEDULE_CMD_CHECK_NOT_IN_SCENE_S(SCENE_YADOYA, 0x12 - 0x08),
    /* 0x08 */ SCHEDULE_CMD_CHECK_TIME_RANGE_S( 6,  0, 18,  0, 0x0F - 0x0E),
    /* 0x0E */ SCHEDULE_CMD_RET_NONE(),
    /* 0x0F */ SCHEDULE_CMD_RET_VAL_L(3),
    /* 0x12 */ SCHEDULE_CMD_CHECK_NOT_IN_SCENE_S(SCENE_OMOYA, 0x20 - 0x16),
    /* 0x16 */ SCHEDULE_CMD_CHECK_TIME_RANGE_S(18,  0,  6,  0, 0x1D - 0x1C),
    /* 0x1C */ SCHEDULE_CMD_RET_NONE(),
    /* 0x1D */ SCHEDULE_CMD_RET_VAL_L(4),
    /* 0x20 */ SCHEDULE_CMD_RET_NONE(),
    /* 0x21 */ SCHEDULE_CMD_CHECK_NOT_IN_SCENE_S(SCENE_YADOYA, 0x72 - 0x25),
    /* 0x25 */ SCHEDULE_CMD_CHECK_NOT_IN_DAY_S(1, 0x47 - 0x29),
    /* 0x29 */ SCHEDULE_CMD_CHECK_TIME_RANGE_S( 8,  0, 12,  0, 0x44 - 0x2F),
    /* 0x2F */ SCHEDULE_CMD_CHECK_TIME_RANGE_S(12,  0, 12, 15, 0x41 - 0x35),
    /* 0x35 */ SCHEDULE_CMD_CHECK_TIME_RANGE_S(12, 15, 18,  0, 0x3E - 0x3B),
    /* 0x3B */ SCHEDULE_CMD_RET_VAL_L(3),
    /* 0x3E */ SCHEDULE_CMD_RET_VAL_L(1),
    /* 0x41 */ SCHEDULE_CMD_RET_VAL_L(2),
    /* 0x44 */ SCHEDULE_CMD_RET_VAL_L(1),
    /* 0x47 */ SCHEDULE_CMD_CHECK_FLAG_S(0x32, 0x20, 0x57 - 0x4B),
    /* 0x4B */ SCHEDULE_CMD_CHECK_TIME_RANGE_S( 8,  0, 18,  0, 0x54 - 0x51),
    /* 0x51 */ SCHEDULE_CMD_RET_VAL_L(3),
    /* 0x54 */ SCHEDULE_CMD_RET_VAL_L(1),
    /* 0x57 */ SCHEDULE_CMD_CHECK_TIME_RANGE_S( 8,  0, 12,  0, 0x70 - 0x5D),
    /* 0x5D */ SCHEDULE_CMD_CHECK_TIME_RANGE_S(12,  0, 12, 15, 0x6E - 0x63),
    /* 0x63 */ SCHEDULE_CMD_CHECK_TIME_RANGE_S(12, 15, 18,  0, 0x6C - 0x69),
    /* 0x69 */ SCHEDULE_CMD_RET_VAL_L(3),
    /* 0x6C */ SCHEDULE_CMD_RET_VAL_S( 1),
    /* 0x6E */ SCHEDULE_CMD_RET_VAL_S( 2),
    /* 0x70 */ SCHEDULE_CMD_RET_VAL_S( 1),
    /* 0x72 */ SCHEDULE_CMD_RET_NONE(),
};

s32 D_80BC1464[] = {
    0x1B040800, 0x6A0A0010, 0x00080010, 0x00080000, 0x00080E29, 0x122D000E, 0x0C100E29, 0x012D000E, 0x0C100E29,
    0x020C0F29, 0x030C0500, 0x00000600, 0x22312D00, 0x0E121030, 0x1C04040E, 0x29040C20, 0x00030004, 0x150900C4,
    0x0900000F, 0x29050C15, 0x0900B930, 0x1D04040E, 0x290B0C20, 0x00030004, 0x150900A8, 0x0900000F, 0x290C0C15,
    0x09009D20, 0x00030017, 0x1B040400, 0x090E2911, 0x2D000E0C, 0x16100E29, 0x0A2D000E, 0x0C16101B, 0x0404003B,
    0x0E290D0C, 0x05000000, 0x0A00000E, 0x29102D00, 0x0E0C1216, 0x100E290E, 0x00320400, 0x590C0F29, 0x0F0C1206,
    0x000C0000, 0x13000C2F, 0x00002E2D, 0x002A2D00, 0x0E113204, 0x0C16100E, 0x29060C05, 0x000A0000, 0x00000E29,
    0x072D000E, 0x0C121610, 0x0E290800, 0x3202001E, 0x0C0F2909, 0x0C120600, 0x0C000013, 0x000C2F00, 0x002E2D00,
    0x292D000E, 0x1132020C, 0x16102D00, 0x0E0C1216, 0x10000000,
};

s32 D_80BC1574[] = {
    0x0900000E, 0x28C70C09, 0x0000170E, 0x28C80C09, 0x0000180E, 0x28C90C09, 0x0000170E,
    0x28CA0C09, 0x0000180E, 0x28CB0C09, 0x0000170E, 0x28CC0C09, 0x0000180E, 0x28CD0C09,
    0x0000170E, 0x28CE0C09, 0x0000180E, 0x28CF2D00, 0x012D000E, 0x0C090000, 0x10000000,
};

s32 D_80BC15C8[] = {
    0x0E23622D,
    0x000E0C10,
};

const ActorInit En_Nb_InitVars = {
    ACTOR_EN_NB,
    ACTORCAT_NPC,
    FLAGS,
    OBJECT_NB,
    sizeof(EnNb),
    (ActorFunc)EnNb_Init,
    (ActorFunc)EnNb_Destroy,
    (ActorFunc)EnNb_Update,
    (ActorFunc)EnNb_Draw,
};

static ColliderCylinderInit sCylinderInit = {
    {
        COLTYPE_HIT1,
        AT_NONE,
        AC_NONE,
        OC1_ON | OC1_TYPE_ALL,
        OC2_TYPE_1,
        COLSHAPE_CYLINDER,
    },
    {
        ELEMTYPE_UNK1,
        { 0x00000000, 0x00, 0x00 },
        { 0x00000000, 0x00, 0x00 },
        TOUCH_NONE | TOUCH_SFX_NORMAL,
        BUMP_NONE,
        OCELEM_ON,
    },
    { 10, 68, 0, { 0, 0, 0 } },
};

static CollisionCheckInfoInit2 sColChkInfoInit = { 0, 0, 0, 0, MASS_IMMOVABLE };

AnimationInfoS D_80BC1628[] = {
    { &object_nb_Anim_000990, 1.0f, 0, -1, 0, 0 },  { &object_nb_Anim_000990, 1.0f, 0, -1, 0, -4 },
    { &object_nb_Anim_000290, 1.0f, 0, -1, 2, 0 },  { &object_nb_Anim_000290, 1.0f, 0, -1, 0, -4 },
    { &object_nb_Anim_00052C, 1.0f, 0, -1, 0, -4 }, { &object_nb_Anim_0006D4, 1.0f, 0, -1, 2, -4 },
};

Actor* func_80BBFDB0(EnNb* this, PlayState* play, u8 actorCategory, s16 actorId) {
    Actor* thisx;
    Actor* actor = NULL;

    while (true) {
        actor = SubS_FindActor(play, actor, actorCategory, actorId);
        if (actor == NULL) {
            break;
        }

        thisx = &this->actor;
        if ((actor != thisx) && (actor->update != NULL)) {
            break;
        }

        if (actor->next == NULL) {
            actor = NULL;
            break;
        }

        actor = actor->next;
    }

    return actor;
}

void func_80BBFE60(EnNb* this) {
    this->skelAnime.playSpeed = this->unk_268;
    SkelAnime_Update(&this->skelAnime);
}

s32 EnNb_ChangeAnim(EnNb* this, s32 arg1) {
    s32 phi_v1 = false;
    s32 phi_t0 = 0;

    if ((arg1 == 0) || (arg1 == 1)) {
        if ((this->unk_290 != 0) && (this->unk_290 != 1)) {
            phi_v1 = true;
        }
    } else if (arg1 != this->unk_290) {
        phi_v1 = true;
    }

    if (phi_v1) {
        this->unk_290 = arg1;
        phi_t0 = SubS_ChangeAnimationByInfoS(&this->skelAnime, D_80BC1628, arg1);
        this->unk_268 = this->skelAnime.playSpeed;
    }

    return phi_t0;
}

void func_80BBFF24(EnNb* this, PlayState* play) {
    f32 diff;
    s32 pad;

    Collider_UpdateCylinder(&this->actor, &this->collider);

    diff = this->actor.focus.pos.y - this->actor.world.pos.y;
    this->collider.dim.height = diff;
    CollisionCheck_SetOC(play, &play->colChkCtx, &this->collider.base);
}

Actor* func_80BBFF90(EnNb* this, PlayState* play) {
    Actor* actor;

    if (this->unk_1DC == 2) {
        actor = func_80BBFDB0(this, play, ACTORCAT_NPC, ACTOR_EN_AN);
    } else {
        actor = &GET_PLAYER(play)->actor;
    }
    return actor;
}

s32 func_80BBFFD4(EnNb* this, s16 arg1) {
    s32 ret = false;

    if (ActorCutscene_GetCurrentIndex() == 0x7C) {
        ActorCutscene_Stop(0x7C);
        ActorCutscene_SetIntentToPlay(arg1);
    } else if (ActorCutscene_GetCanPlayNext(arg1)) {
        ActorCutscene_StartAndSetUnkLinkFields(arg1, &this->actor);
        ret = true;
    } else {
        ActorCutscene_SetIntentToPlay(arg1);
    }

    return ret;
}

s16 func_80BC0050(EnNb* this, s32 arg1) {
    s16 cutscene = this->actor.cutscene;
    s32 i;

    for (i = 0; i < arg1; i++) {
        cutscene = ActorCutscene_GetAdditionalCutscene(cutscene);
    }

    return cutscene;
}

s32 func_80BC00AC(EnNb* this, PlayState* play) {
    s32 pad;
    s16 sp2A = func_80BC0050(this, 0);
    s32 phi_v1 = 0;

    switch (this->unk_288) {
        case 0x0:
            if (func_80BBFFD4(this, sp2A) != 0) {
                case 0x2:
                case 0x4:
                case 0x6:
                case 0x8:
                    Camera_SetTargetActor(Play_GetCamera(play, ActorCutscene_GetCurrentSubCamId(sp2A)),
                                          &this->actor);
                    this->unk_288++;
                    phi_v1 = 1;
            }
            break;

        case 0x1:
        case 0x3:
        case 0x5:
        case 0x7:
            if ((this->actor.child != NULL) && (this->actor.child->update != NULL)) {
                Camera_SetTargetActor(Play_GetCamera(play, ActorCutscene_GetCurrentSubCamId(sp2A)),
                                      this->actor.child);
            }
            this->unk_288++;
            phi_v1 = 1;
            break;

        case 0x9:
            ActorCutscene_Stop(sp2A);
            this->unk_288++;
            phi_v1 = 1;
            break;
    }

    return phi_v1;
}

s32 func_80BC01DC(EnNb* this, PlayState* play) {
    s32 pad[2];
    s32 sp2C = 0;

    switch (this->unk_288) {
        case 0x0:
            if (Player_GetMask(play) == PLAYER_MASK_ALL_NIGHT) {
                this->unk_288 = 1;
            } else {
                this->unk_288 = 5;
            }
            break;

        case 0x1:
            func_8016A268(&play->state, 1, 0, 0, 0, 0);
            this->unk_286 = 40;
            this->unk_288 = (u16)(this->unk_288 + 1);
            break;

        case 0x2:
            MREG(68) = (s16)(s32)(255.0f - (((f32)ABS_ALT(20 - this->unk_286) / 20.0f) * 255.0f));

            if (this->unk_286 == 20) {
                if (gSaveContext.eventInf[4] & 4) {
                    play->interfaceCtx.unk_31B = 0;
                } else {
                    play->interfaceCtx.unk_31B = 1;
                }
                play->interfaceCtx.unk_31A = 6;
                XREG(91) = 0xFF;
            }

            if (DECR(this->unk_286) == 0) {
                this->unk_288++;
            }
            break;

        case 0x3:
            play->interfaceCtx.unk_31A = 4;
            this->unk_288++;
            sp2C = 1;
            break;

        case 0x4:
            play->interfaceCtx.unk_31A = 5;
            this->unk_288++;
            /* fallthrough */

        case 0x5:
            if (!(gSaveContext.eventInf[4] & 4)) {
                gSaveContext.save.time = CLOCK_TIME(8, 0);
                Sram_IncrementDay();
            } else {
                func_800FE658(120.0f);
            }

            this->unk_288++;
            play->nextEntranceIndex = 0xBC20;
            gSaveContext.nextCutsceneIndex = 0;
            play->transitionTrigger = TRANS_TRIGGER_START;
            play->transitionType = TRANS_TYPE_02;
            gSaveContext.nextTransitionType = TRANS_TYPE_06;
            gSaveContext.eventInf[4] |= 8;
            break;
    }

    return sp2C;
}

UNK_PTR func_80BC045C(EnNb* this, PlayState* play) {
    if (gSaveContext.eventInf[4] & 8) {
        this->unk_28C = func_80BC01DC;
        return &D_80BC1464;
    }

    if (this->unk_1DC == 2) {
        this->unk_28C = func_80BC00AC;
        return &D_80BC1574;
    }

    if (Player_GetMask(play) == PLAYER_MASK_KAFEIS_MASK) {
        return &D_80BC15C8;
    }

    this->unk_28C = func_80BC01DC;
    return &D_80BC1464;
}

s32 func_80BC04FC(EnNb* this, PlayState* play) {
    s32 phi_v1 = 0;

    if (this->unk_262 & 7) {
        if (Actor_ProcessTalkRequest(&this->actor, &play->state)) {
            this->unk_262 |= 0x20;
            SubS_UpdateFlags(&this->unk_262, 0, 7);
            this->unk_288 = 0;
            this->unk_28C = NULL;
            this->actor.child = this->unk_1E8;
            this->unk_1E0 = func_80BC045C(this, play);
            this->unk_262 |= 0x20;
            this->actionFunc = func_80BC0EAC;
            phi_v1 = 1;
        }
    }
    return phi_v1;
}

void func_80BC05A8(EnNb* this, PlayState* play) {
    Player* player = GET_PLAYER(play);
    s32 talkState = Message_GetState(&play->msgCtx);
    u16 temp_a0 = play->msgCtx.currentTextId;

    if ((&this->actor == player->targetActor) && ((temp_a0 < 0xFF) || (temp_a0 > 0x200)) && (talkState == 3) &&
        (this->lastTalkState == 3)) {
        if ((play->state.frames % 3) == 0) {
            if (this->unk_26C == 120.0f) {
                this->unk_26C = 0.0f;
            } else {
                this->unk_26C = 120.0f;
            }
        }
    } else {
        this->unk_26C = 0.0f;
    }

    Math_SmoothStepToF(&this->unk_270, this->unk_26C, 0.8f, 40.0f, 10.0f);
    Matrix_Translate(this->unk_270, 0.0f, 0.0f, 1);
    this->lastTalkState = talkState;
}

void func_80BC06C4(EnNb* this) {
    s32 pad;
    Vec3f sp40;
    Vec3f sp34;
    Player* player;

    Math_Vec3f_Copy(&sp40, &this->unk_1E8->world.pos);
    Math_Vec3f_Copy(&sp34, &this->actor.world.pos);
    Math_ApproachS(&this->unk_27E, Math_Vec3f_Yaw(&sp34, &sp40) - this->actor.shape.rot.y, 4, 0x2AA8);

    this->unk_27E = CLAMP(this->unk_27E, -0x1FFE, 0x1FFE);

    Math_Vec3f_Copy(&sp34, &this->actor.focus.pos);

    if (this->unk_1E8->id == ACTOR_PLAYER) {
        player = (Player*)this->unk_1E8;

        sp40.y = player->bodyPartsPos[7].y + 3.0f;
    } else {
        Math_Vec3f_Copy(&sp40, &this->unk_1E8->focus.pos);
    }

    Math_ApproachS(&this->headRot, Math_Vec3f_Pitch(&sp34, &sp40), 4, 0x2AA8);

    this->headRot = CLAMP(this->headRot, -0x1554, 0x1554);
}

void func_80BC0800(EnNb* this) {
    if (this->unk_262 & 0x20) {
        if ((this->unk_1E8 != NULL) && (this->unk_1E8->update != NULL)) {
            if (DECR(this->unk_282) == 0) {
                func_80BC06C4(this);
                this->unk_262 &= ~0x400;
                this->unk_262 |= 0x100;
                return;
            }
        }
    }

    if (this->unk_262 & 0x100) {
        this->unk_262 &= ~0x100;
        this->headRot = 0;
        this->unk_27E = 0;
        this->unk_282 = 20;
    } else if (DECR(this->unk_282) == 0) {
        this->unk_262 |= 0x400;
    }
}

// Related to both stories?
void func_80BC08E0(EnNb* this, PlayState* play) {
    if (this->unk_284 == 0) {
        EnNb_ChangeAnim(this, 2);
        this->unk_262 |= 0x400;
        this->unk_284++;
    } else if ((this->unk_284 == 1) && Animation_OnFrame(&this->skelAnime, this->skelAnime.endFrame)) {
        EnNb_ChangeAnim(this, 1);
        this->unk_262 &= 0xFBFF;
        this->unk_284++;
    }
}

void func_80BC0978(EnNb* this, PlayState* play) {
    if (this->unk_284 == 0) {
        EnNb_ChangeAnim(this, 5);
        this->unk_262 &= ~0x20;
        this->unk_262 |= 0x400;
        this->unk_284 += 1;
    } else if ((this->unk_284 == 1) && Animation_OnFrame(&this->skelAnime, this->skelAnime.endFrame)) {
        EnNb_ChangeAnim(this, 3);
        this->unk_262 &= ~0x400;
        this->unk_284 += 1;
    }
}

s32 func_80BC0A18(EnNb* this, PlayState* play) {
    Player* player = GET_PLAYER(play);
    u16 currentTextId = play->msgCtx.currentTextId;

    if (player->stateFlags1 & 0x40) {
        this->unk_262 |= 0x80;

        if (this->textId != currentTextId) {
            switch (currentTextId) {
                case 0x28CF:
                    this->unk_262 |= 0x20;
                    EnNb_ChangeAnim(this, 3);
                    break;

                case 0x2904: // "You want to hear the carnival of time story? ..."
                case 0x290B: // "You want to hear the four giants story? ..."
                    this->unk_18C = func_80BC08E0;
                    this->unk_284 = 0;
                    break;

                case 0x28CD:
                    this->unk_18C = func_80BC0978;
                    this->unk_284 = 0;
                    break;

                case 0x28CB:
                    EnNb_ChangeAnim(this, 4);
                    break;

                case 0x28C7:
                case 0x2901:
                case 0x2902:
                case 0x2906:
                case 0x290D:
                case 0x2912:
                    EnNb_ChangeAnim(this, 3);
                    break;
            }
        }

        this->textId = currentTextId;
    } else if (this->unk_262 & 0x80) {
        this->unk_18C = NULL;
        this->textId = 0;
        this->unk_262 &= ~0x80;
        EnNb_ChangeAnim(this, 1);
    }

    if (this->unk_18C != NULL) {
        this->unk_18C(this, play);
    }

    return 0;
}

s32 func_80BC0B98(EnNb* this, PlayState* play, UNK_TYPE arg2) {
    s32 sp24 = 0;

    if (func_80BBFDB0(this, play, ACTORCAT_NPC, ACTOR_EN_AN) != NULL) {
        SubS_UpdateFlags(&this->unk_262, 3, 7);
        this->unk_262 |= 0x20;
        EnNb_ChangeAnim(this, 0);
        sp24 = 1;
    }

    return sp24;
}

s32 func_80BC0C0C(EnNb* this, PlayState* play, UNK_TYPE arg2) {
    if (!(gSaveContext.eventInf[4] & 8)) {
        SubS_UpdateFlags(&this->unk_262, 3, 7);
    } else {
        SubS_UpdateFlags(&this->unk_262, 4, 7);
    }
    EnNb_ChangeAnim(this, 0);

    return 1;
}

s32 func_80BC0C80(EnNb* this, PlayState* play, u8* arg2) {
    s32 phi_v0;

    this->actor.flags |= ACTOR_FLAG_1;
    this->actor.targetMode = 0;
    this->unk_262 = 0;
    this->unk_274 = 40.0f;

    switch (*arg2) {
        default:
            phi_v0 = 0;
            break;

        case 0x1:
        case 0x3:
        case 0x4:
            phi_v0 = func_80BC0C0C(this, play, arg2);
            break;

        case 0x2:
            phi_v0 = func_80BC0B98(this, play, arg2);
            break;
    }
    return phi_v0;
}

s32 func_80BC0D08(EnNb* this, PlayState* play) {
    return 0;
}

void func_80BC0D1C(EnNb* this, PlayState* play) {
    if ((this->unk_1DC == 1) || (this->unk_1DC == 2) || (this->unk_1DC == 3) || (this->unk_1DC == 4)) {
        func_80BC0D08(this, play);
    }
    Math_ApproachS(&this->actor.shape.rot.y, this->actor.world.rot.y, 3, 0x2AA8);
}

void EnNb_Wait(EnNb* this, PlayState* play) {
    ScheduleOutput scheduleResult;

    this->unk_280 = REG(15) + ((void)0, gSaveContext.save.daySpeed);

    if (gSaveContext.eventInf[4] & 8) {
        scheduleResult.result = 1;
        func_80BC0C80(this, play, &scheduleResult.result);
        this->actor.shape.shadowDraw = ActorShadow_DrawCircle;
        this->actor.flags |= ACTOR_FLAG_1;
    } else if ((!Schedule_RunScript(play, sScheduleScript, &scheduleResult)) ||
               ((this->unk_1DC != scheduleResult.result) && (func_80BC0C80(this, play, &scheduleResult.result) == 0))) {
        this->actor.shape.shadowDraw = NULL;
        this->actor.flags &= ~ACTOR_FLAG_1;
        scheduleResult.result = 0;
    } else {
        this->actor.shape.shadowDraw = ActorShadow_DrawCircle;
        this->actor.flags |= ACTOR_FLAG_1;
    }

    this->unk_1DC = scheduleResult.result;
    this->unk_1E8 = func_80BBFF90(this, play);
    func_80BC0D1C(this, play);
}

void func_80BC0EAC(EnNb* this, PlayState* play) {
    if (func_8010BF58(&this->actor, play, this->unk_1E0, this->unk_28C, &this->unk_1E4) != 0) {
        if (gSaveContext.eventInf[4] & 8) {
            gSaveContext.eventInf[4] &= (u8)~4;
            gSaveContext.eventInf[4] &= (u8)~8;
        }
        SubS_UpdateFlags(&this->unk_262, 3, 7);
        if (this->unk_1DC != 2) {
            this->unk_262 &= ~0x20;
        }
        this->actor.child = NULL;
        this->unk_262 |= 0x400;
        this->unk_282 = 20;
        this->unk_1E4 = 0;
        this->actionFunc = EnNb_Wait;
    }
}

void EnNb_Init(Actor* thisx, PlayState* play) {
    EnNb* this = THIS;

    ActorShape_Init(&this->actor.shape, 0.0f, NULL, 0.0f);
    SkelAnime_InitFlex(play, &this->skelAnime, &object_nb_Skel_008C40, NULL, this->jointTable, this->morphTable,
                       OBJECT_NB_LIMB_MAX);

    this->unk_290 = -1;
    EnNb_ChangeAnim(this, 0);

    Collider_InitAndSetCylinder(play, &this->collider, &this->actor, &sCylinderInit);
    CollisionCheck_SetInfo2(&this->actor.colChkInfo, DamageTable_Get(0x16), &sColChkInfoInit);
    Actor_SetScale(&this->actor, 0.01f);
    this->unk_262 = 0;

    if (gSaveContext.eventInf[4] & 8) {
        SubS_UpdateFlags(&this->unk_262, 4, 1 | 2 | 4);
    } else {
        gSaveContext.eventInf[4] &= (u8)~4;
        gSaveContext.eventInf[4] &= (u8)~8;
    }

    this->actionFunc = EnNb_Wait;
    this->actionFunc(this, play);
}

void EnNb_Destroy(Actor* thisx, PlayState* play) {
    EnNb* this = THIS;

    Collider_DestroyCylinder(play, &this->collider);
    play->interfaceCtx.unk_31A = 3;
}

void EnNb_Update(Actor* thisx, PlayState* play) {
    EnNb* this = THIS;

    func_80BC04FC(this, play);
    this->actionFunc(this, play);
    func_80BC0A18(this, play);

    if (this->unk_1DC != 0) {
        func_80BBFE60(this);
        func_80BC0800(this);
        if (Actor_IsFacingPlayer(&this->actor, 0x38E0)) {
            func_8013C964(&this->actor, play, this->unk_274, 30.0f, 0, this->unk_262 & 7);
        }
        func_80BBFF24(this, play);
    }
}

s32 EnNb_OverrideLimbDraw(PlayState* play, s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3s* rot, Actor* thisx) {
    EnNb* this = THIS;

    if (limbIndex == OBJECT_NB_LIMB_05) {
        func_80BC05A8(this, play);
    }

    return false;
}

void EnNb_PostLimbDraw(PlayState* play, s32 limbIndex, Gfx** dList, Vec3s* rot, Actor* thisx) {
    EnNb* this = THIS;
    Vec3f sp18;

    if ((ActorCutscene_GetCurrentIndex() == -1) && (limbIndex == OBJECT_NB_LIMB_05)) {
        Matrix_MultVec3f(&gZeroVec3f, &sp18);
        Math_ApproachF(&thisx->focus.pos.x, sp18.x, 0.6f, 10000.0f);
        Math_ApproachF(&thisx->focus.pos.y, sp18.y, 0.6f, 10000.0f);
        Math_ApproachF(&thisx->focus.pos.z, sp18.z, 0.6f, 10000.0f);
        Math_Vec3s_Copy(&thisx->focus.rot, &thisx->world.rot);
    }
}

void EnNb_TransformLimbDraw(PlayState* play, s32 limbIndex, Actor* thisx) {
    EnNb* this = THIS;
    s32 phi_v0;
    s32 phi_v1;

    if (!(this->unk_262 & 0x400)) {
        phi_v1 = false;
        if (this->unk_262 & 0x100) {
            phi_v1 = true;
            phi_v0 = true;
        } else {
            phi_v0 = true;
        }
    } else {
        phi_v1 = false;
        phi_v0 = false;
    }

    if (limbIndex == OBJECT_NB_LIMB_05) {
        SubS_UpdateLimb(this->headRot + 0x4000, this->unk_27E + this->actor.shape.rot.y + 0x4000, &this->unk_1F0,
                      &this->unk_1FC, phi_v0, phi_v1);
        Matrix_Pop();
        Matrix_Translate(this->unk_1F0.x, this->unk_1F0.y, this->unk_1F0.z, 0);
        Matrix_Scale(this->actor.scale.x, this->actor.scale.y, this->actor.scale.z, 1);
        Matrix_RotateYS(this->unk_1FC.y, 1);
        Matrix_RotateXS(this->unk_1FC.x, 1);
        Matrix_RotateZS(this->unk_1FC.z, 1);
        Matrix_Push();
    }
}

//#define PRINT_TO_SCREEN

#ifdef PRINT_TO_SCREEN

#define RELOCATE(symbol)      \
    ((uintptr_t)(symbol) == 0 \
         ? 0                  \
         : ((uintptr_t)(symbol) - (uintptr_t)func_80BBFDB0 + (uintptr_t)SEGMENT_START(ovl_En_Nb)))

void EnNb_PrintSymbol(EnNb* this, PlayState* play, GfxPrint* printer, uintptr_t symbol) {
    if (symbol == (uintptr_t)EnNb_Wait) {
        GfxPrint_Printf(printer, "Wait");
    } else {
        GfxPrint_Printf(printer, "%X", RELOCATE(symbol) & 0x00FFFFFF);
    }
}

void EnNb_PrintRelocatedStuff(EnNb* this, PlayState* play, GfxPrint* printer) {
    s32 x = 21;
    s32 y = 20;
    GfxPrint_SetColor(printer, 255, 255, 255, 255);

    GfxPrint_SetPos(printer, x, y++);
    GfxPrint_Printf(printer, "actionFunc: ");
    EnNb_PrintSymbol(this, play, printer, this->actionFunc);
    GfxPrint_SetPos(printer, x, y++);
    GfxPrint_Printf(printer, "unk_18C:    ");
    EnNb_PrintSymbol(this, play, printer, this->unk_18C);
    GfxPrint_SetPos(printer, x, y++);
    GfxPrint_Printf(printer, "unk_28C:    ");
    EnNb_PrintSymbol(this, play, printer, this->unk_28C);

    y++;

    // GfxPrint_SetPos(printer, x, y++);
    // GfxPrint_Printf(printer, "unk_1E0:    ");
    // EnNb_PrintSymbol(this, play, printer, this->unk_1E0);
}

void EnNb_PrintStructMembers(EnNb* this, PlayState* play, GfxPrint* printer) {
    s32 x = 1;
    s32 y = 5;
    GfxPrint_SetColor(printer, 255, 255, 255, 255);

    GfxPrint_SetPos(printer, x, y++);
    GfxPrint_Printf(printer, "unk_1DC:    %X", this->unk_1DC);
    GfxPrint_SetPos(printer, x, y++);
    GfxPrint_Printf(printer, "unk_1E4:    %X", this->unk_1E4);

    if (this->unk_1E8 != NULL) {
        // GfxPrint_SetPos(printer, x, y++);
        // GfxPrint_Printf(printer, "unk_1E8.id: %X", this->unk_1E8->id);
    }

    GfxPrint_SetPos(printer, x, y++);
    GfxPrint_Printf(printer, "unk_262:    %X", this->unk_262);
    GfxPrint_SetPos(printer, x, y++);
    GfxPrint_Printf(printer, "textId:     %X", this->textId);

    // GfxPrint_SetPos(printer, x, y++);
    // GfxPrint_Printf(printer, "unk_268:    %f", this->unk_268);
    // GfxPrint_SetPos(printer, x, y++);
    // GfxPrint_Printf(printer, "unk_26C:    %f", this->unk_26C);
    // GfxPrint_SetPos(printer, x, y++);
    // GfxPrint_Printf(printer, "unk_270:    %f", this->unk_270);
    // GfxPrint_SetPos(printer, x, y++);
    // GfxPrint_Printf(printer, "unk_274:    %f", this->unk_274);

    // GfxPrint_SetPos(printer, x, y++);
    // GfxPrint_Printf(printer, "headRot:    %X", this->headRot);
    // GfxPrint_SetPos(printer, x, y++);
    // GfxPrint_Printf(printer, "unk_27E:    %X", this->unk_27E);
    GfxPrint_SetPos(printer, x, y++);
    GfxPrint_Printf(printer, "unk_280:    %X", this->unk_280);
    GfxPrint_SetPos(printer, x, y++);
    GfxPrint_Printf(printer, "unk_282:    %i", this->unk_282);
    GfxPrint_SetPos(printer, x, y++);
    GfxPrint_Printf(printer, "unk_284:    %X", this->unk_284);
    GfxPrint_SetPos(printer, x, y++);
    GfxPrint_Printf(printer, "unk_286:    %X", this->unk_286);
    GfxPrint_SetPos(printer, x, y++);
    GfxPrint_Printf(printer, "unk_288:    %X", this->unk_288);

    GfxPrint_SetPos(printer, x, y++);
    GfxPrint_Printf(printer, "unk_290:    %X", this->unk_290);
    GfxPrint_SetPos(printer, x, y++);
    GfxPrint_Printf(printer, "lastTalkState:    %X", this->lastTalkState);
}

void EnNb_PrintEventInf(EnNb* this, PlayState* play, GfxPrint* printer) {
    s32 x = 24;
    s32 y = 8;
    GfxPrint_SetColor(printer, 255, 255, 255, 255);

    GfxPrint_SetPos(printer, x, y++);
    GfxPrint_Printf(printer, "event[4] & 4: %i", gSaveContext.eventInf[4] & 4);
    GfxPrint_SetPos(printer, x, y++);
    GfxPrint_Printf(printer, "event[4] & 8: %i", gSaveContext.eventInf[4] & 8);
}

void EnNb_DrawToScreen(EnNb* this, PlayState* play) {
    GraphicsContext* gfxCtx = play->state.gfxCtx;
    GfxPrint printer;

    OPEN_DISPS(gfxCtx);

    func_8012C4C0(gfxCtx);

    GfxPrint_Init(&printer);
    GfxPrint_Open(&printer, POLY_OPA_DISP);

    EnNb_PrintRelocatedStuff(this, play, &printer);
    EnNb_PrintStructMembers(this, play, &printer);
    // EnNb_PrintEventInf(this, play, &printer);

    POLY_OPA_DISP = GfxPrint_Close(&printer);
    GfxPrint_Destroy(&printer);

    CLOSE_DISPS(gfxCtx);
}

#endif

void EnNb_Draw(Actor* thisx, PlayState* play) {
    EnNb* this = THIS;

    if (this->unk_1DC != 0) {
        func_8012C5B0(play->state.gfxCtx);
        SkelAnime_DrawTransformFlexOpa(play, this->skelAnime.skeleton, this->skelAnime.jointTable,
                                       this->skelAnime.dListCount, EnNb_OverrideLimbDraw, EnNb_PostLimbDraw,
                                       EnNb_TransformLimbDraw, &this->actor);
    }

#ifdef PRINT_TO_SCREEN
    EnNb_DrawToScreen(this, play);
#endif
}
