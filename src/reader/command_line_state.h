/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   command_line_state.h                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: osamara <osamara@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/04/26 13:36:57 by osamara       #+#    #+#                 */
/*   Updated: 2021/05/01 20:05:50 by osamara       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMAND_LINE_STATE_H
#define COMMAND_LINE_STATE_H

# include <stddef.h>
# include <limits.h>

# define BUF_SIZE ARG_MAX
# define PROMPT "minishell-0.1$ " // temp prompt to differentiate from original bash
// # define PROMPT "bash-3.2$ "

typedef struct s_line
{
	char	*buf;
	size_t	line_len;
}				t_line;


#endif
