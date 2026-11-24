
#include <stdio.h>
#include <pthread.h>

void *display(void *arg)
{
    int num = *(int *)arg;
    printf("Thread %d is executing\n", num);
    return NULL;
}

int main()
{
    pthread_t t[3];
    int num[3] = {1, 2, 3};

    for(int i = 0; i < 3; i++)
        pthread_create(&t[i], NULL, display, &num[i]);

    for(int i = 0; i < 3; i++)
        pthread_join(t[i], NULL);
    printf("All threads have completed.\n");
    return 0;
}
