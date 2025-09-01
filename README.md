# Funções Utilizadas

## mpi_simples.c

Este programa executa funções essenciais para iniciar, executar uma comunicação básica e finalizar um programa MPI.

- MPI_Init(&argc, &argv): Inicializa o ambiente MPI. Esta é a primeira função MPI que deve ser chamada em qualquer programa. Ela prepara toda a infraestrutura necessária para a comunicação entre os processos.

- MPI_Comm_size(MPI_COMM_WORLD, &num_procs): Obtém o número total de processos que estão participando da execução. O resultado é armazenado na variável num_procs. MPI_COMM_WORLD é o comunicador que inclui todos os processos.

- MPI_Comm_rank(MPI_COMM_WORLD, &meu_ranque): Obtém o identificador (rank) do processo atual. Cada processo recebe um número de identificação único, que vai de 0 até num_procs - 1. O rank do processo que chama a função é guardado na variável meu_ranque.

- MPI_Send(mensagem, strlen(mensagem)+1, MPI_CHAR, destino, etiq, MPI_COMM_WORLD): Envia uma mensagem de forma bloqueante (o processo espera a escrita de dados no buffer ser concluída com segurança).

        mensagem: Dados a serem enviados.

        strlen(mensagem)+1: Quantidade de dados (incluindo o caractere nulo \0 da string).

        MPI_CHAR: Tipo do dado.

        destino: Rank do processo que receberá a mensagem.

        etiq: Uma etiqueta (inteiro) para identificar a mensagem.

        MPI_COMM_WORLD: O comunicador - O grupo de processos que está se comunicando.

- MPI_Recv(mensagem, 200, MPI_CHAR, origem, etiq, MPI_COMM_WORLD, &estado): Recebe uma mensagem de forma bloqueante (o processo espera a leitura de dados do buffer ser concluída com segurança).

        mensagem: Buffer para armazenar a mensagem recebida.

        200: Tamanho máximo do buffer.

        MPI_CHAR: Tipo do dado esperado.

        origem: Rank do processo que enviará a mensagem.

        etiq: Etiqueta da mensagem esperada.

        MPI_COMM_WORLD: O comunicador.

        &estado: Estrutura que guarda informações sobre a mensagem recebida. Contém MPI_SOURCE, MPI_TAG e MPI_ERROR.

    MPI_Finalize(): Finaliza o ambiente MPI. Deve ser a última função MPI a ser chamada, liberando todos os recursos alocados.

### Observações

- MPI_ANY_SOURCE: recebe uma mensagem de qualquer fonte
- MPI_ANY_TAG: recebe uma mensagem com qualquer tag

## mpi_simples_v2.c (aula02)

Utiliza MPI_ANY_SOURCE para que, não necessariamente, as mensagens sejam recebidas na ordem.

## Tabela de Datatypes MPI e C

A tabela a seguir mostra a correspondência entre os tipos de dados básicos do MPI e seus equivalentes na linguagem C.

| MPI Datatype              | Corresponding C Datatype                               |
| ------------------------- | ------------------------------------------------------ |
| `MPI_CHAR`                | `signed char`                                          |
| `MPI_SHORT`               | `signed short int`                                     |
| `MPI_INT`                 | `signed int`                                           |
| `MPI_LONG`                | `signed long int`                                      |
| `MPI_UNSIGNED_CHAR`       | `unsigned char`                                        |
| `MPI_UNSIGNED_SHORT`      | `unsigned short int`                                   |
| `MPI_UNSIGNED`            | `unsigned int`                                         |
| `MPI_UNSIGNED_LONG`       | `unsigned long int`                                    |
| `MPI_FLOAT`               | `float`                                                |
| `MPI_DOUBLE`              | `double`                                               |
| `MPI_LONG_DOUBLE`         | `long double`                                          |
| `MPI_BYTE`                | representa um byte de 8 bits)                          |
| `MPI_PACKED`              | usado para empacotar dados diversos)                   |

---

### Notas sobre `MPI_BYTE` e `MPI_PACKED`:

* **`MPI_BYTE`**: Este tipo é usado quando você quer tratar os dados como uma coleção de bytes, sem se preocupar com o tipo (inteiro, float, etc.). É útil para ler/escrever arquivos binários ou enviar dados heterogêneos.

* **`MPI_PACKED`**: Este não é um tipo de dado no sentido tradicional (utiliza uma estrutura de dados). Ele é usado em conjunto com as funções `MPI_Pack` e `MPI_Unpack` para agrupar diferentes tipos de dados em um único buffer antes de enviá-los, o que é útil para otimizar a comunicação de dados não contíguos.

