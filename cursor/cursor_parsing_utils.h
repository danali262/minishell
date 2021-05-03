/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cursor_parsing_utils.h                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: osamara <osamara@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/01/23 16:52:24 by osamara       #+#    #+#                 */
/*   Updated: 2021/04/30 15:14:42 by osamara       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef CURSOR_PARSING_UTILS_H
# define CURSOR_PARSING_UTILS_H

int		is_valid_component(const char *string, int *component);
char	**split_into_components(char *line, char separator, int num_components);


#endif
