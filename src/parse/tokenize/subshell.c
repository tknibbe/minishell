/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subshell.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tknibbe <tknibbe@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 14:46:50 by tknibbe           #+#    #+#             */
/*   Updated: 2023/11/28 17:34:09 by tknibbe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

#define RESET -1
#define ADD 1
#define RETRIEVE 0

int	is_subshell(int token)
{
	return (token == BRACE_OPEN || token == BRACE_CLOSE);
}

int	sub_count(char c, int option)
{
	static int	amount_open;
	static int	amount_close;

	if (option == ADD)
	{
		if (c == '(')
			amount_open++;
		else if (c == ')')
		{
			if (amount_open > amount_close)
				amount_close++;
			else
				unclosed_warning(')');
		}
		return (EXIT_SUCCESS);
	}
	else if (option == RESET)
	{
		amount_open = 0;
		amount_close = 0;
		return (EXIT_SUCCESS);
	}
	while (amount_open-- > amount_close)
		unclosed_warning('(');
	return (amount_close);
}

static void	set_brace(int *token, int brace, int *active, int *open_close)
{
	*token = brace;
	if (brace == BRACE_OPEN)
		*active += 1;
	else if (brace == BRACE_CLOSE)
		*active -= 1;
	*open_close -= 1;
}

void	set_subshell(t_list *list, char *input)
{
	int	open;
	int	close;
	int	i;
	int	active;

	open = sub_count(' ', RETRIEVE);
	close = open;
	i = 0;
	active = 0;
	while ((open || close) && input[i])
	{
		if (input[i] == '(' && open)
			set_brace(&list->token[i], BRACE_OPEN, &active, &open);
		else if (input[i] == ')' && close && open < close)
			set_brace(&list->token[i], BRACE_CLOSE, &active, &close);
		if (active && input[i + 1])
			list->token[i + 1] = BLANK;
		i++;
	}
	sub_count(' ', RESET);
}

t_list	*add_subshell(char *input, t_list *list, int *i, t_env_info *env)
{
	int		start;
	char	*str;
	int		shdepth;
	t_list	*temp;

	start = *i + 1;
	shdepth = 1;
	*i += 1;
	while (shdepth && input[*i])
	{
		if (list->token[*i] == BRACE_OPEN)
			shdepth++;
		else if (list->token[*i] == BRACE_CLOSE)
			shdepth--;
		*i += 1;
	}
	str = ft_substr(input, start, *i - start - 1);
	if (!str)
		ft_minishell_error("malloc()", NULL, strerror(errno), errno);
	temp = parse_input(&str, env);
	free (str);
	if (!temp)
		return (NULL);
	return (temp);
}
