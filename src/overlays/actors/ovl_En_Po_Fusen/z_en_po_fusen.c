#include "z_en_po_fusen.h"
#include "../ovl_En_Ma4/z_en_ma4.h"

#define FLAGS 0x80100030

#define THIS ((EnPoFusen*)thisx)

void EnPoFusen_Init(Actor* thisx, GlobalContext* globalCtx);
void EnPoFusen_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnPoFusen_Update(Actor* thisx, GlobalContext* globalCtx);
void EnPoFusen_Draw(Actor* thisx, GlobalContext* globalCtx);

u16 EnPoFusen_CheckParent(EnPoFusen* this, GlobalContext* globalCtx);
void EnPoFusen_InitNoFuse(EnPoFusen* this);
void EnPoFusen_InitFuse(EnPoFusen *this);
void EnPoFusen_Pop(EnPoFusen *this, GlobalContext *gCtx);
void func_80AC158C(EnPoFusen* this, GlobalContext* gCtx);
void EnPoFusen_IdleFuse(EnPoFusen* this, GlobalContext* gCtx);
s32  EnPoFusen_OverrideLimbDraw(GlobalContext* gCtx, s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3s* rot, struct Actor* actor);

const ActorInit En_Po_Fusen_InitVars = {
    ACTOR_EN_PO_FUSEN,
    ACTORCAT_PROP,
    FLAGS,
    OBJECT_PO_FUSEN,
    sizeof(EnPoFusen),
    (ActorFunc)EnPoFusen_Init,
    (ActorFunc)EnPoFusen_Destroy,
    (ActorFunc)EnPoFusen_Update,
    (ActorFunc)EnPoFusen_Draw
};

u32 EnPoFusenSphereInit[] = { //ColSphereInit  
    0x0A000939, 0x12040000, 0x00000000, 0xF7CFFFFF,
    0x00000000, 0xF7CFFFFF, 0x00000000, 0x00010100,
    0x00000000, 0x00000000, 0x00C80064, };

DamageTable EnPoFusenDamageTable = { 
    0x00, 0x00, 0x00, 0x00, 0x00, 0xF1, 0x00, 0x00, 0x00, 0x00, 0x00, 0xF1, 0xF1, 0xF1, 0xF1, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
};

void EnPoFusen_Init(Actor *thisx, GlobalContext *globalCtx) {
    EnPoFusen* this = THIS;
    f32 heightTemp;

    this->actor.scale.x = this->actor.scale.y = this->actor.scale.z = 0.00700000021607;
    this->actor.targetMode = 6;
    this->actor.colChkInfo.damageTable = &EnPoFusenDamageTable;

    Collision_InitSphereDefault(globalCtx, &this->collider);
    Collision_InitSphereWithData(globalCtx, &this->collider, &this->actor, &EnPoFusenSphereInit);
    if (0){}
    this->collider.params.colInfo.radius  = 40;
    SkelAnime_InitSV(globalCtx, &this->anime, &D_060024F0, &D_06000040,
        &this->limbDrawTbl, &this->transitionDrawTbl, 10);
    Actor_SetDrawParams(&this->actor.shape, 0.0f, func_800B3FC0, 25.0f);
    func_800B78B8(globalCtx, this, 0.0f, 0.0f, 0.0f, 4);
    if (EnPoFusen_CheckParent(this, globalCtx) == 0) {
        Actor_MarkForDeath(&this->actor);
    }

    heightTemp = this->actor.floorHeight + 90.0f;
    if (this->actor.home.pos.y < heightTemp) {
        this->actor.home.pos.y = heightTemp;
    }

    this->randScaleChange = ((rand() % 0xFFFEU) - 0x7FFF);
    this->randYRotChange = ((rand() % 0x4B0U) - 0x258);
    this->avgBaseRotation = 0x1555;
    this->limb3Rot = 0;
    this->limb46Rot = 0;
    this->limb57Rot = 0;
    this->limb8Rot = 0;
    this->limb9Rot = 0x71C;
    this->randBaseRotChange = 0;
    if (GET_IS_FUSE_TYPE_PARAM(this)) {
        EnPoFusen_InitFuse(this);
        return;
    }
    EnPoFusen_InitNoFuse(this);
}

void EnPoFusen_Destroy(Actor* thisx, GlobalContext *gCtx) {
    EnPoFusen* this = THIS;
    Collision_FiniSphere(gCtx, &this->collider);
}

u16 EnPoFusen_CheckParent(EnPoFusen *this, GlobalContext *globalCtx) {
    struct Actor *actorPtr;

    actorPtr = globalCtx->actorCtx.actorList[4].first;
    if (GET_IS_FUSE_TYPE_PARAM(this)) {
        return 1;
    }
    if (actorPtr != 0) {
        do{
            if (actorPtr->id == ACTOR_EN_MA4) {
                this->actor.parent = actorPtr;
                return 1;
            }
            actorPtr = actorPtr->next;
        } while (actorPtr != 0);
    }
    return 0;
}

u16 EnPoFusen_CheckCollision(EnPoFusen *this, GlobalContext *gCtx) {
    
    if ((u32) this->actionFunc == (u32) EnPoFusen_IdleFuse ) {
      return 0;
    }

    this->collider.params.colInfo.loc.x = this->actor.world.pos.x;
    this->collider.params.colInfo.loc.y = (this->actor.world.pos.y + 20.0f);
    this->collider.params.colInfo.loc.z = this->actor.world.pos.z;
    if (((this->collider.base.flagsAC & 2) != 0) 
      && (this->actor.colChkInfo.damageEffect == 0xF)) {
        this->collider.base.flagsAC &= ~0x2;
        return 1;
    }
    Collision_AddOT(gCtx, &gCtx->colCheckCtx, &this->collider);
    Collision_AddAC(gCtx, &gCtx->colCheckCtx, &this->collider);
    return 0;
}

void EnPoFusen_InitNoFuse(EnPoFusen *this) {
    this->actor.shape.rot.z = 0;
    this->actionFunc = func_80AC158C;
}

void func_80AC158C(EnPoFusen *this, GlobalContext *gCtx) {
    f32 shadowScaleTmp;
    f32 shadowAlphaTmp;
    f32 heightOffset;
    f32 f255 = 255.0f;

    this->actor.world.pos = this->actor.home.pos;
    this->randScaleChange += 0x190;
    this->randXZRotChange += 0x5DC;
    this->randBaseRotChange += 0x9C4;
    heightOffset = Math_Sins(this->randScaleChange);
    heightOffset = 50.0f * heightOffset;
    this->actor.shape.rot.y += this->randYRotChange;
    this->actor.world.pos.y += heightOffset;
    this->actor.shape.rot.z =  (Math_Sins(this->randBaseRotChange) * 910.0f);
    if ((this->randScaleChange < 0x4000) && (this->randScaleChange >= -0x3FFF)) {
        Math_SmoothScaleMaxMinS( &this->limb9Rot, 0x38E, 0x14, 0xBB8, 0x64);
    } else {
        Math_SmoothScaleMaxMinS( &this->limb9Rot, 0x71C, 0x8, 0xBB8, 0x64);
    }
    this->avgBaseRotation = this->limb9Rot * 3;
    this->limb3Rot  = (Math_Sins(this->randBaseRotChange + 0x38E3) * this->avgBaseRotation);
    this->limb46Rot = (Math_Sins(this->randBaseRotChange)          * this->avgBaseRotation);
    this->limb57Rot = (Math_Sins(this->randBaseRotChange - 0x38E3) * this->avgBaseRotation);
    this->limb8Rot  = (Math_Sins(this->randBaseRotChange - 0x71C6) * this->avgBaseRotation);

    shadowScaleTmp = ((1.0f - Math_Sins(this->randScaleChange)) * 10.0f) + 50.0f;
    shadowAlphaTmp = ((1.0f - Math_Sins(this->randScaleChange)) * 75.0f) + 100.0f;
    this->actor.shape.shadowScale = shadowScaleTmp;
    this->actor.shape.shadowAlpha = (shadowAlphaTmp > f255) ? (u8) f255 : (u8) shadowAlphaTmp;
}

void EnPoFusen_IncrementMalonPop(EnPoFusen *this) {
    Actor* parent = this->actor.parent;
    EnMa4* romani;

    if ((parent != 0) && (parent->id == ACTOR_EN_MA4)) { 
        romani = (EnMa4*) parent;
        romani->unk338 += 1;
    }

    this->actor.draw = NULL;
    this->actionFunc = EnPoFusen_Pop;
}

void EnPoFusen_Pop(EnPoFusen *this, GlobalContext *gCtx) {
    Actor_Spawn(&gCtx->actorCtx, gCtx, ACTOR_EN_CLEAR_TAG,
       this->actor.world.pos.x, this->actor.world.pos.y + 20.0f, this->actor.world.pos.z, 
       255, 255, 200, 2);
    func_800B8EC8(&this->actor, 0x180E); // NA_SE_IT_BOMB_EXPLOSION sfx
    Actor_MarkForDeath(&this->actor);
}

void EnPoFusen_InitFuse(EnPoFusen *this) {
    s16 rotZ = this->actor.shape.rot.z;
    this->fuse = GET_FUSE_LEN_PARAM(this);
    this->actor.shape.rot.z = 0;
    this->randScaleChange = rotZ & 0xFFFFu;
    this->actionFunc = EnPoFusen_IdleFuse;
}

void EnPoFusen_IdleFuse(EnPoFusen *this, GlobalContext *gCtx) {

    func_80AC158C(this, gCtx);
    if ((this->fuse--) == 0) {
        EnPoFusen_IncrementMalonPop(this);
    }
}

void EnPoFusen_Update(Actor *thisx, GlobalContext *globalCtx) {
    EnPoFusen* this = THIS;
    this->actionFunc(this, globalCtx);
    if (EnPoFusen_CheckCollision(this, globalCtx) != 0) {
        EnPoFusen_IncrementMalonPop(this);
    }
}

s32 EnPoFusen_OverrideLimbDraw(GlobalContext *gCtx, s32 limbIndex, Gfx **dList, Vec3f *pos, Vec3s *rot, struct Actor *actor) {
    EnPoFusen* this = (EnPoFusen*)actor;
    f32 zScale;
    f32 yScale;
    f32 xScale;
    s16 pad;
    s16 zRot;
    s16 pad2;
    s16 xRot;

    if (limbIndex == 2) {
        zScale = (Math_Coss(this->randScaleChange) * 0.0799999982119f) + 1.0f;
        xScale = zScale;
        if (!zScale) { }
        yScale = (Math_Sins(this->randScaleChange) * 0.0799999982119f) + 1.0f;
        yScale = yScale * yScale;
        xRot = ((Math_Sins(this->randXZRotChange) * 2730.0f));
        zRot = ((Math_Coss(this->randXZRotChange) * 2730.0f));
        SysMatrix_InsertRotation(xRot, 0, zRot , 1);
        SysMatrix_InsertScale(xScale, yScale , zScale, 1);
        SysMatrix_InsertZRotation_s( -zRot, 1);
        SysMatrix_InsertXRotation_s( -xRot, 1);
    } else if (limbIndex == 3) {
        rot->y += this->limb3Rot;
    } else if (limbIndex == 6) {
        rot->y += this->limb46Rot;
    } else if (limbIndex == 4) {
        rot->z += this->limb46Rot;
    } else if ((limbIndex == 5) || (limbIndex == 7)) {
        rot->z += this->limb57Rot;
    } else if (limbIndex == 8) {
        rot->z += this->limb8Rot;
    } else if (limbIndex == 9) {
        rot->y += (s16) (this->limb9Rot * Math_Sins(this->randBaseRotChange));
        rot->z += (s16) (this->limb9Rot * Math_Coss(this->randBaseRotChange));
    }
    return 0;
}

void EnPoFusen_PostLimbDraw(s32 arg0, s32 arg1, s32 arg2, s32 arg3) { }

void EnPoFusen_UnkActorDraw(s32 arg0, s32 arg1, s32 arg2) { }

void EnPoFusen_Draw(Actor *thisx, GlobalContext *globalCtx) {
    EnPoFusen* this = THIS;
    func_8012C28C(globalCtx->state.gfxCtx);
    func_801343C0(globalCtx, this->anime.skeleton,
       this->anime.limbDrawTbl, this->anime.dListCount, 
       EnPoFusen_OverrideLimbDraw, EnPoFusen_PostLimbDraw, EnPoFusen_UnkActorDraw, &this->actor);
}
