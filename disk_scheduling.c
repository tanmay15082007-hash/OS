
#include <stdio.h>

// Calculate positive difference
int difference(int a, int b)
{
    if(a > b)
        return a - b;
    else
        return b - a;
}

// FCFS Algorithm
void FCFS(int a[], int n, int head)
{
    int i, total = 0, current = head;

    printf("\nFCFS:\n");
    printf("Service Sequence: ");

    for(i = 0; i < n; i++)
    {
        printf("%d", a[i]);

        total += difference(current, a[i]);
        current = a[i];

        if(i != n-1)
            printf(" -> ");
    }

    printf("\nTotal Head Movement: %d\n", total);
}

// SSTF Algorithm
void SSTF(int a[], int n, int head)
{
    int visited[100] = {0};
    int i, j, min, pos;
    int current = head, total = 0;

    printf("\nSSTF:\n");
    printf("Service Sequence: ");

    for(i = 0; i < n; i++)
    {
        min = 999999;
        pos = -1;

        for(j = 0; j < n; j++)
        {
            if(visited[j] == 0 &&
               difference(current, a[j]) < min)
            {
                min = difference(current, a[j]);
                pos = j;
            }
        }

        visited[pos] = 1;

        printf("%d", a[pos]);

        total += difference(current, a[pos]);
        current = a[pos];

        if(i != n-1)
            printf(" -> ");
    }

    printf("\nTotal Head Movement: %d\n", total);
}

// Sorting Function
void sort(int a[], int n)
{
    int i, j, temp;

    for(i = 0; i < n-1; i++)
    {
        for(j = 0; j < n-i-1; j++)
        {
            if(a[j] > a[j+1])
            {
                temp = a[j];
                a[j] = a[j+1];
                a[j+1] = temp;
            }
        }
    }
}

// SCAN Algorithm
void SCAN(int a[], int n, int head, int max, char dir)
{
    int b[100], i;
    int current = head, total = 0;

    for(i = 0; i < n; i++)
        b[i] = a[i];

    sort(b, n);

    printf("\nSCAN:\n");
    printf("Service Sequence: ");

    if(dir == 'R' || dir == 'r')
    {
        for(i = 0; i < n; i++)
        {
            if(b[i] >= head)
            {
                printf("%d -> ", b[i]);
                total += difference(current, b[i]);
                current = b[i];
            }
        }

        total += difference(current, max-1);
        current = max-1;

        for(i = n-1; i >= 0; i--)
        {
            if(b[i] < head)
            {
                printf("%d", b[i]);
                total += difference(current, b[i]);
                current = b[i];

                if(i > 0)
                    printf(" -> ");
            }
        }
    }
    else
    {
        for(i = n-1; i >= 0; i--)
        {
            if(b[i] <= head)
            {
                printf("%d -> ", b[i]);
                total += difference(current, b[i]);
                current = b[i];
            }
        }

        total += current;
        current = 0;

        for(i = 0; i < n; i++)
        {
            if(b[i] > head)
            {
                printf("%d", b[i]);
                total += difference(current, b[i]);
                current = b[i];

                if(i < n-1)
                    printf(" -> ");
            }
        }
    }

    printf("\nTotal Head Movement: %d\n", total);
}

// C-SCAN Algorithm
void CSCAN(int a[], int n, int head, int max, char dir)
{
    int b[100], i;
    int current = head, total = 0;

    for(i = 0; i < n; i++)
        b[i] = a[i];

    sort(b, n);

    printf("\nC-SCAN:\n");
    printf("Service Sequence: ");

    if(dir == 'R' || dir == 'r')
    {
        for(i = 0; i < n; i++)
        {
            if(b[i] >= head)
            {
                printf("%d -> ", b[i]);
                total += difference(current, b[i]);
                current = b[i];
            }
        }

        total += difference(current, max-1);
        total += max-1;
        current = 0;

        for(i = 0; i < n; i++)
        {
            if(b[i] < head)
            {
                printf("%d", b[i]);
                total += difference(current, b[i]);
                current = b[i];

                if(i < n-1)
                    printf(" -> ");
            }
        }
    }
    else
    {
        for(i = n-1; i >= 0; i--)
        {
            if(b[i] <= head)
            {
                printf("%d -> ", b[i]);
                total += difference(current, b[i]);
                current = b[i];
            }
        }

        total += current;
        total += max-1;
        current = max-1;

        for(i = n-1; i >= 0; i--)
        {
            if(b[i] > head)
            {
                printf("%d", b[i]);
                total += difference(current, b[i]);
                current = b[i];

                if(i > 0)
                    printf(" -> ");
            }
        }
    }

    printf("\nTotal Head Movement: %d\n", total);
}

// Main Function
int main()
{
    int a[100], n, head, cylinders, i;
    char dir;

    printf("Enter number of disk requests: ");
    scanf("%d", &n);

    printf("Enter disk request queue:\n");

    for(i = 0; i < n; i++)
        scanf("%d", &a[i]);

    printf("Enter initial head position: ");
    scanf("%d", &head);

    printf("Enter total number of cylinders: ");
    scanf("%d", &cylinders);

    printf("Enter direction (L/R): ");
    scanf(" %c", &dir);

    printf("\nInitial Head Position: %d\n", head);

    FCFS(a, n, head);
    SSTF(a, n, head);
    SCAN(a, n, head, cylinders, dir);
    CSCAN(a, n, head, cylinders, dir);

    return 0;
}
