#include "gpio.h"


uint8_t set_gpio_clock(void)
{
  // Enable and wait for the port to be ready for access
  SysCtlPeripheralEnable(SYSCTL_PERIPH_GPION);
  while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPION))
  {
  }
  // Configure the GPIO port for the LED operation.
  GPIOPinTypeGPIOOutput(GPIO_PORTN_BASE, (GPIO_PIN_0|GPIO_PIN_1));
  // If the program reaches here, then the work is done
  return 1;
}


void blink_test(void)
{
  // Turn on the LED
  GPIOPinWrite(GPIO_PORTN_BASE, (GPIO_PIN_0|GPIO_PIN_1), GPIO_PIN_0);
  // Delay for a bit
  SysCtlDelay(get_system_clock()/600);
  // Turn on the LED
  GPIOPinWrite(GPIO_PORTN_BASE, (GPIO_PIN_0|GPIO_PIN_1), GPIO_PIN_1);
  // Delay for a bit
  SysCtlDelay(get_system_clock()/600);
  
  
  
}