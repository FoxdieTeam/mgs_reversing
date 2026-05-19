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

typedef int (*GCL_COMMANDFUNC)(unsigned char *top);

#define GCL_OK          0
#define GCL_RETURN      1
#define GCL_ERROR       -1

typedef struct {
    unsigned short id;
    GCL_COMMANDFUNC func;
} GCL_COMMANDLIST;

typedef struct _gcl_commanddef {
    struct _gcl_commanddef *next;
    int n_commlist;
    GCL_COMMANDLIST *commlist;
} GCL_COMMANDDEF;

#define GCL_COMMANDS(a) { NULL, countof(a), a }

typedef struct {
    u_short argc;
    long *argv;
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

/* ----- Types ----- */

#define GCL_END         0x00

#define GCL_SHORT       0x01    // $w:
#define GCL_BYTE        0x02    // $b:
#define GCL_CHAR        0x03    // $c:
#define GCL_BOOL        0x04    // $f:
#define GCL_VECTOR      0x05    // $v:
#define GCL_STRID       0x06    // $s:
#define GCL_STRING      0x07    //
#define GCL_PROCID      0x08    // $p:
#define GCL_INT         0x09    // $i:
#define GCL_LONG        GCL_INT
#define GCL_SYMBOL      0x0a    // $t:

#define GCL_TYPEMASK    0x0f
#define GCL_TYPE(a)     ((a) & GCL_TYPEMASK)

#define GCL_CONST       0x00
#define GCL_VAR         0x10
#define GCL_ARRAY       0x20

#define GCL_EXPR        0x30
#define GCL_OP          0x31

#define GCL_ARG         0x40
#define GCL_OPTION      0x50
#define GCL_COMMAND     0x60
#define GCL_PROC        0x70

#define GCL_TAGMASK     0xf0
#define GCL_TAG(a)      ((a) & GCL_TAGMASK)

#define GCL_VAR_TYPE_GLOBAL 0x000000
#define GCL_VAR_TYPE_LOCAL  0x100000
#define GCL_VAR_TYPE_SYSTEM 0x400000
#define GCL_VAR_TYPE_LINK   0x800000

#define GCL_IsVariable(gcl_code)    ((gcl_code & 0xF0) == GCL_VAR)
#define GCL_IsParam(gcl_code)       ((gcl_code & 0xFF) == GCL_OPTION)

#define GCL_GetVarTypeCode(gcl_var) (((gcl_var << 1) >> 25) & 0xF)
#define GCL_GetVarOffset(gcl_var)   (gcl_var & 0xFFFF)
#define GCL_IsGameStateVar(gcl_var) ((gcl_var & 0xF00000) == GCL_VAR_TYPE_LINK)
#define GCL_GetFlagBitFlag(gcl_var) (char)(1 << (((gcl_var << 1) >> 17) & 0xF))

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
/*---------------------------------------------------------------------------*/

extern GCL_ARGS gcl_null_args;

/* gcl_init.c */
void GCL_ChangeSenerioCode(int demo_flag);
void GCL_StartDaemon(void);
void GCL_ResetSystem(void);

/* command.c */
int  GCL_AddCommMulti(GCL_COMMANDDEF *def);
int  GCL_Command(unsigned char *ptr);
void GCL_ForceExecProc(int proc_id, GCL_ARGS *args);
int  GCL_ExecProc(int proc_id, GCL_ARGS *args);
int  GCL_LoadScript(unsigned char *datatop);
int  GCL_ExecBlock(unsigned char *top, GCL_ARGS *args);
void GCL_ExecScript(void);

/* basic.c */
void GCL_InitBasicCommands(void);

/* expr.c */
int GCL_Expr(unsigned char *data, int *value);

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
