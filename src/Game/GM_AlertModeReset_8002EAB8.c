void GM_CallSystemCallbackProc_8002B570(int id, int arg);

void GM_AlertModeReset_8002EAB8(void)
{
    GM_CallSystemCallbackProc_8002B570(2, 0);
}
