#include "pato_lmp.h"

#include "common.h"
#include "mts/mts.h"
#include "libgv/libgv.h"
#include "libdg/libdg.h"
#include "libgcl/libgcl.h"
#include "Game/object.h"
#include "Game/camera.h"

typedef struct _PatoLmpPrims
{
    DR_TPAGE tpage[2];
    TILE     tile[2];
} PatoLmpPrims;

typedef struct _PatoLmpWork
{
    GV_ACT         actor;
    PatoLmpPrims  *field_20;
    OBJECT         field_24[4];
    OBJECT         field_3B4[4];
    OBJECT         field_744[4];
    OBJECT         field_AD4[4];
    MATRIX         field_E64[4][2];
    MATRIX         field_F64[2];
    SVECTOR        field_FA4[4];
    SVECTOR        field_FC4[4];
    SVECTOR        field_FE4[4];
    int            field_1004;
    DG_PRIM       *field_1008;
    SVECTOR        field_100C[4][8];
    int            field_110C[4];
    SVECTOR        field_111C[4][32];
    SVECTOR        field_151C[4][32];
    int            field_191C;
    int            field_1920;
    int            field_1924;
    SVECTOR        field_1928;
    SVECTOR        field_1930;
    int            field_1938;
    int            field_193C;
    int            field_1940;
    int            field_1944;
    int            map;
    int            name;
    int            field_1950;
    int            field_1954;
    int            field_1958;
    int            field_195C;
    int            field_1960;
    int            field_1964;
} PatoLmpWork;

const char s00a_dword_800E0ADC[] = "開く";
const char s00a_dword_800E0AE4[] = "閉める";
const char s00a_aOpen_800E0AEC[] = "open";
const char s00a_aClose_800E0AF4[] = "close";
const char s00a_aSeon_800E0AFC[] = "se_on";
const char s00a_aSeoff_800E0B04[] = "se_off";

extern UnkCameraStruct2 gUnkCameraStruct2_800B7868;
extern int              GV_Clock;

#define EXEC_LEVEL 4

int s00a_pato_lmp_800D5E30( unsigned short name, int hash_count, unsigned short* hashes )
{
    GV_MSG *msg;
    int     msg_count;
    int     found;
    int     hash;
    int     i;

    msg_count = GV_ReceiveMessage(name, &msg);
    found = -1;

    for (; msg_count > 0; msg_count--, msg++)
    {
        hash = msg->message[0];

        for (i = 0; i < hash_count; i++)
        {
            if (hash == hashes[i])
            {
                found = i;
            }
        }
    }

    return found;
}

int s00a_pato_lmp_800D5EC8(char *opt, SVECTOR *svecs)
{
    int            count;
    unsigned char *param;

    count = 0;
    for (count = 0; (param = GCL_GetParamResult()); svecs++, count++)
    {
        GCL_StrToSV(param, svecs);
    }
    return count;
}

void s00a_pato_lmp_800D5F1C( POLY_FT4* poly, int rgb )
{
    setRGB0( poly, rgb / 2, rgb / 2, rgb / 2 );
}

void s00a_pato_lmp_800D5F38(POLY_FT4 *polys, int count, DG_TEX *tex)
{
    int offx, width;
    int offy, height;

    while (--count >= 0)
    {
        setPolyFT4(polys);
        setSemiTrans(polys, 1);

        offx = tex->off_x;
        width = tex->w;
        offy = tex->off_y;
        height = tex->h;

        setUVWH(polys, offx, offy, width, height);

        polys->tpage = tex->tpage;
        polys->clut = tex->clut;
        polys->tpage |= 0x60;

        polys->r0 = 0;
        polys->g0 = 0;
        polys->b0 = 0;

        polys++;
    }
}

extern int GV_PauseLevel;

void s00a_pato_lmp_800D5FC4( PatoLmpWork* work )
{
    short rgb[3];

    if ( GV_PauseLevel )
    {
        return;
    }

    work->field_1924++;

    if ( work->field_1920 >= work->field_1924 )
    {
        rgb[0] = work->field_1928.vx + ( ( ( work->field_1930.vx - work->field_1928.vx ) * work->field_1924 ) / work->field_1920 );
        rgb[1] = work->field_1928.vy + ( ( ( work->field_1930.vy - work->field_1928.vy ) * work->field_1924 ) / work->field_1920 );
        rgb[2] = work->field_1928.vz + ( ( ( work->field_1930.vz - work->field_1928.vz ) * work->field_1924 ) / work->field_1920 );
    }
    else
    {
        rgb[0] = work->field_1930.vx;
        rgb[1] = work->field_1930.vy;
        rgb[2] = work->field_1930.vz;
    }

    setRGB0( &work->field_20->tile[GV_Clock], rgb[0], rgb[1], rgb[2] );

}

void s00a_pato_lmp_800D617C(PatoLmpWork *work, int field_191C, short vx, short vy, short vz)
{
    work->field_1920 = field_191C;
    work->field_1930.vx = vx;
    work->field_1930.vy = vy;
    work->field_1930.vz = vz;
}

void s00a_pato_lmp_800D6194(PatoLmpWork *work, int arg1, int arg2, int arg3)
{
    SVECTOR vec;


    SVECTOR *var_a2;

    int temp_a0;
    int temp_t1;
    int x, y, z;
    int temp;
    int temp2;
    int temp_v1;
    int a3_2;
    union Prim_Union *prim_uni;

    prim_uni = work->field_1008->packs[GV_Clock];
    a3_2 = arg3 * 4;
    prim_uni = (union Prim_Union*)&prim_uni->poly_ft4_multi[arg1][arg3];
    x = work->field_151C[arg1][arg2].vx;

    if (x != 0)
    {
        vec = work->field_111C[arg1][arg2];
        var_a2 = &work->field_100C[arg1][a3_2];

        y = work->field_151C[arg1][arg2].vy;
        z = work->field_151C[arg1][arg2].vz;

        temp = temp_v1 = 255 - z;
        temp2 = temp * 9;
        temp_t1 = (temp * 12) + 50;
        temp_a0 = temp2 + 50;
        temp_v1 =  temp * 4 + 150;

        switch (y)
        {
        case 0:
            var_a2->vx = vec.vx - temp_t1;
            var_a2->vy = vec.vy + temp_v1;
            var_a2->vz = vec.vz;
            var_a2++;

            var_a2->vx = vec.vx + temp_a0;
            var_a2->vy = vec.vy + temp_v1;
            var_a2->vz = vec.vz;
            var_a2++;

            var_a2->vx = vec.vx - temp_t1;
            var_a2->vy = vec.vy - temp_v1;
            var_a2->vz = vec.vz;
            var_a2++;

            var_a2->vx = vec.vx + temp_a0;
            var_a2->vy = vec.vy - temp_v1;
            var_a2->vz = vec.vz;
            break;

        case 1:
            var_a2->vx = vec.vx;
            var_a2->vz = vec.vz - temp_t1;
            var_a2->vy = vec.vy + temp_v1;
            var_a2++;

            var_a2->vx = vec.vx;
            var_a2->vz = vec.vz + temp_a0;
            var_a2->vy = vec.vy + temp_v1;
            var_a2++;

            var_a2->vx = vec.vx;
            var_a2->vz = vec.vz - temp_t1;
            var_a2->vy = vec.vy - temp_v1;
            var_a2++;

            var_a2->vx = vec.vx;
            var_a2->vz = vec.vz + temp_a0;
            var_a2->vy = vec.vy - temp_v1;
            break;

        case 2:
            var_a2->vx = vec.vx + temp_t1;
            var_a2->vy = vec.vy + temp_v1;
            var_a2->vz = vec.vz;
            var_a2++;

            var_a2->vx = vec.vx - temp_a0;
            var_a2->vy = vec.vy + temp_v1;
            var_a2->vz = vec.vz;
            var_a2++;

            var_a2->vx = vec.vx + temp_t1;
            var_a2->vy = vec.vy - temp_v1;
            var_a2->vz = vec.vz;
            var_a2++;

            var_a2->vx = vec.vx - temp_a0;
            var_a2->vy = vec.vy - temp_v1;
            var_a2->vz = vec.vz;
            break;

        case 3:
            var_a2->vx = vec.vx;
            var_a2->vz = vec.vz + temp_t1;
            var_a2->vy = vec.vy + temp_v1;
            var_a2++;

            var_a2->vx = vec.vx;
            var_a2->vz = vec.vz - temp_a0;
            var_a2->vy = vec.vy + temp_v1;
            var_a2++;

            var_a2->vx = vec.vx;
            var_a2->vz = vec.vz + temp_t1;
            var_a2->vy = vec.vy - temp_v1;
            var_a2++;

            var_a2->vx = vec.vx;
            var_a2->vz = vec.vz - temp_a0;
            var_a2->vy = vec.vy - temp_v1;
            break;
        }

        s00a_pato_lmp_800D5F1C((POLY_FT4*)prim_uni, z);
    }
    else
    {
        s00a_pato_lmp_800D5F1C((POLY_FT4*)prim_uni, 0);
    }
}

void s00a_pato_lmp_800D6550( PatoLmpWork* work )
{
    int i;
    for ( i = 0 ; i < work->field_1004 ; i++ )
    {
        DG_VisibleObjs(work->field_744[i].objs);
        DG_VisibleObjs(work->field_AD4[i].objs);
        DG_VisiblePrim(work->field_1008);

        work->field_FE4[i] = DG_ZeroVector;

    }

    work->field_193C = 1;
}

void s00a_pato_lmp_800D6600( PatoLmpWork* work )
{
    int i;
    for ( i = 0 ; i < work->field_1004 ; i++ )
    {
        DG_InvisibleObjs(work->field_744[i].objs);
        DG_InvisibleObjs(work->field_AD4[i].objs);
        DG_InvisiblePrim(work->field_1008);
    }
}

void PatrolLampAct_800D6678(PatoLmpWork *work)
{
    SVECTOR svec;
    short   hashes[6];
    int     i;
    int     sp30;

    int field_1940;
    int field_1940_2;

    char *ot;

    OBJECT *field_3B4_iter;
    OBJECT *field_AD4_iter;
    OBJECT *field_744_iter;
    SVECTOR *field_FA4_iter;
    SVECTOR *field_FE4_iter;

    short zero;

    zero = 0;
    GM_CurrentMap = work->map;

    hashes[0] = GV_StrCode(s00a_dword_800E0ADC);
    hashes[1] = GV_StrCode(s00a_dword_800E0AE4);
    hashes[2] = GV_StrCode(s00a_aOpen_800E0AEC);
    hashes[3] = GV_StrCode(s00a_aClose_800E0AF4);
    hashes[4] = GV_StrCode(s00a_aSeon_800E0AFC);
    hashes[5] = GV_StrCode(s00a_aSeoff_800E0B04);

    switch (s00a_pato_lmp_800D5E30(work->name, 6, hashes))
    {
    case 0:
    case 2:
        work->field_1950 = 1;
        s00a_pato_lmp_800D6550(work);
        work->field_1940 = 0;
        work->field_195C = 1;
        break;

    case 1:
    case 3:
        work->field_1950 = 0;
        s00a_pato_lmp_800D6600(work);
        break;

    case 4:
        work->field_195C = 1;
        break;

    case 5:
        work->field_195C = 0;
        break;
    }

    if (work->field_1958 == 0)
    {
        work->field_1958 = 1;

        for (i = 0; i < work->field_1004; i++)
        {
            DG_SetPos2(&work->field_FA4[i], &work->field_FC4[i]);
            GM_ActObject2(&work->field_3B4[i]);
            GM_ActObject2(&work->field_24[i]);
            DG_GetLightMatrix(&work->field_FA4[i], work->field_E64[i]);
        }
    }

    if (work->field_1950 != 0 || work->field_193C != 0)
    {
        work->field_1940++;
        sp30 = 65536;

        if (work->field_1950 == 1)
        {
            field_FA4_iter = work->field_FA4;
            field_FE4_iter = work->field_FE4;
            field_3B4_iter = work->field_3B4;
            field_744_iter = work->field_744;
            field_AD4_iter = work->field_AD4;

            work->field_193C = work->field_1950;

            for (i = 0; i < work->field_1004;
                 i++, field_FA4_iter++, field_FE4_iter++, field_3B4_iter++, field_744_iter++, field_AD4_iter++)
            {
                field_FE4_iter->vy += 128;
                DG_SetPos2(field_FA4_iter, field_FE4_iter);
                GM_ActObject2(field_744_iter);

                svec = *field_FE4_iter;
                svec.vy += 2048;

                DG_SetPos2(field_FA4_iter, &svec);
                GM_ActObject2(field_AD4_iter);
                GM_ActObject2(field_3B4_iter);

                if (work->field_1954 == 1)
                {
                    sp30 = 0;
                }
                else
                {
                    work->field_110C[i] = GV_DiffVec3(field_FA4_iter, &gUnkCameraStruct2_800B7868.eye);
                    if (work->field_110C[i] < sp30)
                    {
                        sp30 = work->field_110C[i];
                    }
                }
            }
        }
        else
        {
            sp30 = 0;
        }

        field_1940 = work->field_1940;
        field_1940 %= 32;
        if (mts_get_tick_count() - work->field_1960 >= 64)
        {
            work->field_1960 = mts_get_tick_count();
            if (work->field_1950 == 1)
            {
                if (work->field_195C == work->field_1950)
                {
                    GM_SeSet2(0, 127, work->field_1964);
                }
            }
        }

        field_1940_2 = field_1940 + 16;
        if (field_1940_2 >= 32)
        {
            field_1940_2 = field_1940 - 16;
        }
        for (i = 0; i < work->field_1004; i++)
        {
            s00a_pato_lmp_800D6194(work, i, field_1940, 0);
            s00a_pato_lmp_800D6194(work, i, field_1940_2, 1);
        }

        if (work->field_193C == 1 && sp30 < 16384)
        {
            ot = DG_ChanlOTag(0);
            addPrim(ot, &work->field_20->tile[GV_Clock]);
            addPrim(ot, &work->field_20->tpage[GV_Clock]);
            s00a_pato_lmp_800D5FC4(work);
            if (work->field_1924 == work->field_1920)
            {
                work->field_1924 = zero;
                work->field_1928 = work->field_1930;
                switch (work->field_1938)
                {
                case 0:
                    sp30 = 16384 - sp30;
                    s00a_pato_lmp_800D617C(work, work->field_191C, sp30 / 128, sp30 / 512, 0);
                    break;

                case 1:
                    s00a_pato_lmp_800D617C(work, work->field_191C, 0, 0, 0);
                    break;
                }
                work->field_1938++;

                if (work->field_1938 >= 2)
                {
                    work->field_1938 = 0;
                }
                if (work->field_1938 == 1 && work->field_1950 == 0)
                {
                    work->field_193C = 0;
                }
            }
        }
    }
}

void PatrolLampDie_800D6C44(PatoLmpWork *work)
{
    DG_PRIM *prim;
    void    *allocated;
    int      i;

    prim = work->field_1008;
    if (prim)
    {
        DG_DequeuePrim(prim);
        DG_FreePrim(prim);
    }
    for (i = 0; i < work->field_1004; i++)
    {
        GM_FreeObject(&work->field_24[i]);
        GM_FreeObject(&work->field_3B4[i]);
        GM_FreeObject(&work->field_744[i]);
        GM_FreeObject(&work->field_AD4[i]);
    }
    allocated = work->field_20;
    if (allocated)
    {
        GV_DelayedFree(allocated);
    }
}

void s00a_pato_lmp_800D6D24(SVECTOR* svec, short x, short z)
{
    svec->vx += x;
    svec->vz += z;
}

void s00a_pato_lmp_800D6D40( PatoLmpWork *work, int idx, int idx2, int y )
{
    int dis;

    dis = GV_DiffVec3( &work->field_FA4[idx] , &work->field_111C[idx][idx2]);

    if (dis > 3500 )
    {
        if ( work->field_151C[idx][idx2].vx != 0 )
        {
            work->field_151C[idx][idx2].vx = 0;
            return;
        }
    }

    work->field_151C[idx][idx2].vy = y;
    work->field_151C[idx][idx2].vz = (255 - ((dis * 255)) / 3500);

}

const char aPatlit[] = "patlit";
const char aPatBody[] = "pat_body";
const char aPatLamp[] = "pat_lamp";
const char aPatSpt1[] = "pat_spt1";


//I'll clean this up later
int PatrolLampGetResources_800D6E28(PatoLmpWork *work, int name, int map)
{
    SVECTOR sp18[4][16];
    int     sp218[4][16];
    int     sp318[4];

    PatoLmpPrims *prims;

    int sp328;

    int i, j;
    int rot;
    DG_PRIM* prim;
    DG_TEX* tex;
    OBJECT* temp_s0_2;
    OBJECT* temp_s0_3;
    OBJECT* temp_s0_4;
    OBJECT* temp_s0_5;
    char *opt;
    char *str;

    int s0, s2, s4;

    int cos, sin;
    int s5, x, y;
    int prim_temp;

    sp328 = 0;

    GM_CurrentMap = map;

    work->field_1944 = 0;
    work->name = name;
    work->map  = map;

    if (GCL_GetOption('l'))
    {
        work->field_1954 = 1;
    }
    else
    {
        work->field_1954 = 0;
    }

    opt = GCL_GetOption('p');
    prim_temp = 5000;
    if (opt)
    {
        work->field_1004 = s00a_pato_lmp_800D5EC8( opt, work->field_FA4 );
        sp328 = work->field_1004;
        if (sp328 >= 5)
        {
            return -1;
        }
    }

    opt = GCL_GetOption('d');
    if (opt)
    {
        sp328 = s00a_pato_lmp_800D5EC8( opt, work->field_FC4 );
        if (sp328 >= 5)
        {
            return -1;
        }

        for (i = 0; i < sp328; i++)
        {
            work->field_FE4[i] = DG_ZeroVector;
        }
    }

    if (sp328 != work->field_1004)
    {
        return -1;
    }

    opt = GCL_GetOption('s');
    if (opt)
    {
        work->field_1964 = GCL_StrToInt( ( char* ) opt );
    }
    else
    {
        work->field_1964 = 181;
    }

    if (GCL_GetOption('w'))
    {

        for (i = 0; i < sp328; i++)
        {
            for (cos = 0; cos < 4; cos++)
            {
                if ((str = GCL_GetParamResult()) == NULL)
                {
                    break;
                }

                sp318[cos] = GCL_StrToInt(str);
            }

            //loc_800D700C:
            for ( j = 0 ; j < 16 ; j++ )
            {
                cos = rcos(-960 + j * 128);
                sin = rsin(-960 + j * 128);

                if ( cos == 0 )
                {
                    cos = 1;
                }

                sp18[0][j]  = work->field_FA4[i];
                sp218[0][j] = (sp318[0] * sin) / cos;
                s00a_pato_lmp_800D6D24(&sp18[0][j], (unsigned short)sp218[0][j] * -1, (unsigned short)sp318[0] * -1);

                sp18[1][j]  = work->field_FA4[i];
                sp218[1][j] = (sp318[1] * sin) / cos;
                s00a_pato_lmp_800D6D24(&sp18[1][j], (unsigned short)sp318[1] * -1, (unsigned short)sp218[1][j]);

                sp18[2][j]  = work->field_FA4[i];
                sp218[2][j] = (sp318[2] * sin) / cos;
                s00a_pato_lmp_800D6D24(&sp18[2][j], (unsigned short)sp218[2][j], (unsigned short)sp318[2]);

                sp18[3][j]  = work->field_FA4[i];
                sp218[3][j] = (sp318[3] * sin) / cos;
                s00a_pato_lmp_800D6D24(&sp18[3][j], (unsigned short)sp318[3], (unsigned short)sp218[3][j] * -1);
            }

            s0 = 0;
            s5 = 8;
            s2 = s5;
            //loc_800D7290:
            for ( j = 0 ; j < s2 ; j++ )
            {
                x = j + s5;
                work->field_151C[i][j].vx = 1;
                rot = abs(sp218[3][x]);

                if ( ( rot < sp318[0] || sp318[0] == -1 ) )
                {
                    if ( sp318[3] != -1)
                    {
                        goto temp_label1;
                    }
                    else
                    {
                        if ( sp318[0] == -1)
                        {
                            goto temp_label3;
                        }
                        else
                        {
                            goto temp_label2;
                        }
                    }
                }
                else
                {
                    goto temp_label2;
                }


temp_label1:
                work->field_111C[i][j] = sp18[3][x];
                s0 = 1;
                goto temp_label_end;
temp_label2:
                work->field_111C[i][j] = sp18[0][j];
                s0 = 0;
                goto temp_label_end;
temp_label3:
                 work->field_151C[i][j].vx = 0;
temp_label_end:


/*
                if ( ( rot < sp318[0] || sp318[0] == -1 ) && sp318[3] != -1 )
                {
                        work->field_111C[i][j] = sp18[3][j];
                        s0 = 1;
                }
                else if ( sp318[3] != -1 )
                {
                    work->field_111C[i][j] = sp18[i][j];
                    s0 = 0;
                }
                else
                {
                    work->field_151C[i][j].vx = 0;
                }
*/
                //might just be repeated in the conditionals
                s00a_pato_lmp_800D6D40(work, i, j, s0);

            }

            s5 = s2;
            s2 = 16;
            //loc_800D7398:
            for (  ; j < s2 ; j++ )
            {
                x = j + s5;
                work->field_151C[i][j].vx = 1;
                rot = abs(sp218[0][j]);

                if ( rot < sp318[1] || sp318[1] == -1 )
                {
                    //loc_800D72D4
                    if (sp318[0] != -1)
                    {
                        goto temp_label4;
                    }
                    else if ( sp318[1] == -1 )
                    {
                        goto temp_label6;
                    }
                    else
                    {
                        goto temp_label5;
                    }

                }
                else
                {
                    goto temp_label5;
                }

temp_label4:
                work->field_111C[i][j] = sp18[0][j];
                s0 = 0;
                goto temp_label_end2;
temp_label5:
                work->field_111C[i][j] = sp18[1][j - s5];
                s0 = 3;
                goto temp_label_end2;
temp_label6:
                 work->field_151C[i][j].vx = 0;
temp_label_end2:

                //might just be repeated in the conditionals
                s00a_pato_lmp_800D6D40(work, i, j, s0);
            }

            //loc_800D74A4:
            s5 = s2;
            s4 = 8;
            s2 = s2 + s4;

            //s2 = 24;
            for (  ; j < s2 ; j++ )
            {
                //y = j - s4;
                work->field_151C[i][j].vx = 1;
                rot = abs(sp218[1][j - s4]);

                //loc_800D74D4
                if ( rot < sp318[2] || sp318[2] == -1 )
                {

                    if (sp318[1] != -1)
                    {
                        goto temp_label7;
                    }
                    else if ( sp318[2] == -1 )
                    {
                        goto temp_label9;
                    }
                    else
                    {
                        goto temp_label8;
                    }

                }
                else
                {
                    goto temp_label8;
                }
temp_label7:
                work->field_111C[i][j] = sp18[1][j - s4];
                s0 = 3;
                goto temp_label_end3;
temp_label8:
                work->field_111C[i][j] = sp18[2][j - s5];
                s0 = 2;
                goto temp_label_end3;
temp_label9:
                 work->field_151C[i][j].vx = 0;
temp_label_end3:
                //might just be repeated in the conditionals
                s00a_pato_lmp_800D6D40(work, i, j, s0);
            }
            //loc_800D75B0:
            //s5 = s2;
            //s2 = 32;
            //s4 = 16;
            do { s5 = s2; s2 = 32; s4 = 16; } while (0);
            for (  ; j < s2 ; j++ )
            {
                y = j - s4;
                work->field_151C[i][j].vx = 1;
                rot = abs(sp218[2][y]);

                if ( rot < sp318[3] || sp318[3] == -1 )
                {
                    //loc_800D72D4
                    if (sp318[2] != -1)
                    {
                        goto temp_label10;
                    }
                    else if ( sp318[3] == -1 )
                    {
                        goto temp_label12;
                    }
                    else
                    {
                        goto  temp_label11;
                    }

                }
                else
                {
                    goto  temp_label11;
                }

temp_label10:
                work->field_111C[i][j] = sp18[2][y];
                        s0 = 2;
                goto temp_label_end4;
temp_label11:
                work->field_111C[i][j] = sp18[3][j - s5];
                        s0 = 1;
                goto temp_label_end4;
temp_label12:
                 work->field_151C[i][j].vx = 0;
temp_label_end4:
                //might just be repeated in the conditionals
                s00a_pato_lmp_800D6D40(work, i, j, s0);
            }
        }
    }

    prim = DG_GetPrim(DG_PRIM_ONEFACE | DG_PRIM_POLY_FT4, work->field_1004 * 2, 0, (SVECTOR*)work->field_100C, NULL);
    work->field_1008 = prim;

    if (!prim)
    {
        return -1;
    }

    prim->field_2E_k500 = prim_temp;

    tex = DG_GetTexture(GV_StrCode(aPatlit));
    if (!tex)
    {
        return -1;
    }

    s00a_pato_lmp_800D5F38((POLY_FT4*)prim->packs[0], work->field_1004 * 2, tex);
    s00a_pato_lmp_800D5F38((POLY_FT4*)prim->packs[1], work->field_1004 * 2, tex);

    work->field_F64[0].t[0] = 16;
    work->field_F64[0].t[1] = 16;
    work->field_F64[0].t[2] = 16;

    for (sp328 = 0; sp328 < work->field_1004; sp328++)
    {
        temp_s0_2 = &work->field_24[sp328];
        GM_InitObject(temp_s0_2, GV_StrCode(aPatBody), 0x6D, 0);
        GM_ConfigObjectJoint(temp_s0_2);
        GM_ConfigObjectLight(temp_s0_2, work->field_E64[sp328]);

        temp_s0_3 = &work->field_3B4[sp328];
        GM_InitObject(temp_s0_3, GV_StrCode(aPatLamp), 0x6D, 0);
        GM_ConfigObjectJoint(temp_s0_3);

        temp_s0_4 = &work->field_744[sp328];
        GM_InitObject(temp_s0_4, GV_StrCode(aPatSpt1), 0x16D, 0);
        GM_ConfigObjectJoint(temp_s0_4);
        GM_ConfigObjectLight(temp_s0_4, work->field_F64);

        temp_s0_5 = &work->field_AD4[sp328];
        GM_InitObject(temp_s0_5, GV_StrCode(aPatSpt1), 0x16D, 0);
        GM_ConfigObjectJoint(temp_s0_5);
        GM_ConfigObjectLight(temp_s0_5, work->field_F64);
    }

    prims = GV_Malloc(sizeof(PatoLmpPrims));
    work->field_20 = prims;
    if (!prims)
    {
        return -1;
    }

    setDrawTPage(&prims->tpage[0], 0, 1, getTPage(0, 1, 0, 0));
    setDrawTPage(&prims->tpage[1], 0, 1, getTPage(0, 1, 0, 0));

    setTile(&prims->tile[0]);
    setSemiTrans(&prims->tile[0], 1);
    prims->tile[0].x0 = -160;
    prims->tile[0].y0 = -112;
    prims->tile[0].w = 320;
    prims->tile[0].h = 224;

    prims->tile[1] = prims->tile[0];

    setRGB0(&prims->tile[0], 0, 0, 0);
    setRGB0(&prims->tile[1], 0, 0, 0);

    work->field_1928 = DG_ZeroVector;

    work->field_1930.vx = 0;
    work->field_1930.vy = 0;
    work->field_1930.vz = 0;

    work->field_1920 = 1;
    work->field_1938 = 0;
    work->field_193C = 0;
    work->field_191C = 8;
    work->field_1940 = 0;
    work->field_1950 = 0;

    s00a_pato_lmp_800D6600(work);

    work->field_1944 = 1;
    work->field_1958 = 0;
    work->field_195C = 1;
    work->field_1960 = mts_get_tick_count();

    return 0;
}

GV_ACT *NewPatrolLamp_800D7A2C(int name, int where, int argc, char **argv)
{
    PatoLmpWork *work;

    work = (PatoLmpWork *)GV_NewActor(EXEC_LEVEL, sizeof(PatoLmpWork));
    if (work != NULL)
    {
        GV_SetNamedActor(&work->actor, (GV_ACTFUNC)PatrolLampAct_800D6678,
                         (GV_ACTFUNC)PatrolLampDie_800D6C44, "pato_lmp.c");

        if (PatrolLampGetResources_800D6E28(work, name, where) < 0)
        {
            GV_DestroyActor(&work->actor);
            return NULL;
        }
    }

    return &work->actor;
}
