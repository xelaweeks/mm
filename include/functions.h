#ifndef _FUNCTIONS_H_
#define _FUNCTIONS_H_

#include "z64.h"

float fabsf(float f);
#pragma intrinsic(fabsf)
float sqrtf(float f);
#pragma intrinsic(sqrtf)
double sqrt(double d);
#pragma intrinsic(sqrt)

void bootproc(void);
void Idle_ThreadEntry(void* arg);
void ViConfig_UpdateVi(u32 arg0);
void ViConfig_UpdateBlack(void);
s32 DmaMgr_DMARomToRam(u32 src, void* dst, u32 size);
void DmaMgr_DmaCallback0(OSPiHandle* pOParm1, OSIoMesg* pOParm2, s32 OParm3);
DmaEntry* DmaMgr_FindDmaEntry(u32 vromAddr);
u32 DmaMgr_TranslateVromToRom(u32 vromAddr);
s32 DmaMgr_FindDmaIndex(u32 vromAddr);
const char* func_800809F4(u32 param_1);
void DmaMgr_ProcessMsg(DmaRequest* request);
void DmaMgr_ThreadEntry(void* arg);
s32 DmaMgr_SendRequestImpl(DmaRequest* request, void* vramStart, u32 vromStart, u32 size, UNK_TYPE4 unused,
                           OSMesgQueue* callback, void* callbackMesg);
s32 DmaMgr_SendRequest0(void* vramStart, u32 vromStart, u32 size);
void DmaMgr_Start(void);
void DmaMgr_Stop(void);
void* Yaz0_FirstDMA(void);
void* Yaz0_NextDMA(void* curSrcPos);
s32 Yaz0_DecompressImpl(u8* hdr, u8* dst);
void Yaz0_Decompress(u32 romStart, void* dst, u32 size);
void IrqMgr_AddClient(IrqMgr* irqmgr, IrqMgrClient* add, OSMesgQueue* msgQ);
void IrqMgr_RemoveClient(IrqMgr* irqmgr, IrqMgrClient* remove);
void IrqMgr_SendMesgForClient(IrqMgr* irqmgr, OSMesg msg);
void IrqMgr_JamMesgForClient(IrqMgr* irqmgr, OSMesg msg);
void IrqMgr_HandlePreNMI(IrqMgr* irqmgr);
void IrqMgr_CheckStack(void);
void IrqMgr_HandlePRENMI450(IrqMgr* irqmgr);
void IrqMgr_HandlePRENMI480(IrqMgr* irqmgr);
void IrqMgr_HandlePRENMI500(IrqMgr* irqmgr);
void IrqMgr_HandleRetrace(IrqMgr* irqmgr);
void IrqMgr_ThreadEntry(IrqMgr* irqmgr);
void IrqMgr_Init(IrqMgr* irqmgr, void* stack, OSPri pri, u8 retraceCount);
void CIC6105_Nop80081820(void);
void CIC6105_Nop80081828(void);
void CIC6105_PrintRomInfo(void);
void CIC6105_AddRomInfoFaultPage(void);
void CIC6105_RemoveRomInfoFaultPage(void);
void func_800818F4(void);
void __osSyncVPrintf(const char* fmt, ...);
void osSyncPrintf(const char* fmt, ...);
void rmonPrintf(const char* fmt, ...);
void Fault_SleepImpl(u32 duration);
void Fault_AddClient(FaultClient* client, fault_client_func callback, void* param0, void* param1);
void Fault_RemoveClient(FaultClient* client);
void Fault_AddAddrConvClient(FaultAddrConvClient* client, fault_address_converter_func callback, void* param);
void Fault_RemoveAddrConvClient(FaultAddrConvClient* client);
void* Fault_ConvertAddress(void* addr);
void Fault_Sleep(u32 duration);
void Fault_PadCallback(Input* input);
void Fault_UpdatePadImpl(void);
u32 Fault_WaitForInputImpl(void);
void Fault_WaitForInput(void);
void Fault_DrawRec(s32 x, s32 y, s32 w, s32 h, u16 color);
void Fault_FillScreenBlack(void);
void Fault_FillScreenRed(void);
void Fault_DrawCornerRec(u16 color);
void Fault_PrintFReg(s32 idx, f32* value);
void osSyncPrintfFReg(s32 idx, f32* value);
void Fault_PrintFPCR(u32 value);
void osSyncPrintfFPCR(u32 value);
void Fault_PrintThreadContext(OSThread* t);
void osSyncPrintfThreadContext(OSThread* t);
OSThread* Fault_FindFaultedThread(void);
void Fault_Wait5Seconds(void);
void Fault_WaitForButtonCombo(void);
void Fault_DrawMemDumpPage(char* title, u32* addr, u32 param_3);
void Fault_DrawMemDump(u32 pc, u32 sp, u32 unk0, u32 unk1);
void Fault_FindNextStackCall(u32** sp, u32** pc, u32** ra);
void Fault_DrawStackTrace(OSThread* t, u32 flags);
void osSyncPrintfStackTrace(OSThread* t, u32 flags);
void Fault_ResumeThread(OSThread* t);
void Fault_CommitFB(void);
void Fault_ProcessClients(void);
void Fault_SetOptionsFromController3(void);
void Fault_SetOptions(void);
void Fault_ThreadEntry(void* arg);
void Fault_SetFB(void* fb, u16 w, u16 h);
void Fault_Start(void);
void Fault_HangupFaultClient(const char* arg0, char* arg1);
void Fault_AddHungupAndCrashImpl(const char* arg0, char* arg1);
void Fault_AddHungupAndCrash(const char* filename, u32 line);
void FaultDrawer_SetOsSyncPrintfEnabled(u32 enabled);
void FaultDrawer_DrawRecImpl(s32 xstart, s32 ystart, s32 xend, s32 yend, u16 color);
void FaultDrawer_DrawChar(char c);
s32 FaultDrawer_ColorToPrintColor(u16 color);
void FaultDrawer_UpdatePrintColor(void);
void FaultDrawer_SetForeColor(u16 color);
void FaultDrawer_SetBackColor(u16 color);
void FaultDrawer_SetFontColor(u16 color);
void FaultDrawer_SetCharPad(s8 padW, s8 padH);
void FaultDrawer_SetCursor(s32 x, s32 y);
void FaultDrawer_FillScreen(void);
FaultDrawer* FaultDrawer_FormatStringFunc(FaultDrawer* arg, const char* str, s32 count);
void FaultDrawer_VPrintf(const char* str, char* args);
void FaultDrawer_Printf(const char* fmt, ...);
void FaultDrawer_DrawText(s32 x, s32 y, const char* fmt, ...);
void FaultDrawer_SetDrawerFB(void* fb, u16 w, u16 h);
void FaultDrawer_SetInputCallback(func_ptr func);
void FaultDrawer_Init(void);
void func_80084940(void);
void func_80084968(void);
void Load_Relocate(u32 allocatedVRamAddr, OverlayRelocationSection* overlayInfo, u32 vRamStart);
s32 Load_LoadOverlay(u32 vRomStart, u32 vRomEnd, u32 vRamStart, u32 allocatedVRamAddr, u32 allocatedBytes);
void* Load_AllocateAndLoad(u32 vRomStart, u32 vRomEnd, u32 vRamStart);
void Load2_Relocate(u32 allocatedVRamAddr, OverlayRelocationSection* overlayInfo, u32 vRamStart);
s32 Load2_LoadOverlay(u32 vRomStart, u32 vRomEnd, u32 vRamStart, u32 vRamEnd, u32 allocatedVRamAddr);
void* Load2_AllocateAndLoad(u32 vRomStart, u32 vRomEnd, u32 vRamStart, u32 vRamEnd);
void PadUtils_Init(Input* input);
void func_80085150(void);
void PadUtils_ResetPressRel(Input* input);
u32 PadUtils_CheckCurExact(Input* input, u16 value);
u32 PadUtils_CheckCur(Input* input, u16 key);
u32 PadUtils_CheckPressed(Input* input, u16 key);
u32 PadUtils_CheckReleased(Input* input, u16 key);
u16 PadUtils_GetCurButton(Input* input);
u16 PadUtils_GetPressButton(Input* input);
s8 PadUtils_GetCurX(Input* input);
s8 PadUtils_GetCurY(Input* input);
void PadUtils_SetRelXY(Input* input, s32 x, s32 y);
s8 PadUtils_GetRelXImpl(Input* input);
s8 PadUtils_GetRelYImpl(Input* input);
s8 PadUtils_GetRelX(Input* input);
s8 PadUtils_GetRelY(Input* input);
void PadUtils_UpdateRelXY(Input* input);
void StackCheck_Init(StackEntry* entry, void* stackTop, void* stackBottom, u32 initValue, s32 minSpace,
                     const char* name);
void StackCheck_Cleanup(StackEntry* entry);
StackStatus StackCheck_GetState(StackEntry* entry);
u32 StackCheck_CheckAll(void);
u32 StackCheck_Check(StackEntry* entry);
// void GfxPrint_InitDlist(void);
// void GfxPrint_SetColor(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4
// param_5); void GfxPrint_SetPosPx(void); void GfxPrint_SetPos(void);
void GfxPrint_SetBasePosPx(GfxPrint* this, s32 param_2, s32 param_3);
void GfxPrint_PrintCharImpl(GfxPrint* this, u8 c);
void GfxPrint_PrintChar(GfxPrint* this, u8 c);
// void GfxPrint_PrintStringWithSize(void);
// void GfxPrint_PrintString(void);
// void GfxPrint_Callback(void);
// void GfxPrint_Init(void);
// void GfxPrint_Destroy(void);
// void GfxPrint_Open(void);
// void GfxPrint_Close(void);
// void GfxPrint_VPrintf(void);
// void GfxPrint_Printf(void);
// void MtxConv_F2L(void);
// void MtxConv_L2F(void);
void __assert(const char* file, u32 lineNum);
// void func_800862B4(void);
void* SystemArena_MallocMin1(u32 size);
void SystemArena_FreeNull(void* pvParm1);
void func_8008633C(u32 param_1, s32 param_2, s32 param_3, UNK_PTR param_4);
void func_800863AC(u32 param_1, s32 param_2, s32 param_3, UNK_PTR param_4);
// void func_8008641C(void);
// void func_800864EC(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5);
// void func_80086588(void);
void SystemArena_Init(u32 base, u32 size);
s32 func_80086620(OSMesgQueue* param_1, PadMgr* param_2, OSContStatus* param_3);
// void func_80086760(void);
// void func_80086794(void);
// void func_800867B4(void);
// void func_800867D4(void);
// void func_800867F4(void);
// void func_80086814(void);
// void func_80086834(void);
// void func_80086880(void);
// void func_800869A4(void);
// void func_80086AF0(void);
f32 func_80086B30(f32 y, f32 x);
// void func_80086C18(void);
f32 func_80086C48(f32 param_1);
// void func_80086C70(void);
f64 func_80086C7C(f64 param_1);
s32 func_80086C88(f32 param_1);
s32 func_80086C98(f64 param_1);
// void func_80086CA8(void);
f64 func_80086CB4(f64 param_1);
s32 func_80086CC0(f32 param_1);
s32 func_80086CD0(f64 param_1);
// void func_80086CE0(void);
f64 func_80086CEC(f64 param_1);
s32 func_80086CF8(f32 param_1);
s32 func_80086D08(f64 param_1);
// void func_80086D18(void);
// void func_80086D24(void);
s32 func_80086D30(f32 param_1);
s32 func_80086D40(f64 param_1);
// void func_80086D50(void);
f64 func_80086D6C(f64 param_1);
s32 func_80086D8C(f32 param_1);
s32 func_80086DAC(f64 param_1);
void* SystemArena_Malloc(u32 size);
void* SystemArena_MallocR(u32 size);
void* SystemArena_Realloc(void* oldPtr, u32 newSize);
void SystemArena_Free(void* ptr);
void* SystemArena_Calloc(u32 elements, u32 size);
void SystemArena_AnalyzeArena(u32* maxFreeBlock, u32* bytesFree, u32* bytesAllocated);
u32 SystemArena_CheckArena(void);
void SystemArena_InitArena(void* start, u32 size);
void SystemArena_Cleanup(void);
u8 SystemArena_IsInitialized(void);
s32 Rand_Next(void);
void Rand_Seed(u32 seed);
f32 Rand_ZeroOne(void);
f32 Rand_Centered(void);
void Rand_Seed_Variable(u32* rndNum, u32 seed);
u32 Rand_Next_Variable(u32* param_1);
f32 Rand_ZeroOne_Variable(u32* param_1);
f32 Rand_Centered_Variable(u32* param_1);
void ArenaImpl_LockInit(Arena* heap);
void ArenaImpl_Lock(Arena* heap);
void ArenaImpl_Unlock(Arena* heap);
ArenaNode* ArenaImpl_GetLastBlock(Arena* param_1);
void __osMallocInit(Arena* heap, void* heapBase, u32 heapSize);
void __osMallocAddBlock(Arena* heap, void* start, s32 size);
void __osMallocCleanup(Arena* heap);
u8 __osMallocIsInitalized(Arena* heap);
void* __osMalloc(Arena* heap, u32 size);
void* __osMallocR(Arena* heap, u32 size);
void __osFree(Arena* heap, void* ptr);
void* __osRealloc(Arena* heap, void* oldPtr, u32 newSize);
void __osAnalyzeArena(Arena* heap, u32* maxFreeBlock, u32* bytesFree, u32* bytesAllocated);
u32 __osCheckArena(Arena* heap);
void* proutSprintf(void* s, const char* buf, size_t n);
s32 vsprintf(char* dst, char* fmt, va_list args);
s32 sprintf(char* s, char* fmt, ...);
void PrintUtils_VPrintf(void* callback, const char* fmt, va_list args);
// void PrintUtils_Printf(void);
void Sleep_Cycles(OSTime time);
// void Sleep_Nsec(void);
void Sleep_Usec(s32);
void Sleep_Msec(u32 param_1);
// void Sleep_Sec(void);
// void __osSetCause(void);
s32 osSendMesg(OSMesgQueue* mq, OSMesg msg, s32 flags);
// void osPfsFreeBlocks(void);
void osViExtendVStart(u32 param_1);
void osStopThread(OSThread* t);
s32 osRecvMesg(OSMesgQueue* mq, OSMesg* msg, s32 flags);
OSIntMask osSetIntMask(OSIntMask im);
// OSIntMask osGetIntMask(void);
// void osVoiceSetWord(void);
// void guScale(void);
f32 __sinf(f32 __x);
s16 sins(u16 x);
OSTask* _VirtualToPhysicalTask(OSTask* intp);
void osSpTaskLoad(OSTask* intp);
void osSpTaskStartGo(OSTask* tp);
long long __ull_rshift(unsigned long long left, unsigned long long right);
unsigned long long __ull_rem(unsigned long long left, unsigned long long right);
unsigned long long __ull_div(unsigned long long left, unsigned long long right);
long long __ll_lshift(long long left, long long right);
long long __ll_rem(long long left, unsigned long long right);
long long __ll_div(long long left, long long right);
long long __ll_mul(long long left, long long right);
void __ull_divremi(unsigned long long* quotient, unsigned long long* remainder, unsigned long long dividend,
                   unsigned short divisor);
long long __ll_mod(long long left, long long right);
long long __ll_rshift(long long left, long long right);
void __osExceptionPreamble(void);
void __osException(void);
// void send_mesg(void);
// void handle_CpU(void);
void __osEnqueueAndYield(OSThread** param_1);
void __osEnqueueThread(OSThread** param_1, OSThread* param_2);
OSThread* __osPopThread(OSThread** param_1);
// void __osNop(void);
void __osDispatchThread(void);
void __osCleanupThread(void);
void __osDequeueThread(OSThread** param_1, OSThread* param_2);
void osDestroyThread(OSThread* puParm1);
// void __osVoiceCheckResult(void);
void bzero(void* begin, s32 length);
// void osSetRumble(void);
// void osSetUpMempakWrite(void);
// void osProbeRumblePak(void);
void __osSiCreateAccessQueue(void);
void __osSiGetAccess(void);
void __osSiRelAccess(void);
s32 osContInit(OSMesgQueue* mq, u8* bitpattern, OSContStatus* data);
void __osContGetInitData(u8* pattern, OSContStatus* data);
void __osPackRequestData(u8 cmd);
void osCreateThread(OSThread* t, OSId id, void* entry, void* arg, void* sp, OSPri p);
s32 osContStartReadData(OSMesgQueue* mq);
void osContGetReadData(OSContPad* data);
void __osPackReadData(void);
// void osVoiceGetReadData(void);
uintptr_t osVirtualToPhysical(void* vaddr);
u32 __osGetSR(void);
void __osSetSR(u32 value);
void osWritebackDCache(void* vaddr, s32 nbytes);
void __createSpeedParam(void);
void osInitialize(void);
void __osInitialize_autodetect(void);
void* osViGetNextFramebuffer(void);
void guPerspectiveF(float mf[4][4], u16* perspNorm, f32 fovy, f32 aspect, f32 near, f32 far, f32 scale);
void guPerspective(Mtx* m, u16* perspNorm, f32 fovy, f32 aspect, f32 near, f32 far, f32 scale);
s32 __osSpRawStartDma(s32 direction, void* devAddr, void* dramAddr, u32 size);
s32 __osSiRawStartDma(s32 direction, void* dramAddr);
// void osEPiLinkHandle(void);
void osViBlack(u8 active);
s32 __osSiRawReadIo(u32 devAddr, u32* data);
OSId osGetThreadId(OSThread* t);
void osSpTaskYield(void);
s32 __osPfsGetNextPage(OSPfs* param_1, __OSInode* param_2, u8 param_3, u8 param_4);
s32 osPfsReadWriteFile(OSPfs* pfs, s32 file_no, u8 flag, s32 offset, s32 size_in_bytes, u8* data_buffer);
// void __osPfsGetStatus(void);
// void __osPfsRequestOneChannel(void);
// void __osPfsGetOneChannelData(void);
void guMtxIdentF(float mf[4][4]);
void osViSetMode(OSViMode* modep);
// void __osGetConfig(void);
// void __osSetConfig(void);
void guLookAtF(float mf[4][4], f32 xEye, f32 yEye, f32 zEye, f32 xAt, f32 yAt, f32 zAt, f32 xUp, f32 yUp, f32 zUp);
void guLookAt(Mtx* m, f32 xEye, f32 yEye, f32 zEye, f32 xAt, f32 yAt, f32 zAt, f32 xUp, f32 yUp, f32 zUp);
// void osPfsAllocateFile(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5,
// UNK_TYPE4 param_6, UNK_TYPE4 param_7); void __osPfsDeclearPage(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1
// param_3, UNK_TYPE1 param_4, UNK_TYPE1 param_5, UNK_TYPE4 param_6, UNK_TYPE4 param_7);
s32 osStopTimer(OSTimer* t);
u32 __osProbeTLB(void* param_1);
void osCreatePiManager(OSPri pri, OSMesgQueue* cmdQ, OSMesg* cmdBuf, s32 cmdMsgCnt);
void __osPiCreateAccessQueue(void);
void __osPiGetAccess(void);
void __osPiRelAccess(void);
void __osDevMgrMain(void* arg);
// void func_8008C640(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE1 param_5,
// UNK_TYPE1 param_6, UNK_TYPE1 param_7, UNK_TYPE1 param_8, UNK_TYPE4 param_9, UNK_TYPE4 param_10, UNK_TYPE4 param_11,
// UNK_TYPE4 param_12, UNK_TYPE4 param_13, UNK_TYPE4 param_14, UNK_TYPE4 param_15, UNK_TYPE4 param_16, UNK_TYPE4
// param_17, UNK_TYPE4 param_18);
s32 osPiRawStartDma(s32 direction, u32 devAddr, void* dramAddr, u32 size);
// void __osSumcalc(void);
// void __osIdCheckSum(void);
// void __osRepairPackId(void);
// void __osCheckPackId(void);
// void __osGetId(void);
// void __osCheckId(void);
// void __osPfsRWInode(void);
u32 osGetCount(void);
void guMtxL2F(MtxF* m1, Mtx* m2);
u32 osGetMemSize(void);
// void osPfsFindFile(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5,
// UNK_TYPE4 param_6);
void osSetEventMesg(OSEvent e, OSMesgQueue* mq, OSMesg m);
f32 sqrtf(f32 __x);
s32 osAfterPreNMI(void);
s32 osContStartQuery(OSMesgQueue* mq);
void osContGetQuery(OSContStatus* data);
void guLookAtHiliteF(float mf[4][4], LookAt* l, Hilite* h, f32 xEye, f32 yEye, f32 zEye, f32 xAt, f32 yAt, f32 zAt,
                     f32 xUp, f32 yUp, f32 zUp, f32 xl1, f32 yl1, f32 zl1, f32 xl2, f32 yl2, f32 zl2, s32 twidth,
                     s32 theight);
void guLookAtHilite(Mtx* m, LookAt* l, Hilite* h, f32 xEye, f32 yEye, f32 zEye, f32 xAt, f32 yAt, f32 zAt, f32 xUp,
                    f32 yUp, f32 zUp, f32 xl1, f32 yl1, f32 zl1, f32 xl2, f32 yl2, f32 zl2, s32 twidth, s32 theight);
s32 _Printf(PrintCallback pfn, void* arg, const char* fmt, va_list ap);
void _Putfld(_Pft* px, va_list* pap, u8 code, u8* ac);
// void osVoiceClearDictionary(void);
void osUnmapTLBAll(void);
s32 osEPiStartDma(OSPiHandle* pihandle, OSIoMesg* mb, s32 direction);
// void __osVoiceContRead2(void);
// void __osVoiceContDataCrc(void);
const char* strchr(const char* __s, s32 __c);
size_t strlen(const char* __s);
void* memcpy(void* __dest, const void* __src, size_t __n);
void osCreateMesgQueue(OSMesgQueue* mq, OSMesg* msq, s32 count);
void osInvalICache(void* vaddr, s32 nbytes);
void osInvalDCache(void* vaddr, s32 nbytes);
void __osTimerServicesInit(void);
void __osTimerInterrupt(void);
void __osSetTimerIntr(OSTime tim);
OSTime __osInsertTimer(OSTimer* t);
// void __osVoiceContRead36(void);
s32 __osSpDeviceBusy(void);
s32 __osSiDeviceBusy(void);
// void guMtxIdent(void);
s32 osJamMesg(OSMesgQueue* mq, OSMesg msg, s32 flag);
void osSetThreadPri(OSThread* t, OSPri pri);
OSPri osGetThreadPri(OSThread* t);
s32 osEPiRawReadIo(OSPiHandle* handle, u32 devAddr, u32* data);
void osViSwapBuffer(void* frameBufPtr);
void guPositionF(float mf[4][4], f32 r, f32 p, f32 h, f32 s, f32 x, f32 y, f32 z);
void guPosition(Mtx* m, f32 r, f32 p, f32 h, f32 s, f32 x, f32 y, f32 z);
s32 osEPiRawStartDma(OSPiHandle*, s32, u32, void*, u32);
OSYieldResult osSpTaskYielded(OSTask* task);
s32 bcmp(void* __s1, void* __s2, size_t __n);
OSTime osGetTime(void);
void guRotateF(float mf[4][4], f32 a, f32 x, f32 y, f32 z);
void guRotate(Mtx* m, f32 a, f32 x, f32 y, f32 z);
void __osSetGlobalIntMask(u32 mask);
// void osVoiceInit(void);
// void __osContChannelReset(void);
// void __osVoiceSetADConverter(void);
s32 osAiSetFrequency(u32 frequency);
s32 __osContRamRead(OSMesgQueue* mq, s32 channel, u16 address, u8* buffer);
// void __osVoiceContWrite20(void);
u8 __osContAddressCrc(u16 addr);
u8 __osContDataCrc(u8* data);
OSThread* __osGetActiveQueue(void);
void guNormalize(float* x, float* y, float* z);
void __osSetCompare(u32 value);
// u32 __osGetCompare(void);
u32 osDpGetStatus(void);
void osDpSetStatus(u32 data);
void bcopy(void* __src, void* __dest, size_t __n);
void __osResetGlobalIntMask(u32 mask);
// void osPfsDeleteFile(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5);
// void __osPfsReleasePages(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4
// param_5);
void guOrthoF(float mf[4][4], f32 l, f32 r, f32 b, f32 t, f32 n, f32 f, f32 scale);
void guOrtho(Mtx* m, f32 l, f32 r, f32 b, f32 t, f32 n, f32 f, f32 scale);
OSIntMask __osDisableInt(void);
void __osRestoreInt(OSIntMask im);
void __osViInit(void);
void __osViSwapContext(void);
OSMesgQueue* osPiGetCmdQueue(void);
f32 __cosf(f32 __x);
// void osEPiReadIo(void);
void osViSetSpecialFeatures(u32 func);
s16 coss(u16 x);
void osSetTime(OSTime ticks);
// void osVoiceStopReadData(void);
void osViSetEvent(OSMesgQueue* mq, OSMesg m, u32 retraceCount);
s32 osPfsIsPlug(OSMesgQueue* queue, u8* pattern);
// void __osPfsRequestData(void);
// void __osPfsGetInitData(void);
s32 __osVoiceGetStatus(OSMesgQueue* mq, s32 port, u8* status);
OSPiHandle* osCartRomInit(void);
// void guS2DInitBg(void);
// s32 __osPfsSelectBank(OSPfs* pfs, UNK_TYPE4 param_2);
s32 osContSetCh(u8 ch);
u32 __osSetFpcCsr(u32 value);
u32 __osGetFpcCsr(void);
// void osPfsFileState(void);
// void osPfsInitPak(void);
// void __osPfsCheckRamArea(void);
// void osPfsChecker(void);
// void corrupted_init(void);
// void corrupted(void);
u32 osAiGetLength(void);
// void osEPiWriteIo(void);
void osMapTLBRdb(void);
void osYieldThread(void);
// void guTranslate(void);
u32 __osGetCause(void);
s32 __osContRamWrite(OSMesgQueue* mq, s32 channel, u16 address, u8* buffer, s32 force);
s32 __osEPiRawWriteIo(OSPiHandle* handle, u32 devAddr, u32 data);
s32 osSetTimer(OSTimer* t, OSTime value, OSTime interval, OSMesgQueue* mq, OSMesg msg);
void _Ldtob(_Pft* px, u8 code);
// void _Ldunscale(void);
void _Genld(_Pft* px, u8 code, u8* p, s16 nsig, s16 xexp);
ldiv_t ldiv(long numer, long denom);
lldiv_t lldiv(long long numer, long long denom);
void _Litob(_Pft* px, u8 code);
s32 __osSiRawWriteIo(u32 devAddr, u32 data);
u32 __osSpGetStatus(void);
void __osSpSetStatus(u32 value);
void osCreateViManager(OSPri pri);
void viMgrMain(OSDevMgr* iParm1);
__OSViContext* __osViGetCurrentContext(void);
void osWritebackDCacheAll(void);
OSThread* __osGetCurrFaultedThread(void);
// void osVoiceMaskDictionary(void);
void guMtxF2L(float mf[4][4], Mtx* m);
void osStartThread(OSThread* param_1);
void osViSetYScale(f32 value);
void osViSetXScale(f32 value);
long long __d_to_ll(double d);
long long __f_to_ll(float f);
unsigned long long __d_to_ull(double d);
unsigned long long __f_to_ull(float f);
double __ll_to_d(long long l);
float __ll_to_f(long long l);
double __ull_to_d(unsigned long long l);
float __ull_to_f(unsigned long long l);
// void osVoiceCheckWord(void);
// void osVoiceControlGain(void);
// void osVoiceStartReadData(void);
void* osViGetCurrentFramebuffer(void);
s32 __osSpSetPc(void* data);
// void __osVoiceContWrite4(void);
void __osGetHWIntrRoutine(s32 idx, OSMesgQueue** outQueue, OSMesg* outMsg);
// void __osSetHWIntrRoutine(void);
u32 __osGetWatchLo(void);
void __osSetWatchLo(u32 value);
f32 fmodf(f32 dividend, f32 divisor);
void* __osMemset(void* ptr, s32 val, u32 size);
s32 __osStrcmp(const char* str1, const char* str2);
char* __osStrcpy(char* dst, const char* src);
void* __osMemcpy(void* dst, void* src, size_t size);
void EnAObj_Init(ActorEnAObj* this, GlobalContext* globalCtx);
void EnAObj_Destroy(ActorEnAObj* this, GlobalContext* globalCtx);
void EnAObj_Update1(ActorEnAObj* this, GlobalContext* globalCtx);
void EnAObj_Update2(ActorEnAObj* this, GlobalContext* globalCtx);
void EnAObj_Update(ActorEnAObj* this, GlobalContext* globalCtx);
void EnAObj_Draw(ActorEnAObj* this, GlobalContext* globalCtx);
// void EnItem00_SetObject(EnItem00* this, GlobalContext* globalCtx, f32* shadowOffset, f32* shadowScale);
// void EnItem00_Init(Actor* thisx, GlobalContext* globalCtx);
// void EnItem00_Destroy(Actor* thisx, GlobalContext* globalCtx);
// void EnItem00_WaitForHeartObject(EnItem00* this, GlobalContext* globalCtx);
// void func_800A640C(EnItem00* this, GlobalContext* globalCtx);
// void func_800A6650(EnItem00* this, GlobalContext* globalCtx);
// void func_800A6780(EnItem00* this, GlobalContext* globalCtx);
// void func_800A6A40(EnItem00* this, GlobalContext* globalCtx);
// void EnItem00_Update(Actor* thisx, GlobalContext* globalCtx);
// void EnItem00_Draw(Actor* thisx, GlobalContext* globalCtx);
// void EnItem00_DrawRupee(EnItem00* this, GlobalContext* globalCtx);
// void EnItem00_DrawSprite(EnItem00* this, GlobalContext* globalCtx);
// void EnItem00_DrawHeartContainer(EnItem00* this, GlobalContext* globalCtx);
// void EnItem00_DrawHeartPiece(EnItem00* this, GlobalContext* globalCtx);
// s16 func_800A7650(s16 dropId);
EnItem00* Item_DropCollectible(GlobalContext* globalCtx, Vec3f* spawnPos, u32 params);
Actor* Item_DropCollectible2(GlobalContext* globalCtx, Vec3f* spawnPos, u32 params);
void Item_DropCollectibleRandom(GlobalContext* globalCtx, Actor* fromActor, Vec3f* spawnPos, s16 params);
s32 func_800A8150(s32 index);
s32 func_800A817C(s32 index);
s32 func_800A81A4(GlobalContext* globalCtx, s32 a1, s32 a2);
void func_800A81F0(EffectBlure* this, Vec3f* p1, Vec3f* p2);
void func_800A8514(void* effectParams);
void EffectBlure_Initcommon(EffectBlure* params);
void EffectBlure_Init1(EffectBlure* params, EffBlureInit1* init);
void EffectBlure_Init2(EffectBlure* params, EffBlureInit2* init);
void EffectBlure_Destroy(EffectBlure* params);
s32 EffectBlure_Update(EffectBlure* params);
// void func_800A8C78(void);
// void func_800A8DE8(void);
// void func_800A92FC(void);
// void func_800A9330(void);
// void func_800A9804(void);
// void func_800AA190(void);
// void func_800AA460(void);
// void func_800AA498(void);
// void func_800AA700(void);
// void func_800AABE0(void);
void EffectBlure_Draw(EffectBlure* params, GraphicsContext* gfxCtx);
void EffectShieldParticle_Init(EffShieldParticleParams* params, EffShieldParticleInit* init);
void EffectShieldParticle_Destroy(EffShieldParticleParams* params);
s32 EffectShieldParticle_Update(EffShieldParticleParams* params);
void EffectShieldParticle_CalculateColors(EffShieldParticleParams* params, Color_RGBA8* primColor,
                                          Color_RGBA8* envColor);
void EffectShieldParticle_Draw(EffShieldParticleParams* params, GraphicsContext* gfxCtx);
void EffectSpark_Init(EffSparkParams* params, EffSparkParams* init);
void EffectSpark_Destroy(EffSparkParams* params);
s32 EffectSpark_Update(EffSparkParams* params);
void EffectSpark_Draw(EffSparkParams* params, GraphicsContext* gfxCtx);
// void func_800AE2A0(void);
void func_800AE434(GlobalContext* globalCtx, Color_RGBA8* color, s16 sParm3, s16 sParm4);
void func_800AE5A0(GlobalContext* globalCtx);
// void func_800AE5E4(void);
void func_800AE778(GlobalContext* globalCtx, Color_RGBA8* color, s16 param_3, s16 param_4);
void func_800AE8EC(GlobalContext* globalCtx);
void func_800AE930(CollisionContext* colCtx, s32 param_2, float* param_3, f32 param_4, s16 param_5,
                   CollisionPoly* param_6, s32 param_7);
// void func_800AEF44(void);
void EffectTireMark_InitParticle(EffTireMarkParticle* particle);
void EffectTireMark_Init(EffTireMarkParams* params, EffTireMarkInit* init);
void EffectTireMark_Destroy(EffTireMarkParams* params);
s32 EffectTireMark_Update(EffTireMarkParams* params);
void EffectTireMark_InitVertices(F3DVertexColor* vertices, EffTireMarkParticle* particle, s32 index, s32 alpha);
void EffectTireMark_Draw(EffTireMarkParams* params, GraphicsContext* gfxCtx);
GlobalContext* Effect_GetContext(void);
void* Effect_GetParams(s32 index);
void Effect_InitCommon(EffCommon* common);
void Effect_Init(GlobalContext* globalCtx);
void Effect_Add(GlobalContext* globalCtx, s32* index, s32 type, u8 param_4, u8 param_5, void* initParams);
void Effect_DrawAll(GraphicsContext* gfxCtx);
void Effect_UpdateAll(GlobalContext* globalCtx);
void Effect_Destroy(GlobalContext* globalCtx, s32 index);
void Effect_DestroyAll(GlobalContext* globalCtx);
void EffectSS_Init(GlobalContext* globalCtx, s32 numEntries);
void EffectSS_Clear(GlobalContext* globalCtx);
EffectSs* EffectSS_GetTable(void);
void EffectSS_Delete(EffectSs* param_1);
void EffectSS_ResetEntry(EffectSs* particle);
s32 EffectSS_FindFreeSpace(s32 priority, s32* tableEntry);
void EffectSS_Copy(GlobalContext* globalCtx, EffectSs* particle);
void EffectSs_Spawn(GlobalContext* globalCtx, s32 type, s32 priority, void* initParams);
void EffectSS_UpdateParticle(GlobalContext* globalCtx, s32 index);
void EffectSS_UpdateAllParticles(GlobalContext* globalCtx);
void EffectSS_DrawParticle(GlobalContext* globalCtx, s32 index);
void EffectSS_DrawAllParticles(GlobalContext* globalCtx);
s16 func_800B096C(s16 param_1, s16 param_2, s32 param_3);
s16 func_800B09D0(s16 a0, s16 a1, f32 a2);
u8 func_800B0A24(u8 a0, u8 a1, f32 a2);
void EffectSs_DrawGEffect(GlobalContext* globalCtx, EffectSs* this, void* texture);
void EffectSsDust_Spawn(GlobalContext* globalCtx, u16 drawFlags, Vec3f* pos, Vec3f* velocity, Vec3f* accel,
                        Color_RGBA8* primColor, Color_RGBA8* envColor, s16 scale, s16 scaleStep, s16 life,
                        u8 updateMode);
void func_800B0DE0(GlobalContext* globalCtx, Vec3f* pos, Vec3f* velocity, Vec3f* accel, Color_RGBA8* primColor,
                   Color_RGBA8* envColor, s16 scale, s16 scaleStep);
void func_800B0E48(GlobalContext* globalCtx, Vec3f* pos, Vec3f* velocity, Vec3f* accel, Color_RGBA8* primColor,
                   Color_RGBA8* envColor, s16 scale, s16 scaleStep);
void func_800B0EB0(GlobalContext* globalCtx, Vec3f* pos, Vec3f* velocity, Vec3f* accel, Color_RGBA8* primColor,
                   Color_RGBA8* envColor, s16 scale, s16 scaleStep, s16 life);
void func_800B0F18(GlobalContext* globalCtx, Vec3f* pos, Vec3f* velocity, Vec3f* accel, Color_RGBA8* primColor,
                   Color_RGBA8* envColor, s16 scale, s16 scaleStep, s16 life);
void func_800B0F80(GlobalContext* globalCtx, Vec3f* pos, Vec3f* velocity, Vec3f* accel, Color_RGBA8* primColor,
                   Color_RGBA8* envColor, s16 scale, s16 scaleStep, s16 life);
void func_800B0FE8(GlobalContext* globalCtx, Vec3f* pos, Vec3f* velocity, Vec3f* accel, Color_RGBA8* primColor,
                   Color_RGBA8* envColor, s16 scale, s16 scaleStep);
void func_800B1054(GlobalContext* globalCtx, Vec3f* pos, Vec3f* velocity, Vec3f* accel, Color_RGBA8* primColor,
                   Color_RGBA8* envColor, s16 scale, s16 scaleStep);
void func_800B10C0(GlobalContext* globalCtx, Vec3f* pos, Vec3f* velocity, Vec3f* accel);
void func_800B1130(GlobalContext* globalCtx, Vec3f* pos, Vec3f* velocity, Vec3f* accel);
void func_800B11A0(GlobalContext* globalCtx, Vec3f* pos, Vec3f* velocity, Vec3f* accel, s16 scale, s16 scaleStep);
void func_800B1210(GlobalContext* globalCtx, Vec3f* pos, Vec3f* velocity, Vec3f* accel, s16 scale, s16 scaleStep);
void func_800B1280(GlobalContext* globalCtx, Vec3f* pos, Vec3f* velocity, Vec3f* accel, s16 scale, s16 scaleStep,
                   s16 life);
void func_800B12F0(GlobalContext* globalCtx, Vec3f* pos, Vec3f* velocity, Vec3f* accel, s16 scale, s16 scaleStep,
                   s16 life);
void func_800B1360(GlobalContext* globalCtx, Vec3f* pos, Vec3f* velocity, Vec3f* accel, Color_RGBA8* primColor,
                   Color_RGBA8* envColor);
void func_800B139C(GlobalContext* globalCtx, Vec3f* pos, Vec3f* velocity, Vec3f* accel, Color_RGBA8* primColor,
                   Color_RGBA8* envColor);
void func_800B13D8(Vec3f* srcPos, f32 randScale, Vec3f* newPos, Vec3f* velocity, Vec3f* accel);
void func_800B14D4(GlobalContext* globalCtx, f32 randScale, Vec3f* srcPos);
void func_800B1598(GlobalContext* globalCtx, f32 randScale, Vec3f* srcPos);
void EffectSsKiraKira_SpawnSmallYellow(GlobalContext* globalCtx, Vec3f* pos, Vec3f* velocity, Vec3f* accel);
void EffectSsKiraKira_SpawnSmall(GlobalContext* globalCtx, Vec3f* pos, Vec3f* velocity, Vec3f* accel,
                                 Color_RGBA8* primColor, Color_RGBA8* envColor);
void EffectSsGSpk_SpawnSmall(GlobalContext* globalCtx, Actor* actor, Vec3f* pos, Vec3f* velocity, Vec3f* accel,
                             Color_RGBA8* primColor, Color_RGBA8* envColor);
void EffectSsKiraKira_SpawnDispersed(GlobalContext* globalCtx, Vec3f* pos, Vec3f* velocity, Vec3f* accel,
                                     Color_RGBA8* primColor, Color_RGBA8* envColor, s16 scale, s32 life);
// void EffectSsKiraKira_SpawnFocused(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4,
// UNK_TYPE4 param_5, UNK_TYPE4 param_6, UNK_TYPE2 param_7, UNK_TYPE4 param_8); void EffectSsBomb2_SpawnFade(UNK_TYPE4
// uParm1, Vec3f* pzParm2, Vec3f* pzParm3, Vec3f* pzParm4); void EffectSsBomb2_SpawnLayered(UNK_TYPE4 param_1, Vec3f*
// param_2, Vec3f* param_3, Vec3f* param_4, UNK_TYPE2 param_5, UNK_TYPE2 param_6); void EffectSsBlast_Spawn(UNK_TYPE4
// uParm1, Vec3f* pzParm2, Vec3f* pzParm3, Vec3f* pzParm4, Color_RGBA8* param_5, Color_RGBA8* param_6, UNK_TYPE2
// param_7, UNK_TYPE2 param_8, UNK_TYPE2 param_9, UNK_TYPE2 param_10); void
// EffectSsBlast_SpawnWhiteCustomScale(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4,
// UNK_TYPE2 param_5, UNK_TYPE2 param_6, UNK_TYPE2 param_7); void EffectSsBlast_SpawnShockwave(UNK_TYPE1 param_1,
// UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6, UNK_TYPE2 param_7);
// void EffectSsBlast_SpawnWhiteShockwave(void);
// void EffectSsGSpk_SpawnAccel(UNK_TYPE4 uParm1, UNK_TYPE4 uParm2, Vec3f* pzParm3, Vec3f* pzParm4, Vec3f* param_5, Color_RGBA8* param_6, Color_RGBA8* param_7, UNK_TYPE2 param_8, UNK_TYPE2 param_9);
// void EffectSsGSpk_SpawnNoAccel(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6, UNK_TYPE4 param_7, UNK_TYPE2 param_8, UNK_TYPE2 param_9);
// void EffectSsGSpk_SpawnFuse(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5);
// void EffectSsGSpk_SpawnRandColor(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE2 param_6, UNK_TYPE2 param_7);
// void EffectSsGSpk_SpawnSmall(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6, UNK_TYPE4 param_7);
void EffectSsDFire_Spawn(GlobalContext* globalCtx, Vec3f* pos, Vec3f* velocity, Vec3f* accel, s16 scale, s16 scaleStep,
                         s16 alpha, s16 fadeDelay, s16 arg8, s32 life);
void EffectSsBubble_Spawn(GlobalContext* globalCtx, Vec3f* pos, f32 yPosOffset, f32 yPosRandScale, f32 xzPosRandScale,
                          f32 scale);
void EffectSsGRipple_Spawn(GlobalContext* globalCtx, Vec3f* pos, s16 radius, s16 radiusMax, s16 life);
void EffectSsGSplash_Spawn(GlobalContext* globalCtx, Vec3f* pos, Color_RGBA8* primColor, Color_RGBA8* envColor,
                           s16 type, s16 scale);
// void EffectSsGFire_Spawn(UNK_TYPE4 uParm1, Vec3f* pzParm2);
// void EffectSsLightning_Spawn(UNK_TYPE4 uParm1, Vec3f* pzParm2, Color_RGBA8* pzParm3, Color_RGBA8* pzParm4, UNK_TYPE2
// param_5, UNK_TYPE2 param_6, UNK_TYPE2 param_7, UNK_TYPE2 param_8); void EffectSsDtBubble_SpawnColorProfile(UNK_TYPE4
// param_1, Vec3f* param_2, Vec3f* param_3, Vec3f* param_4, UNK_TYPE2 param_5, UNK_TYPE2 param_6, UNK_TYPE2 param_7,
// UNK_TYPE2 param_8);
void EffectSsDtBubble_SpawnCustomColor(GlobalContext* globalCtx, Vec3f* pos, Vec3f* velocity, Vec3f* accel,
                                       Color_RGBA8* primColor, Color_RGBA8* envColor, s16 scale, s16 life, s16 randXZ);
void EffectSsHahen_Spawn(GlobalContext* globalCtx, Vec3f* pos, Vec3f* velocity, Vec3f* accel, s16 unused, s16 scale,
                         s16 objId, s16 life, Gfx* dList);
void EffectSsHahen_SpawnBurst(GlobalContext* globalCtx, Vec3f* pos, f32 burstScale, s16 unused, s16 scale,
                              s16 randScaleRange, s16 count, s16 objId, s16 life, Gfx* dList);
// void func_800B2364(void);
// void EffectSsStick_Spawn(UNK_TYPE4 uParm1, UNK_PTR puParm2, UNK_TYPE2 uParm3);
// void EffectSsSibuki_Spawn(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE2
// param_5, UNK_TYPE2 param_6, UNK_TYPE2 param_7);
void EffectSsSibuki_SpawnBurst(GlobalContext* globalCtx, Vec3f* pos);
// void EffectSsStone1_Spawn(UNK_TYPE4 uParm1, UNK_PTR puParm2, UNK_TYPE4 uParm3);
// void EffectSsHitMark_Spawn(UNK_TYPE4 uParm1, UNK_TYPE4 uParm2, UNK_TYPE2 uParm3, Vec3f* pzParm4);
void EffectSsHitMark_SpawnFixedScale(GlobalContext* globalCtx, s32 type, Vec3f* pos);
// void EffectSsHitMark_SpawnCustomScale(void);
// void EffectSsFhgFlash_SpawnShock(UNK_TYPE4 uParm1, UNK_TYPE4 uParm2, Vec3f* pzParm3, UNK_TYPE2 uParm4, UNK_TYPE1
// param_5); void EffectSsKFire_Spawn(UNK_TYPE4 uParm1, Vec3f* pzParm2, Vec3f* pzParm3, Vec3f* pzParm4, UNK_TYPE2
// param_5, UNK_TYPE1 param_6);
void EffectSsSolderSrchBall_Spawn(GlobalContext* globalCtx, Vec3f* pos, Vec3f* velocity, Vec3f* accel, s16 unused,
                                  s16* linkDetected, s16 drawFlag);
void EffectSsKakera_Spawn(GlobalContext* globalCtx, Vec3f* pos, Vec3f* velocity, Vec3f* arg3, s16 gravity, s16 arg5,
                          s16 arg6, s16 arg7, s16 arg8, s16 scale, s16 arg10, s16 arg11, s32 life, s16 colorIdx,
                          s16 objId, Gfx* dList);
// void EffectSsIcePiece_Spawn(UNK_TYPE4 uParm1, Vec3f* pzParm2, UNK_TYPE4 uParm3, Vec3f* pzParm4, Vec3f* param_5,
// UNK_TYPE4 param_6); void EffectSsIcePiece_SpawnBurst(void); void EffectSsEnIce_SpawnFlyingVec3f(UNK_TYPE4 uParm1,
// Actor* pzParm2, Vec3f* pzParm3, Color_RGBA8* pzParm4, Color_RGBA8* param_5, UNK_TYPE4 param_6); void
// func_800B2B44(void); void func_800B2B7C(void);
void EffectSsEnIce_Spawn(GlobalContext* globalCtx, Vec3f* pos, f32 scale, Vec3f* velocity, Vec3f* accel,
                         Color_RGBA8* primColor, Color_RGBA8* envColor, s32 life);
// void EffectSsFireTail_Spawn(UNK_TYPE4 uParm1, UNK_TYPE4 uParm2, Vec3f* pzParm3, UNK_TYPE4 uParm4, Vec3f* param_5,
// UNK_TYPE2 param_6, Color_RGBA8* param_7, Color_RGBA8* param_8, UNK_TYPE2 param_9, UNK_TYPE2 param_10, UNK_TYPE4
// param_11); void EffectSsFireTail_SpawnFlame(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1
// param_4, UNK_TYPE2 param_5, UNK_TYPE4 param_6); void EffectSsFireTail_SpawnFlameOnPlayer(void);
void EffectSsEnFire_SpawnVec3f(GlobalContext* globalCtx, Actor* actor, Vec3f* pos, s16 scale, s16 arg4, s16 flags,
                               s16 bodyPart);
// void EffectSsEnFire_SpawnVec3s(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE2
// param_5, UNK_TYPE2 param_6, UNK_TYPE2 param_7); void EffectSsExtra_Spawn(UNK_TYPE4 uParm1, Vec3f* pzParm2, Vec3f*
// pzParm3, Vec3f* pzParm4, UNK_TYPE2 param_5, UNK_TYPE2 param_6);
void EffectSsDeadDb_Spawn(GlobalContext* globalCtx, Vec3f* pos, Vec3f* velocity, Vec3f* accel, Color_RGBA8* prim,
                          Color_RGBA8* env, s16 scale, s16 scaleStep, s32 unk);
void func_800B3030(GlobalContext* globalCtx, Vec3f* pos, Vec3f* velocity, Vec3f* accel, s16 scale, s16 scaleStep,
                   s32 colorIndex);
// void EffectSsDeadDd_Spawn(UNK_TYPE4 uParm1, Vec3f* pzParm2, Vec3f* pzParm3, Vec3f* pzParm4, UNK_TYPE1* param_5,
// UNK_TYPE1* param_6, UNK_TYPE2 param_7, UNK_TYPE2 param_8, UNK_TYPE2 param_9, UNK_TYPE4 param_10); void
// EffectSsDeadDs_Spawn(UNK_TYPE4 uParm1, Vec3f* pzParm2, Vec3f* pzParm3, Vec3f* pzParm4, UNK_TYPE2 param_5, UNK_TYPE2
// param_6, UNK_TYPE2 param_7, UNK_TYPE4 param_8); void func_800B31BC(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1
// param_3, UNK_TYPE1 param_4, UNK_TYPE2 param_5, UNK_TYPE4 param_6);
void EffectSsIceSmoke_Spawn(GlobalContext* globalCtx, Vec3f* pos, Vec3f* velocity, Vec3f* accel, s16 scale);
// void EffectSsIceBlock_Spawn(UNK_TYPE4 uParm1, Vec3f* pzParm2, Vec3f* pzParm3, Vec3f* pzParm4, UNK_TYPE2 param_5);
void func_800B32D0(GameState* gamestate);
// void func_800B3644(void);
void DLF_LoadGameState(GameStateOverlay* gameState);
void DLF_FreeGameState(GameStateOverlay* gameState);
void Actor_PrintLists(ActorContext* actorCtx);
void ActorShape_Init(ActorShape* actorShape, f32 yOffset, ActorShadowFunc func, f32 scale);
void ActorShadow_Draw(Actor* actor, Lights* mapper, GlobalContext* globalCtx, Gfx* displayList, Color_RGBA8* color);
void func_800B3FC0(Actor* actor, Lights* mapper, GlobalContext* globalCtx);
void func_800B4024(Actor* actor, Lights* mapper, GlobalContext* globalCtx);
void func_800B4088(Actor* actor, Lights* mapper, GlobalContext* globalCtx);
void func_800B40B8(Actor* actor, Lights* mapper, GlobalContext* globalCtx);
void func_800B40E0(GlobalContext* globalCtx, Light* light, MtxF* arg2, s32 arg3, f32 arg4, f32 arg5, f32 arg6);
void func_800B42F8(Actor* actor, Lights* mapper, GlobalContext* globalCtx);
void func_800B4A98(Actor* actor, s32 limbIndex, s32 leftFootIndex, Vec3f* leftFootPos, s32 rightFootIndex, Vec3f* rightFootPos);
void func_800B4AEC(GlobalContext* globalCtx, Actor* actor, f32 param_3);
void func_800B4B50(Actor* actor, s32 iParm2, GlobalContext* globalCtx);
void func_800B4EDC(GlobalContext* globalCtx, Vec3f* pzParm2, Vec3f* pzParm3, f32* pfParm4);
void func_800B4F40(TargetContext* targetCtx, s32 index, f32 x, f32 y, f32 z);
void func_800B4F78(TargetContext* targetCtx, u8 type, GlobalContext* globalCtx);
void func_800B5040(TargetContext* targetCtx, Actor* actor, u8 type, GlobalContext* globalCtx);
void Actor_TargetContextInit(TargetContext* targetCtx, Actor* actor, GlobalContext* globalCtx);
void func_800B5208(TargetContext* targetCtx, GlobalContext* globalCtx);
void func_800B5814(TargetContext* targetCtx, Player* player, Actor* actor, GlobalContext* globalCtx);
u32 Flags_GetSwitch(GlobalContext* globalCtx, s32 flag);
void Actor_SetSwitchFlag(GlobalContext* globalCtx, s32 flag);
void Actor_UnsetSwitchFlag(GlobalContext* globalCtx, s32 flag);
u32 Actor_GetChestFlag(GlobalContext* globalCtx, u32 flag);
void Actor_SetChestFlag(GlobalContext* globalCtx, u32 flag);
void Actor_SetAllChestFlag(GlobalContext* globalCtx, u32 flags);
u32 Actor_GetAllChestFlag(GlobalContext* globalCtx);
u32 Actor_GetRoomCleared(GlobalContext* globalCtx, u32 roomNumber);
void Actor_SetRoomCleared(GlobalContext* globalCtx, u32 roomNumber);
void Actor_UnsetRoomCleared(GlobalContext* globalCtx, u32 roomNumber);
u32 Actor_GetRoomClearedTemp(GlobalContext* globalCtx, u32 roomNumber);
void Actor_SetRoomClearedTemp(GlobalContext* globalCtx, u32 roomNumber);
void Actor_UnsetRoomClearedTemp(GlobalContext* globalCtx, u32 roomNumber);
u32 Actor_GetCollectibleFlag(GlobalContext* globalCtx, s32 index);
void Actor_SetCollectibleFlag(GlobalContext* globalCtx, s32 index);
void TitleCard_ContextInit(GlobalContext* globalCtx, TitleCardContext* titleCtx);
void TitleCard_InitBossName(GlobalContext* globalCtx, TitleCardContext* titleCtx, u32 texture, s16 param_4,
                           s16 param_5, u8 param_6, u8 param_7);
void TitleCard_InitPlaceName(GlobalContext* globalCtx, TitleCardContext* titleCtx, void* texture, s32 x, s32 y,
                             s32 width, s32 height, s32 delay);
void TitleCard_Update(GlobalContext* globalCtx, TitleCardContext* titleCtx);
void TitleCard_Draw(GlobalContext* globalCtx, TitleCardContext* titleCtx);
s32 func_800B6434(GlobalContext* globalCtx, TitleCardContext* titleCtx);
// UNK_TYPE4 func_800B645C(void);
void func_800B6468(GlobalContext* globalCtx);
void func_800B6474(GlobalContext* globalCtx);
s32 func_800B648C(GlobalContext* globalCtx, s32 arg1, s32 arg2, f32 arg3, Vec3f* arg4);
f32 func_800B64FC(GlobalContext* globalCtx, f32 fParm2, Vec3f* pzParm3, u32* puParm4);
void* func_800B6584(GlobalContext* globalCtx, s16 sParm2, void* pvParm3, u32 uParm4);
// UNK_TYPE4 func_800B6608(s32 iParm1, s16 sParm2);
// void func_800B6680(void);
void Actor_MarkForDeath(Actor* actor);
void Actor_InitCurrPosition(Actor* actor);
void Actor_SetHeight(Actor* actor, f32 height);
void Actor_SetRotationFromDrawRotation(Actor* actor);
void Actor_InitDrawRotation(Actor* actor);
void Actor_SetScale(Actor* actor, f32 scale);
void Actor_SetObjectDependency(GlobalContext* globalCtx, Actor* actor);
void Actor_Init(Actor* actor, GlobalContext* globalCtx);
void Actor_Destroy(Actor* actor, GlobalContext* globalCtx);
void Actor_SetMovementScale(s32 scale);
void Actor_ApplyMovement(Actor* actor);
void Actor_SetVelocityYRotationAndGravity(Actor* actor);
void Actor_SetVelocityAndMoveYRotationAndGravity(Actor* actor);
void Actor_SetVelocityXYRotation(Actor* actor);
void Actor_SetVelocityAndMoveXYRotation(Actor* actor);
void Actor_SetVelocityXYRotationReverse(Actor* actor);
void Actor_SetVelocityAndMoveXYRotationReverse(Actor* actor);
void func_800B6C04(Actor* actor, f32 speed);
void func_800B6C58(Actor* actor, SkelAnime* skelAnime);
s16 Actor_YawBetweenActors(Actor* from, Actor* to);
s16 Actor_YawBetweenActorsTop(Actor* from, Actor* to);
s16 Actor_YawToPoint(Actor* actor, Vec3f* point);
s16 Actor_PitchBetweenActors(Actor* from, Actor* to);
s16 Actor_PitchBetweenActorsTop(Actor* from, Actor* to);
s16 Actor_PitchToPoint(Actor* actor, Vec3f* point);
f32 Actor_DistanceBetweenActors(Actor* actor1, Actor* actor2);
f32 Actor_DistanceToPoint(Actor* actor, Vec3f* point);
f32 Actor_XZDistanceBetweenActors(Actor* actor1, Actor* actor2);
f32 Actor_XZDistanceToPoint(Actor* actor, Vec3f* point);
void Actor_CalcOffsetOrientedToDrawRotation(Actor* actor, Vec3f* offset, Vec3f* point);
f32 Actor_HeightDiff(Actor* actor1, Actor* actor2);
void func_800B6F20(GlobalContext* globalCtx, s32 param_2, f32 param_3, s16 param_4);
float Player_GetHeight(Player* player);
f32 func_800B7090(Player* player);
s32 func_800B7118(Player* player);
s32 func_800B7128(Player* player);
s32 func_800B715C(GlobalContext* globalCtx);
void func_800B7170(GlobalContext* globalCtx, Player* player);
void Actor_MountHorse(GlobalContext* globalCtx, Player* player, Actor* horse);
s32 func_800B7200(Player* player);
void func_800B722C(GlobalContext* globalCtx, Player* player);
s32 func_800B724C(GlobalContext* globalCtx, Actor* actor, u8 csMode);
u32 func_800B7298(GlobalContext* globalCtx, Actor* actor, u8 arg2);
void func_800B72E0(DynaPolyActor* dyna);
void func_800B72F8(DynaPolyActor* dyna, f32 a1, s16 a2);
s32 Actor_IsPlayerFacingActor(Actor* actor, s16 tolerance, GlobalContext* globalCtx);
s32 Actor_IsActorFacedByActor(Actor* actor, Actor* other, s16 tolerance);
s32 Actor_IsActorFacingPlayer(Actor* actor, s16 angle);
s32 Actor_IsActorFacingActor(Actor* actor, Actor* other, s16 tolerance);
s32 Actor_IsActorFacingPlayerAndWithinRange(Actor* actor, f32 range, s16 tolerance);
s32 Actor_IsActorFacingActorAndWithinRange(Actor* actor, Actor* other, f32 range, s16 tolerance);
void func_800B75A0(CollisionPoly* param_1, Vec3f* param_2, s16* param_3);
// UNK_TYPE4 func_800B761C(Actor* param_1, UNK_TYPE4 param_2, u32 param_3);
// UNK_TYPE4 func_800B7678(GlobalContext* globalCtx, Actor* param_2, s32 param_3, u32 param_4);
void Actor_UpdateBgCheckInfo(GlobalContext* globalCtx, Actor* actor, f32 wallCheckHeight, f32 wallCheckRadius,
                             f32 ceilingCheckHeight, u32 flags);
// void func_800B7E04(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5,
// UNK_TYPE4 param_6);
s32 func_800B7FE0(f32* param_1, f32* param_2, f32* param_3, GraphicsContext* gfxCtx);
// void func_800B8018(void);
void func_800B8050(Actor* actor, GlobalContext* globalCtx, s32 iParm3);
void func_800B8118(Actor* actor, GlobalContext* globalCtx, s32 iParm3);
// void func_800B81E0(void);
UNK_PTR func_800B8214(PosRot* param_1, Actor* param_2);
f32* func_800B8248(PosRot* param_1, Player* param_2);
// void func_800B82EC(void);
// void func_800B83BC(void);
// void func_800B83F8(void);
s32 Actor_IsTalking(Actor* actor, GlobalContext* globalCtx);
s32 func_800B8500(Actor* actor, GlobalContext* globalCtx, f32 fParm3, f32 fParm4, s32 param_5);
s32 func_800B85E0(Actor* actor, GlobalContext* globalCtx, f32 uParm3, s32 uParm4);
s32 func_800B8614(Actor* actor, GlobalContext* globalCtx, f32 uParm3);
s32 func_800B863C(Actor* actor, GlobalContext* globalCtx);
u32 func_800B867C(Actor* actor, GlobalContext* globalCtx);
UNK_TYPE4 func_800B86C8(Actor* actor1, GlobalContext* globalCtx, Actor* actor2);
s32 func_800B8708(GlobalContext* globalCtx);
// void func_800B8718(void);
// void func_800B874C(void);
// void func_800B8804(void);
// void func_800B882C(void);
// void func_800B886C(void);
void func_800B8898(GlobalContext* globalCtx, Actor* actor, s16* arg2, s16* arg3);
s32 func_800B8934(GlobalContext* globalCtx, Actor* actor);
u32 Actor_HasParent(Actor* actor, GlobalContext* globalCtx);
s32 func_800B8A1C(Actor* actor, GlobalContext* globalCtx, s32 getItemId, f32 xzRange, f32 yRange);
s32 func_800B8B84(Actor* actor, GlobalContext* globalCtx, s32 getItemId);
s32 func_800B8BB0(Actor* actor, GlobalContext* globalCtx);
s32 func_800B8BD0(Actor* actor, GlobalContext* globalCtx, s32 getItemId);
s32 Actor_HasNoParent(Actor* actor, GlobalContext* globalCtx);
// void func_800B8C20(void);
void func_800B8C50(Actor* actor, GlobalContext* globalCtx);
// void func_800B8C78(void);
// void func_800B8C9C(void);
// void func_800B8CEC(void);
// void func_800B8D10(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5,
// UNK_TYPE4 param_6, UNK_TYPE4 param_7);
void func_800B8D50(GlobalContext* globalCtx, Actor* actor, f32 arg2, s16 yaw, f32 arg4, u32 arg5);
void func_800B8D98(GlobalContext* globalCtx, Actor* actor, f32 arg2, s16 arg3, f32 arg4);
// void func_800B8DD4(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5,
// UNK_TYPE4 param_6); void func_800B8E1C(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4,
// UNK_TYPE4 param_5);
//void func_800B8E58(UNK_PTR, u16 sfxId);
void Audio_PlayActorSound2(Actor* actor, u16 sfxId);
// void func_800B8FC0(void);
void func_800B8F98(Actor* actor, u16 sfxId);
void func_800B9010(Actor* actor, u16 sfxId);
// void func_800B9038(void);
// void func_800B9084(void);
void func_800B9098(Actor* actor);
s32 func_800B90AC(GlobalContext* globalCtx, Actor* actor, CollisionPoly* polygon, s32 index, UNK_TYPE arg4);
// void func_800B90F4(void);
void func_800B9120(ActorContext* actorCtx);
// void func_800b9170(GlobalContext* globalCtx, ActorContext* actorCtx, UNK_TYPE4 uParm3);
void func_800B9334(GlobalContext* globalCtx, ActorContext* actorCtx);
Actor* Actor_UpdateActor(s800B948C* params);
void Actor_UpdateAll(GlobalContext* globalCtx, ActorContext* actorCtx);
void Actor_DrawActor(GlobalContext* globalCtx, Actor* actor);
void func_800B9D1C(Actor* actor);
void Actor_DrawAllSetup(GlobalContext* globalCtx);
s32 Actor_RecordUndrawnActor(GlobalContext* globalCtx, Actor* actor);
// void func_800B9E84(void);
void func_800B9EF4(GlobalContext* globalCtx, s32 numActors, Actor** actors);
s32 func_800BA2D8(GlobalContext* globalCtx, Actor* actor);
s32 func_800BA2FC(GlobalContext* globalCtx, Actor* actor, Vec3f* param_3, f32 param_4);
void Actor_DrawAll(GlobalContext* globalCtx, ActorContext* actorCtx);
void func_800BA6FC(GlobalContext* globalCtx, ActorContext* actorCtx);
void func_800BA798(GlobalContext* globalCtx, ActorContext* actorCtx);
void func_800BA8B8(GlobalContext* globalCtx, ActorContext* actorCtx);
// void func_800BA9B4(void);
void Actor_InsertIntoTypeList(ActorContext* actorCtx, Actor* actor, u8 actorCategory);
Actor* Actor_RemoveFromTypeList(GlobalContext* globalCtx, ActorContext* actorCtx, Actor* actor);
void Actor_FreeOverlay(ActorOverlay* entry);
Actor* Actor_Spawn(ActorContext* actorCtx, GlobalContext* globalCtx, s16 actorId, f32 posX, f32 posY, f32 posZ,
                   s16 rotX, s16 rotY, s16 rotZ, s16 params);
ActorInit* Actor_LoadOverlay(ActorContext* actorCtx, s16 index);
Actor* Actor_SpawnAsChildAndCutscene(ActorContext* actorCtx, GlobalContext* globalCtx, s16 index, f32 x, f32 y, f32 z,
                                     s16 rotX, s16 rotY, s16 rotZ, s32 params, u32 cutscene, s32 param_12,
                                     Actor* parent);
Actor* Actor_SpawnAsChild(ActorContext* actorCtx, Actor* parent, GlobalContext* globalCtx, s16 actorId, f32 posX, f32 posY,
                          f32 posZ, s16 rotX, s16 rotY, s16 rotZ, s32 params);
void Actor_SpawnTransitionActors(GlobalContext* globalCtx, ActorContext* actorCtx);
void func_800BB2D0(ActorContext* actorCtx, u16* param_2, GlobalContext* globalCtx);
Actor* func_800BB498(ActorContext* actorCtx, Actor* actor, GlobalContext* globalCtx);
// void func_800BB59C(void);
// void func_800BB604(void);
// void func_800BB8EC(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5);
void func_800BBA88(GlobalContext* globalCtx, Actor* actor);
// void func_800BBAC0(void);
void func_800BBB74(s16* arg1, UNK_TYPE1 arg2, UNK_TYPE1 arg3, UNK_TYPE4 arg4);
// void func_800BBC20(void);
void func_800BBCEC(Actor* actor, GlobalContext* globalCtx, s16 arg2, Gfx** dList);
void func_800BBDAC(GlobalContext* globalCtx, Actor* actor, Vec3f* arg2, f32 arg3, UNK_TYPE4 arg4, f32 arg5, s16 arg6,
                   s16 arg7, u8 arg8);
void func_800BBFB0(GlobalContext* globalCtx, Vec3f* position, f32 param3, s32 param_4, s16 param_5, s16 param_6,
                   u8 param_7);
void func_800BC154(GlobalContext* globalCtx, ActorContext* actorCtx, Actor* actor, u8 actorCategory);
// void func_800BC188(void);
// void func_800BC1B4(void);
Actor* func_800BC270(GlobalContext* globalCtx, Actor* actor, f32 arg2, UNK_TYPE4 arg3);
Actor* func_800BC444(GlobalContext* globalCtx, Actor* actor, f32 arg2);
// void func_800BC4EC(void);
// void func_800BC5B8(void);
s32 func_800BC5EC(GlobalContext* globalCtx, Actor* actor);
void func_800BC620(Vec3f* arg0, Vec3f* arg1, UNK_TYPE arg2, GlobalContext* globalCtx);
// void func_800BC770(void);
// void func_800BC7D8(void);
// void func_800BC848(void);
// void func_800BC8B8(void);
// void func_800BCB50(void);
void func_800BCB70(Actor* actor, s16 arg1, s16 arg2, s16 arg3, s16 arg4);
void func_800BCBF4(Vec3f* uParm1, GlobalContext* globalCtx);
void func_800BCC68(Vec3f* param_1, GlobalContext* globalCtx);
void func_800BCCDC(Vec3s* points, s32 pathcount, Vec3f* pos1, Vec3f* pos2, s32 parm5);
s32 func_800BD2B4(GlobalContext* globalCtx, Actor* actor, s16* arg2, f32 arg3, u16 (*arg4)(GlobalContext*, Actor*), s16 (*arg5)(GlobalContext*, Actor*));
void func_800BD384(Actor* actor, struct_800BD888_arg1* arg1, s16 arg2, s16 arg3, s16 arg4, s16 arg5, s16 arg6, s16 arg7, u8 arg8);
s16 func_800BD6E4(Actor* actor, struct_800BD888_arg1* arg1, f32 arg2, s16 arg3, s16 flag);
void func_800BD888(Actor*, struct_800BD888_arg1*, s16, s16); // This function is very similar to OoT's func_80034A14
void* func_800BD9A0(GraphicsContext* gfxCtx);
void func_800BD9E0(GlobalContext* globalCtx, SkelAnime* skelAnime, OverrideLimbDraw2 overrideLimbDraw, PostLimbDraw2 postLimbDraw, Actor* actor, s16 alpha);
void func_800BDAA0(GlobalContext* globalCtx, SkelAnime* skelAnime, OverrideLimbDraw2 overrideLimbDraw, PostLimbDraw2 postLimbDraw, Actor* actor, s16 alpha);
s16 func_800BDB6C(Actor* actor, GlobalContext* globalCtx, s16 arg2, f32 arg3);
void func_800BDC5C(SkelAnime* skelAnime, ActorAnimationEntry animation[], s32 index);
void func_800BDCF4(GlobalContext* globalCtx, s16* arg1, s16* arg2, s32 size);
void Actor_Noop(Actor* actor, GlobalContext* globalCtx);
void Gfx_DrawDListOpa(GlobalContext* globalCtx, Gfx* dlist);
void func_800BE03C(GlobalContext* globalCtx, Gfx* dlist);
Actor* func_800BE0B8(GlobalContext* globalCtx, Actor* inActor, s16 arg2, u8 arg3, f32 arg4);
// void func_800BE184(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE2 param_5, UNK_TYPE2 param_6);
u8 func_800BE22C(Actor* actor);
void func_800BE258(Actor* actor, UNK_PTR arg1);
void func_800BE2B8(Actor* actor, ColliderJntSph* jntSphere);
void func_800BE33C(Vec3f* arg0, Vec3f* arg1, Vec3s* arg2, s32 arg3);
// void func_800BE3D0(void);
void func_800BE504(Actor* actor, ColliderCylinder* collider);
// void func_800BE568(void);
void func_800BE5CC(Actor* actor, ColliderJntSph* collider, s32 arg2);
// void func_800BE63C(void);
void func_800BE680(GlobalContext* globalCtx, Actor* actor, Vec3f limbPos[], s32 arg3, f32 arg4, f32 arg5, f32 arg6,
                   u8 mode);
void func_800BF7CC(GlobalContext* globalCtx, Actor* actor, Vec3f limbPos[], s32 arg3, s32 arg4, f32 arg5, f32 arg6);
void ActorOverlayTable_FaultPrint(void* arg0, void* arg1);
void* ActorOverlayTable_FaultAddrConv(void* arg0, void* arg1);
void ActorOverlayTable_Init(void);
void ActorOverlayTable_Cleanup(void);
void BgCheck_PolygonLinkedListNodeInit(SSNode* node, s16* polyIndex, u16 next);
void BgCheck_PolygonLinkedListResetHead(u16* head);
void BgCheck_ScenePolygonListsNodeInsert(SSNodeList* list, u16* head, s16* polyIndex);
void BgCheck_PolygonLinkedListNodeInsert(DynaSSNodeList* list, u16* head, s16* polyIndex);
void BgCheck_PolygonLinkedListInit(GlobalContext* globalCtx, DynaSSNodeList* list);
void BgCheck_PolygonLinkedListAlloc(GlobalContext* globalCtx, DynaSSNodeList* list, u32 numNodes);
void BgCheck_PolygonLinkedListReset(DynaSSNodeList* list);
u16 BgCheck_AllocPolygonLinkedListNode(DynaSSNodeList* list);
void BgCheck_CreateVec3fFromVertex(Vec3s* vertex, Vec3f* vector);
void BgCheck_CreateVertexFromVec3f(Vec3s* vertex, Vec3f* vector);
float func_800BFD84(CollisionPoly* polygon, f32 param_2, f32 param_3);
s32 func_800BFDEC(CollisionPoly* param_1, CollisionPoly* param_2, u32* param_3, u32* param_4);
s32 BgCheck_PolygonGetMinY(CollisionPoly* polygons, Vec3s* vertices);
void BgCheck_PolygonGetNormal(CollisionPoly* polygon, f32* normalX, f32* normalY, f32* normalZ);
void func_800C0094(struct CollisionPoly* param_1, f32 xOffset, f32 yOffset, f32 zOffset, MtxF* matrix);
f32 func_800C01B8(CollisionPoly* param_1, Vec3f* param_2);
void BgCheck_CreateColTriParamsFromPolygon(CollisionPoly* polygon, Vec3s* vertices, TriNorm* tri);
void func_800C02C0(CollisionPoly* poly, s32 index, CollisionContext* colCtx, TriNorm* tri);
// void func_800C0340(CollisionPoly* param_1, Vec3s* param_2, UNK_TYPE4 param_3, UNK_TYPE4 param_4, UNK_TYPE4 param_5,
// UNK_TYPE4 param_6); UNK_TYPE4 func_800C0474(CollisionPoly* param_1, Vec3s* param_2, UNK_TYPE4 param_3, UNK_TYPE4
// param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6); void func_800C0668(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1
// param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5); void func_800C06A8(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1
// param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5); void func_800C074C(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1
// param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5); void func_800C07F0(void);
void BgCheck_PolygonCollidesWithSphere(CollisionPoly* polygon, Vec3s* verticies, Vec3f* pos, f32 readius);
void BgCheck_ScenePolygonListsInsertSorted(CollisionContext* colCtx, u16* head, CollisionPoly* polygons,
                                           Vec3s* vertices, s16 index);
void BgCheck_ScenePolygonListsInsert(StaticLookup* subdivision, CollisionContext* colCtx, CollisionPoly* polygons,
                                     Vec3s* vertices, s16 index);
// void func_800C0E74(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5,
// UNK_TYPE4 param_6, UNK_TYPE4 param_7, UNK_TYPE4 param_8, UNK_TYPE4 param_9, UNK_TYPE4 param_10); void
// func_800C10FC(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5,
// UNK_TYPE4 param_6, UNK_TYPE4 param_7, UNK_TYPE4 param_8, UNK_TYPE4 param_9); void func_800C1238(UNK_TYPE1 param_1,
// UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE1 param_6, UNK_TYPE4 param_7,
// UNK_TYPE4 param_8, UNK_TYPE4 param_9, UNK_TYPE4 param_10, UNK_TYPE4 param_11); void func_800C12A4(UNK_TYPE1 param_1,
// UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6, UNK_TYPE4 param_7,
// UNK_TYPE4 param_8, UNK_TYPE4 param_9); void func_800C1B68(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3,
// UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6, UNK_TYPE4 param_7, UNK_TYPE4 param_8); void
// func_800C1D7C(void); void func_800C2008(void); void func_800C20F4(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1
// param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6, UNK_TYPE4 param_7); void func_800C2310(UNK_TYPE1
// param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6, UNK_TYPE2
// param_7, UNK_TYPE4 param_8); void func_800C2460(void); void func_800C2514(void); void func_800C25E0(void);
void BgCheck_GetPolyMinSubdivisions(CollisionContext* colCtx, Vec3f* min, s32* xSubdivision, s32* ySubdivision,
                                    s32* zSubdivision);
void BgCheck_GetPolyMaxSubdivisions(CollisionContext* colCtx, Vec3f* max, s32* xSubdivision, s32* ySubdivision,
                                    s32* zSubdivision);
void BgCheck_GetPolyMinMaxSubdivisions(CollisionContext* colCtx, Vec3s* vertices, CollisionPoly* polygons, s32* minX,
                                       s32* minY, s32* minZ, s32* maxX, s32* maxY, s32* maxZ, s16 index);
// UNK_TYPE4 func_800C2BE0(Vec3f* param_1, Vec3f* param_2, CollisionPoly* polygons, Vec3s* vertices, s16 index);
u32 BgCheck_SplitScenePolygonsIntoSubdivisions(CollisionContext* colCtx, GlobalContext* globalCtx,
                                               StaticLookup* subdivisions);
s32 BgCheck_GetIsDefaultSpecialScene(GlobalContext* globalCtx);
s32 BgCheck_GetSpecialSceneMaxMemory(s32 sceneId, u32* maxMemory);
void BgCheck_CalcSubdivisionSize(f32 min, s32 subdivisions, f32* max, f32* subdivisionSize,
                                 f32* inverseSubdivisionSize);
s32 BgCheck_GetSpecialSceneMaxObjects(GlobalContext* globalCtx, u32* maxNodes, u32* maxPolygons, u32* maxVertices);
void BgCheck_Init(CollisionContext* colCtx, GlobalContext* globalCtx, CollisionHeader* mesh);
void func_800C3C00(CollisionContext* colCtx, u32 param_2);
void func_800C3C14(CollisionContext* colCtx, u32 param_2);
CollisionHeader* BgCheck_GetActorMeshHeader(CollisionContext* colCtx, s32 index);
// void func_800C3C94(void);
f32 func_800C3D50(s32 arg0, CollisionContext* colCtx, s32 arg2, CollisionPoly** arg3, s32* arg4, Vec3f* pos,
                  Actor* actor, s32 arg7, f32 arg8, s32 arg9);
// void func_800C3F40(void);
// void func_800C3FA0(void);
f32 func_800C4000(GlobalContext* globalCtx, CollisionContext* colCtx, s32* arg2, Vec3f* arg3);
// void func_800C4058(void);
// void func_800C40B4(void);
f32 func_800C411C(CollisionContext* colCtx, CollisionPoly** arg1, s32* arg2, Actor* actor, Vec3f* pos);
f32 func_800C4188(f32, CollisionContext* colCtx, CollisionPoly**, UNK_PTR param_4, Actor* actor, Vec3f* pos); 
// void func_800C41E4(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4,
// UNK_TYPE4 param_5, UNK_TYPE4 param_6); void func_800C4240(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3,
// UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6); void func_800C42A8(UNK_TYPE1 param_1, UNK_TYPE1 param_2,
// UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5); void func_800C4314(void); void func_800C43CC(void); void
// func_800C4488(void); void func_800C44F0(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4,
// UNK_TYPE4 param_5); void func_800C455C(void);
s32 func_800C45C4(CollisionContext* colCtx, u32 arg1, Vec3f* arg2, Vec3f* arg3, Vec3f* arg4, f32 arg5, s32* arg6,
                  s32* arg7, DynaPolyActor* arg8, f32 arg9, u8 arg10);
// void func_800C4C74(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5,
// UNK_TYPE4 param_6, UNK_TYPE4 param_7); void func_800C4CD8(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3,
// UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6, UNK_TYPE4 param_7, UNK_TYPE4 param_8); void
// func_800C4D3C(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5,
// UNK_TYPE4 param_6, UNK_TYPE4 param_7, UNK_TYPE4 param_8, UNK_TYPE4 param_9); void func_800C4DA4(UNK_TYPE1 param_1,
// UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6, UNK_TYPE4 param_7,
// UNK_TYPE4 param_8, UNK_TYPE4 param_9); void func_800C4E10(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3,
// UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6, UNK_TYPE4 param_7, UNK_TYPE4 param_8); void
// func_800C4F38(void); void func_800C4F84(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4,
// UNK_TYPE4 param_5, UNK_TYPE4 param_6, UNK_TYPE4 param_7); void func_800C4FD4(UNK_TYPE1 param_1, UNK_TYPE1 param_2,
// UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6, UNK_TYPE4 param_7, UNK_TYPE4 param_8,
// UNK_TYPE4 param_9, UNK_TYPE4 param_10, UNK_TYPE4 param_11); void func_800C5464(UNK_TYPE1 param_1, UNK_TYPE1 param_2,
// UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5); void func_800C54AC(UNK_TYPE1 param_1, UNK_TYPE1 param_2,
// UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6, UNK_TYPE4 param_7, UNK_TYPE4 param_8,
// UNK_TYPE4 param_9, UNK_TYPE4 param_10); void func_800C5538(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3,
// UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6, UNK_TYPE4 param_7, UNK_TYPE4 param_8, UNK_TYPE4 param_9,
// UNK_TYPE4 param_10);
s32 func_800C55C4(CollisionContext* colCtx, Vec3f* arg1, Vec3f* arg2, Vec3f* arg3, CollisionPoly** arg4, u32 arg5,
                  u32 arg6, u32 arg7, u32 arg8, u32* arg9);
// void func_800C5650(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5,
// UNK_TYPE4 param_6, UNK_TYPE4 param_7, UNK_TYPE4 param_8, UNK_TYPE4 param_9, UNK_TYPE4 param_10, UNK_TYPE4 param_11);
// void func_800C56E0(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5,
// UNK_TYPE4 param_6, UNK_TYPE4 param_7, UNK_TYPE4 param_8, UNK_TYPE4 param_9, UNK_TYPE4 param_10, UNK_TYPE4 param_11,
// UNK_TYPE4 param_12);
s32 func_800C576C(CollisionContext* colCtx, Vec3f* arg1, Vec3f* arg2, Vec3f* arg3, CollisionPoly** arg4, u32 arg5,
                  u32 arg6, u32 arg7, u32 arg8, u32* arg9);
// void func_800C57F8(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5,
// UNK_TYPE4 param_6); void func_800C583C(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4,
// UNK_TYPE4 param_5, UNK_TYPE4 param_6, UNK_TYPE4 param_7, UNK_TYPE4 param_8, UNK_TYPE4 param_9); void
// func_800C58C8(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5,
// UNK_TYPE4 param_6, UNK_TYPE4 param_7, UNK_TYPE4 param_8, UNK_TYPE4 param_9, UNK_TYPE4 param_10); void
// func_800C5954(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5,
// UNK_TYPE4 param_6, UNK_TYPE4 param_7, UNK_TYPE2 param_8);
s32 func_800C5A20(CollisionContext* colCtx, Vec3f* arg1, f32 arg2);
// void func_800C5A64(void);
void BgCheck_ScenePolygonListsInit(SSNodeList* arg0);
void BgCheck_ScenePolygonListsAlloc(GlobalContext* globalCtx, SSNodeList* lists, s32 numNodes, u32 numPolygons);
s32 func_800C5B80(u16* arg0);
u16 BgCheck_ScenePolygonListsReserveNode(SSNodeList* lists);
void BgCheck_ActorMeshParamsInit(ScaleRotPos* params);
void BgCheck_SetActorMeshParams(ScaleRotPos* params, Vec3f* scale, Vec3s* rotation, Vec3f* position);
s32 BgCheck_AreActorMeshParamsEqual(ScaleRotPos* arg0, ScaleRotPos* arg1);
void BgCheck_ActorMeshPolyListsHeadsInit(DynaLookup* lists);
void BgCheck_ActorMeshPolyListsInit(DynaLookup* lists);
void BgCheck_ActorMeshVerticesIndexInit(s16* index);
void BgCheck_ActorMeshWaterboxesIndexInit(s16* index);
void BgCheck_ActorMeshInit(GlobalContext* globalCtx, BgActor* mesh);
void BgCheck_ActorMeshInitFromActor(BgActor* actorMesh, DynaPolyActor* actor, CollisionHeader* header);
s32 BgCheck_HasActorMeshChanged(BgActor* mesh);
void BgCheck_PolygonsInit(CollisionPoly** polygons);
void BgCheck_PolygonsAlloc(GlobalContext* globalCtx, CollisionPoly* polygons, u32 numPolygons);
void BgCheck_VerticesInit(Vec3s** vertices);
void BgCheck_VerticesListAlloc(GlobalContext* globalCtx, Vec3s** vertices, u32 numVertices);
void BgCheck_WaterboxListInit(DynaSSWaterboxList* waterboxList);
void BgCheck_WaterboxListAlloc(GlobalContext* globalCtx, DynaSSWaterboxList* waterboxList, u32 numWaterboxes);
void BgCheck_ActorMeshUpdateParams(GlobalContext* globalCtx, BgActor* mesh);
s32 BgCheck_IsActorMeshIndexValid(s32 index);
void BgCheck_DynaInit(GlobalContext* globalCtx, DynaCollisionContext* param_2);
void BgCheck_DynaAlloc(GlobalContext* globalCtx, DynaCollisionContext* dyna);
s32 BgCheck_AddActorMesh(GlobalContext* globalCtx, DynaCollisionContext* dyna, DynaPolyActor* actor,
                         CollisionHeader* header);
DynaPolyActor* BgCheck_GetActorOfMesh(CollisionContext* colCtx, s32 index);
void func_800C62BC(GlobalContext* globalCtx, DynaCollisionContext* dyna, s32 index);
void func_800C6314(GlobalContext* globalCtx, DynaCollisionContext* dyna, s32 index);
void func_800C636C(GlobalContext* globalCtx, DynaCollisionContext* dyna, s32 index);
void func_800C63C4(GlobalContext* globalCtx, DynaCollisionContext* dyna, s32 index);
void func_800C641C(GlobalContext* globalCtx, DynaCollisionContext* dyna, s32 index);
void func_800C6474(GlobalContext* globalCtx, DynaCollisionContext* dyna, s32 index);
void BgCheck_RemoveActorMesh(GlobalContext* globalCtx, DynaCollisionContext* dyna, s32 index);
// void func_800C6554(void);
void BgCheck_CalcWaterboxDimensions(Vec3f* minPos, Vec3f* maxXPos, Vec3f* maxZPos, Vec3s* minPosOut, s16* xLength,
                                    s16* zLength);
void BgCheck_AddActorMeshToLists(GlobalContext* globalCtx, DynaCollisionContext* dyna, s32 index, s32* currVertices,
                                 s32* currPolygons, s32* currWaterboxes);
void BgCheck_ResetFlagsIfLoadedActor(GlobalContext* globalCtx, DynaCollisionContext* dyna, Actor* actor);
void BgCheck_Update(GlobalContext* globalCtx, DynaCollisionContext* dyna);
void func_800C756C(s32 param_1, s32* param_2, s32* param_3, s32* param_4);
void BgCheck_UpdateAllActorMeshes(GlobalContext* globalCtx, DynaCollisionContext* dyna);
// void func_800C76EC(void);
// void func_800C7974(void);
// void func_800C7E40(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5,
// UNK_TYPE4 param_6, UNK_TYPE4 param_7, UNK_TYPE4 param_8, UNK_TYPE4 param_9, UNK_TYPE4 param_10, UNK_TYPE4 param_11,
// UNK_TYPE4 param_12); void func_800C8580(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4,
// UNK_TYPE4 param_5, UNK_TYPE4 param_6, UNK_TYPE4 param_7, UNK_TYPE4 param_8, UNK_TYPE4 param_9); void
// func_800C87D0(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5,
// UNK_TYPE4 param_6, UNK_TYPE4 param_7, UNK_TYPE4 param_8, UNK_TYPE4 param_9); void func_800C8A60(UNK_TYPE1 param_1,
// UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6, UNK_TYPE4 param_7,
// UNK_TYPE4 param_8); void func_800C8BD0(void); void func_800C8DC0(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1
// param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6, UNK_TYPE4 param_7, UNK_TYPE4 param_8, UNK_TYPE4
// param_9, UNK_TYPE4 param_10, UNK_TYPE4 param_11); void func_800C8EEC(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1
// param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6, UNK_TYPE4 param_7, UNK_TYPE4 param_8, UNK_TYPE4
// param_9, UNK_TYPE4 param_10, UNK_TYPE4 param_11); void func_800C90AC(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1
// param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6, UNK_TYPE4 param_7); void func_800C921C(UNK_TYPE1
// param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6, UNK_TYPE2
// param_7, UNK_TYPE4 param_8); void func_800C9380(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1
// param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6, UNK_TYPE4 param_7, UNK_TYPE2 param_8);
void BgCheck_RelocateMeshHeaderPointers(CollisionHeader* header);
void BgCheck_RelocateMeshHeader(CollisionHeader* meshSegPtr, CollisionHeader** param_2);
void BgCheck_RelocateAllMeshHeaders(CollisionContext* colCtx, GlobalContext* globalCtx);
// void func_800C9640(void);
u32 BgCheck_GetPolygonAttributes(CollisionContext* colCtx, CollisionPoly* polygon, s32 index, s32 attributeIndex);
u32 func_800C9704(CollisionContext* colCtx, CollisionPoly* polygon, s32 index);
// void func_800C9728(void);
// UNK_TYPE4 func_800C9770(CollisionContext* colCtx, CollisionPoly* polygon, s32 index);
// void func_800C97F8(void);
// UNK_TYPE4 func_800C9844(CollisionContext* colCtx, CollisionPoly* polygon, s32 index);
// void func_800C98CC(void);
// UNK_TYPE4 func_800C9924(CollisionContext* colCtx, CollisionPoly* polygon, s32 index);
u32 func_800C99AC(CollisionContext* colCtx, CollisionPoly* polygon, s32 index);
u32 func_800C99D4(CollisionContext* colCtx, CollisionPoly* polygon, s32 index);
u32 func_800C99FC(CollisionContext* colCtx, CollisionPoly* polygon, s32 index);
u32 func_800C9A24(CollisionContext* colCtx, CollisionPoly* polygon, s32 index);
u32 func_800C9A4C(CollisionContext* colCtx, CollisionPoly* polygon, s32 index);
u32 func_800C9A7C(CollisionContext* colCtx, CollisionPoly* polygon, s32 index);
u32 func_800C9AB0(CollisionContext* colCtx, CollisionPoly* polygon, s32 index);
u32 func_800C9AE4(CollisionContext* colCtx, CollisionPoly* polygon, s32 index);
u32 func_800C9B18(CollisionContext* colCtx, CollisionPoly* polygon, s32 index);
u32 func_800C9B40(CollisionContext* colCtx, CollisionPoly* polygon, s32 index);
u32 func_800C9B68(CollisionContext* colCtx, CollisionPoly* polygon, s32 index);
u32 func_800C9B90(CollisionContext* colCtx, CollisionPoly* polygon, s32 index);
u32 func_800C9BB8(CollisionContext* colCtx, CollisionPoly* polygon, s32 index);
u32 func_800C9BDC(CollisionContext* colCtx, CollisionPoly* polygon, s32 index);
// u32 func_800C9C24(CollisionContext* colCtx, CollisionPoly* polygon, s32 index, UNK_TYPE4 param_4);
u32 func_800C9C74(CollisionContext* colCtx, CollisionPoly* polygon, s32 index);
u32 func_800C9C9C(CollisionContext* colCtx, CollisionPoly* polygon, s32 index);
u32 func_800C9CC4(CollisionContext* colCtx, CollisionPoly* polygon, s32 index);
u32 func_800C9CEC(CollisionContext* colCtx, CollisionPoly* polygon, s32 index);
// void func_800C9D14(void);
// void func_800C9D50(void);
u32 func_800C9D8C(CollisionContext* param_1, CollisionPoly* param_2, s32 param_3);
// void func_800C9DDC(void);
u32 func_800C9E18(CollisionContext* colCtx, CollisionPoly* polygon, s32 index);
u32 func_800C9E40(CollisionContext* colCtx, CollisionPoly* polygon, s32 index);
u32 func_800C9E88(CollisionContext* colCtx, CollisionPoly* polygon, s32 index);
// void func_800C9EBC(GlobalContext* globalCtx, CollisionContext* colCtx, UNK_TYPE1 param_3, UNK_TYPE1 param_4,
// UNK_TYPE4 param_5, UNK_TYPE4 param_6, UNK_TYPE4 param_7);
s32 func_800CA1AC(GlobalContext* globalCtx, CollisionContext* colCtx, f32 x, f32 z, f32* ySurface,
                  WaterBox** outWaterBox);
void func_800CA1E8(GlobalContext* globalCtx, CollisionContext* colCtx, f32 arg2, f32 arg3, f32* arg4, UNK_PTR arg5);
// void func_800CA22C(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5,
// UNK_TYPE4 param_6); void func_800CA568(void); void func_800CA634(void); void func_800CA648(void); void
// func_800CA6B8(void); void func_800CA6D8(void); void func_800CA6F0(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1
// param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6, UNK_TYPE4 param_7); void func_800CA9D0(UNK_TYPE1
// param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6); void
// func_800CAA14(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5);
void BgCheck2_UpdateActorPosition(CollisionContext* colCtx, s32 index, Actor* actor);
void BgCheck2_UpdateActorYRotation(CollisionContext* colCtx, s32 index, Actor* actor);
void BgCheck2_AttachToMesh(CollisionContext* colCtx, Actor* actor, s32 index);
u32 BgCheck2_UpdateActorAttachedToMesh(CollisionContext* colCtx, s32 index, Actor* actor);
void BcCheck3_BgActorInit(DynaPolyActor* actor, UNK_TYPE4 param_2);
void BgCheck3_LoadMesh(GlobalContext* globalCtx, DynaPolyActor* actor, CollisionHeader* meshHeader);
void BgCheck3_ResetFlags(DynaPolyActor* actor);
void func_800CAE88(DynaPolyActor* actor);
void func_800CAE9C(DynaPolyActor* actor);
void func_800CAEB0(CollisionContext* colCtx, s32 index);
void func_800CAEE0(DynaPolyActor* actor);
void func_800CAEF4(CollisionContext* colCtx, s32 index);
void func_800CAF24(DynaPolyActor* actor);
void func_800CAF38(DynaPolyActor* actor);
s32 func_800CAF4C(DynaPolyActor* actor);
s32 func_800CAF70(DynaPolyActor* actor);
s32 func_800CAF94(DynaPolyActor* actor);
s32 func_800CAFB8(DynaPolyActor* actor);
s32 func_800CAFDC(DynaPolyActor* actor);
// void func_800CB000(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE2 param_5);
f32 Camera_fabsf(f32 f);
f32 Camera_LengthVec3f(Vec3f* v);
// void func_800CB270(void);
f32 Camera_Lerpf(f32 b, f32 a, f32 t, f32 minDist);
s16 Camera_Lerps(s16 b, s16 a, f32 t, s16 minDist);
// void func_800CB42C(void);
void Camera_LerpVec3f(Vec3f* b, Vec3f* a, f32 tXZ, f32 tY, f32 minDist);
void func_800CB544(Camera* camera);
// void func_800CB584(void);
// void func_800CB5DC(void);
// void func_800CB60C(void);
// void func_800CB674(void);
// void func_800CB6C8(void);
f32 func_800CB700(Camera* camera);
// void func_800CB780(void);
// void func_800CB7CC(void);
// void func_800CB7F8(void);
// void func_800CB828(void);
// void func_800CB854(void);
// void func_800CB880(void);
// void func_800CB8C8(void);
// void func_800CB8F4(void);
// void func_800CB924(void);
// void func_800CB950(void);
// void func_800CBA08(void);
// void func_800CBA34(void);
// void func_800CBA7C(void);
// void func_800CBAAC(void);
// void func_800CBAD4(void);
// void func_800CBB58(void);
// void func_800CBB88(void);
// void func_800CBC00(void);
// void func_800CBC30(void);
// void func_800CBC84(void);
// void func_800CBFA4(void);
// void func_800CC000(void);
// void func_800CC128(void);
// void func_800CC1C4(void);
// void func_800CC260(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5,
// UNK_TYPE2 param_6); void func_800CC488(void); void func_800CC56C(void); void func_800CC5C8(void); void
// func_800CC740(void); void func_800CC7A8(void); void func_800CC804(void); void func_800CC874(void); void
// func_800CC938(void); void func_800CC958(void); void func_800CC9C0(void); void func_800CCCEC(void); void
// func_800CD04C(void); void func_800CD288(void); void func_800CD2E0(void); void func_800CD2F0(void); void
// func_800CD3E4(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5); void
// func_800CD44C(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE2 param_5); void
// func_800CD634(void); void func_800CD6CC(void); void func_800CD6F8(void); void func_800CD834(UNK_TYPE1 param_1,
// UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5); void func_800CDA14(void); void
// func_800CDB6C(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5,
// UNK_TYPE2 param_6); void func_800CDE6C(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4,
// UNK_TYPE4 param_5, UNK_TYPE4 param_6, UNK_TYPE4 param_7, UNK_TYPE2 param_8); void func_800CE2B8(UNK_TYPE1 param_1,
// UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6, UNK_TYPE4 param_7,
// UNK_TYPE4 param_8, UNK_TYPE2 param_9); void func_800CE5E0(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3,
// UNK_TYPE1 param_4, UNK_TYPE2 param_5); void func_800CE79C(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3,
// UNK_TYPE1 param_4, UNK_TYPE2 param_5); void func_800CE930(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3,
// UNK_TYPE1 param_4, UNK_TYPE2 param_5); void func_800CEAD8(void); void func_800CEC38(UNK_TYPE1 param_1, UNK_TYPE1
// param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5); void func_800CED90(UNK_TYPE1 param_1, UNK_TYPE1
// param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6, UNK_TYPE4 param_7);
s32 Camera_ModeNop(Camera* camera);
s32 Camera_ModeNORM1(Camera* camera);
s32 Camera_ModeNORM2(Camera* camera);
s32 Camera_ModeNORM3(Camera* camera);
s32 Camera_ModeNORM4(Camera* camera);
s32 Camera_ModeNORM0(Camera* camera);
s32 Camera_ModePARA1(Camera* camera);
s32 Camera_ModePARA2(Camera* camera);
s32 Camera_ModePARA3(Camera* camera);
s32 Camera_ModePARA4(Camera* camera);
s32 Camera_ModePARA0(Camera* camera);
s32 Camera_ModeJUMP1(Camera* camera);
s32 Camera_ModeJUMP2(Camera* camera);
s32 Camera_ModeJUMP3(Camera* camera);
s32 Camera_ModeJUMP4(Camera* camera);
s32 Camera_ModeJUMP0(Camera* camera);
s32 Camera_ModeBATT1(Camera* camera);
s32 Camera_ModeBATT2(Camera* camera);
s32 Camera_ModeBATT3(Camera* camera);
s32 Camera_ModeBATT4(Camera* camera);
s32 Camera_ModeBATT0(Camera* camera);
s32 Camera_ModeKEEP1(Camera* camera);
s32 Camera_ModeKEEP2(Camera* camera);
s32 Camera_ModeKEEP3(Camera* camera);
s32 Camera_ModeKEEP4(Camera* camera);
// void func_800D7C44(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE1 param_5,
// UNK_TYPE1 param_6, UNK_TYPE1 param_7, UNK_TYPE1 param_8, UNK_TYPE1 param_9, UNK_TYPE1 param_10, UNK_TYPE2 param_11,
// UNK_TYPE2 param_12);
s32 Camera_ModeKEEP0(Camera* camera);
s32 Camera_ModeFIXD1(Camera* camera);
s32 Camera_ModeFIXD2(Camera* camera);
s32 Camera_ModeFIXD3(Camera* camera);
s32 Camera_ModeFIXD4(Camera* camera);
s32 Camera_ModeFIXD0(Camera* camera);
s32 Camera_ModeSUBJ1(Camera* camera);
s32 Camera_ModeSUBJ2(Camera* camera);
s32 Camera_ModeSUBJ3(Camera* camera);
s32 Camera_ModeSUBJ4(Camera* camera);
s32 Camera_ModeSUBJ0(Camera* camera);
s32 Camera_ModeDATA0(Camera* camera);
s32 Camera_ModeDATA1(Camera* camera);
s32 Camera_ModeDATA2(Camera* camera);
s32 Camera_ModeDATA3(Camera* camera);
s32 Camera_ModeDATA4(Camera* camera);
s32 Camera_ModeUNIQ1(Camera* camera);
s32 Camera_ModeUNIQ2(Camera* camera);
s32 Camera_ModeUNIQ3(Camera* camera);
s32 Camera_ModeUNIQ4(Camera* camera);
s32 Camera_ModeUNIQ5(Camera* camera);
s32 Camera_ModeUNIQ0(Camera* camera);
s32 Camera_ModeUNIQ6(Camera* camera);
s32 Camera_ModeUNIQ7(Camera* camera);
s32 Camera_ModeUNIQ8(Camera* camera);
s32 Camera_ModeUNIQ9(Camera* camera);
s32 Camera_ModeDEMO1(Camera* camera);
s32 Camera_ModeDEMO2(Camera* camera);
s32 Camera_ModeDEMO3(Camera* camera);
s32 Camera_ModeDEMO4(Camera* camera);
s32 Camera_ModeDEMO5(Camera* camera);
s32 Camera_ModeDEMO6(Camera* camera);
s32 Camera_ModeDEMO7(Camera* camera);
s32 Camera_ModeDEMO8(Camera* camera);
s32 Camera_ModeDEMO9(Camera* camera);
s32 Camera_ModeDEMO0(Camera* camera);
s32 Camera_ModeSPEC0(Camera* camera);
s32 Camera_ModeSPEC1(Camera* camera);
s32 Camera_ModeSPEC2(Camera* camera);
s32 Camera_ModeSPEC3(Camera* camera);
s32 Camera_ModeSPEC4(Camera* camera);
s32 Camera_ModeSPEC5(Camera* camera);
s32 Camera_ModeSPEC6(Camera* camera);
s32 Camera_ModeSPEC7(Camera* camera);
s32 Camera_ModeSPEC8(Camera* camera);
s32 Camera_ModeSPEC9(Camera* camera);
Camera* Camera_Alloc(View* view, CollisionContext* bg, GlobalContext* globalCtx);
void Camera_Free(Camera* camera);
void Camera_Init(Camera* camera, View* view, CollisionContext* bg, GlobalContext* globalCtx);
// void func_800DDFE0(void);
void func_800DE0EC(Camera* camera, Actor* actor);
// s32 func_800DE308(Camera* camera, UNK_TYPE2 uParm2);
// void func_800DE324(void);
// void func_800DE62C(void);
// void func_800DE840(void);
// void func_800DE890(void);
// UNK_TYPE4 func_800DE954(Camera* camera);
Vec3s* Camera_Update(Vec3s* param_1, Camera* camera);
// void func_800DF498(void);
u32 Camera_SetMode(Camera* camera, s16 mode, s8 param_3);
// void func_800DF840(void);
// void func_800DF86C(void);
// void func_800DF8EC(void);
s32 func_800DFAC8(Camera* camera, s16 param_2);
u32 func_800DFB14(Camera* camera, u32 param_2);
// void func_800DFC1C(void);
// void func_800DFC40(void);
s32 func_800DFC68(Camera* camera);
// void func_800DFC90(void);
s16 func_800DFCB4(Camera* camera);
s16 func_800DFCDC(Camera* camera);
// void func_800DFD04(void);
// void func_800DFD78(void);
// UNK_TYPE4 func_800DFEF0(s32 param_1, u16 param_2);
// UNK_TYPE4 func_800DFF18(Camera* iParm1, UNK_TYPE2 uParm2);
// UNK_TYPE4 func_800DFF34(s32 param_1);
// UNK_TYPE4 func_800DFF44(void);
s16 Camera_SetFlags(Camera* iParm1, s16 flags);
s16 Camera_ClearFlags(Camera* camera, s16 flags);
// void func_800DFFAC(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE2 param_5,
// UNK_TYPE2 param_6, UNK_TYPE2 param_7); UNK_TYPE4 func_800E007C(Camera* param_1, Camera* param_2); UNK_TYPE4
// func_800E01AC(void); void func_800E01B8(void); void func_800E01DC(s32 param_1, u32 param_2, UNK_TYPE4 param_3,
// UNK_TYPE4 param_4, UNK_TYPE2 param_5, UNK_TYPE2 param_6); UNK_TYPE4 func_800E0228(void); void func_800E0238(void);
void func_800E02AC(Camera* camera, Actor* actor);
// void func_800E0308(void);
// void func_800E031C(void);
void func_800E0348(Camera* camera);
DamageTable* DamageTable_Get(s32 index);          // func_800E03A0
void DamageTable_Clear(DamageTable* damageTable); // func_800E03CC
f32 CollisionCheck_GetDamageAndEffectOnBumper(Collider* at, ColliderInfo* atInfo, Collider* ac, ColliderInfo* acInfo,
                                              u32* effect);
f32 CollisionCheck_ApplyBumperDefense(f32 damage, ColliderInfo* ac);
s32 CollisionCheck_GetToucherDamage(Collider* at, ColliderInfo* atInfo, Collider* ac, ColliderInfo* acInfo);
s32 Collider_InitBase(GlobalContext* globalCtx, Collider* collider);
s32 Collider_DestroyBase(GlobalContext* globalCtx, Collider* collider);
s32 Collider_SetBaseToActor(GlobalContext* globalCtx, Collider* collider, ColliderInitToActor* src);
s32 Collider_SetBaseType1(GlobalContext* globalCtx, Collider* collider, Actor* actor, ColliderInitType1* src);
s32 Collider_SetBase(GlobalContext* globalCtx, Collider* collider, Actor* actor, ColliderInit* src);
void Collider_ResetATBase(GlobalContext* globalCtx, Collider* collider);
void Collider_ResetACBase(GlobalContext* globalCtx, Collider* collider);
void Collider_ResetOCBase(GlobalContext* globalCtx, Collider* collider);
s32 Collider_InitTouch(GlobalContext* globalCtx, ColliderTouch* touch);
s32 Collider_DestroyTouch(GlobalContext* globalCtx, ColliderTouch* touch);
s32 Collider_SetTouch(GlobalContext* globalCtx, ColliderTouch* touch, ColliderTouchInit* src);
void Collider_ResetATInfoUnk(GlobalContext* globalCtx, ColliderInfo* info);
s32 Collider_InitBump(GlobalContext* globalCtx, ColliderBump* bump);
s32 Collider_DestroyBump(GlobalContext* globalCtx, ColliderBump* bump);
s32 Collider_SetBump(GlobalContext* globalCtx, ColliderBump* bump, ColliderBumpInit* src);
s32 Collider_InitInfo(GlobalContext* globalCtx, ColliderInfo* info);
s32 Collider_DestroyInfo(GlobalContext* globalCtx, ColliderInfo* info);
s32 Collider_SetInfo(GlobalContext* globalCtx, ColliderInfo* info, ColliderInfoInit* src);
void Collider_ResetATInfo(GlobalContext* globalCtx, ColliderInfo* info);
void Collider_ResetACInfo(GlobalContext* globalCtx, ColliderInfo* info);
void Collider_ResetOCInfo(GlobalContext* globalCtx, ColliderInfo* info);
s32 Collider_InitJntSphElementDim(GlobalContext* globalCtx, ColliderJntSphElementDim* dim);
s32 Collider_DestroyJntSphElementDim(GlobalContext* globalCtx, ColliderJntSphElementDim* dim);
s32 Collider_SetJntSphElementDim(GlobalContext* globalCtx, ColliderJntSphElementDim* dest,
                                 ColliderJntSphElementDimInit* src);
s32 Collider_InitJntSphElement(GlobalContext* globalCtx, ColliderJntSphElement* element);
s32 Collider_DestroyJntSphElement(GlobalContext* globalCtx, ColliderJntSphElement* element);
s32 Collider_SetJntSphElement(GlobalContext* globalCtx, ColliderJntSphElement* dest, ColliderJntSphElementInit* src);
s32 Collider_ResetJntSphElementAT(GlobalContext* globalCtx, ColliderJntSphElement* collider);
s32 Collider_ResetJntSphElementAC(GlobalContext* globalCtx, ColliderJntSphElement* collider);
s32 Collider_ResetJntSphElementOC(GlobalContext* globalCtx, ColliderJntSphElement* collider);
s32 Collider_InitJntSph(GlobalContext* globalCtx, ColliderJntSph* collider);
s32 Collider_FreeJntSph(GlobalContext* globalCtx, ColliderJntSph* collider);
s32 Collider_DestroyJntSph(GlobalContext* globalCtx, ColliderJntSph* collider);
s32 Collider_SetJntSphToActor(GlobalContext* globalCtx, ColliderJntSph* collider, ColliderJntSphInitToActor* src);
s32 Collider_SetJntSphAllocType1(GlobalContext* globalCtx, ColliderJntSph* sphereGroup, Actor* actor,
                                 ColliderJntSphInitType1* src);
s32 Collider_SetJntSph(GlobalContext* globalCtx, ColliderJntSph* sphereGroup, Actor* actor, ColliderJntSphInit* src,
                       ColliderJntSphElement* elements);
s32 Collider_InitAndSetJntSph(GlobalContext* globalCtx, ColliderJntSph* sphereGroup, Actor* actor,
                              ColliderJntSphInit* src, ColliderJntSphElement* elements);
s32 Collider_ResetJntSphAT(GlobalContext* globalCtx, Collider* collider);
s32 Collider_ResetJntSphAC(GlobalContext* globalCtx, Collider* collider);
s32 Collider_ResetJntSphOC(GlobalContext* globalCtx, Collider* collider);
s32 Collider_InitCylinderDim(GlobalContext* globalCtx, Cylinder16* dim);
s32 Collider_DestroyCylinderDim(GlobalContext* globalCtx, Cylinder16* dim);
s32 Collider_SetCylinderDim(GlobalContext* globalCtx, Cylinder16* dim, Cylinder16* src);
s32 Collider_InitCylinder(GlobalContext* globalCtx, ColliderCylinder* collider);
s32 Collider_DestroyCylinder(GlobalContext* globalCtx, ColliderCylinder* collider);
s32 Collider_SetCylinderToActor(GlobalContext* globalCtx, ColliderCylinder* collider, ColliderCylinderInitToActor* src);
s32 Collider_SetCylinderType1(GlobalContext* globalCtx, ColliderCylinder* collider, Actor* actor,
                              ColliderCylinderInitType1* src);
s32 Collider_SetCylinder(GlobalContext* globalCtx, ColliderCylinder* collider, Actor* actor, ColliderCylinderInit* src);
s32 Collider_InitAndSetCylinder(GlobalContext* globalCtx, ColliderCylinder* collider, Actor* actor,
                                ColliderCylinderInit* src);
s32 Collider_ResetCylinderAT(GlobalContext* globalCtx, Collider* collider);
s32 Collider_ResetCylinderAC(GlobalContext* globalCtx, Collider* collider);
s32 Collider_ResetCylinderOC(GlobalContext* globalCtx, Collider* collider);
s32 Collider_InitTrisElementDim(GlobalContext* globalCtx, TriNorm* dim);
s32 Collider_DestroyTrisElementDim(GlobalContext* globalCtx, TriNorm* dim);
s32 Collider_SetTrisElementDim(GlobalContext* globalCtx, TriNorm* dim, ColliderTrisElementDimInit* src);
s32 Collider_InitTrisElement(GlobalContext* globalCtx, ColliderTrisElement* element);
s32 Collider_DestroyTrisElement(GlobalContext* globalCtx, ColliderTrisElement* element);
s32 Collider_SetTrisElement(GlobalContext* globalCtx, ColliderTrisElement* element, ColliderTrisElementInit* src);
s32 Collider_ResetTrisElementAT(GlobalContext* globalCtx, ColliderTrisElement* element);
s32 Collider_ResetTrisElementAC(GlobalContext* globalCtx, ColliderTrisElement* element);
s32 Collider_ResetTrisElementOC(GlobalContext* globalCtx, ColliderTrisElement* element);
s32 Collider_InitTris(GlobalContext* globalCtx, ColliderTris* tris);
s32 Collider_FreeTris(GlobalContext* globalCtx, ColliderTris* tris);
s32 Collider_DestroyTris(GlobalContext* globalCtx, ColliderTris* tris);
s32 Collider_SetTrisAllocType1(GlobalContext* globalCtx, ColliderTris* tris, Actor* actor, ColliderTrisInitType1* src);
s32 Collider_SetTris(GlobalContext* globalCtx, ColliderTris* triGroup, Actor* actor, ColliderTrisInit* src,
                     ColliderTrisElement* tris);
s32 Collider_InitAndSetTris(GlobalContext* globalCtx, ColliderTris* tris, Actor* actor, ColliderTrisInit* src,
                            ColliderTrisElement* elements);
s32 Collider_ResetTrisAT(GlobalContext* globalCtx, Collider* collider);
s32 Collider_ResetTrisAC(GlobalContext* globalCtx, Collider* collider);
s32 Collider_ResetTrisOC(GlobalContext* globalCtx, Collider* collider);
s32 Collider_InitQuadDim(GlobalContext* globalCtx, ColliderQuadDim* dim);
s32 Collider_DestroyQuadDim(GlobalContext* globalCtx, ColliderQuadDim* dim);
s32 Collider_ResetQuadACDist(GlobalContext* globalCtx, ColliderQuadDim* dim);
void Collider_SetQuadMidpoints(ColliderQuadDim* dim);
s32 Collider_SetQuadDim(GlobalContext* globalCtx, ColliderQuadDim* dim, ColliderQuadDimInit* init);
s32 Collider_InitQuad(GlobalContext* globalCtx, ColliderQuad* collider);
s32 Collider_DestroyQuad(GlobalContext* globalCtx, ColliderQuad* collider);
s32 Collider_SetQuadType1(GlobalContext* globalCtx, ColliderQuad* collider, Actor* actor, ColliderQuadInitType1* src);
s32 Collider_SetQuad(GlobalContext* globalCtx, ColliderQuad* collider, Actor* actor, ColliderQuadInit* src);
s32 Collider_InitAndSetQuad(GlobalContext* globalCtx, ColliderQuad* collider, Actor* actor, ColliderQuadInit* src);
s32 Collider_ResetQuadAT(GlobalContext* globalCtx, Collider* collider);
s32 Collider_ResetQuadAC(GlobalContext* globalCtx, Collider* collider);
s32 Collider_ResetQuadOC(GlobalContext* globalCtx, Collider* collider);
s32 Collider_QuadSetNearestAC(GlobalContext* globalCtx, ColliderQuad* quad, Vec3f* hitPos);
s32 Collider_InitSphere(GlobalContext* globalCtx, ColliderSphere* collider);
s32 Collider_DestroySphere(GlobalContext* globalCtx, ColliderSphere* collider);
s32 Collider_SetSphere(GlobalContext* globalCtx, ColliderSphere* collider, Actor* actor, ColliderSphereInit* src);
s32 Collider_InitAndSetSphere(GlobalContext* globalCtx, ColliderSphere* collider, Actor* actor,
                              ColliderSphereInit* src);
s32 Collider_ResetSphereAT(GlobalContext* globalCtx, Collider* collider);
s32 Collider_ResetSphereAC(GlobalContext* globalCtx, Collider* collider);
s32 Collider_ResetSphereOC(GlobalContext* globalCtx, Collider* collider);
s32 Collider_InitLine(GlobalContext* globalCtx, OcLine* line);
s32 Collider_DestroyLine(GlobalContext* globalCtx, OcLine* line);
s32 Collider_SetLinePoints(GlobalContext* globalCtx, OcLine* line, Vec3f* a, Vec3f* b);
s32 Collider_SetLine(GlobalContext* globalCtx, OcLine* line, OcLine* src);
s32 Collider_ResetLineOC(GlobalContext* globalCtx, OcLine* line);
void CollisionCheck_InitContext(GlobalContext* globalCtx, CollisionCheckContext* colCtxt);
void CollisionCheck_DestroyContext(GlobalContext* globalCtx, CollisionCheckContext* colCtxt);
void CollisionCheck_ClearContext(GlobalContext* globalCtx, CollisionCheckContext* colCtxt);
void CollisionCheck_EnableSAC(GlobalContext* globalCtx, CollisionCheckContext* colCtxt);
void CollisionCheck_DisableSAC(GlobalContext* globalCtx, CollisionCheckContext* colCtxt);
s32 CollisionCheck_SetAT(GlobalContext* globalCtx, CollisionCheckContext* colCtxt, Collider* collider);
s32 CollisionCheck_SetAT_SAC(GlobalContext* globalCtx, CollisionCheckContext* colCtxt, Collider* collider, s32 index);
s32 CollisionCheck_SetAC(GlobalContext* globalCtx, CollisionCheckContext* colCtxt, Collider* collider);
s32 CollisionCheck_SetAC_SAC(GlobalContext* globalCtx, CollisionCheckContext* colCtxt, Collider* collider, s32 index);
s32 CollisionCheck_SetOC(GlobalContext* globalCtx, CollisionCheckContext* colCtxt, Collider* collider);
s32 CollisionCheck_SetOC_SAC(GlobalContext* globalCtx, CollisionCheckContext* colCtxt, Collider* collider, s32 index);
s32 CollisionCheck_SetOCLine(GlobalContext* globalCtx, CollisionCheckContext* colCtxt, OcLine* line);
s32 CollisionCheck_SkipTouch(ColliderInfo* info);
s32 CollisionCheck_SkipBump(ColliderInfo* info);
s32 CollisionCheck_NoSharedFlags(ColliderInfo* toucher, ColliderInfo* bumper);
void CollisionCheck_NoBlood(GlobalContext* globalCtx, Collider* collider, Vec3f* v);
void CollisionCheck_BlueBlood(GlobalContext* globalCtx, Collider* collider, Vec3f* v);
void CollisionCheck_GreenBlood(GlobalContext* globalCtx, Collider* collider, Vec3f* v);
void CollisionCheck_WaterBurst(GlobalContext* globalCtx, Collider* collider, Vec3f* v);
void CollisionCheck_RedBlood(GlobalContext* globalCtx, Collider* collider, Vec3f* v);
void CollisionCheck_RedBloodUnused(GlobalContext* globalCtx, Collider* collider, Vec3f* v);
void CollisionCheck_HitSolid(GlobalContext* globalCtx, ColliderInfo* info, Collider* collider, Vec3f* hitPos);
s32 CollisionCheck_SwordHitAudio(Collider* at, ColliderInfo* acInfo);
void CollisionCheck_HitEffects(GlobalContext* globalCtx, Collider* at, ColliderInfo* atInfo, Collider* ac,
                               ColliderInfo* acInfo, Vec3f* hitPos);
void CollisionCheck_SetBounce(Collider* at, Collider* ac);
s32 CollisionCheck_SetATvsAC(GlobalContext* globalCtx, Collider* at, ColliderInfo* atInfo, Vec3f* atPos, Collider* ac,
                             ColliderInfo* acInfo, Vec3f* acPos, Vec3f* hitPos);
void CollisionCheck_TrisAvgPoint(ColliderTrisElement* tri, Vec3f* avg);
void CollisionCheck_QuadAvgPoint(ColliderQuad* quad, Vec3f* avg);
void CollisionCheck_AC_JntSphVsJntSph(GlobalContext* globalCtx, CollisionCheckContext* colCtxt, Collider* colAT,
                                      Collider* colAC);
void CollisionCheck_AC_JntSphVsCyl(GlobalContext* globalCtx, CollisionCheckContext* colCtxt, Collider* colAT,
                                   Collider* colAC);
void CollisionCheck_AC_JntSphVsTris(GlobalContext* globalCtx, CollisionCheckContext* colCtxt, Collider* colAT,
                                    Collider* colAC);
void CollisionCheck_AC_JntSphVsQuad(GlobalContext* globalCtx, CollisionCheckContext* colCtxt, Collider* colAT,
                                    Collider* colAC);
void CollisionCheck_AC_JntSphVsSphere(GlobalContext* globalCtx, CollisionCheckContext* colCtxt, Collider* colAT,
                                      Collider* colAC);
void CollisionCheck_AC_CylVsJntSph(GlobalContext* globalCtx, CollisionCheckContext* colCtxt, Collider* colAT,
                                   Collider* colAC);
void CollisionCheck_AC_CylVsCyl(GlobalContext* globalCtx, CollisionCheckContext* colCtxt, Collider* colAT,
                                Collider* colAC);
void CollisionCheck_AC_CylVsTris(GlobalContext* globalCtx, CollisionCheckContext* colCtxt, Collider* colAT,
                                 Collider* colAC);
void CollisionCheck_AC_CylVsQuad(GlobalContext* globalCtx, CollisionCheckContext* colCtxt, Collider* colAT,
                                 Collider* colAC);
void CollisionCheck_AC_CylVsSphere(GlobalContext* globalCtx, CollisionCheckContext* colCtxt, Collider* colAT,
                                   Collider* colAC);
void CollisionCheck_AC_TrisVsJntSph(GlobalContext* globalCtx, CollisionCheckContext* colCtxt, Collider* colAT,
                                    Collider* colAC);
void CollisionCheck_AC_TrisVsCyl(GlobalContext* globalCtx, CollisionCheckContext* colCtxt, Collider* colAT,
                                 Collider* colAC);
void CollisionCheck_AC_TrisVsTris(GlobalContext* globalCtx, CollisionCheckContext* colCtxt, Collider* colAT,
                                  Collider* colAC);
void CollisionCheck_AC_TrisVsQuad(GlobalContext* globalCtx, CollisionCheckContext* colCtxt, Collider* colAT,
                                  Collider* colAC);
void CollisionCheck_AC_TrisVsSphere(GlobalContext* globalCtx, CollisionCheckContext* colCtxt, Collider* colAT,
                                    Collider* colAC);
void CollisionCheck_AC_QuadVsJntSph(GlobalContext* globalCtx, CollisionCheckContext* colCtxt, Collider* colAT,
                                    Collider* colAC);
void CollisionCheck_AC_QuadVsCyl(GlobalContext* globalCtx, CollisionCheckContext* colCtxt, Collider* colAT,
                                 Collider* colAC);
void CollisionCheck_AC_QuadVsTris(GlobalContext* globalCtx, CollisionCheckContext* colCtxt, Collider* colAT,
                                  Collider* colAC);
void CollisionCheck_AC_QuadVsQuad(GlobalContext* globalCtx, CollisionCheckContext* colCtxt, Collider* colAT,
                                  Collider* colAC);
void CollisionCheck_AC_QuadVsSphere(GlobalContext* globalCtx, CollisionCheckContext* colCtxt, Collider* colAT,
                                    Collider* colAC);
void CollisionCheck_AC_SphereVsJntSph(GlobalContext* globalCtx, CollisionCheckContext* colCtxt, Collider* colAT,
                                      Collider* colAC);
void CollisionCheck_AC_SphereVsCylinder(GlobalContext* globalCtx, CollisionCheckContext* colCtxt, Collider* colAT,
                                        Collider* colAC);
void CollisionCheck_AC_SphereVsTris(GlobalContext* globalCtx, CollisionCheckContext* colCtxt, Collider* colAT,
                                    Collider* colAC);
void CollisionCheck_AC_SphereVsQuad(GlobalContext* globalCtx, CollisionCheckContext* colCtxt, Collider* colAT,
                                    Collider* colAC);
void CollisionCheck_AC_SphereVsSphere(GlobalContext* globalCtx, CollisionCheckContext* colCtxt, Collider* colAT,
                                      Collider* colAC);
void CollisionCheck_SetJntSphHitFX(GlobalContext* globalCtx, CollisionCheckContext* colCtxt, Collider* collider);
void CollisionCheck_SetCylHitFX(GlobalContext* globalCtx, CollisionCheckContext* colCtxt, Collider* collider);
void CollisionCheck_SetTrisHitFX(GlobalContext* globalCtx, CollisionCheckContext* colCtxt, Collider* collider);
void CollisionCheck_SetQuadHitFX(GlobalContext* globalCtx, CollisionCheckContext* colCtxt, Collider* collider);
void CollisionCheck_SetSphereHitFX(GlobalContext* globalCtx, CollisionCheckContext* colCtxt, Collider* collider);
void CollisionCheck_SetHitEffects(GlobalContext* globalCtx, CollisionCheckContext* colCtxt);
void CollisionCheck_AC(GlobalContext* globalCtx, CollisionCheckContext* colCtxt, Collider* colAT);
void CollisionCheck_AT(GlobalContext* globalCtx, CollisionCheckContext* colCtxt);
s32 CollisionCheck_GetMassType(u8 mass);
void CollisionCheck_SetOCvsOC(GlobalContext* globalCtx, Collider* left, ColliderInfo* leftInfo, Vec3f* leftPos,
                              Collider* right, ColliderInfo* rightInfo, Vec3f* rightPos, f32 overlap);
void CollisionCheck_OC_JntSphVsJntSph(GlobalContext* globalCtx, CollisionCheckContext* colCtxt, Collider* l,
                                      Collider* r);
void CollisionCheck_OC_JntSphVsCyl(GlobalContext* globalCtx, CollisionCheckContext* colCtxt, Collider* l, Collider* r);
void CollisionCheck_OC_JntSphVsSphere(GlobalContext* globalCtx, CollisionCheckContext* colCtxt, Collider* l,
                                      Collider* r);
void CollisionCheck_OC_CylVsJntSph(GlobalContext* globalCtx, CollisionCheckContext* colCtxt, Collider* l, Collider* r);
void CollisionCheck_OC_CylVsCyl(GlobalContext* globalCtx, CollisionCheckContext* colCtxt, Collider* l, Collider* r);
void CollisionCheck_OC_CylVsSphere(GlobalContext* globalCtx, CollisionCheckContext* colCtxt, Collider* l, Collider* r);
void CollisionCheck_OC_SphereVsJntSph(GlobalContext* globalCtx, CollisionCheckContext* colCtxt, Collider* l,
                                      Collider* r);
void CollisionCheck_OC_SphereVsCyl(GlobalContext* globalCtx, CollisionCheckContext* colCtxt, Collider* l, Collider* r);
void CollisionCheck_OC_SphereVsSphere(GlobalContext* globalCtx, CollisionCheckContext* colCtxt, Collider* l,
                                      Collider* r);
s32 CollisionCheck_SkipOC(Collider* collider);
s32 CollisionCheck_Incompatible(Collider* left, Collider* right);
void CollisionCheck_OC(GlobalContext* globalCtx, CollisionCheckContext* colCtxt);
void CollisionCheck_InitInfo(CollisionCheckInfo* info);
void CollisionCheck_ResetDamage(CollisionCheckInfo* info);
void CollisionCheck_SetInfoNoDamageTable(CollisionCheckInfo* info, CollisionCheckInfoInit* init);
void CollisionCheck_SetInfo(CollisionCheckInfo* info, DamageTable* damageTable, CollisionCheckInfoInit* init);
void CollisionCheck_SetInfo2(CollisionCheckInfo* info, DamageTable* damageTable, CollisionCheckInfoInit2* init);
void CollisionCheck_SetInfoGetDamageTable(CollisionCheckInfo* info, s32 index, CollisionCheckInfoInit2* init);
void CollisionCheck_ApplyDamage(GlobalContext* globalCtx, CollisionCheckContext* colCtxt, Collider* collider,
                                ColliderInfo* info);
void CollisionCheck_ApplyDamageJntSph(GlobalContext* globalCtx, CollisionCheckContext* colCtxt, Collider* collider);
void CollisionCheck_ApplyDamageCyl(GlobalContext* globalCtx, CollisionCheckContext* colCtxt, Collider* collider);
void CollisionCheck_ApplyDamageTris(GlobalContext* globalCtx, CollisionCheckContext* colCtxt, Collider* collider);
void CollisionCheck_ApplyDamageQuad(GlobalContext* globalCtx, CollisionCheckContext* colCtxt, Collider* collider);
void CollisionCheck_ApplyDamageSphere(GlobalContext* globalCtx, CollisionCheckContext* colCtxt, Collider* collider);
void CollisionCheck_Damage(GlobalContext* globalCtx, CollisionCheckContext* colCtxt);
s32 CollisionCheck_LineOC_JntSph(GlobalContext* globalCtx, CollisionCheckContext* colChkCtx, Collider* collider,
                                 Vec3f* a, Vec3f* b);
s32 CollisionCheck_LineOC_Cyl(GlobalContext* globalCtx, CollisionCheckContext* colChkCtx, Collider* collider, Vec3f* a,
                              Vec3f* b);
s32 CollisionCheck_LineOC_Sphere(GlobalContext* globalCtx, CollisionCheckContext* colChkCtx, Collider* collider,
                                 Vec3f* a, Vec3f* b);
s32 CollisionCheck_LineOC(GlobalContext* globalCtx, CollisionCheckContext* colChkCtx, Vec3f* a, Vec3f* b,
                          Actor** exclusions, s32 numExclusions);
s32 CollisionCheck_LineOCCheckAll(GlobalContext* globalCtx, CollisionCheckContext* colCtxt, Vec3f* a, Vec3f* b);
s32 CollisionCheck_LineOCCheck(GlobalContext* globalCtx, CollisionCheckContext* colCtxt, Vec3f* a, Vec3f* b,
                               Actor** exclusions, s32 numExclusions);
void Collider_UpdateCylinder(Actor* actor, ColliderCylinder* collider);
void Collider_SetCylinderPosition(ColliderCylinder* collider, Vec3s* pos);
void Collider_SetQuadVertices(ColliderQuad* collider, Vec3f* a, Vec3f* b, Vec3f* c, Vec3f* d);
void Collider_SetTrisVertices(ColliderTris* collider, s32 index, Vec3f* a, Vec3f* b, Vec3f* c);
void Collider_SetTrisDim(GlobalContext* globalCtx, ColliderTris* collider, s32 index, ColliderTrisElementDimInit* init);
void Collider_UpdateSpheres(s32 limb, ColliderJntSph* collider);
void Collider_UpdateSpheresElement(ColliderJntSph* collider, s32 index, Actor* actor);
void Collider_UpdateSphere(s32 limb, ColliderSphere* collider);
void CollisionCheck_SpawnRedBlood(GlobalContext* globalCtx, Vec3f* v);
void CollisionCheck_SpawnWaterDroplets(GlobalContext* globalCtx, Vec3f* v);
void CollisionCheck_SpawnShieldParticles(GlobalContext* globalCtx, Vec3f* v);
void CollisionCheck_SpawnShieldParticlesMetal(GlobalContext* globalCtx, Vec3f* v);
void CollisionCheck_SpawnShieldParticlesMetalSound(GlobalContext* globalCtx, Vec3f* v, Vec3f* pos);
void CollisionCheck_SpawnShieldParticlesMetal2(GlobalContext* globalCtx, Vec3f* v);
void CollisionCheck_SpawnShieldParticlesWood(GlobalContext* globalCtx, Vec3f* v, Vec3f* pos);
s32 CollisionCheck_CylSideVsLineSeg(f32 radius, f32 height, f32 offset, Vec3f* actorPos, Vec3f* itemPos,
                                    Vec3f* itemProjPos, Vec3f* out1, Vec3f* out2);
void func_800E8EA0(GlobalContext* globalCtx, Actor* actor, u16 textId);
s32 nop_800E8ED0(UNK_TYPE4 param_1);
void nop_800E8EE0(UNK_TYPE4 param_1);
s32 nop_800E8EEC(UNK_TYPE4 param_1);
void nop_800E8EFC(UNK_TYPE4 param_1);
s32 func_800E8F08(Vec3s* param_1, Vec3s* param_2);
s32 func_800E8FA4(Actor* actor, Vec3f* param_2, Vec3s* param_3, Vec3s* param_4);
s32 func_800E9138(GlobalContext* globalCtx, Actor* actor, Vec3s* param_3, Vec3s* param_4, f32 param_5);
s32 func_800E9250(GlobalContext* globalCtx, Actor* actor, Vec3s* param_3, Vec3s* param_4, Vec3f param_5);
u8 func_800E9360(void);
// void static_context_init(void);
// void func_800E9470(void);
void DebugDisplay_AddObject(f32 posX, f32 posY, f32 posZ, s16 rotX, s16 rotY, s16 rotZ, f32 scaleX, f32 scaleY,
                            f32 scaleZ, u8 red, u8 green, u8 blue, u8 alpha, s16 type, GraphicsContext* gfxCtx);
void DebugDisplay_DrawObjects(GlobalContext* globalCtx);
// void func_800E95F4(void);
// void func_800E97D8(void);
// void func_800E992C(void);
// void func_800E99B0(void);
// void func_800E9C90(void);
// void func_800E9CA0(s32 param_1, UNK_TYPE1 param_2, s8* param_3);
// void func_800E9CFC(void);
// void func_800E9DBC(void);
// void func_800E9E94(void);
void func_800E9F78(GraphicsContext* gfxCtx);
void Cutscene_Init(GlobalContext* globalCtx, CutsceneContext* csCtx);
void func_800EA0D4(GlobalContext* globalCtx, CutsceneContext* csCtx);
void func_800EA0EC(GlobalContext* globalCtx, CutsceneContext* csCtx);
void Cutscene_StepCutscene1(GlobalContext* globalCtx, CutsceneContext* csCtx);
void Cutscene_StepCutscene2(GlobalContext* globalCtx, CutsceneContext* csCtx);
void Cutscene_Nop800EA210(GlobalContext* globalCtx, CutsceneContext* csCtx);
s32 func_800EA220(GlobalContext* globalCtx, CutsceneContext* csCtx, f32 target);
void func_800EA258(GlobalContext* globalCtx, CutsceneContext* csCtx);
void func_800EA2B8(GlobalContext* globalCtx, CutsceneContext* csCtx);
void func_800EA324(GlobalContext* globalCtx, CutsceneContext* csCtx, CsCmdBase* cmd);
void func_800EABAC(GlobalContext* globalCtx, CutsceneContext* csCtx, CsCmdEnvLighting* cmd);
void func_800EAC08(GlobalContext* globalCtx, CutsceneContext* csCtx, CsCmdMusicChange* cmd);
void func_800EAC44(GlobalContext* globalCtx, CutsceneContext* csCtx, CsCmdMusicChange* cmd);
void func_800EAC94(GlobalContext* globalCtx, CutsceneContext* csCtx, CsCmdMusicFade* cmd);
void func_800EAD14(GlobalContext* globalCtx, CutsceneContext* csCtx, CsCmdBase* cmd);
void func_800EAD48(GlobalContext* globalCtx, CutsceneContext* csCtx, CsCmdBase* cmd);
void func_800EAD7C(GlobalContext* globalCtx, CutsceneContext* csCtx, CsCmdBase* cmd);
void func_800EADB0(GlobalContext* globalCtx, CutsceneContext* csCtx, CsCmdBase* cmd);
void func_800EAECC(GlobalContext* globalCtx, CutsceneContext* csCtx, CsCmdBase* cmd);
void func_800EAF20(GlobalContext* globalCtx, CutsceneContext* csCtx, CsCmdUnk190* cmd);
void func_800EAFE0(GlobalContext* globalCtx, CutsceneContext* csCtx, CsCmdUnk9B* cmd);
void func_800EB1DC(GlobalContext* globalCtx, CutsceneContext* csCtx, CsCmdDayTime* cmd);
void func_800EB364(GlobalContext* globalCtx, CutsceneContext* csCtx, CsCmdBase* cmd);
void func_800EB4B4(GlobalContext* globalCtx, CutsceneContext* csCtx, CsCmdBase* cmd);
void func_800EB6F8(GlobalContext* globalCtx, CutsceneContext* csCtx, CsCmdBase* cmd);
void func_800EBB68(GlobalContext* globalCtx, CutsceneContext* csCtx, CsCmdBase* cmd);
void func_800EBCD0(GlobalContext* globalCtx, CutsceneContext* csCtx, CsCmdBase* cmd);
void func_800EBD60(GlobalContext* globalCtx, CutsceneContext* csCtx, CsCmdBase* cmd);
s32 func_800EC678(GlobalContext* globalCtx, CsCmdUnk5A* cmd);
// u32 func_800EC6D4(void);
void func_800EC924(GlobalContext* globalCtx, CutsceneContext* csCtx, CsCmdTextbox* cmd);
void func_800ECD7C(CutsceneContext* csCtx, u8** cutscenePtr, s16 index);
void Cutscene_ProcessCommands(GlobalContext* globalCtx, CutsceneContext* csCtx, u8* cutscenePtr, u16* commandReadHead);
void func_800ED980(GlobalContext* globalCtx, CutsceneContext* csCtx);
void func_800ED9C4(GlobalContext* globalCtx, CutsceneContext* csCtx);
void func_800EDA04(GlobalContext* globalCtx, CutsceneContext* csCtx);
void func_800EDA84(GlobalContext* globalCtx, CutsceneContext* csCtx);
void func_800EDBE0(GlobalContext* globalCtx);
void nop_800EDDB0(GlobalContext* globalCtx);
// void func_800EDDBC(void);
void func_800EDDCC(GlobalContext* globalCtx, u32 uParm2);
void func_800EDE34(Actor* actor, GlobalContext* globalCtx, s32 param_3);
void func_800EDF24(Actor* actor, GlobalContext* globalCtx, u32 arg2);
void func_800EDF78(Actor* actor, GlobalContext* globalCtx, s32 iParm3);
void func_800EE0CC(Actor* actor, GlobalContext* globalCtx, s32 iParm3);
s32 func_800EE1D8(GlobalContext* globalCtx);
u32 func_800EE200(GlobalContext* globalCtx, u32 uParm2);
u32 func_800EE29C(GlobalContext* globalCtx, u32 uParm2);
u32 func_800EE2F4(GlobalContext* globalCtx);
void GetItem_Draw(GlobalContext* globalCtx, s16 index);
void func_800EE364(GlobalContext* globalCtx, s16 index);
void func_800EE400(GlobalContext* globalCtx, s16 index);
void func_800EE5FC(GlobalContext* globalCtx, s16 index);
void func_800EE7D8(GlobalContext* globalCtx, s16 index);
void func_800EE940(GlobalContext* globalCtx, s16 index);
void func_800EEA48(GlobalContext* globalCtx, s16 index);
void func_800EEC18(GlobalContext* globalCtx, s16 index);
void func_800EED20(GlobalContext* globalCtx, s16 index);
void func_800EEE34(GlobalContext* globalCtx, s16 index);
void func_800EEF4C(GlobalContext* globalCtx, s16 index);
void func_800EF054(GlobalContext* globalCtx, s16 index);
void func_800EF0F0(GlobalContext* globalCtx, s16 index);
void func_800EF1F4(GlobalContext* globalCtx, s16 index);
void func_800EF2AC(GlobalContext* globalCtx, s16 index);
void func_800EF364(GlobalContext* globalCtx, s16 index);
void func_800EF4D4(GlobalContext* globalCtx, s16 index);
void func_800EF65C(GlobalContext* globalCtx, s16 index);
void func_800EF780(GlobalContext* globalCtx, s16 index);
void func_800EF89C(GlobalContext* globalCtx, s16 index);
void func_800EF984(GlobalContext* globalCtx, s16 index);
void func_800EFAB8(GlobalContext* globalCtx, s16 index);
void func_800EFBFC(GlobalContext* globalCtx, s16 index);
void func_800EFD44(GlobalContext* globalCtx, s16 index);
void EffFootmark_Init(GlobalContext* globalCtx);
void EffFootmark_Add(GlobalContext* globalCtx, MtxF* displayMatrix, Actor* actor, u8 id, Vec3f* location, u16 size,
                     u8 red, u8 green, u8 blue, u16 alpha, u16 alphaChange, u16 fadeoutDelay);
void EffFootmark_Update(GlobalContext* globalCtx);
void EffFootmark_Draw(GlobalContext* globalCtx);
void func_800F0390(GlobalContext* globalCtx);
void func_800F03C0(GlobalContext* globalCtx);
void func_800F048C(GlobalContext* globalCtx, Vec3f* param_2, u8 param_3, u16 param_4, u8 param_5);
void func_800F0568(GlobalContext* globalCtx, Vec3f* position, s32 param_3, u16 sfxId);
// void func_800F0590(void);
// void func_800F05C0(void);
// void func_800F07C0(void);
// void func_800F0888(void);
// void func_800F0944(void);
// void func_800F09B4(void);
// void func_800F0A20(void);
// void func_800F0A94(void);
// void func_800F0BB4(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE2 param_5);
// void func_800F0CE4(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE2 param_5, UNK_TYPE4 param_6);
// void func_800F0DD4(void);
// void func_800F0E94(void);
// void func_800F0EEC(void);
// void func_800F0F28(void);
// void func_800F0FF0(void);
// void func_800F10AC(void);
// void func_800F112C(void);
u16 Text_GetFaceReaction(GlobalContext* globalCtx, u32 reactionSet);
void func_800F12D0(GlobalContext* globalCtx);
void func_800F1304(GlobalContext* globalCtx, s16 param_2);
void func_800F1374(s32 param_1, s16 param_2);
s16 func_800F13E8(GlobalContext* globalCtx, s16 param_2);
s16 func_800F1460(s16 param_1);
ActorCutscene* ActorCutscene_GetCutsceneImpl(s16 index);
void ActorCutscene_Init(GlobalContext* globalCtx, ActorCutscene* cutscenes, s32 num);
void func_800F15D8(Camera* camera);
// void ActorCutscene_ClearWaiting(void);
// void ActorCutscene_ClearNextCutscenes(void);
// void ActorCutscene_MarkNextCutscenes(void);
// void ActorCutscene_End(void);
// void ActorCutscene_Update(void);
void ActorCutscene_SetIntentToPlay(s16 index);
s16 ActorCutscene_GetCanPlayNext(s16 index);
s16 ActorCutscene_StartAndSetUnkLinkFields(s16 index, Actor* actor);
s16 ActorCutscene_StartAndSetFlag(s16 index, Actor* actor);
s16 ActorCutscene_Start(s16 index, Actor* actor);
s16 ActorCutscene_Stop(s16 index);
s16 ActorCutscene_GetCurrentIndex(void);
ActorCutscene* ActorCutscene_GetCutscene(s16 index);
s16 ActorCutscene_GetAdditionalCutscene(s16 index);
s16 ActorCutscene_GetLength(s16 index);
// void func_800F2138(void);
// void func_800F2178(void);
s16 ActorCutscene_GetCurrentCamera(s16 index);
// void func_800F21CC(void);
// UNK_TYPE4 func_800F22C4(s16 param_1, Actor* actor);
void ActorCutscene_SetReturnCamera(s16 index);
// void func_800F23E0(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5,
// UNK_TYPE4 param_6); void func_800F2478(void); void func_800F2620(void); void func_800F2650(void); void
// func_800F26C0(void); void func_800F26F0(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4,
// UNK_TYPE4 param_5, UNK_TYPE4 param_6); void func_800F2728(void); void func_800F29A0(UNK_TYPE1 param_1, UNK_TYPE1
// param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6, UNK_TYPE4 param_7); void
// func_800F2CD8(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5,
// UNK_TYPE4 param_6, UNK_TYPE4 param_7);
void FireObj_InitWithParams(GlobalContext* globalCtx, FireObj* fire, FireObjInitParams* init);
void FireObj_SetState(FireObj* fire, f32 dynamicSizeStep, u8 newState);
void FireObj_SetPosition(FireObj* fire, Vec3f* pos);
void FireObj_StepSize(FireObj* fire);
void FireObj_UpdateStateTransitions(GlobalContext* globalCtx, FireObj* fire);
void FireObj_Draw(GlobalContext* globalCtx, FireObj* fire);
void FireObj_InitLight(GlobalContext* globalCtx, FireObjLight* light, u8* param_3, Vec3f* pos);
void FireObj_FiniLight(GlobalContext* globalCtx, FireObjLight* light);
void FireObj_UpdateLight(GlobalContext* globalCtx, FireObjLight* light, FireObj* fire);
void FireObj_Init(GlobalContext* globalCtx, FireObj* fire, FireObjInitParams* init, Actor* actor);
void FireObj_Fini(GlobalContext* globalCtx, FireObj* fire);
void FireObj_SetState2(FireObj* fire, f32 dynamicSizeStep, u8 newState);
void FireObj_Update(GlobalContext* globalCtx, FireObj* fire);
// void func_800F3940(void);
// void func_800F39B4(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5);
// void func_800F3A64(void);
// void func_800F3B2C(void);
// void func_800F3B68(void);
// void func_800F3C44(void);
// void func_800F3ED4(void);
void func_800F40A0(GlobalContext* globalCtx, Player* player);
// void func_800F415C(void);
UNK_TYPE func_800F41E4(GlobalContext* globalCtx, ActorContext* actorCtx);
// void func_800F42A0(void);
// void func_800F43BC(void);
// void func_800F44F4(void);
// void func_800F4540(void);
// s32 func_800F470C(UNK_TYPE4 param_1, UNK_TYPE4 param_2, s32 param_3, u32 param_4);
void func_800F4A10(GlobalContext* globalCtx);
void func_800F4C0C(GlobalContext* globalCtx);
void func_800F4E20(GlobalContext* globalCtx);
void func_800F4F28(GlobalContext* globalCtx);
void Font_LoadChar(GlobalContext* globalCtx, u16 codePointIndex, s32 offset);
void Font_LoadCharNES(GlobalContext* globalCtx, u8 codePointIndex, s32 offset);
void Font_LoadMessageBoxEndIcon(Font* font, u16 icon);
void Font_LoadOrderedFont(Font* font);
// void func_800F5090(void);
// void func_800F50D4(void);
void Kankyo_Init(GlobalContext* globalCtx, EnvironmentContext* envCtx);
u32 func_800F5954(u8* param_1, u32 param_2, u32 param_3, u8 param_4, u8 param_5);
// void func_800F5A8C(void);
// void func_800F5B10(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE2 param_5);
// void func_800F5CD0(void);
// void func_800F6834(void);
// void func_800F694C(void);
// void func_800F6A04(void);
// void func_800F6A40(void);
// void func_800F6AB8(void);
void func_800F6B44(GlobalContext* globalCtx, EnvironmentContext* envCtx, s32 iParm3, s32 iParm4, s16* param_5);
// void func_800F6CEC(void);
// void func_800F6EA4(void);
// UNK_TYPE4 Kankyo_IsSceneUpsideDown(GlobalContext* globalCtx);
void func_800F6FF8(GlobalContext* globalCtx, EnvironmentContext* envCtx, LightContext* lightCtx);
// void func_800F8554(void);
// void func_800F88C4(void);
// void func_800F8970(void);
// void func_800F8A9C(void);
// void func_800F8CD4(GlobalContext* globalCtx, EnvironmentContext* envCtx, LightContext* lightCtx, s32 param_4,
// UNK_TYPE4 param_5, UNK_TYPE4 param_6); void func_800F8D84(void); void func_800F9728(UNK_TYPE1 param_1, UNK_TYPE1
// param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6, UNK_TYPE4 param_7);
void func_800F9824(GlobalContext* globalCtx, EnvironmentContext* envCtx, View* view, GraphicsContext* gfxCtx, Vec3f vec,
                   f32 arg5, f32 arg6, s8 arg7, s8 arg8);
// void func_800FA39C(void);
// void func_800FA3C4(void);
// void func_800FA9FC(void);
// void func_800FAAB4(void);
// void func_800FAC20(void);
// void func_800FAF74(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE1 param_5);
// void func_800FB010(void);
void func_800FB320(GlobalContext* globalCtx, u8 param_2);
// void func_800FB388(void);
// void func_800FB758(void);
// void func_800FB9B4(void);
// void func_800FBCBC(void);
// void func_800FBDEC(void);
void func_800FBF3C(GlobalContext* globalCtx);
// void func_800FC158(void);
// void func_800FC3DC(void);
// void func_800FC444(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE1 param_5,
// UNK_TYPE1 param_6); void func_800FC64C(void); void func_800FD2B4(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1
// param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5);
void func_800FD538(Color_RGB8* param_1, Color_RGB8* param_2, f32 param_3, Vec3s* param_4);
void func_800FD59C(GlobalContext* globalCtx, Color_RGB8* pzParm2, f32 fParm3);
void func_800FD5E0(GlobalContext* globalCtx, Color_RGB8* pzParm2, f32 fParm3);
void func_800FD654(GlobalContext* globalCtx, Color_RGB8* pzParm2, f32 fParm3);
// void func_800FD698(void);
// u32 get_days_elapsed(void);
// void reset_days_elapsed(void);
// u32 get_current_day(void);
void func_800FD750(UNK_TYPE arg0);
// void func_800FD768(void);
void func_800FD78C(GlobalContext* globalCtx);
void func_800FD858(GlobalContext* globalCtx);
void func_800FD928(s32 param_1);
// void func_800FD980(void);
// void func_800FDAF8(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5);
// void func_800FDC94(void);
// void func_800FE390(void);
// void func_800FE3E0(void);
void func_800FE484(void);
void func_800FE498(void);
// void func_800FE4A8(void);
u32 func_800FE4B8(GlobalContext* globalCtx);
// void func_800FE590(void);
// void func_800FE5D0(void);
// UNK_TYPE4 func_800FE610(void);
s32 func_800FE620(GlobalContext* globalCtx);
void func_800FE658(f32 arg0);
// UNK_TYPE4 func_800FE6F8(UNK_TYPE4 param_1, s16 param_2, s16 param_3);
// void func_800FE778(void);
// void func_800FE788(void);
// void func_800FE798(void);
// void func_800FE7A8(void);
// void func_800FE9B4(void);
// void func_800FEA50(void);
void func_800FEAB0(void);
// void func_800FEAC0(void);
// void func_800FEAF4(void);
void* Lib_MemCpy(void* dest, void* src, size_t size);
void* Lib_MemSet(void* buffer, s32 value, size_t size);
f32 Math_CosS(s16 angle);
f32 Math_SinS(s16 angle);
s32 Math_StepToIImpl(s32 start, s32 target, s32 step);
void Math_StepToIGet(s32* pValue, s32 target, s32 step);
s32 Math_StepToI(s32* pValue, s32 target, s32 step);
s32 Math_ScaledStepToS(s16* pValue, s16 target, s16 step);
s32 Math_StepToS(s16* pValue, s16 target, s16 step);
s32 Math_StepToC(s8* pValue, s8 target, s8 step);
s32 Math_StepToF(f32* pValue, f32 target, f32 step);
s32 Math_StepUntilAngleS(s16* pValue, s16 target, s16 step);
s32 Math_StepToAngleS(s16* pValue, s16 target, s16 step);
s32 Math_AsymStepToS(s16* pValue, s16 target, s16 incrStep, s16 decrStep);
s32 Math_StepUntilF(f32* pValue, f32 limit, f32 step);
s32 Math_AsymStepToF(f32* pValue, f32 target, f32 incrStep, f32 decrStep);
void func_800FF3A0(f32* distOut, s16* angleOut, Input* input);
s16 Rand_S16Offset(s16 base, s16 range);
s16 Rand_S16OffsetStride(s16 base, s16 stride, s16 range);
void Math_Vec3f_Copy(Vec3f* dest, Vec3f* src);
void Math_Vec3s_Copy(Vec3s* dest, Vec3s* src);
void Math_Vec3s_ToVec3f(Vec3f* dest, Vec3s* src);
void Math_Vec3f_ToVec3s(Vec3s* dest, Vec3f* src);
void Math_Vec3f_Sum(Vec3f* l, Vec3f* r, Vec3f* dest);
void Math_Vec3f_Diff(Vec3f* l, Vec3f* r, Vec3f* dest);
void Math_Vec3s_DiffToVec3f(Vec3f* dest, Vec3s* l, Vec3s* r);
void Math_Vec3f_Scale(Vec3f* vec, f32 scale);
void Math_Vec3f_ScaleAndStore(Vec3f* vec, f32 scale, Vec3f* dest);
void Math_Vec3f_Lerp(Vec3f* a, Vec3f* b, f32 t, Vec3f* dest);
void Math_Vec3f_SumScaled(Vec3f* a, Vec3f* b, f32 scale, Vec3f* dest);
void Math_Vec3f_AddRand(Vec3f* orig, f32 scale, Vec3f* dest);
void Math_Vec3f_DistXYZAndStoreNormDiff(Vec3f* a, Vec3f* b, f32 scale, Vec3f* dest);
f32 Math_Vec3f_DistXYZ(Vec3f* a, Vec3f* b);
f32 Math_Vec3f_DistXYZAndStoreDiff(Vec3f* a, Vec3f* b, Vec3f* dest);
f32 Math_Vec3f_DistXZ(Vec3f* a, Vec3f* b);
f32 Math_Vec3f_DistXZAndStore(Vec3f* a, Vec3f* b, f32* dx, f32* dz);
f32 Math_Vec3f_StepToXZ(Vec3f* start, Vec3f* target, f32 speed);
f32 Math_Vec3f_DiffY(Vec3f* a, Vec3f* b);
s16 Math_Vec3f_Yaw(Vec3f* a, Vec3f* b);
s16 Math_Vec3f_Pitch(Vec3f* a, Vec3f* b);
void Actor_ProcessInitChain(Actor* actor, InitChainEntry* ichain);
// void IChain_Apply_u8(u8* actor, InitChainEntry* init);
// void IChain_Apply_s8(u8* actor, InitChainEntry* init);
// void IChain_Apply_u16(u8* actor, InitChainEntry* init);
// void IChain_Apply_s16(u8* actor, InitChainEntry* init);
// void IChain_Apply_u32(u8* actor, InitChainEntry* init);
// void IChain_Apply_s32(u8* actor, InitChainEntry* init);
// void IChain_Apply_f32(u8* actor, InitChainEntry* init);
// void IChain_Apply_f32div1000(u8* actor, InitChainEntry* init);
// void IChain_Apply_Vec3f(u8* actor, InitChainEntry* init);
// void IChain_Apply_Vec3fdiv1000(u8* actor, InitChainEntry* init);
// void IChain_Apply_Vec3s(u8* actor, InitChainEntry* init);
f32 Math_SmoothStepToF(f32* pValue, f32 target, f32 fraction, f32 step, f32 minStep);
void Math_ApproachF(f32* pValue, f32 target, f32 scale, f32 maxStep);
void Math_ApproachZeroF(f32* pValue, f32 scale, f32 maxStep);
s32 Math_SmoothStepToS(s16* pValue, s16 target, s16 scale, s16 step, s16 minStep);
void Math_ApproachS(s16* pValue, s16 target, s16 scale, s16 maxStep);
void Color_RGBA8_Copy(Color_RGBA8* dst, Color_RGBA8* src);
void func_801000A4(u16 sfxId);
void func_801000CC(u16 sfxId);
void func_801000F4(s32 a0, u16 a1);
void Lib_Vec3f_TranslateAndRotateY(Vec3f* translation, s16 a, Vec3f* src, Vec3f* dst);
void Lib_LerpRGB(Color_RGB8* a, Color_RGB8* b, f32 t, Color_RGB8* dst);
f32 Math_Vec3f_StepTo(Vec3f* start, Vec3f* target, f32 speed);
void Lib_Nop801004FC(void);
void* Lib_SegmentedToVirtual(void* ptr);
void* Lib_SegmentedToVirtualNull(void* ptr);
void* Lib_PhysicalToVirtual(void* ptr);
void* Lib_PhysicalToVirtualNull(void* ptr);
void LifeMeter_Init(GlobalContext* globalCtx);
void LifeMeter_UpdateColors(GlobalContext* globalCtx);
s32 LifeMeter_SaveInterfaceHealth(GlobalContext* globalCtx);
s32 LifeMeter_IncreaseInterfaceHealth(GlobalContext* globalCtx);
s32 LifeMeter_DecreaseInterfaceHealth(GlobalContext* globalCtx);
void LifeMeter_Draw(GlobalContext* globalCtx);
void LifeMeter_UpdateSizeAndBeep(GlobalContext* globalCtx);
bool LifeMeter_IsCritical(void);
void Lights_PointSetInfo(LightInfo* info, s16 x, s16 y, s16 z, u8 r, u8 g, u8 b, s16 radius, s32 type);
void Lights_PointNoGlowSetInfo(LightInfo* info, s16 x, s16 y, s16 z, u8 r, u8 g, u8 b, s16 radius);
void Lights_PointGlowSetInfo(LightInfo* info, s16 x, s16 y, s16 z, u8 r, u8 g, u8 b, s16 radius);
void Lights_PointSetColorAndRadius(LightInfo* info, u8 r, u8 g, u8 b, s16 radius);
void Lights_PointSetPosition(LightInfo* info, s16 x, s16 y, s16 z);
void Lights_DirectionalSetInfo(LightInfo* info, s8 x, s8 y, s8 z, u8 r, u8 g, u8 b);
void Lights_Reset(Lights* lights, u8 r, u8 g, u8 b);
void Lights_Draw(Lights* lights, GraphicsContext* gfxCtx);
Light* Lights_FindSlot(Lights* lights);
void Lights_BindPointWithReference(Lights* lights, LightParams* params, Vec3f* pos);
void Lights_BindPoint(Lights* lights, LightParams* params, GlobalContext* globalCtx);
void Lights_BindDirectional(Lights* lights, LightParams* params, void* unused);
void Lights_BindAll(Lights* lights, LightNode* listHead, Vec3f* refPos, GlobalContext* globalCtx);
LightNode* Lights_FindBufSlot();
void Lights_FreeNode(LightNode* light);
void LightContext_Init(GlobalContext* globalCtx, LightContext* lightCtx);
void LightContext_SetAmbientColor(LightContext* lightCtx, u8 r, u8 g, u8 b);
void func_80102544(LightContext* lightCtx, u8 a1, u8 a2, u8 a3, s16 numLights, s16 sp16);
Lights* LightContext_NewLights(LightContext* lightCtx, GraphicsContext* gfxCtx);
void LightContext_InitList(GlobalContext* globalCtx, LightContext* lightCtx);
void LightContext_DestroyList(GlobalContext* globalCtx, LightContext* lightCtx);
LightNode* LightContext_InsertLight(GlobalContext* globalCtx, LightContext* lightCtx, LightInfo* info);
void LightContext_RemoveLight(GlobalContext* globalCtx, LightContext* lightCtx, LightNode* light);
Lights* Lights_NewAndDraw(GraphicsContext* gfxCtx, u8 ambientR, u8 ambientG, u8 ambientB, u8 numLights, u8 r, u8 g,
                          u8 b, s8 x, s8 y, s8 z);
Lights* Lights_New(GraphicsContext* gfxCtx, u8 ambientR, u8 ambientG, u8 ambientB);
void Lights_GlowCheck(GlobalContext* globalCtx);
void Lights_DrawGlow(GlobalContext* globalCtx);
void* zelda_malloc(u32 size);
void* zelda_mallocR(u32 size);
void* zelda_realloc(void* oldPtr, u32 newSize);
void zelda_free(void* param_1);
void* zelda_calloc(u32 num, u32 size);
void MainHeap_AnalyzeArena(u32* maxFreeBlock, u32* bytesFree, u32* bytesAllocated);
// s32 MainHeap_Check(void);
void MainHeap_Init(u32 base, u32 size);
// void MainHeap_Cleanup(void);
// u32 MainHeap_IsInitialized(void);
// void func_80102E40(void);
// void func_80102E90(void);
// void func_80102EA4(void);
void func_80102EB4(u32 param_1);
void func_80102ED0(u32 param_1);
// void func_80102EF0(void);
// void func_80102F9C(void);
// void func_80103090(void);
// void func_801030B4(void);
// void func_801030F4(void);
// void func_801031D0(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5,
// UNK_TYPE4 param_6); void func_801039EC(void); void func_80103A10(void); void func_80103A58(void); void
// func_8010439C(void); void func_801045AC(void); void func_80104AE8(void); void func_80104C80(void);
void func_80104CF4(GlobalContext* globalCtx);
// void func_80104F34(void);
// void func_80105294(void);
// void func_80105318(void);
// void func_80105328(void);
// void func_8010534C(void);
void func_8010549C(GlobalContext* globalCtx, void* segmentAddress);
void func_8010565C(GlobalContext* globalCtx, u8 num, void* segmentAddress);
void func_80105818(GlobalContext* globalCtx, u32 uParm2, TransitionActorEntry* puParm3);
// void func_80105A40(void);
// void func_80105B34(void);
// void func_80105C40(void);
// void func_80105FE0(void);
// void func_80106408(void);
// void func_80106450(void);
// void func_801064CC(void);
// void func_80106530(void);
// void func_8010657C(void);
// void func_80106644(void);
// void func_8010683C(void);
// void func_801068B4(void);
// void func_801068D8(void);
// void func_801068FC(void);
// void func_80106BEC(void);
// void func_80106D08(void);
// void func_80106D5C(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5,
// UNK_TYPE4 param_6, UNK_TYPE4 param_7); void func_80107B78(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3,
// UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6); void func_80108124(UNK_TYPE1 param_1, UNK_TYPE1 param_2,
// UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6); void func_80108558(UNK_TYPE1 param_1,
// UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6, UNK_TYPE4 param_7);
// void func_80108A10(void);
// void func_80108A64(void);
// void func_80108AF8(void);
// void func_801090B0(void);
// void func_80109124(void);
// void func_801091F0(void);
// void func_80109428(void);
// void func_801094A0(void);
// void func_801094C8(void);
// void func_801094F8(void);
// void func_80109528(void);
// void func_8010954C(void);
// void func_8010956C(void);
// void func_8010958C(void);
// void func_801095AC(void);
// void func_801095DC(void);
// void func_8010960C(void);
// void func_80109630(void);
// void func_80109650(void);
// void func_80109670(void);
// void func_801096D4(void);
// void func_80109714(void);
// void func_80109754(void);
// void func_801097C8(void);
// void func_8010983C(void);
// void func_801098A0(void);
// void func_80109908(void);
// UNK_TYPE4 func_80109964(s32 param_1);
// void func_8010997C(void);
// void func_801099AC(void);
// void func_801099DC(void);
// void func_80109A00(void);
// void func_80109A20(void);
// void func_80109A40(void);
// void func_80109A98(void);
// void func_80109AD8(void);
// void func_80109B38(void);
// void func_80109BA0(void);
// void func_80109BF4(void);
// void func_80109C38(void);
// void func_80109CBC(void);
// void func_80109D40(void);
// void func_80109DD8(void);
// void func_80109E70(void);
// void func_80109EF8(void);
// void func_80109F78(void);
s32 func_8010A000(GlobalContext* globalCtx);
// void func_8010A074(void);
// void func_8010A0A4(void);
// void func_8010A0F0(void);
// void func_8010A164(void);
// void func_8010A194(void);
// void func_8010A208(void);
// void func_8010A238(void);
// void func_8010A2AC(void);
void func_8010A2DC(GlobalContext* globalCtx);
void func_8010A33C(GlobalContext* globalCtx, s16 param_2);
// void func_8010A410(void);
// void func_8010A430(void);
// void func_8010A54C(void);
// void func_8010A580(void);
// void func_8010A760(void);
// void func_8010A7CC(void);
// void func_8010A814(void);
// void func_8010A85C(void);
// void func_8010A8A4(void);
// void func_8010A8EC(void);
// void func_8010A990(void);
// void func_8010AA54(void);
// void func_8010AB30(void);
// void func_8010AB94(void);
// void func_8010AC00(void);
// void func_8010AD24(void);
// void func_8010ADD4(void);
// void func_8010AE48(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5);
// UNK_TYPE4 func_8010AECC(UNK_TYPE4 param_1, s32 param_2, s32* param_3);
// void func_8010AF20(void);
// void func_8010AF6C(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5);
// void func_8010AF94(void);
// void func_8010AFE0(void);
// void func_8010B010(void);
// void func_8010B06C(void);
// void func_8010B0B4(void);
// void func_8010B0DC(void);
// void func_8010B108(void);
// void func_8010B140(void);
// void func_8010B180(void);
// void func_8010B1BC(void);
// void func_8010B22C(void);
// void func_8010B284(void);
// void func_8010B2C0(void);
// void func_8010B300(void);
// void func_8010B434(void);
// void func_8010B4A4(void);
// void func_8010B520(void);
// void func_8010B664(void);
// void func_8010B7A8(void);
// void func_8010B828(void);
// void func_8010B878(void);
// void func_8010B8E4(void);
// void func_8010BB0C(void);
// void func_8010BB6C(void);
// void func_8010BBCC(void);
// void func_8010BC28(void);
// void func_8010BC7C(void);
// void func_8010BD48(void);
// void func_8010BD90(void);
// void func_8010BDDC(void);
// void func_8010BE78(void);
// void func_8010BEBC(void);
// void func_8010BEF0(void);
// void func_8010BF24(void);
s32 func_8010BF58(Actor* actor, GlobalContext* globalCtx, s32* param_2, s32 param_3, s32* param_4);
// void Nmi_Init(void);
// void Nmi_SetPrenmiStart(void);
// s32 Nmi_GetPrenmiHasStarted(void);
// void func_8010C1B0(void);
f32 OLib_Vec3fDist(Vec3f* a, Vec3f* b);
f32 OLib_Vec3fDistOutDiff(Vec3f* a, Vec3f* b, Vec3f* dest);
f32 OLib_Vec3fDistXZ(Vec3f* a, Vec3f* b);
f32 OLib_ClampMinDist(f32 val, f32 min);
f32 OLib_ClampMaxDist(f32 val, f32 max);
Vec3f* OLib_Vec3fDistNormalize(Vec3f* dest, Vec3f* a, Vec3f* b);
Vec3f* OLib_VecSphToVec3f(Vec3f* dest, VecSph* sph);
Vec3f* OLib_VecSphGeoToVec3f(Vec3f* dest, VecSph* sph);
VecSph* OLib_Vec3fToVecSph(VecSph* dest, Vec3f* vec);
VecSph* OLib_Vec3fToVecSphGeo(VecSph* dest, Vec3f* vec);
VecSph* OLib_Vec3fDiffToVecSph(VecSph* dest, Vec3f* a, Vec3f* b);
VecSph* OLib_Vec3fDiffToVecSphGeo(VecSph* dest, Vec3f* a, Vec3f* b);
Vec3f* OLib_VecSphAddToVec3f(Vec3f* dest, Vec3f* a, VecSph* sph);
Vec3f* OLib_Vec3fDiffRad(Vec3f* dest, Vec3f* a, Vec3f* b);
Vec3f* OLib_Vec3fDiffDegF(Vec3f* dest, Vec3f* a, Vec3f* b);
Vec3s* OLib_Vec3fDiffBinAng(Vec3s* dest, Vec3f* a, Vec3f* b);
void OLib_DbCameraVec3fDiff(PosRot* a, Vec3f* b, Vec3f* dest, s16 mode);
void OLib_DbCameraVec3fSum(PosRot* a, Vec3f* b, Vec3f* dest, s16 mode);
// void func_8010CB80(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE2 param_5,
// UNK_TYPE2 param_6, UNK_TYPE2 param_7, UNK_TYPE2 param_8, UNK_TYPE2 param_9, UNK_TYPE2 param_10); void
// func_8010CD98(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE2 param_5,
// UNK_TYPE2 param_6, UNK_TYPE2 param_7, UNK_TYPE2 param_8, UNK_TYPE2 param_9, UNK_TYPE2 param_10); void
// func_8010CFBC(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE2 param_5,
// UNK_TYPE2 param_6, UNK_TYPE2 param_7, UNK_TYPE2 param_8, UNK_TYPE2 param_9, UNK_TYPE2 param_10, UNK_TYPE2 param_11,
// UNK_TYPE2 param_12, UNK_TYPE2 param_13, UNK_TYPE2 param_14); void func_8010D2D4(UNK_TYPE1 param_1, UNK_TYPE1 param_2,
// UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE2 param_5, UNK_TYPE2 param_6, UNK_TYPE2 param_7, UNK_TYPE2 param_8,
// UNK_TYPE2 param_9, UNK_TYPE2 param_10, UNK_TYPE2 param_11); void func_8010D480(UNK_TYPE1 param_1, UNK_TYPE1 param_2,
// UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE2 param_5, UNK_TYPE2 param_6, UNK_TYPE2 param_7, UNK_TYPE2 param_8,
// UNK_TYPE2 param_9, UNK_TYPE2 param_10, UNK_TYPE2 param_11, UNK_TYPE2 param_12, UNK_TYPE2 param_13, UNK_TYPE2
// param_14, UNK_TYPE4 param_15, UNK_TYPE4 param_16); void func_8010D7D0(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1
// param_3, UNK_TYPE1 param_4, UNK_TYPE2 param_5, UNK_TYPE2 param_6, UNK_TYPE2 param_7, UNK_TYPE2 param_8, UNK_TYPE2
// param_9, UNK_TYPE2 param_10); void func_8010D9F4(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1
// param_4, UNK_TYPE2 param_5, UNK_TYPE2 param_6, UNK_TYPE2 param_7, UNK_TYPE2 param_8, UNK_TYPE2 param_9, UNK_TYPE4
// param_10, UNK_TYPE4 param_11, UNK_TYPE4 param_12, UNK_TYPE2 param_13, UNK_TYPE2 param_14); void
// func_8010DC58(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE2 param_5); void
// func_8010DE38(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE2 param_5,
// UNK_TYPE2 param_6); void func_8010E028(void); void func_8010E968(void);
void func_8010E9F0(s16 arg0, s16 arg1);
// void func_8010EA9C(void);
// void func_8010EB50(void);
// void func_8010EBA0(void);
// void func_8010EC54(void);
// void func_8010EE74(void);
void Interface_ChangeAlpha(u16 param_1);
// void func_8010EF9C(void);
// void func_8010F0D4(void);
// void func_8010F1A8(void);
// void func_80110038(void);
// void func_80111CB4(void);
// void func_801129E4(void);
void func_80112AFC(GlobalContext* globalCtx);
// void func_80112B40(void);
// void func_80112BE4(void);
// void func_80112C0C(void);
u32 Item_Give(GlobalContext* globalCtx, u8 param_2);
// void func_801143CC(void);
UNK_TYPE func_80114978(UNK_TYPE arg0);
// void func_801149A0(void);
// void func_80114A9C(void);
// void func_80114B84(void);
// void func_80114CA0(void);
UNK_TYPE func_80114E90(void);
UNK_TYPE func_80114F2C(UNK_TYPE arg0);
// void func_80114FD0(void);
// void func_80115130(void);
// void func_801152B8(void);
// void func_801153C8(void);
// void func_80115428(void);
void func_8011552C(GlobalContext* globalCtx, s16 arg1);
// void func_801155B4(void);
// void func_80115764(void);
void func_80115844(GlobalContext* globalCtx, s16 param_2);
void func_80115908(GlobalContext* globalCtx, u8 param_2);
void func_801159c0(s16 param_1);
void func_801159EC(s16 arg0);
void func_80115A14(s32 arg0, s16 arg1);
// void Parameter_AddMagic(void);
// void func_80115D5C(void);
// void func_80115DB4(void);
// void func_80116088(void);
// void func_80116114(void);
// void func_80116348(void);
// void func_80116918(void);
// void func_80116FD8(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5);
// void func_801170B8(void);
// void func_80117100(void);
// void func_80117A20(void);
// void func_80117BD0(void);
// void func_80118084(void);
// void func_80118890(void);
// void func_80118BA4(void);
// void func_80119030(void);
// void func_80119610(void);
// void func_8011B4E0(void);
// void func_8011B5C0(void);
// void func_8011B9E0(void);
// void func_8011BF70(void);
// void func_8011C4C4(void);
void func_8011C808(GlobalContext* globalCtx);
// void func_8011C898(void);
// void func_8011CA64(void);
// void func_8011E3B4(void);
// void func_8011E730(void);
// void func_8011F0E0(UNK_TYPE4 ctxt);
// void func_80120F90(void);
// void func_80121000(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5,
// UNK_TYPE4 param_6, UNK_TYPE4 param_7, UNK_TYPE1 param_8, UNK_TYPE1 param_9, UNK_TYPE1 param_10, UNK_TYPE4 param_11,
// UNK_TYPE4 param_12, UNK_TYPE4 param_13, UNK_TYPE4 param_14); void func_80121064(void); void func_801210E0(void); void
// func_80121F94(void);
void func_80121FC4(GlobalContext* globalCtx);
s32 func_801224E0(s32 param_1, s16 param_2, s16 param_3);
// void func_80122524(void);
// void func_801225CC(void);
// void func_80122660(void);
// UNK_TYPE4 func_80122670(s32* param_1, Input* input);
// void func_801226E0(void);
void func_80122744(GlobalContext* globalCtx, UNK_PTR arg1, u32 arg2, Vec3s* arg3);
s32 func_80122760(GlobalContext* globalCtx, UNK_PTR arg1, f32 arg2);
void func_80122868(GlobalContext* globalCtx, Player* player);
void func_801229A0(GlobalContext* globalCtx, Player* player);
// void func_801229EC(void);
// void func_801229FC(void);
// void func_80122BA4(void);
// void func_80122C20(void);
// void func_80122D44(void);
// void func_80122ED8(void);
// void func_80122EEC(void);
void func_80122F28(Player* player, GlobalContext* globalCtx, Actor* actor);
// void func_80122F9C(void);
// void func_80122FCC(void);
// void func_8012300C(void);
void func_8012301C(s32 iParm1, GlobalContext* globalCtx);
void func_80123140(GlobalContext* globalCtx, Player* param_2);
u32 func_80123358(GlobalContext* globalCtx, Player* player);
u32 func_801233E4(GlobalContext* globalCtx);
// void func_80123420(void);
// void func_80123434(void);
// void func_80123448(void);
// void func_801234B0(void);
// void func_801234D4(void);
s32 func_80123590(GlobalContext* globalCtx, Actor* actor);
// void func_8012364C(void);
s32 func_80123810(GlobalContext* globalCtx);
// void func_80123960(void);
// void func_801239AC(void);
// void func_80123AA4(void);
// void func_80123BD4(void);
// void func_80123C58(void);
// void func_80123C90(void);
void func_80123D50(GlobalContext* globalCtx, Player* player, UNK_TYPE arg2, UNK_TYPE arg3);
void func_80123DA4(Player* player);
// void func_80123DC0(void);
// void func_80123E90(void);
// void func_80123F2C(void);
// void func_80123F48(void);
// void func_80124020(void);
u8 Player_GetMask(GlobalContext* globalCtx);
void Player_RemoveMask(GlobalContext* globalCtx);
// void func_8012405C(void);
// void func_80124088(void);
s32 func_801240C8(Player* player);
// void func_801240DC(void);
// void func_80124110(void);
// void func_80124148(void);
// void func_80124168(void);
// void func_80124190(void);
// void func_801241B4(void);
// void func_801241E0(void);
// void func_8012420C(void);
// void func_8012422C(void);
s32 func_80124258(Player* player); // Player_GetExplosiveHeld
// void func_80124278(void);
// void func_801242B4(void);
// void func_801242DC(void);
// void func_80124420(void);
// void func_80124618(void);
// void func_801246F4(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5,
// UNK_TYPE4 param_6, UNK_TYPE1 param_7, UNK_TYPE4 param_8, UNK_TYPE4 param_9, UNK_TYPE4 param_10, UNK_TYPE4 param_11);
// void func_80124870(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5,
// UNK_TYPE4 param_6, UNK_TYPE4 param_7, UNK_TYPE4 param_8); void func_80124CC4(void); void func_80124F18(UNK_TYPE1
// param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5); void func_80124FF0(UNK_TYPE1
// param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6, UNK_TYPE4
// param_7, UNK_TYPE4 param_8, UNK_TYPE4 param_9, UNK_TYPE2 param_10); void func_801251C4(void); void
// func_80125318(void); void func_80125340(void); void func_8012536C(void); void func_801253A4(void); void
// func_80125500(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5); void
// func_80125580(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5,
// UNK_TYPE4 param_6); void func_80125CE0(void); void func_80125D4C(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1
// param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6); void func_801262C8(UNK_TYPE1 param_1, UNK_TYPE1
// param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6); void func_801263FC(UNK_TYPE1
// param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6);
void func_80126440(GlobalContext* globalCtx, Collider* param_2, s32* param_3, Vec3f* param_4, Vec3f* param_5);
// void func_801265C8(void);
// void func_8012669C(void);
// void func_80126808(void);
void func_8012697C(GlobalContext* globalCtx, Player* player);
// void func_80126AB4(void);
// void func_80126B8C(void);
// void func_80126BD0(void);
// void func_801271B0(void);
// void func_80127438(void);
// void func_80127488(void);
// void func_8012754C(void);
// void func_80127594(void);
// void func_801278F8(void);
// void func_80127A60(void);
// void func_80127B64(void);
// void func_80127BE8(void);
// void func_80127DA4(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5,
// UNK_TYPE4 param_6, UNK_TYPE4 param_7); void func_80128388(void); void func_801284A0(void); void func_80128640(void);
// void func_80128B74(void);
// void func_80128BD0(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE1 param_5,
// UNK_TYPE4 param_6);
void PreNMI_Stop(PreNMIContext* prenmiCtx);
void PreNMI_Update(PreNMIContext* prenmiCtx);
void PreNMI_Draw(PreNMIContext* prenmiCtx);
void PreNMI_Main(PreNMIContext* prenmiCtx);
void PreNMI_Destroy(PreNMIContext* prenmiCtx);
void PreNMI_Init(PreNMIContext* prenmiCtx);
f32 Quake_Random(void);
void Quake_UpdateShakeInfo(QuakeRequest* req, ShakeInfo* shake, f32 verticalPertubation, f32 horizontalPertubation);
s16 Quake_Callback1(QuakeRequest* req, ShakeInfo* shake);
s16 Quake_Callback5(QuakeRequest* req, ShakeInfo* shake);
s16 Quake_Callback6(QuakeRequest* req, ShakeInfo* shake);
s16 Quake_Callback3(QuakeRequest* req, ShakeInfo* shake);
s16 Quake_Callback2(QuakeRequest* req, ShakeInfo* shake);
s16 Quake_Callback4(QuakeRequest* req, ShakeInfo* shake);
s16 Quake_GetFreeIndex(void);
QuakeRequest* Quake_AddImpl(Camera* camera, u32 callbackIdx);
void Quake_Remove(QuakeRequest* req);
QuakeRequest* Quake_GetRequest(s16 idx);
u32 Quake_SetValue(s16 idx, s16 valueType, s16 value);
u32 Quake_SetSpeed(s16 idx, s16 value);
u32 Quake_SetCountdown(s16 idx, s16 value);
s16 Quake_GetCountdown(s16 idx);
u32 Quake_SetQuakeValues(s16 idx, s16 verticalMag, s16 horizontalMag, s16 zoom, s16 rollOffset);
u32 Quake_SetQuakeValues2(s16 idx, s16 isShakePerpendicular, Vec3s shakePlaneOffset);
void Quake_Init(void);
s16 Quake_Add(Camera* camera, u32 callbackIdx);
u32 Quake_RemoveFromIdx(s16 idx);
s16 Quake_Calc(Camera* camera, QuakeCamCalc* camData);
void Quake2_Init(GlobalContext* globalCtx);
void Quake2_SetCountdown(s16 countdown);
s16 Quake2_GetCountdown(void);
s16 Quake2_GetType(void);
void Quake2_SetType(s32 type);
void Quake2_ClearType(s32 type);
s32 Quake2_GetFloorQuake(Player* player);
void Quake2_Update(void);
s32 Quake_NumActiveQuakes(void);
Gfx* Gfx_SetFog(Gfx* gfx, s32 r, s32 g, s32 b, s32 a, s32 n, s32 f);
Gfx* Gfx_SetFogWithSync(Gfx* gfx, s32 r, s32 g, s32 b, s32 a, s32 n, s32 f);
Gfx* Gfx_SetFog2(Gfx* gfx, s32 r, s32 g, s32 b, s32 a, s32 n, s32 f);
Gfx* Gfx_CallSetupDLImpl(Gfx* gfx, u32 i);
Gfx* Gfx_CallSetupDL(Gfx* gfx, u32 i);
void Gfx_CallSetupDLAtPtr(Gfx** gfxp, u32 i);
Gfx* func_8012BFC4(Gfx* gfx);
Gfx* func_8012BFEC(Gfx* gfx);
Gfx* func_8012C014(Gfx* gfx);
void func_8012C058(GraphicsContext* gfxCtx);
void func_8012C080(GraphicsContext* gfxCtx);
void func_8012C0A8(GraphicsContext* gfxCtx);
void func_8012C0D0(GraphicsContext* gfxCtx);
void func_8012C0F8(GraphicsContext* gfxCtx);
void func_8012C120(GraphicsContext* gfxCtx);
void func_8012C148(GraphicsContext* gfxCtx);
void func_8012C170(GraphicsContext* gfxCtx);
Gfx* func_8012C198(Gfx* gfx);
void func_8012C1C0(GraphicsContext* gfxCtx);
Gfx* func_8012C1EC(Gfx* gfx);
void func_8012C214(GraphicsContext* gfxCtx);
void func_8012C240(GraphicsContext* gfxCtx);
void func_8012C268(GlobalContext* globalCtx);
void func_8012C28C(GraphicsContext* gfxCtx);
Gfx* func_8012C2B4(Gfx* gfx);
void func_8012C2DC(GraphicsContext* gfxCtx);
Gfx* func_8012C304(Gfx* gfx);
void func_8012C32C(GraphicsContext* gfxCtx);
void func_8012C354(GraphicsContext* gfxCtx);
void func_8012C37C(GraphicsContext* gfxCtx);
Gfx* func_8012C3A4(Gfx* gfx);
Gfx* func_8012C3CC(Gfx* gfx);
void func_8012C3F4(GraphicsContext* gfxCtx);
void func_8012C420(GraphicsContext* gfxCtx);
void func_8012C448(GraphicsContext* gfxCtx);
void func_8012C470(GraphicsContext* gfxCtx);
Gfx* func_8012C498(Gfx* gfx);
void func_8012C4C0(GraphicsContext* gfxCtx);
void func_8012C4E8(GraphicsContext* gfxCtx);
void func_8012C510(GraphicsContext* gfxCtx);
void func_8012C538(GraphicsContext* gfxCtx);
void func_8012C560(GraphicsContext* gfxCtx);
void func_8012C588(GraphicsContext* gfxCtx);
void func_8012C5B0(GraphicsContext* gfxCtx);
void func_8012C5D8(GraphicsContext* gfxCtx);
Gfx* func_8012C600(Gfx* gfx);
void func_8012C628(GraphicsContext* gfxCtx);
void func_8012C654(GraphicsContext* gfxCtx);
void func_8012C680(Gfx** gfxp);
void func_8012C6AC(GraphicsContext* gfxCtx);
void func_8012C6D4(GraphicsContext* gfxCtx);
void func_8012C6FC(GraphicsContext* gfxCtx);
Gfx* func_8012C724(Gfx* gfx);
Gfx* func_8012C74C(Gfx* gfx);
Gfx* func_8012C774(Gfx* gfx);
Gfx* func_8012C7B8(Gfx* gfx);
Gfx* func_8012C7FC(Gfx* gfx);
Gfx* func_8012C840(Gfx* gfx);
Gfx* func_8012C868(Gfx* gfx);
void func_8012C8AC(GraphicsContext* gfxCtx);
void func_8012C8D4(GraphicsContext* gfxCtx);
void func_8012C8FC(GraphicsContext* gfxCtx);
void func_8012C924(GraphicsContext* gfxCtx);
void func_8012C94C(GraphicsContext* gfxCtx);
void func_8012C974(GraphicsContext* gfxCtx);
void func_8012C9BC(GraphicsContext* gfxCtx);
void func_8012C9E4(GraphicsContext* gfxCtx);
void func_8012CA0C(Gfx** gfxp);
void func_8012CA38(GraphicsContext* gfxCtx);
Gfx* Gfx_BranchTexScroll(Gfx** gfxp, u32 x, u32 y, s32 width, s32 height);
void func_8012CB04(Gfx** gfxp, u32 x, u32 y);
Gfx* func_8012CB28(GraphicsContext* gfxCtx, u32 x, u32 y);
Gfx* Gfx_TexScroll(GraphicsContext* gfxCtx, u32 x, u32 y, s32 width, s32 height);
Gfx* Gfx_TwoTexScroll(GraphicsContext* gfxCtx, s32 tile1, u32 x1, u32 y1, s32 width1, s32 height1, s32 tile2, u32 x2,
                      u32 y2, s32 width2, s32 height2);
Gfx* Gfx_TwoTexScrollEnvColor(GraphicsContext* gfxCtx, s32 tile1, u32 x1, u32 y1, s32 width1, s32 height1, s32 tile2,
                              u32 x2, u32 y2, s32 width2, s32 height2, s32 r, s32 g, s32 b, s32 a);
Gfx* Gfx_EnvColor(GraphicsContext* gfxCtx, s32 r, s32 g, s32 b, s32 a);
Gfx* Gfx_PrimColor(GraphicsContext* gfxCtx, s32 lodfrac, s32 r, s32 g, s32 b, s32 a);
void func_8012CF0C(GraphicsContext* gfxCtx, s32 iParm2, s32 iParm3, u8 r, u8 g, u8 b);
void func_8012D374(GraphicsContext* gfxCtx, u8 r, u8 g, u8 b);
void func_8012D40C(f32* param_1, f32* param_2, s16* param_3);
void Room_nop8012D510(GlobalContext* globalCtx, Room* room, UNK_PTR param_3, UNK_TYPE1 param_4);
void Room_DrawType3Mesh(GlobalContext* globalCtx, Room* room, u32 flags);
void Room_DrawType0Mesh(GlobalContext* globalCtx, Room* room, u32 flags);
void Room_DrawType2Mesh(GlobalContext* globalCtx, Room* room, u32 flags);
void func_8012DEE8(GlobalContext* globalCtx, Room* room, u32 flags);
u32 func_8012E254(s32 param_1, GlobalContext* globalCtx);
void func_8012E32C(GlobalContext* globalCtx, Room* room, u32 flags);
void Room_DrawType1Mesh(GlobalContext* globalCtx, Room* room, u32 flags);
void Room_Init(GlobalContext* globalCtx, RoomContext* roomCtx);
u32 Room_AllocateAndLoad(GlobalContext* globalCtx, RoomContext* roomCtx);
s32 Room_StartRoomTransition(GlobalContext* globalCtx, RoomContext* roomCtx, s32 index);
s32 Room_HandleLoadCallbacks(GlobalContext* globalCtx, RoomContext* roomCtx);
void Room_Draw(GlobalContext* globalCtx, Room* room, u32 flags);
void func_8012EBF8(GlobalContext* globalCtx, RoomContext* roomCtx);
s32 func_8012EC80(GlobalContext* globalCtx);
void func_8012ED34(s16 equipment);
u8 func_8012ED78(GlobalContext* globalCtx, s16 equipment);
void func_8012EDE8(s16 arg0, u32 arg1);
s32 func_8012EE34(s16 arg0);
void func_8012EF0C(s16 arg0);
void func_8012F0EC(s16 arg0);
void func_8012F1BC(s16 sceneIndex);
s16 func_8012F22C(s16 sceneIndex);
void func_8012F278(GlobalContext* globalCtx);
s32 Object_Spawn(ObjectContext* objectCtx, s16 id);
void Object_InitBank(GameState* gamestate, ObjectContext* objectCtx);
void Object_UpdateBank(ObjectContext* objectCtx);
s32 Object_GetIndex(ObjectContext* objectCtx, s16 id);
s32 Object_IsLoaded(ObjectContext* objectCtx, s32 index);
void Object_LoadAll(ObjectContext* objectCtx);
void* func_8012F73C(ObjectContext* objectCtx, s32 iParm2, s16 id);
void Scene_HeaderCmdSpawnList(GlobalContext* globalCtx, SceneCmd* cmd);
void Scene_HeaderCmdActorList(GlobalContext* globalCtx, SceneCmd* cmd);
void Scene_HeaderCmdActorCutsceneCamList(GlobalContext* globalCtx, SceneCmd* cmd);
void Scene_HeaderCmdColHeader(GlobalContext* globalCtx, SceneCmd* cmd);
void Scene_HeaderCmdRoomList(GlobalContext* globalCtx, SceneCmd* cmd);
void Scene_HeaderCmdEntranceList(GlobalContext* globalCtx, SceneCmd* cmd);
void Scene_HeaderCmdSpecialFiles(GlobalContext* globalCtx, SceneCmd* cmd);
void Scene_HeaderCmdRoomBehavior(GlobalContext* globalCtx, SceneCmd* cmd);
void Scene_HeaderCmdMesh(GlobalContext* globalCtx, SceneCmd* cmd);
void Scene_HeaderCmdObjectList(GlobalContext* globalCtx, SceneCmd* cmd);
void Scene_HeaderCmdLightList(GlobalContext* globalCtx, SceneCmd* cmd);
void Scene_HeaderCmdPathList(GlobalContext* globalCtx, SceneCmd* cmd);
void Scene_HeaderCmdTransiActorList(GlobalContext* globalCtx, SceneCmd* cmd);
void Door_InitContext(GameState* gamestate, DoorContext* doorCtx);
void Scene_HeaderCmdEnvLightSettings(GlobalContext* globalCtx, SceneCmd* cmd);
s32 Scene_LoadAreaTextures(GlobalContext* globalCtx, s32 fileIndex);
void Scene_HeaderCmdSkyboxSettings(GlobalContext* globalCtx, SceneCmd* cmd);
void Scene_HeaderCmdSkyboxDisables(GlobalContext* globalCtx, SceneCmd* cmd);
void Scene_HeaderCmdTimeSettings(GlobalContext* globalCtx, SceneCmd* cmd);
void Scene_HeaderCmdWindSettings(GlobalContext* globalCtx, SceneCmd* cmd);
void Scene_HeaderCmdExitList(GlobalContext* globalCtx, SceneCmd* cmd);
void Scene_HeaderCmd09(GlobalContext* globalCtx, SceneCmd* cmd);
void Scene_HeaderCmdSoundSettings(GlobalContext* globalCtx, SceneCmd* cmd);
void Scene_HeaderCmdEchoSetting(GlobalContext* globalCtx, SceneCmd* cmd);
void Scene_HeaderCmdAltHeaderList(GlobalContext* globalCtx, SceneCmd* cmd);
void Scene_HeaderCmdCutsceneList(GlobalContext* globalCtx, SceneCmd* cmd);
void Scene_HeaderCmdActorCutsceneList(GlobalContext* globalCtx, SceneCmd* cmd);
void Scene_HeaderCmdMiniMap(GlobalContext* globalCtx, SceneCmd* cmd);
void Scene_HeaderCmd1D(GlobalContext* globalCtx, SceneCmd* cmd);
void Scene_HeaderCmdMiniMapCompassInfo(GlobalContext* globalCtx, SceneCmd* cmd);
void Scene_HeaderCmdSetAreaVisitedFlag(GlobalContext* globalCtx, SceneCmd* cmd);
void Scene_HeaderCmdAnimatedMaterials(GlobalContext* globalCtx, SceneCmd* cmd);
void Scene_SetExitFade(GlobalContext* globalCtx);
s32 Scene_ProcessHeader(GlobalContext* globalCtx, SceneCmd* header);
u16 Entrance_CreateIndex(s32 sceneIndex, s32 spawnIndex, s32 sceneSetup);
u16 Entrance_CreateIndexFromSpawn(s32 spawnIndex);
void Scene_ExecuteDrawConfig(GlobalContext* globalCtx);
void Scene_DrawConfigDefault(GlobalContext* globalCtx);
Gfx* AnimatedMat_TexScroll(GlobalContext* globalCtx, AnimatedMatTexScrollParams* params);
void AnimatedMat_DrawTexScroll(GlobalContext* globalCtx, s32 segment, void* params);
Gfx* AnimatedMat_TwoLayerTexScroll(GlobalContext* globalCtx, AnimatedMatTexScrollParams* params);
void AnimatedMat_DrawTwoTexScroll(GlobalContext* globalCtx, s32 segment, void* params);
void AnimatedMat_SetColor(GlobalContext* globalCtx, s32 segment, F3DPrimColor* primColor, F3DEnvColor* envColor);
void AnimatedMat_DrawColor(GlobalContext* globalCtx, s32 segment, void* params);
s32 AnimatedMat_Lerp(s32 min, s32 max, f32 norm);
void AnimatedMat_DrawColorLerp(GlobalContext* globalCtx, s32 segment, void* params);
f32 Scene_LagrangeInterp(s32 n, f32 x[], f32 fx[], f32 xp);
u8 Scene_LagrangeInterpColor(s32 n, f32 x[], f32 fx[], f32 xp);
void AnimatedMat_DrawColorNonLinearInterp(GlobalContext* globalCtx, s32 segment, void* params);
void AnimatedMat_DrawTexCycle(GlobalContext* globalCtx, s32 segment, void* params);
void AnimatedMat_DrawMain(GlobalContext* globalCtx, AnimatedMaterial* matAnim, f32 alphaRatio, u32 step, u32 flags);
void AnimatedMat_Draw(GlobalContext* globalCtx, AnimatedMaterial* matAnim);
void AnimatedMat_DrawOpa(GlobalContext* globalCtx, AnimatedMaterial* matAnim);
void AnimatedMat_DrawXlu(GlobalContext* globalCtx, AnimatedMaterial* matAnim);
void AnimatedMat_DrawAlpha(GlobalContext* globalCtx, AnimatedMaterial* matAnim, f32 alphaRatio);
void AnimatedMat_DrawAlphaOpa(GlobalContext* globalCtx, AnimatedMaterial* matAnim, f32 alphaRatio);
void AnimatedMat_DrawAlphaXlu(GlobalContext* globalCtx, AnimatedMaterial* matAnim, f32 alphaRatio);
void AnimatedMat_DrawStep(GlobalContext* globalCtx, AnimatedMaterial* matAnim, u32 step);
void AnimatedMat_DrawStepOpa(GlobalContext* globalCtx, AnimatedMaterial* matAnim, u32 step);
void AnimatedMat_DrawStepXlu(GlobalContext* globalCtx, AnimatedMaterial* matAnim, u32 step);
void AnimatedMat_DrawAlphaStep(GlobalContext* globalCtx, AnimatedMaterial* matAnim, f32 alphaRatio, u32 step);
void AnimatedMat_DrawAlphaStepOpa(GlobalContext* globalCtx, AnimatedMaterial* matAnim, f32 alphaRatio, u32 step);
void AnimatedMat_DrawAlphaStepXlu(GlobalContext* globalCtx, AnimatedMaterial* matAnim, f32 alphaRatio, u32 step);
void Scene_DrawConfigMatAnim(GlobalContext* globalCtx);
void Scene_DrawConfig3(GlobalContext* globalCtx);
void Scene_DrawConfig4(GlobalContext* globalCtx);
void Scene_DrawConfigDoNothing(GlobalContext* globalCtx);
void Scene_SetRenderModeXlu(GlobalContext* globalCtx, s32 index, u32 flags);
void Scene_SetCullFlag(GlobalContext* globalCtx, s32 index, u32 flags);
void Scene_DrawConfig5(GlobalContext* globalCtx);
void Scene_DrawConfigMatAnimManualStep(GlobalContext* globalCtx);
void Scene_DrawConfigGreatBayTemple(GlobalContext* globalCtx);
EntranceTableEntry* Entrance_GetTableEntry(u16 entrance);
s32 Entrance_GetSceneNum(u16 entranceIndex);
s32 Entrance_GetSceneNumAbsolute(u16 entranceIndex);
s32 Entrance_GetSpawnNum(u16 entranceIndex);
s32 Entrance_GetTransitionFlags(u16 entranceIndex);
// void func_801323D0(void);
// void func_80132428(void);
// void func_80132494(void);
// void func_801326B8(void);
// void func_801328F0(void);
// void func_80132920(void);
// void func_80132938(void);
// void func_80132954(void);
// void func_8013296C(void);
// void func_80132A18(void);
// void func_80132A3C(void);
// void func_80132A80(void);
// void func_80132AD8(void);
// void func_80132B24(void);
// void func_80132B84(void);
// void func_80132D70(void);
// void func_80132E9C(void);
// void func_80132FDC(void);
// void func_80133000(void);
s32 func_80133038(GlobalContext* globalCtx, UNK_PTR arg1, struct_80133038_arg2* arg2);
void SkelAnime_LodDrawLimb(GlobalContext* globalCtx, s32 limbIndex, void** skeleton, Vec3s* limbDrawTable,
                           OverrideLimbDraw overrideLimbDraw, PostLimbDraw postLimbDraw, Actor* actor, s32 dListIndex);
void SkelAnime_LodDraw(GlobalContext* globalCtx, void** skeleton, Vec3s* limbDrawTable,
                       OverrideLimbDraw overrideLimbDraw, PostLimbDraw postLimbDraw, Actor* actor, s32 dListIndex);
void SkelAnime_LodDrawLimbSV(GlobalContext* globalCtx, s32 limbIndex, void** skeleton, Vec3s* limbDrawTable,
                             OverrideLimbDrawSV overrideLimbDraw, PostLimbDrawSV postLimbDraw, Actor* actor,
                             s32 dListIndex, RSPMatrix** mtx);
void SkelAnime_LodDrawSV(GlobalContext* globalCtx, void** skeleton, Vec3s* limbDrawTable, s32 dListCount,
                         OverrideLimbDrawSV overrideLimbDraw, PostLimbDrawSV postLimbDraw, Actor* actor,
                         s32 dListIndex);
void SkelAnime_DrawLimb(GlobalContext* globalCtx, s32 limbIndex, void** skeleton, Vec3s* limbDrawTable,
                        OverrideLimbDraw overrideLimbDraw, PostLimbDraw postLimbDraw, Actor* actor);
void SkelAnime_Draw(GlobalContext* globalCtx, void** skeleton, Vec3s* limbDrawTable, OverrideLimbDraw overrideLimbDraw,
                    PostLimbDraw postLimbDraw, Actor* actor);
void SkelAnime_DrawLimbSV(GlobalContext* globalCtx, s32 limbIndex, void** skeleton, Vec3s* limbDrawTable,
                          OverrideLimbDraw overrideLimbDraw, PostLimbDraw postLimbDraw, Actor* actor,
                          RSPMatrix** limbMatricies);
void SkelAnime_DrawSV(GlobalContext* globalCtx, void** skeleton, Vec3s* limbDrawTable, s32 dListCount,
                      OverrideLimbDraw overrideLimbDraw, PostLimbDraw postLimbDraw, Actor* actor);
void func_80134148(GlobalContext* globalCtx, s32 limbIndex, void** skeleton, Vec3s* limbDrawTable,
                   OverrideLimbDraw overrideLimbDraw, PostLimbDraw postLimbDraw, UnkActorDraw unkDraw, Actor* actor,
                   RSPMatrix** mtx);
void func_801343C0(GlobalContext* globalCtx, void** skeleton, Vec3s* limbDrawTable, s32 dListCount,
                   OverrideLimbDraw overrideLimbDraw, PostLimbDraw postLimbDraw, UnkActorDraw unkDraw, Actor* actor);
void SkelAnime_AnimateFrame(AnimationHeader* animationSeg, s32 currentFrame, s32 limbCount, Vec3s* dst);
s16 SkelAnime_GetTotalFrames(AnimationHeaderCommon* animationSeg);
s16 SkelAnime_GetFrameCount(AnimationHeaderCommon* animationSeg);
Gfx* SkelAnime_Draw2Limb(GlobalContext* globalCtx, s32 limbIndex, void** skeleton, Vec3s* limbDrawTable,
                         OverrideLimbDraw2 overrideLimbDraw, PostLimbDraw2 postLimbDraw, Actor* actor, Gfx* gfx);
Gfx* SkelAnime_Draw2(GlobalContext* globalCtx, void** skeleton, Vec3s* limbDrawTable,
                     OverrideLimbDraw2 overrideLimbDraw, PostLimbDraw2 postLimbDraw, Actor* actor, Gfx* gfx);
Gfx* SkelAnime_DrawLimbSV2(GlobalContext* globalCtx, s32 limbIndex, void** skeleton, Vec3s* limbDrawTable,
                           OverrideLimbDraw2 overrideLimbDraw, PostLimbDraw2 postLimbDraw, Actor* actor,
                           RSPMatrix** mtx, Gfx* gfx);
Gfx* SkelAnime_DrawSV2(GlobalContext* globalCtx, void** skeleton, Vec3s* limbDrawTable, s32 dListCount,
                       OverrideLimbDraw2 overrideLimbDraw, PostLimbDraw2 postLimbDraw, Actor* actor, Gfx* gfx);
s32 func_80134FFC(s32 arg0, s32 arg1, Vec3s* dst);
s16 func_801353D4(AnimationHeaderCommon* animationSeg);
s16 SkelAnime_GetTotalFrames2(AnimationHeaderCommon* animationSeg);
s16 SkelAnime_GetFrameCount2(AnimationHeaderCommon* animationSeg);
void SkelAnime_InterpolateVec3s(s32 limbCount, Vec3s* dst, Vec3s* vec2, Vec3s* vec3, f32 unkf);
void SkelAnime_AnimationCtxReset(AnimationContext* animationCtx);
void func_801358D4(GlobalContext* globalCtx);
void func_801358F4(GlobalContext* globalCtx);
AnimationEntry* SkelAnime_NextEntry(AnimationContext* animationCtx, AnimationType type);
void SkelAnime_LoadLinkAnimetion(GlobalContext* globalCtx, LinkAnimationHeader* linkAnimetionSeg, s32 frame,
                                 s32 limbCount, void* ram);
void SkelAnime_LoadAnimationType1(GlobalContext* globalCtx, s32 vecCount, Vec3s* dst, Vec3s* src);
void SkelAnime_LoadAnimationType2(GlobalContext* globalCtx, s32 limbCount, Vec3s* arg2, Vec3s* arg3, f32 arg4);
void SkelAnime_LoadAnimationType3(GlobalContext* globalCtx, s32 vecCount, Vec3s* dst, Vec3s* src, u8* index);
void SkelAnime_LoadAnimationType4(GlobalContext* globalCtx, s32 vecCount, Vec3s* dst, Vec3s* src, u8* index);
void SkelAnime_LoadAnimationType5(GlobalContext* globalCtx, Actor* actor, SkelAnime* skelAnime, f32 arg3);
void SkelAnime_LinkAnimetionLoaded(GlobalContext* globalCtx, AnimationEntryType0* entry);
void SkelAnime_AnimationType1Loaded(GlobalContext* globalCtx, AnimationEntryType1* entry);
void SkelAnime_AnimationType2Loaded(GlobalContext* globalCtx, AnimationEntryType2* entry);
void SkelAnime_AnimationType3Loaded(GlobalContext* globalCtx, AnimationEntryType3* entry);
void SkelAnime_AnimationType4Loaded(GlobalContext* globalCtx, AnimationEntryType4* entry);
void SkelAnime_AnimationType5Loaded(GlobalContext* globalCtx, AnimationEntryType5* entry);
void func_80135EE8(GlobalContext* globalCtx, AnimationContext* animationCtx);
void SkelAnime_InitLinkAnimetion(GlobalContext* globalCtx, SkelAnime* skelAnime, FlexSkeletonHeader* skeletonHeaderSeg,
                                 LinkAnimationHeader* linkAnimationHeaderSeg, s32 flags, Vec3s* limbDrawTbl,
                                 Vec3s* transitionDrawTbl, s32 limbBufCount);
void func_801360A8(SkelAnime* skelAnime);
s32 func_801360E0(GlobalContext* globalCtx, SkelAnime* skelAnime);
s32 func_80136104(GlobalContext* globalCtx, SkelAnime* skelAnime);
void func_801361BC(GlobalContext* globalCtx, SkelAnime* skelAnime);
s32 func_80136288(GlobalContext* globalCtx, SkelAnime* skelAnime);
s32 func_8013631C(GlobalContext* globalCtx, SkelAnime* skelAnime);
void SkelAnime_SetTransition(GlobalContext* globalCtx, SkelAnime* skelAnime, f32 transitionRate);
void SkelAnime_ChangeLinkAnim(GlobalContext* globalCtx, SkelAnime* skelAnime,
                              LinkAnimationHeader* linkAnimationHeaderSeg, f32 playbackSpeed, f32 frame, f32 frameCount,
                              u8 animationMode, f32 transitionRate);
void SkelAnime_ChangeLinkAnimDefaultStop(GlobalContext* globalCtx, SkelAnime* skelAnime,
                                         LinkAnimationHeader* linkAnimationHeaderSeg);
void SkelAnime_ChangeLinkAnimPlaybackStop(GlobalContext* globalCtx, SkelAnime* skelAnime,
                                          LinkAnimationHeader* linkAnimationHeaderSeg, f32 playbackSpeed);
void SkelAnime_ChangeLinkAnimDefaultRepeat(GlobalContext* globalCtx, SkelAnime* skelAnime,
                                           LinkAnimationHeader* linkAnimationHeaderSeg);
void SkelAnime_ChangeLinkAnimPlaybackRepeat(GlobalContext* globalCtx, SkelAnime* skelAnime,
                                            LinkAnimationHeader* linkAnimationHeaderSeg, f32 playbackSpeed);
void func_8013670C(GlobalContext* globalCtx, SkelAnime* skelAnime);
void func_8013673C(GlobalContext* globalCtx, SkelAnime* skelAnime);
void func_8013676C(GlobalContext* globalCtx, SkelAnime* skelAnime, LinkAnimationHeader* linkAnimationHeaderSeg,
                   f32 frame);
void func_801367B0(GlobalContext* globalCtx, SkelAnime* skelAnime, LinkAnimationHeader* linkAnimationHeaderSeg,
                   f32 frame);
void func_801367F4(GlobalContext* globalCtx, SkelAnime* skelAnime, f32 frame);
void func_8013682C(GlobalContext* globalCtx, SkelAnime* skelAnime, LinkAnimationHeader* linkAnimationHeaderSeg,
                   f32 transitionFrame, LinkAnimationHeader* LinkAnimationHeaderSeg2, f32 frame, f32 transitionRate,
                   Vec3s* limbDrawTbl);
void func_801368CC(GlobalContext* globalCtx, SkelAnime* skelAnime, LinkAnimationHeader* linkAnimationHeaderSeg,
                   f32 transitionFrame, LinkAnimationHeader* LinkAnimationHeaderSeg2, f32 frame, f32 transitionRate,
                   Vec3s* limbDrawTbl);
void SkelAnime_SetModeStop(SkelAnime* skelAnime);
s32 func_80136990(SkelAnime* skelAnime, f32 arg1, f32 updateRate);
s32 func_80136A48(SkelAnime* skelAnime, f32 arg1);
void SkelAnime_Init(GlobalContext* globalCtx, SkelAnime* skelAnime, SkeletonHeader* skeletonHeaderSeg,
                    AnimationHeader* animationSeg, Vec3s* limbDrawTbl, Vec3s* transitionDrawTable, s32 limbCount);
void SkelAnime_InitSV(GlobalContext* globalCtx, SkelAnime* skelAnime, FlexSkeletonHeader* skeletonHeaderSeg,
                      AnimationHeader* animationSeg, Vec3s* limbDrawTbl, Vec3s* transitionDrawTable, s32 limbCount);
void SkelAnime_InitSkin(GlobalContext* globalCtx, SkelAnime* skelAnime, SkeletonHeader* skeletonHeaderSeg,
                        AnimationHeader* animationSeg);
void func_80136C84(SkelAnime* skelAnime);
s32 SkelAnime_FrameUpdateMatrix(SkelAnime* skelAnime);
s32 func_80136CF4(SkelAnime* skelAnime);
s32 func_80136D98(SkelAnime* skelAnime);
void func_80136F04(SkelAnime* skelAnime);
s32 func_8013702C(SkelAnime* skelAnime);
s32 func_801370B0(SkelAnime* skelAnime);
s32 func_8013713C(SkelAnime* skelAnime);
void SkelAnime_ChangeAnimImpl(SkelAnime* skelAnime, AnimationHeader* animationSeg, f32 playbackSpeed, f32 frame,
                              f32 frameCount, u8 animationType, f32 transitionRate, s8 unk2);
void SkelAnime_ChangeAnim(SkelAnime* skelAnime, AnimationHeader* animationSeg, f32 playbackSpeed, f32 frame,
                          f32 frameCount, u8 mode, f32 transitionRate);
void SkelAnime_ChangeAnimDefaultStop(SkelAnime* skelAnime, AnimationHeader* animationSeg);
void SkelAnime_ChangeAnimTransitionStop(SkelAnime* skelAnime, AnimationHeader* animationSeg, f32 transitionRate);
void SkelAnime_ChangeAnimPlaybackStop(SkelAnime* skelAnime, AnimationHeader* animationSeg, f32 playbackSpeed);
void SkelAnime_ChangeAnimDefaultRepeat(SkelAnime* skelAnime, AnimationHeader* animationSeg);
void SkelAnime_ChangeAnimTransitionRepeat(SkelAnime* skelAnime, AnimationHeader* animationSeg, f32 transitionRate);
void SkelAnime_ChangeAnimPlaybackRepeat(SkelAnime* skelAnime, AnimationHeader* animationSeg, f32 playbackSpeed);
void SkelAnime_AnimSetStop(SkelAnime* skelAnime);
void SkelAnime_AnimReverse(SkelAnime* skelAnime);
void func_80137674(SkelAnime* skelAnime, Vec3s* dst, Vec3s* src, u8* index);
void func_801376DC(SkelAnime* skelAnime, Vec3s* dst, Vec3s* src, u8* arg3);
void func_80137748(SkelAnime* skelAnime, Vec3f* pos, s16 angle);
s32 func_801378B8(SkelAnime* skelAnime, f32 arg1);
void SkelAnime_Free(SkelAnime* skelAnime, GlobalContext* globalCtx);
void SkelAnime_CopyVec3s(SkelAnime* skelAnime, Vec3s* dst, Vec3s* src);
// void func_80137970(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5);
// void func_80137B34(void);
// void func_80137EBC(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5);
// void func_80137F58(void);
// void func_80138050(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5,
// UNK_TYPE4 param_6, UNK_TYPE4 param_7, UNK_TYPE4 param_8); void func_80138228(UNK_TYPE1 param_1, UNK_TYPE1 param_2,
// UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5); void func_80138258(UNK_TYPE1 param_1, UNK_TYPE1 param_2,
// UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6); void func_8013828C(UNK_TYPE1 param_1,
// UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6, UNK_TYPE4 param_7);
// void func_801382C4(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5,
// UNK_TYPE4 param_6, UNK_TYPE4 param_7, UNK_TYPE4 param_8); void func_80138300(void); void func_8013835C(void); void
// func_80138410(void); void func_80138424(void); void func_8013859C(void); void func_80138700(void); void
// func_801387D4(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE1 param_5); void
// func_801388E4(void);
void SkinMatrix_Vec3fMtxFMultXYZW(MtxF* mf, Vec3f* src, Vec3f* xyzDest, f32* wDest);
void SkinMatrix_Vec3fMtxFMultXYZ(MtxF* mf, Vec3f* src, Vec3f* dest);
void SkinMatrix_MtxFMtxFMult(MtxF* mfB, MtxF* mfA, MtxF* dest);
void SkinMatrix_GetClear(MtxF** puParm1);
void SkinMatrix_GetClear(MtxF** mf);
void SkinMatrix_MtxFCopy(MtxF* src, MtxF* dest);
s32 SkinMatrix_Invert(MtxF* src, MtxF* dest);
void SkinMatrix_SetScale(MtxF* mf, f32 x, f32 y, f32 z);
void SkinMatrix_SetRotateRPY(MtxF* mf, s16 roll, s16 pitch, s16 yaw);
void SkinMatrix_SetRotateYRP(MtxF* mf, s16 yaw, s16 roll, s16 pitch);
void SkinMatrix_SetTranslate(MtxF* mf, f32 x, f32 y, f32 z);
void SkinMatrix_SetScaleRotateRPYTranslate(MtxF* mf, f32 scaleX, f32 scaleY, f32 scaleZ, s16 roll, s16 pitch, s16 yaw,
                                           f32 dx, f32 dy, f32 dz);
void SkinMatrix_SetScaleRotateYRPTranslate(MtxF* mf, f32 scaleX, f32 scaleY, f32 scaleZ, s16 yaw, s16 roll, s16 pitch,
                                           f32 dx, f32 dy, f32 dz);
void SkinMatrix_SetRotateRPYTranslate(MtxF* mf, s16 roll, s16 pitch, s16 yaw, f32 dx, f32 dy, f32 dz);
void SkinMatrix_Vec3fToVec3s(Vec3f* src, Vec3s* dest);
void SkinMatrix_Vec3sToVec3f(Vec3s* src, Vec3f* dest);
void SkinMatrix_MtxFToMtx(MtxF* src, Mtx* dest);
Mtx* SkinMatrix_MtxFToNewMtx(GraphicsContext* gfxCtx, MtxF* src);
void SkinMatrix_SetRotateAroundVec(MtxF* mf, s16 a, f32 x, f32 y, f32 z);
void SkinMatrix_SetXRotation(MtxF* mf, s16 a);
void SkinMatrix_MulXRotation(MtxF* mf, s16 a);
void SkinMatrix_SetYRotation(MtxF* mf, s16 a);
void SkinMatrix_MulYRotation(MtxF* mf, s16 a);
void SkinMatrix_SetZRotation(MtxF* mf, s16 a);
s32 func_8013A240(GlobalContext* globalCtx);
void func_8013A41C(s32 flag);
void func_8013A46C(s32 flag);
u32 func_8013A4C4(s32 flag);
s16 func_8013A504(s16 val);
s32 func_8013A530(GlobalContext* globalCtx, Actor* actor, s32 flag, Vec3f* pos, Vec3s* rot, f32 distanceMin,
                  f32 distanceMax, s16 angleError);
// void func_8013A7C0(void);
// void func_8013A860(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6, UNK_TYPE4 param_7, UNK_TYPE4 param_8, UNK_TYPE4 param_9, UNK_TYPE4 param_10);
Gfx* func_8013AB00(GlobalContext* globalCtx, void** skeleton, Vec3s* limbDrawTable, s32 dListCount, void* func1, void* func2, void* func3, Actor* actor, Gfx* gfx);
s32 func_8013AD6C(GlobalContext* globalCtx);
// void func_8013AD9C(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5,
// UNK_TYPE4 param_6);
void func_8013AED4(u16* param_1, u16 param_2, u16 param_3);
void func_8013AF00(UNK_PTR arg0, UNK_TYPE arg1, UNK_TYPE arg2);
// void func_8013B010(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5,
// UNK_TYPE4 param_6, UNK_TYPE4 param_7); void func_8013B0C8(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3,
// UNK_TYPE1 param_4, UNK_TYPE4 param_5); void func_8013B350(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3,
// UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6, UNK_TYPE4 param_7);
s32 func_8013B6B0(Path* path, UNK_PTR arg1, s32* arg2, s32 arg3, s32 arg4, s32* arg5, UNK_PTR arg6, Vec3f* arg7,
                  s16 arg8);
void func_8013B878(GlobalContext* globalCtx, Path* path, s32 arg2, Vec3f* arg3);
Path* func_8013BB34(GlobalContext* globalCtx, u8 arg1, s32 arg2);
Actor* func_8013BB7C(Actor* actor, GlobalContext* globalCtx, s32 actorCategory, s32 actorId);
UNK_TYPE func_8013BC6C(SkelAnime* skelAnime, ActorAnimationEntryS* arg1, s32 arg2);
// void func_8013BD40(void);
// void func_8013BEDC(void);
// void func_8013C068(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5);
// void func_8013C624(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6);
// void func_8013C8B8(void);
void func_8013C964(Actor* actor, GlobalContext* globalCtx, f32 arg2, f32 arg3, s32 arg4, s32 arg5);
// void func_8013CC2C(void);
// void func_8013CD64(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE1 param_5, UNK_TYPE4 param_6, UNK_TYPE4 param_7);
// void func_8013CF04(void);
// void func_8013D0E0(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6);
void func_8013D2E0(Vec3f* arg0, PosRot* arg1, ActorShape* arg2, s16* arg3, s16* arg4, s16* arg5, s16* arg6);
UNK_TYPE func_8013D5E8(s16 arg0, UNK_TYPE arg1, s16 arg2);
Path* func_8013D648(GlobalContext* globalCtx, s16 arg1, s32 arg2);
UNK_TYPE func_8013D68C(Path* path, s16 arg1, UNK_PTR arg2);
// void func_8013D720(void);
UNK_TYPE func_8013D768(Actor* actor, UNK_PTR arg1, s16 arg2);
// void func_8013D83C(void);
// void func_8013D8DC(void);
// void func_8013D924(void);
Actor* func_ActorCategoryIterateById(GlobalContext* globalCtx, struct Actor* actorListStart, s32 actorCategory,
                                     s32 actorId);
void func_8013D9C8(GlobalContext* globalCtx, s16* arg1, s16* arg2, UNK_TYPE arg3);
u8 func_8013DB90(GlobalContext* globalCtx, UNK_PTR arg1, f32 arg2);
// void func_8013DC40(void);
void func_8013DCE0(GlobalContext* globalCtx, Vec3f* param_2, Actor* actor, EnDno_ActorUnkStruct* param_4, Path* param_5, s32 param_6, s32 param_7, s32 param_8, s32 param_9, s32 param_10);
void func_8013DE04(GlobalContext* globalCtx, EnDno_ActorUnkStruct* arg1, EnDno_ActorUnkFunc arg2, EnDno_ActorUnkFunc arg3, EnDno_ActorUnkFunc arg4, EnDno_ActorUnkFunc arg5);
s32 func_8013DF3C(GlobalContext* globalCtx, EnDno_ActorUnkStruct* arg1);
// void func_8013E054(void);
// void func_8013E07C(void);
s32 func_8013E0A4(GlobalContext* globalCtx, EnDno_ActorUnkStruct* arg1);
void func_8013E1C8(SkelAnime* skelAnime, struct_80B8E1A8 animations[], s32 animationIndex, s32* actorAnimationIndex);
s32 func_8013E2D4(Actor* actor, s16 arg1, s32 arg2, s32 arg3);
s32 func_8013E3B8(Actor* actor, s16 cutscenes[], s32 cutsceneArrayLen);
// void func_8013E4B0(void);
s32 func_8013E5CC(Vec3f* param_1, Vec3s* param_2, Vec3f* param_3, Vec3f* param_4, Vec3f* param_5, Vec3f* param_6);
// void func_8013E640(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE2 param_5, UNK_TYPE4 param_6, UNK_TYPE4 param_7);
// void func_8013E748(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6, UNK_TYPE4 param_7);
// void func_8013E7C0(void);
// void func_8013E8F8(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE2 param_6, UNK_TYPE2 param_7);
s32 func_8013E950(Vec3f* param_1, Vec3f* param_2, s16 param_3, Vec3f* param_4, Vec3f* param_5, s16* param_6, s16* param_7, s16* param_8, s16* param_9, u16 param_10, u16 param_11, u16 param_12, u16 param_13);
// void func_8013EC10(void);
// void func_8013EC44(void);
void func_8013ECE0(f32 xyzDistToPlayerSq, u8 arg1, u8 arg2, u8 arg3);
void func_8013ED9C(void);
void func_8013EDD0(void);
// void func_8013EE04(void);
// void func_8013EE24(void);
// void func_8013EE38(void);
// void func_8013EE48(void);
void View_ViewportToVp(Vp* dest, Viewport* src);
void View_Init(View* view, GraphicsContext* gfxCtx);
void View_SetViewOrientation(View* view, Vec3f* eye, Vec3f* at, Vec3f* up);
void func_8013F050(View* view, Vec3f* eye, Vec3f* at, Vec3f* up);
void View_SetScale(View* view, f32 scale);
void View_GetScale(View* view, f32* scale);
void func_8013F0D0(View* view, f32 fovy, f32 zNear, f32 zFar);
void func_8013F100(View* view, f32* fovy, f32* zNear, f32* zFar);
void func_8013F120(View* view, f32 fovy, f32 zNear, f32 zFar);
void func_8013F15C(View* view, f32* fovy, f32* zNear, f32* zFar);
void View_SetViewport(View* view, Viewport* viewport);
void View_GetViewport(View* view, Viewport* viewport);
void View_WriteScissor(Gfx** gfx, s32 ulx, s32 uly, s32 lrx, s32 lry);
void View_SyncAndWriteScissor(View* view, Gfx** gfx);
void View_SetScissorForLetterbox(View* view);
s32 View_SetQuakeRotation(View* view, f32 x, f32 y, f32 z);
s32 View_SetQuakeScale(View* view, f32 x, f32 y, f32 z);
s32 View_SetQuakeSpeed(View* view, f32 speed);
s32 View_InitCameraQuake(View* view);
s32 View_ClearQuake(View* view);
s32 View_SetQuake(View* view, Vec3f rot, Vec3f scale, f32 speed);
s32 View_StepQuake(View* view, RSPMatrix* matrix);
void View_RenderView(View* view, s32 uParm2);
s32 View_RenderToPerspectiveMatrix(View* view);
s32 View_RenderToOrthographicMatrix(View* view);
s32 func_8013FBC8(View* view);
s32 func_8013FD74(View* view);
s32 func_80140024(View* view);
s32 func_801400CC(View* view, Gfx** gfxp);
void func_80140260(OSViMode* vimode);
// void func_8014026C(OSViMode* param_1, UNK_TYPE1 param_2, s32 param_3, s32 param_4, s32 param_5, s32 param_6, s32
// param_7, s32 param_8, UNK_TYPE4 param_9, s32 param_10, s16 param_11, u32 param_12, UNK_TYPE4 param_13); void
// func_80140730(void); void func_80140810(void);
void func_80140898(void* arg0);
void func_80140900(void* arg0);
// void func_8014090C(void);
// void func_80140970(void);
void func_80140CE0(void* arg0);
void func_80140D04(void* arg0);
void func_80140D10(void* arg0, Gfx** gfx, u32 arg2);
void func_80140E80(void* param_1);
// void func_80140EA0(void);
// void func_80140EAC(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5,
// UNK_TYPE4 param_6); void func_80141008(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4,
// UNK_TYPE4 param_5, UNK_TYPE4 param_6, UNK_TYPE4 param_7, UNK_TYPE4 param_8, UNK_TYPE4 param_9, UNK_TYPE4 param_10);
// void func_8014116C(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5,
// UNK_TYPE4 param_6); void func_801411B4(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4,
// UNK_TYPE4 param_5, UNK_TYPE4 param_6, UNK_TYPE4 param_7, UNK_TYPE4 param_8, UNK_TYPE4 param_9, UNK_TYPE4 param_10);
// void func_80141200(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5,
// UNK_TYPE4 param_6); void func_8014151C(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4,
// UNK_TYPE4 param_5, UNK_TYPE4 param_6); void func_80141678(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3,
// UNK_TYPE1 param_4, UNK_TYPE4 param_5); void func_80141778(void);
void func_801418B0(void* arg0);
void func_80141900(void* arg0);
// void func_80141924(void);
// void func_80141C34(void);
void VisMono_Draw(void* arg0, Gfx** gfx, u32 arg2); // VisMono_Draw
// void func_8014204C(void);
void func_801420C0(void* arg0);
void func_801420F4(void* arg0);
void func_80142100(void* arg0, Gfx** gfx, u32 arg2);
s32 func_80142440(SkyboxContext* skyboxCtx, Vtx* vtx, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7,
                  s32 arg8);                                                         // func_80142440
void func_80143148(SkyboxContext* skyboxCtx, s32 arg1);                              // func_80143148
void func_801431E8(GameState* gamestate, SkyboxContext* skyboxCtx, s16 skyType);     // func_801431E8
void func_80143324(GlobalContext* globalCtx, SkyboxContext* skyboxCtx, s16 skyType); // func_80143324
void func_801434E4(GameState* gamestate, SkyboxContext* skyboxCtx, s16 skyType);     // func_801434E4
// void func_801435A0(void);
// void func_80143624(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE1 param_5, UNK_TYPE1 param_6, UNK_TYPE1 param_7);
// void func_80143668(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6, UNK_TYPE4 param_7);
// void func_80143A04(void);
void func_80143A10(u8 owlId);
// void func_80143A54(void);
// void func_80143AC4(void);
void func_80143B0C(GlobalContext* globalCtx);
// void Sram_IncrementDay(void);
u32 Sram_CalcChecksum(u8* data, u32 length);
// void func_80144628(void);
// void Sram_GenerateRandomSaveFields(void);
// void func_80144890(void);
// void func_80144968(void);
// void func_80144A94(void);
// void func_80144E78(void);
// void func_8014546C(void);
// void func_80145698(void);
void func_801457CC(GameState* gamestate, SramContext* param_2);
void func_80146580(s32 param_1, SramContext* param_2, s32 param_3);
// void func_80146628(void);
// void func_80146AA0(void);
// void func_80146DF8(void);
// void func_80146E40(void);
void Sram_Alloc(GameState* gamestate, SramContext* iParm2);
// void func_80146EBC(SramContext* param_1, UNK_TYPE4 param_2, UNK_TYPE4 param_3);
// void func_80146EE8(void);
// void func_80146F5C(void);
// void func_80147008(void);
void func_80147020(SramContext* param_1);
void func_80147068(SramContext* param_1);
// void func_80147138(SramContext* param_1, UNK_TYPE4 param_2, UNK_TYPE4 param_3);
void func_80147150(SramContext* param_1);
void func_80147198(SramContext* param_1);
// void func_80147314(void);
// void func_80147414(void);
// void Sram_nop8014750C(UNK_TYPE4 param_1);
// void func_80147520(void);
void func_80147564(GlobalContext* globalCtx);
u32 func_80147624(GlobalContext* globalCtx);
u32 func_80147734(GlobalContext* globalCtx);
void func_801477B4(GlobalContext* globalCtx);
// void func_80147818(GlobalContext* globalCtx, UNK_PTR puParm2, UNK_TYPE4 uParm3, UNK_TYPE4 uParm4);
// void func_80147F18(GlobalContext* globalCtx, UNK_PTR puParm2, UNK_TYPE4 uParm3, UNK_TYPE4 uParm4);
// void func_80148558(GlobalContext* globalCtx, UNK_PTR puParm2, UNK_TYPE4 uParm3, UNK_TYPE4 uParm4);
void func_80148B98(GlobalContext* globalCtx, u8 bParm2);
// void func_80148CBC(void);
// void func_80148D64(void);
// void func_80149048(void);
// void func_801491DC(void);
// void func_80149454(void);
// void func_801496C8(void);
// void func_8014995C(void);
// void func_80149C18(void);
// void func_80149EBC(void);
void func_80149F74(GlobalContext* globalCtx, u32** ppuParm2);
// void func_8014AAD0(void);
void func_8014ADBC(GlobalContext* globalCtx, UNK_PTR puParm2);
// void func_8014C70C(void);
// void func_8014CC14(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE2 param_5);
// void func_8014CCB4(void);
// void func_8014CDF0(void);
// void func_8014CFDC(void);
// void func_8014D304(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5);
// void func_8014D62C(void);
// void func_8014D7B4(void);
// void func_80150A84(void);
void func_80150D08(GlobalContext* globalCtx, u32 uParm2);
// void func_801514B0(void);
void func_801518B0(GlobalContext* globalCtx, u16 textId, Actor* Actor);
void func_80151938(GlobalContext* globalCtx, u16 textId);
void func_80151A68(GlobalContext* globalCtx, u16 param_2);
void func_80151BB4(GlobalContext* globalCtx, u32 uParm2);
// void func_80151C9C(void);
// void func_80151DA4(void);
void func_80152434(GlobalContext* globalCtx, u16 arg2);
// void func_80152464(void);
u8 func_80152498(MessageContext* msgCtx);
// void func_8015268C(void);
// void func_80152C64(void);
// void func_80152CAC(void);
// void func_80152EC0(void);
// void func_80152FB8(void);
// void func_80153750(void);
// void func_80153E7C(void);
// void func_80153EF0(void);
// void func_801541D4(void);
// void func_80156758(void);
void func_8015680C(GlobalContext* globalCtx);
void func_801586A4(GlobalContext* globalCtx);
void Message_Init(GlobalContext* globalCtx);
void func_801588D0(GlobalContext* globalCtx, s16 param_2);
// void func_80158988(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE2 param_5);
// void func_80158A24(void);
// void func_80158C04(void);
// void func_80158D98(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE2 param_5);
// void func_80158FB0(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5);
// void func_8015926C(void);
// void func_80159438(void);
// void func_8015966C(void);
// void func_8015A144(void);
// void func_8015B198(void);
// void func_8015E750(void);
void func_8015E7EC(GlobalContext* globalCtx, UNK_PTR puParm2);
// void func_8015F8A8(UNK_TYPE4 ctxt);
// void func_80160A90(void);
// void func_80160AF8(void);
// void func_80160B40(void);
// void func_80160B80(void);
// void func_80160BC0(void);
void ShrinkWindow_SetLetterboxTarget(s8 target);
// s32 ShrinkWindow_GetLetterboxTarget(void);
void ShrinkWindow_SetLetterboxMagnitude(s8 magnitude);
s32 ShrinkWindow_GetLetterboxMagnitude(void);
void ShrinkWindow_SetPillarboxTarget(s8 target);
// s32 ShrinkWindow_GetPillarboxTarget(void);
void ShrinkWindow_SetPillarboxMagnitude(u8 magnitude);
// s32 ShrinkWindow_GetPillarboxMagnitude(void);
// void ShrinkWindow_Init(void);
// void ShrinkWindow_Fini(void);
void ShrinkWindow_Step(s32 framerateDivisor);
void ShrinkWindow_Draw(GlobalContext* globalCtx);
// void func_80161180(void);
// void func_8016119C(void);
// void func_8016122C(void);
// void func_801612B8(void);
// void func_80161998(void);
// s32 func_80161BAC(void);
// void func_80161BE0(void);
// void func_80161C0C(void);
// void func_80161C20(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5,
// UNK_TYPE4 param_6); void func_80161E4C(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4,
// UNK_TYPE4 param_5, UNK_TYPE4 param_6); void func_801620CC(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3,
// UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6); void func_8016237C(UNK_TYPE1 param_1, UNK_TYPE1 param_2,
// UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE1 param_5, UNK_TYPE4 param_6); void func_801623E4(UNK_TYPE1 param_1,
// UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6); void
// func_801624EC(void); void func_8016253C(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4,
// UNK_TYPE4 param_5, UNK_TYPE4 param_6); void func_801629BC(void); void func_80162A50(UNK_TYPE1 param_1, UNK_TYPE1
// param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6); void func_80162FF8(void); void
// func_801631DC(void); void func_80163334(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4,
// UNK_TYPE4 param_5, UNK_TYPE4 param_6); void func_80163660(void); void func_80163700(void); void func_80163758(void);
// void func_801637B4(void);
void func_80163804(GlobalContext* globalCtx);
// void func_8016388C(void);
// void func_801638D8(void);
// void func_801639A0(void);
void func_801639EC(GlobalContext* globalCtx);
void func_80163A38(GlobalContext* globalCtx);
// void func_80163A58(void);
// void func_80163C0C(void);
// void func_80163C90(void);
// void func_80163D80(void);
// void func_80163DC0(void);
// void func_8016418C(void);
// void func_8016424C(void);
// void func_801642D8(void);
// void func_80164438(void);
// void func_8016454C(void);
// void func_80164678(void);
// void func_801647AC(void);
// UNK_TYPE4 func_801647B8(void);
// void TransitionFade_Start(void);
void* TransitionFade_Init(void* param_1);
// void TransitionFade_Destroy(void);
// void TransitionFade_Update(void);
// void TransitionFade_Draw(void);
// void TransitionFade_IsDone(void);
// void TransitionFade_SetColor(void);
// void TransitionFade_SetType(void);
// void TransitionCircle_Start(void);
// void TransitionCircle_Init(void);
// void TransitionCircle_Destroy(void);
// void TransitionCircle_Update(void);
// void TransitionCircle_SetColor(void);
// void TransitionCircle_SetType(void);
// void func_80164C14(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5,
// UNK_TYPE4 param_6, UNK_TYPE4 param_7); void TransitionCircle_Draw(void); void TransitionCircle_IsDone(void); void
// func_801651B0(void); void func_80165224(void); void func_80165288(void); void func_8016537C(void);
void func_80165438(UNK_PTR param_1);
// void func_80165444(s32 param_1, UNK_TYPE4 param_2, UNK_TYPE4 param_3, UNK_TYPE4 param_4, UNK_TYPE4 param_5);
// void func_80165460(void);
// void func_80165608(void);
// void func_80165630(void);
// void func_80165658(void);
// void func_8016566C(void);
// void func_80165690(void);
// void func_801656A4(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5,
// UNK_TYPE4 param_6, UNK_TYPE4 param_7, UNK_TYPE4 param_8); void func_80165DCC(void); void func_80165DF0(void); void
// func_80165E1C(void); void func_80165E7C(void); void func_80165EC0(void); void func_80166060(void);
Gfx* func_801660B8(GlobalContext* globalCtx, Gfx* gfx);
void Play_Fini(GlobalContext* globalCtx);
// void func_801663C4(void);
// void func_80166644(void);
// void func_801668B4(void);
void func_80166968(GlobalContext* globalCtx, Camera* camera);
void func_80166B30(GlobalContext* globalCtx);
void func_80167814(GlobalContext* globalCtx);
void func_80167DE4(GlobalContext* globalCtx);
// void func_80167F0C(void);
void func_80168090(GlobalContext* globalCtx);
void func_80168DAC(GlobalContext* globalCtx);
void Play_Update(GlobalContext* globalCtx);
s32 func_801690CC(GlobalContext* globalCtx);
// void func_80169100(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5);
// void func_801691F0(void);
void* Play_LoadScene(GlobalContext* globalCtx, RomFile* entry);
void func_8016927C(GlobalContext* globalCtx, s16 sParm2);
// void func_801692C4(GlobalContext* globalCtx, UNK_TYPE1 uParm2);
// void Play_SceneInit(GlobalContext* globalCtx, s32 sceneIndex, UNK_TYPE1 param_3);
UNK_RET func_80169474(GlobalContext* globalCtx, Vec3f* v1, Vec3f* v2);
s32 func_801694DC(GlobalContext* globalCtx);
s32 Play_GetActiveCameraIndex(GlobalContext* globalCtx);
void func_80169590(GlobalContext* globalCtx, s16 param_2, s16 param_3);
void func_80169600(GlobalContext* globalCtx, s16 param_2);
// void func_80169668(void);
Camera* Play_GetCamera(GlobalContext* globalCtx, s16 index);
s32 func_8016970C(GlobalContext* globalCtx, s16 camId, Vec3f* at, Vec3f* eye);
// void func_8016981C(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5);
// void func_80169940(void);
// void func_80169988(void);
void func_801699D4(GlobalContext* globalCtx, s16 arg1, s16 arg2);
// void func_80169A50(void);
// void func_80169AC0(void);
void func_80169AFC(GlobalContext* globalCtx, s16 camId, s16 arg2);
// void func_80169C64(void);
// void func_80169C84(void);
// void convert_scene_number_among_shared_scenes(void);
void func_80169D40(GlobalContext* globalCtx);
void func_80169DCC(GlobalContext* globalCtx, s32 arg1, u16 arg2, s32 arg3, s32 arg4, Vec3f* arg5, s16 arg6);
void func_80169E6C(GlobalContext* globalCtx, s32 param_1, s32 param_2);
// void func_80169ECC(void);
void func_80169EFC(GlobalContext* globalCtx);
// void func_80169F78(void);
// void func_80169FDC(void);
// void func_80169FFC(void);
s32 FrameAdvance_IsEnabled(GlobalContext* globalCtx);
// UNK_TYPE4 func_8016A02C(s32 param_1, s32 param_2, s16* param_3);
// void func_8016A0AC(void);
// void func_8016A168(void);
// void func_8016A178(void);
// void func_8016A268(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE1 param_5,
// UNK_TYPE1 param_6);
void Play_Init(GlobalContext* globalCtx);
// void func_8016AC10(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5,
// UNK_TYPE4 param_6, UNK_TYPE4 param_7, UNK_TYPE4 param_8, UNK_TYPE4 param_9, UNK_TYPE4 param_10); void
// func_8016AE1C(void); void func_8016B278(void); void func_8016B4B0(void); void func_8016C344(void); void
// func_8016CD4C(void); void func_8016E40C(void); void func_8016EA90(void); void func_8016F1A8(void); void
// func_8016F4EC(void);
void func_8016F5A8(GlobalContext* globalCtx, s8* pcParm2, Input* iParm3);
// void func_8016FC78(void);
// void func_8016FC98(void);
void PreRender_SetValuesSave(PreRender* this, u32 width, u32 height, void* fbuf, void* zbuf, void* cvg);
void PreRender_Init(PreRender* this);
void PreRender_SetValues(PreRender* this, u32 width, u32 height, void* fbuf, void* zbuf);
void PreRender_Destroy(PreRender* this);
void func_8016FDB8(PreRender* this, Gfx** gfxp, void* buf, void* bufSave, u32 arg4);
void func_8016FF70(PreRender* this, Gfx** gfxp, void* buf, void* bufSave);
void func_8016FF90(PreRender* this, Gfx** gfxp, void* buf, void* bufSave, s32 envR, s32 envG, s32 envB, s32 envA);
void func_80170200(PreRender* this, Gfx** gfxp, void* buf, void* bufSave);
void func_8017023C(PreRender* this, Gfx** gfxp, void* buf, void* bufSave);
void func_8017057C(PreRender* this, Gfx** gfxp);
void func_801705B4(PreRender* this, Gfx** gfxp);
void func_801705EC(PreRender* this, Gfx** gfxp);
void func_80170730(PreRender* this, Gfx** gfxp);
void func_80170774(PreRender* this, Gfx** gfxp);
void func_80170798(PreRender* this, Gfx** gfxp);
void func_80170AE0(PreRender* this, Gfx** gfxp, s32 alpha);
void func_80170B28(PreRender* this, Gfx** gfxp);
void PreRender_AntiAliasAlgorithm(PreRender* this, s32 x, s32 y);
void PreRender_ApplyAntiAliasingFilter(PreRender* this);
u32 func_801716C4(u8* arg0, u8* arg1, u8* arg2);
void func_801717F8(PreRender* this);
void PreRender_ApplyFilters(PreRender* this);
void PreRender_ApplyFiltersSlowlyInit(PreRender* this);
void PreRender_ApplyFiltersSlowlyDestroy(PreRender* this);
void func_801720C4(PreRender* this);
void func_801720FC(PreRenderParams* params, Gfx** gfxp);
void func_80172758(Gfx** gfxp, void* timg, void* tlut, u16 width, u16 height, u8 fmt, u8 siz, u16 tt, u16 arg8, f32 x,
                   f32 y, f32 xScale, f32 yScale, u32 flags);
void THGA_Ct(TwoHeadGfxArena* thga, Gfx* start, u32 size);
void THGA_Dt(TwoHeadGfxArena* thga);
u32 THGA_IsCrash(TwoHeadGfxArena* thga);
void THGA_Init(TwoHeadGfxArena* thga);
s32 THGA_GetSize(TwoHeadGfxArena* thga);
Gfx* THGA_GetHead(TwoHeadGfxArena* thga);
void THGA_SetHead(TwoHeadGfxArena* thga, Gfx* start);
Gfx* THGA_GetTail(TwoHeadGfxArena* thga);
Gfx* THGA_AllocStartArray8(TwoHeadGfxArena* thga, u32 count);
Gfx* THGA_AllocStart8(TwoHeadGfxArena* thga);
Gfx* THGA_AllocStart8Wrapper(TwoHeadGfxArena* thga);
Gfx* THGA_AllocEnd(TwoHeadGfxArena* thga, u32 size);
Gfx* THGA_AllocEndArray64(TwoHeadGfxArena* thga, u32 count);
Gfx* THGA_AllocEnd64(TwoHeadGfxArena* thga);
Gfx* THGA_AllocEndArray16(TwoHeadGfxArena* thga, u32 count);
Gfx* THGA_AllocEnd16(TwoHeadGfxArena* thga);
void* THA_GetHead(TwoHeadArena* tha);
void THA_SetHead(TwoHeadArena* tha, void* start);
void* THA_GetTail(TwoHeadArena* tha);
void* THA_AllocStart(TwoHeadArena* tha, u32 size);
void* THA_AllocStart1(TwoHeadArena* tha);
void* THA_AllocEnd(TwoHeadArena* tha, u32 size);
void* THA_AllocEndAlign16(TwoHeadArena* tha, u32 size);
void* THA_AllocEndAlign(TwoHeadArena* tha, u32 size, u32 mask);
s32 THA_GetSize(TwoHeadArena* tha);
u32 THA_IsCrash(TwoHeadArena* tha);
void THA_Init(TwoHeadArena* tha);
void THA_Ct(TwoHeadArena* tha, void* ptr, u32 size);
void THA_Dt(TwoHeadArena* tha);
void func_80172BC0(void);
void func_80172C30(AudioMgr* audioMgr);
void AudioMgr_HandleRetrace(AudioMgr* audioMgr);
void AudioMgr_HandlePRENMI(AudioMgr* audioMgr);
void AudioMgr_ThreadEntry(void* arg);
void AudioMgr_Unlock(AudioMgr* audioMgr);
void AudioMgr_Init(AudioMgr* audioMgr, void* stack, OSPri pri, OSId id, SchedContext* sched, IrqMgr* irqMgr);
void TitleSetup_GameStateResetContext(void);
void TitleSetup_InitImpl(GameState* gameState);
void TitleSetup_Destroy(GameState* gameState);
void TitleSetup_Init(GameState* gameState);
void Game_UpdateFramerateVariables(s32 divisor);
void Game_SetFramerateDivisor(GameState* gameState, s32 divisor);
void GameState_SetFBFilter(Gfx** gfx, u32 arg1);
void Game_Nop80173534(GameState* gamestate);
void GameState_Draw(GameState* gamestate, GraphicsContext* gfxCtx);
void Game_ResetSegments(GraphicsContext* gfxCtx);
void func_801736DC(GraphicsContext* gfxCtx);
void Game_UpdateInput(GameState* gamestate);
void Game_Update(GameState* gamestate);
void Game_IncrementFrameCount(GameState* gamestate);
void Game_InitHeap(GameState* gamestate, u32 size);
void Game_ResizeHeap(GameState* gamestate, u32 size);
void Game_StateInit(GameState* gamestate, GameStateFunc gameStateInit, GraphicsContext* gfxCtx);
void Game_StateFini(GameState* gamestate);
GameStateFunc Game_GetNextStateInit(GameState* gamestate);
u32 Game_GetNextStateSize(GameState* gamestate);
u32 Game_GetShouldContinue(GameState* gamestate);
s32 Game_GetHeapFreeSize(GameState* gamestate);
s32 func_80173B48(GameState* gamestate);
GameAlloc* func_80173BF0(GameAlloc* heap);
void* Gamealloc_Alloc(GameAlloc* heap, u32 size);
void Gamealloc_Free(GameAlloc* heap, void* ptr);
void Gamealloc_FreeAll(GameAlloc* heap);
void Gamealloc_Init(GameAlloc* iParm1);
// void Graph_FaultClient(void);
void Graph_DlAlloc(TwoHeadGfxArena* dl, void* memoryBlock, u32 size);
void Graph_InitTHGA(GraphicsContext* gfxCtx);
GameStateOverlay* Graph_GetNextGameState(GameState* gamestate);
void* Graph_FaultAddrConvFunc(void* addr);
void Graph_Init(GraphicsContext* gfxCtx);
// void Graph_Destroy(void);
void Graph_Render(GraphicsContext* gfxCtx, GameState* gamestate);
void Graph_FrameSetup(GameState* gamestate);
void Graph_RenderFrame(GraphicsContext* gfxCtx, GameState* gamestate);
void Graph_DoFrame(GraphicsContext* gfxCtx, GameState* gamestate);
void Graph_ThreadEntry(void* arg);
Gfx* Graph_GfxPlusOne(Gfx* gfx);
Gfx* Graph_BranchDlist(Gfx* gfx, Gfx* dst);
void* Graph_DlistAlloc(Gfx** gfx, u32 size);
void func_80174AA0(ListAlloc* alloc);
// void func_80174AB4(void);
// void func_80174B20(void);
void func_80174BA0(ListAlloc* alloc);
void Main(void* arg);
// u32 Padmgr_GetControllerBitmask(void);
// void func_80174F24(void);
// void func_80174F44(void);
// void func_80174F7C(void);
// void func_80174F9C(void);
// OSMesgQueue* Padmgr_GetEventCallback(void);
// void func_80175008(void);
void Padmgr_SetEventCallback(OSMesg pvParm1);
// void func_8017506C(void);
// void Padmgr_Lock(void);
// void Padmgr_Unlock(void);
// void func_801750FC(void);
// void func_80175364(void);
// void func_80175434(void);
// void func_8017544C(void);
// void func_80175474(void);
// void func_801754C0(void);
void Padmgr_CalcStickEdges(Input* input);
// void Padmgr_ParseState(void);
// void func_801759BC(void);
// void func_80175AE0(void);
// void Padmgr_Update(void);
// void Padmgr_Stop(void);
void func_80175E68(Input* input, s32 param_2);
void Padmgr_GetInput(Input* input, s32 param_2);
void Padmgr_GetInput2(Input* input, s32 param_2);
void Padmgr_ThreadEntry(PadMgr* padmgr);
void Padmgr_Start(OSMesgQueue* siEventCallbackQueue, IrqMgr* irqmgr, OSId threadId, OSPri threadPri, void* stack);
void Sched_SwapFramebuffer(CfbInfo* cfbInfo);
void Sched_RetraceUpdateFramebuffer(SchedContext* sched, CfbInfo* cfbInfo);
void Sched_HandleReset(SchedContext* sched);
void Sched_HandleStop(SchedContext* sched);
void Sched_HandleAudioCancel(SchedContext* sched);
void Sched_HandleGfxCancel(SchedContext* sched);
void Sched_QueueTask(SchedContext* sched, OSScTask* task);
void Sched_Yield(SchedContext* sched);
s32 Sched_Schedule(SchedContext* sched, OSScTask** spTask, OSScTask** dpTask, s32 state);
void Sched_TaskUpdateFramebuffer(SchedContext* sched, OSScTask* task);
void Sched_NotifyDone(SchedContext* sched, OSScTask* task);
void Sched_RunTask(SchedContext* sched, OSScTask* spTask, OSScTask* dpTask);
void Sched_HandleEntry(SchedContext* sched);
void Sched_HandleRetrace(SchedContext* sched);
void Sched_HandleRSPDone(SchedContext* sched);
void Sched_HandleRDPDone(SchedContext* sched);
void Sched_SendEntryMsg(SchedContext* sched);
void Sched_SendAudioCancelMsg(SchedContext* sched);
void Sched_SendGfxCancelMsg(SchedContext* sched);
void Sched_FaultClient(void* param1, void* param2);
void Sched_ThreadEntry(void* arg);
void Sched_Init(SchedContext* sched, void* stack, OSPri pri, UNK_TYPE arg3, UNK_TYPE arg4, IrqMgr* irqMgr);
// void func_80177390(void);
void func_801773A0(void* arg0);
void func_801773C4(void* arg0);
void SpeedMeter_DrawTimeEntries(void* displayList, GraphicsContext* gCtx);
// void func_80177A84(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE2 param_5, UNK_TYPE4 param_6, UNK_TYPE4 param_7, UNK_TYPE4 param_8, UNK_TYPE4 param_9);
// void func_80177AC8(void);
void SpeedMeter_DrawAllocEntries(void* displayList, GraphicsContext* gfxCtx, GameState* gameState);
void func_801780F0(Mtx* param_1, f32 param_2, f32 param_3, f32 param_4, f32 param_5, f32 param_6, f32 param_7);
// void func_801781EC(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5);
// void func_8017842C(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE2 param_5, UNK_TYPE4 param_6, UNK_TYPE4 param_7, UNK_TYPE4 param_8, UNK_TYPE4 param_9, UNK_TYPE4 param_10, UNK_TYPE4 param_11);
// void func_80178750(void);
// void func_80178818(void);
// void func_80178978(void);
// void func_801789D4(void);
u32* get_framebuffer(s32 index);
// u16* get_zbuffer(void);
// UNK_TYPE4 func_80178A24(void);
// void func_80178A34(void);
s32 func_80178A94(s32 param_1, s32 param_2);
// void func_80178AC0(void);
// void func_80178C80(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5);
// void func_80178D7C(void);
// void func_80178DAC(void);
// void func_80178E3C(void);
// void func_80178E7C(void);
void Check_WriteRGBA16Pixel(u16* buffer, u32 x, u32 y, u16 value);
void Check_WriteI4Pixel(u16* buffer, u32 x, u32 y, u32 value);
void Check_DrawI4Texture(u16* buffer, u32 x, u32 y, u32 width, u32 height, u8* texture);
void Check_ClearRGBA16(s16* buffer);
// void Check_DrawExpansionPakErrorMessage(void);
// void Check_DrawRegionLockErrorMessage(void);
// void Check_ExpansionPak(void);
// void Check_RegionIsSupported(void);
f32 func_80179300(f32 param_1);
f32 func_80179400(s32 param_1);
f32 pow_int(f32 x, s32 pow);
f32 sin_rad(f32 rad);
f32 cos_rad(f32 rad);
f32 Rand_ZeroFloat(f32 scale);
f32 randPlusMinusPoint5Scaled(f32 scale);
f32 Math3D_Normalize(Vec3f* vec);
// UNK_TYPE4 func_80179678(f32 fParm1, f32 fParm2, f32 fParm5, f32 param_4, f32 param_5, f32 param_6, f32 param_7,
// UNK_TYPE4 param_8, UNK_TYPE4 param_9, UNK_TYPE4 param_10, UNK_TYPE4 param_11); UNK_TYPE4 func_80179798(Vec3f*
// param_1, Vec3f* param_2, Vec3f* param_3, Vec3f* param_4, Vec3f* param_5, Vec3f* param_6); void func_80179A44(void);
void func_80179B34(float fParm1, f32 fParm2, f32 fParm5, f32 fParm6, f32 param_5, f32 param_6, f32 param_7,
                   float* param_8, float* param_9);
// UNK_TYPE4 func_80179B94(f32 fParm1, f32 fParm2, f32 fParm5, f32 param_4, f32 param_5, f32 param_6, f32 param_7, f32
// param_8, Vec3f* param_9); void func_80179D74(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1
// param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6, UNK_TYPE4 param_7, UNK_TYPE4 param_8, UNK_TYPE4 param_9, UNK_TYPE4
// param_10);
void Math3D_ScaleAndAdd(Vec3f* a, Vec3f* b, f32 scale, Vec3f* dst);
void Math3D_Lerp(Vec3f* a, Vec3f* b, f32 t, Vec3f* dst);
s32 Math3D_Parallel(Vec3f* a, Vec3f* b);
s32 Math3D_AngleBetweenVectors(Vec3f* a, Vec3f* b, f32* angle);
void func_80179F64(Vec3f* param_1, Vec3f* param_2, Vec3f* param_3);
s32 Math3D_XZBoundCheck(f32 xMin, f32 xMax, f32 zMin, f32 zMax, f32 x, f32 z);
// void func_8017A09C(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5,
// UNK_TYPE4 param_6); void func_8017A1D0(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4,
// UNK_TYPE4 param_5, UNK_TYPE4 param_6); void func_8017A304(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3,
// UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6); UNK_TYPE4 func_8017A438(Vec3f* pfParm1, Vec3f* pfParm2,
// Vec3f* pfParm3, Vec3f* pfParm4, f32 param_5);
f32 Math3D_XZLengthSquared(f32 x, f32 z);
f32 Math3D_XZLength(f32 x, f32 z);
f32 Math3D_XZDistanceSquared(f32 x1, f32 x2, f32 z1, f32 z2);
f32 Math3D_XZDistance(f32 x1, f32 x2, f32 z1, f32 z2);
f32 Math3D_LengthSquared(Vec3f* vec);
f32 Math3D_Vec3fMagnitude(Vec3f* vec);
f32 Math3D_DistanceSquared(Vec3f* a, Vec3f* b);
f32 Math3D_Distance(Vec3f* a, Vec3f* b);
f32 Math3D_DistanceS(Vec3s* s, Vec3f* f);
f32 func_8017A7B8(f32* param_1, f32* param_2, f32 param_3, f32 param_4);
f32 func_8017A7F8(f32* param_1, f32* param_2, f32 param_3, f32 param_4);
f32 func_8017A838(f32* param_1, f32* param_2, f32 param_3, f32 param_4);
void Math3D_CrossProduct(Vec3f* a, Vec3f* b, Vec3f* res);
void Math3D_NormalVector(Vec3f* a, Vec3f* b, Vec3f* c, Vec3f* res);
u32 func_8017A954(Vec3f* param_1, Vec3f* param_2, Vec3f* param_3);
u32 func_8017AA0C(Vec3f* param_1, Vec3f* param_2, Vec3f* param_3);
u32 func_8017ABBC(Vec3f* param_1, Vec3f* param_2, Vec3f* param_3);
// void func_8017AD38(void);
// void func_8017B68C(void);
void func_8017B7F8(Vec3f* arg0, s16 arg1, f32* arg2, f32* arg3, f32* arg4);
void Math3D_UnitNormalVector(Vec3f* a, Vec3f* b, Vec3f* c, f32* normX, f32* normY, f32* normZ, f32* param_7);
f32 Math3D_SignedDistanceFromPlane(f32 normX, f32 normY, f32 normZ, f32 d, Vec3f* position);
// void func_8017B9D8(void);
f32 Math3D_NormalizedDistanceFromPlane(f32 normX, f32 normY, f32 normZ, f32 d, Vec3f* position);
f32 Math3D_NormalizedSignedDistanceFromPlane(f32 normX, f32 normY, f32 normZ, f32 d, Vec3f* position);
// void func_8017BAD0(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5,
// UNK_TYPE4 param_6, UNK_TYPE4 param_7, UNK_TYPE4 param_8); void func_8017BD98(UNK_TYPE1 param_1, UNK_TYPE1 param_2,
// UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6, UNK_TYPE4 param_7); void
// func_8017BDE0(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5); void
// func_8017BE30(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5,
// UNK_TYPE4 param_6, UNK_TYPE4 param_7, UNK_TYPE4 param_8, UNK_TYPE4 param_9, UNK_TYPE4 param_10, UNK_TYPE4 param_11);
// void func_8017BEE0(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5,
// UNK_TYPE4 param_6, UNK_TYPE4 param_7, UNK_TYPE4 param_8, UNK_TYPE4 param_9, UNK_TYPE4 param_10, UNK_TYPE4 param_11);
// void func_8017BF8C(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5,
// UNK_TYPE4 param_6); void func_8017C008(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4,
// UNK_TYPE4 param_5, UNK_TYPE4 param_6, UNK_TYPE4 param_7, UNK_TYPE4 param_8, UNK_TYPE4 param_9, UNK_TYPE4 param_10,
// UNK_TYPE4 param_11, UNK_TYPE4 param_12); void func_8017C17C(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3,
// UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6, UNK_TYPE4 param_7); void func_8017C1F0(UNK_TYPE1 param_1,
// UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6, UNK_TYPE4 param_7,
// UNK_TYPE4 param_8); void func_8017C494(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4,
// UNK_TYPE4 param_5, UNK_TYPE4 param_6, UNK_TYPE4 param_7, UNK_TYPE4 param_8, UNK_TYPE4 param_9, UNK_TYPE4 param_10,
// UNK_TYPE4 param_11); void func_8017C540(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4,
// UNK_TYPE4 param_5, UNK_TYPE4 param_6, UNK_TYPE4 param_7, UNK_TYPE4 param_8); void func_8017C808(UNK_TYPE1 param_1,
// UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6, UNK_TYPE4 param_7);
// void func_8017C850(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5,
// UNK_TYPE4 param_6, UNK_TYPE4 param_7, UNK_TYPE4 param_8, UNK_TYPE4 param_9, UNK_TYPE4 param_10); void
// func_8017C904(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5,
// UNK_TYPE4 param_6); void func_8017C980(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4,
// UNK_TYPE4 param_5, UNK_TYPE4 param_6, UNK_TYPE4 param_7, UNK_TYPE4 param_8, UNK_TYPE4 param_9, UNK_TYPE4 param_10,
// UNK_TYPE4 param_11, UNK_TYPE4 param_12); void func_8017CB08(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3,
// UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6, UNK_TYPE4 param_7); void func_8017CB7C(UNK_TYPE1 param_1,
// UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6, UNK_TYPE4 param_7,
// UNK_TYPE4 param_8); void func_8017CEA8(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4,
// UNK_TYPE4 param_5, UNK_TYPE4 param_6, UNK_TYPE4 param_7); void func_8017CEF0(UNK_TYPE1 param_1, UNK_TYPE1 param_2,
// UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6, UNK_TYPE4 param_7, UNK_TYPE4 param_8,
// UNK_TYPE4 param_9, UNK_TYPE4 param_10); void func_8017CFA4(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3,
// UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6); void func_8017D020(UNK_TYPE1 param_1, UNK_TYPE1 param_2,
// UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6, UNK_TYPE4 param_7, UNK_TYPE4 param_8,
// UNK_TYPE4 param_9, UNK_TYPE4 param_10, UNK_TYPE4 param_11, UNK_TYPE4 param_12); void func_8017D1AC(UNK_TYPE1 param_1,
// UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6, UNK_TYPE4 param_7);
// void func_8017D220(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5);
// void func_8017D2FC(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5,
// UNK_TYPE4 param_6, UNK_TYPE4 param_7, UNK_TYPE4 param_8); void func_8017D404(UNK_TYPE1 param_1, UNK_TYPE1 param_2,
// UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6, UNK_TYPE4 param_7, UNK_TYPE4 param_8,
// UNK_TYPE4 param_9, UNK_TYPE4 param_10, UNK_TYPE4 param_11);
void Math3D_TriSetCoords(TriNorm* tri, Vec3f* pointA, Vec3f* pointB, Vec3f* pointC);
u32 Math3D_IsPointInSphere(Sphere16* sphere, Vec3f* point);
s32 Math3D_PointDistToLine2D(f32 arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, f32* arg6, f32* arg7, f32* arg8); // returns boolean
// void func_8017D7C0(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6, UNK_TYPE4 param_7);
// void func_8017D814(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5);
// void func_8017D91C(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5);
// void func_8017DA24(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5);
s32 Math3D_ColSphereLineSeg(Sphere16* sphere, LineSegment* line);
void func_8017DD34(Sphere16* sphere, TriNorm* tri, Vec3f* pfParm3);
s32 Math3D_ColSphereTri(Sphere16* sphere, TriNorm* tri, Vec3f* uParm3);
// void func_8017E294(void);
UNK_TYPE func_8017E350(UNK_PTR, Vec3f*, Vec3f*, Vec3f*, Vec3f*);
s32 Math3D_ColCylinderTri(Cylinder16* cylinder, TriNorm* tri, Vec3f* pzParm3);
// void func_8017F1A0(void);
s32 Math3D_ColSphereSphere(Sphere16* sphere1, Sphere16* sphere2);
s32 Math3D_ColSphereSphereIntersect(Sphere16* sphere1, Sphere16* sphere2, f32* intersectAmount);
s32 Math3D_ColSphereSphereIntersectAndDistance(Sphere16* sphere1, Sphere16* sphere2, f32* intersectAmount, f32* dist);
s32 Math3D_ColSphereCylinderDistance(Sphere16* sphere, Cylinder16* cylinder, f32* dist);
s32 Math3D_ColSphereCylinderDistanceAndAmount(Sphere16* sphere, Cylinder16* cylinder, f32* dist, f32* intersectAmount);
s32 Math3D_ColCylinderCylinderAmount(Cylinder16* cylinder1, Cylinder16* cylinder2, f32* intersectAmount);
s32 Math3D_ColCylinderCylinderAmountAndDistance(Cylinder16* cylinder1, Cylinder16* cylinder2, f32* intersectAmount,
                                                f32* dist);
s32 Math3d_ColTriTri(TriNorm* tri1, TriNorm* tri2, Vec3f* uParm3);
// void func_8017F9C0(void);
// void func_8017FA34(void);
// void func_8017FAA8(void);
// void func_8017FB1C(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5,
// UNK_TYPE4 param_6, UNK_TYPE4 param_7, UNK_TYPE4 param_8, UNK_TYPE4 param_9, UNK_TYPE4 param_10, UNK_TYPE4 param_11);
// void func_8017FD44(void);
u16 Math_GetAtan2Tbl(f32 opposite, f32 adjacent);
s16 Math_Atan2S(f32 opposite, f32 adjacent);
f32 Math_Atan2F(f32 opposite, f32 adjacent);
s16 Math_FAtan2F(f32 adjacent, f32 opposite);
f32 Math_Acot2F(f32 adjacent, f32 opposite);
void SysMatrix_StateAlloc(GameState* gamestate);
void SysMatrix_StatePush(void);
void SysMatrix_StatePop(void);
void SysMatrix_CopyCurrentState(MtxF* matrix);
void SysMatrix_SetCurrentState(MtxF* matrix);
MtxF* SysMatrix_GetCurrentState(void);
void SysMatrix_InsertMatrix(MtxF* matrix, s32 appendToState);
void SysMatrix_InsertTranslation(f32 x, f32 y, f32 z, s32 appendToState);
void Matrix_Scale(f32 xScale, f32 yScale, f32 zScale, s32 appendToState);
void SysMatrix_InsertXRotation_s(s16 rotation, s32 appendToState);
void SysMatrix_InsertXRotation_f(f32 rotation, s32 appendToState);
void SysMatrix_RotateStateAroundXAxis(f32 rotation);
void SysMatrix_SetStateXRotation(f32 rotation);
void Matrix_RotateY(s16 rotation, u8 appendToState);
void SysMatrix_InsertYRotation_f(f32 rotation, s32 appendToState);
void SysMatrix_InsertZRotation_s(s16 rotation, s32 appendToState);
void SysMatrix_InsertZRotation_f(f32 rotation, s32 appendToState);
void SysMatrix_InsertRotation(s16 xRotation, s16 yRotation, s16 zRotation, s32 appendToState);
void SysMatrix_RotateAndTranslateState(Vec3f* translation, Vec3s* rotation);
void SysMatrix_SetStateRotationAndTranslation(f32 x, f32 y, f32 z, Vec3s* rotation);
RSPMatrix* SysMatrix_ToRSPMatrix(MtxF* src, RSPMatrix* dst);
RSPMatrix* SysMatrix_GetStateAsRSPMatrix(RSPMatrix* matrix);
Mtx* Matrix_NewMtx(GraphicsContext* gfxCtx);
RSPMatrix* SysMatrix_AppendStateToPolyOpaDisp(GraphicsContext* gfxCtx);
void SysMatrix_AppendToPolyOpaDisp(MtxF* mtx, GraphicsContext* gfxCtx);
void SysMatrix_MultiplyVector3fByState(Vec3f* src, Vec3f* dst);
void SysMatrix_GetStateTranslation(Vec3f* dst);
void SysMatrix_GetStateTranslationAndScaledX(f32 scale, Vec3f* dst);
void SysMatrix_GetStateTranslationAndScaledY(f32 scale, Vec3f* dst);
void SysMatrix_GetStateTranslationAndScaledZ(f32 scale, Vec3f* dst);
void SysMatrix_MultiplyVector3fXZByCurrentState(Vec3f* src, Vec3f* dst);
void Matrix_MtxFCopy(MtxF* dst, MtxF* src);
void SysMatrix_FromRSPMatrix(RSPMatrix* src, MtxF* dst);
void SysMatrix_MultiplyVector3fByMatrix(Vec3f* src, Vec3f* dst, MtxF* matrix);
void SysMatrix_TransposeXYZ(MtxF* matrix);
void SysMatrix_NormalizeXYZ(MtxF* matrix);
void func_8018219C(MtxF* pfParm1, Vec3s* psParm2, s32 iParm3);
// void func_801822C4(void);
void SysMatrix_InsertRotationAroundUnitVector_f(f32 rotation, Vec3f* vector, s32 appendToState);
void SysMatrix_InsertRotationAroundUnitVector_s(s16 rotation, Vec3f* vector, s32 appendToState);
// void func_80182C90(void);
// void func_80182CA0(void);
// void func_80182CBC(void);
// void func_80182CCC(void);
// void func_80182CE0(void);
// void func_80183020(void);
// void func_80183058(void);
void func_80183070(void);
// void func_801830A0(void);
// void func_801830C8(void);
// void func_801830E8(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5,
// UNK_TYPE4 param_6, UNK_TYPE4 param_7); void func_80183148(void); void func_80183224(void); void func_801832B0(void);
// void func_8018332C(void);
// void func_8018340C(void);
// void func_80183430(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5,
// UNK_TYPE4 param_6); void func_8018349C(void); void func_801834A8(void); void func_80183510(void); void
// func_80183580(void); void func_801835EC(void); void func_80183658(void); void func_801836CC(void); void
// func_8018373C(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5,
// UNK_TYPE4 param_6, UNK_TYPE4 param_7, UNK_TYPE4 param_8, UNK_TYPE4 param_9); void func_801837CC(void); void
// func_80183808(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5,
// UNK_TYPE4 param_6); void func_80183880(void); void func_80183A3C(void); void func_80183B08(void); void
// func_80183B68(void); void func_80183DE0(void); void func_8018410C(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1
// param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6, UNK_TYPE4 param_7); void func_8018450C(UNK_TYPE1
// param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6); void
// func_801845A4(void); void func_801845C8(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4,
// UNK_TYPE4 param_5); void func_80184638(void); void func_801846AC(void); void func_80184728(void); void
// func_801847A0(void); void func_80184818(void); void func_80184898(void); void func_80184914(UNK_TYPE1 param_1,
// UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6, UNK_TYPE4 param_7,
// UNK_TYPE4 param_8, UNK_TYPE4 param_9, UNK_TYPE4 param_10); void func_801849A0(void); void func_801849DC(void); void
// func_80184C48(void); void func_801850A0(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4,
// UNK_TYPE4 param_5, UNK_TYPE4 param_6, UNK_TYPE4 param_7); void func_801853C8(UNK_TYPE1 param_1, UNK_TYPE1 param_2,
// UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6); void func_80185460(void);
// void Slowly_Main(SlowlyTask* slowly);
// void Slowly_ThreadEntry(SlowlyTask* slowly);
void Slowly_Start(SlowlyTask* slowly, void* stack, void (*callback)(), void* callbackArg0, void* callbackArg1);
void Slowly_Stop(SlowlyTask* slowly);
// void func_801857C0(void);
// char* func_801857D0(void);
// void func_80185864(void);
u32 func_80185908(void);
// void func_80185968(void);
// void func_801859F0(void);
// void func_80185A2C(void);
// void func_80185B1C(void);
// void func_80185BE4(void);
// void func_80185C24(void);
void SysFlashrom_ThreadEntry(s80185D40* param_1);
// void func_80185DDC(void);
// void func_80185EC4(void);
// void func_80185F04(void);
// void func_80185F64(void);
s32 func_80185F90(u32 param_1);
// void func_80186A70(void);
// void func_80186B78(void);
// void func_80186CAC(void);
// void func_80186D60(void);
// void func_80186E64(void);
// void func_80186EC8(void);
// void func_80187018(void);
// void func_80187080(void);
// void func_80187124(void);
// void func_80187284(void);
// void func_801872FC(void);
// void func_801873BC(void);
// void func_8018752C(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5,
// UNK_TYPE4 param_6); void func_801877D0(void); void func_80187B64(void); void func_80187BEC(void); void
// func_80187DE8(void); void func_80187E58(void); void func_80187F00(void); void func_80187FB0(void); void
// func_80187FE8(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5); void
// func_80188034(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5); void
// func_80188078(void); void func_801880C4(void); void func_801880E8(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1
// param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5); void func_80188124(void); void func_8018814C(void); void
// func_80188174(void); void func_801881A8(void); void func_801881C4(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1
// param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5); void func_801881F8(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1
// param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5); void func_80188264(void); void func_80188288(void); void
// func_801882A0(void); void func_80188304(void); void func_801884A0(void); void func_80188698(void); void
// func_8018883C(void); void func_801888E4(void); void func_801889A4(void); void func_80188A50(void); void
// func_80188AFC(void); void func_80188C48(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4,
// UNK_TYPE4 param_5); void func_80188CB4(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4,
// UNK_TYPE4 param_5); void func_80188D28(void); void func_80188D68(void); void func_80188DDC(void); void
// func_80188FBC(void); void func_80189064(void); void func_80189620(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1
// param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6, UNK_TYPE4 param_7); void func_8018A4B4(UNK_TYPE1
// param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6); void
// func_8018A768(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE2 param_5,
// UNK_TYPE4 param_6); void func_8018A808(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4,
// UNK_TYPE2 param_5, UNK_TYPE4 param_6); void func_8018ACC4(void); void func_8018AE34(UNK_TYPE1 param_1, UNK_TYPE1
// param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6); void func_8018B0F0(void); void
// func_8018B10C(void); void func_8018B250(void); void func_8018B318(void); void func_8018B474(void); void
// func_8018B4F8(void); void func_8018B520(void); void func_8018B578(void); void func_8018B5D0(void); void
// func_8018B608(void); void func_8018B640(void); void func_8018B69C(void); void func_8018B6E8(void); void
// func_8018B740(void); void func_8018B768(void); void func_8018B77C(void); void func_8018B7BC(void); void
// func_8018B8FC(void); void func_8018B95C(void); void func_8018B9E0(void); void func_8018BA64(void); void
// func_8018BB28(void); void func_8018BBEC(void); void func_8018C380(void); void func_8018C3D8(void); void
// func_8018C8E8(void); void func_8018C93C(void); void func_8018C994(void); void func_8018CB70(void); void
// func_8018CB78(void); void func_8018CC3C(void); void func_8018CCA8(void); void func_8018CFAC(void); void
// func_8018D57C(void); void func_8018D5D4(void); void func_8018D658(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1
// param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5); void func_8018D6C8(void); void func_8018D760(void); void
// func_8018DA50(void); void func_8018DBC4(void); void func_8018DCB4(void); void func_8018DCF8(void); void
// func_8018DD98(void); void func_8018DDD4(void); void func_8018DF24(void); void func_8018DFE0(void); void
// func_8018E00C(void); void func_8018E03C(void); void func_8018E2A8(void); void func_8018E344(void); void
// func_8018E8C8(void); void func_8018EB60(void); void func_8018EC4C(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1
// param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5); void func_8018EF88(void); void func_8018F220(void); void
// func_8018F298(void); void func_8018F310(void); void func_8018F388(void); void func_8018F3B8(void); void
// func_8018F3E8(void); void func_8018F448(void); void func_8018F478(void); void func_8018F4D8(void); void
// func_8018F588(void); void func_8018F604(void); void func_8018F6F0(void); void func_8018F7C0(UNK_TYPE1 param_1,
// UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5); void func_8018F7F8(void); void
// func_8018F83C(void); void func_8018F880(void); void func_8018F8C4(void); void func_8018F908(void); void
// func_8018F9B8(void); void func_8018FA60(void); void func_8018FAD0(void); void func_8018FB20(void); void
// func_8018FB78(void); void func_8018FCCC(void); void func_8018FD20(void); void func_8018FD40(void); void
// func_8018FE5C(void); void func_8018FF60(void); void func_80190204(void); void func_80190240(void); void
// func_80190294(void); void func_801902D8(void); void func_80190544(void); void func_80190668(void); void
// func_8019067C(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5,
// UNK_TYPE4 param_6, UNK_TYPE4 param_7, UNK_TYPE4 param_8); void func_8019075C(void); void func_8019077C(UNK_TYPE1
// param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5); void func_80190B08(void);
void func_80190B38(void* callback);
// void func_80190B50(void);
// void func_80190BB0(void);
// void func_80190F50(void);
// void func_80190F64(void);
// void func_80191134(void);
// void func_801911CC(void);
// void func_80191240(void);
// void func_801913C8(void);
// void func_8019144C(void);
// void func_80191460(void);
// void func_80191568(void);
// void func_80191598(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5,
// UNK_TYPE4 param_6, UNK_TYPE4 param_7, UNK_TYPE4 param_8); void func_8019161C(UNK_TYPE1 param_1, UNK_TYPE1 param_2,
// UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6, UNK_TYPE4 param_7); void
// func_80191740(void); void func_80191864(void); void func_80191870(void); void func_801919AC(void); void
// func_80191B40(void); void func_80191BD0(void); void func_80191C40(void); void func_80191C54(void); void
// func_80191D94(void); void func_8019218C(void); void func_80192340(void); void func_80192388(void); void
// func_801924BC(void); void func_80192514(void); void func_80192990(void); void func_80192AE8(void); void
// func_80192B54(void); void func_80192BAC(void);
AudioTask* func_80192BE0(void);
// void func_80192C00(void);
// void func_8019319C(void);
// void func_801936D8(void);
// void func_8019372C(void);
// void func_80193774(void);
// void func_8019380C(void);
// void func_80193858(void);
// void func_8019387C(void);
// void func_801938A0(void);
// void func_801938D0(void);
// void func_80193900(void);
// void func_80193990(void);
// void func_801939A8(void);
// void func_80193AEC(void);
// void func_80193BA0(void);
// void func_80193C04(void);
// void func_80193C5C(void);
// void func_80193CB4(void);
// void func_80193D08(void);
// void func_80193DA4(void);
// void func_80193E6C(void);
// void func_80193EA8(void);
// void func_80194080(void);
// void func_80194304(void);
// void func_80194328(void);
// void func_8019435C(void);
// void func_8019439C(void);
// void func_801943D0(void);
// void func_8019440C(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5);
// void func_80194528(void);
// void func_80194548(void);
// void func_80194568(void);
// void func_80194668(void);
// void func_801946E4(void);
// void func_80194710(void);
// void func_80194750(void);
// void func_80194790(void);
// void func_80194840(void);
// void func_801948B0(void);
// void func_80194930(void);
// void func_80194DB0(void);
// void func_80194E60(void);
// void func_80194F20(void);
// void func_80194F84(void);
// void func_801954CC(void);
// void func_80195508(void);
// void func_801955DC(void);
// void func_801956C0(void);
// void func_801957B4(void);
// void func_801958F8(void);
// void func_80195C40(void);
// void func_80195C60(void);
// void func_80195C80(void);
// void func_80195D84(void);
// void func_80195DDC(void);
// void func_80195DEC(void);
// void func_80195E3C(void);
// void func_80195EE0(void);
// void func_80196040(void);
// void func_8019617C(void);
// void func_801961BC(void);
// void func_801961E8(void);
// void func_80196268(void);
// void func_801963E8(void);
// void func_8019641C(void);
// void func_80196448(void);
// void func_80196494(void);
// void func_801964F8(void);
// void func_801965F0(void);
// void func_801968C4(void);
// void func_80196A00(void);
// void func_80196BC8(void);
// void func_80196D20(void);
// void func_80196D7C(void);
// void func_80196DB4(void);
// void func_80196FEC(void);
// void func_80197048(void);
// void func_80197138(void);
// void func_80197164(void);
// void func_80197188(void);
// void func_801974D0(void);
// void func_80197538(void);
// void func_80197714(void);
// void func_80197880(void);
// void func_801979D8(void);
// void func_80197A54(void);
// void func_80197AA4(void);
// void func_80197B14(void);
// void func_80197C0C(void);
// void func_80197C8C(void);
// void func_80197D24(void);
// void func_80197D4C(void);
// void func_80197E08(void);
// void func_80197E48(void);
// void func_80197E88(void);
// void func_80197F28(void);
// void func_80197F3C(void);
// void func_80197F74(void);
// void func_80197FB4(void);
// void func_801980D0(void);
// void func_8019815C(void);
// void func_8019825C(void);
// void func_80198640(void);
// void func_80198CE0(void);
// void func_801990F4(void);
// void func_80199124(void);
// void func_80199198(void);
// void func_80199244(void);
void func_80199268(s32* param_1);
// void func_8019A0BC(void);
// void func_8019AA3C(void);
// void func_8019AAF0(void);
// void func_8019AB40(void);
// void func_8019AC10(void);
// void func_8019ACEC(void);
// void func_8019ADBC(void);
void func_8019AE40(s32 param_1, s32 param_2, u32 param_3, s32 param_4);
void func_8019AEC0(UNK_PTR param_1, UNK_PTR param_2);
// void func_8019AF00(void);
// void func_8019AF58(void);
// void func_8019AFE8(void);
// void func_8019B02C(void);
// void func_8019B074(void);
// void func_8019B144(void);
// void func_8019B378(void);
// void func_8019B38C(void);
// void func_8019B3D0(void);
// void func_8019B4B8(void);
// void func_8019B544(void);
// void func_8019B568(void);
// void func_8019B5AC(void);
// void func_8019B5EC(void);
// void func_8019B618(void);
// void func_8019B654(void);
// void func_8019B6B4(void);
// void func_8019BC44(void);
// void func_8019BE98(void);
// void func_8019C1D0(void);
// void func_8019C268(void);
// void func_8019C2E4(void);
// void func_8019C300(void);
// void func_8019C398(void);
// void func_8019C5A0(void);
// void func_8019C8D8(void);
// void func_8019CD08(void);
// void func_8019CE34(void);
// void func_8019CE6C(void);
// void func_8019CEBC(void);
// void func_8019CF6C(void);
// void func_8019CF78(void);
// void func_8019CF9C(void);
// void func_8019CFA8(void);
// void func_8019D134(void);
// void func_8019D26C(void);
// void func_8019D488(void);
// void func_8019D4F8(void);
// void func_8019D600(void);
// void func_8019D758(void);
// void func_8019D864(void);
// void func_8019D8B4(void);
// void func_8019D8E4(void);
// void func_8019DF28(void);
// void func_8019DF64(void);
void func_8019E014(void);
// void func_8019E110(void);
// void func_8019E14C(void);
// void func_8019E324(void);
// void func_8019E4B0(void);
// void func_8019E634(void);
// void func_8019E864(void);
// void func_8019EA40(void);
// void func_8019EB2C(void);
// void func_8019F024(void);
// void func_8019F05C(void);
void play_sound(u16 sfxId);
void func_8019F128(u16 sfxId);
void func_8019F170(Vec3f *pos, u16 sfxId);
void func_8019F1C0(Vec3f* pos, u16 sfxId);
void func_8019F208(void);
void func_8019F230(void); // Plays "No" sound
// void func_8019F258(void);
// void func_8019F300(void);
void func_8019F420(Vec3f* pos, u16 sfxId);
// void func_8019F4AC(void);
void func_8019F540(u8 arg0);
// void func_8019F570(void);
// void func_8019F5AC(void);
// void func_8019F638(void);
// void func_8019F780(void);
// void func_8019F7D8(void);
// void func_8019F830(void);
void func_8019F88C(Vec3f* arg0, u16 sfxId, UNK_TYPE arg2);
// void func_8019F900(void);
// void func_8019FA18(void);
void func_8019FAD8(Vec3f* param_1, u16 param_2, f32 param_3);
// void func_8019FB0C(void);
// void func_8019FC20(void);
// void func_8019FCB8(void);
// void func_8019FD90(void);
void func_8019FDC8(UNK_PTR arg0, u16 sfxId, UNK_TYPE arg2);
// void func_8019FE1C(void);
// void func_8019FE74(void);
// void func_8019FEDC(void);
// void func_8019FF38(void);
// void func_8019FF9C(void);
// void func_801A0048(void);
// void func_801A00EC(void);
// void func_801A0124(void);
// void func_801A0184(void);
// void func_801A01C4(void);
void func_801A0204(UNK_TYPE);
// void func_801A0238(void);
// void func_801A026C(void);
// void func_801A0318(void);
// void func_801A046C(void);
// void func_801A0554(void);
// void func_801A05F0(void);
// void func_801A0654(void);
// void func_801A0810(void);
// void func_801A0868(void);
// void func_801A09D4(void);
// void func_801A0CB0(void);
// void func_801A0E44(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5,
// UNK_TYPE4 param_6, UNK_TYPE4 param_7); void func_801A1290(void); void func_801A1348(UNK_TYPE1 param_1, UNK_TYPE1
// param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6, UNK_TYPE4 param_7); void
// func_801A13BC(void); void func_801A153C(void); void func_801A17F4(void); void func_801A1904(void); void
// func_801A1A10(void); void func_801A1A8C(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4,
// UNK_TYPE4 param_5, UNK_TYPE4 param_6);
void func_801A1D44(Vec3f* vec, UNK_TYPE arg1, f32 arg2);
void func_801A1DB8(Vec3f* vec, UNK_TYPE arg1, f32 arg2);
// void func_801A1E0C(void);
void func_801A1F00(s32 arg0, s32 arg1);
void func_801A1F88(void);
// void func_801A1FB4(void);
// void func_801A2090(void);
void func_801A246C(u8 param_1, u8 param_2);
// void func_801A2544(void);
// void func_801A257C(void);
// void func_801A25E4(void);
// void func_801A2670(void);
// void func_801A2778(void);
// void func_801A27E8(void);
// void func_801A281C(void);
void func_801A29D4(UNK_TYPE arg0, f32 arg1, UNK_TYPE arg2);
// void func_801A2BB8(void);
// void func_801A2C20(void);
// void func_801A2C44(void);
// void func_801A2C88(void);
// void func_801A2D54(void);
s32 func_801A2DE0(UNK_TYPE4 arg1);
void func_801A2E54(s32 param_1);
void func_801A2ED8(void);
// void func_801A2F88(void);
// void func_801A3000(void);
// void func_801A3038(void);
void func_801A3098(u16 arg0);
// void func_801A312C(void);
void func_801A31EC(UNK_TYPE1 arg1, UNK_TYPE4 arg2, u8 arg3);
// void func_801A3238(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE1 param_5);
// void func_801A32CC(void);
// void func_801A3590(void);
// void func_801A3950(void);
u8 func_801A39F8(void);
// void func_801A3A7C(void);
// void func_801A3AC0(void);
// void func_801A3AEC(void);
void func_801A3B48(UNK_TYPE arg0);
// void func_801A3B90(void);
void func_801A3CD8(s8 param_1);
// void func_801A3CF4(void);
// void func_801A3D98(void);
// void func_801A3E38(void);
// void func_801A3EC0(void);
// void func_801A3F54(void);
// void func_801A3F6C(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5,
// UNK_TYPE4 param_6); void func_801A3FB4(void); void func_801A3FFC(UNK_TYPE1 param_1);
void audio_setBGM(u32 bgmID);
// void func_801A4058(void);
// void func_801A41C8(void);
// void func_801A41F8(void);
// void func_801A429C(void);
// void func_801A42C8(void);
// void func_801A4324(void);
// void func_801A4348(void);
// void func_801A4380(void);
// void func_801A4428(void);
void Audio_PreNMI(void);
// void func_801A44C4(void);
// void func_801A44D4(void);
s32 func_801A46F8(void);
// void func_801A4748(void);
// void func_801A479C(void);
// void func_801A47DC(void);
// void func_801A48E0(void);
// void func_801A4A28(void);
// void func_801A4B80(void);
void func_801A4C30(void);
// void func_801A4C54(void);
void func_801A4D00(void);
// void func_801A4D50(void);
// void func_801A4DA4(void);
// void func_801A4DF4(void);
// void func_801A4E64(void);
// void func_801A4EB0(void);
// void func_801A4EB8(void);
// void func_801A4FD8(void);
// void func_801A5080(void);
// void func_801A5100(void);
// void func_801A5118(void);
UNK_TYPE func_801A51F0(UNK_TYPE arg0);
// void func_801A5228(void);
// void func_801A5390(void);
// void func_801A53E8(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE2 param_5);
// void func_801A541C(void);
// void func_801A5488(void);
// void func_801A54C4(void);
// void func_801A54D0(void);
// void func_801A5680(void);
// void func_801A5808(void);
// void func_801A5A10(void);
// void func_801A5A1C(void);
void func_801A5BD0(s32 param_1);
// void func_801A5C28(void);
// void func_801A5C8C(void);
// void func_801A5CFC(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5,
// UNK_TYPE4 param_6); void func_801A5DDC(void); void func_801A5F7C(void); void func_801A6430(void); void
// func_801A65C8(void); void func_801A6D0C(void); void func_801A7084(void); void func_801A7168(void); void
// func_801A7284(void);
void func_801A72CC(Vec3f* uParm1);
// void func_801A7328(void);
// void func_801A7484(void);
// void func_801A75E8(void);
// void func_801A7720(void);
void func_801A7794(u32 param_1, u32 param_2, u32 param_3);
// void func_801A7828(void);
// void func_801A787C(void);
// void func_801A78E4(void);
// void func_801A794C(void);
// void func_801A7B10(void);
// void func_801A7D04(void);
// void func_801A7D84(void);
void func_801A89A8(s32 arg0);
// void func_801A89D0(void);
s32 func_801A8A50(s32 param1);
// void func_801A8ABC(void);
// void func_801A8BD0(void);
// void func_801A8D5C(void);
// void func_801A8E90(void);
// void func_801A9768(void);
// void func_801A982C(void);
// void func_801A99B8(void);
// void func_801A9A74(void);
// void func_801A9B10(void);
// void func_801A9B78(void);
// void func_801A9BFC(void);
// void func_801A9C68(void);
// void func_801A9D10(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE1 param_5);
// void func_801A9DCC(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE1 param_5);
// void func_801A9EA4(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE2 param_5,
// UNK_TYPE1 param_6); void func_801A9F4C(void); void func_801AA020(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1
// param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5); void func_801AA248(void); void func_801AA3E4(void); void
// func_801AA520(void);
void func_801AA610(GlobalContext* globalCtx);
void func_801AA624(GlobalContext* globalCtx);
// void func_801AA68C(UNK_TYPE4 ctxt);
void func_801AAAA0(GlobalContext* globalCtx);

#endif
