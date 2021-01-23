#ifndef GCL_H
#define GCL_H

// A hashed name of an actor and a pointer to a function that creates an instance of said actor
struct Actor;
typedef struct Actor *(*TGCL_ActorCreateFn)(int unknown1, int binds, unsigned char *pScript2, int unknown);

typedef struct GCL_ActorTableEntry
{
	unsigned short hashCode;
	TGCL_ActorCreateFn function;
} GCL_ActorTableEntry;

// A hashed name of a GCL command and pointer to function that implements the command
typedef int (*TGCL_CommandFn)(unsigned char *pScript);

typedef struct GCL_CommandTableEntry
{
	unsigned short hashCode;
	TGCL_CommandFn function;
} GCL_CommandTableEntry;

// A linked list containing pointers to arrays of GCL_CommandTableEntry
typedef struct GCL_CommandChain
{
	struct GCL_CommandChain *pNext;
	int commandTableSize;
	GCL_CommandTableEntry *pTable;
} GCL_CommandChain;

typedef struct GCLArgsPtr
{
	short count;
	int *pArgs;
} GCLArgsPtr;

void GCL_StartDaemon_8001FCDC(void);

int GCL_Run_80020118(unsigned char *pScript, GCLArgsPtr *pArgs);
int GCL_RunOrCancelProc_8001FF2C(int procId, GCLArgsPtr *pArgs);
int GCL_GetParam_80020968(int paramName);
int GCL_Get_Param_80020AD4(void);
unsigned char *GCL_Get_Param_Result_80020AA4(void);
unsigned char *GCL_Execute_8002069C(unsigned char *pScript, int *ppScript, int *pRet);
int GCL_ReadVector_80020A14(unsigned char *pInScript, short *pOut3Words);
void GCL_SetMainOrDemo_8001FCB0(int bMain);

int GCL_800209E8(unsigned char *uParm1);

#define GCL_ReadShort(p) ( p[1] ) | ( p[0] << 8 )
#define GCL_AdvanceShort(p) p += sizeof(short)

#define GCL_ReadByte(p) p[0]
#define GCL_AdvanceByte(p) p += sizeof(unsigned char)


#endif // GCL_H
