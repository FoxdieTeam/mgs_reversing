

extern void GV_FreeMemory2_80016078(unsigned int, void *);

void GV_DelayedFree_80016254(int arg0)
{
    GV_FreeMemory2_80016078(2, &arg0);
}
