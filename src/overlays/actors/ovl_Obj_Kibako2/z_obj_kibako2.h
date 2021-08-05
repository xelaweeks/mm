#ifndef Z_OBJ_KIBAKO2_H
#define Z_OBJ_KIBAKO2_H

#include "global.h"

#define KIBAKO2_COLLECTIBLE_ID(thisx) ((thisx)->params & 0x3F)
#define KIBAKO2_COLLECTIBLE_FLAG(thisx) (((thisx)->params >> 0x8) & 0x7F)
#define KIBAKO2_SKULLTULA_SPAWN_PARAM(thisx) ((((thisx)->params & 0x1F) << 2) | 0xFF01)
#define KIBAKO2_CONTENTS(thisx) (((thisx)->params >> 0xF) & 1)

typedef enum {
    /*  0   */ CONTENTS_COLLECTIBLE,
    /*  1   */ CONTENTS_SKULLTULA
} ObjKibako2Contents;

struct ObjKibako2;

typedef void (*ObjKibako2ActionFunc)(struct ObjKibako2* this, GlobalContext* globalCtx);

typedef struct ObjKibako2 {
    /* 0x0000 */ DynaPolyActor dyna;
    /* 0x015C */ ColliderCylinder collider;
    /* 0x01A8 */ ObjKibako2ActionFunc actionFunc;
    /* 0x01AC */ s8 unk_1AC;
    /* 0x01AD */ s8 skulltulaNoiseTimer;
    /* 0x01AE */ char unk_1AE[0x2];
} ObjKibako2; // size = 0x1B0

extern const ActorInit Obj_Kibako2_InitVars;

#endif // Z_OBJ_KIBAKO2_H
