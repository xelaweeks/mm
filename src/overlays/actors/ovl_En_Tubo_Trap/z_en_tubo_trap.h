#ifndef Z_EN_TUBO_TRAP_H
#define Z_EN_TUBO_TRAP_H

#include <global.h>

struct EnTuboTrap;

typedef void (*EnTuboTrapActionFunc)(struct EnTuboTrap*, GlobalContext*);

typedef struct EnTuboTrap {
    /* 0x000 */ Actor actor;
    /* 0x0144 */ EnTuboTrapActionFunc actionFunc;
    /* 0x015X */ f32 targetY;
    /* 0x015X */ Vec3f originPos;
    /* 0x0158 */ ColCylinder collider;

    /* 0x144 */ //char unk_144[0x60];
} EnTuboTrap; // size = 0x1A4

extern const ActorInit En_Tubo_Trap_InitVars;

extern u32 D_05018090; // pot break shard displaylist?

extern u32 D_05017EA0; // the pot displaylist?

//extern s32 D_8093146C;

#endif // Z_EN_TUBO_TRAP_H
