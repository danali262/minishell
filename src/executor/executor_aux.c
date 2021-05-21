#include "executor.h"

#include "libft.h"

#include <stdlib.h>

char	*concat_path(char *left, char *right)
{
	char	*path;
	size_t	left_len;
	size_t	right_len;

	left_len = ft_strlen(left);
	right_len = ft_strlen(right);

	path = malloc(sizeof(char) * (left_len + right_len) + 2);
	if (!path)
	{
		printf("Error: unable to allocate memory for the path.\n");
		return (NULL);
	}
	ft_memmove(path, left, left_len);
	path[left_len] = '/';
	ft_memmove(path + left_len + 1, right, right_len);
	path[left_len + right_len + 2] = '\0';
	return (path);
}