#include "read_command_line.h"

void	write_prompt(void)
{
	write(STDOUT_FILENO, "\r", 1);
	ft_putstr_fd("\033[1;32m", STDOUT_FILENO);
	ft_putstr_fd(PROMPT, STDOUT_FILENO);
	ft_putstr_fd("\033[0m", STDOUT_FILENO);
}