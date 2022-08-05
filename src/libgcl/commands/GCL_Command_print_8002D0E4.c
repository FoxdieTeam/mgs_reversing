#include "linker.h"
#include "libgcl/gcl.h"
#include "mts/mts_new.h"

extern const char aPrint[];
extern const char aS_2[];
extern const char aD_3[];
extern const char asc_800AB428[];

/* unsigned char*  GCL_GetNextValue_8002069C(unsigned char* pScript, int* ppScript, int* pRet); */

int GCL_Command_print_8002D0E4(unsigned char *argc, char **argv) // argc ??
{
    int code;
    int value;

    mts_printf_8008BBA0(aPrint); // "print: "
    if (argc)
    {
        do {
            argc = GCL_GetNextValue_8002069C(argc, &code, &value);
            if (code == GCLCODE_NULL)
                break;
            if (code == GCLCODE_STRING)
                mts_printf_8008BBA0(aS_2, value); // "%s"
            else
                mts_printf_8008BBA0(aD_3, value); // "%d"
        } while (argc);
    }
    mts_printf_8008BBA0(asc_800AB428); // "\n"
    return 0;
}
