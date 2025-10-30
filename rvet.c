/**
 * Template base para implementação de Relógios Vetoriais (MPI)
 * -------------------------------------------------------------
 * Objetivo: servir como ponto de partida para alunos implementarem a lógica
 * ilustrada na figura:
 * https://people.cs.rutgers.edu/~pxk/417/notes/images/clocks-vector.png
 *
 * Compilação: mpicc -o rvet rvet.c
 * Execução:   mpiexec -n 3 ./rvet
 */

#include <stdio.h>
#include <string.h>
#include <mpi.h>

/* 
 * Estrutura do relógio vetorial.
 * Cada processo mantém um vetor com o tempo lógico de todos os processos.
 * Exemplo: clock.p[0] representa a visão do tempo do processo 0.
 */
typedef struct Clock {
    int p[3];
} Clock;

/*
 * Função que representa um evento interno (sem comunicação).
 * Deve: incrementar o contador local.
 */
void Event(int pid, Clock *clock) {
    clock->p[pid]++;
}

/*
 * Função de envio de mensagem.
 * Deve: 
 *   - incrementar o contador local (evento de envio);
 *   - enviar o vetor de relógio via MPI para outro processo.
 */
void Send(int pid, Clock *clock, int dest) {
    // TODO: incrementar clock local e enviar clock->p via MPI_Send
}

/*
 * Função de recebimento de mensagem.
 * Deve:
 *   - receber o vetor de outro processo via MPI_Recv;
 *   - incrementar o contador local (evento de recebimento);
 *   - atualizar o vetor local fazendo max(elemento a elemento).
 */
void Receive(int pid, Clock *clock, int src) {
    // TODO: receber vetor e fazer fusão com o relógio local
}

/*
 * Processo de rank 0.
 * Deve implementar a sequência de eventos e comunicações conforme o diagrama.
 */
void process0() {
    Clock clock = {{0,0,0}};

    // Exemplo de evento interno
    Event(0, &clock);
    printf("Process 0, Clock: (%d,%d,%d)\n", clock.p[0], clock.p[1], clock.p[2]);

    // TODO: chamadas Send() / Receive() conforme sequência da figura
}

/*
 * Processo de rank 1.
 * Deve implementar sua sequência de eventos e trocas com P0 e P2.
 */
void process1() {
    Clock clock = {{0,0,0}};
    printf("Process 1, Clock: (%d,%d,%d)\n", clock.p[0], clock.p[1], clock.p[2]);

    // TODO
}

/*
 * Processo de rank 2.
 * Deve implementar sua sequência de eventos e possíveis eventos internos.
 */
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
