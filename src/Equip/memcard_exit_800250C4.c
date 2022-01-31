#include "linker.h"
#include "memcard.h"

extern int gmem_card_system_inited_8009D524;

extern long gHardware_end_io_800B52C8;
extern long gHardware_end_write_800B52CC;
extern long gHardware_timeout_800B52D0;
extern long gHardware_new_device_800B52D4;

extern long gSoftware_end_io_800B52D8;
extern long gSoftware_end_write_800B52DC;
extern long gSoftware_timeout_800B52E0;
extern long gSoftware_new_device_800B52E4;

extern long gHwCard_do_op_800B52E8;
extern long gSwCard_do_op_800B52EC;
extern volatile long gSwCardLastOp_800B52F0;
extern volatile long gHwCardLastOp_800B52F4;

void StopCARD_80099130(void);
void EnterCriticalSection_8009952C(void);
void ExitCriticalSection_8009953C(void);
void CloseEvent_8009947C(int event);
long EnableEvent_800994AC(long);
long OpenEvent_8009946C(unsigned long desc, long spec, long mode, long (*func)());
extern void InitCARD_8009908C(long val);
extern long StartCARD_800990F8(void);
extern void bu_init_80098FEC(void);

extern struct mem_card gMemCards_800B52F8[2];

int memcard_check_80024A54(int idx);
int memcard_easy_format_test_800246C0(long hCard);
void memcard_reset_status_80024A3C();
void memcard_set_sw_hw_card_fns_8002469C();
void mts_set_vsync_task_800892B8(void);

long memcard_hwcard_end_io_800244FC();
long memcard_hwcard_end_write_80024524();
long memcard_hwcard_timeout_8002455C();
long memcard_hwcard_new_80024594();
long memcard_swcard_end_io_800245CC();
long memcard_swcard_end_write_800245F4();
long memcard_swcard_timeout_8002462C();
long memcard_swcard_new_80024664();

void memcard_init_80024E48()
{
    int idx; // $s1

    if (!gmem_card_system_inited_8009D524)
    {
        gmem_card_system_inited_8009D524 = !gmem_card_system_inited_8009D524;
        gHwCardLastOp_800B52F4 = 1;

        gSwCardLastOp_800B52F0 = 1;
        memcard_set_sw_hw_card_fns_8002469C();

        EnterCriticalSection_8009952C();

        gHardware_end_io_800B52C8 = OpenEvent_8009946C(0xF0000011, 4, 0x1000, memcard_hwcard_end_io_800244FC);            // f = hardware, 11 = HwCARD, 4 = EvSpIOE = end io
        gHardware_end_write_800B52CC = OpenEvent_8009946C(0xF0000011, 0x8000, 0x1000, memcard_hwcard_end_write_80024524); // EvSpIOEW = end write
        gHardware_timeout_800B52D0 = OpenEvent_8009946C(0xF0000011, 0x100, 0x1000, memcard_hwcard_timeout_8002455C);      // EvSpTIMOUT
        gHardware_new_device_800B52D4 = OpenEvent_8009946C(0xF0000011, 0x2000, 0x1000, memcard_hwcard_new_80024594);      // EvSpNEW new device

        gSoftware_end_io_800B52D8 = OpenEvent_8009946C(0xF4000001, 4, 0x1000, memcard_swcard_end_io_800245CC); // f4 = bios/software, 1 = SwCARD, EvSpIOE
        gSoftware_end_write_800B52DC = OpenEvent_8009946C(0xF4000001, 0x8000, 0x1000, memcard_swcard_end_write_800245F4);
        gSoftware_timeout_800B52E0 = OpenEvent_8009946C(0xF4000001, 0x100, 0x1000, memcard_swcard_timeout_8002462C);
        gSoftware_new_device_800B52E4 = OpenEvent_8009946C(0xF4000001, 0x2000, 0x1000, memcard_swcard_new_80024664);

        EnableEvent_800994AC(gHardware_end_io_800B52C8);
        EnableEvent_800994AC(gHardware_end_write_800B52CC);
        EnableEvent_800994AC(gHardware_timeout_800B52D0);
        EnableEvent_800994AC(gHardware_new_device_800B52D4);

        EnableEvent_800994AC(gSoftware_end_io_800B52D8);
        EnableEvent_800994AC(gSoftware_end_write_800B52DC);
        EnableEvent_800994AC(gSoftware_timeout_800B52E0);
        EnableEvent_800994AC(gSoftware_new_device_800B52E4);

        ExitCriticalSection_8009953C();

        idx = 0;

        InitCARD_8009908C(0);
        StartCARD_800990F8();
        bu_init_80098FEC();
        mts_set_vsync_task_800892B8();
        memcard_reset_status_80024A3C();

        for (idx = 0; idx < 2; idx++)
        {
            if (!memcard_check_80024A54(idx))
            {
                long v2 = memcard_easy_format_test_800246C0(idx);
                if (v2 == 5)
                {
                    gMemCards_800B52F8[idx].field_1_last_op = 5;
                }
                else if (v2 == 1)
                {
                    gMemCards_800B52F8[idx].field_1_last_op = 1;
                }
                else
                {
                    gMemCards_800B52F8[idx].field_1_last_op = 2;
                }
            }
            else
            {
                gMemCards_800B52F8[idx].field_1_last_op = 5;
            }
        }
    }
}

void memcard_exit_800250C4()
{
    StopCARD_80099130();
    EnterCriticalSection_8009952C();
    CloseEvent_8009947C(gHardware_end_io_800B52C8);
    CloseEvent_8009947C(gHardware_end_write_800B52CC);
    CloseEvent_8009947C(gHardware_timeout_800B52D0);
    CloseEvent_8009947C(gHardware_new_device_800B52D4);
    CloseEvent_8009947C(gSoftware_end_io_800B52D8);
    CloseEvent_8009947C(gSoftware_end_write_800B52DC);
    CloseEvent_8009947C(gSoftware_timeout_800B52E0);
    CloseEvent_8009947C(gSoftware_new_device_800B52E4);
    ExitCriticalSection_8009953C();
    gmem_card_system_inited_8009D524 = 0;
}
