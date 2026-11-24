
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

int main()
{
    int pid, status, sum = 0;

    printf("Original Process PID: %d\n", getpid());
    printf("Original Process PPID: %d\n", getppid());

    pid = fork();

    if(pid < 0)
    {
        printf("Process creation failed\n");
        exit(1);
    }
    else if(pid == 0)
    {
        printf("\nChild Process\n");
        printf("Child PID: %d\n", getpid());
        printf("Child PPID: %d\n", getppid());

        for(int i = 1; i <= 10; i++)
            sum += i;

        printf("Sum of numbers from 1 to 10 = %d\n", sum);

        exit(0);
    }
    else
    {
        printf("\nParent Process\n");
        printf("Parent PID: %d\n", getpid());
        printf("Child PID: %d\n", pid);

        printf("Parent is waiting for child...\n");

        wait(&status);

        if(WIFEXITED(status))
            printf("Child terminated with status: %d\n", WEXITSTATUS(status));

        printf("Child process completed.\n");
    }

    return 0;
}
