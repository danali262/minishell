#include "command_line_state.h"
#include "read_command_line.h"

#include "libft.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int	init_command_line(t_line *cmd_line)
{
	int i;

	i = 0;
	cmd_line->buf = ft_calloc(BUF_SIZE + 1, 1);
	if (cmd_line->buf == NULL)
	{
		ft_putstr_fd("Error. Unable to allocate memory.\n", STDOUT_FILENO);
		return (0);
	}
	return (1);
}

void	clear_command_line(t_line *cmd_line)
{
	cmd_line->buf[0] = '\0';
	cmd_line->size = 0;
}

void	free_command_line(t_line *cmd_line)
{
		free(cmd_line->buf);
		cmd_line->size = 0;
}
