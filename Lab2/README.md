
# Sistemas Embarcados
- Código: CSW41
- Créditos: 4
- Professor: Douglas Paulo Bertrand Renaux
- Email: douglasrenaux@professores.utfpr.edu.br
- Aluno: Gabriel Alexandre Linhares Calper Seabra
- Email: gabrielseabra@alunos.utfpr.edu.br


# Lab2

#### Introdução
<p>Este laboratório consiste em criar um jogo de reação que use interrupções e interaja com os I/O da  **_EK-TM4C1294XL_** de forma a marcar o tempo de interação do usuário e mostrar esse tempo na tela da do terminal do **_IDE IAR Embedded Workbench for ARM_**.</p>

# Ambiente de desenvolvimento
Como um dos requisitos é aprender um pouco mais sobre a IDE essa parte do tutorial dedica-se aos passos necessários para configuração do ambiente de desenvolvimento.

1 - Como um primeiro requisito para tornar o projeto mais organizado, iremos criar um _workspace_  como mostra a figura.
<figure>
  <img src="https://user-images.githubusercontent.com/48101913/138390281-56377616-eb08-4215-92cb-705bc1055609.png">
</figure>

2 - O segundo passo foi criar um projeto que seja debugável para isso devemos selecionar a opção _Externally build executable_ eu não se explicar exatamente o que acontece mas IDE só permite debuggar quando uma essa opção é marcada.

<figure>
  <img src="https://user-images.githubusercontent.com/48101913/138391144-7e85ab87-8d09-4867-8610-776bdfdcc94c.png">
</figure>

3 - Quando escolhemos criar um projeto devemos escolher onde será a sua pasta no meu caso escolhi calperxd_CSW41/Lab2, que é a pasta do lab 2.

<figure>
  <img src="https://user-images.githubusercontent.com/48101913/138391485-5c7a8ff7-e361-473c-9c2a-9c56a426c040.png">
</figure>

4 - Veja que uma vez criado, a pasta agora o lab2 aparece no _workspace_, esse laboratório requer que seja adicionados os projetos blinky, driverlib, e Lab1 e para isso basta ir em Project>Add Existing Project e selecionar os respectivos projetos, Lembre-se que o caminho do projeto driverlib é importante, pois a driverlib é onde todos os períférico da ARM são mapeados e definidos pela TI além de também mostrar as impletações dos códigos, ao final seu diretório deve parecer com o que está sendo mostrado na figura abaixo.

<figure>
  <img src="https://user-images.githubusercontent.com/48101913/138392913-07eaf6b0-98aa-4ee8-b4c1-ee4bf6c70fbf.png">
</figure>

5 - Agora basta importar o zip disponibilizado pelo professor para dentro do projeto Lab2.

#### Configuração da TivaWare

6 - Uma vez o importados os arquivo disponibilizados pelo professor, é hora de fazer o build.

<figure>
  <img src="https://user-images.githubusercontent.com/48101913/138398097-6fb87bca-b3c6-4e50-9ce4-80494c71c724.png">
</figure>

7 - Conforme pode ser visto, um erro é gerado, esse erro era esperado pois ainda não fizemos nenhuma configuração de mapeamento de diretivas e de bibliotecas, muito menos setamos qual microcontrolador estamos usando. O primeiro passo é configurar o microcontrolador que estamos usando, para isso clique com o botão direito do mouse em cima de Lab2 options>General Options seleciona a caixinha device e coloque o seu respectivo microcontrolador, no meu caso é o TM4C1294NCPDT da TI.

<figure>
  <img src="https://user-images.githubusercontent.com/48101913/138398612-afd7e4c9-98fb-4d17-8c1f-c7e59534e87a.png">
</figure>

8 - Agora mapei a diretivas de pré-processador que a maioria está definida na pasta da TivaWare e aperte OK(Não esqueça de mapear de forma relativa pois assim será fácil para outra pessoa reproduzir seu código conforme a figura abaixo).

<figure>
  <img src="https://user-images.githubusercontent.com/48101913/138399097-265871cf-bfe6-496b-aa16-12c8519dec4b.png">
</figure>

9 - Agora o mais importante a driverlib, que é a biblioteca responsável por implementar um driver de acesso a todas os periféricos do processador, ela é de código aberto, portanto você pode ver a implementação indo na pata da TivaWare e indo em driverlib lá estarão listados todas as implementações e suas interfaces(pode-se compilar a driverlib novamente usando o Makefile disponível na pasta, mas texas já deixa disponível uma biblioteca estática como pode ser visto na imagem).

<figure>
  <img src="https://user-images.githubusercontent.com/48101913/138399662-783b8ad0-9562-415b-920f-149cbad91caa.png">
</figure>

10 - Se você estiver com a ferramenta arm-none-eabi instalada no seu computador você pode ver o que tem compilado dentro da biblioteca estática usando a ferramenta arm-none-eabi-nm, veja que tudo há dentro da .a são todos os arquivos objetos linkados, que ficam disponíveis na pasta ewarm>Obj>Source.

<figure>
  <img src="https://user-images.githubusercontent.com/48101913/138400297-2659ce97-fe82-4d02-9786-656095c59eed.png">
</figure>

se você der um **_arm-none-eabi-nm driverlib.a_** irá ver todos os arquivos objetos compilados, disponíveis na driverlib.

<figure>
  <img src="https://user-images.githubusercontent.com/48101913/138400561-5fe9748d-5432-4014-8ace-fb25ba622b0a.png">
</figure>

11 - Agora vá em Debugger selecione TI Stellaris e caso queira ver o BootLoader você precisa desmarcar a opção _Run to main_

<figure>
  <img src="https://user-images.githubusercontent.com/48101913/138400845-9a57d4a1-4d39-42df-bd61-de331ec634f1.png">
</figure>


agora você já pode buildar a aplicação, haverá um erro pois existem definições duplicadas, existe um arquivo de inicialização escrito em ASSEMBLY da ARM o _startup_TM4C1294.s_, para que seja possível buildar sem erro basta escolher um dos dois e excluir o outro, eu escolhi escluir o feito em assembly pois o escrito em C é melhor de entender no alto nível.

```shell
  $ Lab2
  .
  ├── blinky.c          **arquivo que possui função main**
  ├── cmsis_compiler.h  **arquivo da ARM para compilação**
  ├── cmsis_version.h   **arquivo de versionamento da cmsis**
  ├── cmsis_iccam.h     **arquivo compilador IAR para ARM**
  ├── core_cm4.h        **arquivo core do processador CortexM4**
  ├── startup_ewarm.c   **é um bootloader define o vetor de interrupções além de também chamar a função main, NMI etc.**
  ├── system_TM4C1294.C  **implmenta algumas funções mas a mais importante é a SystemInit()**
  ├── system_TM4C1294.h  **cabeçalho da system_TM4C1294.**
  ├── TM4C1294NCPDT.h     ** Possui todos os endereços do processador além de mascarás usadas pela TivaWare**
  └── Output              ** Arquivos de saída**
```



# O projeto

Para esse projeto eu redefini a função main para que ela se torne mais limpa, agora a estrutura de diretório possui um arquivo main.c que será nosso ponto de partida.  

```shell
  $ Lab2
  .
  ├── main.c          **arquivo que possui função main**
  ├── blinky.c          **arquivo secundário usado como base para o jogo**
  ├── cmsis_compiler.h  **arquivo da ARM para compilação**
  ├── cmsis_version.h   **arquivo de versionamento da cmsis**
  ├── cmsis_iccam.h     **arquivo compilador IAR para ARM**
  ├── core_cm4.h        **arquivo core do processador CortexM4**
  ├── startup_ewarm.c   **é um bootloader define o vetor de interrupções além de também chamar a função main, NMI etc.**
  ├── system_TM4C1294.C  **implmenta algumas funções mas a mais importante é a SystemInit()**
  ├── system_TM4C1294.h  **cabeçalho da system_TM4C1294.**
  ├── TM4C1294NCPDT.h     ** Possui todos os endereços do processador além de mascarás usadas pela TivaWare**
  └── Output              ** Arquivos de saída**
```

Para este lab o tempo é uma variável que precisa ser muito bem conhecida, por isso é necessário inicializar o sistema com um clock conhecido e para isso usaremos a função SysCtlClockFreqSet(), essa função é necessária para configurar o clock do sistema a imagem abaixo mostra os parâmetros necessários do System Divisor para deixar o clock em 120MHz.

<figure>
  <img src="https://user-images.githubusercontent.com/48101913/138494091-c146baea-3832-4ddc-9797-0cdfdebf72dc.png">
</figure>


Para deixar um pouco mais legível podemos usar os defines que estão na biblioteca _Sysctl.h_ da TivaWare, tornando a função com os seguintes parâmetros _ui32SysClock = SysCtlClockFreqSet((SYSCTL_XTAL_25MHZ |SYSCTL_OSC_MAIN | SYSCTL_USE_PLL |SYSCTL_CFG_VCO_240), 120000000)_. A função basicamente indica para usar o Cristal de 25MHz, Usar a entrada principal , Usar o PLL, e setar o VCO para dividir por 4.

A biblioteca TivaWare possui um documentação das funções disponível e seus respectivos exemplos na pasta TivaWare>docs>SW-TM4C-DRL-UG-2.2.0.295.pdf.
#### Systick

Basicamente abrindo o _SW-TM4C-DRL-UG-2.2.0.295.pdf_ podemos ver conforme a figura abaixo as funções da biblioteca systick, o documento também explica como usá-las e também dá alguns exemplos.

<figure>
  <img src="https://user-images.githubusercontent.com/48101913/138505665-e35e6a3f-744f-49b1-b428-78989ed3f383.png">
</figure>

Basicamente o algorítmo para fazer o led piscar em 3 segundos é o mostrado na figura

```table
  1├── Setup do Periférico Systick
    2├──  Carregar o valor no Systick
      3├── Registrar função de interrupção
        4├── Habilitar interrupção do Systick
          5├── Habilitar Systick
            6├── Habilitar clock no perifério GPIO
              7├── Esperar ele ficar pronto para uso
                8├── Setar portas como saída
                  9├──  Liga port_n0 em 1,5 segundo
                    10├── Desliga port_n0 em 1,5 segundo
                      11└── Repetir liga e desliga indefinidamente
```

O código implementado pode ser visto abaixo

```cpp
#include <stdint.h>
#include <stdbool.h>
#include "driverlib/systick.h"
#include "inc/hw_memmap.h"
#include "driverlib/debug.h"
#include "driverlib/gpio.h"
#include "driverlib/sysctl.h"

int flag = 0;

void SysTickIntHandler(void)
{
  flag++;
}

int SetupSystick()
{
  SysTickDisable();
  // The clock is 120MHz, so basically the variable will count every 8.33ns
  // Configure the SysTick counter.
  // Every 10 flag makes 1 second
  SysTickPeriodSet(12000000);
  // Pointer tu a function
  SysTickIntRegister(SysTickIntHandler);
  // Enable the SysTick counter.
  SysTickIntEnable();
  SysTickEnable();
  return 0;
}

int main(void)
{
  SetupSystick();
  volatile uint32_t ui32Loop;
  SysCtlClockFreqSet((SYSCTL_XTAL_25MHZ |
                                       SYSCTL_OSC_MAIN |
                                       SYSCTL_USE_PLL |
                                       SYSCTL_CFG_VCO_240), 120000000);
    // Enable the GPIO port that is used for the on-board LED.
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPION);
    // Check if the peripheral access is enabled.
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPION))
    {
    }
    // Enable the GPIO pin for the LED (PN0).  Set the direction as output, and
    // enable the GPIO pin for digital function.
    GPIOPinTypeGPIOOutput(GPIO_PORTN_BASE, GPIO_PIN_0);
    // Loop forever.
    while(1)
    {
      if(flag == 15)
      {
        // Turn on the LED.
        GPIOPinWrite(GPIO_PORTN_BASE, GPIO_PIN_0, GPIO_PIN_0);
        // Turn off the LED.
      }
      if(flag == 30)
      {
        GPIOPinWrite(GPIO_PORTN_BASE, GPIO_PIN_0, 0x0);
        flag = 0;
      }
    }
}
```
#### O jogo

Para que esse jogo seja possível é necessário criar uma rotina de Setup dos periféricos a serem usados durante o jogo, aqui abaixo iremos listar o que foi utilizado.

> ##### Periféricos Usados
> 
> - Systick
> - GPIO

##### Systick
A função abaixo mostra como foi inicializado o Systick
```cpp
int SetupSystick()
{
  SysTickDisable();
  // The clock is 120MHz, so basically the variable will coun every 8.33ns
  // Configure the SysTick counter.
  // Every 10 flag makes 1 second
  SysTickPeriodSet(12000000);
  // Pointer tu a function
  SysTickIntRegister(SysTickIntHandler);
  // Enable the SysTick counter.
  SysTickIntEnable();
  SysTickEnable();
  return 0;
}
```

##### GPIO
A função abaixo mostra como foi inicializado o GPIO
```cpp
int SetupGPIO(void)
{
  //----------------------------------------------------------------------------------------------
  //port J
  // Enable clock on port J
  SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOJ);
  // Wait until the port is ready to use
  while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOJ))
  {
  }
  // Disable the interrupt of pin 0
  GPIOIntDisable(GPIO_PORTJ_AHB_BASE,GPIO_PIN_0);
  // Register a function to call
  GPIOIntRegister(GPIO_PORTJ_AHB_BASE, GpioPortJIntHandler);
  //Configure as:
  // PortJ
  // Pin 0
  // Strength 2 mA
  // Weak pull-up enabled
  GPIOPadConfigSet(GPIO_PORTJ_AHB_BASE,GPIO_PIN_0,GPIO_STRENGTH_2MA,GPIO_PIN_TYPE_STD_WPU);
  //Define the pin as input
  GPIOPinTypeGPIOInput(GPIO_PORTJ_BASE, GPIO_PIN_1);
  // Make pin 0 rising edge triggered interrupts.
  GPIOIntTypeSet(GPIO_PORTJ_AHB_BASE, GPIO_PIN_0, GPIO_LOW_LEVEL);
  // Enable the pin interrupts.
  GPIOIntEnable(GPIO_PORTJ_BASE, GPIO_PIN_0);
  //----------------------------------------------------------------------------------------------
  // Port N  
  // Enable clock on port N
  SysCtlPeripheralEnable(SYSCTL_PERIPH_GPION);
  // Wait until the port is ready to use
  while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPION))
  {
  }
  //Configure port as output
  GPIOPinTypeGPIOOutput(GPIO_PORTN_BASE, GPIO_PIN_0);
  //Start turned off
  GPIOPinWrite(GPIO_PORTN_BASE, GPIO_PIN_0, 0);
  
  //----------------------------------------------------------------------------------------------
  // Port F  
  // Enable clock on port N
  SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
  // Wait until the port is ready to use
  while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOF))
  {
  }
  //Configure port as output
  GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_0);
  //Start turned off
  GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_0, 1);
  return 0;
}
```

O código para o jogo é o fornecido no arquivo main.cpp e também pode ser visto abaixo além de também apresentar seu respectivo vídeo de funcionamento.
```cpp
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include "inc/hw_memmap.h"
#include "driverlib/debug.h"
#include "driverlib/gpio.h"
#include "driverlib/sysctl.h"
#include "driverlib/systick.h"



//flag that count until 30 represents 3 seconds
int flag = 0;
int flag2 = 0;
int flag3 = 1;
int ms = 0; // milissecond

void SysTickIntHandler(void)
{
  printf("%i second\n",ms);
  ms = ms + 100;
  flag++;
}

void GpioPortJIntHandler(void)
{ 
  flag2 = 1;
}

int SetupFreq(void)
{
  SysCtlClockFreqSet((SYSCTL_XTAL_25MHZ | SYSCTL_OSC_MAIN | SYSCTL_USE_PLL | SYSCTL_CFG_VCO_240), 120000000);
  return 0;
}

int SetupSystick()
{
  SysTickDisable();
  // The clock is 120MHz, so basically the variable will count every 8.33ns
  // Configure the SysTick counter.
  // Every 10 flag makes 1 second
  SysTickPeriodSet(12000000);
  // Pointer tu a function
  SysTickIntRegister(SysTickIntHandler);
  // Enable the SysTick counter.
  SysTickIntEnable();
  SysTickEnable();
  return 0;
}

int SetupGPIO(void)
{
  //----------------------------------------------------------------------------------------------
  //port J
  // Enable clock on port J
  SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOJ);
  // Wait until the port is ready to use
  while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOJ))
  {
  }
  // Disable the interrupt of pin 0
  GPIOIntDisable(GPIO_PORTJ_AHB_BASE,GPIO_PIN_0);
  // Register a function to call
  GPIOIntRegister(GPIO_PORTJ_AHB_BASE, GpioPortJIntHandler);
  //Configure as:
  // PortJ
  // Pin 0
  // Strength 2 mA
  // Weak pull-up enabled
  GPIOPadConfigSet(GPIO_PORTJ_AHB_BASE,GPIO_PIN_0,GPIO_STRENGTH_2MA,GPIO_PIN_TYPE_STD_WPU);
  //Define the pin as input
  GPIOPinTypeGPIOInput(GPIO_PORTJ_BASE, GPIO_PIN_1);
  // Make pin 0 rising edge triggered interrupts.
  GPIOIntTypeSet(GPIO_PORTJ_AHB_BASE, GPIO_PIN_0, GPIO_LOW_LEVEL);
  // Enable the pin interrupts.
  GPIOIntEnable(GPIO_PORTJ_BASE, GPIO_PIN_0);
  //----------------------------------------------------------------------------------------------
  // Port N  
  // Enable clock on port N
  SysCtlPeripheralEnable(SYSCTL_PERIPH_GPION);
  // Wait until the port is ready to use
  while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPION))
  {
  }
  //Configure port as output
  GPIOPinTypeGPIOOutput(GPIO_PORTN_BASE, GPIO_PIN_0);
  //Start turned off
  GPIOPinWrite(GPIO_PORTN_BASE, GPIO_PIN_0, 0);
  
  //----------------------------------------------------------------------------------------------
  // Port F  
  // Enable clock on port N
  SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
  // Wait until the port is ready to use
  while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOF))
  {
  }
  //Configure port as output
  GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_0);
  //Start turned off
  GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_0, 0);
  return 0;
}

int main(void)
{
  SetupFreq();
  SetupSystick();
  SetupGPIO();
  while(1)
  {
    //Inicio do jogo
    if((flag == 1)&&(flag3))
    {
      GPIOPinWrite(GPIO_PORTN_BASE, GPIO_PIN_0, 1);
      printf("Iniciou o jogo\n");
      flag = 0;
      flag3 = 0;
    }
    if(ms == 3000)
    {
      printf("Jogo finalizado\n");
      flag3 = 1;
      flag = 0;
      ms = 0;
    }
    if (flag2 == 1)
    {
      SysTickDisable();
      GPIOIntDisable(GPIO_PORTJ_AHB_BASE,GPIO_PIN_0);
      GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_0, 1);
      printf("Você ganhou\n");
      flag2 = 0;
    }
    
  }
}


```

![WhatsApp-Video-2021-10-23-at-04 00 08](https://user-images.githubusercontent.com/48101913/138548274-022c73a3-c172-48c8-946b-7636acfd1e4d.gif)


#### Volatile 

A palavra reservada volatile tem haver com a otimização do compilador, basicamente quando usamos essa palavra em uma variável indicamos ao processador que aquela variável não deve passar pelo processo de otimização do compilador, isso implica que ela será armazenada na memória RAM e terá um endereço, quando ela é declarada em escopo local processador empilha o contexto atual, usando a palavra volatile, essa variável passa a estar disponível na memória RAM podendo ser mudada a qualquer instante.





#Conclusão


Este laboratório foi importante para o entedimento da Biblioteca TivaWare e seus periféricos disponíveis, além de adicionar conhecimentos referente ao periférico systick que é comumente usado como base de tempo em sistemas operacionais de tempo real, a biblioteca Tivaware torna o processo de usar os periféricos do TM4C1294NCPDT muito fáceis de configurar sem precisar ficar escrevendo em endereços diretamente nos registrados para fazer o setup correto do periférico.