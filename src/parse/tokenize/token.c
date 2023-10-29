/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tknibbe <tknibbe@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 12:18:15 by tknibbe           #+#    #+#             */
/*   Updated: 2023/10/21 15:33:41 by tknibbe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

static void	set_token(t_list *list, char *input);

/*Description:
tokenize is a function used to analyze and tokenize an input string, populating
a t_list structure with tokens that represent different parts of the input. 
It also handles the detection of subshells and their tokens within the input.

Parameters:

list (t_list*): A pointer to a t_list structure that stores the input and its
tokens.*/
void	tokenize(t_list *list)
{
	int	len;

	len = ft_strlen(list->input);
	list->token = ft_calloc(sizeof(int), len + 1); // just a slight optimizations since we fill it with blankspace token or something else no need to calloc, use malloc instead
	if (!list->token)
		ft_minishell_error("malloc()", NULL, strerror(errno), errno);
	set_token(list, list->input);
}

int	is_rdr_pipe_amp(char *c, int i)
{
	if ((c[i] == '|' || c[i] == '<' || c[i] == '>') || \
		(c[i] == '&' && c[i + 1] == '&'))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

static int	is_closed_quote(char *input, int *end_quote, int i)
{
	char	quote;

	if (input[i] != '"' && input[i] != '\'')
		return (EXIT_SUCCESS);
	*end_quote = i + 1;
	quote = input[i];
	i++;
	while (input[i])
	{
		*end_quote += 1;
		if (input[i] == quote)
			return (EXIT_FAILURE);
		i++;
	}
	*end_quote = 0;
	return (EXIT_SUCCESS);
}

static void	norm_bs(t_list *list, char *input, int *i)
{
	if (is_rdr_pipe_amp(input, *i))
	{
		set_rdr_pipe_amp(list, input, i);
		*i += 1;
	}
	else if (input[*i] == '(' || input[*i] == ')')
	{
		sub_count(input[*i], 0);
		*i += 1;
	}
	else
	{
		if (!ft_whitespace(input[*i]) && input[*i] != '\'' && input[*i] != '"'
			&& input[*i] != '(' && input[*i] != ')')
			list->token[*i] = WORD;
		else
		{
			list->token[*i] = BLANK;
		}
		*i += 1;
	}
}

static void	set_token(t_list *list, char *input)
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
				list->token[i] = WORD;
				i++;
			}
		}
		else
			norm_bs(list, input, &i);
	}
	set_subshell(list, input);
}
