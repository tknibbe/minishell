
#include "minishell.h"

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
		ft_minishell_error("malloc()", NULL, "malloc failed", errno);
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

int	expand_dollo(t_exp *x, char *input, char **s, int i)
{
	char	*value;

	value = get_env(&input[i], x->e);
	if (value)
	{
		*s = ft_join(*s, value);
		free(value);
	}
	if (input[i] == '?')
		i++;
	else
	{
		while (ft_isname(input[i]))
			i++;
	}
	return (i);
}

void	append_sub(char **s, char *input, int len)
{
	char	*str;

	str = ft_substr(input, 0, len);
	if (!str)
		ft_minishell_error("malloc()", NULL, strerror(errno), errno);
	*s = ft_join(*s, str);
	free(str);
}

char	*get_brake(int state)
{
	if (state == '\'')
		return ("'");
	else if (state == '"')
		return ("$\"");
	return ("$\"'");
}

char	**lst_to_dp(t_str *c)
{
	char	**result;
	int		i;

	result = malloc((amount(c) + 1) * sizeof(char *));
	if (!result)
		ft_minishell_error("malloc()", NULL, strerror(errno), errno);
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