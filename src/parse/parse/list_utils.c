/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tknibbe <tknibbe@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 12:30:57 by tknibbe           #+#    #+#             */
/*   Updated: 2023/07/24 12:12:36 by tknibbe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_exec	*exec_lstlast(t_exec *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next != 0)
		lst = lst->next;
	return (lst);
}

t_rdr	*rdr_lstlast(t_rdr *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next != 0)
		lst = lst->next;
	return (lst);
}

t_exec	*exec_lstnew(void)
{
	t_exec	*n1;

	n1 = malloc(sizeof(t_exec));
	if (n1 == NULL)
		ft_exit("Malloc error\n", errno);
	n1->cmd = NULL;
	n1->rdr = NULL;
	n1->next = NULL;
	return (n1);
}

void	exec_lstadd_back(t_exec **lst, t_exec *new)
{
	t_exec	*last;

	if (!(*lst))
	{
		*lst = new;
		return ;
	}
	last = exec_lstlast(*lst);
	last->next = new;
}

void	rdr_lstadd_back(t_rdr **lst, t_rdr *new)
{
	t_rdr	*last;

	if (!(*lst))
	{
		*lst = new;
		return ;
	}
	last = rdr_lstlast(*lst);
	last->next = new;
}
