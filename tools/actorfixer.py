#!/usr/bin/env python3

import argparse, os

# "old": "new"
animdict ={
    "Actor_GetSwitchFlag": "Flags_GetSwitch",
    "atan_flip": "Math_Acot2F",
    "atans": "Math_Atan2S",
    "Matrix_Pop": "SysMatrix_StatePop",
    "Matrix_Push": "SysMatrix_StatePush",
    "Matrix_Init": "SysMatrix_StateAlloc",
    "Matrix_Put": "SysMatrix_SetCurrentState",
    "func_800B78B8": "Actor_UpdateBgCheckInfo",
    "func_8012403C": "Player_GetMask",
    "func_8012404c": "Player_RemoveMask",
    "Actor_SpawnWithParentAndCutscene": "Actor_SpawnAsChildAndCutscene",
    "Actor_SpawnWithParent": "Actor_SpawnAsChild",
    "Actor_IsLinkFacingActor": "Actor_IsPlayerFacingActor",
    "Actor_IsActorFacingLink": "Actor_IsActorFacingPlayer",
    "Actor_IsActorFacingLinkAndWithinRange": "Actor_IsActorFacingPlayerAndWithinRange",
    "func_800B84D0": "Actor_RequestTalk",
    "func_8017D668": "Math3D_PointDistToLine2D",
    "func_800BDFC0": "Gfx_DrawDListOpa",
    "func_800BE03C": "Gfx_DrawDListXlu",
    "func_800B6FC8": "Player_GetHeight",
    "Actor_InitCurrPosition": "Actor_SetWorldToHome",
    "Actor_SetHeight": "Actor_SetFocus",
    "Actor_SetRotationFromDrawRotation": "Actor_SetWorldRotToShape",
    "Actor_InitDrawRotation": "Actor_SetShapeRotToWorld",
    "Actor_SetVelocityAndMoveYRotationAndGravity": "Actor_MoveForward",
    "func_800B81E0": "Actor_GetFocus",
    "func_800B8214": "Actor_GetWorld",
    "func_800B8248": "Actor_GetWorldPosShapeRot",
    "func_800BE22C": "Actor_ApplyDamage",
    "func_800F0568": "Audio_PlaySoundAtPosition",
    "func_8016970C": "Play_CameraSetAtEye",
    "func_800BBA88": "Enemy_StartFinishingBlow",
    "ShrinkWindow_Step": "ShrinkWindow_Update",
    "ShrinkWindow_Fini": "ShrinkWindow_Destroy",
    "func_801A89A8": "Audio_QueueSeqCmd",
    "Actor_SetObjectSegment": "Actor_SetObjectDependency",
    "func_800B3FC0": "ActorShadow_DrawCircle",
    "func_800B4024": "ActorShadow_DrawSquare",
    "func_800B4088": "ActorShadow_DrawWhiteCircle",
    "func_800B40B8": "ActorShadow_DrawHorse",
    "func_800B40E0": "ActorShadow_DrawFoot",
    "func_800B42F8": "ActorShadow_DrawFeet",
    "func_800B4A98": "Actor_SetFeetPos",
    "Actor_SetSwitchFlag": "Flags_SetSwitch",
    "Actor_UnsetSwitchFlag": "Flags_UnsetSwitch",
    "Actor_GetChestFlag": "Flags_GetTreasure",
    "Actor_SetChestFlag": "Flags_SetTreasure",
    "Actor_SetAllChestFlag": "Flags_SetAllTreasure",
    "Actor_GetAllChestFlag": "Flags_GetAllTreasure",
    "Actor_GetRoomCleared": "Flags_GetClear",
    "Actor_SetRoomCleared": "Flags_SetClear",
    "Actor_UnsetRoomCleared": "Flags_UnsetClear",
    "Actor_GetRoomClearedTemp": "Flags_GetTempClear",
    "Actor_SetRoomClearedTemp": "Flags_SetTempClear",
    "Actor_UnsetRoomClearedTemp": "Flags_UnsetTempClear",
    "Actor_GetCollectibleFlag": "Flags_GetCollectible",
    "Actor_SetCollectibleFlag": "Flags_SetCollectible",
    "func_800B8A1C": "Actor_PickUp",
    "func_800B8B84": "Actor_PickUpNearby",
    "func_800B8BB0": "Actor_LiftActor",
    "func_800B8BD0": "Actor_PickUpFar",
    "func_801A5CFC": "Audio_PlaySoundGeneral",
    "func_800BBDAC": "Actor_SpawnFloorDustRing",
    "func_800B8708": "Player_GetExchangeItemId",
    "func_801233E4": "Player_InCsMode",
}

def replace_anim(file):
    with open(file, 'r', encoding='utf-8') as infile:
        srcdata = infile.read()

    funcs = list(animdict.keys())
    fixes = 0
    for func in funcs:
        newfunc = animdict.get(func)
        if(newfunc is None):
            print("How did this happen?")
            return -1
        if(func in srcdata):
            fixes += 1
            print(func)
            srcdata = srcdata.replace(func, newfunc)

    if(fixes > 0):
        print('Changed', fixes,'entr' + ('y' if fixes == 1 else 'ies') + ' in',file)
        with open(file, 'w', encoding = 'utf-8', newline = '\n') as outfile:
            outfile.write(srcdata)
    return 1

def replace_anim_all(repo):
    for subdir, dirs, files in os.walk(repo + os.sep + 'src'):
        for filename in files:
            if(filename.endswith('.c')):
                file = subdir + os.sep + filename
                replace_anim(file)
    for subdir, dirs, files in os.walk(repo + os.sep + 'asm'):
        for filename in files:
            if(filename.endswith('.s')):
                file = subdir + os.sep + filename
                replace_anim(file)
    return 1

parser = argparse.ArgumentParser(description='Update to the new animation names')
parser.add_argument('file', help="source file to be processed. use . to process the whole repo", default = None)

if __name__ == "__main__":
    args = parser.parse_args()
    if(args.file == '.'):
        replace_anim_all(os.curdir)
    else:
        replace_anim(args.file)
