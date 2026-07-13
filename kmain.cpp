#include "pgtable.h"
#include "gdt.h"
#include "idt.h"
#include "usermodejmp.h"

extern "C" void kernel_main() {
    
    char array[] = {0x48, 0x0F, 0x65, 0x0F, 0x6C, 0x0F, 0x6C, 0x0F, 0x6F, 0x0F};
    for(int i = 0; i < 10; i += 2){

        volatile char* frame_buffer  = reinterpret_cast<volatile char*>(0x000B8000 + (0x01 * i)); //Adding hex 1 to the VGA buffer makes it write to the next corresponding cell, atleast it looks like it

        frame_buffer[i] = array[i]; //Write Hello written in their Hex values char by char
        frame_buffer[i+1] = array[i+1]; //0x0F is White on black

    }
    std::serial::write("Done writing Hello... \n"); 

    std::serial::write("Enabling Paging \n");
    enablePaging(); 
    std::serial::write("If you see this. Congrats... Paging has been enabled! \n");

    std::serial::write("Time for Booting up the GDT... \n");
    init_gdt(); 
    std::serial::write("If you see this. We have a GDT... \n");

    std::serial::write("Time for the big one... IDTs \n");
    init_idt();
    std::serial::write("We have INTERRUPTS BABY WOOOOHOOOOO... \n");

    std::serial::write("Cross those fingers and hold on tight. We are going places. \n");
    switch_to_user_mode();

    return; 
}