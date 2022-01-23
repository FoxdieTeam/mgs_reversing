
struct mem_card_block
{
    char field_0_name[20];
    char field_14;
    char field_15;
    unsigned short field_16;
    int field_18_size;
};

struct mem_card
{
    unsigned char field_0_card_idx;
    unsigned char field_1_last_op;
    char field_2_file_count;
    char field_3_free_blocks;
    struct mem_card_block field_4_blocks[15];
};

extern struct mem_card gMemCards_800B52F8[2];

void memcard_reset_status_80024A3C(void)
{
    gMemCards_800B52F8[0].field_1_last_op = 2;
    gMemCards_800B52F8[1].field_1_last_op = 2;
}
