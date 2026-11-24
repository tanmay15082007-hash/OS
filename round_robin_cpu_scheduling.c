
#include <stdio.h>

int main()
{
    int n, tq;
    int bt[100], rem[100], wt[100], tat[100];
    int i, time = 0, completed = 0;
    float total_wt = 0, total_tat = 0;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    if(n <= 0 || n > 100)
    {
        printf("Invalid number of processes\n");
        return 0;
    }

    printf("Enter burst time of each process:\n");

    for(i = 0; i < n; i++)
    {
        printf("P%d: ", i + 1);
        scanf("%d", &bt[i]);

        if(bt[i] <= 0)
        {
            printf("Invalid burst time\n");
            return 0;
        }

        rem[i] = bt[i];
    }

    printf("Enter time quantum: ");
    scanf("%d", &tq);

    if(tq <= 0)
    {
        printf("Invalid time quantum\n");
        return 0;
    }

    while(completed < n)
    {
        for(i = 0; i < n; i++)
        {
            if(rem[i] > 0)
            {
                if(rem[i] > tq)
                {
                    time += tq;
                    rem[i] -= tq;
                }
                else
                {
                    time += rem[i];
                    rem[i] = 0;
                    completed++;

                    tat[i] = time;
                    wt[i] = tat[i] - bt[i];
                }
            }
        }
    }

    printf("\nPID\tBurst\tWaiting\tTurnaround\n");

    for(i = 0; i < n; i++)
    {
        printf("P%d\t%d\t%d\t%d\n",
        i + 1, bt[i], wt[i], tat[i]);

        total_wt += wt[i];
        total_tat += tat[i];
    }

    printf("\nAverage Waiting Time = %.2f\n", total_wt / n);
    printf("Average Turnaround Time = %.2f\n", total_tat / n);

    return 0;
}
