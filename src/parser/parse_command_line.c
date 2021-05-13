#include "lexer/lexer.h"
#include "parser.h"

void    print_tokens(t_lexer *lexerbuf)
{
    t_token *head;

    head = lexerbuf->tokens_list;
    while (head != NULL)
    {
        printf("%s\n", head->data);
        head = head->next;
    }
}

int	parse_command_line(t_line *cmd_line, t_treenode *syntax_tree)
{
	t_lexer_state	lex_state;
	t_lexer			lexerbuf;
    // t_treenode      syntax_tree;

    lex_state.line = cmd_line;
    if (lexer_build(&lex_state, &lexerbuf) == -1)
		return (0);
	print_tokens(&lexerbuf);
    if (parser(&lexerbuf, syntax_tree) == -1)
        return (0);
    return (1);
}