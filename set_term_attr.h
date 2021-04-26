/* ************************************************************************* */
/*                                                                            */
/*                                                        ::::::::            */
/*   set_term_attr.h                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: osamara <osamara@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/04/25 13:38:57 by osamara       #+#    #+#                 */
/*   Updated: 2021/04/25 13:38:57 by osamara       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef SET_TERM_ATTR_H
# define SET_TERM_ATTR_H
 
#include "line_state.h"

# define MAX_HISTORY 100
// # define TRUE 1

typedef struct s_history
{
	t_line	line_state[MAX_HISTORY];
}				t_history;

#endif
