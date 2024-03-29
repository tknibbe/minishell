/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tknibbe <tknibbe@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 11:26:11 by tknibbe           #+#    #+#             */
/*   Updated: 2023/11/09 14:58:33 by tknibbe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		new_rdr_node(char *input, t_list *list, int *i, t_env_info *env);
void	new_cmd_node(char *input, int *token, t_exec *exec, int *i);
int		is_redirect(int t);

int	ft_whitespace(char c)
{
	if (c == ' ' || c == '\t' || c == '\n'\
		|| c == '\v' || c == '\f' || c == '\r')
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

static int	select_struct(t_list *list, char *input, int *i, t_env_info *env)
{
	t_exec	*node;
	int		len;

	node = exec_lstnew();
	exec_lstadd_back(&list->exec, node);
	len = ft_strlen(input);
	while (*i < len && list->token[*i] != PIPESYMBOL)
	{
		if (is_redirect(list->token[*i]))
		{
			if (new_rdr_node(input, list, i, env))
				return (EXIT_FAILURE);
		}
		else if (list->token[*i] == WORD)
			new_cmd_node(input, list->token, node, i);
		else if (list->token[*i] == BRACE_OPEN)
		{
			t_listadd_back(&node->subshell, add_subshell(input, list, i, env));
			if (!node->subshell)
				return (EXIT_FAILURE);
		}
		else
			*i += 1;
	}
	return (EXIT_SUCCESS);
}

/***Description:**
`parse` is a function responsible for parsing an input string into a series
of command structures. It considers redirection, subshells, and individual
commands separated by pipe symbols.

**Parameters:**
- `input` (char*): The input string to be parsed.
- `list` (t_list*): A data structure to hold the parsed command structures.
- `env` (t_env_info*): Environment information.

**Return Value:**
- `EXIT_SUCCESS` on successful parsing.
- `EXIT_FAILURE` if an error occurs during parsing.*/
int	parse(char *input, t_list *list, t_env_info *env)
{
	int		i;

	i = 0;
	while (input[i])
	{
		if (select_struct(list, input, &i, env))
			return (EXIT_FAILURE);
		if (input[i] == '|')
			i++;
	}
	return (EXIT_SUCCESS);
}

void	new_cmd_node(char *input, int *token, t_exec *node, int *i)
{
	int		start;
	char	*str;

	while (input[*i] && !is_redirect(token[*i]) && token[*i] != PIPESYMBOL \
			&& token[*i] != BRACE_OPEN)
	{
		start = *i;
		while (input[*i] && token[*i] == WORD)
			*i += 1;
		str = ft_substr(input, start, *i - start);
		if (!str)
			ft_minishell_error("malloc()", NULL, strerror(errno), errno);
		t_str_lstadd_back(&node->cmd, t_str_lstnew(str));
		while (input[*i] && token[*i] == BLANK)
			*i += 1;
	}
}

int	new_rdr_node(char *input, t_list *list, int *i, t_env_info *env)
{
	int		start;
	int		type;
	int		*token;
	t_rdr	*rdr_node;
	t_exec	*cur_node;

	token = list->token;
	cur_node = exec_lstlast(list->exec);
	type = token[*i];
	if (type == HEREDOC_EXP)
		return (add_heredoc(list, i, env));
	rdr_node = rdr_lstnew(NULL, type, 0);
	while ((token[*i] == BLANK || is_redirect(token[*i])) && input[*i])
		*i += 1;
	start = *i;
	while (token[*i] == WORD && input[*i])
		*i += 1;
	rdr_node->file->str = ft_substr(input, start, *i - start);
	if (!rdr_node->file->str)
		ft_minishell_error("malloc()", NULL, strerror(errno), errno);
	rdr_lstadd_back(&cur_node->rdr, rdr_node);
	return (EXIT_SUCCESS);
}
