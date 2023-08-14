/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expander.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: cvan-sch <cvan-sch@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/14 20:18:58 by cvan-sch      #+#    #+#                 */
/*   Updated: 2023/08/14 21:47:38 by cvan-sch      ########   odam.nl         */
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

static void	expansion_ws(t_str *start, t_env *head)
{
	t_str	*next;

	while (start)
	{
		next = start->next;
		split_word(start, head);
		start = next;
	}
}

void	expander(int state, char *brake, t_exp *x, char *input)
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
		return (expander('\'', "'", x, input));
	else if (*input == '"')
		return (expander('"', "$\"", x, input));
	return (expander(0, "$\"'", x, input));
}

char	**full_expansion(t_str *c, t_env *head)
{
	char	**result;
	t_str	*willy;
	int		i;

	expansion_ws(c, head);
	expansion_wc(c);
	result = malloc((amount(c) + 1) * sizeof(char *));
	if (!result)
		ft_exit("Malloc error\n", errno);
	i = 0;
	while (c)
	{
		if (c->str)
			result[i++] = c->str;
		willy = c;
		c = c->next;
		free(willy);
	}
	result[i] = NULL;
	return (result);
}
