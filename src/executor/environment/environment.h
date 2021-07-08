#ifndef ENVIRONMENT_H
# define ENVIRONMENT_H

# include <stddef.h>

# define NOT_IN_ENVLIST -1

typedef struct s_envlist
{
	char				*name;
	char				*value;
	struct s_envlist	*next;
}				t_envlist;

typedef struct s_arg_with_envvar
{
	char	*start;
	char	*search_start;
	size_t	offset;
}				t_arg_with_envvar;

#endif