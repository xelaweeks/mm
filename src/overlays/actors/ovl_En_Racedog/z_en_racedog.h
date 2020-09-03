#ifndef _Z_EN_RACEDOG_H_
#define _Z_EN_RACEDOG_H_

#include <global.h>

struct EnRacedog;

typedef struct EnRacedog {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x184];
} EnRacedog; // size = 0x2C8

extern const ActorInit En_Racedog_InitVars;

#endif
