#pragma once 
#include "ioserial.h"
#include "cstdint.h" 

struct PDTFLAGS{
    uint32_t present    : 1;  // Bit 0. Asks- Is it present in the current memory. If yes- Bit is one else it is 0.
    uint32_t rw         : 1;  // Bit 1. Read and Write permissions(r/w). If set to 1, then both and Read and Write, else Read Only.  
    uint32_t user       : 1;  // Bit 2. If user or Kernel (Supervisor) can access. 1 meaning both can while 0 means only the supervisor can 
    uint32_t pwt        : 1;  // Bit 3. Controls Write-Through' abilities of the page. If the bit is set, write-through caching is enabled. If not, then write-back is enabled instead.
    uint32_t pcd        : 1;  // Bit 4. Is the 'Cache Disable' bit. If the bit is set, the page will not be cached. Otherwise, it will be.
    uint32_t accessed   : 1;  // Bit 5. Did the CPU access this bit? 1 is yes but 0 is no
    uint32_t dirty      : 1;  // Bit 6. Did the CPU write over it?
    uint32_t ps         : 1;  // Bit 7. 'Page Size' stores the page size for that specific entry. If the bit is set, then the PDE maps to a page that is 4 MiB in size. Otherwise, it maps to a 4 KiB page table.
    uint32_t global     : 1;  // Bit 8. 'Global' tells the processor not to invalidate the TLB entry corresponding to the page upon a MOV to CR3 instruction. Bit 7 (PGE) in CR4 must be set to enable global pages.
    
   
    uint32_t available  : 3;  //These bits are unused by the processor and free for the OS to use.

    // Bits 12-31: The Address of Page Table
    uint32_t address    : 20; 
}__attribute__((packed)); //this prevents the compiler for entering padding b/w the bytes and maps it all byte for byte exact


extern uint32_t page_directory[1024]; //Create an array of 1024 entries. Aligns by 4KBs. 
extern uint32_t page_tables[1024][1024]; //Create a 2d array of 1024 arrays where each array is a page table

void SetPDTflags(); 
void Set_and_map_pgtables();
void enablePaging();

extern "C" void loadpdt(uint32_t pdt_address); //ASM func
extern "C" void loadpgtable(); //ASM func