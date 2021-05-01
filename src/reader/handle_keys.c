/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   handle_keys.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: osamara <osamara@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/04/29 17:00:02 by osamara       #+#    #+#                 */
/*   Updated: 2021/05/01 19:59:59 by osamara       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "handle_keys.h"

#include <unistd.h>
#include <stdio.h>

int	handle_backspace(t_history *history, t_line *line_state)
{
	size_t i;

	i = line_state->line_len - 1;
	line_state->buf[i] = '\b';
    write(1, "\b", 1);
	line_state->buf[i] = ' ';
    write(1, " ", 1);
	line_state->buf[i] = '\b';
    write(1, "\b", 1);
	line_state->line_len--;
    return (1);
}

int	handle_eot(t_history *history, t_line *line_state)
{
	//TODO: ^D while typing the command works as TAB
	// only if ^D after the command is executed:
	printf("exit\n");
		exit(0);
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

