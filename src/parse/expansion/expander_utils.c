#include <minishell.h>
#include <expansion.h>

char	*ft_join(char *s1, char *s2)
{
	int		len1;
	int		len2;
	int		i;
	char	*s;

	len1 = 0;
	len2 = 0;
	if (s1)
		len1 = ft_strlen(s1);
	if (s2)
		len2 = ft_strlen(s2);
	s = malloc(len1 + len2 + 1);
	if (!s)
		ft_exit("Malloc error\n", errno);
	i = 0;
	while (s1 && s1[i])
	{
		s[i] = s1[i];
		i++;
	}
	free(s1);
	while (s2 && *s2)
		s[i++] = *(s2++);
	s[i] = '\0';
	return (s);
}

void	expand_dollo(t_exp *x, int state, char *s, int i)
{
	char	*value;

	if (s)
	{
		x->result = ft_join(x->result, s);
		free(s);
	}
	s = get_env(&x->input[i], x->head);
	if (s)
	{
		x->result = ft_join(x->result, s);
		free(s);
	}
	while (ft_isname(x->input[i]))
		i++;
	x->input += i;
	x->token += i;
	if (state == '"')
		return (expander(state, "\"$", x));
	return (expander(state, "\"'$", x));
}

int	identify_substr(t_exp *x, int state, char *brake, char **s)
{
	int	i;

	i = 0;
	while (x->input[i] && x->token[i] == WORD && !ft_isinset(x->input[i], brake))
	{
		if (!state && x->input[i] == '*')
			x->star++;
		i++;
	}
	if (!i)
		return (0);
	*s = ft_substr(x->input, 0, i);
	if (!(*s))
		ft_exit("Malloc error\n", errno);
	return (i);
}
