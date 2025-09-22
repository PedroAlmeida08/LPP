## mpi_isend.c

### MPI_Isend
Operação send não-bloqueante

### MPI_Irecv
Operação recv não-bloqueante

### MPI_Wait()
Função bloqueante usada para esperar que uma operação de comunicação não-bloqueante seja concluída.

### MPI_Test()
Função não-bloqueante usada para esperar que uma operação de comunicação não-bloqueante seja concluída.

## mpi_bsend.c

### MPI_Pack_size
Calcula o espaço necessário para o envio de uma mensagem.

### MPI_Buffer_attach
Atribui o buffer para ser utilizado.

### MPI_BSEND_OVERHEAD
Adiciona um espaço adicional ao buffer.

### MPI_Bsend
Função de envio de mensagens que utiliza um buffer próprio para enviar mensagens
