#include <sys/types.h>

/**
 *  @brief Generate a simple hash from a string.
 *
 *  Given that the digest is only 16 bits wide, this algorithm is highly
 *  prone to collisions. Check for collisions after precalculating a set
 *  of hashes intended for use at runtime. (e.g. stage data files)
 *
 *  @li Passing an empty string will return 0.
 *  @li Passing a single-char string will return the value of the char.
 *  @li Mutations of strings differing in only the last character will
 *      result in the lowest byte of the hash mirroring that difference.
 *
 *  Input/Output Examples:
 *
 *  @li GV_StrCode("cb_box11") returns @c 0xADDB
 *  @li GV_StrCode("cb_box12") returns @c 0xADDC
 *  @li GV_StrCode("op_kcej_l") returns @c 0x4349
 *  @li GV_StrCode("op_kcej_r") returns @c 0x434F
 *
 *  @param      string      NULL-terminated string.
 *
 *  @retval     0           if @p string is empty.
 *  @retval     non-zero    16-bit hash of @p string.
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
