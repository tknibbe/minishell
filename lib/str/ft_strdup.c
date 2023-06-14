/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tknibbe <tknibbe@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 08:10:21 by tknibbe           #+#    #+#             */
/*   Updated: 2023/02/03 15:06:58 by tknibbe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char	*ft_strdup(const char *s)
{
	int		length;
	char	*dup;

	length = ft_strlen(s) + 1;
	dup = malloc(length * sizeof(char));
	if (dup == 0)
		return (0);
	ft_strlcpy(dup, s, length);
	return (dup);
}
