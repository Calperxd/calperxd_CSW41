#include "system.h"

uint32_t ClockSystem;



uint8_t set_system_clock(void)
{
  //ClockSystem
  ClockSystem = SysCtlClockFreqSet(
                                    (SYSCTL_XTAL_25MHZ |
                                     SYSCTL_OSC_MAIN |
                                     SYSCTL_USE_PLL |
                                     SYSCTL_CFG_VCO_240), 
                                     120000000
                                    );
  // Initialization done
  if(ClockSystem > 0) return 1;
  else return 0;
}


uint32_t get_system_clock(void)
{
  if(ClockSystem > 0) return ClockSystem;
  else return 0;
}