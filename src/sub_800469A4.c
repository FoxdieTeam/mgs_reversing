

void         font_clear_800468FC(int param_1);
unsigned int font_draw_string_80045D0C(int param_1, unsigned int param_2, int param_3, char *param_4, int param_5);

void sub_800469A4(int param_1, char *param_2)

{
    font_clear_800468FC(param_1);
    font_draw_string_80045D0C
                        (param_1, 0, (unsigned int) *(char *)(param_1 + 3), param_2, (unsigned int) *(char *)(param_1 + 5));
    return;
}
