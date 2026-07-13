#pragma once
#include "cstdint.h"
#include "ioserial.h"

struct IDT{
    uint16_t offset_low     : 16; // Bits 0-15
    uint16_t selector       : 16; // Bits 16-31
    uint8_t zero            : 8; // Bits 32-39 (Must be 0)
    
    // Bits 40-47: The Type Attribute Byte
    // P (7) | DPL (6-5) | S (4) | Type (3-0)
    uint8_t type_attr       : 8;       

    uint16_t offset_hi      : 16;     // Bits 48-63
} __attribute__((packed));

struct IDTPointer {
    uint16_t limit;  
    uint32_t base;  
} __attribute__((packed));

IDT make_idt_entry(uint32_t offset, uint16_t Segment_Selector, uint8_t attributes);
void init_idt(); 