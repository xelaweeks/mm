#ifndef _Z64ITEM_H_
#define _Z64ITEM_H_

#define DROP_TABLE_SIZE 16
#define DROP_TABLE_NUMBER 17

// TODO fill out these enums

typedef enum {
    /* 0 */ EQUIP_TYPE_SWORD,
    /* 1 */ EQUIP_TYPE_SHIELD,
    /* 2 */ EQUIP_TYPE_MAX
} EquipmentType;

typedef enum {
    /* 0 */ EQUIP_VALUE_SWORD_NONE,
    /* 1 */ EQUIP_VALUE_SWORD_KOKIRI,
    /* 2 */ EQUIP_VALUE_SWORD_RAZOR,
    /* 3 */ EQUIP_VALUE_SWORD_GILDED,
    /* 4 */ EQUIP_VALUE_SWORD_DIETY,
    /* 5 */ EQUIP_VALUE_SWORD_MAX,
} EquipValueSword;

typedef enum {
    /* 0 */ EQUIP_VALUE_SHIELD_NONE,
    /* 1 */ EQUIP_VALUE_SHIELD_HERO,
    /* 2 */ EQUIP_VALUE_SHIELD_MIRROR,
    /* 3 */ EQUIP_VALUE_SHIELD_MAX
} EquipValueShield;

typedef enum {
    /* 0 */ UPG_QUIVER,
    /* 1 */ UPG_BOMB_BAG,
    /* 2 */ UPG_STRENGTH,
    /* 3 */ UPG_SCALE,
    /* 4 */ UPG_WALLET,
    /* 5 */ UPG_BULLET_BAG,
    /* 6 */ UPG_STICKS,
    /* 7 */ UPG_NUTS
} UpgradeType;

typedef enum {
    /* 0x00 */ QUEST_REMAINS_ODOLWA,
    /* 0x01 */ QUEST_REMAINS_GOHT,
    /* 0x02 */ QUEST_REMAINS_GYORG,
    /* 0x03 */ QUEST_REMAINS_TWINMOLD,
    /* 0x04 */ QUEST_SHIELD,
    /* 0x05 */ QUEST_SWORD,
    /* 0x06 */ QUEST_SONG_SONATA,
    /* 0x07 */ QUEST_SONG_LULLABY,
    /* 0x08 */ QUEST_SONG_BOSSA_NOVA,
    /* 0x09 */ QUEST_SONG_ELEGY,
    /* 0x0A */ QUEST_SONG_OATH,
    /* 0x0B */ QUEST_SONG_SARIA,
    /* 0x0C */ QUEST_SONG_TIME,
    /* 0x0D */ QUEST_SONG_HEALING,
    /* 0x0E */ QUEST_SONG_EPONA,
    /* 0x0F */ QUEST_SONG_SOARING,
    /* 0x10 */ QUEST_SONG_STORMS,
    /* 0x11 */ QUEST_SONG_SUN,
    /* 0x12 */ QUEST_BOMBERS_NOTEBOOK, // Obtained Bombers Notebook
    /* 0x13 */ QUEST_QUIVER,
    /* 0x14 */ QUEST_BOMB_BAG,
    /* 0x15 */ QUEST_SKULL_TOKEN,
    /* 0x16 */ QUEST_HEART_PIECE,  // for `pauseCtx->cursorPoint[PAUSE_QUEST]`
    /* 0x17 */ QUEST_17, // Used in a conditional for quest cursors
    /* 0x18 */ QUEST_SONG_LULLABY_INTRO,
    /* 0x19 */ QUEST_PICTOGRAPH, // A photo from the pictograph box is saved
    /* 0x1C */ QUEST_HEART_PIECE_COUNT = 0x1C
} QuestItem;

typedef enum {
    /* -1 */ DUNGEON_NONE = -1,
    /*  0 */ DUNGEON_BOSS_KEY,
    /*  1 */ DUNGEON_COMPASS,
    /*  2 */ DUNGEON_MAP,
    /*  3 */ DUNGEON_STRAY_FAIRIES,
    /*  4 */ DUNGEON_FLOOR_INDEX_4, // Top Floor
    /*  5 */ DUNGEON_FLOOR_INDEX_3,
    /*  6 */ DUNGEON_FLOOR_INDEX_2,
    /*  7 */ DUNGEON_FLOOR_INDEX_1,
    /*  8 */ DUNGEON_FLOOR_INDEX_0 // Bottom Floor
} DungeonItem;

typedef enum {
    /* 0x00 */ SLOT_OCARINA,
    /* 0x01 */ SLOT_BOW,
    /* 0x02 */ SLOT_ARROW_FIRE,
    /* 0x03 */ SLOT_ARROW_ICE,
    /* 0x04 */ SLOT_ARROW_LIGHT,
    /* 0x05 */ SLOT_TRADE_DEED,
    /* 0x06 */ SLOT_BOMB,
    /* 0x07 */ SLOT_BOMBCHU,
    /* 0x08 */ SLOT_STICK,
    /* 0x09 */ SLOT_NUT,
    /* 0x0A */ SLOT_MAGIC_BEANS,
    /* 0x0B */ SLOT_TRADE_KEY_MAMA,
    /* 0x0C */ SLOT_POWDER_KEG,
    /* 0x0D */ SLOT_PICTO_BOX,
    /* 0x0E */ SLOT_LENS,
    /* 0x0F */ SLOT_HOOKSHOT,
    /* 0x10 */ SLOT_SWORD_GREAT_FAIRY,
    /* 0x11 */ SLOT_TRADE_COUPLE,
    /* 0x12 */ SLOT_BOTTLE_1,
    /* 0x13 */ SLOT_BOTTLE_2,
    /* 0x14 */ SLOT_BOTTLE_3,
    /* 0x15 */ SLOT_BOTTLE_4,
    /* 0x16 */ SLOT_BOTTLE_5,
    /* 0x17 */ SLOT_BOTTLE_6,
    /* 0x18 */ SLOT_MASK_POSTMAN,
    /* 0x19 */ SLOT_MASK_ALL_NIGHT,
    /* 0x1A */ SLOT_MASK_BLAST,
    /* 0x1B */ SLOT_MASK_STONE,
    /* 0x1C */ SLOT_MASK_GREAT_FAIRY,
    /* 0x1D */ SLOT_MASK_DEKU,
    /* 0x1E */ SLOT_MASK_KEATON,
    /* 0x1F */ SLOT_MASK_BREMEN,
    /* 0x20 */ SLOT_MASK_BUNNY,
    /* 0x21 */ SLOT_MASK_DON_GERO,
    /* 0x22 */ SLOT_MASK_SCENTS,
    /* 0x23 */ SLOT_MASK_GORON,
    /* 0x24 */ SLOT_MASK_ROMANI,
    /* 0x25 */ SLOT_MASK_CIRCUS_LEADER,
    /* 0x26 */ SLOT_MASK_KAFEIS_MASK,
    /* 0x27 */ SLOT_MASK_COUPLE,
    /* 0x28 */ SLOT_MASK_TRUTH,
    /* 0x29 */ SLOT_MASK_ZORA,
    /* 0x2A */ SLOT_MASK_KAMARO,
    /* 0x2B */ SLOT_MASK_GIBDO,
    /* 0x2C */ SLOT_MASK_GARO,
    /* 0x2D */ SLOT_MASK_CAPTAIN,
    /* 0x2E */ SLOT_MASK_GIANT,
    /* 0x2F */ SLOT_MASK_FIERCE_DEITY,
    /* 0xFF */ SLOT_NONE = 0xFF
} InventorySlot;

typedef enum {
    /* 0x00 */ ITEM_OCARINA,
    /* 0x01 */ ITEM_BOW,
    /* 0x02 */ ITEM_ARROW_FIRE,
    /* 0x03 */ ITEM_ARROW_ICE,
    /* 0x04 */ ITEM_ARROW_LIGHT,
    /* 0x05 */ ITEM_OCARINA_FAIRY,
    /* 0x06 */ ITEM_BOMB,
    /* 0x07 */ ITEM_BOMBCHU,
    /* 0x08 */ ITEM_STICK,
    /* 0x09 */ ITEM_NUT,
    /* 0x0A */ ITEM_MAGIC_BEANS,
    /* 0x0B */ ITEM_SLINGSHOT,
    /* 0x0C */ ITEM_POWDER_KEG,
    /* 0x0D */ ITEM_PICTO_BOX,
    /* 0x0E */ ITEM_LENS,
    /* 0x0F */ ITEM_HOOKSHOT,
    /* 0x10 */ ITEM_SWORD_GREAT_FAIRY,
    /* 0x11 */ ITEM_LONGSHOT, // OoT Leftover
    /* 0x12 */ ITEM_BOTTLE,
    /* 0x13 */ ITEM_POTION_RED,
    /* 0x14 */ ITEM_POTION_GREEN,
    /* 0x15 */ ITEM_POTION_BLUE,
    /* 0x16 */ ITEM_FAIRY,
    /* 0x17 */ ITEM_DEKU_PRINCESS,
    /* 0x18 */ ITEM_MILK_BOTTLE,
    /* 0x19 */ ITEM_MILK_HALF,
    /* 0x1A */ ITEM_FISH,
    /* 0x1B */ ITEM_BUG,
    /* 0x1C */ ITEM_BLUE_FIRE,
    /* 0x1D */ ITEM_POE,
    /* 0x1E */ ITEM_BIG_POE,
    /* 0x1F */ ITEM_SPRING_WATER,
    /* 0x20 */ ITEM_HOT_SPRING_WATER,
    /* 0x21 */ ITEM_ZORA_EGG,
    /* 0x22 */ ITEM_GOLD_DUST,
    /* 0x23 */ ITEM_MUSHROOM,
    /* 0x24 */ ITEM_SEAHORSE,
    /* 0x25 */ ITEM_CHATEAU,
    /* 0x26 */ ITEM_HYLIAN_LOACH,
    /* 0x27 */ ITEM_OBABA_DRINK,
    /* 0x28 */ ITEM_MOON_TEAR,
    /* 0x29 */ ITEM_DEED_LAND,
    /* 0x2A */ ITEM_DEED_SWAMP,
    /* 0x2B */ ITEM_DEED_MOUNTAIN,
    /* 0x2C */ ITEM_DEED_OCEAN,
    /* 0x2D */ ITEM_ROOM_KEY,
    /* 0x2E */ ITEM_LETTER_MAMA,
    /* 0x2F */ ITEM_LETTER_TO_KAFEI,
    /* 0x30 */ ITEM_PENDANT_OF_MEMORIES,
    /* 0x31 */ ITEM_TINGLE_MAP,
    /* 0x32 */ ITEM_MASK_DEKU,
    /* 0x33 */ ITEM_MASK_GORON,
    /* 0x34 */ ITEM_MASK_ZORA,
    /* 0x35 */ ITEM_MASK_FIERCE_DEITY,
    /* 0x36 */ ITEM_MASK_TRUTH,
    /* 0x37 */ ITEM_MASK_KAFEIS_MASK,
    /* 0x38 */ ITEM_MASK_ALL_NIGHT,
    /* 0x39 */ ITEM_MASK_BUNNY,
    /* 0x3A */ ITEM_MASK_KEATON,
    /* 0x3B */ ITEM_MASK_GARO,
    /* 0x3C */ ITEM_MASK_ROMANI,
    /* 0x3D */ ITEM_MASK_CIRCUS_LEADER,
    /* 0x3E */ ITEM_MASK_POSTMAN,
    /* 0x3F */ ITEM_MASK_COUPLE,
    /* 0x40 */ ITEM_MASK_GREAT_FAIRY,
    /* 0x41 */ ITEM_MASK_GIBDO,
    /* 0x42 */ ITEM_MASK_DON_GERO,
    /* 0x43 */ ITEM_MASK_KAMARO,
    /* 0x44 */ ITEM_MASK_CAPTAIN,
    /* 0x45 */ ITEM_MASK_STONE,
    /* 0x46 */ ITEM_MASK_BREMEN,
    /* 0x47 */ ITEM_MASK_BLAST,
    /* 0x48 */ ITEM_MASK_SCENTS,
    /* 0x49 */ ITEM_MASK_GIANT,
    /* 0x4A */ ITEM_BOW_ARROW_FIRE,
    /* 0x4B */ ITEM_BOW_ARROW_ICE,
    /* 0x4C */ ITEM_BOW_ARROW_LIGHT,
    /* 0x4D */ ITEM_SWORD_KOKIRI,
    /* 0x4E */ ITEM_SWORD_RAZOR,
    /* 0x4F */ ITEM_SWORD_GILDED,
    /* 0x50 */ ITEM_SWORD_DEITY,
    /* 0x51 */ ITEM_SHIELD_HERO,
    /* 0x52 */ ITEM_SHIELD_MIRROR,
    /* 0x53 */ ITEM_QUIVER_30,
    /* 0x54 */ ITEM_QUIVER_40,
    /* 0x55 */ ITEM_QUIVER_50,
    /* 0x56 */ ITEM_BOMB_BAG_20,
    /* 0x57 */ ITEM_BOMB_BAG_30,
    /* 0x58 */ ITEM_BOMB_BAG_40,
    /* 0x59 */ ITEM_WALLET_DEFAULT,
    /* 0x5A */ ITEM_WALLET_ADULT,
    /* 0x5B */ ITEM_WALLET_GIANT,
    /* 0x5C */ ITEM_FISHING_ROD,
    /* 0x5D */ ITEM_REMAINS_ODOLWA,
    /* 0x5E */ ITEM_REMAINS_GOHT,
    /* 0x5F */ ITEM_REMAINS_GYORG,
    /* 0x60 */ ITEM_REMAINS_TWINMOLD,
    /* 0x61 */ ITEM_SONG_SONATA,
    /* 0x62 */ ITEM_SONG_LULLABY,
    /* 0x63 */ ITEM_SONG_NOVA,
    /* 0x64 */ ITEM_SONG_ELEGY,
    /* 0x65 */ ITEM_SONG_OATH,
    /* 0x66 */ ITEM_SONG_SARIA,
    /* 0x67 */ ITEM_SONG_TIME,
    /* 0x68 */ ITEM_SONG_HEALING,
    /* 0x69 */ ITEM_SONG_EPONA,
    /* 0x6A */ ITEM_SONG_SOARING,
    /* 0x6B */ ITEM_SONG_STORMS,
    /* 0x6C */ ITEM_SONG_SUN,
    /* 0x6D */ ITEM_BOMBERS_NOTEBOOK,
    /* 0x6E */ ITEM_SKULL_TOKEN,
    /* 0x6F */ ITEM_HEART_CONTAINER,
    /* 0x70 */ ITEM_HEART_PIECE,
    /* 0x73 */ ITEM_SONG_LULLABY_INTRO = 0x73,
    /* 0x74 */ ITEM_KEY_BOSS,
    /* 0x75 */ ITEM_COMPASS,
    /* 0x76 */ ITEM_DUNGEON_MAP,
    /* 0x77 */ ITEM_STRAY_FAIRIES,
    /* 0x78 */ ITEM_KEY_SMALL,
    /* 0x79 */ ITEM_MAGIC_SMALL,
    /* 0x7A */ ITEM_MAGIC_LARGE,
    /* 0x7B */ ITEM_HEART_PIECE_2,
    /* 0x7C */ ITEM_INVALID_1,
    /* 0x7D */ ITEM_INVALID_2,
    /* 0x7E */ ITEM_INVALID_3,
    /* 0x7F */ ITEM_INVALID_4,
    /* 0x80 */ ITEM_INVALID_5,
    /* 0x81 */ ITEM_INVALID_6,
    /* 0x82 */ ITEM_INVALID_7,
    /* 0x83 */ ITEM_RECOVERY_HEART,
    /* 0x84 */ ITEM_RUPEE_GREEN,
    /* 0x85 */ ITEM_RUPEE_BLUE,
    /* 0x86 */ ITEM_RUPEE_10,
    /* 0x87 */ ITEM_RUPEE_RED,
    /* 0x88 */ ITEM_RUPEE_PURPLE,
    /* 0x89 */ ITEM_RUPEE_SILVER,
    /* 0x8A */ ITEM_RUPEE_HUGE,
    /* 0x8B */ ITEM_STICKS_5,
    /* 0x8C */ ITEM_STICKS_10,
    /* 0x8D */ ITEM_NUTS_5,
    /* 0x8E */ ITEM_NUTS_10,
    /* 0x8F */ ITEM_BOMBS_5,
    /* 0x90 */ ITEM_BOMBS_10,
    /* 0x91 */ ITEM_BOMBS_20,
    /* 0x92 */ ITEM_BOMBS_30,
    /* 0x93 */ ITEM_ARROWS_10,
    /* 0x94 */ ITEM_ARROWS_30,
    /* 0x95 */ ITEM_ARROWS_40,
    /* 0x96 */ ITEM_ARROWS_50,
    /* 0x97 */ ITEM_BOMBCHUS_20,
    /* 0x98 */ ITEM_BOMBCHUS_10,
    /* 0x99 */ ITEM_BOMBCHUS_1,
    /* 0x9A */ ITEM_BOMBCHUS_5,
    /* 0x9B */ ITEM_STICK_UPGRADE_20,
    /* 0x9C */ ITEM_STICK_UPGRADE_30,
    /* 0x9D */ ITEM_NUT_UPGRADE_30,
    /* 0x9E */ ITEM_NUT_UPGRADE_40,
    /* 0x9F */ ITEM_CHATEAU_2,
    /* 0xA0 */ ITEM_MILK,
    /* 0xA1 */ ITEM_GOLD_DUST_2,
    /* 0xA2 */ ITEM_HYLIAN_LOACH_2,
    /* 0xA3 */ ITEM_SEAHORSE_CAUGHT,
    /* 0xF0 */ ITEM_F0 = 0xF0,
    /* 0xF1 */ ITEM_F1,
    /* 0xF2 */ ITEM_F2,
    /* 0xFD */ ITEM_FD = 0xFD,
    /* 0xFF */ ITEM_NONE = 0xFF
} ItemId;

#define BOTTLE_FIRST 0
#define BOTTLE_MAX 6

typedef enum {
    /* 0x00 */ GI_NONE,
    /* 0x01 */ GI_RUPEE_GREEN,
    /* 0x02 */ GI_RUPEE_BLUE,
    /* 0x03 */ GI_RUPEE_10,
    /* 0x04 */ GI_RUPEE_RED,
    /* 0x05 */ GI_RUPEE_PURPLE,
    /* 0x06 */ GI_RUPEE_SILVER,
    /* 0x07 */ GI_RUPEE_HUGE,
    /* 0x08 */ GI_WALLET_ADULT,
    /* 0x09 */ GI_WALLET_GIANT,
    /* 0x0A */ GI_RECOVERY_HEART,
    /* 0x0C */ GI_HEART_PIECE = 0x0C,
    /* 0x0D */ GI_HEART_CONTAINER,
    /* 0x0E */ GI_MAGIC_SMALL,
    /* 0x0F */ GI_MAGIC_LARGE,
    /* 0x11 */ GI_STRAY_FAIRY = 0x11,
    /* 0x14 */ GI_BOMBS_1 = 0x14,
    /* 0x15 */ GI_BOMBS_5,
    /* 0x16 */ GI_BOMBS_10,
    /* 0x17 */ GI_BOMBS_20,
    /* 0x18 */ GI_BOMBS_30,
    /* 0x19 */ GI_STICKS_1,
    /* 0x1A */ GI_BOMBCHUS_10,
    /* 0x1B */ GI_BOMB_BAG_20,
    /* 0x1C */ GI_BOMB_BAG_30,
    /* 0x1D */ GI_BOMB_BAG_40,
    /* 0x1E */ GI_ARROWS_10,
    /* 0x1F */ GI_ARROWS_30,
    /* 0x20 */ GI_ARROWS_40,
    /* 0x21 */ GI_ARROWS_50,
    /* 0x22 */ GI_QUIVER_30,
    /* 0x23 */ GI_QUIVER_40,
    /* 0x24 */ GI_QUIVER_50,
    /* 0x25 */ GI_ARROW_FIRE,
    /* 0x26 */ GI_ARROW_ICE,
    /* 0x27 */ GI_ARROW_LIGHT,
    /* 0x28 */ GI_NUTS_1,
    /* 0x29 */ GI_NUTS_5,
    /* 0x2A */ GI_NUTS_10,
    /* 0x2E */ GI_BOMBCHUS_20 = 0x2E,
    /* 0x32 */ GI_SHIELD_HERO = 0x32,
    /* 0x33 */ GI_SHIELD_MIRROR,
    /* 0x34 */ GI_POWDER_KEG,
    /* 0x35 */ GI_MAGIC_BEANS,
    /* 0x36 */ GI_BOMBCHUS_1,
    /* 0x37 */ GI_SWORD_KOKIRI,
    /* 0x38 */ GI_SWORD_RAZOR,
    /* 0x39 */ GI_SWORD_GILDED,
    /* 0x3A */ GI_BOMBCHUS_5,
    /* 0x3B */ GI_SWORD_GREAT_FAIRY,
    /* 0x3C */ GI_KEY_SMALL,
    /* 0x3D */ GI_KEY_BOSS,
    /* 0x3E */ GI_MAP,
    /* 0x3F */ GI_COMPASS,
    /* 0x41 */ GI_HOOKSHOT = 0x41,
    /* 0x42 */ GI_LENS,
    /* 0x43 */ GI_PICTO_BOX,
    /* 0x4C */ GI_OCARINA = 0x4C,
    /* 0x50 */ GI_BOMBERS_NOTEBOOK = 0x50,
    /* 0x52 */ GI_SKULL_TOKEN = 0x52,
    /* 0x55 */ GI_REMAINS_ODOLWA = 0x55,
    /* 0x56 */ GI_REMAINS_GOHT,
    /* 0x57 */ GI_REMAINS_GYORG,
    /* 0x58 */ GI_REMAINS_TWINMOLD,
    /* 0x59 */ GI_POTION_RED_BOTTLE, // ITEM_LONGSHOT
    /* 0x5A */ GI_BOTTLE,
    /* 0x5B */ GI_POTION_RED,
    /* 0x5C */ GI_POTION_GREEN,
    /* 0x5D */ GI_POTION_BLUE,
    /* 0x5E */ GI_FAIRY,
    /* 0x5F */ GI_DEKU_PRINCESS,
    /* 0x60 */ GI_MILK_BOTTLE,
    /* 0x61 */ GI_MILK_HALF,
    /* 0x62 */ GI_FISH,
    /* 0x63 */ GI_BUG,
    /* 0x64 */ GI_BLUE_FIRE,
    /* 0x65 */ GI_POE,
    /* 0x66 */ GI_BIG_POE,
    /* 0x67 */ GI_SPRING_WATER,
    /* 0x68 */ GI_HOT_SPRING_WATER,
    /* 0x69 */ GI_ZORA_EGG,
    /* 0x6A */ GI_GOLD_DUST,
    /* 0x6B */ GI_MUSHROOM,
    /* 0x6E */ GI_SEAHORSE = 0x6E,
    /* 0x6F */ GI_CHATEAU_BOTTLE,
    /* 0x76 */ GI_ICE_TRAP = 0x76,
    /* 0x78 */ GI_MASK_DEKU = 0x78,
    /* 0x79 */ GI_MASK_GORON,
    /* 0x7A */ GI_MASK_ZORA,
    /* 0x7B */ GI_MASK_FIERCE_DEITY,
    /* 0x7C */ GI_MASK_CAPTAIN,
    /* 0x7D */ GI_MASK_GIANT,
    /* 0x7E */ GI_MASK_ALL_NIGHT,
    /* 0x7F */ GI_MASK_BUNNY,
    /* 0x80 */ GI_MASK_KEATON,
    /* 0x81 */ GI_MASK_GARO,
    /* 0x82 */ GI_MASK_ROMANI,
    /* 0x83 */ GI_MASK_CIRCUS_LEADER,
    /* 0x84 */ GI_MASK_POSTMAN,
    /* 0x85 */ GI_MASK_COUPLE,
    /* 0x86 */ GI_MASK_GREAT_FAIRY,
    /* 0x87 */ GI_MASK_GIBDO,
    /* 0x88 */ GI_MASK_DON_GERO,
    /* 0x89 */ GI_MASK_KAMARO,
    /* 0x8A */ GI_MASK_TRUTH,
    /* 0x8B */ GI_MASK_STONE,
    /* 0x8C */ GI_MASK_BREMEN,
    /* 0x8D */ GI_MASK_BLAST,
    /* 0x8E */ GI_MASK_SCENTS,
    /* 0x8F */ GI_MASK_KAFEIS_MASK,
    /* 0x91 */ GI_CHATEAU = 0x91,
    /* 0x92 */ GI_MILK,
    /* 0x93 */ GI_GOLD_DUST_2,
    /* 0x94 */ GI_HYLIAN_LOACH, // Unused bottled eel
    /* 0x95 */ GI_SEAHORSE_CAUGHT,
    /* 0x96 */ GI_MOON_TEAR,
    /* 0x97 */ GI_DEED_LAND,
    /* 0x98 */ GI_DEED_SWAMP,
    /* 0x99 */ GI_DEED_MOUNTAIN,
    /* 0x9A */ GI_DEED_OCEAN,
    /* 0x9B */ GI_SWORD_GREAT_FAIRY_STOLEN,
    /* 0x9C */ GI_SWORD_KOKIRI_STOLEN,
    /* 0x9D */ GI_SWORD_RAZOR_STOLEN,
    /* 0x9E */ GI_SWORD_GILDED_STOLEN,
    /* 0x9F */ GI_SHIELD_HERO_STOLEN, // Code that treats this as hero's shield is unused, implied as intended to be stolen
    /* 0xA0 */ GI_ROOM_KEY,
    /* 0xA1 */ GI_LETTER_TO_MAMA,
    /* 0xA9 */ GI_BOTTLE_STOLEN = 0xA9, // buy back stolen bottle
    /* 0xAA */ GI_LETTER_TO_KAFEI,
    /* 0xAB */ GI_PENDANT_OF_MEMORIES,
    /* 0xB4 */ GI_TINGLE_MAP_CLOCK_TOWN = 0xB4,
    /* 0xB5 */ GI_TINGLE_MAP_WOODFALL,
    /* 0xB6 */ GI_TINGLE_MAP_SNOWHEAD,
    /* 0xB7 */ GI_TINGLE_MAP_ROMANI_RANCH,
    /* 0xB8 */ GI_TINGLE_MAP_GREAT_BAY,
    /* 0xB9 */ GI_TINGLE_MAP_STONE_TOWER,
    /* 0xBA */ GI_MAX
} GetItemId;

typedef enum {
    /* 0x00 */ GID_BOTTLE,
    /* 0x01 */ GID_KEY_SMALL,
    /* 0x02 */ GID_MASK_KAMARO,
    /* 0x03 */ GID_MASK_COUPLE,
    /* 0x04 */ GID_04,
    /* 0x05 */ GID_05,
    /* 0x06 */ GID_06,
    /* 0x07 */ GID_07,
    /* 0x08 */ GID_RECOVERY_HEART,
    /* 0x09 */ GID_KEY_BOSS,
    /* 0x0A */ GID_COMPASS,
    /* 0x0B */ GID_BOMBERS_NOTEBOOK,
    /* 0x0C */ GID_MASK_STONE,
    /* 0x0D */ GID_MASK_KAFEIS_MASK,
    /* 0x0E */ GID_MASK_CIRCUS_LEADER,
    /* 0x0F */ GID_MASK_BREMEN,
    /* 0x10 */ GID_MASK_ALL_NIGHT,
    /* 0x11 */ GID_NUTS,
    /* 0x12 */ GID_HEART_CONTAINER,
    /* 0x13 */ GID_HEART_PIECE,
    /* 0x14 */ GID_QUIVER_30,
    /* 0x15 */ GID_QUIVER_40,
    /* 0x16 */ GID_QUIVER_50,
    /* 0x17 */ GID_BOMB_BAG_20,
    /* 0x18 */ GID_BOMB_BAG_30,
    /* 0x19 */ GID_BOMB_BAG_40,
    /* 0x1A */ GID_STICK,
    /* 0x1B */ GID_DUNGEON_MAP,
    /* 0x1C */ GID_MAGIC_SMALL,
    /* 0x1D */ GID_MAGIC_LARGE,
    /* 0x1E */ GID_BOMB,
    /* 0x1F */ GID_STONE_OF_AGONY,
    /* 0x20 */ GID_WALLET_ADULT,
    /* 0x21 */ GID_WALLET_GIANT,
    /* 0x22 */ GID_MASK_DON_GERO,
    /* 0x23 */ GID_ARROWS_SMALL,
    /* 0x24 */ GID_ARROWS_MEDIUM,
    /* 0x25 */ GID_ARROWS_LARGE,
    /* 0x26 */ GID_BOMBCHU,
    /* 0x27 */ GID_SHIELD_HERO,
    /* 0x28 */ GID_HOOKSHOT,
    /* 0x29 */ GID_29,
    /* 0x2A */ GID_OCARINA,
    /* 0x2B */ GID_MILK,
    /* 0x2C */ GID_MASK_KEATON,
    /* 0x2D */ GID_TINGLE_MAP,
    /* 0x2E */ GID_BOW,
    /* 0x2F */ GID_LENS,
    /* 0x30 */ GID_POTION_GREEN,
    /* 0x31 */ GID_POTION_RED,
    /* 0x32 */ GID_POTION_BLUE,
    /* 0x33 */ GID_SHIELD_MIRROR,
    /* 0x34 */ GID_MAGIC_BEANS,
    /* 0x35 */ GID_FISH,
    /* 0x36 */ GID_LETTER_MAMA,
    /* 0x37 */ GID_37,
    /* 0x38 */ GID_SWORD_BGS,
    /* 0x39 */ GID_MASK_SUN,
    /* 0x3A */ GID_MASK_BLAST,
    /* 0x3B */ GID_FAIRY,
    /* 0x3C */ GID_MASK_SCENTS,
    /* 0x3D */ GID_MASK_CAPTAIN,
    /* 0x3E */ GID_MASK_BUNNY,
    /* 0x3F */ GID_MASK_TRUTH,
    /* 0x40 */ GID_DEED_SWAMP,
    /* 0x41 */ GID_DEED_MOUNTAIN,
    /* 0x42 */ GID_RUPEE_HUGE,
    /* 0x43 */ GID_DEED_OCEAN,
    /* 0x44 */ GID_MASK_GORON,
    /* 0x45 */ GID_MASK_ZORA,
    /* 0x46 */ GID_46,
    /* 0x47 */ GID_ARROW_FIRE,
    /* 0x48 */ GID_ARROW_ICE,
    /* 0x49 */ GID_ARROW_LIGHT,
    /* 0x4A */ GID_SKULL_TOKEN,
    /* 0x4B */ GID_BUG,
    /* 0x4C */ GID_4C,
    /* 0x4D */ GID_POE,
    /* 0x4E */ GID_FAIRY_2,
    /* 0x4F */ GID_RUPEE_GREEN,
    /* 0x50 */ GID_RUPEE_BLUE,
    /* 0x51 */ GID_RUPEE_RED,
    /* 0x52 */ GID_BIG_POE,
    /* 0x53 */ GID_RUPEE_PURPLE,
    /* 0x54 */ GID_RUPEE_SILVER,
    /* 0x55 */ GID_SWORD_KOKIRI,
    /* 0x56 */ GID_SKULL_TOKEN_2,
    /* 0x57 */ GID_57,
    /* 0x58 */ GID_ZORA_EGG,
    /* 0x59 */ GID_MOON_TEAR,
    /* 0x5A */ GID_DEED_LAND,
    /* 0x5B */ GID_MASK_DEKU,
    /* 0x5C */ GID_REMAINS_ODOLWA,
    /* 0x5D */ GID_POWDER_KEG,
    /* 0x5E */ GID_GOLD_DUST,
    /* 0x5F */ GID_SEAHORSE,
    /* 0x60 */ GID_60,
    /* 0x61 */ GID_HYLIAN_LOACH,
    /* 0x62 */ GID_SEAHORSE_CAUGHT,
    /* 0x63 */ GID_REMAINS_GOHT,
    /* 0x64 */ GID_REMAINS_GYORG,
    /* 0x65 */ GID_REMAINS_TWINMOLD,
    /* 0x66 */ GID_SWORD_RAZOR,
    /* 0x67 */ GID_SWORD_GILDED,
    /* 0x68 */ GID_SWORD_GREAT_FAIRY,
    /* 0x69 */ GID_MASK_GARO,
    /* 0x6A */ GID_MASK_GREAT_FAIRY,
    /* 0x6B */ GID_MASK_GIBDO,
    /* 0x6C */ GID_ROOM_KEY,
    /* 0x6D */ GID_LETTER_TO_KAFEI,
    /* 0x6E */ GID_PENDANT_OF_MEMORIES,
    /* 0x6F */ GID_MUSHROOM,
    /* 0x70 */ GID_MASK_ROMANI,
    /* 0x71 */ GID_MASK_POSTMAN,
    /* 0x72 */ GID_MASK_GIANT,
    /* 0x73 */ GID_CHATEAU,
    /* 0x74 */ GID_PICTO_BOX,
    /* 0x75 */ GID_MASK_FIERCE_DEITY,
    /* 0x76 */ GID_MAX
} GetItemDrawId;

#endif
