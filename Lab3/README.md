# Sistemas Embarcados
- Código: CSW41
- Créditos: 4
- Professor: Douglas Paulo Bertrand Renaux
- Email: douglasrenaux@professores.utfpr.edu.br
- Aluno: Gabriel Alexandre Linhares Calper Seabra
- Email: gabrielseabra@alunos.utfpr.edu.brd


# Lab3
#### Introduçãos
Esse laboratório tem como objetivo elaborar uma rotina em assembly que será chamado em um programa C++ . Essa rotina será capaz de gerar um histograma de uma imagem em tons de cinza, para isso será necessário consultar o AAPPCS que

# O histograma
Dado que nos dois últimos laboratórios já foram bem introdutórios no que tange o assunto de configuração de ambiente, portanto essa parte será negligenciada neste lab, para melhor aproveitamento de conteúdo. Geralmente quando se tem problemas a serem resolvidos, tendemos a quebrar o problema em pequenos pedaços, isso facilita na solução do problema além de simplificar as etapas de desemvolvimento, para este laboratório o primeiro passo, apesar de extremamente básico, foi criar uma rotina que seja possível ser chamada em código C, abaixo a estrutura do diretório do projeto, o arquivo histogram.s e main.cpp respectivamente.

```shell
  $ Lab3
  .
  ├── main.cpp          **arquivo que possui função main**
  └── histogram.s              ** Implementação da função EightBitHistogram**
```


```asm
  PUBLIC EightBitHistogram                        ;Torna a função acessível fora de histogram.s

  SECTION .text : CODE(4)                         ;Define uma sessão e alinhamento
  THUMB                                           ;Instruções do tipo thumb


EightBitHistogram:
  PUSH {R4-R12, LR}                               ;Salvar os R4 até R12 na piha e também salvar o Link Register
  MOV R0,#1                                       ;Apenas um teste simples
  POP {R4-R12, PC}                                ;Desempilhando tudo
  END                                             ;Fim do programa assembly
```

```cpp
#include <stdio.h>
#include <stdint.h>
extern void EightBitHistogram();                    //Falando para o compilador que essa função foi definida externamente   
int main()
{
  EightBitHistogram(4);
  printf("Hello World"); 
  return 0;
}
```

Note que até o momento ainda não fizemos nenhuma implementação, nesta etapa, é apenas uma etapa para a ambientação de escrever códigos em assembly e chamá-los em C/C++.
Seguindo ARM Architecture Procedure Call Standard, para verificar como a matriz se organiza na memória foi feito uma pequena verificação na IDE da IAR, opção TI Stellaris>Memory Configuration podemos ver a janela abaixo como a memória é organizada, isso não é tão importante quando se conhece o comportamento da linguagem C, mas apenas para confirmar que a palavra const coloca as variáveis disponíveis na região de memória flash, como pode ser visto na imagem abaixo.


<figure>
  <img src="https://user-images.githubusercontent.com/48101913/139188743-fe278cb3-19d3-4783-828b-4b486b9edc40.png">
</figure>

<figure>
  <img src="https://user-images.githubusercontent.com/48101913/139188973-c3207b85-2252-4925-8183-d97d695135ea.png">
</figure>

Dada essa pequena introdução sobre armazenamento de variáveis iremos discorrer sobre o histograma ao passo que caminharemos com o algoritmo, como a imagem possui 8 bits de tom de cinza isso significa que teremos 255 níveis de cinza disponíveis em cada píxel, uma ilustração disso pode ser vista na imagem abaixo, e logo em seguida uma matriz 3x4 em linguagem C representando uma matriz de pixels.

<figure>
  <img src="https://user-images.githubusercontent.com/48101913/139511958-a42ab4d0-fc40-45f4-82b6-2ea9a5802bb7.png">
</figure>

<figure>
  <img src="https://user-images.githubusercontent.com/48101913/139512195-4d86a328-5a2f-4765-93bb-930a1b520ece.png">
</figure>

A função que chama o gerador de histograma está sendo explicada no quadro abaixo.

```cpp

/**
 * @brief 
 * 
 * @param[in] width Dimensão de colunas da matriz
 * @param[in] height Dimensão de linhas da matriz
 * @param[in] p_image endereço da matriz
 * @param[out] p_histogram endereço onde será armazenado o histogramas
 * @return uint16_t retorna zero se o histograma não é suportado pela função ou endereço caso seja suportado
 */
extern uint16_t *EightBitHistogram(uint16_t width, uint16_t height, const uint8_t * p_image, uint16_t * p_histogram);
```

Para melhor entendimento o programa assembly foi dividido em pequenos pedaços de códigos que fazem algo muito específico , abaixo uma descrição de cada label e sua respectiva função, este processo é necessário pois um código assembly é muito dificil de ser lido e para evitar desgaste no entendimento da implementação em assembly, explicarei em uma linguagem de maior nível o que cada label faz.


```asm

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
  ADD R6,R6,#1                   ; R4 = R4 + 2
  STRH R6,[R3]
  MOV R6,#0                      ; Zera o valor de R6
  BX LR
 

MemInit                         ; Funcao para dar init na memoria
  ADD R3, R3,#2
  STRH  R11,[R3]                ; Zera area de memoria
  ADD R8,#1                     ;´Iterador de memoria
  CMP R8,#512                   
  BNE MemInit
  MOV R3,R4                     ; R3 recebe o endereco da variavel
  BX LR

  END
```
#### EightBitHistogram         
Esta é a função propriamente dita, ela é responsavel por salvar o contexto e verificar se o número de elementos é maior que o que 65k, caso o número de elementos exceda o limite permitido, ela pede para o programa desviar para o label ** Return **  que coloca 0 no Registrador R0 (indicação de erro) e restaura o contexto. Caso a função esteja dentro do limite permmitido de elementos, ela pede para a função desviar para MemInit, que será explicada logo em seguida.






# Referências

1. IAR Assembler User Guide - https://wwwfiles.iar.com/arm/webic/doc/EWARM_AssemblerReference.ENU.pdf

2. ARM Procedure Call Standard for the ARM Architecture https://developer.arm.com/documentation/ihi0042/latest
