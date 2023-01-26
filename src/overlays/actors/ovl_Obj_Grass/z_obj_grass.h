#ifndef Z_OBJ_GRASS_H
#define Z_OBJ_GRASS_H

#include "global.h"
#include "overlays/actors/ovl_Obj_Grass_Carry/z_obj_grass_carry.h"

struct ObjGrass;
struct ObjGrassCarry;

#define OBJ_GRASS_GROUP_DRAW 1
#define OBJ_GRASS_NUM_COLLIDERS 20

typedef struct ObjGrassElement {
    /* 0x00 */ Vec3f pos;
    /* 0x0C */ s16 rotY;
    /* 0x0E */ s8 dropTable;
    /* 0x0F */ u8 elem_flags;
    /* 0x10 */ u8 alpha;
} ObjGrassElement; // size = 0x14

typedef struct {
    /* 0x00 */ Vec3f homePos;
    /* 0x0C */ ObjGrassElement elements[12];
    /* 0xFC */ s16 count;
    /* 0xFE */ u8 flags; // |= 1 is draw group
} ObjGrassGroup; // size = 0x100

typedef struct {
    /* 0x00 */ ColliderCylinder collider;
    /* 0x4C */ ObjGrassElement* entity;
} ObjGrassCollider; // size = 0x50

typedef struct ObjGrass {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ ObjGrassGroup grassGroups[40];
    /* 0x2944 */ s16 activeGrassGroups;
    /* 0x2948 */ ObjGrassCollider grassElemColliders[OBJ_GRASS_NUM_COLLIDERS];
    /* 0x2F88 */ MtxF unk_2F88[12];
    /* 0x3288 */ s16 unk_3288;
    /* 0x328A */ s16 unk_328A;
    /* 0x328C */ s16 unk_328C;
    /* 0x328E */ s16 unk_328E;
    /* 0x3290 */ s16 unk_3290;
    /* 0x3292 */ s16 activeGrassCarry;
    /* 0x3294 */ ObjGrassElement* carryGrassElem;
    /* 0x3298 */ struct ObjGrassCarry* grassCarry[2];
} ObjGrass; // size = 0x32A0

#endif // Z_OBJ_GRASS_H
