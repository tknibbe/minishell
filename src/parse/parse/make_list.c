/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tknibbe <tknibbe@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 11:26:11 by tknibbe           #+#    #+#             */
/*   Updated: 2023/07/24 15:40:37 by tknibbe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	new_rdr_node(char *input, int *token, t_exec *exec, int *i);
void	new_cmd_node(char *input, int *token, t_exec *exec, int *i);

int	is_redirect(int t)
{
	return (t == REDIRLEFT || t == REDIRRIGHT || t == HEREDOC || t == APPRIGHT);
}

void	parse(char *input, t_list *list)
{
	int		i;
	t_exec	*node;

	i = 0;
	while (input[i])
	{
		node = exec_lstnew();
		while (list->token[i] != PIPESYMBOL && input[i])
		{
			if (is_redirect(list->token[i]))
				new_rdr_node(input, list->token, node, &i);
			else if (list->token[i] == WORD)
				new_cmd_node(input, list->token, node, &i);
			else
				i++;
		}
		exec_lstadd_back(&list->exec, node);
		i++;
	}
	print_whole_list(list, input);
}

void	new_cmd_node(char *input, int *token, t_exec *node, int *i)
{
	int		start;
	char	*str;

	while (is_redirect(token[*i]) == 0 && token[*i] != PIPESYMBOL && input[*i])
	{
		start = *i;
		while (token[*i] == WORD && input[*i])
			*i += 1;
		str = ft_substr(input, start, *i - start);
		if (!str)
			ft_exit("Malloc error\n", errno);
		char_lstadd_back(&node->cmd, char_lstnew(str));
		while (token[*i] == BLANK && input[*i])
			*i += 1;
	}
}

void	new_rdr_node(char *input, int *token, t_exec *node, int *i)
{
	int		start;
	int		type;
	char	*str;

	type = token[*i];
	if (type == HEREDOC)
	{
		add_heredoc(input, node, i);
		return ;
	}
	while ((token[*i] == BLANK || is_redirect(token[*i])) && input[*i])
		*i += 1;
	start = *i;
	while (token[*i] == WORD && input[*i])
		*i += 1;
	str = ft_substr(input, start, *i - start);
	if (!str)
		ft_exit("Malloc error\n", errno);
	rdr_lstadd_back(&node->rdr, rdr_lstnew(str, type));
}
