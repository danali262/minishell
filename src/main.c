#include "shell_state.h"
#include "signals/signals.h"
#include "reader/read_command_line.h"
#include "parser/parser.h"
#include "executor/executor.h"
#include "executor/environment/environment.h"
#include "term_cap/init_terminal_data.h"
#include "redirection/redirection.h"

int shell_event_loop(t_shell *shell)
{
    struct termios	origin_attr;
    int             parser_result;
    t_treenode      tree;
    t_redirection   redir;

    while (1)
	{
        shell->syntax_tree = &tree;
        shell->redir = &redir;

        init_tree(shell);
		write(STDOUT_FILENO, "\r", 1);
        ft_putstr_fd(PROMPT, STDOUT_FILENO);
        catch_signals();
        while (shell->is_command_executed != 1)
        {
            if (read_input(shell, &origin_attr) == ERROR)
                return (ERROR);
        }
        reset_input_mode(&origin_attr, 0);
        parser_result = parse_command_line(shell);
        if (parser_result == -1)
            return (ERROR);
        else if (parser_result != 0)
        {
            check_for_redirection(shell->syntax_tree, shell);
            execute_command_line(shell->syntax_tree, shell);
            delete_node(&shell->syntax_tree);
            restore_stdio(shell);
        }
        if (shell->minishell_exits == true)
            return(SUCCESS);
        shell->is_command_executed = 0;
	}
	return (SUCCESS);
}

int init_shell(t_shell *shell)
{
    init_terminal_data(shell);
    if (init_command_line(&shell->cmd_line) == ERROR
            ||  create_env_list(shell) == ERROR)
        return (ERROR);
    init_history(&shell->history);
    shell->is_command_executed = 0;
    shell->exit_code = 0;
    shell->minishell_exits = false;
    return (SUCCESS);
}

void    free_shell_data(t_shell *shell)
{
    free(shell->term_buffer);
   	free_command_line(&shell->cmd_line);
	free_history(&shell->history);
    free_env_list(shell->env_list, ft_env_lstdelone);
}

int		main(void)
// int     main(int ac, char **av, char **envp)
{
    init_shell(&shell);
    if (shell_event_loop(&shell) == ERROR)
    {
        free_shell_data(&shell);
        return (1);
    }
    free_shell_data(&shell);
    return (0);
}
