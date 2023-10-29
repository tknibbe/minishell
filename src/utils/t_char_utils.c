
# include "minishell.h"

t_str	*tstr_new(char *content)
{
	t_str	*new;

	new = malloc(sizeof(t_str));
	if (!new)
		ft_minishell_error("malloc()", NULL, strerror(errno), errno);
	new->next = NULL;
	new->str = content;
	return (new);
}

void	tstr_addback(t_str **head, t_str *new)
{
	t_str	*tmp;

	tmp = *head;
	if (*head == NULL)
		*head = new;
	else
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
}

void	tstr_addnext(t_str *current, t_str *new)
{
	t_str	*tmp;

	tmp = current->next;
	current->next = new;
	new->next = tmp;
}
