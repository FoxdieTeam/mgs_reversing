#ifndef LINKER_H_
#define LINKER_H_

#define SECTION(x) __attribute__((section(x)))

#define COUNTOF(x) sizeof(x) / sizeof(x[0])

#define CTASTR2(pre, post) pre##post
#define CTASTR(pre, post) CTASTR2(pre, post)
#define STATIC_ASSERT(cond, msg, line)                                                                                 \
    typedef struct                                                                                                     \
    {                                                                                                                  \
        int CTASTR(static_assertion_failed_, msg) : !!(cond);                                                          \
    } CTASTR(static_assertion_failed_, line)

#ifdef NO_ASSERT_SIZE // set in everything.h
#define STATIC_ASSERT_SIZE(struct, size) 
#else
#define STATIC_ASSERT_SIZE(struct, size) STATIC_ASSERT(sizeof(struct) == size, wrong_size, __LINE__)
#endif

#define REP0(X)
#define REP1(X) X
#define REP2(X) REP1(X) X
#define REP3(X) REP2(X) X
#define REP4(X) REP3(X) X
#define REP5(X) REP4(X) X
#define REP6(X) REP5(X) X
#define REP7(X) REP6(X) X
#define REP8(X) REP7(X) X
#define REP9(X) REP8(X) X
#define REP10(X) REP9(X) X

#define REP(THOUSANDS,HUNDREDS,TENS,ONES,X) \
  REP##THOUSANDS(REP10(REP10(REP10(X)))) \
  REP##HUNDREDS(REP10(REP10(X))) \
  REP##TENS(REP10(X)) \
  REP##ONES(X)

#define TEMPORARY_VR_MATCHING_PLACEHOLDER(THOUSANDS,HUNDREDS,TENS,ONES) REP(THOUSANDS,HUNDREDS,TENS,ONES, asm("nop");)

#endif // LINKER_H_
