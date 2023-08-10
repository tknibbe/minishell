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

t_str	*get_insert_lst(char *var, t_env *env_head, char *s)
{
	t_exp	x;
	char	**result;
	int		i;

	i = 0;
	head = NULL;
	initialize_xp(&x, s, env_head);
	if (s)
		expand_string(s, &x);
	if (var)
		return (split_var(var, x.result));
	else if (x.result)
		return (tstr_new(x.result));
	return (NULL);
}

void	split_word(t_str *start, t_env *head)
{
	int		i;
	char	*s;
	char	*sub;
	t_str	*splitted;

	s = start->str;
	start->str = NULL;
	i = 0;
	while (s[i])
	{
		sub = create_sub(s, &i, 0);
		if (s[i] == '$')
		{
			splitted = get_insert_lst(get_env(&s[++i], head), head, sub);
			while (ft_isname(s[i]))
				i++;
		}
		else
			splitted = get_insert_lst(NULL, head, sub);
		insert_splitted(&start, splitted);
	}
	free(s);
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
	tstr_addback(&head, tstr_new(ft_strdup("kaas$s-ban$s-aan")));
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
