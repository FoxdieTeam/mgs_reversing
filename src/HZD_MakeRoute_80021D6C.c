
#include "hzd.h"

extern void*    GV_Malloc_8001620C(int size);
extern void     GV_Free_80016230(void *ptr);
extern void     sub_80021C64(HZD_ZON *param_1, int param_2, int param_3, char *param_4);

void HZD_MakeRoute_80021D6C(HZD_HEADER *hzd, char *arg1)
{
    HZD_ZON *navmeshes;
    char    *buf, *argbuf;
    int     n_navmeshes;
    int     i, j, n;
  
    n_navmeshes = hzd->n_navmeshes;
    navmeshes = hzd->navmeshes;
    n = n_navmeshes;
    if (n_navmeshes > 0)
    {
        if ((buf = GV_Malloc_8001620C(n_navmeshes)))
        {
            argbuf = arg1;
            for (i = 0; i < n; i++)
            {
                sub_80021C64(navmeshes, n, i, buf);
                for (j = i + 1; j < n; j++)
                {
                    *argbuf++ = buf[j];
                }
            }
            GV_Free_80016230(buf);
        }
    }
}
