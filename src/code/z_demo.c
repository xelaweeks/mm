#include "global.h"

#if 0

glabel D_801F4D40
/* 010DA0 801F4D40 */ .space 0x2

glabel D_801F4D42
/* 010DA2 801F4D42 */ .space 0x6

glabel D_801F4D48
/* 010DA8 801F4D48 */ .space 0x80

glabel D_801F4DC8
/* 010E28 801F4DC8 */ .space 0x2

glabel D_801F4DCA
/* 010E2A 801F4DCA */ .space 0x2

glabel D_801F4DCC
/* 010E2C 801F4DCC */ .space 0x10

glabel D_801F4DDC
/* 010E3C 801F4DDC */ .space 0x4

glabel D_801F4DE0
/* 010E40 801F4DE0 */ .space 0x2

glabel D_801F4DE2
/* 010E42 801F4DE2 */ .space 0xE
#endif


#if 0
void Cutscene_Init(GlobalContext* globalCtx, CutsceneContext* csCtx) {
    ?* temp_v0;
    ?* phi_v0;

    csCtx->state = 0;
    csCtx->frames = 0;
    csCtx->unk_0C = 0.0f;
    globalCtx->csCtx.sceneCsCount = 0;
    globalCtx->csCtx.unk_12 = 0;
    D_801F4DCA = 0;
    D_801F4DCA = 0;
    phi_v0 = &D_801F4DCC;
    do {
        temp_v0 = phi_v0 + 8;
        temp_v0->unk_-6 = 0;
        temp_v0->unk_-4 = 0;
        temp_v0->unk_-2 = 0;
        temp_v0->unk_-8 = 0;
        phi_v0 = temp_v0;
    } while (temp_v0 != &D_801F4DDC);
    D_801F4DE0 = 0;
    func_801A3F54(0);
}
#else
#pragma GLOBAL_ASM("asm/non_matchings/code/z_demo/Cutscene_Init.s")
#endif

void func_800EA0D4(GlobalContext* globalCtx, CutsceneContext* csCtx) {
    csCtx->state = 1;
    csCtx->linkAction = NULL;
}

void func_800EA0EC(GlobalContext* globalCtx, CutsceneContext* csCtx) {
    if (csCtx->state != 4) {
        csCtx->state = 3;
    }
}

void Cutscene_StepCutscene1(GlobalContext* globalCtx, CutsceneContext* csCtx) {
    if (gSaveContext.cutscene < 0xFFF0) {
        sCsStateHandlers1[csCtx->state](globalCtx, csCtx);
    }
}

void Cutscene_StepCutscene2(GlobalContext* globalCtx, CutsceneContext* csCtx) {
    if ((gSaveContext.cutsceneTrigger != 0) && (globalCtx->sceneLoadFlag == 0x14)) {
        gSaveContext.cutsceneTrigger = 0;
    }

    if ((gSaveContext.cutsceneTrigger != 0) && (csCtx->state == 0)) {
        gSaveContext.cutscene = 0xFFFD;
        gSaveContext.cutsceneTrigger = 1;
    }

    if (gSaveContext.cutscene >= 0xFFF0) {
        func_800EDA84(globalCtx, csCtx);
        sCsStateHandlers2[csCtx->state](globalCtx, csCtx);
    }
}

void Cutscene_Nop800EA210(GlobalContext* globalCtx, CutsceneContext* csCtx) {

}

s32 func_800EA220(GlobalContext* globalCtx, CutsceneContext* csCtx, f32 target) {
    return Math_StepToF(&csCtx->unk_0C, target, 0.1f);
}

void func_800EA258(GlobalContext* globalCtx, CutsceneContext* csCtx) {
    Interface_ChangeAlpha(1);
    ShrinkWindow_SetLetterboxTarget(0x20);
    if (func_800EA220(globalCtx, csCtx, 1.0f) != 0) {
        func_801A3F54(1);
        csCtx->state += 1;
    }
}

void func_800EA2B8(GlobalContext* globalCtx, CutsceneContext* csCtx) {
    func_800ED980(globalCtx, csCtx);
    Interface_ChangeAlpha(1);
    ShrinkWindow_SetLetterboxTarget(0x20);
    if (func_800EA220(globalCtx, csCtx, 1.0f) != 0) {
        func_801A3F54(1);
        csCtx->state += 1;
    }
}

#pragma GLOBAL_ASM("asm/non_matchings/code/z_demo/func_800EA324.s")
#if 0
struct _mips2c_stack_func_800EA324 {
    /* 0x00 */ char pad_0[0x20];
    /* 0x20 */ s32 sp20;                            /* inferred */
    /* 0x24 */ char pad_24[4];
    /* 0x28 */ s32 sp28;                            /* inferred */
    /* 0x2C */ char pad_2C[0x13];                   /* maybe part of sp28[5]? */
    /* 0x3F */ u8 sp3F;                             /* inferred */
    /* 0x40 */ char pad_40[4];                      /* maybe part of sp3F[5]? */
    /* 0x44 */ Actor* sp44;                         /* inferred */
};                                                  /* size = 0x48 */

void Daytelop_Init(GameState* gameState);           /* extern */
? func_80144A94(SramContext*, u16, CsCmdBase*, GlobalContext*); /* extern */
? func_80146EE8(GlobalContext*, u16, CsCmdBase*, GlobalContext*); /* extern */
? func_80146F5C(GlobalContext*, u16, CsCmdBase*, GlobalContext*); /* extern */
? func_8019D758(CutsceneContext*, u16, CsCmdBase*, GlobalContext*); /* extern */
? func_801A47DC(?, ?, ?, GlobalContext*);           /* extern */
extern u8 D_801BB130;
extern u16 D_801BB15C;
extern s16 D_801F4D42;
extern s8 D_801F4DE0;
extern s8 D_801F4E68;

void func_800EA324(GlobalContext* globalCtx, CutsceneContext* csCtx, CsCmdBase* cmd) {
    Actor* sp44;
    u8 sp3F;
    s32 sp28;
    s32 sp20;
    Actor* temp_t2;
    GlobalContext* temp_a0_2;
    GlobalContext* temp_a3;
    GlobalContext* temp_a3_2;
    f32 temp_f0;
    f32 temp_f16;
    f32 temp_f6;
    s16 temp_a0_3;
    s16 temp_v0;
    s16 temp_v1;
    s16 temp_v1_2;
    s32 temp_a0;
    u16 temp_a1;
    u16 temp_a1_2;
    u16 temp_t0;
    u16 temp_t1;
    u16 temp_t3;
    u16 temp_t5;
    u16 temp_t7;
    u16 temp_t9;
    s32 phi_a0;
    u8 phi_v0;

    temp_a3 = globalCtx;
    temp_t2 = temp_a3->actorCtx.actorList[2].first;
    temp_t7 = csCtx->frames;
    sp28 = (s32) temp_t7;
    temp_t9 = cmd->startFrame;
    sp20 = (s32) temp_t9;
    phi_v0 = 0U;
    if (((s32) temp_t7 >= (s32) temp_t9) && ((temp_t1 = cmd->endFrame, temp_a0 = temp_t1 - 1, phi_a0 = temp_a0, (((s32) temp_t7 < (s32) temp_t1) != 0)) || (phi_a0 = temp_a0 & 0xFFFF, (temp_t9 == temp_t1)))) {
        sp3F = 0;
        globalCtx = temp_a3;
        sp44 = temp_t2;
        temp_f0 = func_800F5A8C(phi_a0 & 0xFFFF, unksp22, unksp2A, temp_a3);
        temp_a1 = csCtx->frames;
        temp_t0 = cmd->startFrame;
        temp_a3_2 = globalCtx;
        if (temp_t0 == temp_a1) {
            phi_v0 = 1U;
        }
        temp_t3 = cmd->base;
        switch (temp_t3) {
        case 0x1:
            temp_a0_2 = temp_a3_2;
            if (phi_v0 != 0) {
                globalCtx = temp_a3_2;
                func_800FD78C(temp_a0_2);
                globalCtx->envCtx.unk_F2[0] = 0x3C;
                return;
            }
            /* Duplicate return node #70. Try simplifying control flow for better match */
            return;
        case 0x2:
            if (phi_v0 != 0) {
                globalCtx = temp_a3_2;
                func_801A47DC(0xF, 0, 0, temp_a3_2);
                func_800FB320(globalCtx, 3U);
                D_801F4E68 = 1;
                return;
            }
            /* Duplicate return node #70. Try simplifying control flow for better match */
            return;
        case 0x3:
            temp_v0 = temp_a3_2->envCtx.unk_8C.fogFar;
            if ((s32) temp_v0 < 0x3200) {
                temp_a3_2->envCtx.unk_8C.fogFar = temp_v0 + 0x23;
                return;
            }
            /* Duplicate return node #70. Try simplifying control flow for better match */
            return;
        case 0x4:
            if (phi_v0 != 0) {
                temp_a3_2->envCtx.unk_19 = 1;
                temp_a3_2->envCtx.unk_17 = 1;
                temp_a3_2->envCtx.unk_18 = 0;
                temp_a3_2->envCtx.unk_1A = 0x3C;
                temp_a3_2->envCtx.unk_21 = 1;
                temp_a3_2->envCtx.unk_1F = 0;
                temp_a3_2->envCtx.unk_20 = 1;
                temp_a3_2->envCtx.unk_24 = 0x3C;
                temp_a3_2->envCtx.unk_22 = temp_a3_2->envCtx.unk_24;
                return;
            }
            /* Duplicate return node #70. Try simplifying control flow for better match */
            return;
        case 0x5:
            if ((phi_v0 != 0) && (csCtx->state != 4)) {
                csCtx->state = 3;
                return;
            }
            /* Duplicate return node #70. Try simplifying control flow for better match */
            return;
        case 0x7:
            if ((phi_v0 != 0) && (temp_a1_2 = temp_a3_2->loadedScene->titleTextId, (temp_a1_2 != 0))) {
                func_80151A68(temp_a3_2, temp_a1_2);
                return;
            }
            /* Duplicate return node #70. Try simplifying control flow for better match */
            return;
        case 0x8:
            sp3F = phi_v0;
            globalCtx = temp_a3_2;
            func_8019F128(0x2150U);
            if (phi_v0 != 0) {
                D_801F4D42 = Quake_Add(globalCtx->cameraPtrs[globalCtx->activeCamera], 6U);
                Quake_SetSpeed(D_801F4D42, 0x55F0);
                Quake_SetQuakeValues(D_801F4D42, 6, 4, 0, (s16) 0);
                Quake_SetCountdown(D_801F4D42, 0x320);
                return;
            }
            /* Duplicate return node #70. Try simplifying control flow for better match */
            return;
        case 0x9:
            if (phi_v0 != 0) {
                Quake_Init();
                return;
            }
            /* Duplicate return node #70. Try simplifying control flow for better match */
            return;
        case 0xA:
            temp_f6 = 255.0f * temp_f0;
            D_801F6D30.r = 0xFF;
            D_801F6D30.g = 0xFF;
            D_801F6D30.b = 0xFF;
            D_801F6D30.a = (u8) (u32) temp_f6;
            return;
        case 0xB:
            temp_f16 = 255.0f * temp_f0;
            D_801F6D30.r = 0xFF;
            D_801F6D30.g = 0xB4;
            D_801F6D30.b = 0x64;
            D_801F6D30.a = (u8) (u32) temp_f16;
            return;
        case 0xC:
            temp_a3_2->roomCtx.currRoom.segment = NULL;
            return;
        case 0xD:
            if ((temp_a3_2->state.frames & 8) != 0) {
                temp_v1 = temp_a3_2->envCtx.unk_8C.ambientColor[0];
                if ((s32) temp_v1 < 0x28) {
                    temp_a3_2->envCtx.unk_8C.ambientColor[0] = temp_v1 + 2;
                    temp_a3_2->envCtx.unk_8C.diffuseColor1[1] += -3;
                    temp_a3_2->envCtx.unk_8C.diffuseColor1[2] += -3;
                    return;
                }
                /* Duplicate return node #70. Try simplifying control flow for better match */
                return;
            }
            temp_v1_2 = temp_a3_2->envCtx.unk_8C.ambientColor[0];
            if ((s32) temp_v1_2 >= 3) {
                temp_a3_2->envCtx.unk_8C.ambientColor[0] = temp_v1_2 - 2;
                temp_a3_2->envCtx.unk_8C.diffuseColor1[1] += 3;
                temp_a3_2->envCtx.unk_8C.diffuseColor1[2] += 3;
                return;
            }
            /* Duplicate return node #70. Try simplifying control flow for better match */
            return;
        case 0xE:
            temp_a3_2->unk_18845 = 1;
            return;
        case 0xF:
            temp_a3_2->unk_18845 = 0;
            return;
        case 0x10:
            if (phi_v0 != 0) {
                temp_a3_2->envCtx.unk_EA = 1;
            }
            func_8019F128(0x20C0U);
            return;
        case 0x11:
            gSaveContext.unk_3F58 = 1;
            return;
        case 0x12:
            if (gSaveContext.isNight == 0) {
                gSaveContext.time -= (u16) gGameInfo->data[0xF];
                return;
            }
            gSaveContext.time -= gGameInfo->data[0xF] * 2;
            return;
        case 0x13:
            func_8019D758(csCtx, temp_a1, cmd, temp_a3_2);
            csCtx->frames = cmd->startFrame - 1;
            return;
        case 0x14:
            EnvFlags_Set(temp_a3_2, 3);
            return;
        case 0x15:
            EnvFlags_Set(temp_a3_2, 4);
            return;
        case 0x16:
            gSaveContext.playerForm = 3;
            return;
        case 0x17:
            temp_t2->unk_A70 = (s32) (temp_t2->unk_A70 | 0x4000000);
            return;
        case 0x18:
            temp_t2->unk_A70 = (s32) (temp_t2->unk_A70 & 0xFBFFFFFF);
            return;
        case 0x19:
            D_801BB130 = gSaveContext.playerForm;
            gSaveContext.playerForm = 4;
            gSaveContext.equippedMask = 0;
            return;
        case 0x1A:
            sp3F = phi_v0;
            globalCtx = temp_a3_2;
            func_8019F128(0x2159U);
            if (phi_v0 != 0) {
                D_801F4D42 = Quake_Add(globalCtx->cameraPtrs[globalCtx->activeCamera], 6U);
                Quake_SetSpeed(D_801F4D42, 0x7530);
                Quake_SetQuakeValues(D_801F4D42, 0x14, 0xA, 0, (s16) 0);
                Quake_SetCountdown(D_801F4D42, 0x320);
                return;
            }
            /* Duplicate return node #70. Try simplifying control flow for better match */
            return;
        case 0x1B:
            if (phi_v0 != 0) {
                temp_a3_2->nextEntranceIndex = 0x1C00;
                gSaveContext.nextCutsceneIndex = 0xFFF8;
                temp_a3_2->sceneLoadFlag = 0x14;
                temp_a3_2->unk_1887F = 3;
                return;
            }
            /* Duplicate return node #70. Try simplifying control flow for better match */
            return;
        case 0x1C:
            if (phi_v0 != 0) {
                temp_a3_2->envCtx.unk_17 = 0xD;
                return;
            }
            /* Duplicate return node #70. Try simplifying control flow for better match */
            return;
        case 0x1D:
            gSaveContext.playerForm = D_801BB130;
            return;
        case 0x1E:
            D_801F4DE0 = 1;
            return;
        case 0x1F:
            D_801F4DE0 = 0;
            return;
        case 0x21:
            if (phi_v0 != 0) {
                func_80146EE8(temp_a3_2, temp_a1, cmd, temp_a3_2);
                return;
            }
            /* Duplicate return node #70. Try simplifying control flow for better match */
            return;
        case 0x22:
            if (phi_v0 != 0) {
                func_80144A94(&temp_a3_2->sramCtx, temp_a1, cmd, temp_a3_2);
                return;
            }
            /* Duplicate return node #70. Try simplifying control flow for better match */
            return;
        case 0x23:
            if ((D_801BB15C != temp_a1) && (D_801BB15C = temp_a1, temp_a0_3 = gGameInfo->data[0xF], (temp_a0_3 != 0))) {
                temp_t5 = temp_a0_3 + gSaveContext.time;
                gSaveContext.time = temp_t5;
                gSaveContext.time = gSaveContext.unk_16 + temp_t5;
                return;
            }
            /* Duplicate return node #70. Try simplifying control flow for better match */
            return;
        case 0x24:
            sp3F = phi_v0;
            globalCtx = temp_a3_2;
            func_8019F128(0x2150U);
            if (phi_v0 != 0) {
                D_801F4D42 = Quake_Add(globalCtx->cameraPtrs[globalCtx->activeCamera], 6U);
                Quake_SetSpeed(D_801F4D42, 0x55F0);
                Quake_SetQuakeValues(D_801F4D42, 2, 1, 0, (s16) 0);
                Quake_SetCountdown(D_801F4D42, 0x320);
                return;
            }
            /* Duplicate return node #70. Try simplifying control flow for better match */
            return;
        case 0x26:
            gSaveContext.day = 9;
            temp_a3_2->state.running = 0;
            temp_a3_2->state.nextGameStateSize = 0x248;
            temp_a3_2->state.nextGameStateInit = Daytelop_Init;
            func_80146F5C(temp_a3_2, temp_a1, cmd, temp_a3_2);
            return;
        case 0x27:
            gSaveContext.playerForm = 2;
            return;
        case 0x28:
            csCtx->frames = temp_t0 - 1;
            /* Duplicate return node #70. Try simplifying control flow for better match */
            return;
        }
    } else {
    default:
    }
}
#endif

void func_800EABAC(GlobalContext* globalCtx, CutsceneContext* csCtx, CsCmdEnvLighting* cmd) {
    if (csCtx->frames == cmd->startFrame) {
        if (cmd->setting != 0x20) {
            globalCtx->envCtx.unk_C3 = cmd->setting - 1;
            globalCtx->envCtx.unk_DC = 1.0f;
            return;
        } else {
            globalCtx->envCtx.unk_C3 = 0xFF;
        }
    }
}

void func_800EAC08(GlobalContext* globalCtx, CutsceneContext* csCtx, CsCmdMusicChange* cmd) {
    if (csCtx->frames == cmd->startFrame) {
        func_801A2C88(cmd->sequence - 1);
    }
}

void func_800EAC44(GlobalContext* globalCtx, CutsceneContext* csCtx, CsCmdMusicChange* cmd) {
    if ((csCtx->frames >= cmd->startFrame) && (cmd->endFrame >= csCtx->frames)) {
        func_801A2D54(cmd->sequence - 1);
    }
}

void func_800EAC94(GlobalContext* globalCtx, CutsceneContext* csCtx, CsCmdMusicFade* cmd) {
    if ((csCtx->frames == cmd->startFrame) && (csCtx->frames < cmd->endFrame)) {
        u8 frameCount = (cmd->endFrame - cmd->startFrame);

        if (cmd->type == 2) {
            Audio_QueueSeqCmd((frameCount << 0x10) | 0x110000FF);
        } else {
            Audio_QueueSeqCmd((frameCount << 0x10) | NA_BGM_STOP);
        }
    }
}

void func_800EAD14(GlobalContext* globalCtx, CutsceneContext* csCtx, CsCmdBase* cmd) {
    if (csCtx->frames == cmd->startFrame) {
        func_801A4A28(globalCtx->soundCtx.nightSeqIndex);
    }
}

void func_800EAD48(GlobalContext* globalCtx, CutsceneContext* csCtx, CsCmdBase* cmd) {
    if (csCtx->frames == cmd->startFrame) {
        func_801A4428(2);
    }
}

void func_800EAD7C(GlobalContext* globalCtx, CutsceneContext* csCtx, CsCmdBase* cmd) {
    if (csCtx->frames == cmd->startFrame) {
        func_801A4428(1);
    }
}

#pragma GLOBAL_ASM("asm/non_matchings/code/z_demo/func_800EADB0.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_demo/func_800EAECC.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_demo/func_800EAF20.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_demo/func_800EAFE0.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_demo/func_800EB1DC.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_demo/func_800EB364.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_demo/func_800EB4B4.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_demo/func_800EB6F8.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_demo/func_800EBB68.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_demo/func_800EBCD0.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_demo/func_800EBD60.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_demo/func_800EC678.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_demo/func_800EC6D4.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_demo/func_800EC924.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_demo/func_800ECD7C.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_demo/Cutscene_ProcessCommands.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_demo/func_800ED980.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_demo/func_800ED9C4.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_demo/func_800EDA04.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_demo/func_800EDA84.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_demo/func_800EDBE0.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_demo/nop_800EDDB0.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_demo/func_800EDDBC.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_demo/func_800EDDCC.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_demo/func_800EDE34.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_demo/func_800EDF24.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_demo/func_800EDF78.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_demo/func_800EE0CC.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_demo/func_800EE1D8.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_demo/func_800EE200.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_demo/func_800EE29C.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_demo/func_800EE2F4.s")
