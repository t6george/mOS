global set_data_segments
global set_code_segment
global set_gdt_loc

set_data_segments:
    mov dx, [esp + 4]

    mov ds, dx
    mov ss, dx
    mov es, dx

    ret

set_code_segment:
    mov dx, [esp + 4]
    jmp 0x8: flush_cs

    flush_cs:
        ret

set_gdt_loc:
    mov bx, [esp + 4]
    lgdt [bx]
    
    ret