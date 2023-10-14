/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tknibbe <tknibbe@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 14:56:52 by tknibbe           #+#    #+#             */
/*   Updated: 2023/10/01 16:19:40 by tknibbe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <parsing.h>

static void	continued(t_list *list, char *input, int *i)
{
	if (input[*i] == '<')
		left(list, input, i);
	else if (input[*i] == '>')
		right(list, input, i);
}

void	set_rdr_pipe_amp(t_list *list, char *input, int *i)
{
	if (input[*i] == '&')
	{
		if (input[*i + 1] == '&')
		{
			list->token[*i] = AND;
			list->token[*i + 1] = AND;
			*i += 1;
		}
	}
	else if (input[*i] == '|')
	{
		if (input[*i + 1] == '|')
		{
			list->token[*i] = OR;
			list->token[*i + 1] = OR;
			*i += 1;
		}
		else
			list->token[*i] = PIPESYMBOL;
	}
	else
		continued(list, input, i);
}

void	left(t_list *list, char *input, int *i)
{
	if (input[*i + 1] == '<')
	{
		list->token[*i] = HEREDOC;
		list->token[*i + 1] = HEREDOC;
		*i += 1;
	}
	else
		list->token[*i] = REDIRLEFT;
}

void	right(t_list *list, char *input, int *i)
{
	if (input[*i + 1] == '>')
	{
		list->token[*i] = APPEND;
		list->token[*i + 1] = APPEND;
		*i += 1;
	}
	else
		list->token[*i] = REDIRRIGHT;
}

int	is_alphanumeric(char c)
{
	if (c >= '0' && c <= '9')
		return (EXIT_FAILURE);
	if (c >= 'a' && c <= 'z')
		return (EXIT_FAILURE);
	if (c >= 'A' && c <= 'Z')
		return (EXIT_FAILURE);
	if (c == '_')
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
