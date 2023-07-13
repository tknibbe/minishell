#include <minishell.h>

char	*get_env(char *key, char **env)
{
	char	*mod_key;
	int		len;

	mod_key = ft_strjoin(key, "=");
	if (!mod_key)
		ft_exit("Error: malloc failure\n", errno); 
	len = ft_strlen(mod_key);
	while (*env)
	{
		if (!ft_strncmp(*env, mod_key, len))
		{
			free(mod_key);
			mod_key = ft_strdup(&(*env)[len]);
			if (!mod_key)
				ft_exit("Error: malloc failure\n", errno);
			return (mod_key);
		}
		env++;
	}
	free(mod_key);
	return (NULL);
}
