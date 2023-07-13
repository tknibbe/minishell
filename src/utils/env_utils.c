#include <minishell.h>

char *get_env(char *key, t_env *head)
{
	int	len;

	len = ft_strlen(key) + 1;
	while (head)
	{
		if (!ft_strncmp(key, head->key, len))
			return (head->value);
	}
	return (NULL);
}
