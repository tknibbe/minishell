/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tknibbe <tknibbe@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 13:46:32 by tknibbe           #+#    #+#             */
/*   Updated: 2023/07/18 18:06:44 by tknibbe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	is_redirect(int c)
{
	if (c == REDIRRIGHT || c == REDIRLEFT \
		|| c == APPLEFT || c == APPRIGHT)
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
		if (token == APPLEFT)
			write(2, "<<", 2);
		else if (token == APPRIGHT)
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

static int	check_rdr(t_data *data, char *input, int *i)
{
	*i += 1;
	while (data->token[*i] == BLANK && input[*i])
	{
		*i += 1;
	}
	if (data->token[*i] != WORD || !input[*i])
		return (1);
	return (0);
}

static int	check_rest(t_data *data, char **input, int *i)
{
	char *str;

	str = *input;
	if (data->token[*i] == OR || data->token[*i] == AND)
		*i += 2;
	else
		*i += 1;
	if (!str[*i] && (data->token[*i - 1] == OR || data->token[*i -1] == AND ||
		data->token[*i - 1] == PIPESYMBOL))
		return (2);
	while (data->token[*i] == BLANK)
		*i += 1;
	if (is_redirect(data->token[*i]))
		return (check_rdr(data, str, i));
	else if (data->token[*i] == PIPESYMBOL || data->token[*i] == OR \
			|| data->token[*i] == AND)
		return (1);
	return (0);
}

void	add_new_input(t_data *data, char **input) //WILL LEAK! i think
{
	char	*new_str;
	char	*str;
	char	*temp;

	str = readline("> ");
	new_str = ft_strjoin(*input, str);
	free(*input);
	free(str);
	free(data->token);
	free(data->list);
	*input = new_str;
	//free(new_str);
	set_tokens(*input, &data);
	check_syntax(data, input);
}

int	check_syntax(t_data *data, char **input)
{
	int	check;
	int	i;
	char *test = *input;

	i = 0;
	check = 0;
	while (test[i])
	{
		while (test[i] && data->token[i] == WORD)
			i++;
		if (is_redirect(data->token[i]))
			check = check_rdr(data, *input, &i);
		else if (data->token[i] == PIPESYMBOL || data->token[i] == OR \
			|| data->token[i] == AND)
			check = check_rest(data, input, &i);
		if (check == 1)
		{
			ft_syntax_error("Minishell: syntax error near unexpected token ", \
				test[i], data->token[i]);
			return (1);
		}
		if (check == 2)
		{
			add_new_input(data, input);
			break ;
		}
		i++;
	}
	return (0);
}
