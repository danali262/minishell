#ifndef REDIRECTION_H
#define REDIRECTION_H

#include "../shell_state.h"

void    check_for_redirection(t_treenode *syntax_tree, t_shell *shell);
void	restore_stdio(t_shell *shell);

#endif