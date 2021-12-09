#ifndef SYSTEM_H
#define SYSTEM_H

#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_types.h"
#include "inc/hw_memmap.h"
#include "driverlib/sysctl.h"


uint8_t set_system_clock(void);
uint32_t get_system_clock(void);

#endif /* SYSTEM_H */