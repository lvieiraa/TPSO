#include <stdlib.h>
#include <stdio.h>
#include "dccthread.h"

void f2(int dummy) {
    for(unsigned long long i = 0; i < 100000000ULL; i++) {
        dccthread_yield();
    }
    dccthread_exit();
}

void test2(int dummy) {
  int i=0;
  for(i = 0; i < 5; i++)
  {
    dccthread_t *t1 = dccthread_create("t1", f2, 0);
    dccthread_t *t2 = dccthread_create("t2", f2, 0);
    dccthread_wait(t1);
    dccthread_wait(t2);
  }
  dccthread_exit();
}


int main(int argc, char **argv)
{
  dccthread_init(test4, 0);
}
