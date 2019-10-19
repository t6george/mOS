#ifndef IDT
#define IDT

#include <types.h>

#define IDT_SIZE 48

extern void isr_0();
extern void isr_1();
extern void isr_2();
extern void isr_3();
extern void isr_4();
extern void isr_5();
extern void isr_6();
extern void isr_7();

extern void isr_8();
extern void isr_9();
extern void isr_10();
extern void isr_11();
extern void isr_12();
extern void isr_13();
extern void isr_14();
extern void isr_15();

extern void isr_16();
extern void isr_17();
extern void isr_18();
extern void isr_19();
extern void isr_20();
extern void isr_21();
extern void isr_22();
extern void isr_23();

extern void isr_24();
extern void isr_25();
extern void isr_26();
extern void isr_27();
extern void isr_28();
extern void isr_29();
extern void isr_30();
extern void isr_31();

extern void isr_32();
extern void isr_33();
extern void isr_34();
extern void isr_35();
extern void isr_36();
extern void isr_37();
extern void isr_38();
extern void isr_39();

extern void isr_40();
extern void isr_41();
extern void isr_42();
extern void isr_43();
extern void isr_44();
extern void isr_45();
extern void isr_46();
extern void isr_47();

class InterruptDescriptorTable {
    private:

    struct IdtSpecifier {
        u16 limit;
        u32 base;
    } __attribute__((packed));

    typedef union idt_entry {
        u64 raw;
        struct {
            u16 offset_lo            : 16;
            u16 segment_sel          : 16;
            const u8 reserved              : 5;
            const u8 constant0x30    : 6;
            u8 gateSize              : 1;
            const u8 constant0x0     : 1;
            u8 dpl                   : 2;
            u8 present               : 1;
            u16 offset_hi            : 16;
        } __attribute__((packed));
        idt_entry(): constant0x30{0x30}, constant0x0 {0x0}, reserved{0x0} {  }
    } idt_entry_t;

    idt_entry_t entries[IDT_SIZE];
    IdtSpecifier spec;

    public:

    InterruptDescriptorTable();
    ~InterruptDescriptorTable() = default;
    
    void initIdtEntry(u16 isrNum, u32 isrAddr);
};

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
    entry.gateSize = 0x1;
    entry.offset_hi = 0xFFFF & (isrAddr >> 16);

    entries[isrNum] = entry;
}

typedef struct {
   u32 ds;
   u32 edi, esi, ebp, esp, ebx, edx, ecx, eax; // pusha
   u32 int_no, err_code;
   u32 eip, cs, eflags, useresp, ss; // Auto pushed by cpu
} interrupt_handler_info;

#endif