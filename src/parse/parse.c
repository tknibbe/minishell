
#include <minishell.h>

void	free_list_struct(t_list *list);
void	free_t_str(t_str *cmd);
void	free_rdr(t_rdr	*rdr);

void	parse_input(char **input, t_ally *all)
{
	t_list	*temp;

	tokenize(*input, all->list);
	if (check_syntax(all->list, input))
		return ;
	if (split_pipelines(*input, all))
	{
		temp = all->list;
		while (temp)
		{
			parse(temp->input, temp);
			temp = temp->next;
		}
	}
	else
		parse(*input, all->list);
	//print_test(*list, input);
	//print_tokens(all->list, ft_strlen(*input));
	print_whole_list(all->list);
	//while (all->list) // this loop frees all data that falls under t_list
	//{
	//	free_list_struct(all->list);
	//	all->list = all->list->next;
	//}
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
		free (temp->s);
		free(temp);
		cmd = cmd->next;
	}
}
