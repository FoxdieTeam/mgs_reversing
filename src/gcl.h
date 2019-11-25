#ifndef GCL_H
#define GCL_H

struct Actor;

typedef struct Actor*(*TGCL_CommandFn)(int scriptData, int scriptBinds, unsigned char* pScript);

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

#endif // GCL_H
