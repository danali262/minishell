#ifndef LEXER_H
# define LEXER_H

# include "../../../libft/include/libft.h"

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>

#include "../../reader/command_line_state.h"


typedef struct  s_lexer_state
{
    t_line  *line;
    int     state;
    int     chtype;
}               t_lexer_state;

typedef struct  s_counters
{
    size_t i;
    size_t j;
}               t_counters;

enum    e_tokentype
{
    CHAR_GENERAL = -1,
    CHAR_PIPE = '|',
    CHAR_QUOTE = '\'',
    CHAR_DQUOTE = '\"',
    CHAR_SEMICOLON = ';',
    CHAR_WHITESPACE = ' ',
    CHAR_ESCAPESEQUENCE = '\\',
    CHAR_TAB = '\t',
    CHAR_NEWLINE = '\n',
    CHAR_GREATER = '>',
    CHAR_LESSER = '<',
    CHAR_NULL = 0,
    CHAR_EMPTY = '\0',

    TOKEN = -1
};

enum    e_states
{
    STATE_IN_DQUOTE,
    STATE_IN_QUOTE,
    STATE_IN_ESCAPESEQ,
    STATE_GENERAL
};

typedef struct	s_token
{
	char            *data;
	int	            type;
	struct s_token	*next;
}				t_token;

typedef struct	s_lexer
{
	t_token *tokens_list;
	int		tokens_nbr;
}				t_lexer;

// char	*ft_strdup(const char *s);
char	*ft_strcat(char *src, char *append);
// void	ft_putstr_fd(char *s, int fd);
char	**ft_split(char const *s, char c);
// size_t	ft_strlen(const char *s);
// size_t	ft_strlcpy(char *dst, const char *src, size_t size);


int		lexer_build(t_lexer_state *lex_state, t_lexer *lexerbuf);
void	tok_init(t_token *tok, int datasize);
void    print_tokens(t_lexer *lexerbuf);
void	free_token(t_token *tok);
t_token	*process_general_state(t_lexer_state *lex_state, t_token *token, t_counters *count, char c);
t_token	*process_others(t_lexer_state *lex_state, t_token *token, t_counters *count);
t_token	*new_token(t_lexer_state *lex_state, t_token *token, t_counters *count);
t_token	*process_dquote_state(t_lexer_state *lex_state, t_token *token, t_counters *count);
t_token	*process_quote_state(t_lexer_state *lex_state, t_token *token, t_counters *count);

#endif
