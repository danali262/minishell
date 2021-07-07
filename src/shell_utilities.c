#include "shell_utilities.h"
#include "shell_state.h"
#include "executor/executor.h"
#include "reader/read_command_line.h"
#include "term_cap/init_terminal_data.h"

#include <stdbool.h>

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
	shell->redir->semi_nbr = 0;
	shell->redir->filename_in = NULL;
	shell->redir->filename_out = NULL;
	shell->redir->filename_app = NULL;
	shell->redir->saved_nodetype = NODE_EMPTY;
	shell->redir->stdinfd = dup(STDIN_FILENO);
	shell->redir->stdoutfd = dup(STDOUT_FILENO);
}

int	init_shell(t_shell *shell)
{
	if (init_command_line(&shell->cmd_line) == ERROR
		|| init_terminal_data(shell) == ERROR
		|| create_env_list(shell) == ERROR)
		return (ERROR);
	init_history(&shell->history);
	shell->is_command_executed = 0;
	shell->exit_code = 0;
	shell->minishell_exits = false;
	return (SUCCESS);
}

void	free_shell_data(t_shell *shell)
{
	free(shell->term_buffer);
	free_command_line(&shell->cmd_line);
	free_history(&shell->history);
	free_env_list(shell->env_list, ft_env_lstdelone);
}

int	is_redirect_type(t_token *head)
{
	if (head->type == CHAR_GREATER || head->type == CHAR_LESSER
		|| head->type == CHAR_APPEND || head->type == CHAR_RHOMBUS)
		return (1);
	else
		return (0);
}

int	is_redirect_node(t_treenode *node)
{
	if (node->type == NODE_REDIRECT_IN || node->type == NODE_REDIRECT_OUT
		|| node->type == NODE_APPEND || node->type == NODE_RHOMBUS)
		return (1);
	else
		return (0);
}
