/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   keys.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: osamara <osamara@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/04/27 08:14:47 by osamara       #+#    #+#                 */
/*   Updated: 2021/04/29 11:37:17 by osamara       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "keys.h"

#include "libft.h"

#include <unistd.h>
#include <stdio.h>

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
	reset_line_state(line_state);
	// line_state->eol = 1; // do I need it now?
	history->last_shown_line = history->num_lines - 1;
	return (1);
}

int	handle_backspace(t_history *history, t_line *line_state)
{
	size_t i;

	i = line_state->line_len;
	line_state->buf[i] = '\b';
	line_state->buf[i + 1] = ' ';
	line_state->buf[i + 2] = '\b';
	line_state->line_len--;
    return (1);
}

int	show_prev_history(t_history *history, t_line *line_state)
{
	if (history->num_lines != 0)
	{
		if (line_state->line_len != 0)
		{
			if (!add_history_line(history, line_state))
				return (0);
		}
		handle_backspace(history, line_state);
		line_state->buf = history->lines[history->last_shown_line - 1];
		printf("%s", line_state->buf);
	}
	return (1);
}

int	show_next_history(t_history *history, t_line *line_state)
{
    return (1);
}


int	handle_eot(t_history *history, t_line *line_state)
{
    return (1);
}

// void	handle_interrupt(t_history *history, t_line *line_state)
// {
// 	
// }
// void	handle_quit(t_history *history, t_line *line_state)
// {
// 	
// }


void	map_key_actions(t_history *history, t_line *line_state, char keycode)
{
	int	i;
	static t_keycodes_map	keycodes_map[] =
	{
		{ARROW_UP, show_prev_history},
		{ARROW_DOWN, show_next_history},
		{BACKSPACE, handle_backspace},
		{NEWLINE, handle_newline},
		{CTRL_D, handle_eot},
		// {CTRL_C, handle_interrupt},
		// {CTRL_\, handle_quit},
		{'\0', NULL}
	};

	i = 0;
	while (keycodes_map[i].keycode != '\0')
	{
		if (keycode == keycodes_map[i].keycode)
        {
			keycodes_map[i].action(history, line_state);
            break ;
        }
		i++;
	}
}

char	get_keycode(int fd, char *sequence)
{
	if (read(fd, sequence, 1) == -1 || read(fd, sequence + 1, 1) == -1)
		return (0);
	if (sequence[0] == '[')
	{
		if (sequence[1] >= '0' && sequence[1] <= '9')
		{
			if (read(fd, sequence + 2, 1) == -1)
				return (0);
			return (sequence[2]);
		}
		return (sequence[1]);
	}
	return (0);
}
