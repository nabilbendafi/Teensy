#include "MK20DX256.h"

#include "FreeRTOS.h"
#include "task.h"

/* Priorities at which the tasks are created. */
#define mainLED_TASK_PRIORITY		( tskIDLE_PRIORITY + 1 )

/* Variable to store millisecond ticks */
volatile unsigned long msTicks;

void ledToggle();
static void prvSetupHardware(void);

int main(void) {
    
    /* Setup the microcontroller hardware */
    prvSetupHardware();

    xTaskCreate(ledToggle, "ledToggle", configMINIMAL_STACK_SIZE, NULL, mainLED_TASK_PRIORITY, NULL);

    /* Start the tasks and timer running. */
    vTaskStartScheduler();

    /* Should never reach it */
    for(;;);
}

static void prvSetupHardware(void) {

    // Enable GPIO Port C clock
    SIM->SCGC5 = SIM_SCGC5_PORTC_MASK;

    // Set Port C pin 5 as GPIO (default to be input)
    PORTC->PCR[5] = PORT_PCR_MUX(1);

    // Set it as OUTPUT
    PTC->PDDR = (1<<5);

    /* Start with LED off. */
    PTC->PCOR = (1<<5);
}

void ledToggle() {
    for(;;) {
        PTC->PSOR = (1<<5);
        vTaskDelay(200);
        PTC->PCOR = (1<<5);
        vTaskDelay(1000);
    }
}
