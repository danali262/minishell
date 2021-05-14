#include "command_history.h"

#include "libft.h"

int static	load_next_history_line(t_history *history, t_line *cmd_line)
{
	char	*next_line;

	erase_current_line(history, cmd_line);
	next_line = history->lines[history->last_shown_line + 1];
	if (!update_cmd_line(next_line, cmd_line))
		return (0);
	history->last_shown_line++;
	history->iter_mode = 1;
	return (1);
}

int static	load_from_temp_input(t_history *history, t_line *cmd_line)
{
	if (!update_cmd_line(history->saved_temp_input[MAX_HIST],
			cmd_line))
		return (0);
	free_temp_input(history);
	return (1);
}

int	show_next_history(t_history *history, t_line *cmd_line)
{
	if (history->num_lines != 0)
	{
		if (cmd_line->size != 0 && !history->iter_mode)
		{
			if (!save_temp_cmd_line(history, cmd_line))
				return (0);
		}
		if (history->last_shown_line != history->num_lines - 1)
		{
			if (!load_next_history_line(history, cmd_line))
				return (0);
		}
		else
		{
			erase_current_line(history, cmd_line);
			if (history->saved_temp_input[MAX_HIST] != NULL)
			{
				if (!load_from_temp_input(history, cmd_line))
					return (0);
			}
			history->iter_mode = 0;
		}
	}
	return (1);
}
