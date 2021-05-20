#ifndef BUILTINS_H
# define BUILTINS_H

#include "shell_state.h"

int	can_execute_builtin(t_treenode *syntax_tree, t_shell *shell);
int	execute_exit(t_treenode *simple_cmd_node, t_shell *shell);


#endif
