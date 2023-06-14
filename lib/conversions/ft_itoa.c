/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tknibbe <tknibbe@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 18:20:29 by tknibbe           #+#    #+#             */
/*   Updated: 2023/02/03 15:07:40 by tknibbe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

static char	*max_int(int n)
{
	char	*temp;
	int		i;

	i = 9;
	temp = malloc(sizeof(char) * 12);
	if (temp == 0)
		return (0);
	temp[11] = '\0';
	temp[10] = '8';
	n = n / 10;
	n = n * -1;
	while (i > 0)
	{
		temp[i] = (n % 10) + '0';
		n = n / 10;
		i--;
	}
	temp[i] = '-';
	return (temp);
}

static int	length_str(int n, int minorpos)
{
	int	i;

	i = 1;
	if (minorpos < 0)
		i++;
	while (n > 9)
	{
		n = n / 10;
		i++;
	}
	return (i);
}

static char	*mem_alloc(int n, int length, int minorpos)
{
	char	*temp;

	temp = malloc(sizeof(char) * (length + 1));
	if (temp == 0)
		return (0);
	temp[length] = '\0';
	length--;
	while (length >= 0)
	{
		temp[length] = (n % 10) + '0';
		n = n / 10;
		length--;
	}
	if (minorpos < 0)
		temp[0] = '-';
	return (temp);
}

char	*ft_itoa(int n)
{
	char	*temp;
	int		length;
	int		minorpos;

	minorpos = 1;
	if (n < 0)
	{
		minorpos = -1;
		n = n * -1;
	}
	if (n == -2147483648)
	{
		temp = max_int(n);
		return (temp);
	}
	length = length_str(n, minorpos);
	temp = mem_alloc(n, length, minorpos);
	return (temp);
}
