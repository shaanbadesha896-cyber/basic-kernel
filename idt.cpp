#include "idt.h"

extern "C" void loadIDT(uint32_t idt_ptr_address); 
extern "C" void isr0(); 
extern "C" void isr8(); 
extern "C" void isr10();
extern "C" void isr13();
extern "C" void isr32(); 
extern "C" void isr128(); 

IDT make_idt_entry(uint32_t offset, uint16_t Segment_Selector, uint8_t attributes){
    std::serial::write("If you see this, the function was called... \n");
    IDT entry;
    
    std::serial::write("Offset low value putting... \n");
    entry.offset_low = offset & 0xFFFF; 
    std::serial::write("Putting values in segment selector... \n");
    entry.selector = Segment_Selector;
    
    std::serial::write("Zeroing out reserved spaces... \n");
    entry.zero = 0; 
    entry.type_attr = attributes;

    entry.offset_hi = (offset >> 16) & 0xFFFF; 

    std::serial::write("Returning... \n");
    return entry; 
}

void init_idt(){
    static IDT idt[256]; 

    std::serial::write("Writing the divide by 0 exception... \n");
    idt[0] = make_idt_entry(reinterpret_cast<uint32_t>(isr0), 0x08, 0x8E); //0x8E maps to 1000 1110 
    idt[8] = make_idt_entry(reinterpret_cast<uint32_t>(isr8), 0x08, 0x8E); //Write double fault handler. 
    idt[10] = make_idt_entry(reinterpret_cast<uint32_t>(isr10), 0x08, 0x8E); //Write an invalid TSS handler.
    idt[13] = make_idt_entry(reinterpret_cast<uint32_t>(isr13), 0x08, 0x8E); //Write a GP handler
    idt[32] = make_idt_entry(reinterpret_cast<uint32_t>(isr32), 0x08, 0x8E); //Write an interrupt handler for QEMU's auto hardware interrupt fire
    idt[128] = make_idt_entry(reinterpret_cast<uint32_t>(isr128), 0x08, 0xEE); //Write syscall handler

    static IDTPointer idt_ptr;
    idt_ptr.limit = sizeof(idt) - 1;
    idt_ptr.base  = (uint32_t)&idt;
    std::serial::write("Calling ASM function... \n");
    loadIDT((uint32_t)&idt_ptr);
    std::serial::write("Returned from the ASM func... \n");
}
