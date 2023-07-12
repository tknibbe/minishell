#include <env.h>
#include <minishell.h>

static int	cmp_until_equals(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] && s1[i] == s2[i])
		i++;
	if (!s1[i] && s2[i] == '=')
		return (1);
	if (!s1[i] && s2[i] && s2[i] == '+' && s2[i + 1] == '=')
		return (2);
	return (0);
}

static void	replace_value(t_env *env, char **s, int i)
{
	int	j;

	j = 0;
	while (s[i][j] != '=')
		j++;
	j++;
	free(env->value);
	env->value = ft_strdup(&s[i][j]);
	if (!env->value)
		ft_exit("Error: malloc failure\n", errno);
	move_pointer(s, i);
}

static void	join_value(t_env *env, char **s, int i)
{
	int		j;
	char	*result;

	j = 0;
	while (s[i][j] != '=')
		j++;
	result = ft_strjoin(env->value, &s[i][j + 1]);
	if (!result)
		ft_exit("Error: malloc failure\n", errno);
	free(env->value);
	env->value = result;
	move_pointer(s, i);
}

void	filter_valid_export_item(char **s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (check_valid_name(s[i]))
			move_pointer(s, i);
		else
			i++;
	}
}

void	export(t_env *env, char **to_export)
{
	int	i;
	int	j;

	filter_valid_export_item(to_export);
	while (env)
	{
		i = 0;
		while (to_export[i])
		{
			j = cmp_until_equals(env->key, to_export[i]);
			if (!j)
			{
				i++;
				continue ;
			}
			else if (j == 1)
				replace_value(env, to_export, i);
			else
				join_value(env, to_export, i);
			break ;
		}
		if (!env->next)
			break ;
		env = env->next;
	}
	add_the_rest(env, to_export);
}
