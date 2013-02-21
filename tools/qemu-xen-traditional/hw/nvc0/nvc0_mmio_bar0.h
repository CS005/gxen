#ifndef HW_NVC0_NVC0_MMIO_BAR0_H_
#define HW_NVC0_NVC0_MMIO_BAR0_H_
#include "nvc0.h"

#ifdef __cpp
extern "C" {
#endif

// init
void nvc0_init_bar0(nvc0_state_t* state);

// read functions
uint32_t nvc0_mmio_bar0_readb(void *opaque, target_phys_addr_t addr);
uint32_t nvc0_mmio_bar0_readw(void *opaque, target_phys_addr_t addr);
uint32_t nvc0_mmio_bar0_readd(void *opaque, target_phys_addr_t addr);

// write functions
void nvc0_mmio_bar0_writeb(void *opaque, target_phys_addr_t addr, uint32_t val);
void nvc0_mmio_bar0_writew(void *opaque, target_phys_addr_t addr, uint32_t val);
void nvc0_mmio_bar0_writed(void *opaque, target_phys_addr_t addr, uint32_t val);


#ifdef __cpp
}
#endif

#endif  // HW_NVC0_NVC0_MMIO_BAR0_H_
/* vim: set sw=4 ts=4 et tw=80 : */
