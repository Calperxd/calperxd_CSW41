#include "system.h"
#include "gpio.h"






void main(void)
{
  
    set_system_clock();
    set_gpio_clock();
    while(1)
    {
      blink_test();
    }
}