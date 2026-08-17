#ifndef __G_SOUND_H__
#define __G_SOUND_H__

/*---------------------------------------------------------------------------*/
/*  Resident Sound Effects                                                   */
/*---------------------------------------------------------------------------*/

#define SE_DUMMY                (  0)
#define SE_SHOT_01              (  1)
#define SE_SOCOM_SHOT           SE_SHOT_01
#define SE_STEPL01              (  2)
#define SE_STEP_LEFT            SE_STEPL01
#define SE_STEPR01              (  3)
#define SE_STEP_RIGHT           SE_STEPR01
#define SE_KARASHT1             (  4)           // カラショット
#define SE_KARASHT              SE_KARASHT1
#define SE_HOHUKU03             (  5)           // ほふく
#define SE_CRAWL_LEFT           SE_HOHUKU03
#define SE_HOHUKU04             (  6)           // ほふく
#define SE_CRAWL_RIGHT          SE_HOHUKU04
#define SE_SENAKA01             (  7)           // 背中
#define SE_WALLPRESS            SE_SENAKA01
#define SE_STAND01              (  8)
#define SE_CHANGE_STANCE        SE_STAND01
#define SE_KAMAE01              (  9)           // 構える
#define SE_READY_WEAPON         SE_KAMAE01
#define SE_HEART01              ( 10)
#define SE_HEARTBEAT            SE_HEART01
#define SE_FULL0005             ( 11)
#define SE_ITEM_FULL            SE_FULL0005
#define SE_KAIHUKU1             ( 12)           // 回復
#define SE_RECOVER_LIFE         SE_KAIHUKU1
#define SE_ITEM0003             ( 13)
#define SE_SPAWN_ITEM           SE_ITEM0003
#define SE_RADAR001             ( 14)
#define SE_RADAR_CHIME          SE_RADAR001     // all-clear chime
#define SE_OVER03               ( 15)
#define SE_GAMEOVER             SE_OVER03
#define SE_CALL01               ( 16)
#define SE_RADIO_CALL           SE_CALL01
#define SE_CAMERA02             ( 17)
#define SE_PHOTO_SHUTTER        SE_CAMERA02
#define SE_POUT0003             ( 18)
#define SE_PLAYEROUT_GAS        SE_POUT0003     // asphyxiation
#define SE_SNEEZE01             ( 19)
#define SE_SNEEZE               SE_SNEEZE01
#define SE_IDEC03               ( 20)
#define SE_ITEM_EQUIP           SE_IDEC03
#define SE_IDISP02              ( 21)
#define SE_ITEM_OPENWINDOW      SE_IDISP02
#define SE_IGET01               ( 22)
#define SE_ITEM_GET             SE_IGET01
#define SE_ISEL02               ( 23)
#define SE_ITEM_SELECT          SE_ISEL02
#define SE_PDMG01               ( 24)
#define SE_PLAYER_DAMAGE1       SE_PDMG01
#define SE_PDMG02               ( 25)
#define SE_PLAYER_DAMAGE2       SE_PDMG02
#define SE_POUT0001             ( 26)
#define SE_PLAYEROUT            SE_POUT0001
#define SE_RIFLE01              ( 27)
#define SE_PSG1_SHOT            SE_RIFLE01
#define SE_STEP02               ( 28)
#define SE_HOP_DOWN             SE_STEP02
#define SE_MOUSTEP2             ( 29)
#define SE_MOUSE_STEP           SE_MOUSTEP2
#define SE_WSTEP01              ( 30)
#define SE_WET_STEP             SE_WSTEP01
#define SE_CUR01                ( 31)
#define SE_MENU_CURSOR          SE_CUR01
#define SE_WIN01                ( 32)
#define SE_MENU_SELECT          SE_WIN01
#define SE_START01              ( 33)
#define SE_MENU_EXIT            SE_START01
#define SE_IDEC02               ( 34)
#define SE_ITEM_MEDICINE        SE_IDEC02
#define SE_BUZZER01             ( 35)
#define SE_BUZZER               SE_BUZZER01
#define SE_ZOOM01               ( 36)
#define SE_SCOPE_ZOOM           SE_ZOOM01
#define SE_ATARU01              ( 37)           // あたる
#define SE_HIT                  SE_ATARU01
#define SE_EDMG01               ( 38)
#define SE_ENEMY_DAMAGE         SE_EDMG01
#define SE_REB01                ( 39)
#define SE_RICOCHET_WEAK        SE_REB01
#define SE_REBDRM01             ( 40)
#define SE_RICOCHET_STRONG      SE_REBDRM01
#define SE_EXP_05               ( 41)
#define SE_EXPLOSION            SE_EXP_05
#define SE_SIREN0600            ( 42)
#define SE_ALERT_SIREN          SE_SIREN0600
#define SE_BOUND02              ( 43)
#define SE_GRENADE_HIT          SE_BOUND02
#define SE_PIN01                ( 44)           // grenade pin
#define SE_PINNUKI              SE_PIN01
#define SE_SHOT_E03             ( 45)
#define SE_ENEMY_SHOT           SE_SHOT_E03
#define SE_SHOT_E02             ( 46)
#define SE_GUNCAM_SHOT          SE_SHOT_E02
#define SE_RELOAD01             ( 47)
#define SE_RELOAD               SE_RELOAD01
#define SE_FAMAS03              ( 48)
#define SE_FAMAS_SHOT           SE_FAMAS03
#define SE_C4PUT01              ( 49)
#define SE_C4_PUT               SE_C4PUT01
#define SE_C4SW01               ( 50)
#define SE_C4_SWITCH            SE_C4SW01
#define SE_DOWN0002             ( 51)
#define SE_HIT_FLOOR            SE_DOWN0002
#define SE_PUNCHIT1             ( 52)
#define SE_PUNCH_HIT            SE_PUNCHIT1
#define SE_KICKHIT1             ( 53)
#define SE_KICK_HIT             SE_KICKHIT1
#define SE_ISEL0003             ( 54)
#define SE_ITEM_CURSOR          SE_ISEL0003
#define SE_WALL02               ( 55)
#define SE_WALLKNOCK            SE_WALL02
#define SE_P_SWING1             ( 56)
#define SE_PUNCH_SWING          SE_P_SWING1
#define SE_K_SWING1             ( 57)
#define SE_KICK_SWING           SE_K_SWING1
#define SE_CHAF0003             ( 58)
#define SE_CHAFF_PARTICLE       SE_CHAF0003
#define SE_HIBANA01             ( 59)           // 火花
#define SE_SPARKS               SE_HIBANA01
#define SE_PANEL01              ( 60)
#define SE_ELECTRIC_PANEL       SE_PANEL01
#define SE_CHAIR01              ( 61)
#define SE_CHAIR                SE_CHAIR01
#define SE_REBGLASS             ( 62)
#define SE_BROKEN_GLASS         SE_REBGLASS
#define SE_GLASS11              ( 63)
#define SE_GLASS_SHATTER        SE_GLASS11
#define SE_PAPER01              ( 64)
#define SE_PAPER                SE_PAPER01
#define SE_BAKUHA01             ( 65)           // 爆破
#define SE_BLAST                SE_BAKUHA01
#define SE_CHAF0002             ( 66)
#define SE_CHAFF_EXPLODE        SE_CHAF0002
#define SE_BACKCLS1             ( 67)
#define SE_DOOR_CLOSE_NORMAL    SE_BACKCLS1
#define SE_BACKCLS2             ( 68)
#define SE_DOOR_CLOSE_HEAVY     SE_BACKCLS2
#define SE_DUMMY_069            ( 69)           // (reserved)
#define SE_DUMMY_070            ( 70)           // (reserved)
#define SE_DUMMY_071            ( 71)           // (reserved)
#define SE_MAGAZI01             ( 72)
#define SE_SHOT_M02             ( 73)
#define SE_SOCOM_SHOT2          SE_SHOT_M02
#define SE_FACECHG1             ( 74)
#define SE_RADIO_FACECHANGE     SE_FACECHG1
#define SE_RUN00001             ( 75)
#define SE_RUNNING_ENGINE       SE_RUN00001
#define SE_MISSIL01             ( 76)
#define SE_MISSILE_FIRED        SE_MISSIL01
#define SE_MISILE03             ( 77)
#define SE_MISSILE_BOOST        SE_MISILE03
#define SE_NINJA01              ( 78)
#define SE_NINJA_STEALTH        SE_NINJA01
#define SE_SIGNAL01             ( 79)
#define SE_STINGER_LOCKON       SE_SIGNAL01
#define SE_NINJA02              ( 80)
#define SE_HIZA01               ( 81)           // 膝
#define SE_ENEMY_COLLAPSE       SE_HIZA01
#define SE_SOSIRE01             ( 82)
#define SE_SOCOM_SUPPRESSED     SE_SOSIRE01
#define SE_BIKKRI01             ( 83)           // びっくりマーク
#define SE_EXCLAMATION          SE_BIKKRI01     // "!"
#define SE_R_WINDW1             ( 84)
#define SE_RADIO_CONNECT        SE_R_WINDW1
#define SE_R_SEL01              ( 85)
#define SE_RADIO_SELECT         SE_R_SEL01
#define SE_R_SND01              ( 86)
#define SE_RADIO_SEND           SE_R_SND01
#define SE_R_WINDW2             ( 87)
#define SE_RADIO_DISCONNECT     SE_R_WINDW2
#define SE_DCLOSE03             ( 88)
#define SE_DOOR_CLOSE3          SE_DCLOSE03
#define SE_DCLOSE04             ( 89)
#define SE_DOOR_CLOSE4          SE_DCLOSE04
#define SE_DCLOSE05             ( 90)
#define SE_DOOR_CLOSE5          SE_DCLOSE05
#define SE_DOPEN03              ( 91)
#define SE_DOOR_OPEN3           SE_DOPEN03
#define SE_DOPEN04              ( 92)
#define SE_DOOR_OPEN4           SE_DOPEN04
#define SE_DOPEN05              ( 93)
#define SE_DOOR_OPEN5           SE_DOPEN05
#define SE_CAMERA07             ( 94)
#define SE_CAMERA_SCAN          SE_CAMERA07
#define SE_CAMERA03             ( 95)
#define SE_CAMERA_LENS          SE_CAMERA03
#define SE_BUTTON01             ( 96)
#define SE_ELEVATOR_BUTTON      SE_BUTTON01
#define SE_ELECLS03             ( 97)
#define SE_ELEVATOR_CLOSE       SE_ELECLS03
#define SE_ELEOPN03             ( 98)
#define SE_ELEVATOR_OPEN        SE_ELEOPN03
#define SE_SIGHT08              ( 99)
#define SE_LASER_SIGHT          SE_SIGHT08      // Wolf's laser sight
#define SE_INELEV02             (100)
#define SE_ELEVATOR_RUNNING     SE_INELEV02
#define SE_CASE03               (101)
#define SE_MP5_SHOT             SE_CASE03
#define SE_START001             (102)
#define SE_MENU_GUNSHOT         SE_START001
#define SE_R_TUNE01             (103)
#define SE_RADIO_TUNING         SE_R_TUNE01
#define SE_R_CANCEL             (104)
#define SE_RADIO_CANCEL         SE_R_CANCEL
#define SE_R_CURSOR             (105)
#define SE_RADIO_CURSOR         SE_R_CURSOR
#define SE_O2DAMAGE             (106)
#define SE_POUT0002             (107)
#define SE_PLAYEROUT_GAS2       SE_POUT0002     // asphyxiation
#define SE_R_NOISE1             (108)
#define SE_RADIO_STATIC         SE_R_NOISE1
#define SE_CAMERA06             (109)
#define SE_CAMERA_JAMMED        SE_CAMERA06
#define SE_SHATTR04             (110)
#define SE_SHUTTER_CLOSE        SE_SHATTR04
#define SE_SHATTR06             (111)
#define SE_SHUTTER_CLOSING      SE_SHATTR06
#define SE_EL_CHM02             (112)
#define SE_ELEVATOR_CHIME       SE_EL_CHM02
#define SE_ELSTOP06             (113)
#define SE_ELEVATOR_STOP        SE_ELSTOP06
#define SE_MASK0002             (114)
#define SE_GASMASK_BREATH       SE_MASK0002
#define SE_RATION01             (115)
#define SE_RATION_FROZEN        SE_RATION01
#define SE_SIGNAL02             (116)
#define SE_CLOCK001             (117)
#define SE_TIMEBOMB_TICK        SE_CLOCK001
#define SE_MMASK001             (118)
#define SE_SIGNAL04             (119)
#define SE_RADAR003             (120)
#define SE_RADAR_JAMMED         SE_RADAR003
#define SE_JINGLE01             (121)           // "notice" jingle
#define SE_JINGLE02             (122)           // "strings" jingle
#define SE_CHR_DSP1             (123)
#define SE_LOGO_CHOIR           SE_CHR_DSP1
#define SE_SHATTR0B             (124)
#define SE_SHUTTER_CLOSE2       SE_SHATTR0B
#define SE_MENUOPN1             (125)
#define SE_MENU_RANKING         SE_MENUOPN1
#define SE_KAIHUKU4             (126)           // 回復
#define SE_LIFE_UP              SE_KAIHUKU4
#define SE_IDEC04               (127)
#define SE_MENU_TOGGLE          SE_IDEC04

/*---------------------------------------------------------------------------*/
/*  Non-Resident Sound Effects                                               */
/*---------------------------------------------------------------------------*/
// NOTE: The original filenames of the efx sequences are unknown,
// so we're just going to define our "friendly" names directly here.

// 0x80～0x99 : Character voices
// 0x9A～0x9F : Knocking sounds
// 0xA0～0xAF : Footstep sounds
// 0xB0～     : Stage-specific sounds

/*----- Enemy Soldier -----*/

#define SE_V_ENE_FOUND01        (0x80)  // 敵兵「誰だ！」
                                        // Soldier: Who's that!?
#define SE_V_ENE_FOUND02        (0x81)  // 敵兵「（無線）こっちだ！」
                                        // Soldier: (radio) This way!
#define SE_V_ENE_FOUND03        (0x82)  // 敵兵「（無線）いたぞ！」
                                        // Soldier: (radio) There he is!
#define SE_V_ENE_GRENADE        (0x83)  // 敵兵「くらえ！」
                                        // Soldier: Eat this!
#define SE_V_ENE_LOST           (0x84)  // 敵兵「どこ行った？」
                                        // Soldier: Where'd he go?
#define SE_V_ENE_RETURN         (0x85)  // 敵兵「（無線）配置に戻るぞ！」
                                        // Soldier: (radio) Return to your positions!
#define SE_V_ENE_NOTHING        (0x86)  // 敵兵「気のせいか」
                                        // Soldier: Hm...
#define SE_V_ENE_NOISE          (0x87)  // 敵兵「何の音だ？」
                                        // Soldier: What was that noise?
#define SE_V_ENE_HUH            (0x88)  // 敵兵「ん？」
                                        // Soldier: Huh?
#define SE_V_ENE_UNUSED10       (0x89)  // 敵兵「何か動いたぞ！」
                                        // ---
#define SE_V_ENE_FOOTPRINTS     (0x8A)  // 敵兵「この足跡は？」
                                        // Soldier: Whose footprints are these?
#define SE_V_ENE_JUSTABOX       (0x8B)  // 敵兵「ただの箱か」
                                        // Soldier: Just a box.
#define SE_V_ENE_INMYWAY        (0x8C)  // 敵兵「邪魔だ！」
                                        // Soldier: Get out of the way!

#define SE_V_ENE_PUNCHED        (0x8D)
#define SE_V_ENE_THROWN         (0x8E)
#define SE_V_ENE_GRABBED        (0x8F)
#define SE_V_ENE_SNAPPED        (0x90)
#define SE_V_ENE_KILLED         (0x91)
#define SE_V_ENE_YAWN           (0x92)
#define SE_V_ENE_SNORE          (0x93)
#define SE_V_ENE_SNEEZE         (0x94)

#define SE_V_ENE_THATSOUND      (0x95)  // 敵兵「今の音は！」
                                        // Soldier: I heard something!
#define SE_V_ENE_WHATSTHAT      (0x96)  // 敵兵「何だ？」
                                        // Soldier: What's that?

#endif // __G_SOUND_H__
