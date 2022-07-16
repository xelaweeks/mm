#ifndef Z_EN_MKK_H
#define Z_EN_MKK_H

#include "global.h"

struct EnMkk;

typedef void (*EnMkkActionFunc)(struct EnMkk*, PlayState*);

typedef struct EnMkk {
    /* 0x000 */ Actor actor;
    /* 0x144 */ EnMkkActionFunc actionFunc;
    /* 0x148 */ u8 unk148;
    /* 0x149 */ u8 unk149;
    /* 0x14A */ u8 unk14A;
    /* 0x14B */ u8 unk14B;
    /* 0x14C */ u8 unk14C;
    /* 0x14D */ char pad14D[1]; 
    /* 0x14E */ s16 unk14E;
    /* 0x150 */ s16 unk150;
    /* 0x152 */ s16 unk152;
    /* 0x154 */ Vec3f unk154;
    /* 0x160 */ Vec3f unk160;
    /* 0x16C */ Vec3f unk16C;
    /* 0x178 */ f32 unk178;
    /* 0x17C */ ColliderSphere unk17C;
} EnMkk; // size = 0x1D4



extern const ActorInit En_Mkk_InitVars;

#endif // Z_EN_MKK_H
