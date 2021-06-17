#include "../shell_state.h"

void	init_tree(t_shell *shell)
{
	shell->syntax_tree->data = NULL;
	shell->syntax_tree->type = NODE_EMPTY;
	shell->syntax_tree->left = NULL;
	shell->syntax_tree->right = NULL;
	shell->redir->redirect_in = 0;
	shell->redir->redirect_out = 0;
	shell->redir->redirect_app = 0;
	shell->redir->redir_nbr = 0;
	shell->redir->pipes_nbr = 0;
	shell->redir->filename_in = NULL;
	shell->redir->filename_out = NULL;
	shell->redir->filename_app = NULL;
}
