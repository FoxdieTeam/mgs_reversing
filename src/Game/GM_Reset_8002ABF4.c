extern int  GCL_BindsInit_8002D1A8();
extern int  GM_AlertModeInit_8002EAA8();
extern void GM_InitWhereSystem_8002597C(void);
extern int  sub_8002A978();
extern void sub_8002D3F0();
extern int  sub_80030760();
extern void sub_80032C68();

void GM_Reset_8002ABF4()
{
    sub_80030760();
    GM_InitWhereSystem_8002597C();
    sub_8002D3F0();
    sub_80032C68();
    GCL_BindsInit_8002D1A8();
    sub_8002A978();
    GM_AlertModeInit_8002EAA8();
    return;
}
