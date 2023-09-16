#include <built_ins.h>
#include <minishell.h>

/*will print out all keys with their value's*/
int	env(t_env *env)
{
	
	while (env)
	{
		printf("%s=%s\n", env->key, env->value);
		env = env->next;
	}
	return (0);
}

/*will create or adjust a node for export*/
int	export(t_env_info *e, char **to_export)
{
	int		i;
	int		mode;
	int		ret;

	i = 1;
	ret = 0;
	free(to_export[0]);
	while (to_export[i])
	{
		mode = legit_export_item(to_export[i]);
		if (mode < 1)
		{
			if (!find_and_export(e->head, to_export[i]))
			{
				env_addback(&e->head, env_new(to_export[i]));
				e->count++;
			}
			e->has_changed = 1;
		}
		else if (mode > 1)
			ret = ft_minishell_error("export", to_export[i], "not a valid identifier", 0);
		free(to_export[i++]);
	}
	free(to_export);
	return (ret);
}

/*will unset a variable given the key*/
int	unset(t_env_info *e, char **unset)
{
	int	i;
	int	ret;

	i = 1;
	free(unset[0]);
	ret = 0;
	while (unset[i])
	{
		if (valid_identifier(unset[i]))
		{
			if (find_and_unset(&e->head, unset[i]))
			{
				e->has_changed = 1;
				e->count--;
			}
		}
		else
			ret = ft_minishell_error("export", unset[i], "not a valid identifier", 0);
		free(unset[i]);
		i++;
	}
	free(unset);
	return (ret);
}
