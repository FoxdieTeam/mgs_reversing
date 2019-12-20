#include "linker.h"
#include "mts_new.h"

// To disable this they probably linked with an obj that disables printf because having a stub function
// that has varags will insert stack handling code.
// Therefore we map mts_printf_8008BBA0 to null_mts_printf_8008BBA0 in the linker where the stub function
// has on arguments to replicate this behaviour.
void null_mts_printf_8008BBA0(void)
{
    // This has been compiled out to an empty function
}
