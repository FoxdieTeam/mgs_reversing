extern const char* GV_DebugMes_800AB34C;
extern const char aHangupS[];
extern void mts_printf_8008BBA0(const char*, ...);

void Callback_Hangup_80014B34(void)
{
  mts_printf_8008BBA0(aHangupS, GV_DebugMes_800AB34C);
}
