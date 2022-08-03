

int  CDBIOS_ReadSync_80022854(void);

void FS_LoadFileSync_80021F48(void)

{
    CDBIOS_ReadSync_80022854();
    return;
}
