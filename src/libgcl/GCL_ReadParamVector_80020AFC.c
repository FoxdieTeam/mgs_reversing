
#include "gcl.h"

void GCL_ReadParamVector_80020AFC(short *pOut3Words)
{
	GCL_ReadVector_80020A14(GCL_Get_Param_Result_80020AA4(), pOut3Words);
	return;
}
