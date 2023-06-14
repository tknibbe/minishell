/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tknibbe <tknibbe@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 16:43:58 by tknibbe           #+#    #+#             */
/*   Updated: 2023/02/03 15:06:28 by tknibbe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	strlen;

	i = 0;
	strlen = ft_strlen(needle);
	if (!*needle)
		return ((char *)&haystack[0]);
	if (needle == 0)
		return ((char *)&haystack[i]);
	while (haystack[i] && strlen <= len)
	{
		if (ft_strncmp(&haystack[i], needle, strlen) == 0)
			return ((char *)&haystack[i]);
		i++;
		len--;
	}
	return (0);
}
