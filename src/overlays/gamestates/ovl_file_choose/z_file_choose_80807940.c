/*
 * File: z_file_choose_80807940.c
 * Overlay: ovl_file_choose
 * Description:
 */

#include "z_file_choose.h"
#include "z64rumble.h"

extern UNK_TYPE D_01002800;
extern UNK_TYPE D_01007980;
extern UNK_TYPE D_0102A6B0;
extern UNK_TYPE D_0102B170;
extern UNK_TYPE D_010310F0;
extern UNK_TYPE D_010311F0;

// there are uses of D_0E000000.fillRect (appearing as D_0E0002E0) in this file
extern GfxMasterList D_0E000000;

s32 D_80813DF0[] = {
    0xFFA20048, 0x00000000, 0x00000000, 0xFFFFFFFF, 0x00220048, 0x00000000, 0x10000000, 0xFFFFFFFF, 0xFFA20038,
    0x00000000, 0x00000200, 0xFFFFFFFF, 0x00220038, 0x00000000, 0x10000200, 0xFFFFFFFF, 0xFF9C002C, 0x00000000,
    0x00000000, 0xFFFFFFFF, 0xFFDC002C, 0x00000000, 0x08000000, 0xFFFFFFFF, 0xFF9C001C, 0x00000000, 0x00000200,
    0xFFFFFFFF, 0xFFDC001C, 0x00000000, 0x08000200, 0xFFFFFFFF, 0xFF9C0004, 0x00000000, 0x00000000, 0xFFFFFFFF,
    0xFFDC0004, 0x00000000, 0x08000000, 0xFFFFFFFF, 0xFF9CFFF4, 0x00000000, 0x00000200, 0xFFFFFFFF, 0xFFDCFFF4,
    0x00000000, 0x08000200, 0xFFFFFFFF, 0xFF9CFFDC, 0x00000000, 0x00000000, 0xFFFFFFFF, 0xFFFCFFDC, 0x00000000,
    0x0C000000, 0xFFFFFFFF, 0xFF9CFFCC, 0x00000000, 0x00000200, 0xFFFFFFFF, 0xFFFCFFCC, 0x00000000, 0x0C000200,
    0xFFFFFFFF, 0x00390009, 0x00000000, 0x00000000, 0xFFFFFFFF, 0x00690009, 0x00000000, 0x06000000, 0xFFFFFFFF,
    0x0039FFF8, 0x00000000, 0x00000220, 0xFFFFFFFF, 0x0069FFF8, 0x00000000, 0x06000220, 0xFFFFFFFF,
};

s32 D_80813F30[] = {
    0xFF9C001A, 0x00000000, 0x00000000, 0xFFFFFFFF, 0xFFCC001A, 0x00000000, 0x06000000, 0xFFFFFFFF, 0xFF9C000A,
    0x00000000, 0x00000200, 0xFFFFFFFF, 0xFFCC000A, 0x00000000, 0x06000200, 0xFFFFFFFF, 0xFFD0001A, 0x00000000,
    0x00000000, 0xFFFFFFFF, 0x0000001A, 0x00000000, 0x06000000, 0xFFFFFFFF, 0xFFD0000A, 0x00000000, 0x00000200,
    0xFFFFFFFF, 0x0000000A, 0x00000000, 0x06000200, 0xFFFFFFFF, 0x0004001A, 0x00000000, 0x00000000, 0xFFFFFFFF,
    0x0034001A, 0x00000000, 0x06000000, 0xFFFFFFFF, 0x0004000A, 0x00000000, 0x00000200, 0xFFFFFFFF, 0x0034000A,
    0x00000000, 0x06000200, 0xFFFFFFFF, 0x0038001A, 0x00000000, 0x00000000, 0xFFFFFFFF, 0x0068001A, 0x00000000,
    0x06000000, 0xFFFFFFFF, 0x0038000A, 0x00000000, 0x00000200, 0xFFFFFFFF, 0x0068000A, 0x00000000, 0x06000200,
    0xFFFFFFFF, 0xFF9CFFF2, 0x00000000, 0x00000000, 0xFFFFFFFF, 0xFFCCFFF2, 0x00000000, 0x06000000, 0xFFFFFFFF,
    0xFF9CFFE2, 0x00000000, 0x00000200, 0xFFFFFFFF, 0xFFCCFFE2, 0x00000000, 0x06000200, 0xFFFFFFFF, 0xFFD0FFF2,
    0x00000000, 0x00000000, 0xFFFFFFFF, 0x0000FFF2, 0x00000000, 0x06000000, 0xFFFFFFFF, 0xFFD0FFE2, 0x00000000,
    0x00000200, 0xFFFFFFFF, 0x0000FFE2, 0x00000000, 0x06000200, 0xFFFFFFFF, 0xFF9CFFCA, 0x00000000, 0x00000000,
    0xFFFFFFFF, 0xFFFCFFCA, 0x00000000, 0x0C000000, 0xFFFFFFFF, 0xFF9CFFBA, 0x00000000, 0x00000200, 0xFFFFFFFF,
    0xFFFCFFBA, 0x00000000, 0x0C000200, 0xFFFFFFFF, 0xFFFCFFCA, 0x00000000, 0x00000000, 0xFFFFFFFF, 0x005CFFCA,
    0x00000000, 0x0C000000, 0xFFFFFFFF, 0xFFFCFFBA, 0x00000000, 0x00000200, 0xFFFFFFFF, 0x005CFFBA, 0x00000000,
    0x0C000200, 0xFFFFFFFF,
};

s32 D_80814130[] = {
    0xFF9C001C, 0x00000000, 0x00000000, 0xFFFFFFFF, 0x009C001C, 0x00000000, 0x20000000, 0xFFFFFFFF,
    0xFF9C001A, 0x00000000, 0x00000040, 0xFFFFFFFF, 0x009C001A, 0x00000000, 0x20000040, 0xFFFFFFFF,
};

s32 D_80814170[] = {
    0xFF9CFFF4, 0x00000000, 0x00000000, 0xFFFFFFFF, 0x009CFFF4, 0x00000000, 0x20000000, 0xFFFFFFFF,
    0xFF9CFFF2, 0x00000000, 0x00000040, 0xFFFFFFFF, 0x009CFFF2, 0x00000000, 0x20000040, 0xFFFFFFFF,
};

s32 D_808141B0[] = {
    0xFF9CFFCC, 0x00000000, 0x00000000, 0xFFFFFFFF, 0x009CFFCC, 0x00000000, 0x20000000, 0xFFFFFFFF,
    0xFF9CFFCA, 0x00000000, 0x00000040, 0xFFFFFFFF, 0x009CFFCA, 0x00000000, 0x20000040, 0xFFFFFFFF,
};

s32 D_808141F0[] = {
    0x0A0B0C0D, 0x0E0F1011, 0x12131415, 0x16171819, 0x1A1B1C1D, 0x1E1F2021, 0x22232425,
    0x26272829, 0x2A2B2C2D, 0x2E2F3031, 0x32333435, 0x36373839, 0x3A3B3C3D, 0x01020304,
    0x05060708, 0x0900403F, 0x3E000000, 0x00000000, 0x00000000, 0x00000000,
};

s16 sChooseFileYOffsets[] = { -48, -48, -48, -24, -24, 0 };

s16 D_8081424C[3][3] = {
    { 0x0000, 0xFFD0, 0xFFD0 },
    { 0xFFC0, 0x0010, 0xFFD0 },
    { 0xFFC0, 0xFFC0, 0x0020 },
};

s16 sEraseDelayTimer = 0xF;

s16 D_80814264[] = { -56, -40, -24, 0 };

s16 D_8081426C[] = { 0, 16, 32 };

s32 D_80814274[] = { 0x00000000, 0x00000000, 0x00000000 };

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_file_choose/func_80807940.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_file_choose/func_80807A78.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_file_choose/func_80807C58.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_file_choose/func_80808214.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_file_choose/func_80808D30.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_file_choose/FileSelect_DrawNameEntry.s")

void FileSelect_StartNameEntry(GameState* thisx) {
    FileSelectState* this = (FileSelectState*)thisx;

    this->nameEntryBoxAlpha += 25;

    if (this->nameEntryBoxAlpha >= 255) {
        this->nameEntryBoxAlpha = 255;
    }

    this->nameEntryBoxPosX -= 30;

    if (this->nameEntryBoxPosX <= 0) {
        this->nameEntryBoxPosX = 0;
        this->nameEntryBoxAlpha = 255;
        this->kbdX = 0;
        this->kbdY = 0;
        this->kbdButton = 99;
        this->configMode = 36;
    }
}

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_file_choose/func_80809EA0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_file_choose/func_8080A3CC.s")

void FileSelect_StartOptions(GameState* thisx) {
    FileSelectState* this = (FileSelectState*)thisx;

    this->nameEntryBoxAlpha += 25;

    if (this->nameEntryBoxAlpha >= 255) {
        this->nameEntryBoxAlpha = 255;
    }

    this->nameEntryBoxPosX -= 30;

    if (this->nameEntryBoxPosX <= 0) {
        this->nameEntryBoxPosX = 0;
        this->nameEntryBoxAlpha = 255;
        this->configMode = 41;
    }
}

u8 D_80814E90;
#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_file_choose/func_8080A4A0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_file_choose/func_8080A6BC.s")

void FileSelect_DrawOptionsImpl(GameState* thisx);
#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_file_choose/FileSelect_DrawOptionsImpl.s")

void FileSelect_DrawOptions(GameState* thisx) {
    FileSelect_DrawOptionsImpl(thisx);
}

// bss padding
s32 D_80814E94;
s32 D_80814E98;
s32 D_80814E9C;
s32 D_80814EA0;
