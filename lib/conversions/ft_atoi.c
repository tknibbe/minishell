/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tknibbe <tknibbe@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 10:11:54 by tknibbe           #+#    #+#             */
/*   Updated: 2023/03/02 14:35:05 by tknibbe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

int	ft_atoi(const char *str)
{
	int			i;
	int			temp;
	int			plusormin;

	i = 0;
	temp = 0;
	plusormin = 1;
	while (str[i] == '\n' || str[i] == '\t' || str[i] == ' '
		|| str[i] == '\v' || str[i] == '\f' || str[i] == '\r')
		i++;
	if (str [i] == '+' || str [i] == '-')
	{
		if (str [i] == '-')
			plusormin *= -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		temp = (temp * 10) + (str[i] - '0');
		i++;
	}
	return (temp * plusormin);
}
