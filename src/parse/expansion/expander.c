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

char	*full_expansion(char *input, int *token, t_env *head)
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
		expand_wildcard(&xp.result, xp.star);
	printf("result = [> %s <]\n", xp.result);
	return (xp.result);
}

void	test_env_expansion_shit(t_ally *all, char *input)
{
	t_str *head = NULL;
	t_str_addback(&head, t_strnew(ft_strdup("ls")));
	t_str_addback(&head, t_strnew(ft_strdup("-l")));
	t_str_addback(&head, t_strnew(ft_strdup("-a")));
	t_str_addback(&head, t_strnew(ft_strdup("-h")));
	
}
