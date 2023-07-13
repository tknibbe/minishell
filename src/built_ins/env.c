#include <env.h>
#include <minishell.h>

t_env	*env_new(char *s)
{
	t_env	*new;
	int		i;

	i = 0;
	new = malloc(sizeof(t_env));
	if (!new)
		ft_exit("Error: malloc failure\n", errno);
	while (s[i] && s[i] != '=')
		i++;
	new->key = ft_substr(s, 0, i);
	if (!new->key)
		ft_exit("Error: malloc failure\n", errno);
	new->value = ft_strdup(s + i + 1);
	if (!new->value)
		ft_exit("Error: malloc failure\n", errno);
	new->joined_value = ft_envjoin(new->key, new->value);
	new->next = NULL;
	return (new);
}

void	env_addback(t_env **head, t_env *new)
{
	t_env	*tmp;

	tmp = *head;
	if (!(*head))
		*head = new;
	else
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
}

unsigned int	check_valid_name(char *s)
{
	unsigned int	i;

	i = 0;
	if (ft_isdigit(s[0]) || s[i] == '=')
		return (1);
	while (s[i])
	{
		if (ft_isalnum(s[i]) || s[i] == '_')
		{
			i++;
			continue ;
		}
		if (s[i] == '=' || (s[i] == '+' && s[i + 1] == '='))
			return (0);
		break ;
	}
	return (1);
}

void	env(t_env *env)
{
	while (env)
	{
		printf("%s=%s\n", env->key, env->value);
		env = env->next;
	}
}

t_env_info	*env_init(char **env)
{
	t_env		*head;
	t_env_info	*info;
	int		i;

	info = malloc(sizeof(t_env_info));
	if (!info)
		ft_exit("Error: malloc failure\n", errno);
	i = 0;
	head = NULL;
	while (env[i])
	{
		if (!check_valid_name(env[i]))
			env_addback(&head, env_new(env[i]));
		i++;
	}
	info->count = i;
	info->has_changed = 1;
	info->head = head;
	info->env = NULL;
	return (info);
}
