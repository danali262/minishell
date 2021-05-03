
#include "command_history.h"

#include "libft.h"

#include <stdlib.h>
#include <unistd.h>

/*
** saved_temp_input array is needed to save the copy of the history when its lines are edited but not executed
** it's being cleared after CR/enter/nl is pressed
** + 1 is needed to track the copy of the current command line if the command is typed but not executed yet
*/

void	init_history(t_history *history)
{
	ft_bzero(history->lines, MAX_HISTORY);
	ft_bzero(history->saved_temp_input, MAX_HISTORY + 1);
    history->saved_temp_input[MAX_HISTORY] = NULL;
	history->num_lines = 0;
	history->last_shown_line = -1;
	history->is_command_executed = 0;
	history->iter_mode = 0;
}

void	free_history(t_history *history)
{
	int i;

	i = 0;
	while (i <= history->last_shown_line)
	{
		free(history->lines[i]);
		free(history->saved_temp_input[i]);
		i++;
	}
	free(history->saved_temp_input[MAX_HISTORY]);
}

void	clear_history(t_history *history)
{
	free_history(history);
	init_history(history);
}
