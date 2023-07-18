#include <minishell.h>

int	ft_iswhitespace(int	c)
{
	return (c == 32 || (c >= 9 && c <= 13));
}

int	ft_isname(int c)
{
	return ((c >= '0' && c <='9') || (c >= 'a' && c <='z') || (c >= 'A' && c <='Z') || c == '_');
}

int	ft_isinset(int c, char *s)
{
	while (*s)
	{
		if (*s == c)
			return (1);
		s++;
	}
	return (0);
}