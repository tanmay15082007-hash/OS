
#include <stdio.h>

int main()
{
    int n;
    int i, j;
    int pid[100];
    int burst[100];
    int waiting[100];
    int turnaround[100];
    int temp;
    float total_waiting = 0;
    float total_turnaround = 0;

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    if(n <= 0 || n > 100)
    {
        printf("Invalid number of processes\n");
        return 0;
    }

    printf("\nEnter the burst time of each process:\n");

    for(i = 0; i < n; i++)
    {
        pid[i] = i + 1;
        printf("P%d: ", pid[i]);
        scanf("%d", &burst[i]);

        if(burst[i] < 0)
        {
            printf("Invalid burst time\n");
            return 0;
        }
    }

    for(i = 0; i < n - 1; i++)
    {
        for(j = i + 1; j < n; j++)
        {
            if(burst[i] > burst[j])
            {
                temp = burst[i];
                burst[i] = burst[j];
                burst[j] = temp;

                temp = pid[i];
                pid[i] = pid[j];
                pid[j] = temp;
            }
        }
    }

    waiting[0] = 0;

    for(i = 1; i < n; i++)
    {
        waiting[i] = waiting[i - 1] + burst[i - 1];
    }

    for(i = 0; i < n; i++)
    {
        turnaround[i] = waiting[i] + burst[i];
        total_waiting += waiting[i];
        total_turnaround += turnaround[i];
    }

    printf("\n------------------------------------------------");
    printf("\nProcess\tBurst\tWaiting\tTurnaround");
    printf("\n------------------------------------------------");

    for(i = 0; i < n; i++)
    {
        printf("\nP%d\t%d\t%d\t%d",
        pid[i],
        burst[i],
        waiting[i],
        turnaround[i]);
    }

    printf("\n------------------------------------------------");
    printf("\nAverage Waiting Time : %.2f", total_waiting / n);
    printf("\nAverage Turnaround Time : %.2f\n", total_turnaround / n);

    return 0;
}
