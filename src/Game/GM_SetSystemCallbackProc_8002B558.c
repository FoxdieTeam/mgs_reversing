extern unsigned short gSystemCallbackProcs_800B58C0[];

void GM_SetSystemCallbackProc_8002B558(int index, int proc)
{
    gSystemCallbackProcs_800B58C0[index] = proc;
}
