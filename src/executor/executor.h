#ifndef EXECUTOR_H
# define EXECUTOR_H

#include "../shell_state.h"
#include <fcntl.h>
#include "environment/environment.h"

#include <stdbool.h>

void	execute_command_line(t_treenode *top_node, t_shell *shell);
char	*locate_executable_path(t_treenode *simple_cmd_node);
int		run_simple_command(t_treenode *simple_cmd_node, t_shell *shell);

/*
** environment variables:
*/ 

int         is_envar(t_treenode *arg_node);
char		*handle_argument_with_envvars(t_treenode *arg_node, t_shell *shell);
char		*replace_name_with_value(char *envvar_start, t_shell *shell, size_t *envvar_len,
			bool is_in_str);
char		*replace_dollar_question(char *envvar, t_shell *shell, bool is_in_str);
int		    change_env_value(t_shell *shell, char *var_name, char *new_value);
char		*get_envar_name(char *argument);
char 	*update_argument(char *new_arg_value, char *temp);
char	*create_substring(char *start, size_t len);
char	*create_new_argument_string(char *search_start, t_shell *shell);

/*
**	environment list:
*/

int	        create_env_list(t_shell *shell);
int			add_to_env_list(char *envar_name, char *envar_value,
					t_envlist **env_list);
int	update_env_list(t_shell *shell, char *envar_name, char *value_start);

/*
** environment aux:
*/ 
int			has_alpha_char(char *name, int	length);
void		update_old_pwd(char	*envar_value, t_shell *shell);
t_envlist	*get_node_to_change(t_shell *shell, char *var_name);

t_envlist	*ft_env_lstnew(char *name, char *value);
void	    ft_env_lstadd_back(t_envlist **lst, t_envlist *new);
void	ft_env_lstadd_before_last_node(t_envlist **lst, t_envlist *new);
void	ft_env_lstdelone(t_envlist **lst);
void	free_env_list(t_envlist *lst, void (*f)(t_envlist **));

/*
** utilities:
*/

char	*concat_path(char *left, char *right);

char		*strip_quotes(char *arg);

#endif
