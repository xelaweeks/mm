#ifndef Z_FBDEMO_WIPE4_H
#define Z_FBDEMO_WIPE4_H

#include "global.h"

typedef struct {
    /* 0x00 */ Color_RGBA8_u32 primColor;
    /* 0x04 */ Color_RGBA8_u32 envColor;
    /* 0x08 */ f32 baseSpeed;
    /* 0x0C */ f32 progress;
    /* 0x10 */ u8 direction;
    /* 0x11 */ u8 colorType;
    /* 0x12 */ u8 speedType;
    /* 0x13 */ u8 isDone;
    /* 0x14 */ Struct_80140E80 bg;
} TransitionWipe4; // size = 0x28

#endif
