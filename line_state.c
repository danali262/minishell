/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   line_state.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: osamara <osamara@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/04/28 15:23:35 by osamara       #+#    #+#                 */
/*   Updated: 2021/04/28 15:44:09 by osamara       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "line_state.h"

#include "libft.h"

#include <stdio.h>
#include <stdlib.h>

int	reset_line_state(t_line *line_state)
{
	ft_bzero(line_state->buf, BUF_SIZE);
	line_state->eol = 0;
	line_state->line_len = 0;
	return (1);
}

int	init_buffer(t_line *line_state)
{
	int i;

	i = 0;
	line_state->buf = ft_calloc(BUF_SIZE + 1, 1);
	if (line_state->buf == NULL)
	{
		printf("Error. Unable to allocate memory.\n");
		return (0);
	}
	return (1);
}

void	free_buffer(t_line *line_state)
{
		free(line_state->buf);
		line_state->eol = 0;
		line_state->line_len = 0;
}
