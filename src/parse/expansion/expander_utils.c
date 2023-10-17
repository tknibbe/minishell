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
	{
		return (i++);
	}
	while (ft_isname(input[i]))
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

char	*get_brake(int state)
{
	if (state == '\'')
		return ("'");
	else if (state == '"')
		return ("$\"");
	return ("$\"'");
}

int	identify_substr(t_exp *x, int state, char *input, char **s)
{
	char	*brake;
	int		i;
	int		j;

	i = 0;
	brake = get_brake(state);
	while (input[i] && input[i] != state) //  change statement so it also includes lowest elseif
	{
		j = 0;
		while (input[i + j] && !ft_isinset(input[i + j], brake))
		{
			if (!state && input[i + j] == '*')
				input[i + j] = -1;
			j++;
		}
		if (j)
			append_sub(s, &input[i], j);
		i += j;
		if (input[i] == '$')
			i = expand_dollo(x, input, s, (i + 1));
		else if (ft_isinset(input[i], brake))
			break ;
		//printf("string: %s, input[i]: %c\n", *s, input[i]);
	}
	return (i);
}
