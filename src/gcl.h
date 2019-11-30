#ifndef GCL_H
#define GCL_H

typedef struct GCLArgsPtr
{
    short count;
    int* pArgs;
} GCLArgsPtr;

typedef int(*TGCL_CommandFn)(unsigned char* pScript);

// A hashed name of a GCL command and pointer to function that implements the command
typedef struct GCL_CommandTableEntry
{
	unsigned short hashCode;
	TGCL_CommandFn function;
} GCL_CommandTableEntry;

// A linked list containing pointers to arrays of GCL_CommandTableEntry
typedef struct GCL_CommandChain
{
	struct GCL_CommandChain* pNext;
	int commandTableSize;
	GCL_CommandTableEntry* pTable;
}  GCL_CommandChain;

void GCL_StartDaemon_8001FCDC(void);

int GCL_Run_80020118(unsigned char *pScript, GCLArgsPtr *pArgs);
int GCL_RunOrCancelProc_8001FF2C(int procId, GCLArgsPtr *pArgs);
int GCL_GetParam_80020968(int paramName);
int sub_80020AD4(void);
unsigned char* sub_80020AA4(void);
unsigned char* GCL_Execute_8002069C(unsigned char* pScript, int* ppScript, int* pRet);

#endif // GCL_H
