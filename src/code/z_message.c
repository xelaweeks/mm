#include "global.h"

void func_80147520(void) {
    D_801CFC98 = 0xFF;
    D_801CFCA4[0] = D_801CFCA4[1] = D_801CFCA4[2] = D_801CFCA4[3]= D_801CFCA4[4] = D_801CFCA4[5] = D_801CFCA4[6] = D_801CFCA4[7]  = D_801CFCA4[8] = 0;
}

extern s16 D_801F6B0C;
extern s16 D_801F6B0E;
extern s16 D_801F6B10;
extern s16 D_801F6B12;
extern s16 D_801F6B14;
extern s16 D_801F6B16;
extern s16 D_801F6B18;
extern s16 D_801F6B1A;
extern s16 D_801F6B1C;
extern s16 D_801F6B1E;
extern s16 D_801F6B20;
extern s16 D_801F6B22;


void func_80147564(GlobalContext *globalCtx) {
    MessageContext* msgCtx = &globalCtx->msgCtx;
    
    msgCtx->unk1204A[0] = 0xBD;
    msgCtx->unk1204A[1] = 0xB8;
    msgCtx->unk1204A[2] = 0xB3;
    msgCtx->unk1204A[3] = 0xAE;
    msgCtx->unk1204A[4] = 0xA9;
    func_80147520();
    D_801F6B0C = 0x50;
    D_801F6B10 = 0x96;
    D_801F6B0E = 0xFF;
    D_801F6B12 = 0xA;
    D_801F6B16 = 0xA;
    D_801F6B14 = 0xA;
    D_801F6B18 = 0xFF;
    D_801F6B1C = 0xFF;
    D_801F6B1A = 0x32;
    D_801F6B1E = 0xA;
    D_801F6B22 = 0xA;
    D_801F6B20 = 0xA;
}

#ifdef NON_MATCHING
u32 func_80147624(GlobalContext *globalCtx) {
    Input* input;
    //MessageContext* msgCtx;
    //MessageContext* msgCtx = &globalCtx->msgCtx;

    input = CONTROLLER1(globalCtx);
    if ((globalCtx->msgCtx.unk12020 == 0x10) || (globalCtx->msgCtx.unk12020 == 0x11)) {
        if (CHECK_BTN_ALL(input->press.button, BTN_A)) {
            play_sound(NA_SE_SY_MESSAGE_PASS);
             
        }
        return CHECK_BTN_ALL(input->press.button, BTN_A);
    }else{
        u32 temp_a0;
        if(CHECK_BTN_ALL(input->press.button, BTN_A) ||  CHECK_BTN_ALL(input->press.button,BTN_B) || CHECK_BTN_ALL(input->press.button, BTN_CUP)) {
            play_sound(NA_SE_SY_MESSAGE_PASS);
        }
        temp_a0 = CHECK_BTN_ALL(input->press.button, BTN_A);
        if (!CHECK_BTN_ALL(input->press.button, BTN_A)) {
            temp_a0 = CHECK_BTN_ALL(input->press.button, BTN_B);
            if (!CHECK_BTN_ALL(input->press.button, BTN_B)) {
                temp_a0 = CHECK_BTN_ALL(input->press.button, BTN_CUP);
            }
        }
        return temp_a0;
    }
}
#else
#pragma GLOBAL_ASM("asm/non_matchings/code/z_message/func_80147624.s")
#endif

#ifdef NON_MATCHING

u32 func_80147734(GlobalContext *globalCtx) {
    s32 ret_value;
    Input* controller;
    MessageContext* msgCtx = &globalCtx->msgCtx;

    if(msgCtx->unk12020 == 0x10 ||msgCtx->unk12020 == 0x11){
        return CHECK_BTN_ALL(CONTROLLER1(globalCtx)->press.button, BTN_A);
    }
    controller = CONTROLLER1(globalCtx);
    ret_value = CHECK_BTN_ALL(controller->press.button, BTN_A);
    if(ret_value == 0){
        ret_value = CHECK_BTN_ALL(controller->press.button, BTN_B);
        if(ret_value == 0){
            ret_value = CHECK_BTN_ALL(controller->press.button, BTN_CUP);
        }
    }
    return ret_value;
}

#else
#pragma GLOBAL_ASM("asm/non_matchings/code/z_message/func_80147734.s")
#endif

void func_801477B4(GlobalContext *globalCtx) {
    MessageContext *msgCtx;

    msgCtx = &globalCtx->msgCtx;
    if (globalCtx->msgCtx.unk11F10 != 0) {
        msgCtx->unk12023 = 2;
        msgCtx->msgMode = 0x43;
        msgCtx->unk12020 = 0;
        play_sound(0U);
    }
}

#pragma GLOBAL_ASM("asm/non_matchings/code/z_message/func_80147818.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_message/func_80147F18.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_message/func_80148558.s")

extern s16 D_801CFD80;

void func_80148B98(GlobalContext *globalCtx, u8 bParm2) {
    s8 stickY;
    s32 phi_v1;
    MessageContext *msgCtx = &globalCtx->msgCtx;
    stickY = CONTROLLER1(globalCtx)->rel.stick_y;
    
        if ((stickY >= 0x1E)) {
            if(D_801CFD80 == 0){
            D_801CFD80 = 1;
            msgCtx->choiceIndex--;
            if (msgCtx->choiceIndex >= 0x81) {
                msgCtx->choiceIndex = 0;
                return;
            }
            play_sound(NA_SE_SY_CURSOR);
            return;
        }
        }
        if ((stickY < -0x1D)) {
            if(D_801CFD80 == 0){
            D_801CFD80 = 1;
            msgCtx->choiceIndex++;
            if (bParm2 < msgCtx->choiceIndex) {
                msgCtx->choiceIndex = bParm2;
                return;
            }
            play_sound(NA_SE_SY_CURSOR);
            return;
        }
        }
    phi_v1 = (stickY < 0 ? -stickY : stickY);
    if (phi_v1 < 0x1E) {
        D_801CFD80 = 0;
    }
}


void func_80148CBC(GlobalContext *globalCtx, UNK_PTR puParm2, u8 arg2) {
    MessageContext* msgCtx;

    msgCtx = &globalCtx->msgCtx;
    msgCtx->unk11FF4 = 0x30;
    if (arg2  == 1) {
        msgCtx->unk11FF6 = msgCtx->unk11FFE[1+msgCtx->choiceIndex];
    } else {
        msgCtx->unk11FF6 = msgCtx->unk11FFE[msgCtx->choiceIndex];
    }
    func_80147818(globalCtx, puParm2, msgCtx->unk11FF4, msgCtx->unk11FF6);
}

#pragma GLOBAL_ASM("asm/non_matchings/code/z_message/func_80148D64.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_message/func_80149048.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_message/func_801491DC.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_message/func_80149454.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_message/func_801496C8.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_message/func_8014995C.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_message/func_80149C18.s")

#ifdef NON_EQUIVALENT

void func_80149EBC(GlobalContext *globalCtx, u16 arg2) {
    Font *font;
    s32 temp_a1;
    s32 temp_a1_2;
    s32 temp_a2;
    UnkMsgStruct** temp_v1;
    u16 temp_v0_3;
    u16 phi_v0;
    s8 *phi_v1;

    temp_v1 = globalCtx->msgCtx.unk12080;
    phi_v0 = temp_v1[0]->unk0000;
    temp_a2 = temp_v1[0]->unk0004;
    while(phi_v0 != 0xFFFF){
         if ((arg2 & 0xFFFF) == phi_v0) {
            temp_a1 = temp_v1[0]->unk0004;
            font = &globalCtx->msgCtx.font;
            font->messageStart = temp_a1 - temp_a2;
            font->messageEnd = temp_v1[1]->unk0004 - temp_a1;
            return;
        }
        phi_v0 = temp_v1[1]->unk0000;
        temp_v1 += 1;
        if (phi_v0 == 0xFFFF) {
            // Duplicate return node #4. Try simplifying control flow for better match
            temp_v1 = globalCtx->msgCtx.unk12080;
            temp_a1 = temp_v1[0]->unk0004;
            font = &globalCtx->msgCtx.font;
            font->messageStart = temp_a1 - temp_a2;
            font->messageEnd = temp_v1[1]->unk0004 - temp_a1;
            return;
        }
    }
    
    temp_v1 =  globalCtx->msgCtx.unk12080;
    temp_a1 = temp_v1[0]->unk0004;
    font = &globalCtx->msgCtx.font;
    font->messageStart = temp_a1 - temp_a2;
    font->messageEnd = temp_v1[1]->unk0004 - temp_a1;
}

#else
#pragma GLOBAL_ASM("asm/non_matchings/code/z_message/func_80149EBC.s")
#endif

#pragma GLOBAL_ASM("asm/non_matchings/code/z_message/func_80149F74.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_message/func_8014AAD0.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_message/func_8014ADBC.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_message/func_8014C70C.s")

void func_8014CC14(GlobalContext* globalCtx, u16 codePointIndex, s32* offset, f32* arg3, s16 arg4) {
    MessageContext* msgCtx = &globalCtx->msgCtx;
    s32 temp1 = *offset;
    f32 temp2 = *arg3;

    
    Font_LoadChar(globalCtx, codePointIndex, temp1);
    msgCtx->unk11F24[arg4] = codePointIndex; 
    temp1 += 128;
    temp2 += (16.0f * msgCtx->unk12098);
    *offset = temp1;
    *arg3 = temp2;
}

#pragma GLOBAL_ASM("asm/non_matchings/code/z_message/func_8014CCB4.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_message/func_8014CDF0.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_message/func_8014CFDC.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_message/func_8014D304.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_message/func_8014D62C.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_message/func_8014D7B4.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_message/func_80150A84.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_message/func_80150D08.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_message/func_801514B0.s")

void Message_StartTextbox(GlobalContext* globalCtx, u16 textId, Actor* Actor) {
    MessageContext* msgCtx;

    msgCtx = &globalCtx->msgCtx;
    msgCtx->ocarinaAction = 0xFFFF;
    func_80150D08(globalCtx, textId);
    msgCtx->unkActor = Actor;
    msgCtx->msgMode = 1;
    msgCtx->unk12023 = 0;
    msgCtx->unk12024 = 0;
    globalCtx->msgCtx.ocarinaMode = 0;
}

#pragma GLOBAL_ASM("asm/non_matchings/code/z_message/func_80151938.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_message/func_80151A68.s")


extern u16 D_801C6B28[];

void func_80151BB4(GlobalContext* globalCtx, u8 uParm2) {
    MessageContext* msgCtx = &globalCtx->msgCtx;
    u8 temp = uParm2;

    if (CHECK_QUEST_ITEM(18)) { // CHECK_QUEST_ITEM(QUEST_BOMBERS_NOTEBOOK)
        if (((gSaveContext.weekEventReg[D_801C6B28[uParm2] >> 8]) & (u8)D_801C6B28[uParm2]) == 0) {
            msgCtx->unk120B2[msgCtx->unk120B1] = temp;
            msgCtx->unk120B1++;
        }
    }
    else if (uParm2 >= 20) {
        //temp = uParm2;
        if (((gSaveContext.weekEventReg[D_801C6B28[uParm2] >> 8]) & (u8)D_801C6B28[uParm2]) == 0) {
            msgCtx->unk120B2[msgCtx->unk120B1] = temp;
            msgCtx->unk120B1++;
        }
    }
}


extern u16 D_801C6AB8[];
//extern ? D_801C6B28;

u32 func_80151C9C(GlobalContext *globalCtx) {
    MessageContext* msgCtx;
    u8 flag;

    msgCtx = &globalCtx->msgCtx;
    while(1){
        if(msgCtx->unk120B1 == 0){
            return 0;
        }
        msgCtx->unk120B1--;


        if (((gSaveContext.weekEventReg[ D_801C6B28[msgCtx->unk120B2[msgCtx->unk120B1]]>>8]) & (u8)D_801C6B28[msgCtx->unk120B2[msgCtx->unk120B1]]) == 0) {
            flag = gSaveContext.weekEventReg[D_801C6B28[msgCtx->unk120B2[msgCtx->unk120B1]]>>8];
            gSaveContext.weekEventReg[D_801C6B28[msgCtx->unk120B2[msgCtx->unk120B1]]>>8] = flag | (u8)D_801C6B28[msgCtx->unk120B2[msgCtx->unk120B1]];
            if((D_801C6AB8[msgCtx->unk120B2[msgCtx->unk120B1]] != 0) && (CHECK_QUEST_ITEM(0x12))){ // CHECK_QUEST_ITEM(QUEST_BOMBERS_NOTEBOOK)
                func_80151938(globalCtx, D_801C6AB8[msgCtx->unk120B2[msgCtx->unk120B1]]);
                play_sound(NA_SE_SY_SCHEDULE_WRITE);
                return 1;
            }
        }
    }
}

#pragma GLOBAL_ASM("asm/non_matchings/code/z_message/func_80151DA4.s")

void func_80152434(GlobalContext *globalCtx, u16 arg2) {
    globalCtx->msgCtx.unk12046 = 0;
    func_80151DA4(globalCtx, arg2);
} 

void func_80152464(GlobalContext *globalCtx, u16 arg1) {
    globalCtx->msgCtx.unk12046 = 1;
    func_80151DA4(globalCtx, arg1);
}

#pragma GLOBAL_ASM("asm/non_matchings/code/z_message/Message_GetState.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_message/func_8015268C.s")

void func_80152C64(View *view) {
    Viewport viewport; 
    viewport.bottomY = 0xF0; viewport.rightX = 0x140;
    viewport.topY = 0;
    viewport.leftX = 0;
    

    View_SetViewport(view, (Viewport *) &viewport);
    func_8013FBC8(view);
}

#pragma GLOBAL_ASM("asm/non_matchings/code/z_message/func_80152CAC.s")


s16 D_801D02D8[15] = {
    ACTOR_OCEFF_WIPE5, ACTOR_OCEFF_WIPE5, // Sonata of Awakening Effect, Sonata of Awakening Effect
    ACTOR_OCEFF_WIPE5, ACTOR_OCEFF_WIPE5, // Sonata of Awakening Effect, Sonata of Awakening Effect
    ACTOR_OCEFF_WIPE5, ACTOR_OCEFF_WIPE5, // Sonata of Awakening Effect, Sonata of Awakening Effect
    ACTOR_OCEFF_WIPE,  ACTOR_OCEFF_WIPE7, // Song of Time Effect, Song of Healing Effect
    ACTOR_OCEFF_WIPE2, ACTOR_OCEFF_WIPE6, // Epona's Song Effect, Song of Soaring Effect
    ACTOR_OCEFF_STORM, ACTOR_OCEFF_SPOT,  // Song of Storms Effect II [?], Sun's Song Effect
    ACTOR_OCEFF_WIPE, ACTOR_OCEFF_WIPE,   // Song of Time Effect, Song of Time Effect
    ACTOR_OCEFF_WIPE4                     // Scarecrow's Song Effect 
};
s32 D_801D02F8[15] = { 0,1,2,3,4,0,1,0,0,0,0,0,1,1,0 };


//Spawn song effect?
void func_80152EC0(GlobalContext *globalCtx) {
    MessageContext* msgCtx = &globalCtx->msgCtx;
    Actor* actor = (Actor*)PLAYER;
    
    if(1){}
    if ((msgCtx->songPlayed < 0x17) && (msgCtx->songPlayed != 0xE) && ((msgCtx->unk1202C < 0x43) || (msgCtx->unk1202C >= 0x47))) {
        msgCtx->unk120B0 = 1;
        if (msgCtx->songPlayed != 0x16) {
            Actor_Spawn(&globalCtx->actorCtx, globalCtx, D_801D02D8[msgCtx->songPlayed], actor->world.pos.x, actor->world.pos.y, actor->world.pos.z, 0,  0,  0, D_801D02F8[msgCtx->songPlayed]);
            return;
        }
        Actor_Spawn(&globalCtx->actorCtx, globalCtx, 0xF6, actor->world.pos.x, actor->world.pos.y, actor->world.pos.z, 0, 0,  0,  0);
    }
}


#pragma GLOBAL_ASM("asm/non_matchings/code/z_message/func_80152FB8.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_message/func_80153750.s")

void func_80153E7C(GlobalContext *globalCtx, void *arg1) {
    if ((gSaveContext.language == 0) && (globalCtx->msgCtx.unk12090 == 0)) {
        func_8014ADBC(globalCtx, arg1);
        return;
    }
    if (globalCtx->msgCtx.unk12090 != 0) {
        func_8015E7EC(globalCtx, arg1);
        return;
    }
    func_8015966C(globalCtx, arg1, 0);
}

#pragma GLOBAL_ASM("asm/non_matchings/code/z_message/func_80153EF0.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_message/func_801541D4.s")

void func_80156758(GlobalContext *globalCtx) {
    Gfx* nextDisplayList;
    Gfx* _polyOpa;
    GraphicsContext* gfxCtx;

    gfxCtx = globalCtx->state.gfxCtx;
    OPEN_DISPS(gfxCtx);
    nextDisplayList = Graph_GfxPlusOne(_polyOpa = POLY_OPA_DISP);
    gSPDisplayList(OVERLAY_DISP++, nextDisplayList);
    if ((globalCtx->msgCtx.unk11F04 != 0x5E6) || (func_801690CC(globalCtx) == 0)) {
        func_801541D4(globalCtx, &nextDisplayList);
    }
    gSPEndDisplayList(nextDisplayList++);
    Graph_BranchDlist(_polyOpa, nextDisplayList);
    gfxCtx->polyOpa.p = nextDisplayList;
    CLOSE_DISPS(gfxCtx);
}

#pragma GLOBAL_ASM("asm/non_matchings/code/z_message/func_8015680C.s")

void func_801586A4(GlobalContext *globalCtx) {
    globalCtx->msgCtx.unk12084 = &D_801C6B98;
    globalCtx->msgCtx.unk1208C = &D_801CFB08;
}

void Message_Init(GlobalContext *globalCtx) {
    Font *font;
    MessageContext *messageCtx = &globalCtx->msgCtx;

    func_801586A4(globalCtx);
    globalCtx->msgCtx.ocarinaMode = 0;
    messageCtx->msgMode = 0;
    messageCtx->unk11F10 = 0;
    messageCtx->unk11F04 = 0;
    messageCtx->unk12020 = 0;
    messageCtx->choiceIndex = 0;
    messageCtx->ocarinaAction = messageCtx->unk11FF2 = 0;
    messageCtx->unk1201E = 0xFF;
    View_Init( &messageCtx->view, globalCtx->state.gfxCtx);
    messageCtx->unk11EF8 = THA_AllocEndAlign16(&globalCtx->state.heap, 0x13C00);
    font = &globalCtx->msgCtx.font;
    Font_LoadOrderedFont(&globalCtx->msgCtx.font);
    font->unk_11D88 = 0;
    messageCtx->unk12090 = messageCtx->unk12092 = 0;
    messageCtx->unk12094 = 0;
    messageCtx->unk1209C = 0;
    messageCtx->unk120A0 = 0;
    messageCtx->unk12068 = 0x34;
    messageCtx->unk1206A = 0x24;
    messageCtx->unk120B0 = 0;
    messageCtx->unk120BE = 0;
    messageCtx->unk120C0 = 0;
    messageCtx->unk120C2 = 0;
    messageCtx->unk120C4 = 0;
    messageCtx->unk120C8 = 0;
    messageCtx->unk120CA = 0;
    messageCtx->unk120CC = 0;
    messageCtx->unk120CE = 0;
    messageCtx->unk120D0 = 0;
    messageCtx->unk120D2 = 0;
    messageCtx->unk120D4 = 0;
    messageCtx->unk120D6 = 0;
}


