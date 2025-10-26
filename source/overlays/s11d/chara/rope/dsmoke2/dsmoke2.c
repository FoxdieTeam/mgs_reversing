#include "dsmoke2.h"
#include "libgcl/libgcl.h"

// External globals
extern char s11d_dword_800D1E6C[];  // Name string "dsmoke2"
extern int GV_Clock;

// Forward declarations for all 12 functions
int s11d_dsmoke2_800CC08C(DSmoke2Work *work, SVECTOR *arg1);
void s11d_dsmoke2_800CC0E0(DSmoke2Work *work, SVECTOR *arg1);
void s11d_dsmoke2_800CC1DC(DSmoke2Work *work, int arg1);
void s11d_dsmoke2_800CC418(DSmoke2Work *work);
void s11d_dsmoke2_800CC4B8(DSmoke2Work *work);
void s11d_dsmoke2_800CC648(DSmoke2Work *work);
void s11d_dsmoke2_800CC730(DSmoke2Work *work);
void s11d_dsmoke2_800CC794(DSmoke2Work *work, int arg1);
void s11d_dsmoke2_800CCAB4(DSmoke2Work *work);
int s11d_dsmoke2_800CCC60(DSmoke2Work *work, int where, int argc);
void s11d_dsmoke2_800CCCE0(DSmoke2Work *work);
void *s11d_dsmoke2_800CCD54(int name, int where, int argc, char **argv);

// s11d_dsmoke2_800CC08C - Check if position is in range (26 lines)
int s11d_dsmoke2_800CC08C(DSmoke2Work *work, SVECTOR *arg1)
{
    short val1, val2;
    short range_min, range_max;
    
    val1 = *(short *)((char *)work + 0x6E);
    val2 = *(short *)((char *)work + 0x76);
    
    if (val2 < val1)
    {
        range_max = val1 + 2000;
        range_min = val1 - 2000;
    }
    else
    {
        range_max = val1 + 2000;
        range_min = val2 - 2000;
    }
    
    if (arg1->vy < range_min || arg1->vy > range_max)
    {
        return 1;
    }
    
    return 0;
}

// s11d_dsmoke2_800CC0E0 - Vector operations helper (68 lines)
void s11d_dsmoke2_800CC0E0(DSmoke2Work *work, SVECTOR *arg1)
{
    // Uses GV_SubVec3 and other vector operations
    // TBD - needs detailed assembly analysis
}

// s11d_dsmoke2_800CC1DC - Major update function (148 lines)
void s11d_dsmoke2_800CC1DC(DSmoke2Work *work, int arg1)
{
    // Large function with collision checks
    // TBD - needs detailed assembly analysis
}

// s11d_dsmoke2_800CC418 - Helper function (45 lines)  
void s11d_dsmoke2_800CC418(DSmoke2Work *work)
{
    // Medium complexity helper
    // TBD - needs detailed assembly analysis
}

// s11d_dsmoke2_800CC4B8 - Primitive rendering (105 lines)
void s11d_dsmoke2_800CC4B8(DSmoke2Work *work)
{
    // Handles primitive rendering based on field_284-28A
    // TBD - needs detailed assembly analysis
}

// s11d_dsmoke2_800CC648 - Act function (63 lines)
void s11d_dsmoke2_800CC648(DSmoke2Work *work)
{
    GM_CurrentMap = work->field_B0;
    
    if (work->field_BC != 0)
    {
        work->field_BC--;
        return;
    }
    
    if (work->field_B4 < 0)
    {
        return;
    }
    
    if (work->field_B2 == 0)
    {
        if (work->field_B8 != work->field_B6)
        {
            work->field_B2 = 1;
        }
        
        if (work->field_B6 - 24 >= work->field_B8 && 
            work->field_B8 >= work->field_B6 - 18)
        {
            s11d_dsmoke2_800CC1DC(work, work->field_84 + 0x6C);
        }
        
        s11d_dsmoke2_800CC418(work);
        
        work->field_B8++;
        return;
    }
    
    s11d_dsmoke2_800CCCE0(work);
}

// s11d_dsmoke2_800CC730 - Die function (30 lines)
void s11d_dsmoke2_800CC730(DSmoke2Work *work)
{
    void **ptr;
    int i;

    ptr = (void **)work->prims;
    for (i = 0; i < 16; i++)
    {
        if (*ptr != NULL)
        {
            GM_FreeObject((OBJECT *)*ptr);
            DG_FreePrim((DG_PRIM *)*ptr);
        }
        ptr++;
    }
}

// s11d_dsmoke2_800CC794 - Main rendering/update (205 lines)
void s11d_dsmoke2_800CC794(DSmoke2Work *work, int arg1)
{
    // Largest function - main rendering logic
    // Accesses field_280, field_284-28A
    // TBD - needs detailed assembly analysis
}

// s11d_dsmoke2_800CCAB4 - GCL operations (112 lines)
void s11d_dsmoke2_800CCAB4(DSmoke2Work *work)
{
    // GCL-related operations using field_98 array
    // TBD - needs detailed assembly analysis  
}

// s11d_dsmoke2_800CCC60 - Init function (37 lines)
int s11d_dsmoke2_800CCC60(DSmoke2Work *work, int where, int argc)
{
    int i;
    int *gcl_ptr;
    
    if (GCL_GetOption('p') == 0)
    {
        return -1;
    }
    
    gcl_ptr = (int *)&work->field_98;
    i = 0;
    
    while (i < 3)
    {
        if (GCL_GetParamResult() == 0)
        {
            break;
        }
        
        if (i == 3)
        {
            GCL_StrToInt((unsigned char *)gcl_ptr);
            gcl_ptr += 2;
            i++;
        }
    }
    
    work->field_94 = i;
    return 0;
}

// s11d_dsmoke2_800CCCE0 - Small helper (34 lines)
void s11d_dsmoke2_800CCCE0(DSmoke2Work *work)
{
    s11d_dsmoke2_800CCAB4(work);
    s11d_dsmoke2_800CC794(work, 0);
    s11d_dsmoke2_800CC0E0(work, NULL);
}

// s11d_dsmoke2_800CCD54 - Constructor (40 lines)
void *s11d_dsmoke2_800CCD54(int name, int where, int argc, char **argv)
{
    DSmoke2Work *work;
    
    work = (DSmoke2Work *)GV_NewActor(6, sizeof(DSmoke2Work));
    if (work != NULL)
    {
        GV_SetNamedActor(&work->actor,
                         s11d_dsmoke2_800CC648,
                         s11d_dsmoke2_800CC730,
                         s11d_dword_800D1E6C);
        
        if (s11d_dsmoke2_800CCC60(work, where, argc) < 0)
        {
            GV_DestroyActor(&work->actor);
            return NULL;
        }
        
        return work;
    }
    
    return NULL;
}
