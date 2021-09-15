/*
 * File: z_en_test4.c
 * Overlay: ovl_En_Test4
 * Description: 
 */

#include "z_en_test4.h"
#include "overlays/gamestates/ovl_daytelop/z_daytelop.h"

#define FLAGS 0x00100030

#define THIS ((EnTest4*)thisx)

void EnTest4_Init(Actor* thisx, GlobalContext* globalCtx);
void EnTest4_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnTest4_Update(Actor* thisx, GlobalContext* globalCtx);

void func_80A42AB8(EnTest4* this, GlobalContext* globalCtx);
void func_80A42F20(EnTest4* this, GlobalContext* globalCtx);

#if 0
const ActorInit En_Test4_InitVars = {
    ACTOR_EN_TEST4,
    ACTORCAT_SWITCH,
    FLAGS,
    GAMEPLAY_KEEP,
    sizeof(EnTest4),
    (ActorFunc)EnTest4_Init,
    (ActorFunc)EnTest4_Destroy,
    (ActorFunc)EnTest4_Update,
    (ActorFunc)NULL,
};

#endif

extern s32 D_80A43340;
extern s16 D_80A434D0[];
extern s16 D_801F4E7A;
extern u8 D_801BDBB0;
extern s16 D_80A434D4;
extern s32 D_801BDA9C;
extern s16 D_80A43364[];

extern s8 D_801BDBC8;
extern s16 D_80A43342[];
extern s16 D_80A4334A[];

#ifdef NON_MATCHING
void func_80A41D70(EnTest4* this, GlobalContext* globalCtx) {
    if (this->unk_144 != 0) {
        func_80151A68(globalCtx, D_80A43342[CURRENT_DAY]);
    } else if ((D_80A434D0[this->unk_144] < 0) || ((globalCtx->actorCtx.unk5 & 2) != 0)) {
        if (globalCtx->actorCtx.unk5 & 2) {
            Sram_IncrementDay();
            gSaveContext.time = CLOCK_TIME(6, 0);
            func_80151A68(globalCtx, D_80A4334A[CURRENT_DAY]);
        } else {
            this->unk_144 = 0;
            this->unk_146 = gSaveContext.time += CLOCK_TIME(0, 1);
        }

        func_8010EE74(globalCtx, CURRENT_DAY);
        D_801BDBC8 = 0xFE;
        func_800FB758(globalCtx);
        func_800FEAF4(&globalCtx->envCtx);
        this->actionFunc = func_80A42AB8;
    }

    if (gSaveContext.cutsceneTrigger == 0) {
        if ((D_80A434D0[this->unk_144] >= 0) && ((globalCtx->actorCtx.unk5 & 2) == 0)) {
            this->actionFunc = func_80A42F20;
            D_80A434D4 = D_80A434D0[this->unk_144];
            this->unk_145 = 0;
            gSaveContext.eventInf[1] |= 0x80;
        } else if (this->unk_144 == 0) {
            play_sound(0x2813);
        } else {
            func_8019F128(0x28AE);
        }
    } else {
        this->actionFunc = func_80A42AB8;
        if (this->unk_144 == 0) {
            this->unk_144 = 1;
        } else {
            this->unk_144 = 0;
        }

        this->unk_146 = gSaveContext.time += CLOCK_TIME(0, 1);
    }
}
#else
void func_80A41D70(EnTest4* this, GlobalContext* globalCtx);
#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Test4/func_80A41D70.s")
#endif

void func_80A41FA4(EnTest4* this, GlobalContext* globalCtx);
#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Test4/func_80A41FA4.s")

void func_80A42198(EnTest4* this) {
    if ((gSaveContext.time >= 0x4000) && (gSaveContext.time < 0xC001)) {
        if (gSaveContext.time < 0xBAAA) {
            this->unk_148 = 0xBAAA;
        } else if (gSaveContext.time < 0xBBBB) {
            this->unk_148 = 0xBBBB;
        } else if (gSaveContext.time < 0xBCCC) {
            this->unk_148 = 0xBCCC;
        } else if (gSaveContext.time < 0xBDDD) {
            this->unk_148 = 0xBDDD;
        } else if (gSaveContext.time < 0xBEEE) {
            this->unk_148 = 0xBEEE;
        } else {
            this->unk_148 = 0;
        }
    } else if (gSaveContext.time >= 0x4001) {
        this->unk_148 = 0;
    } else if (gSaveContext.time < 0x1C7) {
        this->unk_148 = 0x1C7;
    } else if (gSaveContext.time < 0x38E) {
        this->unk_148 = 0x38E;
    } else if (gSaveContext.time < 0x555) {
        this->unk_148 = 0x555;
    } else if (gSaveContext.time < 0x71C) {
        this->unk_148 = 0x71C;
    } else if (gSaveContext.time < 0x8E3) {
        this->unk_148 = 0x8E3;
    } else if (gSaveContext.time < 0xAAA) {
        this->unk_148 = 0xAAA;
    } else if (gSaveContext.time < 0xC71) {
        this->unk_148 = 0xC71;
    } else if (gSaveContext.time < 0xE38) {
        this->unk_148 = 0xE38;
    } else if (gSaveContext.time < 0xFFF) {
        this->unk_148 = 0xFFF;
    } else if (gSaveContext.time < 0x11C6) {
        this->unk_148 = 0x11C6;
    } else if (gSaveContext.time < 0x138D) {
        this->unk_148 = 0x138D;
    } else if (gSaveContext.time < 0x1555) {
        this->unk_148 = 0x1555;
    } else if (gSaveContext.time < 0x171C) {
        this->unk_148 = 0x171C;
    } else if (gSaveContext.time < 0x18E3) {
        this->unk_148 = 0x18E3;
    } else if (gSaveContext.time < 0x1AAA) {
        this->unk_148 = 0x1AAA;
    } else if (gSaveContext.time < 0x1C71) {
        this->unk_148 = 0x1C71;
    } else if (gSaveContext.time < 0x1E38) {
        this->unk_148 = 0x1E38;
    } else if (gSaveContext.time < 0x2000) {
        this->unk_148 = 0x2000;
    } else if (gSaveContext.time < 0x21C7) {
        this->unk_148 = 0x21C7;
    } else if (gSaveContext.time < 0x238E) {
        this->unk_148 = 0x238E;
    } else if (gSaveContext.time < 0x2555) {
        this->unk_148 = 0x2555;
    } else if (gSaveContext.time < 0x271C) {
        this->unk_148 = 0x271C;
    } else if (gSaveContext.time < 0x28E3) {
        this->unk_148 = 0x28E3;
    } else if (gSaveContext.time < 0x2AAA) {
        this->unk_148 = 0x2AAA;
    } else if (gSaveContext.time < 0x2C71) {
        this->unk_148 = 0x2C71;
    } else if (gSaveContext.time < 0x2E38) {
        this->unk_148 = 0x2E38;
    } else if (gSaveContext.time < 0x2FFF) {
        this->unk_148 = 0x2FFF;
    } else if (gSaveContext.time < 0x31C6) {
        this->unk_148 = 0x31C6;
    } else if (gSaveContext.time < 0x338D) {
        this->unk_148 = 0x338D;
    } else if (gSaveContext.time < 0x3555) {
        this->unk_148 = 0x3555;
    } else if (gSaveContext.time < 0x3638) {
        this->unk_148 = 0x3638;
    } else if (gSaveContext.time < 0x371C) {
        this->unk_148 = 0x371C;
    } else if (gSaveContext.time < 0x37FF) {
        this->unk_148 = 0x37FF;
    } else if (gSaveContext.time < 0x38E3) {
        this->unk_148 = 0x38E3;
    } else if (gSaveContext.time < 0x39C6) {
        this->unk_148 = 0x39C6;
    } else if (gSaveContext.time < 0x3AAA) {
        this->unk_148 = 0x3AAA;
    } else if (gSaveContext.time < 0x3B32) {
        this->unk_148 = 0x3B32;
    } else if (gSaveContext.time < 0x3BBB) {
        this->unk_148 = 0x3BBB;
    } else if (gSaveContext.time < 0x3C43) {
        this->unk_148 = 0x3C43;
    } else if (gSaveContext.time < 0x3CCC) {
        this->unk_148 = 0x3CCC;
    } else if (gSaveContext.time < 0x3D55) {
        this->unk_148 = 0x3D55;
    } else if (gSaveContext.time < 0x3DDD) {
        this->unk_148 = 0x3DDD;
    } else if (gSaveContext.time < 0x3E66) {
        this->unk_148 = 0x3E66;
    } else if (gSaveContext.time < 0x3EEE) {
        this->unk_148 = 0x3EEE;
    } else if (gSaveContext.time < 0x3F77) {
        this->unk_148 = 0x3F77;
    } else if (gSaveContext.time < 0x4000) {
        this->unk_148 = 0x4000;
    }
}

void func_80A425E4(EnTest4* this, GlobalContext* globalCtx) {
    gSaveContext.unk_3F64 = 1000.0f;

    if ((gSaveContext.time >= 0x4000) && (gSaveContext.time < 0xC000)) {
        if (gSaveContext.time < 0xBAAA) {
            this->unk_148 = 0xBAAA;
        } else if (gSaveContext.time < 0xBBBB) {
            this->unk_148 = 0xBBBB;
        } else if (gSaveContext.time < 0xBCCC) {
            this->unk_148 = 0xBCCC;
        } else if (gSaveContext.time < 0xBDDD) {
            this->unk_148 = 0xBDDD;
        } else if (gSaveContext.time < 0xBEEE) {
            this->unk_148 = 0xBEEE;
        } else {
            this->unk_148 = 0x3AAA;
        }
    } else {
        if (gSaveContext.time < 0x3AAA) {
            this->unk_148 = 0x3AAA;
        } else if (gSaveContext.time < 0x3BBB) {
            this->unk_148 = 0x3BBB;
        } else if (gSaveContext.time < 0x3CCC) {
            this->unk_148 = 0x3CCC;
            gSaveContext.unk_3F64 -= 50.0f;
        } else if (gSaveContext.time < 0x3DDD) {
            this->unk_148 = 0x3DDD;
            gSaveContext.unk_3F64 -= 100.0f;
        } else if (gSaveContext.time < 0x3EEE) {
            this->unk_148 = 0x3EEE;
            gSaveContext.unk_3F64 -= 150.0f;
        } else if (gSaveContext.time < 0x4000) {
            this->unk_148 = 0xBAAA;
            gSaveContext.unk_3F64 -= 200.0f;
        } else {
            this->unk_148 = 0xBAAA;
        }

        if ((D_80A434D0[this->unk_144] < 0) || ((globalCtx->actorCtx.unk5 & 2) != 0) || (CURRENT_DAY == 3) || (gSaveContext.time >= CLOCK_TIME(17, 0))) {
            gSaveContext.unk_3F64 = 1000.0f;
        }
        if (gSaveContext.unk_3F64 != 1000.0f) {
            gSaveContext.unk_3F60 = 1;
        }
    }
}

#ifdef MIPS2C_OUTPUT
void EnTest4_Init(Actor* thisx, GlobalContext* globalCtx) {
    Actor* sp24;
    ActorCutscene* temp_v0_2;
    s8 temp_v0;
    u16 temp_v0_3;
    SaveContext* phi_v1;

    temp_v0 = thisx->cutscene;
    D_80A434D0 = (s16) temp_v0;
    if ((s32) temp_v0 >= 0) {
        sp24 = globalCtx->actorCtx.actorList[2].first;
        temp_v0_2 = ActorCutscene_GetCutscene(D_80A434D0);
        gSaveContext.unk_1011 = (u8) (gSaveContext.unk_1011 | 4);
        *(&D_80A434D0 + 2) = (s16) temp_v0_2->additionalCutscene;
    } else {
        gSaveContext.unk_1011 = (u8) (gSaveContext.unk_1011 & 0xFB);
        *(&D_80A434D0 + 2) = (s16) D_80A434D0;
    }
    phi_v1 = &gSaveContext;
    if ((D_80A43340 != 0) || ((gSaveContext.unk_100E & 0x80) != 0)) {
        Actor_MarkForDeath(thisx);
        phi_v1 = &gSaveContext;
    } else {
        D_80A43340 = 1;
        thisx->room = -1;
        gSaveContext.unk_3F60 = 0;
        gSaveContext.unk_3F64 = 1000.0f;
        if (((s32) gSaveContext.day % 5) == 0) {
            if (gSaveContext.time < 0x402D) {
                gSaveContext.time = 0x4000;
                gSaveContext.gameMode = 0;
                globalCtx->state.running = 0;
                globalCtx->state.nextGameStateInit = Daytelop_Init;
                globalCtx->state.nextGameStateSize = 0x248;
                thisx->unk_144 = (s8) 1;
                gSaveContext.time = 0x4000;
                Actor_MarkForDeath(thisx);
                phi_v1 = &gSaveContext;
            } else {
                gSaveContext.day = 1;
                gSaveContext.daysElapsed = 1;
                thisx->unk_144 = (s8) 1;
                thisx->unk_150 = func_80A42AB8;
                thisx->unk_146 = (u16) gSaveContext.time;
            }
        } else {
            temp_v0_3 = gSaveContext.time;
            if (temp_v0_3 == 0x4000) {
                thisx->unk_144 = 0;
                sp24 = globalCtx->actorCtx.actorList[2].first;
                func_80A41D70(thisx, globalCtx, globalCtx->actorCtx.actorList[2].first);
                phi_v1 = &gSaveContext;
                if ((gSaveContext.cutsceneTrigger == 0) && ((s32) *(&D_80A434D0 + (thisx->unk_144 * 2)) >= 0) && ((globalCtx->actorCtx.unk5 & 2) == 0)) {
                    globalCtx->actorCtx.actorList[2].first->unk_A6C = (s32) (globalCtx->actorCtx.actorList[2].first->unk_A6C | 0x200);
                }
            } else {
                if (((s32) temp_v0_3 >= 0xC001) || ((s32) temp_v0_3 < 0x4000)) {
                    thisx->unk_144 = 0;
                } else {
                    thisx->unk_144 = (s8) 1;
                }
                thisx->unk_150 = func_80A42AB8;
                thisx->unk_146 = (u16) gSaveContext.time;
            }
        }
    }
    if (((s32) phi_v1->day % 5) == 3) {
        func_80A42198(thisx);
    } else {
        func_80A425E4(thisx, globalCtx);
    }
    thisx->unk_14A = (u16) gSaveContext.time;
    if (((s32) *(&D_80A434D0 + (thisx->unk_144 * 2)) < 0) || ((globalCtx->actorCtx.unk5 & 2) != 0)) {
        gSaveContext.unk_3F60 = 0;
        gSaveContext.unk_3F64 = 1000.0f;
    }
}
#else
#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Test4/EnTest4_Init.s")
#endif

void EnTest4_Destroy(Actor* thisx, GlobalContext* globalCtx) {

}

#ifdef NON_EQUIVALENT
void func_80A42AB8(EnTest4* this, GlobalContext* globalCtx) {
    Player* player;
    s16 temp_a2;
    s16 temp_a3;
    s32 temp_v1_3;
    u16 temp_a0;
    u16 temp_t4;
    u16 temp_v1_2;
    s32 phi_v0;

    player = PLAYER;
    if ((globalCtx->unk_18B4A == 0) && ((func_801690CC(globalCtx) == 0)) && ((s32) globalCtx->numSetupActors <= 0) && (globalCtx->roomCtx.unk31 == 0) && (func_8016A168() == 0)) {
        temp_a0 = D_80A43364[this->unk_144];
        temp_a2 = gSaveContext.time - D_80A43364[this->unk_144];
        temp_a3 = this->unk_146 - D_80A43364[this->unk_144];
        if (((temp_a2) * (temp_a3)) <= 0) {
            gSaveContext.unk_3CA7 = 1;
            if (globalCtx->actorCtx.unk5 & 0x04) {
                globalCtx->actorCtx.unk5 &= ~0x04;
            }
            if (temp_a0 != 0x4000) {
                func_80A41FA4(this, globalCtx);
            } else if (temp_a0 == 0x4000) {
                if (CURRENT_DAY == 3) {
                    func_8011C808(globalCtx);
                    Actor_MarkForDeath((Actor* ) this);
                    gSaveContext.eventInf[1] |= 0x80;
                } else {
                    if ((((D_80A434D0)[this->unk_144] < 0) || ((globalCtx->actorCtx.unk5 & 2) != 0)) && (CURRENT_DAY != 3)) {
                        func_80A41FA4(this, globalCtx);
                    } else {
                        gSaveContext.unk_3F64 = 0.0f;
                        func_80169DCC(globalCtx, 0, Entrance_CreateIndexFromSpawn(0) & 0xFFFF, (s32) player->unk_3CE, 0xBFF, &player->unk_3C0, player->unk_3CC);
                        func_80169EFC(globalCtx);
                        //temp_v1_3 = ((s32*)(player->unk_390))[0x150/4];
                        //if ((player->stateFlags1 & 0x800000) && ((/*temp_v1_3 = player->unk_390->unk_150,*/ (temp_v1_3 == 0)) || (temp_v1_3 == 2))) {
                        if ((player->stateFlags1 & 0x800000) && (((((s32*)(player->unk_390))[0x150/4] == 0)) || (((s32*)(player->unk_390))[0x150/4] == 2))) {
                            if (CURRENT_DAY < 3) {
                                D_801BDA9C = 1;
                            } else {
                                D_801BDA9C = 0;
                            }
                        }
                        gSaveContext.respawnFlag = -4;
                        gSaveContext.eventInf[2] |= 0x80;
                        Actor_MarkForDeath((Actor* ) this);
                    }
                }
            }

            if (((s32) (D_80A434D0)[this->unk_144] >= 0) && ((globalCtx->actorCtx.unk5 & 2) == 0)) {
                player->stateFlags1 = (s32) (player->stateFlags1 | 0x200);
                this->unk_146 = gSaveContext.time;
            } else {
                if (this->unk_144 == 0) {
                    this->unk_144 = 1;
                } else {
                    this->unk_144 = 0;
                }
                temp_t4 = gSaveContext.time + 0x2D;
                gSaveContext.time = temp_t4;
                this->unk_146 = temp_t4;
            }
            return;
        }

        if (((s16) (gSaveContext.time - this->unk_148) * (s16) (this->unk_14A - this->unk_148)) <= 0) {
            func_801A0124(&this->actor.projectedPos, ((s32) this->actor.params >> 5) & 0xF & 0xFF);
            this->unk_14A = gSaveContext.time;
            if (CURRENT_DAY == 3) {
                if (((u16) this->unk_148 == 0) && (((u8) gSaveContext.inventory.items == 0xFF) || (globalCtx->sceneNum == 0x6F))) {
                    if ((globalCtx->actorCtx.unk5 & 2) != 0) {
                        phi_v0 = 0xCFF;
                    } else {
                        phi_v0 = 0xBFF;
                    }
                    func_80169DCC(globalCtx, 1, gSaveContext.entranceIndex & 0xFFFF, (s32) player->unk_3CE, phi_v0, &player->unk_3C0, (s16) (s32) player->unk_3CC);

                    if ((globalCtx->sceneNum == 0x29) || (globalCtx->sceneNum == 0x2D)) {
                        globalCtx->nextEntranceIndex = 0x5400;
                    } else {
                        globalCtx->nextEntranceIndex = 0xD800;
                    }
                    gSaveContext.unk_3F4A = 0xFFF1;
                    globalCtx->sceneLoadFlag = 0x14;
                    globalCtx->unk_1887F = 2;
                    player->stateFlags1 = (s32) (player->stateFlags1 | 0x200);
                    Actor_MarkForDeath((Actor* ) this);
                }
                func_80A42198(this);
                return;
            }
            func_80A425E4(this, globalCtx);
            return;
        }
    }
}
#else
#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Test4/func_80A42AB8.s")
#endif

#ifdef NON_MATCHING
void func_80A42F20(EnTest4* this, GlobalContext* globalCtx) {
    if (this->unk_145 == 0) {
        if (D_80A434D4 >= 0) {
            if (ActorCutscene_GetCanPlayNext(D_80A434D4) == 0) {
                ActorCutscene_SetIntentToPlay(D_80A434D4);
            } else {
                ActorCutscene_Start(D_80A434D4, &this->actor);
                this->unk_145 = 1;
            }
        } else {
            this->unk_145 = 1;
        }
        return;
    } else if (this->unk_145 < 0x3C) {
        this->unk_145++;
        if (this->unk_145 == 0xA) {
            if (this->unk_144 == 0) {
                play_sound(0x2813);
            } else {
                func_8019F128(0x28AE);
            }
        }
        if (this->unk_145 == 0x3C) {
            Player* player = PLAYER;

            gSaveContext.time += CLOCK_TIME(0, 1);
            this->unk_146 = gSaveContext.time;
            globalCtx->numSetupActors = -globalCtx->numSetupActors;
            player->stateFlags1 &= ~0x200;
        }
    } else {
        this->actionFunc = func_80A42AB8;
        if (this->unk_144 == 0) {
            this->unk_144 = 1;
        } else {
            this->unk_144 = 0;
        }

        if (D_80A434D4 >= 0) {
            ActorCutscene_Stop(D_80A434D4);
        }
        gSaveContext.unk_3F22 = 0;
        gSaveContext.eventInf[1] &= (u8)~0x80;
        Interface_ChangeAlpha(50);
    }
}
#else
#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Test4/func_80A42F20.s")
#endif

void func_80A430C8(EnTest4* this, GlobalContext* globalCtx) {
    if ((CURRENT_DAY == 2) && (gSaveContext.time >= CLOCK_TIME(7, 0)) && (gSaveContext.time < CLOCK_TIME(17, 30)) && (globalCtx->envCtx.unk_F2[2] == 0)) {
        D_801BDBB0 = 1;
        func_800FD78C(globalCtx);
        globalCtx->envCtx.unk_E3 = 1;
        globalCtx->envCtx.unk_F2[0] = 0x3C;
    } else {
        if (globalCtx->envCtx.unk_F2[0] != 0) {
            if ((globalCtx->state.frames % 4) == 0) {
                globalCtx->envCtx.unk_F2[0]--;
                if ((globalCtx->envCtx.unk_F2[0]) == 8) {
                    func_800FD858(globalCtx);
                }
            }
        }
    }

    if (D_801BDBB0 == 1) {
        this->unk_14C = 1;
    }
}

void func_80A431C8(EnTest4* this, GlobalContext* globalCtx) {
    if (((gSaveContext.time >= 0xBAAA) && (gSaveContext.time < 0xF555) && (globalCtx->envCtx.unk_F2[0] != 0)) || (globalCtx->envCtx.unk_F2[2] != 0)) {
        D_801BDBB0 = 0;
        globalCtx->envCtx.unk_E3 = 2;
    }
    if (D_801BDBB0 == 0) {
        this->unk_14C = 0;
    }
}

void func_80A4323C(EnTest4* this, GlobalContext* globalCtx) {
    s32 temp_v0;

    temp_v0 = ((s32) this->actor.params >> 0xA) * 0x64;
    if (temp_v0 > 0) {
        D_801F4E7A = (s16) temp_v0;
    }
}

void EnTest4_Update(Actor* thisx, GlobalContext* globalCtx) {
    EnTest4* this = THIS;
    Player* player = PLAYER;

    if (!(player->stateFlags1 & 2)) {
        this->actionFunc(this, globalCtx);
        if (func_800FE4B8(globalCtx) != 0) {
            switch (this->unk_14C) {
            case 0:
                func_80A430C8(this, globalCtx);
                break;
            case 1:
                func_80A431C8(this, globalCtx);
                break;
            }
        }
        func_80A4323C(this, globalCtx);
    }
}
