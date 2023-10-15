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
		x->result = ft_join(x->result, s); //TODO: leaks! with input: echo "echo HEY > cat" | ./minishell
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

char	**lst_to_dp(t_str *c)
{
	char	**result;
	int		i;

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
		c = c->next;
	}
	result[i] = NULL;
	return (result);
}

char	**full_expansion(t_str *c, t_env_info *e)
{
	if (!c)
		return (NULL);
	expansion_ws(c, e);
	expansion_wc(c);
	return (lst_to_dp(c));
}
