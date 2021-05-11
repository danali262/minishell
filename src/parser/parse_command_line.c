#include "lexer/lexer.h"
#include "parser.h"
#include "../executor/executor.h"

void    print_tokens(t_lexer *lexerbuf)
{
    t_token *head;

    head = lexerbuf->tokens_list;
    while (head != NULL)
    // while (head->next != NULL)
    {
        printf("%s\n", head->data);
        head = head->next;
    }
}

int	parse_command_line(t_line *cmd_line)
{
	t_lexer_state	lex_state;
	t_lexer			lexerbuf;

    lex_state.line = cmd_line;
    if (lexer_build(&lex_state, &lexerbuf) == -1)
		return (0);
    print_tokens(&lexerbuf);
    execute_command(&lexerbuf);
    return (1);
}