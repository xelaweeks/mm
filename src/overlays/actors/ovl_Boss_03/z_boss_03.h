#ifndef Z_BOSS_03_H
#define Z_BOSS_03_H

#include "global.h"
#include "objects/object_boss03/object_boss03.h"

struct Boss03;

typedef void (*Boss03ActionFunc)(struct Boss03*, GlobalContext*);

#define GYORG_WORK_TIMER_MAX 3

typedef struct {
    /* 0x00 */ u8 type;
    /* 0x02 */ s16 unk_02;
    /* 0x04 */ Vec3f pos;
    /* 0x10 */ Vec3f velocity;
    /* 0x1C */ Vec3f accel;
    /* 0x28 */ UNK_TYPE1 unk_28[0x4];
    /* 0x2C */ s16 alpha;
    /* 0x2E */ s16 unk_2E;
    /* 0x30 */ UNK_TYPE1 unk_30[0x4];
    /* 0x34 */ Vec3f unk_34; // it may not be a Vec3f
    /* 0x40 */ f32 unk_40;
} GyorgEffect; // size = 0x44

#define GYORG_EFFECT_COUNT 150

typedef struct Boss03 {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ UNK_TYPE1 unk_144[0x04];
    /* 0x0148 */ SkelAnime skelAnime;
    /* 0x018C */ Vec3s jointTable[GYORG_LIMB_MAX];
    /* 0x01E6 */ Vec3s morphTable[GYORG_LIMB_MAX];
    /* 0x0240 */ s16 unk_240; // used by Gyorg and seaweed
    /* 0x0242 */ u8 unk_242;
    /* 0x0243 */ UNK_TYPE1 unk_243[0x01];
    /* 0x0244 */ UNK_TYPE1 unk_244[0x08];
    /* 0x024C */ s16 workTimer[GYORG_WORK_TIMER_MAX];
    /* 0x0252 */ s8 unk_252; // number of Tanron3 fish that are currently alive, maybe "numSmallFishAlive"?
    /* 0x0253 */ u8 unk_253;
    /* 0x0254 */ s16 unk_254;
    /* 0x0258 */ f32 waterHeight; // always 430.0f
    /* 0x025C */ s16 unk_25C;
    /* 0x025E */ s16 unk_25E;
    /* 0x0260 */ f32 unk_260; // rotY
    /* 0x0264 */ UNK_TYPE1 unk_264[0x04];
    /* 0x0268 */ Vec3f unk_268; //set to player.world.pos
    /* 0x0274 */ s16 unk_274;
    /* 0x0276 */ s16 unk_276;
    /* 0x0278 */ f32 unk_278;
    /* 0x027C */ f32 unk_27C;
    /* 0x0280 */ s16 unk_280;
    /* 0x0284 */ f32 unk_284; // Maybe a Vec3f
    /* 0x0288 */ f32 unk_288; // Set but not used
    /* 0x028C */ f32 unk_28C;
    /* 0x0290 */ u8 unk_290;
    /* 0x0294 */ f32 unk_294;
    /* 0x0298 */ f32 unk_298;
    /* 0x029C */ s16 leftFinYRot;
    /* 0x029E */ s16 rightFinYRot;
    /* 0x02A0 */ s16 unk_2A0; // body rot?
    /* 0x02A2 */ Vec3s unk_2A2;
    /* 0x02A8 */ s16 jawZRot;
    /* 0x02AC */ Vec3f unk_2AC; // used to grab player?
    /* 0x02B8 */ f32 unk_2B8;
    /* 0x02BC */ s8 unk_2BC;
    /* 0x02BD */ u8 unk_2BD;
    /* 0x02BE */ s16 unk_2BE;
    /* 0x02C0 */ UNK_TYPE1 unk_2C0[0x04];
    /* 0x02C0 */ f32 unk_2C4;
    /* 0x02C8 */ Vec3f unk_2C8; //set to player.world.pos
    /* 0x02D4 */ u8 unk_2D4;
    /* 0x02D5 */ u8 unk_2D5;
    /* 0x02D6 */ s16 unk_2D6; // used as target for this->actor.shape.rot.x
    /* 0x02D8 */ s16 unk_2D8; // used as target for this->actor.shape.rot.y
    /* 0x02DA */ s16 unk_2DA; // used as target for this->actor.shape.rot.z
    /* 0x02DC */ Vec3f unk_2DC[6]; // used by seaweed
    /* 0x0324 */ s16 unk_324; // timer? set by Tanron3
    /* 0x0328 */ Boss03ActionFunc actionFunc;
    /* 0x032C */ ColliderJntSph collider1;
    /* 0x034C */ ColliderJntSphElement colliderElements1[2];
    /* 0x03CC */ ColliderJntSph collider2;
    /* 0x03EC */ ColliderJntSphElement colliderElements2[5];
    /* 0x052C */ f32 unk_52C; // floppingAnimLastFrame?
    /* 0x0530 */ u32 unk_530;
    /* 0x0534 */ s16 unk_534;
    /* 0x0536 */ s16 subCamId;
    /* 0x0538 */ Vec3f unk_538;
    /* 0x0544 */ Vec3f unk_544;
    /* 0x0550 */ Vec3f unk_550;
    /* 0x055C */ Vec3f unk_55C;
    /* 0x0568 */ f32 unk_568;
    /* 0x056C */ f32 unk_56C;
    /* 0x0570 */ f32 unk_570; // set but not used
    /* 0x0574 */ UNK_TYPE1 unk_574[0x04];
    /* 0x0578 */ f32 cameraFov;
} Boss03; // size = 0x57C

extern const ActorInit Boss_03_InitVars;

#endif // Z_BOSS_03_H
