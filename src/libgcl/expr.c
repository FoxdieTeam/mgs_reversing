#include "libgcl.h"

// #define STATIC static
#define STATIC

STATIC int calc(int op, int value1, int value2)
{
    switch (op)
    {
    case GCL_OP_NEGATE:
        return -value2;
    case GCL_OP_ISZERO:
        return value2 == 0;
    case GCL_OP_COMPL:
        return ~value2;
    case GCL_OP_ADD:
        return value1 + value2;
    case GCL_OP_SUB:
        return value1 - value2;
    case GCL_OP_MUL:
        return value1 * value2;
    case GCL_OP_DIV:
        return value1 / value2;
    case GCL_OP_MOD:
        return value1 % value2;
    case GCL_OP_EQUALS:
        return value1 == value2;
    case GCL_OP_NOT_EQ:
        return value1 != value2;
    case GCL_OP_LESS:
        return value1 < value2;
    case GCL_OP_LESS_EQ:
        return value1 <= value2;
    case GCL_OP_GREATER:
        return value1 > value2;
    case GCL_OP_GREATER_EQ:
        return value1 >= value2;
    case GCL_OP_BITOR:
        return value1 | value2;
    case GCL_OP_BITAND:
        return value1 & value2;
    case GCL_OP_BITXOR:
        return value1 ^ value2;
    case GCL_OP_OR:
        return value1 || value2;
    case GCL_OP_AND:
        return value1 && value2;
    default:
        return 0;
    }
    return 0;
}

typedef struct {
    int            value;
    unsigned char *ptr;
} EXPR_STACK;

int GCL_Expr(unsigned char *pScript, int *retValue)
{
    EXPR_STACK *sp;
    char       *ptr;
    int code, value, operator;

    sp = (EXPR_STACK *)0x1F800200;
    ptr = pScript;
    for (;;)
    {
        code = *ptr;
        if (code == GCLCODE_EXPR_OPERATOR)
        {
            // Operator found, process operands
            operator= ptr[1];
            if (!operator)
            {
                if (retValue)
                {
                    *retValue = sp[-1].value;
                }
                return sp[-1].value;
            }
            if (operator == GCL_OP_EQUAL)
            {
                GCL_SetVar(sp[-2].ptr, sp[-1].value);
                sp[-2].value = sp[-1].value;
            }
            else
            {
                sp[-2].value = calc(operator, sp[-2].value, sp[-1].value);
                sp[-2].ptr = 0;
            }
            sp--;
            GCL_AdvanceShort(ptr);
        }
        else
        {
            // Add operand
            sp->ptr = ptr;
            ptr = GCL_GetNextValue(ptr, &code, &value);
            sp->value = value;
            sp++;
        }
    }
}
