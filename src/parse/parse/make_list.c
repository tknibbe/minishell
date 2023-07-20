/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   make_list.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: tknibbe <tknibbe@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/07 11:26:11 by tknibbe       #+#    #+#                 */
/*   Updated: 2023/07/20 14:46:35 by cvan-sch      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	more_space_needed(int i, char **args)
{
	if (!args[i + 1])
		return (0);
	return (1);
}

int	nodes_needed(char *input, t_list *list)
{
	int	i;
	int	count;

	i = 0;
	count = 1;
	while (input[i])
	{
		if (list->token[i] == PIPESYMBOL)
			count++;
		else if (list->token[i] == OR || list->token[i] == AND)
		{
			count++;
			i++;
		}
		i++;
	}
	return (count);
}

void	parse(char *input, t_list **list)
{
	int		node_amount;

	node_amount = nodes_needed(input, *list);
	printf("%d nodes needed\n", node_amount);
	set_rdrs(list, input, node_amount); // make so it takes criss' function
	set_cmds(list, input, node_amount); //see abpve
}
