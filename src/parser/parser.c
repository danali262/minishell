#include "lexer/lexer.h"
#include "parser.h"

int	parser(t_lexer_state *lex_state, t_shell *shell)
{
	t_curtok	curtok;

	curtok.current_token = lex_state->tokens_list;
	shell->syntax_tree = command_line(&curtok);
	if (curtok.current_token != NULL && curtok.current_token->type != 0)
	{
		if (lex_state->spaces_flag == 0)
		{
			shell->exit_code = 0;
			return (ERROR);
		}
		ft_putstr_fd("Syntax Error near: ", STDOUT_FILENO);
		ft_putstr_fd(curtok.current_token->data, STDOUT_FILENO);
		ft_putstr_fd("\n", STDOUT_FILENO);
		shell->exit_code = 258;
		return (ERROR);
	}
	return (SUCCESS);
}
