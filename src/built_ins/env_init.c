#include "minishell.h"

t_env_info	*env_init(char **env)
{
	t_env_info	*info;
	int			i;

	i = 0;
	info = malloc(sizeof(t_env_info));
	if (!info)
		ft_minishell_error("malloc()", "allocating t_env_info", \
			strerror(errno), errno);
	info->head = NULL;
	while (env[i])
		env_addback(&info->head, env_new(env[i++]));
	info->count = i;
	info->has_changed = 1;
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
		ft_minishell_error("malloc()", NULL, strerror(errno), errno);
	while (s[i] && s[i] != '=')
		i++;
	new->key = ft_substr(s, 0, i);
	if (!new->key)
		ft_minishell_error("malloc()", NULL, strerror(errno), errno);
	new->value = ft_strdup(s + i + 1);
	if (!new->value)
		ft_minishell_error("malloc()", NULL, strerror(errno), errno);
	new->joined_value = ft_strdup(s);
	if (!new->joined_value)
		ft_minishell_error("malloc()", NULL, strerror(errno), errno);
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
