/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   history.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: tknibbe <tknibbe@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/30 16:13:23 by tknibbe       #+#    #+#                 */
/*   Updated: 2023/07/03 20:52:07 by cvan-sch      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	history_management(const char *s)
{
	if (ft_strncmp(s, "", 1))
		add_history(s);
	//{
		//printf("--> %s: added to history\n", s);
	//}
	//else
	//	printf("not added\n");
	return (0);
}
