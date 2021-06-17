#include "redirection.h"

#include <sys/errno.h>

void	close_both_pipe_ends(int **pipes_fd, int i)
{
	close(pipes_fd[i][READ]);
	close(pipes_fd[i][WRITE]);
}

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

bool	is_last_command(int i, int pipes_num)
{
	if (i == pipes_num)
		return (true);
	return (false);
}

bool	is_first_command(int i)
{
	if (i == 0)
		return (true);
	return (false);
}

void	create_copy_of_file_descriptor(int **pipes_fd, int index, int pipe_end, t_shell *shell)
{
	int	dup_result;
	int	newfd;

	newfd = 0;
	if (pipe_end == READ)
		newfd = STDIN_FILENO;
	else if (pipe_end == WRITE)
		newfd = STDOUT_FILENO;
		dup_result = dup2(pipes_fd[index][pipe_end], newfd);
	if (dup_result < 0)
	{
		printf("Error creating copy of file descriptor\n");
		shell->exit_code = errno;
		exit(shell->exit_code);
	}
}