#ifndef REDIRECTION_H
# define REDIRECTION_H

# include "../shell_state.h"
# include <fcntl.h>
# include <sys/wait.h>
# include "../executor/executor.h"

void	check_for_redirection(t_treenode *syntax_tree, t_shell *shell);
void	multiple_redirection(t_treenode *syntax_tree, t_shell *shell);
void	restore_stdio(t_shell *shell);
void	redirection_error(t_shell *shell, int opt);
int		implement_redirection(t_shell *shell);


#endif