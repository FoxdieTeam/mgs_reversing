
#include "gcl.h"

void GCL_80020B2C(unsigned char *pScript)
{
	int	code;
	int value;
  
	do {
		pScript = GCL_GetNextValue_8002069C(pScript, &code, &value);
	} while (code != GCLCODE_NULL);
	return;
}
