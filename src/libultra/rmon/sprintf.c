#include "global.h"

void* proutSprintf(void* dst, const char* fmt, size_t size) {
    return (void*)((uintptr_t)memcpy(dst, fmt, size) + size);
}

int vsprintf(char* dst, char* fmt, va_list args) {
    int ans = _Printf(proutSprintf, dst, fmt, args);
    if (ans > -1) {
        dst[ans] = 0;
    }
    return ans;
}

int sprintf(char* dst, char* fmt, ...) {
    int ans;
    va_list ap;
    va_start(ap, fmt);

    ans = _Printf(&proutSprintf, dst, fmt, ap);
    if (ans > -1) {
        dst[ans] = 0;
    }
    return ans;
}
