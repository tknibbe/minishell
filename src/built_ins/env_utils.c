#include <built_ins.h>
#include <minishell.h>

char	*ft_envjoin(char *s1, char *s2)
{
	char	*result;
	int		i;

	i = 0;
	result = malloc(ft_strlen(s1) + ft_strlen(s2) + 2);
	if (!result)
		ft_minishell_error("malloc()", NULL, strerror(errno), errno);
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

static char	*no_env(int c, int status)
{
	char	*value;

	if (c == '?')
		value = ft_itoa(status);
	else
		value = ft_strdup("$");
	if (!value)
		ft_minishell_error("malloc()", NULL, strerror(errno), errno);
	return (value);
}

/*
	finds value corrosponding with key in the environment
	and returns an allocated string
*/
char	*get_env(char *key, t_env_info *e)
{
	int		i;
	char	*value;
	t_env	*head;

	if (!ft_isname(*key))
		return (no_env(*key, e->last_exit_status));
	head = e->head;
	while (head)
	{
		i = 0;
		while (key[i] && head->key[i] == key[i])
			i++;
		if (!ft_isname(head->key[i]) && !ft_isname(key[i]))
		{
			value = ft_strdup(head->value);
			if (!value)
				ft_minishell_error("malloc()", NULL, strerror(errno), errno);
			return (value);
		}
		head = head->next;
	}
	return (NULL);
}

void	update_env(t_env *to_update, t_env_info *e)
{
	free(to_update->joined_value);
	to_update->joined_value = ft_envjoin(to_update->key, to_update->value);
	e->has_changed = 1;
}

void	get_environment_for_exec(t_env_info *e)
{
	t_env	*tmp;
	int		i;

	if (!(e->has_changed))
		return ;
	e->has_changed = 0;
	tmp = e->head;
	if (e->env)
		free(e->env);
	e->env = malloc((e->count + 1) * sizeof(char *));
	if (!e->env)
		ft_minishell_error("malloc()", NULL, strerror(errno), errno);
	i = 0;
	while (tmp)
	{
		e->env[i] = tmp->joined_value;
		tmp = tmp->next;
		i++;
	}
	e->env[i] = NULL;
}
