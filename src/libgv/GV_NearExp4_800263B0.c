int GV_NearExp4_800263B0(int a, int b)
{
    int diff = b - a;
    
    if ((diff > -4) && (diff < 4))
    {
        return b;
    }

    return a + diff / 4;
}
