#ifndef REDIRECTION_H
# define REDIRECTION_H

# include "../shell_state.h"
# include <fcntl.h>
# include <sys/wait.h>
# include "../executor/executor.h"

int		check_for_redirection(t_treenode *syntax_tree, t_shell *shell);
int		implement_redirection(t_shell *shell);
int		multiple_redirection(t_treenode *syntax_tree, t_shell *shell);
void	simple_redirection(t_treenode *syntax_tree, t_shell *shell);
void	restore_stdio(t_shell *shell);
void	redirection_error(t_shell *shell, int opt);
void	assign_file_multiple(t_treenode *syntax_tree, t_shell *shell, int
			type);
void	handle_multiple_append(t_treenode *node, int saved_type, t_shell
			*shell);
void	check_node_type(t_treenode *node, t_shell *shell);
void	handle_redirect_node_execution(t_treenode *node, t_shell *shell);

#endif