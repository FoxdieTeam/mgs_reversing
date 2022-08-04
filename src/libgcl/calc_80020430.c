#include "libgcl/gcl.h"

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
