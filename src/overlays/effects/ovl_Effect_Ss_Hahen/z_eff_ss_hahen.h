#ifndef Z64_EFFECT_SS_HAHEN_H
#define Z64_EFFECT_SS_HAHEN_H

#include "global.h"

#define HAHEN_OBJECT_DEFAULT -1

typedef struct {
    /* 0x00 */ Vec3f pos;
    /* 0x0C */ Vec3f velocity;
    /* 0x18 */ Vec3f accel;
    /* 0x24 */ Gfx* dList;
    /* 0x28 */ s16 unused;
    /* 0x2A */ s16 scale;
    /* 0x2C */ s16 objId;
    /* 0x2C */ s16 life;
} EffectSsHahenInitParams; // size = 0x30

extern const EffectSsInit Effect_Ss_Hahen_InitVars;

#endif
