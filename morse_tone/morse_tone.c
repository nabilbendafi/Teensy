#include "MK20DX256.h"

/* Variable to store millisecond ticks */
volatile unsigned long msTicks;

/* Function declaration */
void wait(uint32_t milliseconds);
void morse(char *str);

/* LED impulse time (in ms) */
const uint32_t impulse = 100;
/* Bip frequency (in Hz) */
const uint32_t frequency = 5000;

const char *ascii = "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789.,?'!/()&:;=+-_\"$@";
const char *bips[] = { ".-","-...","-.-.","-..",".","..-.","--.","....","..",".---",
                       "-.-",".-..","--","-.","---",".--.","--.-",".-.","...","-",
                       "..-","...-",".--","-..-","-.--","--..","-----",".----","..---",
                       "...--","....-",".....","-....","--...","---..","----.",".-.-.-",
                       "--..--","..--..",".----.","-.-.--","-..-.","-.--.","-.--.-",
                       ".-...","---...","-.-.-.","-...-",".-.-.","-....-","..--.-",
                       ".-..-.","...-..-",".--.-."};

int main(void) {
    // Enable GPIO Port A and C clock
    SIM->SCGC5 = SIM_SCGC5_PORTA_MASK |
                 SIM_SCGC5_PORTC_MASK;

    // Enable FTM1 clock
    SIM->SCGC6 = SIM_SCGC6_FTM1_MASK;

    // Set Port A pin 12 as FMT1 Ch 0 
    // and Port C pin 5 as GPIO (default to be input)
    PORTA->PCR[12] = PORT_PCR_MUX(3);
    PORTC->PCR[5] = PORT_PCR_MUX(1);
    // Set GPIO as OUTPUT
    PTC->PDDR = (1<<5);

    // System clock, Select divider
    FTM1->SC = FTM_SC_CLKS(1) | FTM_SC_PS(2);
    // No Interrupts - High True pulses on Edge Aligned PWM
    FTM1->CONTROLS[0].CnSC = FTM_CnSC_MSB_MASK |
                             FTM_CnSC_ELSB_MASK;
    // Initial value of PWM counter
    FTM1->CNTIN = 0;
    // any write to CNT copies CNTIN to the counter;
    FTM1->CNT = 0;
    // always init CNT before initing MOD!
    // upper limit of PWM counter
    FTM1->MOD = SystemCoreClock / 2 / frequency;

    FTM1->SYNC |= FTM_SYNC_SWSYNC_MASK;

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

void bip_led(int on) {
    if (on) {
        FTM1->CONTROLS[0].CnV = FTM1->MOD/2;
        PTC->PSOR = (1<<5);
    } else {
        FTM1->CONTROLS[0].CnV = 1;
        PTC->PCOR = (1<<5);
    }
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

    // Outputs dot_dah as tone and led impulses
    for (i = 0; dot_dah[i]; i++) {
        switch (dot_dah[i]) {
            case '.':
                bip_led(1);
                wait(impulse);
                bip_led(0);
                wait(impulse);
                break;
            case '-':
                bip_led(1);
                wait(3 * impulse);
                bip_led(0);
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
