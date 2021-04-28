/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   gnl_utils.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: osamara <osamara@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/04/26 14:05:53 by osamara       #+#    #+#                 */
/*   Updated: 2021/04/28 15:30:48 by osamara       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "gnl_utils.h"
#include "keys.h"

#include "libft.h"

#include <unistd.h>

int	read_command_line(int fd, t_history *history, t_line *line_state)
{
	ssize_t	bytes_read;
	char	ch;
	char	sequence[3];
	char	keycode;

	ch = 0;
	bytes_read = read(fd, &ch, 1);
	if (bytes_read == -1)
	{
		return (0);
	}
	if (ft_isprint(ch))
	{
		write(STDOUT_FILENO, &ch, 1);
		line_state->buf[line_state->line_len] = ch;
		line_state->line_len++;
	}
	else
	{
		keycode = 0;
		if (ch == ESC)
		{
			keycode = get_keycode(fd, sequence);
			if (keycode != 0)
			{
				ch = keycode;
			}
		}
		map_key_actions(history, line_state, ch);
	}
	return (1);
}
