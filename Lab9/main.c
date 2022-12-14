#include <targets\AT91SAM7.h>
#include "pcf8833u8_lcd.h"

const int options = 4;
int maxdepths[4] = {1, 2, 2, 1};
int suboptions[4] = {0, 4, 2, 0};

void czas(int ms){
  volatile int a,b;
  for(a=0;a<=ms;a++){
    for(b=0;b<=3000;b++){
      __asm__("NOP");
    }
  }
}

void showMainMenu (int sel) {
    LCDClearScreen();
    // Glowne Menu: Zaznaczona opcja - czarny tekst na bialym tle
    LCDPutStr("1.Autor", 20, 5, MEDIUM, (sel == 0) ? GREEN : BLACK, (sel == 0) ? BLACK : WHITE);
    LCDPutStr("2.Figury", 40, 5, MEDIUM, (sel == 1) ? GREEN : BLACK, (sel == 1) ? BLACK : WHITE);
    LCDPutStr("3.Obraz", 60, 5, MEDIUM, (sel == 2) ? GREEN : BLACK, (sel == 2) ? BLACK : WHITE);
    LCDPutStr("4.Tekst i obraz", 80, 5, MEDIUM, (sel == 3) ? GREEN : BLACK, (sel == 3) ? BLACK : WHITE);
}

void showSubmenu (int sel, int subsel) {
    if (sel == 0 || sel == 3) return;
    if (sel == 1) {
        LCDClearScreen();
        LCDPutStr("1.okrag", 20, 5, MEDIUM, (subsel == 0) ? BLUE : BLACK, (subsel == 0) ? BLACK : WHITE);
        LCDPutStr("2.kwadrat", 40, 5, MEDIUM, (subsel == 1) ? BLUE : BLACK, (subsel == 1) ? BLACK : WHITE);
        LCDPutStr("3.trojkat", 60, 5, MEDIUM, (subsel == 2) ? BLUE : BLACK, (subsel == 2) ? BLACK : WHITE);
        LCDPutStr("4.trapez", 80, 5, MEDIUM, (subsel == 3) ? BLUE : BLACK, (subsel == 3) ? BLACK : WHITE);
    }
    if (sel == 2) {
        LCDClearScreen();
        LCDPutStr("1.obraz 1", 20, 5, MEDIUM, (subsel == 0) ? BLUE : BLACK, (subsel == 0) ? BLACK : WHITE);
        LCDPutStr("2.obraz 2", 40, 5, MEDIUM, (subsel == 1) ? BLUE : BLACK, (subsel == 1) ? BLACK : WHITE);
    }
}

void showContent (int sel, int subsel) {
    LCDClearScreen();
    if (sel == 0) {
        LCDPutStr("Marcin Basak", 20, 20, MEDIUM, BLACK, WHITE);
        LCDPutStr("5.1", 40, 20, MEDIUM, BLACK, WHITE);
    }
    if (sel == 1) {
        if (subsel == 0) LCDSetCircle(65, 65, 10, BLACK);
        if (subsel == 1) LCDSetRect(40, 40, 80, 80, WHITE, BLACK);
        if (subsel == 2) {
            LCDSetLine(40, 40, 40, 50, BLACK);
            LCDSetLine(40, 40, 50, 45, BLACK);
            LCDSetLine(40, 50, 50, 45, BLACK);
        }
        if (subsel == 3) {
            LCDSetLine(40, 40, 40, 80, BLACK);
            LCDSetLine(40, 40, 60, 50, BLACK);
            LCDSetLine(40, 80, 60, 70, BLACK);
            LCDSetLine(60, 50, 60, 70, BLACK);
        }
    }
    if (sel == 2) {
        if (subsel == 0) LCDWrite130x130bmp();
        if (subsel == 1) LCDWrite130x130bmp();
    }
    if (sel == 3) {
        LCDWrite130x130bmp();
        LCDPutStr("Marcin Basak", 20, 20, MEDIUM, BLACK, WHITE);
    }
}

int main () {
    PMC_PCER = 1 << 3;
    PMC_PCER |= 1 << 2;
    PIOA_PER |= (1 << 7 | 1 << 8 | 1 << 9 | 1 << 14 | 1 << 15); // Kontrola joysticka (7 - lewo, 8 - dol, 9 - gora, 14 - prawo, 15 - wcisniecie)
    PIOB_PER |= (1 << 24 | 1 << 25);  // Kontrola - przycisk lewy i prawy
    PIOB_ODR = (1 << 24 | 1 << 25);   // Przyciski jako wejscie
    PIOA_ODR = (1 << 7 | 1 << 8 | 1 << 9 | 1 << 14 | 1 << 15);  // Joystick jako wejscie
    InitLCD();
    SetContrast(30);
    LCDClearScreen();
    int selection[2] = {0, 0};
    int depth = 0;
    showMainMenu(selection[0]);
    while (1) {
        // Powrot
        if ((PIOB_PDSR & 1 << 24) == 0 || (PIOA_PDSR & 1 << 7) == 0) {
            if (depth > 0) {
                depth--;
                if (depth == 0) {
                    selection[1] = 0;
                    showMainMenu(selection[0]);
                }
                if (depth == 1 && depth < maxdepths[selection[0]]) showSubmenu(selection[0], selection[1]);
            }
            czas(250);
        }
        // Enter
        if ((PIOB_PDSR & (1 << 25)) == 0 || (PIOA_PDSR & 1 << 14) == 0 || (PIOA_PDSR & 1 << 15) == 0) {
            if (depth < maxdepths[selection[0]]) {
                depth++;
                if (depth == 1) {
                    if (depth < maxdepths[selection[0]]) showSubmenu(selection[0], selection[1]);
                    else showContent(selection[0], selection[1]);
                }
                else if (depth == 2) showContent(selection[0], selection[1]);
            }
            czas(250);
        }
        // Dol
        if ((PIOA_PDSR & (1 << 8)) == 0) {
            if (depth < maxdepths[selection[0]]) {
                selection[depth]++;
                if (depth == 0) {
                    if (selection[depth] >= options) selection[depth] = 0;
                    showMainMenu(selection[0]);
                }
                if (depth == 1) {
                    if (selection[depth] >= suboptions[selection[0]]) selection[depth] = 0;
                    showSubmenu(selection[0], selection[1]);
                }
            }
            czas(250);
        }
        // Gora
        if ((PIOA_PDSR & 1 << 9) == 0) {
            if (depth < maxdepths[selection[0]]) {
                selection[depth]--;
                if (depth == 0) {
                    if (selection[depth] < 0) selection[depth] = options - 1;
                    showMainMenu(selection[0]);
                }
                if (depth == 1) {
                    if (selection[depth] < 0) selection[depth] = suboptions[selection[0]] - 1;
                    showSubmenu(selection[0], selection[1]);
                }
            }
            czas(250);
        }
    }
}
