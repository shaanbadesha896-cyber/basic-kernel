extern gp_handle

section .text
        global isr13
isr13:
        pusha ;push all the general purpose regs
        push ds
        push es
        push fs
        push gs

        push esp
        call gp_handle
        add esp, 4

        pop gs
        pop fs
        pop es
        pop ds
        popa

        iret
