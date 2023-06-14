/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tknibbe <tknibbe@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 09:28:54 by tknibbe           #+#    #+#             */
/*   Updated: 2023/02/03 15:07:19 by tknibbe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*temp;
	int		len1;
	int		len2;

	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	temp = malloc(sizeof(char) * (len1 + len2 + 1));
	if (temp == 0)
		return (0);
	ft_strlcpy(temp, s1, len1 + 1);
	ft_strlcat(temp, s2, len1 + len2 + 1);
	return (temp);
}
