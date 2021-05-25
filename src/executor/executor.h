#ifndef EXECUTOR_H
# define EXECUTOR_H

#include "../shell_state.h"
#include <fcntl.h>

void	execute_command_line(t_treenode *top_node, t_shell *shell);
char	*locate_executable_path(t_treenode *simple_cmd_node);
int		run_simple_command(t_treenode *simple_cmd_node, t_shell *shell);

/*
** environment:
*/ 

int		create_env_var_list(t_shell *shell);
int		change_env_value(t_shell *shell, char *var_name, char *new_value);

/*
** utilities:
*/

char	*concat_path(char *left, char *right);

#endif
