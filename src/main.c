#include "shell_state.h"
#include "signals/signals.h"
#include "reader/read_command_line.h"
#include "parser/parser.h"
#include "executor/executor.h"
#include "term_cap/init_terminal_data.h"

t_shell *get_shell_state(void)
{
    static t_shell shell;

    return (&shell);
}

int shell_event_loop(t_shell *shell)
{
    struct termios	origin_attr;
    int             parser_result;
    t_treenode      tree;

    while (1)
	{
        shell->syntax_tree = &tree;
        
        init_tree(shell->syntax_tree);
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
            execute_command_line(shell->syntax_tree, shell);
            delete_node(&shell->syntax_tree);
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
            ||  create_environment(shell) == ERROR)
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
	// TODO:
    // free_all_env_var_lists(3 lists);
}

int		main(void)
// int     main(int ac, char **av, char **envp)
{
	t_shell			shell;
    
    init_shell(&shell);
    if (shell_event_loop(&shell) == ERROR)
    {
        free_shell_data(&shell);
        return (1);
    }
    free_shell_data(&shell);
    return (0);
}
