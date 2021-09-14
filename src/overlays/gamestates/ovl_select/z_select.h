#ifndef _Z64_SELECT_H_
#define _Z64_SELECT_H_

#include "global.h"

struct SelectContext;

void Select_Init(GameState* thisx);
void Select_Destroy(GameState* thisx);

typedef void (*Select_LoadFunc)(struct SelectContext*, u32, s32);

typedef struct {
    /* 0x00 */ char* name;
    /* 0x04 */ Select_LoadFunc loadFunc;
    /* 0x08 */ s32 entranceIndex;
} SceneSelectEntry; // size = 0xC

typedef struct SelectContext {
    /* 0x000 */ GameState state;
    /* 0x0A8 */ View view;
    /* 0x210 */ s32 count;
    /* 0x214 */ SceneSelectEntry* scenes;
    /* 0x218 */ s32 currentScene;
    /* 0x21C */ s32 pageDownIndex; // Index of pageDownStops
    /* 0x220 */ s32 pageDownStops[7];
    /* 0x23C */ char unk_23C[0xC];
    /* 0x248 */ s32 opt;
    /* 0x24C */ s32 topDisplayedScene; // The scene which is currently at the top of the screen
    /* 0x250 */ char unk_250[0xC];
    /* 0x25C */ s32 verticalInputAccumulator;
    /* 0x260 */ s32 verticalInput;
    /* 0x264 */ s32 timerUp;
    /* 0x268 */ s32 timerDown;
    /* 0x26C */ s32 lockUp;
    /* 0x270 */ s32 lockDown;
    /* 0x274 */ s32 unk_274; // unused
    /* 0x278 */ char unk_278[0x08];
} SelectContext; // size = 0x280

#endif
