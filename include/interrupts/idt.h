#ifndef IDT
#define IDT

#include <types.h>

#define IDT_SIZE 48

extern "C" {
    void isr_0();
    void isr_1();
    void isr_2();
    void isr_3();
    void isr_4();
    void isr_5();
    void isr_6();
    void isr_7();

    void isr_8();
    void isr_9();
    void isr_10();
    void isr_11();
    void isr_12();
    void isr_13();
    void isr_14();
    void isr_15();

    void isr_16();
    void isr_17();
    void isr_18();
    void isr_19();
    void isr_20();
    void isr_21();
    void isr_22();
    void isr_23();

    void isr_24();
    void isr_25();
    void isr_26();
    void isr_27();
    void isr_28();
    void isr_29();
    void isr_30();
    void isr_31();

    void isr_32();
    void isr_33();
    void isr_34();
    void isr_22();
    void isr_22();
    void isr_35();
    void isr_36();
    void isr_37();
    void isr_38();
    void isr_39();

    void isr_40();
    void isr_41();
    void isr_42();
    void isr_43();
    void isr_44();
    void isr_45();
    void isr_46();
    void isr_47();
}

class InterruptDescriptorTable {
    private:

    struct IdtSpecifier {
        u16 limit;
        u32 base;
    } __attribute__((packed));

    typedef union idt_entry {
        u64 raw;
        struct {
            u16 offset_lo             : 16;
            u16 segment_sel           : 16;
            const u16 reserved        : 5;
            const u16 constant0x30    : 6;
            u16 gate_size             : 1;
            const u16 constant0x0     : 1;
            u16 dpl                   : 2;
            u16 present               : 1;
            u16 offset_hi             : 16;
        } __attribute__((packed));
        idt_entry();
        idt_entry& operator= (const idt_entry& other);
    } idt_entry_t;

    idt_entry_t entries[IDT_SIZE];
    IdtSpecifier spec;

    public:

    InterruptDescriptorTable();
    ~InterruptDescriptorTable() = default;
    
    void initIdtEntry(u16 isrNum, u32 isrAddr);
};

typedef struct {
   u32 ds;
   u32 edi, esi, ebp, esp, ebx, edx, ecx, eax; // pusha
   u32 int_no, err_code;
   u32 eip, cs, eflags, useresp, ss; // Auto pushed by cpu
} interrupt_handler_info;

#endif