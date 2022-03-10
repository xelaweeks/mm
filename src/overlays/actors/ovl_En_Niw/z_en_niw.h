#ifndef Z_EN_NIW_H
#define Z_EN_NIW_H

#include "global.h"
#include "objects/object_niw/object_niw.h"

struct EnNiw;

typedef void (*EnNiwActionFunc)(struct EnNiw*, GlobalContext*);

typedef struct {
    /* 0x0000 */ u8 isEnabled;
    /* 0x0004 */ Vec3f pos;
    /* 0x0010 */ Vec3f vel;
    /* 0x001C */ Vec3f accel;
    /* 0x0028 */ s16 life;
    /* 0x002A */ s16 zRotStart;
    /* 0x002C */ f32 scale;
    /* 0x0030 */ f32 zRot;
    /* 0x0034 */ u8 timer;
} EnNiwFeather; // size = 0x38

#define NIW_FEATHER_COUNT 20

typedef struct EnNiw {
    /* 0x000 */ Actor actor;
    /* 0x144 */ SkelAnime skelanime;
    /* 0x188 */ Vec3s jointTable[NIW_LIMB_MAX];
    /* 0x1E8 */ Vec3s morphTable[NIW_LIMB_MAX];
    /* 0x248 */ EnNiwActionFunc actionFunc;
    /* 0x24C */ s16 unkTimer24C;             // set to 10, checked in mystery func
    /* 0x24E */ s16 unkTimer24E;
    /* 0x250 */ union {
                    s16 generalTimer1;       // default name for reset/decr
                    s16 hopTimer;            // every 3 frames while running/idling
                    s16 swimRippleTimer;     // how often swimming cucco spawns ripples 
                    s16 heldTimer;           // timer until updating unk29E
                    s16 unkIdleTimer;        // not sure what _Idle is doing with it yet
                };
    /* 0x252 */ union {
                    s16 generalTimer2;          // default name for reset/decr
                    s16 hoppingTimer;           // hopping after being thrown before running
                    s16 attackNiwSpawnTimer;    // delay between re-attempting to spawn more attack_niw 
                    s16 runningDirectionTimer;  // delay between direction changes when running
                    s16 cuccoStormTimer;        // delay between stages of summoning the storm
                    s16 unkIdleTimer2;          // not sure what _Idle is doing with it yet
                };
    /* 0x254 */ s16 runAwayTimer;
    /* 0x256 */ s16 sfxTimer1; 
    /* 0x258 */ s16 flutterSfxTimer;
    /* 0x25A */ s16 unusedTimer25A;
    /* 0x25C */ s16 yawTimer;                   // every 70 frames rechecks yawToPlayer
    /* 0x25E */ s16 unusedTimer25E;
    /* 0x260 */ s16 iframeTimer;
    /* 0x264 */ f32 unk264[10]; 
    /* 0x28C */ s16 unusedCounter28C;
    /* 0x28E */ s16 niwState;
    /* 0x290 */ s16 attackNiwCount;
    /* 0x292 */ s16 unk292;
    /* 0x294 */ s16 pad294;
    /* 0x296 */ s16 unk296;
    /* 0x298 */ s16 unk298;
    /* 0x29C */ s16 isRunningRight;             // toggle (direction cucco is turning while running)
    /* 0x29C */ u16 unk29C;
    /* 0x29E */ s16 unk29E;                     // three states 0/1/2
    /* 0x2A0 */ s16 isStormActive;              // we have a data value shared between all cucco, this shouldn't need to exist
    /* 0x2A2 */ s16 niwType;
    /* 0x2A4 */ Vec3f unk2A4;
    /* 0x2B0 */ Vec3f unk2B0;
    /* 0x2BC */ Vec3f unk2BC; // init from data (90000 on all three)
    /* 0x2C8 */ f32 leftWingRotZ;
    /* 0x2CC */ f32 leftWingRotY;
    /* 0x2D0 */ f32 leftWingRotX;
    /* 0x2D4 */ f32 rightWingRotZ;
    /* 0x2D8 */ f32 rightWingRotY;
    /* 0x2DC */ f32 rightWingRotX;
    /* 0x2E0 */ f32 upperBodyRotY;
    /* 0x2E4 */ f32 headRotY;
    /* 0x2E8 */ s16 yawTowardsPlayer;
    /* 0x2EA */ s16 unk2EA; // toggle
    /* 0x2EC */ s16 unk2EC;
    /* 0x2EE */ UNK_TYPE1  pad2EE[0x6];
    /* 0x2F4 */ f32 unusedFloat2F4;             // set in EnNiw_Update if Cucco falls off map, never read
    /* 0x2F8 */ f32 unusedFloat2F8;
    /* 0x2FC */ f32 unusedFloat2FC;
    /* 0x300 */ f32 unk300;
    /* 0x304 */ f32 unk304;
    /* 0x308 */ f32 unk308;
    /* 0x30C */ s32 pad30C;
    /* 0x310 */ ColliderCylinder collider;
    /* 0x35C */ EnNiwFeather feathers[NIW_FEATHER_COUNT];
} EnNiw; // size = 0x7BC

// in init, any value below zero becomes zero
//  however, in vanilla, only 0xFFFF (-1) exists in scene spawns, actors can spawn 0x0
#define NIW_TYPE_VANILLA 0xFFFF
#define NIW_TYPE_REGULAR 0
#define NIW_TYPE_UNK1 1
#define NIW_TYPE_HELD 2 // spawns held by the bomber kid in east clock town during hide and seek
// the attacking cuccos are not here, they are a different actor:
//  ovl_En_Attack_Niw

#endif // Z_EN_NIW_H
