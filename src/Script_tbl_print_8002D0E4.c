#include "linker.h"
#include "gcl.h"

extern const char aPrint[];
extern const char aS_2[];
extern const char aD_3[];
extern const char asc_800AB428[];

extern void     mts_printf_8008BBA0(const char*, ...);
unsigned char*  GCL_Execute_8002069C(unsigned char* pScript, int* ppScript, int* pRet);

int Script_tbl_print_8002D0E4(unsigned char *pScript)
{
    int exec_ret;
    int readArgValue;

    mts_printf_8008BBA0(aPrint); // "print: "
    if (pScript)
    {
        do {
            pScript = GCL_Execute_8002069C(pScript, &exec_ret, &readArgValue);
            if (exec_ret == 0)
                break;
            if (exec_ret == 7)
                mts_printf_8008BBA0(aS_2, readArgValue); // "%s"
            else
                mts_printf_8008BBA0(aD_3, readArgValue); // "%d"
        } while (pScript);
    }
    mts_printf_8008BBA0(asc_800AB428); // "\n"
    return 0;
}
