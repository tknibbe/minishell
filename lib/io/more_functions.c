/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   more_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tknibbe <tknibbe@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 11:19:56 by tknibbe           #+#    #+#             */
/*   Updated: 2023/02/03 15:24:18 by tknibbe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

int	out_unsigned_nbr(int count, unsigned int n)
{
	int	temp;

	if (n > 9)
	{
		temp = (n % 10) + '0';
		count = out_nbr(count, n / 10);
		write(1, &temp, 1);
		count++;
	}
	if (n <= 9)
	{
		n = n + '0';
		write(1, &n, 1);
		count++;
	}
	return (count);
}

int	out_nbr(int count, int n)
{
	int	temp;

	if (n == -2147483648)
		return (write(1, "-2147483648", 11));
	if (n < 0)
	{
		count += write(1, "-", 1);
		n = n * -1;
	}
	if (n > 9)
	{
		temp = (n % 10) + '0';
		count = out_nbr(count, n / 10);
		write(1, &temp, 1);
		count++;
	}
	if (n <= 9)
	{
		n = n + '0';
		write(1, &n, 1);
		count++;
	}
	return (count);
}

int	ft_strlength(const char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

int	write_substr(char const *s, unsigned int start, size_t len)
{
	return (write(1, &s[start], len));
}
