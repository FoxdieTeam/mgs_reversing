

extern int  dword_800ABA50;

int sub_8004E2B4(int arg0)
{
    int temp_v0;

    temp_v0 = dword_800ABA50 | arg0;
    dword_800ABA50 = temp_v0;
    return temp_v0;
}
