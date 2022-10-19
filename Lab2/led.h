#ifndef LED_H
#define LED_H
void LED_konf (unsigned int LED_number);
void LED_Set (unsigned int LED_number);
void LED_Clear (unsigned int LED_number);
void LED_Toggle (unsigned int LED_number);
unsigned int LED_GetState (unsigned int LED_number);
#endif
