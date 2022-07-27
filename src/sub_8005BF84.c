int sub_8005BF84(int a1, int a2, int a3, int a4)
{
	int iVar1;
	int iVar2;

	if (a3 < a2)
	{
		iVar1 = a3;
		a3 = a2;
		a2 = iVar1;
		iVar2 = 2 * a4;
	}
	else
	{
		iVar2 = 2 * a4;
		if (a2 == a3)
		{
			return 0;
		}
	}

	return *((unsigned char *) (((((a2 * ((iVar2 - a2) - 3)) / 2) + a3) + a1) - 1));
}
