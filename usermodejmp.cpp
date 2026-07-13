#include "usermodejmp.h"

uint64_t user_stack[4096];

void switch_to_user_mode() {
    // 1. Calculate Selectors
    uint16_t user_cs = 0x18 | 0x03; // Index 3 * 8 (User Code)
    uint16_t user_ds = 0x20 | 0x03; // Index 4 * 8 (User Data)
    uint32_t user_ss = 0x20 |0x03;
    uint32_t user_esp = 0x80000000 + 4096; 
    
    // 2. Set EFLAGS (Enable Interrupts!)
    uint32_t eflags = 0x202; 
    uint32_t user_eip = 0x40000000;

    // 3. Switch Data Segments (Prepare for Ring 3)
    std::serial::write("Executing the first block of assembly \n");
    asm volatile(
        "mov %0, %%ax\n"
        "mov %%ax, %%ds\n"
        "mov %%ax, %%es\n"
        "mov %%ax, %%fs\n"
        "mov %%ax, %%gs\n"
        : : "r"(user_ds)
    );

    // 4. Push IRET frame and JUMP
    // Order: SS, ESP, EFLAGS, CS, EIP
    std::serial::write("Executing the second block of assembly \n");
    asm volatile(
        "push %0\n"     // Stack Segment
        "push %1\n"     // Stack Pointer
        "push %2\n"     // EFLAGS
        "push %3\n"     // Code Segment
        "push %4\n"     // Instruction Pointer (Entry Point)
        "iret\n"
        :
        : "r"(user_ss), "r"(user_esp), "r"(eflags), "r"(user_cs), "r"(user_eip)
    );
    std::serial::write("Executed the second block of assembly \n");
}