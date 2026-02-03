#include "landing.h"
#include "game/strctrl.h"
#include "game/game.h"
#include "libgcl/libgcl.h"
#include "takabe/thing.h"

#if 0 /* WIP: keep asm authoritative; disable C until matching */
// Landing system global variables
unsigned char landing_byte_800C3324;
int           landing_int_800C3328;
int           landing_int_800C332C;
int           landing_int_800C3330;
unsigned char landing_byte_800C3334;
unsigned char landing_byte_800C3335;
int           landing_int_800C3338;
int           landing_int_800C333C;
int           landing_int_800C3340;
int           landing_int_800C3344;

// Tier 1: Simple getter functions

// Returns landing_int_800C332C
int s11d_landing_800CD094(void)
{
    return landing_int_800C332C;
}

// Returns landing_byte_800C3334
unsigned char s11d_landing_800CD0A4(void)
{
    return landing_byte_800C3334;
}

// Returns landing_byte_800C3335
unsigned char s11d_landing_800CD0B4(void)
{
    return landing_byte_800C3335;
}

// Returns true if landing_int_800C3338 is non-zero
int s11d_landing_800CD0C4(void)
{
    return landing_int_800C3338 != 0;
}

// Returns landing_int_800C3328
int s11d_landing_800CD144(void)
{
    return landing_int_800C3328;
}

// Tier 2: Simple setter function

// Sets landing_int_800C3340 and landing_int_800C3344
void s11d_landing_800CCEA8(int arg0, int arg1)
{
    landing_int_800C3340 = arg0;
    landing_int_800C3344 = arg1;
}

// Tier 3A: Simple logic functions

// Compares landing_int_800C332C with arg, returns bool based on landing_int_800C3338 comparison
int s11d_landing_800CD0D4(int arg)
{
    if (landing_int_800C332C == arg)
    {
        return landing_int_800C3338 == 0;
    }
    return 0;
}

// Checks landing_byte_800C3334 == 1, updates landing_int_800C3330 if condition met
void s11d_landing_800CD10C(void)
{
    if (landing_byte_800C3334 == 1)
    {
        landing_int_800C3330++;
    }
}

// Array indexing logic - stores value in array if landing_byte_800C3324 != 6
void s11d_landing_800CCE64(int index, int value)
{
    if (landing_byte_800C3324 != 6)
    {
        // Array at 0x800D1F8C - needs proper declaration
        // For now, using extern reference
        extern int landing_array_800D1F8C[];
        landing_array_800D1F8C[index] = value;
    }
}

// Tier 3B: Initialization function

// Main initialization - resets all landing system state and stops audio stream if active
void s11d_landing_800CCDE0(void)
{
    int status;

    // Initialize all global variables to default state
    landing_byte_800C3324 = 0;          // Reset state byte
    landing_int_800C3328  = -1;         // Initialize to -1 (invalid/unset)
    landing_int_800C332C  = -1;         // Initialize to -1
    landing_int_800C3330  = -1;         // Initialize to -1
    landing_byte_800C3334 = 0;          // Reset status byte
    landing_byte_800C3335 = 0;          // Reset status byte
    landing_int_800C3338  = -1;         // Initialize to -1
    landing_int_800C333C  = -1;         // Initialize to -1
    landing_int_800C3340  = 0;          // Initialize to 0 (delay slot execution)
    landing_int_800C3344  = 0;          // Initialize to 0

    // Check audio stream status
    status = GM_StreamStatus();

    // If stream is active (status != -1), stop it
    if (status != -1)
    {
        GM_StreamPlayStop();
    }
}

// Tier 4: Main entry point / constructor

// Main entry point - creates and initializes a landing zone actor
// Returns actor pointer on success, NULL on failure
GV_ACT *s11d_landing_800CDA20(int arg0, int arg1)
{
    LandingWork *work;
    int          init_result;

    // Allocate actor with execution level 5, size 0x914 (2324 bytes)
    work = (LandingWork *)GV_NewActor(5, sizeof(LandingWork));

    // Check allocation success
    if (work == NULL)
    {
        return NULL;
    }

    // Register actor callbacks with the game engine
    // act_func: s11d_landing_800CD154 - called every frame
    // die_func: s11d_landing_800CD378 - called on cleanup
    GV_SetNamedActor(&work->actor,
                     (GV_ACTFUNC)s11d_landing_800CD154,
                     (GV_ACTFUNC)s11d_landing_800CD378,
                     "landing.c");

    // Initialize landing-specific data
    init_result = s11d_landing_800CD810(work, arg0, arg1);

    // Check initialization success (negative = error)
    if (init_result < 0)
    {
        // Initialization failed, clean up and return NULL
        GV_DestroyActor(&work->actor);
        return NULL;
    }

    // Success - return actor pointer
    return &work->actor;
}

// Initialization function - sets up landing zone with game data
// Returns 0 on success, -1 on failure
int s11d_landing_800CD810(LandingWork *work, int arg1, int arg2)
{
    char *param_p;
    char *param_d;
    int   name_code;
    int   result;

    // Initialize CONTROL structure (movement/collision)
    if (GM_InitControl(&work->control, arg1, arg2) < 0)
    {
        return -1;
    }

    // Get GCL script parameters
    param_p = GCL_GetOption('p'); // Position parameter
    param_d = GCL_GetOption('d'); // Direction/model parameter

    // Configure control with position and direction strings
    GM_ConfigControlString(&work->control, param_p, param_d);

    // Configure hazard/collision settings (height=0, flags=-2)
    GM_ConfigControlHazard(&work->control, 0, -2, 7);

    // Hash and store identifier string
    work->name_hash = GV_StrCode("landing");

    // Hash the model name
    name_code = GV_StrCode(param_d);

    // Initialize 3D object (flag 0x2D = specific render/update flags)
    GM_InitObject(&work->object, name_code, 0x2D);

    // Configure object joint/skeleton
    GM_ConfigObjectJoint(&work->object);

    // Get hashed name again (redundant but matches assembly)
    GV_StrCode(param_d);

    // Configure motion control with various data buffers
    // Offsets: +0x180, +0x1D0, +0x434, control, +0x698
    GM_ConfigMotionControl(&work->object,
                          (MOTION_SEGMENT *)(work->field_A0 + 0xE0),  // +0x180
                          (MOTION_SEGMENT *)(work->field_A0 + 0x130), // +0x1D0
                          (MOTION_SEGMENT *)(work->field_A0 + 0x394), // +0x434
                          &work->control,
                          (MOTION_SEGMENT *)(work->field_A0 + 0x5F8)); // +0x698

    // Configure object lighting (+0x798)
    GM_ConfigObjectLight(&work->object, (MATRIX *)(work->field_A0 + 0x6F8));

    // Configure object action/animation
    GM_ConfigObjectAction(&work->object, 0, arg1, arg2);

    // Optional: Get and parse GCL option 'e' (enemy/event?)
    result = GCL_GetOption('e');
    if (result != 0)
    {
        work->field_910 = GCL_StrToInt(GCL_GetParamResult());
    }
    else
    {
        work->field_910 = -1;
    }

    // Optional: Get and parse GCL option 'c' (count/config?)
    result = GCL_GetOption('c');
    if (result != 0)
    {
        work->field_90C = GCL_StrToInt(GCL_GetParamResult());
    }
    else
    {
        work->field_90C = -1;
    }

    // Optional: Get and parse GCL option 'l' (limit/level?)
    result = GCL_GetOption('l');
    if (result != 0)
    {
        work->field_904 = GCL_StrToInt(GCL_GetParamResult());
    }
    else
    {
        work->field_904 = -16500; // Default value 0xBF8C
    }

    // Call helper initialization functions
    if (s11d_landing_800CD424(&work->object) < 0)
    {
        return -1;
    }

    if (s11d_landing_800CD614(&work->object) < 0)
    {
        return -1;
    }

    // Create shadow for the helicopter
    work->shadow = NewShadow(/* TODO: determine parameters from assembly */);

    // Initialize counter/flags
    work->field_908 = 0;

    // Call info system (parameters: 1, 0x7530)
    // extern void s11d_info_800CDAAC(int, int);
    // s11d_info_800CDAAC(1, 0x7530);

    return 0; // Success
}

// Die function - cleanup when landing actor is destroyed
void s11d_landing_800CD378(GV_ACT *actor)
{
    LandingWork *work;
    extern void s11d_info_800CDAF8(void);  // Info system cleanup

    // Cast actor back to LandingWork
    work = (LandingWork *)actor;

    // Call info system cleanup
    s11d_info_800CDAF8();

    // Free movement/collision system
    GM_FreeControl(&work->control);

    // Free 3D object and rendering resources
    GM_FreeObject(&work->object);

    // Free graphics primitive at offset 0x7D8 if allocated
    if (work->field_7D8 != NULL)
    {
        DG_DequeuePrim(work->field_7D8);
        DG_FreePrim(work->field_7D8);
    }

    // Free graphics primitive at offset 0x800 if allocated
    if (work->field_800 != NULL)
    {
        DG_DequeuePrim(work->field_800);
        DG_FreePrim(work->field_800);
    }

    // Free shadow if allocated
    if (work->shadow != NULL)
    {
        GV_DestroyOtherActor(work->shadow);
    }

    // Clear global game flags (AND with mask 0xEFB5DFFF)
    // This clears specific bits related to landing zone state
    *(unsigned int *)0x800BB3CC &= 0xEFB5DFFF;
}

// Helper function - initializes graphics primitives for landing zone
// Parameter: object pointer (OBJECT* from work+0x9C)
// Returns: 0 on success, -1 on failure
int s11d_landing_800CD424(OBJECT *object)
{
    void *prim;
    void *texture;
    int   name_hash;
    LandingWork *work;
    extern void *DG_MakePrim(int type, int count, int unk, void *objs, void *parent);
    extern void DG_QueuePrim(void *prim);
    extern void *DG_GetTexture(int hash);

    // Get work pointer from object (object is at offset 0x9C)
    work = (LandingWork *)((char *)object - 0x9C);

    // Create graphics primitive (type=18, count=1, unk=0, objs=work->field_878, parent=NULL)
    // field_878 = object base (0x9C) + 0x7DC = 0x878
    prim = DG_MakePrim(18, 1, 0, (void *)((char *)work + 0x878), NULL);

    if (prim != NULL)
    {
        // Queue primitive for rendering
        DG_QueuePrim(prim);

        // Copy global value to prim field
        *(short *)((char *)prim + 0x28) = *(short *)0x800BB9B0;

        // Store primitive pointer in work structure
        work->field_7D8 = prim;
    }

    // Hash texture/model name and load it
    name_hash = GV_StrCode("landing_t"); // String at 0x800D1E84
    texture = DG_GetTexture(name_hash);

    // Check if texture loaded successfully
    if (texture == NULL)
    {
        return -1; // Failure
    }

    // Initialize primitive structure fields
    // This involves setting up vertex data, texture coordinates, etc.
    // The assembly has two loops that initialize various bytes/halfwords
    // in the primitive structure - this is hardware-specific PS1 graphics setup

    // Loop 1: Initialize 2 elements in primitive array
    {
        void *prim_elem = prim;
        int i;
        for (i = 0; i < 2; i++)
        {
            void *prim_data = *(void **)((char *)prim_elem + 0x40);

            // Set various primitive fields (PS1 GPU packet data)
            *(unsigned char *)((char *)prim_data + 0x03) = 9;    // Command byte
            *(unsigned char *)((char *)prim_data + 0x07) = 0x2E; // Texture mode
            *(unsigned char *)((char *)prim_data + 0x04) = 0x48; // Color R
            *(unsigned char *)((char *)prim_data + 0x05) = 0x48; // Color G
            *(unsigned char *)((char *)prim_data + 0x06) = 0x48; // Color B

            // Copy and adjust vertex/UV data from source
            // (Detailed byte manipulation omitted for brevity)

            prim_elem = (void *)((char *)prim_elem + 4); // Next element
        }
    }

    // Loop 2: Copy vertex/UV data (4 iterations)
    {
        char *src = (char *)0x800BB39C; // Global vertex data source
        char *dst = (char *)work + 0x7E0; // Destination in work structure
        int i;
        for (i = 0; i < 4; i++)
        {
            // Copy 8 bytes with conditional modifications based on index bit flags
            // (Simplified - actual code does bitwise conditional stores)
            *(int *)(dst + 0) = *(int *)(src + 0);
            *(int *)(dst + 4) = *(int *)(src + 4);

            src += 8;
            dst += 8;
        }
    }

    // Copy 32 bytes of data from global constant to work structure
    {
        int *src = (int *)0x800AD430;
        int *dst = (int *)((char *)work + 0x878);
        int i;
        for (i = 0; i < 8; i++) // 32 bytes = 8 ints
        {
            dst[i] = src[i];
        }
    }

    // Set field in primitive
    *(short *)((char *)prim + 0x2E) = 2000; // Distance or scale value

    return 0; // Success
}

// Helper function - initializes additional graphics primitives (8 instances)
// Parameter: object pointer (OBJECT* from work+0x9C)
// Returns: 0 on success, -1 on failure
int s11d_landing_800CD614(OBJECT *object)
{
    void *prim;
    void *texture;
    int   name_hash;
    LandingWork *work;
    extern void *DG_MakePrim(int type, int count, int unk, void *objs, void *parent);
    extern void DG_QueuePrim(void *prim);
    extern void *DG_GetTexture(int hash);

    // Get work pointer from object (object is at offset 0x9C)
    work = (LandingWork *)((char *)object - 0x9C);

    // Create 8 graphics primitives (vs 1 in CD424)
    // field_8A0 = object base (0x9C) + 0x804 = 0x8A0
    prim = DG_MakePrim(18, 8, 0, (void *)((char *)work + 0x8A0), NULL);

    if (prim != NULL)
    {
        // Queue primitive for rendering
        DG_QueuePrim(prim);

        // Copy global value to prim field
        *(short *)((char *)prim + 0x28) = *(short *)0x800BB9B0;

        // Store primitive pointer in work structure at field_800
        work->field_800 = prim;

        // Clear the field (overwrite previous value)
        *(short *)((char *)prim + 0x28) = 0;
    }

    // Hash and load different texture (different from CD424)
    name_hash = GV_StrCode("landing_r"); // String at 0x800D1E8C (different texture)
    texture = DG_GetTexture(name_hash);

    // Check if texture loaded successfully
    if (texture == NULL)
    {
        return -1; // Failure
    }

    // Initialize primitive structure fields
    // Triple nested loop structure: 2 outer × 8 middle × 4 inner = 64 total operations
    // This is more complex than CD424 due to 8 primitives vs 1

    {
        void *prim_iter = prim;
        int outer, middle, inner;

        for (outer = 0; outer < 2; outer++)
        {
            for (middle = 0; middle < 8; middle++)
            {
                void *prim_data = *(void **)((char *)prim_iter + 0x40);
                void *data_ptr = (void *)((char *)prim_data + 0x0E);

                // Set GPU command bytes (different colors than CD424: 0x22 vs 0x48)
                *(unsigned char *)((char *)data_ptr - 11) = 9;    // GPU command
                *(unsigned char *)((char *)data_ptr - 7)  = 0x2E; // Texture mode
                *(unsigned char *)((char *)data_ptr - 10) = 0x30; // Color R (lighter)
                *(unsigned char *)((char *)data_ptr - 9)  = 0x30; // Color G
                *(unsigned char *)((char *)data_ptr - 8)  = 0x30; // Color B

                // Inner loop: Copy/adjust vertex and UV data (4 vertices per primitive)
                for (inner = 0; inner < 4; inner++)
                {
                    // Simplified: actual assembly does complex byte manipulation
                    // with conditional stores based on bit flags
                    // (PS1-specific GPU packet setup)
                }

                prim_iter = (void *)((char *)prim_iter + 0x28); // Next primitive element
            }

            prim_iter = (void *)((char *)prim_iter + 0x01F4); // Outer loop increment
        }
    }

    // Copy 32 bytes of static data (same source as CD424)
    {
        int *src = (int *)0x800AD430;
        int *dst = (int *)((char *)work + 0x8A0); // Different destination offset
        int i;
        for (i = 0; i < 8; i++) // 32 bytes = 8 ints
        {
            dst[i] = src[i];
        }
    }

    return 0; // Success
}

// Act function - called every frame to update landing zone
void s11d_landing_800CD154(GV_ACT *actor)
{
    LandingWork *work;
    int counter;
    extern void GM_ActObject(OBJECT *object);
    extern void GM_ActControl(CONTROL *control);
    extern void GM_ConfigObjectRoot(OBJECT *object, CONTROL *control, SVECTOR *vec);
    extern void DG_SetPos2(SVECTOR *src, SVECTOR *dst);
    extern void sub_8001FF2C(int, int, int); // Unknown function
    extern void sub_80032968(int, int, int); // Sound playback
    extern void sub_8005D58C(void *, int);   // Unknown function

    // Cast to LandingWork
    work = (LandingWork *)actor;

    // Update object and control systems every frame
    GM_ActObject(&work->object);
    GM_ActControl(&work->control);

    // Update rotation: combine base rotation + offset
    work->control.rot.vz = work->field_B4 + work->field_904;

    // Configure object transformation root
    GM_ConfigObjectRoot(&work->object, &work->control, NULL);

    // Set position for rendering
    DG_SetPos2(&work->control.mov, (SVECTOR *)((char *)work + 0x798));

    // Copy data from global buffer to work structure (unaligned)
    {
        int *src = (int *)0x800B77B8;
        int *dst = (int *)((char *)work + 0);
        // Simplified: actual code uses lwl/lwr/swl/swr for unaligned copy
        // Copying 8 bytes
    }

    // Store rotation value
    work->control.turn.vy = work->field_B4;

    // Check counter (field_908)
    counter = work->field_908;

    if (counter < 0)
    {
        // Disabled state - skip rest of update
        return;
    }

    // Increment frame counter
    work->field_908 = counter + 1;

    // First frame initialization
    if (counter == 0)
    {
        // Set global flags (0x104A2000)
        *(unsigned int *)0x800BB3CC |= 0x104A2000;

        // Call initialization function
        sub_8001FF2C(work->field_90C, 0, 0x104A2000);
    }

    // Update primitive positions from control position
    if (work->field_7D8 != NULL)
    {
        void *prim = work->field_7D8;
        *(int *)((char *)prim + 0x14) = work->control.mov.vx;
        *(int *)((char *)prim + 0x18) = work->control.mov.vy;
        *(int *)((char *)prim + 0x1C) = work->control.mov.vz;
    }

    // Animation phase based on counter
    if (counter < 17)
    {
        // Early phase: use field_904 value
        if (work->field_7D8 != NULL)
        {
            *(int *)((char *)work->field_7D8 + 0x18) = work->field_904;
        }
    }
    else
    {
        // Later phase: use constant value
        if (work->field_7D8 != NULL)
        {
            *(int *)((char *)work->field_7D8 + 0x18) = 0xCB44; // -13500
        }
    }

    // First 16 frames: copy positions from second primitive set
    if (counter < 16)
    {
        if (work->field_800 != NULL)
        {
            void *prim2 = work->field_800;
            void *obj_field = (void *)((char *)&work->object + 0x130); // object+0x1CC from object base

            *(int *)((char *)prim2 + 0x14) = *(int *)((char *)obj_field + 0);
            *(int *)((char *)prim2 + 0x18) = *(int *)((char *)obj_field + 4);
            *(int *)((char *)prim2 + 0x1C) = *(int *)((char *)obj_field + 8);
        }
    }

    // Frame-specific events
    if (counter == 8)
    {
        // Play helicopter sound at frame 8
        sub_80032968(0, 0x3F, 0x80);
    }

    if (counter == 24)
    {
        // Play landing sound at frame 24
        sub_80032968(0, 0x3F, 0x81);

        // Trigger game events
        sub_8005D58C((void *)0x800C3348, 1);
        sub_8005D58C((void *)0x800C334C, 2);
    }

    // Check for completion/cleanup trigger
    if (work->field_B6 != 0)
    {
        // Trigger final event
        work->field_198 = 0;
        work->field_1C0 = 15;
        sub_8001FF2C(work->field_910, 0, 15);

        // Disable further updates
        work->field_908 = -1;
    }
}

// State machine - manages landing zone global state and coordination
// This function coordinates multiple landing zones and handles timeouts
void s11d_landing_800CCEBC(void)
{
    int prev_stream_status;
    int stream_status;
    int timeout_flag = 0;
    extern int GM_StreamStatus(void);
    extern void GM_StreamPlayStop(void);
    extern void sub_8008BBA0(const char *, int);
    extern void sub_80037E40(void);

    // Countdown timer for deferred initialization
    if (landing_int_800C3344 != 0)
    {
        landing_int_800C3344--;

        if (landing_int_800C3344 == 0)
        {
            // Timer expired - call initialization with stored parameter
            s11d_landing_800CCDE0();
            landing_int_800C3344 = 0;
        }
    }

    // Get previous and current stream status
    prev_stream_status = landing_int_800C3328;
    stream_status = GM_StreamStatus();

    // Reset status bytes
    landing_byte_800C3334 = 0;
    landing_int_800C3328 = stream_status;
    landing_byte_800C3335 = 0;

    // Early exit if system disabled
    if (landing_int_800C3338 < 0)
    {
        return;
    }

    // State machine based on landing_byte_800C3324
    if (landing_byte_800C3324 == 0)
    {
        // State 0: Initialize from landing array
        landing_int_800C332C = -1;
        landing_byte_800C3334 = 1;
        landing_int_800C3330 = landing_array_800D1F8C[0];

        // Copy 5 elements from landing_array (simplified)
        {
            int i;
            for (i = 0; i < 5; i++)
            {
                // Array copy logic
                // (actual implementation copies with complex pointer arithmetic)
            }
        }

        landing_int_800C333C = -1;
        landing_int_800C3338 = -1;
        landing_byte_800C3324--;
    }
    else if (prev_stream_status == landing_byte_800C3324)
    {
        // State match: Reset and re-initialize
        if (landing_byte_800C3324 != 0)
        {
            landing_int_800C333C = 0;
            landing_int_800C3338 = 0;
            landing_byte_800C3335 = 1;
            landing_int_800C332C = landing_array_800D1F8C[0];
            sub_80037E40();
        }
    }
    else
    {
        // Active state: Increment counters and check conditions
        if (prev_stream_status == 2)
        {
            landing_int_800C3338++;
        }

        // Increment timeout counter
        landing_int_800C333C++;

        // Check for timeout (5401 frames ≈ 90 seconds at 60fps)
        if (landing_int_800C333C >= 5401)
        {
            // Timeout reached
            timeout_flag = 1;
            sub_8008BBA0("landing", landing_int_800C332C);
            GM_StreamPlayStop();
            return;
        }

        // Check stream status conditions
        if (stream_status == -1 && timeout_flag == 1)
        {
            return;
        }
    }
}


#endif /* WIP: landing.c disabled (wrapped) */
