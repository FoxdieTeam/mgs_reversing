#include "game/game.h"

#include "democame.h"


void s19b_democame_800DB578(SVECTOR *in, SVECTOR *out, SVECTOR *angle, int *length);
void s19b_democame_800DB5C4(SVECTOR *out, SVECTOR *in, SVECTOR *angle, int *length);

void s19b_democame_800DB470(DemoCamera *work)
{
    switch (work->type)
    {
    case 0:
        break;
    case 1:
        s19b_democame_800DB578(&work->eye, &work->center, &work->rotate, &work->track);
        break;
    case 2:
        s19b_democame_800DB5C4(&work->eye, &work->center, &work->rotate, &work->track);
        break;
    }
}

void s19b_democame_800DB4E0(SVECTOR *from, SVECTOR *to, SVECTOR *out, int *length)
{
    SVECTOR diff;

    GV_SubVec3(to, from, &diff);
    *length = GV_VecLen3(&diff);

    out->vz = 0;
    out->vy = GV_VecDir2(&diff);
    out->vx = ratan2(-diff.vy, SquareRoot0(diff.vx * diff.vx + diff.vz * diff.vz));
}

void s19b_democame_800DB578(SVECTOR *in, SVECTOR *out, SVECTOR *angle, int *length)
{
    SVECTOR dir;

    GV_DirVec3(angle, *length, &dir);
    GV_AddVec3(in, &dir, out);
}

void s19b_democame_800DB5C4(SVECTOR *out, SVECTOR *in, SVECTOR *angle, int *length)
{
    SVECTOR dir;

    GV_DirVec3(angle, *length, &dir);
    GV_SubVec3(in, &dir, out);
}

int s19b_democame_800DB610(int from, int to, int interp)
{
    return GV_NearExp2(from, to);
}

int s19b_democame_800DB630(int from, int to, int interp)
{
    return GV_NearExp4(from, to);
}

int s19b_democame_800DB650(int from, int to, int interp)
{
    return GV_NearExp8(from, to);
}

int s19b_democame_800DB670(int from, int to, int interp)
{
    return GV_NearTime(from, to, interp);
}

void s19b_democame_800DB690(SVECTOR *from, SVECTOR *to, int interp)
{
    GV_NearExp2V((short *)from, (short *)to, 3);
}

void s19b_democame_800DB6B0(SVECTOR *from, SVECTOR *to, int interp)
{
    GV_NearExp4V((short *)from, (short *)to, 3);
}

void s19b_democame_800DB6D0(SVECTOR *from, SVECTOR *to, int interp)
{
    GV_NearExp8V((short *)from, (short *)to, 3);
}

void s19b_democame_800DB6F0(SVECTOR *from, SVECTOR *to, int interp)
{
    GV_NearTimeV((short *)from, (short *)to, interp, 3);
}

void s19b_democame_800DB710(SVECTOR *from, SVECTOR *to, int interp)
{
    GV_NearExp2PV((short *)from, (short *)to, 3);
}

void s19b_democame_800DB730(SVECTOR *from, SVECTOR *to, int interp)
{
    GV_NearExp4PV((short *)from, (short *)to, 3);
}

void s19b_democame_800DB750(SVECTOR *from, SVECTOR *to, int interp)
{
    GV_NearExp8PV((short *)from, (short *)to, 3);
}

void s19b_democame_800DB770(SVECTOR *from, SVECTOR *to, int interp)
{
    GV_NearTimePV((short *)from, (short *)to, interp, 3);
}

DemocameFn1 s19b_dword_800C3AE0[] = {
    s19b_democame_800DB610,
    s19b_democame_800DB630,
    s19b_democame_800DB650,
    s19b_democame_800DB670
};

DemocameFn2 s19b_dword_800C3AF0[4] = {
    s19b_democame_800DB690,
    s19b_democame_800DB6B0,
    s19b_democame_800DB6D0,
    s19b_democame_800DB6F0
};

DemocameFn2 s19b_dword_800C3B00[4] = {
    s19b_democame_800DB710,
    s19b_democame_800DB730,
    s19b_democame_800DB750,
    s19b_democame_800DB770
};

void s19b_democame_800DB790(DemoCamera *work, DEMOCAM_KEY *key)
{
    int index;

    switch (key->mode)
    {
    case 0:
        work->eye_key = key->pos;
        work->center_key = key->param;
        s19b_democame_800DB4E0(&work->eye_key, &work->center_key, &work->rotate_key, &work->track_key);
        work->type = 0;
        break;

    case 1:
        work->eye_key = key->pos;
        work->rotate_key.vx = key->param.vx;
        work->rotate_key.vy = key->param.vy;
        work->rotate_key.vz = 0;
        work->track_key = key->param.vz;
        s19b_democame_800DB578(&work->eye_key, &work->center_key, &work->rotate_key, &work->track_key);
        work->type = 1;
        break;

    case 2:
        work->center_key = key->pos;
        work->rotate_key.vx = key->param.vx;
        work->rotate_key.vy = key->param.vy;
        work->rotate_key.vz = 0;
        work->track_key = key->param.vz;
        s19b_democame_800DB5C4(&work->eye_key, &work->center_key, &work->rotate_key, &work->track_key);
        work->type = 2;
        break;
    }

    work->interp = key->interp;
    work->time = key->time;
    work->flags = key->flags;

    index = work->interp;
    work->near_fn = s19b_dword_800C3AE0[index];
    work->near_vec_fn = s19b_dword_800C3AF0[index];
    work->near_rot_fn = s19b_dword_800C3B00[index];
}

void s19b_democame_800DB968(DemoCamera *work)
{
    SVECTOR *dst;
    SVECTOR *vec;
    SVECTOR *snap;
    int     *val;
    int     *isnap;
    int      interp;
    int      flags;

    if (work->done != 0)
    {
        return;
    }

    interp = work->time - 1;
    flags  = work->flags;

    if (flags & 1)
    {
        dst = &work->eye;
        vec = work->eye_src;
        if (vec == NULL)
        {
            vec = &work->eye_key;
        }
        if (interp == 0)
        {
            *dst = *vec;
        }
        else
        {
            work->near_vec_fn(dst, vec, interp);
        }
    }

    if (flags & 2)
    {
        dst = &work->center;
        vec = work->center_src;
        if (vec == NULL)
        {
            vec = &work->center_key;
        }
        if (interp == 0)
        {
            *dst = *vec;
        }
        else
        {
            work->near_vec_fn(dst, vec, interp);
        }
    }

    if (flags & 4)
    {
        dst = &work->rotate;
        vec = work->rotate_src;
        if (vec == NULL)
        {
            vec = &work->rotate_key;
        }
        if (interp == 0)
        {
            *dst = *vec;
        }
        else
        {
            work->near_rot_fn(dst, vec, interp);
        }
    }

    if (flags & 8)
    {
        val = work->track_src;
        if (val == NULL)
        {
            val = &work->track_key;
        }
        if (interp == 0)
        {
            work->track = *val;
        }
        else
        {
            work->track = work->near_fn(work->track, *val, interp);
        }
    }

    if (flags & 0x10)
    {
        snap = work->eye_src;
        if (snap == NULL)
        {
            snap = &work->eye_key;
        }
        work->eye = *snap;
    }

    if (flags & 0x20)
    {
        snap = work->center_src;
        if (snap == NULL)
        {
            snap = &work->center_key;
        }
        work->center = *snap;
    }

    if (flags & 0x40)
    {
        snap = work->rotate_src;
        if (snap == NULL)
        {
            snap = &work->rotate_key;
        }
        work->rotate = *snap;
    }

    if (flags & 0x80)
    {
        isnap = work->track_src;
        if (isnap == NULL)
        {
            isnap = &work->track_key;
        }
        work->track = *isnap;
    }

    if (flags & 0x100)
    {
        work->eye = GM_Camera.position;
    }

    if (flags & 0x200)
    {
        work->center = GM_Camera.target;
    }

    if (flags & 0x400)
    {
        work->rotate = GM_Camera.rotate;
    }

    if (flags & 0x800)
    {
        work->track = GM_Camera.track;
    }

    if (--work->time <= 0)
    {
        s19b_democame_800DB470(work);
        s19b_democame_800DB790(work, work->key);
        work->key++;
        work->n_keys++;
        if (work->interp == -1)
        {
            work->done = 1;
        }
        else
        {
            work->time -= work->key[-2].time;
        }
    }

    work->frame++;
}
void s19b_democame_800DB968(DemoCamera *);

void s19b_democame_800DBD38(void)
{
    /* do nothing */
}

void *NewDemoCamera(DEMOCAM_KEY *keys)
{
    DemoCamera *work;

    work = GV_NewActor(GV_ACTOR_AFTER, sizeof(DemoCamera));
    if (work)
    {
        GV_SetNamedActor(work, s19b_democame_800DB968, s19b_democame_800DBD38, "democame.c");

        work->eye = gUnkCameraStruct2_800B7868.position;
        work->center = gUnkCameraStruct2_800B7868.target;
        work->rotate = gUnkCameraStruct2_800B7868.rotate;
        work->track = gUnkCameraStruct2_800B7868.track;
        work->type = gUnkCameraStruct2_800B7868.type;

        s19b_democame_800DB470(work);
        s19b_democame_800DB790(work, keys);

        work->key = keys + 1;
        work->n_keys = 1;
    }

    return work;
}
