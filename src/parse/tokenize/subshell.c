/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subshell.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tknibbe <tknibbe@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 14:46:50 by tknibbe           #+#    #+#             */
/*   Updated: 2023/08/19 15:18:25 by tknibbe          ###   ########.fr       */
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
	static int amount_open;
	static int amount_close;

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
	
	open = sub_count(' ', 0);
	close = sub_count(' ', 0);
	i = 0;
	while ((open || close) && input[i])
	{
		if (input[i] == '(' && open)
		{
			list->token[i] = BRACE_OPEN;
			open--;
		}
		else if (input[i] == ')' && close)
		{
			list->token[i] = BRACE_CLOSE;
			close--;
		}
		i++;
	}
	sub_count(' ', RESET);
}