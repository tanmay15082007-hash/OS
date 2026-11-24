
#include <stdio.h>
#include <pthread.h>
#define MAX 20
struct Process
{
    int pid, bt, wt, tat;
};
struct Process p[MAX];
int n, turn = 0, elapsed = 0;
pthread_mutex_t mutex;
pthread_cond_t cond;
void *execute(void *arg)
{
    int i = *(int *)arg;
    pthread_mutex_lock(&mutex);
    while(turn != i)
        pthread_cond_wait(&cond, &mutex);
    p[i].wt = elapsed;
    p[i].tat = p[i].wt + p[i].bt;
    elapsed += p[i].bt;
    printf("Process P%d is executing\n", p[i].pid);
    turn++;
    pthread_cond_broadcast(&cond);
    pthread_mutex_unlock(&mutex);

    return NULL;
}
int main()
{
    pthread_t t[MAX];
    int id[MAX];
    float avgwt = 0, avgtat = 0;
    printf("Enter number of processes: ");
    scanf("%d", &n);
    if(n < 1 || n > MAX)
    {
        printf("Invalid number of processes\n");
        return 0;
    }
    for(int i = 0; i < n; i++)
    {
        p[i].pid = i + 1;
        printf("P%d Burst Time: ", i + 1);
        scanf("%d", &p[i].bt);
        if(p[i].bt < 0)
        {
            printf("Invalid burst time\n");
            return 0;
        }
    }
    pthread_mutex_init(&mutex, NULL);
    pthread_cond_init(&cond, NULL);
    for(int i = 0; i < n; i++)
    {
        id[i] = i;
        pthread_create(&t[i], NULL, execute, &id[i]);
    }
    for(int i = 0; i < n; i++)
        pthread_join(t[i], NULL);
    printf("\nPID\tBurst Time\tWaiting Time\tTurnaround Time\n");
    for(int i = 0; i < n; i++)
    {
        printf("P%d\t%d\t\t%d\t\t%d\n",
        p[i].pid, p[i].bt, p[i].wt, p[i].tat);
        avgwt += p[i].wt;
        avgtat += p[i].tat;
    }
    printf("\nAverage Waiting Time = %.2f\n", avgwt / n);
    printf("Average Turnaround Time = %.2f\n", avgtat / n);
    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&cond);
    return 0;
}
