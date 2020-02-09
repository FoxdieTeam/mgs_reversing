unsigned int rand_8008E6B8(void);

int GV_RandS_800170BC(int input)
{
    return (((input * 2) - 1) & rand_8008E6B8()) - input;
}