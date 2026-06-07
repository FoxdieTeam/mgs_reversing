#ifndef __MGS_STRCODE_H__
#define __MGS_STRCODE_H__

//-----------------------------------------------------------------------------

#define HASH_PAN2               0x922b // GV_StrCode( "pan2" )
#define HASH_ITEM               0x5d43 // GV_StrCode( "item" )

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
#define PCX_EMPTY2              0xb05c // GV_StrCode( "empty2" )
#define PCX_LSIGHT              0x08db // GV_StrCode( "lsight" )
#define PCX_SOCOM_F             0xe4cc // GV_StrCode( "socom_f" )
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
#define PCX_CD_WARN             0xa0f4 // GV_StrCode( "cd_warn" )
#define PCX_CD_KEIKOKU          0xa1bc // GV_StrCode( "cd_keikoku" )
#define PCX_HEAD_LIGHT          0x5699 // GV_StrCode( "head_light" )
#define PCX_M19_C2_GLASS1HLF    0x3cb9 // GV_StrCode( "m19_c2_glass1hlf" )
#define PCX_TAMA_01             0xcb50 // GV_StrCode( "tama_01" )
#define PCX_TAMA_02             0xcb51 // GV_StrCode( "tama_02" )
#define PCX_TAMA_03             0xcb52 // GV_StrCode( "tama_03" )
#define PCX_M60_FLASH           0xc61c // GV_StrCode( "m60_flash" )
#define PCX_JEEP_BONBORI_ADD    0xa7fc // GV_StrCode( "jeep_bonbori_add" )
#define PCX_FIRE2               0x5b68 // GV_StrCode( "fire2" )

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
#define KMD_BOX_01              0x4d5f // GV_StrCode( "box_01" )
#define KMD_LOW_109P            0xff15 // GV_StrCode( "low_109p" )

// Stage s00a/d00a (docks)
#define KMD_SNE_WET2            0x7693 // GV_StrCode( "sne_wet2" )

//-----------------------------------------------------------------------------
// Animation files (.oar)
//-----------------------------------------------------------------------------
#define OAR_SNAKE               0x992d // GV_StrCode( "snake" )
#define OAR_ENEMY               0xa8a1 // GV_StrCode( "enemy" )

//-----------------------------------------------------------------------------
// Chara Names
//-----------------------------------------------------------------------------

#define SNAKE_NAME              0x21ca  // GV_StrCode("スネーク")
#define RCM_NAME                0x50ae  // GV_StrCode("RCM")

#endif // __MGS_STRCODE_H__
