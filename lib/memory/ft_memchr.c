/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tknibbe <tknibbe@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 15:16:54 by tknibbe           #+#    #+#             */
/*   Updated: 2023/02/03 15:06:18 by tknibbe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	temp_c;
	unsigned char	*temp_s;

	i = 0;
	temp_c = (unsigned char) c;
	temp_s = (unsigned char *) s;
	while (i < n)
	{
		if (temp_s[i] == temp_c)
			return (&temp_s[i]);
		i++;
	}
	return (0);
}
