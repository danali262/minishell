#include "shell_state.h"
#include "reader/read_command_line.h"
#include "parser/parser.h"
#include "executor/executor.h"
#include "term_cap/init_terminal_data.h"

int shell_event_loop(t_shell *shell)
{
    struct termios	origin_attr;
    int             parser_result;
    t_treenode      tree;

    while (1)
	{
        shell->syntax_tree = &tree;
        
        init_tree(shell->syntax_tree);
        ft_putstr_fd(PROMPT, STDOUT_FILENO);
        while (shell->is_command_executed != 1)
        {
            if (!read_input(shell, &origin_attr))
                return (0);
        }
        reset_input_mode(&origin_attr, 0);
        parser_result = parse_command_line(shell);
        if (parser_result == -1)
            return (0);
        else if (parser_result != 0)
            execute_command_line(shell->syntax_tree, shell);
        delete_node(shell->syntax_tree);
        if (shell->minishell_exits == true)
            return(1);
        shell->is_command_executed = 0;
	}
	return (1);
}

int init_shell(t_shell *shell)
{
    init_terminal_data(shell);
	if (!init_command_line(&shell->cmd_line))
		return (0);
    init_history(&shell->history);
    shell->is_command_executed = 0;
    shell->exit_code = -1;
    shell->minishell_exits = false;
    return (1);
}

void    free_shell_data(t_shell *shell)
{
    free(shell->term_buffer);
   	free_command_line(&shell->cmd_line);
	free_history(&shell->history);
}

int		main(void)
// int     main(int ac, char **av, char **envp)
{
	t_shell			shell;
    
    init_shell(&shell);
    if (!shell_event_loop(&shell))
    {
        // free_shell_data(&shell); // not implemented yet
        return (1);
    }
    // free_shell_data(&shell); // not implemented yet
    return (0);
}
