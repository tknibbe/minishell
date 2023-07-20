/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exit_funcs.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: tknibbe <tknibbe@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/01 17:24:49 by tknibbe       #+#    #+#                 */
/*   Updated: 2023/07/19 20:37:50 by cvan-sch      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	ft_exit(char *string, int errnum)
{
	write(2, string, ft_strlen(string));
	exit(errnum);
}

void	p_exit(char *msg)
{
	write(2, "minishell: ", 12);
	perror(msg);
	exit(errno);
}
