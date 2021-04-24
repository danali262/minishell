#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <stdlib.h>

int     main(int argc, char *argv[], char *envp[])
{
    pid_t   child;
    char    *command[16], *tok, *lineptr = NULL;	/* not going to use commands with more than 15 words */
    size_t  i;
    size_t  n;
	int		status;

	while (1)
	{
		printf("$ ");
		if (getline(&lineptr, &n, stdin) == -1)
			break;
		tok = strtok(lineptr, " \t\n\r");	/* get the first token */
		i = 0;
		while (i < 16 && tok != NULL)
		{
			command[i] = tok;
			tok = strtok(NULL, " \t\n\r");	/* not sure what this does, but it's used to get the other tokens */
			i++;
		}
		command[i] = NULL;

		child = fork ();
		if (child == 0)
		{
			if (execve(command[0], command, envp))
			{
				perror("execve");
				exit(EXIT_FAILURE);
			}
		}
		if (child > 0)
			wait(&status);
		putchar('\n');
		free(lineptr);
		exit(status);
	}
}