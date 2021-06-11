#include "command_history.h"

#include "libft.h"

#include <stdlib.h>
#include <unistd.h>

/*
** saved_temp_input array is needed to save the copy of the history
** when its lines are edited but not executed
** it's being cleared after CR/enter/nl is pressed
** + 1 is needed to track the copy of the current command line
** if the command is typed but not executed yet
*/

void	init_history(t_history *history)
{
	ft_bzero(history->lines, MAX_HIST);
	ft_bzero(history->saved_temp_input, MAX_HIST + 1);
	history->saved_temp_input[MAX_HIST] = NULL;
	history->num_lines = 0;
	history->last_shown_line = -1;
	history->iter_mode = 0;
}

void	free_history(t_history *history)
{
	int	i;

	i = 0;
	while (i <= history->last_shown_line)
	{
		free(history->lines[i]);
		history->lines[i] = NULL;
		free(history->saved_temp_input[i]);
		history->saved_temp_input[i] = NULL;
		i++;
	}
	free_temp_input(history);
}

void	clear_history(t_history *history)
{
	free_history(history);
	init_history(history);
}

void	free_temp_input(t_history *history)
{
	free(history->saved_temp_input[MAX_HIST]);
	history->saved_temp_input[MAX_HIST] = NULL;
}

int	save_temp_cmd_line(t_history *history, t_line *cmd_line)
{
	history->saved_temp_input[MAX_HIST] = ft_strdup(cmd_line->buf);
	if (history->saved_temp_input[MAX_HIST] == NULL)
	{
		ft_putstr_fd("Error. Unable to allocate memory.\n", STDOUT_FILENO);
		return (0);
	}
	return (1);
}
