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

Mapeie o código do Threadx de acordo com as mensagens de erros geradas no console de log, ou simplesmente mapeie igual a imagem abaixo, tanto para o projeto tx quanto para o sample_threadx.

![image](https://user-images.githubusercontent.com/48101913/143146428-c57d46d5-eaee-470c-ac13-c1a0bc2319c1.png)


Agora é necessário comppilar o ThreadX em uma biblioteca estática para que ele esteja disponível no nosso código., para compilar para arquitetura ARM Cortex M4 é só ir na pasta /ThreadX/ports/cortex_m4 e escolher em qual compilador você irá compilar, note que existem várias além de ser possível compilar usando as ferramentas GNU, entretanto para esse lab usaremos a IDE da iar que vem com seu compilador proprietário, para isso navegue até a pasta \ThreadX\ports\cortex_m4\iar e abra o projeto e compile-o, Isso irá gerar o arquivo abaixo. Para saber o que foi compilado basta você verificar com a ferramenta de linha de comando **arm-none-eabi-nm tx.a** ou **arm-none-eabi-ar t tx.a**.

![image](https://user-images.githubusercontent.com/48101913/143145717-07d7a922-875b-493d-b501-7d99f3ba918f.png)

Agora copie os arquivos sample_threadx.c, cstartup.c e tx_initialize_low_level.c para pasta src além de também copiar para a pasta Lab5 o tx.a.

![image](https://user-images.githubusercontent.com/48101913/143147874-acf8689c-f19f-4d3a-81d7-27a5e37a0e3f.png)


Mapeie o projeto igual a imagem abaixo.

![image](https://user-images.githubusercontent.com/48101913/143148117-32c4d4ce-702b-4bd2-a6ec-1f3ab8f98840.png)

No Linker mapeie a biblioteca estática do ThreadX, que foi o arquivo inicialmente compilado nos dois primeiros passos, conforme a imagem abaixo.

![image](https://user-images.githubusercontent.com/48101913/143148369-d688d0d5-b40c-49ad-aa00-d49e5b2d2f43.png)

Agora habilite o plugin ThreadX para que na hora do debug algumas funções estejam disponíveis

![image](https://user-images.githubusercontent.com/48101913/143149228-ccb509b9-cdf5-45f3-a729-fac399b523b9.png)


# Conclusão

Evidentemente poderíamos ter usado a biblioteca ctype.h e fazer uso das funções tolower() e toupper() para converter para maiúsculo e minúsculo, entretanto como estamos trabalhando em um sistema com recursos limitados, chamar bibliotecas assim podem acarretar problemas, como uso excessivo de recursos, quando na verdade o algoritmo é algo relativamente fácil de ser implementado, claro que esse algoritmo ainda pode melhorar, no quesito eficiência, mas já é melhor que instanciar uma biblioteca completa para isso. 

# Referências

1. Blog sobre funcionamento UART - https://deepbluembedded.com/uart-pic-microcontroller-tutorial/

