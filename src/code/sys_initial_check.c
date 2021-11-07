#include "global.h"

// Address with enough room after to load either of the error message textures before the fault screen buffer at the end
// of RDRAM
#define CHECK_ERROR_MSG_STATIC_SEGMENT (u8*)(FAULT_FB_ADDRESS - 0x1280)

extern void* D_01000000;
extern void* D_01000680;
extern void* D_01001280;

void Check_DrawExpansionPakErrorMessage(void);
void Check_DrawRegionLockErrorMessage(void);

void Check_WriteRGBA16Pixel(u16* buffer, u32 x, u32 y, u32 value) {
    if (value & 1) {
        (&buffer[x])[y * SCREEN_WIDTH] = value;
    }
}

void Check_WriteI4Pixel(u16* buffer, u32 x, u32 y, u32 value) {
    Check_WriteRGBA16Pixel(buffer, x, y, (value * 4228) + 2115);
}

void Check_DrawI4Texture(u16* buffer, s32 x, s32 y, s32 width, s32 height, u8* texture) {
    s32 phi_fp;
    s32 phi_s2;
    u8 temp;
    u8* tex = texture;

    for (phi_fp = 0; phi_fp < height; phi_fp++) {
        for (phi_s2 = 0; phi_s2 < width; phi_s2 += 2, tex++) {
            temp = *tex;
            Check_WriteI4Pixel(buffer, x + phi_s2, y + phi_fp, temp >> 4);
            temp = *tex;
            Check_WriteI4Pixel(buffer, x + phi_s2 + 1, y + phi_fp, temp & 0xF);
        }
    }
}

void Check_ClearRGBA16(u16* buffer) {
    u32 x;
    u32 y;
    for (y = 0; y < SCREEN_HEIGHT; y++) {
        for (x = 0; x < SCREEN_WIDTH; x++) {
            Check_WriteRGBA16Pixel(buffer, x, y, 1);
        }
    }
}

void Check_DrawExpansionPakErrorMessage(void) {
    DmaMgr_SendRequest0(CHECK_ERROR_MSG_STATIC_SEGMENT, (uintptr_t)_memerrmsgSegmentRomStart,
                        (uintptr_t)&D_01001280 - (uintptr_t)&D_01000000);
    Check_ClearRGBA16((u16*)FAULT_FB_ADDRESS);
    Check_DrawI4Texture((u16*)FAULT_FB_ADDRESS, 96, 71, 128, 37, CHECK_ERROR_MSG_STATIC_SEGMENT);
    Check_DrawI4Texture((u16*)FAULT_FB_ADDRESS, 96, 127, 128, 37, CHECK_ERROR_MSG_STATIC_SEGMENT + 0x940);
    osWritebackDCacheAll();
    osViSwapBuffer((u16*)FAULT_FB_ADDRESS);
    osViBlack(0);
}

void Check_DrawRegionLockErrorMessage(void) {
    DmaMgr_SendRequest0(CHECK_ERROR_MSG_STATIC_SEGMENT, (uintptr_t)_locerrmsgSegmentRomStart,
                        (uintptr_t)&D_01000680 - (uintptr_t)&D_01000000);
    Check_ClearRGBA16((u16*)FAULT_FB_ADDRESS);
    Check_DrawI4Texture((u16*)FAULT_FB_ADDRESS, 56, 112, 208, 16, CHECK_ERROR_MSG_STATIC_SEGMENT);
    osWritebackDCacheAll();
    osViSwapBuffer((u16*)FAULT_FB_ADDRESS);
    osViBlack(0);
}

void Check_ExpansionPak(void) {
    // Expansion pak installed
    if (osMemSize >= 0x800000) {
        return;
    }

    Check_DrawExpansionPakErrorMessage();
    osDestroyThread(NULL);
    while (1) {}
}

void Check_RegionIsSupported(void) {
    s32 regionSupported = false;

    if ((osTvType == OS_TV_NTSC) || (osTvType == OS_TV_MPAL)) {
        regionSupported = true;
    }

    if (!regionSupported) {
        Check_DrawRegionLockErrorMessage();
        osDestroyThread(NULL);
        while (true) {}
    }
}
