#include "libgcl.h"
#include "common.h"

enum
{
    OP_END,
    OP_MNS, OP_NOT, OP_NEG,
    OP_ADD, OP_SUB, OP_MUL, OP_DIV, OP_MOD,
    OP_EQ, OP_NE, OP_LT, OP_LE, OP_GT, OP_GE,
    OP_OR, OP_AND, OP_XOR,
    OP_OROR, OP_ANDAND,
    OP_SET
};

static int calc( int op, int value1, int value2 )
{
    switch ( op )
    {
    case OP_MNS: return -value2;
    case OP_NOT: return !value2;
    case OP_NEG: return ~value2;
    case OP_ADD: return ( value1 + value2 );
    case OP_SUB: return ( value1 - value2 );
    case OP_MUL: return ( value1 * value2 );
    case OP_DIV: return ( value1 / value2 );
    case OP_MOD: return ( value1 % value2 );
    case OP_EQ: return ( value1 == value2 );
    case OP_NE: return ( value1 != value2 );
    case OP_LT: return ( value1 < value2 );
    case OP_LE: return ( value1 <= value2 );
    case OP_GT: return ( value1 > value2 );
    case OP_GE: return ( value1 >= value2 );
    case OP_OR: return ( value1 | value2 );
    case OP_AND: return ( value1 & value2 );
    case OP_XOR: return ( value1 ^ value2 );
    case OP_OROR: return ( value1 || value2 );
    case OP_ANDAND: return ( value1 && value2 );
    }

    return 0;
}

typedef struct {
    int value;
    char *ptr;
} EXPR_STACK;

int GCL_Expr( char *data, int *value )
{
    int type;
    char *p;
    EXPR_STACK *sp;

    sp = (EXPR_STACK *)SCRPAD_ADDR + 64;

    p = data;

    for ( ;; )
    {
        type = *p;
        if ( type == GCL_OP )
        {
            int op;

            op = p[ 1 ];
            if ( op == OP_END )
            {
                if ( value != NULL )
                {
                    *value = sp[ -1 ].value;
                }

                return sp[ -1 ].value;
            }
            else if ( op == OP_SET )
            {
                GCL_SetVar( sp[ -2 ].ptr, sp[ -1 ].value );
                sp[ -2 ].value = sp[ -1 ].value;
            }
            else
            {
                sp[ -2 ].value = calc( op, sp[ -2 ].value, sp[ -1 ].value );
                sp[ -2 ].ptr = NULL;
            }

            sp--;
            p += sizeof(short);
        }
        else
        {
            int val;

            sp->ptr = p;
            p = GCL_GetNextValue( p, &type, &val );
            sp->value = val;
            sp++;
        }
    }
}
