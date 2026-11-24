#include <stdio.h>
#include <pthread.h>
#define THREADS 3
#define OPERATIONS 1000000
int count = 0;
pthread_mutex_t mutex;
void *withoutMutex(void *arg)
{
    for(int i = 0; i < OPERATIONS; i++)
        count++;
    return NULL;
}
void *withMutex(void *arg)
{
    for(int i = 0; i < OPERATIONS; i++)
    {
        pthread_mutex_lock(&mutex);
        count++;
        pthread_mutex_unlock(&mutex);
    }
    return NULL;
}
int main()
{
    pthread_t t[THREADS];
    int expected = THREADS * OPERATIONS;
    printf("Number of threads: %d\n", THREADS);
    printf("Operations per thread: %d\n", OPERATIONS);
    printf("Expected final value: %d\n", expected);
    count = 0;
    for(int i = 0; i < THREADS; i++)
        pthread_create(&t[i], NULL, withoutMutex, NULL);
    for(int i = 0; i < THREADS; i++)
        pthread_join(t[i], NULL);
    printf("\nActual value without mutex: %d\n", count);
    count = 0;
    pthread_mutex_init(&mutex, NULL);
    for(int i = 0; i < THREADS; i++)
        pthread_create(&t[i], NULL, withMutex, NULL);
    for(int i = 0; i < THREADS; i++)
        pthread_join(t[i], NULL);
    printf("Actual value with mutex: %d\n", count);
    pthread_mutex_destroy(&mutex);
    return 0;
}
