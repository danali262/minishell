#ifndef PIPES_H
# define PIPES_H

# include "../shell_state.h"

# include <stdbool.h>


#define READ 0
#define WRITE 1

/*
** pipes:
*/
int		handle_pipeline(t_treenode *node, t_shell *shell);
pid_t	*loop_through_pipes(t_treenode *node, int **pipes_fd, t_shell *shell);
void	handle_parent_process(int **pipes_fd, int i);
void	handle_child_process(t_treenode *node, int **pipes_fd, int i,
	t_shell *shell);

/*
** pipes aux:
*/

void	close_both_pipe_ends(int **pipes_fd, int i);
int		**create_pipes_fd_array(t_shell *shell);
bool	is_last_command(int i, int pipes_num);
bool	is_first_command(int i);
void	create_copy_of_fd_for_pipes(int **pipes_fd, int index, int pipe_end,
		t_shell *shell);
void	create_pipeline(int **fd_for_pipeline);

#endif
