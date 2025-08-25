#ifndef __MGS_LIBGCL_H__
#define __MGS_LIBGCL_H__

#include <sys/types.h>
#include <libgte.h>     // for SVECTOR
#include <libgpu.h>
#include "common.h"

/*---------------------------------------------------------------------------*/

typedef struct      // private to libgcl/command.c
{
    unsigned short proc_id;
    unsigned short offset;
} GCL_PROC_TABLE;

typedef struct      // private to libgcl/command.c
{
    GCL_PROC_TABLE *proc_table;
    unsigned char  *proc_body;
    unsigned char  *script_body;
} GCL_SCRIPT;

typedef int (*GCL_COMMANDFUNC)(unsigned char *);

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
#define GCL_OP_NOT          2
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
#define GCL_OP_ASSIGN       20

#define GCL_IsVariable(gcl_code) ((gcl_code & 0xF0) == GCLCODE_VARIABLE)
#define GCL_IsParam(gcl_code) ((gcl_code & 0xFF) == GCLCODE_PARAMETER)

#define GCL_GetVarTypeCode(gcl_var) (((gcl_var << 1) >> 25) & 0xF)
#define GCL_GetVarOffset(gcl_var)   (gcl_var & 0xFFFF)
#define GCL_IsGameStateVar(gcl_var) ((gcl_var & 0xF00000) == 0x800000)
#define GCL_GetFlagBitFlag(gcl_var) (char)(1 << (((gcl_var << 1) >> 17) & 0xF))
#define GCL_StrHash(hash)           ((GCLCODE_HASHED_STRING << 16) | (hash))

/*---------------------------------------------------------------------------*/

// clang-format off
static inline long GCL_GetLong( char *ptr )
{
    unsigned char *p;
    p = ( unsigned char * )ptr;
    return ( p[ 0 ] << 24 ) | ( p[ 1 ] << 16 ) | ( p[ 2 ] << 8 ) | ( p[ 3 ] );
}

static inline long GCL_GetShort( char *ptr )
{
    unsigned char *p;
    p = ( unsigned char * )ptr;
    return ( signed short )( ( p[ 0 ] << 8 ) | ( p[ 1 ] ) );
}

static inline char GCL_GetByte( char *ptr )
{
    return *ptr;
}
// clang-format on

#define GCL_AdvanceShort(p)     p += sizeof(unsigned short)
#define GCL_AdvanceByte(p)      p += sizeof(unsigned char)

/*---------------------------------------------------------------------------*/

extern GCL_ARGS gcl_null_args;

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
int  GCL_LoadScript(unsigned char *datatop);
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

#endif // __MGS_LIBGCL_H__
