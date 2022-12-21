#include <targets/AT91SAM7X256.h>
void timer_counter0_conf (unsigned int prescaler, unsigned int mode) {
  if (prescaler > 4) prescaler = 4;
  unsigned int div = 1;
  switch (prescaler) {
    case 0: { div = 2; break; }
    case 1: { div = 8; break; }
    case 2: { div = 32; break; }
    case 3: { div = 128; break; }
    case 4: { div = 1024; break; }
    default: { break; }
  }
  unsigned int rc_value = 0.1 * 48000000 / div;
  if (rc_value > 65535) return;
  TC0_CCR = 1<<1;
  TC0_SR;
  TC0_CMR = prescaler;
  TC0_RC = rc_value;
  TC0_CCR = 1<<0 | 1<<2;
}
int main() {
  PMC_PCER = 1<<3;
  PIOB_PER = 1<<20;
  PIOB_OER = 1<<20;
  PIOB_OWER = 1<<20;
  PMC_PCER |= 1<<12;
  timer_counter0_conf(4, 0);
  while(1){
    if((TC0_SR & 1<<0) != 0) PIOB_ODSR ^= 1<<20; // Sprawdzenie czy na bicie COVFS jest 1
  }
  return 0;
}
