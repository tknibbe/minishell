/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_pipelines.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tknibbe <tknibbe@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 14:34:27 by tknibbe           #+#    #+#             */
/*   Updated: 2023/10/18 16:03:10 by tknibbe          ###   ########.fr       */
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
		return (EXIT_SUCCESS);
	return (ft_strlen(input) - 1);
}

int	*copy_token(int *token, int start, int end)
{
	int	*new_token;
	int	i;

	new_token = malloc(sizeof(int) * end - start);
	if (!new_token)
		ft_minishell_error("malloc()", "failed", strerror(errno), errno);
	i = 0;
	while (start + i < end)
	{
		new_token[i] = token[start + i];
		i++;
	}
	return (new_token);
}

static t_list	*make_new_node(t_list *data, char *input, int *end, int *start)
{
	t_list	*node;

	if (!input[*end + 1])
		*end += 1;
	node = t_listnew();
	node->input = ft_substr(input, *start, (*end) - (*start));
	if (!node->input)
		ft_minishell_error("malloc()", "failed", strerror(errno), errno);
	node->token = copy_token(data->token, *start, *end);
	node->and_or = data->token[*end];
	if (input[*end + 2])
		*end += 2;
	*start = *end;
	return (node);
}

/*Description:
split_pipelines is a function responsible for segmenting an input string into separate pipelines and constructing a linked list to represent these pipeline segments.
It facilitates the execution of multiple commands separated by the AND and OR operators within a custom shell environment.

Parameters:

    input (char*): The input string to be segmented into pipelines.
    list (t_list**): A pointer to a pointer to a t_list structure, which will hold the segmented pipeline data.

Return Value:

    EXIT_SUCCESS if the input contains no pipelines.
    EXIT_FAILURE if any errors occur during the segmentation process.*/
int	split_pipelines(char *input, t_list **list)
{
	t_list	*data;
	int		start;
	int		end;

	start = 0;
	data = *list;
	end = and_or_instr(input, data->token, 0);
	if (end == 0)
		return (EXIT_SUCCESS);
	*list = NULL;
	while (input[end])
	{
		if (data->token[end] == AND || data->token[end] == OR || \
			!input[end + 1])
			t_listadd_back(list, make_new_node(data, input, &end, &start));
		else
			end++;
	}
	free(data->input);
	free(data->token);
	free(data);
	return (EXIT_FAILURE);
}
