/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tknibbe <tknibbe@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 16:13:23 by tknibbe           #+#    #+#             */
/*   Updated: 2023/06/30 16:14:41 by tknibbe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	history_management(const char *s)
{
	if (ft_strncmp(s, "", 1) > 0)
	{
		add_history(s);
		printf("--> %s: added to history\n", s);
	}
	else
		printf("not added\n");
	return (0);
}
