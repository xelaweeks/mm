/**
 * Bombers Notebook Event Table
 *
 * DEFINE_EVENT should be used for events in the notebook
 *    - Argument 0: Enum value for the event (without the pfefix)
 *    - Argument 1: Icon to use (see BombersNotebookEventIcon)
 *    - Argument 2: WeekEventFlag that updates the icons color
 *    - Argument 3: Message id for the description of this event
 *    - Argument 4: Message id for the completion of this event
 *    - Argument 5: WeekEventFlag for the completion of this event
 */
/* 0x00 */ DEFINE_EVENT(RECEIVED_ROOM_KEY, BOMBERS_NOTEBOOK_EVENT_ICON_EXCLAMATION_POINT, WEEKEVENTREG_75_10, 0x2198, 0x2152, WEEKEVENTREG_BOMBERS_NOTEBOOK_EVENT_RECEIVED_ROOM_KEY)
/* 0x01 */ DEFINE_EVENT(PROMISED_MIDNIGHT_MEETING, BOMBERS_NOTEBOOK_EVENT_ICON_EXCLAMATION_POINT, WEEKEVENTREG_50_08, 0x2199, 0x2153, WEEKEVENTREG_BOMBERS_NOTEBOOK_EVENT_PROMISED_MIDNIGHT_MEETING)
/* 0x02 */ DEFINE_EVENT(PROMISED_TO_MEET_KAFEI, BOMBERS_NOTEBOOK_EVENT_ICON_EXCLAMATION_POINT, WEEKEVENTREG_50_20, 0x219A, 0x2154, WEEKEVENTREG_BOMBERS_NOTEBOOK_EVENT_PROMISED_TO_MEET_KAFEI)
/* 0x03 */ DEFINE_EVENT(RECEIVED_LETTER_TO_KAFEI, BOMBERS_NOTEBOOK_EVENT_ICON_EXCLAMATION_POINT, WEEKEVENTREG_50_20, 0x219B, 0, WEEKEVENTREG_BOMBERS_NOTEBOOK_EVENT_RECEIVED_LETTER_TO_KAFEI)
/* 0x04 */ DEFINE_EVENT(DEPOSITED_LETTER_TO_KAFEI, BOMBERS_NOTEBOOK_EVENT_ICON_EXCLAMATION_POINT, BOMBERS_NOTEBOOK_EVENT_COLOR_WEEKEVENTREG_DELIVERED_LETTER, 0x219C, 0x2156, WEEKEVENTREG_BOMBERS_NOTEBOOK_EVENT_DEPOSITED_LETTER_TO_KAFEI)
/* 0x05 */ DEFINE_EVENT(RECEIVED_PENDANT_OF_MEMORIES, BOMBERS_NOTEBOOK_EVENT_ICON_EXCLAMATION_POINT, WEEKEVENTREG_50_80, 0x219D, 0x2157, WEEKEVENTREG_BOMBERS_NOTEBOOK_EVENT_RECEIVED_PENDANT_OF_MEMORIES)
/* 0x06 */ DEFINE_EVENT(DELIVERED_PENDANT_OF_MEMORIES, BOMBERS_NOTEBOOK_EVENT_ICON_EXCLAMATION_POINT, WEEKEVENTREG_51_01, 0x219E, 0x2158, WEEKEVENTREG_BOMBERS_NOTEBOOK_EVENT_DELIVERED_PENDANT_OF_MEMORIES)
/* 0x07 */ DEFINE_EVENT(ESCAPED_SAKONS_HIDEOUT, BOMBERS_NOTEBOOK_EVENT_ICON_EXCLAMATION_POINT, WEEKEVENTREG_51_20, 0x219F, 0x2159, WEEKEVENTREG_BOMBERS_NOTEBOOK_EVENT_ESCAPED_SAKONS_HIDEOUT)
/* 0x08 */ DEFINE_EVENT(PROMISED_TO_HELP_WITH_THEM, BOMBERS_NOTEBOOK_EVENT_ICON_EXCLAMATION_POINT, WEEKEVENTREG_21_20, 0x21A0, 0x215A, WEEKEVENTREG_BOMBERS_NOTEBOOK_EVENT_PROMISED_TO_HELP_WITH_THEM)
/* 0x09 */ DEFINE_EVENT(DEFENDED_AGAINST_THEM, BOMBERS_NOTEBOOK_EVENT_ICON_EXCLAMATION_POINT, WEEKEVENTREG_22_01, 0x21A1, 0x215B, WEEKEVENTREG_BOMBERS_NOTEBOOK_EVENT_DEFENDED_AGAINST_THEM)
/* 0x0A */ DEFINE_EVENT(RECEIVED_MILK_BOTTLE, BOMBERS_NOTEBOOK_EVENT_ICON_RIBBON, BOMBERS_NOTEBOOK_EVENT_COLOR_WEEKEVENTREG_NONE, 0x21A2, 0, WEEKEVENTREG_BOMBERS_NOTEBOOK_EVENT_RECEIVED_MILK_BOTTLE)
/* 0x0B */ DEFINE_EVENT(ESCORTED_CREMIA, BOMBERS_NOTEBOOK_EVENT_ICON_EXCLAMATION_POINT, WEEKEVENTREG_52_01, 0x21A3, 0x215D, WEEKEVENTREG_BOMBERS_NOTEBOOK_EVENT_ESCORTED_CREMIA)
/* 0x0C */ DEFINE_EVENT(RECEIVED_ROMANIS_MASK, BOMBERS_NOTEBOOK_EVENT_ICON_MASK, BOMBERS_NOTEBOOK_EVENT_COLOR_WEEKEVENTREG_NONE, 0x21A4, 0, WEEKEVENTREG_BOMBERS_NOTEBOOK_EVENT_RECEIVED_ROMANIS_MASK)
/* 0x0D */ DEFINE_EVENT(RECEIVED_KEATON_MASK, BOMBERS_NOTEBOOK_EVENT_ICON_MASK, BOMBERS_NOTEBOOK_EVENT_COLOR_WEEKEVENTREG_NONE, 0x21A5, 0x215F, WEEKEVENTREG_BOMBERS_NOTEBOOK_EVENT_RECEIVED_KEATON_MASK)
/* 0x0E */ DEFINE_EVENT(RECEIVED_PRIORITY_MAIL, BOMBERS_NOTEBOOK_EVENT_ICON_EXCLAMATION_POINT, WEEKEVENTREG_80_10, 0x21A6, 0x2160, WEEKEVENTREG_BOMBERS_NOTEBOOK_EVENT_RECEIVED_PRIORITY_MAIL)
/* 0x0F */ DEFINE_EVENT(DELIVERED_PRIORITY_MAIL, BOMBERS_NOTEBOOK_EVENT_ICON_RIBBON, BOMBERS_NOTEBOOK_EVENT_COLOR_WEEKEVENTREG_NONE, 0x21A7, 0x2161, WEEKEVENTREG_BOMBERS_NOTEBOOK_EVENT_DELIVERED_PRIORITY_MAIL)
/* 0x10 */ DEFINE_EVENT(LEARNED_SECRET_CODE, BOMBERS_NOTEBOOK_EVENT_ICON_EXCLAMATION_POINT, BOMBERS_NOTEBOOK_EVENT_COLOR_WEEKEVENTREG_NONE, 0x21A8, 0, WEEKEVENTREG_BOMBERS_NOTEBOOK_EVENT_LEARNED_SECRET_CODE)
/* 0x11 */ DEFINE_EVENT(RECEIVED_BOMBERS_NOTEBOOK, BOMBERS_NOTEBOOK_EVENT_ICON_RIBBON, BOMBERS_NOTEBOOK_EVENT_COLOR_WEEKEVENTREG_NONE, 0x21A9, 0x2163, WEEKEVENTREG_BOMBERS_NOTEBOOK_EVENT_RECEIVED_BOMBERS_NOTEBOOK)
/* 0x12 */ DEFINE_EVENT(RECEIVED_MAYOR_HP, BOMBERS_NOTEBOOK_EVENT_ICON_RIBBON, BOMBERS_NOTEBOOK_EVENT_COLOR_WEEKEVENTREG_NONE, 0x21AA, 0x2164, WEEKEVENTREG_BOMBERS_NOTEBOOK_EVENT_RECEIVED_MAYOR_HP)
/* 0x13 */ DEFINE_EVENT(RECEIVED_ROSA_SISTERS_HP, BOMBERS_NOTEBOOK_EVENT_ICON_RIBBON, BOMBERS_NOTEBOOK_EVENT_COLOR_WEEKEVENTREG_NONE, 0x21AB, 0x2165, WEEKEVENTREG_BOMBERS_NOTEBOOK_EVENT_RECEIVED_ROSA_SISTERS_HP)
/* 0x14 */ DEFINE_EVENT(RECEIVED_TOILET_HAND_HP, BOMBERS_NOTEBOOK_EVENT_ICON_RIBBON, BOMBERS_NOTEBOOK_EVENT_COLOR_WEEKEVENTREG_NONE, 0x21AC, 0x2166, WEEKEVENTREG_BOMBERS_NOTEBOOK_EVENT_RECEIVED_TOILET_HAND_HP)
/* 0x15 */ DEFINE_EVENT(RECEIVED_GRANDMA_SHORT_STORY_HP, BOMBERS_NOTEBOOK_EVENT_ICON_RIBBON, BOMBERS_NOTEBOOK_EVENT_COLOR_WEEKEVENTREG_NONE, 0x21AD, 0x2167, WEEKEVENTREG_BOMBERS_NOTEBOOK_EVENT_RECEIVED_GRANDMA_SHORT_STORY_HP)
/* 0x16 */ DEFINE_EVENT(RECEIVED_GRANDMA_LONG_STORY_HP, BOMBERS_NOTEBOOK_EVENT_ICON_RIBBON, BOMBERS_NOTEBOOK_EVENT_COLOR_WEEKEVENTREG_NONE, 0x21AE, 0x2168, WEEKEVENTREG_BOMBERS_NOTEBOOK_EVENT_RECEIVED_GRANDMA_LONG_STORY_HP)
/* 0x17 */ DEFINE_EVENT(RECEIVED_POSTMAN_HP, BOMBERS_NOTEBOOK_EVENT_ICON_RIBBON, BOMBERS_NOTEBOOK_EVENT_COLOR_WEEKEVENTREG_NONE, 0x21AF, 0x2169, WEEKEVENTREG_BOMBERS_NOTEBOOK_EVENT_RECEIVED_POSTMAN_HP)
/* 0x18 */ DEFINE_EVENT(RECEIVED_KAFEIS_MASK, BOMBERS_NOTEBOOK_EVENT_ICON_MASK, BOMBERS_NOTEBOOK_EVENT_COLOR_WEEKEVENTREG_NONE, 0x21B0, 0x216A, WEEKEVENTREG_BOMBERS_NOTEBOOK_EVENT_RECEIVED_KAFEIS_MASK)
/* 0x19 */ DEFINE_EVENT(RECEIVED_ALL_NIGHT_MASK, BOMBERS_NOTEBOOK_EVENT_ICON_MASK, BOMBERS_NOTEBOOK_EVENT_COLOR_WEEKEVENTREG_NONE, 0x21B1, 0x216B, WEEKEVENTREG_BOMBERS_NOTEBOOK_EVENT_RECEIVED_ALL_NIGHT_MASK)
/* 0x1A */ DEFINE_EVENT(RECEIVED_BUNNY_HOOD, BOMBERS_NOTEBOOK_EVENT_ICON_MASK, BOMBERS_NOTEBOOK_EVENT_COLOR_WEEKEVENTREG_NONE, 0x21B2, 0x216C, WEEKEVENTREG_BOMBERS_NOTEBOOK_EVENT_RECEIVED_BUNNY_HOOD)
/* 0x1B */ DEFINE_EVENT(RECEIVED_GAROS_MASK, BOMBERS_NOTEBOOK_EVENT_ICON_MASK, BOMBERS_NOTEBOOK_EVENT_COLOR_WEEKEVENTREG_NONE, 0x21B3, 0x216D, WEEKEVENTREG_BOMBERS_NOTEBOOK_EVENT_RECEIVED_GAROS_MASK)
/* 0x1C */ DEFINE_EVENT(RECEIVED_CIRCUS_LEADERS_MASK, BOMBERS_NOTEBOOK_EVENT_ICON_MASK, BOMBERS_NOTEBOOK_EVENT_COLOR_WEEKEVENTREG_NONE, 0x21B4, 0x216E, WEEKEVENTREG_BOMBERS_NOTEBOOK_EVENT_RECEIVED_CIRCUS_LEADERS_MASK)
/* 0x1D */ DEFINE_EVENT(RECEIVED_POSTMANS_HAT, BOMBERS_NOTEBOOK_EVENT_ICON_MASK, BOMBERS_NOTEBOOK_EVENT_COLOR_WEEKEVENTREG_NONE, 0x21B5, 0x216F, WEEKEVENTREG_BOMBERS_NOTEBOOK_EVENT_RECEIVED_POSTMANS_HAT)
/* 0x1E */ DEFINE_EVENT(RECEIVED_COUPLES_MASK, BOMBERS_NOTEBOOK_EVENT_ICON_MASK, BOMBERS_NOTEBOOK_EVENT_COLOR_WEEKEVENTREG_NONE, 0x21B6, 0x2170, WEEKEVENTREG_BOMBERS_NOTEBOOK_EVENT_RECEIVED_COUPLES_MASK)
/* 0x1F */ DEFINE_EVENT(RECEIVED_BLAST_MASK, BOMBERS_NOTEBOOK_EVENT_ICON_MASK, BOMBERS_NOTEBOOK_EVENT_COLOR_WEEKEVENTREG_NONE, 0x21B7, 0x2171, WEEKEVENTREG_BOMBERS_NOTEBOOK_EVENT_RECEIVED_BLAST_MASK)
/* 0x20 */ DEFINE_EVENT(RECEIVED_KAMAROS_MASK, BOMBERS_NOTEBOOK_EVENT_ICON_MASK, BOMBERS_NOTEBOOK_EVENT_COLOR_WEEKEVENTREG_NONE, 0x21B8, 0x2172, WEEKEVENTREG_BOMBERS_NOTEBOOK_EVENT_RECEIVED_KAMAROS_MASK)
/* 0x21 */ DEFINE_EVENT(RECEIVED_STONE_MASK, BOMBERS_NOTEBOOK_EVENT_ICON_MASK, BOMBERS_NOTEBOOK_EVENT_COLOR_WEEKEVENTREG_NONE, 0x21B9, 0x2173, WEEKEVENTREG_BOMBERS_NOTEBOOK_EVENT_RECEIVED_STONE_MASK)
/* 0x22 */ DEFINE_EVENT(RECEIVED_BREMEN_MASK, BOMBERS_NOTEBOOK_EVENT_ICON_MASK, BOMBERS_NOTEBOOK_EVENT_COLOR_WEEKEVENTREG_NONE, 0x21BA, 0x2174, WEEKEVENTREG_BOMBERS_NOTEBOOK_EVENT_RECEIVED_BREMEN_MASK)
