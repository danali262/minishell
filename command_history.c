
#include "command_history.h"

#include "libft.h"

void	init_history(t_history *history)
{
	ft_bzero(history->lines, MAX_HISTORY);
	history->last_line_index = 0;
}


void	free_history(t_history *history)
{
	int i;

	i = 0;
	while (i <= history->last_line_index)
	{
		free(history->lines[i]);
		i++;
	}
		history->last_line_index = 0;
}
