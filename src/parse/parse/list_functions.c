/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tknibbe <tknibbe@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 12:30:57 by tknibbe           #+#    #+#             */
/*   Updated: 2023/07/08 19:01:49 by tknibbe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_exec	*ft_lstlast(t_exec *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next != 0)
		lst = lst->next;
	return (lst);
}

void	ft_lstadd_back(t_exec **lst, t_exec *new)
{
	t_exec	*last;

	if (!(*lst))
	{
		*lst = new;
		return ;
	}
	last = ft_lstlast(*lst);
	last->next = new;
}

t_exec	*ft_lstnew(void)
{
	t_exec	*n1;

	n1 = malloc(sizeof(t_exec));
	if (n1 == NULL)
		ft_exit("Malloc error\n", errno);
	n1->cmd = NULL;
	n1->rd = -1;
	n1->file = NULL;
	n1->next = NULL;
	return (n1);
}

int	skip_already_processed(int skip, char *input)
{
	int	i;

	i = 0;
	while (skip && input[i])
	{
		if (input[i] == '|' || input[i] == '<' || input[i] == '>')
			skip--;
		i++;
	}
	return (i);
}

int	get_arg_len(t_data *data, int i, char *input)
{
	int	len;

	len = 0;
	printf("starting point: ");
	while (input[i])
	{
		printf("%c", input[i]);
		i++;
	}
	printf("\n");
	return (0);
}

