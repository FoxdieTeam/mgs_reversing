#include <SYS/TYPES.H>

/**
 * @brief Generate a simple hash code (16-bit) from a string.
 *
 * @param string input string
 * @return int hash value
 */
int GV_StrCode_80016CCC(const char *string)
{
    u_char  c;
    u_char *p = (u_char *)string;
    u_short id = 0;

    while ((c = *p++))
    {
        id = ((id << 5) | (id >> 11));
        id += c;
    }
    return id;
}
