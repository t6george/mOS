#include "gdt.h"

extern void set_data_segments(u8 table_offset)
extern void set_code_segment(u8 table_offset);
extern void set_gdt_loc(u32 specifier_addr);


GlobalDescriptorTable::GlobalDescriptorTable(): 
    segI{0}, spec{(u32)segments, sizeof(gdt_entry) * GDT_SIZE} {}

void GlobalDescriptorTable::initNullDescriptor () {
    // assert(segI == 0);
    gdt_entry_t descriptor;
    descriptor.raw = 0x0;

    segments[segI++] = descriptor;
}

void GlobalDescriptorTable::initCodeDescriptor () {
    // assert(segI > 0 && segI < GDT_SIZE);
    gdt_entry_t descriptor;
    descriptor.raw = 0x0;

    descriptor.type = MemSegmentType::SEG_CODE_EXRD;

    // descriptor.base_low = 0;
    // descriptor.base_high = 0;
    descriptor.limit_low = 0xFFFF;
    descriptor.limit_high = 0xF;
    descriptor.always_1 = 0x1;
    // descriptor.dpl = 0;
    descriptor.present = 0x1;
    // descriptor.avl = 0;
    descriptor.big = 0x1;
    // descriptor.long_mode = 0;
    descriptor.granularity = 0x1;

    segments[segI] = descriptor;

    set_code_segment(sizeof(gdt_entry) * (segI++));
}

void GlobalDescriptorTable::initDataDescriptor() {
    // assert(segI > 0 && segI < GDT_SIZE);
    gdt_entry_t descriptor;
    descriptor.raw = 0x0;

    descriptor.type = MemSegmentType::SEG_DATA_RDWR;

    // descriptor.base_low = 0;
    // descriptor.base_high = 0;
    descriptor.limit_low = 0xFFFF;
    descriptor.limit_high = 0xF;
    descriptor.always_1 = 0x1;
    // descriptor.dpl = 0;
    descriptor.present = 0x1;
    // descriptor.avl = 0;
    descriptor.big = 0x1;
    // descriptor.long_mode = 0;
    descriptor.granularity = 0x1;

    segments[segI] = descriptor;

    set_data_segments(sizeof(gdt_entry) * (segI++));
}

void GlobalDescriptorTable::writeGdt() const {
    set_gdt_loc((u32) &spec);
}