/*
 * File: z_obj_um.c
 * Overlay: ovl_Obj_Um
 * Description: Cremia's cart and milk run quest
 */

#include "z_obj_um.h"

#define FLAGS (ACTOR_FLAG_1 | ACTOR_FLAG_8 | ACTOR_FLAG_10 | ACTOR_FLAG_20)

#define THIS ((ObjUm*)thisx)

void ObjUm_Init(ObjUm* this, GlobalContext* globalCtx);
void ObjUm_Destroy(Actor* thisx, GlobalContext* globalCtx);
void ObjUm_Update(ObjUm* this, GlobalContext* globalCtx);
void ObjUm_Draw(Actor* thisx, GlobalContext* globalCtx);

void func_80B79A50(ObjUm* this, GlobalContext* globalCtx);
void func_80B79F10(ObjUm* this, GlobalContext* globalCtx);
void func_80B7A070(ObjUm* this, GlobalContext* globalCtx);
void func_80B7A0E0(ObjUm* this, GlobalContext* globalCtx);
void func_80B7A144(ObjUm* this, GlobalContext* globalCtx);
void func_80B7A2AC(ObjUm* this, GlobalContext* globalCtx);
void func_80B7A394(ObjUm* this, GlobalContext* globalCtx);
void func_80B7A400(ObjUm* this, GlobalContext* globalCtx);
void func_80B7A494(ObjUm* this, GlobalContext* globalCtx);
void func_80B7A614(ObjUm* this, GlobalContext* globalCtx);
void func_80B7A7AC(ObjUm* this, GlobalContext* globalCtx);
void func_80B7ABE4(ObjUm* this, GlobalContext* globalCtx);
void func_80B7AC94(ObjUm* this, GlobalContext* globalCtx);
void func_80B7AD34(ObjUm* this, GlobalContext* globalCtx);
void func_80B7AE58(ObjUm* this, GlobalContext* globalCtx);

void ObjUm_SetupAction(ObjUm* this, ObjUmActionFunc actionFunc);

#if 0
const ActorInit Obj_Um_InitVars = {
    ACTOR_OBJ_UM,
    ACTORCAT_NPC,
    FLAGS,
    OBJECT_UM,
    sizeof(ObjUm),
    (ActorFunc)ObjUm_Init,
    (ActorFunc)ObjUm_Destroy,
    (ActorFunc)ObjUm_Update,
    (ActorFunc)ObjUm_Draw,
};
#endif

/*
f32 func_800C3FA0(s32, ?*, void*, void*); // extern
f32 func_800C4000(GraphicsContext**, s32, CollisionPoly**, f32*); // extern
? func_800F415C(void*, ?*, ?); // extern
? func_800FE484(ObjUm*, void (*)(ObjUm* this, GlobalContext* globalCtx)); // extern
? func_8017B7F8(?*, s16, f32*, f32*, f32*); // extern
? func_801A3098(?); // extern
? func_801A3F54(?); // extern
? func_801A89A8(?); // extern
void func_80B77770(ObjUm* arg0, GlobalContext* arg1); // static
? func_80B77FA4(void* arg0, GlobalContext* arg1); // static
? func_80B781DC(ObjUm* arg0, void* arg1, void* arg2, GlobalContext* arg3); // static
? func_80B783E0(ObjUm* arg0, GlobalContext* arg1, s32 arg2, void* arg3); // static
? func_80B78764(ObjUm* arg0, GlobalContext* arg1, void* arg2, void* arg3); // static
? func_80B78A54(ObjUm* arg0, GlobalContext* arg1, s32 arg2, void* arg3, void* arg4); // static
? func_80B78C18(ObjUm* arg0, GlobalContext* arg1); // static
? func_80B78D08(ObjUm* arg0, GlobalContext* arg1); // static
SaveContext* func_80B78DF0(ObjUm* arg0, GlobalContext* arg1); // static
void* func_80B78E38(ObjUm* arg0, GlobalContext* arg1); // static
void* func_80B78E88(ObjUm* arg0, GlobalContext* arg1, s16 arg2); // static
void* func_80B78EBC(ObjUm* arg0, GlobalContext* arg1); // static
void* func_80B78EFC(ObjUm* arg0, GlobalContext* arg1, s16 arg2); // static
void func_80B79524(Actor* arg0); // static
void func_80B79560(GlobalContext* arg0, ObjUm* arg1, s32 arg2, u16 arg3); // static
s32 func_80B795A0(GlobalContext*, ObjUm*, s32); // static
s32 func_80B79734(GlobalContext* arg0, ObjUm* arg1, s32 arg2, s32*); // static
u16 func_80B797EC(GlobalContext* arg0, Actor* arg1, s32 arg2); // static
? func_80B7984C(GlobalContext* arg0, Actor* arg1, s32 arg2, s32* arg3); // static
void func_80B79A50(ObjUm* this, GlobalContext* globalCtx); // static
s32 func_80B79BA0(ObjUm* arg0, GlobalContext* arg1); // static
void func_80B79F10(ObjUm* this, GlobalContext* globalCtx); // static
void func_80B79FFC(ObjUm* this, GlobalContext* globalCtx); // static
s32 func_80B7A070(ObjUm* arg0, GlobalContext* arg1); // static
void func_80B7A0E0(ObjUm* this, GlobalContext* globalCtx); // static
void func_80B7A144(ObjUm* this, GlobalContext* globalCtx); // static
u16 func_80B7A1B4(ObjUm* arg0, ObjUm* arg1); // static
void func_80B7A240(ObjUm* arg0, ObjUm* arg1); // static
void func_80B7A2AC(ObjUm* this, GlobalContext* globalCtx); // static
void func_80B7A394(ObjUm* arg0, ObjUm* arg1); // static
void func_80B7A400(ObjUm* this, GlobalContext* globalCtx); // static
SaveContext* func_80B7A494(ObjUm* arg0, GlobalContext* arg1); // static
void func_80B7A614(ObjUm* this, GlobalContext* globalCtx); // static
void func_80B7A7AC(ObjUm* arg0, GlobalContext* arg1); // static
? func_80B7A860(ObjUm*, ObjUm*); // static
void func_80B7AB78(ObjUm* arg0, ObjUm* arg1); // static
void func_80B7AC94(ObjUm* this, GlobalContext* globalCtx); // static
void func_80B7AE58(ObjUm* this, GlobalContext* globalCtx); // static
void func_80B7AEFC(ObjUm* this, GlobalContext* globalCtx); // static
s32 func_80B7AF30(void* arg0, s32 arg1); // static
void func_80B7B154(ObjUm* arg0, GlobalContext* arg1); // static
void func_80B7B18C(ObjUm* arg0, GlobalContext* arg1, s32 arg2, ObjUm*); // static
s32 func_80B7B598(GlobalContext* arg0, s32 arg1, Gfx** arg2, Vec3f* arg3, Vec3s* arg4, Actor* arg5); // static
void func_80B7B93C(GlobalContext* arg0, Vec3f* arg1); // static
void func_80B7BABC(GlobalContext* arg0, s32 arg1, Gfx** arg2, Vec3s* arg3, Actor* arg4); // static
Mtx* func_80B7BEA4(s8* arg0, s16 arg1, f32* arg2, u8 arg3, GraphicsContext** arg4); // static
extern ? D_801D15BC;
extern f32 D_80B7C320;
extern f32 D_80B7C324;
extern f32 D_80B7C398;
extern f32 D_80B7C39C;
extern f32 D_80B7C3A0;
extern f32 D_80B7C3CC;
extern f32 D_80B7C3F4;
extern f32 D_80B7C3F8;
extern f32 D_80B7C3FC;
extern f32 D_80B7C400;
static ? D_80B7C110; // unable to generate initializer
static ? D_80B7C128; // unable to generate initializer
static ColliderCylinderInit D_80B7C138 = {
    {3, 0, 9, 0, 0x10, 1},
    {1, {0, 0, 0}, {0x20, 0, 0}, 0, 1, 0},
    {0x28, 0x40, 0, {0, 0, 0}},
};
static ? D_80B7C164; // unable to generate initializer
static InitChainEntry D_80B7C254[2]; // unable to generate initializer
static ? D_80B7C25C; // unable to generate initializer
static ? D_80B7C260; // unable to generate initializer
static ? D_80B7C274; // unable to generate initializer
static ? D_80B7C284; // unable to generate initializer
static ? D_80B7C290; // unable to generate initializer
static ? D_80B7C29C; // unable to generate initializer
static ? D_80B7C2A8; // unable to generate initializer
static ? D_80B7C2B4; // unable to generate initializer
static ? D_80B7C2CC; // unable to generate initializer
static ? D_80B7C2E4; // unable to generate initializer
static ? D_80B7C2FC; // unable to generate initializer
static ? D_80B7C308; // unable to generate initializer
static ? D_80B7C314; // unable to generate initializer
*/

void func_80B7ABE4(ObjUm* this, GlobalContext* globalCtx);
void func_80B7AD34(ObjUm* this, GlobalContext* globalCtx);



extern FlexSkeletonHeader D_06011DF8;
extern AnimationHeader D_06012CC0;
extern CollisionHeader D_06007E20;
extern CollisionHeader D_06007F50;


#ifdef MIPS_2_C_OUTPUT
void func_80B77770(ObjUm* arg0, GlobalContext* arg1) {
    ? sp108;
    ? spFC;
    ? spF0;
    ? spE4;
    ? spD8;
    ? spCC;
    ? spC0;
    ? spB4;
    ? spA8;
    ? sp9C;
    ? sp90;
    ? sp84;
    ? sp78;
    ? sp6C;
    ? sp60;
    void* sp58;
    void* sp54;
    void* sp50;
    void* sp4C;
    Vec3f* sp48;
    Vec3f* sp44;
    Vec3f* sp40;
    Vec3f* sp3C;
    Vec3f* sp38;
    void* sp34;
    Vec3f* sp30;
    Vec3f* sp2C;
    Vec3f* sp28;
    s32 sp24;
    s32 sp20;
    Vec3f* temp_t6_3;
    Vec3f* temp_t6_4;
    Vec3f* temp_t6_5;
    Vec3f* temp_t7;
    Vec3f* temp_t8_3;
    Vec3f* temp_t8_4;
    Vec3f* temp_t8_5;
    Vec3f* temp_t9;
    s16 temp_a0;
    s16 temp_a0_2;
    s16 temp_s1;
    void* temp_t6;
    void* temp_t6_2;
    void* temp_t8;
    void* temp_t8_2;
    void* temp_t8_6;

    temp_s1 = arg0->dyna.actor.shape.rot.y;
    sp60.unk0 = (f32) arg0->dyna.actor.world.pos.x;
    temp_a0 = temp_s1 + 0x4000;
    sp60.unk4 = (f32) arg0->dyna.actor.world.pos.y;
    sp60.unk8 = (f32) arg0->dyna.actor.world.pos.z;
    arg0->unk414 = (f32) sp60.unk0;
    arg0->unk418 = (f32) sp60.unk4;
    temp_t8 = arg0 + 0x408;
    arg0->unk41C = (f32) sp60.unk8;
    sp6C.unk0 = (f32) sp60.unk0;
    sp6C.unk4 = (f32) sp60.unk4;
    sp6C.unk8 = (f32) sp60.unk8;
    sp58 = temp_t8;
    temp_t8->unk0 = (f32) sp6C.unk0;
    temp_t8->unk4 = (f32) sp6C.unk4;
    temp_t6 = arg0 + 0x3FC;
    temp_t8->unk8 = (f32) sp6C.unk8;
    sp78.unk0 = (f32) sp6C.unk0;
    sp78.unk4 = (f32) sp6C.unk4;
    sp78.unk8 = (f32) sp6C.unk8;
    sp54 = temp_t6;
    temp_t6->unk0 = (f32) sp78.unk0;
    temp_t6->unk4 = (f32) sp78.unk4;
    temp_t8_2 = arg0 + 0x3F0;
    temp_t6->unk8 = (f32) sp78.unk8;
    sp84.unk0 = (f32) sp78.unk0;
    sp84.unk4 = (f32) sp78.unk4;
    sp84.unk8 = (f32) sp78.unk8;
    sp50 = temp_t8_2;
    temp_t8_2->unk0 = (f32) sp84.unk0;
    temp_t8_2->unk4 = (f32) sp84.unk4;
    temp_t6_2 = arg0 + 0x3E4;
    temp_t8_2->unk8 = (f32) sp84.unk8;
    sp90.unk0 = (f32) sp84.unk0;
    sp90.unk4 = (f32) sp84.unk4;
    sp90.unk8 = (f32) sp84.unk8;
    sp4C = temp_t6_2;
    temp_t6_2->unk0 = (f32) sp90.unk0;
    temp_t6_2->unk4 = (f32) sp90.unk4;
    temp_t8_3 = arg0 + 0x3D8;
    temp_t6_2->unk8 = (f32) sp90.unk8;
    sp9C.unk0 = (f32) sp90.unk0;
    sp9C.unk4 = (f32) sp90.unk4;
    sp9C.unk8 = (f32) sp90.unk8;
    sp48 = temp_t8_3;
    temp_t8_3->x = sp9C.unk0;
    temp_t8_3->y = sp9C.unk4;
    temp_t8_3->z = sp9C.unk8;
    spA8.unk0 = (f32) sp9C.unk0;
    spA8.unk4 = (f32) sp9C.unk4;
    spA8.unk8 = (f32) sp9C.unk8;
    arg0->unk3CC = (f32) spA8.unk0;
    arg0->unk3D0 = (f32) spA8.unk4;
    temp_t6_3 = arg0 + 0x3C0;
    arg0->unk3D4 = (f32) spA8.unk8;
    spB4.unk0 = (f32) spA8.unk0;
    spB4.unk4 = (f32) spA8.unk4;
    spB4.unk8 = (f32) spA8.unk8;
    sp44 = temp_t6_3;
    temp_t6_3->x = spB4.unk0;
    temp_t6_3->y = spB4.unk4;
    temp_t8_4 = arg0 + 0x3B4;
    temp_t6_3->z = spB4.unk8;
    spC0.unk0 = (f32) spB4.unk0;
    spC0.unk4 = (f32) spB4.unk4;
    spC0.unk8 = (f32) spB4.unk8;
    sp40 = temp_t8_4;
    temp_t8_4->x = spC0.unk0;
    temp_t8_4->y = spC0.unk4;
    temp_t8_4->z = spC0.unk8;
    spCC.unk0 = (f32) spC0.unk0;
    spCC.unk4 = (f32) spC0.unk4;
    spCC.unk8 = (f32) spC0.unk8;
    arg0->unk3A8 = (f32) spCC.unk0;
    arg0->unk3AC = (f32) spCC.unk4;
    temp_t6_4 = arg0 + 0x39C;
    arg0->unk3B0 = (f32) spCC.unk8;
    spD8.unk0 = (f32) spCC.unk0;
    spD8.unk4 = (f32) spCC.unk4;
    spD8.unk8 = (f32) spCC.unk8;
    sp3C = temp_t6_4;
    temp_t6_4->x = spD8.unk0;
    temp_t6_4->y = spD8.unk4;
    temp_t8_5 = arg0 + 0x390;
    temp_t6_4->z = spD8.unk8;
    spE4.unk0 = (f32) spD8.unk0;
    spE4.unk4 = (f32) spD8.unk4;
    spE4.unk8 = (f32) spD8.unk8;
    sp38 = temp_t8_5;
    temp_t8_5->x = spE4.unk0;
    temp_t8_5->y = spE4.unk4;
    temp_t8_5->z = spE4.unk8;
    spF0.unk0 = (f32) spE4.unk0;
    spF0.unk4 = (f32) spE4.unk4;
    spF0.unk8 = (f32) spE4.unk8;
    temp_t8_6 = arg0 + 0x384;
    sp34 = temp_t8_6;
    temp_t8_6->unk0 = (f32) spF0.unk0;
    temp_t8_6->unk4 = (f32) spF0.unk4;
    temp_t8_6->unk8 = (f32) spF0.unk8;
    spFC.unk0 = (f32) spF0.unk0;
    spFC.unk4 = (f32) spF0.unk4;
    temp_t9 = arg0 + 0x378;
    spFC.unk8 = (f32) spF0.unk8;
    sp30 = temp_t9;
    temp_t9->x = spFC.unk0;
    temp_t9->y = spFC.unk4;
    temp_t9->z = spFC.unk8;
    sp108.unk0 = (f32) spFC.unk0;
    sp108.unk4 = (f32) spFC.unk4;
    temp_t6_5 = arg0 + 0x36C;
    sp108.unk8 = (f32) spFC.unk8;
    sp2C = temp_t6_5;
    temp_t6_5->x = sp108.unk0;
    temp_t6_5->y = sp108.unk4;
    temp_t7 = arg0 + 0x360;
    temp_t6_5->z = sp108.unk8;
    sp28 = temp_t7;
    temp_t7->x = sp108.unk0;
    temp_t7->y = sp108.unk4;
    temp_t7->z = sp108.unk8;
    sp24 = (s32) temp_a0;
    arg0->unk360 = (f32) (arg0->unk360 + (110.0f * Math_SinS(temp_a0)));
    temp_a0_2 = temp_s1 - 0x4000;
    arg0->unk368 = (f32) (arg0->unk368 + (110.0f * Math_CosS(sp26)));
    sp20 = (s32) temp_a0_2;
    arg0->unk36C = (f32) (arg0->unk36C + (110.0f * Math_SinS(temp_a0_2)));
    arg0->unk374 = (f32) (arg0->unk374 + (110.0f * Math_CosS(sp22)));
    Math_Vec3f_Copy(sp30, sp28);
    arg0->unk378 = (f32) (arg0->unk378 - (200.0f * Math_SinS(temp_s1)));
    arg0->unk380 = (f32) (arg0->unk380 - (200.0f * Math_CosS(temp_s1)));
    Math_Vec3f_Copy(sp38, sp2C);
    arg0->unk390 = (f32) (arg0->unk390 - (200.0f * Math_SinS(temp_s1)));
    arg0->unk398 = (f32) (arg0->unk398 - (200.0f * Math_CosS(temp_s1)));
    arg0->unk384 = (f32) (arg0->unk384 - (220.0f * Math_SinS(temp_s1)));
    arg0->unk38C = (f32) (arg0->unk38C - (220.0f * Math_CosS(temp_s1)));
    Math_Vec3f_Copy(sp3C, sp28);
    arg0->unk39C = (f32) (arg0->unk39C - (500.0f * Math_SinS(temp_s1)));
    arg0->unk3A4 = (f32) (arg0->unk3A4 - (500.0f * Math_CosS(temp_s1)));
    Math_Vec3f_Copy(sp40, sp2C);
    arg0->unk3B4 = (f32) (arg0->unk3B4 - (500.0f * Math_SinS(temp_s1)));
    arg0->unk3BC = (f32) (arg0->unk3BC - (500.0f * Math_CosS(temp_s1)));
    arg0->unk3A8 = (f32) (arg0->unk3A8 - (500.0f * Math_SinS(temp_s1)));
    arg0->unk3B0 = (f32) (arg0->unk3B0 - (500.0f * Math_CosS(temp_s1)));
    Math_Vec3f_Copy(sp44, sp28);
    arg0->unk3C0 = (f32) (arg0->unk3C0 - (700.0f * Math_SinS(temp_s1)));
    arg0->unk3C8 = (f32) (arg0->unk3C8 - (700.0f * Math_CosS(temp_s1)));
    Math_Vec3f_Copy(sp48, sp2C);
    arg0->unk3D8 = (f32) (arg0->unk3D8 - (700.0f * Math_SinS(temp_s1)));
    arg0->unk3E0 = (f32) (arg0->unk3E0 - (700.0f * Math_CosS(temp_s1)));
    arg0->unk3CC = (f32) (arg0->unk3CC - (700.0f * Math_SinS(temp_s1)));
    arg0->unk3D4 = (f32) (arg0->unk3D4 - (700.0f * Math_CosS(temp_s1)));
    sp4C->unk0 = (f32) temp_t8_6->unk0;
    sp4C->unk4 = (f32) temp_t8_6->unk4;
    sp4C->unk8 = (f32) temp_t8_6->unk8;
    arg0->unk3E4 = (f32) (arg0->unk3E4 + (40.0f * Math_SinS(sp26)));
    arg0->unk3EC = (f32) (arg0->unk3EC + (40.0f * Math_CosS(sp26)));
    sp50->unk0 = (f32) temp_t8_6->unk0;
    sp50->unk4 = (f32) temp_t8_6->unk4;
    sp50->unk8 = (f32) temp_t8_6->unk8;
    arg0->unk3F0 = (f32) (arg0->unk3F0 + (40.0f * Math_SinS(sp22)));
    arg0->unk3F8 = (f32) (arg0->unk3F8 + (40.0f * Math_CosS(sp22)));
    sp54->unk0 = (f32) sp30->x;
    sp54->unk4 = (f32) sp30->y;
    sp54->unk8 = (f32) sp30->z;
    sp58->unk0 = (f32) temp_t8_5->x;
    sp58->unk4 = (f32) temp_t8_5->y;
    sp58->unk8 = (f32) temp_t8_5->z;
}
#else
#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Um_0x80B77770/func_80B77770.asm")
#endif

#ifdef MIPS_2_C_OUTPUT
? func_80B77FA4(void* arg0, GlobalContext* arg1) {
    void* sp44;
    ActorContext* sp38;
    Actor* temp_v0;
    Actor* temp_v0_2;
    ActorContext* temp_a0;

    sp44 = Lib_SegmentedToVirtual((arg1->setupPathList + (arg0->unk2BC * 8))->unk4);
    func_801A89A8(0x8003);
    temp_a0 = arg1 + 0x1CA0;
    sp38 = temp_a0;
    temp_v0 = Actor_Spawn(temp_a0, arg1, 0xD, (f32) sp44->unk0, (f32) sp44->unk2, (f32) sp44->unk4, (s16) 0, (s16) (s32) arg0->unkBE, (s16) 0, (s16) 0x2013);
    arg0->unk358 = temp_v0;
    temp_v0->unk540 = (f32) temp_v0->world.pos.x;
    temp_v0->unk54C = 0xF;
    temp_v0->unk550 = 0xA;
    temp_v0->unk544 = (f32) temp_v0->world.pos.y;
    temp_v0->unk548 = (f32) temp_v0->world.pos.z;
    temp_v0->unk558 = 0;
    temp_v0->unk55C = 0x28;
    temp_v0->unk560 = 0x28;
    temp_v0->unk554 = (s32) arg0->unk2BC;
    temp_v0->unk568 = 0.0f;
    temp_v0->unk56C = 0.0f;
    temp_v0->unk570 = (f32) D_801D15B0.x;
    temp_v0->unk574 = (f32) D_801D15B0.y;
    temp_v0->unk578 = (f32) D_801D15B0.z;
    temp_v0->unk57C = (f32) D_801D15B0.x;
    temp_v0->unk580 = (f32) D_801D15B0.y;
    temp_v0->unk584 = (f32) D_801D15B0.z;
    temp_v0->unk200 = 1;
    temp_v0->unk588 = (s16) arg0->unkBE;
    temp_v0_2 = Actor_Spawn(temp_a0, arg1, 0xD, (f32) sp44->unk6, (f32) sp44->unk8, (f32) sp44->unkA, (s16) 0, (s16) (s32) arg0->unkBE, (s16) 0, (s16) 0x2014);
    arg0->unk35C = temp_v0_2;
    temp_v0_2->unk540 = (f32) temp_v0_2->world.pos.x;
    temp_v0_2->unk54C = 0xF;
    temp_v0_2->unk550 = 8;
    temp_v0_2->unk544 = (f32) temp_v0_2->world.pos.y;
    temp_v0_2->unk548 = (f32) temp_v0_2->world.pos.z;
    temp_v0_2->unk55C = 0x28;
    temp_v0_2->unk560 = 0x28;
    temp_v0_2->unk554 = (s32) arg0->unk2BC;
    temp_v0_2->unk568 = 0.0f;
    temp_v0_2->unk56C = 0.0f;
    temp_v0_2->unk57C = (f32) D_801D15B0.x;
    temp_v0_2->unk580 = (f32) D_801D15B0.y;
    temp_v0_2->unk584 = (f32) D_801D15B0.z;
    temp_v0_2->unk200 = 2;
    temp_v0_2->unk588 = (s16) arg0->unkBE;
    arg0->unk314 = 4;
    arg0->unk318 = 4;
    arg0->unk31C = 4;
    return 0;
}
#else
#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Um_0x80B77770/func_80B77FA4.asm")
#endif

#ifdef MIPS_2_C_OUTPUT
? func_80B781DC(ObjUm* arg0, void* arg1, void* arg2, GlobalContext* arg3) {
    ?* temp_s0;
    f32 temp_f20;
    s32 temp_s4;
    s32 temp_t1;
    s32 temp_v0;
    s32 temp_v1;
    s32 temp_v1_2;
    ?* phi_s0;
    s32 phi_s3;
    s32 phi_s2;
    s32 phi_s4;
    f32 phi_f20;

    phi_s0 = &D_80B7C164;
    phi_s3 = -1;
    phi_s2 = 0;
    phi_s4 = 0;
    phi_f20 = 0.0f;
    do {
        temp_v1 = phi_s0->unk0;
        if (arg1->unk550 == temp_v1) {
            temp_v0 = phi_s0->unk4;
            if (arg2->unk550 != temp_v0) {
                if (temp_v1 != 3) {
                    if (temp_v0 == 3) {
                        if (Player_GetMask(arg3) != 8) {
block_7:
                            phi_s3 = phi_s0->unk4;
                            phi_s4 = phi_s0->unk8;
                            phi_f20 = phi_s0->unkC;
block_14:
                            phi_s2 = phi_s0->unk10;
                        }
                    } else {
                        goto block_7;
                    }
                } else {
                    temp_v1_2 = arg1->unk54C;
                    if (((temp_v1_2 != 5) || (temp_v0 != 2)) && ((temp_v1_2 != 7) || (temp_v0 != 4))) {
                        temp_s4 = phi_s0->unk8;
                        temp_f20 = phi_s0->unkC;
                        phi_s3 = temp_v0;
                        phi_s4 = temp_s4;
                        phi_f20 = temp_f20;
                        if ((2.0f * Rand_ZeroOne()) < 1.0f) {
                            phi_s3 = temp_v0;
                            phi_s4 = temp_s4;
                            phi_f20 = temp_f20 * -1.0f;
                        }
                        goto block_14;
                    }
                }
            }
        }
        temp_s0 = phi_s0 + 0x14;
        phi_s0 = temp_s0;
    } while (temp_s0 != D_80B7C254);
    if (phi_s3 == -1) {

    } else {
        temp_t1 = arg1->unk550;
        arg1->unk540 = (s32) arg1->unk24;
        arg1->unk550 = phi_s3;
        arg1->unk55C = phi_s2;
        arg1->unk560 = phi_s2;
        arg1->unk564 = phi_s4;
        arg1->unk568 = phi_f20;
        arg1->unk544 = (s32) arg1->unk28;
        arg1->unk54C = temp_t1;
        arg1->unk548 = (s32) arg1->unk2C;
        if (phi_s3 == 3) {
            arg1->unk558 = (s32) (Rand_ZeroOne() * 3.0f);
        } else {
            arg1->unk558 = 0;
        }
    }
    return 0;
}
#else
#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Um_0x80B77770/func_80B781DC.asm")
#endif

#ifdef MIPS_2_C_OUTPUT
? func_80B783E0(ObjUm* arg0, GlobalContext* arg1, s32 arg2, void* arg3) {
    u8* sp6C;
    s32 sp68;
    void* sp64;
    ? sp50;
    f32 sp4C;
    f32 sp48;
    f32 sp44;
    f32 sp3C;
    Vec3f* sp30;
    Vec3f* temp_a0;
    f32 temp_f2;
    s16 temp_a0_3;
    s16 temp_v1_3;
    s32 temp_v1;
    s32 temp_v1_2;
    u8 temp_a0_2;
    u8* temp_v0;
    void* temp_t0;
    void* temp_v0_2;
    void* temp_v0_3;
    f32 phi_f12;
    f32 phi_f14;
    s32 phi_v1;
    s16 phi_v1_2;

    temp_v0 = arg1->setupPathList + (arg0->unk2BC * 8);
    sp68 = (s32) temp_v0->unk0;
    sp6C = temp_v0;
    temp_t0 = Lib_SegmentedToVirtual(temp_v0->unk4);
    temp_a0 = arg3 + 0x24;
    if (sp68 == 0) {
        return 0;
    }
    sp30 = temp_a0;
    sp64 = temp_t0;
    if (Math3D_Distance(temp_a0, arg0 + 0x24) < 800.0f) {
        if (arg2 == 0) {
            arg0->unk2F4 = (s32) (arg0->unk2F4 | 0x200);
        } else {
            arg0->unk2F4 = (s32) (arg0->unk2F4 | 0x400);
        }
        arg3->unk540 = (f32) sp30->x;
        arg3->unk544 = (f32) sp30->y;
        arg3->unk55C = 0x32;
        arg3->unk560 = 0x32;
        arg3->unk564 = 1;
        arg3->unk548 = (f32) sp30->z;
    }
    sp64 = temp_t0;
    Math_Vec3s_ToVec3f((Vec3f* ) &sp50, (arg3->unk200 * 6) + temp_t0);
    temp_v1 = arg3->unk200;
    if (temp_v1 == 0) {
        phi_f12 = (f32) (temp_t0->unk6 - temp_t0->unk0);
        phi_f14 = (f32) (temp_t0->unkA - temp_t0->unk4);
    } else {
        temp_a0_2 = *sp6C;
        if (temp_a0_2 == (temp_v1 + 1)) {
            temp_v0_2 = temp_t0 + (temp_a0_2 * 6);
            phi_f12 = (f32) (temp_v0_2->unk-6 - temp_v0_2->unk-C);
            phi_f14 = (f32) (temp_v0_2->unk-2 - temp_v0_2->unk-8);
        } else {
            temp_v0_3 = temp_t0 + (temp_v1 * 6);
            phi_f12 = (f32) (temp_v0_3->unk6 - temp_v0_3->unk-6);
            phi_f14 = (f32) (temp_v0_3->unkA - temp_v0_3->unk-2);
        }
    }
    sp64 = temp_t0;
    func_8017B7F8(&sp50, Math_Atan2S(phi_f12, phi_f14), &sp4C, &sp48, &sp44);
    if (((arg3->unk24 * sp4C) + (sp48 * arg3->unk2C) + sp44) > 0.0f) {
        temp_v1_2 = arg3->unk200 + 1;
        arg3->unk200 = temp_v1_2;
        phi_v1 = temp_v1_2;
        if (temp_v1_2 >= sp68) {
            arg3->unk200 = 0;
            phi_v1 = 0;
        }
        Math_Vec3s_ToVec3f((Vec3f* ) &sp50, (phi_v1 * 6) + temp_t0);
    }
    arg3->unk32 = Math_Vec3f_Yaw(sp30, (Vec3f* ) &sp50);
    arg3->unk70 = 45.0f;
    sp3C = Math_CosS(arg3->unk30) * arg3->unk70;
    arg3->unk64 = (f32) (Math_SinS(arg3->unk32) * sp3C);
    arg3->unk68 = (f32) (Math_SinS(arg3->unk30) * arg3->unk70);
    temp_f2 = Math_CosS(arg3->unk32) * sp3C;
    temp_a0_3 = arg3->unkBE;
    arg3->unk6C = temp_f2;
    temp_v1_3 = arg3->unk32 - temp_a0_3;
    arg3->unk570 = (f32) (arg3->unk24 + (arg3->unk64 * 0.5f) + arg3->unkA4);
    arg3->unk574 = (f32) (arg3->unk28 + (arg3->unk68 * 0.5f) + arg3->unkA8);
    arg3->unk578 = (f32) (arg3->unk2C + (temp_f2 * 0.5f) + arg3->unkAC);
    if ((s32) temp_v1_3 >= 0x191) {
        phi_v1_2 = 0x190;
    } else {
        phi_v1_2 = temp_v1_3;
        if ((s32) temp_v1_3 < -0x190) {
            phi_v1_2 = -0x190;
        }
    }
    arg3->unkBE = (s16) (temp_a0_3 + phi_v1_2);
    return 0;
}
#else
#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Um_0x80B77770/func_80B783E0.asm")
#endif

#ifdef MIPS_2_C_OUTPUT
? func_80B78764(ObjUm* arg0, GlobalContext* arg1, void* arg2, void* arg3) {
    ? sp30;
    s32 sp28;
    Vec3f* sp24;
    Vec3f* sp20;
    Vec3f* temp_a0_2;
    Vec3f* temp_a1;
    Vec3f* temp_v0;
    s16 temp_v0_3;
    s16 temp_v1_2;
    s32 temp_a0;
    s32 temp_t4;
    s32 temp_t8;
    s32 temp_v0_2;
    s32 temp_v1;
    s32 phi_v1;
    s32 phi_a2;
    s32 phi_v1_2;
    s32 phi_a2_2;
    s32 phi_v1_3;
    s32 phi_v1_4;
    s16 phi_v1_5;

    temp_v1 = arg2->unk55C - 1;
    arg2->unk55C = temp_v1;
    phi_v1_4 = temp_v1;
    if (temp_v1 <= 0) {
        arg2->unk55C = 0;
        if ((arg2->unk550 == 3) && ((arg0->unk2F4 & 0x2000) == 0)) {
            phi_v1 = -1;
            if (arg0->unk314 != 1) {
                phi_v1 = 0;
            }
            phi_a2 = 1;
            phi_v1_2 = phi_v1;
            if ((arg0->unk318 != 1) && ((phi_v1 == -1) || ((phi_a2 = 1, phi_v1_2 = phi_v1, (phi_v1 == 0)) && (sp28 = phi_v1, phi_a2 = 1, phi_v1_2 = phi_v1, (Rand_ZeroOne() < D_80B7C320))))) {
                phi_a2 = 1;
                phi_v1_2 = 1;
            }
            phi_a2_2 = phi_a2;
            phi_v1_3 = phi_v1_2;
            if ((phi_a2 != arg0->unk31C) && ((phi_a2_2 = phi_a2, (phi_v1_2 == -1)) || ((phi_a2_2 = phi_a2, phi_v1_3 = phi_v1_2, (phi_v1_2 != -1)) && (sp28 = phi_v1_2, phi_a2_2 = 1, phi_v1_3 = phi_v1_2, phi_a2_2 = 1, (Rand_ZeroOne() < D_80B7C324))))) {
                phi_v1_3 = 2;
            }
            temp_t8 = phi_v1_3 * 4;
            temp_v0 = arg0 + temp_t8;
            temp_a0 = temp_v0->unk314;
            if (phi_a2_2 != temp_a0) {
                temp_v0->unk320 = phi_a2_2;
                if (temp_a0 == 2) {
                    sp24 = temp_v0;
                    func_8019F1C0(arg0 + (phi_v1_3 * 0xC) + 0x32C, 0x2891U);
                } else {
                    sp24 = temp_v0;
                    func_8019F1C0(arg0 + (phi_v1_3 * 0xC) + 0x32C, 0x297EU);
                }
                temp_t4 = (arg0 + temp_t8)->unk314 - 1;
                (arg0 + temp_t8)->unk314 = temp_t4;
                if (temp_t4 <= 0) {
                    (arg0 + temp_t8)->unk314 = 1;
                }
            }
        }
        func_80B781DC(arg0, arg2, arg3, arg1);
        phi_v1_4 = arg2->unk55C;
    }
    Math3D_Lerp(arg2 + 0x540, arg0 + (arg2->unk550 * 0xC) + 0x360, 1.0f - ((f32) phi_v1_4 / (f32) arg2->unk560), (Vec3f* ) &sp30);
    temp_v0_2 = arg2->unk550;
    arg2->unk570 = (s32) sp30.unk0;
    arg2->unk574 = (s32) sp30.unk4;
    arg2->unk578 = (s32) sp30.unk8;
    arg2->unk588 = (s16) arg0->dyna.actor.shape.rot.y;
    if ((temp_v0_2 == 0xA) || (temp_a0_2 = arg2 + 0x108, (temp_v0_2 == 8))) {
        phi_v1_5 = arg2->unk588;
    } else {
        temp_a1 = arg2 + 0x24;
        sp20 = temp_a1;
        sp24 = temp_a0_2;
        if (Math3D_Distance(temp_a0_2, temp_a1) < 10.0f) {
            phi_v1_5 = arg2->unk588;
        } else {
            phi_v1_5 = Math_Vec3f_Yaw(temp_a0_2, temp_a1);
        }
    }
    temp_v0_3 = arg2->unkBE;
    temp_v1_2 = phi_v1_5 - temp_v0_3;
    if ((s32) temp_v1_2 >= 0x191) {
        arg2->unkBE = (s16) (temp_v0_3 + 0x190);
    } else if ((s32) temp_v1_2 < -0x190) {
        arg2->unkBE = (s16) (temp_v0_3 - 0x190);
    } else {
        arg2->unkBE = (s16) (temp_v0_3 + temp_v1_2);
    }
    return 0;
}
#else
#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Um_0x80B77770/func_80B78764.asm")
#endif

#ifdef MIPS_2_C_OUTPUT
? func_80B78A54(ObjUm* arg0, GlobalContext* arg1, s32 arg2, void* arg3, void* arg4) {
    s16 sp36;
    void* sp30;
    Vec3f* sp2C;
    Actor* temp_v0;
    Actor* temp_v0_2;
    Vec3f* temp_a1;
    void* temp_v1;
    s32 phi_v0;
    s32 phi_v0_2;

    temp_v1 = arg0 + (arg2 * 0x4C);
    if ((temp_v1->unk435 & 2) != 0) {
        temp_a1 = arg3 + 0x24;
        if (arg3->unk550 == 3) {
            sp30 = temp_v1;
            sp2C = temp_a1;
            sp36 = Math_Vec3f_Yaw(arg0 + 0x24, temp_a1) - arg0->dyna.actor.shape.rot.y;
            temp_v1->unk435 = (u8) (temp_v1->unk435 & 0xFFFD);
            func_8019F1C0(arg3 + 0xEC, 0x393BU);
            arg3->unk54C = 0xF;
            if (Math_SinS(sp36) > 0.0f) {
                if (arg4->unk550 != 0xA) {
                    phi_v0 = 0xA;
                } else {
                    phi_v0 = 8;
                }
                arg3->unk550 = phi_v0;
                arg3->unk568 = -1.0f;
            } else {
                if (arg4->unk550 != 8) {
                    phi_v0_2 = 8;
                } else {
                    phi_v0_2 = 0xA;
                }
                arg3->unk550 = phi_v0_2;
                arg3->unk568 = 1.0f;
            }
            temp_v0 = arg3->unk38C;
            arg3->unk540 = (f32) sp2C->x;
            arg3->unk544 = (f32) sp2C->y;
            arg3->unk55C = 0x28;
            arg3->unk560 = 0x28;
            arg3->unk564 = 1;
            arg3->unk548 = (f32) sp2C->z;
            if (temp_v0 != 0) {
                temp_v0->colorFilterTimer = 0x14;
                func_800BCB70(arg3->unk38C, 0x4000, 0xFF, 0, (s16) 0x28);
            }
        } else {
            temp_v0_2 = arg3->unk38C;
            if (temp_v0_2 != 0) {
                temp_v0_2->colorFilterTimer = 0x14;
                func_800BCB70(arg3->unk38C, 0x4000, 0xFF, 0, (s16) 0x28);
            }
            func_8019F1C0(arg3 + 0xEC, 0x393BU);
        }
    }
    return 0;
}
#else
#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Um_0x80B77770/func_80B78A54.asm")
#endif

#ifdef MIPS_2_C_OUTPUT
? func_80B78C18(ObjUm* arg0, GlobalContext* arg1) {
    void* temp_s1;
    void* temp_s2;

    temp_s1 = arg0->unk358;
    temp_s2 = arg0->unk35C;
    if ((arg0->unk2F4 & 0x200) == 0) {
        func_80B783E0(arg0, arg1, 0, temp_s1);
    } else {
        func_80B78764(arg0, arg1, temp_s1, temp_s2);
    }
    if ((arg0->unk2F4 & 0x400) == 0) {
        func_80B783E0(arg0, arg1, 1, temp_s2);
    } else {
        func_80B78764(arg0, arg1, temp_s2, temp_s1);
    }
    func_80B78A54(arg0, arg1, 0, temp_s1, temp_s2);
    func_80B78A54(arg0, arg1, 1, temp_s2, temp_s1);
    return 0;
}
#else
#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Um_0x80B77770/func_80B78C18.asm")
#endif

#ifdef MIPS_2_C_OUTPUT
? func_80B78D08(ObjUm* arg0, GlobalContext* arg1) {
    CollisionCheckContext* sp18;
    Collider* temp_a2;
    CollisionCheckContext* temp_a1;
    void* temp_v0;
    void* temp_v1;

    temp_v0 = arg0->unk358;
    temp_v1 = arg0->unk35C;
    temp_a2 = arg0 + 0x424;
    arg0->unk_424.dim.pos.x = (s16) (s32) temp_v0->unk24;
    arg0->unk_424.dim.pos.y = (s16) (s32) (temp_v0->unk28 + 70.0f);
    arg0->unk_424.dim.pos.z = (s16) (s32) temp_v0->unk2C;
    arg0->unk_470.dim.pos.x = (s16) (s32) temp_v1->unk24;
    arg0->unk_470.dim.pos.y = (s16) (s32) (temp_v1->unk28 + 70.0f);
    arg0->unk_470.dim.pos.z = (s16) (s32) temp_v1->unk2C;
    arg0 = arg0;
    temp_a1 = arg1 + 0x18884;
    sp18 = temp_a1;
    CollisionCheck_SetAC(arg1, temp_a1, temp_a2);
    CollisionCheck_SetAC(arg1, temp_a1, arg0 + 0x470);
    return 0;
}
#else
#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Um_0x80B77770/func_80B78D08.asm")
#endif

#ifdef MIPS_2_C_OUTPUT
SaveContext* func_80B78DF0(ObjUm* arg0, GlobalContext* arg1) {
    func_80B78C18(arg0, arg1);
    func_80B78D08(arg0, arg1);
    return NULL;
}
#else
#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Um_0x80B77770/func_80B78DF0.asm")
#endif

void func_80B78E2C(ObjUm* this, ObjUmActionFunc arg1) {
    this->unk_15C = arg1;
}

#ifdef MIPS_2_C_OUTPUT
void* func_80B78E38(ObjUm* arg0, GlobalContext* arg1) {
    void* temp_v0;
    void* temp_v1;

    temp_v0 = arg1->actorCtx.actorList[2].first;
    temp_v1 = arg0 + 0x308;
    if ((arg0->unk2F4 & 0x20) != 0) {
        temp_v0->unk24 = (s32) temp_v1->unk0;
        temp_v0->unk28 = (s32) temp_v1->unk4;
        temp_v0->unk2C = (s32) temp_v1->unk8;
        temp_v0->unk108 = (s32) temp_v1->unk0;
        temp_v0->unk10C = (s32) temp_v1->unk4;
        temp_v0->unk110 = (s32) temp_v1->unk8;
    }
    return temp_v0;
}
#else
#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Um_0x80B77770/func_80B78E38.asm")
#endif

#ifdef MIPS_2_C_OUTPUT
void* func_80B78E88(ObjUm* arg0, GlobalContext* arg1, s16 arg2) {
    s16 temp_v1;
    void* temp_v0;

    temp_v0 = arg1->actorCtx.actorList[2].first;
    temp_v1 = arg0->dyna.actor.shape.rot.y + arg2;
    temp_v0->unkAD4 = temp_v1;
    temp_v0->unk32 = temp_v1;
    temp_v0->unkBE = temp_v1;
    return temp_v0;
}
#else
#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Um_0x80B77770/func_80B78E88.asm")
#endif

#ifdef MIPS_2_C_OUTPUT
void* func_80B78EBC(ObjUm* arg0, GlobalContext* arg1) {
    void* temp_v0;

    temp_v0 = arg1->actorCtx.actorList[2].first;
    temp_v0->unk48 = 0;
    temp_v0->unk4C = 0;
    temp_v0->unk4A = (s16) temp_v0->unkBE;
    temp_v0->unkAAC = 0;
    temp_v0->unkAAE = 0;
    temp_v0->unkAB0 = 0;
    temp_v0->unkAB2 = 0;
    temp_v0->unkAB4 = 0;
    temp_v0->unkAB6 = 0;
    temp_v0->unkAD4 = (s16) temp_v0->unk4A;
    return temp_v0;
}
#else
#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Um_0x80B77770/func_80B78EBC.asm")
#endif

void func_80B78EFC(ObjUm* this, GlobalContext* globalCtx, s16 arg2) {
    Player* player = PLAYER;

    player->actor.focus.rot.y += arg2;
}

#ifdef MIPS_2_C_OUTPUT
void ObjUm_Init(ObjUm* this, GlobalContext* globalCtx) {
    s32 sp54;
    ? sp48;
    SkelAnime* sp44;
    Actor* temp_v0_5;
    PosRot* temp_a3;
    SkelAnime* temp_a1;
    f32* temp_a0;
    s16 temp_v0;
    s32 temp_a2;
    s32 temp_v1;
    u16 temp_v0_2;
    u8 temp_v0_3;
    u8 temp_v0_4;
    ObjUm* phi_v0;
    f32* phi_a0;
    s32 phi_v1;

    sp54 = 1;
    BcCheck3_BgActorInit((DynaPolyActor* ) this, 0);
    this->unk350 = 0;
    temp_a3 = &this->dyna.actor.world;
    this->unk2C4 = (f32) temp_a3->pos.x;
    this->unk2C8 = (f32) temp_a3->pos.y;
    this->unk2CC = (f32) temp_a3->pos.z;
    this->unk2DC = (f32) temp_a3->pos.x;
    this->unk2E0 = (f32) temp_a3->pos.y;
    this->unk2E4 = (f32) temp_a3->pos.z;
    this->unk308 = (f32) temp_a3->pos.x;
    this->unk30C = (f32) temp_a3->pos.y;
    this->unk310 = (f32) temp_a3->pos.z;
    phi_v0 = this;
    phi_a0 = this + 0x32C;
    phi_v1 = 0;
    do {
        phi_v0->unk314 = 5;
        phi_v0->unk320 = 0;
        temp_v1 = phi_v1 + 1;
        *phi_a0 = (f32) D_801D15B0.x;
        temp_a0 = phi_a0 + 0xC;
        temp_a0->unk-8 = (f32) D_801D15B0.y;
        temp_a0->unk-4 = (f32) D_801D15B0.z;
        phi_v0 += 4;
        phi_a0 = temp_a0;
        phi_v1 = temp_v1;
    } while (temp_v1 != 3);
    this->unk2B8 = NULL;
    this->unk354 = 0;
    this->unk420 = 0;
    this->unk_4BC = (f32) temp_a3->pos.x;
    this->unk4C0 = (f32) temp_a3->pos.y;
    this->unk4CC = 0;
    this->unk4D4 = 0;
    this->unk2F4 = 0;
    this->dyna.actor.gravity = -3.5f;
    this->unk4C4 = (f32) temp_a3->pos.z;
    Actor_ProcessInitChain((Actor* ) this, D_80B7C254);
    ActorShape_Init(&this->dyna.actor.shape, 0.0f, NULL, 50.0f);
    temp_a1 = &this->unk_160;
    sp44 = temp_a1;
    SkelAnime_InitSV(globalCtx, temp_a1, &D_06011DF8, NULL, this->unk_1A4, this->unk_228, 0x16);
    SkelAnime_ChangeAnimDefaultRepeat(sp44, &D_06012CC0);
    this->unk_2AC = 0;
    func_80B7B154(this, globalCtx);
    this->unk2AE = (s16) ((s32) (this->dyna.actor.params & 0xFF00) >> 8);
    this->unk2B0 = (s16) (this->dyna.actor.params & 0xFF);
    if ((gSaveContext.unkF0E & 1) == 0) {
        Actor_MarkForDeath((Actor* ) this);
        return;
    }
    temp_v0 = this->unk2AE;
    if (temp_v0 == 0) {
        func_80B78E2C(this, func_80B7AEFC);
block_32:
        sp48.unk0 = (s32) D_801D15BC.unk0;
        sp48.unk4 = (u16) D_801D15BC.unk4;
        this->unk2FE = (unaligned s32) sp48.unk0;
        this->unk302 = (u16) sp48.unk4;
        this->unk2F8 = (unaligned s32) sp48.unk0;
        this->unk2FC = (u16) sp48.unk4;
        if (sp54 != 0) {
            BcCheck3_BgActorInit((DynaPolyActor* ) this, 0);
            BgCheck3_LoadMesh(globalCtx, (DynaPolyActor* ) this, &D_06007E20);
        } else {
            BcCheck3_BgActorInit((DynaPolyActor* ) this, 3);
            BgCheck3_LoadMesh(globalCtx, (DynaPolyActor* ) this, &D_06007F50);
        }
        temp_a2 = this->dyna.bgId;
        if (temp_a2 == 0x32) {
            Actor_MarkForDeath((Actor* ) this);
            return;
        }
        func_800C636C(globalCtx, &globalCtx->colCtx.dyna, temp_a2);
        temp_v0_5 = Actor_Spawn(&globalCtx->actorCtx, globalCtx, 0xD, this->dyna.actor.world.pos.x, this->dyna.actor.world.pos.y, this->dyna.actor.world.pos.z, (s16) 0, (s16) (s32) this->dyna.actor.shape.rot.y, (s16) 0, (s16) 0x8012);
        this->unk2B8 = temp_v0_5;
        if (temp_v0_5 == 0) {
            Actor_MarkForDeath((Actor* ) this);
            return;
        }
        Collider_InitAndSetCylinder(globalCtx, &this->unk_424, (Actor* ) this, &D_80B7C138);
        Collider_InitAndSetCylinder(globalCtx, &this->unk_470, (Actor* ) this, &D_80B7C138);
        return;
    }
    if (temp_v0 == 1) {
        this->unk2BC = (s32) this->unk2B0;
        if ((gSaveContext.unkF17 & 0x80) != 0) {
            sp54 = 0;
            this->unk2F4 = (s32) (this->unk2F4 | 0x100);
            func_80B78E2C(this, func_80B7A144);
            func_800FE484();
            goto block_32;
        }
        if (((gSaveContext.unkF1A & 0x80) != 0) || (temp_v0_2 = gSaveContext.time, (((s32) temp_v0_2 < 0xCAAA) == 0)) || ((s32) temp_v0_2 < 0x4001) || (temp_v0_3 = gSaveContext.unkF2C, ((temp_v0_3 & 1) != 0)) || ((temp_v0_3 & 2) != 0)) {
            Actor_MarkForDeath((Actor* ) this);
            return;
        }
        this->dyna.actor.targetMode = 6;
        this->unk2B4 = 0;
        func_80B78E2C(this, func_80B79A50);
        goto block_32;
    }
    if (temp_v0 == 2) {
        if (((gSaveContext.unkF17 & 0x80) == 0) || (temp_v0_4 = gSaveContext.unkF2C, ((temp_v0_4 & 1) != 0))) {
            Actor_MarkForDeath((Actor* ) this);
            return;
        }
        if ((temp_v0_4 & 2) == 0) {
            this->unk2BC = (s32) this->unk2B0;
            sp54 = 0;
            func_800FE484(this, func_80B7AEFC);
            func_80B78E2C(this, func_80B7A400);
            this->unk354 = 0;
            func_80B78E88(this, globalCtx, 0);
        }
        goto block_32;
    }
    if (temp_v0 == 3) {
        if ((gSaveContext.unkF17 & 0x80) == 0) {
            Actor_MarkForDeath((Actor* ) this);
            return;
        }
        this->unk2BC = (s32) this->unk2B0;
        sp54 = 0;
        func_800FE484(this, func_80B7AEFC);
        func_80B78E2C(this, func_80B7AC94);
        this->unk354 = 0;
        func_80B78E88(this, globalCtx, 0);
        goto block_32;
    }
    if (temp_v0 == 4) {
        if (((gSaveContext.unkF2C & 1) == 0) || ((gSaveContext.unkF33 & 2) != 0)) {
            Actor_MarkForDeath((Actor* ) this);
            return;
        }
        this->unk2BC = (s32) this->unk2B0;
        sp54 = 0;
        func_800FE484(this, func_80B7AEFC);
        func_80B78E2C(this, func_80B7AE58);
        this->unk354 = 0;
        func_80B78E88(this, globalCtx, 0);
        func_801A3098(0x19);
        goto block_32;
    }
    this->unk2AE = 0;
    func_80B78E2C(this, func_80B7AEFC);
    goto block_32;
}
#else
#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Um_0x80B77770/ObjUm_Init.asm")
#endif

void ObjUm_Destroy(Actor* thisx, GlobalContext* globalCtx) {
    ObjUm* this = THIS;
    s32 i;

    BgCheck_RemoveActorMesh(globalCtx, &globalCtx->colCtx.dyna, this->dyna.bgId);

    for (i = 0; i < ARRAY_COUNT(this->unk_32C); i++) {
        func_801A72CC(&this->unk_32C[i]);
    }

    Collider_DestroyCylinder(globalCtx, &this->unk_424);
    Collider_DestroyCylinder(globalCtx, &this->unk_470);
}

//#ifdef MIPS_2_C_OUTPUT
void func_80B79524(ObjUm* this) {

    Actor_MarkForDeath(this);
    if (this->unk_2B8 != NULL) {
        Actor_MarkForDeath(this->unk_2B8);
    }
}
//#else
//#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Um_0x80B77770/func_80B79524.asm")
//#endif

#ifdef MIPS_2_C_OUTPUT
void func_80B79560(GlobalContext* arg0, ObjUm* arg1, s32 arg2, u16 arg3) {
    if ((arg3 & 0xFFFF) == 0x33BF) {
        func_80B78E2C(arg1, func_80B7AC94);
    }
}
#else
#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Um_0x80B77770/func_80B79560.asm")
#endif

/*
Failed to decompile function func_80B795A0:

Found jr instruction at ovl_Obj_Um_0x80B77770.asm line 2072, but the corresponding jump table is not provided.

Please include it in the input .s file(s), or in an additional file.
It needs to be within ".section .rodata" or ".section .late_rodata".

(You might need to pass --goto and --no-andor flags as well, to get correct control flow for non-jtbl switch jumps.)
*/
#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Um_0x80B77770/func_80B795A0.asm")

#ifdef MIPS_2_C_OUTPUT
s32 func_80B79734(GlobalContext* arg0, ObjUm* arg1, s32 arg2) {
    s32 sp20;
    MessageContext* sp18;
    MessageContext* temp_a0;
    s32 temp_v0;

    sp20 = 0;
    temp_a0 = arg0 + 0x4908;
    sp18 = temp_a0;
    temp_v0 = func_80152498(temp_a0);
    if (temp_v0 != 2) {
        if ((temp_v0 != 4) && (temp_v0 != 5)) {

        } else if ((func_80147624(arg0) != 0) && (func_80B795A0(arg0, arg1, arg2) != 0)) {
            sp18->unk11F22 = 0x43;
            sp20 = 1;
        }
        return sp20;
    }
    func_80B79560(arg0, arg1, arg2, arg1->dyna.actor.textId);
    return 1;
}
#else
#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Um_0x80B77770/func_80B79734.asm")
#endif

#ifdef MIPS_2_C_OUTPUT
u16 func_80B797EC(GlobalContext* arg0, Actor* arg1, s32 arg2) {
    u16 phi_v1;
    u16 phi_v1_2;

    phi_v1 = 0x33B7U;
    if (gSaveContext.playerForm == 4) {
        if ((gSaveContext.unkF17 & 0x40) != 0) {
            phi_v1 = 0x33CFU;
        } else {
            phi_v1 = 0x33B4U;
        }
    }
    phi_v1_2 = phi_v1;
    if (phi_v1 == 0) {
        phi_v1_2 = 1U;
    }
    return phi_v1_2;
}
#else
#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Um_0x80B77770/func_80B797EC.asm")
#endif

#ifdef MIPS_2_C_OUTPUT
? func_80B7984C(GlobalContext* arg0, Actor* arg1, s32 arg2, s32* arg3) {
    f32 temp_f0;
    s16 temp_v0_2;
    s32 temp_v0;
    s32* temp_a3;
    s32 phi_v1;
    u16 phi_v0;

    temp_v0 = *arg3;
    if (temp_v0 == 4) {
block_25:
        return 0;
    }
    if (temp_v0 == 2) {
        func_801518B0(arg0, (u32) arg1->textId, arg1);
        *arg3 = 1;
        return 0;
    }
    if (temp_v0 == 3) {
        func_80151938(arg0, arg1->textId);
        *arg3 = 1;
        return 0;
    }
    temp_a3 = arg3;
    if (func_800B84D0(arg1, arg0) != 0) {
        *temp_a3 = 1;
        return 1;
    }
    if (*temp_a3 == 1) {
        arg3 = temp_a3;
        if (func_80B79734(arg0, (ObjUm* ) arg1, arg2, temp_a3) != 0) {
            *arg3 = 0;
        }
    } else {
        temp_v0_2 = arg1->yawTowardsPlayer - arg1->shape.rot.y;
        phi_v1 = temp_v0_2 << 0x10;
        if ((s32) temp_v0_2 < 0) {
            phi_v1 = (s32) temp_v0_2 * -0x10000;
        }
        if ((phi_v1 >> 0x10) >= 0x4E20) {

        } else {
            temp_f0 = arg1->xyzDistToPlayerSq;
            if ((D_80B7C398 < temp_f0) && (arg1->isTargeted == 0)) {

            } else if (temp_f0 <= D_80B7C39C) {
                if (func_800B8614(arg1, arg0, 50.0f) != 0) {
                    phi_v0 = func_80B797EC(arg0, arg1, arg2);
block_24:
                    arg1->textId = phi_v0;
                }
            } else if (func_800B863C(arg1, arg0) != 0) {
                phi_v0 = func_80B797EC(arg0, arg1, arg2);
                goto block_24;
            }
        }
    }
    goto block_25;
}
#else
#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Um_0x80B77770/func_80B7984C.asm")
#endif

s32 func_80B79A24(s32 arg0) {
    if ((arg0 == 1) || (arg0 == 2) || (arg0 == 3)) {
        return 1;
    }
    return 0;
}

#ifdef MIPS_2_C_OUTPUT
void func_80B79A50(ObjUm* arg0, GlobalContext* arg1) {
    Actor* sp24;
    u16 temp_v0;
    u16 temp_v0_2;

    sp24 = arg1->actorCtx.actorList[2].first;
    arg0->dyna.actor.flags |= 1;
    SkelAnime_FrameUpdateMatrix(&arg0->unk_160);
    func_80B7B18C(arg0, arg1, 2);
    arg0->unk2F4 = (s32) (arg0->unk2F4 | 8);
    temp_v0 = gSaveContext.time;
    if (((s32) temp_v0 >= 0xC001) && ((s32) temp_v0 < 0xCAAB)) {
        if ((sp24->unkA6C << 8) >= 0) {
            func_80B7984C(arg1, (Actor* ) arg0, 0, arg0 + 0x2B4);
        }
    } else if ((func_80B79A24(arg0->unk2B4) == 0) && ((s32) gSaveContext.time >= 0xCAAB)) {
        gSaveContext.unkF1A = (u8) (gSaveContext.unkF1A | 0x80);
        func_80B78E2C(arg0, func_80B79F10);
    }
    temp_v0_2 = arg1->msgCtx.unk11F04;
    if (temp_v0_2 != 0x33B4) {
        if (temp_v0_2 != 0x33B5) {
            if (temp_v0_2 != 0x33B7) {
                arg0->unk4CC = 0;
                arg0->unk4D4 = 0;
                return;
            }
block_11:
            arg0->unk4CC = 0;
            arg0->unk4D4 = 1;
            return;
        }
        arg0->unk4CC = 3;
        arg0->unk4D4 = 1;
        return;
    }
    goto block_11;
}
#else
#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Um_0x80B77770/func_80B79A50.asm")
#endif

#ifdef MIPS_2_C_OUTPUT
s32 func_80B79BA0(ObjUm* arg0, GlobalContext* arg1) {
    void* sp6C;
    s32 sp68;
    void* sp64;
    ? sp50;
    f32 sp4C;
    f32 sp48;
    f32 sp44;
    s32 sp3C;
    f32 temp_f2;
    s16 temp_a2_2;
    s16 temp_a2_3;
    s16 temp_v0_3;
    s16 temp_v1_3;
    s32 temp_v0_4;
    s32 temp_v1;
    s32 temp_v1_2;
    u8 temp_a0;
    u8 temp_t1;
    void* temp_a2;
    void* temp_t0;
    void* temp_v0;
    void* temp_v0_2;
    f32 phi_f12;
    f32 phi_f14;
    s32 phi_v0;
    s32 phi_v1;
    s16 phi_a2;

    temp_a2 = arg1->setupPathList + (arg0->unk2BC * 8);
    temp_t1 = temp_a2->unk0;
    sp6C = temp_a2;
    sp68 = (s32) temp_t1;
    temp_t0 = Lib_SegmentedToVirtual(temp_a2->unk4);
    sp3C = 0;
    if (temp_t1 == 0) {
        return 0;
    }
    sp68 = (s32) temp_t1;
    sp64 = temp_t0;
    sp6C = temp_a2;
    Math_Vec3s_ToVec3f((Vec3f* ) &sp50, (arg0->unk2C0 * 6) + temp_t0);
    temp_v1 = arg0->unk2C0;
    if (temp_v1 == 0) {
        phi_f12 = (f32) (temp_t0->unk6 - temp_t0->unk0);
        phi_f14 = (f32) (temp_t0->unkA - temp_t0->unk4);
    } else {
        temp_a0 = temp_a2->unk0;
        if (temp_a0 == (temp_v1 + 1)) {
            temp_v0 = temp_t0 + (temp_a0 * 6);
            phi_f12 = (f32) (temp_v0->unk-6 - temp_v0->unk-C);
            phi_f14 = (f32) (temp_v0->unk-2 - temp_v0->unk-8);
        } else {
            temp_v0_2 = temp_t0 + (temp_v1 * 6);
            phi_f12 = (f32) (temp_v0_2->unk6 - temp_v0_2->unk-6);
            phi_f14 = (f32) (temp_v0_2->unkA - temp_v0_2->unk-2);
        }
    }
    sp64 = temp_t0;
    sp68 = (s32) temp_t1;
    func_8017B7F8(&sp50, Math_Atan2S(phi_f12, phi_f14), &sp4C, &sp48, &sp44);
    if (((arg0->dyna.actor.world.pos.x * sp4C) + (sp48 * arg0->dyna.actor.world.pos.z) + sp44) > 0.0f) {
        temp_v1_2 = arg0->unk2C0 + 1;
        arg0->unk2C0 = temp_v1_2;
        if (temp_v1_2 >= (temp_t1 - 7)) {
            sp3C = 3;
        }
        phi_v0 = sp3C;
        if (temp_v1_2 >= (temp_t1 - 3)) {
            phi_v0 = 1;
        }
        if (temp_v1_2 >= (temp_t1 - 2)) {
            phi_v0 = 4;
        }
        phi_v1 = temp_v1_2;
        if (temp_v1_2 >= (s32) temp_t1) {
            arg0->unk2C0 = 0;
            phi_v0 = 2;
            phi_v1 = 0;
        }
        sp3C = phi_v0;
        Math_Vec3s_ToVec3f((Vec3f* ) &sp50, (phi_v1 * 6) + temp_t0);
    }
    if (arg0->unk2B8 != 0) {
        arg0->dyna.actor.world.rot.y = Math_Vec3f_Yaw(arg0 + 0x24, (Vec3f* ) &sp50);
        func_800F415C(arg0->unk2B8, &sp50, 0x190);
        temp_v1_3 = arg0->dyna.actor.shape.rot.y;
        temp_v0_3 = arg0->unk2B8->unkBE;
        temp_a2_2 = temp_v0_3 - temp_v1_3;
        temp_a2_3 = temp_a2_2;
        temp_f2 = fabsf((f32) temp_a2_3);
        if (temp_f2 < D_80B7C3A0) {
            if (temp_f2 < 100.0f) {
                arg0->dyna.actor.shape.rot.y = temp_v0_3;
                phi_a2 = temp_a2_3;
            } else if ((s32) temp_a2_3 > 0) {
                arg0->dyna.actor.shape.rot.y = temp_v1_3 + 0x64;
                phi_a2 = 0x64;
            } else {
                phi_a2 = temp_a2_3;
                if ((s32) temp_a2_3 < 0) {
                    arg0->dyna.actor.shape.rot.y = temp_v1_3 - 0x64;
                    phi_a2 = -0x64;
                }
            }
        } else if ((s32) temp_a2_3 > 0) {
            arg0->dyna.actor.shape.rot.y = temp_v1_3 + 0x190;
            phi_a2 = 0x190;
        } else {
            phi_a2 = temp_a2_3;
            if ((s32) temp_a2_3 < 0) {
                arg0->dyna.actor.shape.rot.y = temp_v1_3 - 0x190;
                phi_a2 = -0x190;
            }
        }
        if ((arg0->unk2F4 & 0x14) != 0) {
            func_80B78EFC(arg0, arg1, phi_a2);
        }
    }
    temp_v0_4 = arg0->unk304;
    if (temp_v0_4 == 0) {
        arg0->dyna.actor.speedXZ = 4.0f;
    } else if (temp_v0_4 == 1) {
        arg0->dyna.actor.speedXZ = 8.0f;
    }
    return sp3C;
}
#else
#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Um_0x80B77770/func_80B79BA0.asm")
#endif

#ifdef MIPS_2_C_OUTPUT
void func_80B79F10(ObjUm* arg0, GlobalContext* arg1) {
    ObjUm* temp_a3;
    s32 temp_v0;

    temp_a3 = arg0;
    temp_a3->unk_2AC = (s16) temp_a3->unk_2AC + 0x3E8;
    temp_a3->unk2F4 = (s32) (temp_a3->unk2F4 & ~8);
    arg0 = temp_a3;
    func_80B7B18C(temp_a3, arg1, 0, temp_a3);
    temp_v0 = func_80B79BA0(arg0, arg1);
    if ((temp_v0 == 1) || (temp_v0 == 2)) {
        if ((*(&gSaveContext + 0xF17) & 0x80) != 0) {
            ActorCutscene_Stop((s16) arg0->dyna.actor.cutscene);
            arg1->nextEntranceIndex = 0x3E50;
            arg1->unk_1887F = 0x40;
            gSaveContext.nextTransition = 3U;
            arg1->sceneLoadFlag = 0x14;
            return;
        }
        func_80B79524((Actor* ) arg0);
        return;
    }
    Actor_SetVelocityAndMoveYRotationAndGravity((Actor* ) arg0);
}
#else
#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Um_0x80B77770/func_80B79F10.asm")
#endif

#ifdef MIPS_2_C_OUTPUT
void func_80B79FFC(ObjUm* arg0) {
    func_80B7B18C(arg0, (GlobalContext* )2);
    if (ActorCutscene_GetCanPlayNext((s16) arg0->dyna.actor.cutscene) != 0) {
        ActorCutscene_StartAndSetUnkLinkFields((s16) arg0->dyna.actor.cutscene, (Actor* ) arg0);
        arg0->unk4C8 = (u16) gSaveContext.time;
        func_80B78E2C(arg0, func_80B7A0E0);
        return;
    }
    ActorCutscene_SetIntentToPlay((s16) arg0->dyna.actor.cutscene);
}
#else
#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Um_0x80B77770/func_80B79FFC.asm")
#endif

#ifdef MIPS_2_C_OUTPUT
s32 func_80B7A070(ObjUm* arg0, GlobalContext* arg1) {
    func_80B79F10(arg0, arg1);
    func_80B78E88(arg0, arg1, 0);
    if (arg1->msgCtx.unk11F04 == 0x33B6) {
        arg0->unk4CC = 1;
        arg0->unk4D4 = 1;
        return 1;
    }
    arg0->unk4CC = 0;
    arg0->unk4D4 = 0;
    return 1;
}
#else
#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Um_0x80B77770/func_80B7A070.asm")
#endif

#ifdef MIPS_2_C_OUTPUT
void func_80B7A0E0(ObjUm* arg0, GlobalContext* arg1) {
    func_80B7B18C(arg0, arg1, 2);
    if (arg0->unk4C8 != gSaveContext.time) {
        func_80B7B18C(arg0, arg1, 0);
        func_80B78E2C(arg0, (void (*)(ObjUm* this, GlobalContext* globalCtx)) func_80B7A070);
    }
}
#else
#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Um_0x80B77770/func_80B7A0E0.asm")
#endif

#ifdef MIPS_2_C_OUTPUT
void func_80B7A144(ObjUm* arg0, GlobalContext* arg1) {
    Actor* sp1C;
    Actor* temp_v0;
    s32 temp_t7;
    s32 temp_t9;

    temp_v0 = arg1->actorCtx.actorList[2].first;
    sp1C = temp_v0;
    func_80B78E38();
    temp_t7 = arg0->unk2F4 | 0x100;
    temp_t9 = temp_t7 | 4;
    arg0->unk2F4 = temp_t7;
    arg0->unk2F4 = temp_t9;
    temp_v0->unkA6C = (s32) (temp_v0->unkA6C | 0x20);
    func_80B7B18C(arg0, arg1, 2);
    func_80B78E2C(arg0, func_80B79FFC);
}
#else
#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Um_0x80B77770/func_80B7A144.asm")
#endif

#ifdef MIPS_2_C_OUTPUT
u16 func_80B7A1B4(ObjUm* arg0, ObjUm* arg1) {
    s32 temp_t7;
    u16 temp_v0;

    func_80B78E38(arg1);
    temp_t7 = arg0->unk2F4 | 4;
    arg0->unk2F4 = temp_t7;
    temp_v0 = arg1->unk1680C;
    if (temp_v0 != 0x33B8) {
        if (temp_v0 != 0x33B9) {
            arg0->unk2F4 = (s32) (temp_t7 & ~0x800);
            arg0->unk4CC = 0;
        } else {
            arg0->unk4CC = 2;
        }
        arg0->unk4D4 = 0;
        return temp_v0;
    }
    arg0->unk4CC = 0;
    arg0->unk4D4 = 3;
    return temp_v0;
}
#else
#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Um_0x80B77770/func_80B7A1B4.asm")
#endif

#ifdef MIPS_2_C_OUTPUT
void func_80B7A240(ObjUm* arg0, ObjUm* arg1) {
    ObjUm* temp_a0;
    u16 temp_v0;
    u16 phi_v0;
    ObjUm* phi_a0;

    func_80B7B18C(arg1, (GlobalContext* )2);
    temp_a0 = arg0;
    temp_v0 = gSaveContext.time;
    phi_v0 = temp_v0;
    phi_a0 = temp_a0;
    if (temp_a0->unk4C8 != temp_v0) {
        arg0 = temp_a0;
        func_80B78E2C(temp_a0, func_80B7A2AC);
        phi_v0 = gSaveContext.time;
        phi_a0 = arg0;
    }
    phi_a0->unk4C8 = phi_v0;
    func_80B7A1B4(phi_a0, arg1);
}
#else
#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Um_0x80B77770/func_80B7A240.asm")
#endif

#ifdef MIPS_2_C_OUTPUT
void func_80B7A2AC(ObjUm* arg0, GlobalContext* arg1) {
    s32 temp_v0;
    u16 temp_v0_2;
    u16 phi_v0;

    arg0->unk_2AC = (s16) arg0->unk_2AC + 0x3E8;
    func_80B7B18C(arg0, arg1, 0);
    temp_v0 = func_80B79BA0(arg0, arg1);
    if ((temp_v0 == 1) || (temp_v0 == 2)) {
        arg1->nextEntranceIndex = 0xCE40;
        arg1->unk_1887F = 0x40;
        gSaveContext.nextTransition = 3U;
        arg1->sceneLoadFlag = 0x14;
        return;
    }
    temp_v0_2 = gSaveContext.time;
    phi_v0 = temp_v0_2;
    if (arg0->unk4C8 == temp_v0_2) {
        func_80B78E2C(arg0, (void (*)(ObjUm* this, GlobalContext* globalCtx)) func_80B7A240);
        phi_v0 = gSaveContext.time;
    }
    arg0->unk4C8 = phi_v0;
    Actor_SetVelocityAndMoveYRotationAndGravity((Actor* ) arg0);
    func_80B7A1B4(arg0, (ObjUm* ) arg1);
}
#else
#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Um_0x80B77770/func_80B7A2AC.asm")
#endif

#ifdef MIPS_2_C_OUTPUT
void func_80B7A394(ObjUm* arg0, ObjUm* arg1) {
    ObjUm* temp_a0;

    func_80B78E38(arg1);
    temp_a0 = arg0;
    temp_a0->unk2F4 = (s32) (temp_a0->unk2F4 | 4);
    if (temp_a0->unk4C8 != gSaveContext.time) {
        arg0 = temp_a0;
        func_80B7B18C(temp_a0, (GlobalContext* ) arg1, 0);
        func_80B78E2C(arg0, func_80B7A2AC);
    }
}
#else
#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Um_0x80B77770/func_80B7A394.asm")
#endif

#ifdef MIPS_2_C_OUTPUT
void func_80B7A400(ObjUm* arg0, GlobalContext* arg1) {
    Actor* sp24;
    Actor* temp_v0;

    temp_v0 = arg1->actorCtx.actorList[2].first;
    sp24 = temp_v0;
    func_80B78E38(arg0);
    arg0->unk2F4 = (s32) (arg0->unk2F4 | 4);
    temp_v0->unkA6C = (s32) (temp_v0->unkA6C | 0x20);
    if (ActorCutscene_GetCanPlayNext((s16) arg0->dyna.actor.cutscene) != 0) {
        ActorCutscene_StartAndSetUnkLinkFields((s16) arg0->dyna.actor.cutscene, (Actor* ) arg0);
        arg0->unk4C8 = (u16) gSaveContext.time;
        func_80B78E2C(arg0, (void (*)(ObjUm* this, GlobalContext* globalCtx)) func_80B7A394);
        return;
    }
    ActorCutscene_SetIntentToPlay((s16) arg0->dyna.actor.cutscene);
}
#else
#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Um_0x80B77770/func_80B7A400.asm")
#endif

#ifdef MIPS_2_C_OUTPUT
SaveContext* func_80B7A494(ObjUm* arg0, GlobalContext* arg1) {
    s32 temp_v0;
    u8 temp_t1;
    u8 temp_t9;
    u8 temp_v1;
    SaveContext* phi_return;

    func_80B78E38(arg0, arg1);
    func_80B78E88(arg0, arg1, 0x7FFF);
    arg0->unk_2AC = (s16) arg0->unk_2AC + 0x7D0;
    arg0->unk2F4 = (s32) (arg0->unk2F4 | 0x10);
    func_80B7B18C(arg0, arg1, 1);
    temp_v0 = func_80B79BA0(arg0, arg1);
    if ((temp_v0 == 1) || (temp_v0 == 2)) {
        temp_v1 = gSaveContext.unkF2C;
        gSaveContext.seqIndex = 0xFF;
        gSaveContext.unkF17 = (u8) (gSaveContext.unkF17 & 0x7F);
        gSaveContext.nightSeqIndex = 0xFF;
        phi_return = &gSaveContext;
        if (((temp_v1 & 1) == 0) && (phi_return = &gSaveContext, ((temp_v1 & 2) == 0))) {
            if (arg0->unk4E0 == 0) {
                arg1->nextEntranceIndex = 0x3E60;
                arg1->unk_1887F = 0x40;
                gSaveContext.nextTransition = 3;
                arg1->sceneLoadFlag = 0x14;
                temp_t1 = gSaveContext.unkF2C | 1;
                gSaveContext.unkF2C = temp_t1;
                gSaveContext.unkF2C = (u8) (temp_t1 & 0xFD);
                return &gSaveContext;
            }
            arg1->nextEntranceIndex = 0x6480;
            arg1->unk_1887F = 0x40;
            gSaveContext.nextTransition = 3;
            arg1->sceneLoadFlag = 0x14;
            temp_t9 = gSaveContext.unkF2C | 2;
            gSaveContext.unkF2C = temp_t9;
            gSaveContext.unkF2C = (u8) (temp_t9 & 0xFE);
            return &gSaveContext;
        }
        return phi_return;
    }
    Actor_SetVelocityAndMoveYRotationAndGravity((Actor* ) arg0);
    phi_return = func_80B78DF0(arg0, arg1);
    // Duplicate return node #8. Try simplifying control flow for better match
    return phi_return;
}
#else
#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Um_0x80B77770/func_80B7A494.asm")
#endif

#ifdef MIPS_2_C_OUTPUT
void func_80B7A614(ObjUm* arg0, GlobalContext* arg1) {
    s32 sp20;
    s16 temp_v0_3;
    s32 temp_t9;
    s32 temp_v0;
    s32 temp_v0_2;
    ObjUm* phi_v1;
    s32 phi_v0;
    s16 phi_v1_2;

    func_80B78E38(arg0, arg1);
    func_80B78E88(arg0, arg1, 0x7FFF);
    temp_t9 = arg0->unk2F4 | 0x10;
    arg0->unk2F4 = temp_t9;
    arg0->unk_2AC = (s16) arg0->unk_2AC + 0x7D0;
    arg0->unk2F4 = (s32) (temp_t9 | 0x80);
    func_80B7B18C(arg0, arg1, 1);
    if ((func_80B79BA0(arg0, arg1) == 3) && (arg0->unk4DC == 0)) {
        arg0->unk4DC = 1;
    } else {
        temp_v0 = arg0->unk4DC;
        if (temp_v0 > 0) {
            if (temp_v0 == 1) {
                arg0->unk4E0 = 1;
                phi_v1 = arg0;
                phi_v0 = 0;
loop_6:
                temp_v0_2 = phi_v0 + 4;
                if (phi_v1->unk314 != 1) {
                    arg0->unk4E0 = 0;
                } else {
                    phi_v1 += 4;
                    phi_v0 = temp_v0_2;
                    if (temp_v0_2 != 0xC) {
                        goto loop_6;
                    }
                }
                arg0->unk2F4 = (s32) (arg0->unk2F4 | 0x2000);
            }
            arg0->unk4DC = (s32) (arg0->unk4DC + 1);
        }
    }
    if ((arg0->unk2F4 & 0x2000) != 0) {
        temp_v0_3 = ActorCutscene_GetAdditionalCutscene((s16) arg0->dyna.actor.cutscene);
        phi_v1_2 = temp_v0_3;
        if (arg0->unk4E0 != 0) {
            phi_v1_2 = ActorCutscene_GetAdditionalCutscene(temp_v0_3);
        }
        sp20 = (s32) phi_v1_2;
        if (ActorCutscene_GetCanPlayNext(phi_v1_2) != 0) {
            ActorCutscene_StartAndSetUnkLinkFields(phi_v1_2, (Actor* ) arg0);
            func_80B78E2C(arg0, (void (*)(ObjUm* this, GlobalContext* globalCtx)) func_80B7A494);
            arg0->unk2F4 = (s32) (arg0->unk2F4 & ~0x80);
        } else {
            ActorCutscene_SetIntentToPlay(phi_v1_2);
        }
    }
    Actor_SetVelocityAndMoveYRotationAndGravity((Actor* ) arg0);
    func_80B78DF0(arg0, arg1);
}
#else
#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Um_0x80B77770/func_80B7A614.asm")
#endif

#ifdef MIPS_2_C_OUTPUT
void func_80B7A7AC(ObjUm* arg0, GlobalContext* arg1) {
    void* temp_v0;

    temp_v0 = arg1->actorCtx.actorList[2].first;
    arg0->unk4DC = 0;
    arg0->unk4E0 = 0;
    temp_v0->unkA6C = (s32) (temp_v0->unkA6C & ~0x20);
    func_80B78E38(arg0, arg1);
    func_80B78E88(arg0, arg1, 0x7FFF);
    func_80B78EBC(arg0, arg1);
    arg0->unk2F4 = (s32) (arg0->unk2F4 | 0x10);
    func_80B78DF0(arg0, arg1);
    arg0->unk2F4 = (s32) (arg0->unk2F4 | 4);
    func_80B7B18C(arg0, arg1, 1);
    func_80B78E2C(arg0, func_80B7A614);
}
#else
#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Um_0x80B77770/func_80B7A7AC.asm")
#endif

/*
Failed to decompile function func_80B7A860:

Found jr instruction at ovl_Obj_Um_0x80B77770.asm line 3452, but the corresponding jump table is not provided.

Please include it in the input .s file(s), or in an additional file.
It needs to be within ".section .rodata" or ".section .late_rodata".

(You might need to pass --goto and --no-andor flags as well, to get correct control flow for non-jtbl switch jumps.)
*/
#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Um_0x80B77770/func_80B7A860.asm")

#ifdef MIPS_2_C_OUTPUT
void func_80B7AB78(ObjUm* arg0, ObjUm* arg1) {
    ObjUm* temp_a0;
    u16 temp_v0;
    u16 phi_v0;
    ObjUm* phi_a0;

    func_80B7B18C(arg1, (GlobalContext* )2);
    temp_a0 = arg0;
    temp_v0 = gSaveContext.time;
    phi_v0 = temp_v0;
    phi_a0 = temp_a0;
    if (temp_a0->unk4C8 != temp_v0) {
        arg0 = temp_a0;
        func_80B78E2C(temp_a0, func_80B7ABE4);
        phi_v0 = gSaveContext.time;
        phi_a0 = arg0;
    }
    phi_a0->unk4C8 = phi_v0;
    func_80B7A860(phi_a0, arg1);
}
#else
#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Um_0x80B77770/func_80B7AB78.asm")
#endif

#ifdef MIPS_2_C_OUTPUT
void func_80B7ABE4(ObjUm* this, GlobalContext* globalCtx) {
    u16 temp_v0;
    u16 phi_v0;

    this->unk_2AC = (s16) this->unk_2AC + 0x3E8;
    func_80B7B18C(this, globalCtx, 0);
    if (func_80B79BA0(this, globalCtx) == 2) {
        func_80B79524((Actor* ) this);
        return;
    }
    temp_v0 = gSaveContext.time;
    phi_v0 = temp_v0;
    if (this->unk4C8 == temp_v0) {
        func_80B78E2C(this, (void (*)(ObjUm* this, GlobalContext* globalCtx)) func_80B7AB78);
        phi_v0 = gSaveContext.time;
    }
    this->unk4C8 = phi_v0;
    Actor_SetVelocityAndMoveYRotationAndGravity((Actor* ) this);
    func_80B7A860(this, (ObjUm* ) globalCtx);
}
#else
#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Um_0x80B77770/func_80B7ABE4.asm")
#endif

#ifdef MIPS_2_C_OUTPUT
void func_80B7AC94(ObjUm* this, GlobalContext* globalCtx) {
    Actor* temp_v0;

    temp_v0 = globalCtx->actorCtx.actorList[2].first;
    temp_v0->unkA6C = (s32) (temp_v0->unkA6C | 0x20);
    func_80B78E38(this);
    func_80B78E88(this, globalCtx, 0);
    this->unk2F4 = (s32) (this->unk2F4 | 4);
    if (ActorCutscene_GetCanPlayNext((s16) this->dyna.actor.cutscene) != 0) {
        ActorCutscene_StartAndSetUnkLinkFields((s16) this->dyna.actor.cutscene, (Actor* ) this);
        this->unk4C8 = (u16) gSaveContext.time;
        func_80B78E2C(this, func_80B7ABE4);
        return;
    }
    ActorCutscene_SetIntentToPlay((s16) this->dyna.actor.cutscene);
}
#else
#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Um_0x80B77770/func_80B7AC94.asm")
#endif

#ifdef MIPS_2_C_OUTPUT
void func_80B7AD34(ObjUm* this, GlobalContext* globalCtx) {
    Actor* temp_v0;

    temp_v0 = globalCtx->actorCtx.actorList[2].first;
    temp_v0->unkA6C = (s32) (temp_v0->unkA6C | 0x20);
    func_80B78E38(this, globalCtx);
    func_80B78E88(this, globalCtx, 0);
    this->unk2F4 = (s32) (this->unk2F4 | 4);
    this->unk_2AC = (s16) this->unk_2AC + 0x3E8;
    func_80B7B18C(this, globalCtx, 0);
    if ((func_80B79BA0(this, globalCtx) == 4) && ((gSaveContext.unkF33 & 2) == 0)) {
        ActorCutscene_Stop((s16) this->dyna.actor.cutscene);
        func_801A3F54(0);
        gSaveContext.unkF33 = (u8) (gSaveContext.unkF33 | 2);
        gSaveContext.unk_3F4A = 0xFFF3;
        globalCtx->nextEntranceIndex = 0x5400;
        globalCtx->unk_1887F = 0x40;
        gSaveContext.nextTransition = 3;
        globalCtx->sceneLoadFlag = 0x14;
        gSaveContext.time += 0xAAC;
    }
    Actor_SetVelocityAndMoveYRotationAndGravity((Actor* ) this);
}
#else
#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Um_0x80B77770/func_80B7AD34.asm")
#endif

#ifdef MIPS_2_C_OUTPUT
void func_80B7AE58(ObjUm* this, GlobalContext* globalCtx) {
    Actor* temp_v0;

    temp_v0 = globalCtx->actorCtx.actorList[2].first;
    temp_v0->unkA6C = (s32) (temp_v0->unkA6C | 0x20);
    func_80B78E38(this);
    func_80B78E88(this, globalCtx, 0);
    this->unk2F4 = (s32) (this->unk2F4 | 4);
    func_80B7B18C(this, globalCtx, 2);
    if (ActorCutscene_GetCanPlayNext((s16) this->dyna.actor.cutscene) != 0) {
        ActorCutscene_StartAndSetUnkLinkFields((s16) this->dyna.actor.cutscene, (Actor* ) this);
        func_80B78E2C(this, func_80B7AD34);
        return;
    }
    ActorCutscene_SetIntentToPlay((s16) this->dyna.actor.cutscene);
}
#else
#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Um_0x80B77770/func_80B7AE58.asm")
#endif

#ifdef MIPS_2_C_OUTPUT
void func_80B7AEFC(ObjUm* this, GlobalContext* globalCtx) {
    func_80B7B18C(this, (GlobalContext* )2);
    SkelAnime_FrameUpdateMatrix(&this->unk_160);
}
#else
#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Um_0x80B77770/func_80B7AEFC.asm")
#endif

#ifdef MIPS_2_C_OUTPUT
s32 func_80B7AF30(void* arg0, s32 arg1) {
    ? sp44;
    f32 sp38;
    f32 sp34;
    f32 sp30;
    void* sp28;
    s32 sp24;
    f32 temp_f0;
    f32 temp_f0_2;
    f32 temp_f10;
    f32 temp_f16;
    f32 temp_f16_2;
    f32 temp_f2;
    f32 temp_f2_2;
    f32 temp_f4;
    f32 temp_f8;
    f32 temp_ret_2;
    s16 temp_ret;
    s32 temp_a0;
    s32 temp_cond;
    s32 temp_v0;
    void* temp_a2;
    void* temp_a3;
    s32 phi_return;

    temp_v0 = arg0->unk2F4;
    temp_a2 = arg0 + 0x2C4;
    if ((temp_v0 & 1) == 0) {
        arg0->unkBC = 0;
        arg0->unkC0 = 0;
        return temp_v0;
    }
    arg0->unk2F4 = (s32) (temp_v0 & ~1);
    temp_a3 = arg0 + 0x2DC;
    arg0->unk2D0 = (f32) temp_a2->unk0;
    arg0->unk2D4 = (f32) temp_a2->unk4;
    arg0->unk2D8 = (f32) temp_a2->unk8;
    arg0->unk2E8 = (f32) temp_a3->unk0;
    arg0->unk2EC = (f32) temp_a3->unk4;
    arg0->unk2F0 = (f32) temp_a3->unk8;
    sp28 = temp_a3;
    temp_a0 = arg1 + 0x830;
    sp24 = temp_a0;
    temp_f0 = func_800C3FA0(temp_a0, &sp44, temp_a2, temp_a3);
    temp_cond = temp_f0 == -32000.0f;
    arg0->unk2D4 = temp_f0;
    if (temp_cond) {
        arg0->unk2D4 = (f32) arg0->unk88;
    }
    temp_f0_2 = func_800C3FA0(temp_a0, &sp44, temp_a3, temp_a3);
    arg0->unk2EC = temp_f0_2;
    if (temp_f0_2 == -32000.0f) {
        arg0->unk2EC = (f32) arg0->unk88;
    }
    temp_f10 = (arg0->unk2D0 + arg0->unk2E8) * 0.5f;
    sp30 = temp_f10;
    temp_f4 = (arg0->unk2D4 + arg0->unk2EC) * 0.5f;
    sp34 = temp_f4;
    temp_f8 = (arg0->unk2D8 + arg0->unk2F0) * 0.5f;
    sp38 = temp_f8;
    temp_f2 = temp_f10 - arg0->unk24;
    temp_f16 = temp_f8 - arg0->unk2C;
    arg0->unkBC = Math_Atan2S(temp_f4 - arg0->unk28, sqrtf((temp_f2 * temp_f2) + (temp_f16 * temp_f16)));
    temp_f2_2 = sp30 - arg0->unk2D0;
    temp_f16_2 = sp38 - arg0->unk2D8;
    temp_ret = Math_Atan2S(temp_f4 - arg0->unk2D4, sqrtf((temp_f2_2 * temp_f2_2) + (temp_f16_2 * temp_f16_2)));
    arg0->unkC0 = (s16) -temp_ret;
    phi_return = (s32) temp_ret;
    if ((arg0->unk2F4 & 2) != 0) {
        arg0->unkBC = (s16) (arg0->unkBC + (s32) ((Rand_ZeroOne() * 100.0f) - 50.0f));
        temp_ret_2 = Rand_ZeroOne();
        arg0->unkC0 = (s16) (arg0->unkC0 + (s32) ((temp_ret_2 * 100.0f) - 50.0f));
        phi_return = (bitwise s32) temp_ret_2;
    }
    return phi_return;
}
#else
#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Um_0x80B77770/func_80B7AF30.asm")
#endif

void func_80B7B154(ObjUm* this, GlobalContext* globalCtx) {
    SkelAnime_ChangeAnimDefaultStop(&this->unk_160, &D_06012CC0);
    this->unk_304 = 0;
}

#ifdef MIPS_2_C_OUTPUT
void func_80B7B18C(Actor* arg0, GlobalContext* arg1, s32 arg2) {
    s32 sp3C;
    s32 sp34;
    SkelAnime* sp24;
    AnimationHeader** temp_v0;
    SkelAnime* temp_a0;
    s32 temp_a1;
    s32 temp_lo;
    s32 temp_v1;
    void* temp_v0_2;
    void* temp_v1_2;
    f32 phi_f0;
    s32 phi_a3;

    temp_v1 = arg2;
    temp_a0 = arg0 + 0x160;
    if (*(&D_80B7C260 + (arg2 * 8)) != 0) {
        arg0->unk2F4 = (s32) (arg0->unk2F4 | 2);
    } else {
        arg0->unk2F4 = (s32) (arg0->unk2F4 & ~2);
    }
    if (arg2 == 0) {
        phi_f0 = arg0->speedXZ * 0.25f;
    } else if (arg2 == 1) {
        phi_f0 = arg0->speedXZ * D_80B7C3CC;
    } else {
        phi_f0 = 0.0f;
        if (arg2 == 2) {
            phi_f0 = 1.0f;
        }
    }
    arg0->unk17C = phi_f0;
    phi_a3 = arg2;
    if ((arg0->unk2F4 & 0x800) != 0) {
        arg0->unk17C = 1.0f;
        phi_a3 = -1;
    }
    arg2 = phi_a3;
    sp24 = temp_a0;
    temp_a1 = phi_a3 != arg0->unk304;
    sp3C = temp_a1;
    sp34 = temp_v1;
    if ((SkelAnime_FrameUpdateMatrix(temp_a0) != 0) || (temp_a1 != 0)) {
        arg0->unk304 = arg2;
        if (arg2 != -1) {
            temp_v1_2 = arg0->unk2B8;
            temp_v0 = (arg2 * 8) + &D_80B7C25C;
            if (temp_v1_2 != 0) {
                temp_v1_2->unk538 = arg2;
            }
            if (temp_a1 != 0) {
                SkelAnime_ChangeAnimTransitionStop(temp_a0, *temp_v0, -3.0f);
            } else {
                SkelAnime_ChangeAnimDefaultStop(temp_a0, *temp_v0);
            }
        } else {
            temp_v0_2 = arg0->unk2B8;
            if (temp_v0_2 != 0) {
                temp_v0_2->unk538 = temp_v1;
            }
            if (temp_a1 != 0) {
                SkelAnime_ChangeAnimTransitionStop(temp_a0, *(&D_80B7C274 + (arg2 * -8)), -10.0f);
            } else {
                SkelAnime_ChangeAnimDefaultStop(temp_a0, *(&D_80B7C274 + (arg2 * -8)));
            }
        }
    }
    temp_lo = (s32) arg0->unk2AC / 0x199A;
    if (arg0->unk420 != temp_lo) {
        arg0->unk420 = temp_lo;
        Audio_PlayActorSound2(arg0, 0x2958U);
    }
}
#else
#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Um_0x80B77770/func_80B7B18C.asm")
#endif

/*
Failed to decompile function ObjUm_Update:

Found jr instruction at ovl_Obj_Um_0x80B77770.asm line 4266, but the corresponding jump table is not provided.

Please include it in the input .s file(s), or in an additional file.
It needs to be within ".section .rodata" or ".section .late_rodata".

(You might need to pass --goto and --no-andor flags as well, to get correct control flow for non-jtbl switch jumps.)
*/
#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Um_0x80B77770/ObjUm_Update.asm")


s32 func_80B7B598(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3s* rot, Actor* actor);
#ifdef MIPS_2_C_OUTPUT
s32 func_80B7B598(GlobalContext* arg0, s32 arg1, Gfx** arg2, Vec3f* arg3, Vec3s* arg4, Actor* arg5) {
    void* sp70;
    ? sp5C;
    ? sp50;
    void* sp4C;
    s32* sp44;
    s32* sp40;
    s16 sp3E;
    f32 sp34;
    f32 sp30;
    f32 temp_f16;
    s16 temp_v0_3;
    s32* temp_v0;
    s32* temp_v0_2;
    void* temp_v1;

    sp70 = arg0->actorCtx.actorList[2].first;
    sp5C.unk0 = (s32) D_80B7C284.unk0;
    sp5C.unk4 = (s32) D_80B7C284.unk4;
    sp5C.unk8 = (s32) D_80B7C284.unk8;
    sp50.unk0 = (s32) D_80B7C290.unk0;
    sp50.unk4 = (s32) D_80B7C290.unk4;
    sp50.unk8 = (s32) D_80B7C290.unk8;
    if ((arg1 >= 0xB) && (arg5->unk2AE == 0)) {
        *arg2 = NULL;
        return 0;
    }
    if (arg1 == 0xD) {
        temp_v1 = arg0->state.gfxCtx;
        temp_v0 = temp_v1->unk2B0;
        temp_v1->unk2B0 = (s32* ) (temp_v0 + 8);
        *temp_v0 = 0xDB060020;
        arg1 = arg1;
        sp4C = temp_v1;
        sp44 = temp_v0;
        sp44->unk4 = Lib_SegmentedToVirtual(*(&D_80B7C110 + (arg5->unk4D0 * 4)));
        temp_v0_2 = temp_v1->unk2B0;
        temp_v1->unk2B0 = (s32* ) (temp_v0_2 + 8);
        *temp_v0_2 = 0xDB060024;
        arg1 = arg1;
        sp40 = temp_v0_2;
        sp40->unk4 = Lib_SegmentedToVirtual(*(&D_80B7C128 + (arg5->unk4D4 * 4)));
    }
    if (arg1 == 3) {
        if ((arg5->unk2F4 & 2) != 0) {
            arg4->x = (s16) -(s32) arg5->unk2AC;
        }
        SysMatrix_MultiplyVector3fByState((Vec3f* ) &sp5C, arg5 + 0x2C4);
    } else if (arg1 == 4) {
        if ((arg5->unk2F4 & 2) != 0) {
            arg4->x = arg5->unk2AC;
        }
        SysMatrix_MultiplyVector3fByState((Vec3f* ) &sp50, arg5 + 0x2DC);
    } else if ((arg1 == 0xD) && ((arg5->unk2F4 & 8) != 0)) {
        if ((func_8013D5E8(arg5->shape.rot.y, 0x4E20, arg5->yawTowardsPlayer) != 0) && (arg5->xzDistToPlayer < 500.0f)) {
            sp30.unk0 = (s32) sp70->unk24;
            sp30.unk4 = (s32) sp70->unk28;
            sp30.unk8 = (s32) sp70->unk2C;
            temp_f16 = sp70->unkC44 + 3.0f;
            sp34 = temp_f16;
            sp3E = Math_Vec3f_Yaw(arg5 + 0x3C, (Vec3f* ) &sp30) - arg5->shape.rot.y;
            temp_v0_3 = Math_Atan2S(arg5->focus.pos.y - temp_f16, Math3D_XZLength(sp30 - arg5->focus.pos.x, sp38 - arg5->focus.pos.z));
            arg5->unk2FE = (s16) (arg4->x + sp3E);
            arg5->unk300 = (s16) arg4->y;
            arg5->unk302 = (s16) (arg4->z + temp_v0_3);
            Math_SmoothStepToS(arg5 + 0x2F8, arg5->unk2FE, 4, 0x3E8, (s16) 1);
            Math_SmoothStepToS(arg5 + 0x2FC, arg5->unk302, 4, 0x3E8, (s16) 1);
            arg5->unk2FA = (s16) arg4->y;
            arg4->x = arg5->unk2F8;
            arg4->z = arg5->unk2FC;
        } else {
            arg5->unk2FE = (s16) arg4->x;
            arg5->unk300 = (s16) arg4->y;
            arg5->unk302 = (s16) arg4->z;
            Math_SmoothStepToS(arg5 + 0x2F8, arg5->unk2FE, 4, 0x3E8, (s16) 1);
            Math_SmoothStepToS(arg5 + 0x2FC, arg5->unk302, 4, 0x3E8, (s16) 1);
            arg5->unk2FA = (s16) arg4->y;
            arg4->x = arg5->unk2F8;
            arg4->z = arg5->unk2FC;
        }
    } else if ((arg1 == 7) && ((arg5->unk2F4 & 0x80) != 0)) {
        *arg2 = NULL;
    }
    return 0;
}
#else
#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Um_0x80B77770/func_80B7B598.asm")
#endif

#ifdef MIPS_2_C_OUTPUT
void func_80B7B93C(GlobalContext* arg0, Vec3f* arg1) {
    ? sp8C;
    ? sp80;
    f32 sp78;
    f32 sp74;
    f32 sp70;
    f32* temp_s5;
    s32 temp_s0;
    s32 phi_s0;

    sp8C.unk0 = (s32) D_80B7C29C.unk0;
    sp8C.unk4 = (s32) D_80B7C29C.unk4;
    sp8C.unk8 = (s32) D_80B7C29C.unk8;
    sp80.unk0 = (s32) D_80B7C2A8.unk0;
    sp80.unk4 = (s32) D_80B7C2A8.unk4;
    sp80.unk8 = (s32) D_80B7C2A8.unk8;
    EffectSsHitMark_SpawnFixedScale(arg0, 0, arg1);
    temp_s5 = &sp70;
    phi_s0 = 0;
    do {
        sp70 = (Rand_ZeroOne() * 20.0f) - 10.0f;
        sp74 = -((Rand_ZeroOne() * 20.0f) - 10.0f);
        sp78 = (Rand_ZeroOne() * 20.0f) - 10.0f;
        EffectSsHahen_Spawn(arg0, arg1, (Vec3f* ) temp_s5, (Vec3f* ) &sp8C, (s16) 1, (s16) 0x64, (s16) 0x1FC, (s16) 0xA, *(&sp80 + ((s32) (Rand_ZeroOne() * 3.0f) * 4)));
        temp_s0 = phi_s0 + 1;
        phi_s0 = temp_s0;
    } while (temp_s0 != 0x14);
}
#else
#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Um_0x80B77770/func_80B7B93C.asm")
#endif

void func_80B7BABC(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3s* rot, Actor* actor);
#ifdef MIPS_2_C_OUTPUT
void func_80B7BABC(GlobalContext* arg0, s32 arg1, Gfx** arg2, Vec3s* arg3, Actor* arg4) {
    ? spFC;
    ? spE4;
    ? spCC;
    f32 spC4;
    ? spC0;
    ? spB4;
    f32 spB0;
    ? spA4;
    ? sp98;
    f32 sp90;
    f32 sp8C;
    f32 sp88;
    s16 sp84;
    s16 sp82;
    s16 sp80;
    f32 sp70;
    MtxF* sp4C;
    Gfx* temp_v0;
    Gfx* temp_v0_2;
    Gfx* temp_v0_3;
    GraphicsContext* temp_s2;
    Mtx* temp_s3;
    s32 temp_s6;
    s32 phi_v0;
    f32* phi_s5;
    Actor* phi_s0;
    Vec3f* phi_s7;
    s32 phi_s6;

    temp_s2 = arg0->state.gfxCtx;
    spFC.unk0 = (s32) D_80B7C2B4.unk0;
    spFC.unk4 = (s32) D_80B7C2B4.unk4;
    spFC.unkC = (s32) D_80B7C2B4.unkC;
    spFC.unk8 = (s32) D_80B7C2B4.unk8;
    spFC.unk10 = (s32) D_80B7C2B4.unk10;
    spFC.unk14 = (s32) D_80B7C2B4.unk14;
    spE4.unk4 = (s32) D_80B7C2CC.unk4;
    spE4.unk0 = (s32) D_80B7C2CC.unk0;
    spE4.unk8 = (s32) D_80B7C2CC.unk8;
    spE4.unkC = (s32) D_80B7C2CC.unkC;
    spE4.unk14 = (s32) D_80B7C2CC.unk14;
    spE4.unk10 = (s32) D_80B7C2CC.unk10;
    spCC.unk0 = (s32) D_80B7C2E4.unk0;
    spCC.unk4 = (s32) D_80B7C2E4.unk4;
    spCC.unk8 = (s32) D_80B7C2E4.unk8;
    spCC.unkC = (s32) D_80B7C2E4.unkC;
    spCC.unk10 = (s32) D_80B7C2E4.unk10;
    spCC.unk14 = (s32) D_80B7C2E4.unk14;
    spC0.unk0 = (f32) D_801D15B0.x;
    spC0.unk4 = (f32) D_801D15B0.y;
    spC0.unk8 = (f32) D_801D15B0.z;
    spC4 += D_80B7C3F4;
    if (arg1 == 5) {
        spA4.unk0 = (s32) D_80B7C2FC.unk0;
        spA4.unk4 = (s32) D_80B7C2FC.unk4;
        spA4.unk8 = (s32) D_80B7C2FC.unk8;
        SysMatrix_MultiplyVector3fByState((Vec3f* ) &spA4, arg4 + 0x308);
        arg4->unk2F4 = (s32) (arg4->unk2F4 | 0x20);
    }
    phi_v0 = 5;
    if (arg1 == 5) {
        sp98.unk0 = (s32) D_80B7C308.unk0;
        sp98.unk4 = (s32) D_80B7C308.unk4;
        sp98.unk8 = (s32) D_80B7C308.unk8;
        SysMatrix_MultiplyVector3fByState((Vec3f* ) &sp98, arg4 + 0x4BC);
        phi_v0 = 5;
    }
    if (arg1 == phi_v0) {
        sp70.unk0 = (s32) D_80B7C314.unk0;
        sp70.unk4 = (s32) D_80B7C314.unk4;
        sp70.unk8 = (s32) D_80B7C314.unk8;
        sp80 = 0;
        sp84 = 0;
        sp88 = D_80B7C3F8;
        sp4C = arg0 + 0x187B0;
        phi_s5 = &sp70;
        phi_s0 = arg4;
        phi_s7 = arg4 + 0x32C;
        phi_s6 = 0;
loop_6:
        sp90 = *phi_s5;
        sp8C = *(&spCC + (phi_s0->unk314 * 4));
        if (phi_s0->unk314 == 5) {
            sp82 = 0x4000;
        } else {
            sp82 = -0x4000;
        }
        SysMatrix_StatePush();
        SysMatrix_RotateAndTranslateState((Vec3f* ) &sp88, (Vec3s* ) &sp80);
        temp_s3 = Matrix_NewMtx(temp_s2);
        SysMatrix_MultiplyVector3fByState((Vec3f* ) &spC0, (Vec3f* ) &spB4);
        SkinMatrix_Vec3fMtxFMultXYZW(sp4C, (Vec3f* ) &spB4, phi_s7, &spB0);
        if (phi_s0->unk320 != 0) {
            phi_s0->unk320 = 0;
            if (phi_s0->unk314 == 1) {
                func_80B7B93C(arg0, (Vec3f* ) &spB4);
            } else {
                EffectSsHitMark_SpawnFixedScale(arg0, 0, (Vec3f* ) &spB4);
            }
        }
        SysMatrix_StatePop();
        if (temp_s3 != 0) {
            temp_v0 = temp_s2->polyOpa.p;
            temp_s2->polyOpa.p = temp_v0 + 8;
            temp_v0->words.w1 = (u32) temp_s3;
            temp_v0->words.w0 = 0xDA380003;
            temp_s6 = phi_s6 + 0xC;
            if (*(&spFC + (phi_s0->unk314 * 4)) != 0) {
                temp_v0_2 = temp_s2->polyOpa.p;
                temp_s2->polyOpa.p = temp_v0_2 + 8;
                temp_v0_2->words.w0 = 0xDE000000;
                temp_v0_2->words.w1 = *(&spFC + (phi_s0->unk314 * 4));
                if ((sp + (phi_s0->unk314 * 4))->unkE4 != 0) {
                    temp_v0_3 = temp_s2->polyOpa.p;
                    temp_s2->polyOpa.p = temp_v0_3 + 8;
                    temp_v0_3->words.w0 = 0xDE000000;
                    temp_v0_3->words.w1 = (sp + (phi_s0->unk314 * 4))->unkE4;
                }
            }
            phi_s5 += 4;
            phi_s0 += 4;
            phi_s7 += 0xC;
            phi_s6 = temp_s6;
            if (temp_s6 == 0x24) {
block_18:
                if (arg1 == 0xD) {
                    SysMatrix_GetStateTranslation(arg4 + 0x3C);
                }
            } else {
                goto loop_6;
            }
        }
    } else {
        goto block_18;
    }
}
#else
#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Um_0x80B77770/func_80B7BABC.asm")
#endif

#ifdef MIPS_2_C_OUTPUT
Mtx* func_80B7BEA4(s8* arg0, s16 arg1, f32* arg2, u8 arg3, GraphicsContext** arg4) {
    f32 sp110;
    f32 sp10C;
    f32 sp108;
    CollisionPoly* sp104;
    Mtx* sp100;
    ? spC0;
    ? sp80;
    ? sp40;
    Gfx* temp_v0_2;
    Gfx* temp_v0_3;
    Gfx* temp_v0_4;
    Gfx* temp_v0_5;
    GraphicsContext* temp_s0;
    Mtx* temp_a2;
    Mtx* temp_ret;
    Mtx* temp_v0;
    Mtx* phi_return;

    sp108 = arg0->unk0;
    sp10C = arg0->unk4 + 1.0f;
    sp110 = arg0->unk8;
    if (sp104 != 0) {
        func_800C0094(sp104, arg0->unk0, func_800C4000(arg4, arg4 + 0x830, &sp104, &sp108), arg0->unk8, (MtxF* ) &spC0);
    } else {
        SkinMatrix_SetTranslate((MtxF* ) &spC0, arg0->unk0, arg0->unk4, arg0->unk8);
    }
    SkinMatrix_MulYRotation((MtxF* ) &spC0, arg1);
    SkinMatrix_SetScale((MtxF* ) &sp80, arg2->unk0, 1.0f, arg2->unk8);
    SkinMatrix_MtxFMtxFMult((MtxF* ) &spC0, (MtxF* ) &sp80, (MtxF* ) &sp40);
    temp_ret = SkinMatrix_MtxFToNewMtx(*arg4, (MtxF* ) &sp40);
    temp_v0 = temp_ret;
    temp_a2 = temp_v0;
    phi_return = temp_ret;
    if (temp_v0 != 0) {
        temp_s0 = *arg4;
        temp_v0_2 = temp_s0->polyOpa.p;
        temp_s0->polyOpa.p = temp_v0_2 + 8;
        temp_v0_2->words.w1 = (u32) &D_801D1DE0;
        temp_v0_2->words.w0 = 0xDA380003;
        sp100 = temp_a2;
        temp_s0->polyOpa.p = Gfx_CallSetupDL(temp_s0->polyOpa.p, 0x2CU);
        temp_v0_3 = temp_s0->polyOpa.p;
        temp_s0->polyOpa.p = temp_v0_3 + 8;
        temp_v0_3->words.w0 = 0xFA000000;
        temp_v0_3->words.w1 = (u32) arg3;
        temp_v0_4 = temp_s0->polyOpa.p;
        temp_s0->polyOpa.p = temp_v0_4 + 8;
        temp_v0_4->words.w1 = (u32) temp_a2;
        temp_v0_4->words.w0 = 0xDA380003;
        temp_v0_5 = temp_s0->polyOpa.p;
        temp_s0->polyOpa.p = temp_v0_5 + 8;
        temp_v0_5->words.w1 = 0x4075A40;
        temp_v0_5->words.w0 = 0xDE000000;
        phi_return = (Mtx* ) temp_v0_5;
    }
    return phi_return;
}
#else
#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Um_0x80B77770/func_80B7BEA4.asm")
#endif

void ObjUm_Draw(Actor* thisx, GlobalContext* globalCtx) {
    s32 pad;
    ObjUm* this = THIS;
    Vec3f sp34;

    this->unk_2F4 |= 1;
    SkelAnime_DrawSV(globalCtx, this->unk_160.skeleton, this->unk_160.limbDrawTbl, this->unk_160.dListCount, func_80B7B598, func_80B7BABC, &this->dyna.actor);
    sp34.x = 0.45f;
    sp34.y = 0.0f;
    sp34.z = 0.7f;
    func_80B7BEA4(&this->unk_4BC, this->dyna.actor.shape.rot.y, &sp34, 0xB4U, globalCtx);
    func_80B77770(this, globalCtx);
}
