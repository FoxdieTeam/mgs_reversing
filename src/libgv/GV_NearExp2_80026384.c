int GV_NearExp2_80026384(int a, int b)
{
    int diff = b - a;
    
    if ((diff <= -2) || (diff >= 2))
    {
        return a + diff / 2;
    }
  
    return b;
}
