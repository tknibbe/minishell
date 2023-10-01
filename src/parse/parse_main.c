
#include <minishell.h>

t_list	*parse_input(char *input, t_env_info *env)
{
	t_list	*list;
	t_list	*temp;

	if (!input[0]) //if we go into a subshell and theres nothing in it
	{
		//free stuff
		// printf("no string left\n");
		env->last_exit_status = 1;
		return (NULL);
	}
	list = t_listnew();
	list->input = ft_strtrim(input, " ");
	tokenize(list);
	if (check_syntax(list, env))
		return (NULL);
	if (split_pipelines(input, &list)) // do i  need input here since it is in list?
	{
		temp = list;
		while (temp)
		{
			if (parse(temp->input, temp, env))
			{
				//need to free stuff here, this edit was necessary to implement syntax errors in the subshell
				return (NULL);
			}
			temp = temp->next;
		}
	}
	else
		if (parse(input, list, env))
		{
			// free stuff here, implemented syntax in subshells
			return (NULL);
		}
	return (list);
}
