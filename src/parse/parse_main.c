
#include <minishell.h>

t_list	*parse_input(char *input)
{
	t_list	*list;
	t_list	*temp;

	if (!input[0]) //if we go into a subshell and theres nothing in it
		return (NULL);
	list = t_listnew();
	list->input = ft_strtrim(input, " ");
	tokenize(list);
	//printf("input is : [%s]\n", input);
	//print_tokens(list, ft_strlen(input));
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
