/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   update_history.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: osamara <osamara@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/04/29 16:53:12 by osamara       #+#    #+#                 */
/*   Updated: 2021/05/03 01:15:12 by osamara       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "command_history.h"
#include "../reader/handle_keys.h"


#include "libft.h"

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int	add_history_line(t_history *history, t_line *cmd_line)
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
	if (history->saved_temp_input[MAX_HISTORY] != NULL)
		history->lines[i] = ft_strdup(history->saved_temp_input[MAX_HISTORY]);
	else
		history->lines[i] = ft_strdup(cmd_line->buf);
	if (history->lines[i] == NULL)
		return (0);
	return (1);
}

/*
**	
*/

int	handle_newline(t_history *history, t_line *cmd_line)
{
	if (!add_history_line(history, cmd_line))
		return (0);
	printf("\n");
	free(history->saved_temp_input[MAX_HISTORY]);
	history->saved_temp_input[MAX_HISTORY] = NULL;
	history->last_shown_line = history->num_lines - 1;
	history->iter_mode = 0;
	history->is_command_executed = 1;
	return (1);
}

int	show_prev_history(t_history *history, t_line *cmd_line)
{
	char	*prev_line;

	if (history->num_lines != 0)
	{
		if (cmd_line->size != 0 && !history->iter_mode)
		// if (cmd_line->size != 0) //iter mode won't be needed after refactoring
		{
			history->saved_temp_input[MAX_HISTORY] = ft_strdup(cmd_line->buf);
			history->is_command_executed = 0;
		}
		if (history->num_lines == 1 && cmd_line->size == 0) //dry!
		{
			cmd_line->size = ft_strlen(history->lines[0]);
			cmd_line->buf = ft_memcpy(cmd_line->buf, history->lines[0], cmd_line->size);
			if (cmd_line->buf == NULL)
				return (0);
			history->iter_mode = 1;
			write(STDOUT_FILENO, cmd_line->buf, cmd_line->size);
		}
		else if (history->last_shown_line != 0)
		{
			while (cmd_line->size != 0)
				handle_backspace(history, cmd_line);
			prev_line = history->lines[history->last_shown_line - 1];
			cmd_line->size = ft_strlen(prev_line);
			cmd_line->buf = ft_memcpy(cmd_line->buf, prev_line, cmd_line->size);
			if (cmd_line->buf == NULL)
				return (0);
			history->last_shown_line--;
			history->iter_mode = 1;
            write(STDOUT_FILENO, cmd_line->buf, cmd_line->size);
		}
	}
	return (1);
}

int	show_next_history(t_history *history, t_line *cmd_line)
{
    char	*next_line;

	// clear_command_line(cmd_line);
	if (history->num_lines != 0)
	{
		if (cmd_line->size != 0 && !history->iter_mode)
		// if (cmd_line->size != 0) // will replace the upper line
		{
			history->saved_temp_input[MAX_HISTORY] = ft_strdup(cmd_line->buf);
			history->is_command_executed = 0;
		}
		if (history->last_shown_line != history->num_lines - 1)
		{
			while (cmd_line->size != 0)
				handle_backspace(history, cmd_line);
			next_line = history->lines[history->last_shown_line + 1];
			cmd_line->size = ft_strlen(next_line);
			cmd_line->buf = ft_memcpy(cmd_line->buf, next_line, cmd_line->size);
			if (cmd_line->buf == NULL)
				return (0);
			history->last_shown_line++;
			history->iter_mode = 1;
            write(STDOUT_FILENO, cmd_line->buf, cmd_line->size);
		}
		else
			if (history->saved_temp_input[MAX_HISTORY] != NULL)
			{
				cmd_line->size = ft_strlen(history->saved_temp_input[MAX_HISTORY]); //dry
				cmd_line->buf = ft_memcpy(cmd_line->buf, history->saved_temp_input[MAX_HISTORY], cmd_line->size);
				free(history->saved_temp_input[MAX_HISTORY]);
				history->saved_temp_input[MAX_HISTORY] = NULL;
			}
		//TODO: add check if history is iterated after newline and no new command is enetered
	}
	return (1);
}
