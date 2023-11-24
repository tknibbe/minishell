/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tknibbe <tknibbe@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 12:33:58 by tknibbe           #+#    #+#             */
/*   Updated: 2023/11/15 12:33:59 by tknibbe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	expansion_wc(t_str *s)
{
	t_str	*matched;
	int		i;

	while (s)
	{
		matched = NULL;
		if (!s->str)
			return ;
		if (check_for_wildcard(s->str))
		{
			expand_wildcard(s->str, &matched, NULL);
			if (matched)
			{
				free(s->str);
				s->str = NULL;
				insert_list(&s, matched);
				continue ;
			}
			i = 0;
			while (s->str[i])
				if (s->str[i++] == -1)
					s->str[i - 1] = '*';
		}
		s = s->next;
	}
}

static void	expansion_ws(t_str *start, t_env_info *e)
{
	t_str	*next;

	while (start)
	{
		next = start->next;
		split_word(start, e);
		start = next;
	}
}

static int	identify_substr(t_exp *x, int state, char *input, char **s)
{
	char	*brake;
	int		i;
	int		j;

	i = 0;
	brake = get_brake(&state);
	while (input[i] && input[i] != state)
	{
		j = 0;
		while (input[i + j] && !ft_isinset(input[i + j], brake))
		{
			if (!state && input[i + j] == '*')
				input[i + j] = -1;
			j++;
		}
		if (j)
			append_sub(s, &input[i], j);
		i += j;
		if (input[i] == '$')
			i = expand_dollo(x, input, s, i + 1);
		if (ft_isinset(input[i], brake))
			break ;
	}
	return (i);
}

void	expander(int state, t_exp *x, char *input)
{
	int		i;
	char	*s;

	s = NULL;
	if (!(*input))
		return ;
	if (state == *input)
		input++;
	i = identify_substr(x, state, input, &s);
	if ((state && state == input[i]) || !state)
		x->result = ft_join(x->result, s);
	free(s);
	if (state && state == input[i])
		i++;
	input += i;
	if (*input == '\'')
		return (expander('\'', x, input));
	else if (*input == '"')
		return (expander('"', x, input));
	return (expander(0, x, input));
}

char	**full_expansion(t_str *c, t_env_info *e)
{
	if (!c)
		return (NULL);
	expansion_ws(c, e);
	expansion_wc(c);
	return (lst_to_dp(c));
}
