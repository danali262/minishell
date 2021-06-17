#include "pipes.h"
#include "../executor/executor.h"

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

void	create_pipeline(int **fd_for_pipeline)
{
	if (pipe(*fd_for_pipeline) != 0)
	{
		printf("Error creating pipe\n");
		exit(-1);
	}	
}
