/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tknibbe <tknibbe@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 12:04:54 by tknibbe           #+#    #+#             */
/*   Updated: 2023/02/03 15:05:49 by tknibbe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	dstlen;
	size_t	srclen;
	size_t	output;
	char	*s;

	s = (char *)src;
	dstlen = ft_strlen(dst);
	srclen = ft_strlen(src);
	i = 0;
	if (dstlen > dstsize)
		output = dstsize + srclen;
	else
		output = dstlen + srclen;
	while (s[i] && (dstlen + 1) < dstsize)
	{
		dst[dstlen] = s[i];
		i++;
		dstlen++;
	}
	dst[dstlen] = '\0';
	return (output);
}
