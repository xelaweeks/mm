#ifndef Z64_DOOR_H
#define Z64_DOOR_H

#include "ultra64.h"
#include "z64actor.h"

typedef struct KnobDoorActor {
    /* 0x000 */ DynaPolyActor dyna;
    /* 0x15C */ SkelAnime skelAnime;
    /* 0x1A0 */ u8 animIndex;
    /* 0x1A1 */ u8 playOpenAnim; // Name suggestions: DoOpen? PerformOpen? closen't? requestOpen? (OoT calls this `playerIsOpening`, but the door may be interacter by NPCs, see func_800F0BB4)
    /* 0x1A2 */ s8 objectSlot;
    /* 0x1A3 */ s8 dlIndex;
} KnobDoorActor; // size = 0x1A4

typedef struct SlidingDoorActor {
    /* 0x000 */ DynaPolyActor dyna;
    /* 0x15C */ s16 unk_15C;
    /* 0x15E */ s16 unk_15E;
} SlidingDoorActor; // size = 0x160

#define TRANSITION_ACTOR_PARAMS_INDEX_SHIFT 10
#define DOOR_GET_TRANSITION_ID(thisx) ((u16)(thisx)->params >> TRANSITION_ACTOR_PARAMS_INDEX_SHIFT)

#endif
