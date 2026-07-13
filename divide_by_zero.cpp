#include "ioserial.h"

extern "C" void div_by_zero(){
    std::serial::write("Good moring, Serial IO reporting here! According to our friends in the IDT, There has been a divide by 0. Despite the wide panic, we expect to be back in business soon. \n"); 
    while(1){}
}