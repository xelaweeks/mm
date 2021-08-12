#include "prevent_bss_reordering.h"
#include "global.h"
#include "overlays/gamestates/ovl_daytelop/z_daytelop.h"
#include "overlays/gamestates/ovl_file_choose/z_file_choose.h"
#include "overlays/gamestates/ovl_opening/z_opening.h"
#include "overlays/gamestates/ovl_select/z_select.h"
#include "overlays/gamestates/ovl_title/z_title.h"

FaultAddrConvClient sGraphFaultAddrConvClient;
FaultClient sGraphFaultClient;
GfxMasterList* gGfxMasterDL;
CfbInfo sGraphCfbInfos[3];
OSTime sGraphTaskStartTime;

void* Graph_FaultClient(void) {
    FaultDrawer_DrawText(30, 100, "ShowFrameBuffer PAGE 0/1");
    osViSwapBuffer(SysCfb_GetFbPtr(0));
    osViSetMode(D_801FBB88);
    osViSetSpecialFeatures(OS_VI_DITHER_FILTER_ON | OS_VI_GAMMA_OFF);
    Fault_WaitForInput();
    osViSwapBuffer(SysCfb_GetFbPtr(1));
    osViSetMode(D_801FBB88);
    osViSetSpecialFeatures(OS_VI_DITHER_FILTER_ON | OS_VI_GAMMA_OFF);
}

void Graph_InitTHGA(TwoHeadGfxArena* arena, Gfx* buffer, s32 size) {
    THGA_Ct(arena, buffer, size);
}

void Graph_SetNextGfxPool(GraphicsContext* gfxCtx) {
    GfxPool* pool = &gGfxPools[gfxCtx->gfxPoolIdx % 2];

    gGfxMasterDL = &pool->master;
    gSegments[0x0E] = gGfxMasterDL;

    pool->headMagic = GFXPOOL_HEAD_MAGIC;
    pool->tailMagic = GFXPOOL_TAIL_MAGIC;

    Graph_InitTHGA(&gfxCtx->polyOpa, pool->polyOpaBuffer, sizeof(pool->polyOpaBuffer));
    Graph_InitTHGA(&gfxCtx->polyXlu, pool->polyXluBuffer, sizeof(pool->polyXluBuffer));
    Graph_InitTHGA(&gfxCtx->overlay, pool->overlayBuffer, sizeof(pool->overlayBuffer));
    Graph_InitTHGA(&gfxCtx->work, pool->workBuffer, sizeof(pool->workBuffer));
    Graph_InitTHGA(&gfxCtx->debug, pool->debugBuffer, sizeof(pool->debugBuffer));

    gfxCtx->polyOpaBuffer = pool->polyOpaBuffer;
    gfxCtx->polyXluBuffer = pool->polyXluBuffer;
    gfxCtx->overlayBuffer = pool->overlayBuffer;
    gfxCtx->workBuffer = pool->workBuffer;
    gfxCtx->debugBuffer = pool->debugBuffer;

    gfxCtx->curFrameBuffer = SysCfb_GetFbPtr(gfxCtx->framebufferIdx % 2);
    gSegments[0x0F] = gfxCtx->curFrameBuffer;

    gfxCtx->zbuffer = SysCfb_GetZBuffer();

    gSPBranchList(&gGfxMasterDL->disps[0], pool->polyOpaBuffer);
    gSPBranchList(&gGfxMasterDL->disps[1], pool->polyXluBuffer);
    gSPBranchList(&gGfxMasterDL->disps[2], pool->overlayBuffer);
    gSPBranchList(&gGfxMasterDL->disps[3], pool->workBuffer);
    gSPEndDisplayList(&gGfxMasterDL->disps[4]);
    gSPBranchList(&gGfxMasterDL->debugDisp[0], pool->debugBuffer);
}

GameStateOverlay* Graph_GetNextGameState(GameState* gameState) {
    GameStateFunc gameStateInit = Game_GetNextStateInit(gameState);

    if (gameStateInit == (GameStateFunc)TitleSetup_Init) {
        return &gGameStateOverlayTable[0];
    }
    if (gameStateInit == (GameStateFunc)Select_Init) {
        return &gGameStateOverlayTable[1];
    }
    if (gameStateInit == (GameStateFunc)Title_Init) {
        return &gGameStateOverlayTable[2];
    }
    if (gameStateInit == (GameStateFunc)Play_Init) {
        return &gGameStateOverlayTable[3];
    }
    if (gameStateInit == (GameStateFunc)Opening_Init) {
        return &gGameStateOverlayTable[4];
    }
    if (gameStateInit == (GameStateFunc)FileChoose_Init) {
        return &gGameStateOverlayTable[5];
    }
    if (gameStateInit == (GameStateFunc)Daytelop_Init) {
        return &gGameStateOverlayTable[6];
    }
    return NULL;
}

#ifdef NON_MATCHING
// Regalloc differences
void* Graph_FaultAddrConvFunc(void* address, void* param) {
    u32 addr = address;
    GameStateOverlay* gamestateOvl;
    u32 ramConv;
    u32 ramStart;
    u32 diff;
    s32 i;

    for (i = 0; i < graphNumGameStates; i++) {
        gamestateOvl = &gGameStateOverlayTable[i];
        ramStart = gamestateOvl->loadedRamAddr;
        diff = (u32)gamestateOvl->vramEnd - (u32)gamestateOvl->vramStart;
        ramConv = (u32)gamestateOvl->vramStart - ramStart;

        if (gamestateOvl->loadedRamAddr != NULL) {
            if (addr >= ramStart && addr < ramStart + diff) {
                return addr + ramConv;
            }
        }
    }
    return NULL;
}
#else
#pragma GLOBAL_ASM("asm/non_matchings/code/graph/Graph_FaultAddrConvFunc.s")
#endif

void Graph_Init(GraphicsContext* gfxCtx) {
    bzero(gfxCtx, sizeof(GraphicsContext));
    gfxCtx->gfxPoolIdx = 0;
    gfxCtx->framebufferIdx = 0;
    gfxCtx->viMode = NULL;
    gfxCtx->viConfigFeatures = gViConfigFeatures;
    gfxCtx->xScale = gViConfigXScale;
    gfxCtx->yScale = gViConfigYScale;
    osCreateMesgQueue(&gfxCtx->queue, gfxCtx->msgBuff, ARRAY_COUNT(gfxCtx->msgBuff));
    Fault_AddClient(&sGraphFaultClient, (fault_client_func)Graph_FaultClient, NULL, NULL);
    Fault_AddAddrConvClient(&sGraphFaultAddrConvClient, (fault_address_converter_func)Graph_FaultAddrConvFunc, NULL);
}

void Graph_Destroy(GraphicsContext* gfxCtx) {
    Fault_RemoveClient(&sGraphFaultClient);
    Fault_RemoveAddrConvClient(&sGraphFaultAddrConvClient);
}

/**
 * Constructs the graphics OSTask and forwards it to the scheduler.
 * Waits for up to 3 additional seconds for any current graphics task to complete.
 * If it does not signal completion in that time, retry or trigger a crash.
 */
void Graph_TaskSet00(GraphicsContext* gfxCtx, GameState* gameState) {
    static s32 retryCount = 10; // retry count?
    static s32 cfbIdx = 0;

    OSTask_t* task = &gfxCtx->task.list.t;
    OSScTask* scTask = &gfxCtx->task;
    OSTimer timer;
    OSMesg msg;
    CfbInfo* cfb;

retry:
    osSetTimer(&timer, OS_USEC_TO_CYCLES(3 * 1000 * 1000), 0, &gfxCtx->queue, (OSMesg)666);
    osRecvMesg(&gfxCtx->queue, &msg, OS_MESG_BLOCK);
    osStopTimer(&timer);

    if (msg == (OSMesg)666) {
        osSyncPrintf("GRAPH SP TIMEOUT\n");
        if (retryCount >= 0) {
            retryCount--;
            Sched_SendGfxCancelMsg(&gSchedContext);
            goto retry;
        } else {
            // graph.c: No more! die!
            osSyncPrintf("graph.c:もうダメ！死ぬ！\n");
            Fault_AddHungupAndCrashImpl("RCP is HUNG UP!!", "Oh! MY GOD!!");
        }
    }

    gfxCtx->masterList = gGfxMasterDL;
    if (gfxCtx->callback != NULL) {
        gfxCtx->callback(gfxCtx, gfxCtx->callbackParam);
    }

    task->type = M_GFXTASK;
    task->flags = OS_SC_DRAM_DLIST;
    task->ucode_boot = SysUcode_GetUCodeBoot();
    task->ucode_boot_size = SysUcode_GetUCodeBootSize();
    task->ucode = SysUcode_GetUCode();
    task->ucode_data = SysUcode_GetUCodeData();
    task->ucode_size = 0x1000;
    task->ucode_data_size = 0x800;
    task->dram_stack = (u64*)gGfxSPTaskStack;
    task->dram_stack_size = sizeof(gGfxSPTaskStack);
    task->output_buff = gGfxSPTaskOutputBufferPtr;
    task->output_buff_size = gGfxSPTaskOutputBufferSize;
    task->data_ptr = (u64*)gGfxMasterDL;
    task->data_size = 0;
    task->yield_data_ptr = (u64*)gGfxSPTaskYieldBuffer;
    task->yield_data_size = sizeof(gGfxSPTaskYieldBuffer);

    scTask->next = NULL;
    scTask->flags = OS_SC_RCP_MASK | OS_SC_SWAPBUFFER | OS_SC_LAST_TASK;

    if (SREG(33) & 1) {
        SREG(33) &= ~1;
        scTask->flags &= ~OS_SC_SWAPBUFFER;
        gfxCtx->framebufferIdx--;
    }

    scTask->msgQ = &gfxCtx->queue;
    scTask->msg = NULL;

    { s32 pad; }

    cfb = &sGraphCfbInfos[cfbIdx];
    cfbIdx = (cfbIdx + 1) % ARRAY_COUNT(sGraphCfbInfos);

    cfb->fb1 = gfxCtx->curFrameBuffer;
    cfb->swapBuffer = gfxCtx->curFrameBuffer;

    if (gfxCtx->updateViMode) {
        gfxCtx->updateViMode = false;
        cfb->viMode = gfxCtx->viMode;
        cfb->features = gfxCtx->viConfigFeatures;
        cfb->xScale = gfxCtx->xScale;
        cfb->yScale = gfxCtx->yScale;
    } else {
        cfb->viMode = NULL;
    }
    cfb->unk_10 = 0;
    cfb->updateRate = gameState->framerateDivisor;

    scTask->framebuffer = cfb;

    while (gfxCtx->queue.validCount != 0) {
        osRecvMesg(&gfxCtx->queue, NULL, OS_MESG_NOBLOCK);
    }

    gfxCtx->schedMsgQ = &gSchedContext.cmdQ;
    osSendMesg(&gSchedContext.cmdQ, scTask, OS_MESG_BLOCK);
    Sched_SendEntryMsg(&gSchedContext);
}

void Graph_UpdateGame(GameState* state) {
    Game_UpdateInput(state);
    Game_IncrementFrameCount(state);
    if (SREG(20) < 3) {
        func_8019E014();
    }
}

/**
 *  Run the gamestate logic, then finalize the gfx buffer
 *  and run the graphics task for this frame.
 */
void Graph_ExecuteAndDraw(GraphicsContext* gfxCtx, GameState* gameState) {
    u32 problem;

    gameState->unk_A3 = 0;
    Graph_SetNextGfxPool(gfxCtx);

    Game_Update(gameState);

    OPEN_DISPS(gfxCtx);

    gSPEndDisplayList(WORK_DISP++);
    gSPEndDisplayList(POLY_OPA_DISP++);
    gSPEndDisplayList(POLY_XLU_DISP++);
    gSPEndDisplayList(OVERLAY_DISP++);
    gSPEndDisplayList(DEBUG_DISP++);

    CLOSE_DISPS(gfxCtx);

    {
        Gfx* gfx = gGfxMasterDL->taskStart;

        gSPSegment(gfx++, 0x0E, gGfxMasterDL);
        gSPDisplayList(gfx++, &D_0E000000.disps[3]);
        gSPDisplayList(gfx++, &D_0E000000.disps[0]);
        gSPDisplayList(gfx++, &D_0E000000.disps[1]);
        gSPDisplayList(gfx++, &D_0E000000.disps[2]);
        gSPDisplayList(gfx++, &D_0E000000.debugDisp[0]);

        gDPPipeSync(gfx++);
        gDPFullSync(gfx++);
        gSPEndDisplayList(gfx++);
    }

    problem = false;

    {
        GfxPool* pool = &gGfxPools[gfxCtx->gfxPoolIdx % 2];

        if (pool->headMagic != GFXPOOL_HEAD_MAGIC) {
            Fault_AddHungupAndCrash("../graph.c", 1054);
        }
        if (pool->tailMagic != GFXPOOL_TAIL_MAGIC) {
            Fault_AddHungupAndCrash("../graph.c", 1066);
        }
    }

    if (THGA_IsCrash(&gfxCtx->polyOpa)) {
        problem = true;
    }
    if (THGA_IsCrash(&gfxCtx->polyXlu)) {
        problem = true;
    }
    if (THGA_IsCrash(&gfxCtx->overlay)) {
        problem = true;
    }
    if (THGA_IsCrash(&gfxCtx->work)) {
        problem = true;
    }
    if (THGA_IsCrash(&gfxCtx->debug)) {
        problem = true;
    }

    if (!problem) {
        Graph_TaskSet00(gfxCtx, gameState);
        gfxCtx->gfxPoolIdx++;
        gfxCtx->framebufferIdx++;
    }

    {
        OSTime time = osGetTime();

        D_801FBAE8 = sRSPGFXTotalTime;
        D_801FBAE0 = gRSPAudioTotalTime;
        D_801FBAF0 = gRDPTotalTime;
        sRSPGFXTotalTime = 0;
        gRSPAudioTotalTime = 0;
        gRDPTotalTime = 0;

        if (sGraphTaskStartTime != 0) {
            lastRenderFrameDuration = time - sGraphTaskStartTime;
        }
        sGraphTaskStartTime = time;
    }
}

void Graph_Update(GraphicsContext* gfxCtx, GameState* gameState) {
    gameState->unk_A3 = 0;

    Graph_UpdateGame(gameState);
    Graph_ExecuteAndDraw(gfxCtx, gameState);
}

void Graph_ThreadEntry(void* arg) {
    GraphicsContext gfxCtx;
    GameStateOverlay* nextOvl = &gGameStateOverlayTable[0];
    GameStateOverlay* ovl;
    GameState* gameState;
    u32 size;
    s32 pad[2];

    gZBuffer = StartHeap_Alloc(sizeof(*gZBuffer) + sizeof(*gWorkBuffer) + 64 - 1);
    gZBuffer = (void*)ALIGN64((u32)gZBuffer);

    gWorkBuffer = (void*)((u8*)gZBuffer + sizeof(*gZBuffer));

    gGfxSPTaskOutputBuffer2 = gGfxSPTaskOutputBuffer = StartHeap_Alloc(sizeof(*gGfxSPTaskOutputBuffer));

    gGfxSPTaskOutputBufferEnd = (u8*)gGfxSPTaskOutputBuffer + sizeof(*gGfxSPTaskOutputBuffer);
    gGfxSPTaskOutputBufferEnd2 = (u8*)gGfxSPTaskOutputBuffer2 + sizeof(*gGfxSPTaskOutputBuffer2);

    func_80178978();
    Fault_SetFB(D_801FBB90, SCREEN_WIDTH, SCREEN_HEIGHT);
    Graph_Init(&gfxCtx);

    while (nextOvl) {
        ovl = nextOvl;

        DLF_LoadGameState(ovl);

        size = ovl->instanceSize;

        func_800809F4(ovl->vromStart);

        gameState = StartHeap_Alloc(size);

        bzero(gameState, size);
        Game_StateInit(gameState, ovl->init, &gfxCtx);

        while (Game_GetShouldContinue(gameState)) {
            Graph_Update(&gfxCtx, gameState);
        }

        nextOvl = Graph_GetNextGameState(gameState);

        if (size) {}

        Game_StateFini(gameState);
        StartHeap_Free(gameState);

        DLF_FreeGameState(ovl);
    }
    Graph_Destroy(&gfxCtx);
}
