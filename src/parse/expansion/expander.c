#include <minishell.h>
#include <expansion.h>

#define WORD 1

void	print_list(t_str *s)
{
	int	i = 1;
	while (s)
	{
		printf("%d: %s\n", i++, s->str);
		s = s->next;
	}
	printf("\n");
}

int	unclosed_quote(int state)
{
	write(2, "Warning: unclosed quote ( ", 26);
	write(2, &state, 1);
	write(2, " ) was ignored\n", 16);
	return (0);
}

int	skip_quoted_state(char *s, int i, int quote)
{
	while (s[i] && s[i] != quote)
		i++;
	if (!s[i])
		return (1);
	return (i + 1);
}

void	initialize_xp(t_exp *xp, char *input, t_env *head)
{
	xp->star = 0;
	xp->head = head;
	xp->result = NULL;
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

t_str	*insert_lst(char *var, t_env *env_head, char *s)
{
	t_str	*head;
	char	**result;
	int		i;
	t_exp	x;

	i = 0;
	head = NULL;
	initialize_xp(&x, s, env_head);
	if (s)
	{
		if (*s == '\'')
			expander('\'', "'", &x, s);
		else if (*s == '"')
			expander('"', "$\"", &x, s);
		else
			expander(0, "$\"'", &x, s);
		free(s);
	}
	if (var)
	{
		result = ft_split(var, ' ');
		if (!result)
			ft_exit("Malloc error\n", errno);
		if (var[0] != ' ')
		{
			s = result[0];
			result[0] = ft_join(x.result, result[0]);
			free(s);
		}
		else
			tstr_addback(&head, tstr_new(x.result));
		while (result[i])
			tstr_addback(&head, tstr_new(result[i++]));
		if (var[0] && var[ft_strlen(var) - 1] == ' ')
			tstr_addback(&head, tstr_new(NULL));
		free(result);
	}
	else if (x.result)
		tstr_addback(&head, tstr_new(x.result));
	return (head);
}

char	*create_sub(char *s, int i, int j)
{
	char	*sub;

	sub = NULL;
	if (j)
	{
		sub = ft_substr(s, i, j);
		if (!sub)
			ft_exit("Malloc error\n", errno);
	}
	return (sub);
}

void	split_word(t_str *start, t_env *head)
{
	int		i;
	int		j;
	char	*s;
	t_str	*splitted;
	t_str	*tmp;
	char	*sub;

	splitted = NULL;
	s = start->str;
	start->str = NULL;

	i = 0;
	while (s[i])
	{
		j = 0;
		while (s[i + j] && !ft_isinset(s[i + j], "'\"$"))
			j++;
		if (s[i + j] == '\'' || s[i + j] == '"' || !s[i + j])
		{
			if (s[i + j] == '\'' || s[i + j] == '"')
				j = skip_quoted_state(s + i, j + 1, s[i + j]);
			sub = create_sub(s, i, j);
			splitted = insert_lst(NULL, head, sub);
		}
		else if (s[i + j] == '$')
		{
			sub = create_sub(s, i, j);
			splitted = insert_lst(get_env(&s[i + ++j], head), head, sub);
			while (ft_isname(s[i + j]))
				j++;
		}
		if (splitted)
		{
			if (start->str)
			{
				start->str = ft_join(start->str, splitted->str);
				free(splitted->str);
			}
			else
				start->str = splitted->str;
			tmp = start->next;
			start->next = splitted->next;
			free(splitted);
			while (start->next)
				start = start->next;
			start->next = tmp;
		}
		i += j;
	}
}

char	**full_expansion(t_str *start, t_env *head)
{
	t_str	*next;

	while (start)
	{
		next = start->next;
		split_word(start, head);
		start = next;
	}
	return (NULL);
}

void	test_env_expansion_shit(t_ally *all, char *input)
{
	t_str *head = NULL;
	tstr_addback(&head, tstr_new(ft_strdup("$s\"ls\"$s-l$s-a$s\"-h\"$s")));
	// tstr_addback(&head, tstr_new(ft_strdup("-l''")));
	// tstr_addback(&head, tstr_new(ft_strdup("-a")));
	// tstr_addback(&head, tstr_new(ft_strdup("-h")));
	full_expansion(head, all->env->head);
	int	i = 1;
	while (head)
	{
		printf("%d %s\n", i++, head->str);
		head = head->next;
	}
}
