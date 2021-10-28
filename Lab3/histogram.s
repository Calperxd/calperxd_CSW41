  PUBLIC EightBitHistogram                        ;Torna a fun??o acess?vel fora de histogram.s

  SECTION .text : CODE(2)                         ;Define uma sess?o e alinhamento
  THUMB                                           ;Instru??es do tipo thumb

EightBitHistogram         PUSH {R4-R12, LR}              ; Salvando contexto
  MUL R0,R0,R1                   ;Numero de elementos a serem processados
  MOV R12, #65536                ;R12 guarda o valor m?ximo de 64k
  CMP R0, R12                    ;Compara se o tamanho nao excede o tamanho m?ximo
  IT HS
  BHS Return                     ; Caso seja maior colaca 0 no R0 e retorna para o fluxo do programa
iter
  LDRB R4,[R2]                ; Carrega a primera posi??o da matriz
  STRB  R4,[R3]
  ADD R2,R2,#1
  ADD R3,R3,#1
  ADD R5,R5,#1
  CMP R5,R0
  BNE iter
  POP {R4-R12, PC}               ;Voltando para o contexto
  

Return
  MOV R0,#0
  POP {R4-R12, PC}               ;Voltando para o contexto
  
  
  
  


  END