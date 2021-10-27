#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include "inc/hw_memmap.h"
#include "driverlib/debug.h"
#include "driverlib/gpio.h"
#include "driverlib/sysctl.h"
#include "driverlib/systick.h"



//flag that count until 30 represents 3 seconds
int flag = 0;
int flag2 = 0;
int flag3 = 1;
int ms = 0; // milissecond

void SysTickIntHandler(void)
{
  printf("%i second\n",ms);
  ms = ms + 100;
  flag++;
}

void GpioPortJIntHandler(void)
{ 
  flag2 = 1;
}

int SetupFreq(void)
{
  SysCtlClockFreqSet((SYSCTL_XTAL_25MHZ | SYSCTL_OSC_MAIN | SYSCTL_USE_PLL | SYSCTL_CFG_VCO_240), 120000000);
  return 0;
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

int SetupGPIO(void)
{
  //----------------------------------------------------------------------------------------------
  //port J
  // Enable clock on port J
  SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOJ);
  // Wait until the port is ready to use
  while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOJ))
  {
  }
  // Disable the interrupt of pin 0
  GPIOIntDisable(GPIO_PORTJ_AHB_BASE,GPIO_PIN_0);
  // Register a function to call
  GPIOIntRegister(GPIO_PORTJ_AHB_BASE, GpioPortJIntHandler);
  //Configure as:
  // PortJ
  // Pin 0
  // Strength 2 mA
  // Weak pull-up enabled
  GPIOPadConfigSet(GPIO_PORTJ_AHB_BASE,GPIO_PIN_0,GPIO_STRENGTH_2MA,GPIO_PIN_TYPE_STD_WPU);
  //Define the pin as input
  GPIOPinTypeGPIOInput(GPIO_PORTJ_BASE, GPIO_PIN_1);
  // Make pin 0 rising edge triggered interrupts.
  GPIOIntTypeSet(GPIO_PORTJ_AHB_BASE, GPIO_PIN_0, GPIO_LOW_LEVEL);
  // Enable the pin interrupts.
  GPIOIntEnable(GPIO_PORTJ_BASE, GPIO_PIN_0);
  //----------------------------------------------------------------------------------------------
  // Port N  
  // Enable clock on port N
  SysCtlPeripheralEnable(SYSCTL_PERIPH_GPION);
  // Wait until the port is ready to use
  while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPION))
  {
  }
  //Configure port as output
  GPIOPinTypeGPIOOutput(GPIO_PORTN_BASE, GPIO_PIN_0);
  //Start turned off
  GPIOPinWrite(GPIO_PORTN_BASE, GPIO_PIN_0, 0);
  
  //----------------------------------------------------------------------------------------------
  // Port F  
  // Enable clock on port N
  SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
  // Wait until the port is ready to use
  while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOF))
  {
  }
  //Configure port as output
  GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_0);
  //Start turned off
  GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_0, 0);
  return 0;
}

int main(void)
{
  SetupFreq();
  SetupSystick();
  SetupGPIO();
  while(1)
  {
    //Inicio do jogo
    if((flag == 1)&&(flag3))
    {
      GPIOPinWrite(GPIO_PORTN_BASE, GPIO_PIN_0, 1);
      printf("Iniciou o jogo\n");
      flag = 0;
      flag3 = 0;
    }
    if(ms == 3000)
    {
      printf("Jogo finalizado\n");
      flag3 = 1;
      flag = 0;
      ms = 0;
    }
    if (flag2 == 1)
    {
      SysTickDisable();
      GPIOIntDisable(GPIO_PORTJ_AHB_BASE,GPIO_PIN_0);
      GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_0, 1);
      printf("Você ganhou\n");
      flag2 = 0;
    }
    
  }
}
