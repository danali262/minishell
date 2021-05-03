#ifndef PARSER_H
# define PARSER_H

#include "lexer/lexer.h"
#include "../reader/command_line_state.h"

// typedef struct	s_simplecommand
// {
// 	char	*command;
// 	char	*arg;
//     char    *last_element;      /* ought to be NULL, we will be using this array to provide input to execve */
// 	char	*input;
// 	char	*output;
// 	char	*err;
// }				t_simplecommand;
// 
// t_simplecommand	    *command_table;

typedef struct  s_treenode
{
    int						type;
    char					*data;
	int						children;			/* number of children */
    struct	s_treenode		*left;				/* rename it to first child..? */
    struct	s_treenode		*right;
	struct	s_treenode		*next_sibling;		/* useful because there may be more than two child nodes..? */
	struct	s_treenode		*prev_sibling;
}               t_treenode;

typedef	enum
{
	NODE_SEMI,							/* ; */
	NODE_PIPE,							/* | */
	NODE_CMD,							/* simple command */
	NODE_REDIRECT_IN,					/* < */
	NODE_REDIRECT_OUT,					/* > */
	NODE_APPEND,						/* >> */
	NODE_ARG,							/* argument */
	// NODE_PATH,							/* pathname */
	// NODE_FILE							/* filename */
}		t_nodetype;


int			parse_command_line(t_line *cmd_line);
int			parse(t_lexer *lexerbuf);
void		parser_functions(t_token *current_token);

t_treenode	*new_node(t_nodetype type);
void		free_node_tree(t_treenode *node);
void		set_node_val_str(t_treenode *node, char *val);
void		add_child_node(t_treenode *parent, t_treenode *child);

#endif
