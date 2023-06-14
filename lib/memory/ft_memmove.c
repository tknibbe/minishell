/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tknibbe <tknibbe@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 14:42:33 by tknibbe           #+#    #+#             */
/*   Updated: 2023/02/03 15:05:13 by tknibbe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	char	*tempdst;
	char	*tempsrc;
	int		i;

	tempdst = (char *)dst;
	tempsrc = (char *)src;
	if (dst == 0 && src == 0)
		return (0);
	if (tempdst < tempsrc)
	{
		i = 0;
		while (i < (int)len)
		{
			tempdst[i] = tempsrc[i];
			i++;
		}
		return (dst);
	}
	i = len - 1;
	while (i >= 0)
	{
		tempdst[i] = tempsrc[i];
		i--;
	}
	return (dst);
}
