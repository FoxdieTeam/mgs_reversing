

extern void GV_Free_80016230(void *ptr);

void HZD_Free_80021C40(void* param_1)

{
    if (param_1 != 0)
    {
        GV_Free_80016230(param_1);
    }
    return;
}
