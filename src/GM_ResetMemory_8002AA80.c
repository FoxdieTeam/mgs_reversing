

extern void GV_ResetMemory_80014CF0(void);
extern void DG_TextureCacheInit_8001F25C(void);
extern void GM_ResetChara_8002A8B0(void);

void GM_ResetMemory_8002AA80(void)
{
    DG_TextureCacheInit_8001F25C();
    GV_ResetMemory_80014CF0();
    GM_ResetChara_8002A8B0();
}
