#include <targets/AT91SAM7.h>
/*
    PCER - Peripherial Clock Enable
    PER - PIO Enable
    OER - Output Enable
    ODR - Output Disable
    SODR - Set Output Data (0 - nic, 1 - ustawia 1)
    CODR - Clear Output Data (0 - nic, 1 - ustawia 0)
    PDSR - Pin Data Status
*/
int main (void) {
    PMC_PCER = 1<<3; //załączenie zegara systemowego do wybranego peryferium (w tym przypadku PIOB). Zapoznad się z rozdziałem 25.5 str. 173 oraz peripheral identifiers str. 30
    PIOB_PER = 1<<20; //załączenie kontroli kontrolera I/O nad wybranym PINem – w tym przypadku PIN 65 będzie kontrolowany przez linię 20 kontorlera I/O B 27.4.2
    PIOB_PER |= 1<<24; // j.w.
    PIOB_OER = 1<<20; // linia 20 portu B pracuje jako wyjście 27.4.4
    PIOB_ODR = 1<<24; // linia 24 portu B pracuje jako wejściowa 27.4.4
    PIOB_SODR = 1<<20; // stan linii 20 portu B ustawiony na 1 (na PINie 65 ustawiony został stan wysoki)
    while(1) { //pętla nieskooczona tak, by program oczekiwał na wciśnięcie przycisku
        if ((PIOB_PDSR & 1<<24) == 0) {
          /* sprawdzenie stanu linii 24 Portu B (PIN 70), jeśli na linii 24 jest
          stan wysoki – na bicie 24 rejestru PDSR pojawia się 1, jeśli stan jest
          linii jest niski – na bicie pojawia się 0*/
          PIOB_CODR = 1<<20; // stan linii 20 portu B ustawiony na 1 (na PINie 65 ustawiony został stan niski)
        }
    }
}
