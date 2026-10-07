//-------------------------
//--- switches.c ---
//-------------------------

/*

SW0-SW1 Välj algoritm - visa antal besökta noder samt path length, execution time (bra till performance analysis)
00 BFS
01 DFS
10 Djikstra
11 Jämförelseläge? (alla tre)

BTN
1 Starta vald algoritm

SW2-SW3 Storlek på maze
00 8x8
01 16x16
10 32x32
11 64x64

SW4 Väggar på/av (när varje gång vi slår på så är väggarna random)
0 av
1 på

*/


#include <stdio.h>
#include <stdlib.h>

// Swtiches, reads SW0-Sw9
int get_sw(void){

  volatile int *switches = (volatile int *) 0x04000010; 
  return *switches & 0x3FF;
}

// Buttons
int get_btn(void){

  volatile int *button = (volatile int *) 0x040000d0;
  return *button & 0x1;
}

