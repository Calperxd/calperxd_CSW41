  PUBLIC EightBitHistogram                        ;Torna a função acessível fora de histogram.s

  SECTION .text : CODE(4)                         ;Define uma sessão e alinhamento
  THUMB                                           ;Instruções do tipo thumb


EightBitHistogram:
  PUSH {R4-R12, LR}
  MOV R0,#1
  POP {R4-R12, PC}
  END