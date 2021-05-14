#include "lexer/lexer.h"
#include "parser.h"
#include "../shell_state.h"

// void	print_tokens(t_lexer *lexerbuf)         /* to be deleted */
// {
// 	t_token	*head;

// 	head = lexerbuf->tokens_list;
// 	while (head != NULL)
// 	{
// 		printf("%s\n", head->data);
// 		head = head->next;
// 	}
// }

int	parse_command_line(t_line *cmd_line, t_shell *shell)
{
	t_lexer_state	lex_state;
	t_lexer			lexerbuf;

	lex_state.line = cmd_line;
	if (lexer_build(&lex_state, &lexerbuf) == -1)
		return (0);
	// print_tokens(&lexerbuf);        /* to be deleted */
	if (parser(&lexerbuf, shell) == -1)
		return (0);
	return (1);
}
