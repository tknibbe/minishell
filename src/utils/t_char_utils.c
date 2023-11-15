/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_char_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tknibbe <tknibbe@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 12:32:20 by tknibbe           #+#    #+#             */
/*   Updated: 2023/11/15 12:32:21 by tknibbe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_str	*tstr_new(char *content)
{
	t_str	*new;

	new = malloc(sizeof(t_str));
	if (!new)
		ft_minishell_error("malloc()", NULL, strerror(errno), errno);
	new->next = NULL;
	new->str = content;
	return (new);
}

void	tstr_addback(t_str **head, t_str *new)
{
	t_str	*tmp;

	tmp = *head;
	if (*head == NULL)
		*head = new;
	else
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
}

void	tstr_addnext(t_str *current, t_str *new)
{
	t_str	*tmp;

	tmp = current->next;
	current->next = new;
	new->next = tmp;
}
