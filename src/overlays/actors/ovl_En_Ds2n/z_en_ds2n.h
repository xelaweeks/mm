#ifndef Z_EN_DS2N_H
#define Z_EN_DS2N_H

#include "global.h"
#include "objects/object_ds2n/object_ds2n.h"

struct EnDs2n;

typedef void (*EnDs2nActionFunc)(struct EnDs2n*, GlobalContext*);

typedef struct EnDs2n {
    /* 0x0000 */ Actor actor;
    ///* 0x0144 */ char unk_144[0x90];
    /* 0x144 */ char pad144[0x4C]; // unused collider?
    /* 0x190 */ SkelAnime skelAnime;
    /* 0x01D4 */ EnDs2nActionFunc actionFunc;
    /* 0x1D8 */ s16 limbRotTableY[DS2N_LIMB_MAX];
    /* 0x1FE */ s16 limbRotTableZ[DS2N_LIMB_MAX];
    /* 0x224 */ Vec3s headRot;
    /* 0x22A */ Vec3s chestRot; // set by function, but not applied to skeleton
    /* 0x230 */ s16 blinkState;
    /* 0x232 */ s16 blinkTimer;

} EnDs2n; // size = 0x234

extern const ActorInit En_Ds2n_InitVars;

#endif // Z_EN_DS2N_H
