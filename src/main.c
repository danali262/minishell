#include "shell_state.h"
#include "shell_utilities.h"
#include "signals/signals.h"
#include "reader/read_command_line.h"
#include "parser/parser.h"
#include "executor/executor.h"
#include "executor/environment/environment.h"
#include "term_cap/init_terminal_data.h"
#include "redirection/redirection.h"

t_shell	*g_shell = NULL;

int	shell_event_loop(t_shell *shell)
{
	int				parser_result;
	t_treenode		tree;
	t_redirection	redir;

	while (shell->minishell_exits != true)
	{
		shell->syntax_tree = &tree;
		shell->redir = &redir;
		init_tree(shell);
		write_prompt();
		while (shell->is_command_executed != 1)
			if (read_input(shell) == ERROR)
				return (ERROR);
		reset_input_mode(shell, 0);
		parser_result = parse_command_line(shell);
		if (parser_result == -1)
			return (ERROR);
		else if (parser_result != 0)
			run_executor(shell);
		shell->is_command_executed = 0;
	}
	return (SUCCESS);
}

int	main(int argc, char **argv)
{
	t_shell	shell;
	int		exit_code;

	(void)argv;
	if (argc > 1)
	{
		printf("Error.Too many arguments.\n");
		return (1);
	}
	g_shell = &shell;
	ft_bzero(&shell, sizeof(t_shell));
	init_shell(&shell);
	catch_signals();
	if (shell_event_loop(&shell) == ERROR)
	{
		g_shell = NULL;
		exit_code = shell.exit_code;
		free_shell_data(&shell);
		return (exit_code);
	}
	g_shell = NULL;
	exit_code = shell.exit_code;
	free_shell_data(&shell);
	return (exit_code);
}
