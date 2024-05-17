#ifndef Z64MSGEVENT_H
#define Z64MSGEVENT_H

#include "PR/ultratypes.h"

struct PlayState;
struct Actor;

typedef enum {
    /* 0x00 */ MSCRIPT_CMD_BRANCH_ON_WEEK_EVENT_REG,
    /* 0x01 */ MSCRIPT_CMD_BRANCH_IF_GORON,
    /* 0x02 */ MSCRIPT_CMD_BRANCH_IF_ZORA,
    /* 0x03 */ MSCRIPT_CMD_BRANCH_IF_DEKU,
    /* 0x04 */ MSCRIPT_CMD_BRANCH_IF_HUMAN,
    /* 0x05 */ MSCRIPT_CMD_BRANCH_ON_TEXT_CHOICE,
    /* 0x06 */ MSCRIPT_CMD_OFFER_ITEM,
    /* 0x07 */ MSCRIPT_CMD_AUTOTALK,
    /* 0x08 */ MSCRIPT_CMD_BRANCH_ON_RUPEES,
    /* 0x09 */ MSCRIPT_CMD_BRANCH_ON_CALLBACK,
    /* 0x0A */ MSCRIPT_CMD_BRANCH_ON_DAY,
    /* 0x0B */ MSCRIPT_CMD_AWAIT_TEXT_JUMP,
    /* 0x0C */ MSCRIPT_CMD_AWAIT_TEXT,
    /* 0x0D */ MSCRIPT_CMD_AWAIT_TEXT_END,
    /* 0x0E */ MSCRIPT_CMD_BEGIN_TEXT,
    /* 0x0F */ MSCRIPT_CMD_CONTINUE_TEXT,
    /* 0x10 */ MSCRIPT_CMD_DONE,
    /* 0x11 */ MSCRIPT_CMD_WEEK_EVENT_REG_SET,
    /* 0x12 */ MSCRIPT_CMD_CLOSE_TEXT,
    /* 0x13 */ MSCRIPT_CMD_COLLECT_SET,
    /* 0x14 */ MSCRIPT_CMD_CHANGE_RUPEES,
    /* 0x15 */ MSCRIPT_CMD_PAUSE,
    /* 0x16 */ MSCRIPT_CMD_UNSET_AUTOTALK,
    /* 0x17 */ MSCRIPT_CMD_FOCUS_TO_CHILD,
    /* 0x18 */ MSCRIPT_CMD_FOCUS_TO_SELF,
    /* 0x19 */ MSCRIPT_CMD_JUMP,
    /* 0x1A */ MSCRIPT_CMD_BRANCH_ON_QUEST_ITEM,
    /* 0x1B */ MSCRIPT_CMD_BRANCH_ON_EVENT_INF,
    /* 0x1C */ MSCRIPT_CMD_SET_EVENT_INF,
    /* 0x1D */ MSCRIPT_CMD_UNSET_EVENT_INF,
    /* 0x1E */ MSCRIPT_CMD_BRANCH_ON_ITEMACTION,
    /* 0x1F */ MSCRIPT_CMD_BRANCH_ON_SONG_OBTAINED,
    /* 0x20 */ MSCRIPT_CMD_BRANCH_ON_WORN_MASK,
    /* 0x21 */ MSCRIPT_CMD_BRANCH_ON_TIME_GT,
    /* 0x22 */ MSCRIPT_CMD_BRANCH_ON_TIME_LEQ,
    /* 0x23 */ MSCRIPT_CMD_BRANCH_ON_SWITCH_FLAG,
    /* 0x24 */ MSCRIPT_CMD_SET_SWITCH_FLAG,
    /* 0x25 */ MSCRIPT_CMD_BRANCH_ON_ITEM,
    /* 0x26 */ MSCRIPT_CMD_BRANCH_ON_TIME_INTERVAL,
    /* 0x27 */ MSCRIPT_CMD_BRANCH_IF_DAY,
    /* 0x28 */ MSCRIPT_CMD_BRANCH_ON_CALLBACK_CONTINUE,
    /* 0x29 */ MSCRIPT_CMD_HAS_POWDER_KEG,
    /* 0x2A */ MSCRIPT_CMD_DEL_ITEM,
    /* 0x2B */ MSCRIPT_CMD_BRANCH_ON_CALLBACK_MULTI,
    /* 0x2C */ MSCRIPT_CMD_PLAYER_TALK,
    /* 0x2D */ MSCRIPT_CMD_NOTEBOOK_EVENT,
    /* 0x2E */ MSCRIPT_CMD_AWAIT_TEXT_DONE,
    /* 0x2F */ MSCRIPT_CMD_JUMP_3,
    /* 0x30 */ MSCRIPT_CMD_PLAY_DECIDE,
    /* 0x31 */ MSCRIPT_CMD_PLAY_CANCEL,
    /* 0x32 */ MSCRIPT_CMD_PLAY_ERROR,
    /* 0x33 */ MSCRIPT_CMD_MAX
} MsgScriptCmd;

typedef u8 MsgScript;

typedef s32 (*MsgEventCallback)(struct Actor* thisx, struct PlayState* play);

typedef s32 (*MsgEventHandler)(struct Actor* actor, struct PlayState* play, u8** scriptPtr, MsgEventCallback callback, s32*);

s32 MsgEvent_RunScript(Actor* actor, struct PlayState* play, MsgScript* script, MsgEventCallback callback, s32* pos);

#define MSCRIPT_GET_8(script, i) ((script)[i])
#define MSCRIPT_GET_16(script, i) ((((script)[i + 1] | ((script)[i] << 8))))

// Command macros

#define MSCRIPT_PACK_8(v) (u8)(v)
#define MSCRIPT_PACK_16(v) (u8)_SHIFTR(v, 8, 8), (u8)_SHIFTR(v, 0, 8)

/**
 * 
 * Size = 5
 */ 
#define MSCRIPT_BRANCH_ON_WEEK_EVENT_REG(reg, skip) \
    MSCRIPT_CMD_BRANCH_ON_WEEK_EVENT_REG, MSCRIPT_PACK_16(reg), MSCRIPT_PACK_16(skip)

#define MSCRIPT_BRANCH_ON_WEEK_EVENT_REG_SIZE 5

/**
 * 
 * Size = 3
 */
#define MSCRIPT_BRANCH_IF_GORON(skip) \
    MSCRIPT_CMD_BRANCH_IF_GORON, MSCRIPT_PACK_16(skip)

#define MSCRIPT_BRANCH_IF_GORON_SIZE 3

/**
 * 
 * Size = 3
 */
#define MSCRIPT_BRANCH_IF_ZORA(skip) \
    MSCRIPT_CMD_BRANCH_IF_ZORA, MSCRIPT_PACK_16(skip)

#define MSCRIPT_BRANCH_IF_ZORA_SIZE 3

/**
 * 
 * Size = 3
 */
#define MSCRIPT_BRANCH_IF_DEKU(skip) \
    MSCRIPT_CMD_BRANCH_IF_DEKU, MSCRIPT_PACK_16(skip)

#define MSCRIPT_BRANCH_IF_DEKU_SIZE 3

/**
 * 
 * Size = 3
 */
#define MSCRIPT_BRANCH_IF_HUMAN(skip) \
    MSCRIPT_CMD_BRANCH_IF_HUMAN, MSCRIPT_PACK_16(skip)

#define MSCRIPT_BRANCH_IF_HUMAN_SIZE 3

/**
 * 
 * Size = 7
 */
#define MSCRIPT_BRANCH_ON_TEXT_CHOICE(skip0, skip1, skip2) \
    MSCRIPT_CMD_BRANCH_ON_TEXT_CHOICE, MSCRIPT_PACK_16(skip0), MSCRIPT_PACK_16(skip1), MSCRIPT_PACK_16(skip2)

#define MSCRIPT_BRANCH_ON_TEXT_CHOICE_SIZE 7

/**
 * 
 * Size = 5
 */
#define MSCRIPT_OFFER_ITEM(unk, skip) \
    MSCRIPT_CMD_OFFER_ITEM, MSCRIPT_PACK_16(unk), MSCRIPT_PACK_16(skip)

#define MSCRIPT_OFFER_ITEM_SIZE 5

/**
 * Size = 3
 */
#define MSCRIPT_AUTOTALK(skip) \
    MSCRIPT_CMD_AUTOTALK, MSCRIPT_PACK_16(skip)

#define MSCRIPT_AUTOTALK_SIZE 3

/**
 * Size = 5
 */
#define MSCRIPT_BRANCH_ON_RUPEES(rupees, skip) \
    MSCRIPT_CMD_BRANCH_ON_RUPEES, MSCRIPT_PACK_16(rupees), MSCRIPT_PACK_16(skip)

#define MSCRIPT_BRANCH_ON_RUPEES_SIZE 5

/**
 * Size = 3
 */
#define MSCRIPT_BRANCH_ON_CALLBACK(skip) \
    MSCRIPT_CMD_BRANCH_ON_CALLBACK, MSCRIPT_PACK_16(skip)

#define MSCRIPT_BRANCH_ON_CALLBACK_SIZE 3

/**
 * Size = 13
 */
#define MSCRIPT_BRANCH_ON_DAY(skipDay1, skipNight1, skipDay2, skipNight2, skipDay3, skipNight3) \
    MSCRIPT_CMD_BRANCH_ON_DAY, \
    MSCRIPT_PACK_16(skipDay1), MSCRIPT_PACK_16(skipNight1), \
    MSCRIPT_PACK_16(skipDay2), MSCRIPT_PACK_16(skipNight2), \
    MSCRIPT_PACK_16(skipDay3), MSCRIPT_PACK_16(skipNight3)

#define MSCRIPT_BRANCH_ON_DAY_SIZE 13

/**
 * Size = 3
 */
#define MSCRIPT_AWAIT_TEXT_JUMP(skip) \
    MSCRIPT_CMD_AWAIT_TEXT_JUMP, MSCRIPT_PACK_16(skip)

#define MSCRIPT_AWAIT_TEXT_JUMP_SIZE 3

/**
 * Size = 1
 */
#define MSCRIPT_AWAIT_TEXT() \
    MSCRIPT_CMD_AWAIT_TEXT

#define MSCRIPT_AWAIT_TEXT_SIZE 1

/**
 * Size = 1
 */
#define MSCRIPT_AWAIT_TEXT_END() \
    MSCRIPT_CMD_AWAIT_TEXT_END

#define MSCRIPT_AWAIT_TEXT_END_SIZE 1

/**
 * Size = 3
 */
#define MSCRIPT_BEGIN_TEXT(arg) \
    MSCRIPT_CMD_BEGIN_TEXT, MSCRIPT_PACK_16(arg)

#define MSCRIPT_BEGIN_TEXT_SIZE 3

/**
 * Size = 3
 */
#define MSCRIPT_CONTINUE_TEXT(arg) \
    MSCRIPT_CMD_CONTINUE_TEXT, MSCRIPT_PACK_16(arg)

#define MSCRIPT_CONTINUE_TEXT_SIZE 3

/**
 * Size = 1
 */
#define MSCRIPT_DONE() \
    MSCRIPT_CMD_DONE

#define MSCRIPT_DONE_SIZE 1

/**
 * Size = 3
 */
#define MSCRIPT_WEEK_EVENT_REG_SET(reg) \
    MSCRIPT_CMD_WEEK_EVENT_REG_SET, MSCRIPT_PACK_16(reg)

#define MSCRIPT_WEEK_EVENT_REG_SET_SIZE 3

/**
 * Size = 1
 */
#define MSCRIPT_CLOSE_TEXT() \
    MSCRIPT_CMD_CLOSE_TEXT

#define MSCRIPT_CLOSE_TEXT_SIZE 1

/**
 * Size = 3
 */
#define MSCRIPT_COLLECT_SET(collectFlag) \
    MSCRIPT_CMD_COLLECT_SET, MSCRIPT_PACK_16(collectFlag)

#define MSCRIPT_COLLECT_SET_SIZE 3

/**
 * Size = 3
 */
#define MSCRIPT_CHANGE_RUPEES(num) \
    MSCRIPT_CMD_CHANGE_RUPEES, MSCRIPT_PACK_16(num)

#define MSCRIPT_CHANGE_RUPEES_SIZE 3

/**
 * Size = 1
 */
#define MSCRIPT_PAUSE() \
    MSCRIPT_CMD_PAUSE

#define MSCRIPT_PAUSE_SIZE 1

/**
 * Size = 1
 */
#define MSCRIPT_UNSET_AUTOTALK() \
    MSCRIPT_CMD_UNSET_AUTOTALK

#define MSCRIPT_UNSET_AUTOTALK_SIZE 1

/**
 * Size = 1
 */
#define MSCRIPT_FOCUS_TO_CHILD() \
    MSCRIPT_CMD_FOCUS_TO_CHILD

#define MSCRIPT_FOCUS_TO_CHILD_SIZE 1

/**
 * Size = 1
 */
#define MSCRIPT_FOCUS_TO_SELF() \
    MSCRIPT_CMD_FOCUS_TO_SELF

#define MSCRIPT_FOCUS_TO_SELF_SIZE 1

/**
 * Size = 3
 */
#define MSCRIPT_JUMP(skip) \
    MSCRIPT_CMD_JUMP, MSCRIPT_PACK_16(skip)

#define MSCRIPT_JUMP_SIZE 3

/**
 * Size = 5
 */
#define MSCRIPT_BRANCH_ON_QUEST_ITEM(questItem, skip) \
    MSCRIPT_CMD_BRANCH_ON_QUEST_ITEM, MSCRIPT_PACK_16(questItem), MSCRIPT_PACK_16(skip)

#define MSCRIPT_BRANCH_ON_QUEST_ITEM_SIZE 5

/**
 * Size = 5
 */
#define MSCRIPT_BRANCH_ON_EVENT_INF(flag, skip) \
    MSCRIPT_CMD_BRANCH_ON_EVENT_INF, MSCRIPT_PACK_8(((flag) >> 4)), MSCRIPT_PACK_8((1 << ((flag) & 0xF))), MSCRIPT_PACK_16(skip)

#define MSCRIPT_BRANCH_ON_EVENT_INF_SIZE 5

/**
 * Size = 3
 */
#define MSCRIPT_SET_EVENT_INF(flag) \
    MSCRIPT_CMD_SET_EVENT_INF, MSCRIPT_PACK_8(((flag) >> 4)), MSCRIPT_PACK_8((1 << ((flag) & 0xF)))

#define MSCRIPT_SET_EVENT_INF_SIZE 3

/**
 * Size = 3
 */
#define MSCRIPT_UNSET_EVENT_INF(flag) \
    MSCRIPT_CMD_UNSET_EVENT_INF, MSCRIPT_PACK_8(((flag) >> 4)), MSCRIPT_PACK_8((1 << ((flag) & 0xF)))

#define MSCRIPT_UNSET_EVENT_INF_SIZE 3

/**
 * Size = 9
 */
#define MSCRIPT_BRANCH_ON_ITEMACTION(unk, skipEqual, skipDefault, skipUnk) \
    MSCRIPT_CMD_BRANCH_ON_ITEMACTION, MSCRIPT_PACK_16(unk), MSCRIPT_PACK_16(skipEqual), MSCRIPT_PACK_16(skipDefault), MSCRIPT_PACK_16(skipUnk)

#define MSCRIPT_BRANCH_ON_ITEMACTION_SIZE 9

/**
 * Size = 5
 */
#define MSCRIPT_BRANCH_ON_SONG_OBTAINED(questItem, skip) \
    MSCRIPT_CMD_BRANCH_ON_SONG_OBTAINED, MSCRIPT_PACK_16(questItem), MSCRIPT_PACK_16(skip)

#define MSCRIPT_BRANCH_ON_SONG_OBTAINED_SIZE 5

/**
 * Size = 5
 */
#define MSCRIPT_BRANCH_ON_WORN_MASK(mask, skip) \
    MSCRIPT_CMD_BRANCH_ON_WORN_MASK, MSCRIPT_PACK_16(mask), MSCRIPT_PACK_16(skip)

#define MSCRIPT_BRANCH_ON_WORN_MASK_SIZE 5

/**
 * Size = 5
 */
#define MSCRIPT_BRANCH_ON_TIME_GT(hours, minutes, skip) \
    MSCRIPT_CMD_BRANCH_ON_TIME_GT, MSCRIPT_PACK_8(hours), MSCRIPT_PACK_8(minutes), MSCRIPT_PACK_16(skip)

#define MSCRIPT_BRANCH_ON_TIME_GT_SIZE 5

/**
 * Size = 5
 */
#define MSCRIPT_BRANCH_ON_TIME_LEQ(hours, minutes, skip) \
    MSCRIPT_CMD_BRANCH_ON_TIME_LEQ, MSCRIPT_PACK_8(hours), MSCRIPT_PACK_8(minutes), MSCRIPT_PACK_16(skip)

#define MSCRIPT_BRANCH_ON_TIME_LEQ_SIZE 5

/**
 * Size = 5
 */
#define MSCRIPT_BRANCH_ON_SWITCH_FLAG(switchFlag, skip) \
    MSCRIPT_CMD_BRANCH_ON_SWITCH_FLAG, MSCRIPT_PACK_16(switchFlag), MSCRIPT_PACK_16(skip)

#define MSCRIPT_BRANCH_ON_SWITCH_FLAG_SIZE 5

/**
 * Size = 3
 */
#define MSCRIPT_SET_SWITCH_FLAG(switchFlag) \
    MSCRIPT_CMD_SET_SWITCH_FLAG, MSCRIPT_PACK_16(switchFlag)

#define MSCRIPT_SET_SWITCH_FLAG_SIZE 3

/**
 * Size = 5
 */
#define MSCRIPT_BRANCH_ON_ITEM(item, skip) \
    MSCRIPT_CMD_BRANCH_ON_ITEM, MSCRIPT_PACK_16(item), MSCRIPT_PACK_16(skip)

#define MSCRIPT_BRANCH_ON_ITEM_SIZE 5

/**
 * Size = 7
 */
#define MSCRIPT_BRANCH_ON_TIME_INTERVAL(hours1, minutes1, hours2, minutes2, skip) \
    MSCRIPT_CMD_BRANCH_ON_TIME_INTERVAL, MSCRIPT_PACK_8(hours1), MSCRIPT_PACK_8(minutes1), MSCRIPT_PACK_8(hours2), MSCRIPT_PACK_8(minutes2), MSCRIPT_PACK_16(skip)

#define MSCRIPT_BRANCH_ON_TIME_INTERVAL_SIZE 7

/**
 * Size = 5
 */
#define MSCRIPT_BRANCH_IF_DAY(day, skip) \
    MSCRIPT_CMD_BRANCH_IF_DAY, MSCRIPT_PACK_16(day), MSCRIPT_PACK_16(skip)

#define MSCRIPT_BRANCH_IF_DAY_SIZE 5

/**
 * Size = 3
 */
#define MSCRIPT_BRANCH_ON_CALLBACK_CONTINUE(skip) \
    MSCRIPT_CMD_BRANCH_ON_CALLBACK_CONTINUE, MSCRIPT_PACK_16(skip)

#define MSCRIPT_BRANCH_ON_CALLBACK_CONTINUE_SIZE 3

/**
 * Size = 3
 */
#define MSCRIPT_HAS_POWDER_KEG(skip) \
    MSCRIPT_CMD_HAS_POWDER_KEG, MSCRIPT_PACK_16(skip)

#define MSCRIPT_HAS_POWDER_KEG_SIZE 3

/**
 * Size = 3
 */
#define MSCRIPT_DEL_ITEM(item) \
    MSCRIPT_CMD_DEL_ITEM, MSCRIPT_PACK_16(item)

#define MSCRIPT_DEL_ITEM_SIZE 3

/**
 * Size = 7
 */
#define MSCRIPT_BRANCH_ON_CALLBACK_MULTI(skip1, skip2, skip3) \
    MSCRIPT_CMD_BRANCH_ON_CALLBACK_MULTI, MSCRIPT_PACK_16(skip1), MSCRIPT_PACK_16(skip2), MSCRIPT_PACK_16(skip3)

#define MSCRIPT_BRANCH_ON_CALLBACK_MULTI_SIZE 7

/**
 * Size = 3
 */
#define MSCRIPT_PLAYER_TALK(textId) \
    MSCRIPT_CMD_PLAYER_TALK, MSCRIPT_PACK_16(textId)

#define MSCRIPT_PLAYER_TALK_SIZE 3

/**
 * Size = 3
 */
#define MSCRIPT_NOTEBOOK_EVENT(event) \
    MSCRIPT_CMD_NOTEBOOK_EVENT, MSCRIPT_PACK_16(event)

#define MSCRIPT_NOTEBOOK_EVENT_SIZE 3

/**
 * Size = 1
 */
#define MSCRIPT_AWAIT_TEXT_DONE() \
    MSCRIPT_CMD_AWAIT_TEXT_DONE

#define MSCRIPT_AWAIT_TEXT_DONE_SIZE 1

/**
 * Size = 3
 */
#define MSCRIPT_JUMP_3(skip) \
    MSCRIPT_CMD_JUMP_3, MSCRIPT_PACK_16(skip)

#define MSCRIPT_JUMP_3_SIZE 3

/**
 * Size = 1
 */
#define MSCRIPT_PLAY_DECIDE() \
    MSCRIPT_CMD_PLAY_DECIDE

#define MSCRIPT_PLAY_DECIDE_SIZE 1

/**
 * Size = 1
 */
#define MSCRIPT_PLAY_CANCEL() \
    MSCRIPT_CMD_PLAY_CANCEL

#define MSCRIPT_PLAY_CANCEL_SIZE 1

/**
 * Size = 1
 */
#define MSCRIPT_PLAY_ERROR() \
    MSCRIPT_CMD_PLAY_ERROR

#define MSCRIPT_PLAY_ERROR_SIZE 1

#endif
