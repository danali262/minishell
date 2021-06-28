#include "read_command_line.h"

#include "libft.h"

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

void	handle_backspace(t_line *cmd_line)
{
	size_t	i;

	i = cmd_line->size - 1;
	if (cmd_line->size != 0)
	{
		cmd_line->buf[i] = '\b';
		write(STDOUT_FILENO, "\b", 1);
		cmd_line->buf[i] = ' ';
		write(STDOUT_FILENO, " ", 1);
		cmd_line->buf[i] = '\b';
		cmd_line->buf[i] = '\0';
		write(STDOUT_FILENO, "\b", 1);
		cmd_line->size--;
	}
}

int	handle_enter(t_shell *shell)
{
	if (!add_history_line(&shell->history, &shell->cmd_line))
		return (0);
	printf("\n");
	free_temp_input(&shell->history);
	shell->history.iter_mode = 0;
	shell->is_command_executed = 1;
	return (1);
}

int	handle_eot(t_shell *shell)
{
	if (shell->cmd_line.size == 0)
	{
		shell->cmd_line.size = ft_strlen("exit");
		shell->cmd_line.buf = ft_memmove(shell->cmd_line.buf, "exit",
				shell->cmd_line.size);
		if (!handle_enter(shell))
			return (0);
	}
	return (1);
}

void	handle_interrupt(t_shell *shell)
{
	shell->exit_code = 1;
	clear_command_line(&shell->cmd_line);
	ft_putstr_fd("\n\r", STDOUT_FILENO);
	ft_putstr_fd(PROMPT, STDOUT_FILENO);
}
