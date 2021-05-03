#include "lexer/lexer.h"
#include "parser.h"

t_token	*current_token = NULL;

int	parse(t_lexer *lexerbuf)
{
	if (!lexerbuf->tokens_nbr)
		return (-1);
	current_token = lexerbuf->tokens_list;
	parser_functions(current_token);
	return (0);
}