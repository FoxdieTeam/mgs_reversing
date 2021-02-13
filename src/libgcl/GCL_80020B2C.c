
#include "gcl.h"

void GCL_80020B2C(unsigned char *pScript)
{
	int	exec_ret;
	int arg_value;
  
	do {
		pScript = GCL_Execute_8002069C(pScript, &exec_ret, &arg_value);
	} while (exec_ret != 0);
	return;
}
