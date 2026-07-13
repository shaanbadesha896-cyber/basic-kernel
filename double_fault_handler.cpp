#include "ioserial.h"

extern "C" void double_fault_handler(){
    std::serial::write("Good morning here. Serial IO reporting \n");
    std::serial::write("A double fault just happened. All work while be halted and interrupts will be disabled. It is advised to restart your PC. Thank you \n");

    while(1){
        asm volatile(
            "cli\n" 
            "hlt\n"
        );
    }
}