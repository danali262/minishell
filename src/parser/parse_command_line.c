#include "parser.h"

// void	print_tokens(t_lexer *lexerbuf)         /* to be deleted */
// {
// 	t_token	*head;

// 	head = lexerbuf->tokens_list;
// 	printf("tokens are:\n");
// 	while (head != NULL)
// 	{
// 		printf("|%s|\t|%d|\n", head->data, head->type);
// 		head = head->next;
// 	}
// }

int	parse_command_line(t_shell *shell)
{
	t_lexer_state	lex_state;
	t_lexer			lexerbuf;
	int				lexer_result;

	lex_state.line = &shell->cmd_line;
	lexer_result = lexer_build(&lex_state, &lexerbuf);
	if (lexer_result == -1)
		return (-1);
	else if (lexer_result == 0)
		return (0);
	// printf("tokens with quotes:\n");
	// print_tokens(&lexerbuf);        /* to be deleted */
	if (parser(&lexerbuf, shell) == -1)
		return (-1);
    return (1);
}
