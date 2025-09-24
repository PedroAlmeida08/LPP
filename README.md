## mpi_ssend.c

### MPI_Ssend()
É um envio bloqueante que só se completa quando o processo receptor inicia o recebimento da mensagem. Ele garante um ponto de sincronização entre o emissor e o receptor.

## mpi_rsend.c

### MPI_Rsend()
É um envio bloqueante que só pode ser chamado quando o processo receptor já está pronto para a operação de recebimento.

## mpi_sendrecv.c

### MPI_Sendrecv()
Combina uma operação de envio e uma de recebimento em uma única chamada bloqueante.


