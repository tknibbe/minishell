/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_funcs2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tknibbe <tknibbe@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 14:54:23 by tknibbe           #+#    #+#             */
/*   Updated: 2023/07/03 12:42:00 by tknibbe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <token.h>

void	trim_undefined(t_data *data, char *input)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i< ft_strlen(input))
	{
		if (data->token[i] == UNDEFINED)
			j++;
		data->token[i] = data->token[i + j];
		input[i] = input[i + j];
		if (i + j > ft_strlen(input))
			data->token[i] = UNDEFINED;
		i++;
	}
	//while (i < ft_strlen(input))
	//	data->token[i++] = UNDEFINED;
	printf("%d undefs found\n%s\n", j, input);
}

int	whitespace(char c)
{
	if (c == ' ' || c == '\t' || c == '\n'\
		|| c == '\v' || c == '\f' || c == '\r')
		return (1);
	return (0);
}

void	set_rest_to_str(t_data *data, char *input)
{
	int	i;
	int	last_token;

	i = 0;
	last_token = 0;
	while (input[i])
	{
		if (input[i] != ' ' && data->token[i] == UNDEFINED)
		{
			while (whitespace(input[i]) == 0 && input[i])
			{
				if (last_token == EXEC)
					data->token[i] = INPUT;
				else
					data->token[i] = STRING;
				i++;
			}		
		}
		if (whitespace(input[i]) == 0)
			last_token = data->token[i];
		i++;
	}
}

/*returns 1 if input[i] is a metacharacter that should be interpreted. 0 if the char can be safely ignored*/
int	metachar(char *input, t_data *data, int i)
{
	char c;

	c = input[i];
	if (c == '|' || c == '<' || c == '>')
		return (1);
	if (c == '$' && data->token[i] != SQUOTE)
		return (1);
	return (0);
}

void find_options(t_data *data, char *input)
{
	int	i;
	
	i = 0;
	while (input[i])
	{
		if (input[i] == '-' && data->token[i] == UNDEFINED)
		{
			while (input[i])// && data->token[i] == UNDEFINED)
			{
				if (whitespace(input[i]) || metachar(input, data, i))
					break ;
				data->token[i] = OPTION;
				i++;
			}
		}
		i++;
	}
}

void	find_exec(t_data *data, char *input, int i)
{
	while (whitespace(input[i]))
		i++;
	while (input[i] && data->token[i] == UNDEFINED)
	{
		if (whitespace(input[i]))
			break ;
		data->token[i] = EXEC;
		i++;
	}
	while (input[i])
	{
		if (input[i] == '|')
			find_exec(data, input, i + 1);
		i++;
	}
}
