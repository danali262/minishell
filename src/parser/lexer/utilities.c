#include "lexer.h"

// void	*ft_memcpy(void *dst, const void *src, size_t n)
// {
// 	unsigned char	*s;
// 	unsigned char	*d;
// 
// 	s = NULL;
// 	d = NULL;
// 	s = (unsigned char *)src;
// 	d = (unsigned char *)dst;
// 	if (dst == 0 && src == 0)
// 		return (dst);
// 	while (n > 0)
// 	{
// 		*d = *s;
// 		d++;
// 		s++;
// 		n--;
// 	}
// 	return (dst);
// }
// 
// size_t	ft_strlen(const char *s)
// {
// 	size_t	i;
// 
// 	i = 0;
// 	while (*s)
// 	{
// 		i++;
// 		s++;
// 	}
// 	return (i);
// }
// 
// static void	ft_bzero(void *s, size_t n)
// {
// 	unsigned char	*ptr;
// 
// 	ptr = NULL;
// 	ptr = (unsigned char *)s;
// 	while (n > 0)
// 	{
// 		*ptr = '\0';
// 		ptr++;
// 		n--;
// 	}
// }

// static void	*ft_calloc(size_t nmemb, size_t size)
// {
// 	void	*ptr;
// 
// 	if (nmemb == 0 || size == 0)
// 	{
// 		nmemb = 1;
// 		size = 1;
// 	}
// 	ptr = malloc(nmemb * size);
// 	if (ptr == NULL)
// 		return (ptr);
// 	ft_bzero(ptr, nmemb * size);
// 	return (ptr);
// }

// char	*ft_strdup(const char *s)
// {
// 	int		len;
// 	char	*ptr;
// 	char	*str;
// 
// 	str = (char *)s;
// 	len = ft_strlen(str) + 1;
// 	ptr = ft_calloc(len, sizeof(char));
// 	if (!ptr)
// 		return (NULL);
// 	ft_memcpy(ptr, str, len);
// 	return (ptr);
// }

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
	int		x;
	char	*dest;

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

// void	ft_putstr_fd(char *s, int fd)
// {
// 	int	i;
// 	int	n;
// 
// 	i = 0;
// 	while (s[i] != '\0')
// 	{
// 		n = write(fd, &s[i], 1);
// 		if (n < 0)
// 			return ;
// 		i++;
// 	}
// }

// size_t	ft_strlcpy(char *dst, const char *src, size_t size)
// {
// 	size_t	res;
// 
// 	res = 0;
// 	if (size > 0)
// 	{
// 		while (src[res] && res < (size - 1))
// 		{
// 			dst[res] = src[res];
// 			res++;
// 		}
// 		dst[res] = '\0';
// 	}
// 	while (src[res])
// 		res++;
// 	return (res);
// }

// char	*ft_substr(char const *s, unsigned int start, size_t len)
// {
// 	char			*res;
// 
// 	if (ft_strlen(s) <= start)
// 		return ((char *)ft_calloc(1, sizeof(char)));
// 	if (ft_strlen(s) - start < len)
// 		len = ft_strlen(s) - start;
// 	res = (char *)malloc((len + 1) * sizeof(char));
// 	if (res == NULL)
// 		return (NULL);
// 	ft_strlcpy(res, s + start, len + 1);
// 	return (res);
// }
// 
// static int		string_number(char const *s, char c)
// {
// 	int num;
// 	int i;
// 	int strlen;
// 
// 	num = 0;
// 	i = 0;
// 	strlen = 0;
// 	while (s[i] != '\0')
// 	{
// 		if (s[i] == c)
// 		{
// 			if (strlen != 0)
// 				num++;
// 			strlen = 0;
// 		}
// 		else
// 			strlen++;
// 		i++;
// 	}
// 	if (strlen != 0)
// 		return (num + 1);
// 	else
// 		return (num);
// }
// 
// static void		*free_strings(char **array, int i)
// {
// 	while (i > 0)
// 	{
// 		i--;
// 		free(array[i]);
// 	}
// 	free(array);
// 	return (NULL);
// }
// 
// static char		**do_split(char const *s, char c, char **array, int str_num)
// {
// 	int		word;
// 	int		strlen;
// 	int		i;
// 
// 	i = 0;
// 	word = 0;
// 	strlen = 0;
// 	while (word < str_num)
// 	{
// 		if (s[i] == c || s[i] == '\0')
// 		{
// 			if (strlen != 0)
// 			{
// 				array[word] = ft_substr(s + i - strlen, 0, strlen);
// 				if (array[word] == NULL)
// 					return (free_strings(array, word - 1));
// 				word++;
// 			}
// 			strlen = 0;
// 		}
// 		else
// 			strlen++;
// 		i++;
// 	}
// 	return (array);
// }
// 
// char			**ft_split(char const *s, char c)
// {
// 	char	**array;
// 	int		str_num;
// 
// 	if (s == 0)
// 		return (NULL);
// 	str_num = string_number(s, c);
// 	array = (char **)malloc((str_num + 1) * sizeof(char *));
// 	if (array == NULL)
// 		return (NULL);
// 	array = do_split(s, c, array, str_num);
// 	array[str_num] = NULL;
// 	return (array);
// }