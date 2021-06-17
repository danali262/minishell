#ifndef REDIRECTION_H
# define REDIRECTION_H

# include "../shell_state.h"
# include <fcntl.h>
# include <sys/wait.h>
# include <stdbool.h>


#define READ 0
#define WRITE 1

void	check_for_redirection(t_treenode *syntax_tree, t_shell *shell);
void	restore_stdio(t_shell *shell);
void	redirection_error(t_shell *shell, int opt);
int		implement_redirection(t_shell *shell);

/*
** pipes aux:
*/

void	close_both_pipe_ends(int **pipes_fd, int i);
int		**create_pipes_fd_array(t_shell *shell);
bool	is_last_command(int i, int pipes_num);
bool	is_first_command(int i);
void	create_copy_of_file_descriptor(int **pipes_fd, int index, int pipe_end, t_shell *shell);

#endif