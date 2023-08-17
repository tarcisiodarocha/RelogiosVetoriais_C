/**
 * Código base (incompleto) para implementação de relógios vetoriais.
 * Meta: implementar a interação entre três processos ilustrada na figura
 * da URL: 
 * 
 * https://people.cs.rutgers.edu/~pxk/417/notes/images/clocks-vector.png
 * 
 * Compilação: mpicc -o rvet rvet.c
 * Execução:   mpiexec -n 3 ./rvet
 */
 
#include <stdio.h>
#include <string.h>  
#include <mpi.h>     


typedef struct Clock { 
   int p[3];
} Clock;


void printClock(Clock *clock, int processo) {
   printf("Process: %d, Clock: (%d, %d, %d)\n", processo, clock->p[0], clock->p[1], clock->p[2]);
}

void Event(int pid, Clock *clock){
   clock->p[pid]++;   
}


void Send(int origem, int destino, Clock *clock){
   // TO DO
   int pid_enviado = clock->p[origem];
   MPI_Send(&pid_enviado, 1, MPI_INT, destino, origem, MPI_COMM_WORLD);
}




void Receive(int origem, Clock *clock){
   // TO DO
   int pid_recebido;
   MPI_Recv(&pid_recebido, 1,  MPI_INT, origem, origem, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
   Event(pid_recebido, clock);
}



// Representa o processo de rank 0
void process0(){
   Clock clock = {{0,0,0}};
   
   Event(0, &clock);
   printClock(&clock, 0);
   
   Event(0, &clock);
   Send(0, 1, &clock);
   printClock(&clock, 0);
   
   Event(0, &clock);
   Receive(1, &clock);
   printClock(&clock, 0);
   
   Event(0, &clock);
   Send(0, 2, &clock);
   printClock(&clock, 0);
   
   Event(0, &clock);
   Receive(2, &clock);
   printClock(&clock, 0);
   
   Event(0, &clock);
   Send(0, 1, &clock);
   printClock(&clock, 0);
   
   Event(0, &clock);
   printClock(&clock, 0);
   
}

// Representa o processo de rank 1
void process1(){
   Clock clock = {{0,0,0}};

   Event(1, &clock);
   Send(1, 0, &clock);
   printClock(&clock, 1);

   Event(1, &clock);
   Receive(0, &clock);
   printClock(&clock, 1);
   
   Event(1, &clock);
   Receive(0, &clock);
   printClock(&clock, 1);
   
   

}

// Representa o processo de rank 2
void process2(){
   Clock clock = {{0,0,0}};

   Event(2, &clock);
   printClock(&clock, 2);
   
   Event(2, &clock);
   Send(2, 0, &clock);
   printClock(&clock, 2);
   
   Event(2, &clock);
   Receive(0, &clock);
   printClock(&clock, 2);   
}

int main(void) {
   int my_rank;               

   MPI_Init(NULL, NULL); 
   MPI_Comm_rank(MPI_COMM_WORLD, &my_rank); 

   if (my_rank == 0) { 
      process0();
   } else if (my_rank == 1) {  
      process1();
   } else if (my_rank == 2) {  
      process2();
   }

   /* Finaliza MPI */
   MPI_Finalize(); 

   return 0;
}  /* main */
