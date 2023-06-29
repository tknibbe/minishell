/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_funcs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tknibbe <tknibbe@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 14:58:29 by tknibbe           #+#    #+#             */
/*   Updated: 2023/06/29 16:16:16 by tknibbe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <token.h>

static void	left(t_data *data, char *input, int *i);
static void	right(t_data *data, char *input, int *i);

void	find_pipe(t_data *data, char *input)
{
	int	i;

	i = 0;
	while (input[i])
	{
		if (input[i] == '|' && data->token[i] == UNDEFINED)
			data->token[i] = PIPESYMBOL;
		i++;
	}
}

void	find_append_redirect(t_data *data, char *input)
{
	int	i;

	i = 0;
	while (input[i])
	{
		if (input[i] == '<' && data->token[i] == UNDEFINED)
			left(data, input, &i);
		if (input[i] == '>' && data->token[i] == UNDEFINED)
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
		if (input[i] == c && data->token[i] == UNDEFINED)
			count++;
		i++;
	}
	return (count);
}

static void	left(t_data *data, char *input, int *i)
{
	if (input[*i + 1] == '<' && data->token[*i + 1] == UNDEFINED)
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
	if (input[*i + 1] == '>' && data->token[*i + 1] == UNDEFINED)
	{
		data->token[*i] = APPRIGHT;
		data->token[*i + 1] = APPRIGHT;
		*i += 1;
	}
	else
		data->token[*i] = REDIRRIGHT;
}
