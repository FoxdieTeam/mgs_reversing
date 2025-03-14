#include "motion.h"

#include "common.h"
#include "game.h"
#include "control.h"
#include "libgv/libgv.h"

short word_8009D69C[15][64] = {
    {0x01EE, 0x0428, 0x056E, 0x0666, 0x072E, 0x07DA, 0x086E, 0x08F4, 0x096C, 0x09DA, 0x0A3E, 0x0A9A, 0x0AEE, 0x0B3E, 0x0B88, 0x0BCE, 0x0C0E, 0x0C4C, 0x0C86, 0x0CBC, 0x0CEF, 0x0D20, 0x0D4E, 0x0D78, 0x0DA2, 0x0DC8, 0x0DEE, 0x0E10, 0x0E32, 0x0E52, 0x0E6F, 0x0E8C, 0x0EA6, 0x0EC0, 0x0ED8, 0x0EEF, 0x0F04, 0x0F19, 0x0F2C, 0x0F3F, 0x0F50, 0x0F60, 0x0F6F, 0x0F7E, 0x0F8B, 0x0F98, 0x0FA3, 0x0FAE, 0x0FB8, 0x0FC2, 0x0FCA, 0x0FD2, 0x0FD9, 0x0FE0, 0x0FE6, 0x0FEB, 0x0FEF, 0x0FF3, 0x0FF7, 0x0FFA, 0x0FFC, 0x0FFE, 0x0FFF, 0x0FFF},
    {0x00B2, 0x0288, 0x03C6, 0x04C0, 0x0590, 0x0644, 0x06E4, 0x0774, 0x07F6, 0x086C, 0x08DA, 0x0940, 0x09A0, 0x09F8, 0x0A4C, 0x0A9A, 0x0AE2, 0x0B28, 0x0B6A, 0x0BA8, 0x0BE4, 0x0C1C, 0x0C52, 0x0C86, 0x0CB6, 0x0CE4, 0x0D10, 0x0D3A, 0x0D62, 0x0D8A, 0x0DAE, 0x0DD1, 0x0DF2, 0x0E13, 0x0E32, 0x0E4F, 0x0E6B, 0x0E86, 0x0E9F, 0x0EB8, 0x0ECF, 0x0EE5, 0x0EFA, 0x0F0E, 0x0F22, 0x0F34, 0x0F46, 0x0F56, 0x0F66, 0x0F75, 0x0F83, 0x0F90, 0x0F9D, 0x0FA9, 0x0FB4, 0x0FBE, 0x0FC8, 0x0FD1, 0x0FDA, 0x0FE2, 0x0FE9, 0x0FF0, 0x0FF6, 0x0FFC},
    {0x005C, 0x0196, 0x0298, 0x0374, 0x0434, 0x04E0, 0x057C, 0x060C, 0x0690, 0x070A, 0x077C, 0x07E6, 0x084A, 0x08AA, 0x0902, 0x0958, 0x09A8, 0x09F4, 0x0A3E, 0x0A84, 0x0AC6, 0x0B06, 0x0B42, 0x0B7C, 0x0BB4, 0x0BEA, 0x0C1D, 0x0C4E, 0x0C7E, 0x0CAC, 0x0CD7, 0x0D02, 0x0D2A, 0x0D51, 0x0D76, 0x0D9A, 0x0DBE, 0x0DDF, 0x0E00, 0x0E1E, 0x0E3C, 0x0E59, 0x0E75, 0x0E90, 0x0EAA, 0x0EC2, 0x0EDA, 0x0EF1, 0x0F07, 0x0F1C, 0x0F30, 0x0F44, 0x0F57, 0x0F69, 0x0F7A, 0x0F8B, 0x0F9A, 0x0FAA, 0x0FB8, 0x0FC6, 0x0FD3, 0x0FE0, 0x0FEC, 0x0FF7},
    {0x0038, 0x0110, 0x01D2, 0x0284, 0x0326, 0x03BE, 0x044C, 0x04D0, 0x054C, 0x05C2, 0x0632, 0x069C, 0x0700, 0x0760, 0x07BC, 0x0814, 0x0868, 0x08BA, 0x0906, 0x0952, 0x099A, 0x09DE, 0x0A20, 0x0A62, 0x0AA0, 0x0ADC, 0x0B14, 0x0B4C, 0x0B83, 0x0BB8, 0x0BEA, 0x0C1B, 0x0C4A, 0x0C78, 0x0CA6, 0x0CD0, 0x0CFA, 0x0D23, 0x0D4A, 0x0D71, 0x0D96, 0x0DBA, 0x0DDD, 0x0DFE, 0x0E20, 0x0E40, 0x0E5E, 0x0E7C, 0x0E9A, 0x0EB6, 0x0ED1, 0x0EEC, 0x0F06, 0x0F1F, 0x0F37, 0x0F4E, 0x0F65, 0x0F7C, 0x0F91, 0x0FA6, 0x0FBA, 0x0FCD, 0x0FE0, 0x0FF2},
    {0x0026, 0x00C0, 0x0152, 0x01DC, 0x0260, 0x02DE, 0x0356, 0x03CA, 0x043A, 0x04A4, 0x050C, 0x056E, 0x05CE, 0x062C, 0x0684, 0x06DC, 0x0730, 0x0780, 0x07D0, 0x081C, 0x0866, 0x08AE, 0x08F6, 0x093A, 0x097C, 0x09BC, 0x09FC, 0x0A3A, 0x0A74, 0x0AAF, 0x0AE8, 0x0B20, 0x0B56, 0x0B8A, 0x0BBE, 0x0BF0, 0x0C20, 0x0C50, 0x0C7F, 0x0CAC, 0x0CD9, 0x0D04, 0x0D2F, 0x0D58, 0x0D81, 0x0DA8, 0x0DD0, 0x0DF6, 0x0E1A, 0x0E3E, 0x0E62, 0x0E84, 0x0EA6, 0x0EC8, 0x0EE8, 0x0F08, 0x0F26, 0x0F44, 0x0F62, 0x0F7F, 0x0F9B, 0x0FB6, 0x0FD2, 0x0FEC},
    {0x001C, 0x008C, 0x00FA, 0x0166, 0x01CE, 0x0234, 0x0298, 0x02F8, 0x0358, 0x03B4, 0x0410, 0x0468, 0x04BE, 0x0514, 0x0568, 0x05B8, 0x0608, 0x0656, 0x06A4, 0x06EE, 0x0738, 0x0782, 0x07C8, 0x080E, 0x0852, 0x0896, 0x08D8, 0x0918, 0x0958, 0x0996, 0x09D4, 0x0A10, 0x0A4C, 0x0A86, 0x0AC0, 0x0AF8, 0x0B2F, 0x0B66, 0x0B9C, 0x0BD0, 0x0C04, 0x0C36, 0x0C69, 0x0C9A, 0x0CCB, 0x0CFB, 0x0D2A, 0x0D58, 0x0D86, 0x0DB3, 0x0DE0, 0x0E0A, 0x0E36, 0x0E60, 0x0E8A, 0x0EB2, 0x0EDA, 0x0F02, 0x0F2A, 0x0F50, 0x0F76, 0x0F9C, 0x0FC0, 0x0FE4},
    {0x0014, 0x0068, 0x00BC, 0x0110, 0x0162, 0x01B2, 0x0204, 0x0252, 0x02A2, 0x02F0, 0x033C, 0x038A, 0x03D4, 0x0420, 0x046A, 0x04B4, 0x04FC, 0x0544, 0x058C, 0x05D2, 0x0618, 0x065E, 0x06A4, 0x06E8, 0x072A, 0x076E, 0x07B0, 0x07F2, 0x0832, 0x0874, 0x08B4, 0x08F2, 0x0932, 0x0970, 0x09AE, 0x09EC, 0x0A28, 0x0A64, 0x0AA0, 0x0ADA, 0x0B16, 0x0B50, 0x0B8A, 0x0BC2, 0x0BFA, 0x0C34, 0x0C6A, 0x0CA2, 0x0CD8, 0x0D10, 0x0D46, 0x0D7A, 0x0DB0, 0x0DE4, 0x0E18, 0x0E4C, 0x0E80, 0x0EB2, 0x0EE4, 0x0F16, 0x0F48, 0x0F7A, 0x0FAA, 0x0FDB},
    {0x000F, 0x004F, 0x008F, 0x00CF, 0x010F, 0x014F, 0x018F, 0x01CF, 0x020F, 0x024F, 0x028F, 0x02CF, 0x030F, 0x034F, 0x038F, 0x03CF, 0x040F, 0x044F, 0x048F, 0x04CF, 0x050F, 0x054F, 0x058F, 0x05CF, 0x060F, 0x064F, 0x068F, 0x06CF, 0x070F, 0x074F, 0x078F, 0x07CF, 0x080F, 0x084F, 0x088F, 0x08CF, 0x090F, 0x094F, 0x098F, 0x09CF, 0x0A0F, 0x0A4F, 0x0A8F, 0x0ACF, 0x0B0F, 0x0B4F, 0x0B8F, 0x0BCF, 0x0C0F, 0x0C4F, 0x0C8F, 0x0CCF, 0x0D0F, 0x0D4F, 0x0D8F, 0x0DCF, 0x0E0F, 0x0E4F, 0x0E8F, 0x0ECF, 0x0F0F, 0x0F4F, 0x0F8F, 0x0FCF},
    {0x000C, 0x003C, 0x006C, 0x009E, 0x00CE, 0x0100, 0x0132, 0x0166, 0x0198, 0x01CC, 0x0200, 0x0234, 0x0269, 0x029E, 0x02D4, 0x030A, 0x0340, 0x0378, 0x03B0, 0x03E8, 0x0420, 0x0458, 0x0492, 0x04CC, 0x0506, 0x0540, 0x057C, 0x05B8, 0x05F4, 0x0632, 0x066F, 0x06AE, 0x06EC, 0x072A, 0x076A, 0x07AA, 0x07EC, 0x082C, 0x086E, 0x08B2, 0x08F4, 0x0938, 0x097E, 0x09C2, 0x0A08, 0x0A4E, 0x0A96, 0x0ADE, 0x0B26, 0x0B70, 0x0BB8, 0x0C04, 0x0C4E, 0x0C9A, 0x0CE8, 0x0D36, 0x0D84, 0x0DD2, 0x0E22, 0x0E74, 0x0EC6, 0x0F18, 0x0F6C, 0x0FC0},
    {0x0008, 0x002C, 0x0050, 0x0076, 0x009C, 0x00C2, 0x00E8, 0x0110, 0x0138, 0x0160, 0x018A, 0x01B4, 0x01DE, 0x020A, 0x0235, 0x0262, 0x028F, 0x02BD, 0x02EC, 0x031C, 0x034C, 0x037C, 0x03AE, 0x03E0, 0x0414, 0x0448, 0x047E, 0x04B4, 0x04EA, 0x0522, 0x055C, 0x0596, 0x05D0, 0x060C, 0x0648, 0x0686, 0x06C6, 0x0706, 0x0748, 0x078A, 0x07CE, 0x0812, 0x085A, 0x08A0, 0x08EA, 0x0934, 0x0980, 0x09CE, 0x0A1E, 0x0A6E, 0x0AC0, 0x0B14, 0x0B6A, 0x0BC2, 0x0C1C, 0x0C78, 0x0CD6, 0x0D36, 0x0D98, 0x0DFC, 0x0E64, 0x0ECE, 0x0F3A, 0x0FAA},
    {0x0006, 0x0020, 0x003A, 0x0056, 0x0072, 0x008E, 0x00AB, 0x00C9, 0x00E8, 0x0107, 0x0127, 0x0148, 0x0169, 0x018B, 0x01AE, 0x01D2, 0x01F6, 0x021C, 0x0242, 0x026A, 0x0292, 0x02BA, 0x02E4, 0x0310, 0x033C, 0x0368, 0x0396, 0x03C6, 0x03F6, 0x0428, 0x045A, 0x048E, 0x04C4, 0x04FA, 0x0532, 0x056C, 0x05A6, 0x05E4, 0x0622, 0x0662, 0x06A2, 0x06E6, 0x072C, 0x0772, 0x07BC, 0x0808, 0x0856, 0x08A6, 0x08F8, 0x094E, 0x09A6, 0x0A00, 0x0A5E, 0x0AC0, 0x0B26, 0x0B8E, 0x0BFC, 0x0C6C, 0x0CE4, 0x0D5E, 0x0DE0, 0x0E66, 0x0EF4, 0x0F8A},
    {0x0004, 0x0016, 0x0028, 0x003B, 0x004F, 0x0064, 0x0078, 0x008E, 0x00A4, 0x00BC, 0x00D4, 0x00EC, 0x0106, 0x0120, 0x013B, 0x0157, 0x0174, 0x0191, 0x01B0, 0x01CF, 0x01EF, 0x0210, 0x0233, 0x0256, 0x027B, 0x02A0, 0x02C8, 0x02F0, 0x0318, 0x0344, 0x036F, 0x039C, 0x03CC, 0x03FC, 0x042E, 0x0460, 0x0496, 0x04CD, 0x0506, 0x0540, 0x057E, 0x05BC, 0x05FE, 0x0642, 0x0688, 0x06D2, 0x071E, 0x076C, 0x07C0, 0x0816, 0x086E, 0x08CC, 0x0930, 0x0996, 0x0A04, 0x0A76, 0x0AEE, 0x0B70, 0x0BF8, 0x0C8A, 0x0D28, 0x0DD2, 0x0E8A, 0x0F56},
    {0x0002, 0x000D, 0x0019, 0x0025, 0x0032, 0x0040, 0x004E, 0x005C, 0x006C, 0x007C, 0x008D, 0x009F, 0x00B1, 0x00C4, 0x00D8, 0x00ED, 0x0102, 0x0119, 0x0130, 0x0148, 0x0162, 0x017C, 0x0198, 0x01B4, 0x01D1, 0x01F0, 0x020F, 0x0230, 0x0252, 0x0276, 0x029A, 0x02C1, 0x02E8, 0x0312, 0x033D, 0x036A, 0x0398, 0x03C8, 0x03FA, 0x042F, 0x0466, 0x049E, 0x04DA, 0x0518, 0x055A, 0x059E, 0x05E4, 0x062E, 0x067E, 0x06D0, 0x0728, 0x0784, 0x07E4, 0x084C, 0x08BA, 0x0930, 0x09B0, 0x0A38, 0x0ACE, 0x0B72, 0x0C28, 0x0CF4, 0x0DE2, 0x0EFC},
    {0x0001, 0x0006, 0x000C, 0x0012, 0x0019, 0x0021, 0x0029, 0x0032, 0x003C, 0x0046, 0x0050, 0x005C, 0x0068, 0x0075, 0x0083, 0x0092, 0x00A1, 0x00B1, 0x00C2, 0x00D4, 0x00E6, 0x00FA, 0x010F, 0x0124, 0x013B, 0x0153, 0x016C, 0x0186, 0x01A2, 0x01BE, 0x01DC, 0x01FC, 0x021C, 0x023E, 0x0262, 0x0288, 0x02B0, 0x02D8, 0x0304, 0x0331, 0x0360, 0x0392, 0x03C6, 0x03FE, 0x0438, 0x0474, 0x04B4, 0x04F8, 0x0540, 0x058C, 0x05DC, 0x0632, 0x068E, 0x06F0, 0x075A, 0x07CC, 0x0848, 0x08D0, 0x0968, 0x0A10, 0x0AD2, 0x0BB4, 0x0CCC, 0x0E42},
    {0x0000, 0x0000, 0x0001, 0x0002, 0x0004, 0x0007, 0x000A, 0x000D, 0x0012, 0x0017, 0x001C, 0x0022, 0x0029, 0x0031, 0x0039, 0x0042, 0x004C, 0x0056, 0x0061, 0x006D, 0x007A, 0x0088, 0x0097, 0x00A6, 0x00B7, 0x00C9, 0x00DC, 0x00F0, 0x0105, 0x011B, 0x0132, 0x014B, 0x0166, 0x0181, 0x019E, 0x01BC, 0x01DD, 0x01FF, 0x0223, 0x0249, 0x0271, 0x029B, 0x02C8, 0x02F6, 0x0328, 0x035D, 0x0394, 0x03D0, 0x0410, 0x0452, 0x049A, 0x04E6, 0x0538, 0x0592, 0x05F2, 0x065A, 0x06CC, 0x074A, 0x07D8, 0x0878, 0x0930, 0x0A0C, 0x0B24, 0x0CB8}
};

int dword_8009DE1C[] =
{
    65536 / 1,
    65536 / 1,
    65536 / 2,
    65536 / 3,
    65536 / 4,
    65536 / 5,
    65536 / 6,
    65536 / 7,
    65536 / 8,
    65536 / 9,
    65536 / 10,
    65536 / 11,
    65536 / 12,
    65536 / 13,
    65536 / 14,
    65536 / 15,
};

short dword_8009DE5C[] =
{
    4096 / 1,
    4096 / 2,
    4096 / 3,
    4096 / 4,
    4096 / 5,
    4096 / 6,
    4096 / 7,
    4096 / 8,
    4096 / 9,
    4096 / 10,
    4096 / 11,
    4096 / 12,
    4096 / 13,
    4096 / 14,
    4096 / 15,
    4096 / 16,
};

MATRIX matrix_8009DE7C = {{{0, 0, 0}, {0, 0, 0}, {0, 0, 0}}, {0, 0, 0}};
MATRIX matrix_8009DE9C = {{{0, 0, 0}, {0, 0, 0}, {0, 0, 0}}, {0, 0, 0}};

void InterpolateJoint(MOTION_SEGMENT *m_seg, SVECTOR *out);
void ApplyJointRotation(MOTION_CONTROL *m_ctrl, MOTION_INFO *m_info);
int  BeginAction(MOTION_CONTROL *m_ctrl, MOTION_INFO *m_info, int action);
int  BeginActionOffset(MOTION_CONTROL *m_ctrl, MOTION_INFO *m_info, int action, int frame);
void SkipToKeyframe(MOTION_SEGMENT *m_seg, int frame);
int  CorrectWaistRotation(SVECTOR *arg0, SVECTOR *arg1);
int  NextKeyframe(MOTION_CONTROL *m_ctrl, MOTION_INFO *m_info);
void InflateKeyframe(MOTION_SEGMENT *m_seg);

// maybe static
void ExtendVector(SVECTOR *vec)
{
    vec->vx = FP_Extend(vec->vx);
    vec->vy = FP_Extend(vec->vy);
    vec->vz = FP_Extend(vec->vz);
}

int GM_ConfigMotionControl(OBJECT *object, MOTION_CONTROL *m_ctrl, int name, MOTION_SEGMENT *m_segs1, MOTION_SEGMENT *m_segs2, CONTROL *control, SVECTOR *rots)
{
    m_ctrl->oar = GV_GetCache(GV_CacheID(name, 'o'));
    m_ctrl->height = &object->height;

    m_ctrl->info1.frames_left = 0;
    m_ctrl->info1.frame = 0;
    m_ctrl->info1.field_4 = 0;
    m_ctrl->info1.mask = 0;
    m_ctrl->info1.m_segs = m_segs1;
    m_ctrl->info1.action = 0;
    m_ctrl->info1.field_12 = 0;
    m_ctrl->info1.field_14 = 0;
    m_ctrl->info1.time = 0;

    m_ctrl->info2.frames_left = 0;
    m_ctrl->info2.frame = 0;
    m_ctrl->info2.field_4 = 0;
    m_ctrl->info2.mask = 0xffffffff;
    m_ctrl->info2.action = 0;
    m_ctrl->info2.field_12 = 0;
    m_ctrl->info2.field_14 = 0;
    m_ctrl->info2.time = 0;

    m_ctrl->interp = 0;
    m_ctrl->rots = rots;
    m_ctrl->rot = &control->rot;
    m_ctrl->step = &control->step;
    m_ctrl->info2.m_segs = m_segs2;

    object->objs->rots = rots;
    object->objs->waist_rot = &m_ctrl->waist_rot;
    object->m_ctrl = m_ctrl;

    return 0;
}

int GM_ConfigMotionAdjust(OBJECT *object, SVECTOR *adjust)
{
    object->objs->adjust = adjust;
    return 0;
}

void GM_ConfigAction(MOTION_CONTROL *m_ctrl, int action, int frame)
{
    MATRIX       saved;
    MOTION_INFO *m_info;

    ReadRotMatrix(&saved);

    m_info = &m_ctrl->info1;
    if (m_info->frames_left != 0)
    {
        ApplyJointRotation(m_ctrl, m_info);
    }

    if (frame == 0)
    {
        BeginAction(m_ctrl, m_info, action);
    }
    else
    {
        BeginActionOffset(m_ctrl, m_info, action, frame);
    }

    if (m_info->frames_left == 1)
    {
        m_info->field_14 = 2;
        m_info->action = action;
    }
    else
    {
        m_info->field_14 = 1;
        m_info->action = action;
    }

    SetRotMatrix(&saved);
}

void GM_ConfigActionOverride(MOTION_CONTROL *m_ctrl, int action, int frame)
{
    MATRIX       saved;
    MOTION_INFO *m_info;

    ReadRotMatrix(&saved);

    m_info = &m_ctrl->info2;
    if (m_info->frames_left != 0)
    {
        ApplyJointRotation(m_ctrl, m_info);
    }

    if (frame == 0)
    {
        BeginAction(m_ctrl, m_info, action);
    }
    else
    {
        BeginActionOffset(m_ctrl, m_info, action, frame);
    }

    if (m_info->frames_left == 1)
    {
        m_info->field_14 = 2;
        m_info->action = action;
    }
    else
    {
        m_info->field_14 = 1;
        m_info->action = action;
    }

    SetRotMatrix(&saved);
}

STATIC int BeginAction( MOTION_CONTROL *m_ctrl, MOTION_INFO *m_info, int action )
{
    char            unused[16];
    MOTION_SEGMENT     *m_seg;
    int             n_joint;
    int             i;
    MOTION_TABLE   *table;
    int             n_frame;
    int             size;
    MOTION_ARCHIVE *archive;
    unsigned int    temp1, temp2;
    unsigned short  vec_size;
    char            channel_size;
    SVECTOR*        svec;

    n_joint = m_ctrl->oar->n_joint;
    size = n_joint + 2;
    m_seg = m_info->m_segs;

    table = &m_ctrl->oar->table[ size * action ];

    n_frame = table[ 0 ];
    table++; //progresses it to the start of the archive offsets

    m_info->frame = 0;
    m_info->field_4 = 0;
    m_info->frames_left = n_frame;

    archive = &m_ctrl->oar->archive[ table[ 0 ] ]; //start of bitstream vectors
    table++; //progresses to the next offset

    m_seg->base.vy = archive[ 0 ];
    archive++; //progress to next vector

    temp1 = archive[ 0 ] + ( archive [ 1 ] << 16 );

    archive++; //progress to next vector

    m_seg->bit_offset = 0;
    m_seg->stream = archive;

    temp2 = temp1 & 0xF;
    temp1 &= 0xFFFF;
    temp1 >>= 4;

    m_seg->delta.vx = temp2;

    temp2 = temp1 & 0xF;
    temp1 >>= 4;
    temp1 &= 0xF;

    m_seg->delta.vy = temp2;
    m_seg->delta.vz = temp1;

    m_seg++;

    for ( i = 0; i < n_joint; i++, m_seg++, table++ )
    {
        archive = &m_ctrl->oar->archive[ table[ 0 ] ];

        vec_size = archive [ 0 ];

        m_seg->stream = archive;

        vec_size &= 0xFFF;

        m_seg->bit_offset = 12;

        channel_size = vec_size & 0xF;
        vec_size >>= 4;
        m_seg->x_size = channel_size;

        channel_size = vec_size & 0xF;
        vec_size >>= 4;
        m_seg->y_size = channel_size;

        channel_size = vec_size & 0xF;
        vec_size >>= 4;
        m_seg->z_size = channel_size;

        InflateKeyframe( m_seg );

        if ( i == 0 )
        {
            CorrectWaistRotation( &m_seg->base, &m_seg->delta );
        }
        else
        {
            svec = &m_seg->delta;
            svec->vx = FP_Subtract_2( svec->vx, m_seg->base.vx );
            svec->vy = FP_Subtract_2( svec->vy, m_seg->base.vy );
            svec->vz = FP_Subtract_2( svec->vz, m_seg->base.vz );
        }
    }

    return 0;
}

STATIC void InflateKeyframe(MOTION_SEGMENT *m_seg)
{
    unsigned int    val, val2;
    unsigned int    shiftLeft, field_1C;
    char            shiftRight, nextShiftRight;
    unsigned short *field_14;

    shiftRight = m_seg->bit_offset;
    field_14 = m_seg->stream;

    nextShiftRight = shiftRight + 8;
    val = (unsigned int)(field_14[0] + (field_14[1] << 16)) >> shiftRight;
    field_1C = val & 0xFF;
    shiftRight = nextShiftRight;
    if (nextShiftRight & 0x10)
    {
        field_14++;
        shiftRight = nextShiftRight & 0xF;
    }
    val2 = val & 0xF;
    field_1C >>= 4;
    m_seg->field_1A = val2;
    m_seg->field_1C = field_1C & 0xF;
    m_seg->field_18 = val2 - 1;

    shiftLeft = m_seg->x_size;
    m_seg->interp = dword_8009DE1C[m_seg->field_1A];
    val = (unsigned int)(field_14[0] + (field_14[1] << 16)) >> shiftRight & ((1 << shiftLeft) - 1);
    if (val & 1 << (shiftLeft - 1))
    {
        val |= ~((1 << shiftLeft) - 1);
    }
    m_seg->delta.vx = val;
    nextShiftRight = shiftRight + shiftLeft;
    shiftRight = nextShiftRight;
    if (nextShiftRight & 0x10)
    {
        field_14++;
        shiftRight = nextShiftRight & 0xF;
    }

    shiftLeft = m_seg->y_size;
    val = (unsigned int)(field_14[0] + (field_14[1] << 16)) >> shiftRight & ((1 << shiftLeft) - 1);
    if (val & 1 << (shiftLeft - 1))
    {
        val |= ~((1 << shiftLeft) - 1);
    }
    m_seg->delta.vy = val;
    nextShiftRight = shiftRight + shiftLeft;
    shiftRight = nextShiftRight;
    if (nextShiftRight & 0x10)
    {
        field_14++;
        shiftRight = nextShiftRight & 0xF;
    }

    shiftLeft = m_seg->z_size;
    val = (unsigned int)(field_14[0] + (field_14[1] << 16)) >> shiftRight & ((1 << shiftLeft) - 1);
    if (val & 1 << (shiftLeft - 1))
    {
        val |= ~((1 << shiftLeft) - 1);
    }
    m_seg->delta.vz = val;
    nextShiftRight = shiftRight + shiftLeft;
    shiftRight = nextShiftRight;
    if (nextShiftRight & 0x10)
    {
        field_14++;
        shiftRight = nextShiftRight & 0xF;
    }
    m_seg->bit_offset = shiftRight;
    m_seg->stream = field_14;
}

int GM_PlayAction(MOTION_CONTROL *m_ctrl)
{
    MATRIX       mtx;
    MOTION_INFO *m_info;
    int          time;

    ReadRotMatrix(&mtx);

    m_ctrl->step->vx = 0;
    m_ctrl->step->vz = 0;

    m_info = &m_ctrl->info1;
    if (m_info->field_14 != 0)
    {
        time = NextKeyframe(m_ctrl, m_info);

        if (time == -1)
        {
            if (m_info->field_14 & 1)
            {
                BeginAction(m_ctrl, m_info, m_info->action);
            }

            if (m_info->field_14 & 2)
            {
                if (m_ctrl->interp != 0)
                {
                    BeginAction(m_ctrl, m_info, m_info->action);
                }
                else
                {
                    m_info->field_14 = 0;
                }
            }

            time = 0;
        }

        m_info->time = time;
    }

    m_info = &m_ctrl->info2;
    if (m_info->field_14 != 0)
    {
        time = NextKeyframe(m_ctrl, m_info);

        if (time == -1)
        {
            if (m_info->field_14 & 1)
            {
                BeginAction(m_ctrl, m_info, m_info->action);
            }

            if (m_info->field_14 & 2)
            {
                if (m_ctrl->interp != 0)
                {
                    BeginAction(m_ctrl, m_info, m_info->action);
                }
                else
                {
                    m_info->field_14 = 0;

                    if (m_ctrl->info1.field_14 == 0)
                    {
                        m_ctrl->info1.field_14 = 2;
                    }
                }
            }

            time = 0;
        }

        m_info->time = time;
    }

    SetRotMatrix(&mtx);
    return time;
}

//TODO: move below elsewhere
#define Shift_Op(v, a, b) \
{                         \
    v = a;                \
    if ( a & 0x10 )       \
    {                     \
        b++;              \
        v = a & 0xF;      \
    }                     \
}

#define Mask_Op(sv, v, y, s)    \
{                               \
    v >>= s;                    \
                                \
                                \
    v &= ((1 << y) - 1);        \
                                \
    if (v & (1 << (y - 1)))     \
    {                           \
        v |= ~((1 << y) - 1);   \
    }                           \
                                \
    sv = v;                     \
}
// TODO: better name needed
#define FP_Subtract2(v, a, b) \
{                            \
    (v) = (a) - (b);         \
                             \
    if ((v) >= 0)            \
    {                        \
        (v) &= 0xFFF;        \
                             \
        if ((v) >= 2048)     \
        {                    \
            (v) -= 4096;     \
        }                    \
    }                        \
    else                     \
    {                        \
        (v) |= 0xF000;       \
                             \
        if ((v) < -2048)     \
        {                    \
            (v) += 4096;     \
        }                    \
    }                        \
                             \
    (a) = (v);               \
}

static inline void FP_Subtract3( SVECTOR *svec, SVECTOR *svec2 )
{
    int value;
    FP_Subtract2(value, svec2->vx, svec->vx);
    FP_Subtract2(value, svec2->vy, svec->vy);
    FP_Subtract2(value, svec2->vz, svec->vz);
}

static inline unsigned int extract_archive( MOTION_ARCHIVE *archive )
{
    return archive[0] + (archive[1] << 16);
}

STATIC int NextKeyframe(MOTION_CONTROL *m_ctrl, MOTION_INFO *m_info)
{
    MATRIX  rotation;
    SVECTOR vec;

    MOTION_SEGMENT *m_seg;
    int         record_size;
    int         ret;
    int         delta;

    SVECTOR *rots;

    unsigned int vx, vy, vz;

    MOTION_ARCHIVE *archive;

    int i;

    int interp;

    int flags;
    unsigned char shift;

    SVECTOR *b;

    int res;
    int t0;
    char shift_temp;

    m_seg  = m_info->m_segs;
    record_size = m_ctrl->oar->n_joint;

    ret = 0;

    if (m_info->frames_left == 0)
    {
        return -1;
    }

    m_info->frame++;

    delta = dword_8009DE5C[m_ctrl->interp];
    matrix_8009DE7C.m[0][0] = delta;
    matrix_8009DE7C.m[1][1] = delta;
    matrix_8009DE7C.m[2][2] = delta;

    gte_SetLightMatrix(&matrix_8009DE7C);

    if (!(m_info->mask & 0x1))
    {
        if (m_info->field_4 == 0)
        {
            shift = m_seg->bit_offset;
            archive = m_seg->stream;

            RotMatrix(m_ctrl->rot, &rotation);
            gte_SetRotMatrix(&rotation);

            // vx
            vx = extract_archive(archive);
            Mask_Op(res, vx, m_seg->delta.vx, shift);

            shift_temp = shift + m_seg->delta.vx;
            Shift_Op(shift, shift_temp, archive);

            vec.vx = res;

            // vy
            vy = extract_archive(archive);
            Mask_Op(res, vy, m_seg->delta.vy, shift);

            shift_temp = shift + m_seg->delta.vy;
            Shift_Op(shift, shift_temp, archive);

            t0 = res + m_seg->base.vy;
            vec.vy = 0;

            // vz
            vz = extract_archive(archive);
            Mask_Op(res, vz, m_seg->delta.vz, shift);

            shift_temp = shift + m_seg->delta.vz;
            Shift_Op(shift, shift_temp, archive);

            vec.vz = res;

            gte_ldv0(&vec);
            gte_rtv0();
            res = m_ctrl->step->vy;
            gte_stsv(m_ctrl->step);
            m_ctrl->step->vy = res;

            m_seg->bit_offset = shift;
            m_seg->stream = archive;

            interp = (t0 - *m_ctrl->height) * delta;
            *m_ctrl->height += interp / 4096;
        }
        else if (m_info->field_4 == 1)
        {
            m_ctrl->step->vx = 0;
            m_ctrl->step->vz = 0;
        }
    }

    if (m_info->frames_left == 1)
    {
        ret = -1;
    }

    flags = m_info->mask;
    rots = m_ctrl->rots;

    m_seg++;

    if (!(flags & 0x2))
    {

        b = &m_ctrl->waist_rot;

        InterpolateJoint(m_seg, (SVECTOR *)&rotation.m[0][0]);

        rotation.m[0][0] = (rotation.m[0][0] + m_seg->base.vx) & 0xFFF;
        rotation.m[0][1] = (rotation.m[0][1] + m_seg->base.vy) & 0xFFF;
        rotation.m[0][2] = (rotation.m[0][2] + m_seg->base.vz) & 0xFFF;

        FP_Subtract3(b, (SVECTOR*)&rotation.m[0][0]);

        gte_ldv0(&rotation);
        gte_llv0();
        gte_stsv(&rotation);

        b->vx = (b->vx + rotation.m[0][0]) & 0xFFF;
        b->vy = (b->vy + rotation.m[0][1]) & 0xFFF;
        b->vz = (b->vz + rotation.m[0][2]) & 0xFFF;
    }

    for (i = 0; i < record_size; i++, m_seg++, rots++, flags >>= 1)
    {
        InterpolateJoint(m_seg, (SVECTOR *)&rotation.m[1][1]);

        rotation.m[1][1] = (rotation.m[1][1] + m_seg->base.vx) & 0xFFF;
        rotation.m[1][2] = (rotation.m[1][2] + m_seg->base.vy) & 0xFFF;
        rotation.m[2][0] = (rotation.m[2][0] + m_seg->base.vz) & 0xFFF;

        if (--m_seg->field_18 < 0)
        {
            m_seg->base = *(SVECTOR *)&rotation.m[1][1];

            if (ret == 0)
            {
                InflateKeyframe(m_seg);
                FP_Subtract3(&m_seg->base, (SVECTOR*)&m_seg->delta);
            }
        }

        if (!(flags & 0x1))
        {
            if (i == 0)
            {
                CorrectWaistRotation(rots, (SVECTOR *)&rotation.m[1][1]);
            }
            else
            {
                FP_Subtract3(rots, (SVECTOR*)&rotation.m[1][1]);
            }

            gte_ldv0(&rotation.m[1][1]);
            gte_llv0();
            gte_stsv(&rotation.m[1][1]);

            rots->vx = (rots->vx + rotation.m[1][1]) & 0xFFF;
            rots->vy = (rots->vy + rotation.m[1][2]) & 0xFFF;
            rots->vz = (rots->vz + rotation.m[2][0]) & 0xFFF;
        }
    }

    if (--m_info->frames_left == 1)
    {
        ret = 1;
    }

    return ret;
}

STATIC void InterpolateJoint(MOTION_SEGMENT *m_seg, SVECTOR *out)
{
    int interp;

    interp = m_seg->interp * (m_seg->field_1A - m_seg->field_18);
    interp >>= 10;

    if (interp != 64)
    {
        interp = word_8009D69C[m_seg->field_1C][interp];
    }
    else
    {
        interp = 4096;
    }

    matrix_8009DE9C.m[0][0] = interp;
    matrix_8009DE9C.m[1][1] = interp;
    matrix_8009DE9C.m[2][2] = interp;

    gte_SetRotMatrix(&matrix_8009DE9C);
    gte_ldv0(&m_seg->delta);
    gte_rtv0();
    gte_stsv(out);
}

// maybe static
void GM_FixMotion_80035FFC(MOTION_CONTROL *m_ctrl)
{
    ApplyJointRotation(m_ctrl, &m_ctrl->info1);
}

// maybe static
void GM_FixMotion2_8003601C(MOTION_CONTROL *m_ctrl)
{
    ApplyJointRotation(m_ctrl, &m_ctrl->info2);
}

STATIC void ApplyJointRotation(MOTION_CONTROL *m_ctrl, MOTION_INFO *m_info)
{
    SVECTOR         delta;
    MOTION_SEGMENT *m_seg;
    int             n_joints;
    int             i;

    m_seg = m_info->m_segs;
    m_seg++;

    n_joints = m_ctrl->oar->n_joint;

    m_info->frames_left = 0;
    m_info->field_4 = 1;

    for (i = 0; i < n_joints; i++, m_seg++)
    {
        InterpolateJoint(m_seg, &delta);
        m_seg->base.vx += delta.vx;
        m_seg->base.vy += delta.vy;
        m_seg->base.vz += delta.vz;
    }
}

STATIC int BeginActionOffset(MOTION_CONTROL *m_ctrl, MOTION_INFO *m_info, int action, int frame)
{
    char            unused[8];
    int             i;
    MOTION_SEGMENT     *m_seg;
    int             numRecords;
    unsigned int    v0, v1;
    MOTION_TABLE   *table;
    MOTION_ARCHIVE *archive;
    unsigned int temp3, temp6;
    unsigned int temp4;
    int temp5;
    unsigned short test;

    unsigned int a0, a1;

    numRecords = m_ctrl->oar->n_joint;
    m_seg = m_info->m_segs;

    table = &m_ctrl->oar->table[(numRecords + 2) * action];

    m_info->frames_left = table[0]; //number of frames
    m_info->frame = 0;

    temp5 = m_info->frames_left;
    test = m_info->frames_left;

    table++;

    if (frame >= temp5)
    {
        frame = temp5 - 1;
    }

    m_info->frames_left = test - frame;
    m_info->field_4 = 0;

    archive = &m_ctrl->oar->archive[table[0]];
    m_seg->base.vy = archive[0];
    archive++;

    v1 = archive[0] + (archive[1] << 16);
    a1 = v1 & 0xF;

    v1 &= 0xFFFF;
    v1 >>= 4;
    v0 = v1 & 0xF;

    a0 = a1 + v0;
    v1 >>= 4;
    v1 &= 0xF;

    a0 = a0 + v1;
    a0 = a0 & 0xFFFF;
    a0 = a0 * frame;

    table++;
    archive++;

    m_seg->delta.vx = a1;
    m_seg->delta.vy = v0;
    m_seg->delta.vz = v1;

    archive = &archive[(a0 / 16) & 0xF ];
    m_seg->bit_offset = a0 & 0xF;
    m_seg->stream = archive;
    m_seg++;

    for (i = 0; i < numRecords; i++, m_seg++, table++)
    {
        archive = &m_ctrl->oar->archive[table[0]];

        temp4 = (archive[0] + (archive[1] << 16)) & 0xFFF;
        temp6 = temp4;

        temp3 = temp4;
        temp4 = temp4 >> 4;
        temp6 = temp6 >> 8;

        m_seg->stream = archive;

        m_seg->bit_offset = 12;
        m_seg->x_size = temp3 & 0xF;
        m_seg->y_size = temp4 & 0xF;
        m_seg->z_size = temp6 & 0xF;

        m_seg->field_18 = -1;

        SkipToKeyframe(m_seg, frame);
        FP_Subtract3(&m_seg->base, &m_seg->delta);
    }

    return 0;
}

STATIC void SkipToKeyframe( MOTION_SEGMENT *m_seg, int frame )
{
    MOTION_ARCHIVE *archive;
    MOTION_ARCHIVE *archive2;
    char shift;
    char shift2;
    char shift_temp;
    int t5;
    char x, y, z;
    int vec_size;
    unsigned int a2;
    unsigned int vx, vy, vz;
    unsigned int vx2, vy2, vz2;
    unsigned int b;
    int temp2;
    int temp;

    shift = m_seg->bit_offset;
    archive = m_seg->stream;
    t5 = 0;

    if ((m_seg->field_18 + 1) > frame)
    {
        m_seg->field_18 -= frame;
        return;
    }

    frame -= m_seg->field_18 + 1;

    x = m_seg->x_size;
    y = m_seg->y_size;
    z = m_seg->z_size;
    vec_size = x + y + z;

    for (;;)
    {
        temp = (extract_archive(archive) >> shift);
        a2    = temp & 0xFF;
        temp2 = temp & 0xF;

        if (temp2 > frame)
        {
            z = shift + 8;
            break;
        }

        frame -= temp2;

        shift2 = shift;
        archive2 = archive;
        t5 = 1;

        shift_temp = (shift2 + 8) + vec_size;
        archive = &archive2[shift_temp / 16];
        shift = shift_temp & 0xF;
    }

    Shift_Op(shift, z, archive);
    b = (a2 >> 4);
    b = b & 0xF;

    m_seg->field_1A = temp2;
    do {} while(0);
    m_seg->field_1C = b;


    a2 = frame;

    m_seg->field_18 = (m_seg->field_1A - a2) - 1;
    m_seg->interp = dword_8009DE1C[m_seg->field_1A];

    vec_size = m_seg->x_size;
    vx = extract_archive(archive);
    Mask_Op(m_seg->delta.vx, vx, vec_size, shift);

    z = shift + vec_size;
    Shift_Op(shift, z, archive);

    vec_size = m_seg->y_size;
    vy = extract_archive(archive);
    Mask_Op(m_seg->delta.vy, vy, vec_size, shift);

    z = shift + vec_size;
    Shift_Op(shift, z, archive);

    vec_size = m_seg->z_size;
    vz = extract_archive(archive);
    Mask_Op(m_seg->delta.vz, vz, vec_size, shift);

    z = shift + vec_size;
    Shift_Op(shift, z, archive);

    m_seg->bit_offset = shift;
    m_seg->stream = archive;
    if (t5)
    {
        archive2 = &archive2[shift2 / 16];

        z = (shift2 & 0xF) + 8;
        Shift_Op(shift2, z, archive2);

        vec_size = m_seg->x_size;
        vx2 = extract_archive(archive2);
        Mask_Op(m_seg->delta.vx, vx2, vec_size, shift2);

        z = shift2 + vec_size;
        Shift_Op(shift2, z, archive2);

        vec_size = m_seg->y_size;
        vy2 = extract_archive(archive2);
        Mask_Op(m_seg->delta.vy, vy2, vec_size, shift2);

        z = shift2 + vec_size;
        Shift_Op(shift2, z, archive2);

        vec_size = m_seg->z_size;
        vz2 = extract_archive(archive2);
        Mask_Op(m_seg->delta.vz, vz2, vec_size, shift2);
    }
}

STATIC int CorrectWaistRotation(SVECTOR *arg0, SVECTOR *arg1)
{
    SVECTOR  vec1;
    SVECTOR  vec2;
    SVECTOR *vec1Ptr;
    int      var_a2; // side?
    int      diff;

    vec1 = *arg0;
    vec2 = *arg1;

    var_a2 = 0;

    if (arg0->vy > 0)
    {
        vec1.vy = (2048 - arg0->vy) & 0xFFF;
    }
    else
    {
        vec1.vy = (-2048 - arg0->vy) & 0xFFF;
    }

    if (arg0->vx > 0)
    {
        vec1.vx = (arg0->vx - 2048) & 0xFFF;
    }
    else
    {
        vec1.vx = (arg0->vx + 2048) & 0xFFF;
    }

    if (arg0->vz > 0)
    {
        vec1.vz = (arg0->vz - 2048) & 0xFFF;
    }
    else
    {
        vec1.vz = (arg0->vz + 2048) & 0xFFF;
    }

    // TODO: for some reason using FP_Extend2, FP_ExtendN inlines doesn't work here?
    diff = arg1->vx - arg0->vx;
    if (diff >= 0)
    {
        diff &= 0xfff;
        if (diff >= 2048)
        {
            diff -= 4096;
        }
        arg1->vx = diff;
    }
    else
    {
        diff |= 0xf000;
        if (diff < -2048)
        {
            diff += 4096;
        }
        arg1->vx = diff;
    }

    diff = arg1->vy - arg0->vy;
    if (diff >= 0)
    {
        arg1->vy = FP_Extend2(diff);
    }
    else
    {
        arg1->vy = FP_ExtendN(diff);
    }

    diff = arg1->vz - arg0->vz;
    if (diff >= 0)
    {
        arg1->vz = FP_Extend2(diff);
    }
    else
    {
        arg1->vz = FP_ExtendN(diff);
    }

    vec1Ptr = &vec1;

    diff = vec2.vx - vec1Ptr->vx;
    if (diff >= 0)
    {
        vec2.vx = FP_Extend2(diff);
    }
    else
    {
        vec2.vx = FP_ExtendN(diff);
    }

    diff = vec2.vy - vec1Ptr->vy;
    if (diff >= 0)
    {
        vec2.vy = FP_Extend2(diff);
    }
    else
    {
        vec2.vy = FP_ExtendN(diff);
    }

    diff = vec2.vz - vec1Ptr->vz;
    if (diff >= 0)
    {
        vec2.vz = FP_Extend2(diff);
    }
    else
    {
        vec2.vz = FP_ExtendN(diff);
    }

    if (abs(arg1->vx) <= abs(vec2.vx))
    {
        var_a2++;
    }
    else
    {
        var_a2--;
    }

    if (abs(arg1->vy) <= abs(vec2.vy))
    {
        var_a2++;
    }
    else
    {
        var_a2--;
    }

    if (abs(arg1->vz) <= abs(vec2.vz))
    {
        var_a2++;
    }
    else
    {
        var_a2--;
    }

    if (var_a2 < 0)
    {
        *arg0 = vec1;
        *arg1 = vec2;
        return -1;
    }

    return 0;
}
