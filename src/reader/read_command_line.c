#include "read_command_line.h"
#include "keys.h"
#include "../parser/parser.h"
#include "../command_history/init_terminal_data.h"

#include "libft.h"

#include <unistd.h>
#include <stdio.h>//remove

int	read_input(void)
{
	struct termios	origin_attr;
	t_history		history;
	t_line			cmd_line;

	init_terminal_data(); //probably to the main?
	if (!init_command_line(&cmd_line))
		return (0);
	clear_command_line(&cmd_line);
	init_history(&history);
	while (1)
	{
		ft_putstr_fd(PROMPT, STDOUT_FILENO);
		while (history.is_command_executed != 1)
		{
			if (!set_input_mode(&origin_attr))
				return (0);
			if (read_command_line(STDIN_FILENO, &history, &cmd_line) == -1)
			{
				free_command_line(&cmd_line);
				free_history(&history);
				return (0);
			}
		}
		reset_input_mode(&origin_attr, 0);
		if (!parse_command_line(&cmd_line))
			return (0);

		printf("execution result...\n");//remove
		history.is_command_executed = 0;
	}
	return (1);
}

int	read_command_line(int fd, t_history *history, t_line *cmd_line)
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
		cmd_line->buf[cmd_line->size] = ch;
		cmd_line->size++;
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
		map_key_actions(history, cmd_line, ch);
	}
	return (1);
}
