  PUBLIC EightBitHistogram                        ;Torna a funcao acessivel fora de histogram.s

  SECTION .text : CODE(2)                         ;Define uma sessao e alinhamento
  THUMB                                           ;Instrucoes do tipo thumb

EightBitHistogram         PUSH {R4-R12, LR}              ; Salvando contexto
  MUL R0,R0,R1                   ;Numero de elementos a serem processados
  MOV R12, #65536                ;R12 guarda o valor m?ximo de 64k
  CMP R0, R12                    ;Compara se o tamanho nao excede o tamanho max
  MOV R12, #0
  IT HS
  BHS Return                     ; Caso seja maior colaca 0 no R0 e retorna para o fluxo do programa
  BL  MemInit                    ; Inicia a area de memoria a ser usada
  MOV R4,#0
  ADD R4, R0, R2                 ; Endereco final da iteracao na flash
iter                             ; Iterar a matriz
  LDRB  R1,[R2]                  ; Carrega posicao I da matriz em R1
  ADD R3,R1                      ; Offset no endereco base que está em R3
  ADD R3,R1                      ; Offset no endereco base que está em R3
  BL Sum                         ; Guarda posicao I da matriz na memoria
  SUB R3,R1                      ; Retira o offset e volta para o endereco base
  SUB R3,R1                      ; Retira o offset e volta para o endereco base
  ADD R2,R2,#1                   ; Percorrer os 19200 elemento na flash
  CMP R2,R4                      ; Compara se já chegou ao final da flash
  BNE iter
  MOV R0,R3
  POP {R4-R12, PC}               ;Voltando para o contexto
  

Return                           ;Valor acima do requisito de 64k retorna para a funcao main indicando 0 como retorno
  MOV R0,#0
  POP {R4-R12, PC}               ;Voltando para o contexto


Sum
  LDRH R6,[R3]                   ; Carrega em R4 o valor que existe naquela posicao de memoria
  ADD R6,R6,#1                   ; R4 = R4 + 1
  STRH R6,[R3]
  MOV R6,#0                      ; Zera o valor de R6
  BX LR
 

MemInit                         ; Funcao para dar init na memoria
  STRH  R11,[R3]                ; Zera area de memoria
  ADD R3, R3,#2
  ADD R8,#1                     ;´Iterador de memoria
  CMP R8,#512                   
  BNE MemInit
  MOV R3,R4                     ; R3 recebe o endereco da variavel
  BX LR

  END