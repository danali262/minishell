#ifndef SHELL_UTILITIES_H
# define SHELL_UTILITIES_H

# include "shell_state.h"

int		init_shell(t_shell *shell);
void	init_tree(t_shell *syntax_tree);
void	free_shell_data(t_shell *shell);

#endif
