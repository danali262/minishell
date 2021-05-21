#ifndef BUILTINS_MAP_H
# define BUILTINS_MAP_H

#include "shell_state.h"

typedef struct s_builtins_map
{
	char	*cmd_name;
	int		(*cmd_executor)(t_treenode *syntax_tree, t_shell *shell);
}				t_builtins_map;

#endif
