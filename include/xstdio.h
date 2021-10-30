#ifndef _XSTDIO_H_
#define _XSTDIO_H_

#include "libc/stdarg.h"


typedef struct {
    /* 0x0 */ union {
        /* 0x0 */ s64 ll;
        /* 0x0 */ f64 ld;
    } v;
    /* 0x8 */ char* s;
    /* 0xC */ s32 n0;
    /* 0x10 */ s32 nz0;
    /* 0x14 */ s32 n1;
    /* 0x18 */ s32 nz1;
    /* 0x1C */ s32 n2;
    /* 0x20 */ s32 nz2;
    /* 0x24 */ s32 prec;
    /* 0x28 */ s32 width;
    /* 0x2C */ size_t nchar;
    /* 0x30 */ u32 flags;
    /* 0x34 */ u8 qual;
} _Pft;

#endif
