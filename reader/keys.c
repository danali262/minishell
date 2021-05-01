/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   keys.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: osamara <osamara@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/04/27 08:14:47 by osamara       #+#    #+#                 */
/*   Updated: 2021/05/01 18:38:06 by osamara       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "keys.h"
#include "handle_keys.h"

#include "libft.h"

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>


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
