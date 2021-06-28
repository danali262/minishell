#ifndef EXECUTOR_H
# define EXECUTOR_H

# include "../shell_state.h"
# include <fcntl.h>
# include "environment/environment.h"

# include <stdbool.h>

/*
** environment aux:
*/

t_envlist	*get_node_to_change(t_shell *shell, char *var_name);
t_envlist	*ft_env_lstnew(char *name, char *value);
int			has_alpha_char(char *name, int	length);
void		update_old_pwd(char	*envar_value, t_shell *shell);
void		ft_env_lstadd_back(t_envlist **lst, t_envlist *new);
void		ft_env_lstadd_before_last_node(t_envlist **lst, t_envlist *new);
void		ft_env_lstdelone(t_envlist **lst);
void		free_env_list(t_envlist *lst, void (*f)(t_envlist **));
void		run_executor(t_shell *shell);
void		execute_command_line(t_treenode *top_node, t_shell *shell);
void		execute_job(t_treenode *job_node, t_shell *shell);
char		*locate_executable_path(t_treenode *simple_cmd_node,
				t_shell *shell);
int			run_simple_command(t_treenode *simple_cmd_node, t_shell *shell);
void		wait_for_child(pid_t pid, t_shell *shell);
void		execute_system_function(char **argv, t_shell *shell);
char		**fill_args_list(t_treenode *simple_cmd_node, char *executable_path,
				t_shell *shell);

/*
** environment variables:
*/

int			is_envar(t_treenode *arg_node);
char		*handle_argument_with_envvars(t_treenode *arg_node, t_shell *shell);
char		*replace_name_with_value(char *envvar_start, t_shell *shell,
				size_t *envvar_len);
char		*replace_dollar_question(t_shell *shell);
int			change_env_value(t_shell *shell, char *var_name, char *new_value);
char		*create_envar_name(char *argument);
char		*update_argument(char *new_arg_value, char *temp);
char		*create_substring(char *start, size_t len);
char		*create_new_argument_string(char *search_start, t_shell *shell);
char		*get_envar_value(char *command, t_shell *shell);

/*
**	environment list:
*/

int			create_env_list(t_shell *shell);
int			add_to_env_list(char *envar_name, char *envar_value,
				t_envlist **env_list);
int			update_env_list(t_shell *shell, char *envar_name,
				char *value_start);
int			can_update_env_list(t_shell *shell, char *envar_name, char *string);

/*
** utilities:
*/

char		*concat_path(char *left, char *right);
char		*check_envars_and_quotes(t_treenode *arg_node, t_shell *shell);
void		check_fork_error(pid_t pid, t_shell *shell);
bool		is_command(char *str_to_compare, char *command);

char		*strip_quotes(char *arg);
bool		is_wrapped_by_single_quotes(char *arg_string);

#endif
