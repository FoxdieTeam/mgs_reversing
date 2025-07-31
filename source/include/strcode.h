#ifndef _STRCODE_H_
#define _STRCODE_H_

//-----------------------------------------------------------------------------
// GCL StrCodes
//-----------------------------------------------------------------------------

/* script filenames */
#define GCX_scenerio            0xea54  // GV_StrCode("scenerio")
#define GCX_demo                0xa242  // GV_StrCode("demo")

/* libgcl/basic.c */
#define CMD_if                  0x0d86  // GV_StrCode("if")
#define CMD_eval                0x64c0  // GV_StrCode("eval")
#define CMD_return              0xcd3a  // GV_StrCode("return")
#define CMD_foreach             0x7636  // GV_StrCode("foreach")

/* game/script.c */
#define CMD_mesg                0x22ff  // GV_StrCode("mesg")
#define CMD_trap                0xd4cb  // GV_StrCode("trap")
#define CMD_chara               0x9906  // GV_StrCode("chara")
#define CMD_map                 0xc091  // GV_StrCode("map")
#define CMD_mapdef              0x7d50  // GV_StrCode("mapdef")
#define CMD_camera              0xeee9  // GV_StrCode("camera")
#define CMD_light               0x306a  // GV_StrCode("light")
#define CMD_start               0x9a1f  // GV_StrCode("start")
#define CMD_load                0xc8bb  // GV_StrCode("load")
#define CMD_radio               0x24e1  // GV_StrCode("radio")
#define CMD_restart             0xe43c  // GV_StrCode("restart")
#define CMD_demo                0xa242  // GV_StrCode("demo")
#define CMD_ntrap               0xdbab  // GV_StrCode("ntrap")
#define CMD_delay               0x430d  // GV_StrCode("delay")
#define CMD_pad                 0xcc85  // GV_StrCode("pad")
#define CMD_varsave             0x5c9e  // GV_StrCode("varsave")
#define CMD_system              0x4ad9  // GV_StrCode("system")
#define CMD_sound               0x698d  // GV_StrCode("sound")
#define CMD_menu                0x226d  // GV_StrCode("menu")
#define CMD_rand                0x925e  // GV_StrCode("rand")
#define CMD_func                0xe257  // GV_StrCode("func")
#define CMD_demodebug           0xa2bf  // GV_StrCode("demodebug")
#define CMD_print               0xb96e  // GV_StrCode("print")
#define CMD_jimaku              0xec9d  // GV_StrCode("jimaku") // subtitle

//-----------------------------------------------------------------------------

#define HASH_PAN2               0x922b // GV_StrCode( "pan2" )

//-----------------------------------------------------------------------------
// Traps
//-----------------------------------------------------------------------------

#define HASH_TRAP_ALL           0x14c9 // GV_StrCode( "？" )

//  Events
#define HASH_ENTER              0x0dd2 // GV_StrCode( "入る" )
#define HASH_LEAVE              0xd5cc // GV_StrCode( "出る" )
#define HASH_LEAVE2             0x1a19 // GV_StrCode( "leave" )
#define HASH_KILL               0x3223 // GV_StrCode( "kill" )
#define HASH_OFF                0xc927 // GV_StrCode( "off" )
#define HASH_OFF2               0x006b // GV_StrCode( "ＯＦＦ" )
#define HASH_ON                 0x0e4e // GV_StrCode( "on" )
#define HASH_ON2                0xd182 // GV_StrCode( "ＯＮ" )
#define HASH_PADON              0x2580 // GV_StrCode( "padon" )
#define HASH_PADOFF             0xaf6a // GV_StrCode( "padoff" )
#define HASH_SLOW               0x3e92 // GV_StrCode( "slow" )
#define HASH_SOUND_ON           0x2761 // GV_StrCode( "音入れる" )
#define HASH_SOUND_OFF          0xed7f // GV_StrCode( "音切る" )
#define HASH_TABAKO             0x8012 // GV_StrCode( "tabako" )
#define HASH_POSITION           0x62b6 // GV_StrCode( "position" )
#define HASH_STOP               0x5e8b // GV_StrCode( "stop" )
#define HASH_START              0x9a1f // GV_StrCode( "start" )
#define HASH_STANCE             0x3238 // GV_StrCode( "stance" )
#define HASH_RUN_MOVE           0x70fb // GV_StrCode( "run_move" )
#define HASH_MOTION             0x937a // GV_StrCode( "motion" )
#define HASH_GO_MOTION          0xbe0a // GV_StrCode( "go_motion" )
#define HASH_MOVE               0x4b5d // GV_StrCode( "move" )
#define HASH_MOVE2              0x89cb // GV_StrCode( "移動" )
#define HASH_VOICE              0x385e // GV_StrCode( "voice" )
#define HASH_TURN               0xe2e9 // GV_StrCode( "turn" )
#define HASH_MODE               0x491d // GV_StrCode( "mode" )
#define HASH_OPERATION          0x4f34 // GV_StrCode( "operation" ) (might be wrong)
#define HASH_MAP                0xf9ad // GV_StrCode( "マップ" )
#define HASH_LOOP               0xca87 // GV_StrCode( "loop" )

//-----------------------------------------------------------------------------
// HZD
//-----------------------------------------------------------------------------

#define HASH_MAIN               0x7df9 // GV_StrCode( "メイン" ) - Refers to the main area of the map to load
#define HASH_ASIATO             0xdc55 // GV_StrCode( "asiato" )
#define HASH_POOL               0xca85 // GV_StrCode( "pool" )
#define HASH_POOLATO            0x7833 // GV_StrCode( "poolato" )

//-----------------------------------------------------------------------------
// Textures files (.pcx)
//-----------------------------------------------------------------------------
#define PCX_GO_EXIT             0x4d9a // GV_StrCode( "GO_EXIT" )
#define PCX_GO_CONTINUE         0x669d // GV_StrCode( "GO_CONTINUE" )
#define PCX_EMPTY2              0xb05c // GV_StrCode( "empty2" )
#define PCX_LSIGHT              0x08db // GV_StrCode( "lsight" )
#define PCX_SOCOM_F             0xe4cc // GV_StrCode( "socom_f" )
#define PCX_MG_SOLID            0x3f37 // GV_StrCode( "MG_SOLID" )
#define PCX_COMING_SOON         0x0abb // GV_StrCode( "COMING_SOON" )
#define PCX_SMOKE               0x512d // GV_StrCode( "smoke" )
#define PCX_WT_SUD11            0xdf92 // GV_StrCode( "wt_sud11" )
#define PCX_MAGAZIN             0x7e4c // GV_StrCode( "magazin" )
#define PCX_FA_FL10             0xfe8e // GV_StrCode( "fa_fl10" )
#define PCX_BOMB1_FL            0xac92 // GV_StrCode( "bomb1_fl" )
#define PCX_CANON_SEQ           0x2447 // GV_StrCode( "canon_seq" )
#define PCX_BLOOD_2             0x7b54 // GV_StrCode( "blood_2" )
#define PCX_SONIC               0x4cec // GV_StrCode( "sonic" )
#define PCX_LENSE_FLARE1        0x55a6 // GV_StrCode( "lense_flare1" )
#define PCX_B_MARK              0xdcd3 // GV_StrCode( "b_mark" )
#define PCX_Q_MARK              0xfad3 // GV_StrCode( "q_mark" )
#define PCX_HEART               0x1968 // GV_StrCode( "heart" )
#define PCX_PCH_FOG             0xf314 // GV_StrCode( "pch_fog" )
#define PCX_HOSI                0xcafe // GV_StrCode( "hosi" )
#define PCX_ZZZ                 0xf7bb // GV_StrCode( "zzz" )
#define PCX_ASIATO              0xdc55 // GV_StrCode( "asiato" )
#define PCX_RCM_L               0x479f // GV_StrCode( "rcm_l" )
#define PCX_W_BONBORI           0xa9cd // GV_StrCode( "w_bonbori" )
#define PCX_DOOR2               0x50eb // GV_StrCode( "door2" )

//-----------------------------------------------------------------------------
// Sight files (.sgt)
//-----------------------------------------------------------------------------
#define SGT_SCOPE               0x51c8 // GV_StrCode( "scope" )
#define SGT_NIKITA              0x15a9 // GV_StrCode( "nikita" )
#define SGT_CB_BOX              0xe2a9 // GV_StrCode( "cb_box" )
#define SGT_IR_GGLE1            0x84db // GV_StrCode( "ir_ggle1" )
#define SGT_IR_GGLE2            0x84dc // GV_StrCode( "ir_ggle2" )
#define SGT_IR_GGLE3            0x84dd // GV_StrCode( "ir_ggle3" )
#define SGT_NV_GGLE1            0x8504 // GV_StrCode( "nv_ggle1" )
#define SGT_NV_GGLE2            0x8505 // GV_StrCode( "nv_ggle2" )
#define SGT_NV_GGLE3            0x8506 // GV_StrCode( "nv_ggle3" )
#define SGT_MASK                0x1303 // GV_StrCode( "mask" )
#define SGT_CAMERA              0xeee9 // GV_StrCode( "camera" )
#define SGT_CAMERA_2            0xb3cd // GV_StrCode( "camera_2" )

//-----------------------------------------------------------------------------
// Model files (.kmd)
//-----------------------------------------------------------------------------

// Init "stage" (always loaded before each stage)
#define KMD_NULL                0xe224 // GV_StrCode( "null" )
#define KMD_SNAKE               0x992d // GV_StrCode( "snake" )
#define KMD_GOGGLES             0xe1d2 // GV_StrCode( "goggles" )
#define KMD_GAS_MASK            0x4244 // GV_StrCode( "gas_mask" )
#define KMD_RIFLE               0x2d3b // GV_StrCode( "rifle" )
#define KMD_STINGER             0x57f8 // GV_StrCode( "stinger" )
#define KMD_NIKITA              0x15a9 // GV_StrCode( "nikita" )
#define KMD_STN_FR              0x76ab // GV_StrCode( "stn_fr" )
#define KMD_NIK_MIS             0x9a90 // GV_StrCode( "nik_mis" )
#define KMD_FAMAS               0x4725 // GV_StrCode( "famas" )
#define KMD_SOCOM2              0x36f6 // GV_StrCode( "socom2" )
#define KMD_STN_BA              0x761a // GV_StrCode( "stn_ba" )
#define KMD_CAN_GREN            0x7a64 // GV_StrCode( "can_gren" )
#define KMD_GRENADE             0x3b88 // GV_StrCode( "grenade" )
#define KMD_SOCOM               0x21b6 // GV_StrCode( "socom" )
#define KMD_CLAYMORE            0x17a1 // GV_StrCode( "claymore" )
#define KMD_C4_BOMB             0xf83d // GV_StrCode( "c4_bomb" )
#define KMD_CB_BOX              0xe2a9 // GV_StrCode( "cb_box" )
#define KMD_CIGAR               0x2ef8 // GV_StrCode( "cigar" )
#define KMD_BANDANA             0xdb4d // GV_StrCode( "bandana" )
#define KMD_KAGE                0x117c // GV_StrCode( "kage" )
#define KMD_IPPANHEI            0x96b6 // GV_StrCode( "ippanhei" )

// Stage s00a/d00a (docks)
#define KMD_SNE_WET2            0x7693 // GV_StrCode( "sne_wet2" )

//-----------------------------------------------------------------------------
// Animation files (.oar)
//-----------------------------------------------------------------------------
#define OAR_SNAKE               0x992d // GV_StrCode( "snake" )
#define OAR_ENEMY               0xa8a1 // GV_StrCode( "enemy" )

//-----------------------------------------------------------------------------
// Sprites files (.pcc)
//-----------------------------------------------------------------------------
#define PCC_READ                0xa0be // GV_StrCode( "read" ) // for loading ?

//-----------------------------------------------------------------------------
// Chara IDs
//-----------------------------------------------------------------------------

/* MainCharacterEntries */
#define CHARA_SNAKE             0x21ca  // GV_StrCode("スネーク")
#define CHARA_DOOR              0xb997  // GV_StrCode("ドア")
#define CHARA_ITEM              0x8767  // GV_StrCode("アイテム")

/* _StageCharacterEntries */
#define CHARA_BLAST             0x0001  // source/bullet/blast.c
#define CHARA_UNKNOWN_0002      0x0002  // --> source/anime/animconv/anime.c
#define CHARA_FADEIO_0003       0x0003  // source/takabe/fadeio.c
#define CHARA_FADEIO_0004       0x0004  // source/takabe/fadeio.c
#define CHARA_TELOP_0005        0x0005  // source/takabe/telop.c
#define CHARA_UNKNOWN_0006      0x0006  // --> source/anime/animconv/anime.c (PC-ONLY)
#define CHARA_UNKNOWN_0007      0x0007  // --> source/anime/animconv/anime.c (PC-ONLY)
#define CHARA_UNKNOWN_0008      0x0008  // --> source/anime/animconv/anime.c (PC-ONLY)
#define CHARA_BLOOD             0x0009  // source/okajima/blood.c
#define CHARA_SPLASH            0x000a  // source/okajima/splash.c
#define CHARA_BULLET            0x000b  // source/okajima/bullet.c
#define CHARA_UNKNOWN_000C      0x000c  // --> source/anime/animconv/anime.c
#define CHARA_D_BLOODS          0x000d  // source/okajima/d_bloods.c
#define CHARA_UNKNOWN_000E      0x000e  // --> source/anime/animconv/anime.c
#define CHARA_DEMOKAGE          0x000f  // source/enemy/demokage.c
#define CHARA_DEMOASI           0x0010  // source/enemy/demoasi.c
#define CHARA_UNKNOWN_0011      0x0011  // --> source/anime/animconv/anime.c
#define CHARA_BUBBLE_T          0x0012  // source/okajima/bubble_t.c
#define CHARA_BUBBLE_P          0x0013  // source/okajima/bubble_p.c
#define CHARA_SCOPE_0014        0x0014  // source/equip/scope.c
#define CHARA_GOGGLE            0x0015  // source/takabe/goggle.c
#define CHARA_GGLSIGHT          0x0016  // source/equip/gglsight.c
#define CHARA_GOGGLE_IR         0x0017  // source/takabe/goggleir.c
#define CHARA_GOGGLE_SIGHT      0x0018  // source/equip/gglsight.c
#define CHARA_UNKNOWN_0019      0x0019  // --> source/anime/animconv/anime.c (PC-ONLY)
#define CHARA_KOGAKU2_001A      0x001a  // source/equip/kogaku2.c
#define CHARA_KOGAKU2_001B      0x001b  // source/equip/kogaku2.c
#define CHARA_ENVMAP3           0x001c  // source/takabe/envmap3.c
#define CHARA_PLASMA_001D       0x001d  // source/okajima/plasma.c
#define CHARA_WINDCRCL_001E     0x001e  // source/takabe/windcrcl.c
#define CHARA_SEPIA_001F        0x001f  // source/takabe/sepia.c
#define CHARA_MGREXLZR          0x0020  // source/kojo/mgrexlzr.c
#define CHARA_FOCUS             0x0021  // source/takabe/focus.c
#define CHARA_GASMASK_SIGHT     0x0022  // source/equip/gmsight.c
#define CHARA_D_BLOODS_0023     0x0023  // source/okajima/d_bloods.c
#define CHARA_PLASMA_0024       0x0024  // source/okajima/plasma.c
#define CHARA_BLOOD_BL          0x0025  // source/okajima/blood_bl.c
#define CHARA_UNKNOWN_0026      0x0026  // --> source/anime/animconv/anime.c (PC-ONLY)
#define CHARA_UNKNOWN_0027      0x0027  // --> source/anime/animconv/anime.c
#define CHARA_SEPIA_0028        0x0028  // source/takabe/sepia.c
#define CHARA_RFSIGHT           0x0029  // source/weapon/rfsight.c (PC-ONLY)
#define CHARA_UNKNOWN_002A      0x002a  // ???
#define CHARA_D_BLOODS_002B     0x002b  // source/okajima/d_bloods.c
#define CHARA_SIGHT             0x002c  // source/thing/sight.c (PC-ONLY)
#define CHARA_KATANA            0x002d  // source/enemy/katana.c
#define CHARA_SUB_ROOM          0x002e  // source/okajima/sub_room.c
#define CHARA_UNKNOWN_002F      0x002f  // ???
#define CHARA_BLST_LN           0x0030  // source/okajima/blst_ln.c
#define CHARA_SMKE_LN           0x0031  // source/okajima/smke_ln.c
#define CHARA_M1E1SMKE          0x0032  // source/kojo/m1e1smke.c
#define CHARA_UNKNOWN_0033      0x0033  // --> source/anime/animconv/anime.c
#define CHARA_UNKNOWN_0034      0x0034  // --> source/anime/animconv/anime.c (PC-ONLY)
#define CHARA_UNKNOWN_0035      0x0035  // --> source/anime/animconv/anime.c
#define CHARA_UNKNOWN_0036      0x0036  // --> source/anime/animconv/anime.c
#define CHARA_RED_ALERT_0037    0x0037  // source/okajima/red_alrt.c
#define CHARA_RED_ALERT_0038    0x0038  // source/okajima/red_alrt.c
#define CHARA_CRSH_SMK          0x0039  // source/okajima/crsh_smk.c
#define CHARA_CELOFAN           0x003a  // source/kojo/celofan.c (PC-ONLY)
#define CHARA_INVERLT           0x003b  // source/kojo/inverlt.c
#define CHARA_SPARK2            0x003c  // source/takabe/spark2.c
#define CHARA_SPARK             0x003d  // source/okajima/spark.c
#define CHARA_UNKNOWN_003E      0x003e  // --> source/anime/animconv/anime.c
#define CHARA_INVERLT2          0x003f  // source/kojo/inverlt2.c
#define CHARA_CELOFAN2          0x0040  // source/kojo/celofan2.c (PC-ONLY)
#define CHARA_NINJALZR          0x0041  // source/kojo/ninjalzr.c
#define CHARA_GAS_EFCT          0x0042  // source/takabe/gas_efct.c
#define CHARA_SUB_EFFECT        0x0043  // source/takabe/sub_efct.c
#define CHARA_BLURPURE          0x0044  // source/okajima/blurpure.c
#define CHARA_FAMASLIT          0x0045  // source/kojo/famaslit.c
#define CHARA_REALSHDW          0x0046  // source/takabe/realshdw.c (PC-ONLY)
#define CHARA_BLOOD_HZD         0x0047  // source/kojo/bloodhzd.c
#define CHARA_BLOOD_DRP         0x0048  // source/kojo/blooddrp.c
#define CHARA_WINDCRCL_0049     0x0049  // source/takabe/windcrcl.c
#define CHARA_BOMBLED           0x004a  // source/animal/liquid/bombled.c
#define CHARA_METAL_GEAR_ROOM   0x004b  // source/okajima/mg_room.c
#define CHARA_TELOP_004C        0x004c  // source/takabe/telop.c
#define CHARA_MOSAIC            0x0065  // GV_StrCode("モザイク") source/takabe/mosaic.c
#define CHARA_ASIATOKUN         0x02c4  // GV_StrCode("足跡君") source/enemy/asiato.c
#define CHARA_UNKNOWN_03BF      0x03bf  // ??? (PC-ONLY)
#define CHARA_SHUTER            0x03d9  // GV_StrCode("シャッター") source/takabe/shuter.c
#define CHARA_RANK              0x04f2  // source/onoda/rank/rank.c
#define CHARA_REVOLVER_050C     0x050c  // source/chara/torture/revolver.c
#define CHARA_REVOLVER_05AF     0x05af  // source/onoda/s04b/revolver.c
#define CHARA_A_SHOWER          0x05ef  // source/okajima/a_shower.c (PC-ONLY)
#define CHARA_VMODEL            0x0a02  // GV_StrCode("モデル") source/thing/vmodel.c (PC-ONLY)
#define CHARA_VRSPARK           0x0c09  // source/koba/vr/vrspark.c
#define CHARA_BG_HEX_S          0x0d9b  // source/okajima/photo/bg_hex_s.c
#define CHARA_VOICE_SYSTEM      0x0dc9  // source/takabe/voicesys.c
#define CHARA_MOTION_SE         0x0fad  // source/chara/others/motse.c
#define CHARA_ELECTRIC_DAMAGE   0x107c  // source/takabe/elc_damg.c
#define CHARA_PERAPICT          0x10ff  // source/chara/others/perapict.c
#define CHARA_BLOODY_MERYL      0x1158  // GV_StrCode("血まみれメリル") source/okajima/meryl10/mel10.c
#define CHARA_FIND_TRAP         0x118c  // source/takabe/findtrap.c
#define CHARA_HIND_11E9         0x11e9  // source/chara/hind/hind.c
#define CHARA_BG2               0x1454  // GV_StrCode("ＶＲ背景２") source/koba/vr/bg2.c
#define CHARA_BG3               0x1455  // GV_StrCode("ＶＲ背景３") source/koba/vr/bg3.c
#define CHARA_11G_DEMO          0x153e  // source/okajima/11g_demo.c
#define CHARA_P_LAMP            0x169c  // source/okajima/p_lamp.c
#define CHARA_SMOKE             0x170c  // GV_StrCode("煙") source/enemy/smoke.c
#define CHARA_UNKNOWN_173C      0x173c  // (PSX-ONLY)
#define CHARA_SMKTRGT           0x175b  // source/okajima/smktrgt.c
#define CHARA_HIND_1787         0x1787  // source/chara/hind/hind.c
#define CHARA_BG_SP             0x17f5  // source/okajima/photo/bg_sp.c (PC-ONLY)
#define CHARA_SNOW              0x18e3  // GV_StrCode("雪") source/thing/snow.c
#define CHARA_BUBBLE_S          0x1a02  // GV_StrCode("泡") source/okajima/bubble_s.c
#define CHARA_LAMP              0x1ad3  // source/game/lamp.c
#define CHARA_JOHNNY            0x1ef9  // GV_StrCode("ジョニー") source/chara/torture/johnny.c
#define CHARA_BG_STAGE          0x1fa5  // source/okajima/photo/bg_stage.c
#define CHARA_PANEL             0x20f2  // GV_StrCode("パネル") source/takabe/panel.c
#define CHARA_TIMER             0x22c6  // GV_StrCode("カウントダウン") source/enemy/timer.c
#define CHARA_JEEP_EMY          0x2477  // source/takabe/jeep_emy/jeep_emy.c
#define CHARA_VR_CHECK          0x26bc  // source/nobu/vr_slct/vr_check.c
#define CHARA_SNE_03C_27A2      0x27a2  // source/chara/torture/sne_03c.c
#define CHARA_BED               0x2a21  // source/chara/torture/bed.c
#define CHARA_GCL_ARRAY         0x2a90  // source/takabe/gclarray.c
#define CHARA_ELEVATOR          0x2abc  // GV_StrCode("エレベータ") source/takabe/elevator.c
#define CHARA_WALL_SPA          0x2b24  // source/okajima/wall_spa.c
#define CHARA_SECOND_2D0A       0x2d0a  // source/game/second.c
#define CHARA_NINJA             0x30ba  // GV_StrCode("忍者") source/animal/ninja/ninja.c
#define CHARA_VR2               0x30c8  // GV_StrCode("ＶＲ２") source/koba/vr/vr2.c
#define CHARA_PATO_LAMP         0x30ce  // GV_StrCode("パトランプ") source/okajima/pato_lmp.c
#define CHARA_ZAKO10            0x31e3  // GV_StrCode("ざこ１０") source/animal/zako10/zako10.c
#define CHARA_ZAKO14            0x31e7  // GV_StrCode("ざこ１４") source/animal/zako14/zako14.c
#define CHARA_ZAKO19            0x31ec  // GV_StrCode("ざこ１９") source/animal/zako19/zako19.c
#define CHARA_EMITTER           0x32e5  // source/thing/emitter.c
#define CHARA_BREAK_OBJECT      0x32fc  // source/takabe/breakobj.c
#define CHARA_DUCTMOUS          0x3303  // source/okajima/ductmous.c
#define CHARA_MOVIE_3453        0x3453  // source/game/movie.c
#define CHARA_DEMOSEL           0x3686  // source/onoda/demosel/demosel.c
#define CHARA_OPENA             0x3ac3  // source/onoda/opena/opena.c
#define CHARA_UNKNOWN_3AD2      0x3ad2  // ???
#define CHARA_CLAYMORE          0x3c0c  // GV_StrCode("クレイモア地雷") source/bullet/jirai.c
#define CHARA_KOBA_WINMNGR      0x3d26  // source/koba/vr_slct/winmngr.c
#define CHARA_UNKNOWN_3D78      0x3d78  // (PSX-ONLY)
#define CHARA_PAD_DEMO          0x3ed7  // GV_StrCode("パッドデモ") source/takabe/pad_demo.c
#define CHARA_ENV_SOUND         0x3f9a  // source/takabe/env_snd.c
#define CHARA_PLAY_DEMO         0x3f9d  // source/nobu/vr_demo/playdemo.c (PC-ONLY)
#define CHARA_10A_DEMO          0x40e9  // source/okajima/10a_demo.c
#define CHARA_BREATH            0x4170  // GV_StrCode("スネーク息") source/chara/snake/breath.c
#define CHARA_WAKE              0x41a3  // source/chara/wake/wake.c
#define CHARA_LIFT              0x425f  // GV_StrCode("リフト") source/takabe/lift.c
#define CHARA_HIYOKO            0x42e4  // source/okajima/hiyoko.c
#define CHARA_CENSOR            0x43a0  // GV_StrCode("赤外線センサー") source/takabe/ir_cens.c
#define CHARA_HAIR_M            0x450f  // source/chara/others/hair_m.c
#define CHARA_MGREX             0x4754  // source/kojo/mgrex.c
#define CHARA_OBJECT            0x4811  // source/enemy/object.c
#define CHARA_AB_DEMO1          0x4974  // GV_StrCode("アブストデモ１") source/onoda/abst/ab_demo1.c
#define CHARA_AB_DEMO2          0x4975  // GV_StrCode("アブストデモ２") source/onoda/abst/ab_demo2.c
#define CHARA_VRGLASS           0x49d2  // GV_StrCode("ＶＲガラス") source/koba/vr/vrglass.c
#define CHARA_DRUM2             0x4be8  // GV_StrCode("ドラム缶２") source/takabe/drum2.c
#define CHARA_VRCLEAR           0x4deb  // GV_StrCode("ＶＲクリア") source/koba/vr/vrclear.c
#define CHARA_BLOOD_CL          0x4e95  // GV_StrCode("血溜り") source/okajima/blood_cl.c
#define CHARA_SNDTST            0x4efc  // source/game/sndtst.c
#define CHARA_JPEG_CAMERA       0x4f02  // GV_StrCode("ＪＰＥＧカメラ")
#define CHARA_MERYL7            0x5078  // source/enemy/meryl7.c
#define CHARA_RCM               0x50ae  // GV_StrCode("RCM")
#define CHARA_POINT             0x5147  // source/game/point.c
#define CHARA_CAT_IN            0x51c6  // source/takabe/cat_in.c
#define CHARA_KIKEN             0x52bf  // source/enemy/kiken.c (危険 = danger)
#define CHARA_MOVIE_5345        0x5345  // movie.c
#define CHARA_UNKNOWN_53C7      0x53c7  // ???
#define CHARA_VRBOX2_548E       0x548e  // GV_StrCode("ＶＲＢＯＸ２") source/koba/vr/vrbox2.c
#define CHARA_VRBOX2_548F       0x548f  // GV_StrCode("ＶＲＢＯＸ３") source/koba/vr/vrbox2.c
#define CHARA_VRBOX_5490        0x5490  // GV_StrCode("ＶＲＢＯＸ４") source/koba/vr/vrbox.c
#define CHARA_VRTITLE           0x5667  // GV_StrCode("ＶＲタイトル") source/chara/vrtitle/vrtitle.c
#define CHARA_ABST              0x566f  // GV_StrCode("アブスト") source/onoda/abst/abst.c
#define CHARA_CAMERA2           0x56cc  // GV_StrCode("カメラ２") source/enemy/camera2.c
#define CHARA_DMYWALL           0x58f0  // GV_StrCode("塗り壁") source/takabe/dummy_wl.c
#define CHARA_GAS_EFFECT        0x5a50  // source/takabe/gas_efct.c
#define CHARA_O2_DAMAGE         0x5d64  // source/takabe/o2_damge.c
#define CHARA_ZK11ACOM          0x5efa  // GV_StrCode("ざこ１１ａコマンダー") source/animal/zako11a/zk11acom.c
#define CHARA_PAPER             0x5f02  // source/takabe/paper.c
#define CHARA_ZK11ECOM          0x5f0a  // GV_StrCode("ざこ１１ｅコマンダー") source/animal/zako11e/zk11ecom.c
#define CHARA_ZK11FCOM          0x5f0e  // GV_StrCode("ざこ１１ｆコマンダー") source/animal/zako11f/zk11fcom.c
#define CHARA_GROUND_CAMERA     0x5f5a  // source/thing/grd_cam.c (PC-ONLY)
#define CHARA_RASEN             0x5fd9  // source/takabe/rasen.c
#define CHARA_SCN_BOMB          0x600d  // source/okajima/scn_bomb.c (PC-ONLY)
#define CHARA_RIPPLES           0x63aa  // source/takabe/ripples.c
#define CHARA_POCKET_6414       0x6414  // --> source/menu/pocket.c
#define CHARA_BTN_CHK           0x6471  // source/takabe/btn_chk.c
#define CHARA_SNWARP            0x672e  // GV_StrCode("スネークワープ") source/enemy/snwarp.c
#define CHARA_TEX_SCRL          0x6865  // source/takabe/tex_scrl.c
#define CHARA_WT_OBJ            0x69ad  // source/takabe/wt_obj.c (PC-ONLY)
#define CHARA_JEEP_SRL          0x6a48  // source/takabe/jeep_srl.c
#define CHARA_BLOOD_BL_6A4C     0x6a4c  // GV_StrCode("血溜り２") source/okajima/blood_bl.c
#define CHARA_DSMOKE            0x6a98  // source/chara/rope/dsmoke.c (PC-ONLY)
#define CHARA_B_SMOKE           0x6b6c  // source/animal/liquid/b_smoke.c
#define CHARA_DOG               0x6c0e  // source/okajima/dog/dog.c
#define CHARA_VIB_EDIT          0x6c66  // source/takabe/vib_edit.c
#define CHARA_PREOPE            0x6d1b  // source/onoda/preope/preope.c
#define CHARA_MONITOR1          0x6d78  // GV_StrCode("モニタ１") source/takabe/monitor1.c
#define CHARA_CAMERA            0x6e90  // GV_StrCode("カメラ") source/enemy/camera.c
#define CHARA_WATCHER           0x6e9a  // GV_StrCode("巡回兵") source/enemy/watcher.c
#define CHARA_PSYOBJ            0x710d  // source/chara/psyco/psyobj.c
#define CHARA_LIFE_UP           0x711f  // source/takabe/life_up.c
#define CHARA_PADDEMO2          0x720d  // GV_StrCode("パッドデモ２") source/nobu/vr_demo/paddemo2.c
#define CHARA_SPHERE            0x73ea  // GV_StrCode("天球") source/thing/sphere.c
#define CHARA_DOOR2             0x73f8  // GV_StrCode("ドア２") source/takabe/door2.c
#define CHARA_SNAKE18           0x760e  // GV_StrCode("スネーク１８") source/animal/snake18/snake18.c
#define CHARA_DSMOKE2           0x76bc  // source/chara/rope/dsmoke2.c
#define CHARA_ENV_TEST          0x76fe  // source/takabe/env_test.c (PC-ONLY)
#define CHARA_CHAIR             0x788d  // GV_StrCode("椅子") source/takabe/chair.c
#define CHARA_CINEMA            0x7a05  // GV_StrCode("シネマスクリーン") source/takabe/cinema.c
#define CHARA_MODEL_DT          0x7acf  // source/okajima/photo/model_dt.c (PC-ONLY)
#define CHARA_CAMERA_SHAKE      0x7bc2  // source/takabe/camshake.c
#define CHARA_LIQUID            0x7bf2  // GV_StrCode("リキッド") source/animal/liquid/liquid.c
#define CHARA_ZAKOCOM           0x7cf7  // GV_StrCode("ざこコマンダー") source/animal/zako/zakocom.c
#define CHARA_WIRE              0x7eca  // GV_StrCode("ワイヤ") source/onoda/s04b/wire.c
#define CHARA_TELOP_SET         0x7ff7  // GV_StrCode("テロップ") source/takabe/telop.c
#define CHARA_BLINK_TX          0x8185  // source/okajima/blink_tx.c
#define CHARA_CAMERA_JPEG       0x81c7  // GV_StrCode("ＪＰＥＧ") camera.c
#define CHARA_RSURFACE          0x81ea  // source/takabe/rsurface.c
#define CHARA_SCN_ANIM          0x8427  // source/okajima/scn_anim.c
#define CHARA_FONT_TEXT         0x84e1  // source/chara/others/fonttext.c
#define CHARA_VRDEMO            0x8a46  // GV_StrCode("ＶＲデモ") source/koba/demo/demomngr.c
#define CHARA_LANDING           0x8b1a  // source/chara/rope/landing.c
#define CHARA_OPTA              0x8d31  // source/onoda/optiona/opta.c
#define CHARA_GAS_DAMAGE        0x8d5a  // source/takabe/gasdamge.c
#define CHARA_WT_VIEW           0x8e45  // source/takabe/wt_view.c
#define CHARA_CROW              0x8e60  // GV_StrCode("カラス") source/okajima/valcan/crow.c
#define CHARA_ZK10COM           0x8e64  // GV_StrCode("ざこ１０コマンダー") source/animal/zako10/zk10com.c
#define CHARA_GLASS             0x8e70  // GV_StrCode("ガラス") source/takabe/glass.c
#define CHARA_ZK14COM           0x8e74  // GV_StrCode("ざこ１４コマンダー") source/animal/zako14/zk14com.c
#define CHARA_ZK19COM           0x8e88  // GV_StrCode("ざこ１９コマンダー") source/animal/zako19/zk19com.c
#define CHARA_POCKET_8FDC       0x8fdc  // --> source/menu/pocket.c
#define CHARA_SNOWAREA          0x901e  // source/okajima/snowarea.c
#define CHARA_UNKNOWN_9093      0x9093  // GV_StrCode("ブラー") ???
#define CHARA_ITEM_DOT          0x917b  // source/okajima/item_dot.c
#define CHARA_PUTHZD            0x91aa  // source/takabe/puthzd.c
#define CHARA_LIFT2             0x921b  // GV_StrCode("リフト２") source/takabe/lift2.c (PC-ONLY)
#define CHARA_ASIOTO            0x92bc  // source/enemy/asioto.c (足音 = footstep)
#define CHARA_MLOAD             0x9302  // source/menu/mload.c
#define CHARA_B_SELECT          0x93b6  // source/onoda/brf/b_select.c
#define CHARA_MG_DEMO1          0x954b  // source/takabe/mg_demo1.c
#define CHARA_WOLF2             0x962c  // GV_StrCode("ウルフ") source/okajima/wolf/wolf2.c
#define CHARA_WATER             0x96b5  // source/takabe/water.c (PC-ONLY)
#define CHARA_OPT               0x976c  // source/onoda/option/opt.c
#define CHARA_AT                0x9988  // GV_StrCode("ＡＴ") source/onoda/s04b/at.c
#define CHARA_ELE_CROW          0x9ab9  // source/okajima/valcan/ele_crow.c
#define CHARA_PLASMA_9BC2       0x9bc2  // GV_StrCode("プラズマ") source/okajima/plasma.c
#define CHARA_PK_GATE           0x9c6c  // source/takabe/pk_gate.c
#define CHARA_DMYFLOOR          0x9d00  // GV_StrCode("落とし穴") source/takabe/dummy_fl.c
#define CHARA_M1E1              0x9d71  // source/kojo/m1e1.c
#define CHARA_GODZCOM           0x9eb7  // GV_StrCode("ゴジラコマンダ") source/animal/godzila/godzcom.c
#define CHARA_DISPLAY           0x9f7d  // source/chara/pocket/display/display.c
#define CHARA_VALCAN            0x9ff5  // GV_StrCode("バルカン") source/okajima/valcan/valcan.c
#define CHARA_SECOND_9FFD       0x9ffd  // source/game/second.c
#define CHARA_FADE_IN_OUT       0xa12e  // source/takabe/fadeio.c
#define CHARA_JDRUM             0xa27e  // source/takabe/jeep/jdrum.c
#define CHARA_SAFETY            0xa2b5  // safety.c
#define CHARA_CRANE             0xa3fb  // GV_StrCode("クレーン") source/okajima/crane.c
#define CHARA_SNE_03C_A404      0xa404  // source/chara/torture/sne_03c.c
#define CHARA_WT_AREA2          0xa480  // source/takabe/wt_area2.c
#define CHARA_PAUSE_MENU        0xa5dc  // source/koba/vr/pausmenu.c
#define CHARA_ZAKO11A           0xa608  // GV_StrCode("ざこ１１ａ") source/animal/zako11a/zako11a.c
#define CHARA_ZAKO11E           0xa60c  // GV_StrCode("ざこ１１ｅ") source/animal/zako11e/zako11e.c
#define CHARA_ZAKO11F           0xa60d  // GV_StrCode("ざこ１１ｆ") source/animal/zako11f/zako11f.c
#define CHARA_SSTORM            0xa6f5  // GV_StrCode("雪嵐") source/kojo/sstorm.c
#define CHARA_UNKNOWN_A6F6      0xa6f6  // --> kmdarutl.c
#define CHARA_PSYCO             0xa76f  // GV_StrCode("サイコマンティス") source/chara/psyco/psyco.c
#define CHARA_SNE17A            0xa791  // source/chara/sne17a/sne17a.c (PC-ONLY)
#define CHARA_GUNCAME           0xa9c5  // source/okajima/guncame.c
#define CHARA_EMITTER2          0xa9dd  // source/thing/emitter2.c (PC-ONLY)
#define CHARA_UNKNOWN_AA13      0xaa13  // ???
#define CHARA_RASEN_EL          0xaa21  // source/takabe/rasen_el.c
#define CHARA_FURNACE           0xadd8  // source/takabe/furnace.c
#define CHARA_NOBU_WINMNGR      0xae06  // source/nobu/vr_slct/winmngr.c
#define CHARA_ELECTRIC_FLOOR    0xaef2  // source/takabe/elc_flr.c
#define CHARA_TOBCNT            0xaefb  // source/game/tobcnt.c
#define CHARA_DYNAMIC_FLOOR     0xaf6c  // GV_StrCode("透明床") source/takabe/dymc_flr.c
#define CHARA_MEMPSY            0xaf72  // source/chara/psyco/mempsy.c
#define CHARA_PRESENT           0xaf75  // source/nobu/present/present.c (PC-ONLY)
#define CHARA_BG_ST1            0xb032  // source/okajima/photo/bg_st1.c
#define CHARA_BG_ST2            0xb033  // source/okajima/photo/bg_st2.c (PC-ONLY)
#define CHARA_DYNAMIC_SEGMENT   0xb103  // GV_StrCode("透明壁") source/takabe/dymc_seg.c
#define CHARA_SNAKE_E1          0xb162  // source/okajima/snake_e1.c
#define CHARA_UNKNOWN_B30A      0xb30a  // (PSX-ONLY)
#define CHARA_PJEEP             0xb47a  // source/takabe/pjeep.c
#define CHARA_CANCEL            0xb4e6  // GV_StrCode("デモキャンセル") source/game/cancel.c
#define CHARA_DRUM              0xb58d  // GV_StrCode("ドラム缶") source/takabe/drum.c
#define CHARA_ED_TELOP_B757     0xb757  // source/takabe/ed_telop.c (?)
#define CHARA_ENDING2           0xb789  // source/takabe/ending2.c
#define CHARA_BG_SP_CM          0xb7ae  // source/okajima/photo/bg_sp_cm.c (PC-ONLY)
#define CHARA_NINJA_PLAYABLE    0xb8d4  // source/chara/njaplay/njaplay.c
#define CHARA_OPTP              0xb916  // source/onoda/optionp/optp.c
#define CHARA_HIND2             0xb959  // source/chara/hind2/hind2.c
#define CHARA_CLUTER            0xb95f  // source/koba/vr/cluter.c (PC-ONLY)
#define CHARA_M_DOOR            0xb98c  // source/enemy/m_door.c
#define CHARA_CAPE              0xb99f  // source/onoda/s04b/cape.c
#define CHARA_SHAKE_MODEL       0xba52  // source/takabe/shakemdl.c
#define CHARA_BG_SP_ST          0xbc76  // source/okajima/photo/bg_sp_st.c (PC-ONLY)
#define CHARA_ROPE              0xbda8  // --> source/chara/rope/rope.c
#define CHARA_DEATH_SP          0xbe79  // source/okajima/death_sp.c
#define CHARA_SPHERE2           0xbee1  // GV_StrCode("天球２") source/thing/sphere2.c
#define CHARA_OTACOM            0xbf66  // source/chara/torture/otacom.c
#define CHARA_BUB_D_SN          0xc0fe  // source/okajima/bub_d_sn.c
#define CHARA_MIRROR            0xc218  // source/takabe/mirror.c
#define CHARA_VRCLEAR2          0xc249  // GV_StrCode("ＶＲクリア２") source/koba/vr/vrclear2.c
#define CHARA_VRCLEAR3          0xc24a  // GV_StrCode("ＶＲクリア３") source/koba/vr/vrclear3.c (PC-ONLY)
#define CHARA_PIPE              0xc35f  // source/chara/rope/pipe.c
#define CHARA_SAVE_MANAGER      0xc5b7  // source/nobu/vr_save/savemngr.c
#define CHARA_KEY_ITEM          0xc6ac  // source/okajima/key_item.c
#define CHARA_COMMAND           0xc6d7  // GV_StrCode("コマンダー") source/enemy/command.c
#define CHARA_FALL_SPLASH       0xc73e  // source/okajima/fall_spl.c
#define CHARA_MERYL3            0xc755  // source/animal/meryl3/meryl3.c
#define CHARA_LOADREP           0xc8ca  // source/nobu/vr/loadrep.c
#define CHARA_GODZILA           0xcb1f  // GV_StrCode("ゴジラ") source/animal/godzila/godzila.c
#define CHARA_TRACK_TRAP        0xcb3a  // source/takabe/tracktrp.c
#define CHARA_BG_HEX            0xcbeb  // source/okajima/photo/bg_hex.c (PC-ONLY)
#define CHARA_PAD               0xcbf8  // GV_StrCode("パッドコントロール") source/game/pad.c
#define CHARA_DYNCON            0xcc45  // GV_StrCode("コンテナ") source/okajima/valcan/dyncon.c
#define CHARA_BG_HEX_P          0xcc89  // source/okajima/photo/bg_hex_p.c (PC-ONLY)
#define CHARA_UNKNOWN_CCD3      0xccd3  // ??? (PC-ONLY)
#define CHARA_UNKNOWN_CF00      0xcf00  // ???
#define CHARA_AB_CH             0xcf72  // source/onoda/abst/ab_ch.c
#define CHARA_OPEN              0xcf79  // GV_StrCode("タイトル") source/onoda/open/open.c
#define CHARA_OPENP             0xcfef  // source/onoda/openp/openp.c
#define CHARA_BACKGROUND        0xd07f  // GV_StrCode("ＶＲ背景") source/koba/vr/backgrnd.c
#define CHARA_SELECT            0xd2f6  // source/game/select.c
#define CHARA_UNKNOWN_D3C0      0xd3c0  // ???
#define CHARA_VRWINDOW          0xd44e  // GV_StrCode("ＶＲウィンドウ") source/koba/vr/vrwindow.c
#define CHARA_MOUSE             0xd4a5  // source/okajima/mouse.c
#define CHARA_11B_DEMO          0xd53c  // source/okajima/11b_demo.c
#define CHARA_M1E1CAME          0xd5ec  // source/kojo/m1e1came.c
#define CHARA_FOG               0xd6fb  // source/takabe/fog.c
#define CHARA_NINJA_D8DD        0xd8dd  // source/chara/torture/ninja.c
#define CHARA_GOAL              0xdb1f  // GV_StrCode("ゴール") source/koba/vr/goal.c
#define CHARA_WT_AREA           0xdba3  // source/takabe/wt_area.c
#define CHARA_TEXANIME          0xdcac  // source/enemy/texanime.c (PC-ONLY)
#define CHARA_INTR_CAM          0xdd8b  // source/chara/others/intr_cam.c
#define CHARA_PANEL2            0xdd95  // GV_StrCode("パネル２") source/takabe/panel2.c
#define CHARA_VRBOX_DF07        0xdf0f  // GV_StrCode("ＶＲＢＯＸ") source/koba/vr/vrbox.c
#define CHARA_S11_OBJS          0xe068  // source/okajima/s11_objs.c
#define CHARA_ELEVATOR_PANEL    0xe253  // source/game/evpanel.c
#define CHARA_MERYL72           0xe271  // source/animal/meryl72/meryl72.c
#define CHARA_RED_ALERT_E397    0xe397  // source/okajima/red_alrt.c
#define CHARA_DOLL2             0xe448  // source/takabe/doll2.c
#define CHARA_TORTURE           0xe608  // source/chara/torture/torture.c
#define CHARA_ED_TELOP          0xe75a  // source/takabe/ed_telop.c
#define CHARA_DOLL              0xe97e  // GV_StrCode("デモ人形") source/animal/doll/doll.c
#define CHARA_WALL              0xec77  // GV_StrCode("障害物") source/enemy/wall.c
#define CHARA_PAUSE             0xeced  // --> source/menu/countdwn.c
#define CHARA_VR                0xed86  // GV_StrCode("ＶＲ") source/koba/vr/vr.c
#define CHARA_ZAKO              0xed87  // GV_StrCode("ざこ") source/animal/zako/zako.c
#define CHARA_PHOTOSEL          0xedeb  // source/chara/photosel/photosel.c
#define CHARA_SCN_MARK          0xee63  // source/okajima/scn_mark.c
#define CHARA_WSURFACE          0xeea7  // source/takabe/wsurface.c
#define CHARA_HAIR_N            0xf002  // source/chara/others/hair_n.c
#define CHARA_REC_DEMO          0xf364  // source/nobu/vr_demo/recdemo.c (PC-ONLY)
#define CHARA_MERYL07B          0xf4b0  // GV_StrCode("サイコメリル") source/chara/meryl07b/meryl07b.c
#define CHARA_PUT_OBJECT        0xf4c3  // source/takabe/put_obj.c
#define CHARA_SEARCH_LIGHT      0xf50f  // GV_StrCode("サーチライト") source/enemy/searchli.c
#define CHARA_BELONG            0xf59e  // source/chara/others/belong.c
#define CHARA_UJI               0xf5c5  // source/okajima/uji.c
#define CHARA_CHANGE            0xf722  // source/onoda/change/change.c
#define CHARA_BOXALL            0xf74b  // source/chara/torture/boxall.c
#define CHARA_MOVIE_FAA8        0xfaa8  // source/chara/movie/movie.c
#define CHARA_FLR_SPA           0xfc0b  // source/okajima/flr_spa.c
#define CHARA_POCKET_FDB6       0xfdb6  // source/menu/pocket.c
#define CHARA_VIBRATE           0xfed1  // GV_StrCode("パッド振動") source/game/vibrate.c

//-----------------------------------------------------------------------------
// Stage IDs
//-----------------------------------------------------------------------------

#define STAGE_abst              0x1706  // GV_StrCode("abst")
#define STAGE_brf               0x96a7  // GV_StrCode("brf")
#define STAGE_camera            0xeee9  // GV_StrCode("camera")
#define STAGE_change            0x11f8  // GV_StrCode("change")
#define STAGE_d00a              0xc693  // GV_StrCode("d00a")
#define STAGE_d00aa             0xd2d9  // GV_StrCode("d00aa")
#define STAGE_d01a              0xc6b3  // GV_StrCode("d01a")
#define STAGE_d03a              0xc6f3  // GV_StrCode("d03a")
#define STAGE_d11c              0xcab5  // GV_StrCode("d11c")
#define STAGE_d16e              0xcb57  // GV_StrCode("d16e")
#define STAGE_d18a              0xcb93  // GV_StrCode("d18a")
#define STAGE_d18ar             0x72eb  // GV_StrCode("d18ar")
#define STAGE_demosel           0x2a2f  // GV_StrCode("demosel")
#define STAGE_ending            0x833b  // GV_StrCode("ending")
#define STAGE_endingr           0x67e2  // GV_StrCode("endingr")
#define STAGE_init              0x45ca  // GV_StrCode("init")
#define STAGE_init_tux          0xbbed  // GV_StrCode("init_tux")
#define STAGE_init_ve           0xae0b  // GV_StrCode("init_ve")
#define STAGE_movie             0x6c8e  // GV_StrCode("movie")
#define STAGE_opening           0x58cc  // GV_StrCode("opening")
#define STAGE_openinga          0x19ec  // GV_StrCode("openinga")
#define STAGE_option            0x978a  // GV_StrCode("option")
#define STAGE_optiona           0xf1b3  // GV_StrCode("optiona")
#define STAGE_optionp           0xf1c2  // GV_StrCode("optionp")
#define STAGE_photo_m1          0xf2e4  // GV_StrCode("photo_m1")
#define STAGE_photo_m2          0xf2e5  // GV_StrCode("photo_m2")
#define STAGE_photo_n1          0xf304  // GV_StrCode("photo_n1")
#define STAGE_photo_n2          0xf305  // GV_StrCode("photo_n2")
#define STAGE_photo_n3          0xf306  // GV_StrCode("photo_n3")
#define STAGE_preope            0x31ba  // GV_StrCode("preope")
#define STAGE_rank              0x9265  // GV_StrCode("rank")
#define STAGE_roll              0xca26  // GV_StrCode("roll")
#define STAGE_s00a              0x469b  // GV_StrCode("s00a")
#define STAGE_s00aa             0xd3c9  // GV_StrCode("s00aa")
#define STAGE_s01a              0x46bb  // GV_StrCode("s01a")
#define STAGE_s02a              0x46db  // GV_StrCode("s02a")
#define STAGE_s02b              0x46dc  // GV_StrCode("s02b")
#define STAGE_s02c              0x46dd  // GV_StrCode("s02c")
#define STAGE_s02d              0x46de  // GV_StrCode("s02d")
#define STAGE_s02e              0x46df  // GV_StrCode("s02e")
#define STAGE_s03a              0x46fb  // GV_StrCode("s03a")
#define STAGE_s03ar             0xdfda  // GV_StrCode("s03ar")
#define STAGE_s03b              0x46fc  // GV_StrCode("s03b")
#define STAGE_s03c              0x46fd  // GV_StrCode("s03c")
#define STAGE_s03d              0x46fe  // GV_StrCode("s03d")
#define STAGE_s03dr             0xe03a  // GV_StrCode("s03dr")
#define STAGE_s03e              0x46ff  // GV_StrCode("s03e")
#define STAGE_s03er             0xe05a  // GV_StrCode("s03er")
#define STAGE_s04a              0x471b  // GV_StrCode("s04a")
#define STAGE_s04b              0x471c  // GV_StrCode("s04b")
#define STAGE_s04br             0xe3fa  // GV_StrCode("s04br")
#define STAGE_s04c              0x471d  // GV_StrCode("s04c")
#define STAGE_s05a              0x473b  // GV_StrCode("s05a")
#define STAGE_s06a              0x475b  // GV_StrCode("s06a")
#define STAGE_s07a              0x477b  // GV_StrCode("s07a")
#define STAGE_s07b              0x477c  // GV_StrCode("s07b")
#define STAGE_s07br             0xeffa  // GV_StrCode("s07br")
#define STAGE_s07c              0x477d  // GV_StrCode("s07c")
#define STAGE_s07cr             0xf01a  // GV_StrCode("s07cr")
#define STAGE_s08a              0x479b  // GV_StrCode("s08a")
#define STAGE_s08b              0x479c  // GV_StrCode("s08b")
#define STAGE_s08br             0xf3fa  // GV_StrCode("s08br")
#define STAGE_s08c              0x479d  // GV_StrCode("s08c")
#define STAGE_s08cr             0xf41a  // GV_StrCode("s08cr")
#define STAGE_s09a              0x47bb  // GV_StrCode("s09a")
#define STAGE_s09ar             0xf7da  // GV_StrCode("s09ar")
#define STAGE_s10a              0x4a9b  // GV_StrCode("s10a")
#define STAGE_s10ar             0x53db  // GV_StrCode("s10ar")
#define STAGE_s11a              0x4abb  // GV_StrCode("s11a")
#define STAGE_s11b              0x4abc  // GV_StrCode("s11b")
#define STAGE_s11c              0x4abd  // GV_StrCode("s11c")
#define STAGE_s11d              0x4abe  // GV_StrCode("s11d")
#define STAGE_s11e              0x4abf  // GV_StrCode("s11e")
#define STAGE_s11g              0x4ac1  // GV_StrCode("s11g")
#define STAGE_s11h              0x4ac2  // GV_StrCode("s11h")
#define STAGE_s11i              0x4ac3  // GV_StrCode("s11i")
#define STAGE_s12a              0x4adb  // GV_StrCode("s12a")
#define STAGE_s12b              0x4adc  // GV_StrCode("s12b")
#define STAGE_s12c              0x4add  // GV_StrCode("s12c")
#define STAGE_s13a              0x4afb  // GV_StrCode("s13a")
#define STAGE_s14e              0x4b1f  // GV_StrCode("s14e")
#define STAGE_s15a              0x4b3b  // GV_StrCode("s15a")
#define STAGE_s15b              0x4b3c  // GV_StrCode("s15b")
#define STAGE_s15c              0x4b3d  // GV_StrCode("s15c")
#define STAGE_s16a              0x4b5b  // GV_StrCode("s16a")
#define STAGE_s16b              0x4b5c  // GV_StrCode("s16b")
#define STAGE_s16c              0x4b5d  // GV_StrCode("s16c")
#define STAGE_s16d              0x4b5e  // GV_StrCode("s16d")
#define STAGE_s17a              0x4b7b  // GV_StrCode("s17a")
#define STAGE_s17ar             0x6fdb  // GV_StrCode("s17ar")
#define STAGE_s18a              0x4b9b  // GV_StrCode("s18a")
#define STAGE_s18ar             0x73db  // GV_StrCode("s18ar")
#define STAGE_s19a              0x4bbb  // GV_StrCode("s19a")
#define STAGE_s19ar             0x77db  // GV_StrCode("s19ar")
#define STAGE_s19b              0x4bbc  // GV_StrCode("s19b")
#define STAGE_s19br             0x77fb  // GV_StrCode("s19br")
#define STAGE_s20a              0x4e9b  // GV_StrCode("s20a")
#define STAGE_s20ar             0xd3db  // GV_StrCode("s20ar")
#define STAGE_select            0x8d5c  // GV_StrCode("select")
#define STAGE_select1           0xabc2  // GV_StrCode("select1")
#define STAGE_select2           0xabc3  // GV_StrCode("select2")
#define STAGE_select3           0xabc4  // GV_StrCode("select3")
#define STAGE_select4           0xabc5  // GV_StrCode("select4")
#define STAGE_selectd           0xabf5  // GV_StrCode("selectd")
#define STAGE_selectvr          0x8167  // GV_StrCode("selectvr")
#define STAGE_sound             0x698d  // GV_StrCode("sound")
#define STAGE_title             0x655b  // GV_StrCode("title")
#define STAGE_titlea            0xabcd  // GV_StrCode("titlea")
#define STAGE_titlep            0xabdc  // GV_StrCode("titlep")
#define STAGE_vab_cfr           0x61a1  // GV_StrCode("vab_cfr")
#define STAGE_vab_clm           0x625c  // GV_StrCode("vab_clm")
#define STAGE_vab_fms           0x6e82  // GV_StrCode("vab_fms")
#define STAGE_vab_grn           0x731d  // GV_StrCode("vab_grn")
#define STAGE_vab_nkt           0x8e43  // GV_StrCode("vab_nkt")
#define STAGE_vab_psg           0x9736  // GV_StrCode("vab_psg")
#define STAGE_vab_scm           0xa13c  // GV_StrCode("vab_scm")
#define STAGE_vab_stg           0xa356  // GV_StrCode("vab_stg")
#define STAGE_vab_sud           0xa373  // GV_StrCode("vab_sud")
#define STAGE_vcd_n01           0x8ac0  // GV_StrCode("vcd_n01")
#define STAGE_vcd_n02           0x8ac1  // GV_StrCode("vcd_n02")
#define STAGE_vcd_n03           0x8ac2  // GV_StrCode("vcd_n03")
#define STAGE_vcd_n04           0x8ac3  // GV_StrCode("vcd_n04")
#define STAGE_vcd_n05           0x8ac4  // GV_StrCode("vcd_n05")
#define STAGE_vcd_n06           0x8ac5  // GV_StrCode("vcd_n06")
#define STAGE_vefgh_01          0x98a0  // GV_StrCode("vefgh_01")
#define STAGE_vefgh_02          0x98a1  // GV_StrCode("vefgh_02")
#define STAGE_vefgh_03          0x98a2  // GV_StrCode("vefgh_03")
#define STAGE_vefgh_04          0x98a3  // GV_StrCode("vefgh_04")
#define STAGE_vefgh_05          0x98a4  // GV_StrCode("vefgh_05")
#define STAGE_vefgh_06          0x98a5  // GV_StrCode("vefgh_06")
#define STAGE_vefgh_07          0x98a6  // GV_StrCode("vefgh_07")
#define STAGE_vefgh_08          0x98a7  // GV_StrCode("vefgh_08")
#define STAGE_vefgh_09          0x98a8  // GV_StrCode("vefgh_09")
#define STAGE_vefgh_10          0x98bf  // GV_StrCode("vefgh_10")
#define STAGE_vijkl_01          0xa0e3  // GV_StrCode("vijkl_01")
#define STAGE_vijkl_02          0xa0e4  // GV_StrCode("vijkl_02")
#define STAGE_vijkl_03          0xa0e5  // GV_StrCode("vijkl_03")
#define STAGE_vijkl_04          0xa0e6  // GV_StrCode("vijkl_04")
#define STAGE_vijkl_05          0xa0e7  // GV_StrCode("vijkl_05")
#define STAGE_vijkl_06          0xa0e8  // GV_StrCode("vijkl_06")
#define STAGE_vijkl_07          0xa0e9  // GV_StrCode("vijkl_07")
#define STAGE_vijkl_08          0xa0ea  // GV_StrCode("vijkl_08")
#define STAGE_vijkl_09          0xa0eb  // GV_StrCode("vijkl_09")
#define STAGE_vijkl_10          0xa102  // GV_StrCode("vijkl_10")
#define STAGE_vr01              0xce6d  // GV_StrCode("vr01")
#define STAGE_vr02              0xce6e  // GV_StrCode("vr02")
#define STAGE_vr03              0xce6f  // GV_StrCode("vr03")
#define STAGE_vr04              0xce70  // GV_StrCode("vr04")
#define STAGE_vr05              0xce71  // GV_StrCode("vr05")
#define STAGE_vr06              0xce72  // GV_StrCode("vr06")
#define STAGE_vr07              0xce73  // GV_StrCode("vr07")
#define STAGE_vr08              0xce74  // GV_StrCode("vr08")
#define STAGE_vr09              0xce75  // GV_StrCode("vr09")
#define STAGE_vr10              0xce8c  // GV_StrCode("vr10")
#define STAGE_vr_cfr01          0x1663  // GV_StrCode("vr_cfr01")
#define STAGE_vr_cfr02          0x1664  // GV_StrCode("vr_cfr02")
#define STAGE_vr_cfr03          0x1665  // GV_StrCode("vr_cfr03")
#define STAGE_vr_cfr04          0x1666  // GV_StrCode("vr_cfr04")
#define STAGE_vr_cfr05          0x1667  // GV_StrCode("vr_cfr05")
#define STAGE_vr_clm01          0x0266  // GV_StrCode("vr_clm01")
#define STAGE_vr_clm02          0x0267  // GV_StrCode("vr_clm02")
#define STAGE_vr_clm03          0x0268  // GV_StrCode("vr_clm03")
#define STAGE_vr_clm04          0x0269  // GV_StrCode("vr_clm04")
#define STAGE_vr_clm05          0x026a  // GV_StrCode("vr_clm05")
#define STAGE_vr_fms01          0x9a96  // GV_StrCode("vr_fms01")
#define STAGE_vr_fms02          0x9a97  // GV_StrCode("vr_fms02")
#define STAGE_vr_fms03          0x9a98  // GV_StrCode("vr_fms03")
#define STAGE_vr_fms04          0x9a99  // GV_StrCode("vr_fms04")
#define STAGE_vr_fms05          0x9a9a  // GV_StrCode("vr_fms05")
#define STAGE_vr_grn01          0x06a9  // GV_StrCode("vr_grn01")
#define STAGE_vr_grn02          0x06aa  // GV_StrCode("vr_grn02")
#define STAGE_vr_grn03          0x06ab  // GV_StrCode("vr_grn03")
#define STAGE_vr_grn04          0x06ac  // GV_StrCode("vr_grn04")
#define STAGE_vr_grn05          0x06ad  // GV_StrCode("vr_grn05")
#define STAGE_vr_nkt01          0x9f15  // GV_StrCode("vr_nkt01")
#define STAGE_vr_nkt02          0x9f16  // GV_StrCode("vr_nkt02")
#define STAGE_vr_nkt03          0x9f17  // GV_StrCode("vr_nkt03")
#define STAGE_vr_nkt04          0x9f18  // GV_StrCode("vr_nkt04")
#define STAGE_vr_nkt05          0x9f19  // GV_StrCode("vr_nkt05")
#define STAGE_vr_psg01          0x6b39  // GV_StrCode("vr_psg01")
#define STAGE_vr_psg02          0x6b3a  // GV_StrCode("vr_psg02")
#define STAGE_vr_psg03          0x6b3b  // GV_StrCode("vr_psg03")
#define STAGE_vr_psg04          0x6b3c  // GV_StrCode("vr_psg04")
#define STAGE_vr_psg05          0x6b3d  // GV_StrCode("vr_psg05")
#define STAGE_vr_scm01          0x8361  // GV_StrCode("vr_scm01")
#define STAGE_vr_scm02          0x8362  // GV_StrCode("vr_scm02")
#define STAGE_vr_scm03          0x8363  // GV_StrCode("vr_scm03")
#define STAGE_vr_scm04          0x8364  // GV_StrCode("vr_scm04")
#define STAGE_vr_scm05          0x8365  // GV_StrCode("vr_scm05")
#define STAGE_vr_stg01          0xeb69  // GV_StrCode("vr_stg01")
#define STAGE_vr_stg02          0xeb6a  // GV_StrCode("vr_stg02")
#define STAGE_vr_stg03          0xeb6b  // GV_StrCode("vr_stg03")
#define STAGE_vr_stg04          0xeb6c  // GV_StrCode("vr_stg04")
#define STAGE_vr_stg05          0xeb6d  // GV_StrCode("vr_stg05")
#define STAGE_vr_sud01          0x5f6a  // GV_StrCode("vr_sud01")
#define STAGE_vr_sud02          0x5f6b  // GV_StrCode("vr_sud02")
#define STAGE_vr_sud03          0x5f6c  // GV_StrCode("vr_sud03")
#define STAGE_vr_sud04          0x5f6d  // GV_StrCode("vr_sud04")
#define STAGE_vr_sud05          0x5f6e  // GV_StrCode("vr_sud05")
#define STAGE_vr_sud06          0x5f6f  // GV_StrCode("vr_sud06")
#define STAGE_vr_sud07          0x5f70  // GV_StrCode("vr_sud07")
#define STAGE_vr_sud08          0x5f71  // GV_StrCode("vr_sud08")
#define STAGE_vr_sud09          0x5f72  // GV_StrCode("vr_sud09")
#define STAGE_vr_sud10          0x5f89  // GV_StrCode("vr_sud10")
#define STAGE_vr_sud11          0x5f8a  // GV_StrCode("vr_sud11")
#define STAGE_vr_sud12          0x5f8b  // GV_StrCode("vr_sud12")
#define STAGE_vr_sud13          0x5f8c  // GV_StrCode("vr_sud13")
#define STAGE_vr_sud14          0x5f8d  // GV_StrCode("vr_sud14")
#define STAGE_vr_sud15          0x5f8e  // GV_StrCode("vr_sud15")
#define STAGE_vrdemo            0x9563  // GV_StrCode("vrdemo")
#define STAGE_vrsave            0x0681  // GV_StrCode("vrsave")
#define STAGE_vrtitle           0xc979  // GV_StrCode("vrtitle")

#endif // _STRCODE_H_
