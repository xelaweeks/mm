#include "global.h"
#include "initvars.h"

#define DEFINE_ACTOR(name, _1, allocType, _3)                                                   \
    {                                                                                          \
        SEGMENT_ROM_START(ovl_##name), SEGMENT_ROM_END(ovl_##name), SEGMENT_START(ovl_##name), \
            SEGMENT_END(ovl_##name), NULL, &name##_InitVars, NULL, allocType, 0                \
    }

#define DEFINE_ACTOR_INTERNAL(name, _1, allocType, _3) \
    { 0, 0, NULL, NULL, NULL, &name##_InitVars, NULL, allocType, 0 }

#define DEFINE_ACTOR_UNSET(_1) \
    { 0 }

ActorOverlay gActorOverlayTable[] = {
#include "tables/actor_table.h"
};

s32 gMaxActorId = 0;

FaultClient D_801ED930;
FaultAddrConvClient D_801ED940;

void ActorOverlayTable_FaultPrint(void* arg0, void* arg1) {
    ActorOverlay* overlayEntry;
    u32 overlaySize;
    s32 i;

    FaultDrawer_SetCharPad(-2, 0);

    FaultDrawer_Printf("actor_dlftbls %u\n", gMaxActorId);
    FaultDrawer_Printf("No. RamStart- RamEnd cn  Name\n");

    for (i = 0, overlayEntry = &gActorOverlayTable[0]; i < gMaxActorId; i++, overlayEntry++) {
        overlaySize = VRAM_PTR_SIZE(overlayEntry);
        if (overlayEntry->loadedRamAddr != NULL) {
            FaultDrawer_Printf("%3d %08x-%08x %3d %s\n", i, overlayEntry->loadedRamAddr,
                               (u32)overlayEntry->loadedRamAddr + overlaySize, overlayEntry->numLoaded, "");
        }
    }
}

void* ActorOverlayTable_FaultAddrConv(void* arg0, void* arg1) {
    u8* ptr = arg0;
    ActorOverlay* overlayEntry = &gActorOverlayTable[0];
    s32 i;
    u8* ramStart;
    u8* ramEnd;
    size_t size;
    u32 offset;

    for (i = 0; i < gMaxActorId; i++, overlayEntry++) {
        size = VRAM_PTR_SIZE(overlayEntry);
        ramStart = overlayEntry->loadedRamAddr;
        ramEnd = ramStart + size;
        offset = (u8*)overlayEntry->vramStart - ramStart;
        if (ramStart != NULL) {
            if (ptr >= ramStart && ptr < ramEnd) {
                return ptr + offset;
            }
        }
    }
    return NULL;
}

void ActorOverlayTable_Init(void) {
    gMaxActorId = ACTOR_ID_MAX;
    Fault_AddClient(&D_801ED930, &ActorOverlayTable_FaultPrint, NULL, NULL);
    Fault_AddAddrConvClient(&D_801ED940, &ActorOverlayTable_FaultAddrConv, NULL);
}

void ActorOverlayTable_Cleanup(void) {
    Fault_RemoveClient(&D_801ED930);
    Fault_RemoveAddrConvClient(&D_801ED940);
    gMaxActorId = 0;
}
