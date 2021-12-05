# Sistemas Embarcados
- Código: CSW41
- Créditos: 4
- Professor: Douglas Paulo Bertrand Renaux
- Email: douglasrenaux@professores.utfpr.edu.br
- Aluno: Gabriel Alexandre Linhares Calper Seabra
- Email: gabrielseabra@alunos.utfpr.edu.br


# Lab6

#### Introdução
Criar um conjunto de 3 tarefas com temporizaçõe conhecidas. Experimentando variaçõe de algoritmos de escalonamento disponível no ThreadX.

#### O Projeto
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

#### Fluxo de desenvolvimento

![image](https://user-images.githubusercontent.com/48101913/144734131-6e66aec2-89d3-488b-8caa-900d65db5d96.png)


Acima é um diagrama que mostra como o projeto será desenvolvido, neste momento iremos descrever detalhadamente o bloco de **tx_application_define()** que irá carregar todas as configurações das threads do nosso projeto.


# Referências

1.  Descrição de funções do ThreadX - https://docs.microsoft.com/en-us/azure/rtos/threadx/chapter4#tx_byte_pool_create
2.  Algoritmo para mensuração do tempo - https://en-support.renesas.com/knowledgeBase/18539139

