#ifndef SHELL_STATE_H
# define SHELL_STATE_H

# include "parser/lexer/lexer.h"
# include "command_history/history_state.h"
# include "term_cap/termcap_codes.h"
# include "executor/environment/environment.h"

# define ERROR 1
# define SUCCESS 0

typedef struct  s_treenode
{
    int						type;
    char					*data;
    struct	s_treenode		*left;
    struct	s_treenode		*right;
}               t_treenode;

typedef struct s_redirection
{
	int     redirect_in;
	int     redirect_out;
	int		redirect_app;
	int		redir_nbr;
	int		pipes_nbr;
	int		semi_nbr;
	char	*filename_in;
	char	*filename_out;
	char	*filename_app;
	int		saved_nodetype;
	int		fd;
	int		stdoutfd;
	int		stdinfd;
	int		pipe_read;
	int		pipe_write;
}			t_redirection;


typedef struct  s_shell
{
    t_treenode		*syntax_tree;
	t_history		history;
    t_line			cmd_line;
    t_termcap_codes	termcap_codes;
    t_redirection   *redir;
    char            *term_buffer;
    t_envlist		*env_list;
    int				is_command_executed;
    int             exit_code;
	int             minishell_exits;
	int				is_newline;
}               t_shell;

typedef	enum
{
	NODE_SEMI,							/* 0. ; */
	NODE_PIPE,							/* 1. | */
	NODE_REDIRECT_IN,					/* 2. < */
	NODE_REDIRECT_OUT,					/* 3. > */
	NODE_APPEND,						/* 4. >> */
	NODE_RHOMBUS,						/* 5. <> */
	NODE_FILE,							/* 6. filename */
	NODE_PATH,							/* 7. pathname */
	NODE_ARG,							/* 8. argument */
	NODE_VAR,							/* 9. variable */
	NODE_EMPTY							/* 10. empty */
}		t_nodetype;

int		parse_command_line(t_shell *shell);
int		parser(t_lexer_state *lex_state, t_shell *shell);
void    init_tree(t_shell *syntax_tree);

#endif
