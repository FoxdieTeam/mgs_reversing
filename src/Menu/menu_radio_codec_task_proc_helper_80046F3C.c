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
            simpleAnimIter = anim.simple_anim->field_0_frames;
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
            mts_printf_8008BBA0(aFrameNumD, fullAnim->field_0_frame_count);
            fullAnimIter = fullAnim->field_4_frames;
            for (j = 0; j < fullAnim->field_0_frame_count; fullAnimIter++, j++)
            {
                if (fullAnimIter->field_0 != NULL)
                {
                    OFFSET_TO_PTR(facesIter->field_8_anim_data.raw_ptr, fullAnimIter->field_0);
                }
                if (fullAnimIter->field_4 != NULL)
                {
                    OFFSET_TO_PTR(facesIter->field_8_anim_data.raw_ptr, fullAnimIter->field_4);
                }
            }
            break;
        }
    }
}
