/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tknibbe <tknibbe@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 14:56:52 by tknibbe           #+#    #+#             */
/*   Updated: 2023/07/19 15:07:44 by tknibbe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <token.h>

int	whitespace(char c)
{
	if (c == ' ' || c == '\t' || c == '\n'\
		|| c == '\v' || c == '\f' || c == '\r')
		return (1);
	return (0);
}

void	set_rdr_or_pipe(t_data *data, char *input, int *i)
{
	if (input[*i] == '|')
	{
		if (input[*i + 1] == '|')
		{
			data->token[*i] = OR;
			data->token[*i + 1] = OR;
			*i += 1;
		}
		else
			data->token[*i] = PIPESYMBOL;
	}
	else
	{
		if (input[*i] == '<')
			left(data, input, i);
		else if (input[*i] == '>')
			right(data, input, i);
	}
}

void	left(t_data *data, char *input, int *i)
{
	if (input[*i + 1] == '<')
	{
		data->token[*i] = APPLEFT;
		data->token[*i + 1] = APPLEFT;
		*i += 1;
	}
	else
		data->token[*i] = REDIRLEFT;
}

void	right(t_data *data, char *input, int *i)
{
	if (input[*i + 1] == '>')
	{
		data->token[*i] = APPRIGHT;
		data->token[*i + 1] = APPRIGHT;
		*i += 1;
	}
	else
		data->token[*i] = REDIRRIGHT;
}

int	is_alphanumeric(char c)
{
	if (c >= '0' && c <= '9')
		return (1);
	if (c >= 'a' && c <= 'z')
		return (1);
	if (c >= 'A' && c <= 'Z')
		return (1);
	if (c == '_')
		return (1);
	return (0);
}
