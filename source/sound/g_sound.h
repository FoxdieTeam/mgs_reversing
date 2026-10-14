#ifndef __G_SOUND_H__
#define __G_SOUND_H__
/*----------------------------------------------------------------------*/

/*--------------------*/
/*--- Song Control ---*/
/*--------------------*/
/*SONG PAUSE*/
#define SNG_PAUSEON     0x01FFFF01
#define SNG_PAUSEOFF    0x01FFFF02
/*SONG FADE IN*/
#define SNG_FIN_S       0x01FFFF03  /* (1sec) */
#define SNG_FIN_M       0x01FFFF04  /* (3sec) */
#define SNG_FIN_L       0x01FFFF05  /* (5sec) */
/*SONG FADE OUT & PAUSE*/
#define SNG_FOUTP_SS    0x01FFFF06  /* (0.5sec) */
#define SNG_FOUTP_S     0x01FFFF07  /* (1sec) */
#define SNG_FOUTP_M     0x01FFFF08  /* (3sec) */
#define SNG_FOUTP_L     0x01FFFF09  /* (5sec) */
/*SONG FADE OUT & STOP*/
#define SNG_FOUTS_SS    0x01FFFF0A  /* (0.5sec) */
#define SNG_FOUTS_S     0x01FFFF0B  /* (1sec) */
#define SNG_FOUTS_M     0x01FFFF0C  /* (3sec) */
#define SNG_FOUTS_L     0x01FFFF0D  /* (5sec) */
/*Kaihi MODE*/
#define SNG_KAIHI_01    0x01FFFF10
/*Syukan MODE*/
#define SNG_SYUKAN_ON   0x01FFFF20
#define SNG_SYUKAN_OFF  0x01FFFF21

/*SONG STOP*/
#define SNG_STOP        0x01FFFFFF

/*--------------------*/
/*---- SE CONTROL ----*/
/*--------------------*/
#define SE_JOUCHUU_OFF  0xFF0000FE

/*--------------------*/
/*---- STR CONTROL ---*/
/*--------------------*/
#define STR_STOP        0xFFFFFFFD  /* (0.5sec) */
/*STR FADE IN*/
#define STR_FIN_M       0xFF0000F8  /* (2sec) */
#define STR_FIN_L       0xFF0000F9  /* (5sec) */
/*STR FADE OUT & PAUSE*/
#define STR_FOUTP_SS    0xFF0000F4  /* (1sec) */
#define STR_FOUTP_S     0xFF0000F5  /* (2sec) */
#define STR_FOUTP_M     0xFF0000F6  /* (5sec) */
#define STR_FOUTP_L     0xFF0000F7  /* (10sec) */
/*STR FADE OUT & STOP*/
#define STR_FOUTS_SS    0xFF0000FA  /* (1sec) */
#define STR_FOUTS_S     0xFF0000FB  /* (2sec) */
#define STR_FOUTS_M     0xFF0000FC  /* (5sec) */
#define STR_FOUTS_L     0xFF0000FD  /* (10sec) */

/*--------------------*/
/*-- REVERB CONTROL --*/
/*--------------------*/
/*SE REVERB ON/OFF*/
#define SE_REVERB_ON    0xFF000007
#define SE_REVERB_OFF   0xFF000008
#define STR_REVERB_ON   0xFF000009

/*--------------------*/
/*-- SYSTEM CONTROL --*/
/*--------------------*/
#define SD_MONORAL      0xFF000005
#define SD_STEREO       0xFF000006

/*---------------------- BGM -------------------------------------------*/

/*SONG PLAY CODE*/
#define SNG_PLAY_01     0x01000001
#define SNG_PLAY_02     0x01000002
#define SNG_PLAY_03     0x01000003
#define SNG_PLAY_04     0x01000004
#define SNG_PLAY_05     0x01000005
#define SNG_PLAY_06     0x01000006
#define SNG_PLAY_07     0x01000007
#define SNG_PLAY_08     0x01000008

/*---------------------- SE --------------------------------------------*/

#define SE_DUMMY                (0x00)
#define SE_SHOT_01              (0x01)
#define SE_SOCOM_SHOT           SE_SHOT_01
#define SE_STEPL01              (0x02)
#define SE_STEP_LEFT            SE_STEPL01
#define SE_STEPR01              (0x03)
#define SE_STEP_RIGHT           SE_STEPR01
#define SE_KARASHT1             (0x04)          // カラショット
#define SE_KARASHT              SE_KARASHT1
#define SE_HOHUKU03             (0x05)          // ほふく
#define SE_CRAWL_LEFT           SE_HOHUKU03
#define SE_HOHUKU04             (0x06)          // ほふく
#define SE_CRAWL_RIGHT          SE_HOHUKU04
#define SE_SENAKA01             (0x07)          // 背中
#define SE_WALLPRESS            SE_SENAKA01
#define SE_STAND01              (0x08)
#define SE_CHANGE_STANCE        SE_STAND01
#define SE_KAMAE01              (0x09)          // 構える
#define SE_READY_WEAPON         SE_KAMAE01
#define SE_HEART01              (0x0A)
#define SE_HEARTBEAT            SE_HEART01
#define SE_FULL0005             (0x0B)
#define SE_ITEM_FULL            SE_FULL0005
#define SE_KAIHUKU1             (0x0C)           // 回復
#define SE_RECOVER_LIFE         SE_KAIHUKU1
#define SE_ITEM0003             (0x0D)
#define SE_SPAWN_ITEM           SE_ITEM0003
#define SE_RADAR001             (0x0E)
#define SE_RADAR_CHIME          SE_RADAR001     // all-clear chime
#define SE_OVER03               (0x0F)
#define SE_GAMEOVER             SE_OVER03
#define SE_CALL01               (0x10)
#define SE_RADIO_CALL           SE_CALL01
#define SE_CAMERA02             (0x11)
#define SE_PHOTO_SHUTTER        SE_CAMERA02
#define SE_POUT0003             (0x12)
#define SE_PLAYEROUT_GAS        SE_POUT0003     // asphyxiation
#define SE_SNEEZE01             (0x13)
#define SE_SNEEZE               SE_SNEEZE01
#define SE_IDEC03               (0x14)
#define SE_ITEM_EQUIP           SE_IDEC03
#define SE_IDISP02              (0x15)
#define SE_ITEM_OPENWINDOW      SE_IDISP02
#define SE_IGET01               (0x16)
#define SE_ITEM_GET             SE_IGET01
#define SE_ISEL02               (0x17)
#define SE_ITEM_SELECT          SE_ISEL02
#define SE_PDMG01               (0x18)
#define SE_PLAYER_DAMAGE1       SE_PDMG01
#define SE_PDMG02               (0x19)
#define SE_PLAYER_DAMAGE2       SE_PDMG02
#define SE_POUT0001             (0x1A)
#define SE_PLAYEROUT            SE_POUT0001
#define SE_RIFLE01              (0x1B)
#define SE_PSG1_SHOT            SE_RIFLE01
#define SE_STEP02               (0x1C)
#define SE_HOP_DOWN             SE_STEP02
#define SE_MOUSTEP2             (0x1D)
#define SE_MOUSE_STEP           SE_MOUSTEP2
#define SE_WSTEP01              (0x1E)
#define SE_WET_STEP             SE_WSTEP01
#define SE_CUR01                (0x1F)
#define SE_MENU_CURSOR          SE_CUR01
#define SE_WIN01                (0x20)
#define SE_MENU_SELECT          SE_WIN01
#define SE_START01              (0x21)
#define SE_MENU_EXIT            SE_START01
#define SE_IDEC02               (0x22)
#define SE_ITEM_MEDICINE        SE_IDEC02
#define SE_BUZZER01             (0x23)
#define SE_BUZZER               SE_BUZZER01
#define SE_ZOOM01               (0x24)
#define SE_SCOPE_ZOOM           SE_ZOOM01
#define SE_ATARU01              (0x25)          // あたる
#define SE_HIT                  SE_ATARU01
#define SE_EDMG01               (0x26)
#define SE_ENEMY_DAMAGE         SE_EDMG01
#define SE_REB01                (0x27)
#define SE_RICOCHET_WEAK        SE_REB01
#define SE_REBDRM01             (0x28)
#define SE_RICOCHET_STRONG      SE_REBDRM01
#define SE_EXP_05               (0x29)
#define SE_EXPLOSION            SE_EXP_05
#define SE_SIREN0600            (0x2A)
#define SE_ALERT_SIREN          SE_SIREN0600
#define SE_BOUND02              (0x2B)
#define SE_GRENADE_HIT          SE_BOUND02
#define SE_PIN01                (0x2C)          // grenade pin
#define SE_PINNUKI              SE_PIN01
#define SE_SHOT_E03             (0x2D)
#define SE_ENEMY_SHOT           SE_SHOT_E03
#define SE_SHOT_E02             (0x2E)
#define SE_GUNCAM_SHOT          SE_SHOT_E02
#define SE_RELOAD01             (0x2F)
#define SE_RELOAD               SE_RELOAD01
#define SE_FAMAS03              (0x30)
#define SE_FAMAS_SHOT           SE_FAMAS03
#define SE_C4PUT01              (0x31)
#define SE_C4_PUT               SE_C4PUT01
#define SE_C4SW01               (0x32)
#define SE_C4_SWITCH            SE_C4SW01
#define SE_DOWN0002             (0x33)
#define SE_HIT_FLOOR            SE_DOWN0002
#define SE_PUNCHIT1             (0x34)
#define SE_PUNCH_HIT            SE_PUNCHIT1
#define SE_KICKHIT1             (0x35)
#define SE_KICK_HIT             SE_KICKHIT1
#define SE_ISEL0003             (0x36)
#define SE_ITEM_CURSOR          SE_ISEL0003
#define SE_WALL02               (0x37)
#define SE_WALLKNOCK            SE_WALL02
#define SE_P_SWING1             (0x38)
#define SE_PUNCH_SWING          SE_P_SWING1
#define SE_K_SWING1             (0x39)
#define SE_KICK_SWING           SE_K_SWING1
#define SE_CHAF0003             (0x3A)
#define SE_CHAFF_PARTICLE       SE_CHAF0003
#define SE_HIBANA01             (0x3B)          // 火花
#define SE_SPARKS               SE_HIBANA01
#define SE_PANEL01              (0x3C)
#define SE_ELECTRIC_PANEL       SE_PANEL01
#define SE_CHAIR01              (0x3D)
#define SE_CHAIR                SE_CHAIR01
#define SE_REBGLASS             (0x3E)
#define SE_BROKEN_GLASS         SE_REBGLASS
#define SE_GLASS11              (0x3F)
#define SE_GLASS_SHATTER        SE_GLASS11
#define SE_PAPER01              (0x40)
#define SE_PAPER                SE_PAPER01
#define SE_BAKUHA01             (0x41)          // 爆破
#define SE_BLAST                SE_BAKUHA01
#define SE_CHAF0002             (0x42)
#define SE_CHAFF_EXPLODE        SE_CHAF0002
#define SE_BACKCLS1             (0x43)
#define SE_DOOR_CLOSE_NORMAL    SE_BACKCLS1
#define SE_BACKCLS2             (0x44)
#define SE_DOOR_CLOSE_HEAVY     SE_BACKCLS2
#define SE_DUMMY_069            (0x45)          // (reserved)
#define SE_DUMMY_070            (0x46)          // (reserved)
#define SE_DUMMY_071            (0x47)          // (reserved)
#define SE_MAGAZI01             (0x48)
#define SE_SHOT_M02             (0x49)
#define SE_SOCOM_SHOT2          SE_SHOT_M02
#define SE_FACECHG1             (0x4A)
#define SE_RADIO_FACECHANGE     SE_FACECHG1
#define SE_RUN00001             (0x4B)
#define SE_RUNNING_ENGINE       SE_RUN00001
#define SE_MISSIL01             (0x4C)
#define SE_MISSILE_FIRED        SE_MISSIL01
#define SE_MISILE03             (0x4D)
#define SE_MISSILE_BOOST        SE_MISILE03
#define SE_NINJA01              (0x4E)
#define SE_NINJA_STEALTH        SE_NINJA01
#define SE_SIGNAL01             (0x4F)
#define SE_STINGER_LOCKON       SE_SIGNAL01
#define SE_NINJA02              (0x50)
#define SE_HIZA01               (0x51)          // 膝
#define SE_ENEMY_COLLAPSE       SE_HIZA01
#define SE_SOSIRE01             (0x52)
#define SE_SOCOM_SUPPRESSED     SE_SOSIRE01
#define SE_BIKKRI01             (0x53)          // びっくりマーク
#define SE_EXCLAMATION          SE_BIKKRI01     // "!"
#define SE_R_WINDW1             (0x54)
#define SE_RADIO_CONNECT        SE_R_WINDW1
#define SE_R_SEL01              (0x55)
#define SE_RADIO_SELECT         SE_R_SEL01
#define SE_R_SND01              (0x56)
#define SE_RADIO_SEND           SE_R_SND01
#define SE_R_WINDW2             (0x57)
#define SE_RADIO_DISCONNECT     SE_R_WINDW2
#define SE_DCLOSE03             (0x58)
#define SE_DOOR_CLOSE3          SE_DCLOSE03
#define SE_DCLOSE04             (0x59)
#define SE_DOOR_CLOSE4          SE_DCLOSE04
#define SE_DCLOSE05             (0x5A)
#define SE_DOOR_CLOSE5          SE_DCLOSE05
#define SE_DOPEN03              (0x5B)
#define SE_DOOR_OPEN3           SE_DOPEN03
#define SE_DOPEN04              (0x5C)
#define SE_DOOR_OPEN4           SE_DOPEN04
#define SE_DOPEN05              (0x5D)
#define SE_DOOR_OPEN5           SE_DOPEN05
#define SE_CAMERA07             (0x5E)
#define SE_CAMERA_SCAN          SE_CAMERA07
#define SE_CAMERA03             (0x5F)
#define SE_CAMERA_LENS          SE_CAMERA03
#define SE_BUTTON01             (0x60)
#define SE_ELEVATOR_BUTTON      SE_BUTTON01
#define SE_ELECLS03             (0x61)
#define SE_ELEVATOR_CLOSE       SE_ELECLS03
#define SE_ELEOPN03             (0x62)
#define SE_ELEVATOR_OPEN        SE_ELEOPN03
#define SE_SIGHT08              (0x63)
#define SE_LASER_SIGHT          SE_SIGHT08      // Wolf's laser sight
#define SE_INELEV02             (0x64)
#define SE_ELEVATOR_RUNNING     SE_INELEV02
#define SE_CASE03               (0x65)
#define SE_MP5_SHOT             SE_CASE03
#define SE_START001             (0x66)
#define SE_MENU_GUNSHOT         SE_START001
#define SE_R_TUNE01             (0x67)
#define SE_RADIO_TUNING         SE_R_TUNE01
#define SE_R_CANCEL             (0x68)
#define SE_RADIO_CANCEL         SE_R_CANCEL
#define SE_R_CURSOR             (0x69)
#define SE_RADIO_CURSOR         SE_R_CURSOR
#define SE_O2DAMAGE             (0x6A)
#define SE_POUT0002             (0x6B)
#define SE_PLAYEROUT_GAS2       SE_POUT0002     // asphyxiation
#define SE_R_NOISE1             (0x6C)
#define SE_RADIO_STATIC         SE_R_NOISE1
#define SE_CAMERA06             (0x6D)
#define SE_CAMERA_JAMMED        SE_CAMERA06
#define SE_SHATTR04             (0x6E)
#define SE_SHUTTER_CLOSE        SE_SHATTR04
#define SE_SHATTR06             (0x6F)
#define SE_SHUTTER_CLOSING      SE_SHATTR06
#define SE_EL_CHM02             (0x70)
#define SE_ELEVATOR_CHIME       SE_EL_CHM02
#define SE_ELSTOP06             (0x71)
#define SE_ELEVATOR_STOP        SE_ELSTOP06
#define SE_MASK0002             (0x72)
#define SE_GASMASK_BREATH       SE_MASK0002
#define SE_RATION01             (0x73)
#define SE_RATION_FROZEN        SE_RATION01
#define SE_SIGNAL02             (0x74)
#define SE_CLOCK001             (0x75)
#define SE_TIMEBOMB_TICK        SE_CLOCK001
#define SE_MMASK001             (0x76)
#define SE_SIGNAL04             (0x77)
#define SE_RADAR003             (0x78)
#define SE_RADAR_JAMMED         SE_RADAR003
#define SE_JINGLE01             (0x79)          // "notice" jingle
#define SE_JINGLE02             (0x7A)          // "strings" jingle
#define SE_CHR_DSP1             (0x7B)
#define SE_LOGO_CHOIR           SE_CHR_DSP1
#define SE_SHATTR0B             (0x7C)
#define SE_SHUTTER_CLOSE2       SE_SHATTR0B
#define SE_MENUOPN1             (0x7D)
#define SE_MENU_RANKING         SE_MENUOPN1
#define SE_KAIHUKU4             (0x7E)           // 回復
#define SE_LIFE_UP              SE_KAIHUKU4
#define SE_IDEC04               (0x7F)
#define SE_MENU_TOGGLE          SE_IDEC04

/*----------------------------------------------------------------------*/
/*  Non-Resident Sound Effects                                          */
/*----------------------------------------------------------------------*/
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

/*----------------------------------------------------------------------*/
#endif // __G_SOUND_H__
