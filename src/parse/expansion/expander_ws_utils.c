#include <parsing.h>
#include <minishell.h>
#include <expansion.h>

void	expand_string(char *s, t_exp *x)
{
	if (*s == '\'')
		expander('\'', x, s);
	else if (*s == '"')
		expander('"', x, s);
	else
		expander(0, x, s);
	free(s);
}

void	transform_wildcards(char **s)
{
	int	i;

	while (*s)
	{
		i = 0;
		while ((*s)[i])
		{
			if ((*s)[i] == '*')
				(*s)[i] = -1;
			i++;
		}
		s++;
	}
}

char	*create_sub(char *s, int *i, int j)
{
	char	*sub;
	int		quote;

	while (s[*i + j] && s[*i + j] != '$')
	{
		while (s[*i + j] && !ft_isinset(s[*i + j], "\"'$"))
			j++;
		if (s[*i + j] == '\'' || s[*i + j] == '"')
		{
			quote = *i + j++;
			while (s[*i + j] && s[*i + j] != s[quote])
				j++;
			if (!s[*i + j])
				j = quote - *i + 1;
		}
		else if (s[*i + j] == '$' && !ft_isname(s[*i + j + 1]) && !ft_isinset(s[*i + j + 1], "?$"))
			j++;
	}
	if (!j)
		return (NULL);
	sub = ft_substr(s, *i, j);
	if (!sub)
		ft_minishell_error("malloc()", NULL, strerror(errno), errno);
	*i += j;
	return (sub);
}
