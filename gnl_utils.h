/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   gnl_utils.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: osamara <osamara@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/04/26 14:08:32 by osamara       #+#    #+#                 */
/*   Updated: 2021/04/28 15:30:48 by osamara       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef GNL_UTILS_H
# define GNL_UTILS_H

#include "command_history.h"
#include "line_state.h"

int	read_command_line(int fd, t_history *history, t_line *line_state);


#endif
