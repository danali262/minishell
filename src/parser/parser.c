#include "lexer/lexer.h"
#include "parser.h"
#include "../shell_utilities.h"

int	parser(t_lexer_state *lex_state, t_shell *shell)
{
	t_curtok	curtok;
	int			flag;

	flag = 0;
	curtok.current_token = lex_state->tokens_list;
	if (is_redirect_type(curtok.current_token))
		flag = 1;
	shell->syntax_tree = command_line(&curtok);
	if ((curtok.current_token != NULL && curtok.current_token->type != 0)
		|| (lex_state->tokens_nbr == 2 && flag == 1))
	{
		ft_putstr_fd("Syntax Error near: ", STDOUT_FILENO);
		ft_putstr_fd(curtok.current_token->data, STDOUT_FILENO);
		ft_putstr_fd("\n", STDOUT_FILENO);
		shell->exit_code = 258;
		return (ERROR);
	}
	return (SUCCESS);
}
