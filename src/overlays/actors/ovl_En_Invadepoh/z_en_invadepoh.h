#ifndef Z_EN_INVADEPOH_H
#define Z_EN_INVADEPOH_H

#include "global.h"
#include "assets/objects/object_cow/object_cow.h"
#include "assets/objects/object_dog/object_dog.h"
#include "assets/objects/object_ma1/object_ma1.h"
#include "assets/objects/object_ma2/object_ma2.h"
#include "assets/objects/object_uch/object_uch.h"

struct EnInvadepoh;

typedef void (*EnInvadepohActionFunc)(struct EnInvadepoh* this, PlayState* play);
typedef void (*EnInvadepohInitFunc)(struct EnInvadepoh* this, PlayState* play);
typedef void (*EnInvadepohDestroyFunc)(struct EnInvadepoh* this, PlayState* play);

#define EN_INVADEPOH_GET_INDEX(thisx) ((thisx)->params & 7)
#define EN_INVADEPOH_GET_TYPE(thisx) ((thisx)->params >> 4 & 0xF)
#define EN_INVADEPOH_GET_PATH(thisx) ((thisx)->params >> 8 & 0x7F)

#define EN_INVADEPOH_PARAMS(path, type, index) (((index) & 7) | (((path) << 8) & 0x7F00) | (((type) << 4) & 0xF0))

typedef enum EnInvadepohType {
    /* 0x0 */ EN_INVADEPOH_TYPE_INVASION_HANDLER, // Alien invasion event handler
    /* 0x1 */ EN_INVADEPOH_TYPE_ALIEN,            // The aliens that approach the barn
    /* 0x2 */ EN_INVADEPOH_TYPE_COW,              // An unused abudcted cow, spawned by the alien abductor
    /* 0x3 */ EN_INVADEPOH_TYPE_COW_TAIL,         // An unused abducted cow tail, spawned by the abducted cow
    /* 0x4 */ EN_INVADEPOH_TYPE_ROMANI_ABDUCTED,  // An unused abducted Romani, spawned by alien abductor
    /* 0x5 */ EN_INVADEPOH_TYPE_ROMANI_SILENT,    // A confused, silent Romani that wanders the ranch on day 2
    /* 0x6 */ EN_INVADEPOH_TYPE_UFO,              // The spinning ball of light that spawns the aliens and hovers over the barn
    /* 0x7 */ EN_INVADEPOH_TYPE_ROMANI_NIGHT_1,   // Romani running to the barn on night 1
    /* 0x8 */ EN_INVADEPOH_TYPE_ROMANI_BARN,      // Romani in the barn on night 1
    /* 0x9 */ EN_INVADEPOH_TYPE_ROMANI_REWARD,    // Romani rewarding you for defending the ranch from the aliens
    /* 0xA */ EN_INVADEPOH_TYPE_DOG,              // Dog during alien invasion
    /* 0xB */ EN_INVADEPOH_TYPE_CREMIA_NIGHT_3,   // Cremia walking from the barn to the house on night 3
    /* 0xC */ EN_INVADEPOH_TYPE_ROMANI_NIGHT_3,   // Romnani walking from the barn to the house on night 3
    /* 0xD */ EN_INVADEPOH_TYPE_ALIEN_ABDUCTOR,   // An unused alien variant that can carry either a cow or Romani
    /* 0xE */ EN_INVADEPOH_TYPE_MAX
} EnInvadepohType;

#define EN_INVADEPOH_PATH_INDEX_NONE 0xFF

typedef struct EnInvadepohFaceFrames {
    /* 0x0 */ s8* texIndex;
    /* 0x1 */ s8 count;
} EnInvadepohFaceFrames; // size = 0x2

typedef struct EnInvadepohFaceAnimNext {
    /* 0x0 */ s8 index;
    /* 0x4 */ f32 chance;
} EnInvadepohFaceAnimNext; // size = 0x8

typedef struct {
    /* 0x0 */ s8 type;
    /* 0x4 */ EnInvadepohFaceFrames* frames;
} EnInvadepohFaceAnim; // size = 0x8

typedef struct {
    /* 0x0 */ EnInvadepohFaceAnim anim;
    /* 0x8 */ s8 nextCount;
    /* 0xC */ EnInvadepohFaceAnimNext* nextAnims;
} EnInvadepohFaceAnimBranched; // size = 0x10

typedef struct {
    /* 0x00 */ EnInvadepohFaceAnimBranched loop;
    /* 0x10 */ s16 minDelay;
    /* 0x12 */ s16 maxDelay;
} EnInvadepohFaceAnimDelayedBranched; // size = 0x14

typedef struct EnInvadepohFaceAnimInfo {
    /* 0x0 */ EnInvadepohFaceAnim** animations;
    /* 0x4 */ s8 curAnimType;
    /* 0x8 */ EnInvadepohFaceAnim* curAnim;
    /* 0xC */ s16 delayTimer;
    /* 0xE */ s8 curFrame;
    /* 0xF */ s8 curIndex;
} EnInvadepohFaceAnimInfo; // size = 0x10

typedef struct EnInvadepohInteractInfo {
    /* 0x00 */ EnInvadepohFaceAnimInfo eyeAnim;
    /* 0x10 */ EnInvadepohFaceAnimInfo mouthAnim;
    /* 0x20 */ Vec3s headRot;
    /* 0x26 */ Vec3s headRotTarget;
    /* 0x2C */ s16 headRotMaxStep;
    /* 0x30 */ f32 headRotStepScale;
    /* 0x34 */ f32 torsoRotScaleY;
    /* 0x38 */ f32 torsoRotScaleTargetY;
    /* 0x3c */ f32 torsoRotScaleStepY;
    /* 0x40 */ s16 torsoRotX;
    /* 0x42 */ s16 torsoTargetRotX;
    /* 0x44 */ f32 torsoRotStepScale;
    /* 0x48 */ s16 torsoRotMaxStep;
} EnInvadepohInteractInfo; // size = 0x4C

typedef void (*EnInvadepohFaceFunc) (EnInvadepohFaceAnimInfo*, EnInvadepohFaceAnim**);

#define EN_INVADEPOH_LIMB_MAX \
    MAX(MAX(MAX(MAX(MAX((s32)COW_LIMB_MAX, \
                        (s32)COW_TAIL_LIMB_MAX), \
                        (s32)DOG_LIMB_MAX), \
                        (s32)ROMANI_LIMB_MAX), \
                        (s32)CREMIA_LIMB_MAX), \
                        (s32)ALIEN_LIMB_MAX)

typedef struct EnInvadepoh {
    /* 0x000 */ Actor actor;
    /* 0x144 */ SkelAnime skelAnime;
    /* 0x188 */ Vec3s jointTable[EN_INVADEPOH_LIMB_MAX];
    /* 0x212 */ Vec3s morphTable[EN_INVADEPOH_LIMB_MAX];
    /* 0x29C */ s8 isAnimFinished;
    /* 0x2A0 */ ColliderCylinder collider;
    /* 0x2EC */ EnInvadepohActionFunc actionFunc;
    /* 0x2F0 */ s16 timer;
    /* 0x2F2 */ s16 frameCounter;
    /* 0x2F4 */ s8 objectSlot;
    /* 0x2F8 */ f32 distanceToRomani;
    /* 0x2FC */ UNK_TYPE1 unk_2FC[4];
    /* 0x300 */ f32 alienAbductorAccelY;
    /* 0x304 */ s16 angle;
    /* 0x306 */ s16 angularVelocity;
    /* 0x308 */ s8 endPoint;
    /* 0x309 */ s8 currentPoint;
    /* 0x30A */ s8 pathStep;
    /* 0x30C */ Vec3s *pathPoints;
    /* 0x310 */ f32 pathLength;
    /* 0x314 */ Vec3f currentPos;
    /* 0x320 */ f32 pathProgress;
    /* 0x324 */ EnInvadepohInteractInfo interactInfo;
    /* 0x370 */ s16 shapeAngularVelocityY;
    /* 0x372 */ s16 shapeAngularAccelerationY;
    /* 0x374 */ s8 silentRomaniState;
    /* 0x376 */ u16 textId;
    /* 0x378 */ s8 doorOpened;
    /* 0x379 */ s8 alienCount;
    /* 0x37C */ f32 pathCheckpoints[3];
    /* 0x388 */ UNK_TYPE1 unk_388;
    /* 0x389 */ u8 alpha;
    /* 0x38A */ s8 pathCompleted;
    /* 0x38B */ s8 shouldDraw;
    /* 0x38C */ s8 shouldDrawDeathFlash;
    /* 0x38D */ u8 eyeBeamAlpha;
    /* 0x390 */ Vec3f deathFlashScale;
    /* 0x39C */ f32 ufoPulseScale;
    /* 0x3A0 */ f32 ufoPulseScaleTarget;
    /* 0x3A4 */ f32 ufoPulseScaleSpeed;
    /* 0x3A8 */ s16 ufoPulsePhase;
    /* 0x3AA */ s16 ufoPulsePhaseVelocity;
    /* 0x3AC */ s8 ufoTargetPosIndex;
    /* 0x3AD */ UNK_TYPE1 unk_3AD[0xF];
    /* 0x3BC */ s8 dogTargetPoint;
} EnInvadepoh; // size = 0x3C0

#endif // Z_EN_INVADEPOH_H
