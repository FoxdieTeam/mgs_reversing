void GV_NearExp4V_800266D4(short *a, short *b, int count)
{
    int ca, cb;
    int diff;
    int mid;

    while (--count >= 0)
    {
        ca = *a;
        cb = *b;
        
        diff = cb - ca;
        
        if ((diff > -4) && (diff < 4))
        {
            mid = cb;
        }
        else
        {
            mid = ca + diff / 4;
        }

        *a++ = mid;
        b++;
    } 
}

