/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tknibbe <tknibbe@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 11:26:11 by tknibbe           #+#    #+#             */
/*   Updated: 2023/10/01 16:19:40 by tknibbe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	new_rdr_node(char *input, int *token, t_list *list, int *i, t_env_info *env);
void	new_cmd_node(char *input, int *token, t_exec *exec, int *i);
int		is_redirect(int t);

int	ft_whitespace(char c)
{
	if (c == ' ' || c == '\t' || c == '\n'\
		|| c == '\v' || c == '\f' || c == '\r')
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	parse(char *input, t_list *list, t_env_info *env)
{
	int		i;
	t_exec	*node;

	i = 0;
	while (input[i])
	{
		node = exec_lstnew();
		exec_lstadd_back(&list->exec, node);
		while (list->token[i] != PIPESYMBOL && input[i])
		{
			if (is_redirect(list->token[i]))
			{
				if (new_rdr_node(input, list->token, list, &i, env))
					return (EXIT_FAILURE);
			}		
			else if (list->token[i] == WORD)
				new_cmd_node(input, list->token, node, &i);
			else if (list->token[i] == BRACE_OPEN)
			{
				if (add_subshell(input, list, node, &i, env))
					return (EXIT_FAILURE);
			}
			else
				i++;
		}
		if (input[i] == '|')
			i++;
	}
	return (EXIT_SUCCESS);
}

void	new_cmd_node(char *input, int *token, t_exec *node, int *i)
{
	int		start;
	char	*str;

	while (is_redirect(token[*i]) == 0 && token[*i] != PIPESYMBOL \
			&& input[*i] && token[*i] != BRACE_OPEN)
	{
		start = *i;
		while (token[*i] == WORD && input[*i])
			*i += 1;
		str = ft_substr(input, start, *i - start);
		if (!str)
			ft_exit("Malloc error\n", errno);
		t_str_lstadd_back(&node->cmd, t_str_lstnew(str));
		while (token[*i] == BLANK && input[*i])
			*i += 1;
	}
}

int	new_rdr_node(char *input, int *token, t_list *list, int *i, t_env_info *env)
{
	int		start;
	int		type;
	t_rdr	*rdr_node;
	t_exec	*cur_node;

	cur_node = exec_lstlast(list->exec);
	type = token[*i];
	if (type == HEREDOC)
	{
		add_heredoc(input, list, i, env);
		return (EXIT_FAILURE);
	}
	rdr_node = rdr_lstnew(NULL, type, 0);
	while ((token[*i] == BLANK || is_redirect(token[*i])) && input[*i])
		*i += 1;
	start = *i;
	while (token[*i] == WORD && input[*i])
		*i += 1;
	rdr_node->file->str = ft_substr(input, start, *i - start);
	if (!rdr_node->file->str)
		ft_exit("Malloc error\n", errno);
	rdr_lstadd_back(&cur_node->rdr, rdr_node);
	return (EXIT_SUCCESS);
}
