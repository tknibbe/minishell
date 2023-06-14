/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tknibbe <tknibbe@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 15:51:55 by tknibbe           #+#    #+#             */
/*   Updated: 2022/10/27 13:30:41 by tknibbe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

t_list	*ft_lstnew(void *content)
{
	t_list	*n1;

	n1 = malloc(sizeof(t_list));
	if (n1 == 0)
		return (0);
	n1->content = content;
	n1->next = 0;
	return (n1);
}
