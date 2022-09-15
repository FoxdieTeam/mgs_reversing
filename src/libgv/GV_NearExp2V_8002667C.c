void GV_NearExp2V_8002667C(short *a, short *b, int count)
{
    int start;
    int end;
    int diff;
    int mid;

    while (--count >= 0)
    {
        start = *a;
        end = *b;

        diff = end - start;

        if (diff + 1 < 3u)
        {
            mid = end;
        }
        else
        {
            mid = start + diff / 2;
        }

        *a++ = mid;
        b++;
    }
}
