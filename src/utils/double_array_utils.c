/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   double_array_utils.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: cvan-sch <cvan-sch@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/29 15:58:29 by cvan-sch      #+#    #+#                 */
/*   Updated: 2023/08/16 12:49:06 by cvan-sch      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>

int	count(char **c)
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
