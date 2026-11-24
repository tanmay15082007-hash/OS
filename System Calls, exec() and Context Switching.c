
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

int main()
{
    int pid, status;

    printf("Parent Process\n");
    printf("Parent PID: %d\n", getpid());
    printf("Parent PPID: %d\n", getppid());

    pid = fork();

    if(pid < 0)
    {
        printf("Fork failed\n");
        exit(1);
    }
    else if(pid == 0)
    {
        printf("\nChild Process\n");
        printf("Child PID before exec: %d\n", getpid());
        printf("Child PPID: %d\n", getppid());

        printf("Child is executing ls command\n");
        fflush(stdout);

        execlp("ls", "ls", "-l", NULL);

        printf("Exec failed\n");
        exit(1);
    }
    else
    {
        printf("\nParent is waiting for child...\n");

        wait(&status);

        printf("\nChild PID: %d\n", pid);

        if(WIFEXITED(status))
            printf("Child exit status: %d\n", WEXITSTATUS(status));
        else
            printf("Child terminated abnormally\n");

        printf("Parent process resumed.\n");
    }

    return 0;
}
