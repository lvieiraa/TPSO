#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <ucontext.h>
#include "dccthread.h"
#include <signal.h>

#define TAM 400 //tamanho maximo da fila de threads
#define handle_error(msg) \
           do { perror(msg); exit(EXIT_FAILURE); } while (0) //mensagem de erro copiado do man da funcaos da biblioteca ucontext.h
//inciar fila de prontos e fila de espera
dccthread_t * fila[TAM];
int atual = 0; 
int ultimo = 0;

ucontext_t gerente, principal;

void iniciarContexto(ucontext_t *contexto)
{
  contexto->uc_stack.ss_sp = malloc(SIGSTKSZ); //SIGSTKSZ definido na biblioteca signal.h  tamanho do sinal 
  contexto->uc_stack.ss_size = SIGSTKSZ;
  contexto->uc_stack.ss_flags = 0;
}


void dccthread_init(void (*func)(int), int param){
	
	
	if (getcontext(&gerente) == -1) //inicia  a struct gerente 
	handle_error("getcontext");
	iniciarContexto(&gerente);//inicia a pilha, preenchendo  os campos necessarios da uc_stack 
	makecontext(&gerente, gerenciador, 0); //passa a funcao "gerenciador" que gerencia as threads para a thread gerente
	dccthread_create("principal", func, param);

	/*//verificar a funcao passada por parametro
	principal = dccthread_create("principal", f1, 0);
	gerente = dccthread_create("gerente", f1, 0);*/
}


dccthread_t * dccthread_create(const char *name, void (*func)(int ), int param){
fila[ultimo] = (dccthread_t *) malloc (sizeof(dccthread_t *));
getcontext(fila[ultimo]->estado);
fila[ultimo]->estado.uc_link = &gerente;
iniciarContexto(fila[ultimo]->estado);
makecontext(fila[ultimo]->estado, (void(*) (void)) func, 1, param);

dccthread_t *saida = fila[ultimo];
ultimo ++;
ultimo = ultimo % TAM;//limita a fila ao tamanha maximo da constante TAM
return saida;
}



/*void f1(int dummy)
{
    dccthread_t *tid = dccthread_self();
    char *name = dccthread_name(tid);
	int i = 0;
    for(i = 0; i < 3; i++) {
        printf("thread %s on iteration %d\n", name, i);
        dccthread_yield();
    }
}

void test1(int dummy) {
    dccthread_t *tid1 = dccthread_create("t1", f1, 0);
    dccthread_t *tid2 = dccthread_create("t2", f1, 0);
    dccthread_t *tid3 = dccthread_create("t3", f1, 0);
	int i = 0;
    for(i = 0; i < 10; i++) {
        printf("test1 yielding\n");
        dccthread_yield();
    }
    exit(EXIT_SUCCESS);
}*/

int main(int argc, char **argv)
{
	return 0;
    //dccthread_init(test1, 0);
}
