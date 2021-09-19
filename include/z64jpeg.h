#ifndef Z64JPEG_H
#define Z64JPEG_H

#include "z64.h"


#define MARKER_ESCAPE 0x00
#define MARKER_SOI 0xD8
#define MARKER_SOF 0xC0
#define MARKER_DHT 0xC4
#define MARKER_DQT 0xDB
#define MARKER_DRI 0xDD
#define MARKER_SOS 0xDA
#define MARKER_APP0 0xE0
#define MARKER_APP1 0xE1
#define MARKER_APP2 0xE2
#define MARKER_COM 0xFE
#define MARKER_EOI 0xD9


typedef struct {
    /* 0x00 */ u16 table[8*8];
} JpegQuantizationTable; // size = 0x80

typedef struct {
    /* 0x00 */ u8 codeOffs[16];
    /* 0x10 */ u16 codesA[16];
    /* 0x30 */ u16 codesB[16];
    /* 0x50 */ u8* symbols;
} JpegHuffmanTable; // size = 0x54

// this struct might be unaccurate but it's not used outside jpegutils.c anyways
typedef struct {
    /* 0x000 */ u8 codeOffs[16];
    /* 0x010 */ u16 dcCodes[120];
    /* 0x100 */ u16 acCodes[256];
} JpegHuffmanTableOld; // size = 0x300

typedef struct {
    /* 0x00 */ u32 address;
    /* 0x04 */ u32 mbCount;
    /* 0x08 */ u32 mode;
    /* 0x0C */ u32 qTableYPtr;
    /* 0x10 */ u32 qTableUPtr;
    /* 0x14 */ u32 qTableVPtr;
    /* 0x18 */ char unk_18[0x8];
} JpegTaskData; // size = 0x20

typedef struct {
    /* 0x000 */ JpegTaskData taskData;
    /* 0x020 */ char yieldData[0x200];
    /* 0x220 */ JpegQuantizationTable qTableY;
    /* 0x2A0 */ JpegQuantizationTable qTableU;
    /* 0x320 */ JpegQuantizationTable qTableV;
    /* 0x3A0 */ u8 codesLengths[0x110];
    /* 0x4B0 */ u16 codes[0x108];
    /* 0x6C0 */ u16 data[4][0x180];
} JpegWork; // size = 0x12C0

typedef struct {
    /* 0x00 */ void* imageData;
    /* 0x04 */ u8 mode;
    /* 0x05 */ u8 unk_05;
    /* 0x08 */ JpegHuffmanTable* hTablePtrs[4];
    /* 0x18 */ u8 unk_18;
} JpegDecoder; // size = 0x1C

typedef struct {
    /* 0x00 */ u8 dqtCount;
    /* 0x04 */ u8* dqtPtr[3];
    /* 0x10 */ u8 dhtCount;
    /* 0x14 */ u8* dhtPtr[4];
    /* 0x24 */ void* imageData;
    /* 0x28 */ s8 mode; // 0 if Y V0 is 1 and 2 if Y V0 is 2
    /* 0x29 */ char unk_29[3];
    /* 0x2C */ char unk_2C[4];
    /* 0x30 */ OSScTask scTask;
    /* 0x88 */ char unk_88[0x10];
    /* 0x98 */ OSMesgQueue mq;
    /* 0xB0 */ OSMesg msg;
    /* 0xB4 */ JpegWork* workBuf;
} JpegContext; // size = 0xB8

typedef struct {
    /* 0x00 */ u32 byteIdx;
    /* 0x04 */ u8 bitIdx;
    /* 0x05 */ u8 dontSkip;
    /* 0x08 */ u32 curWord;
    /* 0x0C */ s16 unk_0C;
    /* 0x0E */ s16 unk_0E;
    /* 0x10 */ s16 unk_10;
} JpegDecoderState; // size = 0x14


#endif
