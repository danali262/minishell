#include "keys.h"
#include "handle_keys.h"

#include "libft.h"

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

void	handle_key_action(t_shell *shell, char keycode)
{
	if (keycode == BACKSPACE)
		handle_backspace(&shell->cmd_line);
	else if (keycode == ENTER)
		handle_enter(shell);
	else if (keycode == CTRL_D)
		handle_eot(shell);
	else if (keycode == CTRL_C)
		handle_interrupt(shell);
	else if (keycode == ARROW_UP)
		show_prev_history(&shell->history, &shell->cmd_line);
	else if (keycode == ARROW_DOWN)
		show_next_history(&shell->history, &shell->cmd_line);
	// else if (keycode == shell->termcap_codes.keyup[0]
	// 		&& shell->termcap_codes.keyup[1] == '\0')
	// 	show_prev_history(&shell->history, &shell->cmd_line);
	// else if (keycode == shell->termcap_codes.keydown[0]
	// 		&& shell->termcap_codes.keydown[1] == '\0')
	// 	show_next_history(&shell->history, &shell->cmd_line);
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
