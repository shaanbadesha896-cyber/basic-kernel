extern tss_handle

section .text
        global isr10
isr10:
        pusha ;push all the general purpose regs
        push ds
        push es
        push fs
        push gs

        push esp
        call tss_handle
        add esp, 4

        pop gs
        pop fs
        pop es
        pop ds
        popa

        iret
