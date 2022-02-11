#ifndef Z_EN_MT_TAG_H
#define Z_EN_MT_TAG_H

#include "global.h"
#include "overlays/actors/ovl_En_Rg/z_en_rg.h"

struct EnMttag;

typedef void (*EnMttagActionFunc)(struct EnMttag*, GlobalContext*);

typedef struct EnMttag {
    /* 0x000 */ Actor actor;
    /* 0x144 */ EnMttagActionFunc actionFunc;
    /* 0x148 */ EnRg* unk_148[4];
    /* 0x158 */ u16 unk_158;
    /* 0x15A */ s16 unk_15A;
    /* 0x15C */ char unk_15C[0x8];
    /* 0x164 */ s32 unk_164;
} EnMttag; // size = 0x168

extern const ActorInit En_Mt_tag_InitVars;

#endif // Z_EN_MT_TAG_H
