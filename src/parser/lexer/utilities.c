#include "lexer.h"

static char	*ft_fill(char *src, char *append, char *dest)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	while (append[j] != '\0')
	{
		dest[i] = append[j];
		i++;
		j++;
	}
	dest[i] = '\0';
	return (dest);
}

char	*ft_strcat(char *src, char *append)
{
	size_t		x;
	char		*dest;

	x = ft_strlen(src) + ft_strlen(append);
	dest = (char *)malloc(sizeof(char) * (x + 1));
	if (!dest)
	{
		free(append);
		free(src);
		return (0);
	}
	dest = ft_fill(src, append, dest);
	free(append);
	free(src);
	return (dest);
}
