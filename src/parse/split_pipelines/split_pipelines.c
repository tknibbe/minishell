/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_pipelines.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tknibbe <tknibbe@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 14:34:27 by tknibbe           #+#    #+#             */
/*   Updated: 2023/08/22 15:53:11 by tknibbe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	and_or_instr(char *input, int *token, int i)
{
	while (input[i])
	{
		if (token[i] == AND || token[i] == OR)
			return (i);
		i++;
	}
	if (!input[i])
		return (0);
	return (ft_strlen(input) - 1);
}

int	*copy_token(int *token, int start, int end)
{
	int	*new_token;
	int	i;

	new_token = malloc(sizeof(int) * end - start);
	if (!new_token)
		ft_exit("Malloc error", errno);
	i = 0;
	while (start + i < end)
	{
		new_token[i] = token[start + i];
		i++;
	}
	return (new_token);
}

int	split_pipelines(char *input, t_list *list)
{
	t_list	*node;
	t_list	*data;
	int		start;
	int		end;

	start = 0;
	data = list;
	end = and_or_instr(input, data->token, 0);
	//print_tokens(all->list, ft_strlen(input));
	if (end == 0)
		return (0);
	list = NULL;
	while (input[end])
	{
		if (data->token[end] == AND || data->token[end] == OR || !input[end + 1])
		{
			if (!input[end + 1])
				end++;
			node = t_listnew();
			t_listadd_back(&list, node);
			node->input = ft_substr(input, start, end - start);
			node->token = copy_token(data->token, start, end);
			node->and_or = data->token[end];
			if (input[end + 2])
				end += 2;
			start = end;
		}
		else
			end++;
	}
	printf("exit split_pipes\n");
	free(data->token);
	free(data);
	return (1);
}
 