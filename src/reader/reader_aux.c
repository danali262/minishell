#include "read_command_line.h"

#include <stdbool.h>

void	write_prompt(void)
{
	ft_putstr_fd("\033[1;32m", STDOUT_FILENO);
	ft_putstr_fd(PROMPT, STDOUT_FILENO);
	ft_putstr_fd("\033[0m", STDOUT_FILENO);
}
