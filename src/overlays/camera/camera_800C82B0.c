int camera_800C5308(int);
int camera_800C56F4();
extern int camera_dword_800D072C;
extern int camera_dword_800D0764;

void camera_800C82B0(int arg0, int arg1)
{
    camera_dword_800D0764 = 0;
    camera_dword_800D072C = arg0;
    camera_800C56F4();
    camera_800C5308(arg1);
}
 
