/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tknibbe <tknibbe@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/27 13:45:40 by tknibbe           #+#    #+#             */
/*   Updated: 2023/08/27 13:52:42 by tknibbe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <parsing.h>

int	is_redirect(int t)
{
	return (t == REDIRLEFT || t == REDIRRIGHT || t == HEREDOC || t == APPEND);
}

int	is_control_op(int token)
{
	return (token == OR || token == AND || token == PIPESYMBOL);
}

int	ft_syntax_error(char c, int token)
{
	write(2, "Minishell: syntax error ", 24);
	if (token == -1)
		write(2, "unexpected end of file", 22);
	else if (c == '\0')
		write(2, "near unexpected token 'newline'", 31);
	else
	{
		write(2, "near unexpected token ", 22);
		write(2, "\'", 1);
		if (token == HEREDOC)
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
	write(2, "\n", 1);
	return (1);
}

int	op_amount_check(t_list *list, int i)
{
	int	j;

	j = 1;
	while (list->input[i + j] == list->input[i + j - 1])
		j++;
	if (j > 2)
		return (1);
	return (0);
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
	return (0);
}
