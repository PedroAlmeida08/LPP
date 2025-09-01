# Funções Utilizadas

## mpi_wtime.c

Esse programa executa funções relacionadas à medição de tempo.

- MPI_Wtime(): Retorna o tempo decorrido (em segundos, como um número de ponto flutuante de alta precisão). É usado para medir a duração de trechos de código, calculando a diferença entre duas chamadas a esta função.

- MPI_Wtick(): Retorna a resolução do MPI_Wtime(), ou seja, o menor intervalo de tempo (em segundos) que o relógio consegue medir. Informa a precisão do temporizador.

## mpi_funcoes.c

Esse programa executa funções diversas para gerenciamento e informação do ambiente MPI.

- MPI_Abort(MPI_COMM_WORLD, ret): Termina abruptamente todos os processos MPI no comunicador especificado. É uma chamada de emergência, usada para abortar o programa em caso de um erro crítico. ret é um código de erro retornado ao sistema.

- MPI_Get_version(&versao, &subversao): Obtém a versão da especificação MPI que a biblioteca implementa. Os números da versão principal e secundária são armazenados nas variáveis versao e subversao.

- MPI_Get_processor_name(maquina, &aux): Obtém o nome do nó (ou máquina) do processador onde o processo atual está sendo executado. O nome é armazenado na variável maquina e seu tamanho na variável aux.
