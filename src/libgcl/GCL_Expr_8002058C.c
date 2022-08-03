#include "gcl.h"

typedef struct		EXPR_STACK
{
	int				value;
	unsigned char	*ptr; 
} EXPR_STACK;

char			*GCL_SetVar_8002171C(unsigned char *pScript, int value);
int			calc_80020430(int operation, int v1, int v2);

int	GCL_Expr_8002058C(unsigned char *pScript, int *retValue)
{
	EXPR_STACK	*operands;
	char		*ptr;
	int			code, value, operator;

	operands = (EXPR_STACK*)0x1F800200;
	ptr = pScript;
	for (;;)
	{
		code = *ptr;
		if (code == GCLCODE_EXPR_OPERATOR)
		{
			// Operator found, process operands
			operator = ptr[1];
			if (!operator)
			{
				if (retValue)
				{
					*retValue = operands[-1].value;
				}
				return operands[-1].value;
			}
			if (operator == eEqual)
			{
				GCL_SetVar_8002171C(operands[-2].ptr, operands[-1].value);
				operands[-2].value = operands[-1].value;
			} 
			else
			{
				operands[-2].value = calc_80020430(operator,
															operands[-2].value,
															operands[-1].value);
				operands[-2].ptr = 0;
			}
			operands--;
			GCL_AdvanceShort(ptr);
		}
		else
		{
			// Add operand
			operands->ptr = ptr;
			ptr = GCL_GetNextValue_8002069C(ptr, &code, &value);
			operands->value = value;
			operands++;
		}
	}
}
