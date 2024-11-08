#ifndef _DATACNF_H_
#define _DATACNF_H_

#include <sys/types.h>

typedef struct _STAGE_HEADER
{
    char  field_0;
    char  field_1;
    short field_2_size;
} STAGE_HEADER;

typedef struct _STAGE_CONFIG
{
    unsigned short field_0_hash;
    short          field_2_mode_and_ext[0];
    char           field_2_mode;
    char           field_3_extension;
    int            field_4_size;
} STAGE_CONFIG;

#endif // _DATACNF_H_
