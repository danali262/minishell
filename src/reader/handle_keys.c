#include "handle_keys.h"
#include "keys.h"
#include "read_command_line.h"

#include "libft.h"

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int	handle_backspace(t_history *history, t_line *cmd_line)
{
	size_t i;

	if (history->last_shown_line != -2) //quick hack, get rid of it
	{
        if (cmd_line->size != 0)
        {
            i = cmd_line->size - 1;
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
	return (1);
}

int	handle_eot(t_history *history, t_line *cmd_line)
{
	char	*exit_msg;

	exit_msg = "\nSaving session...\n...copying shared history...\
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

// void	handle_interrupt(t_history *history, t_line *cmd_line)
// {
// 	
// }

// void	handle_quit(t_history *history, t_line *cmd_line)
// {
// 	
// }

