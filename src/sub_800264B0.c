extern short word_8009D528[];

int sub_800264B0(int param_1, int param_2, int param_3)
{
    int var_a2;
    int var_v0;


    var_a2 = param_3;
    if (var_a2 > 15)
    { 
        var_a2 = 15;
    }

    var_a2 = word_8009D528[var_a2];  
    if (var_a2 == 0)
    {
        return param_2;
    }
    
    var_v0 = (param_2 - param_1) * var_a2;
    
    return (var_v0 / 4096) + param_1;
}