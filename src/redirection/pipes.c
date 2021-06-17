#include "redirection.h"
#include "../executor/executor.h"
#include "libft.h"

#include <sys/errno.h>
#include <string.h>

void	handle_child_process(t_treenode *node, int **pipes_fd, int i, t_shell *shell)
{
	int pipes_num;

	pipes_num = shell->redir->pipes_nbr;
	if (!is_first_command(i))
	{
		create_copy_of_file_descriptor(pipes_fd, i - 1, READ, shell); //need -1 to reach the pipe in the pipes array, and it is always less by 1
		close_both_pipe_ends(pipes_fd, i - 1);
	}
	if (!is_last_command(i, pipes_num))
	{
		create_copy_of_file_descriptor(pipes_fd, i, WRITE, shell); 
		close_both_pipe_ends(pipes_fd, i);
		node = node->left;
	}
	if (run_simple_command(node, shell) == ERROR)
	{
		printf("minishell: %s\n\r", strerror(errno));
		shell->exit_code = 126;
	}
	exit(shell->exit_code);
}

pid_t	*loop_through_pipes(t_treenode *node, int **pipes_fd, t_shell *shell)
{
	int		pipes_num;
    pid_t	*pid_array;
    pid_t	pid;
	int 	i;

	pipes_num = shell->redir->pipes_nbr;
	pid_array = (int *)malloc(sizeof(int) * pipes_num + 1);	
	if (!pid_array)
		return (NULL);
	i = 0;
	while (i <= pipes_num)
	{
		if (!is_last_command(i, pipes_num))
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
			handle_child_process(node, pipes_fd, i, shell);
		else
		{
			if (!is_first_command(i))
				close_both_pipe_ends(pipes_fd, i - 1);
		}
		i++;
		node = node->right;
	}
	return (pid_array);
}

int	handle_pipeline(t_treenode *node, t_shell *shell)
{
    pid_t *pid_array;
	int	**pipes_fd;
	int pipes_num;
	int i;

	shell->redir->stdoutfd = dup(STDOUT_FILENO);
	shell->redir->stdinfd = dup(STDIN_FILENO);
	pipes_num = shell->redir->pipes_nbr;
	pipes_fd = create_pipes_fd_array(shell);
	pid_array = loop_through_pipes(node, pipes_fd, shell);
	if (pid_array == NULL)
		return (ERROR);
	i = 0;
	while (i <= pipes_num)
	{
		wait_for_child(pid_array[i],shell);
		i++;
	}
	free_int_array_memory(pipes_fd);
	free(pid_array);
	return (SUCCESS);
}
