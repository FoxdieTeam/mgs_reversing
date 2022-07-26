#include <sys/types.h>
#include <libgte.h>

#define SCRPAD_ADDR 0x1f800000

void GetVecFromScratchpad_80028840(SVECTOR *vec)
{
	SVECTOR *vec1, *vec2;
	vec2 = (SVECTOR*)(SCRPAD_ADDR + 0x54);
	vec1 = (SVECTOR*)(SCRPAD_ADDR + 0xc);

	vec->vx = vec2->vx - vec1->vx;
	vec->vy = vec2->vz - vec1->vz;
	vec->vz = vec2->vy - vec1->vy;
}
