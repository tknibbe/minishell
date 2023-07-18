/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_funcs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tknibbe <tknibbe@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 14:58:29 by tknibbe           #+#    #+#             */
/*   Updated: 2023/07/15 12:42:50 by tknibbe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <token.h>

static void	left(t_data *data, char *input, int *i);
static void	right(t_data *data, char *input, int *i);

static void find_ampersand(t_data *data, char *input, int i)
{
	if (input[i] == '&' && data->token[i] == BLANK)
	{
		if (input[i + 1] == '&')
		{
			data->token[i] = AND;
			data->token[i + 1] = AND;
		}
	}
}

void	find_pipe_and_ampersand(t_data *data, char *input)
{
	int	i;

	i = 0;
	while (input[i])
	{
		if (input[i] == '|' && data->token[i] == BLANK)
		{
			if (input[i + 1] == '|')
			{
				data->token[i] = OR;
				data->token[i + 1] = OR;
			}
			else
				data->token[i] = PIPESYMBOL;
		}
		find_ampersand(data, input, i);
		i++;
	}
}

void	find_append_redirect(t_data *data, char *input)
{
	int	i;

	i = 0;
	while (input[i])
	{
		if (input[i] == '<' && data->token[i] == BLANK)
			left(data, input, &i);
		if (input[i] == '>' && data->token[i] == BLANK)
			right(data, input, &i);
		i++;
	}
}

int	count_quote(char *input, t_data *data, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (input[i])
	{
		if (input[i] == c && data->token[i] == BLANK)
			count++;
		i++;
	}
	return (count);
}

static void	left(t_data *data, char *input, int *i)
{
	if (input[*i + 1] == '<' && data->token[*i + 1] == BLANK)
	{
		data->token[*i] = APPLEFT;
		data->token[*i + 1] = APPLEFT;
		*i += 1;
	}
	else
		data->token[*i] = REDIRLEFT;
}

static void	right(t_data *data, char *input, int *i)
{
	if (input[*i + 1] == '>' && data->token[*i + 1] == BLANK)
	{
		data->token[*i] = APPRIGHT;
		data->token[*i + 1] = APPRIGHT;
		*i += 1;
	}
	else
		data->token[*i] = REDIRRIGHT;
}
