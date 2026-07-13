#include "ioserial.h"

extern "C" void tss_handle(){
    std::serial::write("Serial IO reporting. A TS has occured. Please Update your TS accordingly. Thank you. \n");
    while(1){}
    return; 
}