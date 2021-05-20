#ifndef EXECUTOR_H
# define EXECUTOR_H

#include "../shell_state.h"

void	execute_command_line(t_treenode *top_node, t_shell *shell);
char	*locate_executable_path(t_treenode *simple_cmd_node);
int		run_simple_command(t_treenode *simple_cmd_node, t_shell *shell);

#endif
