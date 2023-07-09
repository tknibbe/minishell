/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   define.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: tknibbe <tknibbe@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/30 14:04:57 by tknibbe       #+#    #+#                 */
/*   Updated: 2023/07/09 11:54:36 by cvan-sch      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <token.h>
#include <minishell.h>

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

int	valid_var_name(t_data *data, char *input, int i)
{
	if (whitespace(input[i - 1]))
		return (0);
	while ((data->token[i] != DQUOTE || data->token[i] == SQUOTE) \
			&& data->token[i] != UNDEFINED && i > 0)
	{
		i--;
	}
	printf("checking [%c]\n", input[i]);
	if (whitespace(input[i]))
		i++;
	if ((input[i] >= '0' && input[i] <= '9') || input[i] == '=')
		return (0);
	while (input[i] != '=')
	{
		if (!is_alphanumeric(input[i]))
			return (0);
		i++;
	}
	return (1);
}

int	valid_var_input(t_data *data, char *input, int i)
{
	data = NULL;
	if (whitespace(input[i + 1]))
		return (0);
	return (1);
}

void	set_name_and_input(t_data *data, char *input, int i)
{
	while (data->token[i] == EXEC && i > 0)
		i--;
	while (input[i] != '=')
	{
		data->token[i] = VARIABLE;
		i++;
	}
	data->token[i] = EQUALS;
	i++;
	while (input[i] && data->token[i] == EXEC)
	{
		data->token[i] = STRING;
		i++;
	}
}

void	find_define(t_data *data, char *input)
{
	int	i;

	i = 0;
	while (input[i])
	{
		if (input[i] == '=' && data->token[i - 1] != SQUOTE \
			&& data->token[i - 1] != DQUOTE)
		{
			if (valid_var_name(data, input, i) && \
				valid_var_input(data, input, i))
			{
				set_name_and_input(data, input, i);
			}
		}
		i++;
	}
}
