#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <ucontext.h>
#include "dccthread.h"
#include <signal.h>

#define MEM 64000
#define TAM 400 //tamanho maximo da fila de threads
#define handle_error(msg) \
           do { perror(msg); exit(EXIT_FAILURE); } while (0) //mensagem de erro copiado do man da funcaos da biblioteca ucontext.h
//inciar fila de prontos e fila de espera
/*
struct sigevent timerEvent;
struct sigaction timerAtua, timeAtuaAnt;
struct itimerspec tempoX;
timer_t timer;
sig_atomic_t gerenteAtua;
*/
dccthread_t * fila[TAM];
int atual = 0; 
int ultimo = 0;

ucontext_t gerente, principal;

dccthread_t * dccthread_self(void)
{
  // Return the running thread.
  return fila[ultimo];
}

void dccthread_yield(void){

printf("Tem que implementar yield\n");
}

void gerenciador(void) {
printf("tem que implementar o gerenciador!\n");
//setcontext(&(fila[ultimo]->estado));
} 

const char *dccthread_name(dccthread_t *tid)
{
  return tid->tid;
} 

void iniciarContexto(ucontext_t *contexto)
{
  contexto->uc_stack.ss_sp = malloc(MEM);
  contexto->uc_stack.ss_size = MEM;
  contexto->uc_stack.ss_flags = 0;
}


void dccthread_init(void (*func)(int), int param){
	
	
 atual = 0;
    ultimo = 0;
	if (getcontext(&gerente) == -1) //inicia  a struct gerente 
	handle_error("getcontext");
	gerente.uc_link = &principal;
	iniciarContexto(&gerente);//inicia a pilha, preenchendo  os campos necessarios da uc_stack 
	iniciarContexto(&principal);	
	makecontext(&gerente, gerenciador, 0); //passa a funcao "gerenciador" que gerencia as threads para a thread gerente
	dccthread_create("principal", func, param);
	printf("debug\n");
	//swapcontext(&principal, &gerente);
	printf("%d\n",ultimo);
	swapcontext(&principal, &fila[ultimo-1]->estado);

	
	

	
exit(0); //exit(0) para parar de dar warning de falha de retorno

	/*//verificar a funcao passada por parametro
	principal = dccthread_create("principal", f1, 0);
	gerente = dccthread_create("gerente", f1, 0);*/
}


dccthread_t * dccthread_create(const char *name, void (*func)(int ), int param){
fila[ultimo] = (dccthread_t *) malloc(sizeof(dccthread_t *));	


//printf("%d\n", aux->uc_sigmask); 
getcontext(&(fila[ultimo]-> estado));
fila[ultimo]-> estado.uc_link = &gerente; 
iniciarContexto(&(fila[ultimo]-> estado)); 
printf("criada a thread: %d\n", ultimo);

makecontext(&(fila[ultimo]-> estado), (void (*)(void)) func, 1, param);
if (ultimo != 0 )
swapcontext(&fila[ultimo-1]->estado, &fila[ultimo]->estado );

dccthread_t *retorno = fila[ultimo];
ultimo ++;
ultimo = ultimo % TAM;//limita a fila ao tamanha maximo da constante TAM
return retorno;
}
