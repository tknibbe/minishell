/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tknibbe <tknibbe@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 13:46:32 by tknibbe           #+#    #+#             */
/*   Updated: 2023/08/19 16:33:35 by tknibbe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	is_redirect(int c)
{
	if (c == REDIRRIGHT || c == REDIRLEFT \
		|| c == HEREDOC || c == APPEND)
		return (1);
	return (0);
}

static int is_control_op(int token)
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

int	add_new_input(t_list *list)
{
	char	*new_str;
	char	*str;

	str = readline("> ");
	if (!str)
		return (ft_syntax_error(' ', -1));
	new_str = ft_strjoin(list->input, str);
	free(list->input);
	free(str);
	free(list->token);
	free(list->exec);
	list->input = new_str;
	tokenize(list);
	check_syntax(list);
	return (0);
}

static int start_check(t_list *list)
{
	int	i;

	i = 0;
	while (list->token[i] == BLANK)
		i++;
	if (list->token[i] != WORD && !is_redirect(list->token[i]) && !is_subshell(list->token[i]))
		return (ft_syntax_error(' ',list->token[i]));
	return (0);
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

static int control_op_check(t_list *list, int *i)
{
	int	j;
	int	token;

	j = 0;
	token = list->token[*i];
	if (op_amount_check(list, *i))
		return ft_syntax_error(' ', list->token[*i]);
	while(list->token[*i] == token && list->input[*i + 1])
		*i += 1;
	while (list->token[*i] == BLANK && list->input[*i + 1])
		*i += 1;
	if (!list->input[*i + 1] && is_control_op(list->token[*i]))
		return (add_new_input(list));
	if (list->token[*i] == WORD || is_redirect(list->token[*i]))
	{
		return (0);
	}
	return (ft_syntax_error(' ',list->token[*i]));
}

static int rdr_check(t_list *list, int *i)
{
	while (is_redirect(list->token[*i]) && list->input[*i])
		*i += 1;
	while (list->token[*i] == BLANK && list->input[*i])
		*i += 1;
	if (!list->input[*i])
	{
		return (ft_syntax_error(list->input[*i], 0));
	}
	if (list->token[*i] != WORD)
	{
		return (ft_syntax_error(' ', list->token[*i]));
	}
	return (0);
}

int	check_syntax(t_list *list)
{
	int	i;
	int	prev_token;

	i = 0;
	prev_token = 0;
	if (start_check(list))
		return (1);
	while (list->input[i])
	{
		//printf("i = %d c = [%c]\n", i, list->input[i]);
		if (is_redirect(list->token[i]))
		{
			if (rdr_check(list, &i))
				return (1);
		}
		else if (is_control_op(list->token[i]))
		{
			if (control_op_check(list, &i))
				return (1);
		}
		else
			i++;
	}
	return (0);
}
