// Remapping guest physical GPU address (PRAMIN address) to host physical GPU address,
// and trapping GPU page table changes
//
// gphys -> hphys
//
// In NVC0 system, max GPU memory address is 40bits (12shift + 28bits)
//
// This table hierarchy is
//
//   DDDDDDDDDDDDD PPPPPPPPPPPPPPP OOOOOOOOOOOO
//   13 directory  15 page         12 offset
//
#ifndef HW_NVC0_NVC0_REMAPPING_H_
#define HW_NVC0_NVC0_REMAPPING_H_
#include <stdint.h>
#include <vector>
#include "nvc0.h"
#include "nvc0_static_assert.h"
#include "nvc0_array.h"
#include "nvc0_memory.h"
namespace nvc0 {
namespace remapping {

static const uint64_t kPAGE = 0x4000;
static const uint64_t kPAGE_BITS           = 12;
static const uint64_t kPAGE_ENTRY_BITS     = 15;
static const uint64_t kPAGE_DIRECTORY_BITS = 13;
static const uint64_t kADDRESS_BITS = kPAGE_BITS + kPAGE_ENTRY_BITS + kPAGE_DIRECTORY_BITS;  // 40bits

struct address_t {
    union {
        uint64_t raw;
        struct {
            uint64_t offset    : 12;
            uint64_t page      : 15;
            uint64_t directory : 13;
            uint64_t unused    : 24;
        };
    };
};

NVC0_STATIC_ASSERT(sizeof(address_t) == sizeof(uint64_t), address_t_size_should_be_uint64_t);

// address remapping structure 10bits
class page_entry {
 public:
  union {
    uint32_t raw;
    struct {
        unsigned present   : 1;
        unsigned read_only : 1;
        unsigned unused    : 2;
        unsigned target    : 28;  // 12 bit shifted
    };
  };
  uint32_t ref_count;
};

NVC0_STATIC_ASSERT(sizeof(page_entry) == sizeof(uint64_t), page_entry_size_should_be_uint64_t);

// point page entries 10bits
class page_directory {
 public:
    bool map(uint64_t page_start_address, uint64_t result_start_address, bool read_only);
    void unmap(uint64_t page_start_address);
    bool lookup(uint64_t address, page_entry* entry) const;

 private:
    std::array<page_entry, 0x1 << kPAGE_ENTRY_BITS> entries_;
};

class table {
 public:
    typedef std::shared_ptr<page_directory> directory;

    table(std::size_t memory_size);

    // returns previous definition exists
    bool map(uint64_t page_start_address, uint64_t result_start_address, bool read_only);
    void unmap(uint64_t page_start_address);

    bool lookup(uint64_t address, page_entry* entry) const;

 private:
    std::vector<directory> table_;
    uint64_t size_;
};

} }  // namespace remapping::nvc0
#endif  // HW_NVC0_NVC0_REMAPPING_H_
/* vim: set sw=4 ts=4 et tw=80 : */
