#include "linker.h"
#include "gcl.h"

void sub_80020B68(void);
void sub_80021264(void);
void sub_8002040C(void);
void sub_8001FC88(unsigned char*); // TODO: Prob wrong
void sub_8001FCB0(int);

void GD_SetFileHandler_80015418(char, void*);

void GCL_StartDaemon_8001FCDC(void)
{
    sub_80020B68();
    sub_80021264();
    sub_8002040C();
    GD_SetFileHandler_80015418('g', sub_8001FC88);
    sub_8001FCB0(0);
}
