#ifndef _DEMOTHRD_H_
#define _DEMOTHRD_H_

#include <SYS/TYPES.H>
#include <LIBGTE.H>
#include <LIBGPU.H>
#include "libgv/actor.h"
#include "Game/GM_Control.h"
#include "Game/game.h"

typedef struct demothrd_2Vec
{
    SVECTOR field_0;
    SVECTOR field_8;
} demothrd_2Vec;

typedef struct demothrd_0x1C
{
    int field_0_magic;
    int field_4_chunk_size;
    int field_8_movie_frames;
    int field_C_num_maps;
    int field_10_num_models;
    int field_14_pMaps;
    int field_18_pModels;
} demothrd_0x1C;

struct Actor_demothrd_sub;

typedef struct Actor_demothrd_sub
{
    struct Actor_demothrd_sub *field_0_pPrev;
    struct Actor_demothrd_sub *field_4_pNext;
    int                        field_8_flag;
    Actor                      field_C_actor;
    int                        field_2C;
    int                        field_30;
    int                        field_34;
    int                        field_38;
    int                        field_3C;
    int                        field_40;
    int                        field_44;
    int                        field_48;
    int                        field_4C;
    int                        field_50;
    int                        field_54;
    int                        field_58;
    int                        field_5C;
    int                        field_60;
    int                        field_64;
    int                        field_68;
    int                        field_6C;
    int                        field_70;
    int                        field_74;
    int                        field_78;
    int                        field_7C;
    int                        field_80;
    int                        field_84;
    int                        field_88_pDemoData;
    GM_Control                 field_8C_ctrl;
    DG_OBJS                   *field_108_obj;
    int                        field_10C;
    int                        field_110;
    int                        field_114;
    int                        field_118;
    int                        field_11C;
} Actor_demothrd_sub;

typedef struct Actor_demothrd
{
    Actor              field_0_actor;
    int                field_20_flag;
    int                field_24_ticks;
    int                field_28_map;
    int                field_2C_timer_ticks;
    demothrd_0x1C     *field_30_dmo_header;
    int                field_34_pModels;
    Actor_demothrd_sub field_38;
    int                field_158;
    int                field_15C;
    int                field_160;
    int                field_164;
    int                field_168;
    int                field_16C;
    int                field_170;
    int                field_174;
    int                field_178;
    int                field_17C;
    int                field_180;
    int                field_184;
    int                field_188;
    int                field_18C;
    int                field_190;
    int                field_194;
    int                field_198;
    int                field_19C;
    int                field_1A0;
    int                field_1A4;
    int                field_1A8;
    int                field_1AC;
    int                field_1B0;
    int                field_1B4;
    int                field_1B8;
    int                field_1BC;
    int                field_1C0;
    int                field_1C4;
    int                field_1C8;
    int                field_1CC;
    int                field_1D0;
    int                field_1D4;
    int                field_1D8;
    int                field_1DC;
    int                field_1E0;
    int                field_1E4;
    int                field_1E8;
    int                field_1EC;
    int                field_1F0;
    int                field_1F4;
    int                field_1F8;
    int                field_1FC;
    int                field_200;
    int                field_204;
    int                field_208;
    int                field_20C;
    int                field_210;
    int                field_214;
    int                field_218;
    int                field_21C;
    int                field_220;
    MATRIX             field_224_light_mtx;
    int                field_244;
    int                field_248;
    int                field_24C;
    int                field_250;
    int                field_254;
    int                field_258;
    int                field_25C;
    int                field_260;
    int                field_264;
    int                field_268;
    int                field_26C;
    int                field_270_pOldRenderFn;
    int                field_274_old_game_state_flags;
    demothrd_2Vec      field_278_stru[7]; // might actually be 8 ?
    int                field_2E8_end_mark;
    int                field_2EC;
    int                field_2F0;
    int                field_2F4_old_equipped_item;
    int                field_2F8_old_equipped_weapon;
} Actor_demothrd;

int DM_ThreadStream_80079460(int flag, int unused);
int DM_ThreadFile_800794E4(int param_1, int param_2);

#endif // _DEMOTHRD_H_
