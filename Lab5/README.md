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

Neste laboratório a configuração do ambiente mudou, isso implica que teremos que configurar novamente o ambiente de desenvolvimento para a nova plataforma de RTOS(ThreadX), Antes estávemos desenvolvendo em Bare Metal, o novo diretório deve parecer como pode ser visto logo abaixo.
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
O primeiro passo é compilar o ThreadX em uma biblioteca estática para que ele esteja disponível no nosso código, para compilar para arquitetura ARM Cortex M4 é só ir na pasta /ThreadX/ports/cortex_m4 e escolher em qual compilador você irá compilar, note que existem várias além de ser possível compilar usando as ferramentas GNU, entretanto para esse lab usaremos a IDE da iar que vem com seu compilador proprietário, para isso navegue até a pasta \ThreadX\ports\cortex_m4\iar e abra o projeto.

# Conclusão

Evidentemente poderíamos ter usado a biblioteca ctype.h e fazer uso das funções tolower() e toupper() para converter para maiúsculo e minúsculo, entretanto como estamos trabalhando em um sistema com recursos limitados, chamar bibliotecas assim podem acarretar problemas, como uso excessivo de recursos, quando na verdade o algoritmo é algo relativamente fácil de ser implementado, claro que esse algoritmo ainda pode melhorar, no quesito eficiência, mas já é melhor que instanciar uma biblioteca completa para isso. 

# Referências

1. Blog sobre funcionamento UART - https://deepbluembedded.com/uart-pic-microcontroller-tutorial/

