#ifndef EXECUTOR_H
# define EXECUTOR_H

#include "../shell_state.h"
#include <fcntl.h>
#include "environment/environment.h"

void	execute_command_line(t_treenode *top_node, t_shell *shell);
char	*locate_executable_path(t_treenode *simple_cmd_node);
int		run_simple_command(t_treenode *simple_cmd_node, t_shell *shell);

/*
** environment:
*/ 

int	        create_env_list(t_shell *shell);
int         is_envar(t_treenode *arg_node);
char        *replace_envar(t_treenode *arg_node, t_shell *shell);
int		    change_env_value(t_shell *shell, char *var_name, char *new_value);
char		*set_envar_name(char *argument);
t_envlist	*get_node_to_change(t_shell *shell, char *var_name);
int			add_to_env_list(char *envar_name, char *envar_value,
					t_envlist **env_list);


t_envlist	*ft_env_lstnew(char *name, char *value);
void	    ft_env_lstadd_back(t_envlist **lst, t_envlist *new);


/*
** utilities:
*/

char	*concat_path(char *left, char *right);

#endif
