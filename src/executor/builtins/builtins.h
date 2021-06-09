#ifndef BUILTINS_H
# define BUILTINS_H

# include "shell_state.h"

# define NOT_BUILTIN -1

int	can_execute_builtin(t_treenode *syntax_tree, t_shell *shell);
int	execute_echo(t_treenode *simple_cmd_node, t_shell *shell);
int	execute_exit(t_treenode *simple_cmd_node, t_shell *shell);
int	execute_pwd(t_treenode *simple_cmd_node, t_shell *shell);
int	execute_cd(t_treenode *simple_cmd_node, t_shell *shell);
int	execute_env(t_treenode *simple_cmd_node, t_shell *shell);
int	execute_export(t_treenode *simple_cmd_node, t_shell *shell);
int	execute_unset(t_treenode *simple_cmd_node, t_shell *shell);

/*
**	builtins_utilities:
*/

int	count_arguments(t_treenode *simple_cmd_node);

#endif
