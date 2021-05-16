#include "shell_state.h"
#include "reader/read_command_line.h"
#include "parser/parser.h"
#include "executor/executor.h"
#include "term_cap/init_terminal_data.h"

int shell_event_loop(t_shell *shell)
{
    struct termios	origin_attr;
    
    while (1)
	{
        ft_putstr_fd(PROMPT, STDOUT_FILENO);
        while (shell->is_command_executed != 1)
        {
            if (!read_input(shell, &origin_attr))
                return (0);
		}
		reset_input_mode(&origin_attr, 0);
        if (parse_command_line(shell) == -1)
            return (0);
        else
            execute_command_line(shell->syntax_tree);
        delete_node(shell->syntax_tree);		/* to be reviewed */
        shell->is_command_executed = 0;
	}
	return (1);
}

int init_shell(t_shell *shell)
{
	init_terminal_data();
	if (!init_command_line(&shell->cmd_line))
		return (0);
	clear_command_line(&shell->cmd_line);
    init_history(&shell->history);
    shell->is_command_executed = 0;
    return (1);
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
