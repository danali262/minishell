
#include "command_history.h"

#include "libft.h"

void	init_history(t_history *history)
{
	ft_bzero(history->lines, MAX_HISTORY);
	history->num_lines = 0;
	history->last_shown_line = -1;
	history->iter_mode = 0;
}


void	free_history(t_history *history)
{
	int i;

	i = 0;
	while (i <= history->last_shown_line)
	{
		free(history->lines[i]);
		i++;
	}
	history->num_lines = 0;
	history->last_shown_line = -1;
	history->iter_mode = 0;
}
