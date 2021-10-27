# Sistemas Embarcados
- Código: CSW41
- Créditos: 4
- Professor: Douglas Paulo Bertrand Renaux
- Email: douglasrenaux@professores.utfpr.edu.br
- Aluno: Gabriel Alexandre Linhares Calper Seabra
- Email: gabrielseabra@alunos.utfpr.edu.br



## Introdução
Esse laboratório tem como objetivo elaborar uma rotina em assembly que será chamado em um programa C++ . Essa rotina será capaz de gerar um histograma de uma imagem em tons de cinza, para isso será necessário consultar o AAPPCS que

## Lab3
Dado que os dois últimos laboratórios já foram bem introdutório no que tange o assunto de configuração ambiente, este laboratório a parte de configuração do ambiente será negligenciada para melhor aproveitamento de conteúdo. Geralmente quando se tem problemas a serem resolvidos, tendemos a quebrar o problema em pequenos pedaços, isso facilita a chegarmos em uma solução relativamente boa, para este laboratório o primeiro passo, apesar de extremamente básico, foi criar uma rotina que seja possível ser chamada para em uma função, abaixo a estrutura do diretório do projeto, o arquivo histogram.s e main.cpp respectivamente.

```shell
  $ Lab3
  .
  ├── main.cpp          **arquivo que possui função main**
  └── histogram.s              ** Implementação da função EightBitHistogram**
```


```armassembly
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

Note que até o momento ainda não fizemos nenhuma implementação, esta etapa é apenas uma etapa para a ambientação de escrever códigos em assembly e chamá-los em C.
## Referências

1. IAR Assembler User Guide - https://wwwfiles.iar.com/arm/webic/doc/EWARM_AssemblerReference.ENU.pdf

2. ARM Procedure Call Standard for the ARM Architecture https://developer.arm.com/documentation/ihi0042/latest