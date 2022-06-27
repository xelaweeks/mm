#ifndef Z_EN_MM2_H
#define Z_EN_MM2_H

#include "global.h"

struct EnMm2;

typedef void (*EnMm2ActionFunc)(struct EnMm2*, PlayState*);

typedef struct EnMm2 {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x44];
    /* 0x188 */ EnMm2ActionFunc actionFunc;
    /* 0x18C */ char unk_18C[0x128];
} EnMm2; // size = 0x2B4

extern const ActorInit En_Mm2_InitVars;

#endif // Z_EN_MM2_H
