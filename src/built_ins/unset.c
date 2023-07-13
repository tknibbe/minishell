#include <env.h>
#include <minishell.h>

void	add_the_rest(t_env_info *e, t_env *env, char **to_export)
{
	int	i;
	
	i = 0;
	while (to_export[i])
	{
		env_addback(&env, env_new(to_export[i]));
		e->count++;
		i++;
	}
}

void	move_pointer(char **s, int i)
{
	int	k;

	k = i;
	while (s[k + 1])
		k++;
	free(s[i]);
	s[i] = s[k];
	s[k] = NULL;
}

static void	release_node(t_env **env, t_env **c, t_env **p)
{
	if (*p)
		(*p)->next = (*c)->next;
	else
		*env = (*c)->next;
	free((*c)->key);
	free((*c)->value);
	free((*c));
	if (*p)
		*c = (*p)->next;
	else
		*c = *env;
}

void	unset(t_env_info *e, char **to_unset)
{
	int		i;
	int		cmp;
	t_env	*curr;
	t_env	*prev;
	
	i = 0;
	prev = NULL;
	curr = e->head;
	while (curr)
	{
		i = 0;
		cmp = ft_strlen(curr->key);
		while (to_unset[i])
		{
			if (!ft_strncmp(curr->key, to_unset[i], cmp))
			{
				release_node(&e->head, &curr, &prev);
				e->count--;
				e->has_changed = 1;
				break ;
			}
			i++;
		}
		if (!to_unset[i])
		{
			prev = curr;
			curr = curr->next;
		}
	}
}
