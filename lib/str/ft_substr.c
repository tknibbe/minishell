/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tknibbe <tknibbe@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 08:28:30 by tknibbe           #+#    #+#             */
/*   Updated: 2023/02/03 15:07:05 by tknibbe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*temp;
	size_t	i;
	size_t	j;

	i = start;
	j = 0;
	if (len > ft_strlen(s) - start)
		len = ft_strlen(s) - start;
	if (len <= 0 || start >= (size_t)ft_strlen(s) || !s[j])
		return (ft_calloc(1, 1));
	if (len > (size_t)ft_strlen(s))
		temp = malloc(sizeof(char) * ft_strlen(s) + 1);
	else
		temp = malloc(sizeof(char) * len + 1);
	if (temp == 0)
		return (0);
	while (j < len && s[i])
	{
		temp[j] = s[i];
		j++;
		i++;
	}
	temp[j] = '\0';
	return (temp);
}
