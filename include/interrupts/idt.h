#ifndef IDT
#define IDT

#include <types.h>

#define GDT_SIZE 256

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
            u16 offset_lo      : 16;
            u16 segment_sel    : 16;
            u8 reserved        : 5;
            u8 present         : 1;
            u8 constant0x30    : 6;
            u8 gateSize        : 1;
            u8 constant0x0     : 1;
            u8 dpl             : 2;
            u8 present         : 1;
            u16 offset_hi      : 16;
        } __attribute__((packed));

    } idt_entry_t;

    idt_entry_t segments[IDT_SIZE];
    IdtSpecifier spec;

    public:

    InterruptDescriptorTable();
    ~InterruptDescriptorTable() = default;
    
    void initNullDescriptor();
    void initCodeDescriptor();
    void initDataDescriptor();
    void writeGdt() const;
};

InterruptDescriptorTable::InterruptDescriptorTable():  {}

#endif