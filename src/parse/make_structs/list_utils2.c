/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tknibbe <tknibbe@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 12:12:28 by tknibbe           #+#    #+#             */
/*   Updated: 2023/08/27 16:20:42 by tknibbe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <parsing.h>

t_rdr	*rdr_lstnew(char *str, int type, int heredoc)
{
	t_rdr	*n1;

	n1 = malloc(sizeof(t_rdr));
	if (n1 == NULL)
		ft_minishell_error("malloc()", NULL, strerror(errno), errno);
	if (!heredoc)
	{
		n1->file = t_str_lstnew(NULL);
		n1->file->str = str;
	}
	else
		n1->file = NULL;
	n1->type = type;
	n1->next = NULL;
	return (n1);
}

t_str	*t_str_lstlast(t_str *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next != 0)
		lst = lst->next;
	return (lst);
}

void	t_str_lstadd_back(t_str **lst, t_str *new)
{
	t_str	*last;

	if (!(*lst))
	{
		*lst = new;
		return ;
	}
	last = t_str_lstlast(*lst);
	last->next = new;
}

t_str	*t_str_lstnew(char *str)
{
	t_str	*n1;

	n1 = malloc(sizeof(t_str));
	if (n1 == NULL)
		ft_minishell_error("malloc()", NULL, strerror(errno), errno);
	n1->str = str;
	n1->next = NULL;
	return (n1);
}
