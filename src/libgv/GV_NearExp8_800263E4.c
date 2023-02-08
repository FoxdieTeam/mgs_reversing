int GV_NearExp8_800263E4(int a, int b)
{
    int diff = b - a;
    
    if ((diff > -8) && (diff < 8))
    {
        return b;
    }

    return a + diff / 8;
}
