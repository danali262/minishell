/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   keys.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: osamara <osamara@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/04/27 08:14:47 by osamara       #+#    #+#                 */
/*   Updated: 2021/04/28 16:40:04 by osamara       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "keys.h"

#include "libft.h"

#include <unistd.h>

void	handle_arrow_up(t_history *history, t_line *line_state)
{
	
}
void	handle_arrow_down(t_history *history, t_line *line_state)
{
	
}
void	handle_backspace(t_history *history, t_line *line_state)
{
	size_t i;

	i = line_state->line_len;
	line_state->buf[i] = '\b';
	line_state->buf[i + 1] = ' ';
	line_state->buf[i + 2] = '\b';
	line_state->line_len--;
}

void	handle_newline(t_history *history, t_line *line_state)
{
	int i;

	history->last_line_index++;
	if (history->last_line_index >= MAX_HISTORY)
	{
		free(history->lines[0]);
		i = 1;
		while (i < MAX_HISTORY - 1)
		{
			history->lines[i - 1] = history->lines[i];
			i++;
		}
	}
    i = history->last_line_index;
	free(history->lines[i]);
	history->lines[i] = ft_strdup(line_state->buf);
	line_state->eol = 1; // do I need it now?
	reset_line_state(line_state);
}

void	handle_eot(t_history *history, t_line *line_state)
{
	
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
		{ARROW_UP, handle_arrow_up},
		{ARROW_DOWN, handle_arrow_down},
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
	{
		return (0);
	}
	if (sequence[0] == '[')
	{
		return (sequence[1]);
	}
	return (0);
}
