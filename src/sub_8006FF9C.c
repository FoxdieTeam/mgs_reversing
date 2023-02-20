typedef struct sub_8006FF9C_unkn1
{
    char  field_0_pad[0x2E];
    short field_2E;
} sub_8006FF9C_unkn1;

typedef struct sub_8006FF9C_unkn2
{
    char                 field_0_pad[0xC];
    short                field_C;
    char                 field_E_pad[0x2];
    short                field_10;
    char                 field_14_pad[0x8];
    sub_8006FF9C_unkn1 **field_1C;
} sub_8006FF9C_unkn2;

int sub_8006FF9C(sub_8006FF9C_unkn2 *arg0, sub_8006FF9C_unkn1 *arg1)
{
    int temp;

    if (arg0->field_C >= arg0->field_10)
    {
        return -1;
    }

    temp = arg0->field_C;

    arg0->field_1C[temp] = arg1;
    arg0->field_C = temp + 1;
    arg1->field_2E |= 0x1;

    return 0;
}
