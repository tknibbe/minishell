#include <minishell.h>
#include <expansion.h>

#define WORD 1

int	unclosed_quote(int state)
{
	write(2, "Warning: unclosed quote ( ", 26);
	write(2, &state, 1);
	write(2, " ) was ignored\n", 16);
	return (0);
}

void	expander(int state, char *brake, t_exp *x)
{
	int		i;
	char	*s;

	s = NULL;
	if (!(*x->input))
		return ;
	if (state == *x->input)
		x->input++;
	i = identify_substr(x, state, brake, &s);
	if ((state && state == x->input[i]) || !state)
		x->result = ft_join(x->result, s);
	if (state && state == x->input[i])
		i++;
	else if (state && !x->input[i])
		i = unclosed_quote(state);
	x->input += i;
	x->token += i;
	free(s);
	if (*x->input == '\'')
		return (expander('\'', "'", x));
	else if (*x->input == '"')
		return (expander('"', "$\"", x));
	return (expander(0, "$\"'", x));
}

void	full_expansion(char *input, int *token, t_env *head, t_char *res)
{
	t_exp	xp;

	xp.star = 0;
	xp.result = NULL;
	xp.input = input;
	xp.token = token;
	xp.head = head;
	if (*xp.input == '\'')
		expander('\'', "'", &xp);
	else if (*xp.input == '"')
		expander('"', "$\"", &xp);
	else
		expander(0, "$\"'", &xp);
	if (xp.star)
		xp.result = expand_wildcard(xp.result, xp.star, ft_strdup("."));
	printf("result = [> %s <]\n", xp.result);
	return (xp.result);
}

void	test_env_expansion_shit(t_ally *all, char *input)
{
	int	*token = malloc((ft_strlen(input) + 1) * sizeof(int));
	for (int i = 0; i < ft_strlen(input); i++)
		token[i] = 1;
	token[ft_strlen(input)] = 0;
	full_expansion(input, token, all->env->head);
}
