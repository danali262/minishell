#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

/* We are executing ls -l in the child and waiting in the parent for the return value */

int	main(int argc, char *argv[], char *envp[])
{
	pid_t	child;	/* child pid returned by fork */
	char	*command[] = {"/bin/ls", "-l", NULL};	/* command and arguments */
	int		status;	/* captures the result of executing ls -l */

    child = fork();
    if (child == -1)
        write(1, "Problems\n", 9);
    if (child == 0)     /* in the child process */
    {
        if (execve(command[0], command, envp))  /* execve only returns if there is an error */
        {
            write(1, "Child problems\n", 15);
            return (-1);
        }
    }
    if (child > 0)
    {
        wait(&status);
        if (status == 0)
            write(1, "Success!\n", 9);
        else
            write(1, "Uhh...\n", 8);
    }
    return (status);
}