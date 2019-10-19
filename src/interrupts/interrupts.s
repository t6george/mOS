%macro no_error_int_handler %1
int_handler_%1:
    cli
    push dword 0
    push dword %1
    jmp isr_handler_main
%endmacro

%macro error_int_handler %1
int_handler_%1:
    cli
    push dword %1       ; remove this??
    push dword %1
    jmp isr_handler_main
%endmacro

isr_handler_main:
    