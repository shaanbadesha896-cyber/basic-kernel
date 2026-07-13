extern double_fault_handler

section .text
        global isr8
isr8:
        pusha ;push all the general purpose regs
        push ds
        push es
        push fs
        push gs

        push esp
        call double_fault_handler
        add esp, 4

        pop gs
        pop fs
        pop es
        pop ds
        popa

        iret
