#ifndef _MAP_H_
#define _MAP_H_


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


struct KmdAndLitHeader
{
    int field_0_numBones;
    int field_4_numMesh;
    int field_8;
    int field_C;
    int field_10;
    int field_14;
    int field_18;
    int field_1C;
  // int field_20;
  //  int field_24;
};

#endif // _MAP_H_
