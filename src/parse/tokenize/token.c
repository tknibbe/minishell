/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tknibbe <tknibbe@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 12:18:15 by tknibbe           #+#    #+#             */
/*   Updated: 2023/07/19 15:41:34 by tknibbe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <token.h>

static void	set_token(t_data *data, char *input);

/*sets tokens according to the ENUMs defined in the header. 
returns 0 on succes.*/
int	tokenize(char *input, t_data **data)
{
	int	len;

	len = ft_strlen(input);
	(*data)->token = malloc(sizeof(int) * len);
	if (!(*data)->token)
		ft_exit("Malloc error\n", errno);
	set_token(*data, input);
	//print_tokens(*data, input);
	return (0);
}

int	is_rdr_pipe_amp(char c)
{
	if (c == '|' || c == '<' || c == '>' || c == '&')
		return (1);
	return (0);
}

static int	is_closed_quote(char *input, int *end_quote, int i)
{
	char	quote;

	if (input[i] != '"' && input[i] != '\'')
		return (0);
	*end_quote = i + 1;
	quote = input[i];
	i++;
	while (input[i])
	{
		*end_quote += 1;
		if (input[i] == quote)
			return (1);
		i++;
	}
	*end_quote = 0;
	return (0);
}

static void	set_token(t_data *data, char *input)
{
	int	i;
	int	end_quote;

	i = 0;
	end_quote = 0;
	while (input[i])
	{
		if (is_closed_quote(input, &end_quote, i))
		{
			while (i < end_quote)
			{
				data->token[i] = WORD;
				i++;
			}
		}
		if (is_rdr_pipe_amp(input[i]))
		{
			set_rdr_pipe_amp(data, input, &i);
			i++;
		}
		else
		{
			if (!whitespace(input[i]))
				data->token[i] = WORD;
			else
				data->token[i] = BLANK;
			i++;
		}
	}
}
