
#include <stdio.h>
#define MAX 100
void FIFO(int pages[], int n, int f)
{
    int frame[MAX], i, j, k = 0, faults = 0, hits = 0, found;
    for(i = 0; i < f; i++)
        frame[i] = -1;
    printf("\nFIFO:\n");
    printf("Page\t");
    for(i = 0; i < f; i++)
        printf("F%d\t", i+1);
    printf("Status\n");
    for(i = 0; i < n; i++)
    {
        found = 0;
        for(j = 0; j < f; j++)
        {
            if(frame[j] == pages[i])
            {
                found = 1;
                break;
            }
        }
        if(found == 1)
        {
            hits++;
            printf("%d\t", pages[i]);
        }
        else
        {
            frame[k] = pages[i];
            k = (k + 1) % f;
            faults++;
            printf("%d\t", pages[i]);
        }
        for(j = 0; j < f; j++)
        {
            if(frame[j] == -1)
                printf("-\t");
            else
                printf("%d\t", frame[j]);
        }
        if(found == 1)
            printf("Hit\n");
        else
            printf("Fault\n");
    }
    printf("Total Page Faults: %d\n", faults);
    printf("Total Page Hits: %d\n", hits);
    printf("Page Fault Ratio: %.2f\n", (float)faults/n);
    printf("Page Hit Ratio: %.2f\n", (float)hits/n);
}
void LRU(int pages[], int n, int f)
{
    int frame[MAX], time[MAX];
    int i, j, pos, faults = 0, hits = 0, found;
    for(i = 0; i < f; i++)
    {
        frame[i] = -1;
        time[i] = 0;
    }
    printf("\nLRU:\n");
    printf("Page\t");
    for(i = 0; i < f; i++)
        printf("F%d\t", i+1);
    printf("Status\n");
    for(i = 0; i < n; i++)
    {
        found = 0;
        for(j = 0; j < f; j++)
        {
            if(frame[j] == pages[i])
            {
                found = 1;
                time[j] = i;
                break;
            }
        }
        if(found == 0)
        {
            pos = -1;
            for(j = 0; j < f; j++)
            {
                if(frame[j] == -1)
                {
                    pos = j;
                    break;
                }
            }
            if(pos == -1)
            {
                pos = 0;
                for(j = 1; j < f; j++)
                {
                    if(time[j] < time[pos])
                        pos = j;
                }
            }
            frame[pos] = pages[i];
            time[pos] = i;
            faults++;
        }
        else
            hits++;
        printf("%d\t", pages[i]);
        for(j = 0; j < f; j++)
        {
            if(frame[j] == -1)
                printf("-\t");
            else
                printf("%d\t", frame[j]);
        }
        if(found == 1)
            printf("Hit\n");
        else
            printf("Fault\n");
    }
    printf("Total Page Faults: %d\n", faults);
    printf("Total Page Hits: %d\n", hits);
    printf("Page Fault Ratio: %.2f\n", (float)faults/n);
    printf("Page Hit Ratio: %.2f\n", (float)hits/n);
}
void Optimal(int pages[], int n, int f)
{
    int frame[MAX];
    int i, j, k, pos, farthest, faults = 0, hits = 0, found;
    for(i = 0; i < f; i++)
        frame[i] = -1;
    printf("\nOPTIMAL:\n");
    printf("Page\t");
    for(i = 0; i < f; i++)
        printf("F%d\t", i+1);
    printf("Status\n");
    for(i = 0; i < n; i++)
    {
        found = 0;
        for(j = 0; j < f; j++)
        {
            if(frame[j] == pages[i])
            {
                found = 1;
                break;
            }
        }
        if(found == 0)
        {
            pos = -1;
            for(j = 0; j < f; j++)
            {
                if(frame[j] == -1)
                {
                    pos = j;
                    break;
                }
            }
            if(pos == -1)
            {
                farthest = -1;
                pos = 0;
                for(j = 0; j < f; j++)
                {
                    for(k = i+1; k < n; k++)
                    {
                        if(frame[j] == pages[k])
                            break;
                    }
                    if(k == n)
                    {
                        pos = j;
                        break;
                    }
                    if(k > farthest)
                    {
                        farthest = k;
                        pos = j;
                    }
                }
            }
            frame[pos] = pages[i];
            faults++;
        }
        else
            hits++;
        printf("%d\t", pages[i]);
        for(j = 0; j < f; j++)
        {
            if(frame[j] == -1)
                printf("-\t");
            else
                printf("%d\t", frame[j]);
        }
        if(found == 1)
            printf("Hit\n");
        else
            printf("Fault\n");
    }
    printf("Total Page Faults: %d\n", faults);
    printf("Total Page Hits: %d\n", hits);
    printf("Page Fault Ratio: %.2f\n", (float)faults/n);
    printf("Page Hit Ratio: %.2f\n", (float)hits/n);
}
int main()
{
    int pages[MAX], n, f, i;
    printf("Enter number of pages: ");
    scanf("%d", &n);
    printf("Enter page reference string:\n");
    for(i = 0; i < n; i++)
        scanf("%d", &pages[i]);
    printf("Enter number of frames: ");
    scanf("%d", &f);
    if(n <= 0 || n > MAX || f <= 0 || f > MAX)
    {
        printf("Invalid input\n");
        return 0;
    }
    FIFO(pages, n, f);
    LRU(pages, n, f);
    Optimal(pages, n, f);
    return 0;
}
