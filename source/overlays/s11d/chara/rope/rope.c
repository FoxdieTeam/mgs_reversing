#include "rope.h"

void s11d_rope_800C4898(void *work, int value)
{
    int temp;
    unsigned short *ptr;
    unsigned short val;

    temp = *(int *)((char *)work + 0xf70);
    ptr = *(unsigned short **)((char *)work + 0x804);
    *(int *)((char *)work + 0xf7c) = value;
    temp |= 0x8000;
    *(int *)((char *)work + 0xf70) = temp;
    val = *ptr;
    val &= 0xFFEB;
    *ptr = val;
}

void s11d_rope_800C6240(void *work)
{
    int temp;
    int mask;

    *(unsigned short *)((char *)work + 0x6E) = 0x800;
    temp = *(int *)((char *)work + 0xF70);
    mask = -129;
    *(unsigned short *)((char *)work + 0x2C) = 0;
    *(unsigned short *)((char *)work + 0x28) = 0;
    *(int *)((char *)work + 0xF70) = temp & mask;
}

void s11d_rope_800C486C(void *work)
{
    int temp;
    unsigned short *ptr;
    unsigned short val;

    *(int *)((char *)work + 0xf7c) = 0x20;
    temp = *(int *)((char *)work + 0xf70);
    ptr = *(unsigned short **)((char *)work + 0x804);
    *(int *)((char *)work + 0xf70) = temp | 0x8000;
    val = *ptr;
    *ptr = val & 0xFFEB;
}

void s11d_rope_800C48C0(void *work)
{
    int temp;
    unsigned short *ptr;
    unsigned short val;
    int mask;

    mask = 0xFFFF7FFF;
    temp = *(int *)((char *)work + 0xf70);
    ptr = *(unsigned short **)((char *)work + 0x804);
    *(int *)((char *)work + 0xf70) = temp & mask;
    val = *ptr;
    *ptr = val | 0x14;
}

void s11d_rope_800C650C(void)
{
    func_8005D58C(&s11d_dword_800C32B4, 1);
    func_8005D58C(&s11d_dword_800C32B8, 2);
}

int s11d_rope_800C4F84(void *work)
{
    unsigned short *ptr;
    unsigned short flags;
    
    ptr = *(unsigned short **)((char *)work + 0xEA8);
    flags = *ptr;
    
    if (flags & 0xA000)
    {
        *(int *)((char *)work + 0xEB4) = -1;
        return 1;
    }
    
    if (flags & 0x2000)
    {
        return 1;
    }
    
    return 1;
}

void s11d_rope_800C5538(void *work)
{
    void *ptr1;
    void *ptr2;
    
    ptr1 = (char *)work + 0xF04;
    ptr2 = (char *)work + 0xEC8;
    
    *(int *)((char *)ptr1 + 0x4) = 0;
    *(int *)((char *)ptr2 + 0x4) = 0;
    *(int *)((char *)ptr2 + 0x20) = 0;
    *(int *)((char *)ptr2 + 0x10) = 0;
    *(int *)((char *)ptr2 + 0x8) = 0;
    *(void **)((char *)work + 0xEC8) = work;
    *(int *)((char *)ptr1 + 0x20) = 0;
    *(int *)((char *)ptr1 + 0x10) = 0;
    *(int *)((char *)ptr1 + 0x8) = 0;
    *(void **)((char *)work + 0xF04) = work;
    *(int *)((char *)ptr2 + 0x2C) = 0;
    *(int *)((char *)ptr2 + 0x28) = 0;
    *(int *)((char *)ptr2 + 0x24) = 0;
    *(int *)((char *)ptr1 + 0x2C) = 0;
    *(int *)((char *)ptr1 + 0x28) = 0;
    *(int *)((char *)ptr1 + 0x24) = 0;
}

void s11d_rope_800C44A4(void *work)
{
    int temp1;
    int temp2;
    int mask;
    void *ptr;
    unsigned short val1;
    unsigned short val2;
    
    mask = -3;
    temp1 = *(int *)((char *)work + 0xF74);
    temp2 = *(int *)((char *)work + 0xF70);
    temp1 = temp1 & mask;
    temp2 = temp2 & 0x2000;
    *(int *)((char *)work + 0xF74) = temp1;
    
    if (temp2 != 0)
    {
        return;
    }
    
    ptr = *(void **)((char *)work + 0xEA4);
    val1 = *(unsigned short *)((char *)ptr + 0x4);
    val2 = *(unsigned short *)((char *)work + 0xF88);
    
    if (val2 < val1)
    {
        temp1 = temp1 | 2;
        *(int *)((char *)work + 0xF74) = temp1;
    }
}

// External function for s11d_rope_800C8200

void s11d_rope_800C8200(void *work, int arg1)
{
    void *ptr1;
    void *ptr2;
    int temp;
    
    if (arg1 != 0)
    {
        return;
    }
    
    ptr1 = *(void **)((char *)work + 0x9C);
    temp = *(int *)((char *)ptr1 + 0x28);
    temp |= 0x80;
    *(int *)((char *)ptr1 + 0x28) = temp;
    
    ptr2 = *(void **)((char *)work + 0x7DC);
    temp = *(int *)((char *)ptr2 + 0x24);
    temp |= 0x100;
    *(int *)((char *)ptr2 + 0x24) = temp;
    
    func_800AB6C8();
}

// External function and data for s11d_rope_800C481C

void s11d_rope_800C481C(void *work)
{
    int value;
    int result;
    
    value = *(int *)((char *)work + 0xEDC);
    result = value / 3;
    result += 0x800;
    data_800B77CA = result;
    
    func_80030938((void *)0x800B77C8);
}

void s11d_rope_800C45F8(void *work)
{
    short value;
    int diff;
    void *ptr;
    int result;
    
    value = *(short *)((char *)work + 0x22);
    diff = 3000 - value;
    ptr = *(void **)((char *)work + 0xA14);
    
    if (diff < 0)
    {
        *(short *)((char *)ptr + 0x2A) = 32;
    }
    else
    {
        result = diff / 100;
        *(short *)((char *)ptr + 0x2A) = 32 - result;
    }
}

int s11d_rope_800C52F0(void *work)
{
    int temp;
    unsigned short *ptr;
    unsigned short flags;
    
    temp = *(int *)((char *)work + 0xF74);
    
    if (temp & 0x2000)
    {
        return 0;
    }
    
    ptr = *(unsigned short **)((char *)work + 0xEA8);
    flags = *ptr;
    
    if (flags & 0xA000)
    {
        *(int *)((char *)work + 0xEB4) = -1;
        return 1;
    }
    
    if (flags & 0x2000)
    {
        return 1;
    }
    
    return 1;
}

int s11d_rope_800C5298(void *work)
{
    int flags;
    int mask;
    unsigned short *ptr;
    unsigned short value;
    
    flags = *(int *)((char *)work + 0xF74);
    
    if (!(flags & 0x4000))
    {
        return 0;
    }
    
    if (flags & 0x1000)
    {
        return 0;
    }
    
    mask = 0x400000;
    
    if (flags & mask)
    {
        return 0;
    }
    
    ptr = *(unsigned short **)((char *)work + 0xEA8);
    value = *ptr;
    
    if (value & 0x20)
    {
        return 0;
    }
    
    flags |= mask;
    *(int *)((char *)work + 0xF74) = flags;
    return 1;
}

// External function for s11d_rope_800C3DF0

void s11d_rope_800C3DF0(void *work, void *arg1)
{
    unsigned char flag;
    unsigned short value;
    
    flag = *(unsigned char *)((char *)work + 0x55);
    
    if (flag & 0x2)
    {
        return;
    }
    
    // Copy 8 bytes from arg1 to work+0x24 (unaligned copy)
    *(int *)((char *)work + 0x24) = *(int *)((char *)arg1 + 0x0);
    *(int *)((char *)work + 0x28) = *(int *)((char *)arg1 + 0x4);
    
    value = *(unsigned short *)((char *)work + 0xA);
    *(unsigned short *)((char *)work + 0x2A) = value;
    
    func_800A9538(arg1 + 0x10, work);
}

int s11d_rope_800C4FC8(void *work)
{
    unsigned short *ptr;
    unsigned short flags;
    int value;
    
    ptr = *(unsigned short **)((char *)work + 0xEA8);
    flags = *ptr;
    
    if (!(flags & 0x2000))
    {
        value = *(int *)((char *)work + 0xEB4);
        if (value != 1)
        {
            ptr = *(unsigned short **)((char *)work + 0xEA8);
            flags = *ptr;
            
            if (flags & 0x8000)
            {
                return 0;
            }
            
            value = *(int *)((char *)work + 0xEB4);
            if (value == -1)
            {
                return 0;
            }
            
            return 1;
        }
    }
    
    ptr = *(unsigned short **)((char *)work + 0xEA8);
    flags = *ptr;
    
    if (flags & 0x8000)
    {
        return 0;
    }
    
    value = *(int *)((char *)work + 0xEB4);
    if (value == -1)
    {
        return 0;
    }
    
    return 1;
}

// External functions and data for s11d_rope_800C61D8

void s11d_rope_800C61D8(void *work, int index)
{
    void *ptr;
    int offset;
    char stack_buf[32];
    
    offset = index * 156;
    offset += 72;
    ptr = *(void **)((char *)work + 0x9C);
    ptr = (char *)ptr + offset;
    
    func_8001BC44(ptr);
    func_8001BD20(&s11d_dword_800C32BC);
    func_8001BD64(&s11d_dword_800C32C4);
    func_80092ED8(stack_buf);
    func_80072728(stack_buf, 1);
}

void s11d_rope_800C62E0(void *work)
{
    int flags;
    int value;
    int mask;
    void *ptr;
    
    flags = *(int *)((char *)work + 0xF74);
    
    if (flags & 0x4000)
    {
        return;
    }
    
    ptr = (char *)work + 0xF04;
    
    if (flags & 0x10)
    {
        value = 1;
    }
    else
    {
        value = -1;
    }
    *(int *)((char *)ptr + 0x8) = value;
    
    *(int *)((char *)work + 0xF04) = 0x30;
    flags = *(int *)((char *)work + 0xF74);
    flags |= 0x200;
    *(int *)((char *)work + 0xF74) = flags;
    
    value = *(int *)((char *)ptr + 0x1C);
    *(int *)((char *)ptr + 0x4) = value;
    
    mask = -8;
    *(int *)((char *)work + 0xF60) = mask;
    flags = *(int *)((char *)work + 0xF74);
    *(int *)((char *)work + 0xF68) = mask;
    
    if (flags & 0x1000)
    {
        *(int *)((char *)work + 0xF64) = mask;
    }
}

// External data for s11d_rope_800C54CC

void s11d_rope_800C54CC(void *work)
{
    void *ptr;
    int count;
    unsigned short target;
    void **array;
    int i;
    
    ptr = *(void **)((char *)work + 0xEA4);
    if (ptr != 0)
    {
        return;
    }
    
    ptr = *(void **)((char *)work + 0xEA0);
    if (ptr == 0)
    {
        return;
    }
    
    array = &GM_WhereList;
    count = data_800BB9B4;
    target = *(unsigned short *)((char *)work + 0xEA0);
    
    for (i = 0; i < count; i++)
    {
        ptr = array[i];
        if (*(unsigned short *)((char *)ptr + 0x30) == target)
        {
            *(void **)((char *)work + 0xEA4) = ptr;
            return;
        }
    }
}

// External functions for s11d_rope_800C90BC and s11d_rope_800C9134

void s11d_rope_800C90BC(void *work)
{
    void *result;
    void **array;
    int i;
    
    result = func_80020968(119);
    if (result == 0)
    {
        return;
    }
    
    array = (void **)((char *)work + 0x107C);
    
    for (i = 0; i < 3; i++)
    {
        result = func_80020AA4();
        if (result == 0)
        {
            break;
        }
        
        result = func_800209E8(result);
        array[i] = result;
    }
}

void s11d_rope_800C9134(void *work)
{
    void *result;
    void **array;
    int i;
    
    result = func_80020968(118);
    if (result == 0)
    {
        return;
    }
    
    array = (void **)((char *)work + 0x1088);
    
    for (i = 0; i < 4; i++)
    {
        result = func_80020AA4();
        if (result == 0)
        {
            break;
        }
        
        result = func_800209E8(result);
        array[i] = result;
    }
}

// External function for s11d_rope_800C8FDC

// External functions and data for s11d_rope_800C879C

int s11d_rope_800C879C(void *work)
{
    void *result;
    unsigned short temp;
    
    result = func_8002D400(work);
    *(void **)((char *)work + 0x804) = result;
    
    if (result == 0)
    {
        return -1;
    }
    
    func_8002DC74(result, 21, 1, &s11d_dword_800C32CC);
    
    temp = *(unsigned short *)((char *)work + 0x18);
    func_8002DCCC(result, 1, -1, &linkvarbuf, &DG_ZeroVector, &temp);
    
    *(unsigned short *)((char *)work + 0x16) = temp;
    return 0;
}

void s11d_rope_800C6478(void *work)
{
    unsigned short *ptr;
    unsigned short flags;
    int temp;
    int mask;
    
    ptr = *(unsigned short **)((char *)work + 0xEA8);
    flags = *(unsigned short *)((char *)ptr + 0x2);
    
    if (flags & 0x40)
    {
        *(int *)((char *)work + 0xF6C) = -8;
    }
    
    temp = *(int *)((char *)work + 0xF6C);
    if (temp < 0)
    {
        temp++;
        *(int *)((char *)work + 0xF6C) = temp;
    }
    
    ptr = *(unsigned short **)((char *)work + 0xEA8);
    flags = *ptr;
    
    if (!(flags & 0x40))
    {
        temp = *(int *)((char *)work + 0xF74);
        mask = 0xFFDFFFFF;
        temp &= mask;
        *(int *)((char *)work + 0xF74) = temp;
    }
    
    ptr = *(unsigned short **)((char *)work + 0xEA8);
    flags = *ptr;
    
    if (!(flags & 0x20))
    {
        temp = *(int *)((char *)work + 0xF74);
        mask = 0xFFBFFFFF;
        temp &= mask;
        *(int *)((char *)work + 0xF74) = temp;
    }
}

// External functions for s11d_rope_800C3D50

int s11d_rope_800C3D50(void *work, int arg1)
{
    unsigned short value;
    int temp;
    
    if (arg1 == 0)
    {
        return 0;
    }
    
    func_800292E4((char *)work + 0x70);
    func_80029324((char *)work + 0x60);
    
    value = *(unsigned short *)((char *)work + 0x60);
    if (value != 0)
    {
        arg1--;
        if (arg1 != 1)
        {
            return arg1;
        }
        
        // Copy 8 bytes from work+0x68 to work+0x60
        *(int *)((char *)work + 0x60) = *(int *)((char *)work + 0x68);
        *(int *)((char *)work + 0x64) = *(int *)((char *)work + 0x6C);
        
        temp = *(int *)((char *)work + 0x74);
        value = *(unsigned short *)((char *)work + 0x60);
        *(int *)((char *)work + 0x70) = temp;
        
        if (value == 0)
        {
            arg1 = 0;
        }
    }
    
    return arg1;
}

void s11d_rope_800C4404(void *work)
{
    int temp;
    void *ptr;
    unsigned short val1;
    unsigned short val2;
    short diff;
    
    temp = *(int *)((char *)work + 0xF60);
    if (temp >= 0)
    {
        return;
    }
    
    temp = *(int *)((char *)work + 0xEAC);
    if (temp == 0x800C7138)
    {
        return;
    }
    
    ptr = *(void **)((char *)work + 0x804);
    val1 = *(unsigned short *)((char *)ptr + 0x12);
    val2 = *(unsigned short *)((char *)work + 0x98);
    
    if (val1 == val2)
    {
        val1 = *(unsigned short *)((char *)work + 0x22);
        val1 -= 250;
    }
    else
    {
        val1 = *(unsigned short *)((char *)work + 0x22);
        val1 -= 950;
    }
    
    diff = val1 - 200;
    diff--;
    
    if ((unsigned short)diff < 499)
    {
        val1 = *(unsigned short *)((char *)work + 0x22);
        val1 -= 200;
        *(unsigned short *)((char *)work + 0x22) = val1;
        return;
    }
    
    if (diff < -499)
    {
        if (diff >= -499)
        {
            return;
        }
        
        val1 = *(unsigned short *)((char *)work + 0x22);
        val1 += 200;
        *(unsigned short *)((char *)work + 0x22) = val1;
    }
}

// Function 27 - s11d_rope_800C4ECC
void s11d_rope_800C4ECC(void *work)
{
    unsigned int flags;
    void *ptr;
    unsigned short value;
    unsigned int temp;
    unsigned int mask;
    
    flags = *(unsigned int *)((char *)work + 0xF70);
    temp = flags & 0x6033;
    
    if (temp == 0)
    {
        return;
    }
    
    ptr = *(void **)((char *)work + 0xEA8);
    value = *(unsigned short *)ptr;
    temp = value & 0x10;
    
    if (temp == 0)
    {
        value = *(unsigned short *)((char *)((void *)0x800B77E8) + 0x22);
        
        if (value == 0)
        {
            flags |= 0x1000;
            *(unsigned int *)((char *)work + 0xF70) = flags;
            *(int *)((char *)work + 0xF78) = -4;
            *(unsigned short *)((char *)((void *)0x800B77E8) + 0x22) = 1;
            
            temp = *(unsigned int *)((char *)((void *)0x800B77B8) + 0x2B);
            *(unsigned int *)((char *)work + 0xF53) = temp;
            temp = *(unsigned int *)((char *)((void *)0x800B77B8) + 0x28);
            *(unsigned int *)((char *)work + 0xF50) = temp;
            
            temp = *(unsigned int *)((char *)((void *)0x800B77B8) + 0x2F);
            *(unsigned int *)((char *)work + 0xF57) = temp;
            temp = *(unsigned int *)((char *)((void *)0x800B77B8) + 0x2C);
            *(unsigned int *)((char *)work + 0xF54) = temp;
            
            return;
        }
    }
    
    value = *(unsigned short *)((char *)((void *)0x800B77E8) + 0x22);
    
    if (value != 0)
    {
        return;
    }
    
    mask = 0xEFFF;
    flags &= mask;
    *(unsigned int *)((char *)work + 0xF70) = flags;
    *(int *)((char *)work + 0xF78) = 4;
    *(unsigned short *)((char *)((void *)0x800B77E8) + 0x22) = 0;
}

// Function 28 - s11d_rope_800C5410

void s11d_rope_800C5410(void)
{
    int mode;
    int value;
    int action;
    
    mode = data_800BBA40;
    value = data_800BB9D4;
    
    action = 0;
    value -= 2;
    
    if ((unsigned int)value >= 16)
    {
        return;
    }
    
    // Jump table based on value
    switch (value)
    {
        case 7:  // 0x09 - 2 = 7
            action = 2;
            break;
            
        case 15: // 0x11 - 2 = 15
            action = 3;
            break;
            
        case 6:  // 0x08 - 2 = 6
            action = 3;
            break;
            
        case 14: // 0x10 - 2 = 14
            action = 3;
            break;
            
        case 12: // 0x0E - 2 = 12
            action = 3;
            break;
            
        case 25: // 0x1B - 2 = 25 (but this is >= 16, unreachable?)
            action = 2;
            break;
            
        default:
            action = 0;
            break;
    }
    
    if (action != 0)
    {
        func_800329C4(GM_PlayerPosition, action, 0);
    }
}

// Function 29 - s11d_rope_800C5348

void s11d_rope_800C5348(void *work)
{
    void *ptr;
    void *base;
    unsigned short value1;
    unsigned short value2;
    unsigned short value3;
    unsigned short check;
    int result;
    unsigned int temp;
    
    result = func_80016CCC((void *)0x800D1D5C);
    
    base = (char *)work + 0x38;
    value1 = *(unsigned short *)((char *)work + 0x36);
    ptr = *(void **)((char *)work + 0x804);
    
    if (value1 == 0)
    {
        return;
    }
    
    do
    {
        check = *(unsigned short *)ptr;
        
        if (check == result)
        {
            func_800C4898(work, 0);
            
            value2 = *(unsigned short *)((char *)work + 0x28);
            value3 = *(unsigned short *)((char *)work + 0x26);
            check = *(unsigned short *)((char *)work + 0x6);
            
            *(unsigned short *)((char *)work + 0x28) = 0;
            *(unsigned short *)((char *)work + 0x2A) = 0;
            
            value3 += value2;
            check &= 0xFFFB;
            
            *(unsigned short *)((char *)work + 0x26) = value3;
            *(unsigned short *)((char *)work + 0x6) = check;
            
            // Copy 8 bytes using unaligned operations
            // From 0x800BB39C to work+0x2C
            temp = *(unsigned int *)((char *)((void *)0x800BB39C) + 0x3);
            *(unsigned int *)((char *)work + 0x2F) = temp;
            temp = *(unsigned int *)((void *)0x800BB39C);
            *(unsigned int *)((char *)work + 0x2C) = temp;
            
            temp = *(unsigned int *)((char *)((void *)0x800BB39C) + 0x7);
            *(unsigned int *)((char *)work + 0x33) = temp;
            temp = *(unsigned int *)((char *)((void *)0x800BB39C) + 0x4);
            *(unsigned int *)((char *)work + 0x30) = temp;
            
            return;
        }
        
        value1--;
        ptr = (char *)ptr + 2;
        
    } while (value1 > 0);
}

// Function 30 - s11d_rope_800C7EC4 - 30 FUNCTION MILESTONE!

void s11d_rope_800C7EC4(void *work, int arg1)
{
    unsigned int flags;
    unsigned short value;
    void *base;
    unsigned int temp;
    
    if (arg1 == 0)
    {
        return;
    }
    
    flags = *(unsigned int *)((char *)work + 0xF74);
    flags |= 0x200;
    
    *(unsigned short *)((char *)work + 0x70) = 0;
    *(unsigned short *)((char *)work + 0x6C) = 0;
    *(unsigned int *)((char *)work + 0xF74) = flags;
    
    data_800B4DAE = 0;
    
    value = *(unsigned short *)((char *)work + 0xAA);
    
    if (value != 14)
    {
        func_80034CD4((char *)work + 0x9C, (void *)arg1, 0, 4);
    }
    
    value = *(unsigned short *)((char *)work + 0x66);
    value -= 32;
    *(unsigned short *)((char *)work + 0x66) = value;
    
    if (arg1 == 8)
    {
        base = GM_PlayerPosition;
        
        // Copy 8 bytes using unaligned operations
        // From base+0x20 to work+0x0
        temp = *(unsigned int *)((char *)base + 0x23);
        *(unsigned int *)((char *)work + 0x3) = temp;
        temp = *(unsigned int *)((char *)base + 0x20);
        *(unsigned int *)work = temp;
        
        temp = *(unsigned int *)((char *)base + 0x27);
        *(unsigned int *)((char *)work + 0x7) = temp;
        temp = *(unsigned int *)((char *)base + 0x24);
        *(unsigned int *)((char *)work + 0x4) = temp;
    }
    
    if (arg1 == 24)
    {
        func_8002B6C8();
    }
}

// Function 31 - s11d_rope_800C7A4C

void s11d_rope_800C7A4C(void *work, int arg1)
{
    unsigned int flags;
    unsigned int mask;
    unsigned short value;
    
    if (arg1 != 0)
    {
        return;
    }
    
    // Clear bits 0x600000 and set bit 0x10000
    flags = *(unsigned int *)((char *)work + 0xF74);
    mask = 0xFF9FFFFF;
    flags &= mask;
    flags |= 0x10000;
    *(unsigned int *)((char *)work + 0xF74) = flags;
    
    func_800329C4((char *)work + 0x20, 25, 1);
    
    // Set bit 0x100 in F70
    flags = *(unsigned int *)((char *)work + 0xF70);
    flags |= 0x100;
    *(unsigned int *)((char *)work + 0xF70) = flags;
    
    value = *(unsigned short *)((char *)work + 0xAA);
    
    if (value != 9)
    {
        func_80034CD4((char *)work + 0x9C, (void *)arg1, 0, 4);
    }
    
    *(unsigned short *)((char *)work + 0x6E) = 0x800;
    
    func_800C4898(work, 0);
    
    value = *(unsigned short *)((char *)work + 0xB6);
    
    if (value == 0)
    {
        func_800C486C(work);
        
        *(int *)((char *)work + 0xEAC) = 0x800C6834;
        
        flags = *(unsigned int *)((char *)work + 0xF70);
        mask = 0xFEFF;
        
        *(int *)((char *)work + 0xEB0) = 0;
        *(unsigned short *)((char *)work + 0xEBE) = 0;
        *(unsigned short *)((char *)work + 0xEBC) = 0;
        
        flags &= mask;
        *(unsigned int *)((char *)work + 0xF70) = flags;
    }
    
    value = *(unsigned short *)((char *)work + 0x66);
    value -= 128;
    *(unsigned short *)((char *)work + 0x66) = value;
}

// Function 32 - s11d_rope_800C8FDC

int s11d_rope_800C8FDC(void *work)
{
    void *ptr;
    void *result;
    int count;
    int limit;
    int index;
    
    count = 0;
    index = work;
    
    result = func_80020968(99);
    
    if (result != 0)
    {
        ptr = (char *)work + 0xFE4;
        limit = 16;
        
        do
        {
            result = func_80020AA4();
            
            if (result == 0)
            {
                break;
            }
            
            if (count == limit)
            {
                break;
            }
            
            index++;
            result = func_80020AA4();
            
            if (result != 0)
            {
                func_8002099E(result, ptr);
            }
            
            ptr = (char *)ptr + 8;
            
        } while (1);
    }
    
    result = func_80020968(104);
    
    if (result != 0)
    {
        ptr = (char *)work + 0xFA4;
        limit = 16;
        
        do
        {
            result = func_80020AA4();
            
            if (result == 0)
            {
                break;
            }
            
            if (count == limit)
            {
                break;
            }
            
            result = func_80020AA4();
            
            if (result != 0)
            {
                result = func_80020A14(result);
                *(int *)ptr = result;
            }
            
            ptr = (char *)ptr + 4;
            count++;
            
        } while (1);
    }
    
    *(int *)((char *)work + 0xF9C) = index;
    *(int *)((char *)work + 0xFA0) = 0;
    
    return 2;
}

// Function 33 - s11d_rope_800C4DE0

int s11d_rope_800C4DE0(void *work)
{
    unsigned int flags;
    unsigned int mask;
    unsigned int temp;
    void *ptr;
    unsigned short value;
    
    flags = *(unsigned int *)((char *)work + 0xF74);
    mask = 0xFEFDFFFF;
    flags &= mask;
    
    temp = flags & 0x10;
    
    if (temp != 0)
    {
        *(unsigned int *)((char *)work + 0xF74) = flags;
        
        temp = flags & 0x200000;
        if (temp != 0)
        {
            return 2;
        }
    }
    else
    {
        *(unsigned int *)((char *)work + 0xF74) = flags;
    }
    
    temp = *(int *)((char *)work + 0xF6C);
    
    if (temp < 0)
    {
        return 2;
    }
    
    ptr = *(void **)((char *)work + 0xEA8);
    flags |= 0x200000;
    
    *(unsigned int *)((char *)work + 0xF74) = flags;
    *(int *)((char *)work + 0xEB4) = 0;
    
    value = *(unsigned short *)ptr;
    temp = value & 0x2000;
    
    if (temp != 0)
    {
        temp = value & 0x8000;
        if (temp != 0)
        {
            *(int *)((char *)work + 0xEB4) = -1;
        }
    }
    
    value = *(unsigned short *)ptr;
    temp = value & 0x4000;
    
    if (temp != 0)
    {
        flags = *(unsigned int *)((char *)work + 0xF74);
        flags |= 0x20000;
        *(unsigned int *)((char *)work + 0xF74) = flags;
    }
    else
    {
        temp = value & 0x1000;
        if (temp != 0)
        {
            flags = *(unsigned int *)((char *)work + 0xF74);
            flags |= 0x1000000;
            *(unsigned int *)((char *)work + 0xF74) = flags;
        }
    }
    
    temp = *(int *)((char *)work + 0xF7C);
    
    if (temp == 0)
    {
        func_800C4898(work, 0);
    }
    
    return 1;
}

// Function 34 - s11d_rope_800C8EE4

void s11d_rope_800C8EE4(void *work)
{
    void *ptr;
    int result;
    unsigned short value;
    
    ptr = (char *)work + 0xF84;
    
    result = func_80020968(97);
    
    if (result != 0)
    {
        func_8002099E(result, (char *)work + 0xF8C);
    }
    else
    {
        *(unsigned short *)((char *)work + 0x8) = 0x1770;
        *(unsigned short *)((char *)work + 0xA) = 0x6590;
        
        value = *(unsigned short *)((char *)work + 0xA);
        data_800D1F7C = value;
        
        value = *(unsigned short *)((char *)work + 0x8);
        data_800D1F80 = value;
    }
    
    result = func_80020968(105);
    
    if (result != 0)
    {
        func_8002099E(result, ptr);
    }
    else
    {
        *(unsigned short *)((char *)work + 0x0) = 0xE4A8;
        *(unsigned short *)((char *)work + 0x2) = 0xCF2C;
        *(unsigned short *)((char *)work + 0x4) = 0;
        
        value = *(unsigned short *)((char *)work + 0x2);
        data_800D1F7E = value;
        
        value = *(unsigned short *)((char *)work + 0x0);
        data_800D1F82 = value;
    }
    
    result = func_80020968(114);
    
    if (result != 0)
    {
        func_8002099E(result, (char *)work + 0x10);
    }
    else
    {
        *(unsigned short *)((char *)work + 0x10) = 0xF448;
        *(unsigned short *)((char *)work + 0x12) = 0x7530;
        *(unsigned short *)((char *)work + 0x14) = 0x258;
    }
}

// Function 35 - s11d_rope_800C42F4

void s11d_rope_800C42F4(void *work, void *dest)
{
    int stack[12];
    void *ptr1;
    void *ptr2;
    void *ptr3;
    int count;
    int loop;
    
    // Copy 32 bytes from work to stack
    stack[0] = *(int *)((char *)work + 0x0);
    stack[1] = *(int *)((char *)work + 0x4);
    stack[2] = *(int *)((char *)work + 0x8);
    stack[3] = *(int *)((char *)work + 0xC);
    stack[4] = *(int *)((char *)work + 0x10);
    stack[5] = *(int *)((char *)work + 0x14);
    stack[6] = *(int *)((char *)work + 0x18);
    stack[7] = *(int *)((char *)work + 0x1C);
    
    ptr1 = *(void **)((char *)work + 0x38);
    ptr2 = *(void **)((char *)work + 0x40);
    
    ptr3 = (char *)work + 0x48;
    count = 0;
    loop = 0;
    
    do
    {
        func_800D1AB0(ptr1, (void *)stack);
        func_800D1950((void *)stack, dest, (char *)work + 0x5C);
        
        stack[9] = *(int *)((char *)ptr3 + 0x20);
        stack[10] = *(int *)((char *)ptr3 + 0x24);
        stack[11] = *(int *)((char *)ptr3 + 0x28);
        
        ptr1 = (char *)ptr1 + 8;
        count++;
        loop++;
        
    } while (count < 5);
    
    *(int *)dest = stack[5];
    *(int *)((char *)dest + 0x4) = stack[6];
    *(int *)((char *)dest + 0x8) = stack[7];
}

// Function 36 - s11d_rope_800C868C

void s11d_rope_800C868C(void *work)
{
    void *ptr1;
    void *ptr2;
    void *ptr3;
    void *ptr4;
    unsigned int flags;
    unsigned int mask;
    int value;
    
    func_800CE04C();
    
    ptr1 = *(void **)((char *)work + 0x800);
    ptr2 = (char *)work + 0x20;
    
    func_80015118(ptr1, ptr2);
    func_80026C0C(work);
    func_80034BF8((char *)work + 0x9C);
    
    ptr1 = *(void **)((char *)work + 0x804);
    func_8002D4B0(ptr1);
    
    ptr3 = *(void **)((char *)work + 0x810);
    if (ptr3 != 0)
    {
        func_80018C2E0(ptr3);
        func_8001BC04(ptr3);
    }
    
    ptr4 = *(void **)((char *)work + 0xA14);
    if (ptr4 != 0)
    {
        func_80018C2E0(ptr4);
        func_8001BC04(ptr4);
    }
    
    ptr3 = *(void **)((char *)work + 0x7DC);
    if (ptr3 != 0)
    {
        func_80018C2E0(ptr3);
        func_8001BC04(ptr3);
    }
    
    mask = 0xFFF7FFFF;
    flags = GM_GameStatus;
    value = data_800BB9F4;
    flags &= mask;
    GM_GameStatus = flags;
    
    if (value == work)
    {
        data_800BB9F4 = 0;
    }
    
    value = data_800BBA20;
    if (value == work)
    {
        data_800BBA20 = 0;
    }
    
    func_800CCDE0();
}

// Function 37 - s11d_rope_800C8250

void s11d_rope_800C8250(void *work)
{
    typedef void (*FuncPtr)(void *);
    FuncPtr func;
    int value;
    unsigned int temp;
    unsigned short mode1;
    unsigned short mode2;
    
    // Copy 8 bytes from 0x800BB39C to work+0x64
    temp = *(unsigned int *)((char *)((void *)0x800BB39C) + 0x3);
    *(unsigned int *)((char *)work + 0x67) = temp;
    temp = *(unsigned int *)((void *)0x800BB39C);
    *(unsigned int *)((char *)work + 0x64) = temp;
    
    temp = *(unsigned int *)((char *)((void *)0x800BB39C) + 0x7);
    *(unsigned int *)((char *)work + 0x6B) = temp;
    temp = *(unsigned int *)((char *)((void *)0x800BB39C) + 0x4);
    *(unsigned int *)((char *)work + 0x68) = temp;
    
    func_800C54CC();
    func_800C44A4(work);
    func_800C4648(work);
    func_800C481C(work);
    func_800C4574(work);
    func_800C44F0(work);
    func_800C5348(work);
    func_800C48EC(work);
    func_800C4B78(work);
    func_800C4ECC(work);
    func_800C45F8(work);
    func_800C6478(work);
    func_800C5B10(work);
    
    value = *(int *)((char *)work + 0xEB0);
    value++;
    *(int *)((char *)work + 0xEB0) = value;
    
    func = (FuncPtr)*(int *)((char *)work + 0xEAC);
    func(work);
    
    func_800C5E74(work);
    func_800C502C(work);
    
    temp = *(unsigned int *)((char *)work + 0xF70);
    temp &= 0x2;
    temp = (temp != 0) ? 1 : 0;
    data_800D1F84 = temp;
    
    mode1 = *(unsigned short *)((char *)work + 0xAA);
    data_800BBA40 = mode1;
    
    mode2 = *(unsigned short *)((char *)work + 0x186);
    data_800BB9D4 = mode2;
    
    func_800C5410();
}

// Function 38 - s11d_rope_800C634C
void s11d_rope_800C634C(void *work)
{
    void *ptr1;
    void *ptr2;
    int value;
    int delta;
    int result;
    int limit;
    int temp;
    unsigned int flags;
    
    ptr1 = (char *)work + 0xEC8;
    value = *(int *)((char *)work + 0xEB4);
    ptr2 = (char *)work + 0xF04;
    
    if (value == 0)
    {
        goto label_exit;
    }
    
    temp = *(int *)((char *)ptr1 + 0x8);
    if (temp != 0)
    {
        *(int *)((char *)ptr1 + 0x8) = value;
    }
    
    delta = *(int *)((char *)ptr1 + 0x8);
    result = delta * value;
    result >>= 9;
    
    if (result < 0)
    {
        limit = 0x80;
    }
    else
    {
        limit = -128;
    }
    
    temp = *(int *)((char *)work + 0xEC8);
    temp += result;
    
    if (temp < 0)
    {
        delta = -delta;
        *(int *)((char *)ptr1 + 0x8) = delta;
        limit = -limit;
    }
    
    if (temp < 16)
    {
        limit = 16;
    }
    
    if (temp >= 181)
    {
        limit = 180;
    }
    
    *(int *)((char *)work + 0xEC8) = limit;
    
    flags = *(unsigned int *)((char *)work + 0xF74);
    flags |= 0x100;
    *(unsigned int *)((char *)work + 0xF74) = flags;
    
    value = *(int *)((char *)ptr1 + 0x1C);
    *(int *)((char *)ptr1 + 0x4) = value;
    
    // Calculate: value * 2 - value / 8
    temp = value << 1;
    temp += value;
    temp <<= 2;
    temp = -temp;
    *(unsigned short *)((char *)work + 0x6E) = temp;
    *(unsigned short *)((char *)work + 0xEC0) = 0;
    return;
    
label_exit:
    value = *(int *)((char *)ptr1 + 0x1C);
    if (value != 0)
    {
        *(unsigned short *)((char *)work + 0x6E) = 0x800;
    }
    
    flags = *(unsigned int *)((char *)work + 0xF74);
    flags |= 0x200;
    *(unsigned int *)((char *)work + 0xF74) = flags;
    
    *(int *)ptr2 = 128;
    
    *(int *)((char *)ptr2 + 0x8) = 1;
    
    value = *(int *)((char *)ptr2 + 0x1C);
    *(int *)((char *)ptr2 + 0x4) = value;
    
    flags = *(unsigned int *)((char *)work + 0xF74);
    temp = flags & 0x4000;
    
    if (temp != 0)
    {
        *(int *)((char *)work + 0xF60) = -8;
        *(int *)((char *)work + 0xF68) = -8;
    }
    else
    {
        *(int *)((char *)work + 0xF60) = -8;
    }
    
    temp = flags & 0x1000;
    if (temp != 0)
    {
        *(int *)((char *)work + 0xF64) = -8;
    }
}

// Function 39 - s11d_rope_800C7530

void s11d_rope_800C7530(void *work, int arg1)
{
    unsigned int flags;
    unsigned int mask;
    unsigned short value;
    void *ptr;
    unsigned short check;
    int result;
    
    if (arg1 != 0)
    {
        flags = *(unsigned int *)((char *)work + 0xF74);
        mask = 0xFFFEFFFF;
        flags &= mask;
        *(unsigned int *)((char *)work + 0xF74) = flags;
        
        flags = *(unsigned int *)((char *)work + 0xF70);
        mask = 0xFF00;
        flags &= mask;
        *(unsigned int *)((char *)work + 0xF70) = flags;
        
        value = *(unsigned short *)((char *)work + 0xAA);
        
        if (value != 1)
        {
            func_80034CD4((char *)work + 0x9C, (void *)arg1, 0, 4);
        }
        
        *(unsigned short *)((char *)work + 0xF44) = 0;
    }
    
    flags = *(unsigned int *)((char *)work + 0xF74);
    check = flags & 0x300;
    
    if (check == 0)
    {
        value = *(unsigned short *)((char *)work + 0xAA);
        
        if (value != 1)
        {
            func_80034CD4((char *)work + 0x9C, (void *)arg1, 0, 4);
        }
        
        ptr = *(void **)((char *)work + 0xEA8);
        check = *(unsigned short *)ptr;
        value = check & 0x8000;
        
        if (value != 0)
        {
            *(unsigned short *)((char *)work + 0x6E) = 0x600;
        }
        else
        {
            value = check & 0x2000;
            if (value != 0)
            {
                *(unsigned short *)((char *)work + 0x6E) = 0xFA00;
            }
        }
    }
    
    flags = *(unsigned int *)((char *)work + 0xF74);
    check = flags & 0x2000;
    
    if (check != 0)
    {
        func_800329C4((char *)work + 0x20, 178, 1);
        func_800C650C();
        *(int *)((char *)work + 0xEAC) = 0x800C6834;
        return;
    }
    
    result = func_80031298(work);
    
    if (result != 0)
    {
        *(int *)((char *)work + 0xEAC) = 0x800C6B18;
        return;
    }
    
    result = func_800C4DE0(work);
    
    if (result != 0)
    {
        *(int *)((char *)work + 0xEAC) = 0x800C766C;
        *(int *)((char *)work + 0xEB0) = 0;
        *(unsigned short *)((char *)work + 0xEBE) = 0;
        *(unsigned short *)((char *)work + 0xEBC) = 0;
    }
}

// Function 40 - s11d_rope_800C6834 - 40 FUNCTION MILESTONE!!!

void s11d_rope_800C6834(void *work, int arg1)
{
    unsigned int flags;
    unsigned int mask;
    unsigned short value;
    unsigned short temp_stack;
    int result;
    unsigned int temp;    
    if (arg1 != 0)
    {
        flags = *(unsigned int *)((char *)work + 0xF74);
        flags |= 0x10000;
        *(unsigned int *)((char *)work + 0xF74) = flags;
        
        // Copy 8 bytes from work+0x28 to work+0xF58 using unaligned ops
        temp = *(unsigned int *)((char *)work + 0x2B);
        *(unsigned int *)((char *)work + 0xF5B) = temp;
        temp = *(unsigned int *)((char *)work + 0x28);
        *(unsigned int *)((char *)work + 0xF58) = temp;
        
        temp = *(unsigned int *)((char *)work + 0x2F);
        *(unsigned int *)((char *)work + 0xF5F) = temp;
        temp = *(unsigned int *)((char *)work + 0x2C);
        *(unsigned int *)((char *)work + 0xF5C) = temp;
        
        flags = *(unsigned int *)((char *)work + 0xF70);
        mask = 0xFF00;
        flags &= mask;
        flags |= 0x80;
        *(unsigned int *)((char *)work + 0xF70) = flags;
        
        flags = *(unsigned int *)((char *)work + 0xF74);
        mask = 0xF0FF;
        flags &= mask;
        *(unsigned int *)((char *)work + 0xF74) = flags;
        
        func_800C5538();
        
        value = *(unsigned short *)((char *)work + 0xAA);
        
        if (value != 11)
        {
            func_80034CD4((char *)work + 0x9C, (void *)arg1, 0, 4);
        }
        
        *(unsigned short *)((char *)work + 0xF44) = 0;
    }
    
    value = *(unsigned short *)((char *)work + 0xF98);
    temp_stack = value;
    
    func_800266D4((char *)work + 0x24, &temp_stack, 1);
    
    result = func_80031298(work);
    
    if (result != 0)
    {
        func_800C6240(work);
        func_800329C4((char *)work + 0x20, 183, 1);
        *(int *)((char *)work + 0xEAC) = 0x800C6B18;
        return;
    }
    
    result = func_800C4DE0(work);
    
    if (result != 0)
    {
        func_800C6240(work);
        *(int *)((char *)work + 0xEAC) = 0x800C766C;
        return;
    }
    
    result = func_800C4F84(work);
    
    if (result != 0)
    {
        *(int *)((char *)work + 0xEAC) = 0x800C697C;
        *(int *)((char *)work + 0xEB0) = 0;
        *(unsigned short *)((char *)work + 0xEBE) = 0;
        *(unsigned short *)((char *)work + 0xEBC) = 0;
        return;
    }
    
    value = *(unsigned short *)((char *)work + 0x66);
    value -= 128;
    *(unsigned short *)((char *)work + 0x66) = value;
}

// Function 41 - s11d_rope_800C697C

void s11d_rope_800C697C(void *work, int arg1)
{
    unsigned int flags;
    unsigned int mask;
    unsigned short value;
    unsigned short temp_stack;
    int eb4_value;
    int result;
    short calc1;
    short calc2;
    short calc3;
    int check;
    
    if (arg1 != 0)
    {
        flags = *(unsigned int *)((char *)work + 0xF74);
        flags |= 0x10000;
        *(unsigned int *)((char *)work + 0xF74) = flags;
        
        flags = *(unsigned int *)((char *)work + 0xF70);
        mask = 0xFF00;
        flags &= mask;
        flags |= 0x80;
        
        value = *(unsigned short *)((char *)work + 0xAA);
        *(unsigned int *)((char *)work + 0xF70) = flags;
        
        if (value != 12)
        {
            func_80034CD4((char *)work + 0x9C, (void *)arg1, 0, 4);
        }
        
        eb4_value = *(int *)((char *)work + 0xEB4);
        
        if (eb4_value == 1)
        {
            *(unsigned short *)((char *)work + 0x6E) = 0xFC00;
        }
        else
        {
            *(unsigned short *)((char *)work + 0x6E) = 0x400;
        }
        
        *(unsigned short *)((char *)work + 0xF44) = 0;
    }
    
    value = *(unsigned short *)((char *)work + 0xF98);
    temp_stack = value;
    
    func_800266D4((char *)work + 0x24, &temp_stack, 1);
    
    result = func_800C4DE0(work);
    
    if (result != 0)
    {
        func_800C6240(work);
        *(int *)((char *)work + 0xEAC) = 0x800C766C;
        return;
    }
    
    result = func_800C4FC8(work);
    
    if (result != 0)
    {
        *(int *)((char *)work + 0xEAC) = 0x800C6834;
        return;
    }
    
    result = func_80031298(work);
    
    if (result != 0)
    {
        func_800C6240(work);
        func_800329C4((char *)work + 0x20, 183, 1);
        *(int *)((char *)work + 0xEAC) = 0x800C6B18;
        *(int *)((char *)work + 0xEB0) = 0;
        *(unsigned short *)((char *)work + 0xEBE) = 0;
        *(unsigned short *)((char *)work + 0xEBC) = 0;
        return;
    }
    
    value = *(unsigned short *)((char *)work + 0x66);
    value -= 128;
    *(unsigned short *)((char *)work + 0x66) = value;
    
    eb4_value = *(int *)((char *)work + 0xEB4);
    calc1 = eb4_value << 1;
    calc1 += eb4_value;
    
    value = *(unsigned short *)((char *)work + 0x20);
    temp_stack = value;
    
    calc2 = calc1 << 2;
    calc2 += calc1;
    calc3 = calc2 << 3;
    calc3 = -calc3;
    
    check = (short)*(unsigned short *)((char *)work + 0xF84);
    if (calc3 < check)
    {
        check = (short)*(unsigned short *)((char *)work + 0xF8C);
        if (calc3 >= check)
        {
            check = 0;
        }
        else
        {
            check = 1;
        }
    }
    else
    {
        check = 1;
    }
    
    if (check != 0)
    {
        eb4_value = *(int *)((char *)work + 0xEB4);
        calc1 = eb4_value << 1;
        calc1 += eb4_value;
        
        value = *(unsigned short *)((char *)work + 0x64);
        calc2 = calc1 << 2;
        calc2 += calc1;
        
        value += calc2;
        *(unsigned short *)((char *)work + 0x64) = value;
    }
}

// Function 42 - s11d_rope_800C7D20

void s11d_rope_800C7D20(void *work, int arg1)
{
    unsigned short value;
    unsigned int flags;
    unsigned int mask;
    int check;
    short temp1;
    short temp2;
    short temp3;
    unsigned char byte_val;
    
    if (arg1 == 0)
    {
        return;
    }
    
    value = *(unsigned short *)((char *)work + 0xAA);
    
    if (value != 13)
    {
        func_80034CD4((char *)work + 0x9C, (void *)arg1, 0, 4);
    }
    
    value = *(unsigned short *)((char *)work + 0x22);
    *(unsigned short *)((char *)work + 0xF44) = 450;
    
    if (value >= 59536)
    {
        func_800329C4((char *)work + 0x20, 179, 1);
    }
    else
    {
        func_800329C4((char *)work + 0x20, 177, 1);
    }
    
    func_8005D58C((void *)0x800C328C, 1);
    func_8005D58C((void *)0x800C3290, 2);
    
    flags = *(unsigned int *)((char *)work + 0xF74);
    flags |= 0x200;
    *(unsigned int *)((char *)work + 0xF74) = flags;
    
    value = *(unsigned short *)((char *)work + 0x22);
    
    if (value >= 51537)
    {
        *(unsigned short *)((char *)work + 0x68) = 48;
    }
    else
    {
        *(unsigned short *)((char *)work + 0x68) = 0;
    }
    
    if (arg1 < 10)
    {
        *(unsigned short *)((char *)work + 0x66) = -32;
    }
    else
    {
        *(unsigned short *)((char *)work + 0x66) = -128;
    }
    
    byte_val = *(unsigned char *)((char *)work + 0x77);
    check = byte_val & 0x1;
    
    if (check != 0)
    {
        *(unsigned short *)((char *)work + 0x6C) = 0xFC00;
    }
    
    temp1 = *(short *)((char *)work + 0x66);
    temp2 = *(short *)((char *)work + 0xB4);
    temp3 = *(short *)((void *)0x960400B4);
    
    temp1 = -temp1;
    
    if (temp1 > temp2)
    {
        temp1 -= temp3;
        *(short *)((char *)work + 0x66) = temp1;
    }
    
    if (arg1 != 16)
    {
        value = *(unsigned short *)((char *)work + 0x22);
        
        if (value >= 49536)
        {
            *(int *)((char *)work + 0xEAC) = 0x800C7EC4;
            *(int *)((char *)work + 0xEB0) = 0;
            *(unsigned short *)((char *)work + 0xEBE) = 0;
            *(unsigned short *)((char *)work + 0xEBC) = 0;
            return;
        }
    }
    
    flags = *(unsigned int *)((char *)work + 0xF74);
    mask = 0xFDFFFFFF;
    flags &= mask;
    
    *(int *)((char *)work + 0xEAC) = 0x800C7F8C;
    *(int *)((char *)work + 0xEB0) = 0;
    *(unsigned short *)((char *)work + 0xEBE) = 0;
    *(unsigned short *)((char *)work + 0xEBC) = 0;
    *(unsigned int *)((char *)work + 0xF74) = flags;
    
    // Complex calculation: (value << 5 >> 3) / 32 + (value << 5 >> 3) / 2
    temp1 = *(short *)((char *)work + 0x66);
    temp1 <<= 5;
    temp1 >>= 3;
    temp2 = temp1 >> 5;
    temp2 += temp1;
    temp2 >>= 1;
    *(short *)((char *)work + 0x66) = temp2;
}

// Function 43 - s11d_rope_800C6B18

void s11d_rope_800C6B18(void *work, int arg1)
{
    unsigned int flags;
    unsigned int mask;
    unsigned short value;
    void *ptr;
    unsigned short check;
    unsigned short ebc_val;
    
    if (arg1 == 0)
    {
        goto label_continue;
    }
    
    flags = *(unsigned int *)((char *)work + 0xF74);
    flags |= 0x10000;
    *(unsigned int *)((char *)work + 0xF74) = flags;
    
    flags = *(unsigned int *)((char *)work + 0xF70);
    mask = 0xFF00;
    flags &= mask;
    flags |= 0x1;
    
    value = *(unsigned short *)((char *)work + 0xAA);
    *(unsigned int *)((char *)work + 0xF70) = flags;
    
    if (value != 7)
    {
        func_80034CD4((char *)work + 0x9C, (void *)arg1, 0, 4);
    }
    
    ptr = *(void **)((char *)work + 0x804);
    *(int *)((char *)work + 0xEB8) = 0;
    *(int *)((char *)work + 0xEB4) = 0;
    *(unsigned short *)((char *)ptr + 0x12) = 200;
    
    *(unsigned short *)((char *)work + 0x6E) = 0x800;
    *(unsigned short *)((char *)work + 0xF44) = 450;
    
    if (arg1 < 4)
    {
        ebc_val = *(unsigned short *)((char *)work + 0xEBC);
        value = *(unsigned short *)((char *)work + 0x66);
        ebc_val++;
        value += 80;
        *(unsigned short *)((char *)work + 0xEBC) = ebc_val;
        *(unsigned short *)((char *)work + 0x66) = value;
    }
    
label_continue:
    value = *(unsigned short *)((char *)work + 0xB6);
    
    if (value != 0)
    {
        *(int *)((char *)work + 0xEAC) = 0x800C6CD4;
        *(int *)((char *)work + 0xEB0) = 0;
        *(unsigned short *)((char *)work + 0xEBE) = 0;
        *(unsigned short *)((char *)work + 0xEBC) = 0;
        return;
    }
    
    ptr = *(void **)((char *)work + 0xEA8);
    check = *(unsigned short *)ptr;
    check &= 0x20;
    
    if (check == 0)
    {
        ebc_val = *(unsigned short *)((char *)work + 0xEBC);
        
        if (ebc_val >= 5)
        {
            *(unsigned short *)((char *)work + 0xEBC) = 4;
        }
        
        *(int *)((char *)work + 0xF68) = -4;
        *(unsigned short *)((char *)work + 0xEBE) = 1;
    }
    
    value = *(unsigned short *)((char *)work + 0xEBE);
    
    if (value != 1)
    {
        goto label_exit;
    }
    
    value = *(unsigned short *)((char *)work + 0x66);
    ebc_val = *(unsigned short *)((char *)work + 0xEBC);
    value -= 80;
    ebc_val--;
    *(unsigned short *)((char *)work + 0xEBC) = ebc_val;
    check = ebc_val << 4;
    
    if (check == 0)
    {
        *(unsigned short *)((char *)work + 0x66) = value;
        return;
    }
    
    *(unsigned short *)((char *)work + 0x66) = value;
    
    ptr = *(void **)((char *)work + 0x804);
    *(unsigned short *)((char *)ptr + 0x12) = 900;
    
    flags = *(unsigned int *)((char *)work + 0xF74);
    check = flags & 0x2000;
    
    if (check != 0)
    {
        func_800329C4((char *)work + 0x20, 178, 1);
        func_800C650C();
        *(int *)((char *)work + 0xEAC) = 0x800C6834;
        return;
    }
    
label_exit:
    *(int *)((char *)work + 0xEAC) = 0x800C7530;
    *(int *)((char *)work + 0xEB0) = 0;
    *(unsigned short *)((char *)work + 0xEBE) = 0;
    *(unsigned short *)((char *)work + 0xEBC) = 0;
    
    value = *(unsigned short *)((char *)work + 0x68);
    value -= 108;
    *(unsigned short *)((char *)work + 0x68) = value;
}

// Function 44 - s11d_rope_800C4648

void s11d_rope_800C4648(void *work)
{
    int func_ptr;
    unsigned int flags;
    int f9c_val;
    int fa0_val;
    int count;
    int index;
    int offset;
    unsigned short value;
    void *ptr;
    short calc;
    unsigned short check;
    short result;
    short temp1;
    short temp2;
    short temp3;
    unsigned int stack[4];
    
    func_ptr = *(int *)((char *)work + 0xEAC);
    
    if (func_ptr == 0x800C6544)
    {
        return;
    }
    
    flags = *(unsigned int *)((char *)work + 0xF70);
    check = flags & 0x1000;
    
    if (check != 0)
    {
        return;
    }
    
    count = -1;
    f9c_val = *(int *)((char *)work + 0xF9C);
    fa0_val = *(int *)((char *)work + 0xFA0);
    index = f9c_val + count;
    
    if (index == fa0_val)
    {
        count++;
    }
    
    offset = fa0_val << 2;
    value = *(unsigned short *)((char *)work + 0x22);
    ptr = (char *)work + offset + 0xFA4;
    calc = *(int *)ptr;
    
    if (calc <= value)
    {
        if (fa0_val == -1)
        {
            fa0_val--;
        }
        else
        {
            count = -1;
            
            if (count != fa0_val)
            {
                count++;
                offset = count << 2;
                ptr = (char *)work + offset + 0xFA4;
                calc = *(int *)ptr;
                
                if (value < calc)
                {
                    fa0_val = count;
                }
            }
        }
    }
    
    offset = fa0_val << 3;
    ptr = (char *)work + 0xFE4 + offset;
    *(int *)((char *)work + 0xFA0) = fa0_val;
    
    temp1 = *(short *)((char *)((void *)0x800B77B8) + 0x18);
    stack[2] = temp1;
    
    // Copy 8 bytes using unaligned operations
    stack[0] = *(unsigned int *)((char *)((void *)0x800B77B8) + 0x13);
    temp2 = *(unsigned int *)((char *)((void *)0x800B77B8) + 0x10);
    stack[1] = *(unsigned int *)((char *)((void *)0x800B77B8) + 0x17);
    temp3 = *(unsigned int *)((char *)((void *)0x800B77B8) + 0x14);
    
    *(unsigned int *)((char *)&stack[0] + 0x3) = stack[0];
    *(unsigned int *)&stack[0] = temp2;
    *(unsigned int *)((char *)&stack[1] + 0x3) = stack[1];
    *(unsigned int *)&stack[1] = temp3;
    
    func_80016D40((void *)&stack[0], (void *)&stack[2], ptr);
    
    result = *(short *)((char *)&stack[3] + 0x4);
    
    if (result < 0)
    {
        result = -result;
    }
    
    if (result >= 65)
    {
        if (result < 0)
        {
            result = -64;
        }
        else
        {
            result = 64;
        }
        *(short *)((char *)&stack[3] + 0x4) = result;
    }
    
    temp1 = *(short *)((char *)((void *)0x800B77B8) + 0x18);
    result = *(short *)((char *)&stack[2]);
    temp1 += result;
    *(short *)((char *)((void *)0x800B77B8) + 0x18) = temp1;
    
    func_80030980(temp1);
    
    *(short *)((char *)&stack[3] + 0x4) = 0;
    
    result = *(short *)&stack[2];
    
    if (result < 0)
    {
        result = -result;
    }
    
    if (result >= 9)
    {
        if (result < 0)
        {
            result = -8;
        }
        else
        {
            result = 8;
        }
        *(short *)&stack[2] = result;
    }
    
    result = *(short *)((char *)&stack[2] + 0x2);
    
    if (result < 0)
    {
        result = -result;
    }
    
    if (result >= 9)
    {
        if (result < 0)
        {
            result = -8;
        }
        else
        {
            result = 8;
        }
        *(short *)((char *)&stack[2] + 0x2) = result;
    }
    
    func_80016D00((void *)0x800B77C8, (void *)&stack[2], (void *)0x800B77C8);
    func_8003093C((void *)0x800B77C8);
}

// Function 45 - s11d_rope_800C7138

void s11d_rope_800C7138(void *work, int arg1)
{
    unsigned int flags;
    unsigned int mask;
    unsigned short value;
    void *ptr;
    unsigned short check;
    int result;
    int f40_val;
    int ed0_val;
    int ee4_val;
    int div_result;
    int remainder;
    short calc;
    
    if (arg1 == 0)
    {
        goto label_continue;
    }
    
    flags = *(unsigned int *)((char *)work + 0xF74);
    flags |= 0x10000;
    *(unsigned int *)((char *)work + 0xF74) = flags;
    
    flags = *(unsigned int *)((char *)work + 0xF70);
    mask = 0xFF00;
    flags &= mask;
    flags |= 0x20;
    
    value = *(unsigned short *)((char *)work + 0xAA);
    *(unsigned int *)((char *)work + 0xF70) = flags;
    
    if (value != 16)
    {
        func_80034CD4((char *)work + 0x9C, (void *)arg1, 0, 4);
    }
    
    *(unsigned short *)((char *)work + 0xF44) = 0;
    
label_continue:
    result = func_800C4DE0(work);
    
    if (result != 0)
    {
        *(int *)((char *)work + 0xEAC) = 0x800C766C;
        return;
    }
    
    result = func_800C52F0(work);
    
    if (result != 0)
    {
        *(int *)((char *)work + 0xEAC) = 0x800C6F28;
        return;
    }
    
    flags = *(unsigned int *)((char *)work + 0xF74);
    check = flags & 0x1000;
    
    if (check != 0)
    {
        check = 0;
    }
    else
    {
        ptr = *(void **)((char *)work + 0xEA8);
        value = *(unsigned short *)ptr;
        check = value & 0x1000;
        check = (check != 0) ? 1 : 0;
    }
    
    if (check == 0)
    {
        *(int *)((char *)work + 0xEAC) = 0x800C6CD4;
        return;
    }
    
    ptr = *(void **)((char *)work + 0xEA8);
    value = *(unsigned short *)ptr;
    check = value & 0x20;
    
    if (check == 0)
    {
        flags = *(unsigned int *)((char *)work + 0xF74);
        check = flags & 0x2000;
        
        if (check != 0)
        {
            func_800329C4((char *)work + 0x20, 178, 1);
            func_800C650C();
            *(int *)((char *)work + 0xEAC) = 0x800C6834;
            return;
        }
        
        *(int *)((char *)work + 0xEAC) = 0x800C7530;
        *(int *)((char *)work + 0xEB0) = 0;
        *(unsigned short *)((char *)work + 0xEBE) = 0;
        *(unsigned short *)((char *)work + 0xEBC) = 0;
        return;
    }
    
    f40_val = *(int *)((char *)work + 0xF40);
    ed0_val = *(int *)((char *)work + 0xED0);
    ee4_val = *(int *)((char *)work + 0xEE4);
    
    if (f40_val < 10001)
    {
        func_80092508(work);
        
        div_result = ed0_val / 12;
        remainder = ed0_val % 12;
        
        div_result = ee4_val / remainder;
        remainder = ee4_val % remainder;
        
        if (remainder < 0)
        {
            remainder += 4095;
        }
        
        calc = *(short *)((char *)work + 0x64);
        remainder >>= 12;
        calc += remainder;
        
        func_800925D8(work);
        
        *(short *)((char *)work + 0x64) = calc;
        
        div_result = 12 / ee4_val;
        remainder = 12 % ee4_val;
        
        if (remainder < 0)
        {
            remainder += 4095;
        }
        
        calc = *(short *)((char *)work + 0x66);
        remainder >>= 12;
        calc += remainder;
        *(short *)((char *)work + 0x66) = calc;
    }
    
    value = *(unsigned short *)((char *)work + 0x68);
    value -= 108;
    *(unsigned short *)((char *)work + 0x68) = value;
}

void s11d_rope_800C6264(void *work)
{
    int value;
    int check;
    int direction;
    unsigned int flags;
    
    value = *(int *)((char *)work + 0x1C);
    
    if (value >= 0)
    {
        check = *(int *)((char *)work + 0x14);
        
        if (check >= 0)
        {
            direction = 1;
        }
        else
        {
            direction = -1;
        }
        
        *(int *)((char *)work + 0x8) = direction;
        *(int *)((char *)work + 0xEC8) = 0x18;
        value = *(int *)((char *)work + 0x1C);
        *(int *)((char *)work + 0x4) = value;
        *(int *)((char *)work + 0xF60) = -8;
        
        flags = *(unsigned int *)((char *)work + 0xF74);
        flags |= 0x100;
        *(unsigned int *)((char *)work + 0xF74) = flags;
        
        flags &= 0x1000;
        
        if (flags != 0)
        {
            *(int *)((char *)work + 0xF64) = -8;
        }
    }
}

void s11d_rope_800C4274(void *work)
{
    void *ptr1;
    void *ptr2;
    unsigned int flags;
    unsigned short value;
    unsigned short stack[4];
    
    ptr1 = (char *)work + 0x20;
    ptr2 = (char *)work + 0x28;
    
    func_80071BC8C(ptr1, ptr2);
    
    flags = *(unsigned int *)((char *)work + 0xF70);
    
    if ((flags & 0x80) != 0)
    {
        ptr2 = (char *)work + 0xF58;
        
        stack[2] = 0;
        stack[0] = 0;
        value = *(unsigned short *)((char *)work + 0x6E);
        stack[1] = value;
        
        func_800269A0(ptr2, (void *)&stack[0], 3);
        func_80071BC8C(ptr1, ptr2);
    }
}

void s11d_rope_800C44F0(void *work)
{
    int f78_value;
    unsigned short global_value;
    void *ptr;
    unsigned int flags;
    
    f78_value = *(int *)((char *)work + 0xF78);
    
    if (f78_value > 0)
    {
        global_value = *(unsigned short *)0x800B780A;
        
        if (global_value == 0)
        {
            f78_value--;
            *(int *)((char *)work + 0xF78) = f78_value;
            
            if (f78_value == 0)
            {
                ptr = *(void **)((char *)work + 0x9C);
                flags = *(unsigned int *)((char *)ptr + 0x28);
                flags &= 0xFFFFFF7F;
                *(unsigned int *)((char *)ptr + 0x28) = flags;
            }
        }
        else if (global_value == 1)
        {
            f78_value++;
            *(int *)((char *)work + 0xF78) = f78_value;
            
            if (f78_value == 1)
            {
                ptr = *(void **)((char *)work + 0x9C);
                flags = *(unsigned int *)((char *)ptr + 0x28);
                flags |= 0x80;
                *(unsigned int *)((char *)ptr + 0x28) = flags;
            }
        }
    }
}

void s11d_rope_800C4574(void *work)
{
    unsigned int flags;
    void *ea8_ptr;
    unsigned short check;
    unsigned short value;
    unsigned char *ptr;
    int i;
    unsigned char byte;
    unsigned int test;
    
    flags = *(unsigned int *)((char *)work + 0xF74);
    flags &= 0xFFFF7FFF;
    *(unsigned int *)((char *)work + 0xF74) = flags;
    
    ea8_ptr = *(void **)((char *)work + 0xEA8);
    check = *(unsigned short *)((char *)ea8_ptr + 0xA);
    
    if (check != 0)
    {
        value = *(unsigned short *)((char *)ea8_ptr + 0x0);
        
        if ((value & 0xF000) != 0)
        {
            ptr = (unsigned char *)((char *)ea8_ptr + 0xC);
            i = 0;
            
            while (i < 4)
            {
                byte = *ptr;
                test = byte - 0xC0;
                test &= 0xFF;
                
                if (test < 0x81)
                {
                    flags = *(unsigned int *)((char *)work + 0xF74);
                    flags |= 0x8000;
                    *(unsigned int *)((char *)work + 0xF74) = flags;
                    return;
                }
                
                i++;
                ptr++;
            }
        }
    }
}

void s11d_rope_800C8C04(void *work)
{
    void *ptr1;
    void *ptr2;
    unsigned short value;
    
    func_800C5538();
    
    ptr1 = (char *)work + 0xEC8;
    ptr2 = (char *)work + 0xF04;
    
    *(int *)((char *)ptr1 + 0x18) = 0;
    *(int *)((char *)ptr1 + 0x14) = 0;
    *(int *)((char *)ptr2 + 0x18) = 0;
    *(int *)((char *)ptr2 + 0x14) = 0;
    *(int *)((char *)ptr1 + 0xC) = 0x18;
    *(int *)((char *)ptr2 + 0xC) = 0x40;
    
    value = *(unsigned short *)((char *)work + 0xF94);
    *(int *)((char *)ptr1 + 0x30) = value;
    
    value = *(unsigned short *)((char *)work + 0xF98);
    *(int *)((char *)ptr2 + 0x30) = value;
    
    *(void **)((char *)ptr1 + 0x34) = (char *)work + 0x20;
    *(void **)((char *)ptr2 + 0x34) = (char *)work + 0x24;
    *(void **)((char *)ptr1 + 0x38) = (char *)work + 0x70;
    *(void **)((char *)ptr2 + 0x38) = (char *)work + 0x6C;
}

int s11d_rope_800C9500(void *arg0, void *arg1)
{
    void *result;
    int status;
    int ret;
    
    result = func_800150E4(5, 0x1098);
    
    if (result != 0)
    {
        func_8001514C(result, (void *)0x800D8364, (void *)0x800D868C, (void *)0x800D1DC4);
        status = func_800C91AC(result, arg1, arg0);
        
        if (status < 0)
        {
            func_800151C8(result);
            ret = 0;
        }
        else
        {
            ret = result;
        }
    }
    else
    {
        ret = 0;
    }
    
    return ret;
}

void s11d_rope_800C7B2C(void *work, int arg1)
{
    unsigned int flags;
    unsigned short aa_value;
    unsigned short ebc_value;
    unsigned short b6_value;
    int result;
    
    if (arg1 != 0)
    {
        flags = *(unsigned int *)((char *)work + 0xF74);
        flags &= 0xFF9FFFFF;
        flags &= 0xFFFEFFFF;
        *(unsigned int *)((char *)work + 0xF74) = flags;
        
        func_80032A1C((char *)work + 0x20, 0x19, 1);
        
        flags = *(unsigned int *)((char *)work + 0xF70);
        aa_value = *(unsigned short *)((char *)work + 0xAA);
        flags |= 0x100;
        *(unsigned int *)((char *)work + 0xF70) = flags;
        
        if (aa_value != 9)
        {
            func_80034CD4((char *)work + 0x9C, 0, 0, 4);
        }
        
        *(unsigned short *)((char *)work + 0x6E) = 0x800;
        func_800C4898(work, 0);
    }
    
    flags = *(unsigned int *)((char *)work + 0xF74);
    
    if ((flags & 0x2000) != 0)
    {
        ebc_value = *(unsigned short *)((char *)work + 0xEBC);
        
        if (ebc_value == 0)
        {
            *(unsigned short *)((char *)work + 0xEBC) = 1;
        }
        
        ebc_value = *(unsigned short *)((char *)work + 0xEBC);
        
        if (ebc_value == 1)
        {
            *(unsigned short *)((char *)work + 0xEBC) = 2;
            flags = *(unsigned int *)((char *)work + 0xF74);
            flags |= 0x10000;
            *(unsigned int *)((char *)work + 0xF74) = flags;
            
            b6_value = *(unsigned short *)((char *)work + 0x66);
            b6_value -= 0x80;
            *(unsigned short *)((char *)work + 0x66) = b6_value;
        }
    }
    
    flags = *(unsigned int *)((char *)work + 0xF74);
    
    if ((flags & 0x2000) != 0)
    {
        func_800C486C(work);
        func_80032A1C((char *)work + 0x20, 0xB2, 1);
        
        flags = *(unsigned int *)((char *)work + 0xF70);
        flags &= 0xFFFFFEFF;
        *(unsigned int *)((char *)work + 0xF70) = flags;
        
        func_800C650C();
        *(int *)((char *)work + 0xEAC) = 0x800C6834;
        return;
    }
    
    result = func_800C5298(work);
    
    if (result != 0)
    {
        func_800C486C(work);
        func_80032A1C((char *)work + 0x20, 0xB7, 1);
        
        flags = *(unsigned int *)((char *)work + 0xF70);
        flags &= 0xFFFFFEFF;
        *(unsigned int *)((char *)work + 0xF70) = flags;
        
        *(int *)((char *)work + 0xEAC) = 0x800C6B18;
        *(int *)((char *)work + 0xEB0) = 0;
        *(unsigned short *)((char *)work + 0xEBE) = 0;
        *(unsigned short *)((char *)work + 0xEBC) = 0;
        return;
    }
    
    result = func_800C4DE0(work);
    
    if (result != 0)
    {
        func_800C486C(work);
        *(int *)((char *)work + 0xEAC) = 0x800C766C;
        return;
    }
    
    b6_value = *(unsigned short *)((char *)work + 0xB6);
    
    if (b6_value != 0)
    {
        func_800C486C(work);
        *(int *)((char *)work + 0xEAC) = 0x800C7530;
        *(int *)((char *)work + 0xEB0) = 0;
        *(unsigned short *)((char *)work + 0xEBE) = 0;
        *(unsigned short *)((char *)work + 0xEBC) = 0;
        
        flags = *(unsigned int *)((char *)work + 0xF70);
        flags &= 0xFFFFFEFF;
        *(unsigned int *)((char *)work + 0xF70) = flags;
    }
}

void s11d_rope_800C6F28(void *work, int arg1)
{
    int eb4_value;
    unsigned int flags;
    int direction;
    unsigned short aa_value;
    void *ea8_ptr;
    unsigned short ea8_flags;
    int result;
    unsigned short value;
    short temp;
    short calc;
    short check1;
    short check2;
    short stack_val;
    
    eb4_value = *(int *)((char *)work + 0xEB4);
    
    if (arg1 != 0)
    {
        flags = *(unsigned int *)((char *)work + 0xF74);
        flags |= 0x10000;
        *(unsigned int *)((char *)work + 0xF74) = flags;
        
        flags = *(unsigned int *)((char *)work + 0xF70);
        flags &= 0xFF00;
        flags |= 0x10;
        *(unsigned int *)((char *)work + 0xF70) = flags;
        
        if (eb4_value == 1)
        {
            direction = 3;
        }
        else
        {
            direction = 2;
        }
        
        aa_value = *(unsigned short *)((char *)work + 0xAA);
        
        if (aa_value != direction)
        {
            func_80034CD4((char *)work + 0x9C, 0, 0, 4);
        }
        
        *(unsigned short *)((char *)work + 0xF44) = 0x1C2;
    }
    
    result = func_800C4DE0(work);
    
    if (result != 0)
    {
        *(int *)((char *)work + 0xEAC) = 0x800C766C;
        return;
    }
    
    result = func_800C52F0(work);
    
    if (result == 0)
    {
        flags = *(unsigned int *)((char *)work + 0xF74);
        
        if ((flags & 0x2000) != 0)
        {
            func_80032A1C((char *)work + 0x20, 0xB2, 1);
            func_800C650C();
            *(int *)((char *)work + 0xEAC) = 0x800C6834;
            return;
        }
        
        *(int *)((char *)work + 0xEAC) = 0x800C6CD4;
        return;
    }
    
    eb4_value = *(int *)((char *)work + 0xEB4);
    
    if (eb4_value == 1)
    {
        direction = 3;
    }
    else
    {
        direction = 2;
    }
    
    aa_value = *(unsigned short *)((char *)work + 0xAA);
    
    if (aa_value != direction)
    {
        func_80034CD4((char *)work + 0x9C, 0, 0, 4);
    }
    
    ea8_ptr = *(void **)((char *)work + 0xEA8);
    ea8_flags = *(unsigned short *)((char *)ea8_ptr + 0x0);
    
    if ((ea8_flags & 0x20) != 0)
    {
        *(int *)((char *)work + 0xEAC) = 0x800C7530;
        *(int *)((char *)work + 0xEB0) = 0;
        *(unsigned short *)((char *)work + 0xEBE) = 0;
        *(unsigned short *)((char *)work + 0xEBC) = 0;
        return;
    }
    
    flags = *(unsigned int *)((char *)work + 0xF74);
    
    if ((flags & 0x1000) == 0)
    {
        value = *(unsigned short *)((char *)work + 0x20);
        temp = eb4_value << 2;
        calc = value + temp;
        stack_val = calc;
        
        calc = calc << 10;
        calc = calc >> 10;
        
        check1 = *(short *)((char *)work + 0xF84);
        
        if (calc < check1)
        {
            result = 1;
        }
        else
        {
            check2 = *(short *)((char *)work + 0xF8C);
            
            if (calc < check2)
            {
                result = 0;
            }
            else
            {
                result = 1;
            }
        }
        
        if (result != 0)
        {
            value = *(unsigned short *)((char *)work + 0x64);
            value += temp;
            *(unsigned short *)((char *)work + 0x64) = value;
            
            value = *(unsigned short *)((char *)work + 0x68);
            value -= 0x6C;
            *(unsigned short *)((char *)work + 0x68) = value;
            
            ea8_ptr = *(void **)((char *)work + 0xEA8);
            ea8_flags = *(unsigned short *)((char *)ea8_ptr + 0x0);
            
            if ((ea8_flags & 0x1000) != 0)
            {
                value = *(unsigned short *)((char *)work + 0x66);
                value += 0xC;
                *(unsigned short *)((char *)work + 0x66) = value;
            }
            else if ((ea8_flags & 0x4000) != 0)
            {
                value = *(unsigned short *)((char *)work + 0x66);
                value -= 0xC;
                *(unsigned short *)((char *)work + 0x66) = value;
            }
        }
    }
}

void s11d_rope_800C7320(void *work, int arg1)
{
    unsigned int flags;
    unsigned short aa_value;
    void *ea8_ptr;
    unsigned short ea8_flags;
    int result;
    int check;
    void *ptr_804;
    int ee4_value;
    int ed0_value;
    int calc1;
    int calc2;
    int div_result;
    int rem_result;
    short value;
    short temp;
    
    if (arg1 != 0)
    {
        flags = *(unsigned int *)((char *)work + 0xF74);
        flags |= 0x10000;
        *(unsigned int *)((char *)work + 0xF74) = flags;
        
        flags = *(unsigned int *)((char *)work + 0xF70);
        flags &= 0xFF00;
        aa_value = *(unsigned short *)((char *)work + 0xAA);
        flags |= 0x20;
        *(unsigned int *)((char *)work + 0xF70) = flags;
        
        if (aa_value != 0x11)
        {
            func_80034CD4((char *)work + 0x9C, 0, 0, 4);
        }
        
        *(unsigned short *)((char *)work + 0xF44) = 0;
    }
    
    result = func_800C4DE0(work);
    
    if (result != 0)
    {
        *(int *)((char *)work + 0xEAC) = 0x800C766C;
        return;
    }
    
    result = func_800C52F0(work);
    
    if (result != 0)
    {
        *(int *)((char *)work + 0xEAC) = 0x800C6F28;
        return;
    }
    
    flags = *(unsigned int *)((char *)work + 0xF74);
    
    if ((flags & 0x2000) != 0)
    {
        ea8_ptr = *(void **)((char *)work + 0xEA8);
        ea8_flags = *(unsigned short *)((char *)ea8_ptr + 0x0);
        check = (ea8_flags & 0x4000) != 0 ? 1 : 0;
    }
    else
    {
        check = 0;
    }
    
    if (check == 0)
    {
        flags = *(unsigned int *)((char *)work + 0xF74);
        
        if ((flags & 0x2000) != 0)
        {
            func_80032A1C((char *)work + 0x20, 0xB2, 1);
            func_800C650C();
            *(int *)((char *)work + 0xEAC) = 0x800C6834;
            return;
        }
        
        *(int *)((char *)work + 0xEAC) = 0x800C6CD4;
        return;
    }
    
    ea8_ptr = *(void **)((char *)work + 0xEA8);
    ea8_flags = *(unsigned short *)((char *)ea8_ptr + 0x0);
    
    if ((ea8_flags & 0x20) != 0)
    {
        result = func_800C4DE0(work);
        
        if (result != 0)
        {
            ptr_804 = *(void **)((char *)work + 0x804);
            *(unsigned short *)((char *)ptr_804 + 0x12) = 0x384;
            *(int *)((char *)work + 0xEAC) = 0x800C766C;
            return;
        }
        
        *(int *)((char *)work + 0xEAC) = 0x800C7530;
        *(int *)((char *)work + 0xEB0) = 0;
        *(unsigned short *)((char *)work + 0xEBE) = 0;
        *(unsigned short *)((char *)work + 0xEBC) = 0;
        return;
    }
    
    ee4_value = *(int *)((char *)work + 0xEE4);
    ed0_value = *(int *)((char *)work + 0xED0);
    
    calc1 = ee4_value >> 10;
    calc1 += ed0_value;
    calc1 = calc1 << 6;
    
    func_80092508(work);
    
    div_result = calc1 / 12;
    rem_result = calc1 % 12;
    
    div_result = div_result * ed0_value;
    
    if (rem_result < 0)
    {
        div_result = div_result + 0xFFF;
    }
    
    value = *(unsigned short *)((char *)work + 0x64);
    div_result = div_result >> 12;
    value += div_result;
    
    func_80092598(ed0_value, work);
    
    div_result = ed0_value / 12;
    
    if (div_result < 0)
    {
        div_result += 0xFFF;
    }
    
    div_result = div_result >> 12;
    temp = *(unsigned short *)((char *)work + 0x66);
    value = *(unsigned short *)((char *)work + 0x68);
    temp -= div_result;
    value -= 0x6C;
    *(unsigned short *)((char *)work + 0x64) = value;
    *(unsigned short *)((char *)work + 0x66) = temp;
    *(unsigned short *)((char *)work + 0x68) = value;
}

void s11d_rope_800C6CD4(void *work, int arg1)
{
    unsigned short aa_value;
    unsigned int flags;
    void *ptr_804;
    int result;
    int check1;
    int check2;
    void *ea8_ptr;
    unsigned short ea8_flags;
    unsigned short ebe_value;
    unsigned short ebc_value;
    unsigned short value;
    
    if (arg1 != 0)
    {
        aa_value = *(unsigned short *)((char *)work + 0xAA);
        
        if (aa_value != 8)
        {
            func_80034CD4((char *)work + 0x9C, 0, 0, 4);
        }
        
        flags = *(unsigned int *)((char *)work + 0xF74);
        flags |= 0x10000;
        ptr_804 = *(void **)((char *)work + 0x804);
        *(int *)((char *)work + 0xEB8) = 0;
        *(int *)((char *)work + 0xEB4) = 0;
        *(unsigned int *)((char *)work + 0xF74) = flags;
        *(unsigned short *)((char *)ptr_804 + 0x12) = 0xC8;
        *(unsigned short *)((char *)work + 0x6E) = 0x800;
        *(unsigned short *)((char *)work + 0xEBC) = 4;
        *(unsigned short *)((char *)work + 0xF44) = 0x1C2;
    }
    
    result = func_800C4DE0(work);
    
    if (result != 0)
    {
        ptr_804 = *(void **)((char *)work + 0x804);
        *(unsigned short *)((char *)ptr_804 + 0x12) = 0x384;
        *(int *)((char *)work + 0xEAC) = 0x800C766C;
        *(int *)((char *)work + 0xEB0) = 0;
        *(unsigned short *)((char *)work + 0xEBE) = 0;
        *(unsigned short *)((char *)work + 0xEBC) = 0;
        
        flags = *(unsigned int *)((char *)work + 0xF74);
        flags &= 0xFFBFFFFF;
        *(unsigned int *)((char *)work + 0xF74) = flags;
        return;
    }
    
    flags = *(unsigned int *)((char *)work + 0xF74);
    
    if ((flags & 0x1000) != 0)
    {
        ea8_ptr = *(void **)((char *)work + 0xEA8);
        ea8_flags = *(unsigned short *)((char *)ea8_ptr + 0x0);
        check1 = (ea8_flags & 0x1000) != 0 ? 1 : 0;
    }
    else
    {
        check1 = 0;
    }
    
    if (check1 != 0)
    {
        ptr_804 = *(void **)((char *)work + 0x804);
        *(unsigned short *)((char *)ptr_804 + 0x12) = 0x384;
        *(int *)((char *)work + 0xEAC) = 0x800C7138;
        return;
    }
    
    flags = *(unsigned int *)((char *)work + 0xF74);
    
    if ((flags & 0x2000) != 0)
    {
        ea8_ptr = *(void **)((char *)work + 0xEA8);
        ea8_flags = *(unsigned short *)((char *)ea8_ptr + 0x0);
        check2 = (ea8_flags & 0x4000) != 0 ? 1 : 0;
    }
    else
    {
        check2 = 0;
    }
    
    if (check2 != 0)
    {
        ptr_804 = *(void **)((char *)work + 0x804);
        *(unsigned short *)((char *)ptr_804 + 0x12) = 0x384;
        *(int *)((char *)work + 0xEAC) = 0x800C7320;
        return;
    }
    
    result = func_800C52F0(work);
    
    if (result != 0)
    {
        ptr_804 = *(void **)((char *)work + 0x804);
        *(unsigned short *)((char *)ptr_804 + 0x12) = 0x384;
        *(int *)((char *)work + 0xEAC) = 0x800C6F28;
        *(int *)((char *)work + 0xEB0) = 0;
        *(unsigned short *)((char *)work + 0xEBE) = 0;
        *(unsigned short *)((char *)work + 0xEBC) = 0;
        return;
    }
    
    ea8_ptr = *(void **)((char *)work + 0xEA8);
    ea8_flags = *(unsigned short *)((char *)ea8_ptr + 0x0);
    
    if ((ea8_flags & 0x20) != 0)
    {
        *(int *)((char *)work + 0xF68) = -4;
        *(unsigned short *)((char *)work + 0xEBE) = 1;
    }
    
    ebe_value = *(unsigned short *)((char *)work + 0xEBE);
    
    if (ebe_value == 1)
    {
        ebc_value = *(unsigned short *)((char *)work + 0xEBC);
        ebc_value--;
        *(unsigned short *)((char *)work + 0xEBC) = ebc_value;
        ebc_value = ebc_value << 16;
        
        if (ebc_value == 0)
        {
            ptr_804 = *(void **)((char *)work + 0x804);
            *(unsigned short *)((char *)ptr_804 + 0x12) = 0x384;
            
            flags = *(unsigned int *)((char *)work + 0xF74);
            
            if ((flags & 0x2000) != 0)
            {
                func_80032A1C((char *)work + 0x20, 0xB2, 1);
                func_800C650C();
                *(int *)((char *)work + 0xEAC) = 0x800C6834;
                return;
            }
            
            *(int *)((char *)work + 0xEAC) = 0x800C7530;
            *(int *)((char *)work + 0xEB0) = 0;
            *(unsigned short *)((char *)work + 0xEBE) = 0;
            *(unsigned short *)((char *)work + 0xEBC) = 0;
        }
    }
    
    value = *(unsigned short *)((char *)work + 0x68);
    value -= 0x6C;
    *(unsigned short *)((char *)work + 0x68) = value;
}

int s11d_rope_800C8C88(void *work)
{
    void *allocation;
    void *rope_data;
    short *init_ptr;
    int i;
    int j;
    int k;
    void *segment_ptr;
    int segment_count;
    unsigned char val1;
    unsigned char val2;
    unsigned char sum;
    int calc;
    short value;
    short *array_ptr;
    
    allocation = func_8001BABC(0x12, 1, 0, (void *)((char *)work + 0x7E0), 0);
    
    if (allocation == 0)
    {
        func_8001827C(allocation);
        value = *(short *)0x800BB9B0;
        *(short *)((char *)work + 0x28) = value;
        rope_data = work;
    }
    else
    {
        return -1;
    }
    
    if (rope_data == 0)
    {
        return -1;
    }
    
    *(short *)((char *)rope_data + 0x2E) = 0xFA;
    func_80016CCC((void *)0x800D1DAC);
    
    rope_data = func_8001D830(rope_data);
    
    if (rope_data == 0)
    {
        return -1;
    }
    
    for (i = 0; i < 2; i++)
    {
        segment_ptr = (char *)rope_data + 0x40;
        init_ptr = (short *)((char *)work + 0x7E0);
        segment_count = 0;
        
        for (j = 0; j < 0x48; j++)
        {
            segment_ptr = (char *)segment_ptr + 0xE;
            
            *(unsigned char *)((char *)segment_ptr - 0xB) = 9;
            *(unsigned char *)((char *)segment_ptr - 0x7) = 0x2C;
            
            func_80092458(segment_ptr, 1);
            
            *(unsigned char *)((char *)segment_ptr - 0xA) = 0x48;
            *(unsigned char *)((char *)segment_ptr - 0x9) = 0x48;
            *(unsigned char *)((char *)segment_ptr - 0x8) = 0x48;
            
            val1 = *(unsigned char *)((char *)init_ptr + 0x8);
            val2 = *(unsigned char *)((char *)init_ptr + 0xA);
            sum = val1 + val2;
            
            *(unsigned char *)((char *)segment_ptr + 0xE) = sum;
            *(unsigned char *)((char *)segment_ptr + 0x2) = sum;
            
            val2 = *(unsigned char *)((char *)init_ptr + 0xB);
            val2++;
            
            calc = val2 * 0x48;
            segment_count++;
            calc = calc * segment_count;
            
            val1 = *(unsigned char *)((char *)init_ptr + 0x9);
            val1 += calc;
            
            *(unsigned char *)((char *)segment_ptr + 0x16) = val1;
            *(unsigned char *)((char *)segment_ptr + 0x6) = val1;
            
            val1 = (segment_count + calc - 1);
            
            *(unsigned char *)((char *)segment_ptr + 0x17) = val1;
            *(unsigned char *)((char *)segment_ptr + 0xF) = val1;
            
            value = *(short *)((char *)init_ptr + 0x4);
            *(short *)((char *)segment_ptr + 0x8) = value;
            
            value = *(short *)((char *)init_ptr + 0x6);
            segment_ptr = (char *)segment_ptr + 0x28;
            *(short *)((char *)segment_ptr - 0x28) = value;
        }
        
        init_ptr = (short *)((char *)init_ptr + 4);
    }
    
    array_ptr = (short *)((char *)work + 0x7E0);
    
    for (i = 0; i < 3; i++)
    {
        *(short *)((char *)array_ptr + 0) = 0xFE70;
        *(short *)((char *)array_ptr - 0x1A) = 0xFD44;
        *(short *)((char *)array_ptr - 0x18) = 0;
        *(short *)((char *)array_ptr - 0x14) = 0x190;
        *(short *)((char *)array_ptr - 0x12) = 0xFD44;
        *(short *)((char *)array_ptr - 0x10) = 0;
        *(short *)((char *)array_ptr - 0xC) = 0xFE70;
        *(short *)((char *)array_ptr - 0xA) = 0x5DC;
        *(short *)((char *)array_ptr - 0x8) = 0;
        *(short *)((char *)array_ptr - 0x4) = 0x190;
        *(short *)((char *)array_ptr - 0x2) = 0x5DC;
        *(short *)((char *)array_ptr + 0x0) = 0;
        
        array_ptr = (short *)((char *)array_ptr + 0x20);
    }
    
    for (i = 0; i < 3; i++)
    {
        for (j = 0; j < 3; j++)
        {
            init_ptr = (short *)((char *)rope_data + (i * 6));
            
            if (j == init_ptr)
            {
                *(short *)((char *)work + 0x1000) = 0x1000;
            }
            else
            {
                *(short *)((char *)work + 0x1000) = 0;
            }
        }
    }
    
    *(void **)((char *)work + 0x7DC) = rope_data;
    return 0;
}

void s11d_rope_800C4B78(void *work)
{
    unsigned int flags;
    int f60_value;
    unsigned char flag_byte;
    int f64_value;
    int f68_value;
    void *ptr_ec8;
    void *ptr_f04;
    void *ptr_70;
    short value1;
    short value2;
    short diff;
    short f88_value;
    short f96_value;
    void *ptr_34;
    void *ptr_30;
    short val1;
    short val2;
    int result = 0;
    int result1;
    int result2;
    int temp;
    void *ptr_38;
    int calc1;
    int calc2;
    int calc3;
    
    flags = *(unsigned int *)((char *)work + 0xF74);
    flags &= 0xFFEF8FFF;
    *(unsigned int *)((char *)work + 0xF74) = flags;
    
    f60_value = *(int *)((char *)work + 0xF60);
    
    if (f60_value < 0)
    {
        f60_value++;
        *(int *)((char *)work + 0xF60) = f60_value;
    }
    
    flag_byte = *(unsigned char *)((char *)work + 0x57);
    
    if ((flag_byte & 2) != 0)
    {
        f60_value = *(int *)((char *)work + 0xF60);
        
        if (f60_value == 0)
        {
            flags = *(unsigned int *)((char *)work + 0xF74);
            flags |= 0x2000;
            *(unsigned int *)((char *)work + 0xF74) = flags;
        }
    }
    
    f64_value = *(int *)((char *)work + 0xF64);
    
    if (f64_value < 0)
    {
        f64_value++;
        *(int *)((char *)work + 0xF64) = f64_value;
    }
    
    flag_byte = *(unsigned char *)((char *)work + 0x57);
    
    if ((flag_byte & 2) != 0)
    {
        f64_value = *(int *)((char *)work + 0xF64);
        
        if (f64_value == 0)
        {
            flags = *(unsigned int *)((char *)work + 0xF74);
            flags |= 0x1000;
            *(unsigned int *)((char *)work + 0xF74) = flags;
        }
    }
    
    f68_value = *(int *)((char *)work + 0xF68);
    
    if (f68_value < 0)
    {
        f68_value++;
        *(int *)((char *)work + 0xF68) = f68_value;
    }
    
    flag_byte = *(unsigned char *)((char *)work + 0x58);
    
    if (flag_byte != 0)
    {
        f68_value = *(int *)((char *)work + 0xF68);
        
        if (f68_value == 0)
        {
            flags = *(unsigned int *)((char *)work + 0xF74);
            ptr_ec8 = (char *)work + 0xEC8;
            ptr_f04 = (char *)work + 0xF04;
            flags |= 0x4000;
            *(unsigned int *)((char *)work + 0xF74) = flags;
            
            ptr_70 = *(void **)((char *)work + 0x70);
            value1 = *(short *)((char *)work + 0x4);
            value2 = *(short *)((char *)ptr_70 + 0x2);
            
            if (value1 >= value2)
            {
                f88_value = *(short *)((char *)work + 0xF88);
                
                if (value1 < f88_value)
                {
                    flags = *(unsigned int *)((char *)work + 0xF74);
                    flags |= 0x100000;
                    *(unsigned int *)((char *)work + 0xF74) = flags;
                }
            }
        }
        else
        {
            ptr_ec8 = (char *)work + 0xEC8;
            ptr_f04 = (char *)work + 0xF04;
        }
    }
    else
    {
        ptr_ec8 = (char *)work + 0xEC8;
        ptr_f04 = (char *)work + 0xF04;
    }
    
    flags = *(unsigned int *)((char *)work + 0xF74);
    f96_value = *(short *)((char *)work + 0xF96);
    flags |= 0x30;
    *(unsigned int *)((char *)work + 0xF74) = flags;
    
    value1 = *(short *)((char *)work + 0x2);
    ptr_34 = *(void **)((char *)ptr_ec8 + 0x34);
    diff = value1 - f96_value;
    val1 = *(short *)((char *)ptr_34 + 0x0);
    ptr_30 = *(void **)((char *)ptr_ec8 + 0x30);
    val2 = val1 - diff;
    
    func_80094308(ptr_30, ptr_ec8, val2);
    
    flags = *(unsigned int *)((char *)work + 0xF74);
    result1 = flags;
    
    if ((result1 & 0x4000) == 0)
    {
        flags &= 0xFFFFFFDF;
        *(unsigned int *)((char *)work + 0xF74) = flags;
    }
    
    ptr_38 = *(void **)((char *)ptr_ec8 + 0x38);
    temp = -result1;
    *(int *)((char *)ptr_ec8 + 0x1C) = temp;
    *(int *)((char *)ptr_ec8 + 0x14) = result2;
    *(int *)((char *)ptr_ec8 + 0x18) = result1;
    *(short *)((char *)ptr_38 + 0x0) = diff;
    
    ptr_34 = *(void **)((char *)ptr_f04 + 0x34);
    val1 = *(short *)((char *)ptr_34 + 0x0);
    ptr_30 = *(void **)((char *)ptr_f04 + 0x30);
    val2 = val1 - diff;
    
    func_80094308(ptr_30, ptr_f04, val2);
    
    flags = *(unsigned int *)((char *)work + 0xF74);
    result1 = flags;
    
    if ((result1 & 0x4000) == 0)
    {
        flags &= 0xFFFFFFEF;
        *(unsigned int *)((char *)work + 0xF74) = flags;
    }
    
    calc1 = result2 >> 3;
    calc1 = calc1 * result2;
    calc1 = calc1 >> 10;
    calc2 = result1 >> 3;
    calc2 = calc2 * result1;
    calc2 = calc2 >> 10;
    calc3 = result >> 3;
    calc3 = calc3 * result;
    
    ptr_38 = *(void **)((char *)ptr_f04 + 0x38);
    *(int *)((char *)ptr_f04 + 0x1C) = temp;
    *(int *)((char *)ptr_f04 + 0x14) = result;
    *(int *)((char *)ptr_f04 + 0x18) = result1;
    *(short *)((char *)ptr_38 + 0x0) = temp;
    
    calc3 = calc3 >> 10;
    calc3 = calc1 + calc3;
    calc3 = calc2 + calc3;
    
    func_80092708(calc3);
    
    calc3 = calc3 << 1;
    *(int *)((char *)work + 0xF40) = calc3;
}

void s11d_rope_800C502C(void *work)
{
    void *ptr_ec8;
    void *ptr_f04;
    unsigned int flags;
    unsigned short aa_value;
    unsigned short ec2_value;
    int direction;
    int calc;
    void *ea8_ptr;
    unsigned short ea8_flags;
    short value;
    
    ptr_ec8 = (char *)work + 0xEC8;
    ptr_f04 = (char *)work + 0xF04;
    
    flags = *(unsigned int *)((char *)work + 0xF74);
    
    if ((flags & 0x10000) != 0)
    {
        flags &= 0xFF7FFFFF;
        *(unsigned int *)((char *)work + 0xF74) = flags;
        *(unsigned short *)((char *)work + 0xEC2) = 0;
    }
    
    flags = *(unsigned int *)((char *)work + 0xF74);
    
    if ((flags & 0x800000) != 0)
    {
        aa_value = *(unsigned short *)((char *)work + 0xAA);
        
        if (aa_value != 0xF)
        {
            func_80034CD4((char *)work + 0x9C, 0, 0, 7);
        }
        
        ec2_value = *(unsigned short *)((char *)work + 0xEC2);
        ec2_value--;
        *(unsigned short *)((char *)work + 0xEC2) = ec2_value;
        ec2_value = ec2_value << 16;
        
        if (ec2_value == 0)
        {
            flags = *(unsigned int *)((char *)work + 0xF74);
            flags &= 0xFF7FFFFF;
            flags |= 0x100;
            *(unsigned int *)((char *)work + 0xF74) = flags;
            
            direction = *(int *)((char *)work + 0x8);
            
            if (direction != 0)
            {
                calc = direction << 2;
                calc = calc + direction;
                calc = calc << 3;
                calc = -calc;
                *(short *)((char *)work + 0x6E) = calc;
            }
        }
    }
    
    flags = *(unsigned int *)((char *)work + 0xF74);
    
    if ((flags & 0x810000) != 0)
    {
        if ((flags & 0x10000) != 0)
        {
            flags &= 0xFFFFF0FF;
            *(unsigned int *)((char *)work + 0xF74) = flags;
            *(int *)((char *)ptr_ec8 + 0x0) = 0;
            *(int *)((char *)ptr_ec8 + 0x8) = 0;
        }
        else
        {
            flags &= 0xFFFFFAFF;
            *(unsigned int *)((char *)work + 0xF74) = flags;
            *(int *)((char *)ptr_ec8 + 0x0) = 0x40;
            *(int *)((char *)ptr_ec8 + 0x8) = 0x40;
        }
    }
    
    flags = *(unsigned int *)((char *)work + 0xF74);
    
    if ((flags & 0x100) == 0)
    {
        func_800C6264(work);
    }
    
    flags = *(unsigned int *)((char *)work + 0xF74);
    
    if ((flags & 0x200) == 0)
    {
        func_800C62E0(work);
    }
    
    flags = *(unsigned int *)((char *)work + 0xF74);
    
    if ((flags & 0x300) != 0)
    {
        aa_value = *(unsigned short *)((char *)work + 0xAA);
        
        if (aa_value == 5)
        {
            // case 5
        }
        else if (aa_value == 7)
        {
            // case 7
        }
        else if (aa_value == 9)
        {
            // case 9
        }
        else if (aa_value == 1)
        {
            func_80034CD4((char *)work + 0x9C, 0, 0, 4);
        }
        
        ea8_ptr = *(void **)((char *)work + 0xEA8);
        ea8_flags = *(unsigned short *)((char *)ea8_ptr + 0x0);
        
        if ((ea8_flags & 0xA000) != 0)
        {
            if ((ea8_flags & 0x8000) == 0)
            {
                value = 0x600;
            }
            else
            {
                value = 0xFA00;
            }
            
            *(short *)((char *)work + 0x6E) = value;
        }
    }
    
    flags = *(unsigned int *)((char *)work + 0xF74);
    
    if ((flags & 0x100) != 0)
    {
        func_800C5584(work, ptr_ec8, 0);
    }
    
    flags = *(unsigned int *)((char *)work + 0xF74);
    
    if ((flags & 0x200) != 0)
    {
        func_800C5584(work, ptr_f04, 1);
    }
    
    flags = *(unsigned int *)((char *)work + 0xF74);
    
    if ((flags & 0x400) != 0)
    {
        *(int *)((char *)ptr_ec8 + 0x8) = 0;
        *(int *)((char *)ptr_ec8 + 0x0) = 0;
        flags = *(unsigned int *)((char *)work + 0xF74);
        flags &= 0xFFFFFBFF;
        *(unsigned int *)((char *)work + 0xF74) = flags;
    }
    
    flags = *(unsigned int *)((char *)work + 0xF74);
    
    if ((flags & 0x800) != 0)
    {
        *(int *)((char *)ptr_f04 + 0x8) = 0x40;
        *(int *)((char *)ptr_f04 + 0x0) = 0x40;
        flags = *(unsigned int *)((char *)work + 0xF74);
        flags &= 0xFFFFF7FF;
        *(unsigned int *)((char *)work + 0xF74) = flags;
    }
}

void s11d_rope_800C7F8C(void *work, int arg1)
{
    unsigned char flag;
    unsigned int flags;
    void *ptr_804;
    unsigned short aa_value;
    short check_value;
    short value1;
    short value2;
    short f84_value;
    short f8C_value;
    int result;
    int eb4_value;
    short calc;
    short temp;
    short diff;
    short stack_values[8];
    
    if (arg1 != 0)
    {
        *(short *)0x800D1F7E = 0x8AD0;
        *(short *)((char *)work + 0x56) = -1;
        
        flag = *(unsigned char *)((char *)work + 0x75);
        flags = *(unsigned int *)((char *)work + 0xF74);
        flag |= 2;
        *(unsigned char *)((char *)work + 0x75) = flag;
        flags |= 0x10000;
        *(unsigned int *)((char *)work + 0xF74) = flags;
        
        flags = *(unsigned int *)((char *)work + 0xF70);
        flags &= 0xFF00;
        
        if ((flags & 0x2000) == 0)
        {
            func_8005D58C((void *)0x800C327C, 1);
            func_8005D58C((void *)0x800C3280, 2);
            func_80032968(0, 0x3F, 0x1A);
            
            flags = *(unsigned int *)((char *)work + 0xF70);
            flags |= 0x2000;
        }
        
        *(unsigned int *)((char *)work + 0xF70) = flags;
        
        ptr_804 = *(void **)((char *)work + 0x804);
        *(short *)((char *)ptr_804 + 0x0) = 0;
        
        aa_value = *(unsigned short *)((char *)work + 0xAA);
        
        if (aa_value != 0xA)
        {
            func_80034CD4((char *)work + 0x9C, 0, 0, 4);
        }
        
        check_value = *(short *)0x800B77E8 + 0x22;
        
        if (check_value != 0)
        {
            *(int *)((char *)work + 0xF78) = 4;
            flags = *(unsigned int *)((char *)work + 0xF70);
            flags &= 0xFFFFEFFF;
            *(unsigned int *)((char *)work + 0xF70) = flags;
            *(short *)(0x800B77E8 + 0x22) = 0;
        }
        
        ptr_804 = *(void **)((char *)work + 0x7DC);
        flags = *(unsigned int *)((char *)ptr_804 + 0x24);
        flags |= 0x100;
        *(unsigned int *)((char *)ptr_804 + 0x24) = flags;
        
        value1 = *(short *)((char *)work + 0xEA0);
        
        if (value1 != 0)
        {
            value1 = *(short *)((char *)work + 0xEA0);
            stack_values[2] = 0x983F;
            stack_values[4] = 2;
            stack_values[1] = 0;
            stack_values[0] = value1;
            
            func_80016504((void *)&stack_values[0]);
        }
    }
    
    value1 = *(short *)((char *)work + 0x20);
    f84_value = *(short *)((char *)work + 0xF84);
    
    if (value1 < f84_value)
    {
        result = 1;
    }
    else
    {
        f8C_value = *(short *)((char *)work + 0xF8C);
        
        if (value1 < f8C_value)
        {
            result = 0;
        }
        else
        {
            result = 1;
        }
    }
    
    if (result != 0)
    {
        eb4_value = *(int *)((char *)work + 0xEB4);
        func_800263E4(eb4_value, 0);
        eb4_value = result;
        *(int *)((char *)work + 0xEB4) = eb4_value;
        value1 = *(short *)((char *)work + 0xEB4);
        *(short *)((char *)work + 0x64) = value1;
    }
    
    flag = *(unsigned char *)((char *)work + 0x77);
    
    if ((flag & 1) != 0)
    {
        *(int *)((char *)work + 0xEAC) = 0x800C7D20;
        *(short *)((char *)work + 0x66) = 0;
        return;
    }
    
    value1 = *(short *)0x800D1F7E;
    value2 = *(short *)((char *)work + 0x22);
    
    if (value1 < value2)
    {
        *(int *)((char *)work + 0xEAC) = 0x800D8200;
        *(int *)((char *)work + 0xEB0) = 0;
        *(unsigned short *)((char *)work + 0xEBE) = 0;
        *(unsigned short *)((char *)work + 0xEBC) = 0;
        return;
    }
    
    value1 = *(short *)((char *)work + 0x6C);
    value1 += 0x40;
    *(short *)((char *)work + 0x6C) = value1;
    
    value1 = *(short *)((char *)work + 0x6E);
    value1 += 0x40;
    *(short *)((char *)work + 0x6E) = value1;
    
    value1 = *(short *)((char *)work + 0x70);
    value2 = *(short *)((char *)work + 0x66);
    value1 += 0x40;
    value2 -= 0x80;
    *(short *)((char *)work + 0x70) = value1;
    
    calc = arg1 << 2;
    calc = calc + arg1;
    calc = calc << 2;
    diff = calc - value2;
    *(short *)((char *)work + 0x66) = diff;
    
    diff = diff << 10;
    diff = diff >> 10;
    
    if (diff < -1078)
    {
        diff = -1078;
        *(short *)((char *)work + 0x66) = diff;
    }
    
    value1 = *(short *)((char *)work + 0x66);
    value1 = value1 << 16;
    value1 = value1 >> 10;
    value1 = value1 >> 5;
    temp = value1 + diff;
    temp = temp >> 3;
    *(short *)((char *)work + 0x66) = temp;
}

void s11d_rope_800C48EC(void *work)
{
    unsigned int flags;
    void *ptr_804;
    short value;
    int f7c_value;
    int result;
    void *ptr_9c;
    unsigned int ptr_flags;
    short value_3e;
    void *src_ptr;
    unsigned int data1;
    unsigned int data2;
    short value_26;
    
    flags = *(unsigned int *)((char *)work + 0xF70);
    
    if ((flags & 0x2100) != 0)
    {
        return;
    }
    
    ptr_804 = *(void **)((char *)work + 0x804);
    value = *(short *)((char *)ptr_804 + 0x6);
    
    if ((flags & 0x8000) != 0)
    {
        if (value != 0)
        {
            f7c_value = *(int *)((char *)work + 0xF7C);
            
            if (f7c_value > 0)
            {
                f7c_value--;
                
                if (f7c_value != 0)
                {
                    *(int *)((char *)work + 0xF7C) = f7c_value;
                    
                    flags = *(unsigned int *)((char *)work + 0xF70);
                    
                    if ((flags & 0x1000) == 0)
                    {
                        if ((flags & 3) != 0)
                        {
                            ptr_9c = *(void **)((char *)work + 0x9C);
                            ptr_flags = *(unsigned int *)((char *)ptr_9c + 0x28);
                            ptr_flags &= 0xFFFFFF7F;
                            *(unsigned int *)((char *)ptr_9c + 0x28) = ptr_flags;
                        }
                        else
                        {
                            ptr_9c = *(void **)((char *)work + 0x9C);
                            ptr_flags = *(unsigned int *)((char *)ptr_9c + 0x28);
                            ptr_flags |= 0x80;
                            *(unsigned int *)((char *)ptr_9c + 0x28) = ptr_flags;
                        }
                    }
                }
                else
                {
                    func_80017090(0x10);
                    
                    f7c_value = *(int *)((char *)work + 0xF7C);
                    result = f7c_value * 0x800B77B8;
                    value = *(short *)0x800B77B8 + 0x2;
                    value += result;
                    *(short *)(0x800B77B8 + 0x2) = value;
                }
            }
            else
            {
                flags = *(unsigned int *)((char *)work + 0xF70);
                
                if ((flags & 0x1000) == 0)
                {
                    ptr_9c = *(void **)((char *)work + 0x9C);
                    ptr_flags = *(unsigned int *)((char *)ptr_9c + 0x28);
                    ptr_flags &= 0xFFFFFF7F;
                    *(unsigned int *)((char *)ptr_9c + 0x28) = ptr_flags;
                }
            }
            
            func_800C48C0(work);
        }
        
        value = *(short *)((char *)ptr_804 + 0x6);
        
        if ((value & 4) != 0)
        {
            value_3e = *(short *)((char *)ptr_804 + 0x3E);
            
            if (value_3e == 2)
            {
                func_800C958C((char *)work + 0x20);
                func_8005D58C((void *)0x800C3260, 1);
                func_8005D58C((void *)0x800C3264, 2);
                *(unsigned short *)((char *)work + 0xF44) = 0;
            }
            else
            {
                func_8005D58C((void *)0x800C326C, 1);
                func_8005D58C((void *)0x800C3270, 2);
                func_80017090(0x10);
                func_800C61D8(work, result);
            }
            
            *(unsigned short *)((char *)work + 0xF44) = 0;
            *(short *)((char *)ptr_804 + 0x28) = 0;
            *(short *)((char *)ptr_804 + 0x2A) = 0;
            
            value = *(short *)((char *)ptr_804 + 0x6);
            value &= 0xFFFB;
            *(short *)((char *)ptr_804 + 0x6) = value;
            
            src_ptr = (void *)0x800BB39C;
            data1 = *(unsigned int *)((char *)src_ptr + 0x0);
            data2 = *(unsigned int *)((char *)src_ptr + 0x4);
            *(unsigned int *)((char *)work + 0x2C) = data1;
            *(unsigned int *)((char *)work + 0x30) = data2;
            
            value_26 = *(short *)((char *)ptr_804 + 0x26);
            
            if (value_26 >= 0)
            {
                flags = *(unsigned int *)0x800BB3CC;
                *(int *)((char *)work + 0xEAC) = 0x800C7F8C;
                *(int *)((char *)work + 0xEB0) = 0;
                *(unsigned short *)((char *)work + 0xEBE) = 0;
                *(unsigned short *)((char *)work + 0xEBC) = 0;
                flags |= 0x2000;
                *(unsigned int *)0x800BB3CC = flags;
                return;
            }
        }
    }
    
    flags = *(unsigned int *)((char *)work + 0xF70);
    
    if ((flags & 0x1000) != 0)
    {
        func_800C486C(work);
        func_80032858((char *)work + 0x20, 0x19);
        return;
    }
    
    flags = *(unsigned int *)((char *)work + 0xF74);
    
    if ((flags & 0x2000) != 0)
    {
        *(int *)((char *)work + 0xEAC) = 0x800C7A4C;
    }
    else
    {
        *(int *)((char *)work + 0xEAC) = 0x800C7B2C;
    }
    
    *(int *)((char *)work + 0xEB0) = 0;
    *(unsigned short *)((char *)work + 0xEBE) = 0;
    *(unsigned short *)((char *)work + 0xEBC) = 0;
    
    ptr_804 = *(void **)((char *)work + 0x804);
    *(short *)((char *)ptr_804 + 0x12) = 0x384;
}

void s11d_rope_800C3E50(void *work)
{
    void *ptr_2c;
    void *ptr_s2;
    int value;
    short value_0;
    short value_44;
    short value_4;
    short value_48;
    short value_36;
    unsigned int data1;
    unsigned int data2;
    short stack_32;
    short stack_3a;
    unsigned char value_58;
    int result_1;
    int result_2;
    int result_3;
    void *ptr_s5;
    short value_2;
    short value_46;
    short value_32;
    int result_4;
    unsigned int flags;
    unsigned int flag_1;
    unsigned int flag_2;
    short stack_20;
    int stack_24;
    short value_78;
    short value_7a;
    unsigned int temp;
    short diff;
    
    ptr_2c = *(void **)((char *)work + 0x2C);
    ptr_s2 = *(void **)((char *)ptr_2c + 0x8);
    value = *(int *)((char *)ptr_2c + 0x0);
    *(int *)0x800BB9B0 = value;
    
    func_800C3DF0(work);
    
    value_0 = *(short *)((char *)work + 0x0);
    value_44 = *(short *)((char *)work + 0x44);
    value_36 = *(short *)((char *)work + 0x36);
    value_0 += value_44;
    *(short *)((char *)work + 0x0) = value_0;
    
    value_4 = *(short *)((char *)work + 0x4);
    value_48 = *(short *)((char *)work + 0x48);
    *(unsigned char *)((char *)work + 0x58) = 0;
    value_4 += value_48;
    
    if (value_36 == 0)
    {
        goto skip_copy;
    }
    
    *(short *)((char *)work + 0x4) = value_4;
    
    data1 = *(unsigned int *)((char *)ptr_s2 + 0x0);
    data2 = *(unsigned int *)((char *)ptr_s2 + 0x4);
    *(unsigned int *)((char *)work + 0x28) = data1;
    *(unsigned int *)((char *)work + 0x2C) = data2;
    
    data1 = *(unsigned int *)((char *)work + 0x28);
    data2 = *(unsigned int *)((char *)work + 0x2C);
    *(unsigned int *)((char *)work + 0x38) = data1;
    *(unsigned int *)((char *)work + 0x3C) = data2;
    
    data1 = *(unsigned int *)((char *)work + 0x38);
    data2 = *(unsigned int *)((char *)work + 0x3C);
    *(unsigned int *)((char *)work + 0x30) = data1;
    *(unsigned int *)((char *)work + 0x34) = data2;
    
    stack_32 = *(short *)((char *)work + 0x32);
    stack_3a = *(short *)((char *)work + 0x3A);
    
    *(int *)0x800D1F78 = 0;
    stack_32 += 0x1F0;
    stack_3a -= 0x1F0;
    *(short *)((char *)work + 0x32) = stack_32;
    *(short *)((char *)work + 0x3A) = stack_3a;
    
    value_58 = *(unsigned char *)((char *)work + 0x58);
    
    if (value_58 != 0)
    {
        goto already_set;
    }
    
    result_1 = func_80029098(work, (char *)work + 0x38, 0x1F4, *(unsigned char *)((char *)work + 0x59), 0xC);
    result_2 = func_800C3D50(work, result_1);
    ptr_s5 = result_2;
    
    if (ptr_s5 == 0)
    {
        result_1 = func_80029098(work, (char *)work + 0x28, 0x1F4, *(unsigned char *)((char *)work + 0x59), 0xC);
        result_3 = func_800C3D50(work, result_1);
        ptr_s5 = result_3;
        goto check_result;
    }
    else
    {
        *(int *)0x800D1F78 = 1;
        goto check_result;
    }
    
check_result:
    if (ptr_s5 == 0)
    {
        result_1 = func_80029098(work, (char *)work + 0x30, 0x1F4, *(unsigned char *)((char *)work + 0x59), 0xC);
        result_3 = func_800C3D50(work, result_1);
        ptr_s5 = result_3;
    }
    
    if (ptr_s5 == 0)
    {
        goto skip_vector;
    }
    
    *(unsigned char *)((char *)work + 0x58) = ptr_s5;
    
    func_80026C68((char *)work + 0x60, value_36, (char *)work + 0x20);
    
    value_0 = *(short *)((char *)work + 0x0);
    stack_20 = *(short *)((char *)work + 0x20);
    value_0 += stack_20;
    *(short *)((char *)work + 0x0) = value_0;
    
    stack_24 = *(int *)((char *)work + 0x24);
    
    if (stack_24 < 0)
    {
        goto skip_y_add;
    }
    
    value_4 = *(short *)((char *)work + 0x4);
    stack_24 = *(short *)((char *)work + 0x24);
    value_4 += stack_24;
    *(short *)((char *)work + 0x4) = value_4;
    
skip_y_add:
    value_0 = *(short *)((char *)work + 0x0);
    temp = *(unsigned short *)0x800D1F82;
    
    if (value_0 < (short)temp)
    {
        goto check_min;
    }
    
    temp = *(unsigned short *)0x800D1F80;
    
    if (value_0 <= (short)temp)
    {
        goto check_min;
    }
    
    *(short *)((char *)work + 0x0) = (short)temp;
    
check_min:
    value_58 = *(unsigned char *)((char *)work + 0x54);
    
    if (value_58 != 0)
    {
        func_800269A0((char *)work + 0x8, (char *)work + 0x4C, 0x3);
        goto skip_sub;
    }
    
    func_80026BC4((char *)work + 0x4C, (char *)work + 0x8, 0x3);
    value_58 = *(unsigned char *)((char *)work + 0x54);
    value_58--;
    *(unsigned char *)((char *)work + 0x54) = value_58;
    
skip_sub:
    value_36 = *(short *)((char *)work + 0x36);
    
    if (value_36 < -1)
    {
        goto skip_vector;
    }
    
    value_2 = *(short *)((char *)work + 0x2);
    value_46 = *(short *)((char *)work + 0x46);
    value_32 = *(short *)((char *)work + 0x32);
    *(unsigned char *)((char *)work + 0x57) = 0;
    value_2 += value_46;
    value_2 += value_32;
    
    result_4 = func_80029644(work, (char *)work + 0x20);
    flags = result_4;
    
    flag_1 = flags & 0x1;
    
    if (flag_1 != 0)
    {
        stack_20 = *(short *)0x800D1F7E;
        *(short *)((char *)work + 0x20) = stack_20;
    }
    
    flag_2 = flags & 0x2;
    
    if (flag_2 != 0)
    {
        stack_24 = *(short *)0x800D1F7C;
        *(int *)((char *)work + 0x24) = stack_24;
    }
    
    if (flag_1 == 0)
    {
        goto check_flag_2;
    }
    
    stack_20 = *(short *)((char *)work + 0x20);
    stack_20 += value_2;
    
check_flag_2:
    if (stack_20 <= value_32)
    {
        goto no_flag_set;
    }
    
    value_78 = value_2;
    value_58 = *(unsigned char *)((char *)work + 0x57);
    value_58 |= 0x1;
    *(unsigned char *)((char *)work + 0x57) = value_58;
    
no_flag_set:
    if (flag_2 == 0)
    {
        goto compute_offset;
    }
    
    stack_20 = value_32 << 1;
    stack_20 += value_32;
    
    if (stack_20 < 0)
    {
        stack_20 += 0x3;
    }
    
    stack_24 = *(int *)((char *)work + 0x24);
    stack_20 = stack_20 >> 2;
    stack_20 = stack_24 - stack_20;
    
    if (stack_20 <= value_78)
    {
        goto compute_offset;
    }
    
    value_78 = value_2;
    value_58 = *(unsigned char *)((char *)work + 0x57);
    value_58 |= 0x2;
    *(unsigned char *)((char *)work + 0x57) = value_58;
    
compute_offset:
    stack_20 = *(short *)((char *)work + 0x20);
    *(short *)((char *)work + 0x78) = stack_20;
    
    value_7a = *(short *)0x800D1F7C;
    stack_24 = *(short *)((char *)work + 0x24);
    
    if (value_78 < value_7a)
    {
        goto set_flag;
    }
    
    *(short *)((char *)work + 0x7A) = stack_24;
    value_78 = value_2;
    value_58 = *(unsigned char *)((char *)work + 0x57);
    value_58 |= 0x2;
    *(unsigned char *)((char *)work + 0x57) = value_58;
    goto check_3;
    
set_flag:
    value_7a = *(short *)0x800D1F7E;
    
    if (stack_20 <= value_7a)
    {
        goto check_3;
    }
    
    value_78 = value_2;
    
check_3:
    if (value_2 == 0x3)
    {
        goto sub_values;
    }
    
    value_0 = *(short *)((char *)work + 0x0);
    value_44 = *(short *)((char *)work + 0x44);
    diff = value_0 - value_44;
    *(short *)((char *)work + 0x0) = diff;
    goto copy_data;
    
sub_values:
    value_2 = *(short *)((char *)work + 0x2);
    value_46 = *(short *)((char *)work + 0x46);
    value_2 += value_46;
    *(short *)((char *)work + 0x2) = value_2;
    
copy_data:
    data1 = *(unsigned int *)((char *)work + 0x8);
    data2 = *(unsigned int *)((char *)work + 0xC);
    *(unsigned int *)((char *)work + 0x18) = data1;
    *(unsigned int *)((char *)work + 0x1C) = data2;
    
    *(short *)((char *)work + 0x1A) = 0x800;
    
    func_8001BC8C(work);
    return;
    
skip_vector:
already_set:
skip_copy:
    *(short *)((char *)work + 0x4) = value_4;
    
    data1 = *(unsigned int *)((char *)work + 0x8);
    data2 = *(unsigned int *)((char *)work + 0xC);
    *(unsigned int *)((char *)work + 0x18) = data1;
    *(unsigned int *)((char *)work + 0x1C) = data2;
    
    *(short *)((char *)work + 0x1A) = 0x800;
    
    func_8001BC8C(work);
}

void s11d_rope_800C5584(void *work, int arg1, int arg2)
{
    int ptr_1c;
    int ptr_0;
    int ptr_c;
    int ptr_f40;
    int ptr_4;
    int result_1;
    int result_2;
    int mult_result;
    int div_result;
    int rem_result;
    int calc1, calc2, calc3, calc4;
    int value_20;
    int value_0;
    int value_24;
    int value_4;
    int value_28;
    int value_c;
    int value_2c;
    unsigned int flags_f74;
    short value_22;
    short global_1f7c;
    unsigned int data1, data2;
    int value_8;
    int value_10;
    int value_14;
    int stack_value;
    short value_44;
    short value_48;
    short value_46;
    int final_value;
    
    ptr_1c = *(int *)((char *)work + 0x1C);
    ptr_0 = *(int *)((char *)work + 0x0);
    ptr_c = *(int *)((char *)work + 0xC);
    ptr_f40 = *(int *)((char *)work + 0xF40);
    ptr_4 = *(void **)((char *)work + 0x4);
    
    result_1 = func_800925D8((char *)work + 0x20);
    result_2 = func_800925D8(ptr_4);
    
    mult_result = ptr_f40 << 4;
    mult_result = mult_result * ptr_f40;
    div_result = mult_result / ptr_0;
    rem_result = div_result - ptr_c;
    
    mult_result = rem_result * ptr_1c;
    div_result = mult_result / arg1;
    
    if (div_result < 0)
    {
        div_result = (div_result + 0xFFF) >> 12;
    }
    else
    {
        div_result = div_result >> 12;
    }
    
    calc1 = div_result + result_1;
    
    if (calc1 < 0)
    {
        calc1 = 0;
    }
    
    result_1 = func_80092708(work);
    
    if (arg2 == 0)
    {
        goto skip_div_check;
    }
    
    value_20 = *(int *)((char *)work + 0x20);
    mult_result = (char *)work + 0x20;
    mult_result = mult_result * value_20;
    div_result = mult_result / value_20;
    
    if (div_result == 0)
    {
        goto complex_calc;
    }
    
    if (ptr_1c > 0)
    {
        calc1 = ptr_0 << 2;
        calc1 = calc1 + ptr_0;
        calc2 = calc1 << 2;
        calc2 = calc2 - calc1;
        calc3 = calc2 << 2;
        
        mult_result = calc3 * 0x1062;
        mult_result = mult_result + 0x4DD3;
        
        calc4 = ptr_4 << 1;
        calc4 = calc4 + ptr_4;
        calc1 = calc4 << 2;
        calc1 = calc1 - calc4;
        calc2 = calc1 << 1;
        
        div_result = calc2 / mult_result;
        div_result = div_result >> 3;
        
        *(int *)((char *)work + 0x2C) = 0x8;
        
        calc1 = div_result >> 5;
        calc2 = calc1 - ptr_0;
        calc3 = calc2 >> 5;
        *(int *)((char *)work + 0x24) = ptr_0;
        
        calc4 = calc3 << 4;
        calc4 = calc3 - calc4;
        calc4 = calc3 - calc4;
        *(int *)((char *)work + 0x28) = calc4;
    }
    
complex_calc:
    value_2c = *(int *)((char *)work + 0x2C);
    
    if (value_2c > 0)
    {
        value_0 = *(int *)((char *)work + 0x0);
        value_24 = *(int *)((char *)work + 0x24);
        
        func_80026430(value_0, value_24);
        
        value_4 = *(int *)((char *)work + 0x4);
        value_28 = *(int *)((char *)work + 0x28);
        value_c = *(int *)((char *)work + 0xC);
        
        func_80026430(value_4, value_28);
        func_80026430(value_4, value_c);
        
        value_0 = *(int *)((char *)work + 0x0);
        
        if (value_0 < 0x10)
        {
            goto check_negative;
        }
        
        if (value_0 >= 0x10)
        {
            if (value_0 < 0)
            {
                value_0 = -value_0;
            }
            
            if (value_0 < 0x20)
            {
                flags_f74 = *(unsigned int *)((char *)work + 0xF74);
                flags_f74 |= 0x400;
                flags_f74 &= 0xFEFF;
                *(unsigned int *)((char *)work + 0xF74) = flags_f74;
                *(int *)((char *)work + 0x2C) = 0;
                goto skip_div_check;
            }
        }
        
check_negative:
        value_2c = *(int *)((char *)work + 0x2C);
        value_2c--;
        *(int *)((char *)work + 0x2C) = value_2c;
        goto skip_div_check;
    }
    
    value_8 = *(int *)((char *)work + 0x8);
    
    if (value_8 == -1)
    {
        flags_f74 = *(unsigned int *)((char *)work + 0xF74);
        
        if ((flags_f74 & 0x4000) != 0)
        {
            func_80032858((char *)work + 0x20, 0xB7);
            
            *(short *)((char *)work + 0x6E) = 0x800;
            *(short *)((char *)work + 0xEC2) = 0x2;
            
            flags_f74 = *(unsigned int *)((char *)work + 0xF74);
            flags_f74 |= 0x80;
            flags_f74 |= 0x800;
            flags_f74 &= 0xFDFF;
            *(unsigned int *)((char *)work + 0xF74) = flags_f74;
        }
    }
    
    value_8 = *(int *)((char *)work + 0x8);
    mult_result = value_8 * value_8;
    
    result_1 = func_800925D8((char *)work + 0x20);
    mult_result = value_8 * result_1;
    div_result = mult_result / result_1;
    
    if (div_result < 0)
    {
        div_result = (div_result + 0xFFF) >> 12;
    }
    else
    {
        div_result = div_result >> 12;
    }
    
    result_2 = func_80092508((char *)work + 0x20);
    mult_result = value_8 * result_2;
    div_result = mult_result / result_2;
    
    if (div_result < 0)
    {
        div_result = (div_result + 0xFFF) >> 12;
    }
    else
    {
        div_result = div_result >> 12;
    }
    
    calc1 = div_result;
    
    if (calc1 < 0)
    {
        calc1 = -calc1;
    }
    
    calc2 = result_1;
    
    if (calc2 < 0)
    {
        calc2 = -calc2;
    }
    
    calc1 = calc1 + calc2;
    
    if (calc1 < 0x10)
    {
        stack_value = 0;
    }
    else
    {
        stack_value = 0x1;
    }
    
    if (arg2 == 0)
    {
        goto check_flags;
    }
    
    flags_f74 = *(unsigned int *)((char *)work + 0xF74);
    
    if ((flags_f74 & 0x1000) != 0)
    {
        value_22 = *(short *)((char *)work + 0x22);
        global_1f7c = *(short *)0x800D1F7C;
        
        if (value_22 != global_1f7c)
        {
            func_80032858((char *)work + 0x20, 0xB7);
        }
    }
    
    data1 = *(unsigned int *)((char *)work + 0x0);
    data2 = *(unsigned int *)((char *)work + 0x4);
    *(unsigned int *)((char *)work + 0x10) = data1;
    *(unsigned int *)((char *)work + 0x14) = data2;
    
    value_8 = *(int *)((char *)work + 0x8);
    calc1 = value_8 << 6;
    calc1 = value_8 - calc1;
    calc2 = calc1 << 2;
    calc2 = calc2 + calc1;
    stack_value = *(int *)((char *)work + 0x10);
    stack_value += calc2;
    *(int *)((char *)work + 0x10) = stack_value;
    
check_flags:
    if (stack_value != 0x1)
    {
        goto check_value_2;
    }
    
    value_10 = *(int *)((char *)work + 0x10);
    
    if (value_10 < 0)
    {
        value_10 = -value_10;
    }
    
    if (arg2 == 0)
    {
        value_8 = -1;
        goto final_section;
    }
    
    value_14 = *(int *)((char *)work + 0x14);
    
    if (value_14 > 0)
    {
        value_8 = 0x1;
        goto final_section;
    }
    else
    {
        value_8 = -1;
        goto final_section;
    }
    
check_value_2:
    if (stack_value != 0x2)
    {
        goto final_calc;
    }
    
    value_22 = *(short *)((char *)work + 0x22);
    global_1f7c = *(short *)0x800D1F7C;
    
    if (value_22 != global_1f7c)
    {
        func_80032858((char *)work + 0x20, 0xB8);
    }
    
    calc1 = ptr_0 << 2;
    calc1 = calc1 + ptr_0;
    calc2 = calc1 << 1;
    calc2 = calc2 - calc1;
    calc3 = calc2 << 3;
    
    mult_result = calc3 * 0x1062;
    mult_result = mult_result + 0x4DD3;
    
    calc4 = ptr_4 << 1;
    calc4 = calc4 + ptr_4;
    calc1 = calc4 << 2;
    calc1 = calc1 - calc4;
    calc2 = calc1 << 1;
    
    div_result = calc2 / mult_result;
    
    value_8 = *(int *)((char *)work + 0x8);
    calc1 = div_result >> 5;
    
    *(int *)((char *)work + 0x20) = ptr_1c;
    value_8 = -value_8;
    *(int *)((char *)work + 0x8) = value_8;
    
    value_10 = -ptr_c;
    *(int *)((char *)work + 0x10) = value_10;
    
    calc2 = calc1 >> 5;
    *(int *)((char *)work + 0x0) = ptr_0;
    
    calc3 = calc2 - ptr_0;
    
    if (calc3 < 0)
    {
        calc1 = -calc1;
    }
    else
    {
        calc1 = calc1;
    }
    
    if (calc1 < 0x41)
    {
        *(int *)((char *)work + 0x4) = calc3;
        goto skip_call;
    }
    
    func_8005D58C(0x800C32B0, 0x2);
    
skip_call:
    value_8 = *(int *)((char *)work + 0x8);
    mult_result = value_8 * value_8;
    
    result_1 = func_800925D8((char *)work + 0x20);
    mult_result = value_8 * result_1;
    div_result = mult_result / result_1;
    
    if (div_result < 0)
    {
        div_result = (div_result + 0xFFF) >> 12;
    }
    else
    {
        div_result = div_result >> 12;
    }
    
    result_2 = func_80092508((char *)work + 0x20);
    mult_result = value_8 * result_2;
    div_result = mult_result / result_2;
    
    if (div_result < 0)
    {
        div_result = (div_result + 0xFFF) >> 12;
        goto final_calc;
    }
    else
    {
        div_result = div_result >> 12;
    }
    
final_calc:
    *(int *)((char *)work + 0x20) = ptr_1c;
    *(int *)((char *)work + 0x10) = ptr_c;
    
final_section:
    if (arg2 == 0)
    {
        goto update_values;
    }
    
    value_44 = *(short *)((char *)work + 0x44);
    value_44 += ptr_f40;
    *(short *)((char *)work + 0x44) = value_44;
    goto exit_function;
    
update_values:
    value_48 = *(short *)((char *)work + 0x48);
    value_48 += ptr_f40;
    *(short *)((char *)work + 0x48) = value_48;
    
    value_46 = *(short *)((char *)work + 0x46);
    value_46 += ptr_c;
    *(short *)((char *)work + 0x46) = value_46;
    
exit_function:
skip_div_check:
    return;
}

void s11d_rope_800C5B10(void *work)
{
    unsigned int flags_f70;
    void *ptr_ea8;
    short value_0;
    unsigned char value_f;
    short value_2;
    unsigned int flags_f74;
    unsigned char value_12;
    int calc_value;
    int div_result;
    short stack_14;
    int temp_calc;
    short value_stack;
    unsigned int data1, data2;
    short value_4;
    unsigned int and_result;
    short final_value;
    
    flags_f70 = *(unsigned int *)((char *)work + 0xF70);
    
    if ((flags_f70 & 0x1000) == 0)
    {
        return;
    }
    
    ptr_ea8 = *(void **)((char *)work + 0xEA8);
    value_0 = *(short *)((char *)ptr_ea8 + 0x0);
    *(short *)((char *)work + 0x10) = value_0;
    
    ptr_ea8 = *(void **)((char *)work + 0xEA8);
    value_f = *(unsigned char *)((char *)ptr_ea8 + 0xF);
    *(unsigned char *)((char *)work + 0x12) = value_f;
    
    func_8004FBF8();
    func_8004FC70((char *)work + 0x12);
    
    value_stack = *(short *)((char *)work + 0x10);
    *(short *)((char *)work + 0x14) = 0;
    
    ptr_ea8 = *(void **)((char *)work + 0xEA8);
    flags_f74 = flags_f70 & 0x1000;
    value_2 = *(short *)((char *)ptr_ea8 + 0x2);
    
    if (flags_f74 == 0)
    {
        goto check_4000_flag;
    }
    
    flags_f74 = *(unsigned int *)((char *)work + 0xF74);
    
    if ((flags_f74 & 0x8000) != 0)
    {
        value_12 = *(unsigned char *)((char *)work + 0x12);
        calc_value = 0x40 - value_12;
        goto compute_div;
    }
    
    calc_value = 0x1;
    flags_f74 = *(unsigned int *)((char *)work + 0xF74);
    
    if ((flags_f74 & 0x8000) != 0)
    {
        calc_value = 0x40;
    }
    else
    {
        calc_value = 0x1;
    }
    
compute_div:
    value_12 = calc_value & 0xFF;
    temp_calc = value_12 << 1;
    temp_calc += value_12;
    temp_calc = temp_calc << 9;
    
    div_result = temp_calc / calc_value;
    
    if (div_result == -1)
    {
        goto div_error;
    }
    
    if (div_result == 0x80000000)
    {
        goto div_check;
    }
    
div_check:
    div_result = div_result >> 1;
    stack_14 = *(short *)((char *)work + 0x14);
    calc_value = stack_14 - div_result;
    *(short *)((char *)work + 0x14) = calc_value;
    goto check_4000_flag;
    
div_error:
    ;
    
check_4000_flag:
    flags_f74 = flags_f70 & 0x4000;
    
    if (flags_f74 == 0)
    {
        goto skip_4000_logic;
    }
    
    flags_f74 = *(unsigned int *)((char *)work + 0xF74);
    
    if ((flags_f74 & 0x8000) != 0)
    {
        value_12 = *(unsigned char *)((char *)work + 0x12);
        value_12 += 0x40;
        calc_value = value_12;
        goto compute_div_2;
    }
    
    flags_f74 = *(unsigned int *)((char *)work + 0xF74);
    
    if ((flags_f74 & 0x8000) != 0)
    {
        calc_value = 0x3F;
    }
    else
    {
        calc_value = 0x1;
    }
    
compute_div_2:
    value_12 = calc_value & 0xFF;
    temp_calc = value_12 << 1;
    temp_calc += value_12;
    temp_calc = temp_calc << 8;
    
    div_result = temp_calc / calc_value;
    
    if (div_result == -1)
    {
        goto skip_4000_logic;
    }
    
    if (div_result == 0x80000000)
    {
        goto continue_4000;
    }
    
continue_4000:
    div_result = div_result >> 1;
    stack_14 = *(short *)((char *)work + 0x14);
    calc_value = stack_14 + div_result;
    *(short *)((char *)work + 0x14) = calc_value;
    
skip_4000_logic:
    flags_f74 = flags_f70 & 0x400;
    
    if (flags_f74 == 0)
    {
        goto skip_400_logic;
    }
    
    flags_f74 = *(unsigned int *)((char *)work + 0xF74);
    
    if ((flags_f74 & 0x8000) != 0)
    {
        value_12 = *(unsigned char *)((char *)work + 0x12);
        calc_value = 0x80 - value_12;
        goto compute_div_3;
    }
    
    flags_f74 = *(unsigned int *)((char *)work + 0xF74);
    
    if ((flags_f74 & 0x8000) != 0)
    {
        calc_value = 0x80;
    }
    else
    {
        calc_value = 0x1;
    }
    
compute_div_3:
    value_12 = calc_value & 0xFF;
    temp_calc = value_12 << 1;
    temp_calc += value_12;
    temp_calc = temp_calc << 8;
    
    div_result = temp_calc / calc_value;
    
    if (div_result == -1)
    {
        goto skip_400_logic;
    }
    
    if (div_result == 0x80000000)
    {
        goto continue_400;
    }
    
continue_400:
    div_result = div_result >> 1;
    stack_14 = *(short *)((char *)work + 0x14);
    calc_value = stack_14 - div_result;
    *(short *)((char *)work + 0x14) = calc_value;
    
skip_400_logic:
    stack_14 = *(short *)((char *)work + 0x14);
    and_result = stack_14 & 0xFFF;
    *(short *)((char *)work + 0x2) = and_result;
    
    data1 = *(unsigned int *)0x800B77B8;
    data2 = *(unsigned int *)0x800B77BC;
    *(unsigned int *)((char *)work + 0x28) = data1;
    *(unsigned int *)((char *)work + 0x2C) = data2;
    
    ptr_ea8 = *(void **)((char *)work + 0xEA8);
    value_4 = *(short *)((char *)ptr_ea8 + 0x4);
    value_2 = *(short *)((char *)ptr_ea8 + 0x2); and_result = value_2 & 0xF1F;
    *(short *)((char *)ptr_ea8 + 0x2) = and_result;
    
    value_stack = *(short *)((char *)work + 0x10);
    ptr_ea8 = *(void **)((char *)work + 0xEA8);
    and_result = value_stack & 0xF1F;
    *(short *)((char *)work + 0x10) = and_result;
    *(short *)((char *)ptr_ea8 + 0x0) = and_result;
    
    ptr_ea8 = *(void **)((char *)work + 0xEA8);
    final_value = value_4 & 0xF1F;
    *(short *)((char *)ptr_ea8 + 0x4) = final_value;
}

void s11d_rope_800C5E74(void *work)
{
    unsigned int flags_f70;
    void *ptr_ea8;
    short value_0;
    unsigned char value_f;
    short value_2;
    unsigned int flags_f74;
    unsigned char value_12;
    int calc_value;
    int div_result;
    short stack_14;
    int temp_calc;
    short value_stack;
    unsigned int data1, data2;
    short value_4;
    unsigned int and_result;
    short final_value;
    
    flags_f70 = *(unsigned int *)((char *)work + 0xF70);
    
    if ((flags_f70 & 0x1000) == 0)
    {
        return;
    }
    
    ptr_ea8 = *(void **)((char *)work + 0xEA8);
    value_0 = *(short *)((char *)ptr_ea8 + 0x0);
    *(short *)((char *)work + 0x10) = value_0;
    
    ptr_ea8 = *(void **)((char *)work + 0xEA8);
    value_f = *(unsigned char *)((char *)ptr_ea8 + 0xF);
    *(unsigned char *)((char *)work + 0x12) = value_f;
    
    func_8004FBF8();
    func_8004FC70((char *)work + 0x12);
    
    value_stack = *(short *)((char *)work + 0x10);
    *(short *)((char *)work + 0x14) = 0;
    
    ptr_ea8 = *(void **)((char *)work + 0xEA8);
    flags_f74 = flags_f70 & 0x1000;
    value_2 = *(short *)((char *)ptr_ea8 + 0x2);
    
    if (flags_f74 == 0)
    {
        goto check_4000_flag;
    }
    
    flags_f74 = *(unsigned int *)((char *)work + 0xF74);
    
    if ((flags_f74 & 0x8000) != 0)
    {
        value_12 = *(unsigned char *)((char *)work + 0x12);
        calc_value = 0x40 - value_12;
        goto compute_div;
    }
    
    calc_value = 0x1;
    flags_f74 = *(unsigned int *)((char *)work + 0xF74);
    
    if ((flags_f74 & 0x8000) != 0)
    {
        calc_value = 0x40;
    }
    else
    {
        calc_value = 0x1;
    }
    
compute_div:
    value_12 = calc_value & 0xFF;
    temp_calc = value_12 << 1;
    temp_calc += value_12;
    temp_calc = temp_calc << 9;
    
    div_result = temp_calc / calc_value;
    
    if (div_result == -1)
    {
        goto div_error;
    }
    
    if (div_result == 0x80000000)
    {
        goto div_check;
    }
    
div_check:
    div_result = div_result >> 1;
    stack_14 = *(short *)((char *)work + 0x14);
    calc_value = stack_14 - div_result;
    *(short *)((char *)work + 0x14) = calc_value;
    goto check_4000_flag;
    
div_error:
    ;
    
check_4000_flag:
    flags_f74 = flags_f70 & 0x4000;
    
    if (flags_f74 == 0)
    {
        goto skip_4000_logic;
    }
    
    flags_f74 = *(unsigned int *)((char *)work + 0xF74);
    
    if ((flags_f74 & 0x8000) != 0)
    {
        value_12 = *(unsigned char *)((char *)work + 0x12);
        value_12 += 0x40;
        calc_value = value_12;
        goto compute_div_2;
    }
    
    flags_f74 = *(unsigned int *)((char *)work + 0xF74);
    
    if ((flags_f74 & 0x8000) != 0)
    {
        calc_value = 0x3F;
    }
    else
    {
        calc_value = 0x1;
    }
    
compute_div_2:
    value_12 = calc_value & 0xFF;
    temp_calc = value_12 << 1;
    temp_calc += value_12;
    temp_calc = temp_calc << 8;
    
    div_result = temp_calc / calc_value;
    
    if (div_result == -1)
    {
        goto skip_4000_logic;
    }
    
    if (div_result == 0x80000000)
    {
        goto continue_4000;
    }
    
continue_4000:
    div_result = div_result >> 1;
    stack_14 = *(short *)((char *)work + 0x14);
    calc_value = stack_14 + div_result;
    *(short *)((char *)work + 0x14) = calc_value;
    
skip_4000_logic:
    flags_f74 = flags_f70 & 0x400;
    
    if (flags_f74 == 0)
    {
        goto skip_400_logic;
    }
    
    flags_f74 = *(unsigned int *)((char *)work + 0xF74);
    
    if ((flags_f74 & 0x8000) != 0)
    {
        value_12 = *(unsigned char *)((char *)work + 0x12);
        calc_value = 0x80 - value_12;
        goto compute_div_3;
    }
    
    flags_f74 = *(unsigned int *)((char *)work + 0xF74);
    
    if ((flags_f74 & 0x8000) != 0)
    {
        calc_value = 0x80;
    }
    else
    {
        calc_value = 0x1;
    }
    
compute_div_3:
    value_12 = calc_value & 0xFF;
    temp_calc = value_12 << 1;
    temp_calc += value_12;
    temp_calc = temp_calc << 8;
    
    div_result = temp_calc / calc_value;
    
    if (div_result == -1)
    {
        goto skip_400_logic;
    }
    
    if (div_result == 0x80000000)
    {
        goto continue_400;
    }
    
continue_400:
    div_result = div_result >> 1;
    stack_14 = *(short *)((char *)work + 0x14);
    calc_value = stack_14 - div_result;
    *(short *)((char *)work + 0x14) = calc_value;
    
skip_400_logic:
    stack_14 = *(short *)((char *)work + 0x14);
    and_result = stack_14 & 0xFFF;
    *(short *)((char *)work + 0x2) = and_result;
    
    data1 = *(unsigned int *)0x800B77C0;
    data2 = *(unsigned int *)0x800B77C4;
    *(unsigned int *)((char *)work + 0x28) = data1;
    *(unsigned int *)((char *)work + 0x2C) = data2;
    
    ptr_ea8 = *(void **)((char *)work + 0xEA8);
    value_4 = *(short *)((char *)ptr_ea8 + 0x4);
    value_2 = *(short *)((char *)ptr_ea8 + 0x2); and_result = value_2 & 0xF1F;
    *(short *)((char *)ptr_ea8 + 0x2) = and_result;
    
    value_stack = *(short *)((char *)work + 0x10);
    ptr_ea8 = *(void **)((char *)work + 0xEA8);
    and_result = value_stack & 0xF1F;
    *(short *)((char *)work + 0x10) = and_result;
    *(short *)((char *)ptr_ea8 + 0x0) = and_result;
    
    ptr_ea8 = *(void **)((char *)work + 0xEA8);
    final_value = value_4 & 0xF1F;
    *(short *)((char *)ptr_ea8 + 0x4) = final_value;
}

void s11d_rope_800C6544(void *work)
{
    unsigned int flags_f70;
    void *ptr_ea8;
    short value_0;
    short value_2;
    unsigned char value_f;
    short stack_14;
    unsigned int flags_f74;
    unsigned char value_12;
    int calc_value;
    int div_result;
    int temp_calc;
    unsigned int data1, data2;
    short value_4;
    unsigned int and_result;
    short value_stack;
    
    flags_f70 = *(unsigned int *)((char *)work + 0xF70);
    
    if ((flags_f70 & 0x1000) == 0)
    {
        return;
    }
    
    ptr_ea8 = *(void **)((char *)work + 0xEA8);
    value_0 = *(short *)((char *)ptr_ea8 + 0x0);
    *(short *)((char *)work + 0x10) = value_0;
    
    ptr_ea8 = *(void **)((char *)work + 0xEA8);
    value_f = *(unsigned char *)((char *)ptr_ea8 + 0xF);
    *(unsigned char *)((char *)work + 0x12) = value_f;
    
    func_8004FBF8();
    func_8004FC70((char *)work + 0x12);
    
    value_stack = *(short *)((char *)work + 0x10);
    *(short *)((char *)work + 0x14) = 0;
    
    ptr_ea8 = *(void **)((char *)work + 0xEA8);
    flags_f74 = flags_f70 & 0x1000;
    value_2 = *(short *)((char *)ptr_ea8 + 0x2);
    
    if (flags_f74 == 0)
    {
        goto check_4000;
    }
    
    flags_f74 = *(unsigned int *)((char *)work + 0xF74);
    
    if ((flags_f74 & 0x8000) != 0)
    {
        value_12 = *(unsigned char *)((char *)work + 0x12);
        calc_value = 0x40 - value_12;
        goto div_calc_1;
    }
    
    calc_value = 0x1;
    flags_f74 = *(unsigned int *)((char *)work + 0xF74);
    
    if ((flags_f74 & 0x8000) != 0)
    {
        calc_value = 0x40;
    }
    else
    {
        calc_value = 0x1;
    }
    
div_calc_1:
    value_12 = calc_value & 0xFF;
    temp_calc = value_12 << 1;
    temp_calc += value_12;
    temp_calc = temp_calc << 9;
    
    div_result = temp_calc / calc_value;
    
    if (div_result == -1)
    {
        goto check_4000;
    }
    
    if (div_result == 0x80000000)
    {
        goto apply_div_1;
    }
    
apply_div_1:
    div_result = div_result >> 1;
    stack_14 = *(short *)((char *)work + 0x14);
    calc_value = stack_14 - div_result;
    *(short *)((char *)work + 0x14) = calc_value;
    
check_4000:
    flags_f74 = flags_f70 & 0x4000;
    
    if (flags_f74 == 0)
    {
        goto check_400;
    }
    
    flags_f74 = *(unsigned int *)((char *)work + 0xF74);
    
    if ((flags_f74 & 0x8000) != 0)
    {
        value_12 = *(unsigned char *)((char *)work + 0x12);
        value_12 += 0x40;
        calc_value = value_12;
        goto div_calc_2;
    }
    
    flags_f74 = *(unsigned int *)((char *)work + 0xF74);
    
    if ((flags_f74 & 0x8000) != 0)
    {
        calc_value = 0x3F;
    }
    else
    {
        calc_value = 0x1;
    }
    
div_calc_2:
    value_12 = calc_value & 0xFF;
    temp_calc = value_12 << 1;
    temp_calc += value_12;
    temp_calc = temp_calc << 8;
    
    div_result = temp_calc / calc_value;
    
    if (div_result == -1)
    {
        goto check_400;
    }
    
    if (div_result == 0x80000000)
    {
        goto apply_div_2;
    }
    
apply_div_2:
    div_result = div_result >> 1;
    stack_14 = *(short *)((char *)work + 0x14);
    calc_value = stack_14 + div_result;
    *(short *)((char *)work + 0x14) = calc_value;
    
check_400:
    flags_f74 = flags_f70 & 0x400;
    
    if (flags_f74 == 0)
    {
        goto finalize;
    }
    
    flags_f74 = *(unsigned int *)((char *)work + 0xF74);
    
    if ((flags_f74 & 0x8000) != 0)
    {
        value_12 = *(unsigned char *)((char *)work + 0x12);
        calc_value = 0x80 - value_12;
        goto div_calc_3;
    }
    
    flags_f74 = *(unsigned int *)((char *)work + 0xF74);
    
    if ((flags_f74 & 0x8000) != 0)
    {
        calc_value = 0x80;
    }
    else
    {
        calc_value = 0x1;
    }
    
div_calc_3:
    value_12 = calc_value & 0xFF;
    temp_calc = value_12 << 1;
    temp_calc += value_12;
    temp_calc = temp_calc << 8;
    
    div_result = temp_calc / calc_value;
    
    if (div_result == -1)
    {
        goto finalize;
    }
    
    if (div_result == 0x80000000)
    {
        goto apply_div_3;
    }
    
apply_div_3:
    div_result = div_result >> 1;
    stack_14 = *(short *)((char *)work + 0x14);
    calc_value = stack_14 - div_result;
    *(short *)((char *)work + 0x14) = calc_value;
    
finalize:
    stack_14 = *(short *)((char *)work + 0x14);
    and_result = stack_14 & 0xFFF;
    *(short *)((char *)work + 0x2) = and_result;
    
    data1 = *(unsigned int *)0x800B77C8;
    data2 = *(unsigned int *)0x800B77CC;
    *(unsigned int *)((char *)work + 0x28) = data1;
    *(unsigned int *)((char *)work + 0x2C) = data2;
    
    ptr_ea8 = *(void **)((char *)work + 0xEA8);
    value_4 = *(short *)((char *)ptr_ea8 + 0x4);
    value_2 = *(short *)((char *)ptr_ea8 + 0x2); and_result = value_2 & 0xF1F;
    *(short *)((char *)ptr_ea8 + 0x2) = and_result;
    
    value_stack = *(short *)((char *)work + 0x10);
    ptr_ea8 = *(void **)((char *)work + 0xEA8);
    and_result = value_stack & 0xF1F;
    *(short *)((char *)work + 0x10) = and_result;
    *(short *)((char *)ptr_ea8 + 0x0) = and_result;
    
    ptr_ea8 = *(void **)((char *)work + 0xEA8);
    and_result = value_4 & 0xF1F;
    *(short *)((char *)ptr_ea8 + 0x4) = and_result;
}

void s11d_rope_800C766C(void *work, int arg1)
{
    unsigned int flags_f74;
    unsigned int flags_f70;
    short value_aa;
    int result;
    short value_b6;
    int value_f7c;
    void *ptr_ea8;
    short value_ebc;
    short value_ebe;
    int value_ed0;
    int calc1, calc2, calc3;
    int mult_result;
    int div_result;
    short value_64;
    short value_66;
    
    if (arg1 == 0)
    {
        goto skip_init;
    }
    
    flags_f74 = *(unsigned int *)((char *)work + 0xF74);
    flags_f74 &= 0xFFFEFFFF;
    *(unsigned int *)((char *)work + 0xF74) = flags_f74;
    
    flags_f70 = *(unsigned int *)((char *)work + 0xF70);
    flags_f70 &= 0xFF00;
    *(unsigned int *)((char *)work + 0xF70) = flags_f70;
    
    value_aa = *(short *)((char *)work + 0xAA);
    
    if (value_aa == 0x5)
    {
        goto call_functions;
    }
    
    func_80034CD4((char *)work + 0x9C, 0, 0, 4);
    
call_functions:
    func_8005D58C(0x800C329C, 0x1);
    
    *(int *)((char *)work + 0xF60) = -8;
    *(int *)((char *)work + 0xF68) = -8;
    *(int *)((char *)work + 0xF64) = -8;
    
    *(short *)((char *)work + 0xEC4) = 0;
    *(short *)((char *)work + 0xF44) = 0x1C2;
    *(short *)((char *)work + 0x1076) = 0;
    *(short *)((char *)work + 0x1074) = 0;
    
    func_8005D58C(0x800C32A4, 0x2);
    
    if (arg1 != 0x1)
    {
        goto check_10;
    }
    
    func_800C634C(work);
    
    result = func_80032A1C((char *)work + 0x20, 0x80, 0x1);
    result = func_80032A1C((char *)work + 0x20, 0xB2, 0x1);
    
check_10:
    if (arg1 != 0x10)
    {
        goto check_b6;
    }
    
    value_f7c = *(int *)((char *)work + 0xF7C);
    
    if (value_f7c != 0)
    {
        goto check_b6;
    }
    
    func_800C48C0(work);
    
check_b6:
    value_b6 = *(short *)((char *)work + 0xB6);
    
    if (value_b6 == 0)
    {
        goto skip_init;
    }
    
    value_aa = *(short *)((char *)work + 0xAA);
    
    if (value_aa != 0x5)
    {
        goto setup_call;
    }
    
    func_80034CD4((char *)work + 0x9C, 0, 0, 4);
    
setup_call:
    func_800C5348(work);
    
skip_init:
    ptr_ea8 = *(void **)((char *)work + 0xEA8);
    value_ebc = *(short *)((char *)ptr_ea8 + 0xEBC);
    value_ebe = *(short *)((char *)ptr_ea8 + 0xEBE);
    
    func_80092508(work);
    
    value_ed0 = *(int *)((char *)work + 0xED0);
    calc1 = value_ed0 >> 7;
    calc1 += value_ebc;
    calc2 = calc1 >> 12;
    
    value_ebc = *(short *)((char *)work + 0xEBC);
    value_ebe = *(short *)((char *)work + 0xEBE);
    
    func_80092508(work);
    
    mult_result = value_ebc * value_ebe;
    div_result = mult_result / value_ebe;
    
    mult_result = div_result * calc2;
    div_result = mult_result / calc2;
    
    if (div_result < 0)
    {
        div_result = (div_result + 0xFFF) >> 12;
    }
    else
    {
        div_result = div_result >> 12;
    }
    
    value_64 = *(short *)((char *)work + 0x64);
    value_64 += div_result;
    *(short *)((char *)work + 0x64) = value_64;
    
    func_800925D8(work);
    
    mult_result = value_ebc * result;
    div_result = mult_result / result;
    
    if (div_result < 0)
    {
        div_result = (div_result + 0xFFF) >> 12;
    }
    else
    {
        div_result = div_result >> 12;
    }
    
    value_66 = *(short *)((char *)work + 0x66);
    value_66 -= div_result;
    *(short *)((char *)work + 0x66) = value_66;
    
    if (arg1 != 0x38)
    {
        return;
    }
    
    *(short *)((char *)work + 0x1076) = 0;
    *(short *)((char *)work + 0x1074) = 0;
    *(int *)((char *)work + 0xEAC) = 0x800C7530;
    *(int *)((char *)work + 0xEB0) = 0;
    *(short *)((char *)work + 0xEBE) = 0;
    *(short *)((char *)work + 0xEBC) = 0;
}

void s11d_rope_800C8364(void *work)
{
    unsigned int flags_f70;
    unsigned int flags_f74;
    void *ptr_ea8;
    short value_ebc;
    short value_ebe;
    int value_ed0;
    int result;
    int calc1, calc2;
    int mult_result;
    int div_result;
    short value_64;
    short value_66;
    int final_calc;
    
    flags_f70 = *(unsigned int *)((char *)work + 0xF70);
    
    if ((flags_f70 & 0x2100) != 0)
    {
        return;
    }
    
    flags_f74 = *(unsigned int *)((char *)work + 0xF74);
    
    if ((flags_f74 & 0x10) == 0)
    {
        return;
    }
    
    ptr_ea8 = *(void **)((char *)work + 0xEA8);
    value_ebc = *(short *)((char *)ptr_ea8 + 0xEBC);
    value_ebe = *(short *)((char *)ptr_ea8 + 0xEBE);
    
    func_80092508(work);
    
    value_ed0 = *(int *)((char *)work + 0xED0);
    calc1 = value_ed0 >> 7;
    calc1 += value_ebc;
    calc2 = calc1 >> 12;
    
    value_ebc = *(short *)((char *)work + 0xEBC);
    value_ebe = *(short *)((char *)work + 0xEBE);
    
    func_80092508(work);
    
    mult_result = value_ebc * value_ebe;
    div_result = mult_result / value_ebe;
    
    mult_result = div_result * calc2;
    div_result = mult_result / calc2;
    
    if (div_result < 0)
    {
        div_result = (div_result + 0xFFF) >> 12;
    }
    else
    {
        div_result = div_result >> 12;
    }
    
    value_64 = *(short *)((char *)work + 0x64);
    value_64 += div_result;
    *(short *)((char *)work + 0x64) = value_64;
    
    func_800925D8(work);
    
    mult_result = value_ebc * result;
    div_result = mult_result / result;
    
    if (div_result < 0)
    {
        div_result = (div_result + 0xFFF) >> 12;
    }
    else
    {
        div_result = div_result >> 12;
    }
    
    value_66 = *(short *)((char *)work + 0x66);
    value_66 -= div_result;
    *(short *)((char *)work + 0x66) = value_66;
}

void s11d_rope_800C882C(void *work)
{
    unsigned int flags_f70;
    unsigned int flags_f74;
    void *ptr_ea8;
    short value_ebc;
    short value_ebe;
    int value_ed0;
    int result;
    int calc1, calc2;
    int mult_result;
    int div_result;
    short value_64;
    short value_66;
    short value_aa;
    
    flags_f70 = *(unsigned int *)((char *)work + 0xF70);
    
    if ((flags_f70 & 0x2100) != 0)
    {
        return;
    }
    
    flags_f74 = *(unsigned int *)((char *)work + 0xF74);
    
    if ((flags_f74 & 0x10) == 0)
    {
        return;
    }
    
    value_aa = *(short *)((char *)work + 0xAA);
    
    if (value_aa != 0x5)
    {
        goto skip_call;
    }
    
    func_80034CD4((char *)work + 0x9C, 0, 0, 4);
    
skip_call:
    ptr_ea8 = *(void **)((char *)work + 0xEA8);
    value_ebc = *(short *)((char *)ptr_ea8 + 0xEBC);
    value_ebe = *(short *)((char *)ptr_ea8 + 0xEBE);
    
    func_80092508(work);
    
    value_ed0 = *(int *)((char *)work + 0xED0);
    calc1 = value_ed0 >> 7;
    calc1 += value_ebc;
    calc2 = calc1 >> 12;
    
    value_ebc = *(short *)((char *)work + 0xEBC);
    value_ebe = *(short *)((char *)work + 0xEBE);
    
    func_80092508(work);
    
    mult_result = value_ebc * value_ebe;
    div_result = mult_result / value_ebe;
    
    mult_result = div_result * calc2;
    div_result = mult_result / calc2;
    
    if (div_result < 0)
    {
        div_result = (div_result + 0xFFF) >> 12;
    }
    else
    {
        div_result = div_result >> 12;
    }
    
    value_64 = *(short *)((char *)work + 0x64);
    value_64 += div_result;
    *(short *)((char *)work + 0x64) = value_64;
    
    func_800925D8(work);
    
    mult_result = value_ebc * result;
    div_result = mult_result / result;
    
    if (div_result < 0)
    {
        div_result = (div_result + 0xFFF) >> 12;
    }
    else
    {
        div_result = div_result >> 12;
    }
    
    value_66 = *(short *)((char *)work + 0x66);
    value_66 -= div_result;
    *(short *)((char *)work + 0x66) = value_66;
}

void s11d_rope_800C91AC(void *work)
{
    unsigned int flags_f70;
    unsigned int flags_f74;
    void *ptr_ea8;
    short value_ebc;
    short value_ebe;
    int value_ed0;
    int result;
    int calc1, calc2;
    int mult_result;
    int div_result;
    short value_64;
    short value_66;
    short value_aa;
    
    flags_f70 = *(unsigned int *)((char *)work + 0xF70);
    
    if ((flags_f70 & 0x2100) != 0)
    {
        return;
    }
    
    flags_f74 = *(unsigned int *)((char *)work + 0xF74);
    
    if ((flags_f74 & 0x10) == 0)
    {
        return;
    }
    
    value_aa = *(short *)((char *)work + 0xAA);
    
    if (value_aa != 0x5)
    {
        goto skip_call;
    }
    
    func_80034CD4((char *)work + 0x9C, 0, 0, 4);
    
skip_call:
    ptr_ea8 = *(void **)((char *)work + 0xEA8);
    value_ebc = *(short *)((char *)ptr_ea8 + 0xEBC);
    value_ebe = *(short *)((char *)ptr_ea8 + 0xEBE);
    
    func_80092508(work);
    
    value_ed0 = *(int *)((char *)work + 0xED0);
    calc1 = value_ed0 >> 7;
    calc1 += value_ebc;
    calc2 = calc1 >> 12;
    
    value_ebc = *(short *)((char *)work + 0xEBC);
    value_ebe = *(short *)((char *)work + 0xEBE);
    
    func_80092508(work);
    
    mult_result = value_ebc * value_ebe;
    div_result = mult_result / value_ebe;
    
    mult_result = div_result * calc2;
    div_result = mult_result / calc2;
    
    if (div_result < 0)
    {
        div_result = (div_result + 0xFFF) >> 12;
    }
    else
    {
        div_result = div_result >> 12;
    }
    
    value_64 = *(short *)((char *)work + 0x64);
    value_64 += div_result;
    *(short *)((char *)work + 0x64) = value_64;
    
    func_800925D8(work);
    
    mult_result = value_ebc * result;
    div_result = mult_result / result;
    
    if (div_result < 0)
    {
        div_result = (div_result + 0xFFF) >> 12;
    }
    else
    {
        div_result = div_result >> 12;
    }
    
    value_66 = *(short *)((char *)work + 0x66);
    value_66 -= div_result;
    *(short *)((char *)work + 0x66) = value_66;
}
