#include <targets/AT91SAM7X256.h>

int main(void){
	PMC_PCER = 1 << 3;
	PIOB_PER = 1 << 20;
	PIOB_OER = 1 << 20;		// PB20 jako wyjscie
	PIOB_OWER = 1 << 20;
	PIT_PIVR;
	PIT_MR = 299999 | (1 << 24);
	/*
	MCR = 48MHz
	48MHz / 16 = 3MHz 3 miliony razy na sekunde
	PIT_MR = 299999 (300000 odliczen zajmie 0.1s)
	przepelnienie co 0.1s
	5s odiczymy zatem 5 / 0.1 = 50 razy
	inkrementacja PICNT do 50
	*/
	while(1){
		if(PIT_PIIR >= (50 << 20)){
			PIT_PIVR;
			PIOB_ODSR ^= 1 << 20;
		}
	}
	return 0;
}
