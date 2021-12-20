#include "gcl.h"

int GCL_Cmd_ForEach_8002033C (char *top )
{
	int argbuf[16];
	GCL_ARGS arg;
	int i, type, value, id;
	char *p = top;
	int* argbuf_p = argbuf;

	for (;;)
	{
		p = GCL_GetNextValue_8002069C( p, &type, &value );

		if ( ( unsigned char )type == 0x50)
		{
			break;
		}

		*argbuf_p = value;
		 argbuf_p++;
	}

	p = GCL_GetNextValue_8002069C( ( unsigned char* )value, &type, &value );
	i = (( int )argbuf_p - ( int )&argbuf) >> 2; //there must be a better way to do this that matches

	id = value;
	arg.argc = 1;
	arg.argv = argbuf;

	while (i > 0)
	{
		GCL_ExecBlock_80020118( ( unsigned char* )id, &arg );
		i--;
		arg.argv++;
	}
	
	return 0;
}