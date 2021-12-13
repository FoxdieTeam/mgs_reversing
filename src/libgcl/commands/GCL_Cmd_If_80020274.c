#include "gcl.h"

int GCL_Cmd_If_80020274 ( char *top )
{
	int type, res;
	int block;
	char *p = top;
EXEC_ELSE:
	p = GCL_GetNextValue_8002069C( p, &type, &res );
EXEC_IF:
	p = GCL_GetNextValue_8002069C( p, &type, &block );

	if ( res )
	{
		GCL_ExecBlock_80020118( ( unsigned char* )block, 0 );
	}
	else
	{
		p = GCL_GetNextValue_8002069C( p, &type, &res );

		if ( p )
		{
			p = ( char* )res;
			
			switch ( type >>= 16 )
			{
				case 0x65:
					res = 1;
					goto EXEC_IF;
				case 0x69:
					goto EXEC_ELSE;
			}
		}
	}

	return 0;
}