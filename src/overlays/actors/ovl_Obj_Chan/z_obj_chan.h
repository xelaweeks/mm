#ifndef Z_OBJ_CHAN_H
#define Z_OBJ_CHAN_H

#include "global.h"

struct ObjChan;

#define OBJCHAN_SUBTYPE(this) (((this)->actor.params >> 12) & 0xF)
#define OBJCHAN_SUBTYPE_CHANDELIER 0
#define OBJCHAN_SUBTYPE_POT 1

/*** stateFlags ***/
/*
 * After the chandelier is hit by a fire attack, each pot gets OBJCHAN_STATE_FIRE_DELAY state and counts down a number of frames until it catches fire.
 * The delay is different for each pot. Remaining frame count is stored in fireDelayFrames.
 * The main actor also gets this flag but it's always equivalent to OBJCHAN_STATE_ON_FIRE.
 */
#define OBJCHAN_STATE_FIRE_DELAY (1 << 0)
/**
 * Pot is now on fire. After this state is set the flame grows to full size over 20 frames. Flame size is stored in flameSize.
 * OBJCHAN_STATE_FIRE_DELAY is not cleared when this flag is set.
 * The main actor also gets this flag.
 */
#define OBJCHAN_STATE_ON_FIRE (1 << 1) // Pot has fire. Flame grows to full size over about 1 second. Flame size is stored in fireSize.
/**
 * Only for the main actor.
 * Once set, the actor tries to start a cutscene.
 * Once cutscene is started, this flag is unset and OBJCHAN_STATE_MAIN_STOP_CUTSCENE_AT_FULL_SPEED is set.
 */
#define OBJCHAN_STATE_START_CUTSCENE (1 << 2)
/**
 * Only for the main actor.
 * Cutscene is running. Once set, the actor waits for full rotation speed and then cancels the cutscene.
 */
#define OBJCHAN_STATE_CUTSCENE (1 << 3)



typedef void (*ObjChanActionFunc)(struct ObjChan*, GlobalContext*);

typedef struct ObjChan {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ ObjChanActionFunc actionFunc;
    /* 0x0148 */ ColliderCylinder collider;
    /* 0x0194 */ u8 myPotIndex; // For OBJCHAN_SUBTYPE_POT: which pot is this?
    /* 0x0196 */ s16 fireDelayFrames;
    /* 0x0198 */ UNK_TYPE1 unk198[0x12];
    /* 0x01AA */ u8 stateFlags;
    /* 0x01AC */ struct ObjChan* pots[5]; // For OBJCHAN_SUBTYPE_BODY: pointers to pot actors
    /* 0x01C0 */ Vec3f unk1C0;
    /* 0x01CC */ f32 unk1CC;
    /* 0x01D0 */ f32 unk1D0;
    /* 0x01D4 */ s16 unk1D4;
    /* 0x01D8 */ f32 flameSize;
    /* 0x01DC */ s16 rotationSpeed; // Main object only. Slowly ramps up under some circumstances. In other circumstances it's immediately set to maximum speed.
    /* 0x01DE */ s16 rotation; // Increases as the chandelier spins. Don't know why they didn't use the actor's rotation variable.
    /* 0x01E0 */ s16 cutscenes[2];
} ObjChan; // size = 0x1E4

extern const ActorInit Obj_Chan_InitVars;

#endif // Z_OBJ_CHAN_H
