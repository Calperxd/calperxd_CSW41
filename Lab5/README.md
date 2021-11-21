# Sistemas Embarcados
- Código: CSW41
- Créditos: 4
- Professor: Douglas Paulo Bertrand Renaux
- Email: douglasrenaux@professores.utfpr.edu.br
- Aluno: Gabriel Alexandre Linhares Calper Seabra
- Email: gabrielseabra@alunos.utfpr.edu.br


# Lab5

#### Introdução
Portar para a Tiva o projeto exemplo do ThreadX.
# Ambiente

Neste laboratório a configuração do ambiente mudou, isso implica que teremos que configurar novamente o ambiente de desenvolvimento para a nova plataforma de RTOS(ThreadX), Antes estávemos desenvolvendo em Bare Metal, o novo diretório deve parecer como mostra o Shell abaixo.
```shell
  $ tree
  .
  ├── lib
  │   └── blackjack.ex
  ├── mix.exs
  ├── README.md
  └── test
      ├── blackjack_test.exs
      └── test_helper.exs
```

#### Funcionamento da UART.

![image](https://user-images.githubusercontent.com/48101913/140612031-1fe59a79-c0bf-4f1b-ab38-4079b29e7c64.png)

Quando parado ou idle o pino está em estado lógico alto.

Cada transmissão de dados começa com 1 bit de start que é sempre estado lógico baixo.

Cada pacote de dados tem 8 ou 9 bits de tamanho, onde o LSB é sempre o primeiro a ser transferido.

![Shift_Register](https://user-images.githubusercontent.com/48101913/140596381-d1d67cd7-bb42-461d-b5f0-0421640c0b89.gif)

Cada transmissão de dados termina com um STOP bit que tem sempre estado lógico alto.

Quando não há dados a serem transmitidos, a linha fica em nível lógico alto.

O receptor reconhece a borda de descida do start bit e sincroniza seu clock.

Após 1 ciclo e meio começa a fazer a leitura dos demais bits a cada clock.

Se as frequências do transmissor e do receptor estiverevem perfeitamente sincronizadas, as leituras serão efetuadas exatamente no meio de cada ciclo.

# O Projeto.

O projeto consite em converter letras maiúsculas e mínúsculas, tanto de maiúscula para minúscula quanto o contrário, para esse projeto usaremos a UART0, e existe uma razão especial para usar ela, ela é mapeada com a interface USB conforme pode ser visto na página 22 do **Tiva C Series TM4C1294 Connected LaunchPad Evaluation Kit (Rev. C).**

Para converter uma letra maiúscula para minúscula podemos usar a tabela ASCII para ver o como estão dispostas as letras e quais suas representações em números decimais. Tomemos a letra "A" como exemplo, a letra "A" é representado pelo decimal 65 e o seu equivalente minúsculo é 97, a diferença entre as duas é 32, quando a UART receber uma letra maiúscula basta somar 32 e essa letra será convertida para minúscula e quando a UART receber uma letra maiúscula bas diminuir 32.



![image](https://user-images.githubusercontent.com/48101913/141230179-ca969428-6314-4525-9356-663152b9f1a4.png)

O algorítmo consiste em nos seguintes passos.

```table
1º Checar se é maiúscula ou minúscula.
2º Somar se maiúscula senão.
3º Subtrair se for minúscula.
```
Para receber os dados da UART uma interrupção de UART será usada, toda vez que houver algum caracter sendo recebido pela UART haverá uma interrupção, para registrar uma interrupção no vetor de interrupção, basta você ir no startup_ewarm.c e mudar o nome da função referente a interrução da UART, note também que existem outra funções que podem ser alteradas, bem como o **__iar_program_start(void)**. A função desse arquivo startup_ewarm.c é bem sugestiva, ele é responsável por declarar algumas funções que serão explicadas logo abaixo.
O arquivo começa declarando funções que serão usadas, a primeira dela é a **void ResetISR(void)**, essa função é responsável pelo bootloader do sistema , e basicamente faz duas coisas habilita a unidade de ponto flutuante e chama o **__iar_program_start(void)** que é de fato a função de bootloader proprietária da IAR, eu particularmente não encontrei a definição da função, mas ela basicamente carrega o programa na memória RAM e ao final chama a famigerada função **main(void)** da linguagem C. Outra função interessante para esse momento é a função **IntDefaultHandler(void)** , essa função basicamente já descreve o que ela faz, ela é um handler default. mas como assim ? Ok, posso explicar mas vamos por partes.

![image](https://user-images.githubusercontent.com/48101913/141415103-3b18b0a1-c96b-4f23-9ab4-d1e85749a886.png)

No arquivo **startup_ewarm.c** , existe um vetor do tipo uint32_t sendo criado(imagem abaixo) , esse vetor é stack do sistema.
![image](https://user-images.githubusercontent.com/48101913/141418424-544c5603-6ae4-459c-a667-3b5207530b89.png)

Logo em seguida um tipo de dado é definido, é um union(ou collection do java) significa que aceita os tipos de dados definido na estrutura.
![image](https://user-images.githubusercontent.com/48101913/141418745-3df07974-f6ca-4101-ba4f-284a09923136.png)

Com o tipo de dado criado um vetor de interrupções é criado, , o que esse trecho de código está fazendo é pegar o endereço da stack do sistema e somando o endereço do vetor de interrupções, note que a palavra const é usada, para que esse vetor seja fixado na memória flash e que depois no bootloader seja possível copiar vetor da memória flash para memória RAM, observe que as três primeiras interrupções registradas são ResetISR, NmiISR e FaultISR, como explicado são as interrupções, o código da FaultISR e NmiISR são simples, apenas executam um loop infinito, evitando que o sistema execute qualquer coisa errada, evidemente essas funções podem ser alteras logo abaixo. Note que a palavra IntDefaultHandler se repete várias vezes e isso acontece pois quando uma interrupção é habilitada, e não possui o nome trocado no seu vetor de interrupções ele chama essa função como default.

![image](https://user-images.githubusercontent.com/48101913/141420307-8d73a187-4046-4a3d-8342-224e310cb10e.png)

Todas as linhas estão comentadas com o respectivo periférico, caso não estivesse comentada, você também poderia consultar a ordem no datasheet do chip **TM4C1294NCPDT** , para alterar a função que representa o handler basta ir na posição do vetor de interrupções e alterar, no meu caso eu irei alterar para MinhaUARTHandle. Essa palavra reservada garante que podemos alterar o funcionamento da função do handler da UART.

![image](https://user-images.githubusercontent.com/48101913/141489623-1f6d41c7-7462-4334-9901-aca392194980.png)
![image](https://user-images.githubusercontent.com/48101913/141489689-6cf103f3-5dfd-48f7-be0f-dc71e2936677.png)

O cerne do algorítmo está no trecho de código abaixo, o resto é apenas configuração de periférico, observe que na pasta do projeto está tudo bem modular, para que o código seja de facil entendimento
```cpp
void MinhaUARTHandler(void)
{
    uint32_t Status;
    volatile int32_t caract;

    Status = UARTIntStatus(UART0_BASE, true);                   // Retorna o status da interrupção    
    UARTIntClear(UART0_BASE, Status);                           // Limpa Flag de interrupção
    
    //Verifica se tem algum dado na fifo
    while(UARTCharsAvail(UART0_BASE))
    {
        // Algoritmo de conversao
        caract = UARTCharGetNonBlocking(UART0_BASE);
        //maiúsculo para minúsculo
        if((caract > 64) && (caract < 91))
        {
          caract = caract + 32;
        }else{
          //minúsculo para maiúsculo
          if((caract > 96) && (caract < 123))
          {
            caract = caract - 32;
          }  
        }
        UARTCharPutNonBlocking(UART0_BASE, caract); // Escreve na UART
        // Feedback visual de que um dado foi recebido na uart
        GPIOPinWrite(GPIO_PORTN_BASE, GPIO_PIN_0, GPIO_PIN_0); 
        SysCtlDelay(SysClock / (1000 * 3));
        GPIOPinWrite(GPIO_PORTN_BASE, GPIO_PIN_0, 0);
    }
    //zera a variável
    caract = 0;
}
```

# Conclusão

Evidentemente poderíamos ter usado a biblioteca ctype.h e fazer uso das funções tolower() e toupper() para converter para maiúsculo e minúsculo, entretanto como estamos trabalhando em um sistema com recursos limitados, chamar bibliotecas assim podem acarretar problemas, como uso excessivo de recursos, quando na verdade o algoritmo é algo relativamente fácil de ser implementado, claro que esse algoritmo ainda pode melhorar, no quesito eficiência, mas já é melhor que instanciar uma biblioteca completa para isso. 
# Referências

1. Blog sobre funcionamento UART - https://deepbluembedded.com/uart-pic-microcontroller-tutorial/

