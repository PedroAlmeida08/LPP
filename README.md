## mpi_scatter.c

MPI_Scatter(void* vet_envia, int cont_envia, MPI_Datatype tipo_envia, void* vet_recebe, int cont_recebe, MPI_Datatype tipo_recebe, int raiz, MPI_comm com)
- O processo com ranque igual a raiz distribui (espalha) o conteúdo de seu vet_envia, dividindo-o em blocos de mesmo tamanho.
- Cada processo em com (incluindo a raiz) recebe um desses blocos em seu vet_recebe. O bloco de dados de vet_envia destinado ao processo de ranque i é copiado para o vet_recebe desse processo.
- Os argumentos envia (vet_envia, cont_envia, tipo_envia) são significativos apenas no processo com ranque igual a raiz.
- O argumento cont_envia indica o número de itens enviados para cada processo individualmente, não o tamanho total do vet_envia, e, normalmente, é igual a cont_recebe.

## mpi_gather

int MPI_Gather(void* vet_envia, int cont_envia, MPI_Datatype tipo_envia, void* vet_recebe, int cont_recebe, MPI_Datatype tipo_recebe, int raiz, MPI_comm com)
- Cada processo em com envia o conteúdo de vet_envia para o processo com ranque igual a raiz.
- O processo raiz concatena os dados que são recebidos em vet_recebe em uma ordem que é definida pelo ranque de cada processo.
- Os argumentos recebe são significativos apenas no processo com ranque igual a raiz.
- O argumento cont_recebe indica o número de itens enviados por cada processo, não o número total de itens recebidos pelo processo raiz e, normalmente, é igual a cont_envia.
