/**
 * Sfx Player Bank
 *
 * DEFINE_SFX should be used for all sfx define in the player bank from sequence 0
 *    - Argument 1: Enum value for this sfx
 *    - Argument 2: Importance for deciding which sfx to prioritize. Higher values have greater importance
 *    - Argument 3: Slows the decay of volume with distance (a 3-bit number ranging from 0-7)
 *    - Argument 4: Applies increasingly random offsets to frequency (a 2-bit number ranging from 0-3)
 *    - Argument 5: Various flags to add properties to the sfx
 *    - Argument 6: Various flags to add properties to the sfx
 *
 * WARNING: entries must align with the table defined for the player bank in sequence 0
 */
/* 0x6800 */ DEFINE_SFX(NA_SE_VO_LI_SWORD_N, 0x30, 2, 0, 0, SFX_FLAG_10)
/* 0x6801 */ DEFINE_SFX(NA_SE_VO_LI_SWORD_L, 0x30, 2, 0, 0, SFX_FLAG_10)
/* 0x6802 */ DEFINE_SFX(NA_SE_VO_LI_LASH, 0x30, 2, 0, 0, SFX_FLAG_10)
/* 0x6803 */ DEFINE_SFX(NA_SE_VO_LI_HANG, 0x20, 2, 0, 0, SFX_FLAG_10)
/* 0x6804 */ DEFINE_SFX(NA_SE_VO_LI_CLIMB_END, 0x30, 2, 0, 0, SFX_FLAG_10)
/* 0x6805 */ DEFINE_SFX(NA_SE_VO_LI_DAMAGE_S, 0x30, 2, 0, 0, SFX_FLAG_10)
/* 0x6806 */ DEFINE_SFX(NA_SE_VO_LI_FREEZE, 0x30, 2, 0, 0, SFX_FLAG_10)
/* 0x6807 */ DEFINE_SFX(NA_SE_VO_LI_FALL_S, 0x30, 2, 0, 0, SFX_FLAG_10)
/* 0x6808 */ DEFINE_SFX(NA_SE_VO_LI_FALL_L, 0x30, 2, 0, 0, SFX_FLAG_10)
/* 0x6809 */ DEFINE_SFX(NA_SE_VO_LI_BREATH_REST, 0x30, 2, 1, 0, SFX_FLAG_10)
/* 0x680A */ DEFINE_SFX(NA_SE_VO_LI_BREATH_DRINK, 0x30, 2, 1, 0, SFX_FLAG_10)
/* 0x680B */ DEFINE_SFX(NA_SE_VO_LI_DOWN, 0x30, 2, 0, 0, SFX_FLAG_10)
/* 0x680C */ DEFINE_SFX(NA_SE_VO_LI_TAKEN_AWAY, 0x30, 2, 0, 0, SFX_FLAG_10)
/* 0x680D */ DEFINE_SFX(NA_SE_VO_LI_HELD, 0x50, 2, 0, 0, SFX_FLAG_10)
/* 0x680E */ DEFINE_SFX(NA_SE_VO_LI_SNEEZE, 0x30, 2, 0, 0, SFX_FLAG_10)
/* 0x680F */ DEFINE_SFX(NA_SE_VO_LI_SWEAT, 0x30, 2, 0, 0, SFX_FLAG_10)
/* 0x6810 */ DEFINE_SFX(NA_SE_VO_LI_DRINK, 0x30, 2, 0, 0, SFX_FLAG_10)
/* 0x6811 */ DEFINE_SFX(NA_SE_VO_LI_RELAX, 0x30, 2, 0, 0, SFX_FLAG_10)
/* 0x6812 */ DEFINE_SFX(NA_SE_VO_LI_SWORD_PUTAWAY, 0x30, 2, 0, 0, SFX_FLAG_10)
/* 0x6813 */ DEFINE_SFX(NA_SE_VO_LI_GROAN, 0x30, 2, 0, 0, SFX_FLAG_10)
/* 0x6814 */ DEFINE_SFX(NA_SE_VO_LI_AUTO_JUMP, 0x30, 2, 0, 0, SFX_FLAG_10)
/* 0x6815 */ DEFINE_SFX(NA_SE_VO_LI_MAGIC_NALE, 0x30, 2, 0, 0, SFX_FLAG_10)
/* 0x6816 */ DEFINE_SFX(NA_SE_VO_LI_SURPRISE, 0x30, 2, 0, 0, SFX_FLAG_10)
/* 0x6817 */ DEFINE_SFX(NA_SE_VO_LI_MAGIC_FROL, 0x30, 2, 0, 0, SFX_FLAG_10)
/* 0x6818 */ DEFINE_SFX(NA_SE_VO_LI_PUSH, 0x30, 2, 2, 0, SFX_FLAG_10)
/* 0x6819 */ DEFINE_SFX(NA_SE_VO_LI_HOOKSHOT_HANG, 0x30, 2, 0, 0, SFX_FLAG_10)
/* 0x681A */ DEFINE_SFX(NA_SE_VO_LI_LAND_DAMAGE_S, 0x30, 2, 0, 0, SFX_FLAG_10)
/* 0x681B */ DEFINE_SFX(NA_SE_VO_LI_MAGIC_START, 0x30, 2, 0, 0, SFX_FLAG_10)
/* 0x681C */ DEFINE_SFX(NA_SE_VO_LI_MAGIC_ATTACK, 0x30, 2, 0, 0, SFX_FLAG_10)
/* 0x681D */ DEFINE_SFX(NA_SE_VO_BL_DOWN, 0x80, 2, 0, 0, SFX_FLAG_10)
/* 0x681E */ DEFINE_SFX(NA_SE_VO_LI_DEMO_DAMAGE, 0x30, 2, 0, 0, SFX_FLAG_10)
/* 0x681F */ DEFINE_SFX(NA_SE_VO_LI_SWORD_N_copy30, 0x30, 2, 0, 0, SFX_FLAG_10)
/* 0x6820 */ DEFINE_SFX(NA_SE_VO_DUMMY_32, 0x30, 2, 0, 0, SFX_FLAG_10)
/* 0x6821 */ DEFINE_SFX(NA_SE_VO_DUMMY_33, 0x30, 2, 0, 0, SFX_FLAG_10)
/* 0x6822 */ DEFINE_SFX(NA_SE_VO_DUMMY_34, 0x30, 2, 0, 0, SFX_FLAG_10)
/* 0x6823 */ DEFINE_SFX(NA_SE_VO_DUMMY_35, 0x20, 2, 0, 0, SFX_FLAG_10)
/* 0x6824 */ DEFINE_SFX(NA_SE_VO_DUMMY_36, 0x30, 2, 0, 0, SFX_FLAG_10)
/* 0x6825 */ DEFINE_SFX(NA_SE_VO_DUMMY_37, 0x30, 2, 0, 0, SFX_FLAG_10)
/* 0x6826 */ DEFINE_SFX(NA_SE_VO_DUMMY_38, 0x30, 2, 0, 0, SFX_FLAG_10)
/* 0x6827 */ DEFINE_SFX(NA_SE_VO_DUMMY_39, 0x30, 2, 0, 0, SFX_FLAG_10)
/* 0x6828 */ DEFINE_SFX(NA_SE_VO_NAVY_ENEMY, 0x30, 2, 0, 0, SFX_FLAG_10)
/* 0x6829 */ DEFINE_SFX(NA_SE_VO_NAVY_HELLO, 0x30, 2, 1, 0, SFX_FLAG_10)
/* 0x682A */ DEFINE_SFX(NA_SE_VO_NAVY_HEAR, 0x30, 2, 1, 0, SFX_FLAG_10)
/* 0x682B */ DEFINE_SFX(NA_SE_VO_DUMMY_43, 0x30, 2, 0, 0, SFX_FLAG_10)
/* 0x682C */ DEFINE_SFX(NA_SE_VO_DUMMY_44, 0x30, 2, 0, 0, SFX_FLAG_10)
/* 0x682D */ DEFINE_SFX(NA_SE_VO_DUMMY_45, 0x50, 2, 0, 0, SFX_FLAG_10)
/* 0x682E */ DEFINE_SFX(NA_SE_VO_DUMMY_46, 0x30, 2, 0, 0, SFX_FLAG_10)
/* 0x682F */ DEFINE_SFX(NA_SE_VO_DUMMY_47, 0x30, 2, 0, 0, SFX_FLAG_10)
/* 0x6830 */ DEFINE_SFX(NA_SE_VO_DUMMY_48, 0x30, 2, 0, 0, SFX_FLAG_10)
/* 0x6831 */ DEFINE_SFX(NA_SE_VO_DUMMY_49, 0x30, 2, 0, 0, SFX_FLAG_10)
/* 0x6832 */ DEFINE_SFX(NA_SE_VO_DUMMY_50, 0x30, 2, 0, 0, SFX_FLAG_10)
/* 0x6833 */ DEFINE_SFX(NA_SE_VO_DUMMY_51, 0x30, 2, 0, 0, SFX_FLAG_10)
/* 0x6834 */ DEFINE_SFX(NA_SE_VO_DUMMY_52, 0x30, 2, 0, 0, SFX_FLAG_10)
/* 0x6835 */ DEFINE_SFX(NA_SE_VO_DUMMY_53, 0x30, 2, 0, 0, SFX_FLAG_10)
/* 0x6836 */ DEFINE_SFX(NA_SE_VO_DUMMY_54, 0x30, 2, 0, 0, SFX_FLAG_10)
/* 0x6837 */ DEFINE_SFX(NA_SE_VO_DUMMY_55, 0x30, 2, 0, 0, SFX_FLAG_10)
/* 0x6838 */ DEFINE_SFX(NA_SE_VO_DUMMY_56, 0x30, 1, 2, 0, SFX_FLAG_10)
/* 0x6839 */ DEFINE_SFX(NA_SE_VO_DUMMY_57, 0x30, 2, 0, 0, SFX_FLAG_10)
/* 0x683A */ DEFINE_SFX(NA_SE_VO_DUMMY_58, 0x30, 2, 0, 0, SFX_FLAG_10)
/* 0x683B */ DEFINE_SFX(NA_SE_VO_DUMMY_59, 0x30, 2, 0, 0, SFX_FLAG_10)
/* 0x683C */ DEFINE_SFX(NA_SE_VO_DUMMY_60, 0x30, 2, 0, 0, SFX_FLAG_10)
/* 0x683D */ DEFINE_SFX(NA_SE_VO_DUMMY_61, 0x30, 2, 0, 0, SFX_FLAG_10)
/* 0x683E */ DEFINE_SFX(NA_SE_VO_DUMMY_62, 0x30, 2, 0, 0, SFX_FLAG_10)
/* 0x683F */ DEFINE_SFX(NA_SE_VO_DUMMY_63, 0x30, 2, 0, 0, SFX_FLAG_10)
/* 0x6840 */ DEFINE_SFX(NA_SE_VO_LK_WAKE_UP, 0x30, 2, 0, 0, SFX_FLAG_10)
/* 0x6841 */ DEFINE_SFX(NA_SE_VO_LK_CATCH_DEMO, 0x30, 2, 0, 0, SFX_FLAG_10)
/* 0x6842 */ DEFINE_SFX(NA_SE_VO_LK_DRAGGED_DAMAGE, 0x30, 0, 0, 0, 0)
/* 0x6843 */ DEFINE_SFX(NA_SE_VO_NAVY_CALL, 0x60, 0, 0, 0, SFX_FLAG_5)
/* 0x6844 */ DEFINE_SFX(NA_SE_VO_NA_HELLO_3, 0x30, 0, 0, 0, 0)
/* 0x6845 */ DEFINE_SFX(NA_SE_VO_CHAT_MESSAGE_CALL, 0x30, 0, 0, 0, 0)
/* 0x6846 */ DEFINE_SFX(NA_SE_VO_BELL_MESSAGE, 0x30, 0, 0, 0, 0)
/* 0x6847 */ DEFINE_SFX(NA_SE_VO_MONDO_MESSAGE, 0x30, 0, 0, 0, 0)
/* 0x6848 */ DEFINE_SFX(NA_SE_VO_LK_USING_UP_ENERGY, 0x30, 0, 0, 0, 0)
/* 0x6849 */ DEFINE_SFX(NA_SE_VO_DUMMY_73, 0x30, 0, 0, 0, 0)
/* 0x684A */ DEFINE_SFX(NA_SE_VO_GO_SLEEP, 0x30, 0, 0, 0, 0)
/* 0x684B */ DEFINE_SFX(NA_SE_VO_NP_SLEEP_OUT, 0x30, 0, 0, 0, 0)
/* 0x684C */ DEFINE_SFX(NA_SE_VO_DUMMY_76, 0x30, 0, 0, 0, 0)
/* 0x684D */ DEFINE_SFX(NA_SE_VO_DUMMY_77, 0x30, 0, 0, 0, 0)
/* 0x684E */ DEFINE_SFX(NA_SE_VO_NP_DRINK, 0x30, 0, 0, 0, 0)
/* 0x684F */ DEFINE_SFX(NA_SE_VO_DUMMY_79, 0x30, 0, 0, 0, 0)
/* 0x6850 */ DEFINE_SFX(NA_SE_VO_NARRATION_0, 0x30, 0, 0, 0, 0)
/* 0x6851 */ DEFINE_SFX(NA_SE_VO_TA_SURPRISE, 0x30, 0, 0, 0, 0)
/* 0x6852 */ DEFINE_SFX(NA_SE_VO_TA_CRY_0, 0x30, 1, 1, 0, SFX_FLAG_15)
/* 0x6853 */ DEFINE_SFX(NA_SE_VO_TA_CRY_1, 0x30, 1, 1, 0, SFX_FLAG_15)
/* 0x6854 */ DEFINE_SFX(NA_SE_VO_IN_CRY_0, 0x30, 1, 1, 0, SFX_FLAG_15)
/* 0x6855 */ DEFINE_SFX(NA_SE_VO_IN_LOST, 0x30, 1, 1, 0, SFX_FLAG_15)
/* 0x6856 */ DEFINE_SFX(NA_SE_VO_IN_LASH_0, 0x30, 1, 1, 0, SFX_FLAG_15)
/* 0x6857 */ DEFINE_SFX(NA_SE_VO_IN_LASH_1, 0x30, 1, 1, 0, SFX_FLAG_15)
/* 0x6858 */ DEFINE_SFX(NA_SE_VO_FR_LAUGH_0, 0x30, 1, 1, 0, SFX_FLAG_15)
/* 0x6859 */ DEFINE_SFX(NA_SE_VO_FR_SMILE_0, 0x30, 1, 1, 0, SFX_FLAG_15)
/* 0x685A */ DEFINE_SFX(NA_SE_VO_NB_AGONY, 0x30, 1, 1, 0, SFX_FLAG_15)
/* 0x685B */ DEFINE_SFX(NA_SE_VO_NB_CRY_0, 0x30, 1, 1, 0, SFX_FLAG_15)
/* 0x685C */ DEFINE_SFX(NA_SE_VO_NB_NOTICE, 0x30, 1, 1, 0, SFX_FLAG_15)
/* 0x685D */ DEFINE_SFX(NA_SE_VO_NA_HELLO_0, 0x30, 0, 0, 0, SFX_FLAG_15)
/* 0x685E */ DEFINE_SFX(NA_SE_VO_NA_HELLO_1, 0x30, 0, 0, 0, SFX_FLAG_15)
/* 0x685F */ DEFINE_SFX(NA_SE_VO_NA_HELLO_2, 0x30, 0, 0, 0, SFX_FLAG_15)
/* 0x6860 */ DEFINE_SFX(NA_SE_VO_RT_CRASH, 0x30, 1, 1, 0, SFX_FLAG_15)
/* 0x6861 */ DEFINE_SFX(NA_SE_VO_RT_DISCOVER, 0x30, 1, 1, 0, SFX_FLAG_15)
/* 0x6862 */ DEFINE_SFX(NA_SE_VO_RT_FALL, 0x30, 1, 1, 0, SFX_FLAG_15)
/* 0x6863 */ DEFINE_SFX(NA_SE_VO_RT_LAUGH_0, 0x30, 1, 1, 0, SFX_FLAG_15)
/* 0x6864 */ DEFINE_SFX(NA_SE_VO_RT_LIFT, 0x30, 1, 1, 0, SFX_FLAG_15)
/* 0x6865 */ DEFINE_SFX(NA_SE_VO_RT_THROW, 0x30, 1, 1, 0, SFX_FLAG_15)
/* 0x6866 */ DEFINE_SFX(NA_SE_VO_RT_UNBALLANCE, 0x30, 1, 1, 0, SFX_FLAG_15)
/* 0x6867 */ DEFINE_SFX(NA_SE_VO_ST_DAMAGE, 0x30, 1, 1, 0, SFX_FLAG_15)
/* 0x6868 */ DEFINE_SFX(NA_SE_VO_ST_ATTACK, 0x30, 1, 1, 0, SFX_FLAG_15)
/* 0x6869 */ DEFINE_SFX(NA_SE_VO_Z0_HURRY, 0x30, 1, 1, 0, SFX_FLAG_15)
/* 0x686A */ DEFINE_SFX(NA_SE_VO_Z0_MEET, 0x30, 1, 1, 0, SFX_FLAG_15)
/* 0x686B */ DEFINE_SFX(NA_SE_VO_Z0_QUESTION, 0x30, 1, 1, 0, SFX_FLAG_15)
/* 0x686C */ DEFINE_SFX(NA_SE_VO_Z0_SIGH_0, 0x30, 1, 1, 0, SFX_FLAG_15)
/* 0x686D */ DEFINE_SFX(NA_SE_VO_Z0_SMILE_0, 0x30, 1, 1, 0, SFX_FLAG_15)
/* 0x686E */ DEFINE_SFX(NA_SE_VO_Z0_SURPRISE, 0x30, 1, 1, 0, SFX_FLAG_15)
/* 0x686F */ DEFINE_SFX(NA_SE_VO_Z0_THROW, 0x30, 1, 1, 0, SFX_FLAG_15)
/* 0x6870 */ DEFINE_SFX(NA_SE_VO_SK_CRY_0, 0x30, 1, 1, 0, SFX_FLAG_15)
/* 0x6871 */ DEFINE_SFX(NA_SE_VO_SK_CRY_1, 0x30, 1, 1, 0, SFX_FLAG_15)
/* 0x6872 */ DEFINE_SFX(NA_SE_VO_SK_CRASH, 0x30, 1, 1, 0, SFX_FLAG_15)
/* 0x6873 */ DEFINE_SFX(NA_SE_VO_NA_LISTEN, 0x30, 1, 1, 0, SFX_FLAG_15)
/* 0x6874 */ DEFINE_SFX(NA_SE_VO_SK_SHOUT, 0x30, 1, 0, 0, SFX_FLAG_15)
/* 0x6875 */ DEFINE_SFX(NA_SE_VO_Z1_CRY_0, 0x30, 3, 1, 0, SFX_FLAG_15)
/* 0x6876 */ DEFINE_SFX(NA_SE_VO_Z1_CRY_1, 0x30, 3, 1, 0, SFX_FLAG_15)
/* 0x6877 */ DEFINE_SFX(NA_SE_VO_Z1_OPENDOOR, 0x30, 3, 1, 0, SFX_FLAG_15)
/* 0x6878 */ DEFINE_SFX(NA_SE_VO_FR_SMILE_1, 0x30, 1, 1, 0, SFX_FLAG_15)
/* 0x6879 */ DEFINE_SFX(NA_SE_VO_FR_SMILE_2, 0x30, 1, 1, 0, SFX_FLAG_15)
/* 0x687A */ DEFINE_SFX(NA_SE_VO_KZ_MOVE, 0x30, 1, 1, 0, SFX_FLAG_15)
/* 0x687B */ DEFINE_SFX(NA_SE_VO_NB_LAUGH, 0x30, 1, 1, 0, SFX_FLAG_15)
/* 0x687C */ DEFINE_SFX(NA_SE_VO_IN_JOY0, 0x30, 1, 1, 0, SFX_FLAG_15)
/* 0x687D */ DEFINE_SFX(NA_SE_VO_IN_JOY1, 0x30, 1, 1, 0, SFX_FLAG_15)
/* 0x687E */ DEFINE_SFX(NA_SE_VO_IN_JOY2, 0x30, 1, 1, 0, SFX_FLAG_15)
/* 0x687F */ DEFINE_SFX(NA_SE_VO_DUMMY_127, 0x30, 1, 1, 0, SFX_FLAG_15)
/* 0x6880 */ DEFINE_SFX(NA_SE_VO_DUMMY_128, 0x30, 2, 0, 0, SFX_FLAG_10)
/* 0x6881 */ DEFINE_SFX(NA_SE_VO_DUMMY_129, 0x30, 2, 0, 0, SFX_FLAG_10)
/* 0x6882 */ DEFINE_SFX(NA_SE_VO_DUMMY_130, 0x30, 2, 0, 0, SFX_FLAG_10)
/* 0x6883 */ DEFINE_SFX(NA_SE_VO_DUMMY_131, 0x20, 2, 0, 0, SFX_FLAG_10)
/* 0x6884 */ DEFINE_SFX(NA_SE_VO_DUMMY_132, 0x30, 2, 0, 0, SFX_FLAG_10)
/* 0x6885 */ DEFINE_SFX(NA_SE_VO_DUMMY_133, 0x30, 2, 0, 0, SFX_FLAG_10)
/* 0x6886 */ DEFINE_SFX(NA_SE_VO_DUMMY_134, 0x30, 2, 0, 0, SFX_FLAG_10)
/* 0x6887 */ DEFINE_SFX(NA_SE_VO_DUMMY_135, 0x30, 2, 0, 0, SFX_FLAG_10)
/* 0x6888 */ DEFINE_SFX(NA_SE_VO_DUMMY_136, 0x30, 2, 0, 0, SFX_FLAG_10)
/* 0x6889 */ DEFINE_SFX(NA_SE_VO_DUMMY_137, 0x30, 2, 1, 0, SFX_FLAG_10)
/* 0x688A */ DEFINE_SFX(NA_SE_VO_DUMMY_138, 0x30, 2, 1, 0, SFX_FLAG_10)
/* 0x688B */ DEFINE_SFX(NA_SE_VO_DUMMY_139, 0x30, 2, 0, 0, SFX_FLAG_10)
/* 0x688C */ DEFINE_SFX(NA_SE_VO_DUMMY_140, 0x30, 2, 0, 0, SFX_FLAG_10)
/* 0x688D */ DEFINE_SFX(NA_SE_VO_DUMMY_141, 0x50, 2, 0, 0, SFX_FLAG_10)
/* 0x688E */ DEFINE_SFX(NA_SE_VO_DUMMY_142, 0x30, 2, 0, 0, SFX_FLAG_10)
/* 0x688F */ DEFINE_SFX(NA_SE_VO_DUMMY_143, 0x30, 2, 0, 0, SFX_FLAG_10)
/* 0x6890 */ DEFINE_SFX(NA_SE_VO_DUMMY_144, 0x30, 2, 0, 0, SFX_FLAG_10)
/* 0x6891 */ DEFINE_SFX(NA_SE_VO_DUMMY_145, 0x30, 2, 0, 0, SFX_FLAG_10)
/* 0x6892 */ DEFINE_SFX(NA_SE_VO_DUMMY_146, 0x30, 2, 0, 0, SFX_FLAG_10)
/* 0x6893 */ DEFINE_SFX(NA_SE_VO_DUMMY_147, 0x30, 2, 0, 0, SFX_FLAG_10)
/* 0x6894 */ DEFINE_SFX(NA_SE_VO_DUMMY_148, 0x30, 2, 0, 0, SFX_FLAG_10)
/* 0x6895 */ DEFINE_SFX(NA_SE_VO_DUMMY_149, 0x30, 2, 0, 0, SFX_FLAG_10)
/* 0x6896 */ DEFINE_SFX(NA_SE_VO_DUMMY_150, 0x30, 2, 0, 0, SFX_FLAG_10)
/* 0x6897 */ DEFINE_SFX(NA_SE_VO_DUMMY_151, 0x30, 2, 0, 0, SFX_FLAG_10)
/* 0x6898 */ DEFINE_SFX(NA_SE_VO_DUMMY_152, 0x30, 1, 2, 0, SFX_FLAG_10)
/* 0x6899 */ DEFINE_SFX(NA_SE_VO_DUMMY_153, 0x30, 2, 0, 0, SFX_FLAG_10)
/* 0x689A */ DEFINE_SFX(NA_SE_VO_DUMMY_154, 0x30, 2, 0, 0, SFX_FLAG_10)
/* 0x689B */ DEFINE_SFX(NA_SE_VO_DUMMY_155, 0x30, 2, 0, 0, SFX_FLAG_10)
/* 0x689C */ DEFINE_SFX(NA_SE_VO_DUMMY_156, 0x30, 2, 0, 0, SFX_FLAG_10)
/* 0x689D */ DEFINE_SFX(NA_SE_VO_DUMMY_157, 0x30, 2, 0, 0, SFX_FLAG_10)
/* 0x689E */ DEFINE_SFX(NA_SE_VO_DUMMY_158, 0x30, 2, 0, 0, SFX_FLAG_10)
/* 0x689F */ DEFINE_SFX(NA_SE_VO_DUMMY_159, 0x30, 2, 0, 0, SFX_FLAG_10)
/* 0x68A0 */ DEFINE_SFX(NA_SE_VO_DUMMY_160, 0x30, 2, 0, 0, SFX_FLAG_10)
/* 0x68A1 */ DEFINE_SFX(NA_SE_VO_DUMMY_161, 0x30, 2, 0, 0, SFX_FLAG_10)
/* 0x68A2 */ DEFINE_SFX(NA_SE_VO_DUMMY_162, 0x30, 2, 0, 0, SFX_FLAG_10)
/* 0x68A3 */ DEFINE_SFX(NA_SE_VO_DUMMY_163, 0x20, 2, 0, 0, SFX_FLAG_10)
/* 0x68A4 */ DEFINE_SFX(NA_SE_VO_DUMMY_164, 0x30, 2, 0, 0, SFX_FLAG_10)
/* 0x68A5 */ DEFINE_SFX(NA_SE_VO_DUMMY_165, 0x30, 2, 0, 0, SFX_FLAG_10)
/* 0x68A6 */ DEFINE_SFX(NA_SE_VO_DUMMY_166, 0x30, 2, 0, 0, SFX_FLAG_10)
/* 0x68A7 */ DEFINE_SFX(NA_SE_VO_DUMMY_167, 0x30, 2, 0, 0, SFX_FLAG_10)
/* 0x68A8 */ DEFINE_SFX(NA_SE_VO_DUMMY_168, 0x30, 2, 0, 0, SFX_FLAG_10)
/* 0x68A9 */ DEFINE_SFX(NA_SE_VO_DUMMY_169, 0x30, 2, 1, 0, SFX_FLAG_10)
/* 0x68AA */ DEFINE_SFX(NA_SE_VO_DUMMY_170, 0x30, 2, 1, 0, SFX_FLAG_10)
/* 0x68AB */ DEFINE_SFX(NA_SE_VO_DUMMY_171, 0x30, 2, 0, 0, SFX_FLAG_10)
/* 0x68AC */ DEFINE_SFX(NA_SE_VO_DUMMY_172, 0x30, 2, 0, 0, SFX_FLAG_10)
/* 0x68AD */ DEFINE_SFX(NA_SE_VO_DUMMY_173, 0x50, 2, 0, 0, SFX_FLAG_10)
/* 0x68AE */ DEFINE_SFX(NA_SE_VO_DUMMY_174, 0x30, 2, 0, 0, SFX_FLAG_10)
/* 0x68AF */ DEFINE_SFX(NA_SE_VO_DUMMY_175, 0x30, 2, 0, 0, SFX_FLAG_10)
/* 0x68B0 */ DEFINE_SFX(NA_SE_VO_DUMMY_176, 0x30, 2, 0, 0, SFX_FLAG_10)
/* 0x68B1 */ DEFINE_SFX(NA_SE_VO_DUMMY_177, 0x30, 2, 0, 0, SFX_FLAG_10)
/* 0x68B2 */ DEFINE_SFX(NA_SE_VO_DUMMY_178, 0x30, 2, 0, 0, SFX_FLAG_10)
/* 0x68B3 */ DEFINE_SFX(NA_SE_VO_DUMMY_179, 0x30, 2, 0, 0, SFX_FLAG_10)
/* 0x68B4 */ DEFINE_SFX(NA_SE_VO_DUMMY_180, 0x30, 2, 0, 0, SFX_FLAG_10)
/* 0x68B5 */ DEFINE_SFX(NA_SE_VO_DUMMY_181, 0x30, 2, 0, 0, SFX_FLAG_10)
/* 0x68B6 */ DEFINE_SFX(NA_SE_VO_DUMMY_182, 0x30, 2, 0, 0, SFX_FLAG_10)
/* 0x68B7 */ DEFINE_SFX(NA_SE_VO_DUMMY_183, 0x30, 2, 0, 0, SFX_FLAG_10)
/* 0x68B8 */ DEFINE_SFX(NA_SE_VO_DUMMY_184, 0x30, 2, 2, 0, SFX_FLAG_10)
/* 0x68B9 */ DEFINE_SFX(NA_SE_VO_DUMMY_185, 0x30, 2, 0, 0, SFX_FLAG_10)
/* 0x68BA */ DEFINE_SFX(NA_SE_VO_DUMMY_186, 0x30, 2, 0, 0, SFX_FLAG_10)
/* 0x68BB */ DEFINE_SFX(NA_SE_VO_DUMMY_187, 0x30, 2, 0, 0, SFX_FLAG_10)
/* 0x68BC */ DEFINE_SFX(NA_SE_VO_DUMMY_188, 0x30, 2, 0, 0, SFX_FLAG_10)
/* 0x68BD */ DEFINE_SFX(NA_SE_VO_DUMMY_189, 0x80, 2, 0, 0, SFX_FLAG_10)
/* 0x68BE */ DEFINE_SFX(NA_SE_VO_DUMMY_190, 0x30, 2, 0, 0, SFX_FLAG_10)
/* 0x68BF */ DEFINE_SFX(NA_SE_VO_DUMMY_191, 0x30, 2, 0, 0, SFX_FLAG_10)
/* 0x68C0 */ DEFINE_SFX(NA_SE_VO_DUMMY_192, 0x30, 2, 0, 0, SFX_FLAG_10)
/* 0x68C1 */ DEFINE_SFX(NA_SE_VO_DUMMY_193, 0x30, 2, 0, 0, SFX_FLAG_10)
/* 0x68C2 */ DEFINE_SFX(NA_SE_VO_DUMMY_194, 0x30, 2, 0, 0, SFX_FLAG_10)
/* 0x68C3 */ DEFINE_SFX(NA_SE_VO_DUMMY_195, 0x20, 2, 0, 0, SFX_FLAG_10)
/* 0x68C4 */ DEFINE_SFX(NA_SE_VO_DUMMY_196, 0x30, 2, 0, 0, SFX_FLAG_10)
/* 0x68C5 */ DEFINE_SFX(NA_SE_VO_DUMMY_197, 0x30, 2, 0, 0, SFX_FLAG_10)
/* 0x68C6 */ DEFINE_SFX(NA_SE_VO_DUMMY_198, 0x30, 2, 0, 0, SFX_FLAG_10)
/* 0x68C7 */ DEFINE_SFX(NA_SE_VO_DUMMY_199, 0x30, 2, 0, 0, SFX_FLAG_10)
/* 0x68C8 */ DEFINE_SFX(NA_SE_VO_DUMMY_200, 0x30, 2, 0, 0, SFX_FLAG_10)
/* 0x68C9 */ DEFINE_SFX(NA_SE_VO_DUMMY_201, 0x30, 2, 1, 0, SFX_FLAG_10)
/* 0x68CA */ DEFINE_SFX(NA_SE_VO_DUMMY_202, 0x30, 2, 1, 0, SFX_FLAG_10)
/* 0x68CB */ DEFINE_SFX(NA_SE_VO_DUMMY_203, 0x30, 2, 0, 0, SFX_FLAG_10)
/* 0x68CC */ DEFINE_SFX(NA_SE_VO_DUMMY_204, 0x30, 2, 0, 0, SFX_FLAG_10)
/* 0x68CD */ DEFINE_SFX(NA_SE_VO_DUMMY_205, 0x50, 2, 0, 0, SFX_FLAG_10)
/* 0x68CE */ DEFINE_SFX(NA_SE_VO_DUMMY_206, 0x30, 2, 0, 0, SFX_FLAG_10)
/* 0x68CF */ DEFINE_SFX(NA_SE_VO_DUMMY_207, 0x30, 2, 0, 0, SFX_FLAG_10)
/* 0x68D0 */ DEFINE_SFX(NA_SE_VO_DUMMY_208, 0x30, 2, 0, 0, SFX_FLAG_10)
/* 0x68D1 */ DEFINE_SFX(NA_SE_VO_DUMMY_209, 0x30, 2, 0, 0, SFX_FLAG_10)
/* 0x68D2 */ DEFINE_SFX(NA_SE_VO_DUMMY_210, 0x30, 2, 0, 0, SFX_FLAG_10)
/* 0x68D3 */ DEFINE_SFX(NA_SE_VO_DUMMY_211, 0x30, 2, 0, 0, SFX_FLAG_10)
/* 0x68D4 */ DEFINE_SFX(NA_SE_VO_DUMMY_212, 0x30, 2, 0, 0, SFX_FLAG_10)
/* 0x68D5 */ DEFINE_SFX(NA_SE_VO_DUMMY_213, 0x30, 2, 0, 0, SFX_FLAG_10)
/* 0x68D6 */ DEFINE_SFX(NA_SE_VO_DUMMY_214, 0x30, 2, 0, 0, SFX_FLAG_10)
/* 0x68D7 */ DEFINE_SFX(NA_SE_VO_DUMMY_215, 0x30, 2, 0, 0, SFX_FLAG_10)
/* 0x68D8 */ DEFINE_SFX(NA_SE_VO_DUMMY_216, 0x30, 2, 2, 0, SFX_FLAG_10)
/* 0x68D9 */ DEFINE_SFX(NA_SE_VO_DUMMY_217, 0x30, 2, 0, 0, SFX_FLAG_10)
/* 0x68DA */ DEFINE_SFX(NA_SE_VO_DUMMY_218, 0x30, 2, 0, 0, SFX_FLAG_10)
/* 0x68DB */ DEFINE_SFX(NA_SE_VO_DUMMY_219, 0x30, 2, 0, 0, SFX_FLAG_10)
/* 0x68DC */ DEFINE_SFX(NA_SE_VO_DUMMY_220, 0x30, 2, 0, 0, SFX_FLAG_10)
/* 0x68DD */ DEFINE_SFX(NA_SE_VO_DUMMY_221, 0x80, 2, 0, 0, SFX_FLAG_10)
/* 0x68DE */ DEFINE_SFX(NA_SE_VO_DUMMY_222, 0x30, 2, 0, 0, SFX_FLAG_10)
/* 0x68DF */ DEFINE_SFX(NA_SE_VO_DUMMY_223, 0x30, 2, 0, 0, SFX_FLAG_10)
/* 0x68E0 */ DEFINE_SFX(NA_SE_VO_LI_POO_WAIT, 0x30, 2, 1, 0, SFX_FLAG_10)
/* 0x68E1 */ DEFINE_SFX(NA_SE_VO_DUMMY_225, 0x30, 2, 1, 0, SFX_FLAG_10)
/* 0x68E2 */ DEFINE_SFX(NA_SE_VO_DUMMY_226, 0x30, 2, 1, 0, SFX_FLAG_10)
/* 0x68E3 */ DEFINE_SFX(NA_SE_VO_DUMMY_227, 0x20, 2, 1, 0, SFX_FLAG_10)
/* 0x68E4 */ DEFINE_SFX(NA_SE_VO_DUMMY_228, 0x30, 2, 1, 0, SFX_FLAG_10)
/* 0x68E5 */ DEFINE_SFX(NA_SE_VO_DUMMY_229, 0x30, 2, 1, 0, SFX_FLAG_10)
/* 0x68E6 */ DEFINE_SFX(NA_SE_VO_DUMMY_230, 0x30, 2, 1, 0, SFX_FLAG_10)
/* 0x68E7 */ DEFINE_SFX(NA_SE_VO_DUMMY_231, 0x30, 2, 1, 0, SFX_FLAG_10)
/* 0x68E8 */ DEFINE_SFX(NA_SE_VO_DUMMY_232, 0x30, 2, 1, 0, SFX_FLAG_10)
/* 0x68E9 */ DEFINE_SFX(NA_SE_VO_DUMMY_233, 0x30, 2, 1, 0, SFX_FLAG_10)
/* 0x68EA */ DEFINE_SFX(NA_SE_VO_DUMMY_234, 0x30, 2, 1, 0, SFX_FLAG_10)
/* 0x68EB */ DEFINE_SFX(NA_SE_VO_DUMMY_235, 0x30, 2, 1, 0, SFX_FLAG_10)
/* 0x68EC */ DEFINE_SFX(NA_SE_VO_DUMMY_236, 0x30, 2, 1, 0, SFX_FLAG_10)
/* 0x68ED */ DEFINE_SFX(NA_SE_VO_DUMMY_237, 0x50, 2, 1, 0, SFX_FLAG_10)
/* 0x68EE */ DEFINE_SFX(NA_SE_VO_DUMMY_238, 0x30, 2, 1, 0, SFX_FLAG_10)
/* 0x68EF */ DEFINE_SFX(NA_SE_VO_DUMMY_239, 0x30, 2, 1, 0, SFX_FLAG_10)
/* 0x68F0 */ DEFINE_SFX(NA_SE_VO_DUMMY_240, 0x30, 2, 1, 0, SFX_FLAG_10)
/* 0x68F1 */ DEFINE_SFX(NA_SE_VO_DUMMY_241, 0x30, 2, 1, 0, SFX_FLAG_10)
/* 0x68F2 */ DEFINE_SFX(NA_SE_VO_DUMMY_242, 0x30, 2, 1, 0, SFX_FLAG_10)
/* 0x68F3 */ DEFINE_SFX(NA_SE_VO_DUMMY_243, 0x30, 2, 1, 0, SFX_FLAG_10)
/* 0x68F4 */ DEFINE_SFX(NA_SE_VO_DUMMY_244, 0x30, 2, 1, 0, SFX_FLAG_10)
/* 0x68F5 */ DEFINE_SFX(NA_SE_VO_DUMMY_245, 0x30, 2, 1, 0, SFX_FLAG_10)
/* 0x68F6 */ DEFINE_SFX(NA_SE_VO_DUMMY_246, 0x30, 2, 1, 0, SFX_FLAG_10)
/* 0x68F7 */ DEFINE_SFX(NA_SE_VO_DUMMY_247, 0x30, 2, 1, 0, SFX_FLAG_10)
/* 0x68F8 */ DEFINE_SFX(NA_SE_VO_DUMMY_248, 0x30, 2, 2, 0, SFX_FLAG_10)
/* 0x68F9 */ DEFINE_SFX(NA_SE_VO_DUMMY_249, 0x30, 2, 1, 0, SFX_FLAG_10)
/* 0x68FA */ DEFINE_SFX(NA_SE_VO_DUMMY_250, 0x30, 2, 1, 0, SFX_FLAG_10)
/* 0x68FB */ DEFINE_SFX(NA_SE_VO_DUMMY_251, 0x30, 2, 1, 0, SFX_FLAG_10)
/* 0x68FC */ DEFINE_SFX(NA_SE_VO_DUMMY_252, 0x30, 2, 1, 0, SFX_FLAG_10)
/* 0x68FD */ DEFINE_SFX(NA_SE_VO_DUMMY_253, 0x80, 2, 1, 0, SFX_FLAG_10)
/* 0x68FE */ DEFINE_SFX(NA_SE_VO_DUMMY_254, 0x30, 2, 1, 0, SFX_FLAG_10)
/* 0x68FF */ DEFINE_SFX(NA_SE_VO_DUMMY_255, 0x30, 2, 1, SFX_FLAG2_7, SFX_FLAG_10)
/* 0x6900 */ DEFINE_SFX(NA_SE_VO_JMVO02, 0x30, 2, 0, 0, SFX_FLAG_10)
/* 0x6901 */ DEFINE_SFX(NA_SE_VO_JMVO04, 0x30, 2, 0, 0, SFX_FLAG_10)
/* 0x6902 */ DEFINE_SFX(NA_SE_VO_CDVO00, 0x30, 2, 0, 0, SFX_FLAG_10)
/* 0x6903 */ DEFINE_SFX(NA_SE_VO_CDVO01, 0x30, 2, 0, 0, SFX_FLAG_10)
/* 0x6904 */ DEFINE_SFX(NA_SE_VO_CDVO02, 0x30, 2, 0, 0, SFX_FLAG_10)
/* 0x6905 */ DEFINE_SFX(NA_SE_VO_CDVO03, 0x30, 2, 0, 0, SFX_FLAG_10)
/* 0x6906 */ DEFINE_SFX(NA_SE_VO_BBVO00, 0x30, 2, 0, 0, SFX_FLAG_10)
/* 0x6907 */ DEFINE_SFX(NA_SE_VO_BBVO01, 0x30, 2, 0, 0, SFX_FLAG_10)
/* 0x6908 */ DEFINE_SFX(NA_SE_VO_BBVO02, 0x30, 2, 0, 0, SFX_FLAG_10)
/* 0x6909 */ DEFINE_SFX(NA_SE_VO_BBVO03, 0x30, 2, 0, 0, SFX_FLAG_10)
/* 0x690A */ DEFINE_SFX(NA_SE_VO_BBVO04, 0x30, 2, 0, 0, SFX_FLAG_10)
/* 0x690B */ DEFINE_SFX(NA_SE_VO_BBVO05, 0x30, 2, 0, 0, SFX_FLAG_10)
/* 0x690C */ DEFINE_SFX(NA_SE_VO_OBVO01, 0x30, 2, 0, 0, SFX_FLAG_10)
/* 0x690D */ DEFINE_SFX(NA_SE_VO_ARVO00, 0x30, 2, 0, 0, SFX_FLAG_10)
/* 0x690E */ DEFINE_SFX(NA_SE_VO_ARVO01, 0x30, 2, 0, 0, SFX_FLAG_10)
/* 0x690F */ DEFINE_SFX(NA_SE_VO_MMVO00, 0x30, 2, 0, 0, SFX_FLAG_10)
/* 0x6910 */ DEFINE_SFX(NA_SE_VO_MMVO01, 0x30, 2, 0, 0, SFX_FLAG_10)
/* 0x6911 */ DEFINE_SFX(NA_SE_VO_MMVO02, 0x30, 2, 0, 0, SFX_FLAG_10)
/* 0x6912 */ DEFINE_SFX(NA_SE_VO_MMVO03, 0x30, 2, 0, 0, SFX_FLAG_10)
/* 0x6913 */ DEFINE_SFX(NA_SE_VO_MMVO04, 0x30, 2, 0, 0, SFX_FLAG_10)
/* 0x6914 */ DEFINE_SFX(NA_SE_VO_MMVO05, 0x30, 2, 0, 0, SFX_FLAG_10)
/* 0x6915 */ DEFINE_SFX(NA_SE_VO_ABVO00, 0x30, 2, 0, 0, SFX_FLAG_10)
/* 0x6916 */ DEFINE_SFX(NA_SE_VO_ABVO01, 0x30, 2, 0, 0, SFX_FLAG_10)
/* 0x6917 */ DEFINE_SFX(NA_SE_VO_NPVO00, 0x30, 2, 0, 0, SFX_FLAG_10)
/* 0x6918 */ DEFINE_SFX(NA_SE_VO_FPVO00, 0x30, 2, 0, 0, SFX_FLAG_10)
/* 0x6919 */ DEFINE_SFX(NA_SE_VO_FPVO01, 0x30, 2, 0, 0, SFX_FLAG_10)
/* 0x691A */ DEFINE_SFX(NA_SE_VO_FPVO02, 0x30, 2, 0, 0, SFX_FLAG_10)
/* 0x691B */ DEFINE_SFX(NA_SE_VO_FPVO03, 0x30, 2, 0, 0, SFX_FLAG_10)
/* 0x691C */ DEFINE_SFX(NA_SE_VO_ROVO01, 0x30, 2, 0, 0, SFX_FLAG_10)
/* 0x691D */ DEFINE_SFX(NA_SE_VO_ROVO02, 0x30, 2, 0, 0, SFX_FLAG_10)
/* 0x691E */ DEFINE_SFX(NA_SE_VO_RYVO01, 0x30, 2, 0, 0, SFX_FLAG_10)
/* 0x691F */ DEFINE_SFX(NA_SE_VO_RYVO02, 0x30, 2, 0, 0, SFX_FLAG_10)
/* 0x6920 */ DEFINE_SFX(NA_SE_VO_RYVO03, 0x30, 2, 0, 0, SFX_FLAG_10)
/* 0x6921 */ DEFINE_SFX(NA_SE_VO_RYVO04, 0x30, 2, 0, 0, SFX_FLAG_10)
/* 0x6922 */ DEFINE_SFX(NA_SE_VO_ANVO00, 0x30, 2, 0, 0, SFX_FLAG_10)
/* 0x6923 */ DEFINE_SFX(NA_SE_VO_ANVO01, 0x30, 2, 0, 0, SFX_FLAG_10)
/* 0x6924 */ DEFINE_SFX(NA_SE_VO_ANVO02, 0x30, 2, 0, 0, SFX_FLAG_10)
/* 0x6925 */ DEFINE_SFX(NA_SE_VO_ANVO03, 0x30, 2, 0, 0, SFX_FLAG_10)
/* 0x6926 */ DEFINE_SFX(NA_SE_VO_CRVO00, 0x30, 2, 0, 0, SFX_FLAG_10)
/* 0x6927 */ DEFINE_SFX(NA_SE_VO_CRVO01, 0x30, 2, 0, 0, SFX_FLAG_10)
/* 0x6928 */ DEFINE_SFX(NA_SE_VO_CRVO02, 0x30, 2, 0, 0, SFX_FLAG_10)
/* 0x6929 */ DEFINE_SFX(NA_SE_VO_CRVO03, 0x30, 2, 0, 0, SFX_FLAG_10)
/* 0x692A */ DEFINE_SFX(NA_SE_VO_HNVO00, 0x30, 2, 0, 0, SFX_FLAG_10)
/* 0x692B */ DEFINE_SFX(NA_SE_VO_HNVO01, 0x30, 2, 0, 0, SFX_FLAG_10)
/* 0x692C */ DEFINE_SFX(NA_SE_VO_HNVO02, 0x30, 2, 0, 0, SFX_FLAG_10)
/* 0x692D */ DEFINE_SFX(NA_SE_VO_RMVO00, 0x30, 2, 0, 0, SFX_FLAG_10)
/* 0x692E */ DEFINE_SFX(NA_SE_VO_RMVO01, 0x30, 2, 0, 0, SFX_FLAG_10)
/* 0x692F */ DEFINE_SFX(NA_SE_VO_RMVO02, 0x30, 2, 0, 0, SFX_FLAG_10)
/* 0x6930 */ DEFINE_SFX(NA_SE_VO_PMVO01, 0x30, 2, 0, 0, SFX_FLAG_10)
/* 0x6931 */ DEFINE_SFX(NA_SE_VO_PMVO02, 0x30, 2, 0, 0, SFX_FLAG_10)
/* 0x6932 */ DEFINE_SFX(NA_SE_VO_PMVO03, 0x30, 2, 0, 0, SFX_FLAG_10)
/* 0x6933 */ DEFINE_SFX(NA_SE_VO_DHVO00, 0x30, 2, 0, 0, SFX_FLAG_10)
/* 0x6934 */ DEFINE_SFX(NA_SE_VO_DHVO01, 0x30, 2, 0, 0, SFX_FLAG_10)
/* 0x6935 */ DEFINE_SFX(NA_SE_VO_DHVO02, 0x30, 2, 0, 0, SFX_FLAG_10)
/* 0x6936 */ DEFINE_SFX(NA_SE_VO_DHVO03, 0x30, 2, 0, 0, SFX_FLAG_10)
/* 0x6937 */ DEFINE_SFX(NA_SE_VO_DHVO04, 0x30, 2, 0, 0, SFX_FLAG_10)
/* 0x6938 */ DEFINE_SFX(NA_SE_VO_TFVO00, 0x30, 2, 0, 0, SFX_FLAG_10)
/* 0x6939 */ DEFINE_SFX(NA_SE_VO_ANVO04, 0x30, 2, 0, 0, SFX_FLAG_10)
/* 0x693A */ DEFINE_SFX(NA_SE_VO_ANVO05, 0x30, 2, 0, 0, SFX_FLAG_10)
/* 0x693B */ DEFINE_SFX(NA_SE_VO_PMVO00, 0x30, 2, 0, 0, SFX_FLAG_10)
/* 0x693C */ DEFINE_SFX(NA_SE_VO_CHVO03, 0x30, 2, 0, 0, SFX_FLAG_10)
/* 0x693D */ DEFINE_SFX(NA_SE_VO_CHVO04, 0x30, 2, 0, 0, SFX_FLAG_10)
/* 0x693E */ DEFINE_SFX(NA_SE_VO_CHVO05, 0x30, 2, 0, 0, SFX_FLAG_10)
/* 0x693F */ DEFINE_SFX(NA_SE_VO_CHVO06, 0x30, 2, 0, 0, SFX_FLAG_10)
/* 0x6940 */ DEFINE_SFX(NA_SE_VO_CHVO07, 0x30, 2, 0, 0, SFX_FLAG_10)
/* 0x6941 */ DEFINE_SFX(NA_SE_VO_CHVO08, 0x30, 2, 0, 0, SFX_FLAG_10)
/* 0x6942 */ DEFINE_SFX(NA_SE_VO_CHVO09, 0x30, 2, 0, 0, SFX_FLAG_10)
/* 0x6943 */ DEFINE_SFX(NA_SE_VO_DPVO00, 0x30, 2, 0, 0, SFX_FLAG_10)
/* 0x6944 */ DEFINE_SFX(NA_SE_VO_DPVO01, 0x30, 2, 0, 0, SFX_FLAG_10)
/* 0x6945 */ DEFINE_SFX(NA_SE_VO_DPVO02, 0x30, 2, 0, 0, SFX_FLAG_10)
/* 0x6946 */ DEFINE_SFX(NA_SE_VO_SKVO00, 0x30, 2, 0, 0, SFX_FLAG_10)
/* 0x6947 */ DEFINE_SFX(NA_SE_VO_SKVO01, 0x30, 2, 0, 0, SFX_FLAG_10)
/* 0x6948 */ DEFINE_SFX(NA_SE_VO_KHVO00, 0x30, 2, 0, 0, SFX_FLAG_10)
/* 0x6949 */ DEFINE_SFX(NA_SE_VO_KHVO01, 0x30, 2, 0, 0, SFX_FLAG_10)
/* 0x694A */ DEFINE_SFX(NA_SE_VO_KHVO02, 0x30, 2, 0, 0, SFX_FLAG_10)
/* 0x694B */ DEFINE_SFX(NA_SE_VO_SHVO00, 0x30, 2, 0, 0, SFX_FLAG_10)
/* 0x694C */ DEFINE_SFX(NA_SE_VO_SHVO01, 0x30, 2, 0, 0, SFX_FLAG_10)
/* 0x694D */ DEFINE_SFX(NA_SE_VO_KAVO02, 0x30, 2, 0, 0, SFX_FLAG_10)
/* 0x694E */ DEFINE_SFX(NA_SE_VO_KAVO03, 0x30, 2, 0, 0, SFX_FLAG_10)
/* 0x694F */ DEFINE_SFX(NA_SE_VO_MTVO00, 0x30, 2, 0, 0, SFX_FLAG_10)
/* 0x6950 */ DEFINE_SFX(NA_SE_VO_TTVO00, 0x30, 2, 0, 0, SFX_FLAG_10)
/* 0x6951 */ DEFINE_SFX(NA_SE_VO_ITVO00, 0x30, 2, 0, 0, SFX_FLAG_10)
/* 0x6952 */ DEFINE_SFX(NA_SE_VO_ITVO01, 0x30, 2, 0, 0, SFX_FLAG_10)
/* 0x6953 */ DEFINE_SFX(NA_SE_VO_ITVO02, 0x30, 2, 0, 0, SFX_FLAG_10)
/* 0x6954 */ DEFINE_SFX(NA_SE_VO_KMVO00, 0x30, 2, 0, 0, SFX_FLAG_10)
/* 0x6955 */ DEFINE_SFX(NA_SE_VO_KMVO01, 0x30, 2, 0, 0, SFX_FLAG_10)
/* 0x6956 */ DEFINE_SFX(NA_SE_VO_JOVO00, 0x30, 2, 0, 0, SFX_FLAG_10)
/* 0x6957 */ DEFINE_SFX(NA_SE_VO_JYVO00, 0x30, 2, 0, 0, SFX_FLAG_10)
/* 0x6958 */ DEFINE_SFX(NA_SE_VO_DTVO00, 0x30, 2, 0, 0, SFX_FLAG_10)
/* 0x6959 */ DEFINE_SFX(NA_SE_VO_GUVO00, 0x30, 2, 0, 0, SFX_FLAG_10)
/* 0x695A */ DEFINE_SFX(NA_SE_VO_KTVO00, 0x30, 2, 0, 0, SFX_FLAG_10)
/* 0x695B */ DEFINE_SFX(NA_SE_VO_KTVO01, 0x30, 2, 0, 0, SFX_FLAG_10)
/* 0x695C */ DEFINE_SFX(NA_SE_VO_KTVO03, 0x30, 2, 0, 0, SFX_FLAG_10)
/* 0x695D */ DEFINE_SFX(NA_SE_VO_ZBVO00, 0x30, 2, 0, 0, SFX_FLAG_10)
/* 0x695E */ DEFINE_SFX(NA_SE_VO_ZBVO01, 0x30, 2, 0, 0, SFX_FLAG_10)
/* 0x695F */ DEFINE_SFX(NA_SE_VO_DAVO01, 0x30, 2, 0, 0, SFX_FLAG_10)
/* 0x6960 */ DEFINE_SFX(NA_SE_VO_SHVO04, 0x30, 2, 0, 0, SFX_FLAG_10)
/* 0x6961 */ DEFINE_SFX(NA_SE_VO_GBVO02, 0x30, 2, 0, 0, SFX_FLAG_10)
/* 0x6962 */ DEFINE_SFX(NA_SE_VO_GBVO03, 0x30, 2, 0, 0, SFX_FLAG_10)
/* 0x6963 */ DEFINE_SFX(NA_SE_VO_PFVO00, 0x30, 2, 0, 0, SFX_FLAG_10)
/* 0x6964 */ DEFINE_SFX(NA_SE_VO_PFVO01, 0x30, 2, 0, 0, SFX_FLAG_10)
/* 0x6965 */ DEFINE_SFX(NA_SE_VO_GAVO00, 0x30, 2, 0, 0, SFX_FLAG_10)
/* 0x6966 */ DEFINE_SFX(NA_SE_VO_GAVO01, 0x30, 2, 0, 0, SFX_FLAG_10)
/* 0x6967 */ DEFINE_SFX(NA_SE_VO_DJVO00, 0x30, 2, 0, 0, SFX_FLAG_10)
/* 0x6968 */ DEFINE_SFX(NA_SE_VO_DJVO01, 0x30, 2, 0, 0, SFX_FLAG_10)
/* 0x6969 */ DEFINE_SFX(NA_SE_VO_MSVO00, 0x30, 2, 0, 0, SFX_FLAG_10)
/* 0x696A */ DEFINE_SFX(NA_SE_VO_MSVO01, 0x30, 2, 0, 0, SFX_FLAG_10)
/* 0x696B */ DEFINE_SFX(NA_SE_VO_JPVO00, 0x30, 2, 0, 0, SFX_FLAG_10)
/* 0x696C */ DEFINE_SFX(NA_SE_VO_HYVO00, 0x30, 2, 0, 0, SFX_FLAG_10)
/* 0x696D */ DEFINE_SFX(NA_SE_VO_HYVO01, 0x30, 2, 0, 0, SFX_FLAG_10)
/* 0x696E */ DEFINE_SFX(NA_SE_VO_BAVO00, 0x30, 2, 0, 0, SFX_FLAG_10)
/* 0x696F */ DEFINE_SFX(NA_SE_VO_POVO00, 0x30, 2, 0, 0, SFX_FLAG_10)
/* 0x6970 */ DEFINE_SFX(NA_SE_VO_DAVO00, 0x30, 2, 0, 0, SFX_FLAG_10)
/* 0x6971 */ DEFINE_SFX(NA_SE_VO_DAVO02, 0x30, 2, 0, 0, SFX_FLAG_10)
/* 0x6972 */ DEFINE_SFX(NA_SE_VO_MKVO00, 0x30, 2, 0, 0, SFX_FLAG_10)
/* 0x6973 */ DEFINE_SFX(NA_SE_VO_MKVO01, 0x30, 2, 0, 0, SFX_FLAG_10)
/* 0x6974 */ DEFINE_SFX(NA_SE_VO_MKVO02, 0x30, 2, 0, 0, SFX_FLAG_10)
/* 0x6975 */ DEFINE_SFX(NA_SE_VO_MKVO03, 0x30, 2, 0, 0, SFX_FLAG_10)
/* 0x6976 */ DEFINE_SFX(NA_SE_VO_MKVO04, 0x30, 2, 0, 0, SFX_FLAG_10)
/* 0x6977 */ DEFINE_SFX(NA_SE_VO_TIVO00, 0x30, 2, 0, 0, SFX_FLAG_10)
/* 0x6978 */ DEFINE_SFX(NA_SE_VO_TIVO01, 0x30, 2, 0, 0, SFX_FLAG_10)
/* 0x6979 */ DEFINE_SFX(NA_SE_VO_TIVO02, 0x30, 2, 0, 0, SFX_FLAG_10)
/* 0x697A */ DEFINE_SFX(NA_SE_VO_TIVO03, 0x30, 2, 0, 0, SFX_FLAG_10)
/* 0x697B */ DEFINE_SFX(NA_SE_VO_TIVO04, 0x30, 2, 0, 0, SFX_FLAG_10)
/* 0x697C */ DEFINE_SFX(NA_SE_VO_TIVO05, 0x30, 2, 0, 0, SFX_FLAG_10)
/* 0x697D */ DEFINE_SFX(NA_SE_VO_OMVO00, 0x30, 2, 0, 0, SFX_FLAG_10)
/* 0x697E */ DEFINE_SFX(NA_SE_VO_OMVO01, 0x30, 2, 0, 0, SFX_FLAG_10)
/* 0x697F */ DEFINE_SFX(NA_SE_VO_OMVO02, 0x30, 2, 0, 0, SFX_FLAG_10)
/* 0x6980 */ DEFINE_SFX(NA_SE_VO_OMVO03, 0x30, 2, 0, 0, SFX_FLAG_10)
/* 0x6981 */ DEFINE_SFX(NA_SE_VO_OMVO04, 0x30, 2, 0, 0, SFX_FLAG_10)
/* 0x6982 */ DEFINE_SFX(NA_SE_VO_OMVO05, 0x30, 2, 0, 0, SFX_FLAG_10)
/* 0x6983 */ DEFINE_SFX(NA_SE_VO_OMVO06, 0x30, 2, 0, 0, SFX_FLAG_10)
/* 0x6984 */ DEFINE_SFX(NA_SE_VO_DEMO_FALL2, 0x30, 2, 0, 0, SFX_FLAG_10)
/* 0x6985 */ DEFINE_SFX(NA_SE_VO_DEMO_384, 0x30, 2, 0, 0, SFX_FLAG_10)
/* 0x6986 */ DEFINE_SFX(NA_SE_VO_DEMO_385, 0x30, 2, 0, 0, SFX_FLAG_10)
/* 0x6987 */ DEFINE_SFX(NA_SE_VO_DEMO_386, 0x30, 2, 0, 0, SFX_FLAG_10)
/* 0x6988 */ DEFINE_SFX(NA_SE_VO_DEMO_387, 0x30, 2, 0, 0, SFX_FLAG_10)
/* 0x6989 */ DEFINE_SFX(NA_SE_VO_DEMO_388, 0x30, 2, 0, 0, SFX_FLAG_10)
/* 0x698A */ DEFINE_SFX(NA_SE_VO_DEMO_389, 0x30, 2, 0, 0, SFX_FLAG_10)
/* 0x698B */ DEFINE_SFX(NA_SE_VO_DEMO_390, 0x30, 2, 0, 0, SFX_FLAG_10)
/* 0x698C */ DEFINE_SFX(NA_SE_VO_DEMO_391, 0x30, 2, 0, 0, SFX_FLAG_10)
/* 0x698D */ DEFINE_SFX(NA_SE_VO_DEMO_392, 0x30, 2, 0, 0, SFX_FLAG_10)
/* 0x698E */ DEFINE_SFX(NA_SE_VO_DEMO_393, 0x30, 2, 0, 0, SFX_FLAG_10)
/* 0x698E */ DEFINE_SFX(NA_SE_VO_DEMO_394, 0x30, 2, 0, 0, SFX_FLAG_10)
