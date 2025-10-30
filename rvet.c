/**
 * Template base para implementação de Relógios Vetoriais (MPI)
 * -------------------------------------------------------------
 * Cada processo obtém seu rank internamente (sem passar por parâmetro).
 * Ideal para alunos implementarem passo a passo.
 *
 * Compilação: mpicc -o rvet rvet.c
 * Execução:   mpiexec -n 3 ./rvet
 */

#include <stdio.h>
#include <string.h>
#include <mpi.h>

/* Estrutura básica do relógio vetorial. */
typedef struct Clock {
    int p[3];
} Clock;

/*
 * Evento interno (sem comunicação).
 * Incrementa o contador local do processo.
 */
void Event(Clock *clock) {
    int pid;
    MPI_Comm_rank(MPI_COMM_WORLD, &pid);
    clock->p[pid]++;
}

/*
 * Envio de mensagem.
 * Deve:
 *   1. Obter o rank do processo.
 *   2. Incrementar o contador local (evento de envio).
 *   3. Enviar o vetor de relógio via MPI.
 */
void Send(Clock *clock /*, int dest */) {
    int pid;
    MPI_Comm_rank(MPI_COMM_WORLD, &pid);
    // TODO: incrementar clock local e enviar clock->p via MPI_Send
}

/*
 * Recebimento de mensagem.
 * Deve:
 *   1. Obter o rank do processo.
 *   2. Receber o vetor remoto via MPI_Recv.
 *   3. Incrementar o contador local (evento de recebimento).
 *   4. Fazer fusão (max elemento a elemento) com o vetor recebido.
 */
void Receive(Clock *clock /*, int src */) {
    int pid;
    MPI_Comm_rank(MPI_COMM_WORLD, &pid);
    // TODO: receber vetor e atualizar clock local
}

/*
 * Cada processo executa sua sequência conforme o diagrama da figura.
 * Use Event(), Send() e Receive() para construir a lógica.
 */

void process0() {
    Clock clock = {{0,0,0}};
    Event(&clock);
    printf("Process 0, Clock: (%d,%d,%d)\n", clock.p[0], clock.p[1], clock.p[2]);
    // TODO: enviar e receber conforme figura
}

void process1() {
    Clock clock = {{0,0,0}};
    printf("Process 1, Clock: (%d,%d,%d)\n", clock.p[0], clock.p[1], clock.p[2]);
    // TODO
}

void process2() {
    Clock clock = {{0,0,0}};
    printf("Process 2, Clock: (%d,%d,%d)\n", clock.p[0], clock.p[1], clock.p[2]);
    // TODO
}

int main(void) {
    int my_rank;

    MPI_Init(NULL, NULL);
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

    if (my_rank == 0)
        process0();
    else if (my_rank == 1)
        process1();
    else if (my_rank == 2)
        process2();

    MPI_Finalize();
    return 0;
}

