#include "redirection.h"
#include "../executor/executor.h"
#include "libft.h"

#include <sys/errno.h>
#include <string.h>

int **create_pipes_fd_array(t_shell *shell)
{
	int	**pipes_fd;
	int	num;
	int	i;
	
	num = shell->redir->pipes_nbr;
	pipes_fd = (int **)malloc(sizeof(int *) * (num + 1));
	if (!pipes_fd)
		return (NULL);
		pipes_fd[num] = NULL;
	i = 0;
	while (i < num)
	{
		pipes_fd[i] = (int *)malloc(sizeof(int) * 2);
		if (!pipes_fd[i])
			return (NULL);
		i++;
	}
	return (pipes_fd);
}

int	handle_pipeline(t_treenode *node, t_shell *shell)
{
    int pid;
    int *pid_array;
	int status;
	int	**pipes_fd;
	int i;
	int pipes_num;

	shell->redir->stdoutfd = dup(STDOUT_FILENO);
	shell->redir->stdinfd = dup(STDIN_FILENO);
	pipes_num = shell->redir->pipes_nbr;
	pipes_fd = create_pipes_fd_array(shell);
	pid_array = (int *)malloc(sizeof(int) * pipes_num + 1);	
	if (!pid_array)
		return (ERROR);
	i = 0;
	while (i <= pipes_num)
	{
		if (i != pipes_num)
		{
			if (pipe(pipes_fd[i]) != 0)
			{
				printf("Error creating pipe\n");
				exit(-1);
			}	
		}
		pid = fork();
		pid_array[i] = pid;
		if (pid < 0)
		{
			restore_stdio(shell);
			printf("Error creating child process.\n\r");
			exit(errno);
		}
		if (pid == 0)
		{
			if (i != 0) // if not the first command
			{
				if (dup2(pipes_fd[i - 1][READ], STDIN_FILENO) < 0)//need -1 to reach the pipe in the pipes array, and it is always less by 1
				{
					printf("Error creating copy of file descriptor\n");
					shell->exit_code = errno;
					exit(shell->exit_code);
				}
				close(pipes_fd[i - 1][READ]); //closing fd of the first created pipe
				close(pipes_fd[i - 1][WRITE]); //closing fd of the first created pipe
			}
			if (i != pipes_num) // if not the last command
			{
				if (dup2(pipes_fd[i][WRITE], STDOUT_FILENO) < 0)
				{	
					printf("Error creating copy of file descriptor\n");
					shell->exit_code = errno;
					exit(shell->exit_code);
				}
				close(pipes_fd[i][READ]);
				close(pipes_fd[i][WRITE]);
			}
			if (i != pipes_num)
				node = node->left;
			if (run_simple_command(node, shell) == ERROR)
			{
				printf("minishell: %s\n\r", strerror(errno));
				shell->exit_code = 126;
			}
			exit(shell->exit_code);
		}
		else
		{
			if (i != 0)
			{
				close(pipes_fd[i - 1][READ]);
				close(pipes_fd[i - 1][WRITE]);
			}
		}
		i++;
		node = node->right;
	}
	int j = 0;
	while (j <= pipes_num)
	{
		waitpid(pid_array[j], &status, 0);
		if (WIFEXITED(status))
			shell->exit_code  = WEXITSTATUS(status);
		j++;
	}
	free_int_array_memory(pipes_fd);
	free(pid_array);
	return (SUCCESS);
}
