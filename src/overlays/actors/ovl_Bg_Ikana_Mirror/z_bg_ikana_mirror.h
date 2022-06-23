#ifndef Z_BG_IKANA_MIRROR_H
#define Z_BG_IKANA_MIRROR_H

#include "global.h"

struct BgIkanaMirror;

typedef void (*BgIkanaMirrorActionFunc)(struct BgIkanaMirror*, GlobalContext*);

//must dyna Actor field.
typedef struct BgIkanaMirror {
    /* 0x000 */ DynaPolyActor dyna;
    /* 0x15C */ ColliderTris colliderTris;                /* inferred */
    /* 0x17C */ ColliderTrisElement colliderTrisElements[9];         /* inferred */
    /* 0x4B8 */ ColliderQuad colliderQuad[2];                /* inferred */
    /* 0x5B8 */ BgIkanaMirrorActionFunc actionFunc;
    /* 0x5BC */ AnimatedMaterial *unk5BC;           /* inferred */ //absorbing light or emanating light
    /* 0x5C0 */ AnimatedMaterial *unk5C0;           /* inferred */ //not unk5BC
    /* 0x5C4 */ s16 unk5C4;                         /* inferred */ //probably charge counter for light
    /* 0x5C6 */ u8 unk5C6;                          /* inferred */ //color stuff
    /* 0x5C7 */ u8 unk5C7;                          /* inferred */ //color stuff
    /* 0x5C8 */ s8 unk5C8;                          /* inferred */
    /* 0x5C9 */ char pad5C9[3];                     /* maybe part of unk5C8[4]? */
} BgIkanaMirror;                                    /* size = 0x5CC */

#endif // Z_BG_IKANA_MIRROR_H
