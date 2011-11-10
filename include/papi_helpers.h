int detect_processor(void);
int copy_events(char *eventset);
int detect_nmi_watchdog(void);

#define PROCESSOR_UNKNOWN     -1
#define PROCESSOR_PENTIUM_PRO  1
#define PROCESSOR_PENTIUM_II   2
#define PROCESSOR_PENTIUM_III  3
#define PROCESSOR_PENTIUM_4    4
#define PROCESSOR_PENTIUM_M    5
#define PROCESSOR_COREDUO      6
#define PROCESSOR_CORE2        7
#define PROCESSOR_NEHALEM      8
#define PROCESSOR_NEHALEM_EX   9
#define PROCESSOR_WESTMERE    10
#define PROCESSOR_WESTMERE_EX 11
#define PROCESSOR_SANDYBRIDGE 12
#define PROCESSOR_ATOM        13
#define PROCESSOR_K7          14
#define PROCESSOR_K8          15
#define PROCESSOR_AMD_FAM10H  16
#define PROCESSOR_AMD_FAM11H  17
#define PROCESSOR_AMD_FAM14H  18
#define PROCESSOR_AMD_FAM15H  19

#define PROCESSOR_POWER3      103
#define PROCESSOR_POWER4      104
#define PROCESSOR_POWER5      105
#define PROCESSOR_POWER6      106
#define PROCESSOR_POWER7      107

#define PROCESSOR_CORTEX_A8   200
#define PROCESSOR_CORTEX_A9   201

#define TEST_MAX_EVENTS 16
#define TEST_MAX_STRLEN 80
