#ifndef Z_OBJ_ETCETERA_H
#define Z_OBJ_ETCETERA_H

#include "global.h"

#define DEKU_FLOWER_TYPE(thisx) (((thisx)->params & 0xFF80) >> 7)

typedef enum {
    /*  0   */ TYPE_PINK_FLOWER,
    /*  1   */ TYPE_PINK_FLOWER_SPAWNED_FROM_MAD_SCRUB,
    /*  2   */ TYPE_GOLD_FLOWER,
    /*  3   */ TYPE_GOLD_FLOWER_SPAWNED_FROM_MAD_SCRUB,
} ObjEtceteraType;

#define NUMBER_OF_FLOWER_TYPES 4

struct ObjEtcetera;

typedef void (*ObjEtceteraActionFunc)(struct ObjEtcetera*, GlobalContext*);

typedef struct ObjEtcetera {
    /* 0x0000 */ DynaPolyActor dyna;
    /* 0x015C */ SkelAnime skelAnime;
    /* 0x01A0 */ ColliderCylinder collider;
    /* 0x01EC */ Vec3s jointTable[11];
    /* 0x022E */ Vec3s morphTable[11];
    /* 0x0270 */ f32 intenseOscillationScale;
    /* 0x0274 */ s16 oscillationTimer;
    /* 0x0276 */ u16 burrowFlag;
    /* 0x0278 */ s8 objIndex;
    /* 0x027C */ Gfx* dList;
    /* 0x0280 */ ObjEtceteraActionFunc actionFunc;
} ObjEtcetera; // size = 0x284

extern const ActorInit Obj_Etcetera_InitVars;

#endif // Z_OBJ_ETCETERA_H
