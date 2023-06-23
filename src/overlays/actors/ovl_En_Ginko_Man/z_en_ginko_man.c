/*
 * File: z_en_ginko_man.c
 * Overlay: ovl_En_Ginko_Man
 * Description: Bank Teller
 */

#include "z_en_ginko_man.h"
#include "objects/object_boj/object_boj.h"

#define FLAGS (ACTOR_FLAG_1 | ACTOR_FLAG_8)

#define THIS ((EnGinkoMan*)thisx)

void EnGinkoMan_Init(Actor* thisx, PlayState* play);
void EnGinkoMan_Destroy(Actor* thisx, PlayState* play);
void EnGinkoMan_Update(Actor* thisx, PlayState* play);
void EnGinkoMan_Draw(Actor* thisx, PlayState* play);

void EnGinkoMan_SetupIdle(EnGinkoMan* this);
void EnGinkoMan_SetupDialogue(EnGinkoMan* this);
void EnGinkoMan_SetupBankAward(EnGinkoMan* this);
void EnGinkoMan_SetupBankAward2(EnGinkoMan* this);
void EnGinkoMan_SetupStamp(EnGinkoMan* this);

void EnGinkoMan_Idle(EnGinkoMan* this, PlayState* play);
void EnGinkoMan_BankAward(EnGinkoMan* this, PlayState* play);
void EnGinkoMan_DepositDialogue(EnGinkoMan* this, PlayState* play);
void EnGinkoMan_BankAward2(EnGinkoMan* this, PlayState* play);
void EnGinkoMan_Stamp(EnGinkoMan* this, PlayState* play);
void EnGinkoMan_Dialogue(EnGinkoMan* this, PlayState* play);
void EnGinkoMan_SwitchAnimation(EnGinkoMan* this, PlayState* play);

ActorInit En_Ginko_Man_InitVars = {
    ACTOR_EN_GINKO_MAN,
    ACTORCAT_NPC,
    FLAGS,
    OBJECT_BOJ,
    sizeof(EnGinkoMan),
    (ActorFunc)EnGinkoMan_Init,
    (ActorFunc)EnGinkoMan_Destroy,
    (ActorFunc)EnGinkoMan_Update,
    (ActorFunc)EnGinkoMan_Draw,
};

typedef enum {
    /* 0 */ GINKO_ANIM_LEGSMACKING,
    /* 1 */ GINKO_ANIM_SITTING,
    /* 2 */ GINKO_ANIM_REACHING,
    /* 3 */ GINKO_ANIM_AMAZED,
    /* 4 */ GINKO_ANIM_ADVERTISING
} GinkoAnimation;

static AnimationInfo sAnimationInfo[] = {
    { &object_boj_Anim_0008C0, 1.0f, 0.0f, 0.0f, ANIMMODE_LOOP, -4.0f },
    { &object_boj_Anim_0043F0, 1.0f, 0.0f, 0.0f, ANIMMODE_LOOP, -4.0f },
    { &object_boj_Anim_004F40, 1.0f, 0.0f, 0.0f, ANIMMODE_ONCE, -4.0f },
    { &object_boj_Anim_000AC4, 1.0f, 0.0f, 0.0f, ANIMMODE_LOOP, -4.0f }, // looking around for customers
    { &object_boj_Anim_004A7C, 1.0f, 0.0f, 0.0f, ANIMMODE_LOOP, -4.0f },
};

void EnGinkoMan_Init(Actor* thisx, PlayState* play) {
    EnGinkoMan* this = THIS;

    this->actor.targetMode = 1;
    this->actor.uncullZoneForward = 400.0f;
    Actor_SetScale(&this->actor, 0.01f);
    this->actor.colChkInfo.cylRadius = 100;
    this->curTextId = 0;
    this->isNewAccount = false;
    this->isStampChecked = false;
    this->choiceDepositWithdrawl = GINKOMAN_CHOICE_RESET;
    this->serviceFee = 0;
    SkelAnime_InitFlex(play, &this->skelAnime, &object_boj_Skel_00C240, &object_boj_Anim_0043F0, this->jointTable,
                       this->morphTable, 16);
    EnGinkoMan_SetupIdle(this);
}

void EnGinkoMan_Destroy(Actor* thisx, PlayState* play) {
}

void EnGinkoMan_SetupIdle(EnGinkoMan* this) {
    this->actor.flags |= ACTOR_FLAG_1; // targetable
    Actor_ChangeAnimationByInfo(&this->skelAnime, sAnimationInfo, GINKO_ANIM_SITTING);
    this->actionFunc = EnGinkoMan_Idle;
}

void EnGinkoMan_Idle(EnGinkoMan* this, PlayState* play) {
    s32 yaw = this->actor.yawTowardsPlayer - this->actor.shape.rot.y;

    EnGinkoMan_SwitchAnimation(this, play);
    if (Actor_ProcessTalkRequest(&this->actor, &play->state)) {
        if ((gSaveContext.save.saveInfo.bankRupees & 0xFFFF) == 0) {
            Actor_ChangeAnimationByInfo(&this->skelAnime, sAnimationInfo, GINKO_ANIM_LEGSMACKING);
            Message_StartTextbox(play, 0x44C, &this->actor);
            this->curTextId = 0x44C; // would you like to make an account
        } else {
            Actor_ChangeAnimationByInfo(&this->skelAnime, sAnimationInfo, GINKO_ANIM_SITTING);
            if ((CURRENT_DAY == 3) && (gSaveContext.save.isNight == true)) {
                Message_StartTextbox(play, 0x467, &this->actor);
                this->curTextId = 0x467; // "What's this? You need somethin' on a day like this?
            } else {
                Message_StartTextbox(play, 0x466, &this->actor);
                this->curTextId = 0x466; // What's this? You need somethin'?
            }
        }
        EnGinkoMan_SetupDialogue(this);
    } else if (ABS_ALT(yaw) < 0x1555) {
        func_800B8614(&this->actor, play, 100.0f);
    }
}

// action func: non-input dialogue
void EnGinkoMan_DepositDialogue(EnGinkoMan* this, PlayState* play) {
    if (!Message_ShouldAdvance(play)) {
        return;
    }

    switch (this->curTextId) {
        case 0x44C: // "Hey there, little guy!  Won't you deposit some Rupees? (first dialogue)
            Actor_ChangeAnimationByInfo(&this->skelAnime, sAnimationInfo, GINKO_ANIM_SITTING);
            if (CHECK_WEEKEVENTREG(WEEKEVENTREG_10_08)) {
                Message_StartTextbox(play, 0x44E, &this->actor);
                this->curTextId = 0x44E; //" ...So, what'll it be?  Deposit Rupees Don't deposit Rupees"
            } else {
                Message_StartTextbox(play, 0x44D, &this->actor);
                this->curTextId =
                    0x44D; // "For example, if you deposit 200 Rupees, you'll get an item that holds a lot of Rupees."
            }
            break;
        case 0x44D: // "For example, if you deposit 200 Rupees, you'll get an item that holds a lot of Rupees."
            Message_StartTextbox(play, 0x44E, &this->actor);
            this->curTextId = 0x44E; //" ...So, what'll it be?  Deposit Rupees Don't deposit Rupees"
            break;
        case 0x44F: // "...So, what'll it be?  Deposit Rupees Don't deposit Rupees"
            Actor_ChangeAnimationByInfo(&this->skelAnime, sAnimationInfo, GINKO_ANIM_LEGSMACKING);
            Message_StartTextbox(play, 0x450, &this->actor);
            this->curTextId = 0x450; // "How much? How much?  [rupee prompt]
            break;

        case 0x453: // you deposited a tiny amount
        case 0x454: // you deposited a normal amount
        case 0x455: // you deposited a lot
            if (this->isNewAccount == true) {
                this->isNewAccount = false;
                if (this->curTextId != 0x453) { // "That's it? That ain't nothing at all, big spender!
                    Actor_ChangeAnimationByInfo(&this->skelAnime, sAnimationInfo, GINKO_ANIM_SITTING);
                }

                Message_StartTextbox(play, 0x461, &this->actor);
                this->curTextId = 0x461; // So, little guy, what's your name?
            } else {
                if (this->curTextId == 0x453) { // "That's it? That ain't nothing at all, big spender!
                    Actor_ChangeAnimationByInfo(&this->skelAnime, sAnimationInfo, GINKO_ANIM_LEGSMACKING);
                }

                play->msgCtx.bankRupees = gSaveContext.save.saveInfo.bankRupees & 0xFFFF;
                Message_StartTextbox(play, 0x45A, &this->actor);
                this->curTextId = 0x45A; // "All right, little guy, now I've got a total of [rupees] from you!"
            }
            break;
        case 0x456: // "Is that so? Think about it, little guy!"
        case 0x459: // "Heyyy! You don't have that much!
            Message_StartTextbox(play, 0x44E, &this->actor);
            this->curTextId = 0x44E; //" ...So, what'll it be?  Deposit Rupees Don't deposit Rupees"
            break;
        case 0x45A: // "All right, little guy, now I've got a total of [rupees] from you!"
            if (((gSaveContext.save.saveInfo.bankRupees & 0xFFFF) >= 200) && (this->previousBankValue < 200) &&
                !CHECK_WEEKEVENTREG(WEEKEVENTREG_59_40)) {
                SET_WEEKEVENTREG(WEEKEVENTREG_59_40);
                Message_StartTextbox(play, 0x45B, &this->actor);
                this->curTextId = 0x45B; // "What's this? You've already saved up 200 Rupees!?!
            } else if (((gSaveContext.save.saveInfo.bankRupees & 0xFFFF) >= 1000) &&
                       ((this->previousBankValue) < 1000) && !CHECK_WEEKEVENTREG(WEEKEVENTREG_59_80)) {
                SET_WEEKEVENTREG(WEEKEVENTREG_59_80);
                Message_StartTextbox(play, 0x45C, &this->actor);
                this->curTextId = 0x45C; // "What's this? You've already saved up 1000 Rupees!?!
            } else if ((gSaveContext.save.saveInfo.bankRupees & 0xFFFF) >= 5000) {
                if ((this->previousBankValue < 5000) && !CHECK_WEEKEVENTREG(WEEKEVENTREG_60_01)) {
                    SET_WEEKEVENTREG(WEEKEVENTREG_60_01);
                    Message_StartTextbox(play, 0x45D, &this->actor);
                    this->curTextId = 0x45D; // "What's this? You've already saved up 5000 Rupees?!
                } else if (this->previousBankValue < (s16)(gSaveContext.save.saveInfo.bankRupees & 0xFFFF)) {
                    Actor_ChangeAnimationByInfo(&this->skelAnime, sAnimationInfo, GINKO_ANIM_SITTING);
                    Message_StartTextbox(play, 0x45E, &this->actor);
                    this->curTextId =
                        0x45E; // "...Hang on there, little guy.  I can't take any more deposits.  Sorry..."
                } else {
                    Actor_ChangeAnimationByInfo(&this->skelAnime, sAnimationInfo, GINKO_ANIM_LEGSMACKING);
                    Message_StartTextbox(play, 0x460, &this->actor);
                    this->curTextId = 0x460; // "Come back and deposit some after you save up a bunch!"
                }
            } else {
                Actor_ChangeAnimationByInfo(&this->skelAnime, sAnimationInfo, GINKO_ANIM_LEGSMACKING);
                Message_StartTextbox(play, 0x460, &this->actor);
                this->curTextId = 0x460; // "Come back and deposit some after you save up a bunch!"
            }
            break;
        case 0x45B: // given 200 reward
        case 0x45C: // given 1000 reward
        case 0x45D: // given 5000 reward
            this->isStampChecked = false;
            Message_CloseTextbox(play);
            EnGinkoMan_SetupBankAward(this);
            EnGinkoMan_BankAward(this, play);
            break;
        case 0x461: // So, little guy, what's your name?
            Message_StartTextbox(play, 0x462, &this->actor);
            this->curTextId = 0x462; // Hmm... Link is it?
            break;
        case 0x462: // Hmm.. Link is it?
            Message_StartTextbox(play, 0x463, &this->actor);
            this->curTextId = 0x463; // Got it... I won't forget your deposits. Let me stamp you
            break;
        case 0x463: // Got it... I won't forget your deposits. Let me stamp you
            Message_StartTextbox(play, 0x464, &this->actor);
            this->curTextId = 0x464; // Hey, relax! It doesn't leave any marks
            break;
        case 0x464: // Hey, relax! It doesn't leave any marks
            play->msgCtx.msgMode = 0x44;
            EnGinkoMan_SetupStamp(this); // stamp player
            break;
        case 0x465: // "There! Now I'll know you when I see you!"
            Actor_ChangeAnimationByInfo(&this->skelAnime, sAnimationInfo, GINKO_ANIM_LEGSMACKING);
            play->msgCtx.bankRupees = gSaveContext.save.saveInfo.bankRupees & 0xFFFF;
            Message_StartTextbox(play, 0x45A, &this->actor);
            this->curTextId = 0x45A; // "All right, little guy, now I've got a total of [rupees] from you!"
            break;
        case 0x466: // What's this? You need somethin'?
        case 0x467: // "What's this? You need somethin' on a day like this?  You haven't evacuated yet?
            Message_StartTextbox(play, 0x468, &this->actor);
            this->curTextId = 0x468; // " Deposit Rupees Withdraw Rupees Nothing really"
            break;
        case 0x469:                      // "Excuse me, but let me take a look at you..."
            EnGinkoMan_SetupStamp(this); // stamp player
            break;
        case 0x46A: // "Ah, yes...[Link].  If I remember, you're the little guy who deposited [rupees]."
        case 0x46C: // "Ah, yes...[Link], right?  If I remember, you're the little guy who deposited [rupees]."
        case 0x47E: // "Your deposits total [rupees]."
            if (this->choiceDepositWithdrawl == GINKOMAN_CHOICE_DEPOSIT) {
                if ((u32)(gSaveContext.save.saveInfo.bankRupees & 0xFFFF) >= 5000) {
                    Message_StartTextbox(play, 0x45F, &this->actor);
                    this->curTextId = 0x45F; // "Excuuuse me! But I can't take anymore deposits!
                } else if (gSaveContext.save.saveInfo.playerData.rupees == 0) {
                    Message_StartTextbox(play, 0x458, &this->actor);
                    this->curTextId =
                        0x458; // "Hmm...You play mean jokes, little guy! You haven't even got a single Rupee!
                } else {
                    Message_StartTextbox(play, 0x479, &this->actor);
                    this->curTextId = 0x479; // "Well, are you gonna make a deposit?"
                }
            } else if ((CURRENT_DAY == 3) && (gSaveContext.save.isNight == true)) {
                Message_StartTextbox(play, 0x46D, &this->actor);
                // "Look, little guy, if it's 'cause of the bad rumors going around, forget it! They're just rumors!"
                this->curTextId = 0x46D;
            } else { // GINKOMAN_CHOICE_WITHDRAWL
                Message_StartTextbox(play, 0x46B, &this->actor);
                this->curTextId = 0x46B; // "So..."
            }

            this->choiceDepositWithdrawl = GINKOMAN_CHOICE_RESET;
            break;
        case 0x46B: // So...
            Message_StartTextbox(play, 0x46E, &this->actor);
            this->curTextId = 0x46E; // "How much do you want?  [rupee prompt]
            break;
        case 0x46D: // "Look, little guy, if it's 'cause of the bad rumors going around, forget it! They're just
                    // rumors!"
            Message_StartTextbox(play, 0x46B, &this->actor);
            this->curTextId = 0x46B; // So...
            break;
        case 0x470: // "Is that so?  Come back and deposit some after saving up a bunch!"
            if (Message_ShouldAdvance(play)) {
                Message_CloseTextbox(play);
                this->isStampChecked = false;
                EnGinkoMan_SetupIdle(this); // change to waiting for approach
            }
            break;
        case 0x476: // "...You haven't deposited that many Rupees, so that much isn't available for withdrawal. Do the
                    // math!
            Actor_ChangeAnimationByInfo(&this->skelAnime, sAnimationInfo, GINKO_ANIM_SITTING);
        case 0x475: // "What's this?  Look, little guy, you can't hold this many rupees! You got that?"
        case 0x47C: // "Is that so?  Think it over, little guy!  So what are you gonna do?"
        case 0x47D: // duplicate of 48
            Message_StartTextbox(play, 0x468, &this->actor);
            this->curTextId = 0x468; // " Deposit Rupees Withdraw Rupees Nothing really"
            break;
        case 0x472: // "What's this? It's a waste to take out such a tiny bit!  ...But if you say so!"
        case 0x473: // Use it wisely...
        case 0x474: // "Aw, you're taking out all that?  If you spend it like that, it'll all be gone before you know
                    // it!"
            if ((gSaveContext.save.saveInfo.bankRupees & 0xFFFF) == 0) {
                Message_StartTextbox(play, 0x478, &this->actor);
                //  "Look, little guy, all the Rupees you deposited are gone, so you can't use that stamp anymore."
                this->curTextId = 0x478;
            } else {
                play->msgCtx.bankRupees = gSaveContext.save.saveInfo.bankRupees & 0xFFFF;
                Message_StartTextbox(play, 0x45A, &this->actor);
                this->curTextId = 0x45A; // "All right, little guy, now I've got a total of [rupees] from you!"
            }
            break;
        case 0x477: // "...You know, at this time of day there's a 4 Rupee service charge on withdrawals!"
            Message_StartTextbox(play, 0x471, &this->actor);
            this->curTextId = 0x471; // "Are you really withdrawing [rupees selected]? Y/n"
            this->serviceFee = play->msgCtx.unk1206C;
            break;
        case 0x479: // Well, are you gonna make a deposit?
            Message_StartTextbox(play, 0x44F, &this->actor);
            this->curTextId = 0x44F; // "All right! So..."
            break;
    }
}

// actionfunc: wait for player dialogue input
void EnGinkoMan_WaitForDialogueInput(EnGinkoMan* this, PlayState* play) {
    if (!Message_ShouldAdvance(play)) {
        return;
    }

    switch (this->curTextId) {
        case 0x44E: // "...So, what'll it be?
            if (play->msgCtx.choiceIndex == GINKOMAN_CHOICE_YES) {
                if ((gSaveContext.save.saveInfo.bankRupees & 0xFFFF) >= 5000) {
                    Audio_PlaySfx(NA_SE_SY_ERROR);
                    Message_StartTextbox(play, 0x45F, &this->actor);
                    this->curTextId = 0x45F; // bank full, cannot accept more
                } else {
                    if (gSaveContext.save.saveInfo.playerData.rupees > 0) {
                        Audio_PlaySfx_MessageDecide();
                        Message_StartTextbox(play, 0x44F, &this->actor);
                        this->curTextId = 0x44F; // "All right! so..."
                    } else {
                        Audio_PlaySfx(NA_SE_SY_ERROR);
                        Message_StartTextbox(play, 0x458, &this->actor);
                        this->curTextId = 0x458; // you haven't even gotten a single rup
                    }
                }
            } else { // GINKOMAN_CHOICE_NO
                Audio_PlaySfx_MessageCancel();
                Message_StartTextbox(play, 0x451, &this->actor);
                this->curTextId = 0x451; // dont say that, come on, trust me!
            }
            break;
        case 0x452: // Really? are you really depositing rupees?
            if (play->msgCtx.choiceIndex == GINKOMAN_CHOICE_YES) {
                if (gSaveContext.save.saveInfo.playerData.rupees < play->msgCtx.bankRupeesSelected) {
                    Audio_PlaySfx(NA_SE_SY_ERROR);
                    Actor_ChangeAnimationByInfo(&this->skelAnime, sAnimationInfo, GINKO_ANIM_SITTING);
                    Message_StartTextbox(play, 0x459, &this->actor);
                    this->curTextId = 0x459; // HEY you dont have that much
                } else {
                    Audio_PlaySfx_MessageDecide();
                    if (play->msgCtx.bankRupeesSelected >= 100) {
                        Message_StartTextbox(play, 0x455, &this->actor);
                        this->curTextId = 0x455; // You're really going to be give me that much? Rich little guy!
                    } else if (play->msgCtx.bankRupeesSelected >= 10) {
                        Message_StartTextbox(play, 0x454, &this->actor);
                        this->curTextId = 0x454; // Seriously? that's a lot. A lot!
                    } else {
                        Actor_ChangeAnimationByInfo(&this->skelAnime, sAnimationInfo, GINKO_ANIM_SITTING);
                        Message_StartTextbox(play, 0x453, &this->actor);
                        this->curTextId = 0x453; // That's it? That aint nothing at all
                    }

                    if ((gSaveContext.save.saveInfo.bankRupees & 0xFFFF) == 0) {
                        this->isNewAccount = true;
                    }

                    Rupees_ChangeBy(-play->msgCtx.bankRupeesSelected);
                    this->previousBankValue = gSaveContext.save.saveInfo.bankRupees & 0xFFFF;
                    gSaveContext.save.saveInfo.bankRupees =
                        ((gSaveContext.save.saveInfo.bankRupees & 0xFFFF) + play->msgCtx.bankRupeesSelected) |
                        (gSaveContext.save.saveInfo.bankRupees & 0xFFFF0000);
                }
            } else { // GINKOMAN_CHOICE_NO
                Audio_PlaySfx_MessageCancel();
                Actor_ChangeAnimationByInfo(&this->skelAnime, sAnimationInfo, GINKO_ANIM_SITTING);
                if ((gSaveContext.save.saveInfo.bankRupees & 0xFFFF) == 0) {
                    Message_StartTextbox(play, 0x456, &this->actor);
                    this->curTextId = 0x456; // Is that so? think about it
                } else {
                    Message_StartTextbox(play, 0x47D, &this->actor);
                    this->curTextId = 0x47D; // is that so? think it over
                }
            }
            break;
        case 0x468: // Deposit OR withdrawl OR cancel screen
            if (play->msgCtx.choiceIndex == GINKOMAN_CHOICE_CANCEL) {
                Audio_PlaySfx_MessageCancel();
                Message_StartTextbox(play, 0x470, &this->actor);
                this->curTextId = 0x470; // "Is that so? Come back and deposit some after saving up a bunch!"
            } else {
                Audio_PlaySfx_MessageDecide();
                this->choiceDepositWithdrawl = play->msgCtx.choiceIndex;
                if (!this->isStampChecked) {
                    this->isStampChecked = true;
                    Message_StartTextbox(play, 0x469, &this->actor);
                    this->curTextId = 0x469; // "Excuse me, but let me take a look at you..."
                } else {
                    Message_StartTextbox(play, 0x47E, &this->actor);
                    this->curTextId = 0x47E; // "Your deposits total [rupees]."
                }
            }
            break;
        case 0x471: // Are you really withdrawling [selected rupees]?
            if (play->msgCtx.choiceIndex == GINKOMAN_CHOICE_YES) {
                if ((s32)((gSaveContext.save.saveInfo.bankRupees & 0xFFFF)) <
                    ((s32)(play->msgCtx.bankRupeesSelected + this->serviceFee))) {
                    Audio_PlaySfx(NA_SE_SY_ERROR);
                    Actor_ChangeAnimationByInfo(&this->skelAnime, sAnimationInfo, GINKO_ANIM_LEGSMACKING);
                    Message_StartTextbox(play, 0x476, &this->actor);
                    this->curTextId = 0x476; // you dont have enough deposited to withdrawl
                } else if (CUR_CAPACITY(UPG_WALLET) <
                           (play->msgCtx.bankRupeesSelected + gSaveContext.save.saveInfo.playerData.rupees)) {
                    // check if wallet is big enough
                    Audio_PlaySfx(NA_SE_SY_ERROR);
                    Message_StartTextbox(play, 0x475, &this->actor);
                    this->curTextId = 0x475; // You can't hold that many in your wallet
                } else {
                    Audio_PlaySfx_MessageDecide();
                    if (play->msgCtx.bankRupeesSelected >= 100) {
                        Message_StartTextbox(play, 0x474, &this->actor);
                        this->curTextId = 0x474; // Aw, you're taking out all that?
                    } else if (play->msgCtx.bankRupeesSelected >= 10) {
                        Message_StartTextbox(play, 0x473, &this->actor);
                        this->curTextId = 0x473; // use it wisely
                    } else {
                        Message_StartTextbox(play, 0x472, &this->actor);
                        this->curTextId = 0x472; // It's a waste to take out such a tiny bit
                    }

                    this->previousBankValue = (s16)(gSaveContext.save.saveInfo.bankRupees & 0xFFFF);
                    gSaveContext.save.saveInfo.bankRupees =
                        (((gSaveContext.save.saveInfo.bankRupees & 0xFFFF) - play->msgCtx.bankRupeesSelected) -
                         this->serviceFee) |
                        (gSaveContext.save.saveInfo.bankRupees & 0xFFFF0000);
                    Rupees_ChangeBy(play->msgCtx.bankRupeesSelected);
                }
            } else {
                Audio_PlaySfx_MessageCancel();
                Message_StartTextbox(play, 0x47C, &this->actor);
                this->curTextId = 0x47C; // "Is that so? Think it over, little guy! So what are you gonna do?"
            }
            break;
    }
}

void EnGinkoMan_WaitForRupeeCount(EnGinkoMan* this, PlayState* play) {
    if (Message_ShouldAdvance(play)) {
        switch (this->curTextId) {
            case 0x450: // "How much? How much?" [rupee prompt] Set the amount with [Control Stick] and
                if (play->msgCtx.bankRupeesSelected == 0) {
                    Actor_ChangeAnimationByInfo(&this->skelAnime, sAnimationInfo, GINKO_ANIM_SITTING);
                    Message_StartTextbox(play, 0x457, &this->actor);
                    this->curTextId = 0x457; // Zero Rupees? Cruel joke!
                } else {
                    Message_StartTextbox(play, 0x452, &this->actor);
                    this->curTextId = 0x452; // Really? are you really depositing [x]? Y/n
                }
                break;
            case 0x46E: // "How much do you want?"  [rupee prompt] Set the amount with [Control Stick]
                if (play->msgCtx.bankRupeesSelected == 0) {
                    Message_StartTextbox(play, 0x46F, &this->actor);
                    this->curTextId = 0x46F; // "Zero Rupees?!?  That's a cruel joke!"
                } else if (gSaveContext.save.isNight == true) {
                    Message_StartTextbox(play, 0x477, &this->actor);
                    this->curTextId = 0x477; // "...You know, at this time of day there's a 4 Rupee service charge...
                } else {
                    Message_StartTextbox(play, 0x471, &this->actor);
                    this->curTextId = 0x471; // "Are you really withdrawing [rupees selected]? Y/n
                    this->serviceFee = 0;
                }
                break;
        }
    }
}

void EnGinkoMan_SetupDialogue(EnGinkoMan* this) {
    this->actionFunc = EnGinkoMan_Dialogue;
}

void EnGinkoMan_Dialogue(EnGinkoMan* this, PlayState* play) {
    switch (Message_GetState(&play->msgCtx)) {
        case TEXT_STATE_CLOSING:
            EnGinkoMan_SetupIdle(this);
            break;

        case TEXT_STATE_CHOICE:
            EnGinkoMan_WaitForDialogueInput(this, play);
            break;

        case TEXT_STATE_5:
            EnGinkoMan_DepositDialogue(this, play);
            break;

        case TEXT_STATE_DONE:
            if (Message_ShouldAdvance(play)) {
                this->isStampChecked = false;
                EnGinkoMan_SetupIdle(this);
            }
            break;

        case TEXT_STATE_14:
            EnGinkoMan_WaitForRupeeCount(this, play);
            break;

        case TEXT_STATE_NONE:
        default:
            break;
    }

    if ((this->skelAnime.animation == &object_boj_Anim_0008C0) &&
        Animation_OnFrame(&this->skelAnime, this->skelAnime.endFrame)) {
        Actor_PlaySfx(&this->actor, NA_SE_EV_BANK_MAN_HAND_HIT);
    }
}

void EnGinkoMan_SetupBankAward(EnGinkoMan* this) {
    this->actionFunc = EnGinkoMan_BankAward;
}

void EnGinkoMan_BankAward(EnGinkoMan* this, PlayState* play) {
    if (Actor_HasParent(&this->actor, play)) {
        // Parent is the player when starting to receive the award
        this->actor.parent = NULL;
        EnGinkoMan_SetupBankAward2(this);
    } else if (this->curTextId == 0x45B) { // "Whats this, you already saved up 200?"
        if (!CHECK_WEEKEVENTREG(WEEKEVENTREG_10_08)) {
            Actor_OfferGetItem(&this->actor, play, GI_WALLET_ADULT + CUR_UPG_VALUE(UPG_WALLET), 500.0f, 100.0f);
        } else {
            Actor_OfferGetItem(&this->actor, play, GI_RUPEE_BLUE, 500.0f, 100.0f);
        }
    } else if (this->curTextId == 0x45C) { // "Whats this, you already saved up 5000?"
        Actor_OfferGetItem(&this->actor, play, GI_RUPEE_BLUE, 500.0f, 100.0f);
    } else if (!CHECK_WEEKEVENTREG(WEEKEVENTREG_59_08)) {
        Actor_OfferGetItem(&this->actor, play, GI_HEART_PIECE, 500.0f, 100.0f);
    } else {
        Actor_OfferGetItem(&this->actor, play, GI_RUPEE_BLUE, 500.0f, 100.0f);
    }
}

// called when bank has a parent actor
void EnGinkoMan_SetupBankAward2(EnGinkoMan* this) {
    this->actionFunc = EnGinkoMan_BankAward2;
}

// separate function to handle bank rewards... called while the player is receiving the award
void EnGinkoMan_BankAward2(EnGinkoMan* this, PlayState* play) {
    if (Actor_ProcessTalkRequest(&this->actor, &play->state)) {
        if (!CHECK_WEEKEVENTREG(WEEKEVENTREG_10_08) && (this->curTextId == 0x45B)) {
            // "What's this? You've already saved up 200 Rupees!?!  Well, little guy, here's your special gift. Take
            // it!"
            SET_WEEKEVENTREG(WEEKEVENTREG_10_08);
            Message_StartTextbox(play, 0x47A, &this->actor);
            this->curTextId = 0x47A; // Message after receiving reward for depositing 200 rupees.
        } else {
            Actor_ChangeAnimationByInfo(&this->skelAnime, sAnimationInfo, GINKO_ANIM_SITTING);
            Message_StartTextbox(play, 0x47B, &this->actor);
            this->curTextId = 0x47B; // Message after receiving reward for depositing 1000 rupees.
        }

        EnGinkoMan_SetupDialogue(this);
    } else if (this->curTextId == 0x45D) { // saved up 5000 rupees for HP
        if ((Message_GetState(&play->msgCtx) == TEXT_STATE_DONE) && Message_ShouldAdvance(play)) {
            if (!CHECK_WEEKEVENTREG(WEEKEVENTREG_59_08)) {
                SET_WEEKEVENTREG(WEEKEVENTREG_59_08);
            }
            EnGinkoMan_SetupIdle(this);
        }
    } else {
        func_800B85E0(&this->actor, play, 500.0f, PLAYER_IA_MINUS1);
    }
}

void EnGinkoMan_SetupStamp(EnGinkoMan* this) {
    Actor_ChangeAnimationByInfo(&this->skelAnime, sAnimationInfo, GINKO_ANIM_REACHING);
    this->actionFunc = EnGinkoMan_Stamp;
}

void EnGinkoMan_Stamp(EnGinkoMan* this, PlayState* play) {
    if ((this->curTextId == 0x464) // "Hey, relax! It doesn't leave any marks, and it's not gonna hurt."
        && (Animation_OnFrame(&this->skelAnime, 10.0f))) {
        Actor_PlaySfx(&this->actor, NA_SE_EV_HANKO); // "stamp"
    }

    if (Animation_OnFrame(&this->skelAnime, this->skelAnime.endFrame)) {
        switch (this->curTextId) {
            case 0x464: // "Hey, relax! It doesn't leave any marks, and it's not gonna hurt."
                Actor_ChangeAnimationByInfo(&this->skelAnime, sAnimationInfo, GINKO_ANIM_SITTING);
                Message_StartTextbox(play, 0x465, &this->actor);
                this->curTextId = 0x465; // "There! Now I'll know you when I see you!"
                break;
            case 0x469: // "Excuse me, but let me take a look at you..."
                Actor_ChangeAnimationByInfo(&this->skelAnime, sAnimationInfo, GINKO_ANIM_SITTING);
                play->msgCtx.bankRupees = (gSaveContext.save.saveInfo.bankRupees & 0xFFFF);
                if ((CURRENT_DAY == 3) && (gSaveContext.save.isNight == true)) {
                    Message_StartTextbox(play, 0x46C, &this->actor);
                    this->curTextId = 0x46C; // "Ah, yes...[Link], right?
                } else {
                    Message_StartTextbox(play, 0x46A, &this->actor);
                    this->curTextId = 0x46A; // "Ah, yes...[Link].
                }
                break;
        }

        EnGinkoMan_SetupDialogue(this);
    }
}

void EnGinkoMan_SwitchAnimation(EnGinkoMan* this, PlayState* play) {
    if (this->actor.xzDistToPlayer > 160.0f) {
        if (this->animTimer == 0) {
            if (this->skelAnime.animation != &object_boj_Anim_004A7C) {
                this->animTimer = 40;
                Actor_ChangeAnimationByInfo(&this->skelAnime, sAnimationInfo, GINKO_ANIM_ADVERTISING);
            }
        }
    } else if ((this->animTimer == 0) && (this->skelAnime.animation != &object_boj_Anim_000AC4)) {
        this->animTimer = 40;
        Actor_ChangeAnimationByInfo(&this->skelAnime, sAnimationInfo, GINKO_ANIM_AMAZED);
    }

    DECR(this->animTimer);
}

void EnGinkoMan_FacePlayer(EnGinkoMan* this, PlayState* play) {
    SkelAnime_Update(&this->skelAnime);
    if (this->skelAnime.animation != &object_boj_Anim_004A7C) {
        Actor_TrackPlayer(play, &this->actor, &this->limb15Rot, &this->limb8Rot, this->actor.focus.pos);
    } else {
        Actor_TrackNone(&this->limb15Rot, &this->limb8Rot);
    }
}

void EnGinkoMan_Update(Actor* thisx, PlayState* play) {
    EnGinkoMan* this = THIS;

    this->actionFunc(this, play);
    this->actor.focus.pos = this->actor.world.pos;
    this->actor.focus.pos.y += 30.0f;
    EnGinkoMan_FacePlayer(this, play);
}

s32 EnGinkoMan_OverrideLimbDraw(PlayState* play, s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3s* rot, Actor* thisx) {
    EnGinkoMan* this = THIS;

    if (limbIndex == 15) {
        *dList = object_boj_DL_00B1D8;
    }

    if (limbIndex == 15) {
        Matrix_Translate(1500.0f, 0.0f, 0.0f, MTXMODE_APPLY);
        Matrix_RotateXS(this->limb15Rot.y, MTXMODE_APPLY);
        Matrix_RotateZS(this->limb15Rot.x, MTXMODE_APPLY);
        Matrix_Translate(-1500.0f, 0.0f, 0.0f, MTXMODE_APPLY);
    } else if (limbIndex == 8) {
        Matrix_RotateXS(-this->limb8Rot.y, MTXMODE_APPLY);
        Matrix_RotateZS(-this->limb8Rot.x, MTXMODE_APPLY);
    }

    return false;
}

void EnGinkoMan_PostLimbDraw(PlayState* play, s32 limbIndex, Gfx** dList, Vec3s* rot, Actor* thisx) {
}

void EnGinkoMan_Draw(Actor* thisx, PlayState* play) {
    EnGinkoMan* this = THIS;

    OPEN_DISPS(play->state.gfxCtx);

    Gfx_SetupDL25_Opa(play->state.gfxCtx);

    gSPSegment(POLY_OPA_DISP++, 0x08, Gfx_EnvColor(play->state.gfxCtx, 50, 80, 0, 0));
    gSPSegment(POLY_OPA_DISP++, 0x09, Gfx_EnvColor(play->state.gfxCtx, 50, 80, 0, 0));
    gDPPipeSync(POLY_OPA_DISP++);

    SkelAnime_DrawFlexOpa(play, this->skelAnime.skeleton, this->skelAnime.jointTable, this->skelAnime.dListCount,
                          EnGinkoMan_OverrideLimbDraw, EnGinkoMan_PostLimbDraw, &this->actor);

    CLOSE_DISPS(play->state.gfxCtx);
}
