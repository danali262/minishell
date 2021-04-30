
#include "command_history.h"

#include "libft.h"

void	init_history(t_history *history)
{
	ft_bzero(history->lines, MAX_HISTORY);
	ft_bzero(history->saved_temp_input, MAX_HISTORY + 1);
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
