# Sistemas Embarcados
- Código: CSW41
- Créditos: 4
- Professor: Douglas Paulo Bertrand Renaux
- Email: douglasrenaux@professores.utfpr.edu.br
- Aluno: Gabriel Alexandre Linhares Calper Seabra
- Email: gabrielseabra@alunos.utfpr.edu.br


# Lab1

#### Introdução
Este laboratório consiste em configurar todo o ambiente necessário para o desenvolvimento da disciplina de sistemas embarcados na launchpad da texas **_EK-TM4C1294XL_**.

#### Execução
1. Primeiro passo foi baixar a **_IDE IAR Embedded Workbench for ARM_** disponível em https://www.iar.com/products/architectures/arm/iar-embedded-workbench-for-arm/

2. Registrar como “Code size limited”.

3. Depois de instalado e devidamente licenciado a estrutura de diretório foi criada como pode ser visto na figura abaixo. 

<img style="-webkit-user-select: none;margin: auto;cursor: zoom-in;background-color: hsl(0, 0%, 90%);transition: background-color 300ms;" src="https://user-images.githubusercontent.com/48101913/135728799-39d40bea-2f5d-4bb9-9269-381963d51b96.PNG" width="854" height="480">

4. Agora devemos criar um projeto clicando no local indicado na imagem abaixo.

<img style="-webkit-user-select: none;margin: auto;cursor: zoom-in;background-color: hsl(0, 0%, 90%);transition: background-color 300ms;" src="https://user-images.githubusercontent.com/48101913/135729064-b3a82a53-d6ac-4f9e-a2bb-83561e090479.PNG" width="854" height="480">

5. Selecione o projeto C++ e clique em OK.
<img style="-webkit-user-select: none;margin: auto;cursor: zoom-in;background-color: hsl(0, 0%, 90%);transition: background-color 300ms;" src="https://user-images.githubusercontent.com/48101913/135729105-e6f9e23b-714c-46ef-b134-9b0b5592381f.png" width="854" height="480">

6. Agora vá em opções do projeto.

<img style="-webkit-user-select: none;margin: auto;cursor: zoom-in;background-color: hsl(0, 0%, 90%);transition: background-color 300ms;" src="https://user-images.githubusercontent.com/48101913/135730626-906b95ea-8912-4d91-92f0-b6a4b1e68ec4.png" width="854" height="480">

7. Coloque o processador em ARM CORTEX M4 e habilite o coprocessador de ponto flutuante com precisão simples.

<img style="-webkit-user-select: none;margin: auto;cursor: zoom-in;background-color: hsl(0, 0%, 90%);transition: background-color 300ms;" src="https://user-images.githubusercontent.com/48101913/135730692-d58b281f-23e1-41a9-bdbc-5bcac8ca1e87.png" width="854" height="480">

<img style="-webkit-user-select: none;margin: auto;cursor: zoom-in;background-color: hsl(0, 0%, 90%);transition: background-color 300ms;" src="https://user-images.githubusercontent.com/48101913/135730708-c87e8776-f74b-4b60-879d-0d03e4397925.png" width="854" height="480">

8. Depois foi escrito o código inicial um famigerado "Hello World" e aperte em **_Download and Debug_**.

<img style="-webkit-user-select: none;margin: auto;cursor: zoom-in;background-color: hsl(0, 0%, 90%);transition: background-color 300ms;" src="https://user-images.githubusercontent.com/48101913/135731201-d6749744-5efc-4bd0-aebb-e4a42bb2f084.png" width="854" height="480">

A saída pode ser vista no Terminal I/O conforme a figura abaixo.

<img style="-webkit-user-select: none;margin: auto;cursor: zoom-in;background-color: hsl(0, 0%, 90%);transition: background-color 300ms;" src="https://user-images.githubusercontent.com/48101913/135731245-63758c3a-8cc5-455d-a131-2c115c2a15d5.png" width="854" height="480">

A saída também pode ser acompanhada no dissassembly do código conforme pode ser visto no código acima.