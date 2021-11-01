#ifndef Z_OBJ_TOKEIDAI_H
#define Z_OBJ_TOKEIDAI_H

#include "global.h"

struct ObjTokeidai;

typedef void (*ObjTokeidaiActionFunc)(struct ObjTokeidai*, GlobalContext*);

typedef struct ObjTokeidai {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ void* unk_144;
    /* 0x0148 */ void* unk_148;
    /* 0x014C */ char unk_14C[0x12];
    /* 0x015E */ s16 unk_15E;
    /* 0x0160 */ s16 unk_160;
    /* 0x0162 */ s16 unk_162;
    /* 0x0164 */ char unk_164[0xC];
    /* 0x0170 */ u16 unk_170;
    /* 0x0174 */ ObjTokeidaiActionFunc actionFunc;
} ObjTokeidai; // size = 0x178

extern const ActorInit Obj_Tokeidai_InitVars;

#endif // Z_OBJ_TOKEIDAI_H
