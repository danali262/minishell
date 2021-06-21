#include "read_command_line.h"

#include <stdbool.h>

void	write_prompt(t_shell *shell)
{
	if (shell->is_newline == true)
		write(STDOUT_FILENO, "\r", 1);
	ft_putstr_fd("\033[1;32m", STDOUT_FILENO);
	ft_putstr_fd(PROMPT, STDOUT_FILENO);
	ft_putstr_fd("\033[0m", STDOUT_FILENO);
	shell->is_newline = true;
}
