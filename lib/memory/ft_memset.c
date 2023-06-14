/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tknibbe <tknibbe@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 15:04:17 by tknibbe           #+#    #+#             */
/*   Updated: 2023/02/24 16:20:44 by tknibbe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

void	*ft_memset(void *b, int c, size_t len)
{
	size_t	i;
	char	*tempb;

	i = 0;
	tempb = b;
	while (i < len)
	{
		tempb[i] = c;
		i++;
	}
	return (b);
}
