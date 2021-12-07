# Sistemas Embarcados
- Código: CSW41
- Créditos: 4
- Professor: Douglas Paulo Bertrand Renaux
- Email: douglasrenaux@professores.utfpr.edu.br
- Aluno: Gabriel Alexandre Linhares Calper Seabra
- Email: gabrielseabra@alunos.utfpr.edu.br


# Lab6

### Introdução
Criar um conjunto de 3 tarefas com temporizaçõe conhecidas. Experimentando variaçõe de algoritmos de escalonamento disponível no ThreadX.

### O Projeto
Basicamente o algoritmo para medir o tempo de execução está descrito logo abaixo.

```cpp

// Algoritmo de tempo de execução
/* Pickup the current system time, in timer-ticks. */
ULONG time_before;
ULONG time_after;
ULONG time_lapsed ;

time_before = tx_time_get();

/***** execution code *****/

time_after = tx_time_get();
time_lapsed = time_after - time_before;

```

Ele é bem simples pois o ThreadX portado já faz uma interface com o systick da ARM. Outro ponto interessante do projeto ThreadX é que ele faz várias interfaces para o desenvolvedor, uma interface extremamente interessante é a possibilidade de usar comandos da biblioteca pthreads.h, o ThreadX tem várias funções implementadas o trecho de código abaixo mostra a função sleep() do linux, como ela é implementada no ThreadX(todas as funções do padrão posix podem ser acessadas no diretório utility/rtos_compatibility_layers/posix/posix_sleep.c).

```cpp
UINT sleep(ULONG seconds)
{

UINT temp1, temp2, diff, result;

    temp1 = tx_time_get();
    tx_thread_sleep(seconds * CPU_TICKS_PER_SECOND);
    temp2 = tx_time_get();
    diff = temp2 - temp1;

    if (diff > (seconds * CPU_TICKS_PER_SECOND))
    {
        result = (diff - (seconds * CPU_TICKS_PER_SECOND));
    }
    else
    {
        result = ((seconds * CPU_TICKS_PER_SECOND) - diff);
    }

    return (result/CPU_TICKS_PER_SECOND);    
    
}


```

Note que apesar de ser um código extremamente simples, é interessante entender a sutileza de diferença entre um RTOS e um OS comum, que quando chamamos a função sleep e passamos qualquer tempo como parâmetro ela dorme pelo tempo e retorna o tempo decorrido, entretando, observe que ela possui dois if's esses if's apenas deixam o retorno positivo, negligenciando uma característica das características relevantes em RTOS, que é atender o **DEADLINE** , por isso deve-se evitar o uso de sleep quando o tempo for uma variável crucial.

### Fluxo de desenvolvimento

![image](https://user-images.githubusercontent.com/48101913/144736287-016db7a7-50b7-4e0b-8b47-b5aeedfe216f.png)



Acima é um diagrama que mostra como o projeto será desenvolvido, neste momento iremos descrever detalhadamente o bloco de **tx_application_define()** que irá carregar todas as configurações das threads do nosso projeto.

Para criar uma thread, podemos simplesmente chamar a função **tx_thread_create()** passando os parãmetros corretos e a thread será criada como mostra o trecho de código abaixo (disponível em : https://docs.microsoft.com/en-us/azure/rtos/threadx/chapter2) o problema do código abaixo é que ele não requisição de recursos à API do RTOS(Como assim requisição de recurso ?). Bom, o sistema operacional é inicializado na função **_tx_initialize_low_level_** essa função ao final da inicialização passa o primeiro endereço de memória RAM disponível para a função **tx_application_define** como parãmetro [3] , ou seja, isso implica que em nenhum momento há registro de que estamos usando aquele endereço, em uma aplição onde existe apenas 1 thread(ou poucas) isso talvez não seja um problema, mas em uma aplicação que usa várias threads é necessário registrar o uso desse espaço de memória e caso não seja possível pegar espaços consectivos, fazer um algoritmo que faça uma lista encadeada ou duplamente encadeada para que seja possível unir pedaços de memória para formar um bloco, é nesse sentido que a função **tx_byte_pool_create()** existe ela tem a tarefa de solicitar um bloco de memória e se posível encadeá-los e naquele blocos serão registrados as pilhas de cada thread.

```cpp
#include "tx_api.h"
unsigned long my_thread_counter = 0;
TX_THREAD my_thread;
main( )
{
    /* Enter the ThreadX kernel. */
    tx_kernel_enter( );
}
void tx_application_define(void *first_unused_memory)
{
    /* Create my_thread! */
    tx_thread_create(&my_thread, "My Thread",
    my_thread_entry, 0x1234, first_unused_memory, 1024,
    3, 3, TX_NO_TIME_SLICE, TX_AUTO_START);
}
void my_thread_entry(ULONG thread_input)
{
    /* Enter into a forever loop. */
    while(1)
    {
        /* Increment thread counter. */
        my_thread_counter++;
        /* Sleep for 1 tick. */
        tx_thread_sleep(1);
    }
}

```

O passo mais seguro para criar thread no ThreadX é solicitar um bloco de memória onde serão armazenados as stacks das threads criadas.


```cpp
TX_BYTE_POOL byte_pool;

// Request a block of memory, if there's no consective blocks of memory avaible then link them by using the function
// All the description above the function tx_byte_pool_create(); does.
tx_byte_pool_create
(
  &byte_pool,
  "Block of memory",
  first_unused_memory,
  9120
);


```

![image](https://user-images.githubusercontent.com/48101913/144735628-845e9601-6c39-4a55-8b64-5f98976bafc5.png)
 
 O código abaixo serve para criação da thread 1, para o restante basta repetir os passos abaixos.
 
 ```cpp
 
    /* Allocate the stack for thread 0. */
   tx_byte_allocate
   (
      &byte_pool,              // Address of block pool
      (void*)&pointer,                  // Recieve the address of stack
      STACK_SIZE,                // The size requested
      TX_NO_WAIT                 // Create the region immediately
   );

   
   // Attemp to create until create
   do
   {
      status = tx_thread_create
      (
         &thread1,               // Pointer to a thread control block.
         "thread 0",             // Pointer to the name of the thread
         thread_led_1,           // Thread function
         30,                     // A 32-bit value that is passed to the thread's entry function when it first executes
                                 // in this case we'll pass the value that we want thread execute
         pointer,                // Pointer to stack
         STACK_SIZE,             // Size of its own stack
         1,                      // Priority
         1,                      // Preempt threhold
         TX_NO_TIME_SLICE,       // Time quantum
         TX_AUTO_START           // Start immediately
      );
   } while (status != TX_SUCCESS);
   
   
}
 
 ```
Quando configurado as 3 Threads para piscar os leds PN0,PN1 e PF4 com **TX_NO_TIME_SLICE**, **Threshold 1**, **Priority 1** e **TX_AUTO_START** temos a impressão que as threads estão sendo executadas paralelamente. Essa velocidade de troca de contexto pode ser alterada no **tx_api.h** por default ela está em 10ms que é um valor adequado para cada tick do sistema operacional, mas caso seja necessário você pode alterar ele para 10 e ficará 1ms de tick no sistema operacional. Outro ponto importante é que os tempos das threads foram feitos com **tx_thread_sleep()**  essa função faz a thread sair do estado pronto e desa forma executar a próxima tarefa pronta, esse comportamento era esperado. O código desse lab na tentativa de evitar que a thread saia do estado "pronto" usaremos loops de for que adicionam uma variável e veremos o comportamento dos escalomentos.





https://user-images.githubusercontent.com/48101913/144761323-65e16280-ab2f-4d11-847f-6309fd94fe99.mp4



### Testando escalonamentos

**a) Escalonamento por time-slice de 50 ms. Todas as tarefas com mesma prioridade.**

```cpp
// O tick foi alterado

   status = tx_thread_create
   (
      &thread1,               // Pointer to a thread control block.
      "thread 1",             // Pointer to the name of the thread
      thread_led_1,           // Thread function
      30,                     // A 32-bit value that is passed to the thread's entry function when it first executes
                              // in this case we'll pass the value that we want thread execute
      pointer,                // Pointer to stack
      STACK_SIZE,             // Size of its own stack
      1,                      // Priority
      1,                      // Preempt threhold
      50,       // Time quantum
      TX_AUTO_START           // Start immediately
   );

   // Attemp to create
   status = tx_thread_create
   (
      &thread2,               // Pointer to a thread control block.
      "thread 2",             // Pointer to the name of the thread
      thread_led_2,           // Thread function
      30,                     // A 32-bit value that is passed to the thread's entry function when it first executes
                              // in this case we'll pass the value that we want thread execute
      pointer,                // Pointer to stack
      STACK_SIZE,             // Size of its own stack
      1,                      // Priority
      1,                      // Preempt threhold
      50,                       // Time quantum
      TX_AUTO_START           // Start immediately
   );


   // Attemp to create
   status = tx_thread_create
   (
      &thread3,               // Pointer to a thread control block.
      "thread 3",             // Pointer to the name of the thread
      thread_led_3,           // Thread function
      30,                     // A 32-bit value that is passed to the thread's entry function when it first executes
                              // in this case we'll pass the value that we want thread execute
      pointer,                // Pointer to stack
      STACK_SIZE,             // Size of its own stack
      1,                      // Priority
      1,                      // Preempt threhold
      50,       // Time quantum
      TX_AUTO_START           // Start immediately
   );


```

Para esse teste os trechos de códigos referente a interrupção do sistick foram alterados para 1ms **tx_initialize_low_level**.
```assembly

    EXTERN  _tx_thread_system_stack_ptr
    EXTERN  _tx_initialize_unused_memory
    EXTERN  _tx_timer_interrupt
    EXTERN  __vector_table
    EXTERN  _tx_execution_isr_enter
    EXTERN  _tx_execution_isr_exit
;
;
SYSTEM_CLOCK      EQU   25000000
SYSTICK_CYCLES    EQU   ((SYSTEM_CLOCK / 1000) -1)

    RSEG    FREE_MEM:DATA
    PUBLIC  __tx_free_memory_start
__tx_free_memory_start
    DS32    4
;
;
```

|  Thread  	| Before 	| After 	|   Time  	|
|:--------:	|:------:	|:-----:	|:-------:	|
| Thread 1 	|    0   	| 10125 	| 10,12 s 	|
| Thread 2 	|    0   	| 10125 	| 10,12 s 	|
| Thread 3 	|    0   	| 10125 	| 10,12 s 	|


 Todas as Threads executaram piscando os LEDS.



https://user-images.githubusercontent.com/48101913/144763732-8b4f9c65-72aa-457b-a733-0cf48e0ee6fa.mp4




**b) Escalonamento sem time-slice e sem preempção. Prioridades estabelecidas no passo 3. A preempção pode ser evitada com o “
preemption threshold” do ThreadX.**

```cpp
// O tick foi alterado

   status = tx_thread_create
   (
      &thread1,               // Pointer to a thread control block.
      "thread 1",             // Pointer to the name of the thread
      thread_led_1,           // Thread function
      30,                     // A 32-bit value that is passed to the thread's entry function when it first executes
                              // in this case we'll pass the value that we want thread execute
      pointer,                // Pointer to stack
      STACK_SIZE,             // Size of its own stack
      1,                      // Priority
      1,                      // Preempt threhold
      TX_NO_TIME_SLICE,       // Time quantum
      TX_AUTO_START           // Start immediately
   );

   status = tx_thread_create
   (
      &thread2,               // Pointer to a thread control block.
      "thread 2",             // Pointer to the name of the thread
      thread_led_2,           // Thread function
      30,                     // A 32-bit value that is passed to the thread's entry function when it first executes
                              // in this case we'll pass the value that we want thread execute
      pointer,                // Pointer to stack
      STACK_SIZE,             // Size of its own stack
      2,                      // Priority
      2,                      // Preempt threhold
      TX_NO_TIME_SLICE,                       // Time quantum
      TX_AUTO_START           // Start immediately
   );

   status = tx_thread_create
   (
      &thread3,               // Pointer to a thread control block.
      "thread 3",             // Pointer to the name of the thread
      thread_led_3,           // Thread function
      30,                     // A 32-bit value that is passed to the thread's entry function when it first executes
                              // in this case we'll pass the value that we want thread execute
      pointer,                // Pointer to stack
      STACK_SIZE,             // Size of its own stack
      3,                      // Priority
      3,                      // Preempt threhold
      TX_NO_TIME_SLICE,       // Time quantum
      TX_AUTO_START           // Start immediately
   );

```


Para esse escalonamento é esperado que ele execute 1 thread por vez, uma vez que todas as threads possuem threshold diferente.

|  Thread  	| Before 	| After 	|  Time  	|
|:--------:	|:------:	|:-----:	|:------:	|
| Thread 1 	|    0   	|  3370 	| 3,37 s 	|
| Thread 2 	|  3370  	|  6741 	| 3,37 s 	|
| Thread 3 	|  6741  	| 10111 	| 3,37 s 	|



https://user-images.githubusercontent.com/48101913/144765713-514653c9-46ba-4528-92d6-40c35ded3c74.mp4


**c) Escalonamento preemptivo por prioridade.**

Uma tarefa executou por vez.


```cpp
// O tick foi alterado

   status = tx_thread_create
   (
      &thread1,               // Pointer to a thread control block.
      "thread 1",             // Pointer to the name of the thread
      thread_led_1,           // Thread function
      30,                     // A 32-bit value that is passed to the thread's entry function when it first executes
                              // in this case we'll pass the value that we want thread execute
      pointer,                // Pointer to stack
      STACK_SIZE,             // Size of its own stack
      1,                      // Priority
      3,                      // Preempt threhold
      TX_NO_TIME_SLICE,       // Time quantum
      TX_AUTO_START           // Start immediately
   );

   status = tx_thread_create
   (
      &thread2,               // Pointer to a thread control block.
      "thread 2",             // Pointer to the name of the thread
      thread_led_2,           // Thread function
      30,                     // A 32-bit value that is passed to the thread's entry function when it first executes
                              // in this case we'll pass the value that we want thread execute
      pointer,                // Pointer to stack
      STACK_SIZE,             // Size of its own stack
      2,                      // Priority
      3,                      // Preempt threhold
      TX_NO_TIME_SLICE,                       // Time quantum
      TX_AUTO_START           // Start immediately
   );

   status = tx_thread_create
   (
      &thread3,               // Pointer to a thread control block.
      "thread 3",             // Pointer to the name of the thread
      thread_led_3,           // Thread function
      30,                     // A 32-bit value that is passed to the thread's entry function when it first executes
                              // in this case we'll pass the value that we want thread execute
      pointer,                // Pointer to stack
      STACK_SIZE,             // Size of its own stack
      3,                      // Priority
      3,                      // Preempt threhold
      TX_NO_TIME_SLICE,       // Time quantum
      TX_AUTO_START           // Start immediately
   );

```
Foto ilustrativa do que deve acontecer

![image](https://user-images.githubusercontent.com/48101913/145097555-54d9c3fd-f631-4e73-b8fc-bfc57f963a00.png)



https://user-images.githubusercontent.com/48101913/145098020-f7a09d33-1707-42cc-afee-0a3fe876a7ee.mp4

|  Thread  	| Before 	| After 	|  Time  	|
|:--------:	|:------:	|:-----:	|:------:	|
| Thread 1 	|    0   	|  3370 	| 3,37 s 	|
| Thread 2 	|  3370  	|  6741 	| 3,37 s 	|
| Thread 3 	|  6741  	| 10111 	| 3,37 s 	|


**d) Implemente um Mutex compartilhado entre T1 e T3. No início de cada job estas tarefas devem solicitar este mutex e liberá-lo no
final. Use mutex sem herança de prioridade. Observe o efeito na temporização das tarefas.**

A tarefa que está com o controle do LED esperou o recurso ser liberado para poder executar, conforme previsto

```cpp

/*
Configuração do mutex 
status = tx_mutex_create(&my_mutex,"my_mutex_name", TX_NO_INHERIT);

*/
// O tick foi alterado

   status = tx_thread_create
   (
      &thread1,               // Pointer to a thread control block.
      "thread 1",             // Pointer to the name of the thread
      thread_led_1,           // Thread function
      30,                     // A 32-bit value that is passed to the thread's entry function when it first executes
                              // in this case we'll pass the value that we want thread execute
      pointer,                // Pointer to stack
      STACK_SIZE,             // Size of its own stack
      1,                      // Priority
      3,                      // Preempt threhold
      50,       // Time quantum
      TX_AUTO_START           // Start immediately
   );

   status = tx_thread_create
   (
      &thread2,               // Pointer to a thread control block.
      "thread 2",             // Pointer to the name of the thread
      thread_led_2,           // Thread function
      30,                     // A 32-bit value that is passed to the thread's entry function when it first executes
                              // in this case we'll pass the value that we want thread execute
      pointer,                // Pointer to stack
      STACK_SIZE,             // Size of its own stack
      1,                      // Priority
      1,                      // Preempt threhold
      50,                       // Time quantum
      TX_AUTO_START           // Start immediately
   );

   status = tx_thread_create
   (
      &thread3,               // Pointer to a thread control block.
      "thread 3",             // Pointer to the name of the thread
      thread_led_3,           // Thread function
      30,                     // A 32-bit value that is passed to the thread's entry function when it first executes
                              // in this case we'll pass the value that we want thread execute
      pointer,                // Pointer to stack
      STACK_SIZE,             // Size of its own stack
      1,                      // Priority
      1,                      // Preempt threhold
      50,       // Time quantum
      TX_AUTO_START           // Start immediately
   );

```


https://user-images.githubusercontent.com/48101913/145118346-3ae73b43-4229-410a-bdd7-7144aed9e260.mp4

|  Thread  	| Before 	| After 	|  Time  	|
|:--------:	|:------:	|:-----:	|:------:	|
| Thread 1 	|    50   	|  6734 	| 3,37 s 	|
| Thread 2 	|    50    	|  10114 	| 3,37 s 	|
| Thread 3 	|    50  	|  6855  	| 3,37 s 	|


# Referências

1.  Descrição de funções do ThreadX - https://docs.microsoft.com/en-us/azure/rtos/threadx/chapter4#tx_byte_pool_create
2.  Algoritmo para mensuração do tempo - https://en-support.renesas.com/knowledgeBase/18539139
3.  Trecho de código criando uma thread https://docs.microsoft.com/en-us/azure/rtos/threadx/chapter2
4.  Esquemático da Tiva fornecido em aula.
5.  Material IF Gerencia de processador https://intranet.ifs.ifsuldeminas.edu.br/kleber.rezende/anteriores/2sem2015/2Redes/FSO_slides_07_Ger%C3%AAncia%20da%20CPU.pdf
