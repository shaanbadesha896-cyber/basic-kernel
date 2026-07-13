#ifndef INCLUDE_SERIALIO_H
#define INCLUDE_SERIALIO_H

extern "C" void outb(unsigned short port, unsigned char data);

namespace std{
    namespace serial{
        inline void putc(char character){
            outb(0x3F8, character); 
        }

        inline void write(const char* string){
            int i = 0; 
            while(string[i] != '\0'){
                putc(string[i]);
                ++i; 
            }
        }
    }
}

#endif

