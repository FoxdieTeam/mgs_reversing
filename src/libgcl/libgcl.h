#ifndef _LIBGCL_H_
#define _LIBGCL_H_

#include "Menu/menuman.h"
#include "Game/map.h"

// A hashed name of an actor and a pointer to a function that creates an instance of said actor
struct GV_ACT;
typedef GV_ACT *(*NEWCHARA)(int name, int where, int argc, char **argv);

typedef struct CHARA
{
    unsigned short  class_id;
    NEWCHARA        function;
} CHARA;

typedef int (*GCL_COMMANDFUNC)(unsigned char *);

int GCL_Command_mesg_8002C138(unsigned char *pScript);
int GCL_Command_trap_8002BD34(unsigned char *pScript);
int GCL_Command_map_8002BB44(unsigned char *pScript);
int GCL_Command_mapdef_8002BD04(unsigned char *pScript);
int GCL_Command_camera_8002B8F0(unsigned char *pScript);
int GCL_Command_light_8002B854(unsigned char *pScript);
int GCL_Command_start_8002C22C(unsigned char *pScript);
int GCL_Command_load_8002C308(unsigned char *pScript);
int GCL_Command_radio_8002C4A8(unsigned char *pScript);
int GCL_Command_strstatus_8002C6A4(unsigned char *pScript);
int GCL_Command_demo_8002C890(unsigned char *pScript);
int GCL_Command_ntrap_8002BE20(unsigned char *pScript);
int GCL_Command_delay_8002C074(unsigned char *pScript);
int GCL_Command_pad_8002C988(unsigned char *pScript);
int GCL_Command_varsave_8002C72C(unsigned char *pScript);
int GCL_Command_system_8002C7C8(unsigned char *pScript);
int GCL_Command_sound_8002CA28(unsigned char *pScript);
int GCL_Command_menu_8002CAAC(unsigned char *pScript);
int GCL_Command_rand_8002CD94(unsigned char *pScript);
int GCL_Command_func_8002CDF4(unsigned char *pScript);
int GCL_Command_demodebug_8002CFBC(unsigned char *pScript);
int GCL_Command_print_8002D0E4(unsigned char *pScript);
int GCL_Command_jimaku_8002D188(unsigned char *pScript);

// TODO: Why is this one different? Putting a breakpoint
// at GCL_Command_chara_8002C1B0 shows it receives trash
// argc and argv.
int GCL_Command_chara_8002C1B0(int argc, char **argv);

/*---------------------------------------------------------------------------*/

typedef struct      // private to libgcl/command.c
{
    unsigned short proc_id;
    unsigned short offset;
} GCL_PROC_TABLE;

typedef struct
{
    GCL_PROC_TABLE *proc_table;
    unsigned char  *proc_body;
    unsigned char  *script_body;
} GCL_SCRIPT;

// A hashed name of a GCL command and pointer to function that implements the command
typedef struct GCL_COMMANDLIST
{
    unsigned short  id;
    GCL_COMMANDFUNC function;
} GCL_COMMANDLIST;

// memleak
typedef struct _gcl_commanddef
{
    struct _gcl_commanddef *next;
    int                     n_commlist;
    GCL_COMMANDLIST        *commlist;
} GCL_COMMANDDEF;

// memleak
typedef struct
{
    unsigned short argc;
    long          *argv;
} GCL_ARGS;

typedef struct GCL_Vars
{
    short var[1024];
} GCL_Vars;

typedef struct SaveGame
{
    int                f008_version;
    int                f00C_version2;
    int                f010_totalFrameTime;
    int                f014_padding[3];
    char               f020_stageName[16];
    AreaHistory        f030_areaHistory;
    short              f040_varbuf[0x60];
    GCL_Vars           f100_gcl_vars;
    RadioMemory        f900_radio_memory[RADIO_MEMORY_COUNT];
} SaveGame; // size 0xA38

typedef struct SaveFile
{
    int      f000_size;
    int      f004_checksum;
    SaveGame f008_saveGame;
} SaveFile;

typedef struct BindStruct
{
    short field_0;
    short field_2_param_m;

    short          field_4;
    unsigned short field_6;

    unsigned char field_8_param_i_c_flags;
    unsigned char field_9_param_s;
    unsigned char field_A_param_b;
    unsigned char field_B_param_e;

    unsigned short field_C_param_d;
    unsigned short field_E_param_d_or_512;

    int field_10_every;
    int field_14_proc_and_block;
} BindStruct;

typedef struct CAMERA
{
    SVECTOR     pos;
    short       trg[3]; // SVECTOR w/ padding as alertMask?
    short       field_0e_alertMask;
    signed char field_10_param1; // example: d:CAM_FIX
    u_char      field_11_param2; // example: d:CAM_INTERP_LINER
    char        field_12_param3; // example: d:CAM_CAM_TO_TRG
    char        field_13_param_p;
} CAMERA;

#define GAME_FLAG_BIT_01        0x1
#define GAME_FLAG_BIT_02        0x2
#define GAME_FLAG_BIT_03        0x4
#define GAME_FLAG_BIT_04        0x8
#define GAME_FLAG_BIT_05        0x10
#define GAME_FLAG_BIT_06        0x20
#define GAME_FLAG_BIT_07        0x40
#define GAME_FLAG_BIT_08        0x80
#define GAME_FLAG_BIT_09        0x100
#define STATE_ENEMY_OFF         0x200
#define GAME_FLAG_BIT_11        0x400
#define GAME_RADAR_ENABLED      0x800
#define GAME_FLAG_BIT_13        0x1000
#define GAME_FLAG_BIT_14        0x2000
#define GAME_FLAG_BIT_15        0x4000
#define GAME_FLAG_BIT_16        0x8000
#define GAME_FLAG_BIT_17        0x10000
#define GAME_FLAG_BIT_18        0x20000
#define GAME_FLAG_BIT_19        0x40000
#define GAME_FLAG_BIT_20        0x80000
#define GAME_FLAG_BIT_21        0x100000
#define GAME_FLAG_BIT_22        0x200000
#define GAME_FLAG_BIT_23        0x400000
#define GAME_FLAG_BIT_24        0x800000
#define GAME_FLAG_BIT_25        0x1000000
#define GAME_FLAG_BIT_26        0x2000000
#define GAME_OVER               0x4000000
#define GAME_FLAG_BIT_28        0x8000000
#define GAME_FLAG_BIT_29        0x10000000
#define GAME_FLAG_BIT_30        0x20000000
#define GAME_FLAG_BIT_31        0x40000000
#define GAME_IN_DEMO            0x80000000

// Radio codes (radio.dat files)
#define RDCODE_NULL             0
#define RDCODE_TALK             1
#define RDCODE_VOICE            2
#define RDCODE_ANIM             3
#define RDCODE_ADD_CONTACT      4
#define RDCODE_MEMSAVE          5
#define RDCODE_SOUND            6
#define RDCODE_PROMPT           7
#define RDCODE_VARSAVE          8
#define RDCODE_IF               0x10
#define RDCODE_ELSE             0x11
#define RDCODE_ELSEIF           0x12
#define RDCODE_SWITCH           0x20
#define RDCODE_SWITCH_CASE      0x21
#define RDCODE_SWITCH_DEFAULT   0x22
#define RDCODE_RANDSWITCH       0x30
#define RDCODE_RANDSWITCH_CASE  0x31
#define RDCODE_EVAL             0x40
#define RDCODE_SCRIPT           0x80
#define RDCODE_ENDLINE          0xFF

// GCL codes (.gcx files)
#define GCLCODE_NULL            0
#define GCLCODE_SHORT           1       // $w:
#define GCLCODE_BYTE            2       // $b:
#define GCLCODE_CHAR            3       //
#define GCLCODE_FLAG            4       // $f: (boolean)
#define GCLCODE_HASHED_STRING   6       // $s:, can also be a hashed proc name
#define GCLCODE_STRING          7       //
#define GCLCODE_PROC_CALL       8       // hashed proc name to call
#define GCLCODE_SDCODE          9       //
#define GCLCODE_TABLE_CODE      10      // .vox, .dmo and radio.dat
#define GCLCODE_VARIABLE        0x10    // variables codes are: 0x11, 0x12, 0x13, 0x14, 0x16, 0x18
#define GCLCODE_STACK_VAR       0x20
#define GCLCODE_EXPRESSION      0x30
#define GCLCODE_EXPR_OPERATOR   0x31
#define GCLCODE_SCRIPT_DATA     0x40
#define GCLCODE_PARAMETER       0x50
#define GCLCODE_COMMAND         0x60
#define GCLCODE_PROC            0x70

#define GCL_OP_NEGATE       1
#define GCL_OP_ISZERO       2
#define GCL_OP_COMPL        3
#define GCL_OP_ADD          4
#define GCL_OP_SUB          5
#define GCL_OP_MUL          6
#define GCL_OP_DIV          7
#define GCL_OP_MOD          8
#define GCL_OP_EQUALS       9
#define GCL_OP_NOT_EQ       10
#define GCL_OP_LESS         11
#define GCL_OP_LESS_EQ      12
#define GCL_OP_GREATER      13
#define GCL_OP_GREATER_EQ   14
#define GCL_OP_BITOR        15
#define GCL_OP_BITAND       16
#define GCL_OP_BITXOR       17
#define GCL_OP_OR           18
#define GCL_OP_AND          19
#define GCL_OP_EQUAL        20

#define GCL_IsVariable(gcl_code) ((gcl_code & 0xF0) == GCLCODE_VARIABLE)
#define GCL_IsParam(gcl_code) ((gcl_code & 0xFF) == GCLCODE_PARAMETER)

#define GCL_GetVarTypeCode(gcl_var) (((gcl_var << 1) >> 25) & 0xF)
#define GCL_GetVarOffset(gcl_var)   (gcl_var & 0xFFFF)
#define GCL_IsGameStateVar(gcl_var) ((gcl_var & 0xF00000) == 0x800000)
#define GCL_GetFlagBitFlag(gcl_var) (char)(1 << (((gcl_var << 1) >> 17) & 0xF))
#define GCL_StrHash(hash)           ((GCLCODE_HASHED_STRING << 16) | (hash))

/*---------------------------------------------------------------------------*/

static inline long GCL_GetLong(char *ptr) // memleak
{
    unsigned char *p;
    p = (unsigned char *)ptr;
    return (p[0] << 24) | (p[1] << 16) | (p[2] << 8) | (p[3]);
}

static inline long GCL_GetShort(char *ptr) // memleak
{
    unsigned char *p;
    p = (unsigned char *)ptr;
    return (signed short)((p[0] << 8) | (p[1]));
}

static inline char GCL_GetByte(char *ptr) // memleak
{
    return *ptr;
}

#define GCL_AdvanceShort(p)     p += sizeof(unsigned short)
#define GCL_AdvanceByte(p)      p += sizeof(unsigned char)

/*---------------------------------------------------------------------------*/

/* gcl_init.c */
void GCL_ChangeSenerioCode(int demo_flag);
void GCL_StartDaemon(void);
void GCL_ResetSystem(void);

/* basic.c */
void GCL_InitBasicCommands(void);

/* command.c */
int  GCL_AddCommMulti(GCL_COMMANDDEF *def);
int  GCL_Command(unsigned char *ptr);
void GCL_ForceExecProc(int proc_id, GCL_ARGS *args);
int  GCL_ExecProc(int proc_id, GCL_ARGS *args);
int  GCL_LoadScript(unsigned char *);
int  GCL_ExecBlock(unsigned char *top, GCL_ARGS *args);
void GCL_ExecScript(void);

/* expr.c */
int GCL_Expr(unsigned char *pScript, int *retValue);

/* parse.c */
void            GCL_SetArgTop(unsigned char *);
unsigned char  *GCL_GetNextValue(unsigned char *top, int *type_p, int *value_p);
int            *GCL_SetArgStack(GCL_ARGS *args);
void            GCL_UnsetArgStack(void *stack);
int             GCL_GetArgs(int argno);
void            GCL_SetCommandLine(unsigned char *argtop);
void            GCL_UnsetCommandLine(void);
char           *GCL_GetOption(char c);
int             GCL_StrToInt(unsigned char *pScript);
int             GCL_StrToSV(unsigned char *pInScript, SVECTOR *pOut3Words);
char           *GCL_ReadString(char *pScript);
unsigned char  *GCL_GetParamResult(void);
int             GCL_GetNextParamValue(void);
void            GCL_ReadParamVector( SVECTOR * );
void            GCL_ParseInit(void);

/* variable.c */
void            GCL_SaveLinkVar(short *gameVar);
int             GCL_MakeSaveFile(char *saveBuf);
int             GCL_SetLoadFile(char *saveBuf);
void            GCL_InitVar(void);
void            GCL_InitClearVar(void);
void            GCL_SaveVar(void);
void            GCL_RestoreVar(void);
unsigned char  *GCL_GetVar(unsigned char *top, int *type_p, int *value_p);
unsigned char  *GCL_SetVar(unsigned char *top, unsigned int value);
unsigned char  *GCL_VarSaveBuffer(unsigned char *top);

/* external stuff */
int             GM_InitBinds_8002D1A8(void);
NEWCHARA        GM_GetChara_8002A8C4(unsigned char *pScript);

MAP            *GCL_Command_mapdef_impl_800310D0(void);
void            GCL_Command_camera_helper_80030888(SVECTOR *vec1, SVECTOR *vec2, int param_3_bool);
void            GCL_Command_camera_helper2_800308E0(SVECTOR *vec1, SVECTOR *vec2, int param_3_bool);
void            GCL_Command_camera_helper3_80030938(SVECTOR *pVec);
void            GCL_Command_camera_helper4_80030980(int param_1);
unsigned int    GCL_Command_menu_helper_8002CA48(void);
void            GCL_Command_sound_impl_8002E688(void);

// TODO: it's defined here, make a static inline in game.h?
void GM_CameraSetAlertMask_80030850(unsigned int param_1, unsigned int param_2);

// TODO: move to game.h?
void sub_8002FCF0(void);

#endif // _LIBGCL_H_
