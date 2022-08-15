/*
 * File: z_file_choose_NES.c
 * Overlay: ovl_file_choose
 * Description:
 */

#include "z_file_choose.h"
#include "overlays/gamestates/ovl_opening/z_opening.h"
#include "z64rumble.h"
#include "z64save.h"

void func_801A3238(u8 playerIdx, u16 seqId, u8 fadeTimer, s8 arg3, s8 arg4);
void func_801A4058(u16);
void func_801457CC(FileSelectState* fileSelect, SramContext* sramCtx);

extern Gfx D_010311F0[];
extern Gfx D_01031408[];
extern Gfx D_01031618[];

extern void* D_01002800[];
extern void* D_01007980[];
extern void* D_0102A6B0[];
extern void* D_0102B170[];
extern void* D_010310F0[];

// there are uses of D_0E000000.fillRect (appearing as D_0E0002E0) in this file
extern GfxMasterList D_0E000000;

s16 D_80814280[] = {
    2, 3, 2, 2, 2, 2, 2, 2, 2, 2, 1, 2, 0, 1, 1, 2, 1, 1, 4, 2, 2, 2, 1, 1, 0, 2, 0, 1, 1, 1, 1, 1, 0,
    1, 1, 1, 2, 2, 2, 2, 2, 3, 2, 2, 4, 3, 2, 4, 1, 2, 2, 1, 1, 2, 2, 3, 2, 2, 0, 2, 2, 2, 0, 3, 1, 0,
};

s16 D_80814304[] = {
    1, 2, 0, 1, 1, 2, 1, 1, 4, 2, 2, 2, 1, 1, 0, 2, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 2, 2, 2, 2, 2, 3,
    2, 2, 4, 3, 2, 4, 1, 2, 2, 1, 1, 2, 2, 3, 2, 2, 0, 2, 2, 2, 3, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1, 3,
};

s16 D_80814384[] = {
    0, 1, 0, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 0, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 2, 1, 1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
};

s16 D_80814404[] = {
    -94, -96, -48, 0, 32, 64,
};

s16 D_80814410[] = {
    56, 44, 44, 28, 28, 44,
};

s16 D_8081441C[] = {
    72, -48, -48, -48, -48, -48,
};

s16 D_80814428[] = { 0x0102, 0x1D30, 0x0102, 0x17B0 };

s16 D_80814430[] = { 28, 44 };

s16 D_80814434[] = {
    -30, -16, -6, 4, 14, 24, 34, 44, 54, -16, -16, 0,
};

s16 D_8081444C[] = {
    72, 69, 69, 69, 69, 69, 69, 69, 69, 69, 69, 0,
};

s32 D_80814464[] = {
    0x01007180, 0x00800010, 0x01008600, 0x00400010, 0x01008D00,
    0x00400010, 0x01009700, 0x00600010, 0x01009D00, 0x00300011,
};

s32 D_8081448C[] = {
    0x01008A00, 0x00300010, 0x01008300, 0x00300010, 0x01008000, 0x00300010,
    0x01007D00, 0x00300010, 0x01009100, 0x00300010, 0x01009400, 0x00300010,
};

s16 D_808144BC = 0xFF;
s16 D_808144C0 = 0xFF;
s16 D_808144C4 = 0xFF;
s16 D_808144C8 = 0;
s16 D_808144CC = 0;
s16 D_808144D0 = 0;
s16 D_808144D4 = 1;
s16 D_808144D8 = 20;
s16 D_808144DC[] = { 0xFF, 0xFF, 0xFF, 0, 0xFF, 0xFF };

s32 D_808144E8[] = {
    0x00000000, 0x00000000, 0x00960096, 0x00000000, 0x00000000,
    0x00000000, 0x00000064, 0x41000000, 0x42C80000, 0x00000000,
};

Gfx sScreenFillSetupDL[] = {
    gsDPPipeSync(),
    gsSPClearGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BOTH | G_FOG | G_LIGHTING | G_TEXTURE_GEN |
                          G_TEXTURE_GEN_LINEAR | G_LOD | G_SHADING_SMOOTH),
    gsDPSetOtherMode(G_AD_DISABLE | G_CD_MAGICSQ | G_CK_NONE | G_TC_FILT | G_TF_BILERP | G_TT_NONE | G_TL_TILE |
                         G_TD_CLAMP | G_TP_NONE | G_CYC_1CYCLE | G_PM_1PRIMITIVE,
                     G_AC_NONE | G_ZS_PIXEL | G_RM_CLD_SURF | G_RM_CLD_SURF2),
    gsDPSetCombineMode(G_CC_PRIMITIVE, G_CC_PRIMITIVE),
    gsSPEndDisplayList(),
};

s16 sFileInfoBoxPartWidths[] = {
    36, 36, 36, 36, 24, 28, 28, 0,
};

s16 sWindowContentColors[] = { 100, 150, 255 };

s16 sFileSelectSkyboxRotation = 0;

s16 D_80814554[] = { 1, 0, 0, 0 };

#define GET_NEWF(sramCtx, slotNum, index) \
    (sramCtx->readBuff[gSramSlotOffsets[slotNum] + offsetof(SaveContext, save.playerData.newf[index])])
#define SLOT_OCCUPIED(sramCtx, slotNum)                                                  \
    ((GET_NEWF(sramCtx, slotNum, 0) == 'Z') || (GET_NEWF(sramCtx, slotNum, 1) == 'E') || \
     (GET_NEWF(sramCtx, slotNum, 2) == 'L') || (GET_NEWF(sramCtx, slotNum, 3) == 'D') || \
     (GET_NEWF(sramCtx, slotNum, 4) == 'A') || (GET_NEWF(sramCtx, slotNum, 5) == '3'))

#define GET_FILE_CHOOSE_NEWF(fileSelect, slotNum, index) (fileSelect->newf[slotNum][index])
#define FILE_CHOOSE_SLOT_OCCUPIED(fileSelect, slotNum)                                                                 \
    ((GET_FILE_CHOOSE_NEWF(fileSelect, slotNum, 0) == 'Z') && (GET_FILE_CHOOSE_NEWF(fileSelect, slotNum, 1) == 'E') && \
     (GET_FILE_CHOOSE_NEWF(fileSelect, slotNum, 2) == 'L') && (GET_FILE_CHOOSE_NEWF(fileSelect, slotNum, 3) == 'D') && \
     (GET_FILE_CHOOSE_NEWF(fileSelect, slotNum, 4) == 'A') && (GET_FILE_CHOOSE_NEWF(fileSelect, slotNum, 5) == '3'))

void func_8080BC20(FileSelectState* this) {
    this->configMode++;
}

void FileSelect_nop8080bc44(void) {
}

void FileSelect_nop8080BC4C(FileSelectState* this) {
}

void func_8080BC58(GameState* thisx) {
    FileSelectState* this = (FileSelectState*)thisx;

    if (this->configMode == 0) {
        if (gSaveContext.options.optionId != 0xA51D) { // Magic number?
            this->configMode++;
        } else {
            // TODO: defines for these
            this->menuMode = 1;
            this->configMode = 0;
            this->titleLabel = 0;
            this->nextTitleLabel = 1;
        }
    }
    if (this->configMode == 1) {
        this->screenFillAlpha -= 40;
        if (this->screenFillAlpha <= 0) {
            this->screenFillAlpha = 0;
            this->configMode++;
        }
    } else {
        if (this->configMode == 2) {
            func_8080BC20(this);
            return;
        }
        this->screenFillAlpha += 40;
        if (this->screenFillAlpha >= 255) {
            this->screenFillAlpha = 255;
            this->menuMode = 1;
            this->configMode = 0;
            this->titleLabel = 0;
            this->nextTitleLabel = 1;
        }
    }
}

void func_8080BDAC(GameState* thisx) {
    FileSelectState* this = (FileSelectState*)thisx;

    func_8012C628(this->state.gfxCtx);
    FileSelect_nop8080BC4C(this);
}

void FileSelect_RenderView(FileSelectState* this, f32 eyeX, f32 eyeY, f32 eyeZ) {
    Vec3f eye;
    Vec3f lookAt;
    Vec3f up;

    eye.x = eyeX;
    eye.y = eyeY;
    eye.z = eyeZ;

    lookAt.x = lookAt.y = lookAt.z = 0.0f;

    up.x = up.z = 0.0f;
    up.y = 1.0f;

    View_SetViewOrientation(&this->view, &eye, &lookAt, &up);
    View_RenderView(&this->view, 0x7F);
}

Gfx* FileSelect_QuadTextureIA8(Gfx* gfx, void* texture, s16 width, s16 height, s16 point) {
    gDPLoadTextureBlock(gfx++, texture, G_IM_FMT_IA, G_IM_SIZ_8b, width, height, 0, G_TX_NOMIRROR | G_TX_WRAP,
                        G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);

    gSP1Quadrangle(gfx++, point, point + 2, point + 3, point + 1, 0);

    return gfx;
}

void FileSelect_FadeInMenuElements(FileSelectState* this) {
    SramContext* sramCtx = &this->sramCtx;
    s16 i;

    this->titleAlpha[0] += 20;
    this->windowAlpha += 16;

    for (i = 0; i < 3; i++) {
        this->fileButtonAlpha[i] = this->windowAlpha;
        if (gSaveContext.unk_3F3F == 0) {
            if (SLOT_OCCUPIED(sramCtx, i)) {
                this->nameBoxAlpha[i] = this->nameAlpha[i] = this->windowAlpha;
                this->connectorAlpha[i] += 20;
                if (this->connectorAlpha[i] >= 255) {
                    this->connectorAlpha[i] = 255;
                }
            }
        } else if (FILE_CHOOSE_SLOT_OCCUPIED(this, i)) {
            this->nameBoxAlpha[i] = this->nameAlpha[i] = this->windowAlpha;
            this->connectorAlpha[i] += 20;

            if (this->connectorAlpha[i] >= 255) {
                this->connectorAlpha[i] = 255;
            }
        }
    }

    this->actionButtonAlpha[0] = this->actionButtonAlpha[1] = this->optionButtonAlpha = this->windowAlpha;
}

// SplitDigits? ExtractDigits?
void FileSelect_SplitNumber(u16 value, u16* hundreds, u16* tens, u16* ones) {
    *hundreds = 0;
    *tens = 0;
    *ones = value;

    do {
        if ((*ones - 100) < 0) {
            break;
        }
        (*hundreds)++;
        *ones -= 100;
    } while (true);

    do {
        if ((*ones - 10) < 0) {
            break;
        }
        (*tens)++;
        *ones -= 10;
    } while (true);
}

// Start of Config Mode Update Functions

void FileSelect_StartFadeIn(GameState* thisx) {
    FileSelectState* this = (FileSelectState*)thisx;

    FileSelect_FadeInMenuElements(this);
    this->screenFillAlpha -= 40;
    this->windowPosX -= 20;

    if (this->windowPosX <= -94) {
        this->windowPosX = -94;
        this->configMode = 1;
        this->screenFillAlpha = 0;
    }
}

void FileSelect_FinishFadeIn(GameState* thisx) {
    FileSelectState* this = (FileSelectState*)thisx;

    this->controlsAlpha += 20;
    FileSelect_FadeInMenuElements(this);

    if (this->titleAlpha[0] >= 255) {
        this->titleAlpha[0] = 255;
        this->controlsAlpha = 255;
        this->windowAlpha = 200;
        this->configMode = 2;
    }
}

u8 sEmptyName[] = { 0x3E, 0x3E, 0x3E, 0x3E, 0x3E, 0x3E, 0x3E, 0x3E };

void FileSelect_UpdateMainMenu(GameState* thisx) {
    FileSelectState* this = (FileSelectState*)thisx;
    SramContext* sramCtx = &this->sramCtx;
    Input* input = &this->state.input[0];

    if (CHECK_BTN_ALL(input->press.button, BTN_START) || CHECK_BTN_ALL(input->press.button, BTN_A)) {
        if (this->buttonIndex < 3) {
            if (gSaveContext.unk_3F3F == 0) {
                if (!SLOT_OCCUPIED(sramCtx, this->buttonIndex)) {
                    play_sound(NA_SE_SY_FSEL_DECIDE_L);
                    this->configMode = 34;
                    this->kbdButton = 99;
                    this->unk_24512 = 0;
                    if (gSaveContext.options.language != 0) {
                        this->unk_24512 = 2;
                    }
                    this->kbdX = 0;
                    this->kbdY = 0;
                    this->unk_24516 = 0;
                    this->unk_24514 = 0;
                    this->unk_2451C = 0;
                    this->nameEntryBoxPosX = 120;
                    this->nameEntryBoxAlpha = 0;
                    Lib_MemCpy(&this->unk_24414[this->buttonIndex], &sEmptyName, 8);
                } else {
                    play_sound(NA_SE_SY_FSEL_DECIDE_L);
                    this->actionTimer = 4;
                    this->selectMode = 0;
                    this->unk_2448E = this->buttonIndex;
                    this->menuMode = 2;
                    this->nextTitleLabel = 1;
                }
            } else if (!FILE_CHOOSE_SLOT_OCCUPIED(this, this->buttonIndex)) {
                play_sound(NA_SE_SY_FSEL_DECIDE_L);
                this->configMode = 34;
                this->kbdButton = 99;
                this->unk_24512 = 0;
                if (gSaveContext.options.language != 0) {
                    this->unk_24512 = 2;
                }
                this->kbdX = 0;
                this->kbdY = 0;
                this->unk_24516 = 0;
                this->unk_24514 = 0;
                this->unk_2451C = 0;
                this->nameEntryBoxPosX = 120;
                this->nameEntryBoxAlpha = 0;
                Lib_MemCpy(&this->unk_24414[this->buttonIndex], &sEmptyName, 8);
            } else {
                play_sound(NA_SE_SY_FSEL_DECIDE_L);
                this->actionTimer = 4;
                this->selectMode = 0;
                this->unk_2448E = this->buttonIndex;
                this->menuMode = 2;
                this->nextTitleLabel = 1;
            }
        } else if (this->warningLabel == -1) {
            play_sound(NA_SE_SY_FSEL_DECIDE_L);
            this->unk_24488 = this->configMode;
            if (this->buttonIndex == 3) {
                this->configMode = 3;
                this->nextTitleLabel = 2;
            } else if (this->buttonIndex == 4) {
                this->configMode = 21;
                this->nextTitleLabel = 6;
            } else {
                this->configMode = 39;
                this->kbdButton = 0;
                this->kbdX = 0;
                this->kbdY = 0;
                this->unk_24514 = 0;
                this->unk_2451C = 0;
                this->nameEntryBoxPosX = 120;
            }
            this->actionTimer = 4;
        } else {
            play_sound(NA_SE_SY_FSEL_ERROR);
        }
    } else if (CHECK_BTN_ALL(input->press.button, BTN_B)) {
        gSaveContext.gameMode = 1;
        STOP_GAMESTATE(&this->state);
        SET_NEXT_GAMESTATE_TEST(&this->state, Opening_Init, OpeningContext);
    } else {
        if (ABS_ALT(this->stickRelY) > 30) {
            play_sound(NA_SE_SY_FSEL_CURSOR);
            if (this->stickRelY > 30) {
                this->buttonIndex--;
                if (this->buttonIndex == 2) {
                    this->buttonIndex = 1;
                }
                if (this->buttonIndex < 0) {
                    this->buttonIndex = 5;
                }
            } else {
                this->buttonIndex++;
                if (this->buttonIndex == 2) {
                    this->buttonIndex = 3;
                }
                if (this->buttonIndex >= 6) {
                    this->buttonIndex = 0;
                }
            }
        }
        if (this->buttonIndex == 3) {
            if (gSaveContext.unk_3F3F == 0) {
                if (!SLOT_OCCUPIED(sramCtx, 0) && !SLOT_OCCUPIED(sramCtx, 1) && !SLOT_OCCUPIED(sramCtx, 2)) {
                    this->warningButtonIndex = this->buttonIndex;
                    this->warningLabel = 0;
                    this->emptyFileTextAlpha = 255;
                } else if (SLOT_OCCUPIED(sramCtx, 0) && SLOT_OCCUPIED(sramCtx, 1) && SLOT_OCCUPIED(sramCtx, 2)) {
                    this->warningButtonIndex = this->buttonIndex;
                    this->warningLabel = 2;
                    this->emptyFileTextAlpha = 255;
                } else {
                    this->warningLabel = -1;
                }
            } else {
                if (!FILE_CHOOSE_SLOT_OCCUPIED(this, 0) && !FILE_CHOOSE_SLOT_OCCUPIED(this, 1) &&
                    !FILE_CHOOSE_SLOT_OCCUPIED(this, 2)) {
                    this->warningButtonIndex = this->buttonIndex;
                    this->warningLabel = 0;
                    this->emptyFileTextAlpha = 255;
                } else if (FILE_CHOOSE_SLOT_OCCUPIED(this, 0) && FILE_CHOOSE_SLOT_OCCUPIED(this, 1) &&
                           FILE_CHOOSE_SLOT_OCCUPIED(this, 2)) {
                    this->warningButtonIndex = this->buttonIndex;
                    this->warningLabel = 2;
                    this->emptyFileTextAlpha = 255;
                } else {
                    this->warningLabel = -1;
                }
            }
        } else if (this->buttonIndex == 4) {
            if (gSaveContext.unk_3F3F == 0) {
                if (!SLOT_OCCUPIED(sramCtx, 0) && !SLOT_OCCUPIED(sramCtx, 1) && !SLOT_OCCUPIED(sramCtx, 2)) {
                    this->warningButtonIndex = this->buttonIndex;
                    this->warningLabel = 1;
                    this->emptyFileTextAlpha = 255;
                } else {
                    this->warningLabel = -1;
                }
            } else {
                if (!FILE_CHOOSE_SLOT_OCCUPIED(this, 0) && !FILE_CHOOSE_SLOT_OCCUPIED(this, 1) &&
                    !FILE_CHOOSE_SLOT_OCCUPIED(this, 2)) {
                    this->warningButtonIndex = this->buttonIndex;
                    this->warningLabel = 1;
                    this->emptyFileTextAlpha = 255;
                } else {
                    this->warningLabel = -1;
                }
            }
        } else {
            this->warningLabel = -1;
        }
    }
}

void func_8080D164(GameState* thisx) {
}

void func_8080D170(GameState* thisx) {
    static s16 D_80814564 = 0;
    FileSelectState* this = (FileSelectState*)thisx;

    D_80814564 += 2;
    if (D_80814564 == 0xFE) {
        this->configMode = this->nextConfigMode;
        D_80814564 = 0;
    }
}

void FileSelect_RotateToNameEntry(GameState* thisx) {
    FileSelectState* this = (FileSelectState*)thisx;

    this->windowRot += 50.0f;

    if (this->windowRot >= 314.0f) {
        this->windowRot = 314.0f;
        this->configMode = 35;
    }
}

void FileSelect_RotateToOptions(GameState* thisx) {
    FileSelectState* this = (FileSelectState*)thisx;

    this->windowRot += 50.0f;

    if (this->windowRot >= 314.0f) {
        this->windowRot = 314.0f;
        this->configMode = 40;
    }
}

void FileSelect_RotateToMain(GameState* thisx) {
    FileSelectState* this = (FileSelectState*)thisx;

    this->windowRot += 50.0f;

    if (this->windowRot >= 628.0f) {
        this->windowRot = 0.0f;
        this->configMode = 2;
    }
}

// End of Config Mode Update Functions

// Nameset
void func_80804010(GameState* thisx);
void func_808041A0(GameState* thisx);
void func_80804654(GameState* thisx);
void func_808047D8(GameState* thisx);
void func_8080489C(GameState* thisx);
void func_80804DAC(GameState* thisx);
void func_80804E74(GameState* thisx);
void func_80804F98(GameState* thisx);
void func_8080525C(GameState* thisx);
void func_808052B0(GameState* thisx);
void func_808054A4(GameState* thisx);
void func_808055D0(GameState* thisx);
void func_808058A4(GameState* thisx);
void func_80805918(GameState* thisx);
void func_80805A58(GameState* thisx);
void func_80805B30(GameState* thisx);
void func_80805C1C(GameState* thisx);
void func_80806014(GameState* thisx);
void func_80806148(GameState* thisx);
void func_80806310(GameState* thisx);
void func_808067E0(GameState* thisx);
void func_80806BC8(GameState* thisx);
void func_80806CA0(GameState* thisx);
void func_80806E84(GameState* thisx);
void func_80806F30(GameState* thisx);
void func_808071E4(GameState* thisx);
void func_80807390(GameState* thisx);
void func_8080742C(GameState* thisx);
void func_808074B4(GameState* thisx);
void func_808077AC(GameState* thisx);

// Copy/erase?
void FileSelect_StartNameEntry(GameState* thisx);
void func_80809EA0(GameState* thisx);
void func_8080A3CC(GameState* thisx);
void FileSelect_StartOptions(GameState* thisx);
void func_8080A4A0(GameState* thisx);
void func_8080A6BC(GameState* thisx);

void (*gConfigModeUpdateFuncs[])(GameState*) = {
    FileSelect_StartFadeIn,
    FileSelect_FinishFadeIn,
    FileSelect_UpdateMainMenu,
    func_80804010,
    func_808041A0,
    func_80804654,
    func_808047D8,
    func_8080489C,
    func_80804DAC,
    func_80804E74,
    func_80804F98,
    func_8080525C,
    func_808052B0,
    func_808054A4,
    func_808055D0,
    func_808058A4,
    func_80805918,
    func_80805A58,
    func_80805B30,
    func_80805C1C,
    func_80806014,
    func_80806148,
    func_80806310,
    func_808067E0,
    func_80806BC8,
    func_80806CA0,
    func_80806E84,
    func_80806F30,
    func_808071E4,
    func_80807390,
    func_8080742C,
    func_808074B4,
    func_808077AC,
    func_8080D164,
    FileSelect_RotateToNameEntry,
    FileSelect_StartNameEntry,
    func_80809EA0,
    func_8080A3CC,
    FileSelect_RotateToMain,
    FileSelect_RotateToOptions,
    FileSelect_StartOptions,
    func_8080A4A0,
    func_8080A6BC,
    FileSelect_RotateToMain,
    func_8080D170,
};

s16 sCursorAlphaTargets[] = { 70, 200 };
/**
 * Updates the alpha of the cursor to make it pulsate.
 */
void FileSelect_PulsateCursor(FileSelectState* this) {
    s32 step = ABS_ALT(this->highlightColor[3] - sCursorAlphaTargets[this->highlightPulseDir]) / this->highlightTimer;

    if (this->highlightColor[3] >= sCursorAlphaTargets[this->highlightPulseDir]) {
        this->highlightColor[3] -= step;
    } else {
        this->highlightColor[3] += step;
    }

    this->highlightTimer--;

    if (this->highlightTimer == 0) {
        this->highlightColor[3] = sCursorAlphaTargets[this->highlightPulseDir];
        this->highlightTimer = 20;
        this->highlightPulseDir ^= 1;
    }
}

void FileSelect_ConfigModeUpdate(GameState* thisx) {
    FileSelectState* this = (FileSelectState*)thisx;

    gConfigModeUpdateFuncs[this->configMode](&this->state);
}

void FileSelect_SetWindowVtx(GameState* thisx) {
    FileSelectState* this = (FileSelectState*)thisx;
    s16 i;
    s16 j;
    s16 x;
    s32 tmp;
    s32 tmp2;
    s32 tmp3;

    this->windowVtx = GRAPH_ALLOC(this->state.gfxCtx, sizeof(Vtx) * 80);
    tmp = this->windowPosX - 90;

    for (x = 0, i = 0; i < 4; i++) {
        tmp += 0x40;
        tmp2 = (i == 3) ? 0x30 : 0x40;

        for (j = 0, tmp3 = 0x50; j < 5; j++, x += 4, tmp3 -= 0x20) {
            this->windowVtx[x].v.ob[0] = this->windowVtx[x + 2].v.ob[0] = tmp;

            this->windowVtx[x + 1].v.ob[0] = this->windowVtx[x + 3].v.ob[0] = tmp2 + tmp;

            this->windowVtx[x].v.ob[1] = this->windowVtx[x + 1].v.ob[1] = tmp3;

            this->windowVtx[x + 2].v.ob[1] = this->windowVtx[x + 3].v.ob[1] = tmp3 - 0x20;

            this->windowVtx[x].v.ob[2] = this->windowVtx[x + 1].v.ob[2] = this->windowVtx[x + 2].v.ob[2] =
                this->windowVtx[x + 3].v.ob[2] = 0;

            this->windowVtx[x].v.flag = this->windowVtx[x + 1].v.flag = this->windowVtx[x + 2].v.flag =
                this->windowVtx[x + 3].v.flag = 0;

            this->windowVtx[x].v.tc[0] = this->windowVtx[x].v.tc[1] = this->windowVtx[x + 1].v.tc[1] =
                this->windowVtx[x + 2].v.tc[0] = 0;

            this->windowVtx[x + 1].v.tc[0] = this->windowVtx[x + 3].v.tc[0] = tmp2 * 0x20;

            this->windowVtx[x + 2].v.tc[1] = this->windowVtx[x + 3].v.tc[1] = 0x400;

            this->windowVtx[x].v.cn[0] = this->windowVtx[x + 2].v.cn[0] = this->windowVtx[x].v.cn[1] =
                this->windowVtx[x + 2].v.cn[1] = this->windowVtx[x].v.cn[2] = this->windowVtx[x + 2].v.cn[2] =
                    this->windowVtx[x + 1].v.cn[0] = this->windowVtx[x + 3].v.cn[0] = this->windowVtx[x + 1].v.cn[1] =
                        this->windowVtx[x + 3].v.cn[1] = this->windowVtx[x + 1].v.cn[2] =
                            this->windowVtx[x + 3].v.cn[2] = this->windowVtx[x].v.cn[3] =
                                this->windowVtx[x + 2].v.cn[3] = this->windowVtx[x + 1].v.cn[3] =
                                    this->windowVtx[x + 3].v.cn[3] = 255;
        }
    }
}

s16 D_80814620[] = { 8, 8, 8, 0 };
s16 D_80814628[] = { 12, 12, 12, 0 };
s16 D_80814630[] = { 12, 12, 12, 0 };
s16 D_80814638[] = {
    88, 104, 120, 940, 944, 948,
};
s16 D_80814644[] = { 88, 104, 120, 944 };
s16 D_8081464C[] = { 940, 944 };
s16 D_80814650[] = { 940, 944 };
#ifdef NON_EQUIVALENT
void FileSelect_SetWindowContentVtx(GameState* thisx) {
    FileSelectState* this = (FileSelectState*)thisx;
    u16 i;       // u16
    s16 j;       // s16
    u16 spA4[3]; // u16
    s32 sp9C;    // s32
    s32 sp98;    // s32
    s32 var_s1;
    s16 var_a3; // s16
    s32 temp_t5;

    this->windowContentVtx = GRAPH_ALLOC(this->state.gfxCtx, 0x3C00);

    for (i = 0; i < 0x3C0; i += 4) {
        this->windowContentVtx[i + 0].v.ob[0] = this->windowContentVtx[i + 2].v.ob[0] = 0x12C;

        this->windowContentVtx[i + 1].v.ob[0] = this->windowContentVtx[i + 3].v.ob[0] =
            this->windowContentVtx[i + 0].v.ob[0] + 0x10;

        this->windowContentVtx[i + 0].v.ob[1] = this->windowContentVtx[i + 1].v.ob[1] = 0;

        this->windowContentVtx[i + 2].v.ob[1] = this->windowContentVtx[i + 3].v.ob[1] =
            this->windowContentVtx[i + 0].v.ob[1] - 0x10;

        this->windowContentVtx[i + 0].v.ob[2] = this->windowContentVtx[i + 1].v.ob[2] =
            this->windowContentVtx[i + 2].v.ob[2] = this->windowContentVtx[i + 3].v.ob[2] = 0;

        this->windowContentVtx[i + 0].v.flag = this->windowContentVtx[i + 1].v.flag =
            this->windowContentVtx[i + 2].v.flag = this->windowContentVtx[i + 3].v.flag = 0;

        this->windowContentVtx[i + 0].v.tc[0] = this->windowContentVtx[i + 0].v.tc[1] =
            this->windowContentVtx[i + 1].v.tc[1] = this->windowContentVtx[i + 2].v.tc[0] = 0;

        this->windowContentVtx[i + 1].v.tc[0] = this->windowContentVtx[i + 2].v.tc[1] =
            this->windowContentVtx[i + 3].v.tc[0] = this->windowContentVtx[i + 3].v.tc[1] = 0x200;

        this->windowContentVtx[i + 0].v.cn[0] = this->windowContentVtx[i + 1].v.cn[0] =
            this->windowContentVtx[i + 2].v.cn[0] = this->windowContentVtx[i + 3].v.cn[0] =
                this->windowContentVtx[i + 0].v.cn[1] = this->windowContentVtx[i + 1].v.cn[1] =
                    this->windowContentVtx[i + 2].v.cn[1] = this->windowContentVtx[i + 3].v.cn[1] =
                        this->windowContentVtx[i + 0].v.cn[2] = this->windowContentVtx[i + 1].v.cn[2] =
                            this->windowContentVtx[i + 2].v.cn[2] = this->windowContentVtx[i + 3].v.cn[2] =
                                this->windowContentVtx[i + 0].v.cn[3] = this->windowContentVtx[i + 1].v.cn[3] =
                                    this->windowContentVtx[i + 2].v.cn[3] = this->windowContentVtx[i + 3].v.cn[3] =
                                        0xFF;
    }

    this->windowContentVtx[0].v.ob[0] = this->windowContentVtx[2].v.ob[0] = this->windowPosX;
    this->windowContentVtx[1].v.ob[0] = this->windowContentVtx[3].v.ob[0] = this->windowContentVtx[0].v.ob[0] + 0x80;
    this->windowContentVtx[0].v.ob[1] = this->windowContentVtx[1].v.ob[1] = 0x48;
    this->windowContentVtx[2].v.ob[1] = this->windowContentVtx[3].v.ob[1] = this->windowContentVtx[0].v.ob[1] - 0x10;
    this->windowContentVtx[1].v.tc[0] = this->windowContentVtx[3].v.tc[0] = 0x1000;

    for (i = 4, var_a3 = 0; var_a3 < 3; var_a3++) {
        var_s1 = this->windowPosX - 6;

        for (j = 0; j < 7; j++, i += 4) {
            this->windowContentVtx[i + 0].v.ob[0] = this->windowContentVtx[i + 2].v.ob[0] = var_s1;

            this->windowContentVtx[i + 1].v.ob[0] = this->windowContentVtx[i + 3].v.ob[0] =
                this->windowContentVtx[i + 0].v.ob[0] + sFileInfoBoxPartWidths[j];

            this->windowContentVtx[i + 0].v.ob[1] = this->windowContentVtx[i + 1].v.ob[1] =
                this->fileNamesY[var_a3] + 0x2C;

            this->windowContentVtx[i + 2].v.ob[1] = this->windowContentVtx[i + 3].v.ob[1] =
                this->windowContentVtx[i + 0].v.ob[1] - 0x38;

            this->windowContentVtx[i + 1].v.tc[0] = this->windowContentVtx[i + 3].v.tc[0] = sFileInfoBoxPartWidths[j]
                                                                                            << 5;

            this->windowContentVtx[i + 2].v.tc[1] = this->windowContentVtx[i + 3].v.tc[1] = 0x700;

            var_s1 += sFileInfoBoxPartWidths[j];
        }
    }

    var_s1 = this->windowPosX - 6;
    sp9C = 0x2C;

    for (j = 0; j < 3; j++, i += 16, sp9C -= 0x10) {
        this->windowContentVtx[i + 0].v.ob[0] = this->windowContentVtx[i + 2].v.ob[0] = var_s1;

        this->windowContentVtx[i + 1].v.ob[0] = this->windowContentVtx[i + 3].v.ob[0] =
            this->windowContentVtx[i + 0].v.ob[0] + 0x40;

        this->windowContentVtx[i + 0].v.ob[1] = this->windowContentVtx[i + 1].v.ob[1] = this->buttonYOffsets[j] + sp9C;

        this->windowContentVtx[i + 2].v.ob[1] = this->windowContentVtx[i + 3].v.ob[1] =
            this->windowContentVtx[i + 0].v.ob[1] - 0x10;

        this->windowContentVtx[i + 1].v.tc[0] = this->windowContentVtx[i + 3].v.tc[0] = 0x800;

        this->windowContentVtx[i + 4].v.ob[0] = this->windowContentVtx[i + 6].v.ob[0] = var_s1 + 0x40;

        this->windowContentVtx[i + 5].v.ob[0] = this->windowContentVtx[i + 7].v.ob[0] =
            this->windowContentVtx[i + 4].v.ob[0] + 0x6C;

        this->windowContentVtx[i + 4].v.ob[1] = this->windowContentVtx[i + 5].v.ob[1] = this->buttonYOffsets[j] + sp9C;

        this->windowContentVtx[i + 6].v.ob[1] = this->windowContentVtx[i + 7].v.ob[1] =
            this->windowContentVtx[i + 4].v.ob[1] - 0x10;

        this->windowContentVtx[i + 5].v.tc[0] = this->windowContentVtx[i + 7].v.tc[0] = 0xD80;

        this->windowContentVtx[i + 8].v.ob[0] = this->windowContentVtx[i + 10].v.ob[0] = var_s1 + 0x34;

        this->windowContentVtx[i + 9].v.ob[0] = this->windowContentVtx[i + 11].v.ob[0] =
            this->windowContentVtx[i + 8].v.ob[0] + 0x18;

        this->windowContentVtx[i + 8].v.ob[1] = this->windowContentVtx[i + 9].v.ob[1] = this->buttonYOffsets[j] + sp9C;

        this->windowContentVtx[i + 10].v.ob[1] = this->windowContentVtx[i + 11].v.ob[1] =
            this->windowContentVtx[i + 8].v.ob[1] - 0x10;

        this->windowContentVtx[i + 9].v.tc[0] = this->windowContentVtx[i + 11].v.tc[0] = 0x300;

        this->windowContentVtx[i + 12].v.ob[0] = this->windowContentVtx[i + 14].v.ob[0] = var_s1 + 0xA9;

        this->windowContentVtx[i + 13].v.ob[0] = this->windowContentVtx[i + 15].v.ob[0] =
            this->windowContentVtx[i + 12].v.ob[0] + 0x34;

        this->windowContentVtx[i + 12].v.ob[1] = this->windowContentVtx[i + 13].v.ob[1] =
            this->buttonYOffsets[j] + sp9C;

        this->windowContentVtx[i + 14].v.ob[1] = this->windowContentVtx[i + 15].v.ob[1] =
            this->windowContentVtx[i + 12].v.ob[1] - 0x10;

        this->windowContentVtx[i + 13].v.tc[0] = this->windowContentVtx[i + 15].v.tc[0] = 0x680;
    }

    sp9C = 0x2C;

    for (j = 0; j < 3; j++, sp9C -= 16) {
        if (gSaveContext.unk_3F3F != 0) {
            if (this->unk_2446A[j] != 0) {
                j += 2;
            }

            var_s1 = this->windowPosX - 6;

            if ((this->configMode == 0x10) && (j == this->fileNum)) {
                sp98 = this->fileNamesY[j] + 0x2C;
            } else if (((this->configMode == 0x11) || (this->configMode == 0x12)) && (j == this->fileNum)) {
                sp98 = this->buttonYOffsets[j] + sp9C;
            } else {
                sp98 = sp9C + this->buttonYOffsets[j] + this->fileNamesY[j];
            }

            sp98 -= 2;

            for (var_a3 = 0; var_a3 < 8; var_a3++, i += 4, var_s1 += 0xA) {

                this->windowContentVtx[i + 0].v.ob[0] = this->windowContentVtx[i + 2].v.ob[0] =
                    D_80814280[this->unk_24414[j][var_a3]] + var_s1 + 0x4E;

                this->windowContentVtx[i + 1].v.ob[0] = this->windowContentVtx[i + 3].v.ob[0] =
                    this->windowContentVtx[i + 0].v.ob[0] + 0xB;

                this->windowContentVtx[i + 0].v.ob[1] = this->windowContentVtx[i + 1].v.ob[1] = sp98;

                this->windowContentVtx[i + 2].v.ob[1] = this->windowContentVtx[i + 3].v.ob[1] =
                    this->windowContentVtx[i + 0].v.ob[1] - 0xC;

                this->windowContentVtx[i + 32].v.ob[0] = this->windowContentVtx[i + 34].v.ob[0] =
                    D_80814280[this->unk_24414[j][var_a3]] + var_s1 + 0x4F;

                this->windowContentVtx[i + 33].v.ob[0] = this->windowContentVtx[i + 35].v.ob[0] =
                    this->windowContentVtx[i + 32].v.ob[0] + 0xB;

                this->windowContentVtx[i + 32].v.ob[1] = this->windowContentVtx[i + 33].v.ob[1] = sp98 - 1;

                this->windowContentVtx[i + 34].v.ob[1] = this->windowContentVtx[i + 35].v.ob[1] =
                    this->windowContentVtx[i + 32].v.ob[1] - 0xC;
            }

            var_s1 = this->windowPosX + 14;
            i += 32;
            FileSelect_SplitNumber(this->rupees[j], &spA4[0], &spA4[1], &spA4[2]);

            sp98 -= 0x18;
            for (var_a3 = 0; var_a3 < 3; var_a3++, i += 4) {

                this->windowContentVtx[i + 0].v.ob[0] = this->windowContentVtx[i + 2].v.ob[0] =
                    D_80814280[spA4[D_80814554[this->unk_24474[j]] + i]] + var_s1;

                this->windowContentVtx[i + 1].v.ob[0] = this->windowContentVtx[i + 3].v.ob[0] =
                    D_80814628[var_a3] + this->windowContentVtx[i + 0].v.ob[0];

                this->windowContentVtx[i + 0].v.ob[1] = this->windowContentVtx[i + 1].v.ob[1] = sp98;

                this->windowContentVtx[i + 2].v.ob[1] = this->windowContentVtx[i + 3].v.ob[1] =
                    this->windowContentVtx[i + 0].v.ob[1] - D_80814630[var_a3];

                this->windowContentVtx[i + 12].v.ob[0] = this->windowContentVtx[i + 14].v.ob[0] =
                    this->windowContentVtx[i + 0].v.ob[0] + 1;

                this->windowContentVtx[i + 13].v.ob[0] = this->windowContentVtx[i + 15].v.ob[0] =
                    D_80814628[var_a3] + this->windowContentVtx[i + 12].v.ob[0];

                this->windowContentVtx[i + 12].v.ob[1] = this->windowContentVtx[i + 13].v.ob[1] = sp98 - 1;

                this->windowContentVtx[i + 14].v.ob[1] = this->windowContentVtx[i + 15].v.ob[1] =
                    this->windowContentVtx[i + 12].v.ob[1] - D_80814630[var_a3];

                var_s1 += D_80814620[var_a3];
            }

            i += 12;
            var_s1 = this->windowPosX + 42;

            FileSelect_SplitNumber(this->maskCount[j], &spA4[0], &spA4[1], &spA4[2]);

            sp98 -= 0x2A;

            for (var_a3 = 1; var_a3 < 3; var_a3++, i += 4) {

                this->windowContentVtx[i + 0].v.ob[0] = this->windowContentVtx[i + 2].v.ob[0] =
                    D_80814280[spA4[var_a3]] + var_s1;

                this->windowContentVtx[i + 1].v.ob[0] = this->windowContentVtx[i + 3].v.ob[0] =
                    D_80814628[var_a3] + this->windowContentVtx[i + 0].v.ob[0];

                this->windowContentVtx[i + 0].v.ob[1] = this->windowContentVtx[i + 1].v.ob[1] = sp98;

                this->windowContentVtx[i + 2].v.ob[1] = this->windowContentVtx[i + 3].v.ob[1] =
                    this->windowContentVtx[i + 0].v.ob[1] - D_80814630[var_a3];

                this->windowContentVtx[i + 8].v.ob[0] = this->windowContentVtx[i + 10].v.ob[0] =
                    this->windowContentVtx[i + 0].v.ob[0] + 1;

                this->windowContentVtx[i + 9].v.ob[0] = this->windowContentVtx[i + 11].v.ob[0] =
                    D_80814628[var_a3] + this->windowContentVtx[i + 8].v.ob[0];

                this->windowContentVtx[i + 8].v.ob[1] = this->windowContentVtx[i + 9].v.ob[1] = sp98 - 1;

                this->windowContentVtx[i + 10].v.ob[1] = this->windowContentVtx[i + 11].v.ob[1] =
                    this->windowContentVtx[i + 8].v.ob[1] - D_80814630[var_a3];

                var_s1 += D_80814620[var_a3];
            }

            var_s1 = this->windowPosX + 0x3F;
            i += 8;

            var_a3 = 0;
            sp98 -= 0x10;
            for (; var_a3 < 20; var_a3++, i += 4, var_s1 += 9) {

                this->windowContentVtx[i + 0].v.ob[0] = this->windowContentVtx[i + 2].v.ob[0] = var_s1;

                this->windowContentVtx[i + 1].v.ob[0] = this->windowContentVtx[i + 3].v.ob[0] =
                    this->windowContentVtx[i + 0].v.ob[0] + 0xA;

                this->windowContentVtx[i + 0].v.ob[1] = this->windowContentVtx[i + 1].v.ob[1] = sp98;

                this->windowContentVtx[i + 2].v.ob[1] = this->windowContentVtx[i + 3].v.ob[1] =
                    this->windowContentVtx[i + 0].v.ob[1] - 0xA;

                if (var_a3 == 9) {
                    var_s1 = this->windowPosX + 54;
                    sp98 -= 8;
                }
            }

            var_s1 = this->windowPosX + 64;
            var_a3 = 0;
            sp98 -= 0x20;

            for (; var_a3 < 4; var_a3++, i += 4, var_s1 += 0x18) {

                this->windowContentVtx[i + 0].v.ob[0] = this->windowContentVtx[i + 2].v.ob[0] = var_s1;

                this->windowContentVtx[i + 1].v.ob[0] = this->windowContentVtx[i + 3].v.ob[0] =
                    this->windowContentVtx[i + 0].v.ob[0] + 0x14;

                this->windowContentVtx[i + 0].v.ob[1] = this->windowContentVtx[i + 1].v.ob[1] = sp98;

                this->windowContentVtx[i + 2].v.ob[1] = this->windowContentVtx[i + 3].v.ob[1] =
                    this->windowContentVtx[i + 0].v.ob[1] - 0x14;

                this->windowContentVtx[i + 1].v.tc[0] = this->windowContentVtx[i + 2].v.tc[1] =
                    this->windowContentVtx[i + 3].v.tc[0] = this->windowContentVtx[i + 3].v.tc[1] = 0x400;
            }

            // sp98 -= 0x15;

            this->windowContentVtx[i + 0].v.ob[0] = this->windowContentVtx[i + 2].v.ob[0] = this->windowPosX - 1;

            this->windowContentVtx[i + 1].v.ob[0] = this->windowContentVtx[i + 3].v.ob[0] =
                this->windowContentVtx[i + 0].v.ob[0] + 0x10;

            this->windowContentVtx[i + 0].v.ob[1] = this->windowContentVtx[i + 1].v.ob[1] = sp98 - 0x15;

            this->windowContentVtx[i + 2].v.ob[1] = this->windowContentVtx[i + 3].v.ob[1] =
                this->windowContentVtx[i + 0].v.ob[1] - 0x10;

            this->windowContentVtx[i + 1].v.tc[0] = this->windowContentVtx[i + 3].v.tc[0] = 0x200;
            this->windowContentVtx[i + 2].v.tc[1] = this->windowContentVtx[i + 3].v.tc[1] = 0x200;

            i += 4;

            this->windowContentVtx[i + 0].v.ob[0] = this->windowContentVtx[i + 2].v.ob[0] = this->windowPosX + 0x27;

            this->windowContentVtx[i + 1].v.ob[0] = this->windowContentVtx[i + 3].v.ob[0] =
                this->windowContentVtx[i + 0].v.ob[0] + 0x18;

            this->windowContentVtx[i + 0].v.ob[1] = this->windowContentVtx[i + 1].v.ob[1] = sp98 - 0x15;

            this->windowContentVtx[i + 2].v.ob[1] = this->windowContentVtx[i + 3].v.ob[1] =
                this->windowContentVtx[i + 0].v.ob[1] - 0x10;

            this->windowContentVtx[i + 1].v.tc[0] = this->windowContentVtx[i + 3].v.tc[0] = 0x300;
            this->windowContentVtx[i + 2].v.tc[1] = this->windowContentVtx[i + 3].v.tc[1] = 0x200;

            i += 4;

            // sp98 -= 0x27;

            this->windowContentVtx[i + 0].v.ob[0] = this->windowContentVtx[i + 2].v.ob[0] = this->windowPosX - 10;

            this->windowContentVtx[i + 1].v.ob[0] = this->windowContentVtx[i + 3].v.ob[0] =
                this->windowContentVtx[i + 0].v.ob[0] + 0x40;

            this->windowContentVtx[i + 0].v.ob[1] = this->windowContentVtx[i + 1].v.ob[1] = sp98 - 0x27;

            this->windowContentVtx[i + 2].v.ob[1] = this->windowContentVtx[i + 3].v.ob[1] =
                this->windowContentVtx[i + 0].v.ob[1] - 0x10;

            this->windowContentVtx[i + 1].v.tc[0] = this->windowContentVtx[i + 3].v.tc[0] = 0x800;
            this->windowContentVtx[i + 2].v.tc[1] = this->windowContentVtx[i + 3].v.tc[1] = 0x200;

            this->windowContentVtx[i + 4].v.ob[0] = this->windowContentVtx[i + 6].v.ob[0] =
                this->windowContentVtx[i + 0].v.ob[0] + 1;

            this->windowContentVtx[i + 5].v.ob[0] = this->windowContentVtx[i + 7].v.ob[0] =
                this->windowContentVtx[i + 4].v.ob[0] + 0x40;

            this->windowContentVtx[i + 4].v.ob[1] = this->windowContentVtx[i + 5].v.ob[1] = sp98 - 0x28;

            this->windowContentVtx[i + 6].v.ob[1] = this->windowContentVtx[i + 7].v.ob[1] =
                this->windowContentVtx[i + 4].v.ob[1] - 0x10;

            this->windowContentVtx[i + 5].v.tc[0] = this->windowContentVtx[i + 7].v.tc[0] = 0x800;

            this->windowContentVtx[i + 6].v.tc[1] = this->windowContentVtx[i + 7].v.tc[1] = 0x200;

            i += 8;

            var_s1 = this->windowPosX + 0xA3;

            if ((this->configMode == 0x10) && (j == this->fileNum)) {
                sp98 = this->fileNamesY[j] + 0x2C;
            } else if (((this->configMode == 0x11) || (this->configMode == 0x12)) && (j == this->fileNum)) {
                sp98 = this->buttonYOffsets[j] + sp9C;
            } else {
                sp98 = sp9C + this->buttonYOffsets[j] + this->fileNamesY[j];
            }

            this->windowContentVtx[i + 0].v.ob[0] = this->windowContentVtx[i + 2].v.ob[0] = var_s1 + 0xE;

            this->windowContentVtx[i + 1].v.ob[0] = this->windowContentVtx[i + 3].v.ob[0] =
                this->windowContentVtx[i + 0].v.ob[0] + 0x18;

            this->windowContentVtx[i + 0].v.ob[1] = this->windowContentVtx[i + 1].v.ob[1] = sp98 - 2;

            this->windowContentVtx[i + 2].v.ob[1] = this->windowContentVtx[i + 3].v.ob[1] =
                this->windowContentVtx[i + 0].v.ob[1] - 0xC;

            this->windowContentVtx[i + 1].v.tc[0] = this->windowContentVtx[i + 3].v.tc[0] = 0x300;
            this->windowContentVtx[i + 2].v.tc[1] = this->windowContentVtx[i + 3].v.tc[1] = 0x180;

            i += 4;

            for (var_a3 = 0; var_a3 < 2; var_a3++, i += 4) {

                this->windowContentVtx[i + 0].v.ob[0] = this->windowContentVtx[i + 2].v.ob[0] = var_s1 + var_a3 + 2;

                this->windowContentVtx[i + 1].v.ob[0] = this->windowContentVtx[i + 3].v.ob[0] =
                    this->windowContentVtx[i + 0].v.ob[0] + 0x30;

                this->windowContentVtx[i + 0].v.ob[1] = this->windowContentVtx[i + 1].v.ob[1] = (sp98 - var_a3) - 0x12;

                this->windowContentVtx[i + 2].v.ob[1] = this->windowContentVtx[i + 3].v.ob[1] =
                    this->windowContentVtx[i + 0].v.ob[1] - 0x18;

                this->windowContentVtx[i + 1].v.tc[0] = this->windowContentVtx[i + 3].v.tc[0] = 0x600;

                this->windowContentVtx[i + 2].v.tc[1] = this->windowContentVtx[i + 3].v.tc[1] = 0x300;
            }

            var_s1 += 6;
            temp_t5 = i;

            for (var_a3 = 0; var_a3 < 5; var_a3++, i += 4, var_s1 += 8) {

                this->windowContentVtx[i + 0].v.ob[0] = this->windowContentVtx[i + 2].v.ob[0] = var_s1;

                this->windowContentVtx[i + 1].v.ob[0] = this->windowContentVtx[i + 3].v.ob[0] =
                    this->windowContentVtx[i + 0].v.ob[0] + 0xC;

                this->windowContentVtx[i + 0].v.ob[1] = this->windowContentVtx[i + 1].v.ob[1] = sp98 - 0x2A;

                this->windowContentVtx[i + 2].v.ob[1] = this->windowContentVtx[i + 3].v.ob[1] =
                    this->windowContentVtx[i + 0].v.ob[1] - 0xC;

                this->windowContentVtx[i + 0x14].v.ob[0] = this->windowContentVtx[i + 0x16].v.ob[0] = var_s1 + 1;

                this->windowContentVtx[i + 0x15].v.ob[0] = this->windowContentVtx[i + 0x17].v.ob[0] =
                    this->windowContentVtx[i + 0x14].v.ob[0] + 0xC;

                this->windowContentVtx[i + 0x14].v.ob[1] = this->windowContentVtx[i + 0x15].v.ob[1] = sp98 - 0x2B;

                this->windowContentVtx[i + 0x16].v.ob[1] = this->windowContentVtx[i + 0x17].v.ob[1] =
                    this->windowContentVtx[i + 0x14].v.ob[1] - 0xC;
            }

            i += 20;

            this->windowContentVtx[temp_t5 + 8].v.ob[0] = this->windowContentVtx[temp_t5 + 10].v.ob[0] =
                this->windowContentVtx[temp_t5 + 8].v.ob[0] + 3;

            this->windowContentVtx[temp_t5 + 9].v.ob[0] = this->windowContentVtx[temp_t5 + 11].v.ob[0] =
                this->windowContentVtx[temp_t5 + 8].v.ob[0] + 0xC;

            this->windowContentVtx[temp_t5 + 0x1C].v.ob[0] = this->windowContentVtx[temp_t5 + 0x1E].v.ob[0] =
                this->windowContentVtx[temp_t5 + 8].v.ob[0] + 1;

            this->windowContentVtx[temp_t5 + 0x1D].v.ob[0] = this->windowContentVtx[temp_t5 + 0x1F].v.ob[0] =
                this->windowContentVtx[temp_t5 + 0x1C].v.ob[0] + 0xC;
        }
    }

    var_s1 = this->windowPosX - 6;
    sp9C = -0xC;

    for (j = 0; j < 2; j++, i += 4, sp9C -= 0x10) {

        this->windowContentVtx[i + 0].v.ob[0] = this->windowContentVtx[i + 2].v.ob[0] = var_s1;

        this->windowContentVtx[i + 1].v.ob[0] = this->windowContentVtx[i + 3].v.ob[0] =
            this->windowContentVtx[i + 0].v.ob[0] + 0x40;

        this->windowContentVtx[i + 0].v.ob[1] = this->windowContentVtx[i + 1].v.ob[1] =
            this->buttonYOffsets[j + 3] + sp9C;

        this->windowContentVtx[i + 2].v.ob[1] = this->windowContentVtx[i + 3].v.ob[1] =
            this->windowContentVtx[i + 0].v.ob[1] - 0x10;

        this->windowContentVtx[i + 1].v.tc[0] = this->windowContentVtx[i + 3].v.tc[0] = 0x800;
    }

    this->windowContentVtx[i + 0].v.ob[0] = this->windowContentVtx[i + 2].v.ob[0] = var_s1;

    this->windowContentVtx[i + 1].v.ob[0] = this->windowContentVtx[i + 3].v.ob[0] =
        this->windowContentVtx[i + 0].v.ob[0] + 0x40;

    this->windowContentVtx[i + 0].v.ob[1] = this->windowContentVtx[i + 1].v.ob[1] = this->buttonYOffsets[5] - 0x34;

    this->windowContentVtx[i + 2].v.ob[1] = this->windowContentVtx[i + 3].v.ob[1] =
        this->windowContentVtx[i + 0].v.ob[1] - 0x10;

    this->windowContentVtx[i + 1].v.tc[0] = this->windowContentVtx[i + 3].v.tc[0] = 0x800;

    i += 4;

    if (((this->menuMode == 1) && (this->configMode >= 2)) || ((this->menuMode == 2) && (this->selectMode == 3))) {
        if (this->menuMode == 1) {
            if ((this->configMode == 4) || (this->configMode == 7) || (this->configMode == 0x16)) {
                j = D_80814644[this->buttonIndex];
            } else if ((this->configMode == 0x19) || (this->configMode == 0xC)) {
                j = D_8081464C[this->buttonIndex];
            } else {
                j = D_80814638[this->buttonIndex];
            }
        } else {
            j = D_80814650[this->confirmButtonIndex];
        }

        this->windowContentVtx[i + 0].v.ob[0] = this->windowContentVtx[i + 2].v.ob[0] = this->windowPosX - 0xA;

        this->windowContentVtx[i + 1].v.ob[0] = this->windowContentVtx[i + 3].v.ob[0] =
            this->windowContentVtx[i + 0].v.ob[0] + 0x48;

        this->windowContentVtx[i + 0].v.ob[1] = this->windowContentVtx[i + 1].v.ob[1] =
            this->windowContentVtx[j].v.ob[1] + 4;

        this->windowContentVtx[i + 2].v.ob[1] = this->windowContentVtx[i + 3].v.ob[1] =
            this->windowContentVtx[i + 0].v.ob[1] - 0x18;

        this->windowContentVtx[i + 1].v.tc[0] = this->windowContentVtx[i + 3].v.tc[0] = 0x900;

        this->windowContentVtx[i + 2].v.tc[1] = this->windowContentVtx[i + 3].v.tc[1] = 0x300;
    }

    this->windowContentVtx[i + 4].v.ob[0] = this->windowContentVtx[i + 6].v.ob[0] = this->windowPosX + 0x3A;

    this->windowContentVtx[i + 5].v.ob[0] = this->windowContentVtx[i + 7].v.ob[0] =
        this->windowContentVtx[i + 4].v.ob[0] + 0x80;

    this->windowContentVtx[i + 4].v.ob[1] = this->windowContentVtx[i + 5].v.ob[1] =
        this->windowContentVtx[D_80814638[this->warningButtonIndex]].v.ob[1];

    this->windowContentVtx[i + 6].v.ob[1] = this->windowContentVtx[i + 7].v.ob[1] =
        this->windowContentVtx[i + 4].v.ob[1] - 0x10;

    this->windowContentVtx[i + 5].v.tc[0] = this->windowContentVtx[i + 7].v.tc[0] = 0x1000;
}
#else
void FileSelect_SetWindowContentVtx(GameState* thisx);
#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_file_choose/FileSelect_SetWindowContentVtx.s")
#endif

s16 D_80814654[] = { 0x0088, 0x0194, 0x02A0, 0 };
s32 D_8081465C[] = { 0x0102BCB0, 0x0102CCB0, 0x0102DCB0, 0x0102ECB0 };
s32 D_8081466C[] = { 0x01030130, 0x01030130, 0x01030370, 0x010305B0 };
s32 D_8081467C[] = { 0x01030AF0, 0x01030C70, 0x01030DF0, 0x01030F70 };
s32 D_8081468C[] = {
    0x02000000, 0x02000100, 0x02000200, 0x02000300, 0x02000400,
    0x02000500, 0x02000600, 0x02000700, 0x02000800, 0x02000900,
};
s32 D_808146B4[] = { 0x00010101, 0x01010202, 0x02020203, 0x03030303 };
s32 D_808146C4[] = {
    0x00C800FF, 0x006400AA, 0x00AA00FF, 0x00FF0069, 0x00690000,
};
s32 D_808146D8[] = {
    0x00000050, 0x0000000A, 0x000A0050, 0x0028000A, 0x00000000,
};
s32 D_808146EC[] = { 0x00FF0046, 0x003200C8, 0x00000000 };
s32 D_808146F8[] = { 0x00320028, 0x003C00FF, 0x00FF00FF };
void FileSelect_DrawFileInfo(GameState*, s16);
#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_file_choose/FileSelect_DrawFileInfo.s")

extern void* D_010220B0[]; // gFileSelNameBoxTex
extern void* D_010277B0[]; // gOptionsButtonTex // Array on PAL
extern void* D_0102A030[]; // gFileSelDISKButtonTex in OoT
extern void* D_0102AAB0[]; // gFileSelBigButtonHighlightTex

void* sFileInfoBoxTextures[] = { 0x01022E30, 0x01023DF0, 0x01024DB0, 0x01025D70, 0x01026D30, 0x010287B0, 0x010293F0 };

void* D_80814720[] = { 0x01004980, 0x01005180, 0x01002980, 0x01003180, 0x01003980,
                       0x01004180, 0x01005980, 0x01006180, 0x01006980 };

void* D_80814744[] = { 0x01000000, 0x01000800, 0x01001000, 0x01001800, 0x01002000 };

void* sFileButtonTextures[] = { 0x0101EFB0, 0x0101F7B0, 0x0101FFB0 };

void* D_80814764[] = { 0x0101E7B0, 0x01020FB0, 0x010207B0, 0x01027FB0 };
extern int ENVIRONMENT;
extern int PRIMITIVE;
extern int TEXEL0;
void FileSelect_DrawWindowContents(GameState* thisx) {
    FileSelectState* this = (FileSelectState*)thisx;
    s16 fileIndex;
    s16 temp;
    s16 i;
    s16 quadVtxIndex;

    if (1) {}

    OPEN_DISPS(this->state.gfxCtx);

    // draw title label
    gDPPipeSync(POLY_OPA_DISP++);
    gDPSetCombineLERP(POLY_OPA_DISP++, PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, TEXEL0, 0, PRIMITIVE, 0, PRIMITIVE,
                      ENVIRONMENT, TEXEL0, ENVIRONMENT, TEXEL0, 0, PRIMITIVE, 0);
    gDPSetPrimColor(POLY_OPA_DISP++, 0, 0, 255, 255, 255, this->titleAlpha[0]);
    gDPSetEnvColor(POLY_OPA_DISP++, 0, 0, 0, 0);

    gSPVertex(POLY_OPA_DISP++, &this->windowContentVtx[0], 4, 0);
    gDPLoadTextureBlock(POLY_OPA_DISP++, D_80814720[this->titleLabel], G_IM_FMT_IA, G_IM_SIZ_8b, 128, 16, 0,
                        G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD,
                        G_TX_NOLOD);
    gSP1Quadrangle(POLY_OPA_DISP++, 0, 2, 3, 1, 0);

    // draw next title label
    gDPPipeSync(POLY_OPA_DISP++);
    gDPSetPrimColor(POLY_OPA_DISP++, 0, 0, 255, 255, 255, this->titleAlpha[1]);
    gDPLoadTextureBlock(POLY_OPA_DISP++, D_80814720[this->nextTitleLabel], G_IM_FMT_IA, G_IM_SIZ_8b, 128, 16, 0,
                        G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD,
                        G_TX_NOLOD);
    gSP1Quadrangle(POLY_OPA_DISP++, 0, 2, 3, 1, 0);

    temp = 4;

    gDPPipeSync(POLY_OPA_DISP++);

    // draw file info box (large box when a file is selected)
    for (fileIndex = 0; fileIndex < 3; fileIndex++, temp += 28) {
        if (fileIndex < 2) {
            gDPPipeSync(POLY_OPA_DISP++);
            gDPSetPrimColor(POLY_OPA_DISP++, 0, 0, this->windowColor[0], this->windowColor[1], this->windowColor[2],
                            this->fileInfoAlpha[fileIndex]);
            gSPVertex(POLY_OPA_DISP++, &this->windowContentVtx[temp], 28, 0);

            for (quadVtxIndex = 0, i = 0; i < 7; i++, quadVtxIndex += 4) {
                if ((i < 5) || ((this->unk_2446A[fileIndex] != 0) && (i >= 5))) {
                    gDPLoadTextureBlock(POLY_OPA_DISP++, sFileInfoBoxTextures[i], G_IM_FMT_IA, G_IM_SIZ_16b,
                                        sFileInfoBoxPartWidths[i], 56, 0, G_TX_NOMIRROR | G_TX_WRAP,
                                        G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
                    gSP1Quadrangle(POLY_OPA_DISP++, quadVtxIndex, quadVtxIndex + 2, quadVtxIndex + 3, quadVtxIndex + 1,
                                   0);
                }
            }
        }
    }

    gDPPipeSync(POLY_OPA_DISP++);

    for (i = 0; i < 3; i++, temp += 16) {
        if (i < 2) {
            // draw file button
            gSPVertex(POLY_OPA_DISP++, &this->windowContentVtx[temp], 16, 0);

            gDPSetPrimColor(POLY_OPA_DISP++, 0, 0, sWindowContentColors[0], sWindowContentColors[1],
                            sWindowContentColors[2], this->fileButtonAlpha[i]);
            gDPLoadTextureBlock(POLY_OPA_DISP++, sFileButtonTextures[i], G_IM_FMT_IA, G_IM_SIZ_16b, 64, 16, 0,
                                G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK,
                                G_TX_NOLOD, G_TX_NOLOD);
            gSP1Quadrangle(POLY_OPA_DISP++, 0, 2, 3, 1, 0);

            // draw file name box
            gDPSetPrimColor(POLY_OPA_DISP++, 0, 0, sWindowContentColors[0], sWindowContentColors[1],
                            sWindowContentColors[2], this->nameBoxAlpha[i]);
            gDPLoadTextureBlock(POLY_OPA_DISP++, D_010220B0, G_IM_FMT_IA, G_IM_SIZ_16b, 108, 16, 0,
                                G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK,
                                G_TX_NOLOD, G_TX_NOLOD);
            gSP1Quadrangle(POLY_OPA_DISP++, 4, 6, 7, 5, 0);

            gDPSetPrimColor(POLY_OPA_DISP++, 0, 0, sWindowContentColors[0], sWindowContentColors[1],
                            sWindowContentColors[2], this->connectorAlpha[i]);
            gDPLoadTextureBlock(POLY_OPA_DISP++, D_01002800, G_IM_FMT_IA, G_IM_SIZ_8b, 24, 16, 0,
                                G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK,
                                G_TX_NOLOD, G_TX_NOLOD);
            gSP1Quadrangle(POLY_OPA_DISP++, 8, 10, 11, 9, 0);

            if (this->unk_2446A[i] != 0) {
                gDPSetPrimColor(POLY_OPA_DISP++, 0, 0, sWindowContentColors[0], sWindowContentColors[1],
                                sWindowContentColors[2], this->nameBoxAlpha[i]);
                gDPLoadTextureBlock(POLY_OPA_DISP++, D_0102A030, G_IM_FMT_IA, G_IM_SIZ_16b, 52, 16, 0,
                                    G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK,
                                    G_TX_NOLOD, G_TX_NOLOD);
                gSP1Quadrangle(POLY_OPA_DISP++, 12, 14, 15, 13, 0);
            }
        }
    }

    // draw file info
    for (fileIndex = 0; fileIndex < 2; fileIndex++) {
        FileSelect_DrawFileInfo(&this->state, fileIndex);
    }

    gDPPipeSync(POLY_OPA_DISP++);
    gDPSetCombineLERP(POLY_OPA_DISP++, PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, TEXEL0, 0, PRIMITIVE, 0, PRIMITIVE,
                      ENVIRONMENT, TEXEL0, ENVIRONMENT, TEXEL0, 0, PRIMITIVE, 0);
    gDPSetEnvColor(POLY_OPA_DISP++, 0, 0, 0, 0);
    gSPVertex(POLY_OPA_DISP++, &this->windowContentVtx[0x3AC], 20, 0);

    // draw primary action buttons (copy/erase)
    for (quadVtxIndex = 0, i = 0; i < 2; i++, quadVtxIndex += 4) {
        gDPPipeSync(POLY_OPA_DISP++);
        gDPSetPrimColor(POLY_OPA_DISP++, 0, 0, this->windowColor[0], this->windowColor[1], this->windowColor[2],
                        this->actionButtonAlpha[i]);
        gDPLoadTextureBlock(POLY_OPA_DISP++, D_80814764[i], G_IM_FMT_IA, G_IM_SIZ_16b, 64, 16, 0,
                            G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD,
                            G_TX_NOLOD);
        gSP1Quadrangle(POLY_OPA_DISP++, quadVtxIndex, quadVtxIndex + 2, quadVtxIndex + 3, quadVtxIndex + 1, 0);
    }

    gDPPipeSync(POLY_OPA_DISP++);

    // draw confirm buttons (yes/quit)
    for (quadVtxIndex = 0, i = 0; i < 2; i++, quadVtxIndex += 4) {
        temp = this->confirmButtonTexIndices[i];
        gDPSetPrimColor(POLY_OPA_DISP++, 0, 0, this->windowColor[0], this->windowColor[1], this->windowColor[2],
                        this->confirmButtonAlpha[i]);
        gDPLoadTextureBlock(POLY_OPA_DISP++, D_80814764[temp], G_IM_FMT_IA, G_IM_SIZ_16b, 64, 16, 0,
                            G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD,
                            G_TX_NOLOD);
        gSP1Quadrangle(POLY_OPA_DISP++, quadVtxIndex, quadVtxIndex + 2, quadVtxIndex + 3, quadVtxIndex + 1, 0);
    }

    // draw options button
    gDPPipeSync(POLY_OPA_DISP++);
    gDPSetPrimColor(POLY_OPA_DISP++, 0, 0, this->windowColor[0], this->windowColor[1], this->windowColor[2],
                    this->optionButtonAlpha);
    gDPLoadTextureBlock(POLY_OPA_DISP++, D_010277B0, G_IM_FMT_IA, G_IM_SIZ_16b, 64, 16, 0, G_TX_NOMIRROR | G_TX_WRAP,
                        G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
    gSP1Quadrangle(POLY_OPA_DISP++, 8, 10, 11, 9, 0);

    // draw highlight over currently selected button
    if (((this->menuMode == 1) && ((this->configMode == 2) || (this->configMode == 4) || (this->configMode == 7) ||
                                   (this->configMode == 12) || (this->configMode == 22) || (this->configMode == 25))) ||
        ((this->menuMode == 2) && (this->selectMode == 3))) {
        gDPPipeSync(POLY_OPA_DISP++);

        gDPSetCombineLERP(POLY_OPA_DISP++, 1, 0, PRIMITIVE, 0, TEXEL0, 0, PRIMITIVE, 0, 1, 0, PRIMITIVE, 0, TEXEL0, 0,
                          PRIMITIVE, 0);
        gDPSetPrimColor(POLY_OPA_DISP++, 0, 0, this->highlightColor[0], this->highlightColor[1],
                        this->highlightColor[2], this->highlightColor[3]);
        gDPLoadTextureBlock(POLY_OPA_DISP++, D_0102AAB0, G_IM_FMT_I, G_IM_SIZ_8b, 72, 24, 0, G_TX_NOMIRROR | G_TX_WRAP,
                            G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
        gSP1Quadrangle(POLY_OPA_DISP++, 12, 14, 15, 13, 0);
    }

    // draw warning labels
    if (this->warningLabel > -1) {
        gDPPipeSync(POLY_OPA_DISP++);

        gDPSetCombineLERP(POLY_OPA_DISP++, PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, TEXEL0, 0, PRIMITIVE, 0,
                          PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, TEXEL0, 0, PRIMITIVE, 0);
        gDPSetPrimColor(POLY_OPA_DISP++, 0, 0, 255, 255, 255, this->emptyFileTextAlpha);
        gDPSetEnvColor(POLY_OPA_DISP++, 0, 0, 0, 0);
        gDPLoadTextureBlock(POLY_OPA_DISP++, D_80814744[this->warningLabel], G_IM_FMT_IA, G_IM_SIZ_8b, 128, 16, 0,
                            G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD,
                            G_TX_NOLOD);
        gSP1Quadrangle(POLY_OPA_DISP++, 16, 18, 19, 17, 0);
    }

    gDPPipeSync(POLY_OPA_DISP++);

    gDPSetCombineMode(POLY_OPA_DISP++, G_CC_MODULATEIDECALA, G_CC_MODULATEIDECALA);

    CLOSE_DISPS(this->state.gfxCtx);
}

void FileSelect_DrawNameEntry(GameState*);
void FileSelect_DrawOptions(GameState*);

void FileSelect_ConfigModeDraw(GameState* thisx) {
    FileSelectState* this = (FileSelectState*)thisx;

    OPEN_DISPS(this->state.gfxCtx);

    gDPPipeSync(POLY_OPA_DISP++);

    func_8012C8AC(this->state.gfxCtx);
    FileSelect_RenderView(this, 0.0f, 0.0f, 64.0f);
    FileSelect_SetWindowVtx(&this->state);
    FileSelect_SetWindowContentVtx(&this->state);

    if ((this->configMode != 36) && (this->configMode != 35)) {
        gDPPipeSync(POLY_OPA_DISP++);
        gDPSetCombineMode(POLY_OPA_DISP++, G_CC_MODULATEIA_PRIM, G_CC_MODULATEIA_PRIM);

        gDPSetPrimColor(POLY_OPA_DISP++, 0, 0, this->windowColor[0], this->windowColor[1], this->windowColor[2],
                        this->windowAlpha);
        gDPSetEnvColor(POLY_OPA_DISP++, 0, 0, 0, 0);

        Matrix_Translate(0.0f, 0.0f, -93.6f, MTXMODE_NEW);
        Matrix_Scale(0.78f, 0.78f, 0.78f, MTXMODE_APPLY);

        if (this->windowRot != 0) {
            Matrix_RotateXFApply(this->windowRot / 100.0f);
        }

        gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(this->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);

        gSPVertex(POLY_OPA_DISP++, &this->windowVtx[0], 32, 0);
        gSPDisplayList(POLY_OPA_DISP++, D_010311F0);

        gSPVertex(POLY_OPA_DISP++, &this->windowVtx[32], 32, 0);
        gSPDisplayList(POLY_OPA_DISP++, D_01031408);

        gSPVertex(POLY_OPA_DISP++, &this->windowVtx[64], 16, 0);
        gSPDisplayList(POLY_OPA_DISP++, D_01031618);

        gDPPipeSync(POLY_OPA_DISP++);

        FileSelect_DrawWindowContents(&this->state);
    }

    // draw name entry menu
    if ((this->configMode >= 34) && (this->configMode <= 38)) {
        gDPPipeSync(POLY_OPA_DISP++);
        gDPSetCombineMode(POLY_OPA_DISP++, G_CC_MODULATEIA_PRIM, G_CC_MODULATEIA_PRIM);
        gDPSetPrimColor(POLY_OPA_DISP++, 0, 0, this->windowColor[0], this->windowColor[1], this->windowColor[2],
                        this->windowAlpha);
        gDPSetEnvColor(POLY_OPA_DISP++, 0, 0, 0, 0);

        Matrix_Translate(0.0f, 0.0f, -93.6f, MTXMODE_NEW);
        Matrix_Scale(0.78f, 0.78f, 0.78f, MTXMODE_APPLY);
        Matrix_RotateXFApply((this->windowRot - 314.0f) / 100.0f);

        gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(this->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);

        gSPVertex(POLY_OPA_DISP++, &this->windowVtx[0], 32, 0);
        gSPDisplayList(POLY_OPA_DISP++, D_010311F0);

        gSPVertex(POLY_OPA_DISP++, &this->windowVtx[32], 32, 0);
        gSPDisplayList(POLY_OPA_DISP++, D_01031408);

        gSPVertex(POLY_OPA_DISP++, &this->windowVtx[64], 16, 0);
        gSPDisplayList(POLY_OPA_DISP++, D_01031618);

        gDPPipeSync(POLY_OPA_DISP++);

        FileSelect_DrawNameEntry(&this->state);
    }

    // draw options menu
    if ((this->configMode >= 39) && (this->configMode <= 43)) {
        gDPPipeSync(POLY_OPA_DISP++);
        gDPSetCombineMode(POLY_OPA_DISP++, G_CC_MODULATEIA_PRIM, G_CC_MODULATEIA_PRIM);
        gDPSetPrimColor(POLY_OPA_DISP++, 0, 0, this->windowColor[0], this->windowColor[1], this->windowColor[2],
                        this->windowAlpha);
        gDPSetEnvColor(POLY_OPA_DISP++, 0, 0, 0, 0);

        Matrix_Translate(0.0f, 0.0f, -93.6f, MTXMODE_NEW);
        Matrix_Scale(0.78f, 0.78f, 0.78f, MTXMODE_APPLY);
        Matrix_RotateXFApply((this->windowRot - 314.0f) / 100.0f);

        gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(this->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);

        gSPVertex(POLY_OPA_DISP++, &this->windowVtx[0], 32, 0);
        gSPDisplayList(POLY_OPA_DISP++, D_010311F0);

        gSPVertex(POLY_OPA_DISP++, &this->windowVtx[32], 32, 0);
        gSPDisplayList(POLY_OPA_DISP++, D_01031408);

        gSPVertex(POLY_OPA_DISP++, &this->windowVtx[64], 16, 0);
        gSPDisplayList(POLY_OPA_DISP++, D_01031618);

        gDPPipeSync(POLY_OPA_DISP++);

        FileSelect_DrawOptions(&this->state);
    }

    gDPPipeSync(POLY_OPA_DISP++);

    FileSelect_RenderView(this, 0.0f, 0.0f, 64.0f);

    CLOSE_DISPS(this->state.gfxCtx);
}

void FileSelect_FadeMainToSelect(GameState* thisx) {
    FileSelectState* this = (FileSelectState*)thisx;
    SramContext* sramCtx = &this->sramCtx;
    s16 i;

    for (i = 0; i < 3; i++) {
        if (i != this->buttonIndex) {
            this->fileButtonAlpha[i] -= 50;
            this->actionButtonAlpha[0] = this->actionButtonAlpha[1] = this->optionButtonAlpha =
                this->fileButtonAlpha[i];

            if (gSaveContext.unk_3F3F == 0) {
                if (SLOT_OCCUPIED(sramCtx, i)) {
                    this->nameAlpha[i] = this->nameBoxAlpha[i] = this->fileButtonAlpha[i];
                    this->connectorAlpha[i] -= 63;
                }
            } else {
                if (FILE_CHOOSE_SLOT_OCCUPIED(this, i)) {
                    this->nameAlpha[i] = this->nameBoxAlpha[i] = this->fileButtonAlpha[i];
                    this->connectorAlpha[i] -= 63;
                }
            }
        }
    }

    this->titleAlpha[0] -= 63;
    this->titleAlpha[1] += 63;
    this->actionTimer--;

    if (this->actionTimer == 0) {
        this->actionTimer = 4;
        this->selectMode++;
        this->confirmButtonIndex = 0;
    }
}

// amount to move by to reach the top of the screen
s16 sFileYOffsets[] = { 0, 16, 32 };

void FileSelect_MoveSelectedFileToTop(GameState* thisx) {
    FileSelectState* this = (FileSelectState*)thisx;
    s32 yStep;

    yStep = ABS_ALT(this->buttonYOffsets[this->buttonIndex] - sFileYOffsets[this->buttonIndex]) / this->actionTimer;
    this->buttonYOffsets[this->buttonIndex] += yStep;
    this->actionTimer--;

    if ((this->actionTimer == 0) || (this->buttonYOffsets[this->buttonIndex] == sFileYOffsets[this->buttonIndex])) {
        this->buttonYOffsets[3] = this->buttonYOffsets[4] = -24;
        this->actionTimer = 4;
        this->selectMode++;
    }
}

void FileSelect_FadeInFileInfo(GameState* thisx) {
    FileSelectState* this = (FileSelectState*)thisx;

    this->fileInfoAlpha[this->buttonIndex] += 50;
    this->nameBoxAlpha[this->buttonIndex] -= 100;

    if (this->nameBoxAlpha[this->buttonIndex] <= 0) {
        this->nameBoxAlpha[this->buttonIndex] = 0;
    }
    this->actionTimer--;

    if (this->actionTimer == 0) {
        this->fileInfoAlpha[this->buttonIndex] = 200;
        this->actionTimer = 4;
        this->selectMode++;
    }

    this->confirmButtonAlpha[0] = this->confirmButtonAlpha[1] = this->fileInfoAlpha[this->buttonIndex];
}

void FileSelect_ConfirmFile(GameState* thisx) {
    FileSelectState* this = (FileSelectState*)thisx;
    Input* input = &this->state.input[0];

    if (CHECK_BTN_ALL(input->press.button, BTN_START) || (CHECK_BTN_ALL(input->press.button, BTN_A))) {
        if (this->confirmButtonIndex == 0) {
            Rumble_Request(300.0f, 180, 20, 100);
            play_sound(NA_SE_SY_FSEL_DECIDE_L);
            this->selectMode = 6;
            func_801A4058(0xF);
        } else {
            play_sound(NA_SE_SY_FSEL_CLOSE);
            this->selectMode++;
        }
    } else if CHECK_BTN_ALL (input->press.button, BTN_B) {
        play_sound(NA_SE_SY_FSEL_CLOSE);
        this->selectMode++;
    } else if (ABS_ALT(this->stickRelY) >= 30) {
        play_sound(NA_SE_SY_FSEL_CURSOR);
        this->confirmButtonIndex ^= 1;
    }
}

void FileSelect_FadeOutFileInfo(GameState* thisx) {
    FileSelectState* this = (FileSelectState*)thisx;

    this->fileInfoAlpha[this->buttonIndex] -= 200 / 4;
    this->nameBoxAlpha[this->buttonIndex] += 200 / 4;
    this->actionTimer--;

    if (this->actionTimer == 0) {
        this->buttonYOffsets[3] = this->buttonYOffsets[4] = 0;
        this->nameBoxAlpha[this->buttonIndex] = 200;
        this->fileInfoAlpha[this->buttonIndex] = 0;
        this->nextTitleLabel = 0;
        this->actionTimer = 4;
        this->selectMode++;
    }
    this->confirmButtonAlpha[0] = this->confirmButtonAlpha[1] = this->fileInfoAlpha[this->buttonIndex];
}

void FileSelect_MoveSelectedFileToSlot(GameState* thisx) {
    FileSelectState* this = (FileSelectState*)thisx;
    SramContext* sramCtx = &this->sramCtx;
    s32 yStep;
    s16 i;

    yStep = ABS_ALT(this->buttonYOffsets[this->buttonIndex]) / this->actionTimer;
    this->buttonYOffsets[this->buttonIndex] -= yStep;

    if (this->buttonYOffsets[this->buttonIndex] <= 0) {
        this->buttonYOffsets[this->buttonIndex] = 0;
    }

    for (i = 0; i < 3; i++) {
        if (i != this->buttonIndex) {
            this->fileButtonAlpha[i] += 200 / 4;

            if (this->fileButtonAlpha[i] >= 200) {
                this->fileButtonAlpha[i] = 200;
            }

            this->actionButtonAlpha[0] = this->actionButtonAlpha[1] = this->optionButtonAlpha =
                this->fileButtonAlpha[i];

            if (gSaveContext.unk_3F3F == 0) {
                if (SLOT_OCCUPIED(sramCtx, i)) {
                    this->nameBoxAlpha[i] = this->nameAlpha[i] = this->fileButtonAlpha[i];
                    this->connectorAlpha[i] += 255 / 4;
                }
            } else {
                if (FILE_CHOOSE_SLOT_OCCUPIED(this, i)) {
                    this->nameBoxAlpha[i] = this->nameAlpha[i] = this->fileButtonAlpha[i];
                    this->connectorAlpha[i] += 255 / 4;
                }
            }
        }
    }

    this->titleAlpha[0] -= 255 / 4;
    this->titleAlpha[1] += 255 / 4;
    this->actionTimer--;

    if (this->actionTimer == 0) {
        this->titleAlpha[0] = 255;
        this->titleAlpha[1] = 0;
        this->titleLabel = this->nextTitleLabel;
        this->actionTimer = 4;
        this->menuMode = 1;
        this->configMode = 2;
        this->nextConfigMode = 2;
        this->selectMode = 0;
    }
}

void FileSelect_FadeOut(GameState* thisx) {
    FileSelectState* this = (FileSelectState*)thisx;

    this->screenFillAlpha += 40;
    if (this->screenFillAlpha >= 255) {
        this->screenFillAlpha = 255;
        this->selectMode++;
    }
}

void FileSelect_LoadGame(GameState* thisx) {
    FileSelectState* this = (FileSelectState*)thisx;
    u16 phi_v0;

    gSaveContext.fileNum = this->buttonIndex;
    Sram_OpenSave(this, &this->sramCtx);

    gSaveContext.gameMode = 0;

    STOP_GAMESTATE(&this->state);
    SET_NEXT_GAMESTATE_TEST(&this->state, Play_Init, PlayState);

    gSaveContext.respawnFlag = 0;
    gSaveContext.respawn[0].entranceIndex = 0xFFFF;
    gSaveContext.seqIndex = 0xFF;
    gSaveContext.nightSeqIndex = 0xFF;
    gSaveContext.showTitleCard = 1;
    gSaveContext.dogParams = 0;

    phi_v0 = 0;
    do {
        gSaveContext.unk_3DD0[phi_v0] = 0;
        phi_v0++;
    } while (phi_v0 < 7);

    gSaveContext.unk_3F26 = 0x32;
    gSaveContext.unk_3DC0 = 0;
    gSaveContext.healthAccumulator = 0;
    gSaveContext.unk_3F2C = 0;
    gSaveContext.unk_3F46 = 0;
    gSaveContext.skyboxTime = 0;
    gSaveContext.nextTransitionType = TRANS_NEXT_TYPE_DEFAULT;
    gSaveContext.cutsceneTrigger = 0;
    gSaveContext.unk_3F4D = 0;
    gSaveContext.nextDayTime = 0xFFFF;
    gSaveContext.unk_3DBB = 0;
    gSaveContext.buttonStatus[0] = 0;
    gSaveContext.buttonStatus[1] = 0;
    gSaveContext.buttonStatus[2] = 0;
    gSaveContext.buttonStatus[3] = 0;
    gSaveContext.buttonStatus[4] = 0;
    gSaveContext.unk_3F1E = 0;
    gSaveContext.unk_3F20 = 0;
    gSaveContext.unk_3F22 = 0;
    gSaveContext.unk_3F24 = 0;
    gSaveContext.save.playerData.tatlTimer = 0;
}

void (*gSelectModeUpdateFuncs[])(GameState*) = {
    FileSelect_FadeMainToSelect, FileSelect_MoveSelectedFileToTop,  FileSelect_FadeInFileInfo, FileSelect_ConfirmFile,
    FileSelect_FadeOutFileInfo,  FileSelect_MoveSelectedFileToSlot, FileSelect_FadeOut,        FileSelect_LoadGame,
};

void FileSelect_SelectModeUpdate(GameState* thisx) {
    FileSelectState* this = (FileSelectState*)thisx;

    gSelectModeUpdateFuncs[this->selectMode](&this->state);
}

void FileSelect_SelectModeDraw(GameState* thisx) {
    FileSelectState* this = (FileSelectState*)thisx;

    OPEN_DISPS(this->state.gfxCtx);

    gDPPipeSync(POLY_OPA_DISP++);

    func_8012C8AC(this->state.gfxCtx);
    FileSelect_RenderView(this, 0.0f, 0.0f, 64.0f);
    FileSelect_SetWindowVtx(&this->state);
    FileSelect_SetWindowContentVtx(&this->state);

    gDPSetCombineMode(POLY_OPA_DISP++, G_CC_MODULATEIA_PRIM, G_CC_MODULATEIA_PRIM);
    gDPSetPrimColor(POLY_OPA_DISP++, 0, 0, this->windowColor[0], this->windowColor[1], this->windowColor[2],
                    this->windowAlpha);
    gDPSetEnvColor(POLY_OPA_DISP++, 0, 0, 0, 0);

    Matrix_Translate(0.0f, 0.0f, -93.6f, MTXMODE_NEW);
    Matrix_Scale(0.78f, 0.78f, 0.78f, MTXMODE_APPLY);
    Matrix_RotateXFApply(this->windowRot / 100.0f);
    gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(this->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);

    gSPVertex(POLY_OPA_DISP++, &this->windowVtx[0], 32, 0);
    gSPDisplayList(POLY_OPA_DISP++, D_010311F0);

    gSPVertex(POLY_OPA_DISP++, &this->windowVtx[32], 32, 0);
    gSPDisplayList(POLY_OPA_DISP++, D_01031408);

    gSPVertex(POLY_OPA_DISP++, &this->windowVtx[64], 16, 0);
    gSPDisplayList(POLY_OPA_DISP++, D_01031618);

    FileSelect_DrawWindowContents(&this->state);
    gDPPipeSync(POLY_OPA_DISP++);
    FileSelect_RenderView(this, 0.0f, 0.0f, 64.0f);

    CLOSE_DISPS(this->state.gfxCtx);
}

void FileSelect_UpdateAndDrawSkybox(FileSelectState* this) {
    GraphicsContext* gfxCtx; // TODO: check if this temp is needed, or if it recasts thisx instead
    f32 eyeX;
    f32 eyeY;
    f32 eyeZ;

    gfxCtx = this->state.gfxCtx;
    OPEN_DISPS(gfxCtx);

    gDPPipeSync(POLY_OPA_DISP++);

    eyeX = 1000.0f * Math_CosS(sFileSelectSkyboxRotation) - 1000.0f * Math_SinS(sFileSelectSkyboxRotation);
    eyeY = -700.0f;
    eyeZ = 1000.0f * Math_SinS(sFileSelectSkyboxRotation) + 1000.0f * Math_CosS(sFileSelectSkyboxRotation);

    FileSelect_RenderView(this, eyeX, eyeY, eyeZ);
    SkyboxDraw_Draw(&this->skyboxCtx, this->state.gfxCtx, 1, this->envCtx.unk_13, eyeX, -700.0f, eyeZ);

    gDPSetTextureLUT(POLY_OPA_DISP++, G_TT_NONE);

    sFileSelectSkyboxRotation += -0xA;

    CLOSE_DISPS(gfxCtx);
}

void (*gFileSelectDrawFuncs[])(GameState*) = {
    func_8080BDAC,
    FileSelect_ConfigModeDraw,
    FileSelect_SelectModeDraw,
};
void (*gFileSelectUpdateFuncs[])(GameState*) = {
    func_8080BC58,
    FileSelect_ConfigModeUpdate,
    FileSelect_SelectModeUpdate,
};

// Please wait, Decide/Cancel, Decide/Save
void* D_808147B4[] = { 0x0100B2B0, 0x0100A030, 0x0100A930 };
s16 D_808147C0[] = { 144, 144, 152 };
s16 D_808147C8[] = { 90, 90, 86 };

void FileSelect_Main(GameState* thisx) {
    FileSelectState* this = (FileSelectState*)thisx;
    Input* input = &this->state.input[0];
    s32 texIndex;
    s32 pad;

    func_8012CF0C(this->state.gfxCtx, 0, 1, 0, 0, 0);

    OPEN_DISPS(this->state.gfxCtx);

    gSPSegment(POLY_OPA_DISP++, 0x01, this->staticSegment);
    gSPSegment(POLY_OPA_DISP++, 0x02, this->parameterSegment);
    gSPSegment(POLY_OPA_DISP++, 0x06, this->titleSegment);

    this->stickRelX = input->rel.stick_x;
    this->stickRelY = input->rel.stick_y;

    if (this->stickRelX < -30) {
        if (this->stickXDir == -1) {
            this->inputTimerX--;
            if (this->inputTimerX < 0) {
                this->inputTimerX = 2;
            } else {
                this->stickRelX = 0;
            }
        } else {
            this->inputTimerX = 10;
            this->stickXDir = -1;
        }
    } else if (this->stickRelX > 30) {
        if (this->stickXDir == 1) {
            this->inputTimerX--;
            if (this->inputTimerX < 0) {
                this->inputTimerX = 2;
            } else {
                this->stickRelX = 0;
            }
        } else {
            this->inputTimerX = 10;
            this->stickXDir = 1;
        }
    } else {
        this->stickXDir = 0;
    }

    if (this->stickRelY < -30) {
        if (this->stickYDir == -1) {
            this->inputTimerY--;
            if (this->inputTimerY < 0) {
                this->inputTimerY = 2;
            } else {
                this->stickRelY = 0;
            }
        } else {
            this->inputTimerY = 10;
            this->stickYDir = -1;
        }
    } else if (this->stickRelY > 30) {
        if (this->stickYDir == 1) {
            this->inputTimerY--;
            if (this->inputTimerY < 0) {
                this->inputTimerY = 2;
            } else {
                this->stickRelY = 0;
            }
        } else {
            this->inputTimerY = 10;
            this->stickYDir = 1;
        }
    } else {
        this->stickYDir = 0;
    }

    this->emptyFileTextAlpha = 0;

    FileSelect_PulsateCursor(this);
    gFileSelectUpdateFuncs[this->menuMode](&this->state);
    FileSelect_UpdateAndDrawSkybox(this);
    gFileSelectDrawFuncs[this->menuMode](&this->state);

    func_8012C628(this->state.gfxCtx);

    gDPSetCombineLERP(POLY_OPA_DISP++, PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, TEXEL0, 0, PRIMITIVE, 0, PRIMITIVE,
                      ENVIRONMENT, TEXEL0, ENVIRONMENT, TEXEL0, 0, PRIMITIVE, 0);
    gDPSetPrimColor(POLY_OPA_DISP++, 0, 0, 100, 255, 255, this->controlsAlpha);
    gDPSetEnvColor(POLY_OPA_DISP++, 0, 0, 0, 0);

    if (this->sramCtx.status > 0) {
        texIndex = 0;
    } else if ((this->configMode > 38) && (this->configMode < 44)) {
        texIndex = 2;
    } else {
        texIndex = 1;
    }

    gDPLoadTextureBlock(POLY_OPA_DISP++, D_808147B4[texIndex], G_IM_FMT_IA, G_IM_SIZ_8b, D_808147C0[texIndex], 16, 0,
                        G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK,
                        G_TX_NOLOD);

    gSPTextureRectangle(POLY_OPA_DISP++, D_808147C8[texIndex] << 2, 204 << 2,
                        (D_808147C8[texIndex] + D_808147C0[texIndex]) << 2, (204 + 16) << 2, G_TX_RENDERTILE, 0, 0,
                        1 << 10, 1 << 10);

    gDPPipeSync(POLY_OPA_DISP++);
    gSPDisplayList(POLY_OPA_DISP++, sScreenFillSetupDL);
    gDPSetPrimColor(POLY_OPA_DISP++, 0, 0, 0, 0, 0, this->screenFillAlpha);
    gSPDisplayList(POLY_OPA_DISP++, D_0E000000.fillRect);

    CLOSE_DISPS(this->state.gfxCtx);
}

void FileSelect_InitContext(GameState* thisx) {
    FileSelectState* this = (FileSelectState*)thisx;
    EnvironmentContext* envCtx = &this->envCtx;

    Sram_Alloc(&this->state, &this->sramCtx);
    func_801457CC(&this->state, &this->sramCtx);

    // this->menuMode = FS_MENU_MODE_INIT;
    this->menuMode = 0;

    this->buttonIndex = this->selectMode = this->unk_2448E = this->fileNum = this->confirmButtonIndex = 0;

    this->confirmButtonTexIndices[0] = 2;
    this->confirmButtonTexIndices[1] = 3;
    this->titleLabel = 0;
    this->nextTitleLabel = 1;

    this->screenFillAlpha = 255;
    this->highlightPulseDir = 1;
    this->unk_244F4 = 0xC;
    this->highlightColor[0] = 155;
    this->highlightColor[1] = 255;
    this->highlightColor[2] = 255;
    this->highlightColor[3] = 70;
    this->configMode = 0;
    this->windowRot = 0.0f;

    this->stickXDir = this->inputTimerX = 0;
    this->stickYDir = this->inputTimerY = 0;

    this->kbdX = this->kbdY = this->unk_24516 = 0;

    // this->kbdButton = FS_KBD_BTN_NONE;
    this->kbdButton = 99;

    this->windowColor[0] = 100;
    this->windowColor[1] = 150;
    this->windowColor[2] = 255;

    this->windowAlpha = this->titleAlpha[0] = this->titleAlpha[1] = this->fileButtonAlpha[0] =
        this->fileButtonAlpha[1] = this->fileButtonAlpha[2] = this->nameBoxAlpha[0] = this->nameBoxAlpha[1] =
            this->nameBoxAlpha[2] = this->nameAlpha[0] = this->nameAlpha[1] = this->nameAlpha[2] =
                this->connectorAlpha[0] = this->connectorAlpha[1] = this->connectorAlpha[2] = this->fileInfoAlpha[0] =
                    this->fileInfoAlpha[1] = this->fileInfoAlpha[2] = this->actionButtonAlpha[0] =
                        this->actionButtonAlpha[1] = this->actionButtonAlpha[2] = this->actionButtonAlpha[3] =
                            this->optionButtonAlpha = this->nameEntryBoxAlpha = this->controlsAlpha =
                                this->emptyFileTextAlpha = 0;

    this->windowPosX = 6;
    this->actionTimer = 4;
    this->warningLabel = -1;

    this->warningButtonIndex = this->buttonYOffsets[0] = this->buttonYOffsets[1] = this->buttonYOffsets[2] =
        this->buttonYOffsets[3] = this->buttonYOffsets[4] = this->buttonYOffsets[5] = this->fileNamesY[0] =
            this->fileNamesY[1] = this->fileNamesY[2] = 0;

    this->unk_2451E[0] = 0;
    this->unk_2451E[1] = 3;
    this->unk_2451E[2] = 6;
    this->unk_2451E[3] = 8;
    this->unk_2451E[4] = 10;
    this->highlightTimer = 20;

    ShrinkWindow_SetLetterboxTarget(0);

    gSaveContext.skyboxTime = 0;
    gSaveContext.save.time = 0;

    // Skybox_Init
    func_801434E4(&this->state, &this->skyboxCtx, 1);
    R_TIME_SPEED = 10;

    // TODO: copy some variable names from OoT
    envCtx->unk_19 = 0;
    envCtx->unk_1A = 0;
    envCtx->unk_21 = 0;
    envCtx->unk_22 = 0;
    envCtx->unk_44 = 0;
    envCtx->unk_10 = 99;
    envCtx->unk_11 = 99;
    envCtx->unk_1F = 0;
    envCtx->unk_20 = 0;
    envCtx->unk_C1 = 0;
    envCtx->unk_17 = 2;
    envCtx->skyboxDisabled = 0;
    envCtx->unk_13 = 0;
    envCtx->unk_84 = 0.0f;
    envCtx->unk_88 = 0.0f;

    gSaveContext.buttonStatus[0] = 0;
    gSaveContext.buttonStatus[1] = 0;
    gSaveContext.buttonStatus[2] = 0;
    gSaveContext.buttonStatus[3] = 0;
    gSaveContext.buttonStatus[4] = 0;
}

void FileSelect_Destroy(GameState* this) {
    ShrinkWindow_Destroy();
}

void FileSelect_Init(GameState* thisx) {
    s32 pad;
    FileSelectState* this = (FileSelectState*)thisx;
    size_t size;

    Game_SetFramerateDivisor(&this->state, 1);
    Matrix_Init(&this->state);
    ShrinkWindow_Init();
    View_Init(&this->view, this->state.gfxCtx);
    this->state.main = FileSelect_Main;
    this->state.destroy = FileSelect_Destroy;
    FileSelect_InitContext(&this->state);
    Font_LoadOrderedFont(&this->font);

    size = SEGMENT_ROM_SIZE(title_static);
    this->staticSegment = THA_AllocEndAlign16(&this->state.heap, size);
    DmaMgr_SendRequest0(this->staticSegment, SEGMENT_ROM_START(title_static), size);

    size = SEGMENT_ROM_SIZE(parameter_static);
    this->parameterSegment = THA_AllocEndAlign16(&this->state.heap, size);
    DmaMgr_SendRequest0(this->parameterSegment, SEGMENT_ROM_START(parameter_static), size);

    size = gObjectTable[OBJECT_MAG].vromEnd - gObjectTable[OBJECT_MAG].vromStart;
    this->titleSegment = THA_AllocEndAlign16(&this->state.heap, size);
    DmaMgr_SendRequest0(this->titleSegment, gObjectTable[OBJECT_MAG].vromStart, size);

    audio_setBGM(0xA);
    func_801A3238(SEQ_PLAYER_BGM_MAIN, NA_BGM_FILE_SELECT, 0, 7, 1);
}
