/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tknibbe <tknibbe@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 09:32:41 by tknibbe           #+#    #+#             */
/*   Updated: 2023/02/03 15:06:23 by tknibbe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*temps1;
	unsigned char	*temps2;
	size_t			i;

	i = 0;
	temps1 = (unsigned char *) s1;
	temps2 = (unsigned char *) s2;
	if (n == 0)
		return (0);
	while ((i + 1) < n && temps1[i] == temps2[i])
	{
		i++;
	}
	return ((unsigned char)temps1[i] - (unsigned char)temps2[i]);
}
