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

int	expand_dollo(t_exp *x, char **s, int i)
{
	char	*value;

	value = get_env(&x->input[i], x->head);
	if (value)
	{
		*s = ft_join(*s, value);
		free(value);
	}
	while (ft_isname(x->input[i]))
		i++;
	return (i);
}

void	append_sub(char **s, char *input, int len)
{
	char	*str;

	str = ft_substr(input, 0, len);
	if (!str)
		ft_exit("Malloc error\n", errno);
	*s = ft_join(*s, str);
	free(str);
}

int	identify_substr(t_exp *x, int state, char *brake, char **s)
{
	char	*str;
	int		i;
	int		j;

	i = 0;
	while (x->input[i] && x->input[i] != state)
	{
		j = 0;
		while (x->input[i + j] && x->token[i + j] == WORD && !ft_isinset(x->input[i + j], brake))
		{
			if (!state && x->input[i + j] == '*')
				x->star++;
			j++;
		}
		if (j)
			append_sub(s, &x->input[i], j);
		i += j;
		if (x->input[i] == '$')
			i = expand_dollo(x, s, (i + 1));
		else if (ft_isinset(x->input[i], brake))
			break ;
	}
	return (i);
}
