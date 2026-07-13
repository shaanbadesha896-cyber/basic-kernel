#include "gdt.h"

TSS tss; 

extern "C" uint32_t kernel_stack_top;

// Helper to create an entry
GDT make_gdt_entry(uint32_t base, uint32_t limit, uint8_t access) {
    GDT entry;
    
    entry.Limitlow   = limit & 0xFFFF;
    entry.Baselow    = (base >> 0)  & 0xFFFF;
    entry.Basemid    = (base >> 16) & 0xFF;
    
    entry.a          = (access >> 0) & 0x1;
    entry.rw         = (access >> 1) & 0x1;
    entry.dc         = (access >> 2) & 0x1;
    entry.e          = (access >> 3) & 0x1;
    entry.s          = (access >> 4) & 0x1;
    entry.dpl        = (access >> 5) & 0x3;
    entry.p          = (access >> 7) & 0x1;
    
    entry.Limithigh  = (limit >> 16) & 0x0F;
    
    entry.resrvd     = 0;
    entry.l          = 0;      // 0 = 32-bit, 1 = 64-bit
    entry.db         = 1;      // 1 = 32-bit protected mode
    entry.g          = 1;      // 1 = 4KB granularity
    
    entry.Basehigh   = (base >> 24) & 0xFF;
    
    return entry;
}

void init_gdt() {
    static GDT gdt[7];
    
    tss.ss0 = 0x10;           // Kernel Stack Segment
    tss.esp0 = kernel_stack_top; // kernel stack pointer
    tss.IOPB = sizeof(tss);   // No IOP bitmap

    // 2. Create the GDT Entry that points to the TSS
    // Base = Address of 'tss', Limit = Size of 'tss'
    uint32_t tss_base = (uint32_t)&tss;
    uint32_t tss_limit = sizeof(tss) - 1;

    // 1. Null Descriptor (Required by CPU)
    std::serial::write("Writing the null descriptor... \n");
    gdt[0] = make_gdt_entry(0, 0, 0);

    // 2. Kernel Code Segment
    // Base=0, Limit=0xFFFFF, Access=0x9A (Present, Ring0, Code, Readable), Flags=0xC (32-bit, 4KB)
    std::serial::write("Writing the first entry... \n");
    gdt[1] = make_gdt_entry(0, 0xFFFFF, 0x9A);

    // 3. Kernel Data Segment
    // Access=0x92 (Present, Ring0, Data, Writable)
    gdt[2] = make_gdt_entry(0, 0xFFFFF, 0x92);

    // 4. User Code Segment
    // Access=0xFA -> 1111 1010
    gdt[3] = make_gdt_entry(0, 0xFFFFF, 0xFA);
    
    // 5. User Data Segment 
    // Access=0xF2 -> 1111 0010
    gdt[4] = make_gdt_entry(0, 0xFFFFF, 0xF2);
    
    // 6. Load TSS
    // Access byte 0xE9 means: Present (0x80) + Ring 3 executable space access (0x60) + Executable/TSS Type (0x09) = 0xE9
    gdt[5] = make_gdt_entry(tss_base, tss_limit, 0xE9);
    
    static GDTPointer gdt_ptr;
    gdt_ptr.limit = sizeof(gdt) - 1;
    gdt_ptr.base  = (uint32_t)&gdt;

    // Pass the address of struct
    std::serial::write("Loading the GDT... \n");
    loadGDT(reinterpret_cast<uint32_t>(&gdt_ptr));
    std::serial::write("GDT Done \n");

    // Selector is Index 5 (0x28) + TI(0) + RPL(0) = 0x28
    uint16_t tss_selector = 0x28; 
    asm volatile("ltr %0" : : "r"(tss_selector));
}