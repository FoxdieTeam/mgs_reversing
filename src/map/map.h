#ifndef _MAP_H_
#define _MAP_H_

#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>

typedef struct map_record
{
    int                 field_0_map_index_bit;
    unsigned short      field_4_mapNameHash;
    unsigned short      field_6_bUsed;
    void                *field_8_hzd;
    struct LitHeader    *field_C_lit_file;
    int                 field_10_zone_id;
} map_record;


struct LitHeader
{
    int                 field_0_num_lights;
};

#endif // _MAP_H_
