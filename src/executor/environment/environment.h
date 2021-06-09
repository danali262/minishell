#ifndef ENVIRONMENT_H
# define ENVIRONMENT_H

# define NOT_IN_ENVLIST -1

typedef struct s_envlist
{
	char				*name;
	char				*value;
	struct s_envlist	*next;
}				t_envlist;

#endif