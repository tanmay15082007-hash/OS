
#include <stdio.h>

int main()
{
    int n, i;
    int bt[100], wt[100], tat[100];
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

        if(bt[i] < 0)
        {
            printf("Invalid burst time\n");
            return 0;
        }
    }

    wt[0] = 0;

    for(i = 1; i < n; i++)
    {
        wt[i] = wt[i - 1] + bt[i - 1];
    }

    for(i = 0; i < n; i++)
    {
        tat[i] = wt[i] + bt[i];
        total_wt += wt[i];
        total_tat += tat[i];
    }

    printf("\nPID\tBurst\tWaiting\tTurnaround\n");

    for(i = 0; i < n; i++)
    {
        printf("P%d\t%d\t%d\t%d\n",
        i + 1, bt[i], wt[i], tat[i]);
    }

    printf("\nAverage Waiting Time = %.2f\n", total_wt / n);
    printf("Average Turnaround Time = %.2f\n", total_tat / n);

    return 0;
}
