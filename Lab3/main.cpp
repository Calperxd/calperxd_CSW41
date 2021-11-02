#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include "image.h"



int main()
{
  uint16_t histogram;           
  uint16_t *p_hist;         
  p_hist = &histogram;
  
  uint16_t *p_hist_result;
  
  p_hist_result = EightBitHistogram(WIDTH1,HEIGTH1,p_start_image1, &histogram);
  for(uint16_t i =0; i < 256     ; i = i + 1)
  {
    printf("posicao %#04x possui %i  pixels\n",i,p_hist[i]);
      p_hist[i]=0;
  }
  
  return 0;
}
