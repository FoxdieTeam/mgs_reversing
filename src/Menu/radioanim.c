#include "psyq.h"
#include "Game/game.h"
#include "Menu/menuman.h"
#include "mts/taskid.h"

#define OFFSET_TO_PTR2(ptr, offset) ((int)(offset) = (int)(ptr) + (int)(offset))

extern menu_0x14 stru_800BDA48[2];

int sub_80046C90(menu_chara_struct_sub *pSub, int idx, face_full_anim *pFullAnim, int pFrameNum)
{
    face_full_anim_frame *fullAnimFrame;
    short                 field_10;
    unsigned int          tmp;

    while (1)
    {
        if (pFrameNum >= pFullAnim->field_0_frame_count)
        {
            return 0;
        }

        fullAnimFrame = &pFullAnim->field_4_frames[pFrameNum];
        if (fullAnimFrame->field_0_palette == NULL && fullAnimFrame->field_4_image == NULL)
        {
            tmp = fullAnimFrame->field_8;
            switch (tmp)
            {
            case 0:
                GM_SeSet2_80032968(0, 0x3f, fullAnimFrame->field_10);
                pFrameNum++;
                break;

            case 1:
                if (pSub->field_4C_leftCodecPortraitFrame == 0)
                {
                    pSub->field_4C_leftCodecPortraitFrame = fullAnimFrame->field_10;
                }

                if (pSub->field_4C_leftCodecPortraitFrame < 255)
                {
                    if (pSub->field_4C_leftCodecPortraitFrame == 1)
                    {
                        return 0;
                    }
                    pSub->field_4C_leftCodecPortraitFrame--;
                }
                pFrameNum = 0;
                break;

            default:
                pFrameNum++;
                break;
            }
        }
        else
        {
            if (fullAnimFrame->field_10 > 0)
            {
                sub_80046BD8(idx);
            }
            menu_radio_load_palette_80046B74(fullAnimFrame->field_0_palette, idx);
            sub_80046B10(fullAnimFrame->field_4_image, idx);

            pSub->field_E = fullAnimFrame->field_8;

            tmp = pFrameNum;
            field_10 = fullAnimFrame->field_10;

            pSub->field_8_animFrameNum = tmp;
            pSub->field_A = field_10;
            pSub->field_C = field_10;
            return 1;
        }
    }
}

void menu_radio_draw_face_helper_helper_80046DF4(int idx, menu_chara_struct *pChara, int chara, int code, int a5)
{
    int                    i;
    face_header           *faceIter;
    face_simple_anim      *simpleAnim;
    face_full_anim        *fullAnim;
    menu_chara_struct_sub *pSub;

    pSub = &pChara->field_3C[idx];

    if (code == 0)
    {
        pSub->field_0_animState = 3;
        pSub->field_14_face_anim.raw_ptr = NULL;
        pSub->field_2_chara = chara;
    }
    else
    {
        faceIter = pChara->field_34_faces;

        for (i = pChara->field_30_face_count; i > 0; faceIter++, i--)
        {
            if (faceIter->field_2_code == code)
            {
                pSub->field_2_chara = chara;

                switch (faceIter->field_0_anim_type)
                {
                case FACE_ANIM_SIMPLE:
                    simpleAnim = faceIter->field_8_anim_data.simple_anim;
                    if (a5 >= 0)
                    {
                        sub_80046BD8(idx);
                    }

                    menu_radio_load_palette_80046B74(simpleAnim->field_0_palette, idx);
                    sub_80046B10(simpleAnim->field_4_face, idx);
                    pSub->field_0_animState = 1;
                    pSub->field_A = a5;
                    pSub->field_C = a5;
                    pSub->field_14_face_anim.simple_anim = simpleAnim;
                    pSub->field_4C_leftCodecPortraitFrame = 0;
                    pSub->field_E = 0;
                    return;

                case FACE_ANIM_FULL:
                    fullAnim = faceIter->field_8_anim_data.full_anim;
                    pSub->field_8_animFrameNum = 0;
                    pSub->field_4C_leftCodecPortraitFrame = 0;
                    sub_80046C90(pSub, idx, fullAnim, pSub->field_8_animFrameNum);
                    pSub->field_0_animState = 2;
                    pSub->field_14_face_anim.full_anim = fullAnim;
                    return;

                default:
                    return;
                }
            }
        }

        printf("NO_FACE_DATA\n");
    }
}

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
        anim.intptr = OFFSET_TO_PTR2(faces, facesIter->field_8_anim_data.raw_ptr);

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
                    OFFSET_TO_PTR2(facesIter->field_8_anim_data.raw_ptr, *simpleAnimIter);
                }
            }
            break;

        case FACE_ANIM_FULL:
            fullAnim = anim.full_anim;
            printf("frame num %d\n", fullAnim->field_0_frame_count);
            fullAnimIter = fullAnim->field_4_frames;
            for (j = 0; j < fullAnim->field_0_frame_count; fullAnimIter++, j++)
            {
                if (fullAnimIter->field_0_palette != NULL)
                {
                    OFFSET_TO_PTR2(facesIter->field_8_anim_data.raw_ptr, fullAnimIter->field_0_palette);
                }
                if (fullAnimIter->field_4_image != NULL)
                {
                    OFFSET_TO_PTR2(facesIter->field_8_anim_data.raw_ptr, fullAnimIter->field_4_image);
                }
            }
            break;
        }
    }
}

unsigned char *menu_gcl_read_word_80047098(int *pOut, unsigned char *pScript)
{
    *pOut = (pScript[1]) | (pScript[0] << 8);
    return pScript + sizeof(short);
}

//menu_set_struct
void menu_800470B4(int idx, menu_chara_struct *pStru, int chara, int code, int faceUnk, int taskWup)
{
    stru_800BDA48[idx].field_0_bUnknown = 1;
    stru_800BDA48[idx].field_10_pCharaStru = pStru;
    stru_800BDA48[idx].field_4_chara = chara;
    stru_800BDA48[idx].field_8_code = code;
    stru_800BDA48[idx].field_C = faceUnk;
    stru_800BDA48[idx].field_2_bTaskWup = taskWup;
}

void menu_radio_draw_face_helper_800470F4(int idx)
{
  if (stru_800BDA48[idx].field_0_bUnknown)
  {
    menu_radio_draw_face_helper_helper_80046DF4(idx, stru_800BDA48[idx].field_10_pCharaStru, stru_800BDA48[idx].field_4_chara, stru_800BDA48[idx].field_8_code, stru_800BDA48[idx].field_C);
    if (!stru_800BDA48[idx].field_8_code)
    {
      if (stru_800BDA48[idx].field_2_bTaskWup)
      {
        mts_wup_tsk_8008A540(MTSID_CD_READ);
        stru_800BDA48[idx].field_2_bTaskWup = 0;
      }
    }
    stru_800BDA48[idx].field_0_bUnknown = 0;
  }
}