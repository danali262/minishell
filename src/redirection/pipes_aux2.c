#include "pipes.h"

#include <sys/errno.h>

void	create_copy_of_fd_for_pipes(int **pipes_fd, int index, int pipe_end,
		t_shell *shell)
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
