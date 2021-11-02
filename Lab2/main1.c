#include <stdint.h>
#include <stdbool.h>
#include "driverlib/systick.h"
#include "inc/hw_memmap.h"
#include "driverlib/debug.h"
#include "driverlib/gpio.h"
#include "driverlib/sysctl.h"

int flag = 0;

void SysTickIntHandler(void)
{
  flag++;
}

int SetupSystick()
{
  SysTickDisable();
  // The clock is 120MHz, so basically the variable will count every 8.33ns
  // Configure the SysTick counter.
  // Every 10 flag makes 1 second
  SysTickPeriodSet(12000000);
  // Pointer tu a function
  SysTickIntRegister(SysTickIntHandler);
  // Enable the SysTick counter.
  SysTickIntEnable();
  SysTickEnable();
  return 0;
}

int main(void)
{
  SetupSystick();
  volatile uint32_t ui32Loop;
  SysCtlClockFreqSet((SYSCTL_XTAL_25MHZ |
                                       SYSCTL_OSC_MAIN |
                                       SYSCTL_USE_PLL |
                                       SYSCTL_CFG_VCO_240), 120000000);
    // Enable the GPIO port that is used for the on-board LED.
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPION);
    // Check if the peripheral access is enabled.
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPION))
    {
    }
    // Enable the GPIO pin for the LED (PN0).  Set the direction as output, and
    // enable the GPIO pin for digital function.
    GPIOPinTypeGPIOOutput(GPIO_PORTN_BASE, GPIO_PIN_0);
    // Loop forever.
    while(1)
    {
      if(flag == 15)
      {
        // Turn on the LED.
        GPIOPinWrite(GPIO_PORTN_BASE, GPIO_PIN_0, GPIO_PIN_0);
        // Turn off the LED.
      }
      if(flag == 30)
      {
        GPIOPinWrite(GPIO_PORTN_BASE, GPIO_PIN_0, 0x0);
        flag = 0;
      }
    }
}
