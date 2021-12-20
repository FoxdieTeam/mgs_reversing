#include "gcl.h"

typedef struct
{
	int		value;
	char	*ptr; 
} EXPR_STACK;

extern char *GCL_SetVar_8002171C( char *top, int value ) ;
extern int   GCL_Operator_Evaluate_80020430( int operation, int v1, int v2 ) ;

int GCL_Expr_8002058C ( char* data, char **a1 )
{
	EXPR_STACK *sp;
	int type, value;
	char *p;

	sp = ( EXPR_STACK* )0x1F800200;
	p = data;

	for (;;)
	{
		type = *p;

		if ( type == 0x31 )
		{
			unsigned int op = p[1];

			if ( !op )
			{
				if ( a1 )
				{
					*a1 = ( char * )( sp - 1 )->value;
				}
				return ( sp - 1 )->value;
			}

			if ( op == 0x14 )
			{
				GCL_SetVar_8002171C( ( sp - 2 )->ptr, ( sp - 1 )->value );
				( sp - 2 )->value = ( sp - 1 )->value;
			} 
			else
			{
				( sp - 2 )->value = GCL_Operator_Evaluate_80020430( op, ( sp - 2 )->value, ( sp - 1 )->value );
				( sp - 2 )->ptr = 0;
			}

			sp--;
			GCL_AdvanceShort( p );

		}
		else
		{
			sp->ptr = p;
			p = GCL_GetNextValue_8002069C( p, &type, &value );
			sp->value = value;
			sp++;
		}
	}
}