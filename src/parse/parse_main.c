
#include <minishell.h>

t_list	*parse_input(char *input)
{
	t_list	*list;
	t_list	*temp;

	list = t_listnew();
	list->input = ft_strtrim(input, " ");
	tokenize(list);
	if (check_syntax(list))
		return (NULL);
	if (split_pipelines(input, &list))
	{
		temp = list;
		while (temp)
		{
			parse(temp->input, temp);
			temp = temp->next;
		}
	}
	else
		parse(input, list);
	return (list);
}
