void GV_NearExp8V_80026734(short *a, short *b, int count)
{
    int ca, cb;
    int diff;
    int mid;

    while (--count >= 0)
    {
        ca = *a;
        cb = *b;
        
        diff = cb - ca;
        
        if ((diff > -8) && (diff < 8))
        {
            mid = cb;
        }
        else
        {
            mid = ca + diff / 8;
        }

        *a++ = mid;
        b++;
    } 
}

