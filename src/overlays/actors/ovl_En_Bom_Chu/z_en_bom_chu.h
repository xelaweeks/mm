#ifndef Z_EN_BOM_CHU_H
#define Z_EN_BOM_CHU_H

#include "global.h"

struct EnBomChu;

typedef void (*EnBomChuActionFunc)(struct EnBomChu*, GlobalContext*);

typedef struct EnBomChu {
    /* 0x000 */ Actor actor;
    /* 0x144 */ EnBomChuActionFunc actionFunc;
    /* 0x148 */ s8 unk_148;
    /* 0x149 */ char unk_149[0x1];
    /* 0x14A */ s16 unk_14A;
    /* 0x14C */ char unk_14C[0x28];
    /* 0x174 */ f32 unk_174;
    /* 0x178 */ char pad178[0x8];
    /* 0x180 */ s32 unk_180;
    /* 0x184 */ s32 unk_184;
    /* 0x188 */ ColliderSphere unk_188;
} EnBomChu; // size = 0x1E0

extern const ActorInit En_Bom_Chu_InitVars;

#endif // Z_EN_BOM_CHU_H
