#include "ioserial.h"
#include "cstdint.h"

struct GPF_Frame {
    // Registers pushed by your assembly stub (e.g., push gs, fs, es, ds, pusha)
    uint32_t gs, fs, es, ds;
    uint32_t edi, esi, ebp, esp_dummy, ebx, edx, ecx, eax;

    // Pushed automatically by the CPU for Exception 13
    uint32_t error_code; 
    
    // Pushed automatically by the CPU for any interrupt/fault
    uint32_t eip;
    uint32_t cs;
    uint32_t eflags;
};

extern "C" void gp_handle(){
    std::serial::write("Serial IO reporting. A General Protection fault has occured. Thank you. \n");

    GPF_Frame frame;

    uint32_t err = frame.error_code;

    // Step 1: Check Bit 0 (External Event)
    bool ext = (err & 0x1);

    // Step 2: Check Bit 1 (IDT Indicator)
    bool idt = (err & 0x2);

    // Step 3: Check Bit 2 (TI - Table Indicator)
    bool gdt_table = !(err & 0x4); // 0 = GDT, 1 = LDT

    // Step 4: Extract Bits 3-15 (The actual Index)
    uint32_t index = (err >> 3) & 0x1FFF;

    // --- Diagnostic Printouts ---
    if (err == 0) {
        std::serial::write("Error Code is 0: Likely a privileged instruction execution attempt in Ring 3.\n");
    } else {
        if (idt) {
            std::serial::write("Fault happened while referencing the IDT.\n");
        } else if (gdt_table) {
            std::serial::write("Fault happened while referencing the GDT.\n");
        } else {
            std::serial::write("Fault happened while referencing the LDT.\n");
        }

        // Print out the exact selector index number
        // (Assuming you have a helper to print numbers or hex values)
        std::serial::write("Faulty Table Index Selector: ");
        // print_hex(index); 
    }

    // Print the instruction pointer that caused the crash
    std::serial::write("\nCrash occurred at Instruction Pointer (EIP): ");

    while(1){}
    return; 
}