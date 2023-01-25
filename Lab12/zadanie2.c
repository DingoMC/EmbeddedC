#include <targets/AT91SAM7X256.h>
#define MCK 32000000
#define PWM_CLOCK_FREQ (MCK/32)
#define PWM_PERIOD (408)
#define PWM_DUTY_CYCLE (PWM_PERIOD/2)

int main (void) {
  unsigned int T = 200000; // 200 ms
  unsigned int d = 0.2 * T; // Wypełnienie 20% okresu
  PMC_PCER = (1 << PIOB_ASR) | (1 << PWM_CPRD1);
  PWM_CMR1 |= 5; // Prescaler 0101 MCK / 32 = 1MHz
  PWM_CPRD1 = T;
  PWM_CDTY1 = d;
  PWM_ENA = 1 << 1;
  while (1) {
    
  }
  return 0;
}
