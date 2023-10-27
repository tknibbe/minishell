#include <built_ins.h>
#include <minishell.h>

t_env_info	*env_init(char **env)
{
	t_env		*head;
	t_env_info	*info;
	int			i;

	info = malloc(sizeof(t_env_info));
	if (!info)
		ft_minishell_error("malloc()", NULL, strerror(errno), errno);
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

void	swap(t_env *pwd, t_env *oldpwd, t_env_info *e)
{
	if (!pwd)
	{
		pwd = env_new("PWD=");
		env_addback(&e->head, pwd);
		e->count++;
	}
	if (!oldpwd)
	{
		oldpwd = env_new("OLDPWD=");
		env_addback(&e->head, oldpwd);
		e->count++;
	}
	free(oldpwd->value);
	oldpwd->value = pwd->value;
	pwd->value = getcwd(NULL, 0);
	if (!pwd->value)
		ft_minishell_error("getcwd()", NULL, strerror(errno), errno);
	update_env(pwd, e);
	update_env(oldpwd, e);
}

void	update_env(t_env *to_update, t_env_info *e)
{
	free(to_update->joined_value);
	to_update->joined_value = ft_envjoin(to_update->key, to_update->value);
	e->has_changed = 1;
}
