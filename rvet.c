/**
 * Template base para implementação de Relógios Vetoriais (MPI)
 * -------------------------------------------------------------
 * Implementar, tomando como base a sequência de operações da figura
 * do link: https://drive.google.com/file/d/1IOAJPpJWUoRC0kygZKr6ERe0hpIICRTP/view?usp=sharing
 *
 * Compilação: mpicc -o rvet rvet.c
 * Execução:   mpiexec -n 3 ./rvet
 */

#include <stdio.h>
#include <string.h>
#include <mpi.h>

/* Estrutura do relógio vetorial (3 processos). */
typedef struct Clock {
    int p[3];
} Clock;

/*
 * Imprime o estado atual do relógio vetorial.
 * Mostra: qual processo realizou a atualização e o vetor resultante.
 */
void PrintClock(const char *acao, Clock *clock) {
    int pid;
    MPI_Comm_rank(MPI_COMM_WORLD, &pid);
    printf("[Atualizado por P%d] %s -> Clock = (%d,%d,%d)\n",
           pid, acao, clock->p[0], clock->p[1], clock->p[2]);
}

/*
 * Evento interno (sem comunicação).
 * Incrementa o contador local do processo.
 */
void Event(Clock *clock) {
    int pid;
    MPI_Comm_rank(MPI_COMM_WORLD, &pid);
    clock->p[pid]++;
    
    // No final, imprime relógio atualizado
    PrintClock("Evento interno", clock);
}

/*
 * Envio de mensagem.
 * Deve:
 *   1. Obter o rank.
 *   2. Incrementar clock local (evento de envio).
 *   3. Enviar clock->p via MPI_Send.
 */
void Send(int dest, Clock *clock) {
    int pid;
    MPI_Comm_rank(MPI_COMM_WORLD, &pid);
    // TODO: incrementar clock local e enviar clock->p via MPI_Send
    
    // No final, imprime relógio atualizado:
    PrintClock("Envio de mensagem", clock);
}

/*
 * Recebimento de mensagem.
 * Deve:
 *   1. Obter o rank.
 *   2. Receber vetor remoto via MPI_Recv.
 *   3. Incrementar clock local (evento de recebimento).
 *   4. Fazer fusão (max elemento a elemento) com vetor recebido.
 */
void Receive(int src, Clock *clock) {
    int pid;
    MPI_Comm_rank(MPI_COMM_WORLD, &pid);
    // TODO: receber vetor e atualizar clock local
    
    // No final, imprime relógio atualizado
    PrintClock("Recebimento de mensagem", clock);
}

/*
 * Cada processo define sua sequência de eventos e comunicações
 * conforme o diagrama da figura de referência.
 */

void process0() {
    Clock clock = {{0,0,0}};
    PrintClock("Estado inicial", &clock);

    Event(&clock);
    // TODO: Send/Receive conforme diagrama
}

void process1() {
    Clock clock = {{0,0,0}};
    PrintClock("Estado inicial", &clock);
    // TODO
}

void process2() {
    Clock clock = {{0,0,0}};
    PrintClock("Estado inicial", &clock);
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

