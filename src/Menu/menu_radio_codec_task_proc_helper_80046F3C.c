#include "Menu/menuman.h"

#define OFFSET_TO_PTR(ptr, offset) ((int)(offset) = (int)(ptr) + (int)(offset))

extern const char aFrameNumD[]; // = "frame num %d\n";

void menu_radio_codec_task_proc_helper_80046F3C(menu_chara_struct *pStru, faces_group *pFacesGroup)
{
    int                   i, j;
    face_header          *faces;
    face_anim             anim;
    face_header          *facesIter;
    void                **simpleAnimIter;
    face_full_anim       *fullAnim;
    face_full_anim_frame *fullAnimIter;

    i = pStru->field_30_face_count = pFacesGroup->field_0_face_count;
    faces = pStru->field_34_faces = pFacesGroup->field_4_faces;
    facesIter = faces;

    for (; i > 0; facesIter++, i--)
    {
        anim.intptr = OFFSET_TO_PTR(faces, facesIter->field_8_anim_data.raw_ptr);

        switch (facesIter->field_0_anim_type)
        {
        case FACE_ANIM_SIMPLE:
            // This loops translates relative offsets to real pointers
            // for all 8 pointers stored in simple_anim so that
            // they can be used directly.
            simpleAnimIter = (void *) anim.simple_anim;
            for (j = 8; j > 0; j--, simpleAnimIter++)
            {
                if (*simpleAnimIter != NULL)
                {
                    OFFSET_TO_PTR(facesIter->field_8_anim_data.raw_ptr, *simpleAnimIter);
                }
            }
            break;

        case FACE_ANIM_FULL:
            fullAnim = anim.full_anim;
            printf(aFrameNumD, fullAnim->field_0_frame_count);
            fullAnimIter = fullAnim->field_4_frames;
            for (j = 0; j < fullAnim->field_0_frame_count; fullAnimIter++, j++)
            {
                if (fullAnimIter->field_0_palette != NULL)
                {
                    OFFSET_TO_PTR(facesIter->field_8_anim_data.raw_ptr, fullAnimIter->field_0_palette);
                }
                if (fullAnimIter->field_4_image != NULL)
                {
                    OFFSET_TO_PTR(facesIter->field_8_anim_data.raw_ptr, fullAnimIter->field_4_image);
                }
            }
            break;
        }
    }
}
