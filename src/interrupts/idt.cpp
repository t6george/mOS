#include <idt.h>

InterruptDescriptorTable::idt_entry::idt_entry(): 
    reserved{0x0}, constant0x30{0x30}, constant0x0 {0x0} {}

InterruptDescriptorTable::idt_entry& InterruptDescriptorTable::idt_entry::operator= (const idt_entry_t& other) {
    offset_lo = other.offset_lo;
    segment_sel = other.segment_sel;
    gate_size = other.gate_size;
    dpl = other.dpl;
    present = other.present;
    offset_hi = other.offset_hi;
    return *this;
}

InterruptDescriptorTable::InterruptDescriptorTable()  {
    initIdtEntry(0, (u32)isr_0); initIdtEntry(1, (u32)isr_1);
    initIdtEntry(2, (u32)isr_2); initIdtEntry(3, (u32)isr_3);
    initIdtEntry(4, (u32)isr_4); initIdtEntry(5, (u32)isr_5);
    initIdtEntry(6, (u32)isr_6); initIdtEntry(7, (u32)isr_7);

    initIdtEntry(8, (u32)isr_8); initIdtEntry(9, (u32)isr_9);
    initIdtEntry(10, (u32)isr_10); initIdtEntry(11, (u32)isr_11);
    initIdtEntry(12, (u32)isr_12); initIdtEntry(13, (u32)isr_13);
    initIdtEntry(14, (u32)isr_14); initIdtEntry(15, (u32)isr_15);

    initIdtEntry(16, (u32)isr_16); initIdtEntry(17, (u32)isr_17);
    initIdtEntry(18, (u32)isr_18); initIdtEntry(19, (u32)isr_19);
    initIdtEntry(20, (u32)isr_20); initIdtEntry(21, (u32)isr_21);
    initIdtEntry(22, (u32)isr_22); initIdtEntry(23, (u32)isr_23);

    initIdtEntry(24, (u32)isr_24); initIdtEntry(25, (u32)isr_25);
    initIdtEntry(26, (u32)isr_26); initIdtEntry(27, (u32)isr_27);
    initIdtEntry(28, (u32)isr_28); initIdtEntry(29, (u32)isr_29);
    initIdtEntry(30, (u32)isr_30); initIdtEntry(31, (u32)isr_31);

    initIdtEntry(32, (u32)isr_32); initIdtEntry(33, (u32)isr_33);
    initIdtEntry(34, (u32)isr_34); initIdtEntry(35, (u32)isr_35);
    initIdtEntry(36, (u32)isr_36); initIdtEntry(37, (u32)isr_37);
    initIdtEntry(38, (u32)isr_38); initIdtEntry(39, (u32)isr_39);

    initIdtEntry(40, (u32)isr_40); initIdtEntry(41, (u32)isr_41);
    initIdtEntry(42, (u32)isr_42); initIdtEntry(43, (u32)isr_43);
    initIdtEntry(44, (u32)isr_44); initIdtEntry(45, (u32)isr_45);
    initIdtEntry(46, (u32)isr_46); initIdtEntry(47, (u32)isr_47);
}

void InterruptDescriptorTable::initIdtEntry(u16 isrNum, u32 isrAddr) {
    idt_entry_t entry;

    entry.offset_lo = 0xFFFF & isrAddr;
    entry.segment_sel = 0x8;
    entry.dpl = 0x0;
    entry.present = 0x1;
    entry.gate_size = 0x1;
    entry.offset_hi = 0xFFFF & (isrAddr >> 16);

    entries[isrNum] = entry;
}