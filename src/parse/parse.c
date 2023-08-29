
#include <minishell.h>

void	free_list_struct(t_list *list);
void	free_t_str(t_str *cmd);
void	free_rdr(t_rdr	*rdr);

t_list	*parse_input(char *input)
{
	t_list	*list;
	t_list	*temp;

	list = t_listnew();
	list->input = ft_strtrim(input, " ");
	tokenize(list);
	//print_tokens(list, ft_strlen(list->input));
	if (check_syntax(list))
		return (NULL);
	if (split_pipelines(input, &list))
	{
		temp = list;
		while (temp)
		{
			//printf("temp->input = %s\n", temp->input);
			//printf("______list address %p\n", list);
			parse(temp->input, temp);
			temp = temp->next;
		}
	}
	else
		parse(input, list);
	//print_test(*list, input);
	//print_whole_list(list);
	//while (all->list) // this loop frees all data that falls under t_list
	//{
	//	free_list_struct(all->list);
	//	all->list = all->list->next;
	//}
	return (list);
}
