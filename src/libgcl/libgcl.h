#ifndef GCL_H
#define GCL_H

#include "Menu/menuman.h"
#include "Game/map.h"

// A hashed name of an actor and a pointer to a function that creates an instance of said actor
struct GV_ACT;
typedef GV_ACT *(*TGCL_ActorCreateFn)(int name, int where, int argc, char **argv);

typedef struct GCL_ActorTableEntry
{
    unsigned short     hashCode;
    TGCL_ActorCreateFn function;
} GCL_ActorTableEntry;

typedef int (*TGCL_CommandFn)(unsigned char *pScript);
int GCL_Command_if_80020274(unsigned char *pScript);
int GCL_Command_eval_80020318(unsigned char *pScript);
int GCL_Cmd_Return_80020404(unsigned char *pScript);
int GCL_Command_foreach_8002033C(unsigned char *pScript);
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

// A hashed name of a GCL command and pointer to function that implements the command
typedef struct GCL_COMMANDLIST
{
    unsigned short hashCode;
    TGCL_CommandFn function;
} GCL_COMMANDLIST;

// leak
typedef struct _gcl_commanddef
{
    struct _gcl_commanddef *next;
    int                     n_commlist;
    GCL_COMMANDLIST        *commlist;
} GCL_COMMANDDEF;

// leak
typedef struct
{
    unsigned short argc;
    long          *argv;
} GCL_ARGS;

typedef struct
{
    unsigned short procNameHashed;
    unsigned short offset;
} GCL_ProcTableEntry;

typedef struct
{
    GCL_ProcTableEntry *field_0_procTable;
    unsigned char      *field_4_pByteCode;
    unsigned char      *field_8_pMainProc;
} GCL_FileData;

typedef struct EXPR_STACK
{
    int            value;
    unsigned char *ptr;
} EXPR_STACK;

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
    SVECTOR     field_00_pos;
    short       field_08_trg[3]; // SVECTOR w/ padding as alertMask?
    short       field_0e_alertMask;
    signed char field_10_param1; // example: d:CAM_FIX
    u_char      field_11_param2; // example: d:CAM_INTERP_LINER
    char        field_12_param3; // example: d:CAM_CAM_TO_TRG
    char        field_13_param_p;
} CAMERA;

enum GCLOperators
{
    eNegate = 1,
    eIsZero = 2,
    eComplement = 3,
    eAdd = 4,
    eSubtract = 5,
    eMultiply = 6,
    eDivide = 7,
    eModulus = 8,
    eEquals = 9,
    eNotEquals = 10,
    eLessThan = 11,
    eLessThanOrEqual = 12,
    eGreaterThan = 13,
    eGreaterThanOrEqual = 14,
    eBitWiseOR = 15,
    eBitWiseAND = 16,
    eBitWiseXOR = 17,
    eOr = 18,
    eAnd = 19,
    eEqual = 20,
};

#define GAME_FLAG_BIT_01 0x1
#define GAME_FLAG_BIT_02 0x2
#define GAME_FLAG_BIT_03 0x4
#define GAME_FLAG_BIT_04 0x8
#define GAME_FLAG_BIT_05 0x10
#define GAME_FLAG_BIT_06 0x20
#define GAME_FLAG_BIT_07 0x40
#define GAME_FLAG_BIT_08 0x80
#define GAME_FLAG_BIT_09 0x100
#define STATE_ENEMY_OFF  0x200
#define GAME_FLAG_BIT_11 0x400
#define GAME_RADAR_ENABLED 0x800
#define GAME_FLAG_BIT_13 0x1000
#define GAME_FLAG_BIT_14 0x2000
#define GAME_FLAG_BIT_15 0x4000
#define GAME_FLAG_BIT_16 0x8000
#define GAME_FLAG_BIT_17 0x10000
#define GAME_FLAG_BIT_18 0x20000
#define GAME_FLAG_BIT_19 0x40000
#define GAME_FLAG_BIT_20 0x80000
#define GAME_FLAG_BIT_21 0x100000
#define GAME_FLAG_BIT_22 0x200000
#define GAME_FLAG_BIT_23 0x400000
#define GAME_FLAG_BIT_24 0x800000
#define GAME_FLAG_BIT_25 0x1000000
#define GAME_FLAG_BIT_26 0x2000000
#define GAME_FLAG_BIT_27 0x4000000
#define GAME_FLAG_BIT_28 0x8000000
#define GAME_FLAG_BIT_29 0x10000000
#define GAME_FLAG_BIT_30 0x20000000
#define GAME_FLAG_BIT_31 0x40000000
#define GAME_FLAG_BIT_32 0x80000000

// Radio codes (radio.dat files)
#define RDCODE_NULL 0
#define RDCODE_TALK 1
#define RDCODE_VOICE 2
#define RDCODE_ANIM 3
#define RDCODE_ADD_CONTACT 4
#define RDCODE_MEMSAVE 5
#define RDCODE_SOUND 6
#define RDCODE_PROMPT 7
#define RDCODE_VARSAVE 8
#define RDCODE_IF 0x10
#define RDCODE_ELSE 0x11
#define RDCODE_ELSEIF 0x12
#define RDCODE_SWITCH 0x20
#define RDCODE_SWITCH_CASE 0x21
#define RDCODE_SWITCH_DEFAULT 0x22
#define RDCODE_RANDSWITCH 0x30
#define RDCODE_RANDSWITCH_CASE 0x31
#define RDCODE_EVAL 0x40
#define RDCODE_SCRIPT 0x80
#define RDCODE_ENDLINE 0xFF

// Gcl codes (.gcx files)
#define GCLCODE_NULL 0
#define GCLCODE_SHORT 1
#define GCLCODE_BYTE 2
#define GCLCODE_CHAR 3
#define GCLCODE_BOOL 4
#define GCLCODE_HASHED_STRING 6 // can also be a hashed proc name
#define GCLCODE_STRING 7
#define GCLCODE_PROC_CALL 8 // hashed proc name to call
#define GCLCODE_SDCODE 9
#define GCLCODE_TABLE_CODE 10 // .vox, .dmo and radio.dat
#define GCLCODE_VARIABLE 0x10 // variables codes are: 0x11, 0x12, 0x13, 0x14, 0x16, 0x18
#define GCLCODE_STACK_VAR 0x20
#define GCLCODE_EXPRESSION 0x30
#define GCLCODE_EXPR_OPERATOR 0x31
#define GCLCODE_SCRIPT_DATA 0x40
#define GCLCODE_PARAMETER 0x50
#define GCLCODE_COMMAND 0x60
#define GCLCODE_PROC 0x70

#define GCL_IsVariable(gcl_code) ((gcl_code & 0xF0) == GCLCODE_VARIABLE)
#define GCL_IsParam(gcl_code) ((gcl_code & 0xFF) == GCLCODE_PARAMETER)

#define GCL_GetVarTypeCode(gcl_var) (((gcl_var << 1) >> 25) & 0xF)
#define GCL_GetVarOffset(gcl_var) (gcl_var & 0xFFFF)
#define GCL_IsGameStateVar(gcl_var) ((gcl_var & 0xF00000) == 0x800000)
#define GCL_GetBoolVarBitFlag(gcl_var) (char)(1 << (((gcl_var << 1) >> 17) & 0xF))
#define GCL_StrHash(hash) ((GCLCODE_HASHED_STRING << 16) | (hash))

static inline long GCL_GetLong(char *ptr) // leak
{
    unsigned char *p;
    p = (unsigned char *)ptr;
    return (p[0] << 24) | (p[1] << 16) | (p[2] << 8) | (p[3]);
}

static inline long GCL_GetShort(char *ptr) // leak
{
    unsigned char *p;
    p = (unsigned char *)ptr;
    return (signed short)((p[0] << 8) | (p[1]));
}

static inline char GCL_GetByte(char *ptr) // leak
{
    return *ptr;
}

#define GCL_AdvanceShort(p) p += sizeof(short)
#define GCL_AdvanceByte(p) p += sizeof(unsigned char)

void               GCL_StartDaemon_8001FCDC(void);
int                GCL_ExecBlock_80020118(unsigned char *pScript, GCL_ARGS *pArgs);
int                GCL_ExecProc_8001FF2C(int procId, GCL_ARGS *pArgs);
char              *GCL_GetOption_80020968(char paramName);
int                GCL_GetNextParamValue_80020AD4(void);
unsigned char     *GCL_Get_Param_Result_80020AA4(void);
unsigned char     *GCL_GetNextValue_8002069C(unsigned char *pScript, int *retCode, int *retValue);
int                GCL_StrToSV_80020A14(unsigned char *pInScript, SVECTOR *pOut3Words);
void               GCL_ChangeSenerioCode_8001FCB0(int bMain);
char              *GCL_Read_String_80020A70(char *pScript);
unsigned char     *GCL_VarSaveBuffer_800217F0(unsigned char *pScript);
void               GCL_InitVar_80021264();
void               GCL_SaveVar_80021314(void);
unsigned char     *GCL_GetVar_80021634(unsigned char *pScript, int *retCode, int *retValue);
int                GCL_Expr_8002058C(unsigned char *pScript, int *retValue);
int                GCL_StrToInt_800209E8(unsigned char *pScript);
int                GCL_AddCommMulti_8001FD2C(GCL_COMMANDDEF *pChain);
int                GM_InitBinds_8002D1A8(void);
void               GCL_ParseInit_80020B68(void);
void               GCL_InitBasicCommands_8002040C(void);
int                GCL_LoadScript_80020064(unsigned char *);
void               GCL_SetCommandLine_80020934(unsigned char *);
void               GCL_SetArgTop_80020690(unsigned char *);
void               GCL_UnsetCommandLine_80020950(void);
int               *GCL_SetArgStack_8002087C(GCL_ARGS *pArgs);
void               GCL_UnsetArgStack_800208F0(void *stack);
int                GCL_GetArgs_80020904(int param_1);
unsigned char     *GCL_SetVar_8002171C(unsigned char *pScript, unsigned int value);
void               GCL_InitClearVar_800212CC(void);
void               GCL_ResetSystem_8001FD24(void);
void               GCL_RestoreVar_80021488(void);
int                calc_80020430(int operation, int v1, int v2);
TGCL_ActorCreateFn GM_GetChara_8002A8C4(unsigned char *pScript);
void               GCL_ExecScript_80020228();
void               GCL_ForceExecProc_8001FEFC(int procNameHashed, GCL_ARGS *pArgs);
int                GCL_MakeSaveFile_80020C0C(char *saveBuf);
int                GCL_SetLoadFile_80020EAC(char *saveBuf);
void               GCL_SaveLinkVar_80020B90(short *gameVar);
void               GCL_ReadParamVector_80020AFC( SVECTOR * );

MAP *GCL_Command_mapdef_impl_800310D0(void);
void               GCL_Command_camera_helper_80030888(SVECTOR *vec1, SVECTOR *vec2, int param_3_bool);
void               GCL_Command_camera_helper2_800308E0(SVECTOR *vec1, SVECTOR *vec2, int param_3_bool);
void               GCL_Command_camera_helper3_80030938(SVECTOR *pVec);
void               GCL_Command_camera_helper4_80030980(int param_1);
unsigned int       GCL_Command_menu_helper_8002CA48(void);
void               GCL_Command_sound_impl_8002E688(void);

unsigned int       crc32_80020BB4(int len, unsigned char *pData);

// TODO: it's defined here, make a static inline in game.h?
void GM_CameraSetAlertMask_80030850(unsigned int param_1, unsigned int param_2);

// TODO: move to game.h?
void sub_8002FCF0(void);

#endif // GCL_H
