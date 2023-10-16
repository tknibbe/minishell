#include <expansion.h>

static t_str	*split_var(char *var, char *sub)
{
	char	**splitted_var;
	char	*willy;
	t_str	*head;
	int		i;

	splitted_var = ft_split(var, ' ');
	if (!splitted_var)
		ft_exit("Malloc error\n", errno);
	transform_wildcards(splitted_var);
	head = NULL;
	if (var[0] == ' ' && sub)
		tstr_addback(&head, tstr_new(sub));
	else if (splitted_var[0] && sub)
	{
		willy = splitted_var[0];
		splitted_var[0] = ft_join(sub, splitted_var[0]);
		free(willy);
	}
	i = 0;
	while (splitted_var[i])
		tstr_addback(&head, tstr_new(splitted_var[i++]));
	if (var[0] && var[ft_strlen(var) - 1] == ' ')
		tstr_addback(&head, tstr_new(NULL));
	free(splitted_var);
	return (head);
}

static t_str	*get_insert_lst(char *var, t_env_info *e, char *s)
{
	t_exp	x;
	int		i;
	t_str	*ret;

	i = 0;
	ret = NULL;
	initialize_xp(&x, e);
	if (s)
		expand_string(s, &x);
	if (var)
		ret = split_var(var, x.result);
	else if (x.result)
		ret = tstr_new(x.result);
	free(var);
	return (ret);
}

void	insert_list(t_str **start, t_str *list)
{
	t_str	*tmp;

	if (!list)
		return ;
	if (!(*start)->str)
		(*start)->str = list->str;
	else
	{
		(*start)->str = ft_join((*start)->str, list->str);
		free(list->str);
	}
	tmp = (*start)->next;
	(*start)->next = list->next;
	free(list);
	while ((*start)->next)
		(*start) = (*start)->next;
	(*start)->next = tmp;
}

void	split_word(t_str *start, t_env_info *e)
{
	int		i;
	char	*s;
	char	*sub;
	t_str	*splitted;

	s = start->str;
	start->str = NULL;
	i = 0;
	while (s[i])
	{
		sub = create_sub(s, &i, 0);
		if (s[i] == '$')
		{
			splitted = get_insert_lst(get_env(&s[++i], e), e, sub);
			if (s[i] == '?')
				i++;
			else
				while (ft_isname(s[i]))
					i++;
		}
		else
			splitted = get_insert_lst(NULL, e, sub);
		insert_list(&start, splitted);
	}
	free(s);
}
