#include "z_en_niw.h"

#define FLAGS 0x00800010

void EnNiw_Init(Actor* thisx, GlobalContext* globalCtx);
void EnNiw_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnNiw_Update(Actor* thisx, GlobalContext* globalCtx);
void EnNiw_Draw(Actor* thisx, GlobalContext* globalCtx);

void EnNiw_SetupIdle(EnNiw* this);
void func_808919E8(EnNiw* this, GlobalContext* globalCtx);
void EnNiw_Thrown(EnNiw* this, GlobalContext* globalCtx);
void EnNiw_SetupRunning(EnNiw* this);
void func_808924B0(EnNiw* this, GlobalContext* globalCtx);
void EnNiw_Swimming(EnNiw* this, GlobalContext* globalCtx);

void EnNiw_Trigger(EnNiw* this, GlobalContext* globalCtx);
void EnNiw_Upset(EnNiw* this, GlobalContext* globalCtx);
void EnNiw_SetupCuccoStorm(EnNiw* this, GlobalContext* globalCtx);
void EnNiw_CuccoStorm(EnNiw* this, GlobalContext* globalCtx);
void EnNiw_SpawnAttackNiw(EnNiw* this, GlobalContext* globalCtx);

void EnNiw_Held(EnNiw* this, GlobalContext* globalCtx);
void EnNiw_UpdateFeather(EnNiw* this, GlobalContext* globalCtx);
void func_808932B0(EnNiw* this, GlobalContext* globalCtx); // draw feather

void EnNiw_CheckRage(EnNiw* this, GlobalContext* globalCtx);
void func_80891320(EnNiw* this, GlobalContext* globalCtx, s16 arg2);

s32 EnNiw_LimbDraw(GlobalContext *gCtx, s32 limbIndex, Gfx **dList, Vec3f *pos, Vec3s *rot, struct Actor *actor );
void EnNiw_SpawnFeather(EnNiw* this, Vec3f* pos, Vec3f* vel, Vec3f* accel, f32 scale);

extern s16 D_80893460;
//s16 D_80893460 = 0x0; 
//u16 D_80893462 = 0x0; // padding?

extern ActorInit En_Niw_InitVars;
//const ActorInit En_Niw_InitVars = {
    //ACTOR_EN_NIW,
    //ACTORCAT_PROP,
    //FLAGS,
    //OBJECT_NIW,
    //sizeof(EnNiw),
    //(ActorFunc)EnNiw_Init,
    //(ActorFunc)EnNiw_Destroy,
    //(ActorFunc)EnNiw_Update,
    //(ActorFunc)EnNiw_Draw,
//};

extern f32 D_80893484[];
//static f32 D_80893484[] = { 5000.0f, -5000.0f, 5000.0f, 3000.0f, 4000.0f,};

extern ColliderCylinderInit D_80893498;
//static ColliderCylinderInit sCylinderInit = {
    //{ 0x45, AT_NONE | AT_BOUNCED | AT_TYPE_PLAYER | AT_TYPE_ENEMY, AC_NONE | AC_NO_DAMAGE, OC1_NONE, OC2_FIRST_ONLY | OC2_UNK2 | OC2_HIT_PLAYER, 0x9C, },
    //{ 0x45, { 0x453B8000, 0x45, 0x7A }, { 0x0500093D, 0x20, 0x01 }, TOUCH_NONE | TOUCH_SFX_NORMAL, BUMP_NONE, OCELEM_NONE, },
    //{ 0, 0, 0, { 0, -2097, -1 } },
//};


extern Vec3f D_808934C4;
//static Vec3f D_808934C4 = { 90000.0f, 90000.0f, 90000.0f, };


extern InitChainEntry D_808934D0;
//static InitChainEntry sInitChain[] = {
    //ICHAIN_U8(targetMode, 6, ICHAIN_CONTINUE),
    //ICHAIN_F32_DIV1000(gravity, -2000, ICHAIN_CONTINUE),
    //ICHAIN_F32(targetArrowOffset, 0, ICHAIN_STOP),
//};

extern Vec3f D_808934DC;
//static Vec3f D_808934DC = { 90000.0f, 90000.0f, 90000.0f, };

extern u32 D_808934E8;
//static Vec3f D_808934E8 = { 90000.0f, 90000.0f, 90000.0f, };

// might be another vec3f with all zeros
//static s32 padding3[] = {0x00000000, 0x00000000, 0x00000000, };

void EnNiw_Init(Actor *thisx, GlobalContext *globalCtx) {
    EnNiw* this = (EnNiw*) thisx;
    Vec3f D_Temp = D_808934C4;

    if ( this->actor.params < 0) { // all neg values become zero
        this->actor.params = ENNIW_TYPE_REGULAR;
    }

    Math_Vec3f_Copy( &this->unk2BC, &D_Temp);

    this->niwType = this->actor.params;
    //Actor_ProcessInitChain(&this->actor, &sInitChain);
    Actor_ProcessInitChain(&this->actor, &D_808934D0);

    // ! @ BUG: I think this is supposed to be if (EnNiwType == value)
    //   but because all cuccos in the game are type 0xFFFF -> 0, it got optimized out
    // thats the only way this code makes sense:
    // if all cuccos are meant to be targetable it would be a default flag
    //   but one of the other types explicitly de-selects this flag anyway
    if (1) {
        this->actor.flags |= 0x1; // targetable ON
    }

    ActorShape_Init(&thisx->shape, 0.0f, func_800B3FC0, 25.0f);

    SkelAnime_InitSV(globalCtx, &this->skelanime,  &D_06002530, &D_060000E8,
         &this->limbDrawTbl, &this->transitionDrawtable, ENNIW_LIMBCOUNT);
    Math_Vec3f_Copy(&this->unk2A4, &this->actor.world.pos);
    Math_Vec3f_Copy(&this->unk2B0, &this->actor.world.pos);

    this->unk308 = 10.0f;
    Actor_SetScale(&this->actor, 0.01f);

    // size dependant on gamedata? beta plans to feed a cucco as a pet/quest?
    if (this->niwType == ENNIW_TYPE_UNK1) {
        Actor_SetScale(&this->actor, (gGameInfo->data[2486] / 10000.0f) + 0.004f);
    }

    // random health between 10-20
    this->actor.colChkInfo.health = Rand_ZeroFloat(9.99f) + 10.0f;
    this->actor.colChkInfo.mass = 0xFF;

    if (this->niwType == ENNIW_TYPE_REGULAR) {
        //Collider_InitAndSetCylinder(globalCtx, &this->collider, &this->actor, &sCylinderInit);
        Collider_InitAndSetCylinder(globalCtx, &this->collider, &this->actor, &D_80893498);
    }

    // never used in game, but maybe meant to be used with a cutscene or switching scenes?
    if (this->niwType == ENNIW_TYPE_UNK2) {
        Audio_PlayActorSound2(&this->actor, NA_SE_EV_CHICKEN_CRY_M); // crow
        this->sfxTimer1 = 30;
        this->unkTimer250 = 30;
        this->actor.flags &= ~0x1; // targetable OFF
        this->unknownState28E = 4;
        this->actionFunc = EnNiw_Held;
        this->actor.speedXZ = 0.0f;
        this->unk2BC.z = 0.0f;
        this->actor.velocity.y = 0.0f;
        this->actor.gravity = 0.0f;
    } else {
        EnNiw_SetupIdle(this);
    }
}

void EnNiw_Destroy(Actor *thisx, GlobalContext *globalCtx) {
    EnNiw* this = (EnNiw*) thisx;

    if (this->niwType == ENNIW_TYPE_REGULAR) {
        Collider_DestroyCylinder(globalCtx, &this->collider);
    }
}

void func_80891320(EnNiw *this, GlobalContext *globalCtx, s16 arg2) {
    f32 tempOne = 1.0f;

    if (this->unkTimer24C == 0) {
        if (arg2 == 0) {
            this->unk264[0] = 0.0f;
        } else {
            this->unk264[0] = (-10000.0f) * tempOne;
        }
        this->unk292 += 1;
        this->unkTimer24C = 3;
        if ((this->unk292 & 1) == 0) {
            this->unk264[0] = 0.0f;
            if (arg2 == 0) {
                this->unkTimer24C = Rand_ZeroFloat(30.0f);
            }
        }
    }
    if (this->unkTimer24E == 0) {
        this->unk296 += 1;
        this->unk296 &= 1;
        switch( arg2 ){
            case 0:
                this->unk264[2] = 0.0f;
                this->unk264[1] = 0.0f;
                break;
            case 1:
                this->unkTimer24E = 3;
                this->unk264[2] = 7000.0f * tempOne;
                this->unk264[1] = 7000.0f * tempOne;
                if (this->unk296 == 0) {
                    this->unk264[2] = 0.0f;
                    this->unk264[1] = 0.0f;
                }
                break;
            case 2:
                this->unkTimer24E = 2;
                this->unk264[2] = -10000.0f;
                this->unk264[1] = -10000.0f;
                this->unk264[7] = 25000.0f;
                this->unk264[5] = 25000.0f;
                this->unk264[8] = 6000.0f;
                this->unk264[6] = 6000.0f;
                if (this->unk296 == 0) {
                    this->unk264[7] = 8000.0f;
                    this->unk264[5] = 8000.0f;
                }
                break;
            case 3:
                this->unkTimer24E = 2;
                this->unk264[5] = 10000.0f;
                this->unk264[7] = 10000.0f;
                if (this->unk296 == 0) {
                    this->unk264[5] = 3000.0f;
                    this->unk264[7] = 3000.0f;
                }
                break;
            case 4:
                this->unkTimer24C = 5;
                break;
            case 5:
                this->unkTimer24E = 5;
                this->unk264[5] = 14000.0f;
                this->unk264[7] = 14000.0f;
                if (this->unk296 == 0) {
                    this->unk264[5] = 10000.0f;
                    this->unk264[7] = 10000.0f;
                }
                break;
            }
            
    }
    if (this->unk264[9] != this->limbFRot) {
        Math_ApproachF(&this->limbFRot, this->unk264[9], 0.5f, 4000.0f);
    }
    if (this->unk264[0] != this->limbDRot) {
        Math_ApproachF(&this->limbDRot, this->unk264[0], 0.5f, 4000.0f);
    }
    if (this->unk264[2] !=  this->limb7Rotz) {
        Math_ApproachF(&this->limb7Rotz, this->unk264[2], 0.8f, 7000.0f);
    }
    if (this->unk264[7] != this->limb7Roty) {
        Math_ApproachF(&this->limb7Roty, this->unk264[7], 0.8f, 7000.0f);
    }
    if (this->unk264[8] != this->limb7Rotx ) {
        Math_ApproachF(&this->limb7Rotx, this->unk264[8], 0.8f, 7000.0f);
    }
    if (this->unk264[1] != this->limbBRotz ) {
        Math_ApproachF(&this->limbBRotz, this->unk264[1], 0.8f, 7000.0f);
    }
    if (this->unk264[5] != this->limbBRoty ) {
        Math_ApproachF(&this->limbBRoty, this->unk264[5], 0.8f, 7000.0f);
    }
    if (this->unk264[6] != this->limbBRotx ) {
        Math_ApproachF(&this->limbBRotx, this->unk264[6], 0.8f, 7000.0f);
    }
}

void EnNiw_SpawnAttackNiw(EnNiw *this, GlobalContext *globalCtx) {
    f32 xView; // looks like Vec3f but couldn't get stack to allign
    f32 yView;
    f32 zView;
    Vec3f newNiwPos;
    Actor* attackNiw;

    if (this->unkTimer252 == 0) {
        if (this->unk290 < 7) {
            xView = globalCtx->view.focalPoint.x - globalCtx->view.eye.x;
            yView = globalCtx->view.focalPoint.y - globalCtx->view.eye.y;
            zView = globalCtx->view.focalPoint.z - globalCtx->view.eye.z;
            newNiwPos.x = ((Rand_ZeroOne() - 0.5f) * xView) + globalCtx->view.eye.x;
            newNiwPos.y = randPlusMinusPoint5Scaled(0.3f) 
                 + (globalCtx->view.eye.y + 50.0f + (yView * 0.5f));
            newNiwPos.z = ((Rand_ZeroOne() - 0.5f) * zView) + globalCtx->view.eye.z;
            attackNiw = Actor_SpawnWithParent(&globalCtx->actorCtx, &this->actor, globalCtx,
                  ACTOR_EN_ATTACK_NIW, newNiwPos.x, newNiwPos.y, newNiwPos.z, 0, 0, 0, 0);

            if (attackNiw) {
                this->unk290 += 1;
                this->unkTimer252 = 10;
            }
        }
    }
}

void func_808917F8(EnNiw *this, GlobalContext *globalCtx, s32 arg2) {
    f32 phi_f2;
    f32 targetRotY;
    f32* D_8089348CPtr = &D_80893484[2];

    if ( this->unkTimer250 == 0) {
        this->unkTimer250 = 3;
        if ((this->actor.bgCheckFlags & 1) ) {
            // hit floor
            this->actor.velocity.y = 3.5f; // hop up?
        }
    }
    if (this->unkTimer252 == 0) {
        this->unk29A++;
        this->unk29A &= 1;
        this->unkTimer252 = 5;
    }
    if (this->unk29A == 0) {
        phi_f2 = D_8089348CPtr[arg2];
    } else {
        phi_f2 = -D_8089348CPtr[arg2];
    }
    if (arg2 == 1) {
        if (( this->unkTimer254 == 0) || ((this->actor.bgCheckFlags & 8))) {
            this->unkTimer254 = 150;
            if (this->yawTimer == 0) {
                this->yawTimer = 70;
                this->yawTowardsPlayer = this->actor.yawTowardsPlayer;
            }
        }
    }
    targetRotY = this->yawTowardsPlayer + phi_f2;
    Math_SmoothStepToS(&this->actor.world.rot.y, targetRotY, 3, this->unk300, 0);
    Math_ApproachF(&this->unk300, 3000.0f, 1.0f, 500.0f);
    func_80891320(this, globalCtx, 5);
}

void EnNiw_SetupIdle(EnNiw *this) {
    SkelAnime_ChangeAnim(&this->skelanime, &D_060000E8, 1.0f, 0.0f,
         SkelAnime_GetFrameCount(&D_060000E8.common), 0, -10.0f);
    this->unknownState28E = 0;
    this->actionFunc = func_808919E8;
}

// EnNiw_Idle
#ifdef NON_MATCHING
// non-matching: stack offset and regalloc
void func_808919E8(EnNiw *this, GlobalContext *globalCtx) {
    //f32 posX;
    //f32 posY;
    //f32 posZ;
    s16 s16tmp;
    Vec3f newPos;
    
    newPos.y = randPlusMinusPoint5Scaled(100.0f);
    newPos.z = randPlusMinusPoint5Scaled(100.0f);
    if (this->niwType == ENNIW_TYPE_REGULAR) {
        if (Actor_HasParent( &this->actor, globalCtx)) {
            // picked up
            Audio_PlayActorSound2(&this->actor, NA_SE_EV_CHICKEN_CRY_M); // crow
            this->sfxTimer1 = 30;
            this->unkTimer250 = 30;
            this->actor.flags &= ~0x1; // targetable OFF
            this->unknownState28E = 4;
            this->actor.speedXZ = 0.0f;
            this->actionFunc = EnNiw_Held;
            return;
        } else {
            func_800B8BB0( &this->actor, globalCtx);
        }
    } else {
        this->unkTimer252 = 10;
    }

    s16tmp = 0;
    if (this->unkTimer252 != 0) {
        if (Rand_ZeroFloat(3.99000000954f) < 1.0f) {
            this->unk2EA++;
            this->unk2EA &= 1;
        }
        Math_ApproachF(&this->unk264[9], D_80893484[this->unk2EA], 0.5f, 4000.0f);
    }

    if ((this->unkTimer252 == 0) && (this->unkTimer250 == 0)) {
        this->unk298 += 1;

        if (this->unk298 >= 8) {
            this->unkTimer252 = Rand_ZeroFloat(30.0f);
            this->unk298 = Rand_ZeroFloat(3.99000000954f);
            // (3.99..) is loaded into f12 for rand_zero, but f12 never released
        // b18:    jal     Rand_ZeroFloat              b18:    jal     Rand_ZeroFloat                  
        // b1c:    lwc1    $f12,%lo(D_80893554)(at)  i b1c:    lwc1    $f12,%lo(.rodata+0x54)(at)
        // b20:    lwc1    $f12,0x34(sp)             r b20:    lwc1    $f2,0x2c(sp)

            if (newPos.y < 0.0f) {
                newPos.y -= 100.0f;
            } else {
                newPos.y += 100.0f;
            }
            if (newPos.z < 0.0f) {
                newPos.z -= 100.0f;
            } else {
                newPos.z += 100.0f;
            }

            this->unk2B0.x = this->unk2A4.x + newPos.y;
            this->unk2B0.z = this->unk2A4.z + newPos.z;

        } else {
            this->unkTimer250 = 4;
            if ((this->actor.bgCheckFlags & 1)) {
                this->actor.speedXZ = 0.0f;
                this->actor.velocity.y = 3.5f;
            }
        }
    }

    if (this->unkTimer250 != 0) {
        Math_ApproachZeroF(&this->unk264[9], 0.5f, 4000.0f);
        s16tmp = 1;
        Math_ApproachF(&this->actor.world.pos.x, this->unk2B0.x, 1.0f, this->unk300);
        Math_ApproachF(&this->actor.world.pos.z, this->unk2B0.z, 1.0f, this->unk300);
        Math_ApproachF(&this->unk300, 3.0f, 1.0f, 0.3f);

        newPos.x = this->unk2B0.x - this->actor.world.pos.x;
        newPos.z = this->unk2B0.z - this->actor.world.pos.z;

        if (fabsf(newPos.x) < 10.0f) {
            newPos.x = 0.0; 
        }
        if (fabsf(newPos.z) < 10.0f) {
            newPos.z = 0.0;
        }

        if ((newPos.x == 0.0f) && (newPos.z == 0.0f)) {
            this->unkTimer250 = 0;
            this->unk298 = 7;
        }

        Math_SmoothStepToS(&this->actor.world.rot.y, Math_Atan2S(newPos.x, newPos.z), 3, this->unk304, 0);
        Math_ApproachF(&this->unk304, 10000.0f, 1.0f, 1000.0f);
    }
    func_80891320(this, globalCtx, s16tmp);
}
#else
#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Niw_0x80891060/func_808919E8.asm")
#endif

void EnNiw_Held(EnNiw *this, GlobalContext *globalCtx) {
    Vec3f vec3fcopy;
    s16 rotZ;

    // again with the stupid double copy?
    vec3fcopy = D_808934DC;
    if (this->unkTimer250 == 0) {
        this->unk29E = 2;
        // cast req
        this->unkTimer250 = (s32) (Rand_ZeroFloat(1.0f) * 10.0f) + 10;
    }

    // casts req
    this->actor.shape.rot.x = ((s16) randPlusMinusPoint5Scaled(5000.0f)) + this->actor.world.rot.x;
    this->actor.shape.rot.y = ((s16) randPlusMinusPoint5Scaled(5000.0f)) + this->actor.world.rot.y;
    this->actor.shape.rot.z = ((s16) randPlusMinusPoint5Scaled(5000.0f)) + this->actor.world.rot.z;
    if (this->niwType == ENNIW_TYPE_REGULAR) {
        if (Actor_HasNoParent( &this->actor, globalCtx)) {
            this->actor.shape.rot.z = 0;
            rotZ = this->actor.shape.rot.z;
            this->unknownState28E = 5;
            this->actor.flags |= 0x1; // targetable ON
            this->actionFunc = EnNiw_Thrown;
            this->actor.shape.rot.y = rotZ;
            this->actor.shape.rot.x = rotZ;
        }
        
    // if not regular..? when does this go off?
    } else if (this->unk2BC.z != 0.0f) {
        this->actor.shape.rot.z = 0;
        rotZ = this->actor.shape.rot.z;
        this->actor.velocity.y = 8.0f;
        this->actor.speedXZ = 4.0f;
        this->actor.gravity = -2.0f;
        this->unknownState28E = 5;
        this->unk2EC = 0;
        this->niwType = ENNIW_TYPE_REGULAR;
        this->actor.shape.rot.y = rotZ;
        this->actor.shape.rot.x = rotZ;
        //Collider_InitAndSetCylinder(globalCtx, &this->collider, &this->actor,  &sCylinderInit );
        Collider_InitAndSetCylinder(globalCtx, &this->collider, &this->actor,  &D_80893498);
        Math_Vec3f_Copy(&this->unk2BC, &vec3fcopy);
        this->actor.flags |= 0x1; // targetable ON
        this->actionFunc = EnNiw_Thrown;
    }
    func_80891320(this, globalCtx, 2);
}

// action function: recently thrown, and also hopping on the floor
void EnNiw_Thrown(EnNiw *this, GlobalContext *globalCtx) {
    if (this->unk2EC == 0) {
        if ((this->actor.bgCheckFlags & 1)) { // about to hit the floor
            this->unk2EC = 1;
            this->unkTimer252 = 80; // hop timer
            this->actor.speedXZ = 0.0f;
            this->actor.velocity.y = 4.0f;
        } else{
            return; // wait until back on floor
        }
    } else {
        if ((this->actor.bgCheckFlags & 1)) { // about to hit the floor
            this->sfxTimer1 = 0;
            this->actor.velocity.y = 4.0f; // vertical hop
            this->unk29E = 1;
        }
        if (this->unkTimer252 == 0) {
            this->unkTimer254 = 100;
            this->unkTimer250 = 0;
            this->unk2EC = 0;
            EnNiw_SetupRunning(this);
            return;
        }
    }
    
    if (Actor_HasParent( &this->actor, globalCtx)) {
        // picked up again before could run off
        Audio_PlayActorSound2(&this->actor, NA_SE_EV_CHICKEN_CRY_M); // crow
        this->sfxTimer1 = 30;
        this->unk2EC = 0;
        this->unkTimer250 = 30;
        this->actor.flags &= ~0x1; // targetable OFF
        this->unknownState28E = 4;
        this->actionFunc = EnNiw_Held;
        this->actor.speedXZ = 0.0f;
    } else {
        if (this->unkTimer252 >= 6) {
            func_800B8BB0(&this->actor, globalCtx);
        }
        func_80891320(this, globalCtx, 2);
    }
}

// EnNiw_Swimming
// action func: swimming and flying away after swimming
void EnNiw_Swimming(EnNiw *this, GlobalContext *globalCtx) {
    Vec3f ripplePos;

    // even if hitting water, keep calling for reinforcements 
    if (this->niwStormActive) {
        EnNiw_SpawnAttackNiw(this, globalCtx); // spawn attack niw 
    }

    this->actor.speedXZ = 2.0f;
    if ((this->actor.bgCheckFlags & 0x20)) {
        // still touching water
        this->actor.gravity = 0.0f;
        if (this->actor.yDistToWater > 15.0f) {
            this->actor.world.pos.y = this->actor.world.pos.y + 2.0f;
        }
        if (this->unkTimer250 == 0) {
            this->unkTimer250 = 30;
            Math_Vec3f_Copy(&ripplePos, &this->actor.world.pos);
            ripplePos.y += this->actor.yDistToWater;
            
            EffectSsGRipple_Spawn( globalCtx, &ripplePos, 100, 500, 30);
        }
        if ((this->actor.bgCheckFlags & 8) != 0) {
            this->actor.velocity.y = 10.0f;
            this->actor.speedXZ = 1.0f;
        }
    } else {
        this->actor.gravity = -2.0f;
        if ((this->actor.bgCheckFlags & 8)) {
            // has hit a wall
            this->actor.velocity.y = 10.0f; // to the moon
            this->actor.speedXZ = 1.0f;
            this->actor.gravity = 0.0f;
        } else {
            this->actor.speedXZ = 4.0f;
        }

        if ((this->actor.bgCheckFlags & 1)) {
            // back on ground
            this->actor.gravity = -2.0f;
            this->unkTimer254 = 100;
            this->unkTimer250 = 0;
            this->actor.velocity.y = 0.0f;
            if ( ! this->niwStormActive) {
                EnNiw_SetupRunning(this);
            } else {
                this->unknownState28E = 3;
                this->actionFunc = EnNiw_CuccoStorm;
            }
        }
    }
    func_80891320(this, globalCtx, 2);
}

void EnNiw_Trigger(EnNiw *this, GlobalContext *globalCtx) {
    // ! @ BUG: I believe multiple values got optimized out
    // value has to be a temp to match (v0) but there is only one value
    // explained by there being code where value got assigned with multiple conditions
    // suspicious: in vanilla there is only one cucco variant (0xFFFF)
    s32 value;
    if (1) {
      value = 1;
    } 

    this->unkTimer252 = 10;
    this->unknownState28E = this->unk29C = value;
    this->actionFunc = EnNiw_Upset;
}

void EnNiw_Upset(EnNiw *this, GlobalContext *globalCtx) {

    this->sfxTimer1 = 100;
    if ( this->unkTimer252 == 0) {
        this->unkTimer252 = 60;
        this->unkTimer24C = 10;
        this->unk29C = 4;
        this->unknownState28E = 2;
        this->actionFunc = EnNiw_SetupCuccoStorm;
    }
  
    func_80891320(this, globalCtx, this->unk29C);
}

// the long crow with head back before they descend
void EnNiw_SetupCuccoStorm(EnNiw *this, GlobalContext *globalCtx) {
    f32 viewY;

    this->sfxTimer1 = 100;
    if (this->unkTimer252 == 40) {
        viewY = 14000.0f;
        this->unk264[0] = 10000.0f;
        this->unk264[7] = viewY;
        if (0) {}
        this->unk264[5] = viewY;
        this->unk264[6] = 0.0f;
        this->unk264[8] = 0.0f;
        this->unk264[1] = 0.0f;
        this->unk264[2] = 0.0f;
        this->unkTimer24C = 10;
        Audio_PlayActorSound2(&this->actor, NA_SE_EV_CHICKEN_CRY_M); // crow
    }
    if (this->unkTimer252 == 0) {
        this->unkTimer252 = 10;
        this->yawTowardsPlayer = this->actor.yawTowardsPlayer;
        this->actor.flags &= ~0x1; // targetable OFF
        this->unknownState28E = 3;
        this->actionFunc = EnNiw_CuccoStorm;
    }
    func_80891320(this, globalCtx, this->unk29C);
}

void EnNiw_CuccoStorm(EnNiw *this, GlobalContext *globalCtx) {
    f32 randFloat;

    EnNiw_SpawnAttackNiw(this, globalCtx);
    if (this->unkTimer252 == 1) {
        this->actor.speedXZ = 3.0f;
        randFloat = Rand_ZeroFloat(1.99f);
        this->unkTimer250 = 0;
        this->unkTimer24E = this->unkTimer250;
        this->unkTimer24C = this->unkTimer250;
        this->unk29A = randFloat;
    } else {
        func_808917F8(this, globalCtx, 1);
    }
}

void EnNiw_SetupRunning(EnNiw *this) {
    SkelAnime_ChangeAnim(&this->skelanime, &D_060000E8, 1.0f, 0.0f, 
          SkelAnime_GetFrameCount(&D_060000E8.common), 0, -10.0f);
    this->unk29A = Rand_ZeroFloat(1.99f);
    this->unknownState28E = 7;
    this->actionFunc = func_808924B0; // running away
    this->actor.speedXZ = 4.0f;
}

#ifdef NON_MATCHING
// bad regalloc, center of first if block
// actionfunc: running away from link
void func_808924B0(EnNiw *this, GlobalContext *globalCtx) {
    ActorPlayer* player = PLAYER;
    Vec3f tempVec3f;
    s16 temp298;
    f32 dX;
    f32 dZ;

    // it actually wants to copy to stack... not modify, then pass to veccopy
    // and it does it BEFORE the if block, this is just unoptimized.
    tempVec3f = D_808934E8;
    if (this->unkTimer254 == 0) {
        // the assignements in this block never want to align properly
        // its not lineswap, as 800k permuter with only lineswap didn't find a solution
        this->unk298 = 0;

        this->unk2A4.x = this->actor.world.pos.x;
        this->unk2A4.y = this->actor.world.pos.y;
        this->unk2A4.z = this->actor.world.pos.z;
        this->unk2B0.x = this->actor.world.pos.x;
        this->unk2B0.y = this->actor.world.pos.y;
        this->unk2B0.z = this->actor.world.pos.z;

        this->unkTimer252 = this->unkTimer250 = this->unk298 ;
        this->unk264[8] = 0;
        this->unk264[6] = 0;
        this->unk264[5] = 0;
        this->unk264[7] = 0;
        this->unk304 = 0;
        this->unk300 = 0;
        this->actor.speedXZ = 0;
        Math_Vec3f_Copy(&this->unk2BC, &tempVec3f);
        EnNiw_SetupIdle(&this->actor); // stop running
    } else {
        if ( this->unk2BC.x != 90000.0f) {
            dX = this->actor.world.pos.x - this->unk2BC.x;
            dZ = this->actor.world.pos.z - this->unk2BC.z;
        } else {
            dX = this->actor.world.pos.x - player->base.world.pos.x;
            dZ = this->actor.world.pos.z - player->base.world.pos.z;
        }
        this->yawTowardsPlayer = Math_Atan2S(dX, dZ);
        func_808917F8(this, globalCtx, 0);
        func_80891320(this, globalCtx, 2);
    }
}
#else 
#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Niw_0x80891060/func_808924B0.asm")
#endif

// check if on the ground after running, once on the ground, start idling
void EnNiw_LandBeforeIdle(EnNiw *this, GlobalContext* gCtx) {
    if ((this->actor.bgCheckFlags & 1)) { // hit floor
        EnNiw_SetupIdle(this);
    }
}

void EnNiw_CheckRage(EnNiw *this, GlobalContext *globalCtx) {
    if ((!this->niwStormActive) && (this->unkTimer260 == 0) && (this->niwType == ENNIW_TYPE_REGULAR)) {
        if (( this->unknownState28E != 7) && (90000.0f != this->unk2BC.x)) {
            this->unkTimer260 = 10;
            this->sfxTimer1 = 30;
            this->unk29E = 1;
            Audio_PlayActorSound2(&this->actor, NA_SE_EV_CHICKEN_CRY_M); // crow
            this->unkTimer254 = 100;
            this->unk2EC = 0;
            EnNiw_SetupRunning(this);
        }
        
        if ((this->collider.base.acFlags & AC_HIT)) {
            this->collider.base.acFlags &= ~AC_HIT; 
            // health gets used as a hit counter until cucco storm
            if (this->actor.colChkInfo.health > 0) {
                this->actor.colChkInfo.health--;
            }
            
            if ((D_80893460 == 0) && (this->actor.colChkInfo.health == 0)) {
                // now you've done it
                this->unkTimer254 = 100;
                D_80893460 = 1;
                this->unk298 = 0;
                this->sfxTimer1 = 10000;
                this->unk2A4.x = this->unk2B0.x = this->actor.world.pos.x;
                this->unk2A4.y = this->unk2B0.y = this->actor.world.pos.y;
                this->unk2A4.z = this->unk2B0.z = this->actor.world.pos.z;
                this->unkTimer252 = this->unkTimer250 = this->unk298;
                  
                this->unk264[8] = 0.0f;
                this->unk264[6] = 0.0f;
                this->unk264[5] = 0.0f;
                this->unk264[7] = 0.0f;
                this->niwStormActive = true;
                this->actionFunc = EnNiw_Trigger;
                this->unk304 = 0.0f;
                this->unk300 = 0.0f;
                this->actor.speedXZ = 0.0f;

            } else {
                this->unkTimer260 = 10;
                this->sfxTimer1 = 30;
                this->unk29E = 1;
                Audio_PlayActorSound2(&this->actor, NA_SE_EV_CHICKEN_CRY_M); // crow
                this->unkTimer254 = 100;
                this->unk2EC = 0;
                EnNiw_SetupRunning(this);
            }
        }
    }
}

void EnNiw_Update(Actor* thisx, GlobalContext* globalCtx) {
    EnNiw* this = (EnNiw*) thisx;
    s8 pad0;
    s16 i;
    ActorPlayer *player = PLAYER;
    s16 pad1;
    s16 featherCount;
    Vec3f pos;
    Vec3f spB8;
    Vec3f spAC;
    s32 pad2[9];
    s16 temp29C;
    f32 featherScale;
    f32 camResult;
    f32 floorHeight;
    f32 dist = 20.0f;
    s32 pad3;

    this->unusedCounter28C++; // incremented here, reset to zero in one other place

    if (this->niwType == ENNIW_TYPE_UNK1) {
        this->actor.shape.rot.y = this->actor.world.rot.y = this->actor.parent->shape.rot.y;
    }

    if (this->unknownState28E != 0) {
        this->unk264[9] = 0.0f;
    }

    if (this->unk29E != 0) {
        featherCount = 20;
        if (this->unk29E == 2) {
            featherCount = 4;
        }
        for(i = 0; i < featherCount; ++i) {
            pos.x = randPlusMinusPoint5Scaled(10.0f) + this->actor.world.pos.x;
            pos.y = randPlusMinusPoint5Scaled(10.0f) + (this->actor.world.pos.y + this->unk308);
            pos.z = randPlusMinusPoint5Scaled(10.0f) + this->actor.world.pos.z;
            featherScale = Rand_ZeroFloat(6.0f) + 6.0f;

            if ((this->unk29E == 2) && (this->unk308 != 0)) {
                pos.y += 10.0f;
            }

            if (this->unk308 == 0) {
                featherScale = Rand_ZeroFloat(2.0f) + 2.0f;
            }
            spB8.x = randPlusMinusPoint5Scaled(3.0f);
            spB8.y = (Rand_ZeroFloat(2.0f) * 0.5f) + 2.0f;
            spB8.z = randPlusMinusPoint5Scaled(3.0f);
            spAC.z = spAC.x = 0.0f;
            spAC.y = -0.15000000596f;

            EnNiw_SpawnFeather(this, &pos, &spB8, &spAC, featherScale); //spawn feather
        }
        this->unk29E = 0;
    }
  
    EnNiw_UpdateFeather(this, globalCtx);

    DECR(this->unkTimer24C);
    DECR(this->unkTimer24E);
    DECR(this->unkTimer250);
    DECR(this->unkTimer252);
    DECR(this->unkTimer254);
    DECR(this->sfxTimer1);
    DECR(this->flutterSfxTimer);
    DECR(this->unusedTimer25A);
    DECR(this->yawTimer);
    DECR(this->unusedTimer25E);
    DECR(this->unkTimer260);

    this->actor.shape.rot = this->actor.world.rot;
    this->actor.shape.shadowScale = 15.0f;
    this->actionFunc(this, globalCtx);
    Actor_SetHeight(&this->actor, this->unk308);
    Actor_SetVelocityAndMoveYRotationAndGravity(&this->actor);

    func_800B78B8(globalCtx, &this->actor, 20.0f, 20.0f, 60.0f, 0x1F); //update bgcheckinfo
    
    // if cucco is off the map?
    if ( (this->actor.floorHeight <= BGCHECK_Y_MIN) || (this->actor.floorHeight >= 32000.0f)) {
        Vec3f camera;
        camera.x = globalCtx->view.focalPoint.x - globalCtx->view.eye.x;
        camera.y = globalCtx->view.focalPoint.y - globalCtx->view.eye.y;
        camera.z = globalCtx->view.focalPoint.z - globalCtx->view.eye.z;
        camResult = camera.y / sqrtf(SQXYZ(camera));

        this->actor.world.pos.x = this->actor.home.pos.x;
        this->actor.world.pos.z = this->actor.home.pos.z;
        this->actor.world.pos.y = (this->actor.home.pos.y + globalCtx->view.eye.y ) + (camResult * 160.0f);
      
        if (this->actor.world.pos.y < this->actor.home.pos.y) {
            this->actor.world.pos.y = this->actor.home.pos.y + 300.0f;
        }

        this->actor.speedXZ = 0.0f;
        this->actor.gravity = -2.0f;
        Math_Vec3f_Copy(&this->unk2A4, &this->actor.home.pos);
        Math_Vec3f_Copy(&this->unk2B0, &this->actor.home.pos);

        this->unk304 = 0.0f;
        this->unk300 = 0.0f;
        this->unusedFloat2FC = 0.0f;
        this->unusedFloat2F8 = 0.0f;
        this->unusedFloat2F4 = 0.0f;
        this->limbBRotx = 0.0f;
        this->limbBRoty = 0.0f;
        this->limbBRotz = 0.0f;
        this->limb7Rotx = 0.0f;
        this->limb7Roty = 0.0f;
        this->limb7Rotz = 0.0f;
        this->limbDRot = 0.0f;
        this->limbFRot = 0.0f;

        // clang-format off
        this->niwStormActive = this->unusedCounter28C = this->unk292 = this->unk29E = this->unk298 = this->unk29A = this->unk29C = 0; 
        // clang-format on

        for( i = 0; i < 0xA; ++i) {
            this->unk264[i] = 0.0f;
        }

        this->unknownState28E = 8;
        this->niwStormActive = false;
        this->actionFunc = EnNiw_LandBeforeIdle;
        return; // still required even with the else/else

    } else if (((this->actor.bgCheckFlags & 0x20)) && (this->actor.yDistToWater > 15.0f) && (this->unknownState28E != 6)) {
        this->actor.velocity.y = 0.0f;
        this->actor.gravity = 0.0f;
        Math_Vec3f_Copy(&pos, &this->actor.world.pos);
        pos.y += this->actor.yDistToWater;
        this->unkTimer250 = 30;
        EffectSsGSplash_Spawn(globalCtx, &pos, 0, 0, 0, 400);
        this->unkTimer252 = 0;
        this->unknownState28E = 6;
        this->actionFunc = EnNiw_Swimming;

    } else {
  
        // player->invincibilityTimer
        if ((this->niwStormActive) && (this->actor.xyzDistToPlayerSq < (SQ(dist))) && (player->unkD5C == 0)) {
            func_800B8D50(globalCtx, &this->actor, 2.0f, this->actor.world.rot.y, 0.0f, 0x10);
        }

        EnNiw_CheckRage(this, globalCtx);
        if ((this->flutterSfxTimer == 0) && (this->unknownState28E == 4)) {
            this->flutterSfxTimer = 7;
            Audio_PlayActorSound2(&this->actor, NA_SE_EN_CHICKEN_FLUTTER);
        }

        if (this->sfxTimer1 == 0) {
            if (this->unknownState28E != 0) {
                this->sfxTimer1 = 30;
                Audio_PlayActorSound2(&this->actor, NA_SE_EV_CHICKEN_CRY_A); // attack cluck 
            } else {
                this->sfxTimer1 = 300;
                Audio_PlayActorSound2(&this->actor, NA_SE_EV_CHICKEN_CRY_N); // cluck 
            }
        }

        if (!this->niwStormActive) {
            if (this->niwType == ENNIW_TYPE_REGULAR) {
                Collider_UpdateCylinder(&this->actor, &this->collider);
                CollisionCheck_SetAC(globalCtx, &globalCtx->colCheckCtx, &this->collider.base);
                
                if (globalCtx){} // req to match

                if ((this->unknownState28E != 4) && (this->unknownState28E != 5)) {
                    CollisionCheck_SetOC(globalCtx, &globalCtx->colCheckCtx,  &this->collider.base);
                }
            }
        }
    }
}

s32 EnNiw_LimbDraw(GlobalContext *gCtx, s32 limbIndex, Gfx **dList, Vec3f *pos, Vec3s *rot, struct Actor *actor) {
    EnNiw* this = (EnNiw*) actor;

    // float to s16 casts req
    if (limbIndex == 0xD) {
        rot->y += (s16) this->limbDRot;
    }
    if (limbIndex == 0xF) {
        rot->y += (s16) this->limbFRot;
    }
    if (limbIndex == 0xB) {
        rot->x += (s16) this->limbBRotx;
        rot->y += (s16) this->limbBRoty;
        rot->z += (s16) this->limbBRotz;
    }
    if (limbIndex == 0x7) {
        rot->x += (s16) this->limb7Rotx;
        rot->y += (s16) this->limb7Roty;
        rot->z += (s16) this->limb7Rotz;
    }
    return 0; 
}

void EnNiw_Draw(Actor *thisx, GlobalContext *globalCtx) {
    EnNiw* this = (EnNiw*) thisx;

    func_8012C28C(globalCtx->state.gfxCtx);
    SkelAnime_DrawSV(globalCtx, this->skelanime.skeleton, this->skelanime.limbDrawTbl,
         this->skelanime.dListCount, EnNiw_LimbDraw, NULL, &this->actor);
    func_808932B0(this, globalCtx);
}

// EnNiw_SpawnFeather ?
void EnNiw_SpawnFeather(EnNiw *this, Vec3f *pos, Vec3f *vel, Vec3f *accel, f32 scale) {
    s16 i;
    EnNiwFeather* feather = this->feathers;

    for (i = 0; i < ARRAY_COUNT(this->feathers); i++, feather++) {
        if (feather->enabled == false) {
            feather->enabled = true;
            feather->pos = *pos;
            feather->vel = *vel;
            feather->accel = *accel;
            feather->timer = 0;
            feather->scale = scale / 1000.0f;
            feather->life = Rand_ZeroFloat(20.0f) + 40.0f;
            feather->zRotStart = Rand_ZeroFloat(1000.0f);
            break;
        }
    }
}

// EnNiw_FeatherUpdate
void EnNiw_UpdateFeather(EnNiw *this, GlobalContext *globalCtx) {
    EnNiwFeather *feather = this->feathers;
    f32 featherVelocityGoal = 0.05f;
    s16 i;

    for (i = 0; i < ARRAY_COUNT(this->feathers); i++, feather++) {
        if (feather->enabled) {
            feather->timer++;
            feather->pos.x += feather->vel.x;
            feather->pos.y += feather->vel.y;
            feather->pos.z += feather->vel.z;
            feather->vel.x += feather->accel.x;
            feather->vel.y += feather->accel.y;
            feather->vel.z += feather->accel.z;
            if (feather->enabled == true) {
                feather->zRotStart++;
                Math_ApproachF(&feather->vel.x, 0.0f, 1.0f, featherVelocityGoal);
                Math_ApproachF(&feather->vel.z, 0.0f, 1.0f, featherVelocityGoal);
                if (feather->vel.y < -0.5f) {
                    feather->vel.y = -0.5f;
                }

                feather->zRot = Math_SinS(feather->zRotStart * 0xBB8) * M_PI * 0.2f;

                if (feather->life < feather->timer) {
                    feather->enabled = false;
                }
            }
        }
    }
}

// feather draw function
#ifdef NON_EQUIVELENT
// this isnt even close
void func_808932B0(EnNiw *this, GlobalContext *globalCtx) {
    
    //EnNiwFeather *temp_s1;
    EnNiwFeather *feather = &this->feathers;
    //f32 temp_f12;
    //z_Matrix *temp_s0;
    u8 flag = 0;
    s16 i;
    //GraphicsContext *gfxCtx = globalCtx->state.gfxCtx;

    OPEN_DISPS(globalCtx->state.gfxCtx);

    //func_8012C2DC(gfxCtx);
    func_8012C2DC(globalCtx->state.gfxCtx);

    //feather = temp_s1;
    //flag = 0;
    //i = (u16)0;
//loop_1:
    //if ((s32) temp_s3 < 0x14) {
        //goto loop_1;
    for(i = 0; i < 10; i++, feather++) {
        if (feather->enabled) {
            //temp_s0 = &globalCtx->unk187FC;
            if (flag == 0) {
                //temp_v0 = gfxCtx->polyXlu.p;
                //gfxCtx->polyXlu.p = temp_v0 + 8;
                //temp_v0->words.w1 = 0x60023B0;
                //temp_v0->words.w0 = 0xDE000000;
                //gSPDisplayList(POLY_XLU_DISP++, 0x60023B0);
                gSPDisplayList(POLY_XLU_DISP++, &D_060023B0);

                flag++;// = (flag + 1) & 0xFF;
            }
            SysMatrix_InsertTranslation(feather->pos.x, feather->pos.y, feather->pos.z, 0); // MTXMODE_NEW?
            SysMatrix_NormalizeXYZ(&globalCtx->unk187FC);
            //temp_f12 = feather->scale;
            //SysMatrix_InsertScale(temp_f12, temp_f12, 1.0f, 1);
            SysMatrix_InsertScale(feather->scale, feather->scale, 1.0f, 1);
            SysMatrix_InsertZRotation_f(feather->zRot, 1);
            SysMatrix_InsertTranslation(0.0f, -1000.0f, 0.0f, 1);

            //temp_v0_2 = gfxCtx->polyXlu.p;
            //gfxCtx->polyXlu.p = temp_v0_2 + 8;
            //temp_v0_2->words.w0 = 0xDA380003;
            //temp_v0_2->words.w1 = SysMatrix_AppendStateToPolyOpaDisp(gfxCtx);
            gSPMatrix(POLY_XLU_DISP++, SysMatrix_AppendStateToPolyOpaDisp(globalCtx->state.gfxCtx),
            //gSPMatrix(POLY_XLU_DISP++, SysMatrix_AppendStateToPolyOpaDisp(globalCtx->state.gfxCtx),
                 G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);

            //temp_v0_3 = gfxCtx->polyXlu.p;
            //gfxCtx->polyXlu.p = temp_v0_3 + 8;
            //temp_v0_3->words.w1 = 0x6002428;
            //temp_v0_3->words.w0 = 0xDE000000;
            gSPDisplayList(POLY_XLU_DISP++, &D_06002428);

        }
    }
    CLOSE_DISPS(globalCtx->state.gfxCtx);
}
#else
#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Niw_0x80891060/func_808932B0.asm")
#endif
