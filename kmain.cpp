extern "C"{
char* frame_buffer= reinterpret_cast<char*> (0x000B8000);

frame_buffer[0]= 'A';
frame_buffer[1] = 0x0F;
}
