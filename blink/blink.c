#include "MK20DX256.h"

/* Variable to store millisecond ticks */
volatile unsigned long msTicks;
void wait(uint32_t milliseconds);

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
        // Toggle Port C pin 5 state
        PTC->PTOR = (1<<5);
        wait(200);
        PTC->PTOR = (1<<5);
        wait(1000);
    }

    return 0; 
}

void wait(uint32_t milliseconds) {
    uint32_t curTicks = msTicks;

    while ((msTicks - curTicks) < milliseconds)
        ;// Do nothing
}

void SysTick_Handler(void) {
    msTicks++;
}
