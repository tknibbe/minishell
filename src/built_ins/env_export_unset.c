#include <built_ins.h>
#include <minishell.h>
#include <expansion.h>

int	valid_identifier(char *s)
{
	int	i;

	i = 0;
	while (ft_isname(s[i]))
		i++;
	if (s[i])
		return (0);
	return (1);
}

int	legit_export_item(char *to_export)
{
	int		i;

	i = 0;
	while (ft_isname(to_export[i]))
		i++;
	if (!to_export[i])
		return (1);
	else if (to_export[i] == '=')
		return (0);
	else if (to_export[i] == '+' && to_export[i + 1] == '=')
		return (0);
	return (2);
}

int	find_and_unset(t_env **env, char *unset)
{
	int		len;
	t_env	*prev;
	t_env	*curr;

	len = ft_strlen(unset) + 1;
	prev = NULL;
	curr = *env;
	while (curr)
	{
		if (!ft_strncmp(curr->key, unset, len))
		{
			if (prev)
				prev->next = curr->next;
			else
				*env = curr->next;
			free(curr->key);
			free(curr->value);
			free(curr);
			return (1);
		}
		prev = curr;
		curr = curr->next;
	}
	return (0);
}

int	find_and_export(t_env *head, char *to_export)
{
	int	i;

	while (head)
	{
		i = 0;
		while (head->key[i] == to_export[i])
			i++;
		if (!head->key[i] && to_export[i] == '=')
		{
			free(head->value);
			head->value = ft_strdup(&to_export[i + 1]);
			return (1);
		}
		else if (!head->key[i] && to_export[i] == '+')
		{
			head->value = ft_join(head->value, &to_export[i + 2]);
			return (1);
		}
		head = head->next;
	}
	return (0);
}