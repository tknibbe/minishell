/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tknibbe <tknibbe@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 20:18:58 by cvan-sch          #+#    #+#             */
/*   Updated: 2023/09/09 13:44:15 by tknibbe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <expansion.h>

static void	expansion_wc(t_str *s)
{
	t_str	*matched;
	int		i;

	while (s)
	{
		if (!s->str)
			return ;
		if (check_for_wildcard(s->str))
		{
			matched = expand_wildcard(s->str);
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
	if (state && state == input[i])
		i++;
	else if (state && !input[i])
		i = unclosed_quote(state);
	input += i;
	free(s);
	if (*input == '\'')
		return (expander('\'', x, input));
	else if (*input == '"')
		return (expander('"', x, input));
	return (expander(0, x, input));
}

char	**full_expansion(t_str *c, t_env_info *e)
{
	char	**result;
	t_str	*willy;
	int		i;

	if (!c)
		return (NULL);
	expansion_ws(c, e);
	expansion_wc(c);
	result = malloc((amount(c) + 1) * sizeof(char *));
	if (!result)
		ft_exit("Malloc error\n", errno);
	i = 0;
	while (c)
	{
		if (c->str)
		{
			result[i++] = c->str;
			c->str = NULL;
		}
		willy = c;
		c = c->next;
	}
	result[i] = NULL;
	return (result);
}
