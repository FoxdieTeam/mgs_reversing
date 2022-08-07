int GV_NearExp2_80026384(int param_1, int param_2)
{
    if (((param_2 - param_1) + 1U) >= 3)
    {
        return param_1 + (param_2 - param_1) / 2;
    }
    return param_2;
}
