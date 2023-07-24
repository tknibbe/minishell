/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tknibbe <tknibbe@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 12:12:28 by tknibbe           #+#    #+#             */
/*   Updated: 2023/07/24 12:25:09 by tknibbe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <token.h>

t_rdr	*rdr_lstnew(char *str, int type)
{
	t_rdr	*n1;

	n1 = malloc(sizeof(t_rdr));
	if (n1 == NULL)
		ft_exit("Malloc error\n", errno);
	n1->file = str;
	n1->type = type;
	n1->next = NULL;
	return (n1);
}

t_char	*char_lstlast(t_char *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next != 0)
		lst = lst->next;
	return (lst);
}

void	char_lstadd_back(t_char **lst, t_char *new)
{
	t_char	*last;

	if (!(*lst))
	{
		*lst = new;
		return ;
	}
	last = char_lstlast(*lst);
	last->next = new;
}

t_char	*char_lstnew(char *str)
{
	t_char	*n1;

	n1 = malloc(sizeof(t_char));
	if (n1 == NULL)
		ft_exit("Malloc error\n", errno);
	n1->s = str;
	n1->next = NULL;
	return (n1);
}
