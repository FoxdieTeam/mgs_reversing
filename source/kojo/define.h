#ifndef _INC_DEFINE
#define _INC_DEFINE

#ifdef __cplusplus
extern "C" {            /* Assume C declarations for C++ */
#endif  /* __cplusplus */

#ifndef _SIZE_T_DEFINED
#ifndef _SIZE_T  /* PlayStation */
#define _SIZE_T
typedef unsigned int size_t;
#endif
#define _SIZE_T_DEFINED
#endif

/* windef.h */
#ifndef _WINDEF_

/*
 * BASETYPES is defined in ntdef.h if these types are already defined
 */

#ifndef BASETYPES
#define BASETYPES
typedef unsigned long ULONG;
typedef ULONG *PULONG;
typedef unsigned short USHORT;
typedef USHORT *PUSHORT;
typedef unsigned char UCHAR;
typedef UCHAR *PUCHAR;
typedef char *PSZ;
#endif  /* !BASETYPES */

#define MAX_PATH          260

#ifndef NULL
#ifdef __cplusplus
#define NULL    0
#else
#define NULL    ((void *)0)
#endif
#endif

#ifndef FALSE
#define FALSE               0
#endif

#ifndef TRUE
#define TRUE                1
#endif

#ifndef IN
#define IN
#endif

#ifndef OUT
#define OUT
#endif

#ifndef OPTIONAL
#define OPTIONAL
#endif

#undef far
#undef near
#define far
#define near

#ifdef _WINDOWS  /* UNIX or Macintosh */
#undef pascal
#if (_MSC_VER >= 800)
#define pascal __stdcall
#else
#define pascal
#endif
#endif

#ifdef DOSWIN32
#define cdecl _cdecl
#ifndef CDECL
#define CDECL _cdecl
#endif
#else
#define cdecl
#ifndef CDECL
#define CDECL
#endif
#endif

#if (_MSC_VER >= 800)
#define CALLBACK    __stdcall
#define WINAPI      __stdcall
#define WINAPIV     __cdecl
#define APIENTRY    WINAPI
#define APIPRIVATE  __stdcall
#define PASCAL      __stdcall
#else
#define CALLBACK
#define WINAPI
#define WINAPIV
#define APIENTRY    WINAPI
#define APIPRIVATE
#define PASCAL      pascal
#endif

#define FAR                 far
#define NEAR                near
#ifndef CONST
#define CONST               const
#endif

typedef unsigned long       DWORD;
/*typedef int                 BOOL;*/
typedef unsigned char       BYTE;
typedef unsigned short      WORD;
typedef float               FLOAT;
typedef FLOAT               *PFLOAT;
typedef BOOL near           *PBOOL;
typedef BOOL far            *LPBOOL;
typedef BYTE near           *PBYTE;
typedef BYTE far            *LPBYTE;
typedef int near            *PINT;
typedef int far             *LPINT;
typedef WORD near           *PWORD;
typedef WORD far            *LPWORD;
typedef long far            *LPLONG;
typedef DWORD near          *PDWORD;
typedef DWORD far           *LPDWORD;
typedef void far            *LPVOID;
typedef CONST void far      *LPCVOID;

typedef int                 INT;
typedef unsigned int        UINT;
typedef unsigned int        *PUINT;

typedef void                *HANDLE;

typedef HANDLE FAR          *LPHANDLE;
typedef HANDLE              HGLOBAL;
typedef HANDLE              HLOCAL;

/* winnt.h */
/*
 * Basics
 */

#ifndef VOID
#define VOID void
typedef char CHAR;
typedef short SHORT;
typedef long LONG;
#endif

/*
 * UNICODE (Wide Character) types
 */
#ifdef  UNICODE
typedef wchar_t WCHAR;    /* wc,   16-bit UNICODE character */

typedef WCHAR *PWCHAR;
typedef WCHAR *LPWCH, *PWCH;
typedef CONST WCHAR *LPCWCH, *PCWCH;
typedef WCHAR *NWPSTR;
typedef WCHAR *LPWSTR, *PWSTR;

typedef CONST WCHAR *LPCWSTR, *PCWSTR;
#endif
/*
 * ANSI (Multi-byte Character) types
 */
typedef CHAR *PCHAR;
typedef CHAR *LPCH, *PCH;

typedef CONST CHAR *LPCCH, *PCCH;
typedef CHAR *NPSTR;
typedef CHAR *LPSTR, *PSTR;
typedef CONST CHAR *LPCSTR, *PCSTR;

/*
 * Neutral ANSI/UNICODE types and macros
 */
#ifdef  UNICODE

#ifndef _TCHAR_DEFINED
typedef WCHAR TCHAR, *PTCHAR;
typedef WCHAR TBYTE , *PTBYTE ;
#define _TCHAR_DEFINED
#endif /* !_TCHAR_DEFINED */

typedef LPWSTR LPTCH, PTCH;
typedef LPWSTR PTSTR, LPTSTR;
typedef LPCWSTR LPCTSTR;
typedef LPWSTR LP;
#define __TEXT(quote) L##quote

#else   /* UNICODE */

#ifndef _TCHAR_DEFINED
typedef char TCHAR, *PTCHAR;
typedef unsigned char TBYTE , *PTBYTE ;
#define _TCHAR_DEFINED
#endif /* !_TCHAR_DEFINED */

typedef LPSTR LPTCH, PTCH;
typedef LPSTR PTSTR, LPTSTR;
typedef LPCSTR LPCTSTR;
#define __TEXT(quote) quote

#endif /* UNICODE */
#define TEXT(quote) __TEXT(quote)

typedef SHORT *PSHORT;  
typedef LONG *PLONG;    

#define DECLARE_HANDLE(name) struct name##__ { int unused; }; typedef struct name##__ *name

#define MINCHAR     0x80        
#define MAXCHAR     0x7f        
#define MINSHORT    0x8000      
#define MAXSHORT    0x7fff      
#define MINLONG     0x80000000  
#define MAXLONG     0x7fffffff  
#define MAXBYTE     0xff        
#define MAXWORD     0xffff      
#define MAXDWORD    0xffffffff  

/* windef.h */
DECLARE_HANDLE(HINSTANCE);
DECLARE_HANDLE(HWND);

#define MAKEWORD(a, b)      ((WORD)(((BYTE)(a)) | ((WORD)((BYTE)(b))) << 8))
#define MAKELONG(a, b)      ((LONG)(((WORD)(a)) | ((DWORD)((WORD)(b))) << 16))
#define LOWORD(l)           ((WORD)(l))
#define HIWORD(l)           ((WORD)(((DWORD)(l) >> 16) & 0xFFFF))
#define LOBYTE(w)           ((BYTE)(w))
#define HIBYTE(w)           ((BYTE)(((WORD)(w) >> 8) & 0xFF))

#ifndef _LIBGPU_H_  /* PlayStation */
typedef struct tagRECT
{
    LONG    left;
    LONG    top;
    LONG    right;
    LONG    bottom;
} RECT, *PRECT, NEAR *NPRECT, FAR *LPRECT;
#endif

typedef struct tagPOINT
{
    LONG  x;
    LONG  y;
} POINT, *PPOINT, NEAR *NPPOINT, FAR *LPPOINT;

typedef struct tagSIZE
{
    LONG        cx;
    LONG        cy;
} SIZE, *PSIZE, *LPSIZE;

/* windef.h */
/* Types use for passing & returning polymorphic values */
typedef UINT WPARAM;
typedef LONG LPARAM;
typedef LONG LRESULT;

typedef DWORD   COLORREF;
typedef DWORD   *LPCOLORREF;

/* wingdi.h */
#define RGB(r,g,b)          ((COLORREF)(((BYTE)(r)|((WORD)((BYTE)(g))<<8))|(((DWORD)(BYTE)(b))<<16)))

#define GetRValue(rgb)      ((BYTE)(rgb))
#define GetGValue(rgb)      ((BYTE)(((WORD)(rgb)) >> 8))
#define GetBValue(rgb)      ((BYTE)((rgb)>>16))

/* winuser.h */
#define MAKEWPARAM(l, h)      (WPARAM)MAKELONG(l, h)
#define MAKELPARAM(l, h)      (LPARAM)MAKELONG(l, h)

#endif  /* _WINDEF_ */

/*
 * Some functions have arguments that are never used.  To prevent C++ compilers
 * from issuing warnings about those arguments, the following macro can be
 * used.
 */
#ifdef __cplusplus
#define _UNUSED_ARG( x )
#else
#define _UNUSED_ARG( x ) x
#endif

/* min = 256 */
#define _MAX_TEXT 4096

#define MININT     0x80000000  
#define MAXINT     0x7fffffff  

/* stdlib.h */
/* Minimum and maximum macros */
#ifndef __max
#define __max(a,b)  (((a) > (b)) ? (a) : (b))
#endif
#ifndef __min
#define __min(a,b)  (((a) < (b)) ? (a) : (b))
#endif

/* original */
#ifndef __sign
#define __sign(a)  ((a == 0) ? (0) : ((a < 0) ? -1 : +1))
#endif

#ifndef __abs
#define __abs(a)  ((a < 0) ? (-(a)) : (a))
#endif

#ifndef __fequal
#define __fequal(a,b,c)  (((a >= (b - __abs(c))) && (a <= (b + __abs(c)))) ? (TRUE) : (FALSE))
#endif

/* stdlib.h */
/*
 * Sizes for buffers used by the _makepath() and _splitpath() functions.
 * note that the sizes include space for 0-terminator
 */
#ifndef _MAX_PATH
#define _MAX_PATH   260 /* max. length of full pathname */
#endif
#ifndef _MAX_DRIVE
#define _MAX_DRIVE  3   /* max. length of drive component */
#endif
#ifndef _MAX_DIR
#define _MAX_DIR    256 /* max. length of path component */
#endif
#ifndef _MAX_FNAME
#define _MAX_FNAME  256 /* max. length of file name component */
#endif
#ifndef _MAX_EXT
#define _MAX_EXT    256 /* max. length of extension component */
#endif

#ifdef __cplusplus
}                       /* End of extern "C" { */
#endif  /* __cplusplus */

#endif  /* _INC_DEFINE */
