#include "libgcl.h"
#include "common.h"

#define OP_END          0
#define OP_MNS          1
#define OP_NOT          2
#define OP_NEG          3
#define OP_ADD          4
#define OP_SUB          5
#define OP_MUL          6
#define OP_DIV          7
#define OP_MOD          8
#define OP_EQ           9
#define OP_NE           10
#define OP_LT           11
#define OP_LE           12
#define OP_GT           13
#define OP_GE           14
#define OP_OR           15
#define OP_AND          16
#define OP_XOR          17
#define OP_OROR         18
#define OP_ANDAND       19
#define OP_SET          20

static int calc(int op, int value1, int value2)
{
    switch (op)
    {
    case OP_MNS:
        return -value2;
    case OP_NOT:
        return !value2;
    case OP_NEG:
        return ~value2;
    case OP_ADD:
        return (value1 + value2);
    case OP_SUB:
        return (value1 - value2);
    case OP_MUL:
        return (value1 * value2);
    case OP_DIV:
        return (value1 / value2);
    case OP_MOD:
        return (value1 % value2);
    case OP_EQ:
        return (value1 == value2);
    case OP_NE:
        return (value1 != value2);
    case OP_LT:
        return (value1 < value2);
    case OP_LE:
        return (value1 <= value2);
    case OP_GT:
        return (value1 > value2);
    case OP_GE:
        return (value1 >= value2);
    case OP_OR:
        return (value1 | value2);
    case OP_AND:
        return (value1 & value2);
    case OP_XOR:
        return (value1 ^ value2);
    case OP_OROR:
        return (value1 || value2);
    case OP_ANDAND:
        return (value1 && value2);
    default:
        return 0;
    }
    return 0;
}

typedef struct {
    int value;
    unsigned char *ptr;
} EXPR_STACK;

int GCL_Expr(unsigned char *data, int *value)
{
    EXPR_STACK *sp;
    char       *ptr;
    int code, val, op;

    sp = (EXPR_STACK *)0x1F800200;
    ptr = data;

    for (;;)
    {
        code = *ptr;
        if (code == GCL_OP)
        {
            // Operator found, process operands
            op = ptr[1];
            if (op == OP_END)
            {
                if (value)
                {
                    *value = sp[-1].value;
                }
                return sp[-1].value;
            }
            if (op == OP_SET)
            {
                GCL_SetVar(sp[-2].ptr, sp[-1].value);
                sp[-2].value = sp[-1].value;
            }
            else
            {
                sp[-2].value = calc(op, sp[-2].value, sp[-1].value);
                sp[-2].ptr = NULL;
            }
            sp--;
            ptr += sizeof(unsigned short);
        }
        else
        {
            // Add operand
            sp->ptr = ptr;
            ptr = GCL_GetNextValue(ptr, &code, &val);
            sp->value = val;
            sp++;
        }
    }
}
