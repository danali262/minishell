#ifndef SHELL_STATE_H
# define SHELL_STATE_H

# include "parser/lexer/lexer.h"
# include "command_history/history_state.h"
# include "term_cap/termcap_codes.h"

# define ERROR 1
# define SUCCESS 0

typedef struct  s_treenode
{
    int						*type;
    char					*data;
    struct	s_treenode		*left;
    struct	s_treenode		*right;
}               t_treenode;

typedef struct  s_shell
{
    t_treenode		*syntax_tree;
	t_history		history;
    t_line			cmd_line;
    t_termcap_codes	termcap_codes;
    char            *term_buffer;
    int				is_command_executed;
    int             exit_code;
    int             minishell_exits;
}               t_shell;

int		parse_command_line(t_shell *shell);
int		parser(t_lexer *lexerbuf, t_shell *shell);
void    init_tree(t_treenode *syntax_tree);

#endif
