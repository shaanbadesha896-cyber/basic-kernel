#pragma once
#include "cstdint.h"
#include "ioserial.h"

struct GDT{
    uint32_t Limitlow   : 16; // A 20-bit value, tells the maximum addressable unit, either in 1 byte units, or in 4KiB pages. Hence, if you choose page granularity and set the Limit value to 0xFFFFF the segment will span the full 4 GiB address space in 32-bit mode.
    uint32_t Baselow    : 16; // Base: A 32-bit value containing the linear address where the segment begins.
    
    uint32_t Basemid    : 8;
    
    //Note- The following are all Access byte flags
    
    uint32_t a          : 1; //accessed?
    uint32_t rw         : 1; //Readable or Writable?
    uint32_t dc         : 1; //Very complex stuff I don't understand 
    uint32_t e          : 1; //Executable?
    uint32_t s          : 1; //More stuff I don't know
    uint32_t dpl        : 2; //Ring 0 or Ring 3
    uint32_t p          : 1; //Present?
    
    uint32_t Limithigh  : 4; 

    //Note- The following are flag values 
    
    uint32_t resrvd     : 1; //Reserved byte 
    uint32_t l          : 1; //Long mode flag 
    uint32_t db         : 1; //Size flag. If it is 0, 16 bit segments are made else it is 32 bit are made 
    uint32_t g          : 1; //Granularity

    uint32_t Basehigh   : 8;
}__attribute__((packed));

struct GDTPointer{
    uint16_t limit;  // Size of GDT - 1
    uint32_t base;   // Address of the GDT
}__attribute__((packed));

struct TSS{
    uint32_t link   : 16; //LINK: Previous Task Link Field. Contains the Segment Selector for the TSS of the previous task.
    uint32_t zero1  : 16; 
    uint32_t esp0   : 32; //ESP0, ESP1, ESP2 are Stack Pointers used to load the stack when a privilege level change occurs from a lower privilege to higher.
    uint32_t ss0    : 16; //SS0, SS1, SS2 are Segment Selectors used to load the stack when a privilege level change occurs from a lower privilege to higher.
    uint32_t zero2  : 16; 
    uint32_t esp1   : 32; 
    uint32_t ss1    : 16;
    uint32_t zero3  : 16;
    uint32_t esp2   : 32;
    uint32_t ss2    : 16;
    uint32_t zero4  : 16;
    
    uint32_t cr3    : 32;
    uint32_t eip    : 32; 
    uint32_t eflags : 32;
    uint32_t eax    : 32;
    uint32_t ecx    : 32;
    uint32_t edx    : 32;
    uint32_t ebx    : 32;
    uint32_t esp    : 32;
    uint32_t ebp    : 32;
    uint32_t esi    : 32;
    uint32_t edi    : 32;

    uint32_t es     : 16;
    uint32_t zero5  : 16; 
    uint32_t cs     : 16;
    uint32_t zero6  : 16; 
    uint32_t ss     : 16;
    uint32_t zero7  : 16; 
    uint32_t ds     : 16;
    uint32_t zero8  : 16; 
    uint32_t fs     : 16;
    uint32_t zero9  : 16; 
    uint32_t gs     : 16;
    uint32_t zeroA  : 16; //Using the hex convention to keep everything clean
    uint32_t LDTR   : 16; 
    uint32_t T      : 16; //Bit 0 is the bit for trap
    uint32_t zeroB  : 16; 
    
    uint32_t zeroC  : 16;
    uint32_t IOPB   : 16; //IOPB: I/O Map Base Address Field. Contains a 16-bit offset from the base of the TSS to the I/O Permission Bit Map.
    
    uint32_t SSP    : 16; //Shadow Stack pointer

}__attribute__((packed));  

struct TSS_Descriptor{
    uint32_t lim_low    : 16; 
    uint32_t base_low   : 16; 
    
    uint32_t base_mid   : 8;

    uint32_t type       : 4; //One of these bits is a flag for busy. Precisely, The second bit. 
    uint32_t resv1      : 1; 

    uint32_t dpl        : 2; 
    uint32_t p          : 1; 

    uint32_t lim_hi     : 4; 
    uint32_t avl        : 1; 
    uint32_t resv2      : 2; 

    uint32_t g          : 1; 
    uint32_t base_hi    : 8; 
}__attribute__((packed));


GDT make_gdt_entry(uint32_t base, uint32_t limit, uint8_t access);
void init_gdt();
extern GDT gdt[3];

extern "C" void loadGDT(uint32_t gdt_ptr_address);