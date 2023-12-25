#ifndef MESSAGE_DATA_FMT_NES_H
#define MESSAGE_DATA_FMT_NES_H

/*
 * Macros to create both a constant and a string literal from a magic value
 *   The constants are used in code files when parsing text for various purposes
 *   The strings are used in the message_data_static files themselves, as you can only concat strings with other strings
 */

#ifndef GLUE
#define GLUE(a, b) a##b
#endif

#define STRINGIFY(s) #s
#define EXPAND_AND_STRINGIFY(s) STRINGIFY(s)

#define HEX(N) GLUE(0x, N)
#define STR(N) EXPAND_AND_STRINGIFY(GLUE(\x, N))

/*
 * Text control characters
 */

// Control character magic values, in 2-digit hex without prefix
#define CTRL_COLOR_DEFAULT 00
#define CTRL_COLOR_RED 01
#define CTRL_COLOR_GREEN 02
#define CTRL_COLOR_BLUE 03
#define CTRL_COLOR_YELLOW 04
#define CTRL_COLOR_LIGHTBLUE 05
#define CTRL_COLOR_PINK 06
#define CTRL_COLOR_SILVER 07
#define CTRL_COLOR_ORANGE 08
#define CTRL_TEXT_SPEED 0A // Note this should take an arg 0 to 6, but always just sets next decode char as 0
#define CTRL_HS_BOAT_ARCHERY 0B
#define CTRL_STRAY_FAIRIES 0C
#define CTRL_TOKENS 0D
#define CTRL_POINTS_TENS 0E
#define CTRL_POINTS_THOUSANDS 0F
#define CTRL_BOX_BREAK 10
#define CTRL_NEWLINE 11
#define CTRL_BOX_BREAK2 12
#define CTRL_CARRIAGE_RETURN 13
#define CTRL_SHIFT 14
#define CTRL_CONTINUE 15
#define CTRL_NAME 16
#define CTRL_QUICKTEXT_ENABLE 17
#define CTRL_QUICKTEXT_DISABLE 18
#define CTRL_EVENT 19
#define CTRL_PERSISTENT 1A
#define CTRL_BOX_BREAK_DELAYED 1B
#define CTRL_FADE 1C
#define CTRL_FADE_SKIPPABLE 1D
#define CTRL_SFX 1E
#define CTRL_DELAY 1F
#define CTRL_BTN_A B0
#define CTRL_BTN_B B1
#define CTRL_BTN_C B2
#define CTRL_BTN_L B3
#define CTRL_BTN_R B4
#define CTRL_BTN_Z B5
#define CTRL_BTN_CUP B6
#define CTRL_BTN_CDOWN B7
#define CTRL_BTN_CLEFT B8
#define CTRL_BTN_CRIGHT B9
#define CTRL_Z_TARGET BA
#define CTRL_CONTROL_PAD BB
#define CTRL_END BF
#define CTRL_BACKGROUND C1
#define CTRL_TWO_CHOICE C2
#define CTRL_THREE_CHOICE C3
#define CTRL_TIMER_POSTMAN C4
#define CTRL_TIMER_MINIGAME_1 C5
#define CTRL_TIMER_2 C6
#define CTRL_TIMER_MOON_CRASH C7
#define CTRL_TIMER_MINIGAME_2 C8
#define CTRL_TIMER_ENV_HAZARD C9
#define CTRL_TIME CA
#define CTRL_CHEST_FLAGS CB
#define CTRL_INPUT_BANK CC
#define CTRL_RUPEES_SELECTED CD
#define CTRL_RUPEES_TOTAL CE
#define CTRL_TIME_UNTIL_MOON_CRASH CF
#define CTRL_INPUT_DOGGY_RACETRACK_BET D0
#define CTRL_INPUT_BOMBER_CODE D1
#define CTRL_PAUSE_MENU D2
#define CTRL_TIME_SPEED D3
#define CTRL_OWL_WARP D4
#define CTRL_INPUT_LOTTERY_CODE D5
#define CTRL_SPIDER_HOUSE_MASK_CODE D6
#define CTRL_STRAY_FAIRIES_LEFT_WOODFALL D7
#define CTRL_STRAY_FAIRIES_LEFT_SNOWHEAD D8
#define CTRL_STRAY_FAIRIES_LEFT_GREAT_BAY D9
#define CTRL_STRAY_FAIRIES_LEFT_STONE_TOWER DA
#define CTRL_POINTS_BOAT_ARCHERY DB // Seems to be the exact same as CTRL_POINTS_THOUSANDS
#define CTRL_LOTTERY_CODE DC
#define CTRL_LOTTERY_CODE_GUESS DD
#define CTRL_HELD_ITEM_PRICE DE
#define CTRL_BOMBER_CODE DF
#define CTRL_EVENT2 E0 // Seems to be the exact same as CTRL_EVENT
#define CTRL_SPIDER_HOUSE_MASK_CODE_1 E1
#define CTRL_SPIDER_HOUSE_MASK_CODE_2 E2
#define CTRL_SPIDER_HOUSE_MASK_CODE_3 E3
#define CTRL_SPIDER_HOUSE_MASK_CODE_4 E4
#define CTRL_SPIDER_HOUSE_MASK_CODE_5 E5
#define CTRL_SPIDER_HOUSE_MASK_CODE_6 E6
#define CTRL_HOURS_UNTIL_MOON_CRASH E7
#define CTRL_TIME_UNTIL_NEW_DAY E8
#define CTRL_HS_POINTS_BANK_RUPEES F0
#define CTRL_HS_POINTS_UNK_1 F1
#define CTRL_HS_POINTS_FISHING F2
#define CTRL_HS_TIME_BOAT_ARCHERY F3 // Note this interprets the highscore value as a time (not the actual timer for the minigame)
#define CTRL_HS_TIME_HORSE_BACK_BALLOON F4 // Note this interprets the highscore value as a time (not the actual timer for the minigame)
#define CTRL_HS_TIME_LOTTERY_GUESS F5
#define CTRL_HS_TOWN_SHOOTING_GALLERY F6
#define CTRL_HS_UNK_1 F7
#define CTRL_HS_UNK_3_LOWER F8
#define CTRL_HS_HORSE_BACK_BALLOON F9
#define CTRL_HS_DEKU_PLAYGROUND_DAY_1 FA
#define CTRL_HS_DEKU_PLAYGROUND_DAY_2 FB
#define CTRL_HS_DEKU_PLAYGROUND_DAY_3 FC
#define CTRL_DEKU_PLAYGROUND_NAME_DAY_1 FD
#define CTRL_DEKU_PLAYGROUND_NAME_DAY_2 FE
#define CTRL_DEKU_PLAYGROUND_NAME_DAY_3 FF

#ifdef MESSAGE_DATA_STATIC
// For use in message_data_static files

#define ARG(x) x

#define CMD_COLOR_DEFAULT STR(CTRL_COLOR_DEFAULT)
#define CMD_COLOR_RED STR(CTRL_COLOR_RED)
#define CMD_COLOR_GREEN STR(CTRL_COLOR_GREEN)
#define CMD_COLOR_BLUE STR(CTRL_COLOR_BLUE)
#define CMD_COLOR_YELLOW STR(CTRL_COLOR_YELLOW)
#define CMD_COLOR_LIGHTBLUE STR(CTRL_COLOR_LIGHTBLUE)
#define CMD_COLOR_PINK STR(CTRL_COLOR_PINK)
#define CMD_COLOR_SILVER STR(CTRL_COLOR_SILVER)
#define CMD_COLOR_ORANGE STR(CTRL_COLOR_ORANGE)
#define CMD_TEXT_SPEED STR(CTRL_TEXT_SPEED)
#define CMD_HS_BOAT_ARCHERY STR(CTRL_HS_BOAT_ARCHERY)
#define CMD_STRAY_FAIRIES STR(CTRL_STRAY_FAIRIES)
#define CMD_TOKENS STR(CTRL_TOKENS)
#define CMD_POINTS_TENS STR(CTRL_POINTS_TENS)
#define CMD_POINTS_THOUSANDS STR(CTRL_POINTS_THOUSANDS)
#define CMD_BOX_BREAK STR(CTRL_BOX_BREAK)
// while a control character, newlines are handled in the charmap conversion
// stage to allow normal newline \n usage in message_data_static files
#define CMD_NEWLINE STR(CTRL_NEWLINE)
#define CMD_BOX_BREAK2 STR(CTRL_BOX_BREAK2)
#define CMD_CARRIAGE_RETURN STR(CTRL_CARRIAGE_RETURN)
#define CMD_SHIFT(x) STR(CTRL_SHIFT) ARG(x) // 1
#define CMD_CONTINUE STR(CTRL_CONTINUE)
#define CMD_NAME STR(CTRL_NAME)
#define CMD_QUICKTEXT_ENABLE STR(CTRL_QUICKTEXT_ENABLE)
#define CMD_QUICKTEXT_DISABLE STR(CTRL_QUICKTEXT_DISABLE)
#define CMD_EVENT STR(CTRL_EVENT)
#define CMD_PERSISTENT STR(CTRL_PERSISTENT)
#define CMD_BOX_BREAK_DELAYED(x) STR(CTRL_BOX_BREAK_DELAYED) ARG(x) // 2
#define CMD_FADE(x) STR(CTRL_FADE) ARG(x) // 2
#define CMD_FADE_SKIPPABLE(x) STR(CTRL_FADE_SKIPPABLE) ARG(x) // 2
#define CMD_SFX(x) STR(CTRL_SFX) ARG(x) // 2
#define CMD_DELAY(x) STR(CTRL_DELAY) ARG(x) // 2
// while control characters, button images are handled in the charmap conversion
#define CMD_BTN_A STR(CTRL_BTN_A)
#define CMD_BTN_B STR(CTRL_BTN_B)
#define CMD_BTN_C STR(CTRL_BTN_C)
#define CMD_BTN_L STR(CTRL_BTN_L)
#define CMD_BTN_R STR(CTRL_BTN_R)
#define CMD_BTN_Z STR(CTRL_BTN_Z)
#define CMD_BTN_CUP STR(CTRL_BTN_CUP)
#define CMD_BTN_CDOWN STR(CTRL_BTN_CDOWN)
#define CMD_BTN_CLEFT STR(CTRL_BTN_CLEFT)
#define CMD_BTN_CRIGHT STR(CTRL_BTN_CRIGHT)
#define CMD_Z_TARGET STR(CTRL_Z_TARGET)
#define CMD_CONTROL_PAD STR(CTRL_CONTROL_PAD)
#define CMD_END STR(CTRL_END)
#define CMD_BACKGROUND STR(CTRL_BACKGROUND)
#define CMD_TWO_CHOICE STR(CTRL_TWO_CHOICE)
#define CMD_THREE_CHOICE STR(CTRL_THREE_CHOICE)
#define CMD_TIMER_POSTMAN STR(CTRL_TIMER_POSTMAN)
#define CMD_TIMER_MINIGAME_1 STR(CTRL_TIMER_MINIGAME_1)
#define CMD_TIMER_2 STR(CTRL_TIMER_2)
#define CMD_TIMER_MOON_CRASH STR(CTRL_TIMER_MOON_CRASH)
#define CMD_TIMER_MINIGAME_2 STR(CTRL_TIMER_MINIGAME_2)
#define CMD_TIMER_ENV_HAZARD STR(CTRL_TIMER_ENV_HAZARD)
#define CMD_TIME STR(CTRL_TIME)
#define CMD_CHEST_FLAGS STR(CTRL_CHEST_FLAGS)
#define CMD_INPUT_BANK STR(CTRL_INPUT_BANK)
#define CMD_RUPEES_SELECTED STR(CTRL_RUPEES_SELECTED)
#define CMD_RUPEES_TOTAL STR(CTRL_RUPEES_TOTAL)
#define CMD_TIME_UNTIL_MOON_CRASH STR(CTRL_TIME_UNTIL_MOON_CRASH)
#define CMD_INPUT_DOGGY_RACETRACK_BET STR(CTRL_INPUT_DOGGY_RACETRACK_BET)
#define CMD_INPUT_BOMBER_CODE STR(CTRL_INPUT_BOMBER_CODE)
#define CMD_PAUSE_MENU STR(CTRL_PAUSE_MENU)
#define CMD_TIME_SPEED STR(CTRL_TIME_SPEED)
#define CMD_OWL_WARP STR(CTRL_OWL_WARP)
#define CMD_INPUT_LOTTERY_CODE STR(CTRL_INPUT_LOTTERY_CODE)
#define CMD_SPIDER_HOUSE_MASK_CODE STR(CTRL_SPIDER_HOUSE_MASK_CODE)
#define CMD_STRAY_FAIRIES_LEFT_WOODFALL STR(CTRL_STRAY_FAIRIES_LEFT_WOODFALL)
#define CMD_STRAY_FAIRIES_LEFT_SNOWHEAD STR(CTRL_STRAY_FAIRIES_LEFT_SNOWHEAD)
#define CMD_STRAY_FAIRIES_LEFT_GREAT_BAY STR(CTRL_STRAY_FAIRIES_LEFT_GREAT_BAY)
#define CMD_STRAY_FAIRIES_LEFT_STONE_TOWER STR(CTRL_STRAY_FAIRIES_LEFT_STONE_TOWER)
#define CMD_POINTS_BOAT_ARCHERY STR(CTRL_POINTS_BOAT_ARCHERY)
#define CMD_LOTTERY_CODE STR(CTRL_LOTTERY_CODE)
#define CMD_LOTTERY_CODE_GUESS STR(CTRL_LOTTERY_CODE_GUESS)
#define CMD_HELD_ITEM_PRICE STR(CTRL_HELD_ITEM_PRICE)
#define CMD_BOMBER_CODE STR(CTRL_BOMBER_CODE)
#define CMD_EVENT2 STR(CTRL_EVENT2)
#define CMD_SPIDER_HOUSE_MASK_CODE_1 STR(CTRL_SPIDER_HOUSE_MASK_CODE_1)
#define CMD_SPIDER_HOUSE_MASK_CODE_2 STR(CTRL_SPIDER_HOUSE_MASK_CODE_2)
#define CMD_SPIDER_HOUSE_MASK_CODE_3 STR(CTRL_SPIDER_HOUSE_MASK_CODE_3)
#define CMD_SPIDER_HOUSE_MASK_CODE_4 STR(CTRL_SPIDER_HOUSE_MASK_CODE_4)
#define CMD_SPIDER_HOUSE_MASK_CODE_5 STR(CTRL_SPIDER_HOUSE_MASK_CODE_5)
#define CMD_SPIDER_HOUSE_MASK_CODE_6 STR(CTRL_SPIDER_HOUSE_MASK_CODE_6)
#define CMD_HOURS_UNTIL_MOON_CRASH STR(CTRL_HOURS_UNTIL_MOON_CRASH)
#define CMD_TIME_UNTIL_NEW_DAY STR(CTRL_TIME_UNTIL_NEW_DAY)
#define CMD_HS_POINTS_BANK_RUPEES STR(CTRL_HS_POINTS_BANK_RUPEES)
#define CMD_HS_POINTS_UNK_1 STR(CTRL_HS_POINTS_UNK_1)
#define CMD_HS_POINTS_FISHING STR(CTRL_HS_POINTS_FISHING)
#define CMD_HS_TIME_BOAT_ARCHERY STR(CTRL_HS_TIME_BOAT_ARCHERY)
#define CMD_HS_TIME_HORSE_BACK_BALLOON STR(CTRL_HS_TIME_HORSE_BACK_BALLOON)
#define CMD_HS_TIME_LOTTERY_GUESS STR(CTRL_HS_TIME_LOTTERY_GUESS)
#define CMD_HS_TOWN_SHOOTING_GALLERY STR(CTRL_HS_TOWN_SHOOTING_GALLERY)
#define CMD_HS_UNK_1 STR(CTRL_HS_UNK_1)
#define CMD_HS_UNK_3_LOWER STR(CTRL_HS_UNK_3_LOWER)
#define CMD_HS_HORSE_BACK_BALLOON STR(CTRL_HS_HORSE_BACK_BALLOON)
#define CMD_HS_DEKU_PLAYGROUND_DAY_1 STR(CTRL_HS_DEKU_PLAYGROUND_DAY_1)
#define CMD_HS_DEKU_PLAYGROUND_DAY_2 STR(CTRL_HS_DEKU_PLAYGROUND_DAY_2)
#define CMD_HS_DEKU_PLAYGROUND_DAY_3 STR(CTRL_HS_DEKU_PLAYGROUND_DAY_3)
#define CMD_DEKU_PLAYGROUND_NAME_DAY_1 STR(CTRL_DEKU_PLAYGROUND_NAME_DAY_1)
#define CMD_DEKU_PLAYGROUND_NAME_DAY_2 STR(CTRL_DEKU_PLAYGROUND_NAME_DAY_2)
#define CMD_DEKU_PLAYGROUND_NAME_DAY_3 STR(CTRL_DEKU_PLAYGROUND_NAME_DAY_3)

#else

#define MESSAGE_COLOR_DEFAULT HEX(CTRL_COLOR_DEFAULT)
#define MESSAGE_COLOR_RED HEX(CTRL_COLOR_RED)
#define MESSAGE_COLOR_GREEN HEX(CTRL_COLOR_GREEN)
#define MESSAGE_COLOR_BLUE HEX(CTRL_COLOR_BLUE)
#define MESSAGE_COLOR_YELLOW HEX(CTRL_COLOR_YELLOW)
#define MESSAGE_COLOR_LIGHTBLUE HEX(CTRL_COLOR_LIGHTBLUE)
#define MESSAGE_COLOR_PINK HEX(CTRL_COLOR_PINK)
#define MESSAGE_COLOR_SILVER HEX(CTRL_COLOR_SILVER)
#define MESSAGE_COLOR_ORANGE HEX(CTRL_COLOR_ORANGE)
#define MESSAGE_TEXT_SPEED HEX(CTRL_TEXT_SPEED)
#define MESSAGE_HS_BOAT_ARCHERY HEX(CTRL_HS_BOAT_ARCHERY)
#define MESSAGE_STRAY_FAIRIES HEX(CTRL_STRAY_FAIRIES)
#define MESSAGE_TOKENS HEX(CTRL_TOKENS)
#define MESSAGE_POINTS_TENS HEX(CTRL_POINTS_TENS)
#define MESSAGE_POINTS_THOUSANDS HEX(CTRL_POINTS_THOUSANDS)
#define MESSAGE_BOX_BREAK HEX(CTRL_BOX_BREAK)
#define MESSAGE_NEWLINE HEX(CTRL_NEWLINE)
#define MESSAGE_BOX_BREAK2 HEX(CTRL_BOX_BREAK2)
#define MESSAGE_CARRIAGE_RETURN HEX(CTRL_CARRIAGE_RETURN)
#define MESSAGE_SHIFT HEX(CTRL_SHIFT)
#define MESSAGE_CONTINUE HEX(CTRL_CONTINUE)
#define MESSAGE_NAME HEX(CTRL_NAME)
#define MESSAGE_QUICKTEXT_ENABLE HEX(CTRL_QUICKTEXT_ENABLE)
#define MESSAGE_QUICKTEXT_DISABLE HEX(CTRL_QUICKTEXT_DISABLE)
#define MESSAGE_EVENT HEX(CTRL_EVENT)
#define MESSAGE_PERSISTENT HEX(CTRL_PERSISTENT)
#define MESSAGE_BOX_BREAK_DELAYED HEX(CTRL_BOX_BREAK_DELAYED)
#define MESSAGE_FADE HEX(CTRL_FADE)
#define MESSAGE_FADE_SKIPPABLE HEX(CTRL_FADE_SKIPPABLE)
#define MESSAGE_SFX HEX(CTRL_SFX)
#define MESSAGE_DELAY HEX(CTRL_DELAY)
#define MESSAGE_BTN_A HEX(CTRL_BTN_A)
#define MESSAGE_BTN_B HEX(CTRL_BTN_B)
#define MESSAGE_BTN_C HEX(CTRL_BTN_C)
#define MESSAGE_BTN_L HEX(CTRL_BTN_L)
#define MESSAGE_BTN_R HEX(CTRL_BTN_R)
#define MESSAGE_BTN_Z HEX(CTRL_BTN_Z)
#define MESSAGE_BTN_CUP HEX(CTRL_BTN_CUP)
#define MESSAGE_BTN_CDOWN HEX(CTRL_BTN_CDOWN)
#define MESSAGE_BTN_CLEFT HEX(CTRL_BTN_CLEFT)
#define MESSAGE_BTN_CRIGHT HEX(CTRL_BTN_CRIGHT)
#define MESSAGE_Z_TARGET HEX(CTRL_Z_TARGET)
#define MESSAGE_CONTROL_PAD HEX(CTRL_CONTROL_PAD)
#define MESSAGE_END HEX(CTRL_END)
#define MESSAGE_BACKGROUND HEX(CTRL_BACKGROUND)
#define MESSAGE_TWO_CHOICE HEX(CTRL_TWO_CHOICE)
#define MESSAGE_THREE_CHOICE HEX(CTRL_THREE_CHOICE)
#define MESSAGE_TIMER_POSTMAN HEX(CTRL_TIMER_POSTMAN)
#define MESSAGE_TIMER_MINIGAME_1 HEX(CTRL_TIMER_MINIGAME_1)
#define MESSAGE_TIMER_2 HEX(CTRL_TIMER_2)
#define MESSAGE_TIMER_MOON_CRASH HEX(CTRL_TIMER_MOON_CRASH)
#define MESSAGE_TIMER_MINIGAME_2 HEX(CTRL_TIMER_MINIGAME_2)
#define MESSAGE_TIMER_ENV_HAZARD HEX(CTRL_TIMER_ENV_HAZARD)
#define MESSAGE_TIME HEX(CTRL_TIME)
#define MESSAGE_CHEST_FLAGS HEX(CTRL_CHEST_FLAGS)
#define MESSAGE_INPUT_BANK HEX(CTRL_INPUT_BANK)
#define MESSAGE_RUPEES_SELECTED HEX(CTRL_RUPEES_SELECTED)
#define MESSAGE_RUPEES_TOTAL HEX(CTRL_RUPEES_TOTAL)
#define MESSAGE_TIME_UNTIL_MOON_CRASH HEX(CTRL_TIME_UNTIL_MOON_CRASH)
#define MESSAGE_INPUT_DOGGY_RACETRACK_BET HEX(CTRL_INPUT_DOGGY_RACETRACK_BET)
#define MESSAGE_INPUT_BOMBER_CODE HEX(CTRL_INPUT_BOMBER_CODE)
#define MESSAGE_PAUSE_MENU HEX(CTRL_PAUSE_MENU)
#define MESSAGE_TIME_SPEED HEX(CTRL_TIME_SPEED)
#define MESSAGE_OWL_WARP HEX(CTRL_OWL_WARP)
#define MESSAGE_INPUT_LOTTERY_CODE HEX(CTRL_INPUT_LOTTERY_CODE)
#define MESSAGE_SPIDER_HOUSE_MASK_CODE HEX(CTRL_SPIDER_HOUSE_MASK_CODE)
#define MESSAGE_STRAY_FAIRIES_LEFT_WOODFALL HEX(CTRL_STRAY_FAIRIES_LEFT_WOODFALL)
#define MESSAGE_STRAY_FAIRIES_LEFT_SNOWHEAD HEX(CTRL_STRAY_FAIRIES_LEFT_SNOWHEAD)
#define MESSAGE_STRAY_FAIRIES_LEFT_GREAT_BAY HEX(CTRL_STRAY_FAIRIES_LEFT_GREAT_BAY)
#define MESSAGE_STRAY_FAIRIES_LEFT_STONE_TOWER HEX(CTRL_STRAY_FAIRIES_LEFT_STONE_TOWER)
#define MESSAGE_POINTS_BOAT_ARCHERY HEX(CTRL_POINTS_BOAT_ARCHERY)
#define MESSAGE_LOTTERY_CODE HEX(CTRL_LOTTERY_CODE)
#define MESSAGE_LOTTERY_CODE_GUESS HEX(CTRL_LOTTERY_CODE_GUESS)
#define MESSAGE_HELD_ITEM_PRICE HEX(CTRL_HELD_ITEM_PRICE)
#define MESSAGE_BOMBER_CODE HEX(CTRL_BOMBER_CODE)
#define MESSAGE_EVENT2 HEX(CTRL_EVENT2)
#define MESSAGE_SPIDER_HOUSE_MASK_CODE_1 HEX(CTRL_SPIDER_HOUSE_MASK_CODE_1)
#define MESSAGE_SPIDER_HOUSE_MASK_CODE_2 HEX(CTRL_SPIDER_HOUSE_MASK_CODE_2)
#define MESSAGE_SPIDER_HOUSE_MASK_CODE_3 HEX(CTRL_SPIDER_HOUSE_MASK_CODE_3)
#define MESSAGE_SPIDER_HOUSE_MASK_CODE_4 HEX(CTRL_SPIDER_HOUSE_MASK_CODE_4)
#define MESSAGE_SPIDER_HOUSE_MASK_CODE_5 HEX(CTRL_SPIDER_HOUSE_MASK_CODE_5)
#define MESSAGE_SPIDER_HOUSE_MASK_CODE_6 HEX(CTRL_SPIDER_HOUSE_MASK_CODE_6)
#define MESSAGE_HOURS_UNTIL_MOON_CRASH HEX(CTRL_HOURS_UNTIL_MOON_CRASH)
#define MESSAGE_TIME_UNTIL_NEW_DAY HEX(CTRL_TIME_UNTIL_NEW_DAY)
#define MESSAGE_HS_POINTS_BANK_RUPEES HEX(CTRL_HS_POINTS_BANK_RUPEES)
#define MESSAGE_HS_POINTS_UNK_1 HEX(CTRL_HS_POINTS_UNK_1)
#define MESSAGE_HS_POINTS_FISHING HEX(CTRL_HS_POINTS_FISHING)
#define MESSAGE_HS_TIME_BOAT_ARCHERY HEX(CTRL_HS_TIME_BOAT_ARCHERY)
#define MESSAGE_HS_TIME_HORSE_BACK_BALLOON HEX(CTRL_HS_TIME_HORSE_BACK_BALLOON)
#define MESSAGE_HS_TIME_LOTTERY_GUESS HEX(CTRL_HS_TIME_LOTTERY_GUESS)
#define MESSAGE_HS_TOWN_SHOOTING_GALLERY HEX(CTRL_HS_TOWN_SHOOTING_GALLERY)
#define MESSAGE_HS_UNK_1 HEX(CTRL_HS_UNK_1)
#define MESSAGE_HS_UNK_3_LOWER HEX(CTRL_HS_UNK_3_LOWER)
#define MESSAGE_HS_HORSE_BACK_BALLOON HEX(CTRL_HS_HORSE_BACK_BALLOON)
#define MESSAGE_HS_DEKU_PLAYGROUND_DAY_1 HEX(CTRL_HS_DEKU_PLAYGROUND_DAY_1)
#define MESSAGE_HS_DEKU_PLAYGROUND_DAY_2 HEX(CTRL_HS_DEKU_PLAYGROUND_DAY_2)
#define MESSAGE_HS_DEKU_PLAYGROUND_DAY_3 HEX(CTRL_HS_DEKU_PLAYGROUND_DAY_3)
#define MESSAGE_DEKU_PLAYGROUND_NAME_DAY_1 HEX(CTRL_DEKU_PLAYGROUND_NAME_DAY_1)
#define MESSAGE_DEKU_PLAYGROUND_NAME_DAY_2 HEX(CTRL_DEKU_PLAYGROUND_NAME_DAY_2)
#define MESSAGE_DEKU_PLAYGROUND_NAME_DAY_3 HEX(CTRL_DEKU_PLAYGROUND_NAME_DAY_3)

#endif

#endif
