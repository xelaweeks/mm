#include "global.h"

void __assert(const char* file, int lineNum) {
    osGetThreadId(NULL);
    Fault_AddHungupAndCrash(file, lineNum);
}

void func_800862B4(void) {
    Fault_AddHungupAndCrash("Reset", 0);
}
