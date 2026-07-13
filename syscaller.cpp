#include "ioserial.h"
#include "cstdint.h" 
#include "timer.h"

extern "C" void syscaller(uint32_t* registers){
    uint32_t passed_esp = registers[0];  // The copy of ESP pushed last
    uint32_t ebx        = registers[1];
    uint32_t ecx        = registers[2];
    uint32_t edx        = registers[3];
    uint32_t esi        = registers[4];
    uint32_t edi        = registers[5];
    uint32_t ebp        = registers[6];
    
    uint32_t enosys     = registers[7];  // Your placeholder error code
    uint32_t ds         = registers[8];
    uint32_t es         = registers[9];
    uint32_t fs         = registers[10];
    uint32_t gs         = registers[11];
    
    uint32_t eax        = registers[12]; // FIRST PUSHED! Your Syscall Number!

    if(eax == 1){
        int exit_code = static_cast<int>(edi);
        char* user_buffer = reinterpret_cast<char*>(esi);
        int cursor_size   = static_cast<int>(edx);
    
        pause(3); 
        std::serial::write(user_buffer);
        
        if(exit_code == 1){
            pause(5); 
            std::serial::write("Hey! It's Serial IO reporting here. If you made it here... CONGRATS! It's over. You are done. This kernel is done. Go take a break. Until next time, Serial IO- Out. \n");
            return; 
        }

        else{
            std::serial::write(" SIGSEGV \n");
            return;
        }
    }

    else{
        return; 
    }
}