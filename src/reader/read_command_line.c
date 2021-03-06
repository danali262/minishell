#include "read_command_line.h"
#include "../parser/parser.h"
#include "../term_cap/init_terminal_data.h"
#include "../shell_state.h"

#include "libft.h"

#include <unistd.h>
#include <errno.h>

int	read_input(t_shell *shell)
{
	if (!set_input_mode(shell))
		return (ERROR);
	if (read_command_line(STDIN_FILENO, shell) == -1)
	{
		free_command_line(&shell->cmd_line);
		free_history(&shell->history);
		return (ERROR);
	}
	return (SUCCESS);
}

int	read_command_line(int fd, t_shell *shell)
{
	ssize_t	bytes_read;
	char	ch;

	ch = 0;
	bytes_read = read(fd, &ch, 1);
	if (bytes_read == -1)
	{
		if (errno == EINTR)
			return (0);
		return (-1);
	}
	if (ft_isprint(ch))
	{
		write(STDOUT_FILENO, &ch, 1);
		shell->cmd_line.buf[shell->cmd_line.size] = ch;
		shell->cmd_line.size++;
	}
	else
		capture_keystrokes(fd, ch, shell);
	return (1);
}

void	capture_keystrokes(int fd, char ch, t_shell *shell)
{
	char	keycode;
	char	sequence[2];

	keycode = 0;
	if (ch == ESC)
	{
		keycode = get_keycode(fd, sequence);
		if (keycode != 0)
		{
			ch = keycode;
		}
	}
	handle_key_action(shell, ch);
}
