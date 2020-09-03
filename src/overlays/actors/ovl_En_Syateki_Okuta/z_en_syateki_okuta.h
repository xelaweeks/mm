#ifndef _Z_EN_SYATEKI_OKUTA_H_
#define _Z_EN_SYATEKI_OKUTA_H_

#include <global.h>

struct EnSyatekiOkuta;

typedef struct EnSyatekiOkuta {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x168];
} EnSyatekiOkuta; // size = 0x2AC

extern const ActorInit En_Syateki_Okuta_InitVars;

#endif
