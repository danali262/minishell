/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   command_line_state.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: osamara <osamara@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/04/28 15:23:35 by osamara       #+#    #+#                 */
/*   Updated: 2021/05/01 20:10:18 by osamara       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "command_line_state.h"
#include "read_command_line.h"

#include "libft.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int	init_command_line(t_line *line_state)
{
	int i;

	i = 0;
	line_state->buf = ft_calloc(BUF_SIZE + 1, 1);
	if (line_state->buf == NULL)
	{
		ft_putstr_fd("Error. Unable to allocate memory.\n", STDOUT_FILENO);
		return (0);
	}
	return (1);
}

int	clear_command_line(t_line *line_state)
{
	line_state->buf[0] = '\0';
	line_state->line_len = 0;
	return (1);
}

void	free_command_line(t_line *line_state)
{
		free(line_state->buf);
		line_state->line_len = 0;
}
