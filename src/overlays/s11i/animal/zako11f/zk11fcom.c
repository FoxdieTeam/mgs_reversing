#include "../../../s00a/Enemy/enemy.h"
#include "mts/mts.h"

typedef struct _Zako11FCommanderWork
{
    GV_ACT actor;
    int    name;
    char   pad[0x4];
} Zako11FCommanderWork;

extern int     GM_PlayerAddress_800AB9F0;
extern int     GM_PlayerMap_800ABA0C;
extern SVECTOR GM_PlayerPosition_800ABA10;

extern SVECTOR           ZAKOCOM_PlayerPosition_800D5AF0;
extern ZAKO11F_COMMAND   Zako11FCommand_800D5AF8;
extern TOPCOMMAND_STRUCT TOPCOMMAND_800D5C40;
extern int               s11i_dword_800D5C48;
extern int               s11i_dword_800D5C4C;
extern int               ZAKOCOM_PlayerAddress_800D5C50;
extern int               ZAKOCOM_PlayerMap_800D5C54;

void s11i_zk11fcom_800D1754(Zako11FCommanderWork *work);
void s11i_zk11fcom_800D19D4(void);

#define EXEC_LEVEL 4

int s11i_zk11fcom_800D0BF4( Zako11FWork *work )
{
    int i;

    for ( i = 0 ; i <  8 ; i++ )
    {
        if ( !Zako11FCommand_800D5AF8.field_0x8C[ i ].watcher )
        {
            Zako11FCommand_800D5AF8.field_0x8C[ i ].watcher = ( WatcherWork * )work;
            Zako11FCommand_800D5AF8.field_0x8C[ i ].field_04 = 2;
            return i;
        }
    }

    return -1;
}

void s11i_zk11fcom_800D0C38( int index )
{
    Zako11FCommand_800D5AF8.field_0x8C[index].watcher = NULL;
    Zako11FCommand_800D5AF8.field_0x8C[index].field_04 = 1;
}

void s11i_zk11fcom_800D0C58( int arg0 )
{
    TOPCOMMAND_800D5C40.alert = arg0;
}

void s11i_zk11fcom_800D0C64( int arg0 )
{
    TOPCOMMAND_800D5C40.mode = arg0;
}

#pragma INCLUDE_ASM("asm/overlays/s11i/s11i_zk11fcom_800D0C70.s")
#pragma INCLUDE_ASM("asm/overlays/s11i/s11i_zk11fcom_800D0CBC.s")
#pragma INCLUDE_ASM("asm/overlays/s11i/s11i_zk11fcom_800D0D34.s")
#pragma INCLUDE_ASM("asm/overlays/s11i/s11i_zk11fcom_800D0DA8.s")
#pragma INCLUDE_ASM("asm/overlays/s11i/s11i_zk11fcom_800D0DB8.s")
#pragma INCLUDE_ASM("asm/overlays/s11i/s11i_zk11fcom_800D0DD8.s")

int s11i_zk11fcom_800D0E04(char *opt, A4_STRUCT *out)
{
    int count;

    count = 0;

    do
    {
        out->field_04[count].field_00 = GCL_StrToInt(GCL_GetParamResult());
        out->field_04[count].field_02 = GCL_StrToInt(GCL_GetParamResult());
        count++;
    } while (GCL_GetParamResult());

    return count;
}

int s11i_zk11fcom_800D0E64(char *opt, short *out)
{
    int   count;
    char *param;

    count = 0;

    while ((param = GCL_GetParamResult()))
    {
        *out++ = GCL_StrToInt(param);
        count++;
    }

    return count;
}

#pragma INCLUDE_ASM("asm/overlays/s11i/s11i_zk11fcom_800D0EBC.s")
#pragma INCLUDE_ASM("asm/overlays/s11i/s11i_zk11fcom_800D0FAC.s")
#pragma INCLUDE_ASM("asm/overlays/s11i/s11i_zk11fcom_800D0FEC.s")
#pragma INCLUDE_ASM("asm/overlays/s11i/s11i_zk11fcom_800D1040.s")
#pragma INCLUDE_ASM("asm/overlays/s11i/s11i_zk11fcom_800D1094.s")
#pragma INCLUDE_ASM("asm/overlays/s11i/s11i_zk11fcom_800D10E8.s")
#pragma INCLUDE_ASM("asm/overlays/s11i/s11i_zk11fcom_800D113C.s")
#pragma INCLUDE_ASM("asm/overlays/s11i/s11i_zk11fcom_800D1190.s")
#pragma INCLUDE_ASM("asm/overlays/s11i/s11i_zk11fcom_800D1220.s")
#pragma INCLUDE_ASM("asm/overlays/s11i/s11i_zk11fcom_800D1274.s")
#pragma INCLUDE_ASM("asm/overlays/s11i/s11i_zk11fcom_800D12D8.s")
#pragma INCLUDE_ASM("asm/overlays/s11i/s11i_zk11fcom_800D139C.s")
#pragma INCLUDE_ASM("asm/overlays/s11i/s11i_zk11fcom_800D1480.s")
#pragma INCLUDE_ASM("asm/overlays/s11i/s11i_zk11fcom_800D15C4.s")
#pragma INCLUDE_ASM("asm/overlays/s11i/s11i_zk11fcom_800D15DC.s")
#pragma INCLUDE_ASM("asm/overlays/s11i/s11i_zk11fcom_800D1640.s")
#pragma INCLUDE_ASM("asm/overlays/s11i/s11i_zk11fcom_800D1754.s")

void s11i_zk11fcom_800D185C(void)
{
    int lo, hi;

    lo = GM_PlayerAddress_800AB9F0 & 0xFF;
    hi = ( GM_PlayerAddress_800AB9F0 >> 8 ) & 0xFF;

    if ( lo == hi && lo != 0xFF )
    {
        ZAKOCOM_PlayerAddress_800D5C50 = GM_PlayerAddress_800AB9F0;
        ZAKOCOM_PlayerPosition_800D5AF0 = GM_PlayerPosition_800ABA10;
        ZAKOCOM_PlayerMap_800D5C54 = GM_PlayerMap_800ABA0C;
    }
}

int s11i_zk11fcom_800D18D0( char *opt )
{
    int count;
    int proc;

    count = 0;

    while (opt)
    {
        proc = GCL_StrToInt(opt);
        opt = GCL_GetParamResult();

        GCL_ExecProc(proc, NULL);
        count++;
    }

    return count;
}

#pragma INCLUDE_ASM("asm/overlays/s11i/s11i_zk11fcom_800D1934.s")
#pragma INCLUDE_ASM("asm/overlays/s11i/s11i_zk11fcom_800D1990.s")
#pragma INCLUDE_ASM("asm/overlays/s11i/s11i_zk11fcom_800D19D4.s")

void ZakoCommanderAct_800D1DB0(Zako11FCommanderWork *work)
{
    if (GM_CheckMessage(&work->actor, work->name, HASH_KILL))
    {
        GV_DestroyActor(&work->actor);
        return;
    }

    s11i_zk11fcom_800D19D4();
    s11i_zk11fcom_800D185C();
    s11i_zk11fcom_800D1754(work);

    Zako11FCommand_800D5AF8.field_0x0C++;

    if (s11i_dword_800D5C4C == 16)
    {
        GV_DestroyActor(&work->actor);
    }
}

void ZakoCommanderDie_800D1E30(Zako11FCommanderWork *work)
{
}

int ZakoCommander_800D1E38(void)
{
    int   i;
    char *opt;

    for (i = 0; i < 8; i++)
    {
        Zako11FCommand_800D5AF8.field_0x124[i] = -1;
    }

    i = 0;
    opt = GCL_GetOption('a');
    while (opt)
    {
        if (i >= 8)
        {
            return -1;
        }

        Zako11FCommand_800D5AF8.field_0x124[i] = GCL_StrToInt(opt);
        opt = GCL_GetParamResult();
        i++;
    }

    return i;
}

void ZakoCommanderGetResources_800D1EC8(Zako11FCommanderWork *work, int name, int where)
{
    int   i;
    char *opt;

    work->name = name;

    s11i_dword_800D5C4C = 0;

    Zako11FCommand_800D5AF8.field_0x20 = 0;
    Zako11FCommand_800D5AF8.alert = 0;
    Zako11FCommand_800D5AF8.field_0x10 = 0;
    Zako11FCommand_800D5AF8.field_0x60 = 0;
    Zako11FCommand_800D5AF8.field_0x112 = 0;
    Zako11FCommand_800D5AF8.field_0x114 = 0;
    Zako11FCommand_800D5AF8.field_0x116 = 0;

    for (i = 0; i < 8; i++)
    {
        Zako11FCommand_800D5AF8.field_0x8C[i].field_00 = 0;
        Zako11FCommand_800D5AF8.field_0x8C[i].field_04 = 0;
        Zako11FCommand_800D5AF8.field_0x8C[i].field_08 = 0;
        Zako11FCommand_800D5AF8.field_0x8C[i].watcher = 0;
    }

    for (i = 0; i < 8; i++)
    {
        Zako11FCommand_800D5AF8.field_0x40[i] = i;
    }

    Zako11FCommand_800D5AF8.field_0x0C = 0;
    Zako11FCommand_800D5AF8.mode = 0;

    TOPCOMMAND_800D5C40.mode = 0;
    TOPCOMMAND_800D5C40.alert = 0;

    Zako11FCommand_800D5AF8.map = Map_FromId_800314C0(where);

    opt = GCL_GetOption('e');
    if (opt)
    {
        Zako11FCommand_800D5AF8.field_0x120 = GCL_StrToInt(GCL_GetParamResult());
    }
    else
    {
        Zako11FCommand_800D5AF8.field_0x120 = -1;
    }

    ZakoCommander_800D1E38();

    opt = GCL_GetOption('v');
    if (opt)
    {
        Zako11FCommand_800D5AF8.n_zones = s11i_zk11fcom_800D0E64(opt, Zako11FCommand_800D5AF8.zones);
    }
    else
    {
        Zako11FCommand_800D5AF8.n_zones = 1;
        Zako11FCommand_800D5AF8.zones[0] = 0;
    }

    for (i = 0; i < Zako11FCommand_800D5AF8.n_zones; i++)
    {
        fprintf(1, "zone=%d ", Zako11FCommand_800D5AF8.zones[i]);
    }

    Zako11FCommand_800D5AF8.field_0x36 = 0;
    s11i_dword_800D5C48 = 0;

    opt = GCL_GetOption('j');
    if (opt)
    {
        Zako11FCommand_800D5AF8.field_0x68.n_entry = s11i_zk11fcom_800D0E04(opt, &Zako11FCommand_800D5AF8.field_0x68);
    }
    else
    {
        Zako11FCommand_800D5AF8.field_0x68.n_entry = 1;
        Zako11FCommand_800D5AF8.field_0x68.field_04[0].field_00 = 0;
        Zako11FCommand_800D5AF8.field_0x68.field_04[0].field_02 = 0;
    }

    Zako11FCommand_800D5AF8.field_0x68.map_id = where;
    Zako11FCommand_800D5AF8.field_0x08 = 0;

    opt = GCL_GetOption('n');
    if (opt)
    {
        Zako11FCommand_800D5AF8.field_0x08 = s11i_zk11fcom_800D18D0(opt);
    }

    Zako11FCommand_800D5AF8.field_0x00 = 0;
    Zako11FCommand_800D5AF8.field_0x04 = 0;
    Zako11FCommand_800D5AF8.field_0x110 = 0;
}

GV_ACT *NewZakoCommander_800D20D8( int name, int where )
{
    Zako11FCommanderWork *work ;

    work = (Zako11FCommanderWork *)GV_NewActor( EXEC_LEVEL, sizeof( Zako11FCommanderWork ) ) ;
    if ( work != NULL ) {
        GV_SetNamedActor( &( work->actor ), ( GV_ACTFUNC )ZakoCommanderAct_800D1DB0, ( GV_ACTFUNC )ZakoCommanderDie_800D1E30, "zk11fcom.c" );
        ZakoCommanderGetResources_800D1EC8( work, name, where );
    }
    return &work->actor;
}
