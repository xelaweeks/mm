#ifndef Z_EN_WEATHER_TAG_H
#define Z_EN_WEATHER_TAG_H

#include <global.h>

struct EnWeatherTag;

typedef void (*EnWeatherTagActionFunc)(struct EnWeatherTag*, GlobalContext*);

typedef struct EnWeatherTag {
    /* 0x000 */ Actor actor;
    /* 0x144 */ EnWeatherTagActionFunc actionFunc;
    /* 0x148 */ u8 pad148[0x4];
    /* 0x14C */ u8 pathCount;
    /* 0x150 */ Vec3s* pathPoints;
    /* 0x154 */ u16 unk154; // treated as signed in some places, but wont match
    /* 0x156 */ u16 fadeDistance;
    /* 0x158 */ u16 unk158; // increment/decrement amount for 154
} EnWeatherTag; // size = 0x15C

extern const ActorInit En_Weather_Tag_InitVars;

#define WEATHER_TAG_TYPE(x) (x & 0xF)
#define WEATHER_TAG_PATHID(x) (x >> 4 & 0xF)
#define WEATHER_TAG_RANGE100(x) ((u8)(((x >> 8) & 0xFF)) * 100.0f)
#define WEATHER_TAG_RANGE100INT(x) ((u8)(((x >> 8))) * 100)

#endif // Z_EN_WEATHER_TAG_H
