#ifndef CSR_H
#define CSR_H

#define CSRR(reg, res) __asm__ volatile("csrr %[out], "reg : [out] "=r" (res))
#define CSRW(reg, val) __asm__ volatile("csrw "reg", %[in]" : : [in] "r" (val))

#endif
