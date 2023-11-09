/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   double_array_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tknibbe <tknibbe@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 15:58:29 by cvan-sch          #+#    #+#             */
/*   Updated: 2023/11/09 15:11:22 by tknibbe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_dp(char **c)
{
	int	i;

	i = 0;
	while (c[i])
		i++;
	return (i);
}

void	free_dp(char **dp)
{
	int	i;

	i = 0;
	if (!dp)
		return ;
	while (dp[i])
	{
		free(dp[i]);
		i++;
	}
	free(dp);
}

void	print_double_array(char **x)
{
	int	i;

	i = 0;
	while (*x)
		printf("%d: %s\n", i++, *(x++));
	printf("(null)\n");
}
