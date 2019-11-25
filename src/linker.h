#ifndef LINKER_H_
#define LINKER_H_

#define SECTION(x) __attribute__((section(x)))

#define COUNTOF(x) sizeof(x) / sizeof(x[0])

#endif // LINKER_H_
