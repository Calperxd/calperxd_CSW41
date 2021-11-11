  PUBLIC systickConfig                            ;Torna a funcao acessivel fora de histogram.s
  PUBLIC systickISR                               ;Torna a funcao acessivel fora de histogram.s
  SECTION .text : CODE(2)                         ;Define uma sessao e alinhamento
  THUMB                                           ;Instrucoes do tipo thumb

NVIC_ST_CTRL_R        EQU 0xE000E010
NVIC_ST_RELOAD_R      EQU 0xE000E014
NVIC_ST_CURRENT_R     EQU 0xE000E018
DELAY1MS EQU 80000

systickConfig
	LDR R1, =NVIC_ST_CTRL_R			; R1 = &NVIC_ST_CTRL_R (ponteiro)
	MOV R0, #0 						; desabilita Systick durante a configura??o
	STR R0, [R1]					; escreve no endere?o de mem?ria do perif?rico
	LDR R1, =NVIC_ST_RELOAD_R 		; R1 = &NVIC_ST_RELOAD_R (pointeiro)
	LDR R0, =0x00FFFFFF; 			; valor m?ximo de recarga 2^24 ticks
	STR R0, [R1] 					; escreve no endere?o de mem?ria do perif?rico o NVIC_ST_RELOAD_M
	LDR R1, =NVIC_ST_CURRENT_R 		; R1 = &NVIC_ST_CURRENT_R (ponteiro)
	MOV R0, #0 						; qualquer escrita no endere?o NVIC_ST_CURRENT_R o limpa
	STR R0, [R1] 					; limpa o contador
	LDR R1, =NVIC_ST_CTRL_R 		; habilita o SysTick com o clock do core
	MOV R0, #0x05					; ENABLE | CLK_SRC
	STR R0, [R1] 					; Seta os bits de ENABLE e CLK_SRC na mem?ria
	BX LR
	
;------------SysTick_Wait------------
; Atraso de tempo utilizando processador ocupado
; Entrada: R0 -> par?metro de delay em unidades do clock do core (12.5ns)
; Sa?da: Nenhum
; Modifica: R0, R1 e R3
SysTick_Wait
	LDR R1, =NVIC_ST_RELOAD_R 	       ; R1 = &NVIC_ST_RELOAD_RSUB R0 (ponteiro)
	SUB R0, #1                          
	STR R0, [R1] 						; delay-1, n?mero de contagens para esperar
	LDR R1, =NVIC_ST_CTRL_R 			; R1 = &NVIC_ST_CTRL_R
SysTick_Wait_loop
	LDR R3, [R1] 						; R3 = &NVIC_ST_CTRL_R (ponteiro)
	ANDS R3, R3, #0x00010000 			; O bit COUNT est? setado? (Bit 16)
	BEQ SysTick_Wait_loop               ; Se sim permanece no loop
	BX LR                               ; Se n?o, retorna

;------------SysTick_Wait1ms------------
; tempo de atraso usando processador ocupado. Assume um clock de 80 MHz
; Entrada: R0 --> N?mero de vezes para contar 1ms.
; Sa?da: N?o tem
; Modifica: R0

systickISR
	PUSH {R4, LR} 						; salva o valor atual de R4 e Link Register
	MOVS R4, R0 						; R4 = R0  numEsperasRestantes com atualiza??o dos flags
	BEQ SysTick_Wait1ms_done 			; Se o numEsperasRestantes == 0, vai para o fim
SysTick_Wait1ms_loop					
	LDR R0, =DELAY1MS 					; R0 = DELAY1MS (n?mero de ticks para contar 1ms)
	BL SysTick_Wait 					; chama a rotina para esperar por 1ms
	SUBS R4, R4, #1 					; R4 = R4 - 1; numEsperasRestantes--
	BHI SysTick_Wait1ms_loop 			; se (numEsperasRestantes > 0), espera mais 1ms
SysTick_Wait1ms_done
	POP {R4, PC}                        ;return
  END