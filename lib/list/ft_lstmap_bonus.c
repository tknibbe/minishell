/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tknibbe <tknibbe@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 14:28:40 by tknibbe           #+#    #+#             */
/*   Updated: 2022/10/27 13:27:45 by tknibbe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*temp_list;
	t_list	*new_list;
	t_list	*f_content;

	if (lst == 0 || f == 0 || del == 0)
		return (0);
	new_list = 0;
	while (lst != 0)
	{
		f_content = f(lst->content);
		temp_list = ft_lstnew(f_content);
		if (temp_list == 0)
		{
			free(f_content);
			ft_lstclear(&new_list, del);
			return (0);
		}
		ft_lstadd_back(&new_list, temp_list);
		lst = lst->next;
	}
	return (new_list);
}
