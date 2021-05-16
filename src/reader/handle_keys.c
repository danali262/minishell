#include "handle_keys.h"
#include "keys.h"
#include "read_command_line.h"

#include "libft.h"

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>


void	handle_backspace(t_line *cmd_line)
{
	size_t i;

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

int	handle_eot(t_history *history, t_line *cmd_line) // replace with the other funcion when exit is implemented
{
	char	*exit_msg;

	exit_msg = "logout\nSaving session...\n...copying shared history...\
		\n...saving history...truncating history files...\
		\n...completed.\n\n[Process completed]\n";
	if (cmd_line->size == 0)
	{
		ft_putstr_fd(exit_msg, STDOUT_FILENO);
		free_history(history);
		free_command_line(cmd_line);
		exit(0);
	}
	//TODO: ^D while typing the command works as TAB
	return (1);
}

// int	handle_eot(t_shell *shell)
// {
// 	shell->cmd_line.size = ft_strlen("exit");
// 	shell->cmd_line.buf = ft_memcpy(shell->cmd_line.buf, "exit", shell->cmd_line.size);
// 	if (!handle_enter(shell))
// 		return (0);
// 	return (1);
// }

// void	handle_interrupt(t_history *history, t_line *cmd_line)
// {
// 	
// }

// void	handle_quit(t_history *history, t_line *cmd_line)
// {
// 	
// }

