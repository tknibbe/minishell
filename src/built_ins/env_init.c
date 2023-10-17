#include <built_ins.h>
#include <minishell.h>

t_env_info	*env_init(char **env)
{
	t_env		*head;
	t_env		*tmp;
	t_env_info	*info;
	int			i;

	info = malloc(sizeof(t_env_info));
	if (!info)
		ft_exit("Error: malloc failure\n", errno);
	i = 0;
	head = NULL;
	while (env[i])
		env_addback(&head, env_new(env[i++]));
	info->count = i;
	info->has_changed = 1;
	info->head = head;
	info->last_exit_status = 0;
	info->env = NULL;
	return (info);
}

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
	new->joined_value = ft_strdup(s);
	if (!new->joined_value)
		ft_exit("Error: malloc failure\n", errno);
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
