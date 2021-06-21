#include "signals.h"
#include "../shell_state.h"
#include "../reader/command_line_state.h"
#include "../reader/read_command_line.h"

#include <signal.h>
#include <stdio.h>

extern t_shell	*g_shell;

void	termination_handler(int signum)
{
	if (!g_shell)
		return ;
	if (signum == SIGINT)
	{
		g_shell->exit_code = 1;
		g_shell->is_command_executed = 1;
		clear_command_line(&g_shell->cmd_line);
		ft_putstr_fd("\n\r", STDOUT_FILENO);
		write_prompt(g_shell);
	}
}

void	quit_execution(int signum)
{
	if (!g_shell)
		return ;
	if (signum == SIGQUIT)
	{
		g_shell->exit_code = 131;
		clear_command_line(&g_shell->cmd_line);
		ft_putstr_fd("Quit: 3\n\r", STDOUT_FILENO);
	}
}

void	catch_signals(void)
{
	signal(SIGINT, termination_handler);
	signal(SIGQUIT, termination_handler);
	return ;
}
