#include <targets\AT91SAM7.h>
#include "pcf8833u8_lcd.h"

const int options = 4
const int maxdepths[options] = {1, 2, 2, 1};
const int suboptions[options] = {0, 4, 2, 0};

void showMainMenu (int sel) {
    LCDClearScreen();
    // Glowne Menu: Zaznaczona opcja - czarny tekst na bialym tle
    LCDPutStr("1. Autor", 20, 20, (sel == 0) ? BLACK : WHITE, (sel == 0) ? WHITE : BLACK);
    LCDPutStr("2. Figury", 40, 20, (sel == 1) ? BLACK : WHITE, (sel == 1) ? WHITE : BLACK);
    LCDPutStr("3. Obraz", 60, 20, (sel == 2) ? BLACK : WHITE, (sel == 2) ? WHITE : BLACK);
    LCDPutStr("4. Tekst i obraz", 80, 20, (sel == 3) ? BLACK : WHITE, (sel == 3) ? WHITE : BLACK);
}

void showSubmenu (int sel, int subsel) {
    if (sel == 0 || sel == 3) return;
    if (sel == 1) {
        LCDClearScreen();
        LCDPutStr("1. okrag", 20, 20, (subsel == 0) ? BLACK : WHITE, (subsel == 0) ? WHITE : BLACK);
        LCDPutStr("2. kwadrat", 40, 20, (subsel == 1) ? BLACK : WHITE, (subsel == 1) ? WHITE : BLACK);
        LCDPutStr("3. trojkat", 60, 20, (subsel == 2) ? BLACK : WHITE, (subsel == 2) ? WHITE : BLACK);
        LCDPutStr("4. trapez", 80, 20, (subsel == 3) ? BLACK : WHITE, (subsel == 3) ? WHITE : BLACK);
    }
    if (sel == 3) {
        LCDClearScreen();
        LCDPutStr("1. obraz 1", 20, 20, (subsel == 0) ? BLACK : WHITE, (subsel == 0) ? WHITE : BLACK);
        LCDPutStr("2. obraz 2", 40, 20, (subsel == 1) ? BLACK : WHITE, (subsel == 1) ? WHITE : BLACK);
    }
}

void showContent (int sel, int subsel) {
    LCDClearScreen();
    if (sel == 0) {
        LCDPutStr("Marcin Basak", 20, 20, WHITE, BLACK);
        LCDPutStr("5.1", 40, 20, WHITE, BLACK);
    }
    if (sel == 1) {
        if (subsel == 0) LCDSetCircle(65, 65, 10, WHITE);
        if (subsel == 1) LCDSetRect(40, 40, 80, 80, BLACK, WHITE);
        if (subsel == 2) {
            LCDSetLine(40, 40, 40, 50, WHITE);
            LCDSetLine(40, 40, 50, 45, WHITE);
            LCDSetLine(40, 50, 50, 45, WHITE);
        }
        if (subsel == 3) {
            LCDSetLine(40, 40, 40, 80, WHITE);
            LCDSetLine(40, 40, 60, 50, WHITE);
            LCDSetLine(40, 80, 60, 70, WHITE);
            LCDSetLine(60, 50, 60, 70, WHITE);
        }
    }
    if (sel == 2) {
        if (subsel == 0) LCDWrite130x130bmp();
        if (subsel == 1) LCDWrite130x130bmp();
    }
    if (sel == 3) {
        LCDPutStr("Marcin Basak", 20, 20, WHITE, BLACK);
        LCDWrite130x130bmp();
    }
}

int main () {
    PIOA_PER |= (1 << 7 | 1 << 8 | 1 << 9 | 1 << 14 | 1 << 15);  // Kontrola joysticka (7 - gora, 8 - lewo, 9 - prawo, 14 - dol, 15 - wcisniecie)
    PIOB_PER |= (1 << 23 | 1 << 24);  // Kontrola - przycisk lewy i prawy
    PIOB_ODR = (1 << 23 | 1 << 24);   // Przyciski jako wejscie
    PIOA_ODR = (1 << 7 | 1 << 8 | 1 << 9 | 1 << 14 | 1 << 15);  // Joystick jako wejscie
    InitLCD();
    SetContrast(30);
    LCDClearScreen();
    int selection[2] = {0, 0};
    int depth = 0;
    showMainMenu(selection[0]);
    while (1) {
        // Powrot
        if ((PIOA_PDSR & 1 << 8) == 0 || (PIOB_PDSR & 1 << 23) == 0) {
            if (depth > 0) {
                depth--;
                if (depth == 0) {
                    selection[1] = 0;
                    showMainMenu(selection[0]);
                }
                if (depth == 1 && depth < maxdepths[selection[0]]) showSubmenu(selection[0], selection[1]);
            }
        }
        // Enter
        if ((PIOA_PDSR & 1 << 9) == 0 || (PIOA_PDSR & 1 << 15) == 0 || (PIOB_PDSR & 1 << 24) == 0) {
            if (depth < maxdepth[selection[0]]) {
                depth++;
                if (depth == 1) {
                    if (depth < maxdepths[selection[0]]) showSubmenu(selection[0], selection[1]);
                    else showContent(selection[0], selection[1]);
                }
                if (depth == 2) showContent(selection[0], selection[1]);
            }
        }
        // Gora
        if ((PIOA_PDSR & 1 << 7) == 0) {
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
        }
        // Dol
        if ((PIOA_PDSR & 1 << 14) == 0) {
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
        }
    }
}
