#include "redirection.h"
#include "../parser/parser.h"

void	redirection_error(t_shell *shell, int opt)
{
	ft_putstr_fd("File handling error in redirection.\n", STDOUT_FILENO);
	delete_node(&shell->syntax_tree);
	if (opt == 1)
		free(shell->redir->filename_in);
	else if (opt == 2)
		free(shell->redir->filename_out);
	else
		free(shell->redir->filename_app);
	exit(1);
}
