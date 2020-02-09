unsigned int rand_8008E6B8(void);

unsigned int GV_RandU_80017090(unsigned int input)
{
    return (input - 1) & rand_8008E6B8();
}