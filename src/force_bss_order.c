#define FORCE_BSS_ORDER(var) \
    extern int var; \
    static inline void *force##var() { return &var; }

FORCE_BSS_ORDER(GV_Clock_800AB920);
FORCE_BSS_ORDER(GV_PassageTime_800AB924);
