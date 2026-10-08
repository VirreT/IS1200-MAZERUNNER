//-------------------------
//--- switches.c ---
//-------------------------


// Swtiches, reads SW0-SW5
int get_sw(void){

  volatile int *switches = (volatile int *) 0x04000010; 
  return *switches & 0x3F;
}

// Buttons
int get_btn(void){

  volatile int *button = (volatile int *) 0x040000d0;
  return *button & 0x1;
}

