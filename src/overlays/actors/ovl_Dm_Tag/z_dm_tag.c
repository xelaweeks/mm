/*
 * File: z_dm_tag.c
 * Overlay: ovl_Dm_Tag
 * Description:
 */

#include "z_dm_tag.h"

#define FLAGS (ACTOR_FLAG_10)

#define THIS ((DmTag*)thisx)

void DmTag_Init(Actor* thisx, PlayState* play);
void DmTag_Destroy(Actor* thisx, PlayState* play);
void DmTag_Update(Actor* thisx, PlayState* play);

void func_80C229AC(DmTag* this, PlayState* play);
void func_80C229EC(DmTag* this, PlayState* play);
void func_80C229FC(DmTag* this, PlayState* play);

ActorInit Dm_Tag_InitVars = {
    ACTOR_DM_TAG,
    ACTORCAT_ITEMACTION,
    FLAGS,
    GAMEPLAY_KEEP,
    sizeof(DmTag),
    (ActorFunc)DmTag_Init,
    (ActorFunc)DmTag_Destroy,
    (ActorFunc)DmTag_Update,
    (ActorFunc)NULL,
};

s32 D_80C22BF0[] = {
    0x0E28F00C,
    0x15090000,
    0x10000000,
};

s32 D_80C22BFC[] = {
    0x0900000E, 0x28F10C09, 0x00000E28, 0xF20C0900, 0x000E28F3, 0x0C090000, 0x0E28F40C,
    0x0900000E, 0x28F50C09, 0x00000E28, 0xF60C1511, 0x55040900, 0x00100000,
};

s32 D_80C22C30[] = {
    0x0E28EF0C,
    0x10000000,
};

Actor* func_80C22350(DmTag* this, PlayState* play, u8 actorCat, s16 actorId) {
    Actor* foundActor = NULL;

    while (true) {
        foundActor = SubS_FindActor(play, foundActor, actorCat, actorId);

        if ((foundActor == NULL) || (((this != (DmTag*)foundActor)) && (foundActor->update != NULL))) {
            break;
        }

        if (foundActor->next == NULL) {
            foundActor = NULL;
            break;
        }
        foundActor = foundActor->next;
    }
    return foundActor;
}

s32 func_80C22400(DmTag* this, s16 csId) {
    s32 ret = false;

    if (CutsceneManager_GetCurrentCsId() == CS_ID_GLOBAL_TALK) {
        CutsceneManager_Stop(CS_ID_GLOBAL_TALK);
        CutsceneManager_Queue(csId);
    } else if (CutsceneManager_IsNext(csId)) {
        CutsceneManager_StartWithPlayerCs(csId, &this->actor);
        ret = true;
    } else {
        CutsceneManager_Queue(csId);
    }
    return ret;
}

s16 func_80C2247C(DmTag* this, s32 numCutscenes) {
    s32 i;
    s16 csId = this->actor.csId;

    for (i = 0; i < numCutscenes; i++) {
        csId = CutsceneManager_GetAdditionalCsId(csId);
    }

    return csId;
}

s32 func_80C224D8(DmTag* this, PlayState* play) {
    s32 pad;
    Actor* sp30;
    Actor* sp2C;
    s16 csId = this->actor.csId;
    s32 ret = false;

    sp30 = func_80C22350(this, play, ACTORCAT_NPC, ACTOR_EN_AN);
    sp2C = func_80C22350(this, play, ACTORCAT_NPC, ACTOR_EN_AH);

    switch (this->unk_1A4) {
        case 0:
            if (func_80C22400(this, csId)) {
                if ((sp2C != NULL) && (sp2C->update != NULL)) {
                    Camera_SetTargetActor(Play_GetCamera(play, CutsceneManager_GetCurrentSubCamId(csId)), sp2C);
                }
                this->unk_1A4++;
                ret = true;
            }
            break;

        case 1:
            if ((sp30 != NULL) && (sp30->update != NULL)) {
                Camera_SetTargetActor(Play_GetCamera(play, CutsceneManager_GetCurrentSubCamId(func_80C2247C(this, 0))),
                                      sp30);
            }
            this->unk_1A4++;
            ret = true;
            break;

        case 2:
            CutsceneManager_Stop(func_80C2247C(this, 0));
            if (func_80C22400(this, func_80C2247C(this, 1))) {
                this->unk_1A4++;
                ret = true;
            }
            break;

        case 3:
            CutsceneManager_Stop(func_80C2247C(this, 1));
            if (func_80C22400(this, func_80C2247C(this, 2))) {
                this->unk_1A4++;
                ret = true;
            }
            break;

        case 4:
            CutsceneManager_Stop(func_80C2247C(this, 2));
            if (func_80C22400(this, func_80C2247C(this, 3))) {
                this->unk_1A4++;
                ret = true;
            }
            break;

        case 5:
            CutsceneManager_Stop(func_80C2247C(this, 3));
            if (func_80C22400(this, func_80C2247C(this, 4))) {
                this->unk_1A4++;
                ret = true;
            }
            break;

        case 6:
            func_800B7298(play, &this->actor, 7);
            play->nextEntrance = ENTRANCE(STOCK_POT_INN, 5);
            gSaveContext.nextCutsceneIndex = 0;
            play->transitionTrigger = TRANS_TRIGGER_START;
            play->transitionType = TRANS_TYPE_FADE_BLACK;
            gSaveContext.nextTransitionType = TRANS_TYPE_FADE_BLACK_SLOW;
            this->unk_1A4++;
            break;
    }
    return ret;
}

s32 func_80C227E8(DmTag* this, PlayState* play) {
    if (this->unk_1A4 == 0) {
        func_800B7298(play, &this->actor, 7);
        play->nextEntrance = ENTRANCE(STOCK_POT_INN, 4);
        gSaveContext.nextCutsceneIndex = 0;
        play->transitionTrigger = TRANS_TRIGGER_START;
        play->transitionType = TRANS_TYPE_FADE_BLACK;
        gSaveContext.nextTransitionType = TRANS_TYPE_FADE_BLACK_SLOW;
        this->unk_1A4++;
    }
    return false;
}

s32* func_80C22880(DmTag* this, PlayState* play) {
    s32 time;

    switch (this->unk_18E) {
        case 1:
            time = gSaveContext.save.time - 0x3FFC;
            if ((time >= 0xA54B) && (time < 0xB54A) && (gSaveContext.save.day == 2)) {
                this->msgEventCallback = func_80C227E8;
                return D_80C22BF0;
            }
            return D_80C22C30;
        case 2:
            this->msgEventCallback = func_80C224D8;
            return D_80C22BFC;
    }
    return NULL;
}

s32 func_80C2291C(DmTag* this, PlayState* play) {
    s32 ret = false;

    if (this->unk_18C & 7) {
        if (Actor_ProcessTalkRequest(&this->actor, &play->state)) {
            this->unk_18C |= 8;
            SubS_UpdateFlags(&this->unk_18C, 0, 7);
            this->msgEventScript = func_80C22880(this, play);
            this->actionFunc = func_80C229FC;
            ret = true;
        }
    }
    return ret;
}

void func_80C229AC(DmTag* this, PlayState* play) {
    SubS_UpdateFlags(&this->unk_18C, 3, 7);
    this->actor.flags |= ACTOR_FLAG_TARGETABLE;
}

void func_80C229EC(DmTag* this, PlayState* play) {
}

void func_80C229FC(DmTag* this, PlayState* play) {
    if (func_8010BF58(&this->actor, play, this->msgEventScript, this->msgEventCallback, &this->msgEventArg4)) {
        this->actionFunc = func_80C229AC;
    }
}

void DmTag_Init(Actor* thisx, PlayState* play) {
    DmTag* this = (DmTag*)thisx;
    Player* player = GET_PLAYER(play);

    if (CHECK_WEEKEVENTREG(WEEKEVENTREG_85_04)) {
        Actor_Kill(&this->actor);
        return;
    }

    if ((play->sceneId == SCENE_YADOYA) && (play->curSpawn == 4)) {
        player->stateFlags1 |= PLAYER_STATE1_20;
        this->unk_18E = 2;
        this->unk_18C = 0;
        SubS_UpdateFlags(&this->unk_18C, 4, 7);
        this->actor.flags &= ~ACTOR_FLAG_TARGETABLE;
        this->actionFunc = func_80C229EC;
    } else if (this->actor.room == 2) {
        Actor_Kill(&this->actor);
    } else {
        this->actor.targetMode = TARGET_MODE_1;
        this->unk_18E = 1;
        this->unk_18C = 0;
        this->actionFunc = func_80C229AC;
    }
}

void DmTag_Destroy(Actor* thisx, PlayState* play) {
}

void DmTag_Update(Actor* thisx, PlayState* play) {
    DmTag* this = THIS;

    func_80C2291C(this, play);
    this->actionFunc(this, play);
    func_8013C964(&this->actor, play, 40.0f, fabsf(this->actor.playerHeightRel) + 1.0f, 0, this->unk_18C & 7);
    Actor_SetFocus(&this->actor, 0.0f);
}
