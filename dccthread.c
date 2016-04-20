#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <ucontext.h>
#include "dccthread.h"



void dccthread_init(void (*func)(int), int param){
	
	//inciar fila de prontos e fila de espera
	

	//verificar a funcao passada por parametro
	principal = dccthread_create("principal", f1, 0);
	gerente = dccthread_create("gerente", f1, 0);
}


dccthread_t * dccthread_create(const char *name, void (*func)(int ), int param){

	return 0; 

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
