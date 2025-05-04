#ifndef _FACE_H
#define _FACE_H

// Structures representing data stored in FACE.DAT

#define FACE_ANIM_SIMPLE ((unsigned short)0)
#define FACE_ANIM_FULL ((unsigned short)1)

struct face_simple_anim;
struct face_full_anim;

typedef union face_anim {
    struct face_simple_anim *simple_anim;
    struct face_full_anim   *full_anim;
    void                    *raw_ptr;
    int                      intptr;
} face_anim;

// Equivalent of:
// https://github.com/Joy-Division/tools-mgs/blob/4e9394baa8ac6872e66202ff0ce26352cd45bef9/face-extract.c#L167-L169
typedef struct face_header
{
    unsigned short field_0_anim_type;
    unsigned short field_2_code;
    int            field_4;
    face_anim      field_8_anim_data;
} face_header;

// Equivalent of:
// https://github.com/Joy-Division/tools-mgs/blob/4e9394baa8ac6872e66202ff0ce26352cd45bef9/face-extract.c#L155-L161
typedef struct faces_group
{
    int         field_0_face_count;
    face_header field_4_faces[0];

    // This is where the actual data is stored, as pointed
    // by pointers in field_4_faces. Added for
    // informative purposes, it is not referenced directly.
    char actual_data[0];
} faces_group;

typedef struct face_anim_image
{
    char         field_0_xpos;
    char         field_1_ypos;
    char         field_2_width;
    char         field_3_height;
    unsigned int field_4_image[0];
} face_anim_image;

// "Simple" animation, equivalent of:
// https://github.com/Joy-Division/tools-mgs/blob/4e9394baa8ac6872e66202ff0ce26352cd45bef9/face-extract.c#L174-L189
typedef struct face_simple_anim
{
    unsigned char   *field_0_palette;
    face_anim_image *field_4_face;
    face_anim_image *field_8_eyes[3];   // last element might not be an eye
    face_anim_image *field_14_mouth[3]; // last element might not be a mouth
} face_simple_anim;

// "Full" animation, equivalent of:
// https://github.com/Joy-Division/tools-mgs/blob/4e9394baa8ac6872e66202ff0ce26352cd45bef9/face-extract.c#L191-L203
typedef struct face_full_anim_frame
{
    unsigned char   *field_0_palette;
    face_anim_image *field_4_image;
    short            field_8;
    short            field_10;
} face_full_anim_frame;

typedef struct face_full_anim
{
    int                  field_0_frame_count;
    face_full_anim_frame field_4_frames[0];
} face_full_anim;

#endif // _FACE_H
