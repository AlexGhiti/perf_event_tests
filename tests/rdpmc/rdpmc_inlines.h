#if defined(__i386__) || defined (__x86_64__)

#define barrier() __asm__ volatile("" ::: "memory")

#elif defined(__aarch64__)

#define barrier()	asm volatile("dmb ish" : : : "memory")
#define isb()		asm volatile("isb" : : : "memory")

#else

#define barrier()

#endif


#if defined(__i386__) || defined (__x86_64__)

inline unsigned long long rdtsc(void) {

	unsigned a,d;

	__asm__ volatile("rdtsc" : "=a" (a), "=d" (d));

	return ((unsigned long long)a) | (((unsigned long long)d) << 32);
}

inline unsigned long long rdpmc(unsigned int counter) {

	unsigned int low, high;

	__asm__ volatile("rdpmc" : "=a" (low), "=d" (high) : "c" (counter));

	return (unsigned long long)low | ((unsigned long long)high) <<32;
}

#elif defined(__aarch64__)


inline unsigned long long rdtsc(void) {
	unsigned long long __val;
	__asm__ volatile("mrs %0, cntvct_el0" : "=r" (__val));
	return __val;
}

inline unsigned long long rdpmc(unsigned int counter) {

	unsigned long long ret=0;

	if (counter == 31) {
		asm volatile("mrs %0, pmccntr_el0" : "=r" (ret));
	}
	else {
		asm volatile("msr pmselr_el0, %0" : : "r" (counter));
		asm volatile("mrs %0, pmxevcntr_el0" : "=r" (ret));
	}

	isb();


	return ret;
}

#elif defined(__riscv) && __riscv_xlen == 64

#define CSR_CYCLE      0xc00
#define CSR_TIME       0xc01
#define CSR_CYCLEH     0xc80

#define csr_read(csr)                                          \
({                                                             \
       register unsigned long __v;                             \
       __asm__ __volatile__ ("csrr %0, " #csr                  \
                             : "=r" (__v) :                    \
                             : "memory");                      \
       __v;                                                    \
})

static unsigned long csr_read_num(int csr_num)
{
#define switchcase_csr_read(__csr_num, __val)           {\
        case __csr_num:                                 \
                __val = csr_read(__csr_num);            \
                break; }
#define switchcase_csr_read_2(__csr_num, __val)         {\
        switchcase_csr_read(__csr_num + 0, __val)        \
        switchcase_csr_read(__csr_num + 1, __val)}
#define switchcase_csr_read_4(__csr_num, __val)         {\
        switchcase_csr_read_2(__csr_num + 0, __val)      \
        switchcase_csr_read_2(__csr_num + 2, __val)}
#define switchcase_csr_read_8(__csr_num, __val)         {\
        switchcase_csr_read_4(__csr_num + 0, __val)      \
        switchcase_csr_read_4(__csr_num + 4, __val)}
#define switchcase_csr_read_16(__csr_num, __val)        {\
        switchcase_csr_read_8(__csr_num + 0, __val)      \
        switchcase_csr_read_8(__csr_num + 8, __val)}
#define switchcase_csr_read_32(__csr_num, __val)        {\
        switchcase_csr_read_16(__csr_num + 0, __val)     \
        switchcase_csr_read_16(__csr_num + 16, __val)}

        unsigned long ret = 0;

        switch (csr_num) {
        switchcase_csr_read_32(CSR_CYCLE, ret)
        switchcase_csr_read_32(CSR_CYCLEH, ret)
        default :
                break;
        }

        return ret;
#undef switchcase_csr_read_32
#undef switchcase_csr_read_16
#undef switchcase_csr_read_8
#undef switchcase_csr_read_4
#undef switchcase_csr_read_2
#undef switchcase_csr_read
}

inline unsigned long long rdpmc(unsigned int counter) {
	return csr_read_num(CSR_CYCLE + counter);
}

inline unsigned long long rdtsc(void) {
	return csr_read_num(CSR_TIME);
}
#else


inline unsigned long long rdtsc(void) {

	return 0;

}

inline unsigned long long rdpmc(unsigned int counter) {

	return 0;
}

#endif
