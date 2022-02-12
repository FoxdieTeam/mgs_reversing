#include "linker.h"

void SetMem_8009944C(int);
void FS_CDInit_80021EC4(void);
void sio_output_stop_8008C5B0(void);

void FS_StartDaemon_80014A7C(void)
{
    // CPU exception if >= 2MB ram range is used since retail consoles have 2 MB and dev have 8 MB.
    SetMem_8009944C(2);
    FS_CDInit_80021EC4(); // init cd and the likes
    sio_output_stop_8008C5B0(); // empty func
}
