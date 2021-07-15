#ifndef SHELL_STATE_H
# define SHELL_STATE_H

# include "parser/lexer/lexer.h"
# include "command_history/history_state.h"
# include "term_cap/termcap_codes.h"
# include "executor/environment/environment.h"

# include <termios.h>

# define ERROR 1
# define SUCCESS 0

typedef struct s_treenode
{
	int						type;
	char					*data;
	struct s_treenode		*left;
	struct s_treenode		*right;
}				t_treenode;

typedef struct s_redirection
{
	int		redirect_in;
	int		redirect_out;
	int		redirect_app;
	int		redir_nbr;
	int		pipes_nbr;
	int		semi_nbr;
	char	*filename_in;
	char	*filename_out;
	char	*filename_app;
	int		first_nodetype;
	int		last_nodetype;
	int		fd;
	int		stdoutfd;
	int		stdinfd;
	int		pipe_read;
	int		pipe_write;
}			t_redirection;

typedef struct s_shell
{
	t_treenode		*syntax_tree;
	t_history		history;
	t_line			cmd_line;
	t_termcap_codes	termcap_codes;
	t_redirection	*redir;
	char			*term_buffer;
	t_envlist		*env_list;
	struct termios	origin_attr;
	int				is_command_executed;
	int				exit_code;
	int				minishell_exits;
}				t_shell;

/* 0. ; */
/* 1. | */
/* 2. < */
/* 3. > */
/* 4. >> */
/* 5. <> */
/* 6. filename */
/* 7. pathname */
/* 9. variable */
/* 10. empty */

typedef enum e_nodetype
{
	NODE_SEMI,
	NODE_PIPE,
	NODE_REDIRECT_IN,
	NODE_REDIRECT_OUT,
	NODE_APPEND,
	NODE_RHOMBUS,
	NODE_FILE,
	NODE_PATH,
	NODE_ARG,
	NODE_VAR,
	NODE_EMPTY		
}		t_nodetype;

int		parse_command_line(t_shell *shell);
int		parser(t_lexer_state *lex_state, t_shell *shell);

#endif
