#include <built_ins.h>
#include <minishell.h>

void	free_env(char **env)
{
	int	i;

	i = 0;
	if (!env)
		return ;
	while (env[i])
		free(env[i++]);
	free(env);
}

char	*ft_envjoin(char *s1, char *s2)
{
	char	*result;
	int		i;

	i = 0;
	result = malloc(ft_strlen(s1) + ft_strlen(s2) + 2);
	if (!result)
		ft_exit("Malloc error\n", errno);
	while (*s1)
	{
		result[i++] = *s1;
		s1++;
	}
	result[i++] = '=';
	while (*s2)
	{
		result[i++] = *s2;
		s2++;
	}
	result[i] = '\0';
	return (result);
}

void	create_env_for_execution(t_env_info *e)
{
	char	**new_env;
	t_env	*tmp;
	int		i;

	if (!(e->has_changed))
		return ;
	e->has_changed = 0;
	i = 0;
	free_env(e->env);
	tmp = e->head;
	new_env = malloc((e->count + 1) * sizeof(char *));
	if (!new_env)
		ft_exit("Malloc error\n", errno);
	while (tmp)
	{
		new_env[i] = tmp->joined_value;
		tmp = tmp->next;
	}
}
