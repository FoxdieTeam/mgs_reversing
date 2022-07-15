

extern int  GM_PlayerStatus_800ABA50;

int GM_CheckPlayerStatusFlag_8004E29C(int arg0)
{
    return (GM_PlayerStatus_800ABA50 & arg0) != 0;
}
