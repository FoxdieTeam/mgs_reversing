#include "linker.h"

/*
const int s07a_dword_800E2F5C = 0x800D8D48;
const int s07a_dword_800E2F60 = 0x800D8D98;
const int s07a_dword_800E2F64 = 0x800D8E60;
const int s07a_dword_800E2F68 = 0x800D8E1C;
const int s07a_dword_800E2F6C = 0x800D8EA4;
const int s07a_dword_800E2F70 = 0x800D8EE4;
const int s07a_dword_800E2F74 = 0x800D8FD8;
const int s07a_dword_800E2F78 = 0x800D9020;
const int s07a_dword_800E2F7C = 0x800D9060;
const int s07a_dword_800E2F80 = 0x800D9040;
const int s07a_dword_800E2F84 = 0x800D908C;
const int s07a_dword_800E2F88 = 0x800D908C;
*/
const char s07a_aFamasx_800E2F8C[] = "FAMAS x 15";
const char s07a_aSocomx_800E2F98[] = "SOCOM x 12";
const char s07a_dword_800E2FA4[] = {'R', 'A', 'T', 'I'};
const char s07a_dword_800E2FA8[] = {'O', 'N', ' ', 'x'};
const char s07a_dword_800E2FAC[] = {' ', '1', 0x0, ' '};
const char s07a_aOkokokodd_800E2FB0[] = " okokoko %d -> %d \n";
const char s07a_aHazuredd_800E2FC4[] = " hazure %d -> %d \n";
const char s07a_aToilletzoned_800E2FD8[] = " toillet zone = %d \n";
const char s07a_aKroekroekrokeorkdd_800E2FF0[] = " kroekroekrokeork %d %d\n";
const char s07a_aOuttoilletgoaddrd_800E300C[] = " out toillet go addr=%d \n";
const char s07a_a_800E3028[] = "0+";
const char s07a_a_800E302C[] = "1+";
const char s07a_a_800E3030[] = "2+";
const char s07a_a_800E3034[] = "3+";
const char s07a_aCrootdrootdpatdnpointsd_800E3038[] = "c_root= %d root %d pat %d n_points = %d \n";
const char s07a_aActdtimeddirdcond_800E3064[] = "act=%d, time=%d dir=%d con=%d\n";
const char s07a_aKirari_800E3084[] = "kirari01";
const char s07a_aRootchange_800E3090[] = " Root Change !!\n";
const char s07a_dword_800E30A4[] = {0x0, 0x0, 0x0, 0x0};