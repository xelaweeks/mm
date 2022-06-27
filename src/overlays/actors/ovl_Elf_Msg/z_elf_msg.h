#ifndef Z_ELF_MSG_H
#define Z_ELF_MSG_H

#include "global.h"

#define ENELF_GET_FF(thisx) ((thisx)->params & 0xFF)
#define ENELF_GET_7F00(thisx) (((thisx)->params & 0x7F00) >> 8)
#define ENELF_GET_8000(thisx) ((thisx)->params & 0x8000)

struct ElfMsg;

typedef void (*ElfMsgActionFunc)(struct ElfMsg*, PlayState*);

typedef struct ElfMsg {
    /* 0x000 */ Actor actor;
    /* 0x144 */ ElfMsgActionFunc actionFunc;
} ElfMsg; // size = 0x148

extern const ActorInit Elf_Msg_InitVars;

#endif // Z_ELF_MSG_H
