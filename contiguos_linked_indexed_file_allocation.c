
#include <stdio.h>

#define MAX 100

// CONTIGUOUS ALLOCATION
void contiguous(char name[][20], int size[], int files, int blocks)
{
    int disk[MAX] = {0};
    int i, j, k, start, found;

    printf("\n--- CONTIGUOUS ALLOCATION ---\n");

    for(i = 0; i < files; i++)
    {
        found = 0;

        for(j = 0; j <= blocks - size[i]; j++)
        {
            // Check consecutive free blocks
            for(k = j; k < j + size[i]; k++)
            {
                if(disk[k] == 1)
                    break;
            }

            if(k == j + size[i])
            {
                start = j;
                found = 1;
                break;
            }
        }

        if(found == 1)
        {
            printf("\nFile: %s\n", name[i]);
            printf("Allocated Blocks: ");

            for(j = start; j < start + size[i]; j++)
            {
                disk[j] = 1;
                printf("%d ", j);
            }
        }
        else
        {
            printf("\nFile %s: Allocation Not Possible", name[i]);
        }

        printf("\n");
    }
}

// LINKED ALLOCATION
void linked(char name[][20], int size[], int files, int blocks)
{
    int disk[MAX] = {0};
    int allocated[MAX];
    int i, j, count;

    printf("\n--- LINKED ALLOCATION ---\n");

    for(i = 0; i < files; i++)
    {
        count = 0;

        // Find free blocks
        for(j = 0; j < blocks && count < size[i]; j++)
        {
            if(disk[j] == 0)
            {
                allocated[count] = j;
                count++;
            }
        }

        if(count == size[i])
        {
            printf("\nFile: %s\n", name[i]);
            printf("Linked Blocks: ");

            for(j = 0; j < count; j++)
            {
                disk[allocated[j]] = 1;

                printf("%d", allocated[j]);

                if(j != count - 1)
                    printf(" -> ");
            }
        }
        else
        {
            printf("\nFile %s: Allocation Not Possible", name[i]);
        }

        printf("\n");
    }
}

// INDEXED ALLOCATION
void indexed(char name[][20], int size[], int files, int blocks)
{
    int disk[MAX] = {0};
    int data[MAX];
    int i, j, count, index;

    printf("\n--- INDEXED ALLOCATION ---\n");

    for(i = 0; i < files; i++)
    {
        count = 0;
        index = -1;

        // Find an index block
        for(j = 0; j < blocks; j++)
        {
            if(disk[j] == 0)
            {
                index = j;
                break;
            }
        }

        if(index != -1)
        {
            // Find data blocks
            for(j = 0; j < blocks && count < size[i]; j++)
            {
                if(disk[j] == 0 && j != index)
                {
                    data[count] = j;
                    count++;
                }
            }
        }

        if(index != -1 && count == size[i])
        {
            disk[index] = 1;

            printf("\nFile: %s\n", name[i]);
            printf("Index Block: %d\n", index);

            printf("Data Blocks: ");

            for(j = 0; j < count; j++)
            {
                disk[data[j]] = 1;
                printf("%d ", data[j]);
            }
        }
        else
        {
            printf("\nFile %s: Allocation Not Possible", name[i]);
        }

        printf("\n");
    }
}

// MAIN FUNCTION
int main()
{
    char name[MAX][20];
    int size[MAX];
    int files, blocks, i;

    printf("Enter total number of disk blocks: ");
    scanf("%d", &blocks);

    printf("Enter number of files: ");
    scanf("%d", &files);

    for(i = 0; i < files; i++)
    {
        printf("\nEnter file name: ");
        scanf("%19s", name[i]);

        printf("Enter file size (in blocks): ");
        scanf("%d", &size[i]);
    }

    contiguous(name, size, files, blocks);

    linked(name, size, files, blocks);

    indexed(name, size, files, blocks);

    return 0;
}
