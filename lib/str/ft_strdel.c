/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tknibbe <tknibbe@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 16:15:10 by tknibbe           #+#    #+#             */
/*   Updated: 2023/10/21 15:47:14 by tknibbe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

int	char_to_be_deleted(char *str, char *del)
{
	int	i;
	int	j;
	int	count;

	i = 0;
	j = 0;
	count = 0;
	while (str[i])
	{
		while (del[j])
		{
			if (str[i] == del[j])
				count++;
			j++;
		}
		j = 0;
		i++;
	}
	return (count);
}

int	in_del(char c, char *del)
{
	int	i;

	i = 0;
	while (del[i])
	{
		if (del[i] == c)
			return (1);
		i++;
	}
	return (0);
}

/*will delete any occurance of any char in "del" out of the input string "str"
the result is malloced and "str" if freed before returning*/
char	*ft_strdel(char *str, char *del)
{
	int		len;
	char	*ret;
	int		i;
	int		j;

	len = ft_strlen(str) - char_to_be_deleted(str, del);
	ret = malloc(sizeof(char) * (len + 1));
	if (!ret)
		return (NULL);
	i = 0;
	j = 0;
	while (str[i])
	{
		if (in_del(str[i], del) == 0)
		{
			ret[j] = str[i];
			j++;
		}
		i++;
	}
	ret[j] = '\0';
	free (str);
	return (ret);
}
