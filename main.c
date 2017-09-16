#include "msp.h"



/* DriverLib Includes */
#include <ti/devices/msp432p4xx/driverlib/driverlib.h>

/* Standard Includes */
#include <stdint.h>
#include <stdbool.h>

/**
 * main.c
 */

int main(void)
{
	volatile uint32_t ii;
	volatile uint32_t jj;
    /* Stop Watchdog  */
    MAP_WDT_A_holdTimer();



	/* Configuring Pins as output */
	MAP_GPIO_setAsOutputPin(GPIO_PORT_P2, GPIO_PIN3 | GPIO_PIN4 | GPIO_PIN5 | GPIO_PIN6 | GPIO_PIN7);
	MAP_GPIO_setOutputLowOnPin(GPIO_PORT_P2, GPIO_PIN3 | GPIO_PIN4 | GPIO_PIN5 | GPIO_PIN6 | GPIO_PIN7);

	uint16_t pins = GPIO_PIN7;	//0x0080

	/* Configuring SysTick to trigger at 1500000 (MCLK is 1.5MHz so this will
	* make it toggle every 1s) */
	MAP_SysTick_enableModule();
	MAP_SysTick_setPeriod(1500000);
	//MAP_Interrupt_enableSleepOnIsrExit();
	MAP_SysTick_enableInterrupt();

	/* Enabling MASTER interrupts */
	MAP_Interrupt_enableMaster();

	while (1)
	{
			MAP_GPIO_setOutputHighOnPin(GPIO_PORT_P2, pins);
			/* Delay*/
			MAP_PCM_gotoLPM0();
			MAP_GPIO_setOutputLowOnPin(GPIO_PORT_P2, pins);

			pins = pins >> 1;

			if(pins == 4){
				pins = GPIO_PIN7;
			}
	}
}
void SysTick_Handler(void)
{
//MAP_GPIO_toggleOutputOnPin(GPIO_PORT_P1, GPIO_PIN0);
}
