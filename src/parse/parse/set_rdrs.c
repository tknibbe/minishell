/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_rdrs.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tknibbe <tknibbe@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 15:58:11 by tknibbe           #+#    #+#             */
/*   Updated: 2023/07/11 19:00:03 by tknibbe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	redir_token(int	*token, int *j)
{
	if (token[*j] == APPLEFT || token[*j] == APPRIGHT)
	{
		//printf("!APPEND\n");
		*j += 1;
		return (1);
	}
	if (token[*j] == REDIRRIGHT || token[*j] == REDIRLEFT)
		return (1);
	return (0);
}

t_rdr	*make_rdr_node(char *input, int	*j, int	*token)
{
	t_rdr	*node;
	int		i;
	int		start;

	i = 0;
	node = rdr_lstnew();
	node->type = token[*j];
	token[*j] = BLANK;
	while (token[*j] == BLANK)
		*j += 1;
	start = *j;
	while (token[*j] != BLANK && input[i])
	{
		token[*j] = BLANK;
		*j += 1;
		i++;
	}
	node->file = ft_substr(input, start, i);
	//printf("filename: %s\n", node->file);
	return (node);
}

void	set_rdrs(t_data **data, char *input, int node_amount)
{
	int		i;
	int		j;
	t_exec	*exec_node;
	t_rdr	*rdr_node;
	t_rdr	*rdr_head;

	i = 0;
	j = 0;
	while (i < node_amount)
	{
		rdr_head = NULL;
		exec_node = exec_lstnew();
		while (input[j] && (*data)->token[j] != PIPESYMBOL)
		{
			if (redir_token((*data)->token, &j))
			{
				rdr_node = make_rdr_node(input, &j, (*data)->token);
				rdr_lstadd_back(&rdr_head, rdr_node);
				//printf("after adding to head %s\n", rdr_node->file);
			}
			j++;
		}
		while ((*data)->token[j] == PIPESYMBOL && input[j])
			j++;
		exec_node->rdr = rdr_head;
		exec_lstadd_back(&(*data)->list, exec_node);
		i++;
	}
	//print_tokens(*data, input);
	print_whole_list(*data, input);
}
