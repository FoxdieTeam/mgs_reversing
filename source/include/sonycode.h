#ifndef __MGS_SONYCODE_H__
#define __MGS_SONYCODE_H__

// TODO: define additional EXE names for the demo versions.

#if defined(INTEGRAL)
#define SONY_CODE       "SLPM-86247"
#ifdef VR_EXE
#define DISC1_SONY_CODE "SLPM_862.49"
#else
#define DISC1_SONY_CODE "SLPM_862.47"
#define DISC2_SONY_CODE "SLPM_862.48"
#endif

#elif defined(VR_MISSIONS)
// TODO: Should INTEGRAL also be defined for these?
#ifdef PAL
#define SONY_CODE       "SLES-02136"
#define DISC1_SONY_CODE "SLES_021.36"
#else
#define SONY_CODE       "SLUS-00957"
#define DISC1_SONY_CODE "SLUS_009.57"
#endif

#else // ORIGINAL

#ifdef PAL
/* European version(s) */
#if defined(ENGLISH)
//#define SONY_CODE     "SLES_01370"
#define SONY_CODE       "SLES-01370"
#elif defined(GERMAN)
#define SONY_CODE       "SLES-01507"
#elif defined(FRENCH)
#define SONY_CODE       "SLES-01506"
#elif defined(ITALIAN)
#define SONY_CODE       "SLES-01508"
#elif defined(SPANISH)
#define SONY_CODE       "SLES-01734"
#endif
#define DISC1_SONY_CODE "MGS1.EXE"
#define DISC2_SONY_CODE "MGS2.EXE"
#else // PAL

#if defined(ENGLISH)
/* North American version */
#define SONY_CODE       "SLUS-00594"
#define DISC1_SONY_CODE "SLUS_005.94"
#define DISC2_SONY_CODE "SLUS_007.76"
#else
/* Japanese version */
#define SONY_CODE       "SLPM-86111"
#define DISC1_SONY_CODE "SLPM_861.11"
#define DISC2_SONY_CODE "SLPM_861.12"
#endif

#endif // PAL
#endif // INTEGRAL

#endif // __MGS_SONYCODE_H__
