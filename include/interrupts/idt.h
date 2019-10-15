#ifndef IDT
#define IDT

#include <types.h>

#define GDT_SIZE 256

extern void isr0();
extern void isr1();
extern void isr2();
extern void isr3();
extern void isr4();
extern void isr5();
extern void isr6();
extern void isr7();
extern void isr8();
extern void isr9();
extern void isr10();
extern void isr11();
extern void isr12();
extern void isr13();
extern void isr14();
extern void isr15();
extern void isr16();
extern void isr17();
extern void isr18();
extern void isr19();
extern void isr20();
extern void isr21();
extern void isr22();
extern void isr23();
extern void isr24();
extern void isr25();
extern void isr26();
extern void isr27();
extern void isr28();
extern void isr29();
extern void isr30();
extern void isr31();

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