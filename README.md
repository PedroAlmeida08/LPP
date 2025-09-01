# Funções Utilizadas

## mpi_simples.c

Este programa executa funções essenciais para iniciar, executar uma comunicação básica e finalizar um programa MPI.

- MPI_Init(&argc, &argv): Inicializa o ambiente MPI. Esta é a primeira função MPI que deve ser chamada em qualquer programa. Ela prepara toda a infraestrutura necessária para a comunicação entre os processos.

- MPI_Comm_size(MPI_COMM_WORLD, &num_procs): Obtém o número total de processos que estão participando da execução. O resultado é armazenado na variável num_procs. MPI_COMM_WORLD é o comunicador que inclui todos os processos.

- MPI_Comm_rank(MPI_COMM_WORLD, &meu_ranque): Obtém o identificador (rank) do processo atual. Cada processo recebe um número de identificação único, que vai de 0 até num_procs - 1. O rank do processo que chama a função é guardado na variável meu_ranque.

- MPI_Send(mensagem, strlen(mensagem)+1, MPI_CHAR, destino, etiq, MPI_COMM_WORLD): Envia uma mensagem de forma bloqueante (o processo espera a operação ser concluída com segurança).

        mensagem: Dados a serem enviados.

        strlen(mensagem)+1: Quantidade de dados (incluindo o caractere nulo \0 da string).

        MPI_CHAR: Tipo do dado.

        destino: Rank do processo que receberá a mensagem.

        etiq: Uma etiqueta (inteiro) para identificar a mensagem.

        MPI_COMM_WORLD: O grupo de processos que está se comunicando.

- MPI_Recv(mensagem, 200, MPI_CHAR, origem, etiq, MPI_COMM_WORLD, &estado): Recebe uma mensagem de forma bloqueante (o processo fica parado esperando a mensagem chegar).

        mensagem: Buffer para armazenar a mensagem recebida.

        200: Tamanho máximo do buffer.

        MPI_CHAR: Tipo do dado esperado.

        origem: Rank do processo que enviará a mensagem.

        etiq: Etiqueta da mensagem esperada.

        MPI_COMM_WORLD: O comunicador.

        &estado: Estrutura que guarda informações sobre a mensagem recebida.

    MPI_Finalize(): Finaliza o ambiente MPI. Deve ser a última função MPI a ser chamada, liberando todos os recursos alocados.

