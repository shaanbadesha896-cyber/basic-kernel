#include "pgtable.h"

extern "C" uint64_t user_stack;


uint32_t page_directory[1024] __attribute__((aligned(4096)));
uint32_t page_tables[1024][1024] __attribute__((aligned(4096)));


void SetPDTflags(){
    for(uint32_t i = 0; i < 256; ++i){
        page_directory[i] = 0x00000002;
        //The above hex maps to the binary 00000000000000000000000000000010. the 1 sets the flags of Write Enabled: It can be both read from and written to. 
    }

    for(uint32_t i = 400; i >= 256 && i < 1024; ++i){
        page_directory[i] = 0x00000007; 
    }
    return;
}

void Set_and_map_pgtables() {
    for (uint32_t dir_index = 0; dir_index < 256; dir_index++) {
        for (uint32_t table_index = 0; table_index < 1024; table_index++) {

            // Calculate the Physical Address we want to map to.
            // Logic: (4MB chunk * index) + (4KB page * index)
            // Shifting is faster than multiplication:
            // dir_index << 22  = Multiply by 4MB
            // table_index << 12 = Multiply by 4KB
            uint32_t phys_addr = (dir_index << 22) | (table_index << 12);

            // Set the entry: Address + Flags (Present + Writable = 0x3)
            page_tables[dir_index][table_index] = phys_addr | 0x3;
        }

        // --- Step 2: Link the Directory to this Table ---
        
        // Get the physical address of this specific table
        // We cast the pointer to int
        uint32_t table_address = (uint32_t)&page_tables[dir_index];

        // Write it to the directory
        // Flags: Present (1) + Writable (1) = 0x3
        page_directory[dir_index] = table_address | 0x3;

    }

    for (uint32_t dir_index = 0; dir_index >= 256 && dir_index < 1024; dir_index++) {
        for (uint32_t table_index = 0; table_index < 1024; table_index++) {
            uint32_t phys_addr = (dir_index << 22) | (table_index << 12);

            // Set the entry: Address + Flags (Present + Writable + User = 0x7)
            page_tables[dir_index][table_index] = phys_addr | 0x07;
        }

        uint32_t table_address = (uint32_t)&page_tables[dir_index];

        // Write it to the directory
        // Flags: Present (1) + Writable (1) + User (1) = 0x7
        page_directory[dir_index] = table_address | 0x07;

    }
}

void map_user_stack() {
    // Address for the stack
    uint32_t user_virtual_esp = 0x80000000; 

    // User_stack location
    uint32_t user_stack_phys = (uint32_t)&user_stack;

    // 3. Calculate Page Table Indices for the Virtual Address
    uint32_t dir_index = user_virtual_esp >> 22;
    uint32_t table_index = (user_virtual_esp >> 12) & 0x3FF;

    // Map Virtual -> Physical
    // Flags: 0x07 (Present + Writable + User)
    page_tables[dir_index][table_index] = user_stack_phys | 0x07;

    // 5. Ensure the Directory points to the table (User Writable)
    page_directory[dir_index] = ((uint32_t)&page_tables[dir_index]) | 0x07;
}

void enablePaging(){
    std::serial::write("Setting flags\n"); 
    SetPDTflags(); 
    std::serial::write("Moving on to memory mapping and page table setting \n"); 
    Set_and_map_pgtables(); 
    std::serial::write("Loading Page Descriptor Table. Hold on... \n");
    uint32_t pdt_addr = reinterpret_cast<uint32_t>(page_directory);
    loadpdt(pdt_addr);
    std::serial::write("Loading the tables... \n"); 
    loadpgtable();
    std::serial::write("User stack being set up"); 
    map_user_stack(); 
}