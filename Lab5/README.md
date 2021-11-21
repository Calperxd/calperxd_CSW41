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
  ├── Debug
  ├── settings
  ├── README.md
  ├── tx.a
  └── src
      ├── cstartup_M.s
      ├── sample_threadx.c
      └── tx_initialize_low_level.s
```

# Conclusão

Evidentemente poderíamos ter usado a biblioteca ctype.h e fazer uso das funções tolower() e toupper() para converter para maiúsculo e minúsculo, entretanto como estamos trabalhando em um sistema com recursos limitados, chamar bibliotecas assim podem acarretar problemas, como uso excessivo de recursos, quando na verdade o algoritmo é algo relativamente fácil de ser implementado, claro que esse algoritmo ainda pode melhorar, no quesito eficiência, mas já é melhor que instanciar uma biblioteca completa para isso. 

# Referências

1. Blog sobre funcionamento UART - https://deepbluembedded.com/uart-pic-microcontroller-tutorial/

