#ifndef MINISHELL_H
#define MINISHELL_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

typedef struct  s_shell
{
    char	*buf;
    char    *cmd;
}               t_shell;

enum    e_tokentype
{
    CHAR_GENERAL = -1,
    CHAR_PIPE = '|',
    CHAR_AMPERSAND = '&',
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

char	*ft_strdup(const char *s);
char	*ft_strcat(char *src, char *append);
void	ft_putstr_fd(char *s, int fd);
char	**ft_split(char const *s, char c);
size_t	ft_strlen(const char *s);
size_t	ft_strlcpy(char *dst, const char *src, size_t size);

int		lexer_build(char *input, size_t size, t_lexer *lexerbuf);

#endif