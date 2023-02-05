void sub_80026734(short *dst, short *src, int count)
{
    int sVar1;
    int sVar2;
  
    for (count--; count >= 0; dst++, src++, count--)
    {
        sVar2 = -(*dst) + *src;

        if ((sVar2 > -8) && (sVar2 < 8))
        { 
            sVar1 = *src;
        }
        else
        {
            sVar1 = *dst + sVar2 / 8;
        }

        *dst = sVar1;
    }
}