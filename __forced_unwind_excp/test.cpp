#include <cstdlib>
#include <iostream>
#include <pthread.h>

static pthread_mutex_t m = PTHREAD_MUTEX_INITIALIZER;
static pthread_cond_t c = PTHREAD_COND_INITIALIZER;

static void *tf (void *)
{
    try {
        ::pthread_mutex_lock(&m);
        ::pthread_cond_wait (&c, &m);
    } catch (...) {
        // do something
    }
}

int main ()
{
    pthread_t th;
    ::pthread_create (&th, NULL, tf, NULL);
    // do some work; simulate using sleep
    std::cout << "Wait a bit" << std::endl;
    //sleep (1);
    // cancel the child thread
    ::pthread_cancel (th);
    // wait for it
    ::pthread_join (th, NULL);
    return 0;
}