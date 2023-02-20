#include "libgcl.h"

int calc_80020430(int operation, int v1, int v2)
{
    switch (operation)
    {
    case eNegate:
        return -v2;
    case eIsZero:
        return v2 == 0;
    case eComplement:
        return ~v2;
    case eAdd:
        return v1 + v2;
    case eSubtract:
        return v1 - v2;
    case eMultiply:
        return v1 * v2;
    case eDivide:
        return v1 / v2;
    case eModulus:
        return v1 % v2;
    case eEquals:
        return v1 == v2;
    case eNotEquals:
        return v1 != v2;
    case eLessThan:
        return v1 < v2;
    case eLessThanOrEqual:
        return v1 <= v2;
    case eGreaterThan:
        return v1 > v2;
    case eGreaterThanOrEqual:
        return v1 >= v2;
    case eBitWiseOR:
        return v1 | v2;
    case eBitWiseAND:
        return v1 & v2;
    case eBitWiseXOR:
        return v1 ^ v2;
    case eOr:
        return v1 || v2;
    case eAnd:
        return v1 && v2;
    default:
        return 0;
    }
    return 0;
}

int GCL_Expr_8002058C(unsigned char *pScript, int *retValue)
{
    EXPR_STACK *operands;
    char       *ptr;
    int code, value, operator;

    operands = (EXPR_STACK *)0x1F800200;
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
                    *retValue = operands[-1].value;
                }
                return operands[-1].value;
            }
            if (operator== eEqual)
            {
                GCL_SetVar_8002171C(operands[-2].ptr, operands[-1].value);
                operands[-2].value = operands[-1].value;
            }
            else
            {
                operands[-2].value = calc_80020430(operator, operands[-2].value, operands[-1].value);
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
