#include "prova.h"
int count = 0;



void systickISR(void)
{
  count++;
}



int main(void)
{
  systickConfig();
  
  
  
  
}