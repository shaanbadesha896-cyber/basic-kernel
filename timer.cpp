#include "timer.h"

uint32_t time; 

    extern "C" void timer(){
        ++time; 
    }

    bool hasSecondpassed(){
        return (time % 18 == 0) ? true : false; 
    }

    void pause(uint32_t seconds_to_wait){
    for (uint32_t i = 0; i < seconds_to_wait; i++) {
        // Calculate exactly what the timer value will be 1 second from now
        uint64_t target_tick = time + 18;
        
        // Wait aggressively until the PIT hardware interrupt increments 
        // the global timer past our target mark
        while (time < target_tick) {
            // Do nothing, just wait for the hardware heartbeat
            asm volatile("pause"); 
        }
    }
}