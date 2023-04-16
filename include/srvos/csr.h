#ifndef CSR_H
#define CSR_H

#define CSRR(reg, res) asm volatile("csrr %[out], "reg : [out] "=r" (res))
#define CSRW(reg, val) asm volatile("csrw "reg", %[in]" : : [in] "r" (val))

#endif
