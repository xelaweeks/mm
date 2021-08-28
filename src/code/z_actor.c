#include "global.h"
#include "overlays/actors/ovl_En_Horse/z_en_horse.h"

void Actor_PrintLists(ActorContext* actorCtx) {
    ActorListEntry* actorList = &actorCtx->actorList[0];
    Actor* actor;
    s32 i;

    FaultDrawer_SetCharPad(-2, 0);
    FaultDrawer_Printf("actor\n", gMaxActorId);
    FaultDrawer_Printf("No. Actor   Name Part SegName\n");

    for (i = 0; i < ARRAY_COUNT(actorCtx->actorList); i++) {
        actor = actorList[i].first;

        while (actor != NULL) {
            FaultDrawer_Printf("%3d %08x %04x %3d %s\n", i, actor, actor->id, actor->category, "");
            actor = actor->next;
        }
    }
}

void ActorShape_Init(ActorShape* actorShape, f32 yOffset, ActorShadowFunc shadowDraw, f32 shadowScale) {
    actorShape->yOffset = yOffset;
    actorShape->shadowDraw = shadowDraw;
    actorShape->shadowScale = shadowScale;
    actorShape->shadowAlpha = 255;
}

void ActorShadow_Draw(Actor* actor, Lights* lights, GlobalContext* globalCtx, Gfx* dlist, Color_RGBA8* color) {
    if (actor->floorPoly != NULL) {
        f32 dy = actor->world.pos.y - actor->floorHeight;

        if (dy >= -50.0f && dy < 500.0f) {
            f32 shadowScale;
            MtxF mtx;

            OPEN_DISPS(globalCtx->state.gfxCtx);

            POLY_OPA_DISP = Gfx_CallSetupDL(POLY_OPA_DISP, 0x2C);

            gDPSetCombineLERP(POLY_OPA_DISP++, 0, 0, 0, PRIMITIVE, TEXEL0, 0, PRIMITIVE, 0, 0, 0, 0, COMBINED, 0, 0, 0,
                              COMBINED);

            dy = CLAMP(dy, 0.0f, 150.0f);
            shadowScale = 1.0f - (dy * 0.0028571428f);
            if ((dy * 0.0028571428f) > 1.0f) {
                shadowScale = 0.0f;
            }

            if (color != NULL) {
                gDPSetPrimColor(POLY_OPA_DISP++, 0, 0, color->r, color->g, color->b,
                                (u8)(actor->shape.shadowAlpha * shadowScale));
            } else {
                gDPSetPrimColor(POLY_OPA_DISP++, 0, 0, 0, 0, 0, (u8)(actor->shape.shadowAlpha * shadowScale));
            }

            func_800C0094(actor->floorPoly, actor->world.pos.x, actor->floorHeight, actor->world.pos.z, &mtx);
            SysMatrix_SetCurrentState(&mtx);

            if ((dlist != D_04076BC0) || (actor->scale.x != actor->scale.z)) {
                Matrix_RotateY(actor->shape.rot.y, MTXMODE_APPLY);
            }

            shadowScale *= actor->shape.shadowScale;
            Matrix_Scale(actor->scale.x * shadowScale, 1.0f, actor->scale.z * shadowScale, MTXMODE_APPLY);

            gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(globalCtx->state.gfxCtx), G_MTX_MODELVIEW | G_MTX_LOAD);
            gSPDisplayList(POLY_OPA_DISP++, dlist);

            CLOSE_DISPS(globalCtx->state.gfxCtx);
        }
    }
}

/* ActorShadow_DrawCircle */
void func_800B3FC0(Actor* actor, Lights* lights, GlobalContext* globalCtx) {
    if (actor->bgCheckFlags & 0x400) {
        func_800B4AEC(globalCtx, actor, 50.0f);
    }

    ActorShadow_Draw(actor, lights, globalCtx, D_04076BC0, NULL);
}

/* ActorShadow_DrawSquare */
void func_800B4024(Actor* actor, Lights* lights, GlobalContext* globalCtx) {
    if (actor->bgCheckFlags & 0x400) {
        func_800B4AEC(globalCtx, actor, 50.0f);
    }

    ActorShadow_Draw(actor, lights, globalCtx, D_04075A40, NULL);
}

static Color_RGBA8 D_801AEC80 = { 255, 255, 255, 255 };

/* ActorShadow_DrawWhiteCircle */
void func_800B4088(Actor* actor, Lights* lights, GlobalContext* globalCtx) {
    ActorShadow_Draw(actor, lights, globalCtx, D_04076BC0, &D_801AEC80);
}

/* ActorShadow_DrawHorse */
void func_800B40B8(Actor* actor, Lights* lights, GlobalContext* globalCtx) {
    ActorShadow_Draw(actor, lights, globalCtx, D_04077480, NULL);
}

/* ActorShadow_DrawFoot */
void func_800B40E0(GlobalContext* globalCtx, Light* light, MtxF* arg2, s32 arg3, f32 arg4, f32 arg5, f32 arg6) {
    s32 pad;
    s16 sp58;
    f32 dir2;
    f32 dir0;

    OPEN_DISPS(globalCtx->state.gfxCtx);

    gDPSetPrimColor(POLY_OPA_DISP++, 0, 0, 0, 0, 0, (u8)(CLAMP_MAX(arg3 * 1.3e-05f, 1.0f) * arg4));

    dir0 = light->l.dir[0];
    dir2 = light->l.dir[2];
    sp58 = Math_FAtan2F(dir2, dir0);
    arg6 *= 4.5f - light->l.dir[1] * 0.035f;
    arg6 = CLAMP_MIN(arg6, 1.0f);
    SysMatrix_SetCurrentState(arg2);
    Matrix_RotateY(sp58, MTXMODE_APPLY);
    Matrix_Scale(arg5, 1.0f, arg5 * arg6, MTXMODE_APPLY);

    gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(globalCtx->state.gfxCtx), G_MTX_MODELVIEW | G_MTX_LOAD);
    gSPDisplayList(POLY_OPA_DISP++, D_04075B30);

    CLOSE_DISPS(globalCtx->state.gfxCtx);
}

// ActorShadow_DrawFeet
#pragma GLOBAL_ASM("asm/non_matchings/code/z_actor/func_800B42F8.s")

// Actor_SetFeetPos
void func_800B4A98(Actor* actor, s32 limbIndex, s32 leftFootIndex, Vec3f* leftFootPos, s32 rightFootIndex,
                   Vec3f* rightFootPos) {
    if (limbIndex == leftFootIndex) {
        SysMatrix_MultiplyVector3fByState(leftFootPos, &actor->shape.feetPos[FOOT_LEFT]);
    } else if (limbIndex == rightFootIndex) {
        SysMatrix_MultiplyVector3fByState(rightFootPos, &actor->shape.feetPos[FOOT_RIGHT]);
    }
}

void func_800B4AEC(GlobalContext* globalCtx, Actor* actor, f32 param_3) {
    s32 floorBgId;
    f32 yPos = actor->world.pos.y;

    actor->world.pos.y += param_3;
    actor->floorHeight =
        func_800C4188(globalCtx, &globalCtx->colCtx, &actor->floorPoly, &floorBgId, actor, &actor->world.pos);
    actor->floorBgId = floorBgId;
    actor->world.pos.y = yPos;
}

#pragma GLOBAL_ASM("asm/non_matchings/code/z_actor/func_800B4B50.s")

void func_800B4EDC(GlobalContext* globalCtx, Vec3f* pzParm2, Vec3f* pzParm3, f32* pfParm4) {
    SkinMatrix_Vec3fMtxFMultXYZW(&globalCtx->projectionMatrix, pzParm2, pzParm3, pfParm4);
    if (*pfParm4 < 1.0f) {
        *pfParm4 = 1.0f;
    } else {
        *pfParm4 = 1.0f / *pfParm4;
    }
}

void func_800B4F40(TargetContext* targetCtx, s32 index, f32 x, f32 y, f32 z) {
    targetCtx->unk50[index].pos.x = x;
    targetCtx->unk50[index].pos.y = y;
    targetCtx->unk50[index].pos.z = z;
    targetCtx->unk50[index].unkC = targetCtx->unk44;
}

s801AEC84 D_801AEC84[] = {
    { 0, 0xFF, 0, 0xFF, 0, 0xFF, 0, 0 },
    { 0, 0xFF, 0, 0xFF, 0, 0xFF, 0, 0 },
    { 0xFF, 0xFF, 0xE6, 0xFF, 0xDC, 0xA0, 0x50, 0 },
    { 0, 0xFF, 0, 0xFF, 0, 0xFF, 0, 0 },
    { 0x96, 0x96, 0xFF, 0xFF, 0x96, 0x96, 0xFF, 0 },
    { 0xFF, 0xFF, 0, 0xFF, 0xC8, 0x9B, 0, 0 },
    { 0, 0xFF, 0, 0xFF, 0, 0xFF, 0, 0 },
    { 0, 0xFF, 0, 0xFF, 0, 0xFF, 0, 0 },
    { 0, 0xFF, 0, 0xFF, 0, 0xFF, 0, 0 },
    { 0xFF, 0xFF, 0, 0xFF, 0xC8, 0x9B, 0, 0 },
    { 0, 0xFF, 0, 0xFF, 0, 0xFF, 0, 0 },
    { 0, 0xFF, 0, 0xFF, 0, 0xFF, 0, 0 },
    { 0, 0xFF, 0, 0xFF, 0, 0xFF, 0, 0 },
};

void func_800B4F78(TargetContext* targetCtx, s32 type, GlobalContext* globalCtx) {
    s801AEC84* temp_s2;
    s32 phi_s1;
    TargetContextEntry* phi_s0;

    Math_Vec3f_Copy(&targetCtx->unkC, &globalCtx->view.eye);
    targetCtx->unk48 = 0x100;
    temp_s2 = &D_801AEC84[type];
    targetCtx->unk44 = 500.0f;

    phi_s0 = targetCtx->unk50;
    for (phi_s1 = 0; phi_s1 < ARRAY_COUNT(targetCtx->unk50); phi_s1++, phi_s0++) {
        func_800B4F40(targetCtx, phi_s1, 0.0f, 0.0f, 0.0f);
        phi_s0->color.r = temp_s2->unk0;
        phi_s0->color.g = temp_s2->unk1;
        phi_s0->color.b = temp_s2->unk2;
    }
}

#pragma GLOBAL_ASM("asm/non_matchings/code/z_actor/func_800B5040.s")

void Actor_TargetContextInit(TargetContext* targetCtx, Actor* actor, GlobalContext* globalCtx) {
    targetCtx->unk90 = NULL;
    targetCtx->unk8C = NULL;
    targetCtx->unk3C = NULL;
    targetCtx->unk38 = NULL;
    targetCtx->unk4B = 0;
    targetCtx->unk4C = 0;
    targetCtx->unk40 = 0;
    func_800B5040(targetCtx, actor, actor->category, globalCtx);
    func_800B4F78(targetCtx, actor->category, globalCtx);
}

#pragma GLOBAL_ASM("asm/non_matchings/code/z_actor/func_800B5208.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_actor/func_800B5814.s")

u32 Flags_GetSwitch(GlobalContext* globalCtx, s32 flag) {
    if (flag >= 0 && flag < 0x80) {
        return globalCtx->actorCtx.switchFlags[(flag & -0x20) >> 5] & (1 << (flag & 0x1F));
    }
    return 0;
}

void Actor_SetSwitchFlag(GlobalContext* globalCtx, s32 flag) {
    if (flag >= 0 && flag < 0x80) {
        globalCtx->actorCtx.switchFlags[(flag & -0x20) >> 5] |= 1 << (flag & 0x1F);
    }
}

void Actor_UnsetSwitchFlag(GlobalContext* globalCtx, s32 flag) {
    if (flag >= 0 && flag < 0x80) {
        globalCtx->actorCtx.switchFlags[(flag & -0x20) >> 5] &= ~(1 << (flag & 0x1F));
    }
}

u32 Actor_GetChestFlag(GlobalContext* globalCtx, u32 flag) {
    return globalCtx->actorCtx.chestFlags & (1 << flag);
}

void Actor_SetChestFlag(GlobalContext* globalCtx, u32 flag) {
    globalCtx->actorCtx.chestFlags |= (1 << flag);
}

void Actor_SetAllChestFlag(GlobalContext* globalCtx, u32 flag) {
    globalCtx->actorCtx.chestFlags = flag;
}

u32 Actor_GetAllChestFlag(GlobalContext* globalCtx) {
    return globalCtx->actorCtx.chestFlags;
}

u32 Actor_GetRoomCleared(GlobalContext* globalCtx, u32 roomNumber) {
    return globalCtx->actorCtx.clearedRooms & (1 << roomNumber);
}

void Actor_SetRoomCleared(GlobalContext* globalCtx, u32 roomNumber) {
    globalCtx->actorCtx.clearedRooms |= (1 << roomNumber);
}

void Actor_UnsetRoomCleared(GlobalContext* globalCtx, u32 roomNumber) {
    globalCtx->actorCtx.clearedRooms &= ~(1 << roomNumber);
}

u32 Actor_GetRoomClearedTemp(GlobalContext* globalCtx, u32 roomNumber) {
    return globalCtx->actorCtx.clearedRoomsTemp & (1 << roomNumber);
}

void Actor_SetRoomClearedTemp(GlobalContext* globalCtx, u32 roomNumber) {
    globalCtx->actorCtx.clearedRoomsTemp |= (1 << roomNumber);
}

void Actor_UnsetRoomClearedTemp(GlobalContext* globalCtx, u32 roomNumber) {
    globalCtx->actorCtx.clearedRoomsTemp &= ~(1 << roomNumber);
}

u32 Actor_GetCollectibleFlag(GlobalContext* globalCtx, s32 index) {
    if (index > 0 && index < 0x80) {
        return globalCtx->actorCtx.collectibleFlags[(index & -0x20) >> 5] & (1 << (index & 0x1F));
    }
    return 0;
}

void Actor_SetCollectibleFlag(GlobalContext* globalCtx, s32 index) {
    if (index > 0 && index < 0x80) {
        globalCtx->actorCtx.collectibleFlags[(index & -0x20) >> 5] |= 1 << (index & 0x1F);
    }
}

void TitleCard_ContextInit(GlobalContext* globalCtx, TitleCardContext* titleCtx) {
    titleCtx->durationTimer = 0;
    titleCtx->delayTimer = 0;
    titleCtx->intensity = 0;
    titleCtx->alpha = 0;
}

void TitleCard_InitBossName(GlobalContext* globalCtx, TitleCardContext* titleCtx, u32 texture, s16 param_4, s16 param_5,
                            u8 param_6, u8 param_7) {
    titleCtx->texture = texture;
    titleCtx->x = param_4;
    titleCtx->y = param_5;
    titleCtx->width = param_6;
    titleCtx->height = param_7;
    titleCtx->durationTimer = 80;
    titleCtx->delayTimer = 0;
}

void TitleCard_InitPlaceName(GlobalContext* globalCtx, TitleCardContext* titleCtx, void* texture, s32 x, s32 y,
                             s32 width, s32 height, s32 delay) {
}

void TitleCard_Update(GlobalContext* globalCtx, TitleCardContext* titleCtx) {
    if (DECR(titleCtx->delayTimer) == 0) {
        if (DECR(titleCtx->durationTimer) == 0) {
            Math_StepToS(&titleCtx->alpha, 0, 30);
            Math_StepToS(&titleCtx->intensity, 0, 70);
        } else {
            Math_StepToS(&titleCtx->alpha, 255, 10);
            Math_StepToS(&titleCtx->intensity, 255, 20);
        }
    }
}

void TitleCard_Draw(GlobalContext* globalCtx, TitleCardContext* titleCtx) {
    s32 spCC;
    s32 spC8;
    s32 unk1;
    s32 spC0;
    s32 sp38;
    s32 spB8;
    s32 spB4;
    s32 temp;

    if (titleCtx->alpha != 0) {
        spCC = titleCtx->width;
        spC8 = titleCtx->height;
        temp = spCC * 2;
        spC0 = (titleCtx->x * 4) - temp;
        spB8 = (titleCtx->y * 4) - (spC8 * 2);
        sp38 = spCC * 2;

        OPEN_DISPS(globalCtx->state.gfxCtx);

        spC8 = (spCC * spC8 > 0x1000) ? 0x1000 / spCC : spC8;
        spB4 = spB8 + (spC8 * 4);

        if (1) {}

        OVERLAY_DISP = func_8012C014(OVERLAY_DISP);

        gDPSetPrimColor(OVERLAY_DISP++, 0, 0, (u8)titleCtx->intensity, (u8)titleCtx->intensity, (u8)titleCtx->intensity,
                        (u8)titleCtx->alpha);

        gDPLoadTextureBlock(OVERLAY_DISP++, (s32*)titleCtx->texture, G_IM_FMT_IA, G_IM_SIZ_8b, spCC, spC8, 0,
                            G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD,
                            G_TX_NOLOD);

        gSPTextureRectangle(OVERLAY_DISP++, spC0, spB8, ((sp38 * 2) + spC0) - 4, spB8 + (spC8 * 4) - 1, G_TX_RENDERTILE,
                            0, 0, 1 << 10, 1 << 10);

        spC8 = titleCtx->height - spC8;

        if (spC8 > 0) {
            gDPLoadTextureBlock(OVERLAY_DISP++, (s32)titleCtx->texture + 0x1000, G_IM_FMT_IA, G_IM_SIZ_8b, spCC, spC8,
                                0, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK,
                                G_TX_NOLOD, G_TX_NOLOD);

            gSPTextureRectangle(OVERLAY_DISP++, spC0, spB4, ((sp38 * 2) + spC0) - 4, spB4 + (spC8 * 4) - 1,
                                G_TX_RENDERTILE, 0, 0, 1 << 10, 1 << 10);
        }

        CLOSE_DISPS(globalCtx->state.gfxCtx);
    }
}

s32 func_800B6434(GlobalContext* globalCtx, TitleCardContext* titleCtx) {
    if ((globalCtx->actorCtx.titleCtxt.delayTimer != 0) || (globalCtx->actorCtx.titleCtxt.alpha != 0)) {
        titleCtx->durationTimer = 0;
        titleCtx->delayTimer = 0;
        return false;
    }
    return true;
}

void func_800B6468(GlobalContext* globalCtx) {
    globalCtx->actorCtx.unk1F5 = 0;
}

void func_800B6474(GlobalContext* globalCtx) {
    if (globalCtx->actorCtx.unk1F5 != 0) {
        globalCtx->actorCtx.unk1F5--;
    }
}

s32 func_800B648C(GlobalContext* globalCtx, s32 arg1, s32 arg2, f32 arg3, Vec3f* arg4) {
    if ((globalCtx->actorCtx.unk1F5 != 0) && (arg3 < globalCtx->actorCtx.unk1F8)) {
        return 0;
    }

    globalCtx->actorCtx.unk1F4 = arg1;
    globalCtx->actorCtx.unk1F5 = arg2;
    globalCtx->actorCtx.unk1F8 = arg3;
    Math_Vec3f_Copy(&globalCtx->actorCtx.unk1FC, arg4);
    return 1;
}

f32 func_800B64FC(GlobalContext* globalCtx, f32 arg1, Vec3f* arg2, u32* arg3) {
    f32 temp_f8;

    if ((globalCtx->actorCtx.unk1F5 == 0) || (arg1 == 0.0f)) {
        return -1.0f;
    }

    temp_f8 = Math_Vec3f_DistXYZ(&globalCtx->actorCtx.unk1FC, arg2) / arg1;
    *arg3 = globalCtx->actorCtx.unk1F4;
    return globalCtx->actorCtx.unk1F8 - temp_f8;
}

#pragma GLOBAL_ASM("asm/non_matchings/code/z_actor/func_800B6584.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_actor/func_800B6608.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_actor/func_800B6680.s")

void Actor_MarkForDeath(Actor* actor) {
    actor->draw = NULL;
    actor->update = NULL;
    actor->flags &= ~0x1;
}

void Actor_SetWorldToHome(Actor* actor) {
    actor->world = actor->home;
}

void Actor_SetFocus(Actor* actor, f32 height) {
    actor->focus.pos.x = actor->world.pos.x;
    actor->focus.pos.y = actor->world.pos.y + height;
    actor->focus.pos.z = actor->world.pos.z;

    actor->focus.rot.x = actor->world.rot.x;
    actor->focus.rot.y = actor->world.rot.y;
    actor->focus.rot.z = actor->world.rot.z;
}

void Actor_SetWorldRotToShape(Actor* actor) {
    actor->world.rot = actor->shape.rot;
}

void Actor_SetShapeRotToWorld(Actor* actor) {
    actor->shape.rot = actor->world.rot;
}

void Actor_SetScale(Actor* actor, f32 scale) {
    actor->scale.z = scale;
    actor->scale.y = scale;
    actor->scale.x = scale;
}

void Actor_SetObjectDependency(GlobalContext* globalCtx, Actor* actor) {
    gSegments[6] = PHYSICAL_TO_VIRTUAL(globalCtx->objectCtx.status[actor->objBankIndex].segment);
}

void Actor_Init(Actor* actor, GlobalContext* globalCtx) {
    Actor_SetWorldToHome(actor);
    Actor_SetShapeRotToWorld(actor);
    Actor_SetFocus(actor, 0.0f);
    Math_Vec3f_Copy(&actor->prevPos, &actor->world.pos);
    Actor_SetScale(actor, 0.01f);
    actor->targetMode = 3;
    actor->minVelocityY = -20.0f;

    actor->xyzDistToPlayerSq = FLT_MAX;
    actor->uncullZoneForward = 1000.0f;
    actor->uncullZoneScale = 350.0f;
    actor->uncullZoneDownward = 700.0f;

    actor->hintId = 255;

    CollisionCheck_InitInfo(&actor->colChkInfo);
    actor->floorBgId = BGCHECK_SCENE;

    ActorShape_Init(&actor->shape, 0.0f, NULL, 0.0f);
    if (Object_IsLoaded(&globalCtx->objectCtx, actor->objBankIndex)) {
        Actor_SetObjectDependency(globalCtx, actor);
        actor->init(actor, globalCtx);
        actor->init = NULL;
    }
}

void Actor_Destroy(Actor* actor, GlobalContext* globalCtx) {
    if (actor->init == NULL) {
        if (actor->destroy != NULL) {
            actor->destroy(actor, globalCtx);
            actor->destroy = NULL;
        }
    }
}

f32 actorMovementScale = 1.0f;

void Actor_SetMovementScale(s32 scale) {
    actorMovementScale = scale * 0.5f;
}

void Actor_ApplyMovement(Actor* actor) {
    f32 speedRate = actorMovementScale;

    actor->world.pos.x += ((actor->velocity.x * speedRate) + actor->colChkInfo.displacement.x);
    actor->world.pos.y += ((actor->velocity.y * speedRate) + actor->colChkInfo.displacement.y);
    actor->world.pos.z += ((actor->velocity.z * speedRate) + actor->colChkInfo.displacement.z);
}

void Actor_SetVelocityYRotationAndGravity(Actor* actor) {
    actor->velocity.x = actor->speedXZ * Math_SinS(actor->world.rot.y);
    actor->velocity.z = actor->speedXZ * Math_CosS(actor->world.rot.y);

    actor->velocity.y += actor->gravity;
    if (actor->velocity.y < actor->minVelocityY) {
        actor->velocity.y = actor->minVelocityY;
    }
}

void Actor_MoveForward(Actor* actor) {
    Actor_SetVelocityYRotationAndGravity(actor);
    Actor_ApplyMovement(actor);
}

void Actor_SetVelocityXYRotation(Actor* actor) {
    f32 velX = Math_CosS(actor->world.rot.x) * actor->speedXZ;

    actor->velocity.x = Math_SinS(actor->world.rot.y) * velX;
    actor->velocity.y = Math_SinS(actor->world.rot.x) * actor->speedXZ;
    actor->velocity.z = Math_CosS(actor->world.rot.y) * velX;
}

void Actor_SetVelocityAndMoveXYRotation(Actor* actor) {
    Actor_SetVelocityXYRotation(actor);
    Actor_ApplyMovement(actor);
}

void Actor_SetVelocityXYRotationReverse(Actor* actor) {
    f32 velX = Math_CosS(-actor->world.rot.x) * actor->speedXZ;
    actor->velocity.x = Math_SinS(actor->world.rot.y) * velX;
    actor->velocity.y = Math_SinS(-actor->world.rot.x) * actor->speedXZ;
    actor->velocity.z = Math_CosS(actor->world.rot.y) * velX;
}

void Actor_SetVelocityAndMoveXYRotationReverse(Actor* actor) {
    Actor_SetVelocityXYRotationReverse(actor);
    Actor_ApplyMovement(actor);
}

void func_800B6C04(Actor* actor, f32 speed) {
    actor->speedXZ = Math_CosS(actor->world.rot.x) * speed;
    actor->velocity.y = -Math_SinS(actor->world.rot.x) * speed;
}

void func_800B6C58(Actor* actor, SkelAnime* skelAnime) {
    Vec3f pos;

    func_80137748(skelAnime, &pos, actor->shape.rot.y);
    actor->world.pos.x += pos.x * actor->scale.x;
    actor->world.pos.y += pos.y * actor->scale.y;
    actor->world.pos.z += pos.z * actor->scale.z;
}

s16 Actor_YawBetweenActors(Actor* from, Actor* to) {
    return Math_Vec3f_Yaw(&from->world.pos, &to->world.pos);
}

s16 Actor_YawBetweenActorsTop(Actor* from, Actor* to) {
    return Math_Vec3f_Yaw(&from->focus.pos, &to->focus.pos);
}

s16 Actor_YawToPoint(Actor* actor, Vec3f* point) {
    return Math_Vec3f_Yaw(&actor->world.pos, point);
}

s16 Actor_PitchBetweenActors(Actor* from, Actor* to) {
    return Math_Vec3f_Pitch(&from->world.pos, &to->world.pos);
}

s16 Actor_PitchBetweenActorsTop(Actor* from, Actor* to) {
    return Math_Vec3f_Pitch(&from->focus.pos, &to->focus.pos);
}

s16 Actor_PitchToPoint(Actor* actor, Vec3f* point) {
    return Math_Vec3f_Pitch(&actor->world.pos, point);
}

f32 Actor_DistanceBetweenActors(Actor* actor1, Actor* actor2) {
    return Math_Vec3f_DistXYZ(&actor1->world.pos, &actor2->world.pos);
}

f32 Actor_DistanceToPoint(Actor* actor, Vec3f* point) {
    return Math_Vec3f_DistXYZ(&actor->world.pos, point);
}

f32 Actor_XZDistanceBetweenActors(Actor* actor1, Actor* actor2) {
    return Math_Vec3f_DistXZ(&actor1->world.pos, &actor2->world.pos);
}

f32 Actor_XZDistanceToPoint(Actor* actor, Vec3f* point) {
    return Math_Vec3f_DistXZ(&actor->world.pos, point);
}

void Actor_CalcOffsetOrientedToDrawRotation(Actor* actor, Vec3f* offset, Vec3f* point) {
    f32 cos_rot_y;
    f32 sin_rot_y;
    f32 imm_x;
    f32 imm_z;

    cos_rot_y = Math_CosS(actor->shape.rot.y);
    sin_rot_y = Math_SinS(actor->shape.rot.y);
    imm_x = point->x - actor->world.pos.x;
    imm_z = point->z - actor->world.pos.z;
    offset->x = ((imm_x * cos_rot_y) - (imm_z * sin_rot_y));
    offset->z = ((imm_z * cos_rot_y) + (imm_x * sin_rot_y));
    offset->y = point->y - actor->world.pos.y;
}

f32 Actor_HeightDiff(Actor* actor1, Actor* actor2) {
    return actor2->world.pos.y - actor1->world.pos.y;
}

void func_800B6F20(GlobalContext* globalCtx, Input* input, f32 arg2, s16 arg3) {
    s16 sp26;

    sp26 = arg3 - func_800DFC68(ACTIVE_CAM);
    input->cur.stick_x = -Math_SinS(sp26) * arg2;
    input->rel.stick_x = input->cur.stick_x;
    input->cur.stick_y = Math_CosS(sp26) * arg2;
    input->rel.stick_y = input->cur.stick_y;
}

f32 Player_GetHeight(Player* player) {
    f32 offset;

    if (player->stateFlags1 & 0x800000) {
        offset = 32.0f;
    } else {
        offset = 0.0f;
    }

    switch (player->transformation) {
        default:
        case PLAYER_FORM_FIERCE_DEITY:
            return offset + 124.0f;
        case PLAYER_FORM_GORON:
            return offset + ((player->stateFlags3 & 0x1000) ? 34.0f : 80.0f);
        case PLAYER_FORM_ZORA:
            return offset + 68.0f;
        case PLAYER_FORM_DEKU:
            return offset + 36.0f;
        case PLAYER_FORM_HUMAN:
            return offset + 44.0f;
    }
}

// Player_GetRunSpeedLimit?
f32 func_800B7090(Player* player) {
    if (player->stateFlags1 & 0x800000) {
        return 15.0f;
    } else if (player->stateFlags1 & 0x8000000) {
        return (R_RUN_SPEED_LIMIT / 100.0f) * 0.6f;
    } else {
        return R_RUN_SPEED_LIMIT / 100.0f;
    }
}

s32 func_800B7118(Player* player) {
    return player->stateFlags1 & 8;
}

s32 func_800B7128(Player* player) {
    return func_800B7118(player) && player->unk_ACC;
}

s32 func_800B715C(GlobalContext* globalCtx) {
    Player* player = PLAYER;

    return player->stateFlags2 & 8;
}

void func_800B7170(GlobalContext* globalCtx, Player* player) {
    if ((globalCtx->roomCtx.currRoom.unk3 != 4) && (player->actor.id == ACTOR_PLAYER)) {
        EnHorse* rideActor = (EnHorse*)player->rideActor;

        if ((rideActor != NULL) && !(rideActor->unk_1EC & 0x10)) {
            func_800DFAC8(Play_GetCamera(globalCtx, 0), 4);
        }
    }
}

void Actor_MountHorse(GlobalContext* globalCtx, Player* player, Actor* horse) {
    player->rideActor = horse;
    player->stateFlags1 |= 0x800000;
    horse->child = &player->actor;
}

s32 func_800B7200(Player* player) {
    return (player->stateFlags1 & 0x20000080) || (player->csMode != 0);
}

void func_800B722C(GlobalContext* globalCtx, Player* player) {
    func_800F40A0(globalCtx, player);
}

s32 func_800B724C(GlobalContext* globalCtx, Actor* actor, u8 csMode) {
    Player* player = PLAYER;

    if ((player->csMode == 5) || ((csMode == 6) && (player->csMode == 0))) {
        return false;
    }

    player->csMode = csMode;
    player->unk_398 = actor;
    player->unk_3BA = 0;
    return true;
}

u32 func_800B7298(GlobalContext* globalCtx, Actor* actor, u8 arg2) {
    Player* player = PLAYER;

    if (func_800B724C(globalCtx, actor, arg2)) {
        player->unk_3BA = 1;
        return true;
    }
    return false;
}

void func_800B72E0(DynaPolyActor* dyna) {
    dyna->unk14C = 0.0f;
    dyna->unk148 = 0.0f;
}

void func_800B72F8(DynaPolyActor* dyna, f32 a1, s16 a2) {
    dyna->unk150 = a2;
    dyna->unk148 += a1;
}

s32 Actor_IsPlayerFacingActor(Actor* actor, s16 tolerance, GlobalContext* globalCtx) {
    Player* player = PLAYER;
    s16 yawDiff = BINANG_ADD(actor->yawTowardsPlayer, 0x8000) - player->actor.shape.rot.y;

    if (ABS_ALT(yawDiff) < tolerance) {
        return true;
    }
    return false;
}

s32 Actor_IsActorFacedByActor(Actor* actor, Actor* other, s16 tolerance) {
    s16 angle = BINANG_ROT180(Actor_YawBetweenActors(actor, other));
    s16 dist;

    dist = angle - other->shape.rot.y;
    if (ABS_ALT(dist) < tolerance) {
        return true;
    }
    return false;
}

s32 Actor_IsActorFacingPlayer(Actor* actor, s16 angle) {
    s16 dist = actor->yawTowardsPlayer - actor->shape.rot.y;

    if (ABS_ALT(dist) < angle) {
        return true;
    }
    return false;
}

s32 Actor_IsActorFacingActor(Actor* actor, Actor* other, s16 tolerance) {
    s16 dist = Actor_YawBetweenActors(actor, other) - actor->shape.rot.y;

    if (ABS_ALT(dist) < tolerance) {
        return 1;
    }
    return 0;
}

s32 Actor_IsActorFacingPlayerAndWithinRange(Actor* actor, f32 range, s16 tolerance) {
    s16 yaw = actor->yawTowardsPlayer - actor->shape.rot.y;

    if (ABS_ALT(yaw) < tolerance) {
    label:;
        if (sqrtf(SQ(actor->xzDistToPlayer) + SQ(actor->yDistToPlayer)) < range) {
            return 1;
        }
    }
    return 0;
}

s32 Actor_IsActorFacingActorAndWithinRange(Actor* actor, Actor* other, f32 range, s16 tolerance) {
    s16 dist;

    if (Actor_DistanceBetweenActors(actor, other) < range) {
        dist = Actor_YawBetweenActors(actor, other) - actor->shape.rot.y;
        if (ABS_ALT(dist) < tolerance) {
            return 1;
        }
    }
    return 0;
}

void func_800B75A0(CollisionPoly* param_1, Vec3f* param_2, s16* param_3) {
    param_2->x = param_1->normal.x * (1.0f / 0x7FFF);
    param_2->y = param_1->normal.y * (1.0f / 0x7FFF);
    param_2->z = param_1->normal.z * (1.0f / 0x7FFF);
    *param_3 = Math_FAtan2F(param_2->z, param_2->x);
}

s32 func_800B761C(Actor* actor, f32 arg1, s32 arg2) {
    if (actor->bgCheckFlags & 0x01) {
        actor->bgCheckFlags &= ~0x01;
        actor->bgCheckFlags |= 0x04;
        if ((actor->velocity.y < 0.0f) && (arg2 & 0x10)) {
            actor->velocity.y = 0.0f;
        }
        return false;
    }
    return true;
}

s32 func_800B7678(GlobalContext* globalCtx, Actor* actor, Vec3f* arg2, s32 arg3) {
    f32 temp_f0;
    s32 sp38;

    arg2->y += (arg3 & 0x800) ? 10.0f : 50.0f;

    actor->floorHeight = func_800C4188(globalCtx, &globalCtx->colCtx, &actor->floorPoly, &sp38, actor, arg2);
    actor->bgCheckFlags &= ~(0x80 | 0x04 | 0x02);
    if (actor->floorHeight <= BGCHECK_Y_MIN) {
        return func_800B761C(actor, BGCHECK_Y_MIN, arg3);
    }

    temp_f0 = actor->floorHeight - actor->world.pos.y;
    actor->floorBgId = sp38;
    if ((temp_f0 >= 0.0f) || (((actor->bgCheckFlags & 1)) && !(actor->bgCheckFlags & 0x800) && (temp_f0 >= -11.0f) &&
                              (actor->velocity.y < 0.0f))) {
        actor->bgCheckFlags |= 0x80;

        if (actor->bgCheckFlags & 0x10) {
            if (sp38 != D_801ED8B4) {
                if (temp_f0 > 15.0f) {
                    actor->bgCheckFlags |= 0x100;
                }
            } else {
                actor->world.pos.x = actor->prevPos.x;
                actor->world.pos.z = actor->prevPos.z;
            }
        }
        actor->world.pos.y = actor->floorHeight;
        if (actor->velocity.y <= 0.0f) {
            if (!(actor->bgCheckFlags & 1)) {
                actor->bgCheckFlags |= 0x02;
            } else if ((arg3 & 8) && (actor->gravity < 0.0f)) {
                actor->velocity.y = -4.0f;
            } else if (!(arg3 & 0x100)) {
                actor->velocity.y = 0.0f;
            }

            actor->bgCheckFlags |= 0x01;
            BgCheck2_AttachToMesh(&globalCtx->colCtx, actor, (s32)actor->floorBgId);
        }
    } else {
        return func_800B761C(actor, temp_f0, arg3);
    }

    return 1;
}

void Actor_UpdateBgCheckInfo(GlobalContext* globalCtx, Actor* actor, f32 wallCheckHeight, f32 wallCheckRadius,
                             f32 ceilingCheckHeight, u32 flags) {
    f32 sp94;
    s32 pad;
    Vec3f sp84;

    sp94 = actor->world.pos.y - actor->prevPos.y;
    if ((actor->floorBgId != 0x32) && (actor->bgCheckFlags & 1)) {
        BgCheck2_UpdateActorAttachedToMesh(&globalCtx->colCtx, actor->floorBgId, actor);
    }

    if (flags & 1) {
        s32 sp80;

        actor->bgCheckFlags &= ~0x1000;
        if ((!(flags & 0x80) &&
             ((func_800C4D3C(&globalCtx->colCtx, &sp84, &actor->world.pos, &actor->prevPos, wallCheckRadius,
                             &actor->wallPoly, &sp80, actor, wallCheckHeight) != 0))) ||
            ((flags & 0x80) &&
             ((func_800C4DA4(&globalCtx->colCtx, &sp84, &actor->world.pos, &actor->prevPos, wallCheckRadius,
                             &actor->wallPoly, &sp80, actor, wallCheckHeight) != 0)))) {
            CollisionPoly* sp7C = actor->wallPoly;

            actor->bgCheckFlags |= 0x08;
            if ((flags & 0x200) && ((actor->bgCheckFlags & 0x1000) != 0) && ((s32)sp7C->normal.y > 0) &&
                ((sqrtf(SQ(actor->colChkInfo.displacement.x) + SQ(actor->colChkInfo.displacement.y) +
                        SQ(actor->colChkInfo.displacement.z)) < 10.0f))) {
                actor->bgCheckFlags &= ~0x08;
            } else if (actor->bgCheckFlags & 0x08) {
                Math_Vec3f_Copy(&actor->world.pos, &sp84);
            }

            actor->wallYaw = Math_FAtan2F(sp7C->normal.z, sp7C->normal.x);
            actor->wallBgId = sp80;
        } else {
            actor->bgCheckFlags &= ~0x08;
        }
    }

    sp84.x = actor->world.pos.x;
    sp84.z = actor->world.pos.z;
    if (flags & 2) {
        f32 sp78;

        sp84.y = actor->prevPos.y + 4.0f;
        if (func_800C4F84(&globalCtx->colCtx, &sp78, &sp84, (ceilingCheckHeight + sp94) - 4.0f, &D_801ED8B0,
                          &D_801ED8B4, actor) != 0) {
            actor->bgCheckFlags |= 0x10;
            actor->world.pos.y = (sp78 + sp94) - 4.0f;
        } else {
            actor->bgCheckFlags &= ~0x10;
        }
    }
    if (flags & 4) {
        WaterBox* sp74;
        f32 sp70;

        sp84.y = actor->prevPos.y;
        func_800B7678(globalCtx, actor, &sp84, flags);
        sp70 = actor->world.pos.y;
        if (func_800CA1AC(globalCtx, &globalCtx->colCtx, actor->world.pos.x, actor->world.pos.z, &sp70, &sp74) != 0) {
            actor->yDistToWater = sp70 - actor->world.pos.y;
            if (actor->yDistToWater <= 0.0f) {
                actor->bgCheckFlags &= ~(0x40 | 0x20);
            } else if ((actor->bgCheckFlags & 0x20) == 0) {
                actor->bgCheckFlags |= (0x40 | 0x20);
                if ((flags & 0x40) == 0) {
                    Vec3f sp64;

                    sp64.x = actor->world.pos.x;
                    sp64.y = sp70;
                    sp64.z = actor->world.pos.z;
                    EffectSsGRipple_Spawn(globalCtx, &sp64, 100, 500, 0);
                    EffectSsGRipple_Spawn(globalCtx, &sp64, 100, 500, 4);
                    EffectSsGRipple_Spawn(globalCtx, &sp64, 100, 500, 8);
                }
            } else {
                actor->bgCheckFlags &= ~0x40;
            }
        } else {
            actor->bgCheckFlags &= ~(0x40 | 0x20);
            actor->yDistToWater = BGCHECK_Y_MIN;
        }
    }

    if (flags & 0x400) {
        WaterBox* sp60;
        f32 sp5C = actor->world.pos.y;

        if (func_800CA1AC(globalCtx, &globalCtx->colCtx, actor->world.pos.x, actor->world.pos.z, &sp5C, &sp60) != 0) {
            actor->yDistToWater = sp5C - actor->world.pos.y;
            if (actor->yDistToWater < 0.0f) {
                actor->bgCheckFlags &= ~(0x40 | 0x20);
            } else if (!(actor->bgCheckFlags & 0x20)) {
                actor->bgCheckFlags |= (0x40 | 0x20);
                if (!(flags & 0x40)) {
                    Vec3f sp50;

                    sp50.x = actor->world.pos.x;
                    sp50.y = sp5C;
                    sp50.z = actor->world.pos.z;
                    EffectSsGRipple_Spawn(globalCtx, &sp50, 100, 500, 0);
                    EffectSsGRipple_Spawn(globalCtx, &sp50, 100, 500, 4);
                    EffectSsGRipple_Spawn(globalCtx, &sp50, 100, 500, 8);
                }
            } else {
                actor->bgCheckFlags &= ~0x40;
            }
        } else {
            actor->bgCheckFlags &= ~(0x40 | 0x20);
            actor->yDistToWater = BGCHECK_Y_MIN;
        }
    }
}

#pragma GLOBAL_ASM("asm/non_matchings/code/z_actor/func_800B7E04.s")

Hilite* func_800B7FE0(Vec3f* object, Vec3f* eye, Vec3f* lightDir, GraphicsContext* gfxCtx) {
    Hilite* sp2C;

    OPEN_DISPS(gfxCtx);

    POLY_OPA_DISP = func_800B7E04(object, eye, lightDir, gfxCtx, POLY_OPA_DISP, &sp2C);

    CLOSE_DISPS(gfxCtx);

    return sp2C;
}

Hilite* func_800B8018(Vec3f* object, Vec3f* eye, Vec3f* lightDir, GraphicsContext* gfxCtx) {
    Hilite* sp2C;

    OPEN_DISPS(gfxCtx);

    POLY_XLU_DISP = func_800B7E04(object, eye, lightDir, gfxCtx, POLY_XLU_DISP, &sp2C);

    CLOSE_DISPS(gfxCtx);

    return sp2C;
}

#pragma GLOBAL_ASM("asm/non_matchings/code/z_actor/func_800B8050.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_actor/func_800B8118.s")

PosRot* Actor_GetFocus(PosRot* dest, Actor* actor) {
    *dest = actor->focus;

    return dest;
}

PosRot* Actor_GetWorld(PosRot* dest, Actor* actor) {
    *dest = actor->world;

    return dest;
}

PosRot* Actor_GetWorldPosShapeRot(PosRot* dest, Actor* actor) {
    PosRot sp1C;

    Math_Vec3f_Copy(&sp1C.pos, &actor->world.pos);
    if (actor->id == ACTOR_PLAYER) {
        Player* player = (Player*)actor;

        sp1C.pos.y += player->unk_AC0 * actor->scale.y;
    }
    sp1C.rot = actor->shape.rot;
    *dest = sp1C;

    return dest;
}

#pragma GLOBAL_ASM("asm/non_matchings/code/z_actor/func_800B82EC.s")

TargetRangeParams D_801AECF0[] = {
    TARGET_RANGE(70, 140),   TARGET_RANGE(170, 255),    TARGET_RANGE(280, 5600),      TARGET_RANGE(350, 525),
    TARGET_RANGE(700, 1050), TARGET_RANGE(1000, 1500),  TARGET_RANGE(100, 105.36842), TARGET_RANGE(140, 163.33333),
    TARGET_RANGE(240, 576),  TARGET_RANGE(280, 280000), TARGET_RANGE(2500, 3750),
};

s32 func_800B83BC(Actor* actor, f32 arg1) {
    return arg1 < D_801AECF0[actor->targetMode].rangeSq;
}

s32 func_800B83F8(Actor* actor, Player* player, s32 flag) {
    if ((actor->update == NULL) || !(actor->flags & 1) || (actor->flags & 0x8000000)) {
        return 1;
    }

    if (!flag) {
        s16 yaw = BINANG_SUB(actor->yawTowardsPlayer, 0x8000) - player->actor.shape.rot.y;
        s16 phi_v1 = ABS_ALT(yaw);
        f32 dist;

        if ((player->unk_730 == NULL) && (phi_v1 >= 0x2AAB)) {
            dist = FLT_MAX;
        } else {
            dist = actor->xyzDistToPlayerSq;
        }

        return !func_800B83BC(actor, D_801AECF0[actor->targetMode].leashScale * dist);
    }
    return 0;
}

s16 D_801AED48[] = {
    0x0101, 0x0141, 0x0111, 0x0151, 0x0105, 0x0145, 0x0115, 0x0155,
};

s32 Actor_IsTalking(Actor* actor, GlobalContext* globalCtx) {
    if (actor->flags & 0x100) {
        actor->flags &= ~0x100;
        return true;
    }

    return false;
}

#pragma GLOBAL_ASM("asm/non_matchings/code/z_actor/func_800B8500.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_actor/func_800B85E0.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_actor/func_800B8614.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_actor/func_800B863C.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_actor/func_800B867C.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_actor/func_800B86C8.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_actor/func_800B8708.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_actor/func_800B8718.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_actor/func_800B874C.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_actor/func_800B8804.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_actor/func_800B882C.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_actor/func_800B886C.s")

void func_800B8898(GlobalContext* globalCtx, Actor* actor, s16* arg2, s16* arg3) {
    Vec3f sp1C;
    f32 sp18;

    func_800B4EDC(globalCtx, &actor->focus.pos, &sp1C, &sp18);
    *arg2 = (sp1C.x * sp18 * 160.0f) + 160.0f;
    *arg3 = (sp1C.y * sp18 * -120.0f) + 120.0f;
}

s32 func_800B8934(GlobalContext* globalCtx, Actor* actor) {
    Vec3f sp2C;
    f32 sp28;
    s32 pad[2];

    func_800B4EDC(globalCtx, &actor->focus.pos, &sp2C, &sp28);

    return (sp2C.x * sp28 >= -1.0f) && (sp2C.x * sp28 <= 1.0f) && (sp2C.y * sp28 >= -1.0f) && (sp2C.y * sp28 <= 1.0f);
}

u32 Actor_HasParent(Actor* actor, GlobalContext* globalCtx) {
    if (actor->parent != NULL) {
        return true;
    } else {
        return false;
    }
}

// Actor_PickUp
s32 func_800B8A1C(Actor* actor, GlobalContext* globalCtx, s32 getItemId, f32 xzRange, f32 yRange) {
    Player* player = PLAYER;

    if (!(player->stateFlags1 & 0x3C7080) && Player_GetExplosiveHeld(player) < 0) {
        if ((actor->xzDistToPlayer <= xzRange) && (fabsf(actor->yDistToPlayer) <= fabsf(yRange))) {
            if ((getItemId == GI_MASK_CIRCUS_LEADER || getItemId == GI_PENDANT_OF_MEMORIES ||
                 getItemId == GI_LAND_TITLE_DEED ||
                 (((player->heldActor != NULL) || (actor == player->targetActor)) &&
                  (getItemId > GI_NONE && getItemId < GI_MAX))) ||
                (!(player->stateFlags1 & 0x20000800))) {
                s16 yawDiff = actor->yawTowardsPlayer - player->actor.shape.rot.y;
                s32 absYawDiff = ABS_ALT(yawDiff);

                if ((getItemId != GI_NONE) || (player->getItemDirection < absYawDiff)) {
                    player->getItemId = getItemId;
                    player->interactRangeActor = actor;
                    player->getItemDirection = absYawDiff;

                    if (getItemId > GI_NONE && getItemId < GI_MAX) {
                        ActorCutscene_SetIntentToPlay(globalCtx->unk_1879C[1]);
                    }

                    return true;
                }
            }
        }
    }

    return false;
}

// Actor_PickUpNearby
s32 func_800B8B84(Actor* actor, GlobalContext* globalCtx, s32 getItemId) {
    return func_800B8A1C(actor, globalCtx, getItemId, 50.0f, 10.0f);
}

// Actor_HoldActor?
s32 func_800B8BB0(Actor* actor, GlobalContext* globalCtx) {
    return func_800B8B84(actor, globalCtx, GI_NONE);
}

// Actor_PickUpFar?
s32 func_800B8BD0(Actor* actor, GlobalContext* globalCtx, s32 getItemId) {
    return func_800B8A1C(actor, globalCtx, getItemId, 9999.9f, 9999.9f);
}

s32 Actor_HasNoParent(Actor* actor, GlobalContext* globalCtx) {
    if (!actor->parent) {
        return true;
    } else {
        return false;
    }
}

void func_800B8C20(Actor* actorA, Actor* actorB, GlobalContext* globalCtx) {
    Actor* parent = actorA->parent;

    if (parent->id == ACTOR_PLAYER) {
        Player* player = (Player*)parent;

        player->heldActor = actorB;
        player->interactRangeActor = actorB;
    }

    parent->child = actorB;
    actorB->parent = parent;
    actorA->parent = NULL;
}

void func_800B8C50(Actor* actor, GlobalContext* globalCtx) {
    Player* player = PLAYER;

    if (actor->xyzDistToPlayerSq < player->unk_AA0) {
        player->unk_AA0 = actor->xyzDistToPlayerSq;
    }
}

s32 Actor_IsMounted(GlobalContext* globalCtx, Actor* horse) {
    if (horse->child != NULL) {
        return true;
    }
    return false;
}

s32 Actor_SetRideActor(GlobalContext* globalCtx, Actor* horse, s32 mountSide) {
    Player* player = PLAYER;

    if (!(player->stateFlags1 & 0x003C7880)) {
        player->rideActor = horse;
        player->mountSide = mountSide;
        ActorCutscene_SetIntentToPlay(0x7C);
        return true;
    }

    return false;
}

s32 Actor_NotMounted(GlobalContext* globalCtx, Actor* horse) {
    if (horse->child == NULL) {
        return true;
    }

    return false;
}

void func_800B8D10(GlobalContext* globalCtx, Actor* actor, f32 arg2, s16 arg3, f32 arg4, u32 arg5, u32 arg6) {
    Player* player = PLAYER;

    player->unk_B74 = arg6;
    player->unk_B75 = arg5;
    player->unk_B78 = arg2;
    player->unk_B76 = arg3;
    player->unk_B7C = arg4;
}

void func_800B8D50(GlobalContext* globalCtx, Actor* actor, f32 arg2, s16 yaw, f32 arg4, u32 arg5) {
    func_800B8D10(globalCtx, actor, arg2, yaw, arg4, 3, arg5);
}

void func_800B8D98(GlobalContext* globalCtx, Actor* actor, f32 arg2, s16 arg3, f32 arg4) {
    func_800B8D50(globalCtx, actor, arg2, arg3, arg4, 0);
}

void func_800B8DD4(GlobalContext* globalCtx, Actor* actor, f32 arg2, s16 arg3, f32 arg4, u32 arg5) {
    func_800B8D10(globalCtx, actor, arg2, arg3, arg4, 2, arg5);
}

void func_800B8E1C(GlobalContext* globalCtx, Actor* actor, f32 arg2, s16 arg3, f32 arg4) {
    func_800B8DD4(globalCtx, actor, arg2, arg3, arg4, 0);
}

#if 0
// The OoT version of this function (func_8002F7DC) takes Actor*, but there's a high chance it takes Player* here
void func_800B8E58(Actor* actor, u16 sfxId) {
    if (actor->unk_153 == 0x14) {
        func_8019F170(&actor->projectedPos, sfxId);
        return;
    }
    func_801A5CFC(sfxId, &actor->projectedPos, 4, &D_801DB4B0, &D_801DB4B0, &D_801DB4B8);
}
#else
#pragma GLOBAL_ASM("asm/non_matchings/code/z_actor/func_800B8E58.s")
#endif

void Audio_PlayActorSound2(Actor* actor, u16 sfxId) {
    func_8019F1C0(&actor->projectedPos, sfxId);
}

void func_800B8EF4(GlobalContext* globalCtx, Actor* actor) {
    u32 sp1C;

    if (actor->bgCheckFlags & 0x20) {
        if (actor->yDistToWater < 20.0f) {
            sp1C = NA_SE_PL_WALK_WATER0 - SFX_FLAG;
        } else {
            sp1C = NA_SE_PL_WALK_WATER1 - SFX_FLAG;
        }
    } else {
        sp1C = func_800C9BDC(&globalCtx->colCtx, actor->floorPoly, actor->floorBgId);
    }

    func_8019F1C0(&actor->projectedPos, NA_SE_EV_BOMB_BOUND);
    func_8019F1C0(&actor->projectedPos, sp1C + SFX_FLAG);
}

void func_800B8F98(Actor* actor, u16 sfxId) {
    actor->sfx = sfxId;
    actor->unk39 &= ~(0x10 | 0x08 | 0x04 | 0x02 | 0x01);
    actor->unk39 |= 0x02;
}

void func_800B8FC0(Actor* actor, u16 sfxId) {
    actor->sfx = sfxId;
    actor->unk39 &= ~(0x10 | 0x08 | 0x04 | 0x02 | 0x01);
    actor->unk39 |= 4;
}

void func_800B8FE8(Actor* actor, u16 sfxId) {
    actor->sfx = sfxId;
    actor->unk39 &= ~(0x10 | 0x08 | 0x04 | 0x02 | 0x01);
    actor->unk39 |= 0x08;
}

void func_800B9010(Actor* actor, u16 sfxId) {
    actor->sfx = sfxId;
    actor->unk39 &= ~(0x10 | 0x08 | 0x04 | 0x02 | 0x01);
    actor->unk39 |= 0x01;
}

void func_800B9038(Actor* actor, s32 arg1) {
    actor->unk39 &= ~(0x10 | 0x08 | 0x04 | 0x02 | 0x01);
    actor->unk39 |= 0x10;

    if (arg1 < 40) {
        actor->sfx = 3;
    } else if (arg1 < 100) {
        actor->sfx = 2;
    } else {
        actor->sfx = 1;
    }
}

void func_800B9084(Actor* actor) {
    actor->unk39 |= 0x20;
}

void func_800B9098(Actor* actor) {
    actor->unk39 |= 0x40;
}

s32 func_800B90AC(GlobalContext* globalCtx, Actor* actor, CollisionPoly* polygon, s32 index, s32 arg4) {
    if (func_800C99D4(&globalCtx->colCtx, polygon, index) == 8) {
        return 1;
    }
    return 0;
}

void func_800B90F4(GlobalContext* globalCtx) {
    if (globalCtx->actorCtx.unk3 != 0) {
        globalCtx->actorCtx.unk3 = 0;
        func_80115D5C(globalCtx);
    }
}

void func_800B9120(ActorContext* actorCtx) {
    s32 phi_v0 = CURRENT_DAY * 2;

    if (gSaveContext.time < CLOCK_TIME(6, 0) || gSaveContext.time > CLOCK_TIME(18, 0)) {
        phi_v0++;
    }
    actorCtx->unkC = (0x200 >> phi_v0);
}

// Actor_InitContext // OoT's func_800304DC
#pragma GLOBAL_ASM("asm/non_matchings/code/z_actor/func_800b9170.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_actor/func_800B9334.s")

#ifdef NON_EQUIVALENT
Actor* Actor_UpdateActor(s800B948C* params) {
    GlobalContext* sp24;
    Actor* temp_s0;
    u32 temp_v1;
    Actor* phi_v1;

    temp_s0 = params->actor;
    sp24 = params->globalCtx;
    if (temp_s0->world.pos.y < -25000.0f) {
        temp_s0->world.pos.y = -25000.0f;
    }
    temp_s0->sfx = 0;
    temp_s0->unk39 &= 0xFF80;
    if (temp_s0->init != 0) {
        if (Object_IsLoaded(&sp24->objectCtx, (s32)temp_s0->objBankIndex) != 0) {
            Actor_SetObjectDependency(sp24, temp_s0);
            temp_s0->init(temp_s0, sp24);
            temp_s0->init = NULL;
        }
        // goto block_38;
        return temp_s0->next;
    } else if (temp_s0->update == 0) {
        if (temp_s0->isDrawn == 0) {
            phi_v1 = Actor_Delete(&sp24->actorCtx, temp_s0, sp24);
        } else {
            Actor_Destroy(temp_s0, sp24);
            // goto block_38;
            return temp_s0->next;
        }
    } else {
        if (Object_IsLoaded(&sp24->objectCtx, (s32)temp_s0->objBankIndex) == 0) {
            Actor_MarkForDeath(temp_s0);
            return temp_s0->next;
        } else {
            if (((params->updateActorIfSet != 0) && ((temp_s0->flags & params->updateActorIfSet) == 0)) ||
                ((params->updateActorIfSet != 0) &&
                 (!(temp_s0->flags & 0x100000) ||
                  ((temp_s0->category == 3) && ((params->player->stateFlags1 & 0x200) != 0))) &&
                 (params->unkC != 0) && (temp_s0 != params->unk10) && ((temp_s0 != params->player->heldActor)) &&
                 (&params->player->actor != temp_s0->parent))) {
                CollisionCheck_ResetDamage(&temp_s0->colChkInfo);
            } else {
                s32 phi_v0;

                Math_Vec3f_Copy(&temp_s0->prevPos, (Vec3f*)&temp_s0->world);
                temp_s0->xzDistToPlayer = Actor_XZDistanceBetweenActors(temp_s0, (Actor*)params->player);
                temp_s0->yDistToPlayer = Actor_HeightDiff(temp_s0, (Actor*)params->player);
                temp_s0->xyzDistToPlayerSq = SQ(temp_s0->xzDistToPlayer) + SQ(temp_s0->yDistToPlayer);

                temp_s0->yawTowardsPlayer = Actor_YawBetweenActors(temp_s0, (Actor*)params->player);
                temp_s0->flags &= 0xFEFFFFFF;

                if (temp_s0->freezeTimer == 0) {
                    phi_v0 = 0;
                } else {
                    temp_s0->freezeTimer--;
                    phi_v0 = temp_s0->freezeTimer & 0xFFFF;
                }

                if ((phi_v0 == 0) && ((temp_s0->flags & params->runMainIfSet) != 0)) {
                    if (temp_s0 == params->player->unk_730) {
                        temp_s0->isTargeted = 1;
                    } else {
                        temp_s0->isTargeted = 0;
                    }
                    if ((temp_s0->targetPriority != 0) && (params->player->unk_730 == 0)) {
                        temp_s0->targetPriority = 0;
                    }
                    Actor_SetObjectDependency(sp24, temp_s0);

                    if (temp_s0->colorFilterTimer != 0) {
                        temp_s0->colorFilterTimer--;
                    }
                    temp_s0->update(temp_s0, sp24);
                    BgCheck_ResetFlagsIfLoadedActor(sp24, &sp24->colCtx.dyna, temp_s0);
                }
                CollisionCheck_ResetDamage(&temp_s0->colChkInfo);
            }
        }
        // block_38:
        phi_v1 = temp_s0->next;
    }
    return phi_v1;
}
#else
#pragma GLOBAL_ASM("asm/non_matchings/code/z_actor/Actor_UpdateActor.s")
#endif

s32 D_801AED58[] = {
    0x100002C2, 0x100002C2, 0x00000200, 0x100006C2, 0x00000282, 0x300002C2,
    0x10000282, 0x00000002, 0x300002C2, 0x100006C2, 0x00000002, 0x100002C2,
};

#ifdef NON_EQUIVALENT
void Actor_UpdateAll(GlobalContext* globalCtx, ActorContext* actorCtx) {
    s800B948C sp40;
    ActorListEntry* sp3C;
    DynaCollisionContext* sp38;
    s32 phi_s3;
    u8 phi_s3_2;
    Actor* phi_s0_3;

    sp40.player = PLAYER;
    sp40.globalCtx = globalCtx;

    if (globalCtx->unk_18844 != 0) {
        sp40.runMainIfSet = 0x200000;
    } else {
        sp40.runMainIfSet = 0x200050;
    }

    func_800B9334(globalCtx, actorCtx);

    if (actorCtx->unk2 != 0) {
        actorCtx->unk2--;
    }

    if (sp40.player->stateFlags2 & 0x8000000) {
        sp40.updateActorIfSet = 0x2000000;
    } else {
        sp40.updateActorIfSet = 0;
    }
    if (((sp40.player->stateFlags1 & 0x40) != 0) && ((sp40.player->actor.textId & 0xFF00) != 0x1900)) {
        sp40.unk10 = sp40.player->targetActor;
    } else {
        sp40.unk10 = 0;
    }

    sp38 = &globalCtx->colCtx.dyna;
    for (phi_s3 = 0; phi_s3 < ARRAY_COUNT(actorCtx->actorList); phi_s3++) {
        sp40.unkC = D_801AED58[phi_s3] & sp40.player->stateFlags1;
        sp40.actor = actorCtx->actorList[phi_s3].first;
        while (sp40.actor != 0) {
            sp40.actor = Actor_UpdateActor(&sp40);
        }
        if (phi_s3 == 1) {
            BgCheck_Update(globalCtx, sp38);
        }
    }

    for (phi_s3_2 = 0; phi_s3_2 != 0xC; phi_s3_2++) {
        if (sp3C->unk_08 != 0) {
            Actor* phi_s0;

            phi_s0 = sp3C->first;
            if (phi_s0 != 0) {
                Actor* phi_s0_2;

                do {
                    u8 temp_v0_3;

                    temp_v0_3 = phi_s0->category;
                    if (phi_s3_2 == temp_v0_3) {
                        phi_s0_2 = phi_s0->next;
                    } else {
                        phi_s0_2 = phi_s0->next;
                        phi_s0->category = phi_s3_2;
                        Actor_RemoveFromTypeList(globalCtx, actorCtx, phi_s0);
                        Actor_InsertIntoTypeList(actorCtx, phi_s0, temp_v0_3);
                    }
                    phi_s0 = phi_s0_2;
                } while (phi_s0_2 != 0);
            }
            sp3C->unk_08 = 0;
        }
        sp3C++;
    }

    phi_s0_3 = sp40.player->unk_730;
    if ((phi_s0_3 != 0) && (phi_s0_3->update == 0)) {
        func_80123DA4(sp40.player);
        phi_s0_3 = NULL;
    }

    if ((phi_s0_3 == 0) || (sp40.player->unk_738 < 5)) {
        phi_s0_3 = NULL;
        if (actorCtx->targetContext.unk4B != 0) {
            actorCtx->targetContext.unk4B = 0;
            play_sound(NA_SE_SY_LOCK_OFF);
        }
    }

    if ((sp40.player->stateFlags1 & 2) == 0) {
        func_800B5814(&actorCtx->targetContext, sp40.player, phi_s0_3, globalCtx);
    }

    TitleCard_Update(globalCtx, &actorCtx->titleCtxt);
    func_800B6474(globalCtx);
    BgCheck_UpdateAllActorMeshes(globalCtx, sp38);
}
#else
#pragma GLOBAL_ASM("asm/non_matchings/code/z_actor/Actor_UpdateAll.s")
#endif

void Actor_Draw(GlobalContext* globalCtx, Actor* actor) {
    Lights* sp44;

    OPEN_DISPS(globalCtx->state.gfxCtx);

    sp44 = LightContext_NewLights(&globalCtx->lightCtx, globalCtx->state.gfxCtx);
    if ((actor->flags & 0x10000000) && (globalCtx->roomCtx.currRoom.enablePosLights || (MREG(93) != 0))) {
        sp44->enablePosLights = true;
    }

    Lights_BindAll(sp44, globalCtx->lightCtx.listHead, (actor->flags & 0x10400000) ? NULL : &actor->world.pos,
                   globalCtx);
    Lights_Draw(sp44, globalCtx->state.gfxCtx);

    if (actor->flags & 0x1000) {
        SysMatrix_SetStateRotationAndTranslation(
            actor->world.pos.x + globalCtx->mainCamera.skyboxOffset.x,
            actor->world.pos.y + ((actor->shape.yOffset * actor->scale.y) + globalCtx->mainCamera.skyboxOffset.y),
            actor->world.pos.z + globalCtx->mainCamera.skyboxOffset.z, &actor->shape.rot);
    } else {
        SysMatrix_SetStateRotationAndTranslation(actor->world.pos.x,
                                                 actor->world.pos.y + (actor->shape.yOffset * actor->scale.y),
                                                 actor->world.pos.z, &actor->shape.rot);
    }

    Matrix_Scale(actor->scale.x, actor->scale.y, actor->scale.z, MTXMODE_APPLY);
    Actor_SetObjectDependency(globalCtx, actor);

    gSPSegment(POLY_OPA_DISP++, 0x06, globalCtx->objectCtx.status[actor->objBankIndex].segment);
    gSPSegment(POLY_XLU_DISP++, 0x06, globalCtx->objectCtx.status[actor->objBankIndex].segment);

    if (actor->colorFilterTimer != 0) {
        s32 temp_v0_2 = actor->colorFilterParams & 0xC000;
        Color_RGBA8 actorDefaultHitColor = { 0, 0, 0, 255 };

        if (temp_v0_2 == 0x8000) {
            actorDefaultHitColor.r = actorDefaultHitColor.g = actorDefaultHitColor.b =
                ((actor->colorFilterParams & 0x1F00) >> 5) | 7;
        } else if (temp_v0_2 == 0x4000) {
            actorDefaultHitColor.r = ((actor->colorFilterParams & 0x1F00) >> 5) | 7;
        } else if (temp_v0_2 == 0xC000) {
            actorDefaultHitColor.b = actorDefaultHitColor.g = actorDefaultHitColor.r = 0;
        } else {
            actorDefaultHitColor.b = ((actor->colorFilterParams & 0x1F00) >> 5) | 7;
        }

        if (actor->colorFilterParams & 0x2000) {
            func_800AE778(globalCtx, &actorDefaultHitColor, actor->colorFilterTimer, actor->colorFilterParams & 0xFF);
        } else {
            func_800AE434(globalCtx, &actorDefaultHitColor, actor->colorFilterTimer, actor->colorFilterParams & 0xFF);
        }
    }

    actor->draw(actor, globalCtx);
    if (actor->colorFilterTimer != 0) {
        if (actor->colorFilterParams & 0x2000) {
            func_800AE8EC(globalCtx);
        } else {
            func_800AE5A0(globalCtx);
        }
    }

    if (actor->shape.shadowDraw != NULL) {
        actor->shape.shadowDraw(actor, sp44, globalCtx);
    }
    actor->isDrawn = true;

    CLOSE_DISPS(globalCtx->state.gfxCtx);
}

#pragma GLOBAL_ASM("asm/non_matchings/code/z_actor/func_800B9D1C.s")

void Actor_DrawAllSetup(GlobalContext* globalCtx) {
    globalCtx->actorCtx.undrawnActorCount = 0;
    globalCtx->actorCtx.unkB = 0;
}

#pragma GLOBAL_ASM("asm/non_matchings/code/z_actor/Actor_RecordUndrawnActor.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_actor/func_800B9E84.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_actor/func_800B9EF4.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_actor/func_800BA2D8.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_actor/func_800BA2FC.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_actor/Actor_DrawAll.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_actor/func_800BA6FC.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_actor/func_800BA798.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_actor/func_800BA8B8.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_actor/func_800BA9B4.s")

void Actor_InsertIntoTypeList(ActorContext* actorCtx, Actor* actor, u8 actorCategory) {
    Actor* phi_v0;
    Actor* phi_v1;

    actor->category = actorCategory;

    actorCtx->totalLoadedActors++;
    actorCtx->actorList[actorCategory].length++;
    phi_v1 = actorCtx->actorList[actorCategory].first;
    if (phi_v1 == NULL) {
        actorCtx->actorList[actorCategory].first = actor;
        return;
    }

    phi_v0 = phi_v1->next;
    while (phi_v0 != NULL) {
        phi_v1 = phi_v0;
        phi_v0 = phi_v0->next;
    }

    phi_v1->next = actor;
    actor->prev = phi_v1;
}

// Actor_RemoveFromCategory
#pragma GLOBAL_ASM("asm/non_matchings/code/z_actor/Actor_RemoveFromTypeList.s")

void Actor_FreeOverlay(ActorOverlay* entry) {
    void* ramAddr;

    if (entry->numLoaded == 0) {
        ramAddr = entry->loadedRamAddr;
        if (ramAddr != NULL) {
            // Bit 1 - always loaded
            if ((entry->allocType & 2) == 0) {
                // Bit 0 - don't alloc memory
                if ((entry->allocType & 1) != 0) {
                    entry->loadedRamAddr = NULL;
                } else {
                    zelda_free(ramAddr);
                    entry->loadedRamAddr = NULL;
                }
            }
        }
    }
}

Actor* Actor_Spawn(ActorContext* actorCtx, GlobalContext* globalCtx, s16 actorId, f32 posX, f32 posY, f32 posZ,
                   s16 rotX, s16 rotY, s16 rotZ, s32 params) {
    return Actor_SpawnAsChildAndCutscene(actorCtx, globalCtx, actorId, posX, posY, posZ, rotX, rotY, rotZ, params, -1,
                                         0x3FF, NULL);
}

#pragma GLOBAL_ASM("asm/non_matchings/code/z_actor/Actor_LoadOverlay.s")

#ifdef NON_MATCHING
Actor* Actor_SpawnAsChildAndCutscene(ActorContext* actorCtx, GlobalContext* globalCtx, s16 index, f32 x, f32 y, f32 z,
                                     s16 rotX, s16 rotY, s16 rotZ, s32 params, u32 cutscene, s32 param_12,
                                     Actor* parent) {
    s32 pad;
    Actor* actor;
    ActorInit* sp2C; // actorInit
    s32 sp28;        // objBankIndex
    // s32 pad2;
    u32 sp20;           // segmentAux
    ActorOverlay* sp1C; // overlayEntry

    if (actorCtx->totalLoadedActors >= 0xFF) {
        return NULL;
    }

    sp2C = Actor_LoadOverlay(actorCtx, index);
    if (sp2C == NULL) {
        return NULL;
    }

    sp28 = Object_GetIndex(&globalCtx->objectCtx, sp2C->objectId);
    if ((sp28 < 0) ||
        ((sp2C->type == ACTORCAT_ENEMY) && ((Actor_GetRoomCleared(globalCtx, globalCtx->roomCtx.currRoom.num) != 0)) &&
         (sp2C->id != ACTOR_BOSS_05))) {
        Actor_FreeOverlay(&gActorOverlayTable[index]);
        return NULL;
    }

    actor = zelda_malloc(sp2C->instanceSize);
    if (actor == NULL) {
        Actor_FreeOverlay(&gActorOverlayTable[index]);
        return NULL;
    }

    sp1C = &gActorOverlayTable[index];
    if (sp1C->vramStart != 0) {
        sp1C->numLoaded++;
    }

    bzero(actor, sp2C->instanceSize);
    actor->overlayEntry = sp1C;
    actor->id = sp2C->id;
    actor->flags = sp2C->flags;

    if (sp2C->id == ACTOR_EN_PART) {
        actor->objBankIndex = rotZ;
        rotZ = 0;
    } else {
        actor->objBankIndex = sp28;
    }

    actor->init = sp2C->init;
    actor->destroy = sp2C->destroy;
    actor->update = sp2C->update;
    actor->draw = sp2C->draw;

    if (parent != NULL) {
        actor->room = parent->room;
        actor->parent = parent;
        parent->child = actor;
    } else {
        actor->room = globalCtx->roomCtx.currRoom.num;
    }

    actor->home.pos.x = x;
    actor->home.pos.y = y;
    actor->home.pos.z = z;
    actor->home.rot.x = rotX;
    actor->home.rot.y = rotY;
    actor->home.rot.z = rotZ;
    actor->params = params & 0xFFFF;
    actor->cutscene = (cutscene & 0x7F);

    if (actor->cutscene == 0x7F) {
        actor->cutscene = -1;
    }

    if (param_12 != 0) {
        actor->unk20 = param_12;
    } else {
        actor->unk20 = 0x3FF;
    }

    Actor_InsertIntoTypeList(actorCtx, actor, sp2C->type);

    goto dummy_label_;
dummy_label_:;

    sp20 = gSegments[6];
    Actor_Init(actor, globalCtx);
    gSegments[6] = sp20;

    //    goto dummy_label_47816;
    // dummy_label_47816:;

    return actor;
}
#else
#pragma GLOBAL_ASM("asm/non_matchings/code/z_actor/Actor_SpawnAsChildAndCutscene.s")
#endif

Actor* Actor_SpawnAsChild(ActorContext* actorCtx, Actor* parent, GlobalContext* globalCtx, s16 actorId, f32 posX,
                          f32 posY, f32 posZ, s16 rotX, s16 rotY, s16 rotZ, s32 params) {
    return Actor_SpawnAsChildAndCutscene(actorCtx, globalCtx, actorId, posX, posY, posZ, rotX, rotY, rotZ, params, -1,
                                         parent->unk20, parent);
}

#ifdef NON_MATCHING
void Actor_SpawnTransitionActors(GlobalContext* globalCtx, ActorContext* actorCtx) {
    TransitionActorEntry* phi_s0;
    s32 phi_s2;
    s16 phi_v1;

    phi_s0 = globalCtx->doorCtx.transitionActorList;
    phi_v1 = globalCtx->doorCtx.numTransitionActors;

    for (phi_s2 = 0; phi_s2 < phi_v1; phi_s2++) {
        if (phi_s0->id >= 0) {
            if ((phi_s0->sides[0].room >= 0 && (globalCtx->roomCtx.currRoom.num == phi_s0->sides[0].room ||
                                                globalCtx->roomCtx.prevRoom.num == phi_s0->sides[0].room)) ||
                (phi_s0->sides[1].room >= 0 && (globalCtx->roomCtx.currRoom.num == phi_s0->sides[1].room ||
                                                globalCtx->roomCtx.prevRoom.num == phi_s0->sides[1].room))) {
                s16 rotY = ((phi_s0->rotY >> 7) & 0x1FF) * 182.04445f;

                if (Actor_SpawnAsChildAndCutscene(
                        actorCtx, globalCtx, phi_s0->id & 0x1FFF, phi_s0->pos.x, phi_s0->pos.y, phi_s0->pos.z, 0, rotY,
                        0, (phi_s2 << 0xA) + (phi_s0->params & 0x3FF), phi_s0->pos.x & 0x7F, 0x3FF, 0) != NULL) {
                    phi_s0->id = -phi_s0->id;
                }
                phi_v1 = globalCtx->doorCtx.numTransitionActors;
            }
        }
        phi_s0 += 1;
    }
}
#else
#pragma GLOBAL_ASM("asm/non_matchings/code/z_actor/Actor_SpawnTransitionActors.s")
#endif

#pragma GLOBAL_ASM("asm/non_matchings/code/z_actor/func_800BB2D0.s")

Actor* Actor_Delete(ActorContext* actorCtx, Actor* actor, GlobalContext* globalCtx) {
    s32 pad;
    Player* player = PLAYER;
    Actor* newHead;
    ActorOverlay* overlayEntry = actor->overlayEntry;

    if ((player != NULL) && (actor == player->unk_730)) {
        func_80123DA4(player);
        Camera_ChangeMode(Play_GetCamera(globalCtx, Play_GetActiveCameraIndex(globalCtx)), 0);
    }

    if (actor == actorCtx->targetContext.unk38) {
        actorCtx->targetContext.unk38 = NULL;
    }

    if (actor == actorCtx->targetContext.unk8C) {
        actorCtx->targetContext.unk8C = NULL;
    }

    if (actor == actorCtx->targetContext.unk90) {
        actorCtx->targetContext.unk90 = NULL;
    }

    func_801A72CC(&actor->projectedPos);
    Actor_Destroy(actor, globalCtx);

    newHead = Actor_RemoveFromTypeList(globalCtx, actorCtx, actor);
    zelda_free(actor);

    if (overlayEntry->vramStart != 0) {
        overlayEntry->numLoaded--;
        Actor_FreeOverlay(overlayEntry);
    }

    return newHead;
}

s32 func_800BB59C(GlobalContext* globalCtx, Actor* actor) {
    s16 sp1E;
    s16 sp1C;

    func_800B8898(globalCtx, actor, &sp1E, &sp1C);

    return (sp1E > -20) && (sp1E < gScreenWidth + 20) && (sp1C > -160) && (sp1C < gScreenHeight + 160);
}

#pragma GLOBAL_ASM("asm/non_matchings/code/z_actor/func_800BB604.s")

UNK_TYPE1 D_801AED8C[] = {
    0x09, 0x05, 0x01, 0x03, 0x04, 0x07, 0x0B, 0x00, 0x06, 0x08, 0x0A, 0x00,
};

#pragma GLOBAL_ASM("asm/non_matchings/code/z_actor/func_800BB8EC.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_actor/func_800BBA88.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_actor/func_800BBAC0.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_actor/func_800BBB74.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_actor/func_800BBC20.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_actor/func_800BBCEC.s")

void func_800BBDAC(GlobalContext* globalCtx, Actor* actor, Vec3f* arg2, f32 arg3, s32 arg4, f32 arg5, s16 arg6,
                   s16 arg7, u8 arg8) {
    Vec3f sp94;
    Vec3f D_801AED98 = { 0.0f, 0.3f, 0.0f };
    s32 pad[2];
    f32 phi_f20;
    s32 phi_s3;

    phi_f20 = (Rand_ZeroOne() - 0.5f) * 6.28f;
    sp94.y = actor->floorHeight;
    D_801AED98.y += (Rand_ZeroOne() - 0.5f) * 0.2f;

    for (phi_s3 = arg4; phi_s3 >= 0; phi_s3--) {
        sp94.x = (sin_rad(phi_f20) * arg3) + arg2->x;
        sp94.z = (cos_rad(phi_f20) * arg3) + arg2->z;
        D_801AED98.x = (Rand_ZeroOne() - 0.5f) * arg5;
        D_801AED98.z = (Rand_ZeroOne() - 0.5f) * arg5;

        if (arg6 == 0) {
            func_800B10C0(globalCtx, &sp94, &D_801D15B0, &D_801AED98);
        } else if (arg8 != 0) {
            func_800B1210(globalCtx, &sp94, &D_801D15B0, &D_801AED98, arg6, arg7);
        } else {
            func_800B11A0(globalCtx, &sp94, &D_801D15B0, &D_801AED98, arg6, arg7);
        }
        phi_f20 += 6.28f / (arg4 + 1.0f);
    }
}

void func_800BBFB0(GlobalContext* globalCtx, Vec3f* position, f32 param3, s32 param_4, s16 param_5, s16 param_6,
                   u8 param_7) {
    Vec3f sp84;
    Vec3f D_801AEDA4 = { 0.0f, 0.3f, 0.0f };
    s32 phi_s0;

    for (phi_s0 = param_4; phi_s0 >= 0; phi_s0--) {
        s16 temp_v0;

        sp84.x = ((Rand_ZeroOne() - 0.5f) * param3) + position->x;
        sp84.y = ((Rand_ZeroOne() - 0.5f) * param3) + position->y;
        sp84.z = ((Rand_ZeroOne() - 0.5f) * param3) + position->z;

        temp_v0 = (s32)(Rand_ZeroOne() * param_5 * 0.2f);
        temp_v0 += param_5;

        if (param_7) {
            func_800B1210(globalCtx, &sp84, &D_801D15B0, &D_801AEDA4, temp_v0, param_6);
        } else {
            func_800B11A0(globalCtx, &sp84, &D_801D15B0, &D_801AEDA4, temp_v0, param_6);
        }
    }
}

void func_800BC154(GlobalContext* globalCtx, ActorContext* actorCtx, Actor* actor, u8 actorCategory) {
    actorCtx->actorList[actor->category].unk_08 = 1;
    actor->category = actorCategory;
}

s32 D_801AEDB0[] = {
    0x00000800, 0x00000020, 0x00000020, 0x00000800, 0x00001000, 0x00002000, 0x00000001, 0x00010000, 0x00000001,
};

s32 func_800BC188(s32 index) {
    if ((index < 0) || (index >= ARRAY_COUNT(D_801AEDB0))) {
        return 0;
    }
    return D_801AEDB0[index];
}

#pragma GLOBAL_ASM("asm/non_matchings/code/z_actor/func_800BC1B4.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_actor/func_800BC270.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_actor/func_800BC444.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_actor/func_800BC4EC.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_actor/func_800BC5B8.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_actor/func_800BC5EC.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_actor/func_800BC620.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_actor/func_800BC770.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_actor/func_800BC7D8.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_actor/func_800BC848.s")

typedef struct {
    /* 0x00 */ f32 unk_00;
    /* 0x04 */ f32 unk_04;
    /* 0x08 */ f32 unk_08;
    /* 0x0C */ f32 unk_0C;
    /* 0x10 */ f32 unk_10;
    /* 0x14 */ Gfx* unk_14;
    /* 0x18 */ Gfx* unk_18;
} struct_801AEDD4; // size = 0x1C

struct_801AEDD4 D_801AEDD4[] = {
    { 0.540000021458f, 6000.0f, 5000.0, 1.0f, 0.0f, 0x05000230, 0x05000140 },
    { 0.643999993801f, 12000.0f, 8000.0f, 1.0f, 0.0f, 0x06000530, 0x06000400 },
    { 0.6400000453f, 8500.0f, 8000.0f, 1.75f, 0.10000000149f, 0x05000230, 0x05000140 },
};

// Actor_DrawDoorLock
void func_800BC8B8(GlobalContext* globalCtx, s32 frame, s32 type) {
    s32 pad[2];
    MtxF spA8;
    s32 phi_s1;
    f32 temp_f22;
    f32 temp_f24;
    struct_801AEDD4* temp_s2;
    f32 phi_f20;
    f32 phi_f2;

    temp_s2 = &D_801AEDD4[type];
    phi_f20 = temp_s2->unk_10;

    OPEN_DISPS(globalCtx->state.gfxCtx);

    SysMatrix_InsertTranslation(0.0f, temp_s2->unk_08, 500.0f, MTXMODE_APPLY);
    SysMatrix_CopyCurrentState(&spA8);

    temp_f22 = __sinf(temp_s2->unk_00 - phi_f20) * -(10 - frame) * 0.1f * temp_s2->unk_04;
    temp_f24 = __cosf(temp_s2->unk_00 - phi_f20) * (10 - frame) * 0.1f * temp_s2->unk_04;

    for (phi_s1 = 0; phi_s1 < 4; phi_s1++) {
        SysMatrix_SetCurrentState(&spA8);
        SysMatrix_InsertZRotation_f(phi_f20, 1);
        SysMatrix_InsertTranslation(temp_f22, temp_f24, 0.0f, 1);
        if (temp_s2->unk_0C != 1.0f) {
            Matrix_Scale(temp_s2->unk_0C, temp_s2->unk_0C, temp_s2->unk_0C, 1);
        }

        gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(globalCtx->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        gSPDisplayList(POLY_OPA_DISP++, temp_s2->unk_14);

        if ((phi_s1 % 2) != 0) {
            phi_f2 = 2.0f * temp_s2->unk_00;
        } else {
            phi_f2 = M_PI - (2.0f * temp_s2->unk_00);
        }
        phi_f20 += phi_f2;
    }

    SysMatrix_SetCurrentState(&spA8);
    Matrix_Scale(frame * 0.1f, frame * 0.1f, frame * 0.1f, MTXMODE_APPLY);

    gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(globalCtx->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPDisplayList(POLY_OPA_DISP++, temp_s2->unk_18);

    CLOSE_DISPS(globalCtx->state.gfxCtx);
}

#pragma GLOBAL_ASM("asm/non_matchings/code/z_actor/func_800BCB50.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_actor/func_800BCB70.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_actor/func_800BCBF4.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_actor/func_800BCC68.s")

#ifdef NON_MATCHING
// small regalloc
void func_800BCCDC(Vec3s* points, s32 pathcount, Vec3f* pos1, Vec3f* pos2, s32 parm5) {
    s32 spB4;
    s32 spB0;
    s32 spA8[2] = { 0, 0 };
    s32 spA0[2] = { 0, 0 };
    Vec3f sp94;
    Vec3f sp7C[2];
    Vec3f sp70;
    Vec3f sp64;
    f32 sp60;
    f32 sp5C;
    f32 sp54[2];

    spB0 = 0;
    sp5C = 1.6e9f;

    for (spB4 = 0; spB4 < pathcount; spB4++) {
        sp60 = Math3D_XZDistanceSquared(pos1->x, pos1->z, points[spB4].x, points[spB4].z);
        if (sp60 < sp5C) {
            sp5C = sp60;
            spB0 = spB4;
        }
    }

    sp94.x = points[spB0].x;
    sp94.z = points[spB0].z;
    pos2->y = points[spB0].y;
    if (spB0 != 0) {
        sp64.x = points[spB0 - 1].x;
        sp64.z = points[spB0 - 1].z;
    } else if (parm5) {
        sp64.x = points[pathcount - 1].x;
        sp64.z = points[pathcount - 1].z;
    }

    if ((spB0 != 0) || (parm5)) {
        spA8[0] =
            Math3D_PointDistToLine2D(pos1->x, pos1->z, sp64.x, sp64.z, sp94.x, sp94.z, &sp7C[0].x, &sp7C[0].z, &sp60);
    }

    if (spB0 + 1 != pathcount) {
        sp70.x = points[spB0 + 1].x;
        sp70.z = points[spB0 + 1].z;
    } else if (parm5) {
        sp70.x = points->x;
        sp70.z = points->z;
    }

    if ((spB0 + 1 != pathcount) || (parm5)) {
        spA8[1] =
            Math3D_PointDistToLine2D(pos1->x, pos1->z, sp94.x, sp94.z, sp70.x, sp70.z, &sp7C[1].x, &sp7C[1].z, &sp60);
    }

    if (parm5) {
        s32 phi_s0_2;

        spA0[0] = ((sp64.x - pos1->x) * (sp94.z - pos1->z)) < ((sp64.z - pos1->z) * (sp94.x - pos1->x));
        spA0[1] = ((sp70.z - pos1->z) * (sp94.x - pos1->x)) < ((sp94.z - pos1->z) * (sp70.x - pos1->x));

        for (phi_s0_2 = 0; phi_s0_2 < ARRAY_COUNT(sp54); phi_s0_2++) {
            if ((spA8)[phi_s0_2] != 0) {
                sp54[phi_s0_2] = Math3D_XZDistanceSquared(pos1->x, pos1->z, sp7C[phi_s0_2].x, sp7C[phi_s0_2].z);
            } else {
                sp54[phi_s0_2] = 1.6e9f;
            }
        }
    }

    if ((parm5) && (((spA0[0] != 0) && (spA0[1] != 0)) || ((spA0[0] != 0) && (spA8[0] != 0) && (sp54[0] < sp54[1])) ||
                    ((spA0[1] != 0) && (spA8[1] != 0) && (sp54[1] < sp54[0])))) {
        pos2->x = pos1->x;
        pos2->z = pos1->z;
    } else if ((spA8[0] != 0) && (spA8[1] != 0)) {
        if ((spA0[0] == 0) && (spA0[1] == 0)) {
            if (Math3D_PointDistToLine2D(pos1->x, pos1->z, sp7C[0].x, sp7C[0].z, sp7C[1].x, sp7C[1].z, &pos2->x,
                                         &pos2->z, &sp60) == 0) {
                pos2->x = (sp7C[1].x + sp7C[0].x) * 0.5f;
                pos2->z = (sp7C[1].z + sp7C[0].z) * 0.5f;
            }
        } else if (sp54[1] < sp54[0]) {
            pos2->x = sp7C[1].x;
            pos2->z = sp7C[1].z;
        } else {
            pos2->x = sp7C[0].x;
            pos2->z = sp7C[0].z;
        }
    } else if (spA8[0] != 0) {
        pos2->x = sp7C[0].x;
        pos2->z = sp7C[0].z;
    } else if (spA8[1] != 0) {
        pos2->x = sp7C[1].x;
        pos2->z = sp7C[1].z;
    } else if ((parm5) && ((((sp64.x - pos1->x) * (sp70.z - pos1->z)) < ((sp64.z - pos1->z) * (sp70.x - pos1->x))))) {
        pos2->x = pos1->x;
        pos2->z = pos1->z;
    } else {
        pos2->x = sp94.x;
        pos2->z = sp94.z;
    }
}
#else
s32 D_801AEE28[] = { 0, 0 };
s32 D_801AEE30[] = { 0, 0 };
#pragma GLOBAL_ASM("asm/non_matchings/code/z_actor/func_800BCCDC.s")
#endif

// unused
s32 func_800BD2B4(GlobalContext* globalCtx, Actor* actor, s16* arg2, f32 arg3, u16 (*arg4)(GlobalContext*, Actor*),
                  s16 (*arg5)(GlobalContext*, Actor*)) {
    if (Actor_IsTalking(actor, globalCtx)) {
        *arg2 = 1;
        return 1;
    } else if (*arg2 != 0) {
        *arg2 = arg5(globalCtx, actor);
        return 0;
    } else if (func_800B8934(globalCtx, actor) == 0) {
        return 0;
    } else if (func_800B8614(actor, globalCtx, arg3) == 0) {
        return 0;
    } else {
        actor->textId = arg4(globalCtx, actor);
        return 0;
    }
}

typedef struct {
    /* 0x00 */ s16 unk_00;
    /* 0x02 */ s16 unk_02;
    /* 0x04 */ s16 unk_04;
    /* 0x06 */ s16 unk_06;
    /* 0x08 */ s16 unk_08;
    /* 0x0A */ s16 unk_0A;
    /* 0x0C */ u8 unk_0C;
} struct_801AEE38_0; // size = 0x10

typedef struct {
    /* 0x00 */ struct_801AEE38_0 sub_00;
    /* 0x10 */ f32 unk_10;
    /* 0x14 */ s16 unk_14;
} struct_801AEE38; // size = 0x18

struct_801AEE38 D_801AEE38[] = {
    { { 0x1C20, 0xE390, 0x1C70, 0x1554, 0, 0, 0 }, 170.0f, 0x3FFC },
    { { 0x2AA8, 0xEAAC, 0x1554, 0x1554, 0xF8E4, 0xE38, 1 }, 170.0f, 0x3FFC },
    { { 0x31C4, 0xE390, 0xE38, 0xE38, 0xF1C8, 0x71C, 1 }, 170.0f, 0x3FFC },
    { { 0x1554, 0xF1C8, 0, 0x71C, 0xF8E4, 0, 1 }, 170.0f, 0x3FFC },
    { { 0x2AA8, 0xF8E4, 0x71C, 0xE38, 0xD558, 0x2AA8, 1 }, 170.0f, 0x3FFC },
    { { 0, 0xE390, 0x2AA8, 0x3FFC, 0xF1C8, 0xE38, 1 }, 170.0f, 0x3FFC },
    { { 0x2AA8, 0xF1C8, 0xE38, 0xE38, 0, 0, 1 }, 0.0f, 0 },
    { { 0x2AA8, 0xF1C8, 0, 0xE38, 0, 0x1C70, 1 }, 0.0f, 0 },
    { { 0x2AA8, 0xF1C8, 0xF1C8, 0, 0, 0, 1 }, 0.0f, 0 },
    { { 0x71C, 0xF1C8, 0xE38, 0x1C70, 0, 0, 1 }, 0.0f, 0 },
    { { 0xE38, 0xF1C8, 0, 0x1C70, 0, 0xE38, 1 }, 0.0f, 0 },
    { { 0x2AA8, 0xE390, 0x1C70, 0xE38, 0xF1C8, 0xE38, 1 }, 0.0f, 0 },
    { { 0x18E2, 0xF1C8, 0xE38, 0xE38, 0, 0, 1 }, 0.0f, 0 },
    { { 0x2A6C, 0xE390, 0x1C70, 0x1554, 0, 0, 0 }, 170.0f, 0x3FFC },
};

void func_800BD384(Actor* actor, struct_800BD888_arg1* arg1, s16 arg2, s16 arg3, s16 arg4, s16 arg5, s16 arg6, s16 arg7,
                   u8 arg8) {
    s16 sp46;
    s16 sp44;
    s16 temp2;
    s16 sp40;
    s16 temp1;
    Vec3f sp30;

    sp30.x = actor->world.pos.x;
    sp30.y = actor->world.pos.y + arg1->unk_14;
    sp30.z = actor->world.pos.z;

    sp46 = Math_Vec3f_Pitch(&sp30, &arg1->unk_18);
    sp44 = Math_Vec3f_Yaw(&sp30, &arg1->unk_18);
    sp40 = Math_Vec3f_Yaw(&actor->world.pos, &arg1->unk_18) - actor->shape.rot.y;

    temp1 = CLAMP(sp40, -arg2, arg2);
    Math_SmoothStepToS(&arg1->unk_08.y, temp1, 6, 2000, 1);

    temp1 = (ABS_ALT(sp40) >= 0x8000) ? 0 : ABS_ALT(sp40);
    arg1->unk_08.y = CLAMP(arg1->unk_08.y, -temp1, temp1);

    sp40 -= arg1->unk_08.y;

    temp1 = CLAMP(sp40, -arg5, arg5);
    Math_SmoothStepToS(&arg1->unk_0E.y, temp1, 6, 2000, 1);

    temp1 = (ABS_ALT(sp40) >= 0x8000) ? 0 : ABS_ALT(sp40);
    arg1->unk_0E.y = CLAMP(arg1->unk_0E.y, -temp1, temp1);

    if (arg8) {
        Math_SmoothStepToS(&actor->shape.rot.y, sp44, 6, 2000, 1);
    }

    temp1 = CLAMP(sp46, arg4, (s16)(u16)arg3);
    Math_SmoothStepToS(&arg1->unk_08.x, temp1, 6, 2000, 1);

    temp2 = sp46 - arg1->unk_08.x;

    temp1 = CLAMP(temp2, arg7, arg6);
    Math_SmoothStepToS(&arg1->unk_0E.x, temp1, 6, 2000, 1);
}

// unused
s16 func_800BD6B8(s16 arg0) {
    return D_801AEE38[arg0].unk_14;
}

s16 func_800BD6E4(Actor* actor, struct_800BD888_arg1* arg1, f32 arg2, s16 arg3, s16 flag) {
    s32 pad;

    if (flag) {
        return flag;
    } else if (arg1->unk_00 != 0) {
        return 4;
    } else if (arg2 < Math_Vec3f_DistXYZ(&actor->world.pos, &arg1->unk_18)) {
        arg1->unk_04 = 0;
        arg1->unk_06 = 0;
        return 1;
    } else {
        s16 yaw = Math_Vec3f_Yaw(&actor->world.pos, &arg1->unk_18);
        s16 phi_a0 = ABS_ALT(BINANG_SUB(yaw, actor->shape.rot.y));

        if (arg3 >= phi_a0) {
            arg1->unk_04 = 0;
            arg1->unk_06 = 0;
            return 2;
        } else if (DECR(arg1->unk_04) != 0) {
            return arg1->unk_02;
        } else {
            switch (arg1->unk_06) {
                case 0:
                case 2:
                    arg1->unk_04 = Rand_S16Offset(30, 30);
                    arg1->unk_06++;
                    return 1;

                case 1:
                    arg1->unk_04 = Rand_S16Offset(10, 10);
                    arg1->unk_06++;
                    return 3;

                default:
                    return 4;
            }
        }
    }
}

// This function is very similar to OoT's func_80034A14
void func_800BD888(Actor* actor, struct_800BD888_arg1* arg1, s16 arg2, s16 arg3) {
    struct_801AEE38_0 sp38;

    arg1->unk_02 = func_800BD6E4(actor, arg1, D_801AEE38[arg2].unk_10, D_801AEE38[arg2].unk_14, arg3);
    sp38 = D_801AEE38[arg2].sub_00;

    switch (arg1->unk_02) {
        case 1:
            sp38.unk_00 = 0;
            sp38.unk_04 = 0;
            sp38.unk_02 = 0;
        case 3:
            sp38.unk_06 = 0;
            sp38.unk_0A = 0;
            sp38.unk_08 = 0;
        case 2:
            sp38.unk_0C = 0;
    }

    func_800BD384(actor, arg1, sp38.unk_00, sp38.unk_04, sp38.unk_02, sp38.unk_06, sp38.unk_0A, sp38.unk_08,
                  sp38.unk_0C);
}

Gfx D_801AEF88[] = {
    gsDPSetRenderMode(AA_EN | Z_CMP | Z_UPD | IM_RD | CLR_ON_CVG | CVG_DST_WRAP | ZMODE_XLU | FORCE_BL |
                          G_RM_FOG_SHADE_A,
                      AA_EN | Z_CMP | Z_UPD | IM_RD | CLR_ON_CVG | CVG_DST_WRAP | ZMODE_XLU | FORCE_BL |
                          GBL_c2(G_BL_CLR_IN, G_BL_A_IN, G_BL_CLR_MEM, G_BL_1MA)),
    gsDPSetAlphaCompare(G_AC_THRESHOLD),
    gsSPEndDisplayList(),
};

Gfx D_801AEFA0[] = {
    gsSPEndDisplayList(),
};

void* func_800BD9A0(GraphicsContext* gfxCtx) {
    Gfx* displayListHead;
    Gfx* displayList;

    displayListHead = displayList = GRAPH_ALLOC(gfxCtx, 0x10);

    gDPSetRenderMode(displayListHead++,
                     AA_EN | Z_CMP | Z_UPD | IM_RD | CLR_ON_CVG | CVG_DST_WRAP | ZMODE_XLU | FORCE_BL |
                         G_RM_FOG_SHADE_A,
                     AA_EN | Z_CMP | Z_UPD | IM_RD | CLR_ON_CVG | CVG_DST_WRAP | ZMODE_XLU | FORCE_BL |
                         GBL_c2(G_BL_CLR_IN, G_BL_A_IN, G_BL_CLR_MEM, G_BL_1MA));
    gSPEndDisplayList(displayListHead++);

    return displayList;
}

// unused
void func_800BD9E0(GlobalContext* globalCtx, SkelAnime* skelAnime, OverrideLimbDraw2 overrideLimbDraw,
                   PostLimbDraw2 postLimbDraw, Actor* actor, s16 alpha) {
    OPEN_DISPS(globalCtx->state.gfxCtx);
    func_8012C28C(globalCtx->state.gfxCtx);

    gDPSetEnvColor(POLY_OPA_DISP++, 0, 0, 0, alpha);
    gSPSegment(POLY_OPA_DISP++, 0x0C, gEmptyDL);

    POLY_OPA_DISP = SkelAnime_DrawSV2(globalCtx, skelAnime->skeleton, skelAnime->limbDrawTbl, skelAnime->dListCount,
                                      overrideLimbDraw, postLimbDraw, actor, POLY_OPA_DISP);
    CLOSE_DISPS(globalCtx->state.gfxCtx);
}

void func_800BDAA0(GlobalContext* globalCtx, SkelAnime* skelAnime, OverrideLimbDraw2 overrideLimbDraw,
                   PostLimbDraw2 postLimbDraw, Actor* actor, s16 alpha) {
    OPEN_DISPS(globalCtx->state.gfxCtx);
    func_8012C2DC(globalCtx->state.gfxCtx);

    gDPSetEnvColor(POLY_XLU_DISP++, 0, 0, 0, alpha);
    gSPSegment(POLY_XLU_DISP++, 0x0C, func_800BD9A0(globalCtx->state.gfxCtx));

    POLY_XLU_DISP = SkelAnime_DrawSV2(globalCtx, skelAnime->skeleton, skelAnime->limbDrawTbl, skelAnime->dListCount,
                                      overrideLimbDraw, postLimbDraw, actor, POLY_XLU_DISP);
    CLOSE_DISPS(globalCtx->state.gfxCtx);
}

// Unused
s16 func_800BDB6C(Actor* actor, GlobalContext* globalCtx, s16 arg2, f32 arg3) {
    Player* player = PLAYER;
    f32 phi_f2;

    if ((globalCtx->csCtx.state != 0) || (D_801D0D50 != 0)) {
        phi_f2 = Math_Vec3f_DistXYZ(&actor->world.pos, &globalCtx->view.eye) * 0.25f;
    } else {
        phi_f2 = Math_Vec3f_DistXYZ(&actor->world.pos, &player->actor.world.pos);
    }

    if (arg3 < phi_f2) {
        actor->flags &= -2;
        Math_SmoothStepToS(&arg2, 0, 6, 0x14, 1);
    } else {
        actor->flags |= 1;
        Math_SmoothStepToS(&arg2, 0xFF, 6, 0x14, 1);
    }

    return arg2;
}

void func_800BDC5C(SkelAnime* skelAnime, ActorAnimationEntry* animation, s32 index) {
    f32 frameCount;

    animation += index;
    if (animation->frameCount > 0.0f) {
        frameCount = animation->frameCount;
    } else {
        frameCount = SkelAnime_GetFrameCount(&animation->animation->common);
    }

    SkelAnime_ChangeAnim(skelAnime, animation->animation, animation->playSpeed, animation->startFrame, frameCount,
                         animation->mode, animation->morphFrames);
}

// Unused
void func_800BDCF4(GlobalContext* globalCtx, s16* arg1, s16* arg2, s32 size) {
    s32 frames = globalCtx->gameplayFrames;
    s32 i;

    for (i = 0; i < size; i++) {
        arg1[i] = (0x814 + 50 * i) * frames;
        arg2[i] = (0x940 + 50 * i) * frames;
    }
}

void Actor_Noop(Actor* actor, GlobalContext* globalCtx) {
}

void Gfx_DrawDListOpa(GlobalContext* globalCtx, Gfx* dlist) {
    Gfx* dl;

    OPEN_DISPS(globalCtx->state.gfxCtx);

    dl = POLY_OPA_DISP;

    gSPDisplayList(&dl[0], &sSetupDL[6 * 0x19]);
    gSPMatrix(&dl[1], Matrix_NewMtx(globalCtx->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPDisplayList(&dl[2], dlist);

    POLY_OPA_DISP = &dl[3];

    CLOSE_DISPS(globalCtx->state.gfxCtx);
}

#pragma GLOBAL_ASM("asm/non_matchings/code/z_actor/Gfx_DrawDListXlu.s")

Actor* func_800BE0B8(GlobalContext* globalCtx, Actor* inActor, s16 arg2, u8 arg3, f32 arg4) {
    Actor* actor = globalCtx->actorCtx.actorList[arg3].first;

    while (actor != NULL) {
        if (actor == inActor || ((arg2 != -1) && (arg2 != actor->id))) {
            actor = actor->next;
            continue;
        }

        if (Actor_DistanceBetweenActors(inActor, actor) <= arg4) {
            return actor;
        }

        actor = actor->next;
    }

    return NULL;
}

#pragma GLOBAL_ASM("asm/non_matchings/code/z_actor/func_800BE184.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_actor/func_800BE22C.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_actor/func_800BE258.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_actor/func_800BE2B8.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_actor/func_800BE33C.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_actor/func_800BE3D0.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_actor/func_800BE504.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_actor/func_800BE568.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_actor/func_800BE5CC.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_actor/func_800BE63C.s")

UNK_TYPE4 D_801AEFA8[] = {
    0x04091DE0,
    0x04091FE0,
    0x040921E0,
    0x040923E0,
};

#pragma GLOBAL_ASM("asm/non_matchings/code/z_actor/func_800BE680.s")

static Color_RGBA8 D_801AEFB8 = { 170, 255, 255, 255 };
static Color_RGBA8 D_801AEFBC = { 200, 200, 255, 255 };
static Vec3f D_801AEFC0 = { 0.0f, -1.0f, 0.0f };

#pragma GLOBAL_ASM("asm/non_matchings/code/z_actor/func_800BF7CC.s")
