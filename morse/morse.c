#include "MK20DX256.h"

/* Variable to store millisecond ticks */
volatile unsigned long msTicks;

/* Function declaration */
void wait(uint32_t milliseconds);
void morse(char *str);

/* LED impulse time (in ms) */
const uint32_t impulse = 200;

const char *ascii = "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789.,?'!/()&:;=+-_\"$@";
const char *bips[] = { ".-","-...","-.-.","-..",".","..-.","--.","....","..",".---",
                       "-.-",".-..","--","-.","---",".--.","--.-",".-.","...","-",
                       "..-","...-",".--","-..-","-.--","--..","-----",".----","..---",
                       "...--","....-",".....","-....","--...","---..","----.",".-.-.-",
                       "--..--","..--..",".----.","-.-.--","-..-.","-.--.","-.--.-",
                       ".-...","---...","-.-.-.","-...-",".-.-.","-....-","..--.-",
                       ".-..-.","...-..-",".--.-."};

int main(void) {
    // Enable GPIO Port C clock
    SIM->SCGC5 = SIM_SCGC5_PORTC_MASK;

    // Set Port C pin 5 as GPIO (default to be input)
    PORTC->PCR[5] = PORT_PCR_MUX(1);
    // Set it as OUTPUT
    PTC->PDDR = (1<<5);

    // Generate interrupt each 1 ms
    if (SysTick_Config(SystemCoreClock / 1000) != 0)
        return -1;

    while (1) {
        msTicks = 0;
        morse("Teensy 3 rocks!!!");
        wait(5000);
    }

    return 0; // Should never reach it
}

void wait(uint32_t milliseconds) {
    uint32_t curTicks = msTicks;

    while ((msTicks - curTicks) < milliseconds)
        ;// Do nothing
}

void morse(char *str) {
    int i = 0;
    char dot_dah[256] = "";
    char *c;

    // Convert ASCII to dot/dah
    for (i = 0; str[i]; i++) {
        if (c = strchr(ascii, toupper(str[i])))
            strcat(dot_dah, bips[c - ascii]);
        else
            strcat(dot_dah," ");
    }

    // Outputs dot_dah as led impulses
    for (i = 0; dot_dah[i]; i++) {
        switch (dot_dah[i]) {
            case '.':
                PTC->PSOR = (1<<5);
                wait(impulse);
                PTC->PCOR = (1<<5);
                wait(impulse);
                break;
            case '-':
                PTC->PSOR = (1<<5);
                wait(3 * impulse);
                PTC->PCOR = (1<<5);
                wait(impulse);
                break;
            case ' ':
                wait(7 * impulse);
                break;
        }
    }
}

void SysTick_Handler(void) {
    msTicks++;
}
