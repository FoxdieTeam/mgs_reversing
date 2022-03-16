#include <sys/types.h>
#include <libgte.h>

void DG_TransposeMatrix_8001EAD8(const MATRIX *in, MATRIX *out)
{
  short temp;
  
  temp = in->m[1][0];
  out->m[1][0] = in->m[0][1];
  out->m[0][1] = temp;

  temp = in->m[2][0];
  out->m[2][0] = in->m[0][2];
  out->m[0][2] = temp;

  temp = in->m[2][1];
  out->m[2][1] = in->m[1][2];
  out->m[1][2] = temp;

  if (in != out) {
    out->m[0][0] = in->m[0][0];
    out->m[1][1] = in->m[1][1];
    out->m[2][2] = in->m[2][2];
  }
}
