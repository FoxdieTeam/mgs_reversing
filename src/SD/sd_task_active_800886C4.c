extern volatile int sd_flags_800C0BFC;

int sd_task_active_800886C4(void)
{
    if (sd_flags_800C0BFC & 0x80)
    {
        return 1;
    }

    return 0;
}
