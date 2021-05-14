#include "command_history.h"

#include "libft.h"

int	static	can_get_prev_history(t_history *history, t_line *cmd_line)
{
	if ((history->num_lines == 1 && cmd_line->size == 0)
		|| (history->num_lines == 1
			&& history->saved_temp_input[MAX_HIST] != NULL
			&& ft_strncmp(history->saved_temp_input[MAX_HIST], cmd_line->buf,
				ft_strlen(history->saved_temp_input[MAX_HIST])) == 0)
		|| history->last_shown_line != 0)
		return (1);
	else
		return (0);
}

int static	load_prev_history_line(t_history *history, t_line *cmd_line)
{
	char	*prev_line;

	if ((history->saved_temp_input[MAX_HIST] != NULL
			   && ft_strncmp(history->saved_temp_input[MAX_HIST], cmd_line->buf,
				   ft_strlen(history->saved_temp_input[MAX_HIST])) == 0)
		|| (history->saved_temp_input[MAX_HIST] == NULL
			&& cmd_line->size == 0))
	{
		history->last_shown_line++;
		prev_line = history->lines[history->last_shown_line];
	}		
	prev_line = history->lines[history->last_shown_line - 1];
	history->last_shown_line--;
	erase_current_line(history, cmd_line);
	if (!update_cmd_line(prev_line, cmd_line))
		return (0);
	history->iter_mode = 1;
	return (1);
}

int	show_prev_history(t_history *history, t_line *cmd_line)
{
	if (history->num_lines != 0)
	{
		if (cmd_line->size != 0 && !history->iter_mode)
		{
			if (!save_temp_cmd_line(history, cmd_line))
				return (0);
		}
		if (can_get_prev_history(history, cmd_line))
		{
			if (!load_prev_history_line(history, cmd_line))
				return (0);
		}
	}
	return (1);
}
