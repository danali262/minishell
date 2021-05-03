#include "handle_keys.h"
#include "keys.h"
#include "read_command_line.h"


#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int	handle_backspace(t_history *history, t_line *cmd_line)
{
	size_t i;

	if (cmd_line->size != 0)
	{
		i = cmd_line->size - 1;
		cmd_line->buf[i] = '\b';
		write(1, "\b", 1);
		cmd_line->buf[i] = ' ';
		write(1, " ", 1);
		cmd_line->buf[i] = '\b';
		write(1, "\b", 1);
		cmd_line->size--;
	}
	return (1);
}

int	handle_eot(t_history *history, t_line *cmd_line)
{
	// only if ^D after the command is executed:
	if (history->is_command_executed)
	{
		printf("exit\n");
		free_history(history);
		free_command_line(cmd_line);
		exit(0);
		
	}
	//TODO: ^D while typing the command works as TAB
	return (1);
}

// void	handle_interrupt(t_history *history, t_line *cmd_line)
// {
// 	
// }

// void	handle_quit(t_history *history, t_line *cmd_line)
// {
// 	
// }

