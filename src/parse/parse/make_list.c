/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tknibbe <tknibbe@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 11:26:11 by tknibbe           #+#    #+#             */
/*   Updated: 2023/07/12 15:39:43 by tknibbe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	more_space_needed(int i, char **args)
{
	if (!args[i + 1])
		return (0);
	return (1);
}

int	nodes_needed(char **args)
{
	int	nodes;
	int	i;

	i = 0;
	nodes = 1;
	while (args[i] && more_space_needed(i, args))
	{
		if (!ft_strncmp(args[i], "|", 1))
			nodes++;
		i++;
	}
	//printf("%d nodes needed\n", nodes);
	return (nodes);
}

void	parse(char *input, t_data **data)
{
	char	**args;
	int		node_amount;

	args = split_args(input, *data); //useless?
	node_amount = nodes_needed(args); // if not using split args anywhere else, make this with using input
	set_rdrs(data, input, node_amount);
	set_cmds(data, input, node_amount);

	//test
	print_whole_list(*data, input);
	//print_tokens(*data, input);
}
