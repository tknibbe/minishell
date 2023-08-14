/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   list_utils2.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: tknibbe <tknibbe@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/24 12:12:28 by tknibbe       #+#    #+#                 */
/*   Updated: 2023/08/10 16:56:41 by cvan-sch      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <parsing.h>

t_rdr	*rdr_lstnew(char *str, int type, int heredoc)
{
	t_rdr	*n1;

	n1 = malloc(sizeof(t_rdr));
	if (n1 == NULL)
		ft_exit("Malloc error\n", errno);
	if (!heredoc)
	{
		n1->file = malloc(sizeof(t_str));  //TODO free this in free function
		n1->file->str = str;
	}
	else
		n1->file = NULL;
	n1->type = type;
	n1->next = NULL;
	return (n1);
}

t_str	*char_lstlast(t_str *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next != 0)
		lst = lst->next;
	return (lst);
}

void	char_lstadd_back(t_str **lst, t_str *new)
{
	t_str	*last;

	if (!(*lst))
	{
		*lst = new;
		return ;
	}
	last = char_lstlast(*lst);
	last->next = new;
}

t_str	*char_lstnew(char *str)
{
	t_str	*n1;

	n1 = malloc(sizeof(t_str));
	if (n1 == NULL)
		ft_exit("Malloc error\n", errno);
	n1->str = str;
	n1->next = NULL;
	return (n1);
}
