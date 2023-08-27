/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tknibbe <tknibbe@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 15:20:01 by tknibbe           #+#    #+#             */
/*   Updated: 2023/08/27 16:20:22 by tknibbe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_list	*t_listnew(void)
{
	t_list	*node;

	node = malloc(sizeof(t_list));
	if (!node)
		ft_exit("Malloc error", errno);
	node->token = NULL;
	node->input = NULL;
	node->and_or = 0;
	node->exec = NULL;
	node->exit_code = 0;
	node->next = NULL;
	return (node);
}

t_list	*t_listlast(t_list *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next != 0)
		lst = lst->next;
	return (lst);
}

void	t_listadd_back(t_list **lst, t_list *new)
{
	t_list	*last;

	if (!(*lst))
	{
		*lst = new;
		return ;
	}
	last = t_listlast(*lst);
	last->next = new;
}