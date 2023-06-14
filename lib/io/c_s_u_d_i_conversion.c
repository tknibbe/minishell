/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   c_s_u_d_i_conversion.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tknibbe <tknibbe@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 17:36:45 by tknibbe           #+#    #+#             */
/*   Updated: 2023/02/03 15:24:13 by tknibbe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

int	c_conversion(int s)
{
	return (write(1, &s, 1));
}

int	s_conversion(char *s)
{
	if (s == 0)
		return (write(1, "(null)", 6));
	return (write(1, s, ft_strlen(s)));
}

int	d_conversion(int s)
{
	return (out_nbr(0, s));
}

int	i_conversion(int s)
{
	return (out_nbr(0, s));
}

int	u_conversion(unsigned int s)
{
	return (out_unsigned_nbr(0, s));
}
