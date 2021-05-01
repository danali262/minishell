/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   read_command_line.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: osamara <osamara@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/04/26 14:05:53 by osamara       #+#    #+#                 */
/*   Updated: 2021/05/01 20:09:48 by osamara       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "read_command_line.h"
#include "keys.h"
#include "lexer/lexer.h"

#include "libft.h"

#include <unistd.h>

int	read_input (void)
{
	struct termios	origin_attr;
	t_history		history;
	t_line			line_state;
	char			*prompt;

	
	if (!set_input_mode(&origin_attr))
		return (0);
	init_terminal_data(); //probably to the main?
	if (!init_command_line(&line_state))
		return (0);
    init_history(&history);
	clear_command_line(&line_state);
	while (1)
	{
		ft_putstr_fd(PROMPT, STDOUT_FILENO);
		while (history.is_command_executed != 1)
		{
			if (read_command_line(STDIN_FILENO, &history, &line_state == -1))
			{
				free_command_line(&line_state);
				free_history(&history);
				return (0);
			}
		}
		reset_input_mode(&origin_attr, 0);
		// if (line_state.line_len != 0)
		printf("lexer...\n");//remove
		lexer_build(prompt.cmd, &lexerbuf);
    	print_tokens(&lexerbuf);
		printf("here is the execution result printed...\n");//remove
		history.is_command_executed = 0;
		//start parsing and executing
		//print execution result
		printf("%s", line_state.buf); //remove it, need for debugging
	}
	return (1);
}


int	read_command_line(int fd, t_history *history, t_line *line_state)
{
	ssize_t	bytes_read;
	char	ch;
	char	sequence[3];
	char	keycode;

	ch = 0;
	bytes_read = read(fd, &ch, 1);
	if (bytes_read == -1) // check if read returns cntrlD? 
	{
		return (-1);
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
