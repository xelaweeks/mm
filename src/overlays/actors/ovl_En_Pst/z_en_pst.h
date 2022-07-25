#ifndef Z_EN_PST_H
#define Z_EN_PST_H

#include "global.h"
#include "objects/object_pst/object_pst.h"

struct EnPst;

typedef void (*EnPstActionFunc)(struct EnPst*, PlayState*);
typedef s32 (*MsgEventFunc)(Actor*, PlayState*);

typedef struct EnPst {
    /* 0x000 */ Actor actor;
    /* 0x144 */ SkelAnime skelAnime;
    /* 0x188 */ EnPstActionFunc actionFunc;
    /* 0x18C */ ColliderCylinder collider;
    /* 0x1D8 */ u8 scheduleResult;
    /* 0x1DC */ s32* msgEventScript;
    /* 0x1E0 */ s32 msgEventArg4;
    /* 0x1E4 */ Vec3s jointTable[POSTBOX_LIMB_MAX];
    /* 0x1F6 */ Vec3s morphTable[POSTBOX_LIMB_MAX];
    /* 0x208 */ u16 stateFlags;
    /* 0x20A */ UNK_TYPE1 pad20A[4];
    /* 0x20E */ s16 behaviour;
    /* 0x210 */ MsgEventFunc msgEventCallback;
    /* 0x214 */ s32 unk214; // Set and not used
    /* 0x218 */ s32 exchangeItemId;
    /* 0x21C */ s32 isLetterToKafeiDeposited;
} EnPst; // size = 0x220

extern const ActorInit En_Pst_InitVars;

#endif // Z_EN_PST_H
