/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tknibbe <tknibbe@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 11:26:11 by tknibbe           #+#    #+#             */
/*   Updated: 2023/07/08 19:03:29 by tknibbe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	strcmp_redirects(char *str)
{
	if (!ft_strncmp(str, "|", 1))
		return (1);
	else if (!strncmp(str, ">", 1))
		return (1);
	else if (!strncmp(str, "<", 1))
		return (1);
	return (0);
}

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
		if (strcmp_redirects(args[i]))
			nodes++;
		i++;
	}
	printf("%d nodes needed\n", nodes);
	return (nodes);
}

int	cmd_needed(char **args, int *j)
{
	int	cmds;

	cmds = 0;
	if (strcmp_redirects(args[*j]))
		*j += 1;
	while (args[*j])
	{
		if (args[*j] == NULL)
			return (cmds);
		if (strcmp_redirects(args[*j]))
			return (cmds);
		else
			cmds++;
		*j += 1;
	}

	return (cmds);
}

void	put_str_in_node(t_exec *node, char **args, int amount, int *k) // fix that it will work next round
{
	int	i;

	i = 0;
	while (i < amount)
	{
		if (strcmp_redirects(args[*k]))
			*k += 1;
		printf("i = %d, amnt = %d arg = %s\n", i, amount, args[*k]);
		node->cmd[i] = args[*k];
		*k += 1;
		i++;
	}
	node->cmd[i] = NULL;
}

void	put_args_in_list(t_data **data, char **args)
{
	int		nodes;
	int		i;
	int		j;
	int		k;
	int		cmds;
	t_exec	*node;

	i = 0;
	j = 0;
	k = 0;
	nodes = nodes_needed(args);
	(*data)->list = malloc(sizeof(t_exec));
	if (!(*data)->list)
		ft_exit("Malloc error\n", errno);
	while (i < nodes)
	{
		cmds = cmd_needed(args, &j);
		printf("%d cmds needed\n", cmds);
		node->cmd = malloc(sizeof(char *) * cmds + 1);
		put_str_in_node(node, args, cmds, &k);
		//ft_lstadd_back(&(*data)->list, node); // all is in the node. need to put it in data->list
	int	f = 0;
	while (node->cmd[f])
	{
		printf("node->cmd[%d] = %s\n", f, node->cmd[f]);
		f++;
	}
		i++;
	}
}

void	parse(char *input, t_data **data)
{
	char	**args;

	args = split_args(input, *data);
	(*data)->list = NULL;
	put_args_in_list(data, args);

}
