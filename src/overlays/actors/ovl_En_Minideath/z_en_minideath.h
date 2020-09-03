#ifndef _Z_EN_MINIDEATH_H_
#define _Z_EN_MINIDEATH_H_

#include <global.h>

struct EnMinideath;

typedef struct EnMinideath {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x168];
} EnMinideath; // size = 0x2AC

extern const ActorInit En_Minideath_InitVars;

#endif
