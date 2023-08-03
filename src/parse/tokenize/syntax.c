/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tknibbe <tknibbe@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 13:46:32 by tknibbe           #+#    #+#             */
/*   Updated: 2023/08/03 13:18:03 by tknibbe          ###   ########.fr       */
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

void	ft_syntax_error(char *str, char c, int token)
{
	write(2, str, ft_strlen(str));
	if (c == '\0')
		write(2, "'newline'", 9);
	else
	{
		write(2, "\'", 1);
		if (token == HEREDOC)
			write(2, "<<", 2);
		else if (token == APPEND)
			write(2, ">>", 2);
		else if (token == OR)
			write(2, "||", 2);
		else if (token == AND)
			write(2, "&&", 2);
		else
			write(2, &c, 1);
		write(2, "\'", 1);
	}
	write(2, "\n", 1);
}

static int	check_rdr(t_list *list, char *input, int *i)
{
	*i += 1;
	if (list->token[*i] == APPEND || list->token[*i] == HEREDOC)
		*i += 1;
	while (list->token[*i] == BLANK && input[*i])
	{
		*i += 1;
	}
	if (list->token[*i] != WORD || !input[*i])
		return (1);
	return (0);
}

static int	check_rest(t_list *list, char **input, int *i)
{
	char	*str;

	str = *input;
	if (list->token[*i] == OR || list->token[*i] == AND)
		*i += 2;
	else
		*i += 1;
	if (!str[*i] && (list->token[*i - 1] == OR || list->token[*i -1] == AND \
		|| list->token[*i - 1] == PIPESYMBOL))
		return (2);
	while (list->token[*i] == BLANK)
		*i += 1;
	if (is_redirect(list->token[*i]))
		return (check_rdr(list, str, i));
	else if (list->token[*i] == PIPESYMBOL || list->token[*i] == OR \
			|| list->token[*i] == AND)
		return (1);
	return (0);
}

void	add_new_input(t_list *list, char **input) //WILL LEAK! i think
{
	char	*new_str;
	char	*str;
	char	*temp;

	str = readline("> ");
	new_str = ft_strjoin(*input, str);
	free(*input);
	free(str);
	free(list->token);
	free(list->exec);
	*input = new_str;
	tokenize(*input, list);
	check_syntax(list, input);
}

int	check_syntax(t_list *list, char **input)
{
	int	check;
	int	i;
	char *test = *input;

	i = 0;
	check = 0;
	while (test[i])
	{
		while (test[i] && list->token[i] == WORD)
			i++;
		if (is_redirect(list->token[i]))
			check = check_rdr(list, *input, &i);
		else if (list->token[i] == PIPESYMBOL || list->token[i] == OR \
			|| list->token[i] == AND)
			check = check_rest(list, input, &i);
		if (check == 1)
		{
			ft_syntax_error("Minishell: syntax error near unexpected token ", \
				test[i], list->token[i]);
			return (1);
		}
		if (check == 2)
		{
			add_new_input(list, input);
			break ;
		}
		i++;
	}
	return (0);
}
