# Sistemas Embarcados
- Código: CSW41
- Créditos: 4
- Professor: Douglas Paulo Bertrand Renaux
- Email: douglasrenaux@professores.utfpr.edu.br
- Aluno: Gabriel Alexandre Linhares Calper Seabra
- Email: gabrielseabra@alunos.utfpr.edu.br


# Lab4
#### Introdução
Esse labaratório tem como objetivo configurar a interface UART de forma que seja possível Enviar e receber dados pelo terminal.
# UART
A UART (Universal Asynchronous Receiver-Transmitter) é um modo de transmissão serial muito utilizado em sistemas embarcados, ele transmite dados de um microcontrolador para outro ou para um computador podendo utilizar apenas 2 fios RX (Reciever) e TX(Transmitter) além da referêcia. É um sistema full duplex ou seja, pode transmitir e receber ao mesmo tempo.

#### Funcionamento.


Quando parado ou idle o pino está em estado lógico alto.


![Shift_Register](https://user-images.githubusercontent.com/48101913/140596381-d1d67cd7-bb42-461d-b5f0-0421640c0b89.gif)

Cada transmissão de dados começa com 1 bit de start que é sempre estado lógico baixo.

Cada pacote de dados tem 8 ou 9 bits de tamanho, onde o LSB é sempre o primeiro a ser transferido.

Cada transmissão de dados termina com um STOP bit que tem sempre estado lógico alto.

Quando não há dados a serem transmitidos, a linha fica em nível lógico alto.

O receptor reconhece a borda de descida do start bit e sincroniza seu clock.

Após 1 ciclo e meio começa a fazer a leitura dos demais bits a cada clock.

Se as frequências do transmissor e do receptor estiverevem perfeitamente sincronizadas, as leituras serão efetuadas exatamente no meio de cada ciclo.




# Conclusão

 Poderíamos ficar aqui conferindo pixel por pixel para ver se o histograma foi gerado corretamente, entretando essa veríficação já foi feita e o algoritmo foi implmentado conforme os requisitos, o cerne da dircussão nessa seção é falar de como esse algoritmo foi implmentado, quais a dificuldades, no que ele contribuiu para o processo de aprendizaegem e uma forma alternativa de desenvolvê-lo.
Primeiramente, este lab serviu para entender as diferenças de armazenamento, além de mostrar o trabalho do compilador, mas por quê o trabalho do compilador ? o compilador organizou a matriz de uma forma que ela ficasse sequencial na memória, isso implica que eu não teria que acessar endereços de endereços para acessar uma linha ou uma coluna da matriz, isso tornou fácil o desenvolvimento uma vez que os dados referente a imagem estavam dispostos sequencialmente na memória. Outro ponto importante foi percorrer a memória, para qualquer pessoa parece trivial fazer um laço for em linguagem C e percorrer os dados, entretanto quando se programa em assembly é necessário saber quantos bytes você irá pular por o tamanho em bytes determina que tipo de dados estamos tratando e esse lab ajudou a compreender como isso acontece internamente.
O primeiro algoritmo implementado era computacionalmente custoso uma vez que ele percorria toda imagem e depois voltava para RAM para somar, isso fazia o algoritmo percorrer a imagem muitas vezes, o que demorava mais, talvez com uma imagem maior e com uma UART fosse possível implementar para imagens de mais bits sem comprometer tanto o tempo de desenvolvimento uma vez que o terminal IO do IAR é um pouco lento. </p>

# Referências

1. Blog sobre funcionamento UART - https://deepbluembedded.com/uart-pic-microcontroller-tutorial/

