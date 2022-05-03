#ifndef Z_EN_WIZ_BROCK_H
#define Z_EN_WIZ_BROCK_H

#include "global.h"

struct EnWizBrock;

typedef void (*EnWizBrockActionFunc)(struct EnWizBrock*, GlobalContext*);

typedef struct EnWizBrock {
    /* 0x0000 */ DynaPolyActor dyna;
    /* 0x015C */ char unk_15C[0x44];
    /* 0x01A0 */ EnWizBrockActionFunc actionFunc;
    /* 0x1A4 */ s16 despawnCounter; // Counter for despawing blocks (Max of 0x25)
    /* 0x1A6 */ s16 unk1A6;
    /* 0x1A8 */ s16 platformNum; // Numeric identifier for platform
    /* 0x1AA */ s16 platformType; // Determines element type for platform (ice/fire)
    /* 0x1AC */ f32 alpha;
} EnWizBrock; // size = 0x1B0

extern const ActorInit En_Wiz_Brock_InitVars;

#endif // Z_EN_WIZ_BROCK_H
