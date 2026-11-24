
#include <stdio.h>
#define MAX 10
int n, m;
int alloc[MAX][MAX], max[MAX][MAX], need[MAX][MAX], avail[MAX];
void calculateNeed()
{
    int i, j;
    for(i = 0; i < n; i++)
    {
        for(j = 0; j < m; j++)
            need[i][j] = max[i][j] - alloc[i][j];
    }
}
void display()
{
    int i, j;
    printf("\nAllocation Matrix:\n");
    for(i = 0; i < n; i++)
    {
        for(j = 0; j < m; j++)
            printf("%d ", alloc[i][j]);
        printf("\n");
    }
    printf("\nMaximum Matrix:\n");
    for(i = 0; i < n; i++)
    {
        for(j = 0; j < m; j++)
            printf("%d ", max[i][j]);
        printf("\n");
    }
    printf("\nNeed Matrix:\n");
    for(i = 0; i < n; i++)
    {
        for(j = 0; j < m; j++)
            printf("%d ", need[i][j]);
        printf("\n");
    }
    printf("\nAvailable Vector:\n");
    for(j = 0; j < m; j++)
        printf("%d ", avail[j]);
    printf("\n");
}
int safety(int sequence[])
{
    int work[MAX], finish[MAX] = {0};
    int i, j, count = 0, found;
    for(j = 0; j < m; j++)
        work[j] = avail[j];
    while(count < n)
    {
        found = 0;
        for(i = 0; i < n; i++)
        {
            if(finish[i] == 0)
            {
                for(j = 0; j < m; j++)
                {
                    if(need[i][j] > work[j])
                        break;
                }
                if(j == m)
                {
                    for(j = 0; j < m; j++)
                        work[j] += alloc[i][j];
                    sequence[count] = i;
                    count++;
                    finish[i] = 1;
                    found = 1;
                }
            }
        }
        if(found == 0)
            return 0;
    }
    return 1;
}
int main()
{
    int i, j, sequence[MAX];
    int request[MAX], p, safe;
    printf("Enter number of processes: ");
    scanf("%d", &n);
    printf("Enter number of resource types: ");
    scanf("%d", &m);
    if(n <= 0 || n > MAX || m <= 0 || m > MAX)
    {
        printf("Invalid input\n");
        return 0;
    }
    printf("Enter Allocation Matrix:\n");
    for(i = 0; i < n; i++)
    {
        for(j = 0; j < m; j++)
            scanf("%d", &alloc[i][j]);
    }
    printf("Enter Maximum Matrix:\n");
    for(i = 0; i < n; i++)
    {
        for(j = 0; j < m; j++)
            scanf("%d", &max[i][j]);
    }
    printf("Enter Available Vector:\n");
    for(j = 0; j < m; j++)
        scanf("%d", &avail[j]);
    calculateNeed();
    display();
    safe = safety(sequence);
    if(safe == 1)
    {
        printf("\nSystem is in SAFE state.\n");
        printf("Safe Sequence: ");
        for(i = 0; i < n; i++)
        {
            printf("P%d", sequence[i]);
            if(i != n-1)
                printf(" -> ");
        }
        printf("\n");
    }
    else
    {
        printf("\nSystem is in UNSAFE state.\n");
        return 0;
    }
    printf("\nEnter process number for resource request: ");
    scanf("%d", &p);
    if(p < 0 || p >= n)
    {
        printf("Invalid process number\n");
        return 0;
    }
    printf("Enter requested resources:\n");
    for(j = 0; j < m; j++)
        scanf("%d", &request[j]);
    for(j = 0; j < m; j++)
    {
        if(request[j] > need[p][j] || request[j] > avail[j] || request[j] < 0)
        {
            printf("Request cannot be granted.\n");
            return 0;
        }
    }
    for(j = 0; j < m; j++)
    {
        avail[j] -= request[j];
        alloc[p][j] += request[j];
        need[p][j] -= request[j];
    }
    printf("\nChecking safety after resource allocation...\n");
    display();
    safe = safety(sequence);
    if(safe == 1)
    {
        printf("\nRequest can be GRANTED.\n");
        printf("System is in SAFE state.\n");
        printf("Safe Sequence: ");
        for(i = 0; i < n; i++)
        {
            printf("P%d", sequence[i]);
            if(i != n-1)
                printf(" -> ");
        }
        printf("\n");
    }
    else
    {
        for(j = 0; j < m; j++)
        {
            avail[j] += request[j];
            alloc[p][j] -= request[j];
            need[p][j] += request[j];
        }
        printf("\nRequest cannot be granted.\n");
        printf("System would become UNSAFE.\n");
        printf("Allocation has been rolled back.\n");
    }
    return 0;
}
