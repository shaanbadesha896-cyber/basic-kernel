extern timer

section .text
        global isr32
isr32:
        pusha ;push all the general purpose regs
        push ds
        push es
        push fs
        push gs

        push esp
        call timer
        add esp, 4

        pop gs
        pop fs
        pop es
        pop ds
        popa

        iret
