#ifndef GDT
#define GDT

#include <types.h>

#define GDT_SIZE 3

class GlobalDescriptorTable {
    private:

    struct GdtSpecifier {
        u32 address;
        u16 size;
    } __attribute__((packed));

    typedef enum {
        SEG_DATA_RD,            // Read-Only 
        SEG_DATA_RDA,           // Read-Only, accessed
        SEG_DATA_RDWR,          // Read/Write
        SEG_DATA_RDWRA,         // Read/Write, accessed
        SEG_DATA_RDEXPD,        // Read-Only, expand-down
        SEG_DATA_RDEXPDA,       // Read-Only, expand-down, accessed
        SEG_DATA_RDWREXPD,      // Read/Write, expand-down
        SEG_DATA_RDWREXPDA,     // Read/Write, expand-down, accessed
        SEG_CODE_EX,            // Execute-Only
        SEG_CODE_EXA,           // Execute-Only, accessed
        SEG_CODE_EXRD,          // Execute/Read
        SEG_CODE_EXRDA,         // Execute/Read, accessed
        SEG_CODE_EXC,           // Execute-Only, conforming
        SEG_CODE_EXCA,          // Execute-Only, conforming, accessed
        SEG_CODE_EXRDC          // Execute/Read, conforming
    } MemSegmentType;

    typedef union gdt_entry {
        u64 raw;
        struct {
            u32 limit_low      : 16;
            u32 base_low       : 24;
            u8 type            : 4;
            u32 always_1       : 1;
            u32 dpl            : 2;
            u32 present        : 1;
            u32 limit_high     : 4;
            u32 avl            : 1;
            u32 long_mode      : 1;
            u32 big            : 1;
            u32 granularity    : 1;
            u32 base_high      : 8;
        } __attribute__((packed));

    } gdt_entry_t;

    gdt_entry_t segments[GDT_SIZE];
    u8 segI;
    GdtSpecifier spec;

    public:

    GlobalDescriptorTable();
    ~GlobalDescriptorTable() = default;
    
    void initNullDescriptor();
    void initCodeDescriptor();
    void initDataDescriptor();
    void writeGdt() const;
};

#endif