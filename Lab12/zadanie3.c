#include <targets/AT91SAM7X256.h>

int main (void) {
  PMC_PCER = 1<<3 | 1<<10;
  PIOB_PDR = 1<<22;
  PIOB_ASR = 1<<22;
  PWM_MR = 1<<0; // Zegary wylaczone
  PWM_CMR1 = 1<<8;  // CALG = 1 center-aligned
  PWM_CPRD1 = 200000; // Okres sygnału 3200000
  PWM_CDTY1 = 0.2 * 200000; // Wypełnienie 20% * 3200000
  PWM_ENA= 1<<1; // zalaczenie sygnału wyjsciowego kanalu PWM1
  while (1) {
    
  }
  return 0;
}
