/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   update_history.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: osamara <osamara@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/04/29 16:53:12 by osamara       #+#    #+#                 */
/*   Updated: 2021/04/29 17:27:34 by osamara       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "update_history.h"
#include "handle_keys.h"

#include "libft.h"

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int	add_history_line(t_history *history, t_line *line_state)
{
	int i;

	history->num_lines++;
	if (history->num_lines > MAX_HISTORY)
	{
		free(history->lines[0]);
		i = 1;
		while (i < MAX_HISTORY - 1)
		{
			history->lines[i - 1] = history->lines[i];
			i++;
		}
	}
	history->last_shown_line++;
    i = history->last_shown_line;
	free(history->lines[i]);
	history->lines[i] = ft_strdup(line_state->buf);
	if (history->lines[i] == NULL)
		return (0);
	return (1);
}

int	handle_newline(t_history *history, t_line *line_state)
{
	if (!add_history_line(history, line_state))
		return (0);
	printf("\n");
	reset_line_state(line_state);
	history->last_shown_line = history->num_lines - 1;
	history->iter_mode = 0;
	history->is_command_executed = 1;
	return (1);
}

int	show_prev_history(t_history *history, t_line *line_state)
{
	char	*prev_line;

	// reset_line_state(line_state);
	if (history->num_lines != 0)
	{
		if (line_state->line_len != 0 && !history->iter_mode)
		{
			if (!add_history_line(history, line_state))
				return (0);
			history->is_command_executed = 0;
		}
		if (history->last_shown_line != 0)
		{
			while (line_state->line_len != 0)
				handle_backspace(history, line_state);
			prev_line = history->lines[history->last_shown_line - 1];
			line_state->line_len = ft_strlen(prev_line);
			line_state->buf = ft_memcpy(line_state->buf, prev_line, line_state->line_len);
			if (line_state->buf == NULL)
				return (0);
			history->last_shown_line--;
			history->iter_mode = 1;
			printf("%s", line_state->buf);
		}
	}
	return (1);
}

int	show_next_history(t_history *history, t_line *line_state)
{
    char	*next_line;

	// reset_line_state(line_state);
	if (history->num_lines != 0)
	{
		if (line_state->line_len != 0 && !history->iter_mode)
		{
			if (!add_history_line(history, line_state))
				return (0);
			history->is_command_executed = 0;
		}
		if (history->last_shown_line != history->num_lines - 1)
		{
			while (line_state->line_len != 0)
				handle_backspace(history, line_state);
			next_line = history->lines[history->last_shown_line + 1];
			line_state->line_len = ft_strlen(next_line);
			line_state->buf = ft_memcpy(line_state->buf, next_line, line_state->line_len);
			if (line_state->buf == NULL)
				return (0);
			history->last_shown_line++;
			history->iter_mode = 1;
			printf("%s", line_state->buf);
		}
		if (history->is_command_executed)
		{
			while (line_state->line_len != 0)
				handle_backspace(history, line_state);
		}
	}
	return (1);
}

