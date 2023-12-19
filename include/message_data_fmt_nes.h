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
#define CTRL_COLOR_0 00
#define CTRL_COLOR_1 01
#define CTRL_COLOR_2 02
#define CTRL_COLOR_3 03
#define CTRL_COLOR_4 04
#define CTRL_COLOR_5 05
#define CTRL_COLOR_6 06
#define CTRL_COLOR_7 07
#define CTRL_COLOR_8 08
#define CTRL_0A 0A
#define CTRL_0B 0B
#define CTRL_0C 0C
#define CTRL_0D 0D
#define CTRL_0E 0E
#define CTRL_0F 0F
#define CTRL_BOX_BREAK 10
#define CTRL_NEWLINE 11
#define CTRL_BOX_BREAK2 12
#define CTRL_13 13
#define CTRL_SHIFT 14
#define CTRL_15 15
#define CTRL_NAME 16
#define CTRL_QUICKTEXT_ENABLE 17
#define CTRL_QUICKTEXT_DISABLE 18
#define CTRL_EVENT 19
#define CTRL_PERSISTENT 1A
#define CTRL_BOX_BREAK_DELAYED 1B
#define CTRL_1C 1C
#define CTRL_1D 1D
#define CTRL_SFX 1E
#define CTRL_1F 1F
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
#define CTRL_C4 C4
#define CTRL_C5 C5
#define CTRL_C6 C6
#define CTRL_C7 C7
#define CTRL_C8 C8
#define CTRL_C9 C9
#define CTRL_CA CA
#define CTRL_CB CB
#define CTRL_CC CC
#define CTRL_CD CD
#define CTRL_CE CE
#define CTRL_CF CF
#define CTRL_D0 D0
#define CTRL_D1 D1
#define CTRL_D2 D2
#define CTRL_D3 D3
#define CTRL_D4 D4
#define CTRL_D5 D5
#define CTRL_D6 D6
#define CTRL_D7 D7
#define CTRL_D8 D8
#define CTRL_D9 D9
#define CTRL_DA DA
#define CTRL_DB DB
#define CTRL_DC DC
#define CTRL_DD DD
#define CTRL_DE DE
#define CTRL_DF DF
#define CTRL_E0 E0
#define CTRL_E1 E1
#define CTRL_E2 E2
#define CTRL_E3 E3
#define CTRL_E4 E4
#define CTRL_E5 E5
#define CTRL_E6 E6
#define CTRL_E7 E7
#define CTRL_E8 E8
#define CTRL_F0 F0
#define CTRL_F1 F1
#define CTRL_F2 F2
#define CTRL_F3 F3
#define CTRL_F4 F4
#define CTRL_F5 F5
#define CTRL_F6 F6
#define CTRL_F7 F7
#define CTRL_F8 F8
#define CTRL_F9 F9
#define CTRL_FA FA
#define CTRL_FB FB
#define CTRL_FC FC
#define CTRL_FD FD
#define CTRL_FE FE
#define CTRL_FF FF

#ifdef MESSAGE_DATA_STATIC
// For use in message_data_static files

#define ARG(x) x

#define CMD_COLOR_0 STR(CTRL_COLOR_0)
#define CMD_COLOR_1 STR(CTRL_COLOR_1)
#define CMD_COLOR_2 STR(CTRL_COLOR_2)
#define CMD_COLOR_3 STR(CTRL_COLOR_3)
#define CMD_COLOR_4 STR(CTRL_COLOR_4)
#define CMD_COLOR_5 STR(CTRL_COLOR_5)
#define CMD_COLOR_6 STR(CTRL_COLOR_6)
#define CMD_COLOR_7 STR(CTRL_COLOR_7)
#define CMD_COLOR_8 STR(CTRL_COLOR_8)
#define CMD_0A STR(CTRL_0A)
#define CMD_0B STR(CTRL_0B)
#define CMD_0C STR(CTRL_0C)
#define CMD_0D STR(CTRL_0D)
#define CMD_0E STR(CTRL_0E)
#define CMD_0F STR(CTRL_0F)
#define CMD_BOX_BREAK STR(CTRL_BOX_BREAK)
// while a control character, newlines are handled in the charmap conversion
// stage to allow normal newline \n usage in message_data_static files
#define CMD_NEWLINE STR(CTRL_NEWLINE)
#define CMD_BOX_BREAK2 STR(CTRL_BOX_BREAK2)
#define CMD_13 STR(CTRL_13)
#define CMD_SHIFT(x) STR(CTRL_SHIFT) ARG(x) // 1
#define CMD_15 STR(CTRL_15)
#define CMD_NAME STR(CTRL_NAME)
#define CMD_QUICKTEXT_ENABLE STR(CTRL_QUICKTEXT_ENABLE)
#define CMD_QUICKTEXT_DISABLE STR(CTRL_QUICKTEXT_DISABLE)
#define CMD_EVENT STR(CTRL_EVENT)
#define CMD_PERSISTENT STR(CTRL_PERSISTENT)
#define CMD_BOX_BREAK_DELAYED(x) STR(CTRL_BOX_BREAK_DELAYED) ARG(x) // 2
#define CMD_1C(x) STR(CTRL_1C) ARG(x) // 2
#define CMD_1D(x) STR(CTRL_1D) ARG(x) // 2
#define CMD_SFX(x) STR(CTRL_SFX) ARG(x) // 2
#define CMD_1F(x) STR(CTRL_1F) ARG(x) // 2
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
#define CMD_C4 STR(CTRL_C4)
#define CMD_C5 STR(CTRL_C5)
#define CMD_C6 STR(CTRL_C6)
#define CMD_C7 STR(CTRL_C7)
#define CMD_C8 STR(CTRL_C8)
#define CMD_C9 STR(CTRL_C9)
#define CMD_CA STR(CTRL_CA)
#define CMD_CB STR(CTRL_CB)
#define CMD_CC STR(CTRL_CC)
#define CMD_CD STR(CTRL_CD)
#define CMD_CE STR(CTRL_CE)
#define CMD_CF STR(CTRL_CF)
#define CMD_D0 STR(CTRL_D0)
#define CMD_D1 STR(CTRL_D1)
#define CMD_D2 STR(CTRL_D2)
#define CMD_D3 STR(CTRL_D3)
#define CMD_D4 STR(CTRL_D4)
#define CMD_D5 STR(CTRL_D5)
#define CMD_D6 STR(CTRL_D6)
#define CMD_D7 STR(CTRL_D7)
#define CMD_D8 STR(CTRL_D8)
#define CMD_D9 STR(CTRL_D9)
#define CMD_DA STR(CTRL_DA)
#define CMD_DB STR(CTRL_DB)
#define CMD_DC STR(CTRL_DC)
#define CMD_DD STR(CTRL_DD)
#define CMD_DE STR(CTRL_DE)
#define CMD_DF STR(CTRL_DF)
#define CMD_E0 STR(CTRL_E0)
#define CMD_E1 STR(CTRL_E1)
#define CMD_E2 STR(CTRL_E2)
#define CMD_E3 STR(CTRL_E3)
#define CMD_E4 STR(CTRL_E4)
#define CMD_E5 STR(CTRL_E5)
#define CMD_E6 STR(CTRL_E6)
#define CMD_E7 STR(CTRL_E7)
#define CMD_E8 STR(CTRL_E8)
#define CMD_F0 STR(CTRL_F0)
#define CMD_F1 STR(CTRL_F1)
#define CMD_F2 STR(CTRL_F2)
#define CMD_F3 STR(CTRL_F3)
#define CMD_F4 STR(CTRL_F4)
#define CMD_F5 STR(CTRL_F5)
#define CMD_F6 STR(CTRL_F6)
#define CMD_F7 STR(CTRL_F7)
#define CMD_F8 STR(CTRL_F8)
#define CMD_F9 STR(CTRL_F9)
#define CMD_FA STR(CTRL_FA)
#define CMD_FB STR(CTRL_FB)
#define CMD_FC STR(CTRL_FC)
#define CMD_FD STR(CTRL_FD)
#define CMD_FE STR(CTRL_FE)
#define CMD_FF STR(CTRL_FF)

#else

#define MESSAGE_COLOR_0 HEX(CTRL_COLOR_0)
#define MESSAGE_COLOR_1 HEX(CTRL_COLOR_1)
#define MESSAGE_COLOR_2 HEX(CTRL_COLOR_2)
#define MESSAGE_COLOR_3 HEX(CTRL_COLOR_3)
#define MESSAGE_COLOR_4 HEX(CTRL_COLOR_4)
#define MESSAGE_COLOR_5 HEX(CTRL_COLOR_5)
#define MESSAGE_COLOR_6 HEX(CTRL_COLOR_6)
#define MESSAGE_COLOR_7 HEX(CTRL_COLOR_7)
#define MESSAGE_COLOR_8 HEX(CTRL_COLOR_8)
#define MESSAGE_0A HEX(CTRL_0A)
#define MESSAGE_0B HEX(CTRL_0B)
#define MESSAGE_0C HEX(CTRL_0C)
#define MESSAGE_0D HEX(CTRL_0D)
#define MESSAGE_0E HEX(CTRL_0E)
#define MESSAGE_0F HEX(CTRL_0F)
#define MESSAGE_BOX_BREAK HEX(CTRL_BOX_BREAK)
#define MESSAGE_NEWLINE HEX(CTRL_NEWLINE)
#define MESSAGE_BOX_BREAK2 HEX(CTRL_BOX_BREAK2)
#define MESSAGE_13 HEX(CTRL_13)
#define MESSAGE_SHIFT HEX(CTRL_SHIFT)
#define MESSAGE_15 HEX(CTRL_15)
#define MESSAGE_NAME HEX(CTRL_NAME)
#define MESSAGE_QUICKTEXT_ENABLE HEX(CTRL_QUICKTEXT_ENABLE)
#define MESSAGE_QUICKTEXT_DISABLE HEX(CTRL_QUICKTEXT_DISABLE)
#define MESSAGE_EVENT HEX(CTRL_EVENT)
#define MESSAGE_PERSISTENT HEX(CTRL_PERSISTENT)
#define MESSAGE_BOX_BREAK_DELAYED HEX(CTRL_BOX_BREAK_DELAYED)
#define MESSAGE_1C HEX(CTRL_1C)
#define MESSAGE_1D HEX(CTRL_1D)
#define MESSAGE_SFX HEX(CTRL_SFX)
#define MESSAGE_1F HEX(CTRL_1F)
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
#define MESSAGE_C4 HEX(CTRL_C4)
#define MESSAGE_C5 HEX(CTRL_C5)
#define MESSAGE_C6 HEX(CTRL_C6)
#define MESSAGE_C7 HEX(CTRL_C7)
#define MESSAGE_C8 HEX(CTRL_C8)
#define MESSAGE_C9 HEX(CTRL_C9)
#define MESSAGE_CA HEX(CTRL_CA)
#define MESSAGE_CB HEX(CTRL_CB)
#define MESSAGE_CC HEX(CTRL_CC)
#define MESSAGE_CD HEX(CTRL_CD)
#define MESSAGE_CE HEX(CTRL_CE)
#define MESSAGE_CF HEX(CTRL_CF)
#define MESSAGE_D0 HEX(CTRL_D0)
#define MESSAGE_D1 HEX(CTRL_D1)
#define MESSAGE_D2 HEX(CTRL_D2)
#define MESSAGE_D3 HEX(CTRL_D3)
#define MESSAGE_D4 HEX(CTRL_D4)
#define MESSAGE_D5 HEX(CTRL_D5)
#define MESSAGE_D6 HEX(CTRL_D6)
#define MESSAGE_D7 HEX(CTRL_D7)
#define MESSAGE_D8 HEX(CTRL_D8)
#define MESSAGE_D9 HEX(CTRL_D9)
#define MESSAGE_DA HEX(CTRL_DA)
#define MESSAGE_DB HEX(CTRL_DB)
#define MESSAGE_DC HEX(CTRL_DC)
#define MESSAGE_DD HEX(CTRL_DD)
#define MESSAGE_DE HEX(CTRL_DE)
#define MESSAGE_DF HEX(CTRL_DF)
#define MESSAGE_E0 HEX(CTRL_E0)
#define MESSAGE_E1 HEX(CTRL_E1)
#define MESSAGE_E2 HEX(CTRL_E2)
#define MESSAGE_E3 HEX(CTRL_E3)
#define MESSAGE_E4 HEX(CTRL_E4)
#define MESSAGE_E5 HEX(CTRL_E5)
#define MESSAGE_E6 HEX(CTRL_E6)
#define MESSAGE_E7 HEX(CTRL_E7)
#define MESSAGE_E8 HEX(CTRL_E8)
#define MESSAGE_F0 HEX(CTRL_F0)
#define MESSAGE_F1 HEX(CTRL_F1)
#define MESSAGE_F2 HEX(CTRL_F2)
#define MESSAGE_F3 HEX(CTRL_F3)
#define MESSAGE_F4 HEX(CTRL_F4)
#define MESSAGE_F5 HEX(CTRL_F5)
#define MESSAGE_F6 HEX(CTRL_F6)
#define MESSAGE_F7 HEX(CTRL_F7)
#define MESSAGE_F8 HEX(CTRL_F8)
#define MESSAGE_F9 HEX(CTRL_F9)
#define MESSAGE_FA HEX(CTRL_FA)
#define MESSAGE_FB HEX(CTRL_FB)
#define MESSAGE_FC HEX(CTRL_FC)
#define MESSAGE_FD HEX(CTRL_FD)
#define MESSAGE_FE HEX(CTRL_FE)
#define MESSAGE_FF HEX(CTRL_FF)

#endif

#endif
