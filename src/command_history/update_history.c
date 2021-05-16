#include "command_history.h"
#include "../reader/handle_keys.h"

#include "libft.h"

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

void static	overlap_history(t_history *history)
{
	int	i;

	free(history->lines[0]);
	history->lines[0] = NULL;
	i = 1;
	while (i <= MAX_HIST - 1)
	{
		history->lines[i - 1] = ft_strdup(history->lines[i]);
		free(history->lines[i]);
		history->lines[i] = NULL;
		i++;
	}
}

int	add_history_line(t_history *history, t_line *cmd_line)
{
	int	i;

	if (history->num_lines + 1 > MAX_HIST)
		overlap_history(history);
	else
		history->num_lines++;
	history->last_shown_line = history->num_lines - 1;
	i = history->last_shown_line;
	if (history->saved_temp_input[MAX_HIST] != NULL
		&& ft_strncmp(history->saved_temp_input[MAX_HIST], cmd_line->buf,
			ft_strlen(history->saved_temp_input[MAX_HIST])) == 0)
		history->lines[i] = ft_strdup(history->saved_temp_input[MAX_HIST]);
	else
		history->lines[i] = ft_strdup(cmd_line->buf);
	if (history->lines[i] == NULL)
		return (0);
	return (1);
}
