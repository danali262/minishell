#include "signals.h"
#include "../reader/command_line_state.h"
#include "../reader/read_command_line.h"

#include <signal.h>
#include <stdio.h>

void	termination_handler(int signum)
{
	t_shell *shell;

	shell = get_shell_state();
	if (signum == SIGINT)
	{
		shell->exit_code = 1;
		clear_command_line(&shell->cmd_line);
		ft_putstr_fd("\n\r", STDOUT_FILENO);
		ft_putstr_fd(PROMPT, STDOUT_FILENO);
	}
	// else if (signum == SIGQUIT)
	// {
	// 	shell->exit_code = 131;
	// 	clear_command_line(&shell->cmd_line);
	// 	ft_putstr_fd("\n\r", STDOUT_FILENO);
	// }
}

void	quit_execution(int signum)
{
		t_shell *shell;

	shell = get_shell_state();
	if (signum == SIGQUIT)
	{
		shell->exit_code = 131;
		clear_command_line(&shell->cmd_line);
		ft_putstr_fd("Quit: 3\n\r", STDOUT_FILENO);
	}
}


void	catch_signals(void)
{
	signal(SIGINT, termination_handler);
	signal(SIGQUIT, termination_handler);
	return ;
}
