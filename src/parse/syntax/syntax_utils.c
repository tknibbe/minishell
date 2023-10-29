/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tymonknibbe <tymonknibbe@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/27 13:45:40 by tknibbe           #+#    #+#             */
/*   Updated: 2023/10/29 22:15:45 by tymonknibbe      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

int	brace_check(t_list *list, int *i)
{
	int	j;

	if (list->token[*i] == BRACE_OPEN)
	{
		if (*i == 0)
			return (EXIT_SUCCESS);
		j = *i - 1;
		while (j >= 0 && list->token[j] == BLANK)
			j--;
		if (is_control_op(list->token[j]) == 0 && list->token[j] != BRACE_OPEN)
			return (ft_syntax_error('(', list->token[*i]));
	}
	else
	{
		j = *i + 1;
		while (list->input[j] && list->token[j] == BLANK)
			j++;
		if (!is_control_op(list->token[j]) && list->input[j])
			return (ft_syntax_error(list->input[j], list->token[j]));
	}
	return (EXIT_SUCCESS);
}

static void	print_unex_token(char c, int token)
{
	write(2, "near unexpected token ", 22);
	write(2, "\'", 1);
	if (token == HEREDOC_EXP)
		write(2, "<<", 2);
	else if (token == APPEND)
		write(2, ">>", 2);
	else if (token == OR)
		write(2, "||", 2);
	else if (token == AND)
		write(2, "&&", 2);
	else if (token == PIPESYMBOL)
		write(2, "|", 1);
	else if (token == REDIRRIGHT)
		write(2, ">", 1);
	else if (token == REDIRLEFT)
		write(2, "<", 1);
	else
		write(2, &c, 1);
	write(2, "\'", 1);
}

int	ft_syntax_error(char c, int token)
{
	write(2, "Minishell: syntax error ", 24);
	if (token == -1)
		write(2, "unexpected end of file", 22);
	else if (c == '\0')
		write(2, "near unexpected token 'newline'", 31);
	else
		print_unex_token(c, token);
	write(2, "\n", 1);
	return (EXIT_FAILURE);
}

int	op_amount_check(t_list *list, int i)
{
	int	j;

	j = 1;
	while (list->input[i + j] == list->input[i + j - 1])
		j++;
	if (j > 2)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	start_check(t_list *list)
{
	int	i;

	i = 0;
	while (list->token[i] == BLANK)
		i++;
	if (list->token[i] != WORD && !is_redirect(list->token[i]) \
		&& !is_subshell(list->token[i]))
		return (ft_syntax_error(' ', list->token[i]));
	return (EXIT_SUCCESS);
}
