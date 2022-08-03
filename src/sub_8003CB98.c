int  menu_restore_nouse_80043470();
int  sub_8003CFE0(int a1, int a2);
int  sub_8003B5E0(int a1);

int sub_8003CB98(int a1)
{
    int v2;
    int result;
    int v4;

    menu_restore_nouse_80043470();
    v2 = *(short *)(a1 + 476);
    result = -1;
    if (v2 != -1 || (v2 = *(signed char *)(a1 + 493), v2 != -1))
    {
        v4 = sub_8003B5E0(v2);
        result = sub_8003CFE0(v4, 0);
    }
    return result;
}

