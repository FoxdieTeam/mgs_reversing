#ifndef GCL_H
#define GCL_H

#define GAME_FLAG_BIT_01	0x1
#define GAME_FLAG_BIT_02	0x2
#define GAME_FLAG_BIT_03	0x4
#define GAME_FLAG_BIT_04	0x8
#define GAME_FLAG_BIT_05	0x10
#define GAME_FLAG_BIT_06	0x20
#define GAME_FLAG_BIT_07	0x40
#define GAME_FLAG_BIT_08	0x80
#define GAME_FLAG_BIT_09	0x100
#define GAME_FLAG_BIT_10	0x200
#define GAME_FLAG_BIT_11	0x400
#define GAME_FLAG_BIT_12	0x800
#define GAME_FLAG_BIT_13	0x1000
#define GAME_FLAG_BIT_14	0x2000
#define GAME_FLAG_BIT_15	0x4000
#define GAME_FLAG_BIT_16	0x8000
#define GAME_FLAG_BIT_17	0x10000
#define GAME_FLAG_BIT_18	0x20000
#define GAME_FLAG_BIT_19	0x40000
#define GAME_FLAG_BIT_20	0x80000
#define GAME_FLAG_BIT_21	0x100000
#define GAME_FLAG_BIT_22	0x200000
#define GAME_FLAG_BIT_23	0x400000
#define GAME_FLAG_BIT_24	0x800000
#define GAME_FLAG_BIT_25	0x1000000
#define GAME_FLAG_BIT_26	0x2000000
#define GAME_FLAG_BIT_27	0x4000000
#define GAME_FLAG_BIT_28	0x8000000
#define GAME_FLAG_BIT_29	0x10000000
#define GAME_FLAG_BIT_30	0x20000000
#define GAME_FLAG_BIT_31	0x40000000
#define GAME_FLAG_BIT_32	0x80000000

// A hashed name of an actor and a pointer to a function that creates an instance of said actor
struct                      Actor;
typedef struct Actor        *(*TGCL_ActorCreateFn)(int unknown1, int binds, unsigned char *pScript2, int unknown);

typedef struct				GCL_ActorTableEntry
{
	unsigned short			hashCode;
	TGCL_ActorCreateFn		function;
} GCL_ActorTableEntry;

// A hashed name of a GCL command and pointer to function that implements the command
typedef int                 (*TGCL_CommandFn)(unsigned char *pScript);

typedef struct				GCL_CommandTableEntry
{
	unsigned short			hashCode;
	TGCL_CommandFn			function;
} GCL_CommandTableEntry;

// A linked list containing pointers to arrays of GCL_CommandTableEntry
typedef struct				GCL_CommandChain
{
	struct GCL_CommandChain *pNext;
	int                     commandTableSize;
	GCL_CommandTableEntry   *pTable;
} GCL_CommandChain;

typedef struct              GCLArgsPtr
{
	short                   count;
	int                     *pArgs;
} GCLArgsPtr;

void						GCL_StartDaemon_8001FCDC(void);

int                         GCL_Run_80020118(unsigned char *pScript, GCLArgsPtr *pArgs);
int                         GCL_RunOrCancelProc_8001FF2C(int procId, GCLArgsPtr *pArgs);
int                         GCL_GetParam_80020968(int paramName);
int                         GCL_Get_Param_80020AD4(void);
unsigned char               *GCL_Get_Param_Result_80020AA4(void);
unsigned char               *GCL_Execute_8002069C(unsigned char *pScript, int *ppScript, int *pRet);
int                         GCL_ReadVector_80020A14(unsigned char *pInScript, short *pOut3Words);
void                        GCL_SetMainOrDemo_8001FCB0(int bMain);

int                         GCL_800209E8(unsigned char *uParm1);

#define GCL_ReadShort(p)    ( p[1] ) | ( p[0] << 8 )
#define GCL_AdvanceShort(p) p += sizeof(short)

#define GCL_ReadByte(p)     p[0]
#define GCL_AdvanceByte(p)  p += sizeof(unsigned char)


#endif // GCL_H
