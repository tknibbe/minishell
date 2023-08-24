/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subshell.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tknibbe <tknibbe@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 14:46:50 by tknibbe           #+#    #+#             */
/*   Updated: 2023/08/23 12:47:13 by tknibbe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

#define RESET -1

int	is_subshell(int token)
{
	return (token == BRACE_OPEN || token == BRACE_CLOSE);
}

int	sub_count(char c, int option)
{
	static int	amount_open;
	static int	amount_close;

	if (c == '(')
		amount_open++;
	else if (c == ')')
		amount_close++;
	if (option == RESET)
	{
		amount_open = 0;
		amount_close = 0;
		return (0);
	}
	if (amount_open < amount_close)
		return (amount_open);
	return (amount_close);
}

void	set_subshell(t_list *list, char *input)
{
	int	open;
	int	close;
	int	i;
	int	active;

	open = sub_count(' ', 0);
	close = sub_count(' ', 0);
	i = 0;
	active = 0;
	while ((open || close) && input[i])
	{
		if (input[i] == '(' && open)
		{
			list->token[i] = BRACE_OPEN;
			active += 1;
			open--;
		}
		else if (input[i] == ')' && close)
		{
			list->token[i] = BRACE_CLOSE;
			active -= 1; 
			close--;
		}
		if (active && input[i + 1])
			list->token[i + 1] = BLANK;
		i++;
	}
	sub_count(' ', RESET);
}

void	add_subshell(char *input, t_list *list, int *i)
{
	int		start;
	char	*str;
	int		shdepth;

	// fork here?
	start = *i + 1;
	shdepth = 1;
	*i += 1;
	while (shdepth && input[*i])
	{
		if (list->token[*i] == BRACE_OPEN)
			shdepth++;
		else if (list->token[*i] == BRACE_CLOSE)
			shdepth--;
		//printf("shdepth = %d\n", shdepth);
		*i += 1;
	}
	str = ft_substr(input, start, *i - start - 1);
	//str = ft_strtrim(str, "()");
	printf("str = %s\n", str);
	t_listadd_back(&list->subshell, parse_input(str));
	//list->subshell = parse_input(str);
}