
#include <stdio.h>

#define MAX 100

// FIRST FIT
void firstFit(int block[], int m, int process[], int n)
{
    int b[MAX], alloc[MAX];
    int i, j, total = 0;

    for(i = 0; i < m; i++)
        b[i] = block[i];

    for(i = 0; i < n; i++)
        alloc[i] = -1;

    printf("\n--- FIRST FIT ---\n");

    for(i = 0; i < n; i++)
    {
        for(j = 0; j < m; j++)
        {
            if(b[j] >= process[i])
            {
                alloc[i] = j;
                b[j] -= process[i];
                break;
            }
        }
    }

    printf("\nProcess\tSize\tBlock\n");

    for(i = 0; i < n; i++)
    {
        printf("P%d\t%d\t", i+1, process[i]);

        if(alloc[i] != -1)
            printf("Block %d\n", alloc[i]+1);
        else
            printf("Not Allocated\n");
    }

    printf("\nRemaining Memory:\n");

    for(i = 0; i < m; i++)
    {
        printf("Block %d: %d KB\n", i+1, b[i]);
        total += b[i];
    }

    printf("Total Unused Memory: %d KB\n", total);
}

// BEST FIT
void bestFit(int block[], int m, int process[], int n)
{
    int b[MAX], alloc[MAX];
    int i, j, best, total = 0;

    for(i = 0; i < m; i++)
        b[i] = block[i];

    for(i = 0; i < n; i++)
        alloc[i] = -1;

    printf("\n--- BEST FIT ---\n");

    for(i = 0; i < n; i++)
    {
        best = -1;

        for(j = 0; j < m; j++)
        {
            if(b[j] >= process[i])
            {
                if(best == -1 || b[j] < b[best])
                    best = j;
            }
        }

        if(best != -1)
        {
            alloc[i] = best;
            b[best] -= process[i];
        }
    }

    printf("\nProcess\tSize\tBlock\n");

    for(i = 0; i < n; i++)
    {
        printf("P%d\t%d\t", i+1, process[i]);

        if(alloc[i] != -1)
            printf("Block %d\n", alloc[i]+1);
        else
            printf("Not Allocated\n");
    }

    printf("\nRemaining Memory:\n");

    for(i = 0; i < m; i++)
    {
        printf("Block %d: %d KB\n", i+1, b[i]);
        total += b[i];
    }

    printf("Total Unused Memory: %d KB\n", total);
}

// WORST FIT
void worstFit(int block[], int m, int process[], int n)
{
    int b[MAX], alloc[MAX];
    int i, j, worst, total = 0;

    for(i = 0; i < m; i++)
        b[i] = block[i];

    for(i = 0; i < n; i++)
        alloc[i] = -1;

    printf("\n--- WORST FIT ---\n");

    for(i = 0; i < n; i++)
    {
        worst = -1;

        for(j = 0; j < m; j++)
        {
            if(b[j] >= process[i])
            {
                if(worst == -1 || b[j] > b[worst])
                    worst = j;
            }
        }

        if(worst != -1)
        {
            alloc[i] = worst;
            b[worst] -= process[i];
        }
    }

    printf("\nProcess\tSize\tBlock\n");

    for(i = 0; i < n; i++)
    {
        printf("P%d\t%d\t", i+1, process[i]);

        if(alloc[i] != -1)
            printf("Block %d\n", alloc[i]+1);
        else
            printf("Not Allocated\n");
    }

    printf("\nRemaining Memory:\n");

    for(i = 0; i < m; i++)
    {
        printf("Block %d: %d KB\n", i+1, b[i]);
        total += b[i];
    }

    printf("Total Unused Memory: %d KB\n", total);
}

// MAIN FUNCTION
int main()
{
    int block[MAX], process[MAX];
    int m, n, i;

    printf("Enter number of memory blocks: ");
    scanf("%d", &m);

    printf("Enter size of each memory block:\n");

    for(i = 0; i < m; i++)
        scanf("%d", &block[i]);

    printf("Enter number of processes: ");
    scanf("%d", &n);

    printf("Enter size of each process:\n");

    for(i = 0; i < n; i++)
        scanf("%d", &process[i]);

    firstFit(block, m, process, n);

    bestFit(block, m, process, n);

    worstFit(block, m, process, n);

    return 0;
}
