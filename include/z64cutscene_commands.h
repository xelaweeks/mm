#ifndef Z64CUTSCENE_COMMANDS_H
#define Z64CUTSCENE_COMMANDS_H

#include "command_macros_base.h"
#include "z64cutscene.h"

/**
 * ARGS
 *   s32 totalEntries (e), s32 endFrame (n)
 * FORMAT
 *   eeeeeeee nnnnnnnn
 *   size = 0x8
 */
#define CS_BEGIN_CUTSCENE(totalEntries, endFrame) CMD_W(totalEntries), CMD_W(endFrame)

/**
 * ARGS
 *   s32 entries (e)
 * FORMAT
 *   00000013 eeeeeeee
 *   size = 0x8
 */
#define CS_TEXT_LIST(entries) CS_CMD_TEXTBOX, CMD_W(entries)


#if 0
/**
 * ARGS
 *   s16 messageId (i), s16 startFrame (s), s16 endFrame (e), s16 type (o), 
 *   s16 topOptionBranch (y), s16 bottomOptionBranch (n)
 * FORMAT
 *   iiiissss eeeeoooo yyyynnnn
 *   size = 0xC
 */
#define CS_TEXT_DISPLAY_TEXTBOX(messageId, startFrame, endFrame, type, topOptionBranch, bottomOptionBranch) \
    CMD_HH(messageId, startFrame), CMD_HH(endFrame, type), CMD_HH(topOptionBranch, bottomOptionBranch)

/**
 * ARGS
 *   s16 startFrame (s), s16 endFrame (e)
 * FORMAT
 *   FFFFssss eeeeFFFF FFFFFFFF
 *   size = 0xC
 */
#define CS_TEXT_NONE(startFrame, endFrame) \
    CS_TEXT_DISPLAY_TEXTBOX(0xFFFF, startFrame, endFrame, 0xFFFF, 0xFFFF, 0xFFFF)

/**
 * ARGS
 *   s16 ocarinaSongAction (o), s16 startFrame (s), s16 endFrame (e), s16 topOptionBranch (i)
 * FORMAT
 *   oooossss eeee0002 iiiiFFFF
 *   size = 0xC
 */
#define CS_TEXT_LEARN_SONG(ocarinaSongAction, startFrame, endFrame, messageId) \
    CS_TEXT_DISPLAY_TEXTBOX(ocarinaSongAction, startFrame, endFrame, 0x0002, messageId, 0xFFFF)

#endif




/**
 * ARGS
 *   s32 entries (e)
 * FORMAT
 *   00000003 eeeeeeee
 *   size = 0x8
 */
#define CS_CMD_UNK_5A_LIST(entries) CS_CMD_5A, CMD_W(entries)







/**
 * ARGS
 *   s32 entries (e)
 * FORMAT
 *   00000003 eeeeeeee
 *   size = 0x8
 */
#define CS_MISC_LIST(entries) CS_CMD_MISC, CMD_W(entries)

/**
 * ARGS
 *   s16 unk (u), s16 startFrame (s), s16 endFrame (e)
 * FORMAT
 *   Capital U is Unused
 *   uuuussss eeeeUUUU
 *   size = 0x30
 */
#define CS_MISC(unk, startFrame, endFrame, unused0) \
    CMD_HH(unk, startFrame), CMD_HH(endFrame, unused0)



/**
 * ARGS
 *   s32 entries (e)
 * FORMAT
 *   00000004 eeeeeeee
 *   size = 0x8
 */
#define CS_LIGHTING_LIST(entries) CS_CMD_SET_LIGHTING, CMD_W(entries)

/**
 * ARGS
 *   s16 setting (m), s16 startFrame (s), s16 endFrame (e)
 * FORMAT
 *   Capital U is Unused
 *   mmmmssss eeeeUUUU
 *   size = 0x30
 */
#define CS_LIGHTING(setting, startFrame, endFrame, unused0) \
    CMD_HH(setting, startFrame), CMD_HH(endFrame, unused0)





/**
 * ARGS
 *   s32 entries (e)
 * FORMAT
 *   00000004 eeeeeeee
 *   size = 0x8
 */
#define CS_SCENE_TRANS_FX_LIST(entries) CS_CMD_SCENE_TRANS_FX, CMD_W(entries)

/**
 * ARGS
 *   
 * FORMAT
 *   Capital U is Unused
 *   mmmmssss eeeeUUUU
 *   size = 0x30
 */
#define CS_SCENE_TRANS_FX(transitionType, startFrame, endFrame, unused0) \
    CMD_HH(transitionType, startFrame), CMD_HH(endFrame, unused0)






/**
 * ARGS
 *   s32 entries (e)
 * FORMAT
 *   00000004 eeeeeeee
 *   size = 0x8
 */
#define CS_SCENE_UNK_99_LIST(entries) CS_CMD_99, CMD_W(entries)

/**
 * ARGS
 *   
 * FORMAT
 *   Capital U is Unused
 *   mmmmssss eeeeUUUU
 *   size = 0x30
 */
#define CS_SCENE_UNK_99(base, startFrame, endFrame, unused0) \
    CMD_HH(base, startFrame), CMD_HH(endFrame, unused0)





/**
 * ARGS
 *   s32 entries (e)
 * FORMAT
 *   0000009A eeeeeeee
 *   size = 0x8
 */
#define CS_GIVETATL_LIST(entries) CS_CMD_GIVETATL, CMD_W(entries)

/**
 * ARGS
 *   
 * FORMAT
 *   
 */
#define CS_GIVETATL(unk, startFrame, endFrame, unk_06) \
    CMD_HH(unk, startFrame), CMD_HH(endFrame, unk_06)







/**
 * ARGS
 *   s32 entries (e)
 * FORMAT
 *   00000004 eeeeeeee
 *   size = 0x8
 */
#define CS_SCENE_UNK_9B_LIST(entries) CS_CMD_9B, CMD_W(entries)

/**
 * ARGS
 *   
 * FORMAT
 *   Capital U is Unused
 *   mmmmssss eeeeUUUU
 *   size = 0x30
 */
#define CS_SCENE_UNK_9B(base, startFrame, endFrame, unk6, unk7, unk8) \
    CMD_HH(base, startFrame), CMD_HBB(endFrame, unk6, unk7), CMD_BBBB(unk8, 0, 0, 0)






/**
 * ARGS
 *   s32 entries (e)
 * FORMAT
 *   00000004 eeeeeeee
 *   size = 0x8
 */
#define CS_FADESEQ_LIST(entries) CS_CMD_FADESEQ, CMD_W(entries)

/**
 * ARGS
 *   
 * FORMAT
 *   Capital U is Unused
 *   mmmmssss eeeeUUUU
 *   size = 0x30
 */
#define CS_FADESEQ(base, startFrame, endFrame, unk_06, unk_08) \
    CMD_HH(base, startFrame), CMD_HH(endFrame, unk_06), CMD_W(unk_08)







/**
 * ARGS
 *   s32 entries (e)
 * FORMAT
 *   0000008C eeeeeeee
 *   size = 0x8
 */
#define CS_TIME_LIST(entries) CS_CMD_SETTIME, CMD_W(entries)

/**
 * ARGS
 *   s16 unk (u), s16 startFrame (s), s16 endFrame (e), s8 hour (h), s8 min (m)
 * FORMAT
 *   Capital U is Unused
 *   uuuussss eeeehhmm UUUUUUUU
 *   size = 0xC
 */
#define CS_TIME(unk, startFrame, endFrame, hour, min, unused) \
    CMD_HH(unk, startFrame), \
    CMD_HBB(endFrame, hour, min), \
    CMD_W(unused)





/**
 * ARGS
 *   s32 cmdType (c), s32 entries (e)
 * FORMAT
 *   cccccccc eeeeeeee
 *   size = 0x8
 */
#define CS_NPC_ACTION_LIST(cmdType, entries) CMD_W(cmdType), CMD_W(entries)

/**
 * ARGS
 *   s16 npcAction (a), s16 startFrame (s), s16 endFrame (e),
 *   s16 rotX (u),      s16 rotY (v),       s16 rotZ (w),
 *   s32 startX (i),    s32 startY (j),     s32 startZ (k),
 *   s32 endX (l),      s32 endY (m),       s32 endZ (n),
 *   s32 normX (x),     s32 normY (y),      s32 normZ (z),
 * FORMAT
 *   aaaassss eeeeuuuu vvvvwwww iiiiiiii jjjjjjjj kkkkkkkk llllllll mmmmmmmm nnnnnnnn xxxxxxxx yyyyyyyy zzzzzzzz
 *   size = 0x30
 */
#define CS_NPC_ACTION(npcAction, startFrame, endFrame, rotX, rotY, rotZ, startX, startY, startZ, endX, endY, endZ, normX, normY, normZ) \
    CMD_HH(npcAction, startFrame), CMD_HH(endFrame, rotX), CMD_HH(rotY, rotZ), \
    CMD_W(startX), CMD_W(startY), CMD_W(startZ), \
    CMD_W(endX), CMD_W(endY), CMD_W(endZ), \
    CMD_W(normX), CMD_W(normY), CMD_W(normZ)

#if 0
/**
 * ARGS
 *   s32 cmdType (c), s32 entries (e)
 * FORMAT
 *   cccccccc eeeeeeee
 *   size = 0x8
 */
#define CS_PLAYER_ACTION_LIST(entries) CS_CMD_SET_PLAYER_ACTION, CMD_W(entries)

/**
 * ARGS
 *   s16 linkAction (a), s16 startFrame (s), s16 endFrame (e),
 *   s16 rotX (u),       s16 rotY (v),       s16 rotZ (w),
 *   s32 startX (i),     s32 startY (j),     s32 startZ (k),
 *   s32 endX (l),       s32 endY (m),       s32 endZ (n),
 *   s32 normX (x),      s32 normY (y),      s32 normZ (z),
 * FORMAT
 *   aaaassss eeeeuuuu vvvvwwww iiiiiiii jjjjjjjj kkkkkkkk llllllll mmmmmmmm nnnnnnnn xxxxxxxx yyyyyyyy zzzzzzzz
 *   size = 0x30
 */
#define CS_PLAYER_ACTION(linkAction, startFrame, endFrame, rotX, rotY, rotZ, startX, startY, startZ, endX, endY, endZ, normX, normY, normZ) \
    CS_NPC_ACTION(linkAction, startFrame, endFrame, rotX, rotY, rotZ, startX, startY, startZ, endX, endY, endZ, normX, normY, normZ)

#endif






/**
 * ARGS
 *   s32 entries (e)
 * FORMAT
 *   00000004 eeeeeeee
 *   size = 0x8
 */
#define CS_PLAYSEQ_LIST(entries) CS_CMD_PLAYSEQ, CMD_W(entries)

/**
 * ARGS
 *   
 * FORMAT
 *   Capital U is Unused
 *   mmmmssss eeeeUUUU
 *   size = 0x30
 */
#define CS_PLAYSEQ(base, startFrame, endFrame, unk_06) \
    CMD_HH(base, startFrame), CMD_HH(endFrame, unk_06)








/**
 * ARGS
 *   s32 entries (e)
 * FORMAT
 *   00000004 eeeeeeee
 *   size = 0x8
 */
#define CS_SCENE_UNK_130_LIST(entries) CS_CMD_130, CMD_W(entries)

/**
 * ARGS
 *   
 * FORMAT
 *   Capital U is Unused
 *   mmmmssss eeeeUUUU
 *   size = 0x30
 */
#define CS_SCENE_UNK_130(base, startFrame, endFrame, unk_06) \
    CMD_HH(base, startFrame), CMD_HH(endFrame, unk_06)




/**
 * ARGS
 *   s32 entries (e)
 * FORMAT
 *   00000004 eeeeeeee
 *   size = 0x8
 */
#define CS_SCENE_UNK_131_LIST(entries) CS_CMD_131, CMD_W(entries)

/**
 * ARGS
 *   
 * FORMAT
 *   Capital U is Unused
 *   mmmmssss eeeeUUUU
 *   size = 0x30
 */
#define CS_SCENE_UNK_131(base, startFrame, endFrame, unk_06) \
    CMD_HH(base, startFrame), CMD_HH(endFrame, unk_06)




/**
 * ARGS
 *   s32 entries (e)
 * FORMAT
 *   00000004 eeeeeeee
 *   size = 0x8
 */
#define CS_SCENE_UNK_132_LIST(entries) CS_CMD_132, CMD_W(entries)

/**
 * ARGS
 *   
 * FORMAT
 *   Capital U is Unused
 *   mmmmssss eeeeUUUU
 *   size = 0x30
 */
#define CS_SCENE_UNK_132(base, startFrame, endFrame, unk_06) \
    CMD_HH(base, startFrame), CMD_HH(endFrame, unk_06)









/**
 * ARGS
 *   s32 entries (e)
 * FORMAT
 *   00000004 eeeeeeee
 *   size = 0x8
 */
#define CS_STOPSEQ_LIST(entries) CS_CMD_STOPSEQ, CMD_W(entries)

/**
 * ARGS
 *   
 * FORMAT
 *   Capital U is Unused
 *   mmmmssss eeeeUUUU
 *   size = 0x30
 */
#define CS_STOPSEQ(base, startFrame, endFrame, unk_06) \
    CMD_HH(base, startFrame), CMD_HH(endFrame, unk_06)











/**
 * ARGS
 *   s32 entries (e)
 * FORMAT
 *   00000004 eeeeeeee
 *   size = 0x8
 */
#define CS_PLAYAMBIENCE_LIST(entries) CS_CMD_PLAYAMBIENCE, CMD_W(entries)

/**
 * ARGS
 *   
 * FORMAT
 *   Capital U is Unused
 *   mmmmssss eeeeUUUU
 *   size = 0x30
 */
#define CS_PLAYAMBIENCE(base, startFrame, endFrame, unk_06) \
    CMD_HH(base, startFrame), CMD_HH(endFrame, unk_06)







/**
 * ARGS
 *   s32 entries (e)
 * FORMAT
 *   00000004 eeeeeeee
 *   size = 0x8
 */
#define CS_FADEAMBIENCE_LIST(entries) CS_CMD_FADEAMBIENCE, CMD_W(entries)

/**
 * ARGS
 *   
 * FORMAT
 *   Capital U is Unused
 *   mmmmssss eeeeUUUU
 *   size = 0x30
 */
#define CS_FADEAMBIENCE(base, startFrame, endFrame, unk_06) \
    CMD_HH(base, startFrame), CMD_HH(endFrame, unk_06)








/**
 * ARGS
 *   s32 entries (e)
 * FORMAT
 *   00000004 eeeeeeee
 *   size = 0x8
 */
#define CS_SCENE_UNK_15E_LIST(entries) CS_CMD_15E, CMD_W(entries)

/**
 * ARGS
 *   
 * FORMAT
 *   Capital U is Unused
 *   mmmmssss eeeeUUUU
 *   size = 0x30
 */
#define CS_SCENE_UNK_15E(base, startFrame, endFrame, unk_06) \
    CMD_HH(base, startFrame), CMD_HH(endFrame, unk_06)





/**
 * ARGS
 *   s32 entries (e)
 * FORMAT
 *   00000004 eeeeeeee
 *   size = 0x8
 */
#define CS_SCENE_UNK_15F_LIST(entries) CS_CMD_15F, CMD_W(entries)

/**
 * ARGS
 *   
 * FORMAT
 *   Capital U is Unused
 *   mmmmssss eeeeUUUU
 *   size = 0x30
 */
#define CS_SCENE_UNK_15F(base, startFrame, endFrame, unk_06) \
    CMD_HH(base, startFrame), CMD_HH(endFrame, unk_06)








/**
 * ARGS
 *   s32 entries (e)
 * FORMAT
 *   00000004 eeeeeeee
 *   size = 0x8
 */
#define CS_SCENE_UNK_190_LIST(entries) CS_CMD_190, CMD_W(entries)

/**
 * ARGS
 *   
 * FORMAT
 *   Capital U is Unused
 *   mmmmssss eeeeUUUU
 *   size = 0x30
 */
#define CS_SCENE_UNK_190(base, startFrame, endFrame, unk6, unk7, unk8) \
    CMD_HH(base, startFrame), CMD_HBB(endFrame, unk6, unk7), CMD_BBBB(unk8, 0, 0, 0)







/**
 * Marks the end of a cutscene
 */
#define CS_END() CMD_W(0xFFFFFFFF)

#endif
