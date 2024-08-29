#ifndef _G_SOUND_H_
#define _G_SOUND_H_

#define SE_DUMMY        (  0)
#define SE_SHOT_01      (  1)   // SOCOM gunshot
#define SE_STEPL01      (  2)   //
#define SE_STEPR01      (  3)   //
#define SE_KARASHT1     (  4)   //
#define SE_KARASHT      SE_KARASHT1
#define SE_HOHUKU03     (  5)   // 「ほふく」
#define SE_CRAWL03      SE_HOHUKU03
#define SE_HOHUKU04     (  6)   // 「ほふく」
#define SE_CRAWL04      SE_HOHUKU04
#define SE_SENAKA01     (  7)   // 「背中」
#define SE_WALLPRESS    SE_SENAKA01
#define SE_STAND01      (  8)   // change stance
#define SE_KAMAE01      (  9)   // 「構える」
#define SE_READYWEAPON  SE_KAMAE01
#define SE_HEART01      ( 10)   //
#define SE_FULL0005     ( 11)   //
#define SE_KAIHUKU1     ( 12)   // 「回復」 (recover LIFE)
#define SE_RECOVER_LIFE SE_KAIHUKU1
#define SE_ITEM0003     ( 13)   // spawn item
#define SE_RADAR001     ( 14)   // all-clear chime
#define SE_OVER03       ( 15)   // game over
#define SE_R_RCV01      ( 16)   // radio CALL (incoming)
#define SE_PHOTO        ( 17)   // photo shutter
#define SE_POUT0003     ( 18)   // player out (asphyxiation)
#define SE_SNEEZE01     ( 19)   //
#define SE_IDEC03       ( 20)   // "item decide" (equip/unequip)
#define SE_IDISP02      ( 21)   // "item display" (open window)
#define SE_IGET01       ( 22)   // "item get" 
#define SE_ISEL01       ( 23)   // item window move
#define SE_PDMG01       ( 24)   // player damage (light)
#define SE_PDMG02       ( 25)   // player damage (heavy)
#define SE_POUT0001     ( 26)   // player out (normal)
#define SE_RIFLE01      ( 27)   // PSG-1 gunshot
#define SE_STEP02       ( 28)   // hop down
#define SE_MOUSTEP2     ( 29)   //
#define SE_WSTEP01      ( 30)   // wet step
#define SE_CUR01        ( 31)   // menu cursor move
#define SE_WIN01        ( 32)   // menu select
#define SE_START01      ( 33)   // menu exit
#define SE_IDEC02       ( 34)   // "item decide" (use medicine)
#define SE_BUZZER01     ( 35)   // "NO USE" buzzer
#define SE_ZOOM01       ( 36)   //
#define SE_ATARU01      ( 37)   // 「あたる」 (hit)
#define SE_EDMG01       ( 38)   // "enemy damage"
#define SE_REB01        ( 39)   // bullet ricochet?
#define SE_REBDRM01     ( 40)   //
#define SE_EXP_05       ( 41)   // explosion
#define SE_SIREN0600    ( 42)   // alert siren
#define SE_BOUND02      ( 43)   // grenade collision
#define SE_PIN01        ( 44)   // grenade pin
#define SE_PINNUKI      SE_PIN01
#define SE_SHOT_E03     ( 45)   // enemy gunshot (FAMAS)
#define SE_SHOT_E02     ( 46)   // enemy gunshot (gun-camera)
#define SE_RELOAD01     ( 47)   //
#define SE_FAMAS01      ( 48)   // player gunshot (FAMAS)
#define SE_C4PUT01      ( 49)   // C4 placement
#define SE_C4SW01       ( 50)   // C4 detonator switch
#define SE_DOWN0002     ( 51)   // (let the bodies) hit the floor
#define SE_PUNCHIT1     ( 52)   // "punch hit"
#define SE_KICKHIT1     ( 53)   // "kick hit"
#define SE_ISEL0003     ( 54)   // "item select" (cursor move)
#define SE_WALL02       ( 55)   // wall-knock
#define SE_P_SWING1     ( 56)   // "punch swing"
#define SE_K_SWING1     ( 57)   // "kick swing"
#define SE_CHAF0003     ( 58)   // chaff particles
#define SE_HIBANA01     ( 59)   // 「火花」 (sparks)
#define SE_UNK060       ( 60)   // also sparks?
#define SE_UNK061       ( 61)   //
#define SE_REBGLASS     ( 62)   // broken glass
#define SE_GLASS11      ( 63)   // glass shatter
#define SE_UNK064       ( 64)   //
#define SE_BAKUHA01     ( 65)   // 「爆破」 (blast)
#define SE_CHAF0002     ( 66)   // chaff explosion
#define SE_BACKCLS1     ( 67)   // door close (normal)
#define SE_BACKCLS2     ( 68)   // door close (heavy)
#define SE_DUMMY_069    ( 69)   //
#define SE_DUMMY_070    ( 70)   //
#define SE_DUMMY_071    ( 71)   //
#define SE_UNK072       ( 72)   //
#define SE_SHOT_M02     ( 73)   // SOCOM gunshot
#define SE_FACECHG1     ( 74)   // radio "face change" static
#define SE_RUN00001     ( 75)   // engine running
#define SE_NIKITA01     ( 76)   // Nikita missile fired
#define SE_NIKITA02     ( 77)   // Nikita missile boost
#define SE_NINJA01      ( 78)   // Ninja stealth effect
#define SE_UNK079       ( 79)   //
#define SE_NINJA02      ( 80)   //
#define SE_HIZA01       ( 81)   // 「ひざ」？ (enemy collapses)
#define SE_SHOT_SUP     ( 82)   // SOCOM gunshot (suppressed)
#define SE_EXCLAMATION  ( 83)   // 「びっくりマーク」
#define SE_R_WINDW1     ( 84)   // radio connect
#define SE_R_SEL01      ( 85)   // radio select
#define SE_R_SND01      ( 86)   // radio CALL (outgoing)
#define SE_R_WINDW2     ( 87)   // radio disconnect
#define SE_DCLOSE03     ( 88)   // "door close 03"
#define SE_DCLOSE04     ( 89)   // "door close 04"
#define SE_DCLOSE05     ( 90)   // "door close 05"
#define SE_DOPEN03      ( 91)   // "door open 03"
#define SE_DOPEN04      ( 92)   // "door open 04"
#define SE_DOPEN05      ( 93)   // "door open 05"
#define SE_CAMERA07     ( 94)   // surveillance camera (scanning)
#define SE_CAMERA03     ( 95)   // surveillance camera (lens focus)
#define SE_BUTTON01     ( 96)   // elevator button
#define SE_ELECLS03     ( 97)   // "elevator close 03"
#define SE_ELEOPN03     ( 98)   // "elevator open 03"
#define SE_SIGHT08      ( 99)   // Wolf's laser sight
#define SE_INELEV02     (100)   // elevator running
#define SE_UNK101       (101)   //
#define SE_START001     (102)   // start/continue gunshot
#define SE_R_TUNE01     (103)   // radio tuning
#define SE_R_CANCEL     (104)   // radio cancel
#define SE_R_CURSOR     (105)   // radio cursor
#define SE_O2DAMAGE     (106)   // LIFE draining
#define SE_POUT0002     (107)   // player out (asphyxiation)
#define SE_R_NOISE1     (108)   // radio static
#define SE_CAMERA06     (109)   // surveillance camera (jammed)
#define SE_SHATTR04     (110)   // shutter close
#define SE_SHATTR06     (111)   // shutter closing
#define SE_EL_CHM02     (112)   // elevator chime
#define SE_ELSTOP06     (113)   // elevator stop
#define SE_MASK0002     (114)   // gas mask breath
#define SE_RATION01     (115)   // ration unfreeze
#define SE_SIGNAL02     (116)   //
#define SE_CLOCK001     (117)   // "tick tick tick"
#define SE_MMASK001     (118)   //
#define SE_SIGNAL04     (119)   //
#define SE_RADAR003     (120)   // radar jammed
#define SE_JINGLE01     (121)   // jingle (notice)
#define SE_JINGLE02     (122)   // jingle (strings)
#define SE_CHR_DSP1     (123)   // (choir aahs)
#define SE_SHATTR0B     (124)   // shutter close
#define SE_MENUOPN1     (125)   // ranking menu
#define SE_KAIHUKU4     (126)   // 「回復」 (LIFE-UP)
#define SE_LIFE_UP      SE_KAIHUKU4
#define SE_IDEC04       (127)   // "item decide" (menu toggle)
#define SE_TBL_MAX      (128)

#endif // _G_SOUND_H_
