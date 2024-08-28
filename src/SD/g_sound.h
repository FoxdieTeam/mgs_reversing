#ifndef _G_SOUND_H_
#define _G_SOUND_H_

#define SE_DUMMY        (  0)
#define SE_SHOT_01      (  1)   //
#define SE_STEPL01      (  2)   //
#define SE_STEPR01      (  3)   //
#define SE_KARASHT1     (  4)   //
#define SE_KARASHT      SE_KARASHT1
#define SE_HOHUKU03     (  5)   // ほふく
#define SE_HOHUKU04     (  6)   // ほふく
#define SE_SENAKA01     (  7)   // 背中
#define SE_STAND01      (  8)   //
#define SE_KAMAE01      (  9)   // 構える
#define SE_HEART01      ( 10)   //
#define SE_FULL0005     ( 11)   //
#define SE_KAIHUKU1     ( 12)   // 回復
#define SE_ITEM0003     ( 13)   //
#define SE_RADAR001     ( 14)   //
#define SE_OVER03       ( 15)   // GAME OVER
#define SE_UNK016       ( 16)   //
#define SE_UNK017       ( 17)   //
#define SE_POUT0003     ( 18)   // PLAYER OUT
#define SE_SNEEZE01     ( 19)   //
#define SE_IDEC03       ( 20)   //
#define SE_IDISP02      ( 21)   //
#define SE_IGET01       ( 22)   //
#define SE_UNK023       ( 23)   //
#define SE_UNK024       ( 24)   //
#define SE_UNK025       ( 25)   //
#define SE_POUT0001     ( 26)   // PLAYER OUT
#define SE_RIFLE01      ( 27)   //
#define SE_STEP02       ( 28)   //
#define SE_MOUSTEP2     ( 29)   //
#define SE_WSTEP01      ( 30)   //
#define SE_CUR01        ( 31)   //
#define SE_WIN01        ( 32)   //
#define SE_START01      ( 33)   //
#define SE_IDEC02       ( 34)   //
#define SE_BUZZER01     ( 35)   //
#define SE_ZOOM01       ( 36)   //
#define SE_ATARU01      ( 37)   //
#define SE_EDMG01       ( 38)   //
#define SE_REB01        ( 39)   //
#define SE_REBDRM01     ( 40)   //
#define SE_EXP_05       ( 41)   //
#define SE_SIREN0600    ( 42)   //
#define SE_BOUND02      ( 43)   //
#define SE_PIN01        ( 44)   //
#define SE_PINNUKI      SE_PIN01
#define SE_SHOT_E03     ( 45)   //
#define SE_SHOT_E02     ( 46)   //
#define SE_RELOAD01     ( 47)   //
#define SE_UNK048       ( 48)   //
#define SE_C4PUT01      ( 49)   //
#define SE_C4SW01       ( 50)   //
#define SE_DOWN0002     ( 51)   //
#define SE_PUNCHIT1     ( 52)   //
#define SE_KICKHIT1     ( 53)   //
#define SE_ISEL0003     ( 54)   //
#define SE_WALL02       ( 55)   //
#define SE_P_SWING1     ( 56)   //
#define SE_K_SWING1     ( 57)   //
#define SE_CHAF0003     ( 58)   //
#define SE_HIBANA01     ( 59)   // 火花
#define SE_UNK060       ( 60)   //
#define SE_UNK061       ( 61)   //
#define SE_REBGLASS     ( 62)   //
#define SE_GLASS11      ( 63)   //
#define SE_UNK064       ( 64)   //
#define SE_BAKUHA01     ( 65)   // 爆破
#define SE_CHAF0002     ( 66)   //
#define SE_BACKCLS1     ( 67)   //
#define SE_BACKCLS2     ( 68)   //
#define SE_DUMMY_069    ( 69)   //
#define SE_DUMMY_070    ( 70)   //
#define SE_DUMMY_071    ( 71)   //
#define SE_UNK072       ( 72)   //
#define SE_SHOT_M02     ( 73)   //
#define SE_FACECHG1     ( 74)   //
#define SE_RUN00001     ( 75)   //
#define SE_UNK076       ( 76)   //
#define SE_UNK077       ( 77)   //
#define SE_NINJA01      ( 78)   //
#define SE_UNK079       ( 79)   //
#define SE_NINJA02      ( 80)   //
#define SE_HIZA01       ( 81)   //
#define SE_UNK082       ( 82)   //
#define SE_UNK083       ( 83)   //
#define SE_R_WINDW1     ( 84)   //
#define SE_R_SEL01      ( 85)   //
#define SE_R_SND01      ( 86)   //
#define SE_R_WINDW2     ( 87)   //
#define SE_DCLOSE03     ( 88)   //
#define SE_DCLOSE04     ( 89)   //
#define SE_DCLOSE05     ( 90)   //
#define SE_DOPEN03      ( 91)   //
#define SE_DOPEN04      ( 92)   //
#define SE_DOPEN05      ( 93)   //
#define SE_CAMERA07     ( 94)   //
#define SE_CAMERA03     ( 95)   //
#define SE_BUTTON01     ( 96)   //
#define SE_ELECLS03     ( 97)   //
#define SE_ELEOPN03     ( 98)   //
#define SE_SIGHT08      ( 99)   //
#define SE_INELEV02     (100)   //
#define SE_UNK101       (101)   //
#define SE_START001     (102)   //
#define SE_R_TUNE01     (103)   //
#define SE_R_CANCEL     (104)   //
#define SE_R_CURSOR     (105)   //
#define SE_O2DAMAGE     (106)   //
#define SE_POUT0002     (107)   // PLAYER OUT
#define SE_R_NOISE1     (108)   //
#define SE_CAMERA06     (109)   //
#define SE_SHATTR04     (110)   // SHUTTER
#define SE_SHATTR06     (111)   // SHUTTER
#define SE_EL_CHM02     (112)   // EV.CHIME
#define SE_ELSTOP06     (113)   // EV.STOP
#define SE_MASK0002     (114)   //
#define SE_RATION01     (115)   //
#define SE_SIGNAL02     (116)   //
#define SE_CLOCK001     (117)   //
#define SE_MMASK001     (118)   //
#define SE_SIGNAL04     (119)   //
#define SE_RADAR003     (120)   //
#define SE_JINGLE01     (121)   //
#define SE_JINGLE02     (122)   //
#define SE_CHR_DSP1     (123)   //
#define SE_SHATTR0B     (124)   // SHUTTER
#define SE_MENUOPN1     (125)   //
#define SE_KAIHUKU4     (126)   // 回復
#define SE_IDEC04       (127)   //
#define SE_TBL_MAX      (128)

#endif // _G_SOUND_H_
