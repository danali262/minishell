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
	struct termios	origin_attr;
	int				parser_result;
	t_treenode		tree;
	t_redirection	redir;

	while (shell->minishell_exits != true)
	{
		shell->syntax_tree = &tree;
		shell->redir = &redir;
		init_tree(shell);
		write_prompt(shell);
		catch_signals();
		while (shell->is_command_executed != 1)
			if (read_input(shell, &origin_attr) == ERROR)
				return (ERROR);
		reset_input_mode(&origin_attr, 0);
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

	(void)argv;
	if (argc > 1)
	{
		printf("Error.Too many arguments.\n");
		return (1);
	}
	g_shell = &shell;
	ft_bzero(&shell, sizeof(t_shell));
	init_shell(&shell);
	if (shell_event_loop(&shell) == ERROR)
	{
		g_shell = NULL;
		free_shell_data(&shell);
		return (1);
	}
	g_shell = NULL;
	free_shell_data(&shell);
	return (0);
}
