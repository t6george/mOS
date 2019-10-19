;extern isr_handler

%macro no_error_isr 1 
global isr_%1
isr_%1:
    cli
    push dword %1       ; remove this??
    push dword %1
    jmp isr_handler_setup
%endmacro

%macro error_isr 1 
global isr_%1
isr_%1:
    cli
    push dword %1       ; remove this??
    push dword %1
    jmp isr_handler_setup
%endmacro

isr_handler_setup:
    pusha
    mov ax, ds
    push eax
    mov ax, 0x10
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax

    ;call isr_handler

    pop eax
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax

    popa
    add esp, 0x8
    sti
    iret

no_error_isr 0
no_error_isr 1
no_error_isr 2
no_error_isr 3
no_error_isr 4
no_error_isr 5
no_error_isr 6
no_error_isr 7

no_error_isr 8
no_error_isr 9
no_error_isr 10
no_error_isr 11
no_error_isr 12
no_error_isr 13
no_error_isr 14
no_error_isr 15

no_error_isr 16
no_error_isr 17
no_error_isr 18
no_error_isr 19
no_error_isr 20
no_error_isr 21
no_error_isr 22
no_error_isr 23

no_error_isr 24
no_error_isr 25
no_error_isr 26
no_error_isr 27
no_error_isr 28
no_error_isr 29
no_error_isr 30
no_error_isr 31

no_error_isr 32
no_error_isr 33
no_error_isr 34
no_error_isr 35
no_error_isr 36
no_error_isr 37
no_error_isr 38
no_error_isr 39

no_error_isr 40
no_error_isr 41
no_error_isr 42
no_error_isr 43
no_error_isr 44
no_error_isr 45
no_error_isr 46
no_error_isr 47