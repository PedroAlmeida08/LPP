# Funções

## mpi_status.c

MPI_Status é uma estrutura de dados que contém informações detalhadas sobre uma operação de comunicação que foi completada. Quando você realiza uma operação de recebimento, como MPI_Recv, você pode passar uma variável do tipo MPI_Status para que o MPI a preencha com informações sobre a mensagem que acabou de chegar.

Os três campos principais e mais utilizados desta estrutura são:

- MPI_SOURCE: O rank (identificador) do processo que enviou a mensagem.
- MPI_TAG: A etiqueta (tag) da mensagem recebida.
- MPI_ERROR: Um código de erro associado à operação.

Além disso, a estrutura MPI_Status também pode ser usada para obter o número de elementos recebidos através da função MPI_Get_count().

Uso principal: É essencial quando você precisa saber quem enviou uma mensagem ou qual era a sua etiqueta, especialmente quando se utilizam coringas como MPI_ANY_SOURCE ou MPI_ANY_TAG na função de recebimento. Se você não precisar dessas informações, pode usar a constante MPI_STATUS_IGNORE.

### MPI_Get_count()

MPI_Get_count() é uma função usada para descobrir o número exato de elementos recebidos em uma operação de comunicação.

Depois que uma função como MPI_Recv completa, a estrutura MPI_Status é preenchida. Você pode então passar essa estrutura para MPI_Get_count() para saber quantos itens de um determinado tipo de dado (MPI_Datatype) foram efetivamente recebidos.

### MPI_STATUS_IGNORE

MPI_STATUS_IGNORE é uma constante especial que você pode passar no lugar de uma variável MPI_Status em uma função de recebimento.

Use MPI_STATUS_IGNORE quando você não precisa de nenhuma informação sobre a mensagem recebida (quem enviou, qual a etiqueta, ou quantos elementos chegaram). Isso sinaliza para a biblioteca MPI que a informação de status pode ser descartada.****

```
// Não nos importamos com o status, pois sabemos que a mensagem
// virá do processo 0 com a tag 0.
MPI_Recv(&dado, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
```
## mpi_probe.c

### MPI_Probe

A função MPI_Probe é muito parecida com a função MPI_Recv, pois realiza as mesmas funções, exceto que MPI_probe não recebe a mensagem efetivamente.

MPI_Probe é uma função de sondagem bloqueante. Ela permite "espiar" uma mensagem recebida sem de fato removê-la da fila de recebimento. A função espera até que uma mensagem que corresponda aos parâmetros (source, tag) chegue e, então, preenche uma estrutura MPI_Status com as informações dessa mensagem (origem, etiqueta e, crucialmente, seu tamanho).

O principal uso do MPI_Probe é descobrir o tamanho de uma mensagem antes de alocar um buffer para recebê-la. Isso permite a alocação dinâmica e eficiente de memória.

## mpi_trapezio.c

### Comandos
- mpicc -o mpi_trapezio mpi_trapezio.c -lm
- mpirun -n 2 mpi_trapezio

1 - #include <math.h>: Ao incluir este arquivo de cabeçalho, você está apenas 
informando ao compilador qual é a "assinatura" da função pow(), ou seja, que ela 
existe e como ela deve ser chamada. Isso é suficiente para a primeira fase da compilação.

2 - Fase de Linkagem: Após compilar, o linker (ld) entra em ação. Ele precisa juntar o 
seu código compilado com o código das bibliotecas que você usou. O erro referência indefinida 
acontece aqui, pois o linker não sabe onde encontrar o código da função exp().

3 - "-lm": Esta flag diz ao linker: "Procure também na biblioteca 'm' (a biblioteca matemática 
padrão do C/Linux)". Com essa instrução, o linker encontra a implementação da função exp() 
e consegue gerar o executável final com sucesso.
