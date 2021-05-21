/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_calculate_array.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: osamara <osamara@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/05/20 14:22:30 by osamara       #+#    #+#                 */
/*   Updated: 2021/05/20 14:23:17 by osamara       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int ft_calculate_array_size(char **array)
{
    int	i;

    i = 0;
	while (array[i] != NULL)
		i++;
	return (i);
}
