
#include <minishell.h>

void	free_list_struct(t_list *list);
void	free_t_str(t_str *cmd);
void	free_rdr(t_rdr	*rdr);

t_list	*parse_input(char *input)
{
	t_list	*list;
	t_list 	*temp;

	list = t_listnew();
	list->input = ft_strtrim(list->input, " ");
	tokenize(list);
	print_tokens(list, ft_strlen(list->input));
	if (check_syntax(list))
		return (NULL);
	if (split_pipelines(*input, list))
	{
		temp = list;
		while (temp)
		{
			parse(temp->input, temp);
			temp = temp->next;
		}
	}
	else
		parse(*input, list);
	//print_test(*list, input);
	print_whole_list(list);
	//while (all->list) // this loop frees all data that falls under t_list
	//{
	//	free_list_struct(all->list);
	//	all->list = all->list->next;
	//}
	return (list);
}

void	free_list_struct(t_list *list)
{
	t_exec	*exec;
	t_exec	*temp;
	t_list	*templist;

	templist = list;
	while (templist)
	{
		exec = templist->exec;
		free (templist->token);
		//free (templist->input); //TODO when its malloced by bonus parse func
		while (exec)
		{
			free_t_str(exec->cmd);
			free_rdr(exec->rdr);
			temp = exec;
			exec = exec->next;
			//printf("temp = %p, exec = %p\n", temp, exec);
			free(temp);
		}
		templist = templist->next; // free old templist?
	}
	free(list);
	list->next = NULL;
	list->exec = NULL;
}

void	free_rdr(t_rdr *rdr)
{
	t_rdr	*temp;
	t_str	*str;

	if (!rdr)
		return ;
	while (rdr)
	{
		free_t_str(rdr->file);
		temp = rdr;
		rdr = rdr->next;
		free(temp);
	}
}

void	free_t_str(t_str *cmd)
{
	t_str	*temp;

	if (!cmd)
		return ;
	while (cmd)
	{
		temp = cmd;
		free (temp->str);
		free(temp);
		cmd = cmd->next;
	}
}
