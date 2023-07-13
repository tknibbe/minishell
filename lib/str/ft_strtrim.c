/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tymonknibbe <tymonknibbe@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 10:42:35 by tknibbe           #+#    #+#             */
/*   Updated: 2023/07/12 21:29:18 by tymonknibbe      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

static int	set_cmp(char c, char const *set)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (c == set[i])
			return (1);
		i++;
	}
	return (0);
}

static	char	*memory_allocation(char *temp, char *s1, int begin, int end)
{
	if ((end - begin) <= 0)
		return (ft_calloc(1, 1));
	temp = malloc(sizeof(char) * (end - begin + 1));
	if (temp == 0)
		return (0);
	ft_strlcpy(temp, &s1[begin], (end - begin) + 1);
	return (temp);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*temp;
	int		i;
	int		set_match;
	int		begin;

	i = 0;
	set_match = 1;
	while (set_match == 1)
	{
		set_match = set_cmp(s1[i], set);
		i++;
	}
	begin = i - 1;
	i = ft_strlen(s1);
	if (i == 0)
		return (ft_calloc(1, 1));
	set_match = 1;
	while (set_match == 1)
	{
		i--;
		set_match = set_cmp(s1[i], set);
	}
	temp = 0;
	temp = memory_allocation(temp, (char *)s1, begin, i + 1);
	return (temp);
}
