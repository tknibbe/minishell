/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_instr.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tknibbe <tknibbe@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 11:55:49 by tknibbe           #+#    #+#             */
/*   Updated: 2023/04/26 12:07:27 by tknibbe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

int	ft_instr(char *str, char *find)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	j = 0;
	k = 0;
	while (str[i])
	{
		if (str[i] == find[j])
		{
			k = i;
			while (str[k] == find[j])
			{
				if (!find[j])
					return (1);
				k++;
				j++;
			}
			j = 0;
		}
		i++;
	}
	return (0);
}
