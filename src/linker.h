#ifndef LINKER_H_
#define LINKER_H_

#define SECTION(x) __attribute__((section(x)))

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

#endif // LINKER_H_
