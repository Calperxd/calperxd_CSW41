  PUBLIC EightBitHistogram                        ;Torna a fun��o acess�vel fora de histogram.s

  SECTION .text : CODE(4)                         ;Define uma sess�o e alinhamento
  THUMB                                           ;Instru��es do tipo thumb


EightBitHistogram:
  PUSH {R4-R12, LR}
  MOV R0,#1
  POP {R4-R12, PC}
  END