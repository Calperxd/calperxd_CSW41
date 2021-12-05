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
Basicamente o fluxo abaixo representa como nossa função deve funcionar 
```cpp

/* Pickup the current system time, in timer-ticks. */
ULONG time_before;
ULONG time_after;
ULONG time_lapsed ;

time_before = tx_time_get();

/***** execution code *****/

time_after = tx_time_get();
time_lapsed = time_after - time_before;

```

# Referências

1.  Descrição de funções do ThreadX - https://docs.microsoft.com/en-us/azure/rtos/threadx/chapter4#tx_byte_pool_create
2.  Algoritmo para mensuração do tempo - https://en-support.renesas.com/knowledgeBase/18539139

