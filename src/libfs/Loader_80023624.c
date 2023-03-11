#include "libfs.h"

int Loader_80023624(struct Loader_Record *pRec)
{
    int status;

    if (pRec->field_2C == 0)
    {
        return 1;
    }

    status = -1;

    while ((status < 0) && (pRec->field_2C <= (pRec->field_14 - 8)))
    {
        switch(pRec->field_2C[2])
        {
        case 'c':
            if (Loader_helper_8002336C(pRec, status))
            {
                return 0;
            }

            goto exit;

        case 's':
            pRec->field_2C += 8;
            break;

        case '\0':
            return 0;

        default:
            status = Loader_helper2_80023460(pRec, status);
            break;
        }
    }

exit:
    return 1;
}
