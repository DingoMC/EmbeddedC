int main () {
  MCK = 48000000;
  
  // CPIV inkrementowany 48MHz/16 = 3 miliony razy na sekunde
  // Odliczenie 300000 inkrementacji zajmie 0.1s (zapisujemy w sekcji PIV rejestru PIT_MR)
  PIT_MR = 300000 | 1 << 24;
  // Po wykonaniu 50 takich odliczeń otrzymamy 0.1s* 50 = 5s
  // Czekamy zatem na doliczenie do wartości 50 w PICNT
  while (1) {
    if (PICNT == 50) {
      // Kod co 5s
      PICNT = 0;
    }
  }
}
