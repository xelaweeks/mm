#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include "z64.h"

void bootproc(void);
void Idle_ThreadEntry(void* arg);
void ViConfig_UpdateVi(u32 arg0);
void ViConfig_UpdateBlack(void);
s32 DmaMgr_DmaRomToRam(u32 src, void* dst, size_t size);
s32 DmaMgr_DmaHandler(OSPiHandle* piHandle, OSIoMesg* mb, s32 direction);
DmaEntry* DmaMgr_FindDmaEntry(u32 vromAddr);
u32 DmaMgr_TranslateVromToRom(u32 vromAddr);
s32 DmaMgr_FindDmaIndex(u32 vromAddr);
const char* func_800809F4(u32 param_1);
void DmaMgr_ProcessMsg(DmaRequest* req);
void DmaMgr_ThreadEntry(void* arg);
s32 DmaMgr_SendRequestImpl(DmaRequest* request, void* vramStart, uintptr_t vromStart, size_t size, UNK_TYPE4 unused,
                           OSMesgQueue* callback, void* callbackMesg);
s32 DmaMgr_SendRequest0(void* vramStart, uintptr_t vromStart, size_t size);
void DmaMgr_Start(void);
void DmaMgr_Stop(void);
void* Yaz0_FirstDMA(void);
void* Yaz0_NextDMA(void* curSrcPos);
s32 Yaz0_DecompressImpl(u8* hdr, u8* dst);
void Yaz0_Decompress(u32 romStart, void* dst, size_t size);
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
void Fault_AddClient(FaultClient* client, void* callback, void* param0, void* param1);
void Fault_RemoveClient(FaultClient* client);
void Fault_AddAddrConvClient(FaultAddrConvClient* client, void* callback, void* param);
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
void Fault_DrawMemDumpPage(const char* title, u32* addr, u32 param_3);
void Fault_DrawMemDump(u32 pc, u32 sp, u32 unk0, u32 unk1);
void Fault_FindNextStackCall(uintptr_t* spPtr, uintptr_t* pcPtr, uintptr_t* raPtr);
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
void* FaultDrawer_FormatStringFunc(void* arg, const char* str, size_t count);
void FaultDrawer_VPrintf(const char* fmt, va_list ap);
void FaultDrawer_Printf(const char* fmt, ...);
void FaultDrawer_DrawText(s32 x, s32 y, const char* fmt, ...);
void FaultDrawer_SetDrawerFB(void* fb, u16 w, u16 h);
void FaultDrawer_SetInputCallback(FaultDrawerCallback callback);
void FaultDrawer_Init(void);
void func_80084940(void);
void func_80084968(void);

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

void MtxConv_F2L(Mtx* m1, MtxF* m2);
void MtxConv_L2F(MtxF* m1, Mtx* m2);

void __assert(const char* file, u32 lineNum);
// void func_800862B4(void);
void* SystemArena_MallocMin1(u32 size);
void SystemArena_FreeNullCheck(void* ptr);
void SystemArena_RunInits(void);
void SystemArena_Init(void* start, size_t size);
s32 func_80086620(OSMesgQueue* param_1, PadMgr* param_2, OSContStatus* param_3);
// void func_80086760(void);
// void func_80086794(void);
// void func_800867B4(void);
// void func_800867D4(void);
// void func_800867F4(void);
f32 func_80086814(f32 x);
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

u32 Rand_Next(void);
void Rand_Seed(u32 seed);
f32 Rand_ZeroOne(void);
f32 Rand_Centered(void);
void Rand_Seed_Variable(u32* rndNum, u32 seed);
u32 Rand_Next_Variable(u32* param_1);
f32 Rand_ZeroOne_Variable(u32* param_1);
f32 Rand_Centered_Variable(u32* param_1);

void* proutSprintf(void* s, const char* buf, size_t n);
s32 vsprintf(char* dst, char* fmt, va_list args);
s32 sprintf(char* s, char* fmt, ...);
s32 PrintUtils_VPrintf(PrintCallback* pfn, const char* fmt, va_list args);
s32 PrintUtils_Printf(PrintCallback* pfn, const char* fmt, ...);
void Sleep_Cycles(OSTime time);
void Sleep_Nsec(u32 nsec);
void Sleep_Usec(u32 usec);
void Sleep_Msec(u32 ms);
void Sleep_Sec(u32 sec);
// void __osSetCause(void);
s32 osSendMesg(OSMesgQueue* mq, OSMesg msg, s32 flags);
s32 osPfsFreeBlocks(OSPfs* pfs, s32* leftoverBytes);
void osViExtendVStart(u32 param_1);
void osStopThread(OSThread* t);
s32 osRecvMesg(OSMesgQueue* mq, OSMesg* msg, s32 flags);
OSIntMask osSetIntMask(OSIntMask im);
// OSIntMask osGetIntMask(void);
// void osVoiceSetWord(void);
// void guScale(void);
f32 sinf(f32 __x);
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
s32 __osSpRawStartDma(s32 direction, void* devAddr, void* dramAddr, size_t size);
s32 __osSiRawStartDma(s32 direction, void* dramAddr);
s32 osEPiLinkHandle(OSPiHandle* handle);
void osViBlack(u8 active);
s32 __osSiRawReadIo(u32 devAddr, u32* data);
OSId osGetThreadId(OSThread* t);
void osSpTaskYield(void);
s32 __osPfsGetNextPage(OSPfs* pfs, u8* bank, __OSInode* inode, __OSInodeUnit* page);
s32 osPfsReadWriteFile(OSPfs* pfs, s32 fileNo, u8 flag, s32 offset, s32 size, u8* data);
s32 __osPfsGetStatus(OSMesgQueue* queue, s32 channel);
// void __osPfsRequestOneChannel(void);
// void __osPfsGetOneChannelData(void);
void guMtxIdentF(float mf[4][4]);
void osViSetMode(OSViMode* modep);
// void __osGetConfig(void);
// void __osSetConfig(void);
void guLookAtF(float mf[4][4], f32 xEye, f32 yEye, f32 zEye, f32 xAt, f32 yAt, f32 zAt, f32 xUp, f32 yUp, f32 zUp);
void guLookAt(Mtx* m, f32 xEye, f32 yEye, f32 zEye, f32 xAt, f32 yAt, f32 zAt, f32 xUp, f32 yUp, f32 zUp);
s32 osPfsAllocateFile(OSPfs* pfs, u16 companyCode, u32 gameCode, u8* gameName, u8* extName, s32 fileSize, s32* fileNo);
s32 __osPfsDeclearPage(OSPfs* pfs, __OSInode* inode, s32 fileSizeInPages, s32* startPage, u8 bank, s32* decleared,
                       s32* finalPage);
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
s32 __osPiRawStartDma(s32 direction, u32 devAddr, void* dramAddr, size_t size);
u16 __osSumcalc(u8* ptr, s32 length);
s32 __osIdCheckSum(u16* ptr, u16* checkSum, u16* idSum);
s32 __osRepairPackId(OSPfs* pfs, __OSPackId* badid, __OSPackId* newid);
// void __osCheckPackId(void);
s32 __osCheckId(OSPfs* pfs);
s32 __osPfsRWInode(OSPfs* pfs, __OSInode* inode, u8 flag, u8 bank);
u32 osGetCount(void);
void guMtxL2F(MtxF* m1, Mtx* m2);
u32 osGetMemSize(void);
s32 osPfsFindFile(OSPfs* pfs, u16 companyCode, u32 gameCode, u8* gameName, u8* extName, s32* fileNo);
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
u8 __osVoiceContDataCrc(u8* data, size_t numBytes);
const char* strchr(const char* __s, s32 __c);
size_t strlen(const char* __s);
void* memcpy(void* __dest, const void* __src, size_t __n);
void osCreateMesgQueue(OSMesgQueue* mq, OSMesg* msq, s32 count);
void osInvalICache(void* vaddr, size_t nbytes);
void osInvalDCache(void* vaddr, size_t nbytes);
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
s32 __osEPiRawReadIo(OSPiHandle* handle, u32 devAddr, u32* data);
void osViSwapBuffer(void* frameBufPtr);
void guPositionF(float mf[4][4], f32 r, f32 p, f32 h, f32 s, f32 x, f32 y, f32 z);
void guPosition(Mtx* m, f32 r, f32 p, f32 h, f32 s, f32 x, f32 y, f32 z);
s32 __osEPiRawStartDma(OSPiHandle* handle, s32 direction, u32 cartAddr, void* dramAddr, size_t size);
OSYieldResult osSpTaskYielded(OSTask* task);
s32 bcmp(void* __s1, void* __s2, size_t __n);
OSTime osGetTime(void);
void guRotateF(float mf[4][4], f32 a, f32 x, f32 y, f32 z);
void guRotate(Mtx* m, f32 a, f32 x, f32 y, f32 z);
void __osSetGlobalIntMask(u32 mask);
// void osVoiceInit(void);
s32 __osContChannelReset(OSMesgQueue* mq, s32 channel);
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
f32 cosf(f32 __x);
s32 osEPiReadIo(OSPiHandle* pihandle, u32 devAddr, u32* data);
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
s32 __osPfsSelectBank(OSPfs* pfs, u8 bank);
s32 osContSetCh(u8 ch);
u32 __osSetFpcCsr(u32 value);
u32 __osGetFpcCsr(void);
// void osPfsFileState(void);
// void osPfsInitPak(void);
// void __osPfsCheckRamArea(void);
// void osPfsChecker(void);
u32 osAiGetLength(void);
s32 osEPiWriteIo(OSPiHandle* pihandle, u32 devAddr, u32 data);
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
// void viMgrMain(OSDevMgr* iParm1);
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
u32* osViGetCurrentFramebuffer(void);
s32 __osSpSetPc(void* pc);
// void __osVoiceContWrite4(void);
void __osGetHWIntrRoutine(s32 idx, OSMesgQueue** outQueue, OSMesg* outMsg);
void __osSetHWIntrRoutine(s32 idx, OSMesgQueue* queue, OSMesg msg);
u32 __osGetWatchLo(void);
void __osSetWatchLo(u32 value);
f32 fmodf(f32 dividend, f32 divisor);
void* __osMemset(void* ptr, s32 val, size_t size);
s32 __osStrcmp(const char* str1, const char* str2);
char* __osStrcpy(char* dst, const char* src);
void* __osMemcpy(void* dst, void* src, size_t size);

// void EnItem00_SetObject(EnItem00* this, PlayState* play, f32* shadowOffset, f32* shadowScale);
// void EnItem00_Init(Actor* thisx, PlayState* play);
// void EnItem00_Destroy(Actor* thisx, PlayState* play);
// void EnItem00_WaitForHeartObject(EnItem00* this, PlayState* play);
// void func_800A640C(EnItem00* this, PlayState* play);
// void func_800A6650(EnItem00* this, PlayState* play);
// void func_800A6780(EnItem00* this, PlayState* play);
// void func_800A6A40(EnItem00* this, PlayState* play);
// void EnItem00_Update(Actor* thisx, PlayState* play);
// void EnItem00_Draw(Actor* thisx, PlayState* play);
// void EnItem00_DrawRupee(EnItem00* this, PlayState* play);
// void EnItem00_DrawSprite(EnItem00* this, PlayState* play);
// void EnItem00_DrawHeartContainer(EnItem00* this, PlayState* play);
// void EnItem00_DrawHeartPiece(EnItem00* this, PlayState* play);
// s16 func_800A7650(s16 dropId);
Actor* Item_DropCollectible(PlayState* play, Vec3f* spawnPos, u32 params);
Actor* Item_DropCollectible2(PlayState* play, Vec3f* spawnPos, s32 params);
void Item_DropCollectibleRandom(PlayState* play, Actor* fromActor, Vec3f* spawnPos, s16 params);
s32 func_800A8150(s32 index);
s32 func_800A817C(s32 index);
s32 Item_CanDropBigFairy(PlayState* play, s32 index, s32 collectibleFlag);
void EffectBlure_AddVertex(EffectBlure* this, Vec3f* p1, Vec3f* p2);
void EffectBlure_AddSpace(EffectBlure* this);
void EffectBlure_Init1(void* thisx, void* initParamsx);
void EffectBlure_Init2(void* thisx, void* initParamsx);
void EffectBlure_Destroy(void* thisx);
s32 EffectBlure_Update(void* thisx);
void EffectBlure_Draw(void* thisx, GraphicsContext* gfxCtx);
void EffectShieldParticle_Init(void* thisx, void* initParamsx);
void EffectShieldParticle_Destroy(void* thisx);
s32 EffectShieldParticle_Update(void* thisx);
void EffectShieldParticle_Draw(void* thisx, GraphicsContext* gfxCtx);
void EffectSpark_Init(void* thisx, void* initParamsx);
void EffectSpark_Destroy(void* thisx);
s32 EffectSpark_Update(void* thisx);
void EffectSpark_Draw(void* thisx, GraphicsContext* gfxCtx);
void func_800AE2A0(PlayState* play, Color_RGBA8* color, s16 arg2, s16 arg3);
void func_800AE434(PlayState* play, Color_RGBA8* color, s16 arg2, s16 arg3);
void func_800AE5A0(PlayState* play);
void func_800AE5E4(PlayState* play, Color_RGBA8* color, s16 arg2, s16 arg3);
void func_800AE778(PlayState* play, Color_RGBA8* color, s16 arg2, s16 arg3);
void func_800AE8EC(PlayState* play);
void func_800AE930(CollisionContext* colCtx, EffectTireMark* this, Vec3f* pos, f32 arg3, s16 angle,
                   CollisionPoly* colPoly, s32 arg6);
void func_800AEF44(EffectTireMark* this);
void EffectTireMark_Init(void* thisx, void* initParamsx);
void EffectTireMark_Destroy(void* thisx);
s32 EffectTireMark_Update(void* thisx);
void EffectTireMark_Draw(void* thisx, GraphicsContext* gfxCtx);
PlayState* Effect_GetPlayState(void);
void* Effect_GetByIndex(s32 index);
void Effect_Init(PlayState* play);
void Effect_Add(PlayState* play, s32* pIndex, s32 type, u8 arg3, u8 arg4, void* initParams);
void Effect_DrawAll(GraphicsContext* gfxCtx);
void Effect_UpdateAll(PlayState* play);
void Effect_Destroy(PlayState* play, s32 index);
void Effect_DestroyAll(PlayState* play);
void EffectSS_Init(PlayState* play, s32 numEntries);
void EffectSS_Clear(PlayState* play);
EffectSs* EffectSS_GetTable(void);
void EffectSS_Delete(EffectSs* param_1);
void EffectSS_ResetEntry(EffectSs* particle);
s32 EffectSS_FindFreeSpace(s32 priority, s32* tableEntry);
void EffectSS_Copy(PlayState* play, EffectSs* particle);
void EffectSs_Spawn(PlayState* play, s32 type, s32 priority, void* initParams);
void EffectSS_UpdateParticle(PlayState* play, s32 index);
void EffectSS_UpdateAllParticles(PlayState* play);
void EffectSS_DrawParticle(PlayState* play, s32 index);
void EffectSS_DrawAllParticles(PlayState* play);
s16 func_800B096C(s16 param_1, s16 param_2, s32 param_3);
s16 func_800B09D0(s16 a0, s16 a1, f32 a2);
u8 func_800B0A24(u8 a0, u8 a1, f32 a2);
void EffectSs_DrawGEffect(PlayState* play, EffectSs* this, void* texture);
void EffectSsDust_Spawn(PlayState* play, u16 drawFlags, Vec3f* pos, Vec3f* velocity, Vec3f* accel,
                        Color_RGBA8* primColor, Color_RGBA8* envColor, s16 scale, s16 scaleStep, s16 life,
                        u8 updateMode);
void func_800B0DE0(PlayState* play, Vec3f* pos, Vec3f* velocity, Vec3f* accel, Color_RGBA8* primColor,
                   Color_RGBA8* envColor, s16 scale, s16 scaleStep);
void func_800B0E48(PlayState* play, Vec3f* pos, Vec3f* velocity, Vec3f* accel, Color_RGBA8* primColor,
                   Color_RGBA8* envColor, s16 scale, s16 scaleStep);
void func_800B0EB0(PlayState* play, Vec3f* pos, Vec3f* velocity, Vec3f* accel, Color_RGBA8* primColor,
                   Color_RGBA8* envColor, s16 scale, s16 scaleStep, s16 life);
void func_800B0F18(PlayState* play, Vec3f* pos, Vec3f* velocity, Vec3f* accel, Color_RGBA8* primColor,
                   Color_RGBA8* envColor, s16 scale, s16 scaleStep, s16 life);
void func_800B0F80(PlayState* play, Vec3f* pos, Vec3f* velocity, Vec3f* accel, Color_RGBA8* primColor,
                   Color_RGBA8* envColor, s16 scale, s16 scaleStep, s16 life);
void func_800B0FE8(PlayState* play, Vec3f* pos, Vec3f* velocity, Vec3f* accel, Color_RGBA8* primColor,
                   Color_RGBA8* envColor, s16 scale, s16 scaleStep);
void func_800B1054(PlayState* play, Vec3f* pos, Vec3f* velocity, Vec3f* accel, Color_RGBA8* primColor,
                   Color_RGBA8* envColor, s16 scale, s16 scaleStep);
void func_800B10C0(PlayState* play, Vec3f* pos, Vec3f* velocity, Vec3f* accel);
void func_800B1130(PlayState* play, Vec3f* pos, Vec3f* velocity, Vec3f* accel);
void func_800B11A0(PlayState* play, Vec3f* pos, Vec3f* velocity, Vec3f* accel, s16 scale, s16 scaleStep);
void func_800B1210(PlayState* play, Vec3f* pos, Vec3f* velocity, Vec3f* accel, s16 scale, s16 scaleStep);
void func_800B1280(PlayState* play, Vec3f* pos, Vec3f* velocity, Vec3f* accel, s16 scale, s16 scaleStep, s16 life);
void func_800B12F0(PlayState* play, Vec3f* pos, Vec3f* velocity, Vec3f* accel, s16 scale, s16 scaleStep, s16 life);
void func_800B1360(PlayState* play, Vec3f* pos, Vec3f* velocity, Vec3f* accel, Color_RGBA8* primColor,
                   Color_RGBA8* envColor);
void func_800B139C(PlayState* play, Vec3f* pos, Vec3f* velocity, Vec3f* accel, Color_RGBA8* primColor,
                   Color_RGBA8* envColor);
void func_800B13D8(Vec3f* srcPos, f32 randScale, Vec3f* newPos, Vec3f* velocity, Vec3f* accel);
void func_800B14D4(PlayState* play, f32 randScale, Vec3f* srcPos);
void func_800B1598(PlayState* play, f32 randScale, Vec3f* srcPos);
void EffectSsKirakira_SpawnSmallYellow(PlayState* play, Vec3f* pos, Vec3f* velocity, Vec3f* accel);
void EffectSsKirakira_SpawnSmall(PlayState* play, Vec3f* pos, Vec3f* velocity, Vec3f* accel, Color_RGBA8* primColor,
                                 Color_RGBA8* envColor);
void EffectSsGSpk_SpawnSmall(PlayState* play, Actor* actor, Vec3f* pos, Vec3f* velocity, Vec3f* accel,
                             Color_RGBA8* primColor, Color_RGBA8* envColor);
void EffectSsKirakira_SpawnDispersed(PlayState* play, Vec3f* pos, Vec3f* velocity, Vec3f* accel, Color_RGBA8* primColor,
                                     Color_RGBA8* envColor, s16 scale, s32 life);
// void EffectSsKirakira_SpawnFocused(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4,
// UNK_TYPE4 param_5, UNK_TYPE4 param_6, UNK_TYPE2 param_7, UNK_TYPE4 param_8); void EffectSsBomb2_SpawnFade(UNK_TYPE4
// uParm1, Vec3f* pzParm2, Vec3f* pzParm3, Vec3f* pzParm4);
void EffectSsBomb2_SpawnLayered(PlayState* play, Vec3f* pos, Vec3f* velocity, Vec3f* accel, s16 scale, s16 scaleStep);
// void EffectSsBlast_Spawn(UNK_TYPE4 uParm1, Vec3f* pzParm2, Vec3f* pzParm3, Vec3f* pzParm4, Color_RGBA8* param_5,
// Color_RGBA8* param_6, UNK_TYPE2 param_7, UNK_TYPE2 param_8, UNK_TYPE2 param_9, UNK_TYPE2 param_10);
void EffectSsBlast_SpawnWhiteCustomScale(PlayState* play, Vec3f* pos, Vec3f* velocity, Vec3f* accel, s16 scale,
                                         s16 scaleStep, s16 life);
// void EffectSsBlast_SpawnShockwave(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4,
// UNK_TYPE4 param_5, UNK_TYPE4 param_6, UNK_TYPE2 param_7);
void EffectSsBlast_SpawnWhiteShockwave(PlayState* play, Vec3f* arg1, Vec3f* arg2, Vec3f* arg3);
// void EffectSsGSpk_SpawnAccel(UNK_TYPE4 uParm1, UNK_TYPE4 uParm2, Vec3f* pzParm3, Vec3f* pzParm4, Vec3f* param_5,
// Color_RGBA8* param_6, Color_RGBA8* param_7, UNK_TYPE2 param_8, UNK_TYPE2 param_9); void
// EffectSsGSpk_SpawnNoAccel(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4
// param_5, UNK_TYPE4 param_6, UNK_TYPE4 param_7, UNK_TYPE2 param_8, UNK_TYPE2 param_9);
void EffectSsGSpk_SpawnFuse(PlayState* play, Actor* actor, Vec3f* pos, Vec3f* velocity, Vec3f* accel);
// void EffectSsGSpk_SpawnRandColor(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4,
// UNK_TYPE4 param_5, UNK_TYPE2 param_6, UNK_TYPE2 param_7); void EffectSsGSpk_SpawnSmall(UNK_TYPE1 param_1, UNK_TYPE1
// param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6, UNK_TYPE4 param_7);
void EffectSsDFire_Spawn(PlayState* play, Vec3f* pos, Vec3f* velocity, Vec3f* accel, s16 scale, s16 scaleStep,
                         s16 alpha, s16 fadeDelay, s16 life, s32 arg9);
void EffectSsBubble_Spawn(PlayState* play, Vec3f* pos, f32 yPosOffset, f32 yPosRandScale, f32 xzPosRandScale,
                          f32 scale);
void EffectSsGRipple_Spawn(PlayState* play, Vec3f* pos, s16 radius, s16 radiusMax, s16 life);
void EffectSsGSplash_Spawn(PlayState* play, Vec3f* pos, Color_RGBA8* primColor, Color_RGBA8* envColor, s16 type,
                           s16 scale);
void EffectSsGFire_Spawn(PlayState* play, Vec3f* pos);
// void EffectSsLightning_Spawn(UNK_TYPE4 uParm1, Vec3f* pzParm2, Color_RGBA8* pzParm3, Color_RGBA8* pzParm4, UNK_TYPE2
// param_5, UNK_TYPE2 param_6, UNK_TYPE2 param_7, UNK_TYPE2 param_8);
void EffectSsDtBubble_SpawnColorProfile(PlayState* play, Vec3f* pos, Vec3f* velocity, Vec3f* accel, s16 scale, s16 life,
                                        s16 colorProfile, s16 randXZ);
void EffectSsDtBubble_SpawnCustomColor(PlayState* play, Vec3f* pos, Vec3f* velocity, Vec3f* accel,
                                       Color_RGBA8* primColor, Color_RGBA8* envColor, s16 scale, s16 life, s16 randXZ);
void EffectSsHahen_Spawn(PlayState* play, Vec3f* pos, Vec3f* velocity, Vec3f* accel, s16 flags, s16 scale, s16 objId,
                         s16 life, Gfx* dList);
void EffectSsHahen_SpawnBurst(PlayState* play, Vec3f* pos, f32 burstScale, s16 flags, s16 scale, s16 randScaleRange,
                              s16 count, s16 objId, s16 life, Gfx* dList);
// void func_800B2364(void);
// void EffectSsStick_Spawn(UNK_TYPE4 uParm1, UNK_PTR puParm2, UNK_TYPE2 uParm3);
// void EffectSsSibuki_Spawn(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE2
// param_5, UNK_TYPE2 param_6, UNK_TYPE2 param_7);
void EffectSsSibuki_SpawnBurst(PlayState* play, Vec3f* pos);
void EffectSsStone1_Spawn(PlayState* play, Vec3f* pos, s32 reg0);
void EffectSsHitmark_SpawnFixedScale(PlayState* play, s32 type, Vec3f* pos);
void EffectSsHitmark_SpawnCustomScale(PlayState* play, s32 type, s16 scale, Vec3f* pos);
// void EffectSsFhgFlash_SpawnShock(UNK_TYPE4 uParm1, UNK_TYPE4 uParm2, Vec3f* pzParm3, UNK_TYPE2 uParm4, UNK_TYPE1
// param_5); void EffectSsKFire_Spawn(UNK_TYPE4 uParm1, Vec3f* pzParm2, Vec3f* pzParm3, Vec3f* pzParm4, UNK_TYPE2
// param_5, UNK_TYPE1 param_6);
void EffectSsSolderSrchBall_Spawn(PlayState* play, Vec3f* pos, Vec3f* velocity, Vec3f* accel, s16 unused,
                                  s16* linkDetected, s16 drawFlag);
void EffectSsKakera_Spawn(PlayState* play, Vec3f* pos, Vec3f* velocity, Vec3f* arg3, s16 gravity, s16 arg5, s16 arg6,
                          s16 arg7, s16 arg8, s16 scale, s16 arg10, s16 arg11, s32 life, s16 colorIdx, s16 objId,
                          Gfx* dList);
// void EffectSsIcePiece_Spawn(UNK_TYPE4 uParm1, Vec3f* pzParm2, UNK_TYPE4 uParm3, Vec3f* pzParm4, Vec3f* param_5,
// UNK_TYPE4 param_6); void EffectSsIcePiece_SpawnBurst(void); void EffectSsEnIce_SpawnFlyingVec3f(UNK_TYPE4 uParm1,
// Actor* pzParm2, Vec3f* pzParm3, Color_RGBA8* pzParm4, Color_RGBA8* param_5, UNK_TYPE4 param_6);
void func_800B2B44(PlayState* play, Actor* actor, Vec3f* arg2, f32 arg3);
// void func_800B2B7C(void);
void EffectSsEnIce_Spawn(PlayState* play, Vec3f* pos, f32 scale, Vec3f* velocity, Vec3f* accel, Color_RGBA8* primColor,
                         Color_RGBA8* envColor, s32 life);
// void EffectSsFireTail_Spawn(UNK_TYPE4 uParm1, UNK_TYPE4 uParm2, Vec3f* pzParm3, UNK_TYPE4 uParm4, Vec3f* param_5,
// UNK_TYPE2 param_6, Color_RGBA8* param_7, Color_RGBA8* param_8, UNK_TYPE2 param_9, UNK_TYPE2 param_10, UNK_TYPE4
// param_11); void EffectSsFireTail_SpawnFlame(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1
// param_4, UNK_TYPE2 param_5, UNK_TYPE4 param_6); void EffectSsFireTail_SpawnFlameOnPlayer(void);
void EffectSsEnFire_SpawnVec3f(PlayState* play, Actor* actor, Vec3f* pos, s16 scale, s16 arg4, s16 flags, s16 bodyPart);
// void EffectSsEnFire_SpawnVec3s(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE2
// param_5, UNK_TYPE2 param_6, UNK_TYPE2 param_7);
void EffectSsExtra_Spawn(PlayState* play, Vec3f* pos, Vec3f* velocity, Vec3f* accel, s16 scale, s16 scoreIdx);
void EffectSsDeadDb_Spawn(PlayState* play, Vec3f* pos, Vec3f* velocity, Vec3f* accel, Color_RGBA8* prim,
                          Color_RGBA8* env, s16 scale, s16 scaleStep, s32 unk);
void func_800B3030(PlayState* play, Vec3f* pos, Vec3f* velocity, Vec3f* accel, s16 scale, s16 scaleStep,
                   s32 colorIndex);
void EffectSsDeadDd_Spawn(PlayState* play, Vec3f* pos, Vec3f* velocity, Vec3f* accel, Color_RGBA8* prim,
                          Color_RGBA8* env, s16 scale, s16 scaleStep, s16 alphaStep, s32 life);
// void EffectSsDeadDs_Spawn(UNK_TYPE4 uParm1, Vec3f* pzParm2, Vec3f* pzParm3, Vec3f* pzParm4, UNK_TYPE2 param_5,
// UNK_TYPE2 param_6, UNK_TYPE2 param_7, UNK_TYPE4 param_8);
void func_800B31BC(PlayState* play, Vec3f* pos, s16 scale, s16 scaleStep, s16 alpha, s32 life);
void EffectSsIceSmoke_Spawn(PlayState* play, Vec3f* pos, Vec3f* velocity, Vec3f* accel, s16 scale);
void EffectSsIceBlock_Spawn(PlayState* play, Vec3f* pos, Vec3f* velocity, Vec3f* accel, s16 scale);
void FlagSet_Update(GameState* gameState);
void FlagSet_Draw(GameState* gameState);
void Overlay_LoadGameState(GameStateOverlay* gameState);
void Overlay_FreeGameState(GameStateOverlay* gameState);

void ActorShape_Init(ActorShape* actorShape, f32 yOffset, ActorShadowFunc shadowDraw, f32 shadowScale);
void ActorShadow_DrawCircle(Actor* actor, Lights* lights, PlayState* play);
void ActorShadow_DrawSquare(Actor* actor, Lights* lights, PlayState* play);
void ActorShadow_DrawWhiteCircle(Actor* actor, Lights* lights, PlayState* play);
void ActorShadow_DrawHorse(Actor* actor, Lights* lights, PlayState* play);

void ActorShadow_DrawFeet(Actor* actor, Lights* mapper, PlayState* play);
void Actor_SetFeetPos(Actor* actor, s32 limbIndex, s32 leftFootIndex, Vec3f* leftFootPos, s32 rightFootIndex,
                      Vec3f* rightFootPos);
void func_800B4AEC(PlayState* play, Actor* actor, f32 y);
void func_800B4B50(Actor* actor, Lights* mapper, PlayState* play);
void Actor_GetProjectedPos(PlayState* play, Vec3f* worldPos, Vec3f* projectedPos, f32* invW);

void Actor_DrawZTarget(TargetContext* targetCtx, PlayState* play);

s32 Flags_GetSwitch(PlayState* play, s32 flag);
void Flags_SetSwitch(PlayState* play, s32 flag);
void Flags_UnsetSwitch(PlayState* play, s32 flag);
s32 Flags_GetTreasure(PlayState* play, s32 flag);
void Flags_SetTreasure(PlayState* play, s32 flag);
void Flags_SetAllTreasure(PlayState* play, s32 flag);
s32 Flags_GetAllTreasure(PlayState* play);
s32 Flags_GetClear(PlayState* play, s32 roomNumber);
void Flags_SetClear(PlayState* play, s32 roomNumber);
void Flags_UnsetClear(PlayState* play, s32 roomNumber);
s32 Flags_GetClearTemp(PlayState* play, s32 roomNumber);
void Flags_SetClearTemp(PlayState* play, s32 roomNumber);
void Flags_UnsetClearTemp(PlayState* play, s32 roomNumber);
s32 Flags_GetCollectible(PlayState* play, s32 flag);
void Flags_SetCollectible(PlayState* play, s32 flag);

void TitleCard_InitBossName(GameState* gameState, TitleCardContext* titleCtx, TexturePtr texture, s16 x, s16 y,
                            u8 width, u8 height);

s32 func_800B648C(PlayState* play, s32 arg1, s32 arg2, f32 arg3, Vec3f* arg4);
f32 func_800B64FC(PlayState* play, f32 arg1, Vec3f* arg2, u32* arg3);
void* func_800B6584(PlayState* play, s16 id, void* arg2, size_t size);
void* func_800B6608(PlayState* play, s16 id);
void* func_800B6680(PlayState* play, s16 id);
void Actor_MarkForDeath(Actor* actor);
void Actor_SetWorldToHome(Actor* actor);
void Actor_SetFocus(Actor* actor, f32 height);
void Actor_SetWorldRotToShape(Actor* actor);
void Actor_SetShapeRotToWorld(Actor* actor);
void Actor_SetScale(Actor* actor, f32 scale);
void Actor_SetObjectDependency(PlayState* play, Actor* actor);
void Actor_SetMovementScale(s32 scale);
void Actor_UpdatePos(Actor* actor);
void Actor_UpdateVelocityWithGravity(Actor* actor);
void Actor_MoveWithGravity(Actor* actor);
void Actor_UpdateVelocityWithoutGravity(Actor* actor);
void Actor_MoveWithoutGravity(Actor* actor);
void Actor_UpdateVelocityWithoutGravityReverse(Actor* actor);
void Actor_MoveWithoutGravityReverse(Actor* actor);
void Actor_SetSpeeds(Actor* actor, f32 speed);
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
void Actor_OffsetOfPointInActorCoords(Actor* actor, Vec3f* offset, Vec3f* point);
f32 Actor_HeightDiff(Actor* actor1, Actor* actor2);
void func_800B6F20(PlayState* play, Input* input, f32 arg2, s16 arg3);
f32 Player_GetHeight(Player* player);
f32 Player_GetRunSpeedLimit(Player* player);
s32 func_800B7118(Player* player);
s32 func_800B7128(Player* player);
s32 func_800B715C(PlayState* play);
void Actor_SetCameraHorseSetting(PlayState* play, Player* player);
void Actor_MountHorse(PlayState* play, Player* player, Actor* horse);
s32 func_800B724C(PlayState* play, Actor* actor, u8 csMode);
u32 func_800B7298(PlayState* play, Actor* actor, u8 csMode);
void func_800B72F8(DynaPolyActor* dyna, f32 extraPushForce, s16 yRotation);

s32 Player_IsFacingActor(Actor* actor, s16 maxAngleDiff, PlayState* play);
s32 Actor_ActorBIsFacingActorA(Actor* actorA, Actor* actorB, s16 maxAngleDiff);
s32 Actor_IsFacingPlayer(Actor* actor, s16 angle);
s32 Actor_ActorAIsFacingActorB(Actor* actorA, Actor* actorB, s16 maxAngleDiff);
s32 Actor_IsFacingAndNearPlayer(Actor* actor, f32 range, s16 maxAngleDiff);
s32 Actor_ActorAIsFacingAndNearActorB(Actor* actorA, Actor* actorB, f32 range, s16 maxAngleDiff);

void func_800B75A0(CollisionPoly* poly, Vec3f* normal, s16* azimuth);
void Actor_UpdateBgCheckInfo(PlayState* play, Actor* actor, f32 wallCheckHeight, f32 wallCheckRadius,
                             f32 ceilingCheckHeight, u32 flags);
Hilite* Hilite_DrawOpa(Vec3f* object, Vec3f* eye, Vec3f* lightDir, GraphicsContext* gfxCtx);
void func_800B8050(Actor* actor, PlayState* play, s32 flag);
void func_800B8118(Actor* actor, PlayState* play, s32 flag);
PosRot* Actor_GetFocus(PosRot* dest, Actor* actor);
PosRot* Actor_GetWorld(PosRot* dest, Actor* actor);
PosRot* Actor_GetWorldPosShapeRot(PosRot* dest, Actor* actor);

s32 func_800B83F8(Actor* actor, Player* player, s32 flag);
s32 Actor_ProcessTalkRequest(Actor* actor, GameState* gameState);
s32 func_800B8500(Actor* actor, PlayState* play, f32 xzRange, f32 yRange, s32 exchangeItemId);
s32 func_800B85E0(Actor* actor, PlayState* play, f32 radius, s32 exchangeItemId);
s32 func_800B8614(Actor* actor, PlayState* play, f32 radius);
s32 func_800B863C(Actor* actor, PlayState* play);
s32 Actor_TextboxIsClosing(Actor* actor, PlayState* play);
s32 Actor_ChangeFocus(Actor* actor1, PlayState* play, Actor* actor2);
s32 Player_GetExchangeItemId(PlayState* play);
s32 func_800B8718(Actor* actor, GameState* gameState);
s32 func_800B874C(Actor* actor, PlayState* play, f32 xzRange, f32 yRange);
s32 func_800B8804(Actor* actor, PlayState* play, f32 xzRange);
s32 func_800B886C(Actor* actor, PlayState* play);
void Actor_GetScreenPos(PlayState* play, Actor* actor, s16* x, s16* y);
s32 func_800B8934(PlayState* play, Actor* actor);
s32 Actor_HasParent(Actor* actor, PlayState* play);
s32 Actor_PickUp(Actor* actor, PlayState* play, s32 getItemId, f32 xzRange, f32 yRange);
s32 Actor_PickUpNearby(Actor* actor, PlayState* play, s32 getItemId);
s32 Actor_LiftActor(Actor* actor, PlayState* play);
s32 Actor_PickUpFar(Actor* actor, PlayState* play, s32 getItemId);
s32 Actor_HasNoParent(Actor* actor, PlayState* play);
void func_800B8C20(Actor* actorA, Actor* actorB, PlayState* play);
void func_800B8C50(Actor* actor, PlayState* play);
s32 Actor_HasRider(PlayState* play, Actor* horse);
s32 Actor_SetRideActor(PlayState* play, Actor* horse, s32 mountSide);
s32 Actor_HasNoRider(PlayState* play, Actor* horse);
void func_800B8D10(PlayState* play, Actor* actor, f32 arg2, s16 arg3, f32 arg4, u32 arg5, u32 arg6);
void func_800B8D50(PlayState* play, Actor* actor, f32 arg2, s16 yaw, f32 arg4, u32 arg5);
void func_800B8D98(PlayState* play, Actor* actor, f32 arg2, s16 arg3, f32 arg4);
void func_800B8DD4(PlayState* play, Actor* actor, f32 arg2, s16 arg3, f32 arg4, u32 arg5);
void func_800B8E1C(PlayState* play, Actor* actor, f32 arg2, s16 arg3, f32 arg4);
void func_800B8E58(Player* player, u16 sfxId);
void Actor_PlaySfxAtPos(Actor* actor, u16 sfxId);
void func_800B8EF4(PlayState* play, Actor* actor);
void func_800B8F98(Actor* actor, u16 sfxId);
void func_800B8FC0(Actor* actor, u16 sfxId);
void func_800B8FE8(Actor* actor, u16 sfxId);
void func_800B9010(Actor* actor, u16 sfxId);
void func_800B9038(Actor* actor, s32 timer);
void func_800B9084(Actor* actor);
void func_800B9098(Actor* actor);
s32 func_800B90AC(PlayState* play, Actor* actor, CollisionPoly* polygon, s32 index, s32 arg4);
void func_800B90F4(PlayState* play);
void func_800B9120(ActorContext* actorCtx);
void Actor_InitContext(PlayState* play, ActorContext* actorCtx, ActorEntry* actorEntry);
void Actor_UpdateAll(PlayState* play, ActorContext* actorCtx);
s32 Actor_RecordUndrawnActor(PlayState* play, Actor* actor);
void Actor_DrawAll(PlayState* play, ActorContext* actorCtx);
void func_800BA6FC(PlayState* play, ActorContext* actorCtx);
void func_800BA798(PlayState* play, ActorContext* actorCtx);
void Actor_CleanupContext(ActorContext* actorCtx, PlayState* play);
Actor* Actor_Spawn(ActorContext* actorCtx, PlayState* play, s16 actorId, f32 posX, f32 posY, f32 posZ, s16 rotX,
                   s16 rotY, s16 rotZ, s32 params);
Actor* Actor_SpawnAsChildAndCutscene(ActorContext* actorCtx, PlayState* play, s16 index, f32 x, f32 y, f32 z, s16 rotX,
                                     s16 rotY, s16 rotZ, s32 params, u32 cutscene, s32 arg11, Actor* parent);
Actor* Actor_SpawnAsChild(ActorContext* actorCtx, Actor* parent, PlayState* play, s16 actorId, f32 posX, f32 posY,
                          f32 posZ, s16 rotX, s16 rotY, s16 rotZ, s32 params);
void Actor_SpawnTransitionActors(PlayState* play, ActorContext* actorCtx);
void Enemy_StartFinishingBlow(PlayState* play, Actor* actor);
s16 func_800BBAC0(s16 arg0[2], s16 arg1, s16 arg2, s16 arg3);
s16 func_800BBB74(s16 arg0[2], s16 arg1, s16 arg2, s16 arg3);
void Actor_SpawnBodyParts(Actor* actor, PlayState* play, s32 arg2, Gfx** dList);
void Actor_SpawnFloorDustRing(PlayState* play, Actor* actor, Vec3f* posXZ, f32 radius, s32 countMinusOne,
                              f32 randAccelWeight, s16 scale, s16 scaleStep, u8 useLighting);
void func_800BBFB0(PlayState* play, Vec3f* position, f32 arg2, s32 arg3, s16 arg4, s16 scaleStep, u8 arg6);
void func_800BC154(PlayState* play, ActorContext* actorCtx, Actor* actor, u8 actorCategory);
s32 func_800BC188(s32 index);
Actor* func_800BC270(PlayState* play, Actor* actor, f32 arg2, s32 arg3);
Actor* func_800BC444(PlayState* play, Actor* actor, f32 arg2);
s16 Actor_TestFloorInDirection(Actor* actor, PlayState* play, f32 distance, s16 angle);
s32 Actor_IsTargeted(PlayState* play, Actor* actor);
s32 Actor_OtherIsTargeted(PlayState* play, Actor* actor);
void func_800BC620(Vec3f* arg0, Vec3f* arg1, u8 alpha, PlayState* play);
void func_800BC770(PlayState* play, s16 y, s16 countdown);
void func_800BC7D8(PlayState* play, s16 y, s16 countdown, s16 speed);
void func_800BC848(Actor* actor, PlayState* play, s16 y, s16 countdown);
void Actor_DrawDoorLock(PlayState* play, s32 frame, s32 type);
void Actor_SetColorFilter(Actor* actor, u16 colorFlag, u16 colorIntensityMax, u16 xluFlag, u16 duration);
Hilite* func_800BCBF4(Vec3f* arg0, PlayState* play);
Hilite* func_800BCC68(Vec3f* arg0, PlayState* play);
void Actor_GetClosestPosOnPath(Vec3s* points, s32 numPoints, Vec3f* srcPos, Vec3f* dstPos, s32 isPathLoop);
s32 func_800BD2B4(PlayState* play, Actor* actor, s16* arg2, f32 arg3, u16 (*textIdCallback)(PlayState*, Actor*),
                  s16 (*arg5)(PlayState*, Actor*));
void func_800BD888(Actor* actor, struct_800BD888_arg1* arg1, s16 arg2, s16 arg3);
void func_800BD9E0(PlayState* play, SkelAnime* skelAnime, OverrideLimbDraw overrideLimbDraw, PostLimbDraw postLimbDraw,
                   Actor* actor, s16 alpha);
void func_800BDAA0(PlayState* play, SkelAnime* skelAnime, OverrideLimbDraw overrideLimbDraw, PostLimbDraw postLimbDraw,
                   Actor* actor, s16 alpha);
void Actor_ChangeAnimationByInfo(SkelAnime* skelAnime, AnimationInfo* animation, s32 index);
void Actor_Noop(Actor* actor, PlayState* play);

void Gfx_DrawDListOpa(PlayState* play, Gfx* dlist);
void Gfx_DrawDListXlu(PlayState* play, Gfx* dlist);

Actor* Actor_FindNearby(PlayState* play, Actor* inActor, s16 actorId, u8 actorCategory, f32 distance);
s32 func_800BE184(PlayState* play, Actor* actor, f32 xzDist, s16 arg3, s16 arg4, s16 arg5);
u8 Actor_ApplyDamage(Actor* actor);
void Actor_SetDropFlag(Actor* actor, ColliderInfo* colInfo);
void Actor_SetDropFlagJntSph(Actor* actor, ColliderJntSph* jntSphere);
void func_800BE33C(Vec3f* arg0, Vec3f* arg1, Vec3s* arg2, s32 arg3);
void func_800BE3D0(Actor* actor, s16 angle, Vec3s* arg2);
void func_800BE504(Actor* actor, ColliderCylinder* collider);
void func_800BE568(Actor* actor, ColliderSphere* collider);
void func_800BE5CC(Actor* actor, ColliderJntSph* collider, s32 colliderIndex);
s32 Actor_IsSmallChest(struct EnBox* chest);
void Actor_DrawDamageEffects(PlayState* play, Actor* actor, Vec3f limbPos[], s16 limbPosCount, f32 effectScale,
                             f32 frozenSteamScale, f32 effectAlpha, u8 type);
void Actor_SpawnIceEffects(PlayState* play, Actor* actor, Vec3f limbPos[], s32 limbPosCount, s32 effectsPerLimb,
                           f32 scale, f32 scaleRange);

void ActorOverlayTable_FaultPrint(void* arg0, void* arg1);
void* ActorOverlayTable_FaultAddrConv(void* arg0, void* arg1);
void ActorOverlayTable_Init(void);
void ActorOverlayTable_Cleanup(void);

void SSNode_SetValue(SSNode* node, s16* polyIndex, u16 next);
void SSList_SetNull(SSList* head);
void SSNodeList_SetSSListHead(SSNodeList* list, SSList* ssList, s16* polyIndex);
void DynaSSNodeList_SetSSListHead(DynaSSNodeList* list, SSList* ssList, s16* polyIndex);
void DynaSSNodeList_Init(PlayState* play, DynaSSNodeList* list);
void DynaSSNodeList_Alloc(PlayState* play, DynaSSNodeList* list, u32 numNodes);
void DynaSSNodeList_ResetCount(DynaSSNodeList* list);
u16 DynaSSNodeList_GetNextNodeIdx(DynaSSNodeList* list);
void BgCheck_Vec3sToVec3f(Vec3s* vertex, Vec3f* vector);
void BgCheck_Vec3fToVec3s(Vec3s* vertex, Vec3f* vector);
f32 func_800BFD84(CollisionPoly* poly, f32 arg1, f32 arg2);
s32 func_800BFDEC(CollisionPoly* polyA, CollisionPoly* polyB, u32* outVtxId0, u32* outVtxId1);
s16 CollisionPoly_GetMinY(CollisionPoly* poly, Vec3s* vertices);
void CollisionPoly_GetNormalF(CollisionPoly* poly, f32* nx, f32* ny, f32* nz);
void func_800C0094(CollisionPoly* poly, f32 tx, f32 ty, f32 tz, MtxF* dest);
f32 CollisionPoly_GetPointDistanceFromPlane(CollisionPoly* poly, Vec3f* point);
void CollisionPoly_GetVerticesByBgId(CollisionPoly* poly, s32 bgId, CollisionContext* colCtx, Vec3f* dest);
s32 CollisionPoly_SphVsPoly(CollisionPoly* poly, Vec3s* vtxList, Vec3f* center, f32 radius);
void StaticLookup_AddPolyToSSList(CollisionContext* colCtx, SSList* ssList, CollisionPoly* polyList, Vec3s* vtxList,
                                  s16 polyId);
void StaticLookup_AddPoly(StaticLookup* lookup, CollisionContext* colCtx, CollisionPoly* polyList, Vec3s* vtxList,
                          s16 index);
void BgCheck_GetSubdivisionMinBounds(CollisionContext* colCtx, Vec3f* pos, s32* sx, s32* sy, s32* sz);
void BgCheck_GetSubdivisionMaxBounds(CollisionContext* colCtx, Vec3f* pos, s32* sx, s32* sy, s32* sz);
void BgCheck_GetPolySubdivisionBounds(CollisionContext* colCtx, Vec3s* vtxList, CollisionPoly* polyList,
                                      s32* subdivMinX, s32* subdivMinY, s32* subdivMinZ, s32* subdivMaxX,
                                      s32* subdivMaxY, s32* subdivMaxZ, s16 polyId);
s32 BgCheck_PolyIntersectsSubdivision(Vec3f* min, Vec3f* max, CollisionPoly* polyList, Vec3s* vtxList, s16 polyId);
u32 BgCheck_InitStaticLookup(CollisionContext* colCtx, PlayState* play, StaticLookup* lookupTbl);
s32 BgCheck_IsSmallMemScene(PlayState* play);
s32 BgCheck_TryGetCustomMemsize(s32 sceneId, u32* memSize);
void BgCheck_SetSubdivisionDimension(f32 min, s32 subdivAmount, f32* max, f32* subdivLength, f32* subdivLengthInv);
s32 BgCheck_GetSpecialSceneMaxObjects(PlayState* play, s32* maxNodes, s32* maxPolygons, s32* maxVertices);
void BgCheck_Allocate(CollisionContext* colCtx, PlayState* play, CollisionHeader* colHeader);
void BgCheck_SetContextFlags(CollisionContext* colCtx, u32 flags);
void BgCheck_UnsetContextFlags(CollisionContext* colCtx, u32 flags);
CollisionHeader* BgCheck_GetCollisionHeader(CollisionContext* colCtx, s32 bgId);
f32 BgCheck_RaycastFloorImpl(PlayState* play, CollisionContext* colCtx, u16 xpFlags, CollisionPoly** outPoly,
                             s32* outBgId, Vec3f* pos, Actor* actor, u32 arg7, f32 chkDist, s32 arg9);
f32 BgCheck_CameraRaycastFloor1(CollisionContext* colCtx, CollisionPoly** outPoly, Vec3f* pos);
f32 BgCheck_EntityRaycastFloor1(CollisionContext* colCtx, CollisionPoly** outPoly, Vec3f* pos);
f32 BgCheck_EntityRaycastFloor2(PlayState* play, CollisionContext* colCtx, CollisionPoly** outPoly, Vec3f* pos);
f32 BgCheck_EntityRaycastFloor2_1(PlayState* play, CollisionContext* colCtx, CollisionPoly** outPoly, Vec3f* pos);
f32 BgCheck_EntityRaycastFloor3(CollisionContext* colCtx, CollisionPoly** outPoly, s32* bgId, Vec3f* pos);
f32 BgCheck_EntityRaycastFloor5(CollisionContext* colCtx, CollisionPoly** outPoly, s32* outBgId, Actor* actor,
                                Vec3f* pos);
f32 BgCheck_EntityRaycastFloor5_2(PlayState* play, CollisionContext* colCtx, CollisionPoly** outPoly, s32* bgId,
                                  Actor* actor, Vec3f* pos);
f32 BgCheck_EntityRaycastFloor5_3(PlayState* play, CollisionContext* colCtx, CollisionPoly** outPoly, s32* bgId,
                                  Actor* actor, Vec3f* pos);
f32 BgCheck_EntityRaycastFloor6(CollisionContext* colCtx, CollisionPoly** outPoly, s32* bgId, Actor* actor, Vec3f* pos,
                                f32 chkDist);
f32 BgCheck_EntityRaycastFloor7(CollisionContext* colCtx, CollisionPoly** outPoly, s32* bgId, Actor* actor, Vec3f* pos);
f32 BgCheck_AnyRaycastFloor1(CollisionContext* colCtx, CollisionPoly* outPoly, Vec3f* pos);
f32 BgCheck_AnyRaycastFloor2(CollisionContext* colCtx, CollisionPoly* outPoly, s32* bgId, Vec3f* pos);
f32 BgCheck_CameraRaycastFloor2(CollisionContext* colCtx, CollisionPoly** outPoly, s32* bgId, Vec3f* pos);
f32 BgCheck_EntityRaycastFloor8(CollisionContext* colCtx, CollisionPoly** outPoly, s32* bgId, Actor* actor, Vec3f* pos);
f32 BgCheck_EntityRaycastFloor9(CollisionContext* colCtx, CollisionPoly** outPoly, s32* bgId, Vec3f* pos);
s32 BgCheck_CheckWallImpl(CollisionContext* colCtx, u16 xpFlags, Vec3f* posResult, Vec3f* posNext, Vec3f* posPrev,
                          f32 radius, CollisionPoly** outPoly, s32* outBgId, Actor* actor, f32 checkHeight, u8 argA);
s32 BgCheck_EntitySphVsWall1(CollisionContext* colCtx, Vec3f* posResult, Vec3f* posNext, Vec3f* posPrev, f32 radius,
                             CollisionPoly** outPoly, f32 checkHeight);
s32 BgCheck_EntitySphVsWall2(CollisionContext* colCtx, Vec3f* posResult, Vec3f* posNext, Vec3f* posPrev, f32 radius,
                             CollisionPoly** outPoly, s32* outBgId, f32 checkHeight);
s32 BgCheck_EntitySphVsWall3(CollisionContext* colCtx, Vec3f* posResult, Vec3f* posNext, Vec3f* posPrev, f32 radius,
                             CollisionPoly** outPoly, s32* outBgId, Actor* actor, f32 checkHeight);
s32 BgCheck_EntitySphVsWall4(CollisionContext* colCtx, Vec3f* posResult, Vec3f* posNext, Vec3f* posPrev, f32 radius,
                             CollisionPoly** outPoly, s32* outBgId, Actor* actor, f32 checkHeight);
s32 BgCheck_CheckCeilingImpl(CollisionContext* colCtx, u16 xpFlags, f32* outY, Vec3f* pos, f32 checkHeight,
                             CollisionPoly** outPoly, s32* outBgId, Actor* actor);
s32 BgCheck_AnyCheckCeiling(CollisionContext* colCtx, f32* outY, Vec3f* pos, f32 checkHeight);
s32 BgCheck_EntityCheckCeiling(CollisionContext* colCtx, f32* outY, Vec3f* pos, f32 checkHeight,
                               CollisionPoly** outPoly, s32* outBgId, Actor* actor);
s32 BgCheck_CameraLineTest1(CollisionContext* colCtx, Vec3f* posA, Vec3f* posB, Vec3f* posResult,
                            CollisionPoly** outPoly, s32 chkWall, s32 chkFloor, s32 chkCeil, s32 chkOneFace, s32* bgId);
s32 BgCheck_CameraLineTest2(CollisionContext* colCtx, Vec3f* posA, Vec3f* posB, Vec3f* posResult,
                            CollisionPoly** outPoly, s32 chkWall, s32 chkFloor, s32 chkCeil, s32 chkOneFace, s32* bgId);
s32 BgCheck_EntityLineTest1(CollisionContext* colCtx, Vec3f* posA, Vec3f* posB, Vec3f* posResult,
                            CollisionPoly** outPoly, s32 chkWall, s32 chkFloor, s32 chkCeil, s32 chkOneFace, s32* bgId);
s32 BgCheck_EntityLineTest2(CollisionContext* colCtx, Vec3f* posA, Vec3f* posB, Vec3f* posResult,
                            CollisionPoly** outPoly, s32 chkWall, s32 chkFloor, s32 chkCeil, s32 chkOneFace, s32* bgId,
                            Actor* actor);
s32 BgCheck_EntityLineTest3(CollisionContext* colCtx, Vec3f* posA, Vec3f* posB, Vec3f* posResult,
                            CollisionPoly** outPoly, s32 chkWall, s32 chkFloor, s32 chkCeil, s32 chkOneFace, s32* bgId,
                            Actor* actor, f32 chkDist);
s32 BgCheck_ProjectileLineTest(CollisionContext* colCtx, Vec3f* posA, Vec3f* posB, Vec3f* posResult,
                               CollisionPoly** outPoly, s32 chkWall, s32 chkFloor, s32 chkCeil, s32 chkOneFace,
                               s32* bgId);
s32 BgCheck_AnyLineTest1(CollisionContext* colCtx, Vec3f* posA, Vec3f* posB, Vec3f* posResult, CollisionPoly** outPoly,
                         s32 chkOneFace);
s32 BgCheck_AnyLineTest2(CollisionContext* colCtx, Vec3f* posA, Vec3f* posB, Vec3f* posResult, CollisionPoly** outPoly,
                         s32 chkWall, s32 chkFloor, s32 chkCeil, s32 chkOneFace);
s32 BgCheck_AnyLineTest3(CollisionContext* colCtx, Vec3f* posA, Vec3f* posB, Vec3f* posResult, CollisionPoly** outPoly,
                         s32 chkWall, s32 chkFloor, s32 chkCeil, s32 chkOneFace, s32* bgId);
s32 BgCheck_SphVsFirstPolyImpl(CollisionContext* colCtx, u16 xpFlags, CollisionPoly** outPoly, s32* outBgId,
                               Vec3f* center, f32 radius, Actor* actor, u16 bciFlags);
s32 BgCheck_SphVsFirstPoly(CollisionContext* colCtx, Vec3f* center, f32 radius);
s32 BgCheck_SphVsFirstWall(CollisionContext* colCtx, Vec3f* center, f32 radius);
void SSNodeList_Init(SSNodeList* this);
void SSNodeList_Alloc(PlayState* play, SSNodeList* this, s32 tblMax, s32 numPolys);
SSNode* SSNodeList_GetNextNode(SSNodeList* this);
u16 SSNodeList_GetNextNodeIdx(SSNodeList* this);
void ScaleRotPos_Init(ScaleRotPos* srp);
void ScaleRotPos_SetValue(ScaleRotPos* srp, Vec3f* scale, Vec3s* rot, Vec3f* pos);
s32 ScaleRotPos_IsEqual(ScaleRotPos* a, ScaleRotPos* b);
void DynaLookup_ResetLists(DynaLookup* dynaLookup);
void DynaLookup_Reset(DynaLookup* dynaLookup);
void DynaLookup_ResetVtxStartIndex(u16* vtxStartIndex);
void DynaLookup_ResetWaterBoxStartIndex(u16* waterBoxStartIndex);
void BgActor_Init(PlayState* play, BgActor* bgActor);
void BgActor_SetActor(BgActor* bgActor, Actor* actor, CollisionHeader* colHeader);
s32 BgActor_IsTransformUnchanged(BgActor* bgActor);
void DynaPoly_NullPolyList(CollisionPoly** polyList);
void DynaPoly_AllocPolyList(PlayState* play, CollisionPoly** polyList, s32 numPolys);
void DynaPoly_NullVtxList(Vec3s** vtxList);
void DynaPoly_AllocVtxList(PlayState* play, Vec3s** vtxList, s32 numVtx);
void DynaPoly_InitWaterBoxList(DynaWaterBoxList* waterBoxList);
void DynaPoly_AllocWaterBoxList(PlayState* play, DynaWaterBoxList* waterBoxList, s32 numWaterBoxes);
void DynaPoly_SetBgActorPrevTransform(PlayState* play, BgActor* bgActor);
s32 DynaPoly_IsBgIdBgActor(s32 bgId);
void DynaPoly_Init(PlayState* play, DynaCollisionContext* dyna);
void DynaPoly_Alloc(PlayState* play, DynaCollisionContext* dyna);
s32 DynaPoly_SetBgActor(PlayState* play, DynaCollisionContext* dyna, Actor* actor, CollisionHeader* colHeader);
DynaPolyActor* DynaPoly_GetActor(CollisionContext* colCtx, s32 bgId);
void func_800C62BC(PlayState* play, DynaCollisionContext* dyna, s32 bgId);
void func_800C6314(PlayState* play, DynaCollisionContext* dyna, s32 bgId);
void func_800C636C(PlayState* play, DynaCollisionContext* dyna, s32 bgId);
void func_800C63C4(PlayState* play, DynaCollisionContext* dyna, s32 bgId);
void func_800C641C(PlayState* play, DynaCollisionContext* dyna, s32 bgId);
void func_800C6474(PlayState* play, DynaCollisionContext* dyna, s32 bgId);
void DynaPoly_DeleteBgActor(PlayState* play, DynaCollisionContext* dyna, s32 bgId);
void BgCheck_CalcWaterboxDimensions(Vec3f* minPos, Vec3f* maxXPos, Vec3f* maxZPos, Vec3s* minPosOut, s16* xLength,
                                    s16* zLength);
void DynaPoly_ExpandSRT(PlayState* play, DynaCollisionContext* dyna, s32 bgId, s32* vtxStartIndex, s32* polyStartIndex,
                        s32* waterBoxStartIndex);
void BgCheck_ResetFlagsIfLoadedActor(PlayState* play, DynaCollisionContext* dyna, Actor* actor);
void DynaPoly_Setup(PlayState* play, DynaCollisionContext* dyna);
void func_800C756C(DynaCollisionContext* dyna, s32* numPolygons, s32* numVertices, s32* numWaterBoxes);
void DynaPoly_UpdateBgActorTransforms(PlayState* play, DynaCollisionContext* dyna);
void CollisionHeader_SegmentedToVirtual(CollisionHeader* header);
void CollisionHeader_GetVirtual(CollisionHeader* meshSegPtr, CollisionHeader** param_2);
void BgCheck_InitCollisionHeaders(CollisionContext* colCtx, PlayState* play);

u32 SurfaceType_GetBgCamIndex(CollisionContext* colCtx, CollisionPoly* poly, s32 bgId);
u16 BgCheck_GetBgCamSettingImpl(CollisionContext* colCtx, u32 bgCamIndex, s32 bgId);
u16 BgCheck_GetBgCamSetting(CollisionContext* colCtx, CollisionPoly* poly, s32 bgId);
u16 BgCheck_GetBgCamCountImpl(CollisionContext* colCtx, u32 bgCamIndex, s32 bgId);
u16 BgCheck_GetBgCamCount(CollisionContext* colCtx, CollisionPoly* poly, s32 bgId);
Vec3s* BgCheck_GetBgCamFuncDataImpl(CollisionContext* colCtx, s32 bgCamIndex, s32 bgId);
Vec3s* BgCheck_GetBgCamFuncData(CollisionContext* colCtx, CollisionPoly* poly, s32 bgId);

u32 SurfaceType_GetSceneExitIndex(CollisionContext* colCtx, CollisionPoly* poly, s32 bgId);
u32 func_800C99D4(CollisionContext* colCtx, CollisionPoly* poly, s32 bgId);
u32 func_800C99FC(CollisionContext* colCtx, CollisionPoly* poly, s32 bgId);
u32 func_800C9A24(CollisionContext* colCtx, CollisionPoly* poly, s32 bgId);
s32 func_800C9A4C(CollisionContext* colCtx, CollisionPoly* poly, s32 bgId);
s32 func_800C9A7C(CollisionContext* colCtx, CollisionPoly* poly, s32 bgId);
s32 func_800C9AB0(CollisionContext* colCtx, CollisionPoly* poly, s32 bgId);
s32 func_800C9AE4(CollisionContext* colCtx, CollisionPoly* poly, s32 bgId);
u32 func_800C9B18(CollisionContext* colCtx, CollisionPoly* poly, s32 bgId);
u32 func_800C9B40(CollisionContext* colCtx, CollisionPoly* poly, s32 bgId);
u32 func_800C9B68(CollisionContext* colCtx, CollisionPoly* poly, s32 bgId);
u32 SurfaceType_IsHorseBlocked(CollisionContext* colCtx, CollisionPoly* poly, s32 bgId);
u32 func_800C9BB8(CollisionContext* colCtx, CollisionPoly* poly, s32 bgId);
u16 SurfaceType_GetSfx(CollisionContext* colCtx, CollisionPoly* poly, s32 bgId);
s32 func_800C9C24(CollisionContext* colCtx, CollisionPoly* poly, s32 bgId, s32 arg3);
u32 SurfaceType_GetSlope(CollisionContext* colCtx, CollisionPoly* poly, s32 bgId);
u32 SurfaceType_GetLightSettingIndex(CollisionContext* colCtx, CollisionPoly* poly, s32 bgId);
u32 SurfaceType_GetEcho(CollisionContext* colCtx, CollisionPoly* poly, s32 bgId);
u32 SurfaceType_IsHookshotSurface(CollisionContext* colCtx, CollisionPoly* poly, s32 bgId);
s32 SurfaceType_IsIgnoredByEntities(CollisionContext* colCtx, CollisionPoly* poly, s32 bgId);
s32 SurfaceType_IsIgnoredByProjectiles(CollisionContext* colCtx, CollisionPoly* poly, s32 bgId);
s32 SurfaceType_GetConveyorType(CollisionContext* colCtx, CollisionPoly* poly, s32 bgId);
s32 func_800C9DDC(CollisionContext* colCtx, CollisionPoly* poly, s32 bgId);
u32 SurfaceType_GetConveyorSpeed(CollisionContext* colCtx, CollisionPoly* poly, s32 bgId);
u32 SurfaceType_GetConveyorDirection(CollisionContext* colCtx, CollisionPoly* poly, s32 bgId);
u32 SurfaceType_IsWallDamage(CollisionContext* colCtx, CollisionPoly* poly, s32 bgId);
s32 WaterBox_GetSurfaceImpl(PlayState* play, CollisionContext* colCtx, f32 x, f32 z, f32* ySurface,
                            WaterBox** outWaterBox, s32* bgId);
s32 WaterBox_GetSurface1(PlayState* play, CollisionContext* colCtx, f32 x, f32 z, f32* ySurface,
                         WaterBox** outWaterBox);
s32 WaterBox_GetSurface1_2(PlayState* play, CollisionContext* colCtx, f32 x, f32 z, f32* ySurface,
                           WaterBox** outWaterBox);
s32 WaterBox_GetSurface2(PlayState* play, CollisionContext* colCtx, Vec3f* pos, f32 surfaceChkDist,
                         WaterBox** outWaterBox, s32* bgId);
f32 func_800CA568(CollisionContext* colCtx, s32 waterBoxId, s32 bgId);
u16 WaterBox_GetBgCamSetting(CollisionContext* colCtx, WaterBox* waterBox, s32 bgId);
void WaterBox_GetSceneBgCamSetting(CollisionContext* colCtx, WaterBox* waterBox);
u32 WaterBox_GetLightSettingIndex(CollisionContext* colCtx, WaterBox* waterBox);
s32 func_800CA6F0(PlayState* play, CollisionContext* colCtx, f32 x, f32 z, f32* ySurface, WaterBox** outWaterBox,
                  s32* bgId);
s32 func_800CA9D0(PlayState* play, CollisionContext* colCtx, f32 x, f32 z, f32* ySurface, WaterBox** outWaterBox);
s32 func_800CAA14(CollisionPoly* polyA, CollisionPoly* polyB, Vec3f* pointA, Vec3f* pointB, Vec3f* closestPoint);
void BgCheck2_UpdateActorPosition(CollisionContext* colCtx, s32 index, Actor* actor);
void BgCheck2_UpdateActorYRotation(CollisionContext* colCtx, s32 index, Actor* actor);
void BgCheck2_AttachToMesh(CollisionContext* colCtx, Actor* actor, s32 index);
u32 BgCheck2_UpdateActorAttachedToMesh(CollisionContext* colCtx, s32 index, Actor* actor);
void DynaPolyActor_Init(DynaPolyActor* dynaActor, s32 flags);
void DynaPolyActor_LoadMesh(PlayState* play, DynaPolyActor* dynaActor, CollisionHeader* meshHeader);
void DynaPolyActor_ResetState(DynaPolyActor* dynaActor);
void DynaPolyActor_SetRidingFallingState(DynaPolyActor* dynaActor);
void DynaPolyActor_SetRidingMovingState(DynaPolyActor* dynaActor);
void DynaPolyActor_SetRidingMovingStateByIndex(CollisionContext* colCtx, s32 index);
void DynaPolyActor_SetRidingRotatingState(DynaPolyActor* dynaActor);
void DynaPolyActor_SetRidingRotatingStateByIndex(CollisionContext* colCtx, s32 index);
void DynaPolyActor_SetSwitchPressedState(DynaPolyActor* dynaActor);
void DynaPolyActor_SetHeavySwitchPressedState(DynaPolyActor* dynaActor);
s32 DynaPolyActor_IsInRidingFallingState(DynaPolyActor* dynaActor);
s32 DynaPolyActor_IsInRidingMovingState(DynaPolyActor* dynaActor);
s32 DynaPolyActor_IsInRidingRotatingState(DynaPolyActor* dynaActor);
s32 DynaPolyActor_IsInSwitchPressedState(DynaPolyActor* dynaActor);
s32 DynaPolyActor_IsInHeavySwitchPressedState(DynaPolyActor* dynaActor);
s32 DynaPolyActor_ValidateMove(PlayState* play, DynaPolyActor* dynaActor, s16 startRadius, s16 endRadius,
                               s16 startHeight);
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
// void Camera_IsSwimming(void);
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
// Camera_GetBgCamOrActorCsCamSetting(void); void Camera_GetBgCamOrActorCsCamFuncData(void); void
// Camera_GetBgCamIndex(void); void Camera_GetWaterBoxBgCamSetting(void); void func_800CC938(void); void
// func_800CC958(void); void func_800CC9C0(void); void func_800CCCEC(void); void func_800CD04C(void); void
// func_800CD288(void); void func_800CD2E0(void); void func_800CD2F0(void); void func_800CD3E4(UNK_TYPE1 param_1,
// UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5); void func_800CD44C(UNK_TYPE1 param_1,
// UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE2 param_5); void func_800CD634(void); void
// func_800CD6CC(void); void func_800CD6F8(void); void func_800CD834(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1
// param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5); void func_800CDA14(void); void func_800CDB6C(UNK_TYPE1 param_1,
// UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE2 param_6); void
// func_800CDE6C(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5,
// UNK_TYPE4 param_6, UNK_TYPE4 param_7, UNK_TYPE2 param_8); void func_800CE2B8(UNK_TYPE1 param_1, UNK_TYPE1 param_2,
// UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6, UNK_TYPE4 param_7, UNK_TYPE4 param_8,
// UNK_TYPE2 param_9); void func_800CE5E0(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4,
// UNK_TYPE2 param_5); void func_800CE79C(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4,
// UNK_TYPE2 param_5); void func_800CE930(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4,
// UNK_TYPE2 param_5); void func_800CEAD8(void); void func_800CEC38(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1
// param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5); void func_800CED90(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1
// param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6, UNK_TYPE4 param_7);
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
Camera* Camera_Alloc(View* view, CollisionContext* bg, PlayState* play);
void Camera_Free(Camera* camera);
void Camera_Init(Camera* camera, View* view, CollisionContext* bg, PlayState* play);
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
s32 Camera_ChangeMode(Camera* camera, s16 mode);
// void func_800DF86C(void);
// void func_800DF8EC(void);
s32 Camera_ChangeSetting(Camera* camera, s16 setting);
u32 Camera_ChangeDataIdx(Camera* camera, u32 camDataIdx);
// void func_800DFC1C(void);
// void func_800DFC40(void);
s32 Camera_GetInputDirYaw(Camera* camera);
void Camera_GetCamDir(Vec3s* dst, Camera* camera);
s16 Camera_GetCamDirPitch(Camera* camera);
s16 Camera_GetCamDirYaw(Camera* camera);
void Camera_AddQuake(Camera* camera, s32 arg1, s16 y, s32 countdown);
void func_800DFD78(Camera* camera, s32 paramFlag, void* value);
// UNK_TYPE4 func_800DFEF0(s32 param_1, u16 param_2);
// UNK_TYPE4 func_800DFF18(Camera* iParm1, UNK_TYPE2 uParm2);
// UNK_TYPE4 func_800DFF34(s32 param_1);
// UNK_TYPE4 func_800DFF44(void);
s16 Camera_SetFlags(Camera* iParm1, s16 flags);
s16 Camera_ClearFlags(Camera* camera, s16 flags);
s32 Camera_ChangeDoorCam(Camera* camera, Actor* doorActor, s16 bgCamDataId, f32 arg3, s16 timer1, s16 timer2,
                         s16 timer3);
// UNK_TYPE4 func_800E007C(Camera* param_1, Camera* param_2);
// UNK_TYPE4 func_800E01AC(void);
Vec3f* Camera_GetQuakeOffset(Vec3f* dst, Camera* camera);
// void func_800E01DC(s32 param_1, u32 param_2, UNK_TYPE4 param_3, UNK_TYPE4 param_4, UNK_TYPE2 param_5, UNK_TYPE2
// param_6); UNK_TYPE4 func_800E0228(void); void func_800E0238(void);
void Camera_SetToTrackActor(Camera* camera, Actor* actor);
void Camera_SetTargetActor(Camera* camera, Actor* actor);
f32 Camera_GetWaterYPos(Camera* camera);
void func_800E0348(Camera* camera);
DamageTable* DamageTable_Get(s32 index);
void DamageTable_Clear(DamageTable* damageTable);
f32 CollisionCheck_GetDamageAndEffectOnBumper(Collider* at, ColliderInfo* atInfo, Collider* ac, ColliderInfo* acInfo,
                                              u32* effect);
f32 CollisionCheck_ApplyBumperDefense(f32 damage, ColliderInfo* ac);
s32 CollisionCheck_GetToucherDamage(Collider* at, ColliderInfo* atInfo, Collider* ac, ColliderInfo* acInfo);
s32 Collider_InitBase(PlayState* play, Collider* collider);
s32 Collider_DestroyBase(PlayState* play, Collider* collider);
s32 Collider_SetBaseToActor(PlayState* play, Collider* collider, ColliderInitToActor* src);
s32 Collider_SetBaseType1(PlayState* play, Collider* collider, Actor* actor, ColliderInitType1* src);
s32 Collider_SetBase(PlayState* play, Collider* collider, Actor* actor, ColliderInit* src);
void Collider_ResetATBase(PlayState* play, Collider* collider);
void Collider_ResetACBase(PlayState* play, Collider* collider);
void Collider_ResetOCBase(PlayState* play, Collider* collider);
s32 Collider_InitTouch(PlayState* play, ColliderTouch* touch);
s32 Collider_DestroyTouch(PlayState* play, ColliderTouch* touch);
s32 Collider_SetTouch(PlayState* play, ColliderTouch* touch, ColliderTouchInit* src);
void Collider_ResetATInfoUnk(PlayState* play, ColliderInfo* info);
s32 Collider_InitBump(PlayState* play, ColliderBump* bump);
s32 Collider_DestroyBump(PlayState* play, ColliderBump* bump);
s32 Collider_SetBump(PlayState* play, ColliderBump* bump, ColliderBumpInit* src);
s32 Collider_InitInfo(PlayState* play, ColliderInfo* info);
s32 Collider_DestroyInfo(PlayState* play, ColliderInfo* info);
s32 Collider_SetInfo(PlayState* play, ColliderInfo* info, ColliderInfoInit* src);
void Collider_ResetATInfo(PlayState* play, ColliderInfo* info);
void Collider_ResetACInfo(PlayState* play, ColliderInfo* info);
void Collider_ResetOCInfo(PlayState* play, ColliderInfo* info);
s32 Collider_InitJntSphElementDim(PlayState* play, ColliderJntSphElementDim* dim);
s32 Collider_DestroyJntSphElementDim(PlayState* play, ColliderJntSphElementDim* dim);
s32 Collider_SetJntSphElementDim(PlayState* play, ColliderJntSphElementDim* dest, ColliderJntSphElementDimInit* src);
s32 Collider_InitJntSphElement(PlayState* play, ColliderJntSphElement* element);
s32 Collider_DestroyJntSphElement(PlayState* play, ColliderJntSphElement* element);
s32 Collider_SetJntSphElement(PlayState* play, ColliderJntSphElement* dest, ColliderJntSphElementInit* src);
s32 Collider_ResetJntSphElementAT(PlayState* play, ColliderJntSphElement* collider);
s32 Collider_ResetJntSphElementAC(PlayState* play, ColliderJntSphElement* collider);
s32 Collider_ResetJntSphElementOC(PlayState* play, ColliderJntSphElement* collider);
s32 Collider_InitJntSph(PlayState* play, ColliderJntSph* collider);
s32 Collider_FreeJntSph(PlayState* play, ColliderJntSph* collider);
s32 Collider_DestroyJntSph(PlayState* play, ColliderJntSph* collider);
s32 Collider_SetJntSphToActor(PlayState* play, ColliderJntSph* collider, ColliderJntSphInitToActor* src);
s32 Collider_SetJntSphAllocType1(PlayState* play, ColliderJntSph* sphereGroup, Actor* actor,
                                 ColliderJntSphInitType1* src);
s32 Collider_SetJntSph(PlayState* play, ColliderJntSph* sphereGroup, Actor* actor, ColliderJntSphInit* src,
                       ColliderJntSphElement* elements);
s32 Collider_InitAndSetJntSph(PlayState* play, ColliderJntSph* sphereGroup, Actor* actor, ColliderJntSphInit* src,
                              ColliderJntSphElement* elements);
s32 Collider_ResetJntSphAT(PlayState* play, Collider* collider);
s32 Collider_ResetJntSphAC(PlayState* play, Collider* collider);
s32 Collider_ResetJntSphOC(PlayState* play, Collider* collider);
s32 Collider_InitCylinderDim(PlayState* play, Cylinder16* dim);
s32 Collider_DestroyCylinderDim(PlayState* play, Cylinder16* dim);
s32 Collider_SetCylinderDim(PlayState* play, Cylinder16* dim, Cylinder16* src);
s32 Collider_InitCylinder(PlayState* play, ColliderCylinder* collider);
s32 Collider_DestroyCylinder(PlayState* play, ColliderCylinder* collider);
s32 Collider_SetCylinderToActor(PlayState* play, ColliderCylinder* collider, ColliderCylinderInitToActor* src);
s32 Collider_SetCylinderType1(PlayState* play, ColliderCylinder* collider, Actor* actor,
                              ColliderCylinderInitType1* src);
s32 Collider_SetCylinder(PlayState* play, ColliderCylinder* collider, Actor* actor, ColliderCylinderInit* src);
s32 Collider_InitAndSetCylinder(PlayState* play, ColliderCylinder* collider, Actor* actor, ColliderCylinderInit* src);
s32 Collider_ResetCylinderAT(PlayState* play, Collider* collider);
s32 Collider_ResetCylinderAC(PlayState* play, Collider* collider);
s32 Collider_ResetCylinderOC(PlayState* play, Collider* collider);
s32 Collider_InitTrisElementDim(PlayState* play, TriNorm* dim);
s32 Collider_DestroyTrisElementDim(PlayState* play, TriNorm* dim);
s32 Collider_SetTrisElementDim(PlayState* play, TriNorm* dim, ColliderTrisElementDimInit* src);
s32 Collider_InitTrisElement(PlayState* play, ColliderTrisElement* element);
s32 Collider_DestroyTrisElement(PlayState* play, ColliderTrisElement* element);
s32 Collider_SetTrisElement(PlayState* play, ColliderTrisElement* element, ColliderTrisElementInit* src);
s32 Collider_ResetTrisElementAT(PlayState* play, ColliderTrisElement* element);
s32 Collider_ResetTrisElementAC(PlayState* play, ColliderTrisElement* element);
s32 Collider_ResetTrisElementOC(PlayState* play, ColliderTrisElement* element);
s32 Collider_InitTris(PlayState* play, ColliderTris* tris);
s32 Collider_FreeTris(PlayState* play, ColliderTris* tris);
s32 Collider_DestroyTris(PlayState* play, ColliderTris* tris);
s32 Collider_SetTrisAllocType1(PlayState* play, ColliderTris* tris, Actor* actor, ColliderTrisInitType1* src);
s32 Collider_SetTris(PlayState* play, ColliderTris* triGroup, Actor* actor, ColliderTrisInit* src,
                     ColliderTrisElement* tris);
s32 Collider_InitAndSetTris(PlayState* play, ColliderTris* tris, Actor* actor, ColliderTrisInit* src,
                            ColliderTrisElement* elements);
s32 Collider_ResetTrisAT(PlayState* play, Collider* collider);
s32 Collider_ResetTrisAC(PlayState* play, Collider* collider);
s32 Collider_ResetTrisOC(PlayState* play, Collider* collider);
s32 Collider_InitQuadDim(PlayState* play, ColliderQuadDim* dim);
s32 Collider_DestroyQuadDim(PlayState* play, ColliderQuadDim* dim);
s32 Collider_ResetQuadACDist(PlayState* play, ColliderQuadDim* dim);
void Collider_SetQuadMidpoints(ColliderQuadDim* dim);
s32 Collider_SetQuadDim(PlayState* play, ColliderQuadDim* dim, ColliderQuadDimInit* init);
s32 Collider_InitQuad(PlayState* play, ColliderQuad* collider);
s32 Collider_DestroyQuad(PlayState* play, ColliderQuad* collider);
s32 Collider_SetQuadType1(PlayState* play, ColliderQuad* collider, Actor* actor, ColliderQuadInitType1* src);
s32 Collider_SetQuad(PlayState* play, ColliderQuad* collider, Actor* actor, ColliderQuadInit* src);
s32 Collider_InitAndSetQuad(PlayState* play, ColliderQuad* collider, Actor* actor, ColliderQuadInit* src);
s32 Collider_ResetQuadAT(PlayState* play, Collider* collider);
s32 Collider_ResetQuadAC(PlayState* play, Collider* collider);
s32 Collider_ResetQuadOC(PlayState* play, Collider* collider);
s32 Collider_QuadSetNearestAC(PlayState* play, ColliderQuad* quad, Vec3f* hitPos);
s32 Collider_InitSphere(PlayState* play, ColliderSphere* collider);
s32 Collider_DestroySphere(PlayState* play, ColliderSphere* collider);
s32 Collider_SetSphere(PlayState* play, ColliderSphere* collider, Actor* actor, ColliderSphereInit* src);
s32 Collider_InitAndSetSphere(PlayState* play, ColliderSphere* collider, Actor* actor, ColliderSphereInit* src);
s32 Collider_ResetSphereAT(PlayState* play, Collider* collider);
s32 Collider_ResetSphereAC(PlayState* play, Collider* collider);
s32 Collider_ResetSphereOC(PlayState* play, Collider* collider);
s32 Collider_InitLine(PlayState* play, OcLine* line);
s32 Collider_DestroyLine(PlayState* play, OcLine* line);
s32 Collider_SetLinePoints(PlayState* play, OcLine* line, Vec3f* a, Vec3f* b);
s32 Collider_SetLine(PlayState* play, OcLine* line, OcLine* src);
s32 Collider_ResetLineOC(PlayState* play, OcLine* line);
void CollisionCheck_InitContext(PlayState* play, CollisionCheckContext* colCtxt);
void CollisionCheck_DestroyContext(PlayState* play, CollisionCheckContext* colCtxt);
void CollisionCheck_ClearContext(PlayState* play, CollisionCheckContext* colCtxt);
void CollisionCheck_EnableSAC(PlayState* play, CollisionCheckContext* colCtxt);
void CollisionCheck_DisableSAC(PlayState* play, CollisionCheckContext* colCtxt);
s32 CollisionCheck_SetAT(PlayState* play, CollisionCheckContext* colCtxt, Collider* collider);
s32 CollisionCheck_SetAT_SAC(PlayState* play, CollisionCheckContext* colCtxt, Collider* collider, s32 index);
s32 CollisionCheck_SetAC(PlayState* play, CollisionCheckContext* colCtxt, Collider* collider);
s32 CollisionCheck_SetAC_SAC(PlayState* play, CollisionCheckContext* colCtxt, Collider* collider, s32 index);
s32 CollisionCheck_SetOC(PlayState* play, CollisionCheckContext* colCtxt, Collider* collider);
s32 CollisionCheck_SetOC_SAC(PlayState* play, CollisionCheckContext* colCtxt, Collider* collider, s32 index);
s32 CollisionCheck_SetOCLine(PlayState* play, CollisionCheckContext* colCtxt, OcLine* line);
s32 CollisionCheck_SkipTouch(ColliderInfo* info);
s32 CollisionCheck_SkipBump(ColliderInfo* info);
s32 CollisionCheck_NoSharedFlags(ColliderInfo* toucher, ColliderInfo* bumper);
void CollisionCheck_NoBlood(PlayState* play, Collider* collider, Vec3f* v);
void CollisionCheck_BlueBlood(PlayState* play, Collider* collider, Vec3f* v);
void CollisionCheck_GreenBlood(PlayState* play, Collider* collider, Vec3f* v);
void CollisionCheck_WaterBurst(PlayState* play, Collider* collider, Vec3f* v);
void CollisionCheck_RedBlood(PlayState* play, Collider* collider, Vec3f* v);
void CollisionCheck_RedBloodUnused(PlayState* play, Collider* collider, Vec3f* v);
void CollisionCheck_HitSolid(PlayState* play, ColliderInfo* info, Collider* collider, Vec3f* hitPos);
s32 CollisionCheck_SwordHitAudio(Collider* at, ColliderInfo* acInfo);
void CollisionCheck_HitEffects(PlayState* play, Collider* at, ColliderInfo* atInfo, Collider* ac, ColliderInfo* acInfo,
                               Vec3f* hitPos);
void CollisionCheck_SetBounce(Collider* at, Collider* ac);
s32 CollisionCheck_SetATvsAC(PlayState* play, Collider* at, ColliderInfo* atInfo, Vec3f* atPos, Collider* ac,
                             ColliderInfo* acInfo, Vec3f* acPos, Vec3f* hitPos);
void CollisionCheck_TrisAvgPoint(ColliderTrisElement* tri, Vec3f* avg);
void CollisionCheck_QuadAvgPoint(ColliderQuad* quad, Vec3f* avg);
void CollisionCheck_AC_JntSphVsJntSph(PlayState* play, CollisionCheckContext* colCtxt, Collider* colAT,
                                      Collider* colAC);
void CollisionCheck_AC_JntSphVsCyl(PlayState* play, CollisionCheckContext* colCtxt, Collider* colAT, Collider* colAC);
void CollisionCheck_AC_JntSphVsTris(PlayState* play, CollisionCheckContext* colCtxt, Collider* colAT, Collider* colAC);
void CollisionCheck_AC_JntSphVsQuad(PlayState* play, CollisionCheckContext* colCtxt, Collider* colAT, Collider* colAC);
void CollisionCheck_AC_JntSphVsSphere(PlayState* play, CollisionCheckContext* colCtxt, Collider* colAT,
                                      Collider* colAC);
void CollisionCheck_AC_CylVsJntSph(PlayState* play, CollisionCheckContext* colCtxt, Collider* colAT, Collider* colAC);
void CollisionCheck_AC_CylVsCyl(PlayState* play, CollisionCheckContext* colCtxt, Collider* colAT, Collider* colAC);
void CollisionCheck_AC_CylVsTris(PlayState* play, CollisionCheckContext* colCtxt, Collider* colAT, Collider* colAC);
void CollisionCheck_AC_CylVsQuad(PlayState* play, CollisionCheckContext* colCtxt, Collider* colAT, Collider* colAC);
void CollisionCheck_AC_CylVsSphere(PlayState* play, CollisionCheckContext* colCtxt, Collider* colAT, Collider* colAC);
void CollisionCheck_AC_TrisVsJntSph(PlayState* play, CollisionCheckContext* colCtxt, Collider* colAT, Collider* colAC);
void CollisionCheck_AC_TrisVsCyl(PlayState* play, CollisionCheckContext* colCtxt, Collider* colAT, Collider* colAC);
void CollisionCheck_AC_TrisVsTris(PlayState* play, CollisionCheckContext* colCtxt, Collider* colAT, Collider* colAC);
void CollisionCheck_AC_TrisVsQuad(PlayState* play, CollisionCheckContext* colCtxt, Collider* colAT, Collider* colAC);
void CollisionCheck_AC_TrisVsSphere(PlayState* play, CollisionCheckContext* colCtxt, Collider* colAT, Collider* colAC);
void CollisionCheck_AC_QuadVsJntSph(PlayState* play, CollisionCheckContext* colCtxt, Collider* colAT, Collider* colAC);
void CollisionCheck_AC_QuadVsCyl(PlayState* play, CollisionCheckContext* colCtxt, Collider* colAT, Collider* colAC);
void CollisionCheck_AC_QuadVsTris(PlayState* play, CollisionCheckContext* colCtxt, Collider* colAT, Collider* colAC);
void CollisionCheck_AC_QuadVsQuad(PlayState* play, CollisionCheckContext* colCtxt, Collider* colAT, Collider* colAC);
void CollisionCheck_AC_QuadVsSphere(PlayState* play, CollisionCheckContext* colCtxt, Collider* colAT, Collider* colAC);
void CollisionCheck_AC_SphereVsJntSph(PlayState* play, CollisionCheckContext* colCtxt, Collider* colAT,
                                      Collider* colAC);
void CollisionCheck_AC_SphereVsCylinder(PlayState* play, CollisionCheckContext* colCtxt, Collider* colAT,
                                        Collider* colAC);
void CollisionCheck_AC_SphereVsTris(PlayState* play, CollisionCheckContext* colCtxt, Collider* colAT, Collider* colAC);
void CollisionCheck_AC_SphereVsQuad(PlayState* play, CollisionCheckContext* colCtxt, Collider* colAT, Collider* colAC);
void CollisionCheck_AC_SphereVsSphere(PlayState* play, CollisionCheckContext* colCtxt, Collider* colAT,
                                      Collider* colAC);
void CollisionCheck_SetJntSphHitFX(PlayState* play, CollisionCheckContext* colCtxt, Collider* collider);
void CollisionCheck_SetCylHitFX(PlayState* play, CollisionCheckContext* colCtxt, Collider* collider);
void CollisionCheck_SetTrisHitFX(PlayState* play, CollisionCheckContext* colCtxt, Collider* collider);
void CollisionCheck_SetQuadHitFX(PlayState* play, CollisionCheckContext* colCtxt, Collider* collider);
void CollisionCheck_SetSphereHitFX(PlayState* play, CollisionCheckContext* colCtxt, Collider* collider);
void CollisionCheck_SetHitEffects(PlayState* play, CollisionCheckContext* colCtxt);
void CollisionCheck_AC(PlayState* play, CollisionCheckContext* colCtxt, Collider* colAT);
void CollisionCheck_AT(PlayState* play, CollisionCheckContext* colCtxt);
s32 CollisionCheck_GetMassType(u8 mass);
void CollisionCheck_SetOCvsOC(PlayState* play, Collider* left, ColliderInfo* leftInfo, Vec3f* leftPos, Collider* right,
                              ColliderInfo* rightInfo, Vec3f* rightPos, f32 overlap);
void CollisionCheck_OC_JntSphVsJntSph(PlayState* play, CollisionCheckContext* colCtxt, Collider* l, Collider* r);
void CollisionCheck_OC_JntSphVsCyl(PlayState* play, CollisionCheckContext* colCtxt, Collider* l, Collider* r);
void CollisionCheck_OC_JntSphVsSphere(PlayState* play, CollisionCheckContext* colCtxt, Collider* l, Collider* r);
void CollisionCheck_OC_CylVsJntSph(PlayState* play, CollisionCheckContext* colCtxt, Collider* l, Collider* r);
void CollisionCheck_OC_CylVsCyl(PlayState* play, CollisionCheckContext* colCtxt, Collider* l, Collider* r);
void CollisionCheck_OC_CylVsSphere(PlayState* play, CollisionCheckContext* colCtxt, Collider* l, Collider* r);
void CollisionCheck_OC_SphereVsJntSph(PlayState* play, CollisionCheckContext* colCtxt, Collider* l, Collider* r);
void CollisionCheck_OC_SphereVsCyl(PlayState* play, CollisionCheckContext* colCtxt, Collider* l, Collider* r);
void CollisionCheck_OC_SphereVsSphere(PlayState* play, CollisionCheckContext* colCtxt, Collider* l, Collider* r);
s32 CollisionCheck_SkipOC(Collider* collider);
s32 CollisionCheck_Incompatible(Collider* left, Collider* right);
void CollisionCheck_OC(PlayState* play, CollisionCheckContext* colCtxt);
void CollisionCheck_InitInfo(CollisionCheckInfo* info);
void CollisionCheck_ResetDamage(CollisionCheckInfo* info);
void CollisionCheck_SetInfoNoDamageTable(CollisionCheckInfo* info, CollisionCheckInfoInit* init);
void CollisionCheck_SetInfo(CollisionCheckInfo* info, DamageTable* damageTable, CollisionCheckInfoInit* init);
void CollisionCheck_SetInfo2(CollisionCheckInfo* info, DamageTable* damageTable, CollisionCheckInfoInit2* init);
void CollisionCheck_SetInfoGetDamageTable(CollisionCheckInfo* info, s32 index, CollisionCheckInfoInit2* init);
void CollisionCheck_ApplyDamage(PlayState* play, CollisionCheckContext* colCtxt, Collider* collider,
                                ColliderInfo* info);
void CollisionCheck_ApplyDamageJntSph(PlayState* play, CollisionCheckContext* colCtxt, Collider* collider);
void CollisionCheck_ApplyDamageCyl(PlayState* play, CollisionCheckContext* colCtxt, Collider* collider);
void CollisionCheck_ApplyDamageTris(PlayState* play, CollisionCheckContext* colCtxt, Collider* collider);
void CollisionCheck_ApplyDamageQuad(PlayState* play, CollisionCheckContext* colCtxt, Collider* collider);
void CollisionCheck_ApplyDamageSphere(PlayState* play, CollisionCheckContext* colCtxt, Collider* collider);
void CollisionCheck_Damage(PlayState* play, CollisionCheckContext* colCtxt);
s32 CollisionCheck_LineOC_JntSph(PlayState* play, CollisionCheckContext* colChkCtx, Collider* collider, Vec3f* a,
                                 Vec3f* b);
s32 CollisionCheck_LineOC_Cyl(PlayState* play, CollisionCheckContext* colChkCtx, Collider* collider, Vec3f* a,
                              Vec3f* b);
s32 CollisionCheck_LineOC_Sphere(PlayState* play, CollisionCheckContext* colChkCtx, Collider* collider, Vec3f* a,
                                 Vec3f* b);
s32 CollisionCheck_LineOC(PlayState* play, CollisionCheckContext* colChkCtx, Vec3f* a, Vec3f* b, Actor** exclusions,
                          s32 numExclusions);
s32 CollisionCheck_LineOCCheckAll(PlayState* play, CollisionCheckContext* colCtxt, Vec3f* a, Vec3f* b);
s32 CollisionCheck_LineOCCheck(PlayState* play, CollisionCheckContext* colCtxt, Vec3f* a, Vec3f* b, Actor** exclusions,
                               s32 numExclusions);
void Collider_UpdateCylinder(Actor* actor, ColliderCylinder* collider);
void Collider_SetCylinderPosition(ColliderCylinder* collider, Vec3s* pos);
void Collider_SetQuadVertices(ColliderQuad* collider, Vec3f* a, Vec3f* b, Vec3f* c, Vec3f* d);
void Collider_SetTrisVertices(ColliderTris* collider, s32 index, Vec3f* a, Vec3f* b, Vec3f* c);
void Collider_SetTrisDim(PlayState* play, ColliderTris* collider, s32 index, ColliderTrisElementDimInit* init);
void Collider_UpdateSpheres(s32 limb, ColliderJntSph* collider);
void Collider_UpdateSpheresElement(ColliderJntSph* collider, s32 index, Actor* actor);
void Collider_UpdateSphere(s32 limb, ColliderSphere* collider);
void CollisionCheck_SpawnRedBlood(PlayState* play, Vec3f* v);
void CollisionCheck_SpawnWaterDroplets(PlayState* play, Vec3f* v);
void CollisionCheck_SpawnShieldParticles(PlayState* play, Vec3f* v);
void CollisionCheck_SpawnShieldParticlesMetal(PlayState* play, Vec3f* v);
void CollisionCheck_SpawnShieldParticlesMetalSound(PlayState* play, Vec3f* v, Vec3f* pos);
void CollisionCheck_SpawnShieldParticlesMetal2(PlayState* play, Vec3f* v);
void CollisionCheck_SpawnShieldParticlesWood(PlayState* play, Vec3f* v, Vec3f* pos);
s32 CollisionCheck_CylSideVsLineSeg(f32 radius, f32 height, f32 offset, Vec3f* actorPos, Vec3f* itemPos,
                                    Vec3f* itemProjPos, Vec3f* out1, Vec3f* out2);
void Actor_ContinueText(PlayState* play, Actor* actor, u16 textId);
s32 Flags_GetEventChkInf(s32 flag);
void Flags_SetEventChkInf(s32 flag);
s32 Flags_GetInfTable(s32 flag);
void Flags_SetInfTable(s32 flag);
s32 Actor_TrackNone(Vec3s* headRot, Vec3s* torsoRot);
s32 Actor_TrackPoint(Actor* actor, Vec3f* target, Vec3s* headRot, Vec3s* torsoRot);
s32 Actor_TrackPlayerSetFocusHeight(PlayState* play, Actor* actor, Vec3s* headRot, Vec3s* torsoRot, f32 focusPosYAdj);
s32 Actor_TrackPlayer(PlayState* play, Actor* actor, Vec3s* headRot, Vec3s* torsoRot, Vec3f focusPos);
void SaveContext_Init(void);
void GameInfo_Init(void);
// void DebugDisplay_Init(void);
DebugDispObject* DebugDisplay_AddObject(f32 posX, f32 posY, f32 posZ, s16 rotX, s16 rotY, s16 rotZ, f32 scaleX,
                                        f32 scaleY, f32 scaleZ, u8 red, u8 green, u8 blue, u8 alpha, s16 type,
                                        GraphicsContext* gfxCtx);
// void func_800E9C90(void);
// void func_800E9CA0(s32 param_1, UNK_TYPE1 param_2, s8* param_3);
// void func_800E9CFC(void);
// void func_800E9DBC(void);
// void func_800E9E94(void);
void func_800E9F78(GraphicsContext* gfxCtx);

void Cutscene_Init(PlayState* play, CutsceneContext* csCtx);
void Cutscene_Start(PlayState* play, CutsceneContext* csCtx);
void Cutscene_End(PlayState* play, CutsceneContext* csCtx);
void Cutscene_Update1(PlayState* play, CutsceneContext* csCtx);
void Cutscene_Update2(PlayState* play, CutsceneContext* csCtx);
void func_800EDBE0(PlayState* play);
void func_800EDDB0(PlayState* play);
void Cutscene_LoadCutsceneData(PlayState* play, u8 csIndex);
void Cutscene_ActorTranslate(Actor* actor, PlayState* play, s32 actorActionIndex);
void Cutscene_ActorTranslateAndYaw(Actor* actor, PlayState* play, s32 actorActionIndex);
void Cutscene_ActorTranslateAndYawSmooth(Actor* actor, PlayState* play, s32 actorActionIndex);
void Cutscene_ActorTranslateXZAndYawSmooth(Actor* actor, PlayState* play, s32 actorActionIndex);
s32 Cutscene_GetSceneSetupIndex(PlayState* play);
s32 Cutscene_GetActorActionIndex(PlayState* play, u16 actorActionCmd);
s32 Cutscene_CheckActorAction(PlayState* play, u16 actorActionCmd);
u8 Cutscene_IsPlaying(PlayState* play);

void GetItem_Draw(PlayState* play, s16 drawId);

void EffFootmark_Init(PlayState* play);
void EffFootmark_Add(PlayState* play, MtxF* displayMatrix, Actor* actor, u8 id, Vec3f* location, u16 size, u8 red,
                     u8 green, u8 blue, u16 alpha, u16 alphaChange, u16 fadeoutDelay);
void EffFootmark_Update(PlayState* play);
void EffFootmark_Draw(PlayState* play);
void SoundSource_InitAll(PlayState* play);
void SoundSource_UpdateAll(PlayState* play);
void SoundSource_PlaySfxAtFixedWorldPos(PlayState* play, Vec3f* worldPos, u32 duration, u16 sfxId);
void SoundSource_PlaySfxEachFrameAtFixedWorldPos(PlayState* play, Vec3f* worldPos, u32 duration, u16 sfxId);
u16 ElfMessage_GetFirstCycleHint(PlayState* play);

u16 Text_GetFaceReaction(PlayState* play, u32 reactionSet);
void EnvFlags_UnsetAll(PlayState* play);
void EnvFlags_Set(PlayState* play, s16 flag);
void EnvFlags_Unset(PlayState* play, s16 flag);
s32 EnvFlags_Get(PlayState* play, s16 flag);
s16 func_800F1460(s16 param_1);
ActorCutscene* ActorCutscene_GetCutsceneImpl(s16 index);
void ActorCutscene_Init(PlayState* play, ActorCutscene* cutscenes, s32 num);
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
s32 func_800F2138(s32 arg0);
s32 func_800F2178(s16 arg0);
s16 ActorCutscene_GetCurrentSubCamId(s16 index);
s16 func_800F21CC(void);
s32 func_800F22C4(s16 param_1, Actor* actor);
void ActorCutscene_SetReturnCamera(s16 index);
void FireObj_SetPosition(FireObj* fire, Vec3f* pos);
void FireObj_Draw(PlayState* play, FireObj* fire);
void FireObj_Init(PlayState* play, FireObj* fire, FireObjInitParams* init, Actor* actor);
void FireObj_Destroy(PlayState* play, FireObj* fire);
void FireObj_SetState2(FireObj* fire, f32 dynamicSizeStep, u8 newState);
void FireObj_Update(PlayState* play, FireObj* fire, Actor* actor);
s32 func_800F3940(PlayState* play);
// void func_800F39B4(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5);
// void func_800F3A64(void);
void func_800F3B2C(PlayState* play);
// void func_800F3B68(void);
// void func_800F3C44(void);
// void func_800F3ED4(void);
void func_800F40A0(GameState* gameState, Player* player);
void func_800F415C(Actor* actor, Vec3f* arg1, s16 arg2);
UNK_TYPE func_800F41E4(PlayState* play, ActorContext* actorCtx);

void func_800F4A10(PlayState* play);
void KaleidoSetup_Update(PlayState* play);
void KaleidoSetup_Init(PlayState* play);
void KaleidoSetup_Destroy(PlayState* play);

void Font_LoadChar(PlayState* play, u16 codePointIndex, s32 offset);
void Font_LoadCharNES(PlayState* play, u8 codePointIndex, s32 offset);
void Font_LoadMessageBoxEndIcon(Font* font, u16 icon);
void Font_LoadOrderedFont(Font* font);
// void func_800F5090(void);
// void func_800F50D4(void);
void Kankyo_Init(PlayState* play, EnvironmentContext* envCtx);
u32 func_800F5954(u8* param_1, u32 param_2, u32 param_3, u8 param_4, u8 param_5);
f32 Environment_LerpWeight(u16 max, u16 min, u16 val);
// void func_800F5B10(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE2 param_5);
// void func_800F5CD0(void);
void func_800F6834(PlayState* play, s32 waterLightsIndex);
// void func_800F694C(void);
// void func_800F6A04(void);
// void func_800F6A40(void);
// void func_800F6AB8(void);
void func_800F6B44(PlayState* play, EnvironmentContext* envCtx, s32 iParm3, s32 iParm4, s16* param_5);
// void func_800F6CEC(void);
// void func_800F6EA4(void);
// UNK_TYPE4 Kankyo_IsSceneUpsideDown(PlayState* play);
void func_800F6FF8(PlayState* play, EnvironmentContext* envCtx, LightContext* lightCtx);
// void func_800F8554(void);
// void func_800F88C4(void);
// void func_800F8970(void);
// void func_800F8A9C(void);
// void func_800F8CD4(PlayState* play, EnvironmentContext* envCtx, LightContext* lightCtx, s32 param_4, UNK_TYPE4
// param_5, UNK_TYPE4 param_6); void func_800F8D84(void); void func_800F9728(UNK_TYPE1 param_1, UNK_TYPE1 param_2,
// UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6, UNK_TYPE4 param_7);
void func_800F9824(PlayState* play, EnvironmentContext* envCtx, View* view, GraphicsContext* gfxCtx, Vec3f vec,
                   f32 arg5, f32 arg6, s8 arg7, s8 arg8);
// void func_800FA39C(void);
// void func_800FA3C4(void);
// void func_800FA9FC(void);
void func_800FAAB4(PlayState* play, u8 arg1);
// void func_800FAC20(void);
// void func_800FAF74(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE1 param_5);
// void func_800FB010(void);
void Environment_AddLightningBolts(PlayState* play, u8 num);
// void func_800FB388(void);
void func_800FB758(PlayState* play);
// void func_800FB9B4(void);
// void func_800FBCBC(void);
void Kankyo_InitGameOverLights(PlayState* play);
void Kankyo_FadeInGameOverLights(PlayState* play);
void Kankyo_FadeOutGameOverLights(PlayState* play);
// void func_800FC3DC(void);
void func_800FC444(GraphicsContext* gfxCtx, u8 arg1, u8 arg2, u8 arg3, u8 arg4, UNK_TYPE arg5);
// void func_800FC64C(void);
s32 func_800FD2B4(PlayState* play, f32 arg1, f32 arg2, f32 arg3, f32 arg4);
void func_800FD538(Color_RGB8* param_1, Color_RGB8* param_2, f32 param_3, Vec3s* param_4);
void func_800FD59C(PlayState* play, Color_RGB8* pzParm2, f32 fParm3);
void func_800FD5E0(PlayState* play, Color_RGB8* pzParm2, f32 fParm3);
void func_800FD654(PlayState* play, Color_RGB8* pzParm2, f32 fParm3);
void func_800FD698(PlayState* play, s16 arg1, s16 arg2, f32 arg3);
// u32 get_days_elapsed(void);
// void reset_days_elapsed(void);
// u32 get_current_day(void);
void func_800FD750(u16 seqId);
// void func_800FD768(void);
void func_800FD78C(PlayState* play);
void func_800FD858(PlayState* play);
void func_800FD928(s32 param_1);
// void func_800FD980(void);
// void func_800FDAF8(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5);
// void func_800FDC94(void);
// void func_800FE390(void);
// void func_800FE3E0(void);
void func_800FE484(void);
void func_800FE498(void);
// void func_800FE4A8(void);
u32 func_800FE4B8(PlayState* play);
// void func_800FE590(void);
// void func_800FE5D0(void);
// UNK_TYPE4 func_800FE610(void);
u32 func_800FE620(PlayState* play);
void func_800FE658(f32 arg0);
// UNK_TYPE4 func_800FE6F8(UNK_TYPE4 param_1, s16 param_2, s16 param_3);
// void func_800FE778(void);
// void func_800FE788(void);
// void func_800FE798(void);
void func_800FE7A8(Color_RGBA8* inColor, Color_RGBA8* outColor);
s32 func_800FE9B4(PlayState* play);
void func_800FEA50(PlayState* play);
void func_800FEAB0(void);
// void func_800FEAC0(void);
void func_800FEAF4(EnvironmentContext* envCtx);
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
s16 Math_SmoothStepToS(s16* pValue, s16 target, s16 scale, s16 step, s16 minStep);
void Math_ApproachS(s16* pValue, s16 target, s16 scale, s16 maxStep);
void Color_RGBA8_Copy(Color_RGBA8* dst, Color_RGBA8* src);
void func_801000A4(u16 sfxId);
void func_801000CC(u16 sfxId);
void Lib_PlaySfxAtPos(Vec3f* pos, u16 sfxId);
void Lib_Vec3f_TranslateAndRotateY(Vec3f* translation, s16 rotAngle, Vec3f* src, Vec3f* dst);
void Lib_LerpRGB(Color_RGB8* a, Color_RGB8* b, f32 t, Color_RGB8* dst);
f32 Math_Vec3f_StepTo(Vec3f* start, Vec3f* target, f32 speed);
void Lib_Nop801004FC(void);
void* Lib_SegmentedToVirtual(void* ptr);
void* Lib_SegmentedToVirtualNull(void* ptr);
void* Lib_PhysicalToVirtual(void* ptr);
void* Lib_PhysicalToVirtualNull(void* ptr);
void LifeMeter_Init(PlayState* play);
void LifeMeter_UpdateColors(PlayState* play);
s32 LifeMeter_SaveInterfaceHealth(PlayState* play);
s32 LifeMeter_IncreaseInterfaceHealth(PlayState* play);
s32 LifeMeter_DecreaseInterfaceHealth(PlayState* play);
void LifeMeter_Draw(PlayState* play);
void LifeMeter_UpdateSizeAndBeep(PlayState* play);
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
void Lights_BindPoint(Lights* lights, LightParams* params, PlayState* play);
void Lights_BindDirectional(Lights* lights, LightParams* params, void* unused);
void Lights_BindAll(Lights* lights, LightNode* listHead, Vec3f* refPos, PlayState* play);
LightNode* Lights_FindBufSlot();
void Lights_FreeNode(LightNode* light);
void LightContext_Init(PlayState* play, LightContext* lightCtx);
void LightContext_SetAmbientColor(LightContext* lightCtx, u8 r, u8 g, u8 b);
void func_80102544(LightContext* lightCtx, u8 a1, u8 a2, u8 a3, s16 numLights, s16 sp16);
Lights* LightContext_NewLights(LightContext* lightCtx, GraphicsContext* gfxCtx);
void LightContext_InitList(PlayState* play, LightContext* lightCtx);
void LightContext_DestroyList(PlayState* play, LightContext* lightCtx);
LightNode* LightContext_InsertLight(PlayState* play, LightContext* lightCtx, LightInfo* info);
void LightContext_RemoveLight(PlayState* play, LightContext* lightCtx, LightNode* light);
Lights* Lights_NewAndDraw(GraphicsContext* gfxCtx, u8 ambientR, u8 ambientG, u8 ambientB, u8 numLights, u8 r, u8 g,
                          u8 b, s8 x, s8 y, s8 z);
Lights* Lights_New(GraphicsContext* gfxCtx, u8 ambientR, u8 ambientG, u8 ambientB);
void Lights_GlowCheck(PlayState* play);
void Lights_DrawGlow(PlayState* play);
void* ZeldaArena_Malloc(size_t size);
void* ZeldaArena_MallocR(size_t size);
void* ZeldaArena_Realloc(void* oldPtr, size_t newSize);
void ZeldaArena_Free(void* param_1);
void* ZeldaArena_Calloc(u32 num, size_t size);
void ZeldaArena_GetSizes(size_t* maxFreeBlock, size_t* bytesFree, size_t* bytesAllocated);
s32 ZeldaArena_Check();
void ZeldaArena_Init(void* start, size_t size);
void ZeldaArena_Cleanup();
u8 ZeldaArena_IsInitialized();
// void func_80102E40(void);
// void func_80102E90(void);
// void func_80102EA4(void);
void func_80102EB4(u32 param_1);
void func_80102ED0(u32 param_1);
s32 func_80102EF0(PlayState* play);
// void func_80102F9C(void);
// void func_80103090(void);
// void func_801030B4(void);
// void func_801030F4(void);
// void func_801031D0(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5,
// UNK_TYPE4 param_6); void func_801039EC(void); void func_80103A10(void); void func_80103A58(void); void
// func_8010439C(void); void func_801045AC(void); void func_80104AE8(void); void func_80104C80(void);
void func_80104CF4(PlayState* play);
// void func_80104F34(void);
s32 func_80105294(void);
s16 func_80105318(void);
// void func_80105328(void);
// void func_8010534C(void);
void func_8010549C(PlayState* play, void* segmentAddress);
void func_8010565C(PlayState* play, u8 num, void* segmentAddress);
void func_80105818(PlayState* play, u32 uParm2, TransitionActorEntry* puParm3);
void func_80105A40(void);
void func_80105B34(PlayState* play);
void func_80105C40(s16 arg0);
// void func_80105FE0(void);
// void func_80106408(void);
// void func_80106450(void);
// void func_801064CC(void);
s32 func_80106530(PlayState* play);
// void func_8010657C(void);
void func_80106644(PlayState* play, s16 arg1, s16 arg2, s16 arg3);
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
s32 func_80109124(s16 arg0);
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
s32 Map_GetDungeonOrBossAreaIndex(PlayState* play);
s32 Map_IsInDungeonOrBossArea(PlayState* play);
s32 func_8010A0A4(PlayState* play);
// void Map_GetDungeonAreaIndex(PlayState* play);
// void Map_IsInDungeonArea(PlayState* play);
// void Map_GetBossAreaIndex(PlayState* play);
// void Map_IsInBossArea(PlayState* play);
// void func_8010A238(PlayState* play);
// void func_8010A2AC(PlayState* play);
void Minimap_SavePlayerRoomInitInfo(PlayState* play);
void Map_InitRoomData(PlayState* play, s16 room);
// void Map_Destroy(void);
// void Map_Init(PlayState* play);
// void Minimap_Draw(PlayState* play);
// void Map_Update(PlayState* play);
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
s32 func_8010BF58(Actor* actor, PlayState* play, s32* param_3, UNK_PTR param_4, s32* param_5);
void Nmi_Init(void);
void Nmi_SetPrenmiStart(void);
// s32 Nmi_GetPrenmiHasStarted(void);
void MsgEvent_SendNullTask(void);
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
void func_8010EA9C(s32 arg0, s32 arg1);
// void func_8010EB50(void);
// void func_8010EBA0(void);
// void func_8010EC54(void);
void func_8010EE74(PlayState* play, s32 day);
void Interface_ChangeAlpha(u16 param_1);
// void func_8010EF9C(void);
// void func_8010F0D4(void);
// void func_8010F1A8(void);
// void func_80110038(void);
// void func_80111CB4(void);
// void func_801129E4(void);
void func_80112AFC(PlayState* play);
void Interface_LoadItemIconImpl(PlayState* play, u8 btn);
void Interface_LoadItemIcon(PlayState* play, u8 btn);
// void func_80112C0C(void);
u8 Item_Give(PlayState* play, u8 item);
u8 Item_CheckObtainability(u8 item);
void Inventory_DeleteItem(s16 item, s16 slot);
void Inventory_UnequipItem(s16 item);
s32 Inventory_ReplaceItem(PlayState* play, u8 oldItem, u8 newItem);
void Inventory_UpdateDeitySwordEquip(PlayState* play);
s32 Inventory_HasEmptyBottle(void);
s32 Inventory_HasItemInBottle(u8 item);
void Inventory_UpdateBottleItem(PlayState* play, u8 item, u8 btn);
s32 Inventory_ConsumeFairy(PlayState* play);
void Inventory_UpdateItem(PlayState* play, s16 slot, s16 item);
// void func_801153C8(void);
// void func_80115428(void);
void func_8011552C(PlayState* play, s16 arg1);
// void func_801155B4(void);
// void func_80115764(void);
void func_80115844(PlayState* play, s16 param_2);
s32 Health_ChangeBy(PlayState* play, s16 healthChange);
void Health_GiveHearts(s16 hearts);
void Rupees_ChangeBy(s16 rupeeChange);
void Inventory_ChangeAmmo(s16 item, s16 ammoChange);
void Parameter_AddMagic(PlayState* play, s16 arg1);
void func_80115D5C(GameState* gamestate);
s32 func_80115DB4(PlayState* play, s16 magicToConsume, s16 type);
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
void func_8011B4E0(PlayState* play, s32 arg1);
// void func_8011B5C0(void);
// void func_8011B9E0(void);
// void func_8011BF70(void);
// void func_8011C4C4(void);
void func_8011C808(PlayState* play);
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
void func_80121FC4(PlayState* play);
Path* Path_GetByIndex(PlayState* play, s16 index, s16 max);
f32 Path_OrientAndGetDistSq(Actor* actor, Path* path, s16 waypoint, s16* yaw);
void Path_CopyLastPoint(Path* path, Vec3f* dest);

void FrameAdvance_Init(FrameAdvanceContext* frameAdvCtx);
s32 FrameAdvance_Update(FrameAdvanceContext* frameAdvCtx, Input* input);

s32 func_801226E0(PlayState* play, s32 arg1);
s32 func_80122744(PlayState* play, struct_80122744_arg1* arg1, u32 arg2, Vec3s* arg3);
s32 func_80122760(PlayState* play, struct_80122744_arg1* arg1, f32 arg2);
void func_80122868(PlayState* play, Player* player);
void func_801229A0(PlayState* play, Player* player);
void func_801229EC(UNK_TYPE arg0, UNK_TYPE arg1);
void func_801229FC(Player* player);
void func_80122BA4(PlayState* play, struct_80122D44_arg1* arg1, s32 arg2, s32 alpha);
void func_80122C20(PlayState* play, struct_80122D44_arg1* arg1);
void func_80122D44(PlayState* play, struct_80122D44_arg1* arg1);
u8 Player_MaskIdToItemId(s32 maskIdMinusOne);
u8 Player_GetCurMaskItemId(PlayState* play);
void func_80122F28(Player* player);
s32 func_80122F9C(PlayState* play);
s32 func_80122FCC(PlayState* play);
void func_8012300C(PlayState* play, s32 arg1);
void func_8012301C(Player* player, PlayState* play);
void func_80123140(PlayState* play, Player* player);
s32 Player_InBlockingCsMode(PlayState* play, Player* player);
s32 Player_InCsMode(PlayState* play);
s32 func_80123420(Player* player);
s32 func_80123434(Player* player);
s32 func_80123448(PlayState* play);
s32 Player_IsGoronOrDeku(Player* player);
s32 func_801234D4(PlayState* play);
s32 func_80123590(PlayState* play, Actor* actor);
s32 func_8012364C(PlayState* play, Player* player, s32 arg2);
s32 func_80123810(PlayState* play);
s32 Player_ActionToModelGroup(Player* player, s32 actionParam);
void func_801239AC(Player* player);
void Player_SetModels(Player* player, s32 arg1);
void Player_SetModelGroup(Player* player, s32 modelGroup);
void func_80123C58(Player* player);
void Player_SetEquipmentData(PlayState* play, Player* this);
void func_80123D50(PlayState* play, Player* player, s32 itemId, s32 actionParam);
void func_80123DA4(Player* player);
void func_80123DC0(Player* player);
void func_80123E90(PlayState* play, Actor* actor);
s32 func_80123F2C(PlayState* play, s32 ammo);
s32 Player_IsBurningStickInRange(PlayState* play, Vec3f* pos, f32 xzRange, f32 yRange);
u8 Player_GetStrength(void);
u8 Player_GetMask(PlayState* play);
void Player_RemoveMask(PlayState* play);
s32 Player_HasMirrorShieldEquipped(PlayState* play);
s32 Player_IsHoldingMirrorShield(PlayState* play);
s32 Player_IsHoldingHookshot(Player* player);
s32 func_801240DC(Player* player);
s32 func_80124110(Player* player, s32 actionParam);
s32 func_80124148(Player* player);
s32 Player_ActionToMeleeWeapon(s32 actionParam);
s32 Player_GetMeleeWeaponHeld(Player* player);
s32 Player_IsHoldingTwoHandedWeapon(Player* player);
s32 Player_ActionToBottle(Player* player, s32 actionParam);
s32 Player_GetBottleHeld(Player* Player);
s32 Player_ActionToExplosive(Player* player, s32 actionParam);
s32 Player_GetExplosiveHeld(Player* player);
s32 func_80124278(Actor* actor, s32 arg1);
s32 func_801242B4(Player* player);
s32 func_801242DC(PlayState* play);
void func_80124420(Player* player);
void func_80124618(struct_80124618 arg0[], f32 curFrame, Vec3f* arg2);
void func_801246F4(PlayState* play, void** skeleton, Vec3s* jointTable, s32 dListCount, s32 lod, s32 tunic, s32 boots,
                   s32 face, OverrideLimbDrawFlex overrideLimbDraw, PostLimbDrawFlex postLimbDraw, Actor* actor);
void func_80125318(Vec3f* arg0, Vec3s* arg1);
void Player_DrawZoraShield(PlayState* play, Player* player);
void func_80125500(PlayState* play, Player* player, s32 limbIndex, Vec3f* pos, Vec3s* rot);
s32 func_80125D4C(PlayState* play, s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3s* rot, Actor* actor);
s32 func_801262C8(PlayState* play, s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3s* rot, Actor* actor);
s32 func_801263FC(PlayState* play, s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3s* rot, Actor* thisx);
s32 func_80126440(PlayState* play, ColliderQuad* collider, WeaponInfo* weaponInfo, Vec3f* arg3, Vec3f* arg4);
void Player_DrawGetItem(PlayState* play, Player* player);
void func_80126B8C(PlayState* play, Player* player);
s32 func_80127438(PlayState* play, Player* player, s32 maskId);
s32 func_80128640(PlayState* play, Player* player, Gfx* dlist);
void func_80128B74(PlayState* play, Player* player, s32 limbIndex);
void func_80128BD0(PlayState* play, s32 limbIndex, Gfx** dList1, Gfx** dList2, Vec3s* rot, Actor* actor);

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
void Distortion_Init(PlayState* play);
void Distortion_SetCountdown(s16 countdown);
s16 Distortion_GetCountdown(void);
s16 Distortion_GetType(void);
void Distortion_SetType(s32 type);
void Distortion_ClearType(s32 type);
s32 Distortion_GetUnderwaterCurrentSpeed(Player* player);
void Distortion_Update(void);
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
void func_8012C268(PlayState* play);
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
void func_8012CF0C(GraphicsContext* gfxCtx, s32 clearFb, s32 clearZb, u8 r, u8 g, u8 b);
void func_8012D374(GraphicsContext* gfxCtx, u8 r, u8 g, u8 b);
void func_8012D40C(f32* param_1, f32* param_2, s16* param_3);
void Room_nop8012D510(PlayState* play, Room* room, UNK_PTR param_3, UNK_TYPE1 param_4);
void Room_DrawType3Mesh(PlayState* play, Room* room, u32 flags);
void Room_DrawType0Mesh(PlayState* play, Room* room, u32 flags);
void Room_DrawType2Mesh(PlayState* play, Room* room, u32 flags);
void func_8012DEE8(PlayState* play, Room* room, u32 flags);
u32 func_8012E254(s32 param_1, PlayState* play);
void func_8012E32C(PlayState* play, Room* room, u32 flags);
void Room_DrawType1Mesh(PlayState* play, Room* room, u32 flags);
void Room_Init(PlayState* play, RoomContext* roomCtx);
u32 Room_AllocateAndLoad(PlayState* play, RoomContext* roomCtx);
s32 Room_StartRoomTransition(PlayState* play, RoomContext* roomCtx, s32 index);
s32 Room_HandleLoadCallbacks(PlayState* play, RoomContext* roomCtx);
void Room_Draw(PlayState* play, Room* room, u32 flags);
void func_8012EBF8(PlayState* play, RoomContext* roomCtx);
s32 Inventory_GetBtnBItem(PlayState* play);
void Inventory_ChangeEquipment(s16 value);
u8 Inventory_DeleteEquipment(PlayState* play, s16 equipment);
void Inventory_ChangeUpgrade(s16 upgrade, u32 value);
s32 Inventory_IsMapVisible(s16 sceneNum);
void Inventory_SetMapVisibility(s16 tingleIndex);
void Inventory_SaveDekuPlaygroundHighScore(s16 timerId);
void Inventory_IncrementSkullTokenCount(s16 sceneIndex);
s16 Inventory_GetSkullTokenCount(s16 sceneIndex);
void Inventory_SaveLotteryCodeGuess(PlayState* play);
s32 Object_Spawn(ObjectContext* objectCtx, s16 id);
void Object_InitBank(GameState* gameState, ObjectContext* objectCtx);
void Object_UpdateBank(ObjectContext* objectCtx);
s32 Object_GetIndex(ObjectContext* objectCtx, s16 id);
s32 Object_IsLoaded(ObjectContext* objectCtx, s32 index);
void Object_LoadAll(ObjectContext* objectCtx);
void* func_8012F73C(ObjectContext* objectCtx, s32 iParm2, s16 id);
void Scene_HeaderCmdSpawnList(PlayState* play, SceneCmd* cmd);
void Scene_HeaderCmdActorList(PlayState* play, SceneCmd* cmd);
void Scene_HeaderCmdActorCutsceneCamList(PlayState* play, SceneCmd* cmd);
void Scene_HeaderCmdColHeader(PlayState* play, SceneCmd* cmd);
void Scene_HeaderCmdRoomList(PlayState* play, SceneCmd* cmd);
void Scene_HeaderCmdEntranceList(PlayState* play, SceneCmd* cmd);
void Scene_HeaderCmdSpecialFiles(PlayState* play, SceneCmd* cmd);
void Scene_HeaderCmdRoomBehavior(PlayState* play, SceneCmd* cmd);
void Scene_HeaderCmdMesh(PlayState* play, SceneCmd* cmd);
void Scene_HeaderCmdObjectList(PlayState* play, SceneCmd* cmd);
void Scene_HeaderCmdLightList(PlayState* play, SceneCmd* cmd);
void Scene_HeaderCmdPathList(PlayState* play, SceneCmd* cmd);
void Scene_HeaderCmdTransiActorList(PlayState* play, SceneCmd* cmd);
void Door_InitContext(GameState* gameState, DoorContext* doorCtx);
void Scene_HeaderCmdEnvLightSettings(PlayState* play, SceneCmd* cmd);
void Scene_LoadAreaTextures(PlayState* play, s32 fileIndex);
void Scene_HeaderCmdSkyboxSettings(PlayState* play, SceneCmd* cmd);
void Scene_HeaderCmdSkyboxDisables(PlayState* play, SceneCmd* cmd);
void Scene_HeaderCmdTimeSettings(PlayState* play, SceneCmd* cmd);
void Scene_HeaderCmdWindSettings(PlayState* play, SceneCmd* cmd);
void Scene_HeaderCmdExitList(PlayState* play, SceneCmd* cmd);
void Scene_HeaderCmd09(PlayState* play, SceneCmd* cmd);
void Scene_HeaderCmdSoundSettings(PlayState* play, SceneCmd* cmd);
void Scene_HeaderCmdEchoSetting(PlayState* play, SceneCmd* cmd);
void Scene_HeaderCmdAltHeaderList(PlayState* play, SceneCmd* cmd);
void Scene_HeaderCmdCutsceneList(PlayState* play, SceneCmd* cmd);
void Scene_HeaderCmdActorCutsceneList(PlayState* play, SceneCmd* cmd);
void Scene_HeaderCmdMiniMap(PlayState* play, SceneCmd* cmd);
void Scene_HeaderCmd1D(PlayState* play, SceneCmd* cmd);
void Scene_HeaderCmdMiniMapCompassInfo(PlayState* play, SceneCmd* cmd);
void Scene_HeaderCmdSetAreaVisitedFlag(PlayState* play, SceneCmd* cmd);
void Scene_HeaderCmdAnimatedMaterials(PlayState* play, SceneCmd* cmd);
void Scene_SetExitFade(PlayState* play);
s32 Scene_ProcessHeader(PlayState* play, SceneCmd* header);
u16 Entrance_CreateIndex(s32 sceneIndex, s32 spawnIndex, s32 sceneSetup);
u16 Entrance_CreateIndexFromSpawn(s32 spawnIndex);
void Scene_ExecuteDrawConfig(PlayState* play);
void Scene_DrawConfigDefault(PlayState* play);
Gfx* AnimatedMat_TexScroll(PlayState* play, AnimatedMatTexScrollParams* params);
void AnimatedMat_DrawTexScroll(PlayState* play, s32 segment, void* params);
Gfx* AnimatedMat_TwoLayerTexScroll(PlayState* play, AnimatedMatTexScrollParams* params);
void AnimatedMat_DrawTwoTexScroll(PlayState* play, s32 segment, void* params);
void AnimatedMat_SetColor(PlayState* play, s32 segment, F3DPrimColor* primColor, F3DEnvColor* envColor);
void AnimatedMat_DrawColor(PlayState* play, s32 segment, void* params);
s32 AnimatedMat_Lerp(s32 min, s32 max, f32 norm);
void AnimatedMat_DrawColorLerp(PlayState* play, s32 segment, void* params);
f32 Scene_LagrangeInterp(s32 n, f32 x[], f32 fx[], f32 xp);
u8 Scene_LagrangeInterpColor(s32 n, f32 x[], f32 fx[], f32 xp);
void AnimatedMat_DrawColorNonLinearInterp(PlayState* play, s32 segment, void* params);
void AnimatedMat_DrawTexCycle(PlayState* play, s32 segment, void* params);
void AnimatedMat_DrawMain(PlayState* play, AnimatedMaterial* matAnim, f32 alphaRatio, u32 step, u32 flags);
void AnimatedMat_Draw(PlayState* play, AnimatedMaterial* matAnim);
void AnimatedMat_DrawOpa(PlayState* play, AnimatedMaterial* matAnim);
void AnimatedMat_DrawXlu(PlayState* play, AnimatedMaterial* matAnim);
void AnimatedMat_DrawAlpha(PlayState* play, AnimatedMaterial* matAnim, f32 alphaRatio);
void AnimatedMat_DrawAlphaOpa(PlayState* play, AnimatedMaterial* matAnim, f32 alphaRatio);
void AnimatedMat_DrawAlphaXlu(PlayState* play, AnimatedMaterial* matAnim, f32 alphaRatio);
void AnimatedMat_DrawStep(PlayState* play, AnimatedMaterial* matAnim, u32 step);
void AnimatedMat_DrawStepOpa(PlayState* play, AnimatedMaterial* matAnim, u32 step);
void AnimatedMat_DrawStepXlu(PlayState* play, AnimatedMaterial* matAnim, u32 step);
void AnimatedMat_DrawAlphaStep(PlayState* play, AnimatedMaterial* matAnim, f32 alphaRatio, u32 step);
void AnimatedMat_DrawAlphaStepOpa(PlayState* play, AnimatedMaterial* matAnim, f32 alphaRatio, u32 step);
void AnimatedMat_DrawAlphaStepXlu(PlayState* play, AnimatedMaterial* matAnim, f32 alphaRatio, u32 step);
void Scene_DrawConfigMatAnim(PlayState* play);
void Scene_DrawConfig3(PlayState* play);
void Scene_DrawConfig4(PlayState* play);
void Scene_DrawConfigDoNothing(PlayState* play);
void Scene_SetRenderModeXlu(PlayState* play, s32 index, u32 flags);
void Scene_SetCullFlag(PlayState* play, s32 index, u32 flags);
void Scene_DrawConfig5(PlayState* play);
void Scene_DrawConfigMatAnimManualStep(PlayState* play);
void Scene_DrawConfigGreatBayTemple(PlayState* play);
EntranceTableEntry* Entrance_GetTableEntry(u16 entrance);
s32 Entrance_GetSceneNum(u16 entranceIndex);
s32 Entrance_GetSceneNumAbsolute(u16 entranceIndex);
s32 Entrance_GetSpawnNum(u16 entranceIndex);
s32 Entrance_GetTransitionFlags(u16 entranceIndex);
s32 Schedule_RunScript(PlayState* play, u8* script, ScheduleOutput* output);
void SkelAnime_DrawLimbLod(PlayState* play, s32 limbIndex, void** skeleton, Vec3s* jointTable,
                           OverrideLimbDrawOpa overrideLimbDraw, PostLimbDrawOpa postLimbDraw, Actor* actor, s32 lod);
void SkelAnime_DrawLod(PlayState* play, void** skeleton, Vec3s* jointTable, OverrideLimbDrawOpa overrideLimbDraw,
                       PostLimbDrawOpa postLimbDraw, Actor* actor, s32 lod);
void SkelAnime_DrawFlexLimbLod(PlayState* play, s32 limbIndex, void** skeleton, Vec3s* jointTable,
                               OverrideLimbDrawFlex overrideLimbDraw, PostLimbDrawFlex postLimbDraw, Actor* actor,
                               s32 lod, Mtx** mtx);
void SkelAnime_DrawFlexLod(PlayState* play, void** skeleton, Vec3s* jointTable, s32 dListCount,
                           OverrideLimbDrawFlex overrideLimbDraw, PostLimbDrawFlex postLimbDraw, Actor* actor, s32 lod);
void SkelAnime_DrawLimbOpa(PlayState* play, s32 limbIndex, void** skeleton, Vec3s* jointTable,
                           OverrideLimbDrawOpa overrideLimbDraw, PostLimbDrawOpa postLimbDraw, Actor* actor);
void SkelAnime_DrawOpa(PlayState* play, void** skeleton, Vec3s* jointTable, OverrideLimbDrawOpa overrideLimbDraw,
                       PostLimbDrawOpa postLimbDraw, Actor* actor);
void SkelAnime_DrawFlexLimbOpa(PlayState* play, s32 limbIndex, void** skeleton, Vec3s* jointTable,
                               OverrideLimbDrawOpa overrideLimbDraw, PostLimbDrawOpa postLimbDraw, Actor* actor,
                               Mtx** limbMatricies);
void SkelAnime_DrawFlexOpa(PlayState* play, void** skeleton, Vec3s* jointTable, s32 dListCount,
                           OverrideLimbDrawOpa overrideLimbDraw, PostLimbDrawOpa postLimbDraw, Actor* actor);
void SkelAnime_DrawTransformFlexLimbOpa(PlayState* play, s32 limbIndex, void** skeleton, Vec3s* jointTable,
                                        OverrideLimbDrawOpa overrideLimbDraw, PostLimbDrawOpa postLimbDraw,
                                        TransformLimbDrawOpa transformLimbDraw, Actor* actor, Mtx** mtx);
void SkelAnime_DrawTransformFlexOpa(PlayState* play, void** skeleton, Vec3s* jointTable, s32 dListCount,
                                    OverrideLimbDrawOpa overrideLimbDraw, PostLimbDrawOpa postLimbDraw,
                                    TransformLimbDrawOpa transformLimbDraw, Actor* actor);
void SkelAnime_GetFrameData(AnimationHeader* animation, s32 currentFrame, s32 limbCount, Vec3s* dst);
s16 Animation_GetLength(void* animation);
s16 Animation_GetLastFrame(void* animation);
Gfx* SkelAnime_DrawLimb(PlayState* play, s32 limbIndex, void** skeleton, Vec3s* jointTable,
                        OverrideLimbDraw overrideLimbDraw, PostLimbDraw postLimbDraw, Actor* actor, Gfx* gfx);
Gfx* SkelAnime_Draw(PlayState* play, void** skeleton, Vec3s* jointTable, OverrideLimbDraw overrideLimbDraw,
                    PostLimbDraw postLimbDraw, Actor* actor, Gfx* gfx);
Gfx* SkelAnime_DrawFlexLimb(PlayState* play, s32 limbIndex, void** skeleton, Vec3s* jointTable,
                            OverrideLimbDraw overrideLimbDraw, PostLimbDraw postLimbDraw, Actor* actor, Mtx** mtx,
                            Gfx* gfx);
Gfx* SkelAnime_DrawFlex(PlayState* play, void** skeleton, Vec3s* jointTable, s32 dListCount,
                        OverrideLimbDraw overrideLimbDraw, PostLimbDraw postLimbDraw, Actor* actor, Gfx* gfx);
s16 SkelAnime_GetFrameDataLegacy(LegacyAnimationHeader* animation, s32 frame, Vec3s* frameTable);
s16 Animation_GetLimbCount2(LegacyAnimationHeader* animation);
s16 Animation_GetLength2(LegacyAnimationHeader* animation);
s16 Animation_GetLastFrame2(LegacyAnimationHeader* animation);
void SkelAnime_InterpFrameTable(s32 limbCount, Vec3s* dst, Vec3s* vec2, Vec3s* vec3, f32 unkf);
void AnimationContext_Reset(AnimationContext* animationCtx);
void AnimationContext_SetNextQueue(PlayState* play);
void AnimationContext_DisableQueue(PlayState* play);
AnimationEntry* AnimationContext_AddEntry(AnimationContext* animationCtx, AnimationType type);
void AnimationContext_SetLoadFrame(PlayState* play, LinkAnimationHeader* animation, s32 frame, s32 limbCount,
                                   Vec3s* frameTable);
void AnimationContext_SetCopyAll(PlayState* play, s32 vecCount, Vec3s* dst, Vec3s* src);
void AnimationContext_SetInterp(PlayState* play, s32 vecCount, Vec3s* base, Vec3s* mod, f32 weight);
void AnimationContext_SetCopyTrue(PlayState* play, s32 vecCount, Vec3s* dst, Vec3s* src, u8* index);
void AnimationContext_SetCopyFalse(PlayState* play, s32 vecCount, Vec3s* dst, Vec3s* src, u8* index);
void AnimationContext_SetMoveActor(PlayState* play, Actor* actor, SkelAnime* skelAnime, f32 arg3);
void AnimationContext_LoadFrame(PlayState* play, AnimationEntryData* data);
void AnimationContext_CopyAll(PlayState* play, AnimationEntryData* data);
void AnimationContext_Interp(PlayState* play, AnimationEntryData* data);
void AnimationContext_CopyTrue(PlayState* play, AnimationEntryData* data);
void AnimationContext_CopyFalse(PlayState* play, AnimationEntryData* data);
void AnimationContext_MoveActor(PlayState* play, AnimationEntryData* data);
void AnimationContext_Update(PlayState* play, AnimationContext* animationCtx);
void SkelAnime_InitLink(PlayState* play, SkelAnime* skelAnime, FlexSkeletonHeader* skeletonHeaderSeg,
                        LinkAnimationHeader* animation, s32 flags, Vec3s* jointTable, Vec3s* morphTable,
                        s32 limbBufCount);
void LinkAnimation_SetUpdateFunction(SkelAnime* skelAnime);
s32 LinkAnimation_Update(PlayState* play, SkelAnime* skelAnime);
s32 LinkAnimation_Morph(PlayState* play, SkelAnime* skelAnime);
void LinkAnimation_AnimateFrame(PlayState* play, SkelAnime* skelAnime);
s32 LinkAnimation_Loop(PlayState* play, SkelAnime* skelAnime);
s32 LinkAnimation_Once(PlayState* play, SkelAnime* skelAnime);
void Animation_SetMorph(PlayState* play, SkelAnime* skelAnime, f32 morphFrames);
void LinkAnimation_Change(PlayState* play, SkelAnime* skelAnime, LinkAnimationHeader* animation, f32 playSpeed,
                          f32 startFrame, f32 endFrame, u8 mode, f32 morphFrames);
void LinkAnimation_PlayOnce(PlayState* play, SkelAnime* skelAnime, LinkAnimationHeader* animation);
void LinkAnimation_PlayOnceSetSpeed(PlayState* play, SkelAnime* skelAnime, LinkAnimationHeader* animation,
                                    f32 playSpeed);
void LinkAnimation_PlayLoop(PlayState* play, SkelAnime* skelAnime, LinkAnimationHeader* animation);
void LinkAnimation_PlayLoopSetSpeed(PlayState* play, SkelAnime* skelAnime, LinkAnimationHeader* animation,
                                    f32 playSpeed);
void LinkAnimation_CopyJointToMorph(PlayState* play, SkelAnime* skelAnime);
void LinkAnimation_CopyMorphToJoint(PlayState* play, SkelAnime* skelAnime);
void LinkAnimation_LoadToMorph(PlayState* play, SkelAnime* skelAnime, LinkAnimationHeader* animation, f32 frame);
void LinkAnimation_LoadToJoint(PlayState* play, SkelAnime* skelAnime, LinkAnimationHeader* animation, f32 frame);
void LinkAnimation_InterpJointMorph(PlayState* play, SkelAnime* skelAnime, f32 frame);
void LinkAnimation_BlendToJoint(PlayState* play, SkelAnime* skelAnime, LinkAnimationHeader* animation1, f32 frame1,
                                LinkAnimationHeader* animation2, f32 frame2, f32 blendWeight, Vec3s* blendTable);
void LinkAnimation_BlendToMorph(PlayState* play, SkelAnime* skelAnime, LinkAnimationHeader* animation1, f32 frame1,
                                LinkAnimationHeader* animation2, f32 frame2, f32 blendWeight, Vec3s* blendTable);
void LinkAnimation_EndLoop(SkelAnime* skelAnime);
s32 Animation_OnFrameImpl(SkelAnime* skelAnime, f32 frame, f32 updateRate);
s32 LinkAnimation_OnFrame(SkelAnime* skelAnime, f32 frame);
void SkelAnime_Init(PlayState* play, SkelAnime* skelAnime, SkeletonHeader* skeletonHeaderSeg,
                    AnimationHeader* animation, Vec3s* jointTable, Vec3s* morphTable, s32 limbCount);
void SkelAnime_InitFlex(PlayState* play, SkelAnime* skelAnime, FlexSkeletonHeader* skeletonHeaderSeg,
                        AnimationHeader* animation, Vec3s* jointTable, Vec3s* morphTable, s32 limbCount);
void SkelAnime_InitSkin(GameState* gameState, SkelAnime* skelAnime, SkeletonHeader* skeletonHeaderSeg,
                        AnimationHeader* animationSeg);
void SkelAnime_SetUpdate(SkelAnime* skelAnime);
s32 SkelAnime_Update(SkelAnime* skelAnime);
s32 SkelAnime_Morph(SkelAnime* skelAnime);
s32 SkelAnime_MorphTaper(SkelAnime* skelAnime);
void SkelAnime_AnimateFrame(SkelAnime* skelAnime);
s32 SkelAnime_LoopFull(SkelAnime* skelAnime);
s32 SkelAnime_LoopPartial(SkelAnime* skelAnime);
s32 SkelAnime_Once(SkelAnime* skelAnime);
void Animation_ChangeImpl(SkelAnime* skelAnime, AnimationHeader* animation, f32 playSpeed, f32 startFrame, f32 endFrame,
                          u8 mode, f32 morphFrames, s8 taper);
void Animation_Change(SkelAnime* skelAnime, AnimationHeader* animation, f32 playSpeed, f32 startFrame, f32 endFrame,
                      u8 mode, f32 morphFrames);
void Animation_PlayOnce(SkelAnime* skelAnime, AnimationHeader* animation);
void Animation_MorphToPlayOnce(SkelAnime* skelAnime, AnimationHeader* animation, f32 morphFrames);
void Animation_PlayOnceSetSpeed(SkelAnime* skelAnime, AnimationHeader* animation, f32 playSpeed);
void Animation_PlayLoop(SkelAnime* skelAnime, AnimationHeader* animation);
void Animation_MorphToLoop(SkelAnime* skelAnime, AnimationHeader* animation, f32 morphFrames);
void Animation_PlayLoopSetSpeed(SkelAnime* skelAnime, AnimationHeader* animation, f32 playSpeed);
void Animation_EndLoop(SkelAnime* skelAnime);
void Animation_Reverse(SkelAnime* skelAnime);
void SkelAnime_CopyFrameTableTrue(SkelAnime* skelAnime, Vec3s* dst, Vec3s* src, u8* copyFlag);
void SkelAnime_CopyFrameTableFalse(SkelAnime* skelAnime, Vec3s* dst, Vec3s* src, u8* copyFlag);
void SkelAnime_UpdateTranslation(SkelAnime* skelAnime, Vec3f* pos, s16 angle);
s32 Animation_OnFrame(SkelAnime* skelAnime, f32 frame);
void SkelAnime_Free(SkelAnime* skelAnime, PlayState* play);
void SkelAnime_CopyFrameTable(SkelAnime* skelAnime, Vec3s* dst, Vec3s* src);
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
s32 View_SetDistortionDirRot(View* view, f32 dirRotX, f32 dirRotY, f32 dirRotZ);
s32 View_SetDistortionScale(View* view, f32 scaleX, f32 scaleY, f32 scaleZ);
s32 View_SetDistortionSpeed(View* view, f32 speed);
s32 View_InitDistortion(View* view);
s32 View_ClearDistortion(View* view);
s32 View_SetDistortion(View* view, Vec3f dirRot, Vec3f scale, f32 speed);
s32 View_StepDistortion(View* view, Mtx* projectionMtx);
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
void VisMono_Init(VisMono* this);
void VisMono_Destroy(VisMono* this);
// void VisMono_DesaturateTLUT(u16* tlut);
// void VisMono_DesaturateDList(Gfx* gfx);
void VisMono_Draw(VisMono* this, Gfx** gfxp);
// void VisMono_DrawOld(VisMono* this);
void func_801420C0(void* arg0);
void func_801420F4(void* arg0);
void func_80142100(void* arg0, Gfx** gfx, u32 arg2);
s32 func_80142440(SkyboxContext* skyboxCtx, Vtx* vtx, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7,
                  s32 arg8);
void func_80143148(SkyboxContext* skyboxCtx, s32 arg1);
void func_801431E8(GameState* gameState, SkyboxContext* skyboxCtx, s16 skyType);
void func_80143324(PlayState* play, SkyboxContext* skyboxCtx, s16 skyType);
void func_801434E4(GameState* gameState, SkyboxContext* skyboxCtx, s16 skyType);
Mtx* SkyboxDraw_UpdateMatrix(SkyboxContext* skyboxCtx, f32 x, f32 y, f32 z);
void SkyboxDraw_SetColors(SkyboxContext* skyboxCtx, u8 primR, u8 primG, u8 primB, u8 envR, u8 envG, u8 envB);
void SkyboxDraw_Draw(SkyboxContext* skyboxCtx, GraphicsContext* gfxCtx, s16 skyboxId, s16 blend, f32 x, f32 y, f32 z);
void SkyboxDraw_Noop(SkyboxContext* skyboxCtx);

// void func_80147520(void);
void func_80147564(PlayState* play);
s32 Message_ShouldAdvance(PlayState* play);
s32 Message_ShouldAdvanceSilent(PlayState* play);
void func_801477B4(PlayState* play);
void func_80147818(PlayState* play, UNK_PTR puParm2, UNK_TYPE4 uParm3, UNK_TYPE4 uParm4);
// void func_80147F18(PlayState* play, UNK_PTR puParm2, UNK_TYPE4 uParm3, UNK_TYPE4 uParm4);
// void func_80148558(PlayState* play, UNK_PTR puParm2, UNK_TYPE4 uParm3, UNK_TYPE4 uParm4);
void func_80148B98(PlayState* play, u8 bParm2);
// void func_80148CBC(void);
// void func_80148D64(void);
// void func_80149048(void);
// void func_801491DC(void);
// void func_80149454(void);
// void func_801496C8(void);
// void func_8014995C(void);
void func_80149C18(PlayState* play);
// void Message_FindMessage(void);
void func_80149F74(PlayState* play, u32** ppuParm2);
// void func_8014AAD0(void);
void func_8014ADBC(PlayState* play, UNK_PTR puParm2);
// void func_8014C70C(void);
void Message_LoadChar(PlayState* play, u16 codePointIndex, s32* offset, f32* arg3, s16 arg4);
// void func_8014CCB4(void);
// void func_8014CDF0(void);
// void func_8014CFDC(void);
void func_8014D304(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5);
// void func_8014D62C(void);
// void func_8014D7B4(void);
void func_80150A84(PlayState* play);
void func_80150D08(PlayState* play, u32 uParm2);
// void func_801514B0(void);
void Message_StartTextbox(PlayState* play, u16 textId, Actor* Actor);
void func_80151938(PlayState* play, u16 textId);
void func_80151A68(PlayState* play, u16 textId);
void func_80151BB4(PlayState* play, u8 uParm2);
// void func_80151C9C(void);
void func_80151DA4(PlayState* play, u16 arg2);
void func_80152434(PlayState* play, u16 arg2);
// void func_80152464(void);
u8 Message_GetState(MessageContext* msgCtx);
// void func_8015268C(void);
// void func_80152C64(void);
// void func_80152CAC(void);
// void func_80152EC0(void);
// void func_80152FB8(void);
// void func_80153750(void);
// void func_80153E7C(void);
// void func_80153EF0(void);
void func_801541D4(PlayState* play, Gfx** gfxp);
// void func_80156758(void);
void func_8015680C(PlayState* play);
void func_801586A4(PlayState* play);
void Message_Init(PlayState* play);
void Message_FindMessageNES(PlayState* play, u16 textId);
// void Message_LoadCharNES(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE2
// param_5); void Message_LoadPluralRupeesNES(void); void Message_LoadLocalizedRupeesNES(void); void
// Message_LoadRupeesNES(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE2 param_5);
// void Message_LoadTimeNES(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4
// param_5); void Message_LoadAreaTextNES(void); void func_80159438(void);
void func_8015966C(PlayState* play, UNK_PTR puParm2, UNK_TYPE arg3);
// void func_8015A144(void);
void func_8015B198(PlayState* play);
void Message_FindCreditsMessage(PlayState* play, u16 textId);
void func_8015E7EC(PlayState* play, UNK_PTR puParm2);
// void func_8015F8A8(UNK_TYPE4 ctxt);

void ShrinkWindow_SetLetterboxTarget(s32 target);
s32 ShrinkWindow_GetLetterboxTarget(void);
void ShrinkWindow_SetLetterboxMagnitude(s32 magnitude);
s32 ShrinkWindow_GetLetterboxMagnitude(void);
void ShrinkWindow_SetPillarboxTarget(s32 target);
s32 ShrinkWindow_GetPillarboxTarget(void);
void ShrinkWindow_SetPillarboxMagnitude(s32 magnitude);
s32 ShrinkWindow_GetPillarboxMagnitude(void);
void ShrinkWindow_Init(void);
void ShrinkWindow_Destroy(void);
void ShrinkWindow_Update(s32 framerateDivisor);
void ShrinkWindow_Draw(GraphicsContext* gfxCtx);
// void func_80161180(void);
s32 func_8016119C(Camera* camera, DbCameraUnkStruct* arg1);
// void func_8016122C(void);
// void func_801612B8(void);
s32 func_80161998(u8* cmd, DbCameraUnkStruct* arg1);
// s32 func_80161BAC(void);
void func_80161BE0(s16 arg0);
void func_80161C0C(void);
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
// UNK_TYPE4 param_5, UNK_TYPE4 param_6); void func_80163660(void);
void* KaleidoManager_FaultAddrConvFunc(void* address, void* param);
void KaleidoManager_LoadOvl(KaleidoMgrOverlay* ovl);
void KaleidoManager_ClearOvl(KaleidoMgrOverlay* ovl);
void KaleidoManager_Init(PlayState* play);
void KaleidoManager_Destroy();
void* KaleidoManager_GetRamAddr(void* vram);
void KaleidoScopeCall_LoadPlayer(void);
void KaleidoScopeCall_Init(PlayState* play);
void KaleidoScopeCall_Destroy(PlayState* play);
void KaleidoScopeCall_Update(PlayState* play);
void KaleidoScopeCall_Draw(PlayState* play);
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
void func_80164C14(Gfx** arg0, TexturePtr* arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, f32 arg6);
// void TransitionCircle_Draw(void);
// void TransitionCircle_IsDone(void);
// void func_801651B0(void);
// void func_80165224(void);
// void func_80165288(void);
// void func_8016537C(void);
void func_80165438(UNK_PTR param_1);
// void func_80165444(s32 param_1, UNK_TYPE4 param_2, UNK_TYPE4 param_3, UNK_TYPE4 param_4, UNK_TYPE4 param_5);
// void func_80165460(void);
// void func_80165608(void);
// void func_80165630(void);
void func_80165658(u32 arg0);
void func_8016566C(u32 arg0);
void func_80165690(void);
// void func_801656A4(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5,
// UNK_TYPE4 param_6, UNK_TYPE4 param_7, UNK_TYPE4 param_8); void func_80165DCC(void); void func_80165DF0(void); void
// func_80165E1C(void); void func_80165E7C(void); void func_80165EC0(void); void func_80166060(void);
Gfx* func_801660B8(PlayState* play, Gfx* gfx);
void Play_Fini(GameState* thisx);
// void func_801663C4(void);
// void func_80166644(void);
// void func_801668B4(void);
void func_80166968(PlayState* play, Camera* camera);
void func_80166B30(PlayState* play);
void func_80167814(PlayState* play);
void func_80167DE4(PlayState* play);
// void func_80167F0C(void);
void Play_Draw(PlayState* play);
void func_80168DAC(PlayState* play);
void Play_Update(PlayState* play);
s32 Play_InCsMode(PlayState* play);
f32 func_80169100(PlayState* play, MtxF* mtx, CollisionPoly** arg2, s32* arg3, Vec3f* feetPosPtr);
// void func_801691F0(void);
void* Play_LoadScene(PlayState* play, RomFile* entry);
void func_8016927C(PlayState* play, s16 sParm2);
// void func_801692C4(PlayState* play, UNK_TYPE1 uParm2);
// void Play_SceneInit(PlayState* play, s32 sceneIndex, UNK_TYPE1 param_3);
UNK_RET func_80169474(PlayState* play, Vec3f* v1, Vec3f* v2);
s32 Play_CreateSubCamera(PlayState* play);
s32 Play_GetActiveCamId(PlayState* play);
void Play_CameraChangeStatus(PlayState* play, s16 camId, s16 status);
void Play_ClearCamera(PlayState* play, s16 camId);
Camera* Play_GetCamera(PlayState* play, s16 camId);
s32 Play_CameraSetAtEye(PlayState* play, s16 camId, Vec3f* at, Vec3f* eye);
void Play_CameraSetAtEyeUp(PlayState* play, s16 camId, Vec3f* at, Vec3f* eye, Vec3f* up);
void Play_CameraSetFov(PlayState* play, s16 camId, f32 fov);
void Play_CameraSetRoll(PlayState* play, s16 camId, s16 roll);
void Play_CopyCamera(PlayState* play, s16 dstCamId, s16 srcCamId);
// void func_80169A50(void);
void Play_CameraChangeSetting(PlayState* play, s16 camId, s16 setting);
void func_80169AFC(PlayState* play, s16 camId, s16 arg2);
u16 Play_GetActorCsCamSetting(PlayState* play, s32 csCamDataIndex);
Vec3s* Play_GetActorCsCamFuncData(PlayState* play, s32 csCamDataIndex);
s16 Play_GetOriginalSceneNumber(s16 sceneNum);
void Play_SaveCycleSceneFlags(GameState* gameState);
void Play_SetRespawnData(GameState* gameState, s32 respawnNumber, u16 sceneSetup, s32 roomIndex, s32 playerParams,
                         Vec3f* pos, s16 yaw);
void Play_SetupRespawnPoint(GameState* gameState, s32 respawnNumber, s32 playerParams);
void func_80169EFC(GameState* gameState);
void func_80169F78(GameState* gameState);
void func_80169FDC(GameState* gameState);
s32 func_80169FFC(GameState* gameState);
s32 FrameAdvance_IsEnabled(GameState* gameState);
s32 func_8016A02C(GameState* gameState, Actor* actor, s16* yaw);
s32 Play_IsUnderwater(PlayState* play, Vec3f* pos);
s32 Play_IsDebugCamEnabled(void);
void Play_AssignPlayerActorCsIdsFromScene(GameState* gameState, s32 cutscene);
void func_8016A268(GameState* gameState, s16 arg1, u8 arg2, u8 arg3, u8 arg4, u8 arg5);
void Play_Init(GameState* gameState);
// void func_8016AC10(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5,
// UNK_TYPE4 param_6, UNK_TYPE4 param_7, UNK_TYPE4 param_8, UNK_TYPE4 param_9, UNK_TYPE4 param_10); void
// func_8016AE1C(void); void func_8016B278(void); void func_8016B4B0(void); void func_8016C344(void); void
// func_8016CD4C(void); void func_8016E40C(void); void func_8016EA90(void); void func_8016F1A8(void); void
// func_8016F4EC(void);
void func_8016F5A8(PlayState* play, s8* pcParm2, Input* iParm3);
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
void THGA_Ct(TwoHeadGfxArena* thga, Gfx* start, size_t size);
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
Gfx* THGA_AllocEnd(TwoHeadGfxArena* thga, size_t size);
Gfx* THGA_AllocEndArray64(TwoHeadGfxArena* thga, u32 count);
Gfx* THGA_AllocEnd64(TwoHeadGfxArena* thga);
Gfx* THGA_AllocEndArray16(TwoHeadGfxArena* thga, u32 count);
Gfx* THGA_AllocEnd16(TwoHeadGfxArena* thga);
void* THA_GetHead(TwoHeadArena* tha);
void THA_SetHead(TwoHeadArena* tha, void* start);
void* THA_GetTail(TwoHeadArena* tha);
void* THA_AllocStart(TwoHeadArena* tha, size_t size);
void* THA_AllocStart1(TwoHeadArena* tha);
void* THA_AllocEnd(TwoHeadArena* tha, size_t size);
void* THA_AllocEndAlign16(TwoHeadArena* tha, size_t size);
void* THA_AllocEndAlign(TwoHeadArena* tha, size_t size, u32 mask);
s32 THA_GetSize(TwoHeadArena* tha);
u32 THA_IsCrash(TwoHeadArena* tha);
void THA_Init(TwoHeadArena* tha);
void THA_Ct(TwoHeadArena* tha, void* ptr, size_t size);
void THA_Dt(TwoHeadArena* tha);
void AudioMgr_StopAllSfxExceptSystem(void);
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
void Game_Nop80173534(GameState* gameState);
void GameState_Draw(GameState* gameState, GraphicsContext* gfxCtx);
void GameState_SetFrameBuffer(GraphicsContext* gfxCtx);
void func_801736DC(GraphicsContext* gfxCtx);
void Game_UpdateInput(GameState* gameState);
void Game_Update(GameState* gameState);
void Game_IncrementFrameCount(GameState* gameState);
void GameState_InitArena(GameState* gameState, size_t size);
void GameState_Realloc(GameState* gameState, size_t size);
void GameState_Init(GameState* gameState, GameStateFunc gameStateInit, GraphicsContext* gfxCtx);
void GameState_Destroy(GameState* gameState);
GameStateFunc GameState_GetNextStateInit(GameState* gameState);
size_t GameState_GetNextStateSize(GameState* gameState);
u32 GameState_IsRunning(GameState* gameState);
s32 GameState_GetArenaSize(GameState* gameState);
s32 func_80173B48(GameState* gameState);
void GameAlloc_Log(GameAlloc* this);
void* GameAlloc_Malloc(GameAlloc* this, size_t size);
void GameAlloc_Free(GameAlloc* this, void* data);
void GameAlloc_Cleanup(GameAlloc* this);
void GameAlloc_Init(GameAlloc* this);
void Graph_FaultClient(void);
void Graph_InitTHGA(TwoHeadGfxArena* arena, Gfx* buffer, s32 size);
void Graph_SetNextGfxPool(GraphicsContext* gfxCtx);
GameStateOverlay* Graph_GetNextGameState(GameState* gameState);
void* Graph_FaultAddrConvFunc(void* address, void* param);
void Graph_Init(GraphicsContext* gfxCtx);
void Graph_Destroy(GraphicsContext* gfxCtx);
void Graph_TaskSet00(GraphicsContext* gfxCtx, GameState* gameState);
void Graph_UpdateGame(GameState* gameState);
void Graph_ExecuteAndDraw(GraphicsContext* gfxCtx, GameState* gameState);
void Graph_Update(GraphicsContext* gfxCtx, GameState* gameState);
void Graph_ThreadEntry(void* arg);
Gfx* Graph_GfxPlusOne(Gfx* gfx);
Gfx* Graph_BranchDlist(Gfx* gfx, Gfx* dst);
void* Graph_DlistAlloc(Gfx** gfx, size_t size);
ListAlloc* ListAlloc_Init(ListAlloc* this);
// void ListAlloc_Alloc(void);
// void ListAlloc_Free(void);
void ListAlloc_FreeAll(ListAlloc* this);
void Main(void* arg);
u32 Padmgr_GetControllerBitmask(void);
void func_80174F24(void (*arg0)(void*), void* arg1);
void func_80174F44(void (*arg0)(void*), void* arg1);
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
void func_80175434(void);
void func_8017544C(s32 port, s32 rumbleOn);
void PadMgr_RumbleSet(u8 rumbleEnabled[MAXCONTROLLERS]);
s32 PadMgr_ControllerHasRumblePak(s32 port);
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
void PadMgr_Init(OSMesgQueue* siEventCallbackQueue, IrqMgr* irqmgr, OSId threadId, OSPri threadPri, void* stack);
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
void SpeedMeter_DrawTimeEntries(void* displayList, GraphicsContext* gfxCtx);
// void func_80177A84(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE2 param_5,
// UNK_TYPE4 param_6, UNK_TYPE4 param_7, UNK_TYPE4 param_8, UNK_TYPE4 param_9);
// void func_80177AC8(void);
void SpeedMeter_DrawAllocEntries(void* displayList, GraphicsContext* gfxCtx, GameState* gameState);
void func_801780F0(Mtx* param_1, f32 param_2, f32 param_3, f32 param_4, f32 param_5, f32 param_6, f32 param_7);
// void func_801781EC(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5);
// void func_8017842C(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE2 param_5,
// UNK_TYPE4 param_6, UNK_TYPE4 param_7, UNK_TYPE4 param_8, UNK_TYPE4 param_9, UNK_TYPE4 param_10, UNK_TYPE4 param_11);
// void func_80178750(void);
// void func_80178818(void);
void func_80178978(void);
// void func_801789D4(void);
u32 SysCfb_GetFbPtr(s32 index);
u32 SysCfb_GetZBuffer(void);
// UNK_TYPE4 func_80178A24(void);
// void func_80178A34(void);
s32 func_80178A94(s32 param_1, s32 param_2);
// void func_80178AC0(void);
// void func_80178C80(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5);
// void func_80178D7C(void);
// void func_80178DAC(void);
// void func_80178E3C(void);
// void func_80178E7C(void);
// void Check_WriteRGBA16Pixel(u16* buffer, u32 x, u32 y, u32 value);
// void Check_WriteI4Pixel(u16* buffer, u32 x, u32 y, u32 value);
// void Check_DrawI4Texture(u16* buffer, u32 x, u32 y, u32 width, u32 height, u8* texture);
// void Check_ClearRGBA16(u16* buffer);
// void Check_DrawExpansionPakErrorMessage(void);
// void Check_DrawRegionLockErrorMessage(void);
void Check_ExpansionPak(void);
void Check_RegionIsSupported(void);
f32 func_80179300(f32 n);
f32 func_80179400(s32 n);
f32 pow_int(f32 base, s32 exp);
f32 sin_rad(f32 rad);
f32 cos_rad(f32 rad);
f32 Rand_ZeroFloat(f32 scale);
f32 randPlusMinusPoint5Scaled(f32 scale);
f32 Math3D_Normalize(Vec3f* vec);
s32 Math3D_PlaneVsLineSegClosestPoint(f32 planeAA, f32 planeAB, f32 planeAC, f32 planeADist, f32 planeBA, f32 planeBB,
                                      f32 planeBC, f32 planeBDist, Vec3f* linePointA, Vec3f* linePointB,
                                      Vec3f* closestPoint);
s32 func_80179798(Vec3f* param_1, Vec3f* param_2, Vec3f* param_3, Vec3f* param_4, Vec3f* param_5, Vec3f* param_6);
// void func_80179A44(void);
void func_80179B34(float fParm1, f32 fParm2, f32 fParm5, f32 fParm6, f32 param_5, f32 param_6, f32 param_7,
                   float* param_8, float* param_9);
// UNK_TYPE4 func_80179B94(f32 fParm1, f32 fParm2, f32 fParm5, f32 param_4, f32 param_5, f32 param_6, f32 param_7, f32
// param_8, Vec3f* param_9); void func_80179D74(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1
// param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6, UNK_TYPE4 param_7, UNK_TYPE4 param_8, UNK_TYPE4 param_9, UNK_TYPE4
// param_10);
void Math3D_ScaleAndAdd(Vec3f* a, Vec3f* b, f32 scale, Vec3f* dst);
void Math3D_Lerp(Vec3f* a, Vec3f* b, f32 t, Vec3f* dst);
f32 Math3D_Parallel(Vec3f* a, Vec3f* b);
s32 Math3D_AngleBetweenVectors(Vec3f* a, Vec3f* b, f32* angle);
void func_80179F64(Vec3f* param_1, Vec3f* param_2, Vec3f* param_3);
s32 Math3D_XZBoundCheck(f32 xMin, f32 xMax, f32 zMin, f32 zMax, f32 x, f32 z);
// void func_8017A09C(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5,
// UNK_TYPE4 param_6); void func_8017A1D0(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4,
// UNK_TYPE4 param_5, UNK_TYPE4 param_6);
s32 func_8017A304(Vec3f* v0, Vec3f* v1, Vec3f* v2, f32 z, f32 x, f32 chkDist);
// UNK_TYPE4 func_8017A438(Vec3f* pfParm1, Vec3f* pfParm2, Vec3f* pfParm3, Vec3f* pfParm4, f32 param_5);
f32 Math3D_XZLengthSquared(f32 x, f32 z);
f32 Math3D_XZLength(f32 x, f32 z);
f32 Math3D_XZDistanceSquared(f32 x1, f32 x2, f32 z1, f32 z2);
f32 Math3D_XZDistance(f32 x1, f32 x2, f32 z1, f32 z2);
f32 Math3D_LengthSquared(Vec3f* vec);
f32 Math3D_Vec3fMagnitude(Vec3f* vec);
f32 Math3D_Vec3fDistSq(Vec3f* a, Vec3f* b);
f32 Math3D_Distance(Vec3f* a, Vec3f* b);
f32 Math3D_DistanceS(Vec3s* s, Vec3f* f);
f32 func_8017A7B8(f32* param_1, f32* param_2, f32 param_3, f32 param_4);
f32 func_8017A7F8(f32* param_1, f32* param_2, f32 param_3, f32 param_4);
f32 func_8017A838(f32* param_1, f32* param_2, f32 param_3, f32 param_4);
void Math3D_CrossProduct(Vec3f* a, Vec3f* b, Vec3f* res);
void Math3D_SurfaceNorm(Vec3f* a, Vec3f* b, Vec3f* c, Vec3f* res);
u32 Math3D_PointRelativeToCubeFaces(Vec3f* param_1, Vec3f* param_2, Vec3f* param_3);
u32 Math3D_PointRelativeToCubeEdges(Vec3f* param_1, Vec3f* param_2, Vec3f* param_3);
u32 Math3D_PointRelativeToCubeVertices(Vec3f* param_1, Vec3f* param_2, Vec3f* param_3);
s32 Math3D_LineVsCube(Vec3f* min, Vec3f* max, Vec3f* a, Vec3f* b);
// void func_8017B68C(void);
void func_8017B7F8(Vec3f* arg0, s16 arg1, f32* arg2, f32* arg3, f32* arg4);
void Math3D_UnitNormalVector(Vec3f* a, Vec3f* b, Vec3f* c, f32* normX, f32* normY, f32* normZ, f32* param_7);
f32 Math3D_SignedDistanceFromPlane(f32 normX, f32 normY, f32 normZ, f32 d, Vec3f* position);
// void func_8017B9D8(void);
f32 Math3D_UDistPlaneToPos(f32 normX, f32 normY, f32 normZ, f32 d, Vec3f* position);
f32 Math3D_DistPlaneToPos(f32 normX, f32 normY, f32 normZ, f32 d, Vec3f* position);
s32 Math3D_TriChkPointParaYDist(Vec3f* v0, Vec3f* v1, Vec3f* v2, f32 y, f32 z, f32 unk, f32 chkDist, f32 ny);
// void func_8017BD98(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5,
// UNK_TYPE4 param_6, UNK_TYPE4 param_7); void func_8017BDE0(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3,
// UNK_TYPE1 param_4, UNK_TYPE4 param_5);
s32 Math3D_TriChkPointParaYIntersectDist(Vec3f* a, Vec3f* b, Vec3f* c, f32 nx, f32 ny, f32 nz, f32 dist, f32 z, f32 x,
                                         f32* yIntersect, f32 chkDist);
s32 Math3D_TriChkPointParaYIntersectInsideTri(Vec3f* v0, Vec3f* v1, Vec3f* v2, f32 nx, f32 ny, f32 nz, f32 originDist,
                                              f32 z, f32 x, f32* yIntersect, f32 chkDist);
// void func_8017BF8C(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5,
// UNK_TYPE4 param_6);
s32 Math3D_TriChkLineSegParaYIntersect(Vec3f* v0, Vec3f* v1, Vec3f* v2, f32 nx, f32 ny, f32 nz, f32 originDist, f32 z,
                                       f32 x, f32* yIntersect, f32 y0, f32 y1);
// void func_8017C17C(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5,
// UNK_TYPE4 param_6, UNK_TYPE4 param_7); void func_8017C1F0(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3,
// UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6, UNK_TYPE4 param_7, UNK_TYPE4 param_8);
s32 Math3D_TriChkPointParaYIntersectInsideTri2(Vec3f* v0, Vec3f* v1, Vec3f* v2, f32 nx, f32 ny, f32 nz, f32 originDist,
                                               f32 z, f32 x, f32* yIntersect, f32 chkDist);
s32 Math3D_TriChkPointParaXDist(Vec3f* v0, Vec3f* v1, Vec3f* v2, f32 y, f32 z, f32 unk, f32 chkDist, f32 nx);
// void func_8017C808(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5,
// UNK_TYPE4 param_6, UNK_TYPE4 param_7);
s32 Math3D_TriChkPointParaXIntersect(Vec3f* a, Vec3f* b, Vec3f* c, f32 nx, f32 ny, f32 nz, f32 dist, f32 y, f32 z,
                                     f32* xIntersect);
// void func_8017C904(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5,
// UNK_TYPE4 param_6);
s32 Math3D_TriChkLineSegParaXIntersect(Vec3f* v0, Vec3f* v1, Vec3f* v2, f32 nx, f32 ny, f32 nz, f32 originDist, f32 y,
                                       f32 z, f32* xIntersect, f32 x0, f32 x1);
// void func_8017CB08(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5,
// UNK_TYPE4 param_6, UNK_TYPE4 param_7);
s32 Math3D_TriChkLineSegParaZDist(Vec3f* v0, Vec3f* v1, Vec3f* v2, f32 y, f32 z, f32 unk, f32 chkDist, f32 nz);
// void func_8017CEA8(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5,
// UNK_TYPE4 param_6, UNK_TYPE4 param_7);
s32 Math3D_TriChkPointParaZIntersect(Vec3f* a, Vec3f* b, Vec3f* c, f32 nx, f32 ny, f32 nz, f32 dist, f32 x, f32 y,
                                     f32* zIntersect);
// void func_8017CFA4(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5,
// UNK_TYPE4 param_6);
s32 Math3D_TriChkLineSegParaZIntersect(Vec3f* v0, Vec3f* v1, Vec3f* v2, f32 nx, f32 ny, f32 nz, f32 originDist, f32 x,
                                       f32 y, f32* zIntersect, f32 z0, f32 z1);
// void func_8017D1AC(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5,
// UNK_TYPE4 param_6, UNK_TYPE4 param_7); void func_8017D220(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3,
// UNK_TYPE1 param_4, UNK_TYPE4 param_5);
s32 Math3D_LineSegVsPlane(f32 nx, f32 ny, f32 nz, f32 originDist, Vec3f* linePointA, Vec3f* linePointB,
                          Vec3f* intersect, s32 fromFront);
// void func_8017D404(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5,
// UNK_TYPE4 param_6, UNK_TYPE4 param_7, UNK_TYPE4 param_8, UNK_TYPE4 param_9, UNK_TYPE4 param_10, UNK_TYPE4 param_11);
void Math3D_TriSetCoords(TriNorm* tri, Vec3f* pointA, Vec3f* pointB, Vec3f* pointC);
u32 Math3D_IsPointInSphere(Sphere16* sphere, Vec3f* point);
s32 Math3D_PointDistToLine2D(f32 arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, f32* arg6, f32* arg7,
                             f32* arg8); // returns boolean
s32 func_8017D7C0(f32 x0, f32 y0, f32 x1, f32 y1, f32 x2, f32 y2, f32* lineLenSq);
// void func_8017D814(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5);
// void func_8017D91C(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5);
// void func_8017DA24(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5);
s32 Math3D_LineVsSph(Sphere16* sphere, LineSegment* line);
void func_8017DD34(Sphere16* sphere, TriNorm* tri, Vec3f* pfParm3);
s32 Math3D_ColSphereTri(Sphere16* sphere, TriNorm* tri, Vec3f* uParm3);
// void func_8017E294(void);
UNK_TYPE func_8017E350(UNK_PTR, Vec3f*, Vec3f*, Vec3f*, Vec3f*);
s32 Math3D_ColCylinderTri(Cylinder16* cylinder, TriNorm* tri, Vec3f* pzParm3);
// void func_8017F1A0(void);
s32 Math3D_SphVsSph(Sphere16* sphere1, Sphere16* sphere2);
s32 Math3D_ColSphereSphereIntersect(Sphere16* sphere1, Sphere16* sphere2, f32* intersectAmount);
s32 Math3D_ColSphereSphereIntersectAndDistance(Sphere16* sphere1, Sphere16* sphere2, f32* intersectAmount, f32* dist);
s32 Math3D_ColSphereCylinderDistance(Sphere16* sphere, Cylinder16* cylinder, f32* dist);
s32 Math3D_ColSphereCylinderDistanceAndAmount(Sphere16* sphere, Cylinder16* cylinder, f32* dist, f32* intersectAmount);
s32 Math3D_ColCylinderCylinderAmount(Cylinder16* cylinder1, Cylinder16* cylinder2, f32* intersectAmount);
s32 Math3D_ColCylinderCylinderAmountAndDistance(Cylinder16* cylinder1, Cylinder16* cylinder2, f32* intersectAmount,
                                                f32* dist);
s32 Math3d_ColTriTri(TriNorm* tri1, TriNorm* tri2, Vec3f* uParm3);
s32 Math3D_XZInSphere(Sphere16* sphere, f32 x, f32 z);
s32 Math3D_XYInSphere(Sphere16* sphere, f32 x, f32 y);
s32 Math3D_YZInSphere(Sphere16* sphere, f32 y, f32 z);
// void func_8017FB1C(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5,
// UNK_TYPE4 param_6, UNK_TYPE4 param_7, UNK_TYPE4 param_8, UNK_TYPE4 param_9, UNK_TYPE4 param_10, UNK_TYPE4 param_11);
// void func_8017FD44(void);

u16 Math_GetAtan2Tbl(f32 opposite, f32 adjacent);
s16 Math_Atan2S(f32 opposite, f32 adjacent);
f32 Math_Atan2F(f32 opposite, f32 adjacent);
s16 Math_FAtan2F(f32 adjacent, f32 opposite);
f32 Math_Acot2F(f32 adjacent, f32 opposite);

u64* SysUcode_GetUCodeBoot(void);
size_t SysUcode_GetUCodeBootSize(void);
u64* SysUcode_GetUCode(void);
u64* SysUcode_GetUCodeData(void);

void func_80183070(void);
// void func_801830A0(void);
// void func_801830C8(void);
// void func_801830E8(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5,
// UNK_TYPE4 param_6, UNK_TYPE4 param_7); void func_80183148(void); void func_80183224(void); void func_801832B0(void);
// void func_8018332C(void);
// void func_8018340C(void);
void func_80183430(SkeletonInfo* skeletonInfo, void* arg1, void* arg2, Vec3s* arg3, Vec3s* arg4,
                   UnkKeyframeCallback* callbacks);
void func_8018349C(UNK_PTR arg0);
void func_801834A8(SkeletonInfo* skeletonInfo, void* arg1);
// void func_80183510(void);
// void func_80183580(void);
void func_801835EC(UNK_PTR arg0, UNK_PTR arg1);
// void func_80183658(void);
// void func_801836CC(void);
// void func_8018373C(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5,
// UNK_TYPE4 param_6, UNK_TYPE4 param_7, UNK_TYPE4 param_8, UNK_TYPE4 param_9); void func_801837CC(void); void
// func_80183808(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5,
// UNK_TYPE4 param_6); void func_80183880(void); void func_80183A3C(void); void func_80183B08(void); void
// func_80183B68(void);
s32 func_80183DE0(SkeletonInfo* skeletonInfo);
// void func_8018410C(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5,
// UNK_TYPE4 param_6, UNK_TYPE4 param_7);
void func_8018450C(PlayState* play, SkeletonInfo* skeleton, Mtx* mtx, OverrideKeyframeDrawScaled overrideKeyframeDraw,
                   PostKeyframeDrawScaled postKeyframeDraw, Actor* actor);
// void func_801845A4(void);
// void func_801845C8(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5);
// void func_80184638(void);
// void func_801846AC(void);
// void func_80184728(void);
// void func_801847A0(void);
// void func_80184818(void);
// void func_80184898(void);
// void func_80184914(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5,
// UNK_TYPE4 param_6, UNK_TYPE4 param_7, UNK_TYPE4 param_8, UNK_TYPE4 param_9, UNK_TYPE4 param_10); void
// func_801849A0(void); void func_801849DC(void); void func_80184C48(void); void func_801850A0(UNK_TYPE1 param_1,
// UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6, UNK_TYPE4 param_7);
// void func_801853C8(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5,
// UNK_TYPE4 param_6); void func_80185460(void);
// void Slowly_Main(SlowlyTask* slowly);
// void Slowly_ThreadEntry(SlowlyTask* slowly);
void Slowly_Start(SlowlyTask* slowly, void* stack, void (*callback)(), void* callbackArg0, void* callbackArg1);
void Slowly_Stop(SlowlyTask* slowly);
// void func_801857C0(void);
// char* func_801857D0(void);
// void func_80185864(void);
u32 func_80185908(void);
UNK_TYPE func_80185968(void* arg0, UNK_TYPE arg1, UNK_TYPE arg2);
// void func_801859F0(void);
// void func_80185A2C(void);
// void func_80185B1C(void);
// void func_80185BE4(void);
// void func_80185C24(void);
void SysFlashrom_ThreadEntry(s80185D40* param_1);
void func_80185DDC(u8* arg0, u32 arg1, u32 arg2);
s32 func_80185EC4(void);
s32 func_80185F04(void);
void func_80185F64(void* arg0, UNK_TYPE arg1, UNK_TYPE arg2);
s32 func_80185F90(u32 param_1);
u32 osFlashGetAddr(u32 pageNum);
OSPiHandle* osFlashReInit(u8 latency, u8 pulse, u8 pageSize, u8 relDuration, u32 start);
void osFlashChange(u32 flashNum);
OSPiHandle* osFlashInit(void);
void osFlashReadStatus(u8* flashStatus);
void osFlashReadId(u32* flashType, u32* flashVendor);
void osFlashClearStatus(void);
s32 osFlashAllErase(void);
void osFlashAllEraseThrough(void);
s32 osFlashCheckEraseEnd(void);
s32 osFlashSectorErase(u32 pageNum);
void osFlashSectorEraseThrough(u32 pageNum);
s32 osFlashWriteBuffer(OSIoMesg* mb, s32 priority, void* dramAddr, OSMesgQueue* mq);
s32 osFlashWriteArray(u32 pageNum);
s32 osFlashReadArray(OSIoMesg* mb, s32 priority, u32 pageNum, void* dramAddr, u32 pageCount, OSMesgQueue* mq);
// void func_801877D0(void);
// void func_80187B64(void);
// void func_80187BEC(void);
// void func_80187DE8(void);
// void func_80187E58(void);
// void func_80187F00(void);
// void func_80187FB0(void);
// void func_80187FE8(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5);
// void func_80188034(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5);
// void func_80188078(void);
// void func_801880C4(void);
// void func_801880E8(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5);
// void func_80188124(void);
// void func_8018814C(void);
// void func_80188174(void);
// void func_801881A8(void);
// void func_801881C4(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5);
// void func_801881F8(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5);
// void func_80188264(void);
// void func_80188288(void);
// void func_801882A0(void);
// void func_80188304(void);
// void func_801884A0(void);
// void func_80188698(void);
// void func_8018883C(void);
// void func_801888E4(void);
// void func_801889A4(void);
// void func_80188A50(void);
// void func_80188AFC(void);
// void func_80188C48(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5);
// void func_80188CB4(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5);
// void func_80188D28(void);
// void func_80188D68(void);
// void func_80188DDC(void);
// void func_80188FBC(void);
// void func_80189064(void);
// void func_80189620(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5,
// UNK_TYPE4 param_6, UNK_TYPE4 param_7); void func_8018A4B4(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3,
// UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6); void func_8018A768(UNK_TYPE1 param_1, UNK_TYPE1 param_2,
// UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE2 param_5, UNK_TYPE4 param_6); void func_8018A808(UNK_TYPE1 param_1,
// UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE2 param_5, UNK_TYPE4 param_6); void
// func_8018ACC4(void); void func_8018AE34(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4,
// UNK_TYPE4 param_5, UNK_TYPE4 param_6);
void AudioHeap_DiscardFont(s32 fontId);
void* AudioHeap_WritebackDCache(void* addr, size_t size);
void* AudioHeap_AllocAttemptExternal(AudioAllocPool* pool, size_t size);
void* AudioHeap_AllocDmaMemory(AudioAllocPool* pool, size_t size);
void* AudioHeap_AllocZeroed(AudioAllocPool* pool, size_t size);
void* AudioHeap_Alloc(AudioAllocPool* pool, size_t size);
void AudioHeap_AllocPoolInit(AudioAllocPool* pool, void* addr, size_t size);
void AudioHeap_PopCache(s32 tableType);
void AudioHeap_InitMainPool(size_t initPoolSize);
void* AudioHeap_AllocCached(s32 tableType, size_t size, s32 cache, s32 id);
void* AudioHeap_SearchCaches(s32 tableType, s32 cache, s32 id);
void AudioHeap_LoadFilter(s16* filter, s32 lowPassCutoff, s32 highPassCutoff);
s32 AudioHeap_ResetStep(void);
void AudioHeap_Init(void);
void* AudioHeap_SearchPermanentCache(s32 tableType, s32 id);
void* AudioHeap_AllocPermanent(s32 tableType, s32 id, size_t size);
void* AudioHeap_AllocSampleCache(size_t size, s32 sampleBankId, void* sampleAddr, s8 medium, s32 cache);
void AudioHeap_ApplySampleBankCache(s32 sampleBankId);
void AudioHeap_SetReverbData(s32 reverbIndex, u32 dataType, s32 data, s32 flags);
void AudioLoad_DecreaseSampleDmaTtls(void);
void* AudioLoad_DmaSampleData(uintptr_t devAddr, size_t size, s32 arg2, u8* dmaIndexRef, s32 medium);
void AudioLoad_InitSampleDmaBuffers(s32 numNotes);
s32 AudioLoad_IsFontLoadComplete(s32 fontId);
s32 AudioLoad_IsSeqLoadComplete(s32 seqId);
void AudioLoad_SetFontLoadStatus(s32 fontId, s32 status);
void AudioLoad_SetSeqLoadStatus(s32 seqId, s32 status);
void AudioLoad_SyncLoadSeqParts(s32 seqId, s32 arg1, s32 arg2, OSMesgQueue* arg3);
s32 AudioLoad_SyncLoadInstrument(s32 fontId, s32 instId, s32 drumId);
void AudioLoad_AsyncLoadSeq(s32 seqId, s32 arg1, s32 retData, OSMesgQueue* retQueue);
void AudioLoad_AsyncLoadSampleBank(s32 sampleBankId, s32 arg1, s32 retData, OSMesgQueue* retQueue);
void AudioLoad_AsyncLoadFont(s32 fontId, s32 arg1, s32 retData, OSMesgQueue* retQueue);
u8* AudioLoad_GetFontsForSequence(s32 seqId, u32* outNumFonts);
void AudioLoad_DiscardSeqFonts(s32 seqId);
void func_8018FA60(u32 tableType, u32 id, s32 arg2, s32 arg3);
s32 AudioLoad_SyncInitSeqPlayer(s32 playerIndex, s32 seqId, s32 arg2);
s32 AudioLoad_SyncInitSeqPlayerSkipTicks(s32 playerIndex, s32 seqId, s32 skipTicks);
void AudioLoad_ProcessLoads(s32 resetStatus);
void AudioLoad_SetDmaHandler(DmaHandler callback);
void AudioLoad_Init(void* heap, u32 heapSize);
void AudioLoad_InitSlowLoads(void);
s32 AudioLoad_SlowLoadSample(s32 fontId, s32 instId, s8* isDone);
s32 AudioLoad_SlowLoadSeq(s32 seqId, u8* ramAddr, s8* isDone);
void AudioLoad_InitAsyncLoads(void);
void AudioLoad_LoadPermanentSamples(void);
void AudioLoad_ScriptLoad(s32 tableType, s32 id, s8* isDone);
void AudioLoad_ProcessScriptLoads(void);
void AudioLoad_InitScriptLoads(void);
AudioTask* func_80192BE0(void);
// void func_80192C00(void);
// void func_8019319C(void);
// void func_801936D8(void);
// void func_8019372C(void);
// void func_80193774(void);
// void func_8019380C(void);
// void func_80193858(void);
// void func_8019387C(void);
void Audio_QueueCmdS8(u32 opArgs, s8 data);
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
u32 Audio_NextRandom(void);
void Audio_InitMesgQueues(void);
void Audio_InvalDCache(void* buf, size_t size);
void Audio_WritebackDCache(void* buf, size_t size);
// void func_80194790(void);
// void func_80194840(void);
// void func_801948B0(void);
void AudioPlayback_NoteDisable(Note* note);
void AudioPlayback_ProcessNotes(void);
SoundFontSound* AudioPlayback_InstrumentGetSound(Instrument* instrument, s32 semitone);
Instrument* AudioPlayback_GetInstrumentInner(s32 fontId, s32 instId);
Drum* AudioPlayback_GetDrum(s32 fontId, s32 drumId);
SoundFontSound* AudioPlayback_GetSfx(s32 fontId, s32 sfxId);
s32 AudioPlayback_SetFontInstrument(s32 instrumentType, s32 fontId, s32 index, void* value);
void AudioPlayback_SeqLayerNoteDecay(SequenceLayer* layer);
void AudioPlayback_SeqLayerNoteRelease(SequenceLayer* layer);
void AudioPlayback_InitSyntheticWave(Note* note, SequenceLayer* layer);
void AudioPlayback_InitNoteLists(NotePool* pool);
void AudioPlayback_InitNoteFreeList(void);
void AudioPlayback_NotePoolClear(NotePool* pool);
void AudioPlayback_NotePoolFill(NotePool* pool, s32 count);
void AudioPlayback_AudioListRemove(AudioListItem* item);
Note* AudioPlayback_AllocNote(SequenceLayer* layer);
void AudioPlayback_NoteInitAll(void);
void AudioEffects_SequencePlayerProcessSound(SequencePlayer* seqPlayer);
void AudioEffects_NoteVibratoUpdate(Note* note);
void AudioEffects_NoteVibratoInit(Note* note);
void AudioEffects_NotePortamentoInit(Note* note);
void AudioEffects_AdsrInit(AdsrState* adsr, EnvelopePoint* envelope, s16* volOut);
f32 AudioEffects_AdsrUpdate(AdsrState* adsr);
void AudioSeq_SequenceChannelDisable(SequenceChannel* channel);
void AudioSeq_SequencePlayerDisableAsFinished(SequencePlayer* seqPlayer);
void AudioSeq_SequencePlayerDisable(SequencePlayer* seqPlayer);
void AudioSeq_AudioListPushBack(AudioListItem* list, AudioListItem* item);
void* AudioSeq_AudioListPopBack(AudioListItem* list);
void AudioSeq_ProcessSequences(s32 arg0);
void AudioSeq_SkipForwardSequence(SequencePlayer* seqPlayer);
void AudioSeq_ResetSequencePlayer(SequencePlayer* seqPlayer);
void AudioSeq_InitSequencePlayerChannels(s32 playerIndex);
void AudioSeq_InitSequencePlayers(void);
void func_8019AE40(s32 param_1, s32 param_2, u32 param_3, s32 param_4);
void func_8019AEC0(UNK_PTR param_1, UNK_PTR param_2);

void AudioOcarina_SetSongStartingPos(void);
void AudioOcarina_StartAtSongStartingPos(u32 ocarinaFlags);
void AudioOcarina_StartForSongCheck(u32 ocarinaFlags, u8 ocarinaStaffPlayingPosStart);
void AudioOcarina_StartWithSongNoteLengths(u32 ocarinaFlags);
void AudioOcarina_StartDefault(u32 ocarinaFlags);
u8 func_8019B5AC(void);
void AudioOcarina_ResetAndReadInput(void);
void AudioOcarina_SetOcarinaDisableTimer(u8 resetUnused, u8 resetDelay);
u32 AudioOcarina_SetInstrument(u8 ocarinaInstrumentId);
void AudioOcarina_SetPlaybackSong(s8 songIndexPlusOne, u8 playbackState);
void AudioOcarina_SetRecordingState(u8 recordingState);
OcarinaStaff* AudioOcarina_GetRecordingStaff(void);
OcarinaStaff* AudioOcarina_GetPlayingStaff(void);
OcarinaStaff* AudioOcarina_GetPlaybackStaff(void);
void AudioOcarina_TerminaWallGenerateNotes(void);
void AudioOcarina_PlayLongScarecrowAfterCredits(void);

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
void func_8019F170(Vec3f* pos, u16 sfxId);
void Audio_PlaySfxAtPos(Vec3f* pos, u16 sfxId);
void func_8019F208(void); // decide sfx
void func_8019F230(void); // cancel sfx
// void func_8019F258(void);
// void func_8019F300(void);
void func_8019F420(Vec3f* pos, u16 sfxId);
void func_8019F4AC(Vec3f* pos, u16 sfxId);
void func_8019F540(s8 arg0);
void func_8019F570(Vec3f* pos, s8 arg1);
// void func_8019F5AC(void);
// void func_8019F638(void);
// void func_8019F780(void);
// void func_8019F7D8(void);
// void func_8019F830(void);
void func_8019F88C(Vec3f* arg0, u16 sfxId, UNK_TYPE arg2);
void func_8019F900(Vec3f* pos, u8 chargeLevel);
// void func_8019FA18(void);
void func_8019FAD8(Vec3f* param_1, u16 sfxId, f32 param_3);
void func_8019FB0C(Vec3f* arg0, u16 sfxId, f32 arg2, s32 arg3);
void func_8019FC20(Vec3f* pos, u16 sfxId);
// void func_8019FCB8(void);
// void func_8019FD90(void);
void func_8019FDC8(UNK_PTR arg0, u16 sfxId, UNK_TYPE arg2);
// void func_8019FE1C(void);
void func_8019FE74(f32* arg0, f32 arg1, s32 arg2);
// void func_8019FEDC(void);
// void func_8019FF38(void);
void Audio_PlaySfxForRiver(Vec3f* pos, f32 freqScale);
// void Audio_PlaySfxForWaterfall(void);
// void Audio_StepFreqLerp(void);
void func_801A0124(Vec3f* pos, u8 arg1);
// void func_801A0184(void);
// void func_801A01C4(void);
void func_801A0204(s8 seqId);
void func_801A0238(s32 arg0, s32 arg1);
// void Audio_SetGanonsTowerBgmVolumeLevel(void);
// void Audio_SetGanonsTowerBgmVolume(void);
// void Audio_UpdateRiverSoundVolumes(void);
// void func_801A0554(void);
// void func_801A05F0(void);
void func_801A0654(Vec3f* arg0, u16 sfxId, s32 arg2);
void func_801A0810(Vec3f* arg0, u16 sfxId, u8 arg2);
void func_801A0868(Vec3f* pos, u16 sfxId, u8 val);
// void func_801A09D4(void);
// void Audio_SplitBgmChannels(void);
// void func_801A0E44(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5,
// UNK_TYPE4 param_6, UNK_TYPE4 param_7); void func_801A1290(void); void func_801A1348(UNK_TYPE1 param_1, UNK_TYPE1
// param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5, UNK_TYPE4 param_6, UNK_TYPE4 param_7); void
// func_801A13BC(void); void func_801A153C(void); void func_801A17F4(void); void func_801A1904(void); void
// func_801A1A10(void); void func_801A1A8C(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4,
// UNK_TYPE4 param_5, UNK_TYPE4 param_6);
void func_801A1D44(Vec3f* vec, u8 seqId, f32 arg2);
void func_801A1DB8(Vec3f* vec, u8 seqId, f32 arg2);
// void func_801A1E0C(void);
void func_801A1F00(u8 arg0, u16 seqId);
void func_801A1F88(void);
void func_801A1FB4(u8 playerIndex, Vec3f* pos, u16 seqId, f32 maxDist);
// void func_801A2090(void);
void func_801A246C(u8 param_1, u8 param_2);
// void func_801A2544(void);
// void func_801A257C(void);
void func_801A25E4(u16 seqId, u8 dayMinusOne);
// void func_801A2670(void);
// void func_801A2778(void);
// void func_801A27E8(void);
// void func_801A281C(void);
void func_801A29D4(UNK_TYPE arg0, f32 arg1, UNK_TYPE arg2);
void func_801A2BB8(s32 seqId);
void func_801A2C20(void);
// void func_801A2C44(void);
void func_801A2C88(u16 seqId);
void func_801A2D54(u16 seqId);
s32 Audio_IsSequencePlaying(u8 seqId);
void func_801A2E54(s32 bgmId);
void func_801A2ED8(void);
// void func_801A2F88(void);
// void func_801A3000(void);
// void func_801A3038(void);
void func_801A3098(u16 seqId);
// void func_801A312C(void);
void func_801A31EC(u16 seqId, s8 arg1, u8 arg2);
// void func_801A3238(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE1 param_5);
// void func_801A32CC(void);
// void func_801A3590(void);
u8 func_801A3950(s32 playerIndex, s32 isChannelIOSet);
u8 func_801A39F8(void);
void func_801A3A7C(s32 arg0);
// void func_801A3AC0(void);
void func_801A3AEC(s32 arg0);
void func_801A3B48(UNK_TYPE arg0);
// void func_801A3B90(void);
void func_801A3CD8(s8 param_1);
// void func_801A3CF4(void);
void func_801A3D98(s8 audioSetting);
// void func_801A3E38(void);
// void func_801A3EC0(void);
void Audio_SetCutsceneFlag(u8 flag);
// void func_801A3F6C(UNK_TYPE1 param_1, UNK_TYPE1 param_2, UNK_TYPE1 param_3, UNK_TYPE1 param_4, UNK_TYPE4 param_5,
// UNK_TYPE4 param_6); void func_801A3FB4(void); void func_801A3FFC(UNK_TYPE1 param_1);
void audio_setBGM(u32 bgmID);
void func_801A4058(UNK_TYPE arg0);
// void func_801A41C8(void);
// void func_801A41F8(void);
// void func_801A429C(void);
// void func_801A42C8(void);
// void func_801A4324(void);
// void func_801A4348(void);
void Audio_SetSfxVolumeExceptSystemAndOcarinaBanks(u8 arg0);
void func_801A4428(u8 reverbIndex);
void Audio_PreNMI(void);
// void func_801A44C4(void);
// void func_801A44D4(void);
s32 func_801A46F8(void);
void func_801A4748(Vec3f* pos, u16 sfxId);
void func_801A479C(Vec3f* arg0, u16 sfxId, s32 arg2);
void func_801A47DC(u8 channelIndexRange, u8 port, u8 val);
// void func_801A48E0(void);
void func_801A4A28(u8 natureSeqId);
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
void func_801A5080(u16 arg0);
u16 func_801A5100(void);
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
void Audio_SetSfxBanksMute(u16 muteMask);
void Audio_SetFlagForBgmVolumeLow(u8 channelIndex);
void Audio_ClearFlagForBgmVolumeLow(u8 channelIndex);
void Audio_PlaySfxGeneral(u16 sfxId, Vec3f* param_2, u8 param_3, f32* param_4, f32* param_5, s8* param_6);
// void func_801A5DDC(void);
// void func_801A5F7C(void);
// void func_801A6430(void);
// void func_801A65C8(void);
// void func_801A6D0C(void);
void func_801A7084(u8 bankId);
// void func_801A7168(void);
// void func_801A7284(void);
void Audio_StopSfxByPos(Vec3f* pos);
void func_801A7328(Vec3f* pos, u16 sfxId);
// void func_801A7484(void);
void Audio_StopSfxById(u16 sfxId);
// void func_801A7720(void);
void func_801A7794(u32 param_1, u32 param_2, u32 param_3);
// void func_801A7828(void);
// void func_801A787C(void);
u8 Audio_IsSfxPlaying(u32 sfxId);
// void func_801A794C(void);
// void func_801A7B10(void);
// void func_801A7D04(void);
// void func_801A7D84(void);
void Audio_QueueSeqCmd(u32 cmd);
// void func_801A89D0(void);
s32 func_801A8A50(s32 param1);
// void func_801A8ABC(void);
void Audio_SetVolumeScale(u8 playerIndex, u8 scaleIndex, u8 targetVol, u8 volFadeTimer);
// void func_801A8D5C(void);
// void func_801A8E90(void);
// void func_801A9768(void);
// void func_801A982C(void);
// void func_801A99B8(void);
// void func_801A9A74(void);

void GameOver_Init(PlayState* play);
void GameOver_FadeLights(PlayState* play);
void GameOver_Update(PlayState* play);
void func_801AAAA0(PlayState* play);

#endif
