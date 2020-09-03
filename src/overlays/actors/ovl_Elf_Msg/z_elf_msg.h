#ifndef _Z_ELF_MSG_H_
#define _Z_ELF_MSG_H_

#include <global.h>

struct ElfMsg;

typedef struct ElfMsg {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x4];
} ElfMsg; // size = 0x148

extern const ActorInit Elf_Msg_InitVars;

#endif
