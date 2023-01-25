#include <targets/AT91SAM7X256.h>

int main (void) {
  PMC_PCER = 1<<3 | 1<<10;
  PIOB_PDR = 1<<22;
  PIOB_ASR = 1<<22;
  PWM_CMR2 = 1<<8;  // CALG = 1 center-aligned
  PWM_CPRD2 = 1632000000; // Ustawienie okresu sygnalu
  PWM_CDTY2 = 816000000; // Wypełnienie 50% okresu
  PWM_ENA= 1<<2; // zalaczenie sygnału wyjsciowego kanalu PWM1
  while (1) {
    
  }
  return 0;
}
/*
  408 = (2*CPRD*DIVA*PREA) / 64000000
  13056000000 = (CPRD*DIVA*PREA)
  DIVA=1
  PREA=8
  CPRD = 1 632 000 000
  CDTY = CPRD * 0.5 = 816 000 000
*/
