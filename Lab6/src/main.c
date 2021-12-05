#include <stdint.h>
#include <stdbool.h>
#include "tx_api.h"
#include "inc/hw_memmap.h"
#include "driverlib/gpio.h"
#include "driverlib/sysctl.h"

#define STACK_SIZE 1024 
#define BYTE_POOL_SIZE (TX_MINIMUM_STACK * 20)


UCHAR                   byte_pool_memory[BYTE_POOL_SIZE];

// TCB for each thread
TX_THREAD               thread1;
TX_THREAD               thread2;
TX_THREAD               thread3;

// Tx byte pool
TX_BYTE_POOL byte_pool;
UINT status;

//Threads functions
void thread_led_1(ULONG thread_input);
void thread_led_2(ULONG thread_input);
void thread_led_3(ULONG thread_input);
//Setup function
void led_setup(void);

int main()
{
   led_setup();
   tx_kernel_enter();
}

void led_setup(void)
{
   SysCtlPeripheralEnable(SYSCTL_PERIPH_GPION);
   while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPION))
   {
   }
   GPIOPinTypeGPIOOutput(GPIO_PORTN_BASE, GPIO_PIN_0);
}

//Threads configs
void    tx_application_define(void *first_unused_memory)
{
   // This pointer is used to store the address requested
   // by the user to the kernel, where is the stack .
   CHAR    *pointer = TX_NULL;
   status = tx_byte_pool_create
   (
      &byte_pool,
      "Block of memory",
      byte_pool_memory,
      BYTE_POOL_SIZE
   );

    /* Allocate the stack for thread 0. */
   status = tx_byte_allocate
   (
      &byte_pool,                // Address of block pool
      (VOID**)&pointer,          // Recieve the address of stack
      STACK_SIZE,                // The size requested
      TX_NO_WAIT                 // Create the region immediately
   );

   
   // Attemp to create
   status = tx_thread_create
   (
      &thread1,               // Pointer to a thread control block.
      "thread 0",             // Pointer to the name of the thread
      thread_led_1,           // Thread function
      30,                     // A 32-bit value that is passed to the thread's entry function when it first executes
                              // in this case we'll pass the value that we want thread execute
      pointer,                // Pointer to stack
      STACK_SIZE,             // Size of its own stack
      1,                      // Priority
      1,                      // Preempt threhold
      TX_NO_TIME_SLICE,       // Time quantum
      TX_AUTO_START           // Start immediately
   );
   
   
   tx_block_release(pointer);

}


//Threads

void thread_led_1(ULONG thread_input)
{
  uint32_t ui32Loop;
  while(1)
  {
       GPIOPinWrite(GPIO_PORTN_BASE, GPIO_PIN_0, GPIO_PIN_0);
        for(ui32Loop = 0; ui32Loop < 200000; ui32Loop++)
        {
        }
        GPIOPinWrite(GPIO_PORTN_BASE, GPIO_PIN_0, 0x0);
        for(ui32Loop = 0; ui32Loop < 200000; ui32Loop++)
        {
        }
    
  }
}