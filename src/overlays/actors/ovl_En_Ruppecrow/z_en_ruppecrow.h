#ifndef Z_EN_RUPPECROW_H
#define Z_EN_RUPPECROW_H

#include "global.h"

struct EnRuppecrow;

typedef void (*EnRuppecrowActionFunc)(struct EnRuppecrow*, GlobalContext*);

typedef struct EnRuppecrow {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ EnItem00* items[20];
    /* 0x0194 */ SkelAnime skelAnime;
    /* 0x01D8 */ EnRuppecrowActionFunc actionFunc;
    /* 0x01DC */ UNK_TYPE unk_1DC;
    /* 0x01E0 */ Vec3s joinTable[9];
    /* 0x0216 */ Vec3s morphTable[9];
    /* 0x024C */ Path* path;
    /* 0x0250 */ UNK_TYPE unk_250;
    /* 0x0254 */ ColliderJntSph collider;
    /* 0x0274 */ ColliderJntSphElement colliderElement;
    /* 0x02B4 */ u16 unk_2B4;
    /* 0x02B6 */ s16 unk_2B6;
    /* 0x02B8 */ f32 unk_2B8;
    /* 0x02BC */ s16 unk_2BC;
    /* 0x02BE */ s16 unk_2BE;
    /* 0x02C0 */ s32 unk_2C0;
    /* 0x02C4 */ s8 unk_2C4; 
    /* 0x02C5 */ s8 unk_2C5; 
    /* 0x02C6 */ s8 unk_2C6; 
    /* 0x02C7 */ s8 unk_2C7;
    /* 0x02C8 */ f32 unk_2C8;
    /* 0x02CC */ f32 unk_2CC;
    /* 0x02D0 */ f32 unk_2D0;
    /* 0x02D4 */ Vec3f limbPos[4];
} EnRuppecrow; // size = 0x304

extern const ActorInit En_Ruppecrow_InitVars;

#endif // Z_EN_RUPPECROW_H
