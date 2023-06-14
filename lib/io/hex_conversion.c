/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hex_conversion.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tknibbe <tknibbe@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 11:18:28 by tknibbe           #+#    #+#             */
/*   Updated: 2023/02/03 15:24:15 by tknibbe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

int	p_conversion(unsigned long s)
{
	write(1, "0x", 2);
	return (hex_conversion(s, "0123456789abcdef", 0) + 2);
}

int	lower_x_conversion(unsigned int s)
{
	return (hex_conversion(s, "0123456789abcdef", 0));
}

int	upper_x_conversion(unsigned int s)
{
	return (hex_conversion(s, "0123456789ABCDEF", 0));
}

int	hex_conversion(unsigned long s, char *hex, int count)
{
	int	temp;

	if (s >= 16)
	{
		temp = s % 16;
		count = hex_conversion((s / 16), hex, count);
		write(1, &hex[temp], 1);
		count++;
	}
	if (s < 16)
	{
		write(1, &hex[s], 1);
		count++;
	}
	return (count);
}
