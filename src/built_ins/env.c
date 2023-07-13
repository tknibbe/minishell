#include <built_ins.h>
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

/*the function will check if the name pointed to by 's' is a valid name 
a valid name is defined as a word comprised of only letters, numbers and or lower dash
it can also not start as a number as those are reserved*/
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

/*when called the function will loop through the already existing env linked list and print both key and value*/
void	env(t_env *env)
{
	while (env)
	{
		printf("%s\n", env->joined_value);
		env = env->next;
	}
}

/*env_init is a call to initialize the environment it creates the struct with data about the environment
and will also put all the inherited env_variables in a linked list that can be modified for later use*/
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
		env_addback(&head, env_new(env[i++]));
	info->count = i;
	info->has_changed = 1;
	info->head = head;
	info->env = NULL;
	return (info);
}
