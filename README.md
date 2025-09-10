# Funções

## mpi_barrier.c

- MPI_Barrier(MPI_COMM_WORLD): A função MPI_Barrier fornece um mecanismo para sincronizar todos os processos no comunicador. Cada processo fica bloqueado até que todos os processos em com tenham chamado MPI_Barrier.

## mpi_bcast.c

- MPI_Bcast(&valor, 1, MPI_INT, raiz, MPI_COMM_WORLD): A função MPI_Bcast envia uma cópia dos dados de mensagem no processo raiz para cada processo no comunicador. Uma mensagem de broadcast não pode ser recebida com MPI_Recv.
  - se ranque != 0, &valor recebe 1 mensagem do tipo INT do processo raiz.
 
## mpi_reduce.c

- MPI_Reduce(void* operando, void* resultado, int cont, MPI_Datatype tipo_mpi, MPI_Op oper, int raiz, MPI_Comm com)
  - A operação MPI_Reduce combina os operandos armazenados em *operando usando a operação oper e armazena o resultado em *resultado no processo raiz.
  - Tanto operando como resultado referem-se a cont posições de memória com o tipo tipo_mpi.
  - MPI_Reduce deve ser chamada por todos os processos no comunicador com e os valores de cont, tipo_mpi e oper devem ser os mesmos em cada processo.
  - O argumento oper pode ter um dos seguintes valores pré-definidos:

| Nome                      | Função                                                 |
| ------------------------- | ------------------------------------------------------ |
| `MPI_MAX`                 | `Máximo`                                               |
| `MPI_MIN`                 | `Mínimo`                                               |
| `MPI_SUM`                 | `Soma`                                                 |
| `MPI_PROD`                | `Produto`                                              |
| `MPI_LAND`                | `"E" lógico`                                           |
| `MPI_BAND`                | `"E" bit a bit`                                        |
| `MPI_LOR`                 | `"OU" lógico`                                          |
| `MPI_BOR`                 | `"OU" bit a bit`                                       |
| `MPI_LXOR`                | `"OU Exclusivo" lógico`                                |
| `MPI_BXOR`                | `"OU Exclusivo" bit a bit`                             |
| `MPI_MAXLOC`              | `Máximo e Posição do Máximo`                           |
| `MPI_MINLOC`              | `Mínimo e Posição do Mínimo`                           |

