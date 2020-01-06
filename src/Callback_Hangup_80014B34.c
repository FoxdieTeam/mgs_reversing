extern const char* aNone2_800AB34C;
extern const char* aHangupS[];
extern void mts_printf_8008BBA0(const char*, ...);

void Callback_Hangup_80014B34()
{
  mts_printf_8008BBA0((const char*)aHangupS, aNone2_800AB34C);
}
