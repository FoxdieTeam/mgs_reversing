extern int  GM_PlayerStatus_800ABA50;

int GM_ClearPlayerStatusFlag_8004E2D4(int flag)
{
    GM_PlayerStatus_800ABA50 &= ~flag;
}
