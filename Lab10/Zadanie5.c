#include <targets/AT91SAM7X256.h>
int main() {
  PMC_PCER = 1<<3;
  PIOB_PER = 1<<20;
  PIOB_OER = 1<<20;
  PIOB_OWER = 1<<20;
  PMC_PCER |= 1<<12;
  TC0_CCR = 1<<1;
  TC0_SR;
  TC0_CMR = 3; //Najwyzszy mozliwy dzielnik TIMER_CLOCK4 MCK/128
  TC0_RC = 37500; //RC obliczony ze wzoru (128 * 37500) / 48000000 = 0.1s
  TC0_CCR = 1<<0 | 1<<2;
  while(1){
    if((TC0_SR & 1<<0) != 0) PIOB_ODSR ^= 1<<20; // Sprawdzenie czy na bicie COVFS jest 1
  }
  return 0;
}
