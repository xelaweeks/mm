#ifndef Z_DM_AL_H
#define Z_DM_AL_H

#include "global.h"

struct DmAl;

typedef void (*DmAlActionFunc)(struct DmAl*, PlayState*);

typedef struct DmAl {
    /* 0x0000 */ Actor actor;
    /* 0x144 */ SkelAnime unk144;
    /* 0x188 */ DmAlActionFunc actionFunc;
    /* 0x18C */ MtxF unkMtx[6];
    /* 0x30C */ Vec3s unk30C;
    /* 0x312 */ char pad312[0x9C];
    /* 0x3AE */ Vec3s unk3AE;
    /* 0x3B4 */ char pad3B4[0x9C];
    /* 0x450 */ u8 unk450;
    /* 0x451 */ char pad451[3];
    /* 0x454 */ PlayState* unk454;
    /* 0x458 */ PlayState* unk458;
    /* 0x45C */ s32 unk45C;
} DmAl; // size = 0x460

extern const ActorInit Dm_Al_InitVars;

#endif // Z_DM_AL_H
