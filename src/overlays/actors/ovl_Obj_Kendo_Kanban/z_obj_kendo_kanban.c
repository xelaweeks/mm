/*
 * File: z_obj_kendo_kanban.c
 * Overlay: ovl_Obj_Kendo_Kanban
 * Description: Swordsman's School - Cuttable Board
 */

#include "z_obj_kendo_kanban.h"
#include "objects/object_dora/object_dora.h"
#include "z64math.h"

#define FLAGS 0x00000000

#define PART_FULL 0
#define PART_TOP_RIGHT (1 << 0)
#define PART_TOP_LEFT (1 << 1)
#define PART_BOTTOM_RIGHT (1 << 2)
#define PART_BOTTOM_LEFT (1 << 3)
#define RIGHT_HALF (PART_TOP_RIGHT | PART_BOTTOM_RIGHT)
#define LEFT_HALF (PART_TOP_LEFT | PART_BOTTOM_LEFT)
#define TOP_HALF (PART_TOP_RIGHT | PART_TOP_LEFT)
#define BOTTOM_HALF (PART_BOTTOM_RIGHT | PART_BOTTOM_LEFT)

#define THIS ((ObjKendoKanban*)thisx)

void ObjKendoKanban_Init(Actor* thisx, PlayState* play);
void ObjKendoKanban_Destroy(Actor* thisx, PlayState* play);
void ObjKendoKanban_Update(Actor* thisx, PlayState* play);
void ObjKendoKanban_Draw(Actor* thisx, PlayState* play);

void ObjKendoKanban_SetupDoNothing(ObjKendoKanban* this);
void ObjKendoKanban_DoNothing(ObjKendoKanban* this, PlayState* play);
void ObjKendoKanban_SetupAerial(ObjKendoKanban* this, PlayState* play);
void ObjKendoKanban_Aerial(ObjKendoKanban* this, PlayState* play);
void ObjKendoKanban_Settled(ObjKendoKanban* this, PlayState* play);
void func_80B65DA8_BounceHandler(ObjKendoKanban* this, PlayState* play);
s32 func_80B6618C(ObjKendoKanban* this, PlayState* play);

const ActorInit Obj_Kendo_Kanban_InitVars = {
    ACTOR_OBJ_KENDO_KANBAN,
    ACTORCAT_NPC,
    FLAGS,
    OBJECT_DORA,
    sizeof(ObjKendoKanban),
    (ActorFunc)ObjKendoKanban_Init,
    (ActorFunc)ObjKendoKanban_Destroy,
    (ActorFunc)ObjKendoKanban_Update,
    (ActorFunc)ObjKendoKanban_Draw,
};

// Directly applied to the velocity of the actor upon object creation.
Vec3f OBJKENDOKANBAN_LBREAK_VEL = { -1.5f, 10.0f, 0.5f }; // Push Left/Up/Forward  (Left side Breakaway)
Vec3f OBJKENDOKANBAN_RBREAK_VEL = { 1.5f, 10.0f, 0.5f };  // Push Right/Up/Forward (Right side Breakaway)
Vec3f OBJKENDOKANBAN_BBREAK_VEL = { 0.0f, 4.0f, -1.0f };  // Push Up/Back  (Bottom Breakaway)
Vec3f OBJKENDOKANBAN_TBREAK_VEL = { 1.0f, 7.0f, 4.0f };   // Push Right/Up/Forward (Top Breakaway)

// Centerpoint of the piece
Vec3f OBJKENDOKANBAN_L_CENTERPOINT = { -150.0f, 425.0f, 40.0f }; // Left
Vec3f OBJKENDOKANBAN_R_CENTERPOINT = { 150.0f, 425.0f, 40.0f };  // Right
Vec3f OBJKENDOKANBAN_B_CENTERPOINT = { 0.0f, 140.0f, 40.0f };    // Bottom
Vec3f OBJKENDOKANBAN_T_CENTERPOINT = { 0.0f, 565.0f, 40.0f };    // Top

// Displaylists for the 4 pieces.
Gfx* sDisplayLists[] = { gKendoKanbanTopRightDL, gKendoKanbanTopLeftDL, gKendoKanbanBottomRightDL,
                         gKendoKanbanBottomLeftDL };

// Coordinates on the object face providing the split
Vec3f pointTL = { -300.0f, 850.0f, 40.0f }; // Left and Top
Vec3f pointTC = { 10.0f, 850.0f, 40.0f };   // Right and Left
Vec3f pointTR = { 300.0f, 850.0f, 40.0f };  // Right and Top
Vec3f pointCL = { -300.0f, 310.0f, 40.0f }; // Bottom and Top
Vec3f pointCC = { 0.0f, 280.0f, 40.0f };
Vec3f pointCR = { 300.0f, 250.0f, 40.0f }; // Bottom and Top
Vec3f pointBL = { -300.0f, 10.0f, 40.0f }; // Left and Bottom
Vec3f pointBC = { 0.0f, 10.0f, 40.0f };    // Left and Right
Vec3f pointBR = { 300.0f, 10.0f, 40.0f };  // Right and Bottom

static ColliderTrisElementInit sTrisElementsInit[] = {
    {
        {
            ELEMTYPE_UNK5,
            { 0x00000000, 0x00, 0x00 },
            { 0x01000202, 0x00, 0x00 },
            TOUCH_NONE | TOUCH_SFX_NORMAL,
            BUMP_ON,
            OCELEM_NONE,
        },
        { { { -300.0f, 850.0f, 40.0f }, { -300.0f, 10.0f, 40.0f }, { 300.0f, 850.0f, 40.0f } } },
    },
    {
        {
            ELEMTYPE_UNK5,
            { 0x00000000, 0x00, 0x00 },
            { 0x01000202, 0x00, 0x00 },
            TOUCH_NONE | TOUCH_SFX_NORMAL,
            BUMP_ON,
            OCELEM_NONE,
        },
        { { { 300.0f, 850.0f, 40.0f }, { 300.0f, 10.0f, 40.0f }, { -300.0f, 10.0f, 40.0f } } },
    },
};

static ColliderTrisInit sTrisInit = {
    {
        COLTYPE_TREE,
        AT_NONE,
        AC_ON | AC_TYPE_PLAYER,
        OC1_NONE,
        OC2_TYPE_1,
        COLSHAPE_TRIS,
    },
    ARRAY_COUNT(sTrisElementsInit),
    sTrisElementsInit,
};

static ColliderCylinderInit sCylinderInit = {
    {
        COLTYPE_TREE,
        AT_NONE,
        AC_ON | AC_TYPE_PLAYER,
        OC1_ON | OC1_TYPE_ALL,
        OC2_TYPE_1,
        COLSHAPE_CYLINDER,
    },
    {
        ELEMTYPE_UNK1,
        { 0x00000000, 0x00, 0x00 },
        { 0xF7CFFFFF, 0x00, 0x00 },
        TOUCH_NONE | TOUCH_SFX_NORMAL,
        BUMP_ON | BUMP_HOOKABLE,
        OCELEM_ON,
    },
    { 33, 80, 0, { 0, 0, 0 } },
};

static DamageTable sDamageTable = {
    /* Deku Nut       */ DMG_ENTRY(0, 0x0),
    /* Deku Stick     */ DMG_ENTRY(0, 0xF),
    /* Horse trample  */ DMG_ENTRY(0, 0x0),
    /* Explosives     */ DMG_ENTRY(0, 0x0),
    /* Zora boomerang */ DMG_ENTRY(0, 0x0),
    /* Normal arrow   */ DMG_ENTRY(0, 0x0),
    /* UNK_DMG_0x06   */ DMG_ENTRY(2, 0xF),
    /* Hookshot       */ DMG_ENTRY(0, 0x0),
    /* Goron punch    */ DMG_ENTRY(2, 0xF),
    /* Sword          */ DMG_ENTRY(1, 0xF),
    /* Goron pound    */ DMG_ENTRY(1, 0xF),
    /* Fire arrow     */ DMG_ENTRY(0, 0x0),
    /* Ice arrow      */ DMG_ENTRY(0, 0x0),
    /* Light arrow    */ DMG_ENTRY(0, 0x0),
    /* Goron spikes   */ DMG_ENTRY(1, 0xF),
    /* Deku spin      */ DMG_ENTRY(0, 0x1),
    /* Deku bubble    */ DMG_ENTRY(0, 0x0),
    /* Deku launch    */ DMG_ENTRY(0, 0x0),
    /* UNK_DMG_0x12   */ DMG_ENTRY(0, 0x0),
    /* Zora barrier   */ DMG_ENTRY(0, 0x0),
    /* Normal shield  */ DMG_ENTRY(0, 0x0),
    /* Light ray      */ DMG_ENTRY(0, 0x0),
    /* Thrown object  */ DMG_ENTRY(0, 0xF),
    /* Zora punch     */ DMG_ENTRY(0, 0x0),
    /* Spin attack    */ DMG_ENTRY(1, 0xF),
    /* Sword beam     */ DMG_ENTRY(0, 0x0),
    /* Normal Roll    */ DMG_ENTRY(0, 0x0),
    /* UNK_DMG_0x1B   */ DMG_ENTRY(0, 0x0),
    /* UNK_DMG_0x1C   */ DMG_ENTRY(0, 0x0),
    /* Unblockable    */ DMG_ENTRY(0, 0x0),
    /* UNK_DMG_0x1E   */ DMG_ENTRY(0, 0x0),
    /* Powder Keg     */ DMG_ENTRY(0, 0x0),
};

static CollisionCheckInfoInit2 sColChkInfoInit = { 8, 0, 0, 0, MASS_HEAVY };

Vec3f OBJKENDOKANBAN_NULL_VECTOR = { 0.0f, 0.0f, 0.0f };
Vec3f OBJKENDOKANBAN_UNITX_VECTOR = { 1.0f, 0.0f, 0.0f }; // Unit Vector X (Rotation around the X-axis)

void ObjKendoKanban_Init(Actor* thisx, PlayState* play) {
    s32 pad[2];
    ObjKendoKanban* this = THIS;
    Vec3f sp70[3];
    s32 i;
    s32 j;

    Actor_SetScale(&this->actor, 0.1f);

    Collider_InitCylinder(play, &this->colliderCylinder);
    Collider_SetCylinder(play, &this->colliderCylinder, &this->actor, &sCylinderInit);
    CollisionCheck_SetInfo2(&this->actor.colChkInfo, &sDamageTable, &sColChkInfoInit);
    Collider_InitTris(play, &this->colliderTris);
    Collider_SetTris(play, &this->colliderTris, &this->actor, &sTrisInit, this->colliderTrisElements);

    Matrix_SetTranslateRotateYXZ(this->actor.world.pos.x, this->actor.world.pos.y, this->actor.world.pos.z,
                                 &this->actor.shape.rot);
    Matrix_Scale(this->actor.scale.x, this->actor.scale.y, this->actor.scale.z, MTXMODE_APPLY);

    for (i = 0; i < ARRAY_COUNT(this->colliderTrisElements); i++) {
        for (j = 0; j < ARRAY_COUNT(sp70); j++) {
            Matrix_MultVec3f(&sTrisElementsInit[i].dim.vtx[j], &sp70[j]);
        }
        Collider_SetTrisVertices(&this->colliderTris, i, &sp70[0], &sp70[1], &sp70[2]);
    }

    Actor_UpdateBgCheckInfo(play, &this->actor, 0.0f, 0.0f, 0.0f, 4);

    this->boardFragments = OBJKENDOKANBAN_GET_F(&this->actor);
    this->actor.gravity = -2.0f;
    this->fragmentCenterpoint = OBJKENDOKANBAN_NULL_VECTOR;
    this->centerPos = OBJKENDOKANBAN_NULL_VECTOR;
    this->vectLowestPoint = OBJKENDOKANBAN_NULL_VECTOR;
    this->rotationalAxis = OBJKENDOKANBAN_UNITX_VECTOR;
    this->rotationAngle = 0;
    this->rotationVelocity = 0;
    this->idxLastLowestPoint = -1;
    this->bHasNewLowestPoint = 0;
    this->framesSinceGrounded = 0;

    for (i = 0; i < ARRAY_COUNT(this->cornerPos); i++) {
        this->cornerPos[i] = this->corners[i] = OBJKENDOKANBAN_NULL_VECTOR;
    }

    this->unk_30A = 0;
    if (this->boardFragments == PART_FULL) {
        ObjKendoKanban_SetupDoNothing(this);
    } else {
        ObjKendoKanban_SetupAerial(this, play);
    }
}

void ObjKendoKanban_Destroy(Actor* thisx, PlayState* play) {
    ObjKendoKanban* this = THIS;

    Collider_DestroyCylinder(play, &this->colliderCylinder);
    Collider_DestroyTris(play, &this->colliderTris);
}

void ObjKendoKanban_SetupDoNothing(ObjKendoKanban* this) {
    this->actionFunc = ObjKendoKanban_DoNothing;
}

void ObjKendoKanban_DoNothing(ObjKendoKanban* this, PlayState* play) {
}

/**
 * @brief Setup the motion of individual board pieces.
 *
 * This function both "breaks" the board object in two, and serves as the initializer for boards in motion.
 *
 */
void ObjKendoKanban_SetupAerial(ObjKendoKanban* this, PlayState* play) {
    Player* player = GET_PLAYER(play);

    if (this->boardFragments == PART_FULL) {
        if ((player->meleeWeaponAnimation == PLAYER_MWA_FORWARD_SLASH_1H) ||
            (player->meleeWeaponAnimation == PLAYER_MWA_FORWARD_SLASH_2H) ||
            (player->meleeWeaponAnimation == PLAYER_MWA_JUMPSLASH_FINISH)) {

            // Initialize the right half, spawn the left half.
            this->boardFragments = RIGHT_HALF;
            this->rotationVelocity = DEG_TO_BINANG(10);
            this->actor.velocity = OBJKENDOKANBAN_RBREAK_VEL;
            this->fragmentCenterpoint = OBJKENDOKANBAN_R_CENTERPOINT;

            Actor_SpawnAsChild(&play->actorCtx, &this->actor, play, ACTOR_OBJ_KENDO_KANBAN,
                               this->actor.home.pos.x - 5.0f, this->actor.home.pos.y, this->actor.home.pos.z, 0, 0, 0,
                               LEFT_HALF);

            this->corners[0] = pointTC;
            this->corners[1] = pointTR;
            this->corners[2] = pointBR;
            this->corners[3] = pointBC;
        } else {

            // Initialize the bottom half, spawn the top half.
            this->boardFragments = BOTTOM_HALF;
            this->rotationVelocity = DEG_TO_BINANG(-10);
            this->actor.velocity = OBJKENDOKANBAN_BBREAK_VEL;
            this->fragmentCenterpoint = OBJKENDOKANBAN_B_CENTERPOINT;

            Actor_SpawnAsChild(&play->actorCtx, &this->actor, play, ACTOR_OBJ_KENDO_KANBAN, this->actor.home.pos.x,
                               this->actor.home.pos.y + 5.0f, this->actor.home.pos.z, 0, 0, 0, TOP_HALF);

            this->corners[0] = pointCL;
            this->corners[1] = pointCR;
            this->corners[2] = pointBR;
            this->corners[3] = pointBL;
        }
    } else if (this->boardFragments == LEFT_HALF) {

        // Initialize the newly spawned left half
        this->rotationVelocity = DEG_TO_BINANG(10);
        this->actor.velocity = OBJKENDOKANBAN_LBREAK_VEL;
        this->fragmentCenterpoint = OBJKENDOKANBAN_L_CENTERPOINT;

        this->corners[0] = pointTL;
        this->corners[1] = pointTC;
        this->corners[2] = pointBC;
        this->corners[3] = pointBL;
    } else if (this->boardFragments == TOP_HALF) {

        // Initialize the newly spawned top half
        this->rotationVelocity = DEG_TO_BINANG(10);
        this->actor.velocity = OBJKENDOKANBAN_TBREAK_VEL;
        this->fragmentCenterpoint = OBJKENDOKANBAN_T_CENTERPOINT;

        this->corners[0] = pointTL;
        this->corners[1] = pointTR;
        this->corners[2] = pointCR;
        this->corners[3] = pointCL;
    }

    this->unk_30A = 0;
    this->actionFunc = ObjKendoKanban_Aerial;
}

void ObjKendoKanban_Aerial(ObjKendoKanban* this, PlayState* play) {
    this->actor.velocity.y += this->actor.gravity;
    Actor_UpdatePos(&this->actor);
    this->rotationAngle += this->rotationVelocity;
    func_80B65DA8_BounceHandler(this, play);
    if (this->actor.world.pos.y < -200.0f) {
        this->actor.world.pos.y = -200.0f;
    }
}

void ObjKendoKanban_SetupSettled(ObjKendoKanban* this) {
    this->actionFunc = ObjKendoKanban_Settled;
}

void ObjKendoKanban_Settled(ObjKendoKanban* this, PlayState* play) {
    Player* player = GET_PLAYER(play);

    if (func_80B6618C(this, play) == 1) {
        player->unk_AC0 = 700.0f;
    }
}

void func_80B65DA8_BounceHandler(ObjKendoKanban* this, PlayState* play) {
    Vec3f lowestPoint;
    s32 pad[2];
    Vec3f vecCenterOut;
    s32 pad2;
    s32 idxLowestPoint = 0;
    s32 i;
    f32 verticalScalar;

    lowestPoint = this->cornerPos[0];

    // Calculate gravity's effect on rotation.
    // Determine whether the board face is pointing down or up. If pointing down, accelerate, if not, decellerate
    vecCenterOut = this->actor.world.pos;
    vecCenterOut.x -= this->centerPos.x;
    vecCenterOut.y -= this->centerPos.y;
    vecCenterOut.z -= this->centerPos.z;
    verticalScalar = (this->rotationalAxis.x * vecCenterOut.z) + (this->rotationalAxis.z * -vecCenterOut.x);
    if (verticalScalar < 0.0f) {
        this->rotationVelocity += 0x64;
    } else {
        this->rotationVelocity -= 0x64;
    }

    // Find the lowest point? Why? Actor position is set to the lowest point
    for (i = 0; i < ARRAY_COUNT(this->cornerPos); i++) {
        if (this->cornerPos[i].y < lowestPoint.y) {
            lowestPoint = this->cornerPos[i];
            idxLowestPoint = i;
        }
    }

    // When the lowest point changes, re-initialize the actor position to that point?
    if (idxLowestPoint != this->idxLastLowestPoint) {
        this->bHasNewLowestPoint = 1;
        this->idxLastLowestPoint = idxLowestPoint;
        this->vectLowestPoint = this->corners[idxLowestPoint];

        Matrix_Push();
        Matrix_SetTranslateRotateYXZ(this->actor.world.pos.x, this->actor.world.pos.y, this->actor.world.pos.z,
                                     &this->actor.shape.rot);
        Matrix_Scale(this->actor.scale.x, this->actor.scale.y, this->actor.scale.z, MTXMODE_APPLY);
        Matrix_MultVec3f(&this->vectLowestPoint, &this->actor.world.pos);
        this->actor.world.pos = lowestPoint; // Doesn't this blast away all the matrix math?
        this->actor.prevPos = this->actor.world.pos;
        Matrix_Pop();
    }

    Actor_UpdateBgCheckInfo(play, &this->actor, 0.0f, 0.0f, 0.0f, 4);

    if (this->actor.bgCheckFlags & 1) { // Stationary Grounded
        // When the board is on the ground, Apply some drag to slow it to a stop?
        this->actor.velocity.x *= 0.8f;
        this->actor.velocity.z *= 0.8f;
    }

    if (this->bHasNewLowestPoint == 1) {
        if (this->framesSinceGrounded >= 7) {

            // Suppress rotational velocity?
            s16 deltaRotationAngle = this->rotationAngle & 0x3FFF; // Limit to 90 degrees
            if (deltaRotationAngle >= 0x2000) {                    // If Greater than 45
                deltaRotationAngle -= 0x4000;                      // Go 90 degrees opposite
            }
            this->rotationAngle -= deltaRotationAngle;
            this->rotationVelocity = 0;
            ObjKendoKanban_SetupSettled(this);
            return;
        }

        if (this->actor.bgCheckFlags & 2) {
            // When the board Touches the ground,...
            Actor_PlaySfxAtPos(&this->actor, NA_SE_EV_WOODPLATE_BOUND);
            this->bHasNewLowestPoint = 0;
            this->actor.velocity.y *= 0.5f;
        } else if (this->actor.bgCheckFlags & 1) {
            // When the board on the ground, ...
            this->framesSinceGrounded++;
            this->bHasNewLowestPoint = 0;
            this->actor.velocity.x *= 0.3f;
            this->actor.velocity.z *= 0.3f;
            Actor_PlaySfxAtPos(&this->actor, NA_SE_EV_WOODPLATE_BOUND);

            if (verticalScalar > 0.0f) {
                if (this->rotationVelocity > 0) {
                    this->rotationVelocity *= 1.2f;
                } else {
                    this->rotationVelocity *= -0.6f;
                }
            } else if (this->rotationVelocity < 0) {
                this->rotationVelocity *= 1.2f;
            } else {
                this->rotationVelocity *= -0.6f;
            }
        }
    }
}

// cjb need to check what this function is doing.
s32 func_80B6618C(ObjKendoKanban* this, PlayState* play) {
    Player* player = GET_PLAYER(play);
    s32 nextIdx;
    s32 phi_v1 = 0;
    s32 i;
    f32 x;
    f32 z;
    f32 x2;
    f32 z2;

    for (i = 0; i < ARRAY_COUNT(this->cornerPos); i++) {
        nextIdx = i != 3 ? i + 1 : 0;

        // Horizontal components of displacement from X[i] to Player
        z = this->cornerPos[i].z - player->actor.world.pos.z;
        x = this->cornerPos[i].x - player->actor.world.pos.x;

        // Horizontal components of displacement from X[nextIdx] to Player
        z2 = (this->cornerPos[nextIdx].z - player->actor.world.pos.z);
        x2 = (this->cornerPos[nextIdx].x - player->actor.world.pos.x);

        // If the cross product's y component is negative
        if ((x * z2) < (z * x2)) {
            if (phi_v1 == 0) {
                phi_v1 = 1;
            } else if (phi_v1 != 1) {
                return false;
            }
        } else if (phi_v1 == 0) {
            phi_v1 = -1;
        } else if (phi_v1 != -1) {
            return false;
        }
    }
    return true;
}

void ObjKendoKanban_UpdateCollision(ObjKendoKanban* this, PlayState* play) {
    if ((this->actionFunc != ObjKendoKanban_Aerial) && (this->actionFunc != ObjKendoKanban_Settled)) {
        if (this->colliderTris.base.acFlags & AC_HIT) {
            this->colliderTris.base.acFlags &= ~AC_HIT;
            ObjKendoKanban_SetupAerial(this, play);
        }

        Collider_UpdateCylinder(&this->actor, &this->colliderCylinder);
        this->colliderCylinder.dim.pos.z -= (s16)(20.0f * Math_CosS(this->actor.shape.rot.y));
        this->colliderCylinder.dim.pos.x -= (s16)(20.0f * Math_SinS(this->actor.shape.rot.y));

        if (this->actionFunc == ObjKendoKanban_DoNothing) {
            CollisionCheck_SetAC(play, &play->colChkCtx, &this->colliderTris.base);
        }

        CollisionCheck_SetOC(play, &play->colChkCtx, &this->colliderCylinder.base);
    }
}

void ObjKendoKanban_Update(Actor* thisx, PlayState* play) {
    ObjKendoKanban* this = THIS;

    this->actionFunc(this, play);

    ObjKendoKanban_UpdateCollision(this, play);
}

void ObjKendoKanban_Draw(Actor* thisx, PlayState* play) {
    ObjKendoKanban* this = THIS;
    s32 i;
    Gfx* poly;

    OPEN_DISPS(play->state.gfxCtx);

    func_8012C28C(play->state.gfxCtx);

    if (this->boardFragments == PART_FULL) {
        // A full board is simply displayed
        gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(play->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        gSPDisplayList(POLY_OPA_DISP++, gKendoKanbanDL);
    } else {
        // Fragments of boards are in motion, so apply their rotation/translation, and display only the DLs which
        // apply.
        Matrix_RotateAxisS(this->rotationAngle, &this->rotationalAxis, MTXMODE_APPLY);
        Matrix_Translate(-this->vectLowestPoint.x, -this->vectLowestPoint.y, -this->vectLowestPoint.z, MTXMODE_APPLY);
        gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(play->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);

        // Display only the fragments of the board which are present
        for (i = 0; i < ARRAY_COUNT(sDisplayLists); i++) {
            if ((1 << i) & this->boardFragments) {
                gSPDisplayList(POLY_OPA_DISP++, sDisplayLists[i]);
            }
        }
    }

    CLOSE_DISPS(play->state.gfxCtx);

    // Update the alternate position trackers (Corners and Center of the board)
    for (i = 0; i < ARRAY_COUNT(this->cornerPos); i++) {
        Matrix_MultVec3f(&this->corners[i], &this->cornerPos[i]);
    }
    Matrix_MultVec3f(&this->fragmentCenterpoint, &this->centerPos);
}
