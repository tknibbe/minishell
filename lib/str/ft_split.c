/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tknibbe <tknibbe@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 10:25:03 by tknibbe           #+#    #+#             */
/*   Updated: 2023/02/03 15:07:29 by tknibbe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

static int	count_str(char const *s, char c)
{
	int		i;
	char	*temps;
	int		str_count;

	i = 0;
	temps = (char *)s;
	str_count = 0;
	while (temps[i])
	{
		while (temps[i] == c && temps[i])
			i++;
		if (temps[i] != c && temps[i])
			str_count++;
		while (temps[i] != c && temps[i])
			i++;
		while (temps[i] == c && temps[i])
			i++;
	}
	return (str_count);
}

static char	**fill_mem(char **temp, char const *s, char c, int str_count)
{
	int		begin;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (j < str_count && s[i])
	{
		while (s[i] == c && s[i])
			i++;
		begin = i;
		while (s[i] != c && s[i])
			i++;
		temp[j] = ft_substr(s, begin, (i - begin));
		if (temp[j] == 0)
		{
			while (j-- > 0)
				free(temp[j]);
			free(temp);
			return (NULL);
		}
		j++;
	}
	temp[j] = 0;
	return (temp);
}

char	**ft_split(char const *s, char c)
{
	char	**temp;
	int		str_count;

	str_count = count_str(s, c);
	temp = (char **)malloc(sizeof(char *) * (str_count + 1));
	if (temp == 0)
		return (0);
	return (fill_mem(temp, s, c, str_count));
}
