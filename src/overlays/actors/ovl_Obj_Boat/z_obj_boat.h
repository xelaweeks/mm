#ifndef Z_OBJ_BOAT_H
#define Z_OBJ_BOAT_H

#include "global.h"

#define OBJBOAT_GET_PARAMS(thisx) ((thisx)->params)
#define OBJBOAT_GET_PATH(thisx) ((thisx)->params >> 0x07)
#define OBJBOAT_GET_4000(thisx) ((thisx)->params & 0x4000)

struct ObjBoat;

typedef struct ObjBoat {
    /* 0x000 */ DynaPolyActor dyna;
    /* 0x15C */ u8 posX;
    /* 0x15D */ s8 rotY;
    /* 0x15E */ u8 unk_15E;
    /* 0x15F */ u8 unk_15F;
    /* 0x160 */ s16 unk_160;
    /* 0x162 */ UNK_TYPE1 pad_162;
    /* 0x163 */ u8 unk_163;
    /* 0x164 */ Vec3s* unk_164;
} ObjBoat;

extern const ActorInit Obj_Boat_InitVars;

#endif // Z_OBJ_BOAT_H
