#ifndef Z_EN_TG_H
#define Z_EN_TG_H

#include "global.h"

struct EnTg;

typedef void (*EnTgActionFunc)(struct EnTg*, GlobalContext*);

typedef struct EnTgIdk {
    /* 0x00 */ u8 unk0;
    /* 0x01 */ u8 unk1;
    /* 0x02 */ char unk2[0x12];
    /* 0x14 */ Vec3f unk14;
    /* 0x20 */ char unk20[0x10];
    /* 0x30 */ f32 unk30;
    /* 0x38 */ s16 unk38;
} EnTgIdk; // size = ???

typedef struct EnTg {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ EnTgActionFunc actionFunc;
    /* 0x0148 */ SkelAnime skelAnime;
    /* 0x018C */ ColliderCylinder collider;
    /* 0x01D8 */ char unk1D8[0x18]; // 24 bytes
    /* 0x01F0 */ Vec3s jointTable[21];
    /* 0x026E */ Vec3s morphTable[21];
    /* 0x02EC */ int unk2EC;
    /* 0x02F0 */ EnTgIdk unk2F0;
    // /* 0x02FC */ UNK_TYPE1 unk2FC[0x24C];
} EnTg; // size = 0x548

extern const ActorInit En_Tg_InitVars;

#endif // Z_EN_TG_H
